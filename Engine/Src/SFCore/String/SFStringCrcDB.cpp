////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StringCrc64 DB for reverse crc
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "String/SFHasher32.h"
#include "String/SFHasher64.h"
#include "String/SFStringCrcDB.h"
#include "String/SFStrFormat.h"
#include "Service/SFService.h"
#include "Stream/SFStream.h"
#include "Types/SFEngineTypeSerialization.h"


namespace SF
{

	const StringCrcDB::StringItem* StringCrcDB::StringBuffer::AddString(uint64_t hash64, uint32_t hash32, const char* string, size_t strLen)
	{
		auto requiredSize = strLen + 1;
		requiredSize = AlignUp(requiredSize, 8);
		if (string == nullptr || RemainSize < requiredSize)
			return nullptr;

		auto stringItem = (StringItem*)StringItems + (BufferSize - RemainSize);
		stringItem->Hash64 = hash64;
		stringItem->Hash32 = hash32;
		stringItem->ValueSize = (uint32_t)(requiredSize - sizeof(StringItem));

		memcpy(stringItem->StringValue, string, strLen);
		stringItem->StringValue[strLen] = '\0';

		RemainSize -= requiredSize; // Include null terminate

		return stringItem;
	}


	StringCrcDB::StringCrcDB()
		: m_Heap("StringCrcDB", GetSystemHeap())
		, m_StringMap32(m_Heap)
		, m_StringMap64(m_Heap)
	{
		Service::StringDB = this;
	}

	StringCrcDB::~StringCrcDB()
	{
		Clear();
	}


	// Clear and release all memory
	void StringCrcDB::Clear()
	{
		auto pCurBlock = m_Head;
		while (pCurBlock != nullptr)
		{
			auto pNext = pCurBlock->Next;
			free(pCurBlock);
			pCurBlock = pNext;
		}
		m_Head = nullptr;

		m_StringMap32.clear();
		m_StringMap64.clear();
	}

	// Load string table file
	bool StringCrcDB::LoadStringTable(IInputStream& stream)
	{
		// FILE_MAGIC
		uint64_t fileMagic, fileVersion;
		stream.Read(&fileMagic, sizeof(fileMagic));
		if (fileMagic != FILE_MAGIC)
			return false;

		stream.Read(&fileVersion, sizeof(fileVersion));
		if (fileVersion != FILE_VERSION)
			return false;

		char stringLoadingBuffer[4096];
		StringItem* item = (StringItem*)stringLoadingBuffer;
		char* itemRemainStart = (char*)(item + 1);

		while (stream.Read(item, sizeof(StringItem)))
		{
			memset(itemRemainStart, 0, sizeof(stringLoadingBuffer) - sizeof(StringItem));
			stream.Read(itemRemainStart, item->ValueSize);

			// Add to both
			auto newAddr = AddStringToBuffer(item->Hash64, item->Hash32, item->StringValue);
			m_StringMap32.Insert(item->Hash32, newAddr);
			m_StringMap64.Insert(item->Hash64, newAddr);
		}

		return true;
	}

	// Save current strings to string table
	bool StringCrcDB::SaveStringTable(IOutputStream& stream)
	{
		// If nothing to save
		if (m_Head == nullptr)
		{
			return true;
		}

		uint64_t fileMagic = FILE_MAGIC, fileVersion = FILE_VERSION;
		stream.Write(&fileMagic, sizeof(fileMagic));
		stream.Write(&fileVersion, sizeof(fileVersion));

		// loop hash64
		//for (auto& itTbl : m_StringMap64)
		m_StringMap64.ForeachOrder(0, (uint)m_StringMap64.size(), [&stream](uint64_t key, const StringItem* pStrItem)
		{
			size_t saveSize = pStrItem->ValueSize + sizeof(StringItem);
			stream.Write((const char*)pStrItem, saveSize);

			return true;
		});

		return true;
	}


	const StringCrcDB::StringItem* StringCrcDB::AddStringToBuffer(uint64_t hash64, uint32_t hash32, const char* string)
	{
		if (string == nullptr)
			return nullptr;

		size_t strLen = strlen(string);
		const StringItem* newAddr = nullptr;

		// find free space from existing buffers
		auto pCurBlock = m_Head;
		while (pCurBlock != nullptr && newAddr == nullptr)
		{
			auto pNext = pCurBlock->Next;
			newAddr = pCurBlock->AddString(hash64, hash32, string, strLen);
			pCurBlock = pNext;
		}

		// if it's added successfully
		if (newAddr != nullptr)
			return newAddr;

		// we need more buffer
		size_t allocateSize = DefaultBufferSize;
		char* pBuffer = (char*)malloc(allocateSize + sizeof(StringBuffer));
		StringBuffer * newBuffer = new(pBuffer) StringBuffer(allocateSize);

		newAddr = newBuffer->AddString(hash64, hash32, string, strLen);
		// it should be assigned at this moment
		assert(newAddr != nullptr);

		newBuffer->Next = m_Head;
		m_Head = newBuffer;

		return newAddr;
	}

	// Add string to both 32 and 64 hash
	void StringCrcDB::AddString(const char* str)
	{
		uint32_t hash32Value = Crc32C(str);
		uint64_t hash64Value = Hash64(str);

		const StringItem* pStrItem = nullptr;
		if (m_StringMap64.Find(hash64Value, pStrItem))
		{
			return;
		}

		// Both table don't have it
		const StringItem* newAddr = AddStringToBuffer(hash64Value, hash32Value, str);
		m_StringMap32.Insert(hash32Value, newAddr);
		m_StringMap64.Insert(hash64Value, newAddr);

	}

	// Add string to specific table
	uint32_t StringCrcDB::AddNGetString32(const char* str)
	{
		uint64_t hash64Value = Hash64(str);
		uint32_t hash32Value = Crc32C(str);

		const StringItem* pStrItem = nullptr;
		if (m_StringMap64.Find(hash64Value, pStrItem))
		{
			return hash32Value;
		}


		// Both table don't have it
		const StringItem* newAddr = AddStringToBuffer(hash64Value, hash32Value, str);
		m_StringMap32.Insert(hash32Value, newAddr);
		m_StringMap64.Insert(hash64Value, newAddr);

		return hash32Value;
	}

	uint64_t StringCrcDB::AddNGetString(const char* str)
	{
		uint64_t hash64Value = Hash64(str);
		uint32_t hash32Value = Crc32C(str);

		const StringItem* pStrItem = nullptr;
		if (m_StringMap64.Find(hash64Value, pStrItem))
		{
			return hash64Value;
		}


		// Both table don't have it
		const StringItem* newAddr = AddStringToBuffer(hash64Value, hash32Value, str);
		{
			MutexScopeLock lock(m_LockForStringWrite);
			m_StringMap32.Insert(hash32Value, newAddr);
			m_StringMap64.Insert(hash64Value, newAddr);

			m_StringMap32.CommitChanges();
			m_StringMap64.CommitChanges();
		}

		return hash64Value;
	}

	const char* StringCrcDB::GetString(uint32_t hash)
	{
		if (hash == 0)
			return nullptr;

		const StringItem* pStrItem = nullptr;
		if (m_StringMap32.Find(hash, pStrItem))
		{
			return pStrItem->StringValue;
		}

		return nullptr;
	}

	const char* StringCrcDB::GetString(uint64_t hash)
	{
		if (hash == 0)
			return nullptr;

		const StringItem* pStrItem = nullptr;
		if (m_StringMap64.Find(hash, pStrItem))
		{
			return pStrItem->StringValue;
		}

		return nullptr;
	}

}



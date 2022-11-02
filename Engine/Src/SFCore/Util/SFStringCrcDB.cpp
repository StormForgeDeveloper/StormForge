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

#include "Util/SFHasher32.h"
#include "Util/SFHasher64.h"
#include "Util/SFStringCrcDB.h"
#include "Util/SFStrFormat.h"
#include "IO/SFFileUtil.h"
#include "IO/SFFileInputStream.h"
#include "Container/SFArray.h"
#include "Service/SFService.h"
#include "Stream/SFStream.h"
#include "Types/SFEngineTypeSerialization.h"
#include "Util/SFLog.h"


namespace SF
{

	static const char* g_DefaultStrings[] = 
	{
		"Result",
		"bool",
		"int",
		"uint",
		"int8",
		"uint8",
		"int16",
		"uint16",
		"int32",
		"uint32",
		"int64",
		"uint64",
		"float",
		"double",
		"Vector2",
		"Vector3",
		"Vector4",
		"StringCrc32",
		"StringCrc64",
		"BLOB",
		"string",
		"Static",
		"Type",
		"Name",
	};

	size_t StringCrcDB::StringItem::CalculateItemSize(size_t strLen)
	{
		auto requiredSize = sizeof(StringItem) + strLen;
		return AlignUp(requiredSize, 8);
	}

	const StringCrcDB::StringItem* StringCrcDB::StringBuffer::AddString(uint64_t hash64, uint32_t hash32, const char* string, size_t strLen)
	{
		auto requiredSize = StringItem::CalculateItemSize(strLen);
		if (string == nullptr || RemainSize < requiredSize)
			return nullptr;

		auto stringItem = (StringItem*)StringItems + (BufferSize - RemainSize);
		stringItem->Hash64 = hash64;
		stringItem->Hash32 = hash32;
		stringItem->ValueSize = static_cast<uint16_t>(requiredSize - sizeof(StringItem));

		memcpy(stringItem->StringValue, string, strLen);
		stringItem->StringValue[strLen] = '\0';

		RemainSize -= requiredSize; // Include null terminate

		return stringItem;
	}


	StringCrcDB::StringCrcDB()
		: m_Heap("StringCrcDB", GetSystemHeap())
		, m_StringMap32(GetHeap())
		, m_StringMap64(GetHeap())
	{
		// default strings
		ArrayView<const char*> DefaultStrings(g_DefaultStrings);
		for (auto itString : DefaultStrings)
		{
			AddNGetString(itString);
		}

		//const char* defaultFileName = "strings.crcbin";
		//if (FileUtil::IsFileExist(defaultFileName))
		//{
		//	SF::FileInputStream readFrom(defaultFileName);
		//	LoadStringTable(readFrom);
		//}


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

	StringCrcDB::FileHeaderCheckResult StringCrcDB::CheckFileHeader(IInputStream& stream)
	{
		StringFileHeader header{};
		stream.Read(&header, sizeof(StringFileHeader));

		if (header.Magic != StringFileHeader::FILE_MAGIC)
			return FileHeaderCheckResult::InvalidHeader;

		if (header.Version != StringFileHeader::FILE_VERSION)
			return FileHeaderCheckResult::InvalidVersion;

		return FileHeaderCheckResult::Successed;
	}

	// Load string table file
	Result StringCrcDB::LoadStringTable(IInputStream& stream)
	{
		// load header
		StringFileHeader header{};
		stream.Read(&header, sizeof(StringFileHeader));

		if (header.Magic != StringFileHeader::FILE_MAGIC)
			return ResultCode::INVALID_FORMAT;

		if (header.Version != StringFileHeader::FILE_VERSION)
			return ResultCode::INVALID_VERSION;

		char* pBuffer = (char*)malloc(header.ChunkSize + sizeof(StringBuffer));
		StringBuffer* newBuffer = new(pBuffer) StringBuffer(header.ChunkSize);
		memset(newBuffer, 0, sizeof(StringBuffer));

		if (!stream.Read(newBuffer->StringItems, header.ChunkSize))
			return ResultCode::INVALID_FORMAT;

		newBuffer->BufferSize = header.ChunkSize;
		newBuffer->RemainSize = 0;

		int numStringItem = 0;

		uintptr_t endItemPos = uintptr_t(newBuffer->StringItems) + header.ChunkSize;
		for (uintptr_t curItemPos = (uintptr_t)newBuffer->StringItems; curItemPos < endItemPos; )
		{
			auto* pStrItem = (StringItem*)curItemPos;
			numStringItem++;

			// Add to both
			if (!m_StringMap32.Contains(pStrItem->Hash32))
				m_StringMap32.Insert(pStrItem->Hash32, pStrItem);

			if (!m_StringMap64.Contains(pStrItem->Hash64))
				m_StringMap64.Insert(pStrItem->Hash64, pStrItem);

			curItemPos += sizeof(StringItem) + pStrItem->ValueSize;
		}

		newBuffer->Next = m_Head;
		m_Head = newBuffer;

		m_StringMap32.CommitChanges();
		m_StringMap64.CommitChanges();

		return ResultCode::SUCCESS;
	}

	// Save current strings to string table
    Result StringCrcDB::SaveStringTable(IOutputStream& stream)
	{
		// If nothing to save
		if (m_Head == nullptr)
		{
			return ResultCode::SUCCESS;
		}

		StringFileHeader header;
		header.Magic = StringFileHeader::FILE_MAGIC;
		header.Version = StringFileHeader::FILE_VERSION;
		header.ChunkSize = 0;


		// loop hash64 and create merged one
		m_StringMap64.ForeachOrder(0, (uint)m_StringMap64.size(), [&header](uint64_t key, const StringItem* pStrItem)
			{
				size_t saveSize = pStrItem->ValueSize + sizeof(StringItem);
				header.ChunkSize += saveSize;
				return true;
			});


		stream.Write(&header, sizeof(StringFileHeader));


		m_StringMap64.ForeachOrder(0, (uint)m_StringMap64.size(), [&stream](uint64_t key, const StringItem* pStrItem)
			{
				size_t saveSize = pStrItem->ValueSize + sizeof(StringItem);
				stream.Write((const char*)pStrItem, saveSize);

				return true;
			});

		return ResultCode::SUCCESS;
	}

	// Save current strings to text file
	bool StringCrcDB::DumpToTextFile(IOutputStream& stream)
	{
		// If nothing to save
		if (m_Head == nullptr)
		{
			return true;
		}

		DynamicArray<char> stringBuffer;
		stringBuffer.reserve(10 * 1024);

		m_StringMap64.ForeachOrder(0, (uint)m_StringMap64.size(), [&](uint64_t key, const StringItem* pStrItem)
			{
				int capacity = int(stringBuffer.capacity());
				size_t usedSize = StrUtil::Format(stringBuffer.data(), capacity, "{0:x}, {1:x}, '{2}'\n", pStrItem->Hash32, pStrItem->Hash64, pStrItem->StringValue);
				stream.Write(stringBuffer.data(), usedSize - 1);

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
		{
			MutexScopeLock lock(m_LockForStringWrite);
			m_StringMap32.Insert(hash32Value, newAddr);
			m_StringMap64.Insert(hash64Value, newAddr);

			m_StringMap32.CommitChanges();
			m_StringMap64.CommitChanges();
		}

#ifdef DEBUG
		const StringItem* pTest{};
		if (!m_StringMap32.Find(hash32Value, pTest))
		{
			SFLog(System, Error, "StringCrcDB::AddNGetString32 has failed to add32 '{0}'", str);
		}

		if (!m_StringMap64.Find(hash64Value, pTest))
		{
			SFLog(System, Error, "StringCrcDB::AddNGetString32 has failed to add64 '{0}'", str);
		}
#endif

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
		{
			MutexScopeLock lock(m_LockForStringWrite);
			m_StringMap32.Insert(hash32Value, newAddr);
			m_StringMap64.Insert(hash64Value, newAddr);

			m_StringMap32.CommitChanges();
			m_StringMap64.CommitChanges();
		}

#ifdef DEBUG
		const StringItem* pTest{};
		if (!m_StringMap32.Find(hash32Value, pTest))
		{
			SFLog(System, Error, "StringCrcDB::AddNGetString32 has failed to add32 '{0}':{1:X}", str, hash32Value);
		}

		if (!m_StringMap64.Find(hash64Value, pTest))
		{
			SFLog(System, Error, "StringCrcDB::AddNGetString32 has failed to add64 '{0}':{1:X}", str, hash64Value);
		}
#endif

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


	void StringCrcDB::DumpStringList()
	{
		SFLog(System, Debug, "String table dump count:{0}", m_StringMap64.size());

		m_StringMap64.ForeachOrder(0, (uint)m_StringMap64.size(), [&](uint64_t key, const StringItem* pStrItem)
			{
				SFLog(System, Debug, "{0}, {1}, {2}", pStrItem->Hash32, pStrItem->Hash64, pStrItem->StringValue);
				return true;
			});
	}
}



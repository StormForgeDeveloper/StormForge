////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StringCrc DB
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryManager.h"
#include "Container/SFDualSortedMap.h"



namespace SF
{
	class IInputStream;
	class IOutputStream;

	class StringCrcDB
	{
	public:

		const size_t DefaultBufferSize = 512 * 1024;
		static constexpr uint64_t FILE_MAGIC = "StringTable"_hash64;
		static constexpr uint64_t FILE_VERSION = 1;

	private:

		// String Item
		struct StringItem
		{
			uint64_t Hash64;
			uint32_t Hash32;
			uint32_t ValueSize;
			char StringValue[1];
		};

		// String buffer linked list
		struct StringBuffer
		{
			size_t BufferSize;
			size_t RemainSize;
			StringBuffer *Next;
			StringItem StringItems[1];

			StringBuffer(size_t bufferSize)
				: BufferSize(bufferSize)
				, RemainSize(bufferSize)
				, Next(nullptr)
			{
				memset(StringItems, 0, BufferSize);
			}

			// Add string to buffer and return new string address
			const StringItem* AddString(uint64_t hash64, uint32_t hash32, const char* string, size_t strLen);
		};

		// String buffer linked list
		StringBuffer *m_Head = nullptr;

		Heap m_Heap;

		SF::CriticalSection m_LockForStringWrite;

		DualSortedMap<uint32_t, const StringItem*> m_StringMap32;
		DualSortedMap<uint64_t, const StringItem*> m_StringMap64;

	private:

		const StringItem* AddStringToBuffer(uint64_t hash64, uint32_t hash32, const char* string);

	public:
		StringCrcDB();
		~StringCrcDB();

		// Clear and release all memory
		void Clear();

		IHeap& GetHeap() { return *m_Heap.get(); }

		size_t GetStringCount() {
			return std::max(m_StringMap32.size(), m_StringMap64.size());
		}

		// Merge all string buffer into one
		//bool MergeStringBuffer();

		// Load string table file
		bool LoadStringTable(IInputStream& stream);

		// Save current strings to string table
		bool SaveStringTable(IOutputStream& stream);

		// Add string to both 32 and 64 hash
		void AddString(const char* str);

		// Add string to specific table
		uint32_t AddNGetString32(const char* str);
		uint64_t AddNGetString(const char* str);

		const char* GetString(uint32_t hash);
		const char* GetString(uint64_t hash);

	};


}


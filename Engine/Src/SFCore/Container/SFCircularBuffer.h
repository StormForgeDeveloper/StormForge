////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular Buffer for multithread
//
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Multithread/SFSynchronization.h"
#include "Multithread/SFSystemSynchronization.h"

namespace SF
{

	////////////////////////////////////////////////////////////////////////////////
	//
	// Circular Buffer 
	//	- Queue style buffer allocator
	// 

	class CircularBuffer
	{
	public:

		enum class ItemState : uint32_t
		{
			Free,
			Reserved,
			Dummy,		// marked as dummy space
		};

#pragma pack(push, 4)
		struct BufferItem
		{
			std::atomic<ItemState>	State;		// Item state
			uint32_t				NextPos;	// Next item position, offset from m_Buffer

			void* GetDataPtr() { return this + 1; }
		};
#pragma pack(pop)

		using Item = BufferItem;

	private:

		// buffer size
		size_t m_BufferSize = 0;

		// Buffer
		uint8_t* m_Buffer = nullptr;

		// External buffer?
		bool m_ExternalBuffer = false;

		// HeadPos lock
		CriticalSection m_HeadLock;

		// Read position
		std::atomic<BufferItem*> m_TailPos;

		// Write position
		std::atomic <BufferItem*> m_HeadPos;


	public:

		// Constructor/Destructor
		CircularBuffer(IHeap& heap, size_t bufferSize = 2048, uint8_t* externalBuffer = nullptr);
		~CircularBuffer();

		// Empty check
		bool IsEmpty();

		// Clear all items
		void Clear();

		// Reserve buffer. The pointer it returns is reserved for writing, after done writing, Call SetReadyForRead to mark the buffer is ready for read
		BufferItem* Allocate(size_t bufferSize);

		// mark the buffer for read
		Result Free(BufferItem* pBuffer);

		// get buffer item size
		size_t GetBufferItemSize(BufferItem* pBufferItem);

	};


	// Circular buffer with static size
	template<size_t BufferSize>
	class StaticCircularBuffer : public CircularBuffer
	{
	private:
		uint8_t m_StaticBuffer[BufferSize];

	public:
		StaticCircularBuffer() : CircularBuffer(GetSystemHeap(), BufferSize, m_StaticBuffer) {}
	};


}


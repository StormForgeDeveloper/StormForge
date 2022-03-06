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
#include "MemoryManager/SFIMemoryManager.h"
#include "Multithread/SFSynchronization.h"
#include "Multithread/SFSystemSynchronization.h"

namespace SF
{

	////////////////////////////////////////////////////////////////////////////////
	//
	// Circular Buffer 
	//	- Queue style buffer allocator
	// 

	class CircularBufferQueue
	{
	public:

		enum class ItemState : uint32_t
		{
			Free,
			Reserved,
			Filled,
			Reading,
			Dummy,		// marked as dummy space
		};

#pragma pack(push, 4)
		struct BufferItem
		{
			std::atomic<ItemState>	State;		// Item state
			uint32_t				DataSize;
			uint32_t				NextPos;	// Next item position, offset from m_Buffer

			void* GetDataPtr() { return this + 1; }
		};
#pragma pack(pop)

		using Item = BufferItem;

	private:

		IHeap& m_Heap;

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
		CircularBufferQueue(IHeap& heap, size_t bufferSize = 2048, uint8_t* externalBuffer = nullptr);
		~CircularBufferQueue();

		void Initialize(size_t bufferSize = 2048, uint8_t* externalBuffer = nullptr);

		SF_FORCEINLINE size_t GetBufferSize() const { return m_BufferSize; }
		SF_FORCEINLINE size_t size() const { return m_BufferSize; }

		// Empty check
		bool IsEmpty() const;

		size_t GetFreeSize() const;

		SF_FORCEINLINE uint8_t* data() { return m_Buffer; }
		SF_FORCEINLINE const uint8_t* data() const { return m_Buffer; }

		// Clear all items
		void Reset();
		SF_FORCEINLINE void Clear() { Reset(); }

		// forcefully reset the position. This is useful when you handle external buffer manually save/load from file system.
		bool ForceReset(int headOffset, int tailOffset);

		BufferItem* GetHead() const { return m_HeadPos.load(MemoryOrder::memory_order_acquire); }
		BufferItem* GetTail() const { return m_TailPos.load(MemoryOrder::memory_order_acquire); }

		// Reserve buffer. The pointer it returns is reserved for writing, after done writing, Call SetReadyForRead to mark the buffer is ready for read
		BufferItem* AllocateWrite(size_t bufferSize);

		// mark the buffer for read
		Result ReleaseWrite(BufferItem* pBuffer);

		BufferItem* DequeueRead();
		Result ReleaseRead(BufferItem* pBuffer);

		// low level access. don't change state, just sneak peek tail item. 
		// NOTE: NOT thread safe. caller should guarantee thread safety   
		BufferItem* PeekTail();
		BufferItem* PeekNext(BufferItem* item);

		// get buffer item size
		size_t GetBufferItemSize(BufferItem* pBufferItem) const;

		// Iterate readable items. the item passed to the functor will be freed
		template<class FunctorT>
		void ForeachReadableItems(FunctorT func)
		{
			BufferItem* pBufferItem = nullptr;

			while (true)
			{
				pBufferItem = DequeueRead();
				if (pBufferItem == nullptr)
					return; // nothing left for now

				bool bRet = func(pBufferItem);

				ReleaseRead(pBufferItem);

				if (!bRet)
					return;
			}
		}

		bool CheckIntegrity() const;
	};


	// Circular buffer with static size
	template<size_t BufferSize>
	class StaticCircularBufferQueue : public CircularBufferQueue
	{
	private:
		uint8_t m_StaticBuffer[BufferSize];

	public:
		StaticCircularBufferQueue() : CircularBufferQueue(GetSystemHeap(), BufferSize, m_StaticBuffer) {}
	};


}


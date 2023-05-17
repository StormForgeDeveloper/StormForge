////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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

			SF_FORCEINLINE void* GetDataPtr() { return this + 1; }
            SF_FORCEINLINE static BufferItem* FromDataPtr(void* pData) { return pData != nullptr ? reinterpret_cast<BufferItem*>(pData) - 1 : nullptr; }
            SF_FORCEINLINE size_t GetDataSize() const { return DataSize; }

            Result AcquireRead();
		};
#pragma pack(pop)

		using Item = BufferItem;


        class ItemPtr
        {
        protected:
            ItemPtr() {}
            ItemPtr(CircularBufferQueue* pContainer, BufferItem* pItem)
                : m_pContainer(pContainer)
                , m_pItem(pItem)
            {
            }
            ItemPtr(ItemPtr&& src)
                : m_pContainer(src.m_pContainer)
                , m_pItem(src.m_pItem)
            {
                src.m_pContainer = nullptr;
                src.m_pItem = nullptr;
            }
            ~ItemPtr()
            {
            }
        public:

            SF_FORCEINLINE bool IsValid() const { return m_pContainer && m_pItem; }
            SF_FORCEINLINE operator bool() const { return IsValid(); }
            SF_FORCEINLINE void* data() const { return m_pItem ? m_pItem->GetDataPtr() : nullptr; }
            SF_FORCEINLINE size_t GetDataSize() const { return m_pItem ? m_pItem->DataSize : 0; }
            SF_FORCEINLINE BufferItem* GetBufferItem() const { return m_pItem; }

            ItemPtr& operator = (ItemPtr&& src)
            {
                assert(m_pContainer == nullptr);
                assert(m_pItem == nullptr);
                m_pContainer = src.m_pContainer;
                m_pItem = src.m_pItem;
                src.m_pContainer = nullptr;
                src.m_pItem = nullptr;
                return *this;
            }

        protected:
            CircularBufferQueue* m_pContainer{};
            BufferItem* m_pItem{};
        };

        // Write ptr wrapper
        class ItemWritePtr : public ItemPtr
        {
        public:
            ItemWritePtr() {}
            ItemWritePtr(CircularBufferQueue* pContainer, BufferItem* pItem)
                : ItemPtr(pContainer, pItem)
            {
                assert(pItem == nullptr || pItem->State.load(std::memory_order_relaxed) == ItemState::Reserved);
            }
            ItemWritePtr(ItemWritePtr&& src)
                : ItemPtr(std::forward<ItemPtr>(src))
            {
            }
            ~ItemWritePtr()
            {
                Reset();
            }

            using ItemPtr::IsValid;
            using ItemPtr::data;
            using ItemPtr::GetDataSize;
            using ItemPtr::GetBufferItem;

            void Reset()
            {
                if (m_pContainer && m_pItem)
                {
                    m_pContainer->ReleaseWrite(m_pItem);
                    m_pContainer = nullptr;
                    m_pItem = nullptr;
                }
            }

            ItemWritePtr& operator = (ItemWritePtr&& src)
            {
                Reset();
                *((ItemPtr*)this) = std::forward<ItemPtr>(src);
                return *this;
            }
        };

        // read ptr wrapper
        class ItemReadPtr : public ItemPtr
        {
        public:
            ItemReadPtr() {}
            ItemReadPtr(CircularBufferQueue* pContainer, BufferItem* pItem)
                : ItemPtr(pContainer, pItem)
            {
                assert(pItem == nullptr || pItem->State.load(std::memory_order_relaxed) == ItemState::Reading);
            }
            ItemReadPtr(ItemReadPtr&& src)
                : ItemPtr(std::forward<ItemPtr>(src))
            {
            }
            ~ItemReadPtr()
            {
                Reset();
            }

            using ItemPtr::IsValid;
            using ItemPtr::data;
            using ItemPtr::GetDataSize;
            using ItemPtr::GetBufferItem;


            void Reset()
            {
                if (m_pContainer && m_pItem)
                {
                    m_pContainer->ReleaseRead(m_pItem);
                    m_pContainer = nullptr;
                    m_pItem = nullptr;
                }
            }

            void CancelRead()
            {
                if (m_pContainer && m_pItem)
                {
                    m_pContainer->CancelRead(m_pItem);
                    m_pContainer = nullptr;
                    m_pItem = nullptr;
                }
            }

            ItemReadPtr& operator = (ItemReadPtr&& src)
            {
                Reset();
                *((ItemPtr*)this) = std::forward<ItemPtr>(src);
                return *this;
            }
        };


        class ItemIterator : public ItemPtr
        {
        public:
            ItemIterator() {}
            ItemIterator(CircularBufferQueue* pContainer, BufferItem* pItem)
                : ItemPtr(pContainer, pItem)
            {
                assert(pItem == nullptr || pItem->State.load(std::memory_order_relaxed) == ItemState::Filled);
            }
            ItemIterator(ItemReadPtr&& src)
                : ItemPtr(std::forward<ItemPtr>(src))
            {
            }
            ~ItemIterator()
            {
                Reset();
            }

            using ItemPtr::IsValid;
            using ItemPtr::data;
            using ItemPtr::GetDataSize;
            using ItemPtr::GetBufferItem;

            void Reset()
            {
                if (m_pContainer && m_pItem)
                {
                    m_pContainer = nullptr;
                    m_pItem = nullptr;
                }
            }

            Result StartRead()
            {
                ItemState expected = ItemState::Filled;
                bool bExchanged = m_pItem->State.compare_exchange_strong(expected, ItemState::Reading, std::memory_order_release, std::memory_order_acquire);
                if (!bExchanged)
                {
                    assert(expected == ItemState::Dummy);
                    return ResultCode::FAIL;
                }
                return ResultCode::SUCCESS;
            }

            void CancelRead()
            {
                m_pContainer->CancelRead(m_pItem);
            }

            ItemIterator& operator ++()
            {
                if (!IsValid())
                    return *this;

                m_pItem = m_pContainer->PeekNext(m_pItem);

                return *this;
            }

            ItemIterator& operator = (ItemIterator&& src)
            {
                Reset();
                *((ItemPtr*)this) = std::forward<ItemPtr>(src);
                return *this;
            }
        };



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

        // Tail pos lock
        CriticalSection m_TailLock;

		// Read position
		std::atomic<BufferItem*> m_TailPos;

		// Write position
		std::atomic <BufferItem*> m_HeadPos;

        std::atomic<uint> m_ItemCount;

	public:

		// Constructor/Destructor
		CircularBufferQueue(IHeap& heap = GetSystemHeap(), size_t bufferSize = 2048, uint8_t* externalBuffer = nullptr);
		~CircularBufferQueue();

		void Initialize(size_t bufferSize = 2048, uint8_t* externalBuffer = nullptr);

		SF_FORCEINLINE size_t GetBufferSize() const { return m_BufferSize; }
		SF_FORCEINLINE size_t size() const { return m_BufferSize; }

		// Empty check
		bool IsEmpty() const;
        SF_FORCEINLINE uint GetItemCount() const { return m_ItemCount.load(std::memory_order_relaxed); }

		size_t GetFreeSize() const;

		SF_FORCEINLINE uint8_t* data() { return m_Buffer; }
		SF_FORCEINLINE const uint8_t* data() const { return m_Buffer; }

		// Clear all items
		void Reset();
		SF_FORCEINLINE void Clear() { Reset(); }

        SF_FORCEINLINE bool IsManagedAddress(void* pPtr) const
        {
            return (
                uintptr_t(pPtr) > uintptr_t(m_Buffer))
                && (uintptr_t(pPtr) < (uintptr_t(m_Buffer) + m_BufferSize)
                    );
        }

		// forcefully reset the position. This is useful when you handle external buffer manually save/load from file system.
		bool ForceReset(int headOffset, int tailOffset);

		BufferItem* GetHead() const { return m_HeadPos.load(MemoryOrder::memory_order_acquire); }
		BufferItem* GetTail() const { return m_TailPos.load(MemoryOrder::memory_order_acquire); }

		// Reserve buffer. The pointer it returns is reserved for writing, after done writing, Call SetReadyForRead to mark the buffer is ready for read
        ItemWritePtr AllocateWrite(size_t bufferSize);

		// mark the buffer for read
		Result ReleaseWrite(BufferItem* pBuffer);

        ItemReadPtr DequeueRead();
        ItemReadPtr DequeueReadNoLock();
		void CancelRead(BufferItem* item);
        Result ReleaseRead(BufferItem* pBuffer)
        {
            return ReleaseReadInternal(pBuffer, ItemState::Reading);
        }
        Result ForceReleaseRead(BufferItem* pBuffer)
        {
            return ReleaseReadInternal(pBuffer, ItemState::Filled);
        }

		// low level access. don't change state, just sneak peek tail item. 
		// NOTE: NOT thread safe. caller should guarantee thread safety
        ItemIterator TailIterator() { return ItemIterator(this, PeekTail()); }
		BufferItem* PeekTail();
		BufferItem* PeekNext(BufferItem* item);

		// get buffer item size
		size_t GetBufferItemSize(const BufferItem* pBufferItem) const;

		bool CheckIntegrity() const;

    private:
        Result ReleaseReadInternal(BufferItem* pBuffer, ItemState expectedState = ItemState::Reading);
	};


	// Circular buffer with static size
	template<size_t BufferSize>
	class StaticCircularBufferQueue : public CircularBufferQueue
	{
	private:
		uint8_t m_StaticBuffer[BufferSize];

	public:
		StaticCircularBufferQueue(IHeap& overflowHeap = GetSystemHeap()) : CircularBufferQueue(overflowHeap, BufferSize, m_StaticBuffer) {}
	};


}


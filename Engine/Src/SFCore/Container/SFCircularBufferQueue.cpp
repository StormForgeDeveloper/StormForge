////////////////////////////////////////////////////////////////////////////////
// 
// Author : KyungKun Ko
//
// Description : Circular Buffer for multithread
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "MemoryManager/SFIMemoryManager.h"
#include "MemoryManager/SFMemory.h"
#include "SFCircularBufferQueue.h"


namespace SF
{


    Result CircularBufferQueue::BufferItem::AcquireRead()
    {
        Result hr;

        ItemState expectedState = ItemState::Filled;
        bool bExchanged = State.compare_exchange_strong(expectedState, ItemState::Reading, std::memory_order_release, std::memory_order_acquire);
        if (!bExchanged)
        {
            switch (expectedState)
            {
            case ItemState::Free:
                return ResultCode::FAIL;
            case ItemState::Reserved:
                // It's not ready. let's return at this moment
                return ResultCode::FAIL;
            case ItemState::Filled:
                //assert(State == ItemState::Reading);
                break;
            case ItemState::Reading:
                // broken?
                assert(false);
                return ResultCode::FAIL;
            case ItemState::Dummy:
                // might be broken
                // Let's silently flush dummy out
                return ResultCode::IO_TRY_AGAIN;
            }
        }

        //assert(State == ItemState::Reading);
        return hr;
    }

	CircularBufferQueue::CircularBufferQueue(IHeap& heap, size_t bufferSize, uint8_t* externalBuffer)
		: m_Heap(heap)
	{
		if (bufferSize > 0)
			Initialize(bufferSize, externalBuffer);
        m_ItemCount = 0;
    }

	CircularBufferQueue::~CircularBufferQueue()
	{
		if (!m_ExternalBuffer && m_Buffer != nullptr)
			IHeap::Delete(m_Buffer);
		m_Buffer = nullptr;
	}

	void CircularBufferQueue::Initialize(size_t bufferSize /* = 2048 */, uint8_t* externalBuffer /* = nullptr */)
	{
		if (!m_ExternalBuffer && m_Buffer != nullptr)
			IHeap::Delete(m_Buffer);

		m_BufferSize = bufferSize;
		m_Buffer = externalBuffer;
			
		m_ExternalBuffer = externalBuffer != nullptr;
		if (!m_ExternalBuffer)
		{
			m_Buffer = new(m_Heap) uint8_t[m_BufferSize];
		}

        static_assert(sizeof(std::atomic<uint64_t>) == sizeof(uint64_t), "My assumption has broken!");

        Reset();
	}

	// Clear all items
	void CircularBufferQueue::Reset()
	{
        m_ItemCount = 0;

        m_TailPos = (reinterpret_cast<BufferItem*>(m_Buffer));
        m_HeadPos = (reinterpret_cast<BufferItem*>(m_Buffer));

        memset(m_Buffer, 0, m_BufferSize);
	}

	bool CircularBufferQueue::IsEmpty() const
	{
		return m_HeadPos.load(std::memory_order_relaxed) == m_TailPos.load(std::memory_order_relaxed);
	}

	size_t CircularBufferQueue::GetFreeSize() const
	{
        intptr_t tail = intptr_t(m_TailPos.load(std::memory_order_relaxed));
        intptr_t head = intptr_t(m_HeadPos.load(std::memory_order_relaxed));
		if (head == tail)
			return GetBufferSize();
		else if (head < tail)
			return size_t(tail - head);
		else 
			return GetBufferSize() - size_t(head - tail);
	}

	bool CircularBufferQueue::ForceReset(int headOffset, int tailOffset)
	{
		if (headOffset < 0 || headOffset >= m_BufferSize
			|| tailOffset < 0 || tailOffset >= m_BufferSize)
			return false;

		m_HeadPos.store(reinterpret_cast<BufferItem*>(m_Buffer + headOffset));
		m_TailPos.store(reinterpret_cast<BufferItem*>(m_Buffer + tailOffset));

		return CheckIntegrity();
	}


	// Reserve buffer. The pointer it returns is reserved for writing, after done writing, Call SetReadyForRead to mark the buffer is ready for read
	CircularBufferQueue::ItemWritePtr CircularBufferQueue::AllocateWrite(size_t requesteSize)
	{
		// We only support 8 byte aligned allocation
		size_t bufferSize = AlignUp(requesteSize, 8);
        uintptr_t expectedSize = (uintptr_t)(sizeof(BufferItem) + bufferSize);

		uintptr_t startPos = (const uintptr_t)m_Buffer;
        uintptr_t endPos = (uintptr_t)m_Buffer + (uintptr_t)m_BufferSize;

        // We are allocating memory here, so using lock free doesn't effective because it doesn't guaranteed that writing order in allocated memory space.
        // Head allocation should be happened in order
        MutexScopeLock ticketScope(m_HeadLock);

        // TODO: since we have mutex lock, this loop might not be necessary.
		while(true)
		{
			BufferItem* pHead = m_HeadPos.load(std::memory_order_relaxed); // We just need to access this like a simple volatile type
            BufferItem* pTail = m_TailPos.load(std::memory_order_acquire);
			BufferItem* pNextHead = nullptr;

			// We want to put BufferItem structure at the end of allocation for next allocation
            uintptr_t expectedEnd = (uintptr_t)pHead + expectedSize;
			if ((uintptr_t)pHead >= (uintptr_t)pTail) // if head is place at the right side
			{
				if (expectedEnd > endPos) // remain buffer is too small. mark current head as dummy and move forward
				{
					// If we don't have enough space between tail and start pos.
					if (((uintptr_t)pTail - startPos) < (uintptr_t)(expectedSize + sizeof(BufferItem)))
						return ItemWritePtr();// out of memory

                    ItemState expectedState = ItemState::Free;
                    if (!pHead->State.compare_exchange_strong(expectedState, ItemState::Dummy, std::memory_order_relaxed, std::memory_order_acquire))
					{
						if (expectedState != ItemState::Free)
						{
							// Broken?
							assert(false);
							return ItemWritePtr();
						}
					}

					// Point next head at start
					pHead->NextPos = 0;

					// setup next head
					pNextHead = reinterpret_cast<BufferItem*>(startPos);
					pNextHead->NextPos = 0;
					pNextHead->State.store(ItemState::Free);

					m_HeadPos.store(pNextHead, std::memory_order_relaxed);

					continue; // start over
				}


				// We have enough space at right after head
				// but don't have enough space for next head. grow size so that it consumes all memory , and place next head at the beginning
				if ((uintptr_t)(expectedEnd + sizeof(BufferItem)) > endPos)
				{
					// We are going to back to start of
					// We need to make sure we have enough space at the beginning of the buffer
					expectedSize = expectedEnd - (uintptr_t)pHead;
					expectedEnd = endPos;

					// We can't put next head at the beginning of the array, so out of memory
					if (((uintptr_t)pTail - startPos) < sizeof(BufferItem))
						return ItemWritePtr(); // out of memory

					pNextHead = reinterpret_cast<BufferItem*>(startPos);
				}
				else
				{
					pNextHead = reinterpret_cast<BufferItem*>(expectedEnd);
				}
			}
			else // head is placed left side of the tail.
			{
				endPos = (uintptr_t)pTail; // limit end pos to tail
				// and check remain space
				if ((expectedEnd + (uintptr_t)sizeof(BufferItem)) > endPos) // out of memory, we need next head before tail
					return ItemWritePtr();

				pNextHead = reinterpret_cast<BufferItem*>(expectedEnd);
			}

			// all condition checks have passed
			// Let's change memory values
            ItemState expectedState = ItemState::Free;
			if (!pHead->State.compare_exchange_strong(expectedState, ItemState::Reserved, std::memory_order_relaxed, std::memory_order_acquire))
			{
				if (expectedState != ItemState::Free)
				{
					// Broken?
					assert(false);
					return ItemWritePtr();
				}
			}
			pHead->NextPos = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(pNextHead) - startPos);
			pHead->DataSize = static_cast<uint32_t>(requesteSize);

			// prepare next head
			pNextHead->State.store(ItemState::Free, std::memory_order_relaxed);// using relaxed here because the write in SetReadyForRead is the most important state writing
			pNextHead->NextPos = 0;
			m_HeadPos.store(pNextHead, std::memory_order_release);

			// we've done
			return ItemWritePtr(this, pHead);

		}

		return ItemWritePtr();
	}

	// mark the buffer for read
	Result CircularBufferQueue::ReleaseWrite(BufferItem* pBuffer)
	{
		if (pBuffer == nullptr)
			return ResultCode::INVALID_POINTER;

        m_ItemCount.fetch_add(1, std::memory_order_relaxed);

        std::atomic_thread_fence(std::memory_order_release);

		// Flip the state to free
        ItemState expectedState = ItemState::Reserved;
		while (!pBuffer->State.compare_exchange_weak(expectedState, ItemState::Filled, std::memory_order_release, std::memory_order_acquire))
		{
			if (expectedState != ItemState::Reserved)
			{
				// Broken?
				assert(false);
				return ResultCode::UNEXPECTED;
			}
		}

		return ResultCode::SUCCESS;
	}

    CircularBufferQueue::ItemReadPtr CircularBufferQueue::DequeueRead()
    {
        MutexScopeLock ticketScope(m_TailLock);
        return std::forward<ItemReadPtr>(DequeueReadNoLock());
    }

	// mark the buffer for read
	CircularBufferQueue::ItemReadPtr CircularBufferQueue::DequeueReadNoLock()
	{
		BufferItem* pHead = m_HeadPos.load(std::memory_order_acquire);

		if (pHead == nullptr)
			return ItemReadPtr();

        BufferItem* pTail = m_TailPos.load(std::memory_order_relaxed);
		if (pTail == pHead) // queue is empty
			return ItemReadPtr();

        Result hr = pTail->AcquireRead();
        if (hr == ResultCode::IO_TRY_AGAIN)
        {
            ReleaseRead(pTail);
            pTail = m_TailPos.load(std::memory_order_relaxed);
            if (pTail == pHead) // queue is empty
                return ItemReadPtr();

            if (!pTail->AcquireRead())
                return ItemReadPtr();

            assert(pTail->State == ItemState::Reading);
        }
        else if (!hr.IsSuccess())
        {
            return ItemReadPtr();
        }

        // we have critical section, but it is only for head and tail position
        std::atomic_thread_fence(std::memory_order_acquire);

        //assert(pTail->State == ItemState::Reading);

		return ItemReadPtr(this, pTail);
	}

	void CircularBufferQueue::CancelRead(BufferItem* item)
	{
        ItemState expectedState = ItemState::Reading;
		while (!item->State.compare_exchange_weak(expectedState, ItemState::Filled, std::memory_order_release, std::memory_order_acquire))
		{
			switch (expectedState)
			{
			case ItemState::Reading:
				// Retry
				break;
			case ItemState::Dummy:
				// might be broken
				return;
			default:
				assert(false);
				// Retry
				return;
			}
		}
	}

	Result CircularBufferQueue::ReleaseReadInternal(BufferItem* pBuffer, ItemState expectedState)
	{
		if (pBuffer == nullptr)
			return ResultCode::FAIL;

		uintptr_t startPos = (uintptr_t)m_Buffer;
		[[maybe_unused]] uintptr_t endPos = (uintptr_t)m_Buffer + (uintptr_t)m_BufferSize;

		// for debug
#if defined(_DEBUG) || defined(DEBUG)
		if (pBuffer->NextPos == 0)
		{
			if ((uintptr_t)pBuffer != startPos)
				memset(pBuffer + 1, 0xFF, endPos - (uintptr_t)(pBuffer + 1));
			else
			{
				// Possibly broken
				assert(0);
			}
		}
		else
		{
			memset(pBuffer + 1, 0xFF, pBuffer->NextPos - ((uintptr_t)(pBuffer + 1) - startPos));
		}
#endif

        // TailPos and item state should be synchronized, so need to lock them together
        MutexScopeLock ticketScope(m_TailLock);

        ItemState expected = expectedState;
        bool bExchanged = pBuffer->State.compare_exchange_strong(expected,
            ItemState::Free,
            std::memory_order_release,
            std::memory_order_acquire);
        if (bExchanged)
        {
            m_ItemCount.fetch_sub(1, std::memory_order_relaxed);
        }
        else
		{
			if (expected != expectedState && expected != ItemState::Dummy)
			{
				assert(false); // maybe broken?
				return ResultCode::FAIL;
			}
		}

		// And we have to take care of tail position, and this should be rigorously synchronous way
		BufferItem* curTail = m_TailPos.load(std::memory_order_relaxed);
        BufferItem* pHead = m_HeadPos.load(std::memory_order_relaxed);
		while(curTail != pHead)
		{
			// if the item state isn't free. it means somebody working on it. leave that free to other thread
            ItemState tailState = curTail->State.load(std::memory_order_relaxed);
			if (tailState != ItemState::Free && tailState != ItemState::Dummy)
				break;

			BufferItem* nextTail = reinterpret_cast<BufferItem*>(startPos + curTail->NextPos);
			assert((uintptr_t)nextTail >= startPos && (uintptr_t)nextTail < endPos);

			curTail = nextTail;
		}
		m_TailPos.store(curTail, std::memory_order_relaxed);

		return ResultCode::SUCCESS;
	}

	CircularBufferQueue::BufferItem* CircularBufferQueue::PeekTail()
	{
		BufferItem* pHead = m_HeadPos.load(std::memory_order_relaxed);

		if (pHead == nullptr)
			return nullptr;

        BufferItem* curTail = m_TailPos.load(std::memory_order_relaxed);
		if (curTail == pHead) // queue is empty
			return nullptr;

		ItemState tailState = curTail->State.load(std::memory_order_relaxed);

		if (tailState != ItemState::Filled && curTail != pHead)
			return PeekNext(curTail);

        std::atomic_thread_fence(MemoryOrder::memory_order_acquire);

		return curTail;
	}

	CircularBufferQueue::BufferItem* CircularBufferQueue::PeekNext(BufferItem* item)
	{
        BufferItem* pHead = m_HeadPos.load(std::memory_order_relaxed);

		if (pHead == nullptr)
			return nullptr;

		uintptr_t startPos = (uintptr_t)m_Buffer;

        BufferItem* curTail = item;
		ItemState tailState{};

		do
		{
			BufferItem* nextTail = reinterpret_cast<BufferItem*>(startPos + curTail->NextPos);
			curTail = nextTail;
			tailState = curTail->State.load(std::memory_order_relaxed);
		} while (tailState != ItemState::Filled && curTail != pHead);

		if (curTail == pHead) // queue is empty
			return nullptr;

        std::atomic_thread_fence(MemoryOrder::memory_order_acquire);

		return curTail;
	}


	// get read buffer size
	size_t CircularBufferQueue::GetBufferItemSize(const BufferItem* pBufferItem) const
	{
		if (pBufferItem == nullptr)
			return 0;

		//if (pBufferItem->State != ItemState::Reading)
		//	return 0;

		if (pBufferItem->NextPos == 0)
		{
			auto endPos = (uintptr_t)m_Buffer + (uintptr_t)m_BufferSize;
			return (size_t)(endPos - (uintptr_t)(pBufferItem + 1));
		}

		auto startPos = (uintptr_t)m_Buffer;
		return pBufferItem->NextPos - ((uintptr_t)pBufferItem + sizeof(BufferItem) - startPos);
	}

	bool CircularBufferQueue::CheckIntegrity() const
	{
		// TODO:

		return false;
	}
}

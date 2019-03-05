////////////////////////////////////////////////////////////////////////////////
// 
// Author : KyungKun Ko
//
// Description : Circular Buffer for multithread
//
////////////////////////////////////////////////////////////////////////////////

#include "CoreBasePCH.h"
#include "Memory/SFIMemoryManager.h"
#include "Memory/SFMemory.h"
#include "SFCircularBuffer.h"


namespace SF
{


	CircularBuffer::CircularBuffer(IHeap& heap, size_t bufferSize, uint8_t* externalBuffer)
		: m_BufferSize(bufferSize)
		, m_Buffer(externalBuffer)
	{
		m_ExternalBuffer = externalBuffer != nullptr;
		if (!m_ExternalBuffer)
		{
			m_Buffer = new(heap) uint8_t[m_BufferSize];
		}

		m_TailPos = (reinterpret_cast<BufferItem*>(m_Buffer));
		m_HeadPos = (reinterpret_cast<BufferItem*>(m_Buffer));

		static_assert(sizeof(std::atomic<uint64_t>) == sizeof(uint64_t), "My assumption has broken!");
		memset(m_Buffer, 0, m_BufferSize);
	}

	CircularBuffer::~CircularBuffer()
	{
		if (!m_ExternalBuffer && m_Buffer != nullptr)
			delete[] m_Buffer;
		m_Buffer = nullptr;
	}

	// Clear all items
	void CircularBuffer::Clear()
	{
		m_TailPos = m_HeadPos = 0;
		memset(m_Buffer, 0, m_BufferSize);
	}

	bool CircularBuffer::IsEmpty()
	{
		return m_HeadPos.load(std::memory_order_relaxed) == m_TailPos.load(std::memory_order_relaxed);
	}


	// Reserve buffer. The pointer it returns is reserved for writing, after done writing, Call SetReadyForRead to mark the buffer is ready for read
	CircularBuffer::BufferItem* CircularBuffer::Allocate(size_t bufferSize)
	{
		// We are allocating memory here, so using lockfree doesn't effective because it doesn't guaranteed that writing order in allocated memory space.
		// Let's just use regular sync except head state
		MutexScopeLock ticketScope(m_HeadLock);

		// We only support 8 byte aligned allocation
		bufferSize = AlignUp(bufferSize, 8);

		auto startPos = (const uintptr_t)m_Buffer;
		auto endPos = (uintptr_t)m_Buffer + (uintptr_t)m_BufferSize;

		do
		{
			auto pHead = m_HeadPos.load(std::memory_order_relaxed); // We just need to access this like a simple volatile type
			auto pTail = m_TailPos.load(std::memory_order_acquire);
			BufferItem* pNextHead = nullptr;

			// We want to put BufferItem structure at the end of allocation for next allocation
			auto expectedSize = (uintptr_t)(sizeof(BufferItem) + bufferSize);
			auto expectedEnd = (uintptr_t)pHead + expectedSize;
			if ((uintptr_t)pHead >= (uintptr_t)pTail) // if head is place at the right side
			{
				if (expectedEnd > endPos) // remain buffer is too small. mark current head as dummy and move forward
				{
					// If we don't have enough space between tail and start pos.
					if (((uintptr_t)pTail - startPos) < (uintptr_t)(expectedSize + sizeof(BufferItem)))
						return nullptr;// out of memory

					auto expectedState = ItemState::Free;
					while (!pHead->State.compare_exchange_weak(expectedState, ItemState::Dummy, std::memory_order_relaxed, std::memory_order_acquire))
					{
						if (expectedState != ItemState::Free)
						{
							// Broken?
							assert(false);
							return nullptr;
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
						return nullptr; // out of memory

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
					return nullptr;

				pNextHead = reinterpret_cast<BufferItem*>(expectedEnd);
			}

			// all condition checks have passed
			// Let's change memory values
			auto expectedState = ItemState::Free;
			while (!pHead->State.compare_exchange_weak(expectedState, ItemState::Reserved, std::memory_order_relaxed, std::memory_order_acquire))
			{
				if (expectedState != ItemState::Free)
				{
					// Broken?
					assert(false);
					return nullptr;
				}
			}
			pHead->NextPos = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(pNextHead) - startPos);

			// prepare next head
			pNextHead->State.store(ItemState::Free, std::memory_order_relaxed);// using relaxed here because the write in SetReadyForRead is the most important state writing
			pNextHead->NextPos = 0;
			m_HeadPos.store(pNextHead, std::memory_order_relaxed);

			// we've done
			return pHead;

		} while (true);

		return nullptr;
	}

	// mark the buffer for read
	Result CircularBuffer::Free(BufferItem* pBuffer)
	{
		if (pBuffer == nullptr)
			return ResultCode::INVALID_POINTER;

		auto startPos = (uintptr_t)m_Buffer;
		auto endPos = (uintptr_t)m_Buffer + (uintptr_t)m_BufferSize;


		// for debug
#if defined(_DEBUG) || defined(DEBUG)
		if (pBuffer->NextPos == 0)
		{
			if ((uintptr_t)pBuffer != startPos)
				memset(pBuffer + 1, 0xFF, endPos - (uintptr_t)(pBuffer + 1));
			else
			{
				// Possible broken
				assert(0);
			}
		}
		else
		{
			memset(pBuffer + 1, 0xFF, pBuffer->NextPos - ((uintptr_t)(pBuffer + 1) - startPos));
		}
#endif

		// Flip the state to free
		auto expectedState = ItemState::Reserved;
		while (!pBuffer->State.compare_exchange_weak(expectedState, ItemState::Free, std::memory_order_release, std::memory_order_acquire))
		{
			if (expectedState != ItemState::Reserved && expectedState != ItemState::Dummy)
			{
				// Broken?
				assert(false);
				return ResultCode::UNEXPECTED;
			}
		}



		MutexScopeLock ticketScope(m_HeadLock);
		// And we have to take care of tail position, and this should be rigorously synchronous way
		BufferItem* curTail = m_TailPos.load(std::memory_order_relaxed);
		auto pHead = m_HeadPos.load(std::memory_order_relaxed);
		while (curTail != pHead)
		{
			// if the item state isn't free. it means somebody working on it. leave that free to other thread
			auto tailState = curTail->State.load(std::memory_order_relaxed);
			if (tailState != ItemState::Free && tailState != ItemState::Dummy)
				break;

			BufferItem* nextTail = reinterpret_cast<BufferItem*>(startPos + curTail->NextPos);
			assert((uintptr_t)nextTail >= startPos && (uintptr_t)nextTail < endPos);

			curTail = nextTail;
		}
		m_TailPos.store(curTail, std::memory_order_relaxed);

		return ResultCode::SUCCESS;
	}

	// get read buffer size
	size_t CircularBuffer::GetBufferItemSize(BufferItem* pBufferItem)
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


}

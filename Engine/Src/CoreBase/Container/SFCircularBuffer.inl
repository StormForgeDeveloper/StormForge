////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular Buffer for multithread
//
////////////////////////////////////////////////////////////////////////////////


namespace SF {

		template <size_t SIZE_BUFFER>
		CircularBuffer<SIZE_BUFFER>::CircularBuffer()
			: m_TailPos(reinterpret_cast<std::atomic<uint64_t>*>(m_Buffer))
			, m_HeadPos(reinterpret_cast<std::atomic<uint64_t>*>(m_Buffer))
			, m_nItemCount(0)
		{
			static_assert(sizeof(std::atomic<uint64_t>) == sizeof(uint64_t), "My assumption has broken!");
			memset(m_Buffer, 0, sizeof(m_Buffer));
		}

		template <size_t SIZE_BUFFER>
		CircularBuffer<SIZE_BUFFER>::~CircularBuffer()
		{
		}

		// Clear all items
		template <size_t SIZE_BUFFER>
		void CircularBuffer<SIZE_BUFFER>::Clear()
		{
			m_nItemCount = 0;
			m_TailPos = m_HeadPos = 0;
			memset(m_Buffer, 0, sizeof(m_Buffer));
		}

		template <size_t SIZE_BUFFER>
		bool CircularBuffer<SIZE_BUFFER>::IsEmpty()
		{
			return m_HeadPos.load(std::memory_order_relaxed) == m_TailPos.load(std::memory_order_relaxed);
		}


		// Reserve buffer. The pointer it returns is reserved for writing, after done writing, Call SetReadyForRead to mark the buffer is ready for read
		template <size_t SIZE_BUFFER>
		void* CircularBuffer<SIZE_BUFFER>::Reserve(size_t bufferSize)
		{
			// TODO: performance tweak is required

			MutexScopeLock ticketScope(m_HeadTicketRegister);

			// We only support 8 byte aligned allocation
			bufferSize = AlignUp(bufferSize, 8);

			auto startPos = (uintptr_t)m_Buffer;
			auto endPos = (uintptr_t)m_Buffer + (uintptr_t)SIZE_BUFFER;

			do
			{
				auto pHead = m_HeadPos.load(std::memory_order_acquire);
				auto pTail = m_TailPos.load(std::memory_order_acquire);
				std::atomic<uint64_t>* pNextHead = nullptr;

				// We want to put BufferItem structure at the end of allocation for next allocation
				auto expectedSize = (uintptr_t)(sizeof(BufferItem) + bufferSize);
				auto expectedEnd = (uintptr_t)pHead + expectedSize;
				if ((uintptr_t)pHead >= (uintptr_t)pTail) // if head is place at thr right side
				{
					if (expectedEnd > endPos) // remain buffer is too small. mark current head as dummy and move forward
					{
						if (((uintptr_t)pTail - startPos) < (uintptr_t)(expectedSize + sizeof(BufferItem)))
							return nullptr;// out of memory

						BufferItem headItem, desireItem;
						headItem.Composited = (pHead)->load(std::memory_order_acquire);
						if (headItem.State != ItemState::Free)
							continue; // the block isn't free anymore, try again

						auto expectedComposited = headItem.Composited;
						desireItem.State = ItemState::Dummy;
						desireItem.NextPos = 0;
						while (!pHead->compare_exchange_weak(expectedComposited, desireItem.Composited, std::memory_order_release, std::memory_order_acquire))
						{
							if (expectedComposited != headItem.Composited)
								break;
						}
						if (expectedComposited != headItem.Composited)
							continue; // failed to change, try again

						pNextHead = (std::atomic<uint64_t>*)startPos;
						// prepare next head
						pNextHead->exchange(0, std::memory_order_relaxed);

						// Move head position and try again
						auto expected = pHead;
						while (!m_HeadPos.compare_exchange_weak(expected, (std::atomic<uint64_t>*)startPos, std::memory_order_release, std::memory_order_acquire))
						{
							if (expected != pHead) // Somebody changed? should be broken
							{
								AssertRel(false);
								break; // need to start over
							}
						}

						continue; // start over
					}
					else if ((uintptr_t)(expectedEnd + sizeof(BufferItem)) > endPos)
					{
						// We are going to back to start of
						// We need to make sure we have enough space at the beginning of the buffer
						expectedSize = expectedEnd - (uintptr_t)pHead;
						expectedEnd = endPos;
						pNextHead = (std::atomic<uint64_t>*)startPos;

						// We can't put another head at the beginning of the array
						if (((uintptr_t)pTail - startPos) < sizeof(BufferItem))
							return nullptr; // out of memory
					}
					else
					{
						pNextHead = (std::atomic<uint64_t>*)expectedEnd;
					}
					
				}
				else // head is placed left side
				{
					endPos = (uintptr_t)pTail;
					if ((expectedEnd + (uintptr_t)sizeof(BufferItem)) > endPos) // out of memory, we need next head before tail
						return nullptr;

					pNextHead = (std::atomic<uint64_t>*)expectedEnd;
				}

				// all condition checks have passed
				// Let's change memory values
				BufferItem headItem, desireItem;
				headItem.Composited = (pHead)->load(std::memory_order_acquire);
				if (headItem.State != ItemState::Free)
					continue; // the block isn't free anymore, try again

				// reserve current head
				desireItem.State = ItemState::Reserved;
				desireItem.NextPos = (uint32_t)((uintptr_t)pNextHead - startPos);
				auto expectedComposited = headItem.Composited;
				while (!pHead->compare_exchange_weak(expectedComposited, desireItem.Composited, std::memory_order_release, std::memory_order_acquire))
				{
					if (expectedComposited != headItem.Composited)
						break;
				}
				if (expectedComposited != headItem.Composited)
					continue; // failed to change, try again

				// prepare next head
				pNextHead->exchange(0, std::memory_order_relaxed);

				// Move head position 
				auto expected = pHead;
				while (!m_HeadPos.compare_exchange_weak(expected, pNextHead, std::memory_order_release, std::memory_order_acquire))
				{
					if (expected != pHead) // Somebody changed?
					{
						AssertRel((uintptr_t)pHead != (uintptr_t)m_Buffer);
						break; // need to start over
					}
				}

				if (expected == pHead) // We've done
					return pHead + 1;

			} while (true);

			return nullptr;
		}

		// mark the buffer for read
		template <size_t SIZE_BUFFER>
		Result CircularBuffer<SIZE_BUFFER>::SetReadyForRead(void* pBuffer)
		{
			BufferItem itemHead, orgHead;
			auto pItemHead = (std::atomic<uint64_t>*)((uintptr_t)pBuffer - sizeof(uint64_t));
			auto orgHeadValue = pItemHead->load(std::memory_order_acquire);

			orgHead.Composited = orgHeadValue;
			AssertRel(orgHead.State == ItemState::Reserved);

			auto pAtomicHead = (std::atomic<uint64_t>*)pItemHead;
			itemHead.Composited = orgHeadValue;
			auto expected = orgHeadValue;
			itemHead.State = ItemState::Filled;
			while (pAtomicHead->compare_exchange_weak(expected, itemHead.Composited, std::memory_order_release, std::memory_order_relaxed))
			{
				if (expected != orgHeadValue)
				{
					AssertRel(false); // something very very wrong
					return ResultCode::UNEXPECTED;
				}
			}

			return ResultCode::SUCCESS;
		}

		// Take a buffer for read
		template <size_t SIZE_BUFFER>
		typename CircularBuffer<SIZE_BUFFER>::BufferItem* CircularBuffer<SIZE_BUFFER>::TakeBufferForRead()
		{
			// TODO: performance tweak is required

			auto pHead = m_HeadPos.load(std::memory_order_acquire);

			while (true)
			{
				auto pTail = m_TailPos.load(std::memory_order_acquire);
				if (pHead == pTail)
					return nullptr; //nothing to read at this moment

				BufferItem tail;
				auto tailValueOrg = pTail->load(std::memory_order_acquire);
				tail.Composited = tailValueOrg;
				auto tailOrgState = tail.State;
				switch(tailOrgState)
				{
				case ItemState::Free:
					// the tail already handled, start over
					ThisThread::SleepFor(DurationMS(0));
					continue;
				case ItemState::Reserved:
					// the guy still working on it
					return nullptr;
				case ItemState::Filled:
				case ItemState::Dummy:
					break;
				default:
					// Broken?
					AssertRel(false);
					return nullptr;
				}


				tail.State = ItemState::Reading;
				auto expectedTailValue = tail.Composited;
				while (!pTail->compare_exchange_weak(expectedTailValue, tail.Composited, std::memory_order_release, std::memory_order_relaxed))
				{
					if (expectedTailValue != tailValueOrg)
						break;
				}

				if (expectedTailValue != tailValueOrg)
					continue; // somebody took the tail


				if (tailOrgState == ItemState::Dummy)
				{
					FreeReadBuffer((BufferItem*)pTail);
					// We took care of dummy, start over
					continue;
				}

				return (BufferItem*)pTail;
			}

			// failed for some reason
			return nullptr;
		}

		// FreeBuffer
		template <size_t SIZE_BUFFER>
		Result CircularBuffer<SIZE_BUFFER>::FreeReadBuffer(BufferItem* pBufferItem)
		{
			auto startPos = (uintptr_t)m_Buffer;
			auto endPos = (uintptr_t)m_Buffer + (uintptr_t)SIZE_BUFFER;

			if (pBufferItem == nullptr)
				return ResultCode::INVALID_POINTER;

			auto pCurHead = (std::atomic<uint64_t>*)pBufferItem;
			BufferItem curItem;
			auto orgItemheadValue = pCurHead->load(std::memory_order_consume);
			curItem.Composited = orgItemheadValue;
			if (curItem.State != ItemState::Reading)
			{
				// broken?
				AssertRel(false);
				return ResultCode::UNEXPECTED;
			}


			// moving tail should be the last, after processing data
			auto nextTail = (std::atomic<uint64_t>*)(startPos + curItem.NextPos);
			AssertRel((uintptr_t)nextTail >= startPos && (uintptr_t)nextTail < endPos);


			// for debug
			if (curItem.NextPos == 0)
			{
				if ((uintptr_t)pBufferItem != startPos)
					memset(pBufferItem + 1, 0xFF, endPos - (uintptr_t)pBufferItem - (uintptr_t)sizeof(BufferItem));
				else
				{
					// Possible broken
					AssertRel(0);
				}
			}
			else
			{
				memset(pBufferItem + 1, 0xFF, pBufferItem->NextPos - ((uintptr_t)pBufferItem - startPos) - (uintptr_t)sizeof(BufferItem));
			}

			curItem.State = ItemState::Free;
			auto expectedHeadValue = orgItemheadValue;
			while (pCurHead->compare_exchange_weak(expectedHeadValue, curItem.Composited, std::memory_order_relaxed, std::memory_order_relaxed))
			{
				if (expectedHeadValue != orgItemheadValue)
				{
					// Broken?
					AssertRel(false);
					return ResultCode::UNEXPECTED;
				}
			}

			auto expectedTail = (std::atomic<uint64_t>*)pBufferItem;
			while (!m_TailPos.compare_exchange_weak(expectedTail, nextTail, std::memory_order_release, std::memory_order_relaxed))
			{
				if (expectedTail != (std::atomic<uint64_t>*)pBufferItem)
				{
					// Somebody took the tail
					// this shouldn't be happened
					AssertRel(false);
					return ResultCode::UNEXPECTED;
				}
			}

			return ResultCode::SUCCESS;
		}

		// get read buffer size
		template <size_t SIZE_BUFFER>
		size_t CircularBuffer<SIZE_BUFFER>::GetBufferSize(BufferItem* pBufferItem)
		{
			if (pBufferItem == nullptr)
				return 0;

			//if (pBufferItem->State != ItemState::Reading)
			//	return 0;

			if (pBufferItem->NextPos == 0)
			{
				auto endPos = (uintptr_t)m_Buffer + (uintptr_t)SIZE_BUFFER;
				return (size_t)(endPos - (uintptr_t)(pBufferItem + 1));
			}

			auto startPos = (uintptr_t)m_Buffer;
			return pBufferItem->NextPos - ((uintptr_t)pBufferItem + sizeof(BufferItem) - startPos);
		}



}

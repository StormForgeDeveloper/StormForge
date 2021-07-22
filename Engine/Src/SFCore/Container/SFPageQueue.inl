////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Paged queue
//
////////////////////////////////////////////////////////////////////////////////


namespace SF
{

	template <class DataType>
	PageQueue<DataType>::PageQueue(IHeap& heap, int iDataPerPage)
		: m_Heap(heap)
		, m_NumberOfItemsPerPage(0)
		, m_PageIndex(0)
	{
		// get page item count
		if (iDataPerPage <= 0)
			iDataPerPage = 2048;

		m_NumberOfItemsPerPage = iDataPerPage;


		// calculate alignment
		size_t szDataAllign = __alignof(DataType);
		size_t szPageHdr = sizeof(PageHeader);

		szPageHdr = ((szPageHdr + szDataAllign - 1) / szDataAllign) * szDataAllign;

		m_EnqueueTicket = 0;
		m_DequeueTicket = 0;

		m_EnqueuePage = nullptr;
		m_EnqueueNextPage = nullptr;
		m_DequeuePage = nullptr;
		m_EnqueuePageID = 0;
		m_DequeuePageID = 0;

		// fix up to maximum available power of two size
		auto nearPower = Util::NearPowerOf2((uint32_t)m_NumberOfItemsPerPage);
		m_NumberOfItemsPerPage = nearPower;

		auto newPage = AllocatePage();
		newPage->Header.pNext = AllocatePage();
		m_EnqueuePage.store(newPage, std::memory_order_relaxed);
		m_EnqueuePageID.store(0, std::memory_order_relaxed);
		m_EnqueueNextPage.store(newPage->Header.pNext, std::memory_order_relaxed);
		// two pointer is initialized pointing to default Page
		m_DequeuePage = newPage;
	}


	template <class DataType>
	PageQueue<DataType>::~PageQueue(void)
	{
		Page* pCurPage = (Page*)m_DequeuePage;

		while (pCurPage)
		{
			Page *pNext = pCurPage->Header.pNext;
			FreePage(pCurPage);
			//m_pPageAllocator->Free( pCurPage );
			pCurPage = pNext;
		}
	}

	template <class DataType>
	typename PageQueue<DataType>::Page* PageQueue<DataType>::AllocatePage()
	{
		void *pNewPageBuff = nullptr;

		pNewPageBuff = GetHeap().Alloc(GetPageMemorySize());

		Page *pNewPage = new(pNewPageBuff) Page(m_NumberOfItemsPerPage);
		pNewPage->Header.PageID = m_PageIndex++;

		return pNewPage;
	}

	template <class DataType>
	void PageQueue<DataType>::FreePage(Page* pPage)
	{
		if (pPage == nullptr) return;

		pPage->DeleteElements(m_NumberOfItemsPerPage);

		GetHeap().Free(pPage);
	}

	template <class DataType>
	Result PageQueue<DataType>::DequeuePageMove()
	{
		// We use Page ID to sync check of HeadPage then pointer
		Page* curDequeue = m_DequeuePage.load(std::memory_order_relaxed);
		if (//curDequeue->Header.PageID == m_EnqueuePageID.load(std::memory_order_acquire) || 
			curDequeue == m_EnqueuePage.load(std::memory_order_relaxed))
			return ResultCode::FAIL;

		if (curDequeue->Header.WriteCounter.load(std::memory_order_relaxed) <= m_NumberOfItemsPerPage)
			return ResultCode::FAIL;

		if (curDequeue->Header.pNext == nullptr) return ResultCode::FAIL;

		// change the tail header pointer
		m_DequeuePage.store(curDequeue->Header.pNext, std::memory_order_release);

		FreePage(curDequeue);

		return ResultCode::SUCCESS;
	}

	template <class DataType>
	Result PageQueue<DataType>::DequeuePageMoveMT(uint32_t expectedPageId)
	{
		MutexScopeLock lock(m_DequeuePageRemoveLock);

		// We use Page ID to sync check of HeadPage then pointer
		Page* curDequeue = m_DequeuePage.load(std::memory_order_relaxed);
		if (curDequeue->Header.PageID != expectedPageId)
			return ResultCode::SUCCESS_FALSE;

		if (//curDequeue->Header.PageID == m_EnqueuePageID.load(std::memory_order_acquire) || 
			curDequeue == m_EnqueuePage.load(std::memory_order_relaxed))
			return ResultCode::SUCCESS_FALSE; // It is enqueue page as well at the moment

		if (curDequeue->Header.WriteCounter.load(std::memory_order_relaxed) <= m_NumberOfItemsPerPage)
			return ResultCode::FAIL;

		if (curDequeue->Header.pNext == nullptr)
			return ResultCode::FAIL;

		// change the tail header pointer
		Page* pNewDequeueHead = curDequeue->Header.pNext;
		m_DequeuePage.store(pNewDequeueHead, std::memory_order_relaxed);
		m_DequeuePageID.store(pNewDequeueHead->Header.PageID, std::memory_order_release);

		FreePage(curDequeue);

		return ResultCode::SUCCESS;
	}

	template <class DataType>
	void PageQueue<DataType>::EnqueuePageMove(Page* pMyEnqueuePage, uint32_t myPageID)
	{
		int nLockTry = 0;

		while (pMyEnqueuePage->Header.PageID != m_EnqueuePageID.load(std::memory_order_acquire)
			|| pMyEnqueuePage != m_EnqueuePage.load(std::memory_order_relaxed))
		{
			nLockTry++;
			if (nLockTry % MaximumRetryInARow)
			{
				ThisThread::SleepFor(DurationMS(0));
			}
		}

		Page* newHead = pMyEnqueuePage->Header.pNext;
		if (newHead->Header.pNext == nullptr)
		{
			newHead->Header.pNext = AllocatePage();
			//std::atomic_thread_fence(std::memory_order_release);
		}

		AssertRel((pMyEnqueuePage->Header.PageID + 1) == newHead->Header.PageID);

		// Mark page move is done
		pMyEnqueuePage->Header.WriteCounter.fetch_add(1, std::memory_order_relaxed);

		// order is matter
		m_EnqueuePage.store(newHead, std::memory_order_relaxed);
		m_EnqueueNextPage.store(newHead->Header.pNext, std::memory_order_release);
		// This page id is used for synchronize point to page change
		m_EnqueuePageID.store(newHead->Header.PageID, std::memory_order_release);
	}

	template <class DataType>
	Result PageQueue<DataType>::Enqueue(const DataType& item)
	{
		DataType temp = item;
		return Enqueue(Forward<DataType>(temp));
	}

	template <class DataType>
	Result PageQueue<DataType>::Enqueue(DataType&& item)
	{
		Assert(!IsDefaultValue(item));
		if (IsDefaultValue(item))
			return ResultCode::FAIL;

		// total ticket number
		uint32_t myTicket = m_EnqueueTicket.fetch_add(1, std::memory_order_relaxed);

		// my pertinent PageID...starting from 0
		uint32_t myPageID = (myTicket) / m_NumberOfItemsPerPage;

		// my order in this Page...starting from 0
		uint32_t myCellID = (myTicket) % m_NumberOfItemsPerPage;

		int iTry = 0;
		auto diffPageID = (SignedCounterType)(myPageID - m_EnqueuePageID.load(std::memory_order_acquire));
		Page* pMyEnqueuePage = nullptr;
		while (diffPageID != 0)
		{
			iTry++;
			if (iTry % MaximumRetryInARow)
				ThisThread::SleepFor(DurationMS(0));

			// can write if next page ready
			if (diffPageID == 1) // If next page can be mine
			{
				pMyEnqueuePage = m_EnqueueNextPage.load(std::memory_order_seq_cst);
				if (pMyEnqueuePage != nullptr)
				{
					if (pMyEnqueuePage->Header.PageID == myPageID)
					{
						break;
					}
					pMyEnqueuePage = nullptr;
				}
			}
			else
			{
				// I'm far away to be able to enqueue an item
				//ThisThread::SleepFor(DurationMS(0));
			}

			// try again
			diffPageID = (SignedCounterType)(myPageID - m_EnqueuePageID.load(std::memory_order_relaxed));
		}
		if (pMyEnqueuePage == nullptr)
			pMyEnqueuePage = m_EnqueuePage.load(std::memory_order_seq_cst);

		Assert(pMyEnqueuePage->Header.PageID == myPageID);

		// this page is appropriate to write....write to this page
		if constexpr (CanUseAtomic)
		{
			auto pElement = (Atomic<DataType>*)pMyEnqueuePage->Element;
			pElement[myCellID].store(item);
		}
		else
		{
			pMyEnqueuePage->Element[myCellID] = std::forward<DataType>(item);
		}
		pMyEnqueuePage->SetWritten(myCellID);

		uint32_t WriteCount = pMyEnqueuePage->Header.WriteCounter.fetch_add(1, std::memory_order_release) + 1;

		Assert(WriteCount <= m_NumberOfItemsPerPage);

		if (WriteCount == m_NumberOfItemsPerPage)
		{
			// The last guy handle page move
			EnqueuePageMove(pMyEnqueuePage, myPageID);
		}

		return ResultCode::SUCCESS;
	}

	template <class DataType>
	Result PageQueue<DataType>::Dequeue(DataType& item)
	{
		// empty state / read count is bigger than written count
		if (m_DequeueTicket.load(std::memory_order_relaxed) >= m_EnqueueTicket.load(std::memory_order_relaxed)) return ResultCode::FAIL;

		Page* pCurPage = m_DequeuePage.load(std::memory_order_relaxed);
		if (pCurPage->Header.WriteCounter.load(std::memory_order_relaxed) == 0) return ResultCode::FAIL;

		// read all of the page items...delete used page
		if (pCurPage->Header.ReadCounter.load(std::memory_order_relaxed) == m_NumberOfItemsPerPage)
		{
			// shorten queue size (delete a used page)
			Result hr = DequeuePageMove();

			if (!hr)
			{
				return hr;
			}
		}

		uint32_t myDequeueTicket = m_DequeueTicket.fetch_add(1, std::memory_order_relaxed);

		// my order in this Page...starting from 0
		uint32_t myCellID = (myDequeueTicket) % m_NumberOfItemsPerPage;

		// Read the data & clear that read position 
		int LockTry = 0;
		Page* pMyPage = m_DequeuePage.load(std::memory_order_relaxed);
		while (!pMyPage->HasValue(myCellID))
		{
			LockTry++;
			if (LockTry % MaximumRetryInARow)
			{
				ThisThread::SleepFor(DurationMS(0));
			}
		}

		if constexpr (CanUseAtomic)
		{
			DataType defaultValue{};
			auto pElement = (Atomic<DataType>*)pMyPage->Element;
			item = Forward<DataType>(pElement[myCellID].exchange(defaultValue, MemoryOrder::memory_order_acquire));
		}
		else
		{
			item = Forward<DataType>(pMyPage->Element[myCellID]);
			pMyPage->Element[myCellID] = DataType{};
		}

		// increment item read count
		pMyPage->Header.ReadCounter.fetch_add(1, std::memory_order_release);

		return ResultCode::SUCCESS;
	}

	template <class DataType>
	Result PageQueue<DataType>::DequeueMT(DataType& item, DurationMS uiCheckInterval)
	{
		Result hr = ResultCode::SUCCESS;
		//auto defaultValue = DataType{};

		// total ticket number
		uint32_t myDequeueTicket = m_DequeueTicket.fetch_add(1, std::memory_order_relaxed);

		// my order in this Page...starting from 0
		uint32_t myCellID = (myDequeueTicket) % m_NumberOfItemsPerPage;

		// my pertinent PageID...starting from 0
		uint32_t myPageID = (myDequeueTicket) / m_NumberOfItemsPerPage;

		// Page ID circulation can be occur so change to subtraction
		auto CurDequeuePageId = m_DequeuePageID.load(std::memory_order_relaxed);
		while (myPageID != CurDequeuePageId)
		{
			// It isn't my page, but previous thread might failed to release it
			Page* pCurPage = m_DequeuePage.load(std::memory_order_acquire);
			if (pCurPage->Header.PageID != CurDequeuePageId)
			{
				ThisThread::SleepFor(DurationMS(1));
				continue;
			}

			auto CurReadCount = pCurPage->Header.ReadCounter.load(MemoryOrder::memory_order_acquire);
			if (CurReadCount == m_NumberOfItemsPerPage)
			{
				DequeuePageMoveMT(CurDequeuePageId);
			}

			ThisThread::SleepFor(DurationMS(1));

			CurDequeuePageId = m_DequeuePageID.load(std::memory_order_acquire);
		}

		Page* pMyDequeuePage = m_DequeuePage.load(std::memory_order_acquire);

		// Read the data & clear that read position 
		int LockTry = 0;

		while(!pMyDequeuePage->HasValue(myCellID))
		{
			LockTry++;
			if (LockTry % 5)
			{
				ThisThread::SleepFor(uiCheckInterval);
			}

			//std::atomic_thread_fence(std::memory_order_consume);
		}

		if constexpr (CanUseAtomic)
		{
			auto pElement = (Atomic<DataType>*)pMyDequeuePage->Element;
			item = Forward<DataType>(pElement[myCellID].exchange(DataType{}, MemoryOrder::memory_order_acquire));
		}
		else
		{
			item = Forward<DataType>(pMyDequeuePage->Element[myCellID]);
			pMyDequeuePage->Element[myCellID] = DataType{};
		}

		// increment item read count
		uint32_t ReadCount = pMyDequeuePage->Header.ReadCounter.fetch_add(1, MemoryOrder::memory_order_release) + 1;
		AssertRel(ReadCount <= m_NumberOfItemsPerPage);

		if (ReadCount == m_NumberOfItemsPerPage)
		{
			// even though my page has finished work, previous page could be still being accessed
			// Let's leave it to other thread.
			hr = DequeuePageMoveMT(myPageID);
			AssertRel((hr));
		}

		return hr;
	}



	// Just get first item
	// This will not safe if use DequeueMT
	template <class DataType>
	Result PageQueue<DataType>::GetFront(DataType& item)
	{
		// empty state / read count is bigger than written count
		if (m_DequeueTicket.load(std::memory_order_relaxed) >= m_EnqueueTicket.load(std::memory_order_relaxed)) return ResultCode::FAIL;

		Page* pCurPage = m_DequeuePage.load(std::memory_order_relaxed);
		if (pCurPage->Header.WriteCounter.load(std::memory_order_relaxed) == 0) return ResultCode::FAIL;

		// read all of the page items...delete used page
		if (pCurPage->Header.ReadCounter.load(std::memory_order_relaxed) == m_NumberOfItemsPerPage)
		{
			// shorten queue size (delete a used page)
			Result hr = DequeuePageMove();

			if (!hr)
			{
				return hr;
			}
		}

		uint32_t myDequeueTicket = m_DequeueTicket.load(std::memory_order_relaxed);

		// my order in this Page...starting from 0
		uint32_t myCellID = (myDequeueTicket) % m_NumberOfItemsPerPage;

		// my pertinent PageID...starting from 0
		//uint32_t myPageID = (myDequeueTicket) / m_NumberOfItemsPerPage;

		// Read the data & clear that read position 
		int LockTry = 0;
		Page* pMyPage = m_DequeuePage.load(std::memory_order_relaxed);

		while (!pMyPage->HasValue(myCellID))
		{
			LockTry++;
			if (LockTry % 10)
			{
				ThisThread::SleepFor(DurationMS(0));
			}
		}

		if constexpr (CanUseAtomic)
		{
			auto pElement = (Atomic<DataType>*)pMyPage->Element;
			item = pElement[myCellID].load(MemoryOrder::memory_order_acquire);
		}
		else
		{
			item = pMyPage->Element[myCellID];
		}

		return ResultCode::SUCCESS;
	}

	template <class DataType>
	inline uint32_t PageQueue<DataType>::GetEnqueCount() const
	{
		return m_EnqueueTicket.load(std::memory_order_relaxed) - m_DequeueTicket.load(std::memory_order_relaxed);
	}

	// Clear queue and remove all enqueued items
	// This operation is not thread safe
	template <class DataType>
	void PageQueue<DataType>::ClearQueue()
	{
		m_PageIndex = 1;

		auto enqueueNext = m_EnqueueNextPage.load(std::memory_order_relaxed);
		auto headPage = m_EnqueuePage.load(std::memory_order_relaxed);
		while (m_DequeuePage != headPage)
		{
			// this page is to free.
			Page* pFreePage = (Page*)m_DequeuePage;

			// change the tail header pointer
			m_DequeuePage = pFreePage->Header.pNext;

			FreePage(pFreePage);
		}

		// if it's not deleted, reuse it
		if (enqueueNext)
		{
			enqueueNext->DeleteElements(m_NumberOfItemsPerPage);
			new((void*)enqueueNext) Page(m_NumberOfItemsPerPage);
			enqueueNext->Header.PageID = 1;
			m_PageIndex++;
		}
		else
		{
			enqueueNext = AllocatePage();
		}

		headPage->DeleteElements(m_NumberOfItemsPerPage);
		headPage = new((void*)headPage) Page(m_NumberOfItemsPerPage);
		headPage->Header.PageID = 0;
		headPage->Header.pNext = enqueueNext;
		m_EnqueueNextPage = headPage->Header.pNext;

		Assert(headPage->Header.pNext->Header.PageID == 1);

		// reset counters
		m_EnqueuePageID = 0;
		m_EnqueueTicket = 0;
		m_DequeueTicket = 0;
	}

}


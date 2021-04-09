////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Paged queue
//
////////////////////////////////////////////////////////////////////////////////


namespace SF {


		template <class DataType, class DataStorageType, class StorageAccessor>
		CircularPageQueue<DataType,DataStorageType, StorageAccessor>::CircularPageQueue(IHeap& heap, int iDataPerPage, int initialCircularPageCount)
			: m_TotalPageCount(initialCircularPageCount)
			, m_Heap(heap)
		{
			// get page item count
			if (iDataPerPage <= 0)
				iDataPerPage = 2048;

			if (m_TotalPageCount < 4) m_TotalPageCount = 4;
			m_TotalPageCount = Util::NearPowerOf2(m_TotalPageCount);

			m_CircularPages = new(GetHeap()) std::atomic<Page*>[m_TotalPageCount];
			// This is dangerous, but fast
			memset(m_CircularPages, 0, sizeof(std::atomic<Page*>) * m_TotalPageCount);
			m_NumberOfItemsPerPage = iDataPerPage;

#if defined(CIRCULARPAGEQUEUE_TRACE_PAGE)
			m_PageDebug = new(GetHeap()) PageDebug[m_TotalPageCount];
			memset(m_PageDebug, 0, sizeof(PageDebug) * m_TotalPageCount);
#endif

			// calculate alignment
			size_t szDataAllign = __alignof(DataType);
			size_t szPageHdr = sizeof(PageHeader);

			szPageHdr = ((szPageHdr + szDataAllign - 1) / szDataAllign) * szDataAllign;

			m_PageIDBase = 0;
			m_EnqueueTicket = 0;
			m_DequeueTicket = 0;


			auto nearPower = Util::NearPowerOf2((uint32_t)m_NumberOfItemsPerPage);
			m_NumberOfItemsPerPage = nearPower;
		}


		template <class DataType, class DataStorageType, class StorageAccessor>
		CircularPageQueue<DataType,DataStorageType, StorageAccessor>::~CircularPageQueue(void)
		{
			ClearQueue();
			IHeap::Delete(m_CircularPages);
			m_CircularPages = nullptr;

			for (auto pPoolItem = m_PagePool.Pop(); pPoolItem != nullptr; pPoolItem = m_PagePool.Pop())
			{
				IHeap::Delete((Page*)pPoolItem);
			}
		}

		template <class DataType, class DataStorageType, class StorageAccessor>
		void CircularPageQueue<DataType, DataStorageType, StorageAccessor>::Dispose()
		{
			ClearQueue();

			IHeap::Delete(m_CircularPages);
			m_CircularPages = nullptr;

			for (auto pPoolItem = m_PagePool.Pop(); pPoolItem != nullptr; pPoolItem = m_PagePool.Pop())
			{
				IHeap::Delete((Page*)pPoolItem);
			}

#if defined(CIRCULARPAGEQUEUE_TRACE_PAGE)
			if(m_PageDebug != nullptr)
				IHeap::Delete(m_PageDebug);
#endif
		}


		template <class DataType, class DataStorageType, class StorageAccessor>
		typename CircularPageQueue<DataType,DataStorageType, StorageAccessor>::Page* CircularPageQueue<DataType,DataStorageType, StorageAccessor>::AllocatePage()
		{
			Page *pNewPage = nullptr;

			auto pPoolItem = m_PagePool.Pop();
			if (pPoolItem != nullptr)
			{
				pNewPage = (Page*)pPoolItem;
				pNewPage->Header.Init();
			}
			else
			{
				auto pNewPageBuff = new(GetHeap()) uint8_t[GetPageMemorySize()];
				pNewPage = new(pNewPageBuff) Page(m_NumberOfItemsPerPage);
			}

			return pNewPage;
		}

		template <class DataType, class DataStorageType, class StorageAccessor>
		void CircularPageQueue<DataType,DataStorageType, StorageAccessor>::FreePage(Page* pPage, bool cleanUp)
		{
			if (pPage == nullptr)
				return;

			if (!cleanUp)
			{
				// TODO: need to find a way to wait efficiently
				for(int iTry = 0; iTry < 10 && m_NumberOfItemsPerPage != pPage->Header.WriteCounter.load(std::memory_order_acquire); iTry++)
					ThisThread::SleepFor(DurationMS(1));
				for (int iTry = 0; iTry < 10 && m_NumberOfItemsPerPage != pPage->Header.ReadCounter.load(std::memory_order_acquire); iTry++)
					ThisThread::SleepFor(DurationMS(1));

				Assert(m_NumberOfItemsPerPage == pPage->Header.WriteCounter.load(std::memory_order_acquire));
				Assert(m_NumberOfItemsPerPage == pPage->Header.ReadCounter.load(std::memory_order_acquire));
			}

			pPage->DeleteElements(m_NumberOfItemsPerPage);

			if (m_PagePool.size() > 2)
				IHeap::Free((uint8_t*)pPage);
			else
				m_PagePool.Push(pPage);
		}

		template <class DataType, class DataStorageType, class StorageAccessor>
		Result CircularPageQueue<DataType,DataStorageType, StorageAccessor>::Enqueue(const DataType& item)
		{
			return Enqueue(std::forward<DataType>(const_cast<DataType&>(item)));
		}

		template <class DataType, class DataStorageType, class StorageAccessor>
		Result CircularPageQueue<DataType,DataStorageType, StorageAccessor>::Enqueue(DataType&& item)
		{
			if (m_CircularPages == nullptr)
				return ResultCode::INVALID_POINTER;

			if (IsDefaultValue(item))
			{
				assert(false);
				return ResultCode::FAIL;
			}

			auto expectedTicket = m_EnqueueTicket.load(std::memory_order_relaxed) + 1;
			auto expectedPageID = expectedTicket / m_NumberOfItemsPerPage;

			//auto dequeueTicket = m_DequeueTicket.load(std::memory_order_relaxed);
			//auto dequeuePageID = dequeueTicket / m_NumberOfItemsPerPage;
			//if ((long)(expectedPageID - dequeuePageID) >= m_TotalPageCount) // Circular Queue is full
			//	return ResultCode::FAIL;

			if ((long)(expectedPageID - m_PageIDBase) >= m_TotalPageCount) // Circular Queue is full
				return ResultCode::FAIL;

			// total ticket number
			CounterType enqueueTicket = m_EnqueueTicket.fetch_add(1, std::memory_order_acq_rel);

			auto pageID = enqueueTicket / m_NumberOfItemsPerPage;
			auto queueIndex = pageID % m_TotalPageCount;
			CounterType itemIndex = enqueueTicket % m_NumberOfItemsPerPage;


			Page* pCurPage = nullptr;
			int LockTry = 0;
			do
			{
				LockTry++;
				if (LockTry % MaximumRetryInARow)
				{
					ThisThread::SleepFor(DurationMS(0));
				}

				pCurPage = m_CircularPages[queueIndex].load(std::memory_order_relaxed);
				if (pCurPage == nullptr) // empty add new one
				{
					//SF::TicketScopeLockT<TicketLock> scopeLock(TicketLock::LockMode::Exclusive, m_CircularBufferLock);

					// We need to check after lock
					pCurPage = m_CircularPages[queueIndex].load(std::memory_order_consume);
					if (pCurPage == nullptr)
					{
						auto newPage = AllocatePage();
						newPage->Header.PageID = (decltype(newPage->Header.PageID))pageID;
						pCurPage = newPage;
						Page* expectedPageData = nullptr;
						while (!m_CircularPages[queueIndex].compare_exchange_weak(expectedPageData, newPage, std::memory_order_acq_rel))
						{
							//AssertRel(expectedPageData == nullptr);
							//expectedPageData = nullptr;
							if (expectedPageData != nullptr && expectedPageData != newPage) // if it already has new one
							{
								//auto oldPageID = expectedPageData->Header.PageID;
								//AssertRel(oldPageID == pageID);
								//AssertRel(oldPageID == m_PageIDBase.load(std::memory_order_relaxed));
								//m_PageIDBase.fetch_add(1, std::memory_order_release);
								FreePage(newPage, true);
								pCurPage = expectedPageData;
								break;
							}
							expectedPageData = nullptr;
						}

#if defined(CIRCULARPAGEQUEUE_TRACE_PAGE)
						m_PageDebug[queueIndex].SetupCounter.fetch_add(1, std::memory_order_relaxed);
#endif
					}
				}

			} while (pCurPage->Header.PageID != pageID); // Overflow, wait


			assert(pCurPage->Header.WriteCounter.load(std::memory_order_relaxed) < m_NumberOfItemsPerPage);
			assert(pCurPage->Header.PageID == pageID);

			// this page is appropriate to write....write to this page
			StorageAccessor::Write(pCurPage->Element[itemIndex], std::forward<DataType>(item));
			//pCurPage->Element[itemIndex] = std::forward<DataType>(item);

			CounterType WriteCount = pCurPage->Header.WriteCounter.fetch_add(1, std::memory_order_release) + 1;

			Assert(WriteCount <= m_NumberOfItemsPerPage);
			unused(WriteCount);

			return ResultCode::SUCCESS;
		}

		template <class DataType, class DataStorageType, class StorageAccessor>
		Result CircularPageQueue<DataType,DataStorageType, StorageAccessor>::Dequeue(DataType& item, std::function<bool()> abortCheck)
		{
			if (m_CircularPages == nullptr)
				return ResultCode::INVALID_POINTER;

			auto defaultValue = DataType{};

			//SF::TicketScopeLockT<TicketLock> scopeLock(TicketLock::LockMode::Exclusive, m_CircularBufferLock);

			// empty state / read count is bigger than written count
			// m_EnqueueTicket is number of items have been enqueued
			// m_DequeueTicket is number of items have been dequeued or trying
			if((SignedCounterType)(m_EnqueueTicket.load(std::memory_order_relaxed) - m_DequeueTicket.load(std::memory_order_relaxed)) <= 0)
				return ResultCode::FAIL;

			// total ticket number
			CounterType dequeueTicket = m_DequeueTicket.fetch_add(1, std::memory_order_acq_rel);

			auto pageID = dequeueTicket / m_NumberOfItemsPerPage;
			auto queueIndex = pageID % m_TotalPageCount;
			CounterType itemIndex = dequeueTicket % m_NumberOfItemsPerPage;

			int LockTry = 0;
			Page* pCurPage = m_CircularPages[queueIndex].load(std::memory_order_acquire);
			while (pCurPage == nullptr || pCurPage->Header.PageID != pageID)
			{
				LockTry++;
				if (LockTry % MaximumRetryInARow)
				{
					ThisThread::SleepFor(DurationMS(0));

					if (abortCheck())
					{
						return ResultCode::FAIL;
					}
				}
				pCurPage = m_CircularPages[queueIndex].load(std::memory_order_acquire);
			}

			AssertRel(pCurPage->Header.PageID == pageID);
			AssertRel(pCurPage->Header.ReadCounter.load(std::memory_order_relaxed) < m_NumberOfItemsPerPage);

			// Read the data & clear that read position 
			LockTry = 0;
			while (IsDefaultValue(StorageAccessor::Read(pCurPage->Element[itemIndex])))
			{
				LockTry++;
				if (LockTry % MaximumRetryInARow)
				{
					ThisThread::SleepFor(DurationMS(0));

					if (abortCheck())
					{
						return ResultCode::FAIL;
					}
				}
			}

			StorageAccessor::CopyRValue(item, pCurPage->Element[itemIndex]);

			// Even though previous one is rvalue copy, some datatype doesn't support rvalue copy.
			// Thus, we need to make sure the element is cleaned up
			//pCurPage->Element[itemIndex] = {};

			// increment item read count
			auto readCount = pCurPage->Header.ReadCounter.fetch_add(1, std::memory_order_acq_rel) + 1;
			if (readCount == m_NumberOfItemsPerPage) // If the last item is dequeued
			{
				Page* expectedPageData = pCurPage;
				auto basePageID = m_PageIDBase.load(std::memory_order_acquire);

				// wait base id to be mine
				while (basePageID != pageID)
				{
					LockTry++;
					if (LockTry % MaximumRetryInARow)
					{
						ThisThread::SleepFor(DurationMS(0));

						if (abortCheck())
						{
							return ResultCode::FAIL;
						}
					}

					basePageID = m_PageIDBase.load(std::memory_order_acquire);
				}

				// exchange page pointer
				AssertRel(basePageID == pageID);
				while (!m_CircularPages[queueIndex].compare_exchange_weak(expectedPageData, nullptr, std::memory_order_seq_cst))
				{
					AssertRel(expectedPageData == pCurPage);

					if (abortCheck())
					{
						return ResultCode::FAIL;
					}
				}

#if defined(CIRCULARPAGEQUEUE_TRACE_PAGE)
				m_PageDebug[queueIndex].ClearCounter.fetch_add(1, std::memory_order_relaxed);
#endif


				auto oldPageID = pCurPage->Header.PageID;
				auto oldBasePageID = m_PageIDBase.fetch_add(1, std::memory_order_release);
				AssertRel(oldPageID == pageID);
				AssertRel(oldPageID == oldBasePageID);
				FreePage(pCurPage, false);
			}

			return ResultCode::SUCCESS;
		}



		// Just get first item
		// This will not safe if use DequeueMT
		template <class DataType, class DataStorageType, class StorageAccessor>
		Result CircularPageQueue<DataType,DataStorageType, StorageAccessor>::GetFront(DataType& item)
		{
			if (m_CircularPages == nullptr)
				return ResultCode::INVALID_POINTER;

			//SF::TicketScopeLockT<TicketLock> scopeLock(TicketLock::LockMode::NonExclusive, m_CircularBufferLock);

			Page* pCurPage = nullptr;
			CounterType dequeueTicket = 0;
			int LockTry = 0;
			while (true)
			{
				LockTry++;
				if (LockTry % 5)
				{
					ThisThread::SleepFor(DurationMS(0));
				}

				// Check whether the queue is empty or not
				dequeueTicket = m_DequeueTicket.load(std::memory_order_relaxed);
				if (m_DequeueTicket.load(std::memory_order_relaxed) >= m_EnqueueTicket.load(std::memory_order_relaxed))
					return ResultCode::FAIL;

				auto pageID = dequeueTicket / m_NumberOfItemsPerPage;
				auto queueIndex = pageID % m_TotalPageCount;
				pCurPage = m_CircularPages[queueIndex].load(std::memory_order_relaxed);
				if (pCurPage == nullptr)
					return ResultCode::FAIL;

				if (pCurPage->Header.WriteCounter.load(std::memory_order_relaxed) == 0)
					return ResultCode::FAIL;

				// read all of the page items...delete used page
				if (pCurPage->Header.ReadCounter.load(std::memory_order_acquire) == m_NumberOfItemsPerPage)
				{
					Page* expectedPageData = pCurPage;
					if (m_CircularPages[queueIndex].compare_exchange_weak(expectedPageData, nullptr, std::memory_order_seq_cst))
					{
						// Successfully switched
						FreePage(pCurPage, false);
						pCurPage = nullptr;
						continue;
					}

					// already freed
					if (expectedPageData == nullptr)
						continue;
				}
				else
				{
					// current page has valid data
					break;
				}
			}


			CounterType itemIndex = dequeueTicket % m_NumberOfItemsPerPage;

			// Read the data & clear that read position 
			LockTry = 0;

			item = pCurPage->Element[itemIndex];
			while (IsDefaultValue(item))
			{
				LockTry++;
				if (LockTry % 10)
				{
					ThisThread::SleepFor(DurationMS(0));
				}

				item = pCurPage->Element[itemIndex];
			}

			return ResultCode::SUCCESS;
		}

		template <class DataType, class DataStorageType, class StorageAccessor>
		inline size_t CircularPageQueue<DataType,DataStorageType, StorageAccessor>::size() const
		{
			return m_EnqueueTicket.load(std::memory_order_relaxed) - m_DequeueTicket.load(std::memory_order_relaxed);
		}

		// Clear queue and remove all enqueued items
		// This operation is not thread safe
		template <class DataType, class DataStorageType, class StorageAccessor>
		void CircularPageQueue<DataType,DataStorageType, StorageAccessor>::ClearQueue()
		{
			MutexScopeLock lock(m_CircularBufferLock);
			//SF::TicketScopeLockT<TicketLock> scopeLock(TicketLock::LockMode::Exclusive, m_CircularBufferLock);

			if (m_CircularPages != nullptr)
			{
				for (auto iPage = 0; iPage < m_TotalPageCount; iPage++)
				{
					auto pPage = m_CircularPages[iPage].exchange(nullptr, std::memory_order_acq_rel);
					if (pPage == nullptr) continue;

					FreePage(pPage, true);
				}
			}

			// reset counters
			m_PageIDBase = 0;
			m_EnqueueTicket = 0;
			m_DequeueTicket = 0;
		}

} // namespace SF

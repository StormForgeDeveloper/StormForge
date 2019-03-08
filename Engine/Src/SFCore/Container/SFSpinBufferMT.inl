////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Spin buffer for Multi thread
//
////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//	Spin Buffer Class
//

#define ITEM typename SpinBufferMT<T,BufferSize>::BLOCK


namespace SF {


		template <typename T, int BufferSize>
		SpinBufferMT<T, BufferSize>::SpinBufferMT(void)
		{
		}

		template <typename T, int BufferSize>
		SpinBufferMT<T, BufferSize>::~SpinBufferMT(void)
		{
		}

		template <typename T, int BufferSize>
		ITEM* SpinBufferMT<T, BufferSize>::Write_Lock()
		{
			// lock ticketing
			CounterType myTicket = m_writeTicket.AcquireTicket();


			// Do not cross over the single cycle boundary
			while (((SignedCounterType)(myTicket - m_readTicket.GetWorkingCompleteCount())) >= BufferSize)
			{
				ThisThread::SleepFor(DurationMS(0));
			}

			// total waiting thread count
			CounterType nWaitingOrder = m_writeTicket.GetMyWaitingOrder(myTicket);
			while (nWaitingOrder > MAX_COUNTER)
			{
				if (nWaitingOrder - MAX_COUNTER > 10)
				{
					ThisThread::SleepFor(DurationMS(3));
				}
				else
				{
					ThisThread::SleepFor(DurationMS(0));
				}

				// Update Waiting Order value
				nWaitingOrder = m_writeTicket.GetMyWaitingOrder(myTicket);
			}

			int nWritePos = (myTicket - 1) % BufferSize;

			int nLockTry = 0;
			ITEM_STATE expectedFreeState = ITEM_STATE::STATE_FREE;
			while (!m_SpinBuffer[nWritePos].BlockMode.compare_exchange_weak(expectedFreeState, ITEM_STATE::STATE_WRITE_LOCK, std::memory_order_release, std::memory_order_relaxed))
			{
				nLockTry++;
				if (nLockTry % 5)
				{
					ThisThread::SleepFor(DurationMS(0));
				}
				expectedFreeState = ITEM_STATE::STATE_FREE;
			}

			Assert(m_SpinBuffer[nWritePos].BlockMode.load(std::memory_order_relaxed) == ITEM_STATE::STATE_WRITE_LOCK);

			// return buffer block
			return &m_SpinBuffer[nWritePos];
		}

		template <typename T, int BufferSize>
		void SpinBufferMT<T, BufferSize>::Write_Unlock(ITEM* pItem)
		{
			Assert(pItem->BlockMode.load(std::memory_order_relaxed) == ITEM_STATE::STATE_WRITE_LOCK);

			pItem->BlockMode.store(ITEM_STATE::STATE_WRITE_UNLOCK, std::memory_order_release);

			// increase now servig thread count
			m_writeTicket.ReleaseTicket();
		}

		template <typename T, int BufferSize>
		void SpinBufferMT<T, BufferSize>::Read_Unlock(ITEM* pItem)
		{
			AssertRel(pItem->BlockMode.load(std::memory_order_relaxed) == ITEM_STATE::STATE_READ_LOCK);

			pItem->BlockMode.store(ITEM_STATE::STATE_FREE, std::memory_order_release);

			m_readTicket.ReleaseTicket();
		}

		// size of buffer writing complet and get ready for reading
		template <typename T, int BufferSize>
		CounterType SpinBufferMT<T, BufferSize>::GetReadableCount()
		{
			// Already reading started count....
			CounterType nReadWorking = m_readTicket.GetNowWorkingCount();

			// Writing Complete Count...
			CounterType	nWriteComplete = m_writeTicket.GetWorkingCompleteCount();

			AssertRel((nWriteComplete - nReadWorking) >= 0);

			return nWriteComplete - nReadWorking;
		}


}

#undef ITEM 

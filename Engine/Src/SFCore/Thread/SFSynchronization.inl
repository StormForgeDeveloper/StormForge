////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread Synchronize
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {

	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Spinlock class
	//


	// Lock
	void SpinLock::Lock()
	{
		int iLockTry = 0;
		int32_t expected = STATE_FREE;
		while (!m_LockValue.compare_exchange_weak(expected, STATE_LOCKED, std::memory_order_acquire, std::memory_order_relaxed))
		{
			iLockTry++;
			if (iLockTry % 5)
			{
				std::this_thread::sleep_for(DurationMS(0));
			}

			expected = STATE_FREE;
		}
	}

	// Unlock
	void SpinLock::UnLock()
	{
		m_LockValue.store(STATE_FREE, std::memory_order_relaxed);
	}

	// Try lock bit a while
	bool SpinLock::TryLock(int iTryCount)
	{
		int iLockTry = 0;
		int32_t expected = STATE_FREE;

		while (!m_LockValue.compare_exchange_weak(expected, STATE_LOCKED, std::memory_order_acquire, std::memory_order_relaxed))
		{
			iLockTry++;

			if (iLockTry > iTryCount)
				return false;

			if (iLockTry % 5)
			{
				ThisThread::SleepFor(DurationMS(0));
			}

			expected = STATE_FREE;
		}

		return true;
	}





	// Reset ticket
	inline void Ticketing::Reset()
	{
		m_Working = 0;
		m_Worked = 0;
	}

	// Ticketing
	inline Ticketing::Ticket Ticketing::AcquireTicket()
	{
		return m_Working.fetch_add(1, std::memory_order_acquire) + 1;
	}

	inline Ticketing::Ticket Ticketing::ReleaseTicket()
	{
		return m_Worked.fetch_add(1, std::memory_order_release) + 1;
	}

	inline Ticketing::Ticket Ticketing::GetMyWaitingOrder(Ticket myTicket) const
	{
		SignedCounterType Diff = (SignedCounterType)(myTicket - m_Worked.load(std::memory_order_relaxed));
		if (Diff < 0) Diff = 0;
		return (Ticket)Diff;
	}

	inline void Ticketing::WaitMyOrder(Ticket myTicket) const
	{
		Ticketing::Ticket myOrder = GetMyWaitingOrder(myTicket);

		while (myOrder > 1)
		{
			auto sleepTime = myOrder * 2;
			ThisThread::SleepFor(DurationMS(std::min(5, (int)sleepTime)));

			myOrder = GetMyWaitingOrder(myTicket);
		}
	}

	inline Ticketing::Ticket Ticketing::GetNowWorkingCount() const
	{
		return m_Working.load(std::memory_order_relaxed);
	}

	inline Ticketing::Ticket Ticketing::GetWorkingCompleteCount() const
	{
		return m_Worked.load(std::memory_order_relaxed);
	}






	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Ticket Lock Class
	//

	TicketLock::TicketLock()
	{
		//m_NonExclusiveWorkerCount[0] = 0;
		//m_NonExclusiveWorkerCount[1] = 0;
		m_NonExclusiveCount = 0;
	}

	TicketLock::~TicketLock()
	{
	}

	// Exclusive lock/unlock
	void TicketLock::ExLock()
	{
		m_ExLock.Lock();
		m_IsLocked = true;

		// increase non exclusive index before we put free state
		//auto curNonExIndex = m_NonExclusiveIndex.load(std::memory_order_acquire) % countof(m_NonExclusiveWorkerCount);
		// wait all non exclusive workers to finish their job
		auto& curCounter = m_NonExclusiveCount;// m_NonExclusiveWorkerCount[curNonExIndex];
		while (curCounter.load(std::memory_order_relaxed) > 0)
		{
			ThisThread::SleepFor(DurationMS(0));
		}

		//m_NonExclusiveIndex.fetch_add(1, std::memory_order_release);
	}

	void TicketLock::ExUnlock()
	{
		m_IsLocked = false;
		m_ExLock.UnLock();
	}

	// Non-Exclusive lock/unlock
	void TicketLock::NonExLock()
	{
		MutexScopeLock scopeLock(m_ExLock);

		//auto curNonExIndex = m_NonExclusiveIndex.load(std::memory_order_acquire) % countof(m_NonExclusiveWorkerCount);
		// wait all non exclusive workers to finish their job
		//m_NonExclusiveWorkerCount[curNonExIndex].fetch_add(1, std::memory_order_release);
		m_NonExclusiveCount.fetch_add(1, std::memory_order_relaxed);
	}

	void TicketLock::NonExUnlock()
	{
		//auto curNonExIndex = m_NonExclusiveIndex.load(std::memory_order_acquire) % countof(m_NonExclusiveWorkerCount);
		// wait all non exclusive workers to finish their job
		auto count = m_NonExclusiveCount.fetch_sub(1, std::memory_order_release);// m_NonExclusiveWorkerCount[curNonExIndex].fetch_sub(1, std::memory_order_relaxed);
		unused(count);
		assert(count >= 0);
	}




	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Scope TicketLock Class
	//

	template< class TicketLockType >
	TicketScopeLockT<TicketLockType>::TicketScopeLockT(TicketLock::LockMode lockMode, TicketLockType &ticketLock)
		: m_LockMode(lockMode)
		, m_TicketLock(ticketLock)
	{
		Assert(m_LockMode == TicketLock::LockMode::Exclusive || m_LockMode == TicketLock::LockMode::NonExclusive);
		if (m_LockMode == TicketLock::LockMode::Exclusive)
			m_TicketLock.ExLock();
		else
			m_TicketLock.NonExLock();
	}

	template< class TicketLockType >
	TicketScopeLockT<TicketLockType>::~TicketScopeLockT()
	{
		if (m_LockMode == TicketLock::LockMode::Exclusive)
			m_TicketLock.ExUnlock();
		else
			m_TicketLock.NonExUnlock();
	}

}

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread Synchronize
//
////////////////////////////////////////////////////////////////////////////////



#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Thread/SFThread.h"
#include "SFResult.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {




	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Sync counter class
	//

	class SyncCounter : public std::atomic<CounterType>
	{
	public:
		SyncCounter()                    { store(0, std::memory_order_release); }
		SyncCounter(CounterType value)   { store(value, std::memory_order_release); }

		SyncCounter& operator = (CounterType value) { store(value, std::memory_order_seq_cst); return *this; }
		SyncCounter& operator = (const SyncCounter& value) { store(value.load(std::memory_order_relaxed), std::memory_order_seq_cst); return *this; }
	};



	// Scope counter
	class ScopeCounter
	{
	public:
		ScopeCounter(SyncCounter& counterInstance) : m_CounterInstance(counterInstance)
		{
			m_CounterInstance.fetch_add(1, std::memory_order_acquire);
		}

		~ScopeCounter()
		{
			m_CounterInstance.fetch_sub(1, std::memory_order_release);
		}

	private:
		SyncCounter &m_CounterInstance;
	};

	
	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Spinlock class
	//
	
	class SpinLock
	{
	public:
		// Lock state
		enum {
			STATE_FREE,
			STATE_LOCKED,
		} LOCK_STATE;
	private:

		// Lock state
		std::atomic<int32_t> m_LockValue; 
   
	public:
		SpinLock() : m_LockValue(STATE_FREE) { } 
		~SpinLock() {}

	public:
		// Lock
		inline void Lock();
	
		// Unlock
		inline void UnLock();

		// Try lock bit a while
		inline bool TryLock(int iTryCount = 100);

		inline int32_t	GetLockCount() { return m_LockValue; }
	};




	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Scopelock class
	//

	class ScopeLock
	{
	private:
		// Spin lock to controllered by scope
		SpinLock& m_SpinLock;


	public:
		// Constructor/destructor
		ScopeLock(SpinLock& nLock)
			:m_SpinLock(nLock)
		{
			m_SpinLock.Lock();
		}
	
		~ScopeLock()
		{
			m_SpinLock.UnLock();
		}
	};




	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Ticketing class
	//		- This works only when everybody wait their order
	//

	class Ticketing
	{
	public:
		typedef CounterType Ticket;

		// working thread count...until now
		SyncCounter m_Working;

		// working complete thread count..
		SyncCounter m_Worked;

		Ticketing() {}
		~Ticketing() {}
		

		// Reset ticket
		void Reset();


		// getting a ticket
		Ticket AcquireTicket();

		// using done the ticket
		Ticket ReleaseTicket();

		// getting my waiting order
		Ticket GetMyWaitingOrder(Ticket) const;

		void WaitMyOrder(Ticket ticket) const;

		// getting total waiting thread count
		Ticket GetTotalWaitingCount() const;

		// getting working thread count...until now;
		Ticket GetNowWorkingCount() const;

		// getting worked thread count...until now;
		Ticket GetWorkingCompleteCount() const;
	};





	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Scope Ticketing Class
	//

	class TicketScope
	{
	private:
		Ticketing &m_TicketRegister;

		Ticketing::Ticket m_Ticket;

	public:

		TicketScope(Ticketing &ticketRegister);

		void WaitMyOrder();

		~TicketScope();

	};

	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Ticket Lock Class with mode support
	//

	class TicketLock
	{
	public:
		enum class LockMode : uint32_t
		{ 
			Free, 
			NonExclusive,
			Exclusive,
		};

	private:
		// read lock count
		//std::atomic<int32_t>	m_NonExclusiveWorkerCount[3];
		std::atomic<uint32_t>	m_NonExclusiveCount;
		CriticalSection			m_ExLock;
		bool					m_IsLocked = false;

	public:
		inline TicketLock();
		inline ~TicketLock();

		// Exclusive lock/unlock
		inline void ExLock();
		inline void ExUnlock();

		// Non-Exclusive lock/unlock
		inline void NonExLock();
		inline void NonExUnlock();

		// checking only ex lock state
		// Use only for debugging
		bool IsLocked() { return m_IsLocked; }
	};

	// Fake ticket lock
	class FakeTicketLock
	{
	public:
	private:

	public:
		FakeTicketLock(){}
		~FakeTicketLock(){}

		// Exclusive lock/unlock
		inline void ExLock() {}
		inline void ExUnlock() {}

		// Non-Exclusive lock/unlock
		inline void NonExLock() {}
		inline void NonExUnlock() {}

		// Query status
		inline CounterType GetTicketCount() const {return 0;}
		inline CounterType GetNonExclusiveCount() const {return 0;}
		inline bool	IsLocked() const {return false;}
	};




	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Scope TicketLock Class
	//

	template< class TicketLockType >
	class TicketScopeLockT
	{
	private:
		TicketLock::LockMode	m_LockMode;
		TicketLockType &m_TicketLock;

	public:

		TicketScopeLockT( TicketLock::LockMode lockMode, TicketLockType &ticketLock );	
		~TicketScopeLockT();

	};

	typedef TicketScopeLockT<TicketLock> TicketScopeLock;



	extern template class TicketScopeLockT<TicketLock>;
	extern template class TicketScopeLockT<FakeTicketLock>;

	



}; // namespace SF

#include "SFSynchronization.inl"



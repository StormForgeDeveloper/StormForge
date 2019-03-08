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
#include "SFResult.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {


	/////


	///////////////////////////////////////////////////////////////////////////////
	//
	//	Critical Section
	//

	class MutexBase
	{
	public:
		virtual void Lock() = 0;
		virtual void UnLock() = 0;
	};


	// Scope locker
	class MutexScopeLock
	{
	public:
		MutexScopeLock(MutexBase& lock) : m_Mutex(lock)
		{
			m_Mutex.Lock();
		}

		~MutexScopeLock()
		{
			m_Mutex.UnLock();
		}

	private:
		MutexBase &m_Mutex;
	};



#if defined(_WIN32) || defined(_WIN64)
#include "SFSystemSynchronize_win.inl"
#else
#include "SFSystemSynchronize_linux.inl"
#endif


	// It's not actually ticket lock but it works very well
	class WriteOnlyTicketLock
	{
	public:
	private:
		SF::CriticalSection m_WriteCriticalSection;

	public:
		WriteOnlyTicketLock() {}
		~WriteOnlyTicketLock() {}

		// Exclusive lock/unlock
		inline void ExLock() { m_WriteCriticalSection.Lock(); }
		inline void ExUnlock() { m_WriteCriticalSection.UnLock(); }

		// Non-Exclusive lock/unlock
		inline void NonExLock() {}
		inline void NonExUnlock() {}

		// Query status
		inline CounterType GetTicketCount() const { return 0; }
		inline CounterType GetNonExclusiveCount() const { return 0; }
		inline bool	IsLocked() const { return false; }
	};


}; // namespace SF


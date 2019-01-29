////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Timer scheduler
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryPool.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Thread/SFSystemSynchronization.h"
#include "Task/SFTimerSchedulerAction.h"



namespace SF {



	// Shared object base
	class TimerScheduler
	{
	public:

	private:
		// Minimum timer tick time when the action doesn't assigned a valid tick time
		DurationMS m_FailSafeTimerTickInterval;

		// Assert on invalid tick time
		bool m_AssertOnInvalidTickTime;

		// timer map
		DualSortedMap<uint64_t, SharedPointerT<TimerAction>> m_TimerMap;
		//BR::CriticalSection m_WriteLock;
		ThreadID m_WorkingThreadID;

		std::atomic<int> m_IsWriteLocked;

		std::function<bool(const uint64_t&, const SharedPointerT<TimerAction>&)> m_TimerTickActionUpdate;
		bool TimerTickActionUpdate(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction);

		TimeStampMS m_GetNextTickResult;
		std::function<bool(const uint64_t&, const SharedPointerT<TimerAction>&)> m_TimerTickActionGetNextTick;
		bool TimerTickActionGetNextTick(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction);

	public:

		TimerScheduler(IHeap& memoryManager);

		void Clear();

		void SetFailSafeTimerTickInterval(DurationMS timerTick)				{ m_FailSafeTimerTickInterval = timerTick; }
		void SetAssertOnInvalidTickTime(bool assertOn)						{ m_AssertOnInvalidTickTime = assertOn; }

		ThreadID GetWorkingThreadID() const { return m_WorkingThreadID; }
		void UpdateWorkingThreadID(ThreadID threadID);

		Result AddTimerAction(ThreadID threadID, TimerAction* pAction);
		Result RemoveTimerAction(ThreadID threadID, TimerAction* pAction);
		Result CommitChanges(ThreadID threadID);

		Result Reschedul(ThreadID threadID, TimerAction* pAction);

		TimeStampMS GetNextTimeTick();

		CounterType GetScheduledItemCount()								{ return m_TimerMap.size(); }
		CounterType GetChangedItemCount()								{ return m_TimerMap.GetWriteItemCount(); }

		void ValidateTimerKeys();

		void UpdateTick(ThreadID threadID);
	};


}; // namespace SF


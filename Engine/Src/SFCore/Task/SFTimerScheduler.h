////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Timer scheduler
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFCircularPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "Multithread/SFSystemSynchronization.h"
#include "Task/SFTimerSchedulerAction.h"



namespace SF {



	// Shared object base
	class TimerScheduler
	{
	private:
		// Minimum timer tick time when the action doesn't assigned a valid tick time
		DurationMS m_FailSafeTimerTickInterval;

		// Assert on invalid tick time
		bool m_AssertOnInvalidTickTime;

		// timer map
		DualSortedMap<uint64_t, SharedPointerT<TimerAction>> m_TimerMap;
		ThreadID m_WorkingThreadID;

		// objects needs reschedule
		CircularPageQueue<SharedPointerT<TimerAction>> m_RescheduleQueue;

		//std::atomic<int> m_IsWriteLocked;

		std::function<bool(const uint64_t&, const SharedPointerT<TimerAction>&)> m_TimerTickActionUpdate;
		bool TimerTickActionUpdate(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction);

		TimeStampMS m_GetNextTickResult;
		std::function<bool(const uint64_t&, const SharedPointerT<TimerAction>&)> m_TimerTickActionGetNextTick;
		bool TimerTickActionGetNextTick(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction);

		void UpdateRescheduleQueue();
	public:

		TimerScheduler(IHeap& heap);

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

		CounterType GetScheduledItemCount()								{ return m_TimerMap.GetWriteItemCount() + m_RescheduleQueue.size(); }

		void ValidateTimerKeys();

		void UpdateTick(ThreadID threadID);
	};


} // namespace SF


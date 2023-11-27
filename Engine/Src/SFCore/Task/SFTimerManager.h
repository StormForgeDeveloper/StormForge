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
#include "Task/SFTimerAction.h"



namespace SF {


    /////////////////////////////////////////////////////////////////////////////////////////
	// Timer schedule manager. Non-thread safe
	class TimerManager
	{
	private:
		// Minimum timer tick time when the action doesn't assigned a valid tick time
		DurationMS m_FailSafeTimerTickInterval;

		// Assert on invalid tick time
		bool m_AssertOnInvalidTickTime;

		// timer map. We don't use thread safety, however, DualSortedMap provides separation between read and write tree and safely add/removed during tick update.
		DualSortedMap<uint64_t, SharedPointerT<TimerAction>> m_TimerMap;

		std::function<bool(const uint64_t&, const SharedPointerT<TimerAction>&)> m_TimerTickActionUpdate;
		bool TimerTickActionUpdate(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction);

		TimeStampMS m_GetNextTickResult;
		std::function<bool(const uint64_t&, const SharedPointerT<TimerAction>&)> m_TimerTickActionGetNextTick;
		bool TimerTickActionGetNextTick(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction);

	public:

		TimerManager(IHeap& heap = GetSystemHeap(), uint failSafeTimerTickInterval = 30 * 1000);

		void Clear();

		void SetFailSafeTimerTickInterval(DurationMS timerTick)				{ m_FailSafeTimerTickInterval = timerTick; }
		void SetAssertOnInvalidTickTime(bool assertOn)						{ m_AssertOnInvalidTickTime = assertOn; }

		// Kick the task so that it updated asap
		Result KickTickUpdate(const SharedPointerT<TimerAction>& pAction);

		Result AddTimerAction(const SharedPointerT<TimerAction>& pAction);
		Result RemoveTimerAction(const SharedPointerT<TimerAction>& pAction);
		Result CommitChanges();

        // Reschedule action if it has different next tick time signature
		Result Reschedule(const SharedPointerT<TimerAction>& pAction);

		TimeStampMS GetNextTimeTick();

		CounterType GetScheduledItemCount()								{ return m_TimerMap.GetWriteItemCount(); }

		void ValidateTimerKeys();

		void UpdateTick();
	};


} // namespace SF


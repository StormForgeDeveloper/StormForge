////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Timer scheduler
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
#include "Util/SFToString.h"
#include "Util/SFLog.h"
#include "Task/SFTimerScheduler.h"
#include "ResultCode/SFResultCodeLibrary.h"



namespace SF {

	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	TimerScheduler::TimerScheduler()
		: m_FailSafeTimerTickInterval(500)
		, m_AssertOnInvalidTickTime(false)
	{
	}

	void TimerScheduler::Clear()
	{
		m_TimerMap.ClearMap();
	}

	bool TimerScheduler::TimerTickActionGetNextTick(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction)
	{
		m_GetNextTickResult = pAction->GetScheduledTime();
		return false;
	}

	bool TimerScheduler::TimerTickActionUpdate(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction)
	{
		TimeStampMS currentTime = Util::Time.GetTimeMs();
		TimerAction::TimeKey key;
		key.TimerKey = keyVal;

		auto diff = (key.Components.NextTickTime - currentTime);
		if ((int)diff.count() > 0)
			return false;

		SharedPointerT<TimerAction> removed;
		Result hr = m_TimerMap.Remove(key.TimerKey, removed);
		if (!hr.IsSuccess())
		{
			hr = m_TimerMap.Remove(pAction->GetInQueueKey().TimerKey, removed);
			Assert((hr));
		}
		assert(static_cast<const SharedPointerT<TimerAction>&>(pAction) == removed);
		// removed clear in-queue time
		pAction->m_ScheduledKey.Components.NextTickTime = TimeStampMS::max();
		//pAction->m_Queued = false;

		//auto savedTime = key;
		auto diffTime = pAction->m_TimerKey.Components.NextTickTime - Util::Time.GetTimeMs();
		unused(diffTime);
		Assert((INT)diffTime.count() < 5000);

		bool bIsNeedToKeep = pAction->OnTimerTick();

		// if it doesn't need to be scheduled anymore
		auto nextDiff = (INT)(pAction->m_TimerKey.Components.NextTickTime - Util::Time.GetTimeMs()).count();
		if (nextDiff < 0)
		{
			if (key.Components.NextTickTime == pAction->m_TimerKey.Components.NextTickTime)
			{
				if (bIsNeedToKeep)
				{
					Assert(!m_AssertOnInvalidTickTime || bIsNeedToKeep);
					SFLog(Engine, Error, "Same Timer value:{1} of {0} correct to fail safe timer value:{2}", pAction->GetDebugString(), pAction->m_TimerKey.Components.NextTickTime, m_FailSafeTimerTickInterval);
					pAction->m_TimerKey.Components.NextTickTime = Util::Time.GetTimeMs() + m_FailSafeTimerTickInterval;
				}
			}
			// this condition isn't true for long running machine
			//else if (pAction->m_TimerKey.Components.NextTickTime == TimeStampMS::max() || !bIsNeedToKeep)
			//{
			//	if (!bIsNeedToKeep)
			//	{
			//		//svrTrace(Trace::TRC_DBG1, "Remove tick timer value:-1, {0}", typeid(*(const TimerAction*)pAction).name());
			//		return true;
			//	}
			//}
			//else
			//{
			//	// Too short period, but negative value is fine
			//	//if (bIsNeedToKeep)
			//	//{
			//	//	svrTrace(Trace::TRC_WARN, "Negative tick timer value:{0}, {1}", nextDiff, typeid(*(const TimerAction*)pAction).name());
			//	//}
			//	//Assert(!m_AssertOnInvalidTickTime);
			//	//pAction->m_TimerKey.NextTickTime = Util::Time.GetTimeMs() + m_FailSafeTimerTickInterval;
			//	//SFLog(Engine, Error, "Invalid Timer value, correct to fail safe timer value");
			//}
		}
		else
		{
			//Assert(nextDiff < 10000);
		}

		if (bIsNeedToKeep)
		{
			//Assert(pAction->m_Queued == false);
			//pAction->m_ScheduledKey.TimerKey = pAction->m_TimerKey.TimerKey;
			//pAction->m_Queued = true;
			//if (!(m_TimerMap.Insert(pAction->m_ScheduledKey.TimerKey, pAction)))
			//{
			//	pAction->m_Queued = false;
			//	Assert(false);
			//}
			m_RescheduleQueue.Enqueue(pAction);
		}
		else
		{
			//svrTrace(Trace::TRC_DBG1, "Remove tick timer {0}", typeid(*(const TimerAction*)pAction).name());
		}

		ValidateTimerKeys();

		return true;

	}

	void TimerScheduler::UpdateWorkingThreadID(ThreadID threadID)
	{
		//Assert(threadID != 0);
		m_WorkingThreadID = threadID;
	}

	Result TimerScheduler::KickTickUpdate(TimerAction* pAction)
	{
		if (pAction == nullptr)
			return ResultCode::INVALID_ARG;

		return m_RescheduleQueue.Enqueue(pAction);
	}

	Result TimerScheduler::AddTimerAction(ThreadID threadID, TimerAction* pAction)
	{
		Result hr = ResultCode::SUCCESS;

		if (pAction == nullptr) return ResultCode::INVALID_POINTER;

		Assert(pAction->m_ScheduledKey.Components.NextTickTime == TimeStampMS::max());

		return m_RescheduleQueue.Enqueue(pAction);
	}


	Result TimerScheduler::RemoveTimerAction(ThreadID threadID, TimerAction* pAction)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<TimerAction> removed;

		if (pAction == nullptr)
			return ResultCode::INVALID_POINTER;

		if (pAction->m_ScheduledKey.Components.NextTickTime == TimeStampMS::max()) // if not schedule
			return hr;

		Assert(m_WorkingThreadID == threadID);
		if (m_WorkingThreadID != threadID)
		{
			hr = (ResultCode::INVALID_THREAD);
			if (!hr.IsSuccess()) return hr;
		}

		if (!m_TimerMap.Remove(pAction->m_ScheduledKey.TimerKey, removed))
		{
			Assert(pAction->m_ScheduledKey.Components.NextTickTime == TimeStampMS::max());
		}

		Assert(removed == pAction);
		pAction->m_ScheduledKey.Components.NextTickTime = TimeStampMS::max();

//#ifdef DEBUG
//		m_TimerMap.ForeachOrderWrite(0, (uint)m_TimerMap.GetWriteItemCount(), [&](const uint64_t& keyVal, SharedPointerT<TimerAction> pInAction) -> bool
//		{
//			Assert(pInAction != pAction);
//			return true;
//		});
//#endif
		//ValidateTimerKeys();

		return hr;
	}

	Result TimerScheduler::CommitChanges(ThreadID threadID)
	{
		//Assert(m_IsWriteLocked.load(std::memory_order_relaxed) == 0);

		Assert(m_WorkingThreadID == threadID);
		if (m_WorkingThreadID != threadID)
		{
			return ResultCode::INVALID_THREAD;
		}
		return m_TimerMap.CommitChanges();
	}

	Result TimerScheduler::Reschedul(ThreadID threadID, TimerAction* pAction)
	{
		Result hr = ResultCode::SUCCESS;

		if (pAction == nullptr)
			return ResultCode::SUCCESS;

		//Assert(m_IsWriteLocked.load(std::memory_order_relaxed) == 0);

		Assert(m_WorkingThreadID == threadID);
		if (m_WorkingThreadID != threadID)
		{
			return ResultCode::INVALID_THREAD;
		}

		if (pAction->m_TimerKey.Components.NextTickTime == pAction->m_ScheduledKey.Components.NextTickTime)
			return hr;

		//if (pAction->m_ScheduledKey.Components.NextTickTime != TimeStampMS::max())
		if (pAction->m_ScheduledKey.Components.NextTickTime != TimeStampMS::max())
		{
			SharedPointerT<TimerAction> removed;
			if (!m_TimerMap.Remove(pAction->m_ScheduledKey.TimerKey, removed))
			{
				Assert(false);
			}
			else
			{
				Assert(removed == pAction);
			}
			pAction->m_ScheduledKey.Components.NextTickTime = TimeStampMS::max();
		}

		//Assert(!m_AssertOnInvalidTickTime || ( (int32_t)(pAction->m_TimerKey.Components.NextTickTime - Util::Time.GetTimeMs()).count() < (2*60*1000)));
		//Assert(pAction->m_TimerKey.Components.NextTickTime != TimeStampMS::max());
		//if (pAction->m_TimerKey.Components.NextTickTime != TimeStampMS::max())
		//{
		//	pAction->m_ScheduledKey.TimerKey = pAction->m_TimerKey.TimerKey;
		//	pAction->m_Queued = true;
		//	if (!(m_TimerMap.Insert(pAction->m_ScheduledKey.TimerKey, pAction)))
		//	{
		//		pAction->m_Queued = false;
		//		Assert(false);
		//	}
		//}

		//ValidateTimerKeys();
		return m_RescheduleQueue.Enqueue(pAction);
	}

	TimeStampMS TimerScheduler::GetNextTimeTick()
	{
		m_GetNextTickResult = TimeStampMS::max();
		m_TimerMap.ForeachReverseOrder(0, 1, [&](const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction) { return TimerTickActionGetNextTick(keyVal, pAction); });

		return m_GetNextTickResult;
	}

	void TimerScheduler::ValidateTimerKeys()
	{
#ifdef DEBUG
		//MutexScopeLock localLock(m_WriteLock);
		//m_TimerMap.ForeachOrderWrite(0, (uint)m_TimerMap.GetWriteItemCount(), [&](const uint64_t& keyVal, SharedPointerT<TimerAction> pAction) -> bool
		//{
		//	Assert(pAction->m_ScheduledKey.NextTickTime != TimeStampMS::max());
		//	AssertRel(keyVal == pAction->m_ScheduledKey.TimerKey);
		//	return true;
		//});
#endif
	}

	void TimerScheduler::UpdateRescheduleQueue()
	{
		auto numReschedule = m_RescheduleQueue.size();
		SharedPointerT<TimerAction> actionItem;
		for (uint iItem = 0; iItem < numReschedule && m_RescheduleQueue.Dequeue(actionItem); iItem++)
		{
			if (actionItem == nullptr || actionItem->GetNextTickTime() == TimeStampMS::max())
				continue;

			// if already in timer map
			if (actionItem->IsScheduled())
				continue;

			actionItem->m_ScheduledKey.TimerKey = actionItem->m_TimerKey.TimerKey;
			if (!m_TimerMap.Insert(actionItem->m_ScheduledKey.TimerKey, actionItem))
			{
				actionItem->m_ScheduledKey.Components.NextTickTime = TimeStampMS::max();
				Assert(false);
			}
		}

	}

	void TimerScheduler::UpdateTick(ThreadID threadID)
	{
		UpdateRescheduleQueue();

		CommitChanges(threadID);

		//m_IsWriteLocked.fetch_add(1, std::memory_order_acquire);

		m_TimerMap.ForeachReverseOrder(0, (uint)m_TimerMap.size(), [&](const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction)
			{
				return TimerTickActionUpdate(keyVal, pAction);
			});

		//m_IsWriteLocked.fetch_sub(1, std::memory_order_release);

		ValidateTimerKeys();
	}




} // namespace SF


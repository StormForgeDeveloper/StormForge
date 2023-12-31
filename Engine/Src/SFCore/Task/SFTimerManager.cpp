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
#include "Task/SFTimerManager.h"
#include "ResultCode/SFResultCodeLibrary.h"



namespace SF {


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	TimerManager::TimerManager(IHeap& heap, uint failSafeTimerTickInterval)
		: m_FailSafeTimerTickInterval(failSafeTimerTickInterval)
		, m_AssertOnInvalidTickTime(false)
		, m_TimerMap(heap)
	{
	}

	void TimerManager::Clear()
	{
		m_TimerMap.ClearMap();
	}

	bool TimerManager::TimerTickActionGetNextTick(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction)
	{
		m_GetNextTickResult = pAction->GetScheduledTime();
		return false;
	}

	bool TimerManager::TimerTickActionUpdate(const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction)
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
			assert((hr));
		}
		assert(removed == pAction);
		// removed clear in-queue time
		pAction->m_ScheduledKey.Components.NextTickTime = TimeStampMS::max();
		//pAction->m_Queued = false;

		//auto savedTime = key;
		DurationMS diffTime = pAction->GetNextTickTime() - Util::Time.GetTimeMs();
		unused(diffTime);
		assert((INT)diffTime.count() < 5000);

		bool bIsNeedToKeep = pAction->OnTimerTick();

		// if it doesn't need to be scheduled anymore
		int nextDiff = (INT)(pAction->GetNextTickTime() - Util::Time.GetTimeMs()).count();
		if (nextDiff < 0)
		{
            // when OnTimerTick returns true new tick time should be assigned
            // check if fail safe timer is enabled
			if (bIsNeedToKeep
                && key.Components.NextTickTime == pAction->m_TimerKey.Components.NextTickTime)
			{
				if (m_FailSafeTimerTickInterval > DurationMS()) // if failsafe tick is enabled
				{
					assert(!m_AssertOnInvalidTickTime || bIsNeedToKeep);
					SFLog(System, Warning, "TimerManager: Same Timer value:{1} of {0} correct to fail safe timer value:{2}", pAction->GetDebugString(), pAction->m_TimerKey.Components.NextTickTime, m_FailSafeTimerTickInterval);
					pAction->m_TimerKey.Components.NextTickTime = Util::Time.GetTimeMs() + m_FailSafeTimerTickInterval;
				}
                else
                {
                    SFLog(System, Warning, "Removing expired timer action, It asked to keep but no new tick time has been assigned");
                    bIsNeedToKeep = false;
                }
			}
		}
		else
		{
			//Assert(nextDiff < 10000);
		}

		if (bIsNeedToKeep)
		{
            // if we need to keep
            Reschedule(pAction);
		}

		ValidateTimerKeys();

        // keep iterate
		return true;

	}

	Result TimerManager::KickTickUpdate(const SharedPointerT<TimerAction>& pAction)
	{
		if (pAction == nullptr)
			return ResultCode::INVALID_POINTER;

        pAction->SetNextTickTime(Util::Time.GetTimeMs() + DurationMS(0));

        // if already in timer map
        return Reschedule(pAction);
	}

	Result TimerManager::AddTimerAction(const SharedPointerT<TimerAction>& pAction)
	{
		Result hr = ResultCode::SUCCESS;

		if (pAction == nullptr) return ResultCode::INVALID_POINTER;

		Assert(pAction->m_ScheduledKey.Components.NextTickTime == TimeStampMS::max());
        if (pAction->IsScheduled())
        {
            RemoveTimerAction(pAction);
        }

        pAction->m_ScheduledKey.TimerKey = pAction->m_TimerKey.TimerKey;
        return m_TimerMap.Insert(pAction->m_ScheduledKey.TimerKey, pAction);
	}


	Result TimerManager::RemoveTimerAction(const SharedPointerT<TimerAction>& pAction)
	{
		Result hr;
		SharedPointerT<TimerAction> removed;

		if (pAction == nullptr)
			return ResultCode::INVALID_POINTER;

        if (!pAction->IsScheduled())
        {
            return hr;
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

	Result TimerManager::CommitChanges()
	{
		return m_TimerMap.CommitChanges();
	}

	Result TimerManager::Reschedule(const SharedPointerT<TimerAction>& pAction)
	{
		Result hr = ResultCode::SUCCESS;

		if (pAction == nullptr)
			return ResultCode::SUCCESS;

        // If scheduled key and requested key are same
		if (pAction->m_TimerKey.Components.NextTickTime == pAction->m_ScheduledKey.Components.NextTickTime)
			return hr;

        if (pAction->IsScheduled())
        {
            RemoveTimerAction(pAction);
        }

        return AddTimerAction(pAction);
	}

	TimeStampMS TimerManager::GetNextTimeTick()
	{
		m_GetNextTickResult = TimeStampMS::max();
		m_TimerMap.ForeachReverseOrder(0, 1, [&](const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction) { return TimerTickActionGetNextTick(keyVal, pAction); });

		return m_GetNextTickResult;
	}

	void TimerManager::ValidateTimerKeys()
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

	void TimerManager::UpdateTick()
	{
        // commit changes before run tick updates
		CommitChanges();

		m_TimerMap.ForeachReverseOrder(0, (uint)m_TimerMap.size(), [&](const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction)
			{
				return TimerTickActionUpdate(keyVal, pAction);
			});

        // update new tick time
        //CommitChanges();

        ValidateTimerKeys();
	}




} // namespace SF


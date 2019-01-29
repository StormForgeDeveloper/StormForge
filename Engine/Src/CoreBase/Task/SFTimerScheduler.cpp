////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Timer scheduler
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "String/SFToString.h"
#include "Util/SFLog.h"
#include "Task/SFTimerScheduler.h"
#include "ResultCode/SFResultCodeLibrary.h"



namespace SF {

	template class SharedPointerT < TimerAction >;

	
	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//


	TimerAction::TimerAction()
		: m_Queued(false)
	{
		m_InQueueKey.TimerKey = -1;
		TimeData.TimerKey = -1;
	}

	TimerAction::~TimerAction()
	{
	}

	void TimerAction::SetNextTickTime(TimeStampMS nextTickTime)
	{
		auto curTime = Util::Time.GetTimeMs();
		// circular time can be any value
		//Assert(nextTickTime != TimeStampMS::min());
		//if (nextTickTime < curTime || nextTickTime == TimeStampMS::min()) // correct the time
		if (nextTickTime < curTime) // correct the time
			nextTickTime = curTime;
		auto diffTime = nextTickTime - curTime;
		unused(diffTime);
		Assert((INT)diffTime.count() < 60*60*1000);
		
		TimeData.Components.NextTickTime = nextTickTime;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	TimerScheduler::TimerScheduler(IHeap& memoryManager)
		: m_FailSafeTimerTickInterval(500)
		, m_AssertOnInvalidTickTime(false)
		, m_TimerMap(memoryManager)
		//, m_WorkingThreadID(0)
		, m_IsWriteLocked(0)
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
		if (!(hr))
		{
			hr = m_TimerMap.Remove(pAction->GetInQueueKey().TimerKey, removed);
			Assert((hr));
		}
		Assert(removed == pAction);
		// removed clear in-queue time
		pAction->m_InQueueKey.Components.NextTickTime = TimeStampMS::max();
		pAction->m_Queued = false;

		//auto savedTime = key;
		auto diffTime = pAction->TimeData.Components.NextTickTime - Util::Time.GetTimeMs();
		unused(diffTime);
		Assert((INT)diffTime.count() < 5000);

		bool bIsNeedToKeep = pAction->OnTimerTick();

		// if it doesn't need to be scheduled anymore
		auto nextDiff = (INT)(pAction->TimeData.Components.NextTickTime - Util::Time.GetTimeMs()).count();
		if (nextDiff < 0)
		{
			if (key.Components.NextTickTime == pAction->TimeData.Components.NextTickTime)
			{
				if (bIsNeedToKeep)
				{
					Assert(!m_AssertOnInvalidTickTime || bIsNeedToKeep);
					SFLog(Engine, Error, "Same Timer value:{1} of {0} correct to fail safe timer value:{2}", pAction->GetDebugString(), pAction->TimeData.Components.NextTickTime, m_FailSafeTimerTickInterval);
					pAction->TimeData.Components.NextTickTime = Util::Time.GetTimeMs() + m_FailSafeTimerTickInterval;
				}
			}
			// this condition isn't true for long running machine
			//else if (pAction->TimeData.Components.NextTickTime == TimeStampMS::max() || !bIsNeedToKeep)
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
			//	//pAction->TimeData.NextTickTime = Util::Time.GetTimeMs() + m_FailSafeTimerTickInterval;
			//	//SFLog(Engine, Error, "Invalid Timer value, correct to fail safe timer value");
			//}
		}
		else
		{
			//Assert(nextDiff < 10000);
		}

		if (bIsNeedToKeep)
		{
			//Assert(pAction->TimeData.TimerKey != 0);
			// Time tick can be 0xffffffff
			//Assert(pAction->TimeData.Components.NextTickTime != TimeStampMS::max());
			Assert(pAction->m_Queued == false);
			pAction->m_InQueueKey.TimerKey = pAction->TimeData.TimerKey;
			pAction->m_Queued = true;
			if (!(m_TimerMap.Insert(pAction->m_InQueueKey.TimerKey, pAction)))
			{
				pAction->m_Queued = false;
				Assert(false);
			}
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

	Result TimerScheduler::AddTimerAction(ThreadID threadID, TimerAction* pAction)
	{
		Result hr = ResultCode::SUCCESS;


		Assert(m_WorkingThreadID == threadID);
		if (m_WorkingThreadID != threadID)
		{
			hr = ResultCode::INVALID_THREAD;
			if(!hr) return hr;
		}

		//Assert(m_IsWriteLocked.load(std::memory_order_relaxed) == 0);

		if (pAction == nullptr) return ResultCode::INVALID_POINTER;

		Assert(pAction->m_InQueueKey.Components.NextTickTime == TimeStampMS::max() && pAction->m_Queued == false);
		// new time can be TimeStampMS::max() if muchine is running over 28 days
		//defAssert(pAction->TimeData.Components.NextTickTime != TimeStampMS::max());
		//defAssert(pAction->TimeData.TimerKey != 0);

		Assert(pAction->m_Queued == false);
		pAction->m_Queued = true;
		pAction->m_InQueueKey.TimerKey = pAction->TimeData.TimerKey;
		if (!(m_TimerMap.Insert(pAction->m_InQueueKey.TimerKey, pAction)))
		{
			pAction->m_Queued = false;
			Assert(false);
		}


		return hr;
	}


	Result TimerScheduler::RemoveTimerAction(ThreadID threadID, TimerAction* pAction)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<TimerAction> removed;

		if (pAction == nullptr)
			return hr;

		if (pAction->m_Queued == false) // if not schedule
			return hr;

		Assert(m_WorkingThreadID == threadID);
		if (m_WorkingThreadID != threadID)
		{
			hr = (ResultCode::INVALID_THREAD);
			if (!hr) return hr;
		}

		if (pAction == nullptr) return ResultCode::INVALID_POINTER;

		if (!(m_TimerMap.Remove(pAction->m_InQueueKey.TimerKey, removed)))
		{
			Assert(pAction->m_InQueueKey.Components.NextTickTime == TimeStampMS::max() && pAction->m_Queued == false);
		}

		Assert(removed == pAction);
		pAction->m_InQueueKey.Components.NextTickTime = TimeStampMS::max();
		pAction->m_Queued = false;

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

		if (pAction->TimeData.Components.NextTickTime == pAction->m_InQueueKey.Components.NextTickTime)
			return hr;

		//if (pAction->m_InQueueKey.Components.NextTickTime != TimeStampMS::max())
		if (pAction->m_Queued)
		{
			SharedPointerT<TimerAction> removed;
			if (!(m_TimerMap.Remove(pAction->m_InQueueKey.TimerKey, removed)))
			{
				Assert(false);
			}
			else
			{
				Assert(removed == pAction);
			}
			pAction->m_InQueueKey.Components.NextTickTime = TimeStampMS::max();
			pAction->m_Queued = false;
		}

		Assert(!m_AssertOnInvalidTickTime || ( (int32_t)(pAction->TimeData.Components.NextTickTime - Util::Time.GetTimeMs()).count() < (2*60*1000)));
		Assert(pAction->TimeData.Components.NextTickTime != TimeStampMS::max());
		if (pAction->TimeData.Components.NextTickTime != TimeStampMS::max())
		{
			pAction->m_InQueueKey.TimerKey = pAction->TimeData.TimerKey;
			pAction->m_Queued = true;
			if (!(m_TimerMap.Insert(pAction->m_InQueueKey.TimerKey, pAction)))
			{
				pAction->m_Queued = false;
				Assert(false);
			}
		}

		//ValidateTimerKeys();

		return hr;
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
		//	Assert(pAction->m_InQueueKey.NextTickTime != TimeStampMS::max());
		//	AssertRel(keyVal == pAction->m_InQueueKey.TimerKey);
		//	return true;
		//});
#endif
	}

	void TimerScheduler::UpdateTick(ThreadID threadID)
	{
		CommitChanges(threadID);

		//m_IsWriteLocked.fetch_add(1, std::memory_order_acquire);

		m_TimerMap.ForeachReverseOrder(0, (uint)m_TimerMap.size(), [&](const uint64_t& keyVal, const SharedPointerT<TimerAction>& pAction) { return TimerTickActionUpdate(keyVal, pAction); });

		//m_IsWriteLocked.fetch_sub(1, std::memory_order_release);

		ValidateTimerKeys();
	}




}; // namespace SF


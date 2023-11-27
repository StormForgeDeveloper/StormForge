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

	template class SharedPointerT < TimerAction >;

	
	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	constexpr uint64_t TimerAction::INVALID_TIMERKEY;

	TimerAction::TimerAction()
	{
        m_ScheduledKey.TimerKey = INVALID_TIMERKEY;
        m_TimerKey.TimerKey = INVALID_TIMERKEY;
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
		
        m_TimerKey.Components.NextTickTime = nextTickTime;
	}



} // namespace SF

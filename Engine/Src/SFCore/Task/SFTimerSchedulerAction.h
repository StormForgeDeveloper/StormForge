////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Timer task
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryPool.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Thread/SFSystemSynchronization.h"



namespace SF {



	class TimerAction : public SharedObject
	{
	public:

#pragma pack(push, 4)
		union TimeKey {
			struct {
				uint32_t ObjectID;
				TimeStampMS NextTickTime;
			} Components;

			uint64_t TimerKey;

			TimeKey() {}
		};
#pragma pack(pop)

	private:

		TimeKey m_InQueueKey;
		bool    m_Queued;
		friend class TimerScheduler;

		DurationMS m_TickInterval;

	protected:

		const TimeKey& GetInQueueKey() { return m_InQueueKey; }

	public:
		TimeKey TimeData;

		TimerAction();
		virtual ~TimerAction();

		DurationMS GetTickInterval() { return m_TickInterval; }
		void SetTickInterval(DurationMS interval) { m_TickInterval = interval; }

		bool IsScheduled()									{ return m_InQueueKey.Components.NextTickTime != TimeStampMS::max(); }
		void ClearTime()									{ TimeData.Components.NextTickTime = TimeStampMS::max(); }

		TimeStampMS GetNexTickTime()						{ return TimeData.Components.NextTickTime; }
		void SetNextTickTime(TimeStampMS nextTickTime);

		TimeStampMS GetScheduledTime()						{ Assert(m_InQueueKey.Components.NextTickTime != TimeStampMS::min());  return m_InQueueKey.Components.NextTickTime; }

		virtual bool OnTimerTick() { return false; }

		virtual const char* GetDebugString() = 0;
	};


	extern template class SharedPointerT < TimerAction >;



}; // namespace SF


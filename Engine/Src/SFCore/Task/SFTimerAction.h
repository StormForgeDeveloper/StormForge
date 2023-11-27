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
#include "MemoryManager/SFMemoryPool.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Multithread/SFSystemSynchronization.h"



namespace SF {



	class TimerAction : public SharedObject
	{
	public:

		static constexpr uint64_t INVALID_TIMERKEY = uint64_t(-1);

#pragma pack(push, 4)
		union TimeKey {
			struct {
				uint32_t ObjectId{};// This should be unique id in the processes, something like entity id
				TimeStampMS NextTickTime{};
			} Components{};

			uint64_t TimerKey;
		};
#pragma pack(pop)

		static_assert(sizeof(TimeStampMS) == 4, "This will break TimeKey size assumption");

	private:

        // Registered timer key
        TimeKey m_ScheduledKey;

        // requested timer key
        TimeKey m_TimerKey;
        //bool    m_Queued;
		friend class TimerScheduler;
        friend class TimerManager;

		DurationMS m_TickInterval;

	public:

		TimerAction();
		virtual ~TimerAction();

        const TimeKey& GetInQueueKey() { return m_ScheduledKey; }
        const TimeKey& GetTimeKey() { return m_TimerKey; }

        DurationMS GetTickInterval() const { return m_TickInterval; }
		void SetTickInterval(DurationMS interval) { m_TickInterval = interval; }

		bool IsScheduled() const { return m_ScheduledKey.Components.NextTickTime != TimeStampMS::max(); }
		void ClearTime()									{ m_TimerKey.Components.NextTickTime = TimeStampMS::max(); }

        void SetKeyObjectId(uint objectId) { m_TimerKey.Components.ObjectId = objectId; }
		TimeStampMS GetNextTickTime() const { return m_TimerKey.Components.NextTickTime; }
		void SetNextTickTime(TimeStampMS nextTickTime);

		TimeStampMS GetScheduledTime() const { Assert(m_ScheduledKey.Components.NextTickTime != TimeStampMS::min());  return m_ScheduledKey.Components.NextTickTime; }

		virtual bool OnTimerTick() { return false; }

		virtual const char* GetDebugString() { return "DefaultTimerAction"; }
	};


	extern template class SharedPointerT < TimerAction >;



}; // namespace SF


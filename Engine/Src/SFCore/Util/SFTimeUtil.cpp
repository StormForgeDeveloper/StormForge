////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Time utility 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFTimeUtil.h"
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
#include "Util/SFLog.h"




namespace SF {
	namespace Util {

		Time_Chrono Time;



		////////////////////////////////////////////////////////////////////////////////
		//
		//	Module
		//

		constexpr StringCrc64 LibraryComponentTime::TypeName;

		LibraryComponentTime::LibraryComponentTime()
			: LibraryComponent(StringCrc64("Timer"))
		{

		}

		LibraryComponentTime::~LibraryComponentTime()
		{

		}

		// Initialize server component
		Result LibraryComponentTime::InitializeComponent()
		{
			Result hr = LibraryComponent::InitializeComponent();
			if (hr.IsFailure()) return hr;

			m_Thread.SetFunc([](Thread* pThread)
			{
				DurationMS expectedTickInterval(10);
				pThread->SetPriority(Thread::PRIORITY::TIME_CRITICAL);

				while (1)
				{
					// 50ms will be the precision of our timer
					auto loopInterval = pThread->UpdateInterval(expectedTickInterval);

					if (pThread->CheckKillEvent(loopInterval))
					{
						// Kill Event signaled
						break;
					}

					Time.UpdateTimer();
				}
			});

			m_Thread.Start();
			m_Thread.SetThreadName("TimeUtil");
			return ResultCode::SUCCESS;
		}

		// Terminate server component
		void LibraryComponentTime::DeinitializeComponent()
		{
			LibraryComponent::DeinitializeComponent();

			m_Thread.Stop(true);
		}



		Time_Chrono::Time_Chrono()
			: m_ulTimeStampMs(TimeStampMS())
			, m_ullTimeStampUTC(UTCTimeStampSec())
		{
			auto timeStamp = std::chrono::high_resolution_clock::now().time_since_epoch();
			m_ullTimeStamp.store(timeStamp.count(), std::memory_order_relaxed);
			m_ullTimeStampPrevious = timeStamp;
			m_ulTimeStampMs = TimeStampMS(std::chrono::duration_cast<DurationMS>(timeStamp));

			// Calculate shift of UTC
			tm timeStruct;
			memset(&timeStruct, 0, sizeof(timeStruct));
			timeStruct.tm_year = 1900;
			timeStruct.tm_mday = 1;

			m_ullUTCOffset = DurationMSDouble(0);

			UpdateTimer();
		}

		Time_Chrono::~Time_Chrono()
		{
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// Initialize/Terminate
		//


		// Update Timer
		void Time_Chrono::UpdateTimer()
		{
			m_ullTimeStampPrevious = ClockType::duration(m_ullTimeStamp);

			auto now = std::chrono::high_resolution_clock::now();
			auto timeStamp = now.time_since_epoch();
			m_ullTimeStamp.store(timeStamp.count(), std::memory_order_relaxed);

			m_ulTimeStampMs.store(TimeStampMS(std::chrono::duration_cast<DurationMS>(timeStamp)), std::memory_order_release);

			m_ullTimeStampUTC.store(GetRawUTCSec(), std::memory_order_release);
		}

		// Get time stamp in MS
		TimeStampMS Time_Chrono::GetTimeMs()
		{
			return m_ulTimeStampMs.load(std::memory_order_relaxed);
		}

		// Get UTC time stamp
		UTCTimeStampSec Time_Chrono::GetTimeUTCSec()
		{
			return m_ullTimeStampUTC.load(std::memory_order_relaxed);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// Timer query
		//

		// Get time tick in ms
		TimeStampMS Time_Chrono::GetRawTimeMs()
		{
			auto timeStamp = std::chrono::high_resolution_clock::now().time_since_epoch();
			return TimeStampMS(std::chrono::duration_cast<DurationMS>(timeStamp));
		}


		// Get current UTC sec
		UTCTimeStampSec Time_Chrono::GetRawUTCSec()
		{
			UTCTimeStampMS utcMS = GetRawUTCMs();
			return UTCTimeStampSec(std::chrono::duration_cast<std::chrono::seconds>(utcMS.time_since_epoch()));
		}

		UTCTimeStampMS Time_Chrono::GetRawUTCMs()
		{
			return UTCTimeStampMS(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()));
		}


		void Time_Chrono::UpdateUTCOffset(TimeStampMS expectedTime)
		{
			// TODO: Fixme
			//auto oldValue = 0; m_ullUTCOffset;
			//auto localTime = GetRawUTCMs();
			//auto diff = ((uint64_t)localTime.time_since_epoch().count() - (uint64_t)expectedTime.time_since_epoch().count());

			// Average with previous value
			//if (oldValue.count() != 0)
			//{
			//	m_ullUTCOffset = DurationMS(diff + oldValue.count());
			//}
		}



		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// Utility
		//


		DurationMS TimeMinNonZero(DurationMS timeMs, DurationMS timeMs2)
		{
			if ((INT)timeMs.count() <= 0) return timeMs2;
			if ((INT)timeMs2.count() <= 0) return timeMs;

			return (INT)((timeMs - timeMs2).count()) >= 0 ? timeMs2 : timeMs;
		}

		TimeStampMS TimeMinNonZero(TimeStampMS timeMs, TimeStampMS timeMs2)
		{
			TimeStampMS minT = TimeStampMS::min();
			//TimeStampMS maxT = TimeStampMS::max();

			if (timeMs == minT) return timeMs2;
			if (timeMs2 == minT) return timeMs;

			return timeMs > timeMs2 ? timeMs2 : timeMs;
		}



		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// TimeStampTimer
		//


		const TimeStampMS TimeStampTimer::InvalidTime;


		// set timer
		Result TimeStampTimer::SetTimer(DurationMS TimerDuration, bool bRepeat)
		{
            m_TimerDuration = TimerDuration;
            m_bRepeat = bRepeat;

			m_ulTimeToExpire = Time.GetTimeMs() + TimerDuration;
			if (m_ulTimeToExpire.time_since_epoch().count() == 0)
				m_ulTimeToExpire = Time.GetTimeMs();

			return ResultCode::SUCCESS;
		}


		// Timer check update
		bool	TimeStampTimer::CheckTimer()
		{
			if (m_ulTimeToExpire == InvalidTime)
				return false;

			auto diff = m_ulTimeToExpire - Time.GetTimeMs();
			bool bExpired = ((INT)diff.count() < 0);

			if (bExpired)
			{
				if (m_delOnExpired)
					m_delOnExpired();

                if (m_bRepeat)
                {
                    // restart timer
                    m_ulTimeToExpire = Time.GetTimeMs() + m_TimerDuration;
                    if (m_ulTimeToExpire.time_since_epoch().count() == 0)
                        m_ulTimeToExpire = Time.GetTimeMs();
                }
                else
                {
                    // Clear timer
                    m_ulTimeToExpirePrev = m_ulTimeToExpire;
                    m_ulTimeToExpire = InvalidTime;
                }
			}

			return bExpired;
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// Timer
		//


		const TimeStampMS Timer::InvalidTime;

		// Timer check update
		bool	Timer::CheckTimer()
		{
			if (m_ulTimeToExpire == InvalidTime)
				return false;

			auto diff = m_ulTimeToExpire - Time.GetRawTimeMs();
			bool bExpired = ((INT)diff.count() < 0);

			if (bExpired)
			{
				if (m_delOnExpired)
					m_delOnExpired();

				// Clear timer
				m_ulTimeToExpirePrev = m_ulTimeToExpire;
				m_ulTimeToExpire = InvalidTime;
			}

			return bExpired;
		}

		Result Timer::SetTimer(DurationMS TimerDuration)
		{
			TimeStampMS ulNewTime = Time.GetRawTimeMs() + TimerDuration;

			m_ulTimeToExpire = ulNewTime;
			if (m_ulTimeToExpire.time_since_epoch().count() == 0)
				m_ulTimeToExpire = Time.GetRawTimeMs();

			return ResultCode::SUCCESS;
		}

	}	// namespace Util
} // namespace SF


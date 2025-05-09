////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Time Utility library
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Component/SFLibraryComponent.h"
#include "Multithread/SFThread.h"
#include "Service/SFService.h"

namespace SF {
	namespace Util {




		////////////////////////////////////////////////////////////////////////////////
		//
		//	Win32 timer class
		//

		class Time_Chrono
		{
		private:

			std::chrono::time_point<ClockType> m_TickStamp;

			// Time stamp
			std::atomic<uint64_t>			m_ullTimeStamp;

			ClockType::duration				m_ullTimeStampPrevious;
			std::atomic<TimeStampMS>		m_ulTimeStampMs;
			std::atomic<UTCTimeStampSec>		m_ullTimeStampUTC;

			// Default UTC offset
			DurationMSDouble				m_ullUTCOffset{};


		protected:
			// Update Time stamp
			void		UpdateTimer();

			friend class LibraryComponentTime;

		public:
			Time_Chrono();
			~Time_Chrono();


			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// Time query
			//

			// Get time stamp in ms
			TimeStampMS		GetTimeMs();

			// Get UTC time stamp
			UTCTimeStampSec	GetTimeUTCSec();



			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// Global Time query
			//

			// Get time tick in ms
			TimeStampMS		GetRawTimeMs();

			// Get current UTC sec
			UTCTimeStampSec	GetRawUTCSec();
			UTCTimeStampMS	GetRawUTCMs();


			void			UpdateUTCOffset(TimeStampMS expectedTime);

		};


		// Global main timer
		extern Time_Chrono Time;


		////////////////////////////////////////////////////////////////////////////////
		//
		//	Timer
		//

		class TimeStampTimer
		{
		public:
			const static TimeStampMS	InvalidTime;

		private:

            DurationMS m_TimerDuration;

			TimeStampMS	m_ulTimeToExpire;
			TimeStampMS	m_ulTimeToExpirePrev;

            // if set repeat after expire
            bool m_bRepeat = false;

			// Timer expire caller
			std::function<void()> m_delOnExpired;

		public:
            inline TimeStampTimer() {}
            inline ~TimeStampTimer() {}


			// Set timer delegate
            inline  void	SetTimerFunc(std::function<void()> funcOnExpired) { m_delOnExpired = funcOnExpired; }

			// set timer
			Result	SetTimer(DurationMS TimerDuration, bool bRepeat = false);

			// clear timer
			inline void	ClearTimer() { m_ulTimeToExpire = InvalidTime; }

			TimeStampMS	GetTimerExpireTime() { return m_ulTimeToExpire; }

			// check about timer is working
            inline bool	IsSet() const { return m_ulTimeToExpire != InvalidTime; }
            inline bool	IsTimerWorking() const { return IsSet(); }

			// Timer check update
            bool	CheckTimer();
		};


		class Timer
		{
		public:
			const static TimeStampMS	InvalidTime;

		private:
			TimeStampMS	m_ulTimeToExpire;
			TimeStampMS	m_ulTimeToExpirePrev;

			// Timer expire caller
			std::function<void()> m_delOnExpired;

		public:
			Timer() = default;
			~Timer() = default;


			// Set timer delegate
			 void SetTimerFunc(std::function<void()> funcOnExpired)
			{
				m_delOnExpired = funcOnExpired;
			}

			// set timer
			Result SetTimer(DurationMS TimerDuration);

			// clear timer
			void ClearTimer()
			{
				m_ulTimeToExpire = InvalidTime;
			}

			TimeStampMS	GetTimerExpireTime() { return m_ulTimeToExpire; }

			// check about timer is active
			SF_FORCEINLINE bool IsTimerActive() const
			{
				return m_ulTimeToExpire != InvalidTime;
			}

			// Timer check update
			bool	CheckTimer();
		};

		////////////////////////////////////////////////////////////////////////////////
		//
		//	Module
		//

		class LibraryComponentTime : public LibraryComponent
		{
		public:
			static constexpr StringCrc64 TypeName = "LibraryComponentTime";

		private:

			FunctorThread m_Thread;

		public:

			LibraryComponentTime();
			~LibraryComponentTime();

			virtual const StringCrc64& GetTypeName() const override { return TypeName; }

			// Initialize server component
			virtual Result InitializeComponent() override;
			// Terminate server component
			virtual void DeinitializeComponent() override;

		};



		////////////////////////////////////////////////////////////////////////////////
		//
		//	Utility
		//

		DurationMS TimeMinNonZero(DurationMS timeMs, DurationMS timeMs2);
		TimeStampMS TimeMinNonZero(TimeStampMS timeMs, TimeStampMS timeMs2);

		inline DurationMS TimeSinceRaw(TimeStampMS timeMs)
        {
            TimeStampMS timeCur = Time.GetRawTimeMs();
            return (timeCur > timeMs) ? (timeCur - timeMs) : DurationMS(0);
        }
		inline DurationMS TimeSince(TimeStampMS timeMs)
        {
            TimeStampMS timeCur = Time.GetTimeMs();
            return (timeCur > timeMs) ? (timeCur - timeMs) : DurationMS(0);
        }
		inline DurationSec TimeSinceUTC(UTCTimeStampSec timeUTC)
        {
            UTCTimeStampSec timeCur = Time.GetTimeUTCSec();
            return (timeCur > timeUTC) ? (timeCur - timeUTC) : DurationSec(0);
        }
		inline DurationMS TimeSinceUTC(UTCTimeStampMS timeUTC)
        {
            UTCTimeStampMS timeCur = Time.GetRawUTCMs();
            return (timeCur > timeUTC) ? (timeCur - timeUTC) : DurationSec(0);
        }

	} // namespace Util
} // namespace SF


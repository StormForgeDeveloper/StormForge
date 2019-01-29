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

namespace SF {
	namespace Util {

		TimeStampTimer::TimeStampTimer()
		{
		}

		TimeStampTimer::~TimeStampTimer()
		{
		}

		// Set timer delegate
		void TimeStampTimer::SetTimerFunc(std::function<void()> funcOnExpired)
		{
			m_delOnExpired = funcOnExpired;
		}

		// clear timer
		void TimeStampTimer::ClearTimer()
		{
			m_ulTimeToExpire = InvalidTime;
		}

		// check about timer is working
		bool	TimeStampTimer::IsTimerWorking() const
		{
			return m_ulTimeToExpire != InvalidTime;
		}


	}
}


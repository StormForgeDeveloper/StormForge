////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread library
//	
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFTimeUtil.h"
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
#include "Multithread/SFSynchronization.h"
#include "Multithread/SFSystemSynchronization.h"



namespace SF {


	template class TicketScopeLockT<TicketLock>;
	template class TicketScopeLockT<FakeTicketLock>;




	Ticketing::Ticket Ticketing::GetTotalWaitingCount() const
	{
		return m_Working.load(std::memory_order_relaxed) - m_Worked.load(std::memory_order_relaxed);
	}





	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Scope Ticketing Class
	//


	TicketScope::TicketScope(Ticketing &ticketRegister)
		: m_TicketRegister(ticketRegister)
	{
		m_Ticket = m_TicketRegister.AcquireTicket();
	}

	void TicketScope::WaitMyOrder()
	{
		m_TicketRegister.WaitMyOrder(m_Ticket);
	}

	TicketScope::~TicketScope()
	{
		m_TicketRegister.WaitMyOrder(m_Ticket);
		m_TicketRegister.ReleaseTicket();
	}



#if defined(_WIN32) || defined(_WIN64)


#else

	Event::Event(bool isInitialySet, bool autoReset)
		: m_hEvent(isInitialySet)
		, m_AutoReset(autoReset)
	{
	}

	Event::~Event()
	{
	}

	void Event::Reset()
	{
		m_hEvent.store(false, std::memory_order_seq_cst);
	}

	void Event::Set()
	{
		m_hEvent.store(true, std::memory_order_seq_cst);
	}


	bool Event::WaitEvent(DurationMS waitTimeMs)
	{
		bool bSet = false;
		auto startTime = Util::Time.GetRawTimeMs();
		if (m_AutoReset)
		{
			do
			{
				bSet = m_hEvent.exchange(false, std::memory_order_seq_cst);
			} while (!bSet && Util::TimeSinceRaw(startTime) < waitTimeMs);
		}
		else
		{
			do
			{
				bSet = m_hEvent.load(std::memory_order_seq_cst);
			} while (!bSet && Util::TimeSinceRaw(startTime) < waitTimeMs);
		}

		return bSet;
	}

#endif




}; // namespace SF




////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread safe Stack implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Container/SFStackPool.h"


namespace SF {



		StackPool::StackPool()
			: m_head(nullptr)
			, m_lSize(0)
		{
			//AssertRel( ((int64_t)this & (BR_ALIGN_DOUBLE-1)) == 0 );
			//m_head.pHead = (volatile Item*)nullptr;
			//m_head.TSeqID = 0;
		}


		StackPool::~StackPool()
		{
			//AssertRel( ((int64_t)this & (BR_ALIGN_DOUBLE-1)) == 0 );
			Clear();
		}


		// Clear
		void StackPool::Clear()
		{
			// This stack didn't created item os nothing to release, just clear variables
			m_head.store(nullptr, std::memory_order_relaxed);
			m_lSize = (CounterType)0;
		}

		StackPool::Item* StackPool::Pop()
		{
			CounterType myTicket = m_Ticket.AcquireTicket();

			m_Ticket.WaitMyOrder(myTicket);

			auto currentHeader = m_head.load(std::memory_order_acquire);
			if (currentHeader == nullptr)
			{
				m_Ticket.ReleaseTicket();
				return nullptr;
			}

			m_head.store(currentHeader->pNext, std::memory_order_relaxed);

			currentHeader->pNext = nullptr;

			m_lSize.fetch_sub(1, std::memory_order_relaxed);

			m_Ticket.ReleaseTicket();

			return currentHeader;
		}


		void StackPool::Push(Item* pEntry)
		{
			CounterType myTicket = m_Ticket.AcquireTicket();

			m_Ticket.WaitMyOrder(myTicket);

			auto currentHeader = m_head.load(std::memory_order_acquire);
			Assert(pEntry->pNext == nullptr);
			pEntry->pNext = currentHeader;
			m_head.store(pEntry, std::memory_order_relaxed);

			m_lSize.fetch_add(1, std::memory_order_relaxed);

			m_Ticket.ReleaseTicket();
		}


}	// namespace SF



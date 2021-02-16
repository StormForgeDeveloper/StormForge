////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Spin buffer for Multi thread
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Multithread/SFSynchronization.h"
#include "ResultCode/SFResultCodeLibrary.h"


namespace SF {


		//////////////////////////////////////////////////////////////////////////////////
		//
		//	Spin Buffer Class (N-by-M)
		//

		template <typename T, int BufferSize = 8>
		class SpinBufferMT
		{
			enum
			{
				MAX_COUNTER = BufferSize - 1,
			};

			enum ITEM_STATE
			{
				STATE_FREE,			// Free State, READ_LOCK->FREE
				STATE_WRITE_LOCK,	// locked state to write
				STATE_WRITE_UNLOCK,	// writing complete state
				STATE_READ_LOCK,	// locked state to read
			};

		public:
			// Block of Buffer
			struct BLOCK
			{
				// Buffer block State 
				std::atomic<ITEM_STATE> BlockMode;

				T Data;

				BLOCK()
				{
					// initializing Buffer_state as Free
					BlockMode = ITEM_STATE::STATE_FREE;
					memset(&Data, 0, sizeof(T));
				}
			};


		private:
			// Spin Buffer
			BLOCK m_SpinBuffer[BufferSize];

			// ticket to the entering write section
			Ticketing	m_writeTicket;

			// ticket to the entering read section
			Ticketing	m_readTicket;

		public:
			// Constructor / Destructor
			SpinBufferMT();
			~SpinBufferMT();

		public:
			// Public Interface
				// locking on write mode 
			BLOCK* Write_Lock();
			void Write_Unlock(BLOCK* pItem);

			// locking on read mode 
			template<class Func>
			BLOCK* Read_Lock(Func waitBlockAction)
			{
				constexpr DurationMS sleepOrderWaitFar(10);
				constexpr DurationMS sleepOrderWaitSoon(1);
				constexpr DurationMS sleepReadWait[] =
				{
					DurationMS(5),
					DurationMS(1),
					DurationMS(0),
				};

				// lock ticketing...
				CounterType myTicket = m_readTicket.AcquireTicket();

				// total waiting thread count
				CounterType nWaitingCount = m_readTicket.GetMyWaitingOrder(myTicket);
				while (nWaitingCount > (BufferSize >> 1))
				{
					if ((nWaitingCount - MAX_COUNTER) > 10)
					{
						ThisThread::SleepFor(sleepOrderWaitFar);
					}
					else
					{
						ThisThread::SleepFor(sleepOrderWaitSoon);
					}

					if(!waitBlockAction())
						return nullptr;

					// Update Waiting Order value
					nWaitingCount = m_readTicket.GetMyWaitingOrder(myTicket);
				}

				int nReadPos = (myTicket - 1) % BufferSize;
				int nLockTry = 0;
				auto expected = ITEM_STATE::STATE_WRITE_UNLOCK;
				while (!m_SpinBuffer[nReadPos].BlockMode.compare_exchange_weak(expected, ITEM_STATE::STATE_READ_LOCK, std::memory_order_release, std::memory_order_relaxed))
				{
					nLockTry++;
					if (nLockTry % 3)
					{
						auto sleepTimeIndex = (int)std::max(SignedCounterType(m_writeTicket.GetWorkingCompleteCount() + 1 - myTicket), SignedCounterType(0));
						sleepTimeIndex = std::min(sleepTimeIndex, (int)countof(sleepReadWait) - 1);
						ThisThread::SleepFor(sleepReadWait[sleepTimeIndex]);
					}

					if (!waitBlockAction())
						return nullptr;

					expected = ITEM_STATE::STATE_WRITE_UNLOCK;
				}

				return &m_SpinBuffer[nReadPos];
			}

			void Read_Unlock(BLOCK* pItem);

			// writing complet and get ready for reading
			CounterType GetReadableCount();

			CounterType GetReadPosition() { return m_readTicket.GetWorkingCompleteCount(); }
			CounterType GetWritePosition() { return m_writeTicket.GetWorkingCompleteCount(); }
		};



}; // namespace SF

#include "SFSpinBufferMT.inl"

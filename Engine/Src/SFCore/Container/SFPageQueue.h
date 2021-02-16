////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Paged queue
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFAssert.h"
#include "Multithread/SFSynchronization.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"



namespace SF
{
	
		
	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Page Queue Class (n-by-one)
	//

	template <class DataType> 
	class PageQueue
	{
	private:

		enum { MaximumRetryInARow = 10 };

		struct Page;

		// Page Header
		struct PageHeader
		{
			Page* pNext;
			CounterType PageID;		// starting from 0

			Atomic<uint32_t>	WriteCounter;
			Atomic<uint32_t> ReadCounter;

			PageHeader() :pNext(nullptr), PageID(0), WriteCounter(0), ReadCounter(0) { }
			~PageHeader() { }
		};

		// Page
		struct Page
		{
			// Page header
			PageHeader Header;

			// Data Array start
			DataType Element[1];

			Page( CounterType InItemCount )
			{
				for( CounterType iEle = 1; iEle < InItemCount; iEle++ )
				{
					new ((void*)&Element[iEle]) DataType;
				}

				auto defaultValue = DataType{};
				for( CounterType iEle = 0; iEle < InItemCount; iEle++ )
				{
					Element[iEle] = defaultValue;
				}
			}

			void DeleteElements(CounterType ItemCpacity)
			{
				for (CounterType iEle = 1; iEle < ItemCpacity; iEle++)
				{
					Element[iEle].DataType::~DataType();
				}
			}
		};

		size_t GetPageMemorySize() { return sizeof(Page)+m_NumberOfItemsPerPage*sizeof(DataType); }


	private:

		IHeap& m_MemeoryManager;

		// page header pointer
		Atomic<Page*>       m_EnqueuePage;
		Atomic<Page*>       m_EnqueueNextPage;
		Atomic<CounterType> m_EnqueuePageID;
		Atomic<Page*>       m_DequeuePage;
		Atomic<CounterType> m_DequeuePageID;

		CriticalSection m_DequeuePageRemoveLock;
		// item_count per page
		CounterType m_NumberOfItemsPerPage;	

		// ticket to the entering write section
		Atomic<uint32_t> m_EnqueueTicket;
		Atomic<uint32_t>	m_DequeueTicket;

		// Page allocation index
		CounterType m_PageIndex;


	private:

		void EnqueuePageMove(Page* pMyEnqueuePage, CounterType myPageID);

	public:
		// constructor / destructor
		PageQueue(IHeap& memoryManager, int iDataPerPage = -1 );
		~PageQueue(void);

		IHeap& GetHeap() { return m_MemeoryManager; }

		// item enqueue
		inline Result Enqueue( const DataType& item);
		inline Result Enqueue(DataType&& item);

		// item deque
		inline Result Dequeue( DataType& item );

		// item deque with MT
		inline Result DequeueMT( DataType& item, DurationMS uiCheckInterval = DurationMS(100) );


		// Just get first dequeue item if exist, not dequeue
		// This will not safe if use DequeueMT
		inline Result GetFront( DataType& item );

		// Item count in queue
		inline CounterType GetEnqueCount() const;

		// Clear queue and remove all enqueued items
		// This operation is not thread safe
		void ClearQueue();

	private:
		// private function
		inline Page* AllocatePage();
		inline void FreePage(Page* pPage);

		inline Result DequeuePageMove();
		inline Result DequeuePageMoveMT();
	};

} // namespace SF


#include "SFPageQueue.inl"

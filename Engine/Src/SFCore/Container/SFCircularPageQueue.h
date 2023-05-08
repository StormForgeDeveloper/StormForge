////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular Paged queue
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"

#include "MemoryManager/SFMemoryPool.h"
#include "Multithread/SFSynchronization.h"
#include "Multithread/SFSystemSynchronization.h"
#include "Container/SFStackPool.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"


//#define CIRCULARPAGEQUEUE_TRACE_PAGE


namespace SF {
	



	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Circular Page Queue storage accessor Class
	//	 - Those are for wrapping element access
	//


	// Accessor for regular storage element
	template <class DataType, class DataStorageType>
	class CircularPageQueueStorageAccessor
	{
	public:
		static DataType Read(DataStorageType& src) { return src; }
		static void CopyRValue(DataType& dest, DataStorageType& src) { dest = std::forward<DataStorageType>(src); }

		static void Write(DataStorageType& dest, const DataType& data) { dest = data; }
		static void Write(DataStorageType& dest, DataType&& data) 
		{
			dest = std::forward<DataType>(data); 
			data = DataType{};
		}
	};


	// Accessor for atomic storage element
	template <class DataType>
	class CircularPageQueueStorageAccessorAtomic
	{
	public:

		typedef std::atomic<DataType> DataStorageType;

	public:
		static DataType Read(DataStorageType& src) { return src.load(std::memory_order_acquire); }
		static void CopyRValue(DataType& dest, DataStorageType& src) { dest = src.exchange(DataType{}, std::memory_order_acq_rel); }

		static void Write(DataStorageType& dest, const DataType& data) { DataType temp = data; dest.store(temp, std::memory_order_release); }
		static void Write(DataStorageType& dest, DataType&& data) { dest.store(data, std::memory_order_release); }
	};

		
	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Circular Page Queue Class
	//

	template <class DataType, class DataStorageType = DataType, class StorageAccessor = CircularPageQueueStorageAccessor<DataType, DataStorageType>>
	class CircularPageQueue
	{
	private:

		static constexpr int MaximumRetryInARow = 10;


		struct Page;


#pragma pack(push,4)
		// Page Header
		struct PageHeader
		{
			uint32_t PageID = 0;		// starting from 0
			uint32_t Dummy;		// Dummy

			std::atomic<uint32_t>	WriteCounter;
			std::atomic<uint32_t>	ReadCounter;

			PageHeader()
			{
				WriteCounter = 0;
				ReadCounter = 0;
			}

			~PageHeader() { }

			void Init()
			{
				PageID = 0;
				WriteCounter.store(0, std::memory_order_relaxed);
				ReadCounter.store(0,std::memory_order_relaxed);
			}
		};
#pragma pack(pop)

		// Page
		struct Page : public StackPool::Item
		{
			// Page header
			PageHeader Header;

			// Pading for 128bit alignment
			uint64_t Dummy;

			// volatile is better than atomic_fence
			// Data Array start
			DataStorageType Element[1];

			Page( CounterType InItemCount )
			{
				for( CounterType iEle = 1; iEle < InItemCount; iEle++ )
				{
					new (&Element[iEle]) DataType;
					StorageAccessor::Write(Element[iEle], {});
				}
			}

			void DeleteElements(CounterType ItemCpacity)
			{
				for (CounterType iEle = 1; iEle < ItemCpacity; iEle++)
				{
					StorageAccessor::Write(Element[iEle], {});
				}
			}
		};

		size_t GetPageMemorySize() { return sizeof(Page)+m_NumberOfItemsPerPage*sizeof(DataType); }


	private:

		// Circular queue size for pages
		int m_TotalPageCount;

		// Circular queue for pages
		std::atomic<Page*>* m_CircularPages = nullptr;

#if defined(CIRCULARPAGEQUEUE_TRACE_PAGE)
		// Page swap counter
		struct PageDebug
		{
			std::atomic<int> ClearCounter;
			std::atomic<int> SetupCounter;
		};
		PageDebug* m_PageDebug = nullptr;
#endif
		// item_count per page
		CounterType m_NumberOfItemsPerPage = 0;	

		// ticket to the entering write section
		SyncCounter m_PageIDBase;
		// number of items have been enqueued
		SyncCounter m_EnqueueTicket;
		// number of items have been dequeued or tried to
		SyncCounter	m_DequeueTicket;

		//TicketLock m_CircularBufferLock;
		CriticalSection m_CircularBufferLock;

		// heap
		IHeap& m_Heap;

		// page pool
		StackPool m_PagePool;

	private:

		// private function
		inline Page* AllocatePage();
		inline void FreePage(Page* pPage, bool cleanUp);

	public:
		// constructor / destructor
		// iDataPerPage: Data count per page
		// initialCircularPageCount: Initial circular page count, iDataPerPage * initialCircularPageCount is the maximum item count for the queue
		CircularPageQueue(IHeap& heap, int iDataPerPage = -1, int initialCircularPageCount = 64 );
		~CircularPageQueue(void);

		// Dispose, clear all memory, after calling dispose you can't use queue anymore
		void Dispose();

		IHeap& GetHeap() { return m_Heap; }

		// item enqueue, Thread safe
		inline Result Enqueue( const DataType& item);
		inline Result Enqueue(DataType&& item);

		// item deque, Non Thread safe
		// This is non-blocking function, it will return fail if there is not item available
		inline Result Dequeue(DataType& item, std::function<bool()> abortCheck = [] { return false; });

		// Just get first dequeue item if exist, not dequeue
		// This will not safe if use DequeueMT
		inline Result GetFront( DataType& item );


		// Item count in queue
		size_t size() const;

		// Clear queue and remove all enqueued items
		// This operation is not thread safe
        [[deprecated]]void ClearQueue() { Reset(); }
        void Reset();

	};




	// Circular queue with atomic load/save. When you need to define atomic element for circular page queue, you should use this class
	// For example, if you want to use atomic queue such as CircularPageQueue<Command*, atomic<Command*>>, you should go for CircularPageQueueAtomic<Command*>
	// The important thing is when you use container class pointer with atomic member inside, you can not gurantee that the atomic inside class has writed before it accessed by another thread.
	// CircularPageQueueAtomic will gurantee that for you
	template <class DataType>
	class CircularPageQueueAtomic : public CircularPageQueue<DataType, std::atomic<DataType>, CircularPageQueueStorageAccessorAtomic<DataType>>
	{
	public:
		CircularPageQueueAtomic(IHeap& memoryManager, int iDataPerPage = -1, int initialCircularQueueSize = 64)
			: CircularPageQueue<DataType,std::atomic<DataType>, CircularPageQueueStorageAccessorAtomic<DataType>>(memoryManager, iDataPerPage, initialCircularQueueSize)
		{}


	};



} // namespace SF



#include "SFCircularPageQueue.inl"

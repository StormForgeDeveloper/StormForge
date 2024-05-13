////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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

		static constexpr bool IsTirviallyConstructable = std::is_trivially_constructible_v<DataType>;
		static constexpr bool IsMoveConstructable = std::is_move_constructible_v<DataType>;
		static constexpr bool IsMoveAssignalbe = std::is_move_constructible_v<DataType>;

		static constexpr bool CanUseAtomic =
			std::is_trivially_constructible_v<DataType>
			&& std::is_copy_constructible_v<DataType>
			&& std::is_move_constructible_v<DataType>
			&& std::is_copy_assignable_v<DataType>
			&& std::is_move_assignable_v<DataType>;


		struct Page;


		// Page Header
		struct PageHeader
		{
			Page* pNext;
			uint32_t PageID;		// starting from 0

			Atomic<uint32_t> WriteCounter;
			Atomic<uint32_t> ReadCounter;

			PageHeader() : pNext(nullptr), PageID(0), WriteCounter(0), ReadCounter(0) { }
			~PageHeader() { }
		};


		// Page
		struct Page
		{
			// Page header
			PageHeader Header;

			Atomic<uint32_t>* ValueState{};

			// Data Array start
			DataType* Element{};

			inline Page(size_t InItemCount);

			SF_FORCEINLINE void SetWritten(uint iElement)
			{
				auto iDword = iElement >> 5;
				auto iValue = iElement & ((uint(1) << 5) - 1);

				ValueState[iDword].fetch_or(uint(1) << iValue, MemoryOrder::release);
			}

			SF_FORCEINLINE bool HasValue(uint iElement)
			{
				auto iDword = iElement >> 5;
				auto iValue = iElement & ((uint(1) << 5) - 1);

				return (ValueState[iDword].load(MemoryOrder::acquire) & (uint(1) << iValue)) != 0;
			}

			void DeleteElements(uint32_t ItemCpacity)
			{
				if constexpr (CanUseAtomic)
				{
					auto pElement = (Atomic<DataType>*)Element;
					for (uint32_t iEle = 1; iEle < ItemCpacity; iEle++)
					{
						pElement[iEle].~Atomic<DataType>();
					}
				}
				else
				{
					for (uint32_t iEle = 1; iEle < ItemCpacity; iEle++)
					{
						Element[iEle].DataType::~DataType();
					}
				}
			}
		};


		static constexpr size_t PageStructSize = AlignUp(sizeof(Page), SF_ALIGN_DOUBLE);


		SF_FORCEINLINE static size_t GetValueStateSize(size_t InItemCount)
		{
			auto aligned32Count = AlignUp(InItemCount, SF_ALIGN_DOUBLE * 8);
			return aligned32Count >> 3;
		}
		SF_FORCEINLINE size_t GetPageMemorySize() { return PageStructSize + GetValueStateSize(m_NumberOfItemsPerPage) + m_NumberOfItemsPerPage * sizeof(DataType); }


	private:

		IHeap& m_Heap;

		// page header pointer
		Atomic<Page*> m_EnqueuePage;
		Atomic<Page*> m_EnqueueNextPage;
		Atomic<uint32_t> m_EnqueuePageID;
		Atomic<Page*> m_DequeuePage;
		Atomic<uint32_t> m_DequeuePageID;

		CriticalSection m_DequeuePageRemoveLock;
		// item_count per page
		uint32_t m_NumberOfItemsPerPage;	

		// ticket to the entering write section
		Atomic<uint32_t> m_EnqueueTicket;
		Atomic<uint32_t> m_DequeueTicket;

		// Page allocation index
		uint32_t m_PageIndex;


	private:

		void EnqueuePageMove(Page* pMyEnqueuePage, uint32_t myPageID);

	public:
		// constructor / destructor
		PageQueue(IHeap& heap, int iDataPerPage = -1 );
		~PageQueue(void);

		SF_FORCEINLINE IHeap& GetHeap() { return m_Heap; }

		// item enqueue
		inline Result Enqueue(const DataType& item);
		inline Result Enqueue(DataType&& item);

		// item deque
		inline Result Dequeue( DataType& item );

		// item deque with MT
		inline Result DequeueMT( DataType& item, DurationMS uiCheckInterval = DurationMS(100) );


		// Just get first dequeue item if exist, not dequeue
		// This will not safe if use DequeueMT
		inline Result GetFront( DataType& item );

		// Item count in queue
		SF_FORCEINLINE uint32_t GetEnqueCount() const { return size(); }
		SF_FORCEINLINE uint32_t size() const
		{
			return m_EnqueueTicket.load(std::memory_order_relaxed) - m_DequeueTicket.load(std::memory_order_relaxed);
		}

		// Clear queue and remove all enqueued items
		// This operation is not thread safe
		void ClearQueue();

	private:
		// private function
		inline Page* AllocatePage();
		inline void FreePage(Page* pPage);

		inline Result DequeuePageMove();
		inline Result DequeuePageMoveMT(uint32_t expectedPageId);
	};

} // namespace SF


#include "SFPageQueue.inl"

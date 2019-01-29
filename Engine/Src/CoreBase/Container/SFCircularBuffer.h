////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular Buffer for multithread
//
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Thread/SFSynchronization.h"
#include "Thread/SFSystemSynchronization.h"

namespace SF
{

	////////////////////////////////////////////////////////////////////////////////
	//
	// Circular Buffer 
	//	- Queue style buffer allocator
	// 

	template <size_t SIZE_BUFFER = 2048>
	class CircularBuffer
	{
	public:

		enum class ItemState : uint32_t
		{
			Free,
			Reserved,
			Filled,
			Reading,
			Dummy,		// marked as dummy space
		};

#pragma pack(push, 4)
		union BufferItem
		{
			struct
			{
				ItemState	State;		// Item state
				uint32_t	NextPos;	// Next item position, offset from m_Buffer
			};
			uint64_t Composited;

			void* GetDataPtr() { return this + 1; }
		};
#pragma pack(pop)

	private:
		// Buffer
		uint64_t m_Buffer[(SIZE_BUFFER + 7) / 8];

		// HeadPos ticketing
		//Ticketing m_HeadTicketRegister;
		CriticalSection m_HeadTicketRegister;

		// Read position
		std::atomic<std::atomic<uint64_t>*> m_TailPos;

		// Write position
		std::atomic<std::atomic<uint64_t>*> m_HeadPos;

		// Items in queue
		std::atomic<uint> m_nItemCount;


	public:

		// Constructor/Destructor
		CircularBuffer();
		~CircularBuffer();

		// Empty check
		bool IsEmpty();

		// Clear all items
		void Clear();

		// Reserve buffer. The pointer it returns is reserved for writing, after done writing, Call SetReadyForRead to mark the buffer is ready for read
		void* Reserve(size_t bufferSize);

		// mark the buffer for read
		Result SetReadyForRead(void* pBuffer);

		// Take a buffer for read
		BufferItem* TakeBufferForRead();

		// FreeReadBuffer
		Result FreeReadBuffer(BufferItem* pBufferItem);

		// get buffer size
		size_t GetBufferSize(BufferItem* pBufferItem);

		// Iterate readable items. the item passed to the functor will be freed
		template<class FunctorT>
		void ForeachReadableItems(FunctorT func)
		{
			BufferItem* pBufferItem = nullptr;

			while (true)
			{
				pBufferItem = TakeBufferForRead();
				if (pBufferItem == nullptr)
					return; // nothing left for now

				func(pBufferItem->GetDataPtr());

				FreeReadBuffer(pBufferItem);
			}
		}
	};


}

#include "SFCircularBuffer.inl"

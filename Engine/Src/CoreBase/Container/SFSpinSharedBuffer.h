////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Spin shared buffer for multithired thread 
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Thread/SFSynchronization.h"


namespace SF {


		//////////////////////////////////////////////////////////////////////////////////
		//
		//	Spin Shared Buffer Class
		//

		template <class ItemType>
		class SpinSharedBuffer
		{
			struct Buffer
			{
				// Buffer State 
				typedef enum
				{
					STATE_FREE,	// Free Buffer State
					STATE_USE,	// Read Buffer State
				} BufferState;


				// Buffer State
				std::atomic<BufferState> State;
				//union {
				//	volatile int32_t State; 
				//	BufferState eState; // for easy to see state
				//};

				// Data storage
				ItemType Data;


				// constructor
				Buffer()
				{
					// initializing Buffer state as Free
					State = STATE_FREE;
				}
			};

		private:
			// Number of buffer to maintain
			uint m_BufferCount;

			// Spin shared Buffer
			Buffer *m_SpinBuffer;

			// Spin Index
			SyncCounter m_AccessPosition;

			// Used buffer count
			SyncCounter m_UsedBufferCount;

			IHeap& m_Heap;

		public:
			// Constructor / Destructor
			SpinSharedBuffer(IHeap& memoryManager, uint BufferCount);
			~SpinSharedBuffer();

			IHeap& GetHeap() { return m_Heap; }

			// Set buffer count, all pervious buffer data will be lost
			Result SetBufferCount(uint BufferCount);

			// Get buffer count
			uint GetBufferCount();

			// Get used buffer count
			CounterType GetUsedBufferCount();

			// Try to get one buffer while given times
			Result TryAllocBuffer(INT iTryCount, ItemType* &pBuffer);

			// Get free buffer
			Result AllocBuffer(ItemType* &pBuffer);

			// Free given buffer
			Result FreeBuffer(ItemType* pBuffer);
		};




} // namespace SF

#include "SFSpinSharedBuffer.inl"



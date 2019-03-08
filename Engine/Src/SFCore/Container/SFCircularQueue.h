////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular queue for multithread
//
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "SFTypedefs.h"
#include "SFAssert.h"


namespace SF {

		////////////////////////////////////////////////////////////////////////////////
		// Circular Buffer 

		template <typename T, int SIZE_BUFFER = 3>
		class CircularQueue
		{
		private:
			// Buffer
			T m_Buffer[SIZE_BUFFER];

			// Read position
			INT m_nReadPtr;

			// Write position
			INT m_nWritePtr;

			// Items in queue
			uint m_nItemCount;

		public:

			// Constructor/Destructor
			CircularQueue();
			~CircularQueue();

			// Full/Empty check
			inline bool IsFull();
			inline bool IsEmpty();

			// Enqueue an element
			inline Result Enqueue(T&& item);

			// Dequeue an element
			inline Result Dequeue(T& item);

			// Get item count
			inline uint	GetSize();

			// Clear all items
			inline void ClearQueue();

			// foreach items in queue
			void ReverseForeach(uint from, uint Count, std::function<bool(const T& item)> func) const;
			void ReverseForeach(uint from, uint Count, std::function<bool(const T& item)> func);
		};


}

#include "SFCircularQueue.inl"

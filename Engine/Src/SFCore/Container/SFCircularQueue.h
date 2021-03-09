////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
		//  - Single thread input, single thread output.
		//  - Input and output thread can be different

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
			inline Result Enqueue(const T& item);

			// Dequeue an element
			Result Dequeue(T& item);

			// Get item count
			uint GetSize() const { return m_nItemCount; }
			size_t size() const { return m_nItemCount; }

			// Clear all items
			void ClearQueue();

			// index based access
			// index: 0 is front
			const T& operator[](int iIndex);

			// foreach items in queue
			void ReverseForeach(uint from, uint Count, std::function<bool(const T& item)> func) const;
			void ReverseForeach(uint from, uint Count, std::function<bool(const T& item)> func);
		};


}

#include "SFCircularQueue.inl"

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Async IO
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Container/SFCircularPageQueue.h"


namespace SF {
	namespace AsyncIO {



		////////////////////////////////////////////////////////////////////////////////
		//
		// WriteBufferQueue  interface
		//

		struct IOBUFFER;
		struct IOBUFFER_WRITE;

		// Write buffer queue
		class WriteBufferQueue : public CircularPageQueueAtomic<IOBUFFER_WRITE*>
		{
		public:
			typedef CircularPageQueueAtomic<IOBUFFER_WRITE*> super;

		public:
			WriteBufferQueue(IHeap& heap, uint uiNumElePerPage = 512);
			virtual ~WriteBufferQueue();

			// Clear queue element
			void Reset();
		};





	} // AsyncIO
} // namespace SF



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


#include "SFCorePCH.h"
#include "MemoryManager/SFMemoryManager.h"
#include "IO/AsyncIO/AsyncIOPortWriteBufferQueue.h"
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPort_EPOLL.h"
#include "IO/AsyncIO/AsyncIOPort_KQUEUE.h"
#include "IO/AsyncIO/AsyncIOPort_IOCP.h"

#include "ResultCode/SFResultCodeLibrary.h"
#include "MemoryManager/SFMemoryPool.h"

#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"



namespace SF {
	namespace AsyncIO {


		WriteBufferQueue::WriteBufferQueue(IHeap& heap, uint uiNumElePerPage)
			: CircularPageQueueAtomic<IOBUFFER_WRITE*>(heap, uiNumElePerPage)
		{
		}

		WriteBufferQueue::~WriteBufferQueue()
		{
			ClearQueue();
		}

		// Clear queue element
		void WriteBufferQueue::ClearQueue()
		{
			IOBUFFER_WRITE* data = nullptr;

			while (Dequeue(data))
			{
				Util::SafeDelete(data);
			}

			super::ClearQueue();
		}


	} // namespace AsyncIO
} // namespace SF


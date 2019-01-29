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


#include "CoreBasePCH.h"
#include "Memory/SFMemoryManager.h"
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOAdapter.h"
#include "IO/AsyncIO/AsyncIOPort_EPOLL.h"
#include "IO/AsyncIO/AsyncIOPort_KQUEUE.h"
#include "IO/AsyncIO/AsyncIOPort_IOCP.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Thread/SFThread.h"
#include "Util/SFUtility.h"
#include "Container/SFSpinSharedBuffer.h"
#include "Memory/SFMemoryPool.h"



namespace SF {
namespace AsyncIO {



	////////////////////////////////////////////////////////////////////////////////
	//
	// NetIO interface
	//

	AsyncIOAdapter::AsyncIOAdapter(IHeap& heap, const NativeHandle &IOHandleVariable)
		: m_Heap(heap)
		, m_IOStatus(IOStatus::None)
		, m_IOHandle(IOHandleVariable)
		, m_PendingReadCount(0)
		, m_PendingWriteCount(0)
	{
	}

	AsyncIOAdapter::~AsyncIOAdapter()
	{
		AssertRel(m_IOStatus == IOStatus::None);
		Assert(m_PendingWriteCount == 0 && m_PendingReadCount == 0);
	}

	void AsyncIOAdapter::SetAssignedIOWorker(int assignedIOWorker)
	{
		m_AssignedIOWorker = assignedIOWorker;
	}

	void AsyncIOAdapter::OnIORegistered()
	{
		IOStatus expected = IOStatus::None;
		int iTry = 1;
		while (!m_IOStatus.compare_exchange_weak(expected, IOStatus::Registered, std::memory_order_acquire))
		{
			if ((iTry % 4) == 0)
				std::this_thread::sleep_for(DurationMS(0));

			if (expected == IOStatus::Registered)
			{
				assert(false);
				break;
			}
			iTry++;
		}

	}

	void AsyncIOAdapter::OnIOUnregistered()
	{
		IOStatus expected = IOStatus::Registered;
		int iTry = 1;
		while (!m_IOStatus.compare_exchange_weak(expected, IOStatus::None, std::memory_order_acquire))
		{
			if ((iTry % 4) == 0)
				std::this_thread::sleep_for(DurationMS(0));

			if (expected == IOStatus::None)
			{
				break;
			}
			iTry++;
		}
	}

	Result AsyncIOAdapter::OnWriteReady()
	{
		Result hr = ResultCode::SUCCESS;
		IOBUFFER_WRITE* pWriteBuffer = nullptr;

		auto writeQueue = m_pWriteQueues;
		if(writeQueue == nullptr) return ResultCode::INVALID_POINTER;

		while (1)
		{
			if (m_pLatestWriteBuffer != nullptr)
			{
				pWriteBuffer = m_pLatestWriteBuffer;
				m_pLatestWriteBuffer = nullptr;
			}
			else
			{
				hr = writeQueue->Dequeue(pWriteBuffer);
				if (!(hr))
				{
					hr = ResultCode::SUCCESS;
					break;
				}
			}

			hr = WriteBuffer(pWriteBuffer);
			switch ((uint32_t)hr)
			{
			case (uint32_t)ResultCode::SUCCESS:
				break;
			case (uint32_t)ResultCode::IO_IO_PENDING:
				m_pLatestWriteBuffer = pWriteBuffer;
				break;
			case (uint32_t)ResultCode::IO_WOULDBLOCK:  // WOULDBLOCK in Linux can be try again
			case (uint32_t)ResultCode::IO_TRY_AGAIN:
			default:
				m_pLatestWriteBuffer = pWriteBuffer;
				goto Proc_End;
				break;
			}
		}

	Proc_End:

		return hr;
	}

	Result AsyncIOAdapter::EnqueueWriteBuffer(IOBUFFER_WRITE *pWriteBuffer)
	{
		assert((((uint)pWriteBuffer->Operation)&OP_WRITE_BIT) != 0);
		auto writeQueue = m_pWriteQueues;
		if (writeQueue == nullptr)
			return ResultCode::INVALID_POINTER;

		return writeQueue->Enqueue(pWriteBuffer);
	}

	Result AsyncIOAdapter::OnReadReady()
	{
		IOBUFFER_READ* pReadBuffer = nullptr;
		Result result;

		while (1)
		{
			if(pReadBuffer == nullptr)
				pReadBuffer = CreateReadBuffer();

			if (pReadBuffer == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			result = ReadBuffer(pReadBuffer);
			switch ((uint32_t)result)
			{
			case (uint32_t)ResultCode::IO_TRY_AGAIN:
			case (uint32_t)ResultCode::IO_WOULDBLOCK:
			case (uint32_t)ResultCode::SUCCESS_FALSE:
				// These are expected return code
				result = ResultCode::SUCCESS;
				break;
			case (uint32_t)ResultCode::IO_IO_PENDING:
				Assert(false);
				break;
			default:
				if (!result)
				{
					//SFLog(System, "", );
				}
				// fallthru
			case (uint32_t)ResultCode::SUCCESS:
				// toss data to working thread
				if (pReadBuffer != nullptr)
				{
					OnIOReadCompleted(result, pReadBuffer);
				}
				break;
			}
		}

		if (pReadBuffer != nullptr)
			IHeap::Delete(pReadBuffer);

		return result;
	}



} // namespace AsyncIO
} // namespace SF


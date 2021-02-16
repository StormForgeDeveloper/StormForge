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
#include "MemoryManager/SFMemoryPool.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"

#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPort_Reactor.h"
#include "IO/AsyncIO/AsyncIOAdapter.h"





namespace SF {
namespace AsyncIO {




	////////////////////////////////////////////////////////////////////////////////
	//
	//	AsyncIOPortSystem_Impl
	//

	AsyncIOPortSystem_Impl::AsyncIOPortSystem_Impl(IHeap& heap)
		: m_Heap(heap)
		, m_iWorkerAssignIndex(0)
		, m_Workers(heap)
	{
	}


	AsyncIOPortSystem_Impl::~AsyncIOPortSystem_Impl()
	{
	}

	IOWorker* AsyncIOPortSystem_Impl::GetNextWorkerAssignment()
	{
		if (m_Workers.size() == 0)
			return nullptr;

		auto workerIndex = m_iWorkerAssignIndex.fetch_add(1, std::memory_order_relaxed);
		return m_Workers[workerIndex % m_Workers.size()];
	}

	IOWorker* AsyncIOPortSystem_Impl::GetWorker(int id)
	{
		if (id >= 0 && id < (int)m_Workers.size())
			return m_Workers[id];
		else
			return nullptr;
	}

	void AsyncIOPortSystem_Impl::AddIOWorker(IOWorker* pIOWorker)
	{
		m_Workers.push_back(pIOWorker);
	}

	Result AsyncIOPortSystem_Impl::Initialize(uint netThreadCount)
	{
		m_iWorkerAssignIndex = 0;

		return ResultCode::SUCCESS;
	}

	void AsyncIOPortSystem_Impl::Terminate()
	{
		for (auto itWorker : m_Workers)
		{
			itWorker->SetKillEvent();
		}

		CloseSystemHandle();

		for (auto& itWorker : m_Workers)
		{
			itWorker->Stop();
			IHeap::Delete(itWorker);
		}
		m_Workers.Clear();

	}


	// Register the socket to EPOLL
	Result AsyncIOPortSystem_Impl::RegisterIO(AsyncIOAdapter* cbInstance)
	{
		auto pWorker = GetNextWorkerAssignment();
		if (pWorker == nullptr)
			return ResultCode::NOT_INITIALIZED;

		cbInstance->SetAssignedIOWorker(pWorker->GetID());
		pWorker->RegisterIO(cbInstance);

		return ResultCode::SUCCESS;
	}

	Result AsyncIOPortSystem_Impl::UnregisterIO(AsyncIOAdapter* cbInstance)
	{
		auto assignIndex = cbInstance->GetAssignedIOWorker();
		auto pWorker = GetWorker(assignIndex);
		if (pWorker != nullptr)
		{
			pWorker->UnregisterIO(cbInstance);
			cbInstance->SetAssignedIOWorker(-1);
		}


		return ResultCode::SUCCESS;
	}


} // namespace AsyncIO
} // namespace SF



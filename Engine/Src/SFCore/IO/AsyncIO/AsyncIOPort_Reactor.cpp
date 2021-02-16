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
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Multithread/SFSystemSynchronization.h"
#include "MemoryManager/SFMemoryPool.h"
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPort_Reactor.h"
#include "IO/AsyncIO/AsyncIOAdapter.h"
#include "IO/AsyncIO/AsyncIOPortSystemImpl.h"
#include "IO/AsyncIO/AsyncIOPort_EPOLL.h"
#include "IO/AsyncIO/AsyncIOPort_KQUEUE.h"

#include "Util/SFLog.h"


// IOS doesn't support 
#if SF_PLATFORM == SF_PLATFORM_IOS
#define MSG_NOSIGNAL 0
#endif



namespace SF {
namespace AsyncIO {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//


	//// Clear Buffer
	//void IOBUFFER::ClearBuffer()
	//{
	//}




	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//


	IOWorker::IOWorker(AsyncIOPortSystem_Impl* ownerSystem, int id)
		: m_Owner(ownerSystem)
		, m_ID(id)
	{

	}

	IOWorker::~IOWorker()
	{
	}


	Result IOWorker::RegisterIO(AsyncIOAdapter* cbInstance)
	{
		return ResultCode::SUCCESS;
	}

	Result IOWorker::UnregisterIO(AsyncIOAdapter* cbInstance)
	{
		return ResultCode::SUCCESS;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	socket network system
	//


	AsyncIOSystem_Reactor::AsyncIOSystem_Reactor(IHeap& heap)
		: AsyncIOPortSystem_Impl(heap)
	{
	}

	Result AsyncIOSystem_Reactor::RegisterIO(AsyncIOAdapter* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;
		//int iOptValue;

		if (cbInstance == nullptr)
			return ResultCode::INVALID_ARG;

		Assert(cbInstance->GetIOHandle() != INVALID_NATIVE_HANDLE_VALUE);

		cbInstance->OnIORegistered();


		if (!hr)
		{
			cbInstance->OnIOUnregistered();
		}

		return hr;
	}


	Result AsyncIOSystem_Reactor::Initialize(uint netThreadCount)
	{
		Result result = AsyncIOPortSystem_Impl::Initialize(netThreadCount);
		if (!result)
			return result;



		return ResultCode::SUCCESS;
	}

	void AsyncIOSystem_Reactor::Terminate()
	{

		AsyncIOPortSystem_Impl::Terminate();
	}


	Result AsyncIOSystem_Reactor::UnregisterIO(AsyncIOAdapter* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;

		if (cbInstance == nullptr)
			return ResultCode::INVALID_ARG;

		cbInstance->OnIOUnregistered();

		return hr;
	}








} // namespace Net
} // namespace SF



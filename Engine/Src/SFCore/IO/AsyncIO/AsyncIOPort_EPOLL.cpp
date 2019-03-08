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
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPort_Reactor.h"
#include "IO/AsyncIO/AsyncIOPort_EPOLL.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Thread/SFSystemSynchronization.h"
#include "Memory/SFMemoryPool.h"


#if USE_REACTOR_PATTERN && EPOLL

#include <sys/epoll.h>




namespace SF {
namespace AsyncIO {


#if SF_PLATFORM == SF_PLATFORM_ANDROID
#define EVENT_MASK (EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLET | EPOLLHUP)
#define ERROR_EVENT_MASK (EPOLLERR)
#else
#define EVENT_MASK (EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLET | EPOLLHUP | EPOLLRDHUP)
#define ERROR_EVENT_MASK (EPOLLERR)
#endif

	////////////////////////////////////////////////////////////////////////////////
	//
	//	EPOLL thread worker
	//

	IOWorkerEPOLL::IOWorkerEPOLL(AsyncIOPortSystem_Impl* ownerSystem, int id, int hEpoll)
		: IOWorker(ownerSystem, id)
		, m_hEpoll(hEpoll)
	{
		if (m_hEpoll == 0)
		{
			m_hEpoll = epoll_create(1);
		}
	}

	IOWorkerEPOLL::~IOWorkerEPOLL()
	{

	}

	Result IOWorkerEPOLL::RegisterIO(AsyncIOAdapter* cbInstance)
	{
		epoll_event epollEvent;

		memset(&epollEvent, 0, sizeof(epollEvent));
		epollEvent.events = EVENT_MASK;
		epollEvent.data.ptr = cbInstance;
		if (epoll_ctl(m_hEpoll, EPOLL_CTL_ADD, (int)(intptr_t)cbInstance->GetIOHandle(), &epollEvent) == -1) {
			SFLog(Net, Error, "epoll_ctl: RegisterSocket sock:{0}", cbInstance->GetIOHandle());
			return ResultCode::FAIL;
		}

		SFLog(Net, Info, "epoll register sock:{0}", (int)(intptr_t)cbInstance->GetIOHandle());

		return ResultCode::SUCCESS;
	}

	Result IOWorkerEPOLL::UnregisterIO(AsyncIOAdapter* cbInstance)
	{
		epoll_event epollEvent;

		memset(&epollEvent, 0, sizeof(epollEvent));
		epollEvent.events = EVENT_MASK;
		epollEvent.data.ptr = cbInstance;
		if (epoll_ctl(m_hEpoll, EPOLL_CTL_DEL, (int)(intptr_t)cbInstance->GetIOHandle(), &epollEvent) == -1) {
			SFLog(Net, Error, "epoll_ctl: UnregisterSocket sock:{0}", (int)(intptr_t)cbInstance->GetIOHandle());
			return ResultCode::FAIL;
		}

		SFLog(Net, Info, "epoll unregister sock:{0}", (int)(intptr_t)cbInstance->GetIOHandle());

		return ResultCode::SUCCESS;
	}

	Result IOWorkerEPOLL::HandleRW(unsigned int events, AsyncIOAdapter* pCallBack)
	{
		Result hr = ResultCode::SUCCESS;// , hrErr = ResultCode::SUCCESS;

		//  skip when the socket value is different
		if (pCallBack == nullptr)
			return ResultCode::INVALID_POINTER;


		if (events & EPOLLIN)
		{
			pCallBack->OnReadReady();
		}

		if (events & EPOLLOUT)
		{
			// This call will just poke working thread
			hr = pCallBack->OnWriteReady();
		}


		if (!(hr))
		{
			char stringBuffer[512];
			SFLog(System, Info, "ERROR Epoll RW fail nativeHandle:{0}, events:{1} hr:{2}", pCallBack->GetIOHandle(), GetOwner()->EventFlagToString(sizeof(stringBuffer), stringBuffer, events), hr);
		}

		return hr;
	}

	void IOWorkerEPOLL::Run()
	{
		Result hr = ResultCode::SUCCESS;
		int iNumEvents;
		epoll_event events[MAX_EPOLL_EVENTS];

		while (1)
		{
			hr = ResultCode::SUCCESS;

			// Getting status
			iNumEvents = epoll_wait(m_hEpoll, events, countof(events), MAX_EPOLL_WAIT);
			if (iNumEvents < 0)
			{
				hr = GetLastResultCode();
				switch ((uint32_t)hr)
				{
				case (uint32_t)ResultCode::INTERRUPTED_SYSCALL:
					break;
				case (uint32_t)ResultCode::INVALID_FILE_HANDLE:
				case (uint32_t)ResultCode::INVALID_POINTER:
				case (uint32_t)ResultCode::IO_NOTSOCK:
				case (uint32_t)ResultCode::INVALID_ARG:
				default:
					SFLog(System, Info, "ERROR EPOLL wait failed hr={0:X8}", hr);
					break;
				}
			}

			for (int iEvent = 0; iEvent < iNumEvents; iEvent++)
			{
				if (events[iEvent].data.ptr == nullptr)
				{
					SFLog(System, Info, "ERROR EPOLL null handler, skipping...");
					continue;
				}

				auto& curEvent = events[iEvent];
				auto pCallback = (AsyncIOAdapter*)curEvent.data.ptr;

				// skip invalid handlers
				if (pCallback == nullptr || !pCallback->GetIsIORegistered())
					continue;

				if ((curEvent.events&ERROR_EVENT_MASK) != 0)
				{
					char stringBuffer[512];
					SFLog(System, Info, "Closing epoll worker nativeHandle:{0}, event:{1}", pCallback->GetIOHandle(), GetOwner()->EventFlagToString(sizeof(stringBuffer), stringBuffer, curEvent.events));
					GetOwner()->UnregisterIO(pCallback);
					pCallback->OnIOUnregistered();
					continue;
				}

				HandleRW(curEvent.events, pCallback);
			}

			// Check exit event
			if (CheckKillEvent(DurationMS(0)))
				break;

		} // while(1)

	}





	////////////////////////////////////////////////////////////////////////////////
	//
	//	EPOLL network system
	//


	EPOLLSystem::EPOLLSystem(IHeap& memMgr)
		: AsyncIOSystem_Reactor(memMgr)
		, m_iWorkerAssignIndex(0)
		, m_Workers(memMgr)
	{
	}

	Result EPOLLSystem::Initialize(uint netThreadCount)
	{
		Result result = AsyncIOSystem_Reactor::Initialize(netThreadCount);
		if (!result)
			return result;

		int hEPoll = epoll_create(1);


		SetNativeIOSystemHandle((NativeHandle)(intptr_t)hEPoll);

		// client will use only 1 thread
		for (uint iThread = 0; iThread < netThreadCount; iThread++)
		{
			auto pNewWorker = new(GetHeap()) IOWorkerEPOLL(this, iThread, hEPoll);
			pNewWorker->Start();
			AddIOWorker(pNewWorker);
		}

		return ResultCode::SUCCESS;
	}

	void EPOLLSystem::Terminate()
	{
		AsyncIOSystem_Reactor::Terminate();
	}


	const char* EPOLLSystem::EventFlagToString(int32_t bufferSize, char* stringBuffer, uint32_t eventFlags)
	{
		const char* orgStart = stringBuffer;
		stringBuffer[0] = '\0';
		if ((eventFlags&EPOLLIN) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLIN ");
		if ((eventFlags&EPOLLOUT) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLOUT ");
#if defined(EPOLLRDHUP)
		if ((eventFlags&EPOLLRDHUP) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLRDHUP  ");
#endif
		if ((eventFlags&EPOLLPRI) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLPRI ");
		if ((eventFlags&EPOLLERR) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLERR ");
		if ((eventFlags&EPOLLHUP) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLHUP ");
		if ((eventFlags&EPOLLET) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLET ");
#if defined(EPOLLONESHOT)
		if ((eventFlags&EPOLLONESHOT) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLONESHOT ");
#endif
#if defined(EPOLLWAKEUP)
		if ((eventFlags&EPOLLWAKEUP) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLWAKEUP ");
#endif
#ifdef EPOLLEXCLUSIVE
		if ((eventFlags&EPOLLEXCLUSIVE) != 0) StrUtil::StringCopyEx(stringBuffer, bufferSize, "EPOLLEXCLUSIVE ");
#endif

		return orgStart;
	}



} // namespace AsyncIO
} // namespace SF

#else
void Dummp_AsyncIO_EPOLL() {}
#endif


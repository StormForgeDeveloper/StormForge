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


#if USE_REACTOR_PATTERN && KQUEUE

#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPort_KQUEUE.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Thread/SFSystemSynchronization.h"
#include "Memory/SFMemoryPool.h"

#include "Service/SFEngineService.h"

#include <sys/event.h>



namespace SF {
namespace AsyncIO {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	KQUEUE thread worker
	//

	IOWorkerKQUEUE::IOWorkerKQUEUE(AsyncIOPortSystem_Impl* ownerSystem, int id, int hKQUEUE)
		: IOWorker(ownerSystem, id, memMgr)
		, m_hKQUEUE(hKQUEUE)
	{
		if (m_hKQUEUE == 0)
		{
			m_hKQUEUE = kqueue();
		}
	}

	IOWorkerKQUEUE::~IOWorkerKQUEUE()
	{

	}

	Result IOWorkerKQUEUE::RegisterIOHandler(AsyncIOAdapter* cbInstance)
	{
		struct kevent evSet;

		EV_SET(&evSet, cbInstance->GetIOSocket(), EVFILT_READ | EVFILT_WRITE , EV_ADD, 0, 0, cbInstance);
		if (kevent(m_hKQUEUE, &evSet, 1, NULL, 0, NULL) == -1)
		{
			SFLog(Net, Error, "KQUEUE_ctl: RegisterSocket");
			return GetLastResultCode();
		}

		SFLog(Net, Info, "Socket Registered sock:{0}", cbInstance->GetIOSocket());

		return ResultCode::SUCCESS;
	}

	Result IOWorkerKQUEUE::UnregisterIOHandler(AsyncIOAdapter* cbInstance)
	{
		// This will be handled with EV_EOF
		//struct kevent evSet;

		//EV_SET(&evSet, cbInstance->GetIOSocket(), EVFILT_READ | EVFILT_WRITE, EV_DELETE, 0, 0, cbInstance);
		//if (kevent(m_hKQUEUE, &evSet, 1, NULL, 0, NULL) == -1)
		//{
		//	SFLog(Net, Error, "KQUEUE_ctl: UnregisterSocket");
		//	return GetLastResultCode();
		//}

		return ResultCode::SUCCESS;
	}

	Result IOWorkerKQUEUE::HandleAccept(SOCKET sock, AsyncIOAdapter* pCallBack)
	{
		Result hr = ResultCode::SUCCESS;
		IOBUFFER_ACCEPT* pAcceptInfo = nullptr;

		SFLog(Net, Info, "Socket Accepted sock:{0}", sock);
		while (1)
		{
			// Accept will happened in network thread
			hr = pCallBack->Accept(pAcceptInfo);
			switch ((uint32_t)hr)
			{
			case (uint32_t)ResultCode::SUCCESS:
				netChk(pCallBack->OnIOAccept(hr, pAcceptInfo));
				pAcceptInfo = nullptr;
				break;
			case (uint32_t)ResultCode::NOT_IMPLEMENTED:
				Assert(false); // Fix it!
				break;
			case (uint32_t)ResultCode::IO_TRY_AGAIN:
			case (uint32_t)ResultCode::IO_WOULDBLOCK:
			case (uint32_t)ResultCode::IO_IO_PENDING:
			case (uint32_t)ResultCode::INVALID_FILE_HANDLE:
				goto Proc_End;
			default:
				// some failure? try again
				break;
			}

			Util::SafeDelete(pAcceptInfo);
		}

	Proc_End:

		Util::SafeDelete(pAcceptInfo);


		return hr;
	}

	Result IOWorkerKQUEUE::HandleRW(unsigned int events, AsyncIOAdapter* pCallBack)
	{
		Result hr = ResultCode::SUCCESS;

		if (!(events & (EVFILT_READ| EVFILT_WRITE)))
		{
			SFLog(System, Error, "Error sock:{0}, event:{1}", sock, events);
			return ResultCode::UNEXPECTED;
		}

		if (events & EVFILT_READ)
		{
			hr = pCallBack->OnReadReady();
			if (!(hr))
			{
				goto Proc_End;
			}
		}

		if ((events & EVFILT_WRITE) != 0)
		{
			// This call will just poke working thread
			hr = pCallBack->OnWriteReady();
			if (!(hr))
			{
				goto Proc_End;
			}
		}

	Proc_End:

		if (!(hr))
		{
			SFLog(System, Info, "ERROR KQUEUE RW fail events:{0:X8} hr:{1:X8}", events, hr);
		}


		return hr;
	}

	void IOWorkerKQUEUE::Run()
	{
		Result hr = ResultCode::SUCCESS;
		int iNumEvents;
		struct kevent events[MAX_KQUEUE_EVENTS];

		while (1)
		{
			hr = ResultCode::SUCCESS;

			// Getting status
			iNumEvents = kevent(m_hKQUEUE, NULL, 0, events, countof(events), NULL);
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
					SFLog(Net, Info, "ERROR KQUEUE wait failed hr={0:X8}", hr);
					break;
				}
			}

			for (int iEvent = 0; iEvent < iNumEvents; iEvent++)
			{
				if (events[iEvent].udata == nullptr)
				{
					SFLog(System, Info, "ERROR KQUEUE null handler, skipping...");
					continue;
				}

				auto& curEvent = events[iEvent];
				auto pCallback = (AsyncIOAdapter*)curEvent.udata;
				auto ioHandle = pCallback->GetIOHandle();

				// skip invalid handlers
				if (pCallback == nullptr || !pCallback->GetIsIORegistered())
					continue;

				if ((curEvent.flags&(EV_EOF)))
				{
					SFLog(System, Info, "Closing epoll ioHandle:{0}, event:{1}", ioHandle, curEvent.flags);
					pCallback->OnIOUnregistered();
					continue;
				}

				HandleRW(curEvent.flags, pCallback);

				if (pCallback->GetIOHandle() == INVALID_NATIVE_HANDLE_VALUE)
				{
					pCallback->OnIOUnregistered();
				}

			}

			// Check exit event
			if (CheckKillEvent(DurationMS(0)))
				break;

		} // while(1)

	}




	////////////////////////////////////////////////////////////////////////////////
	//
	//	KQUEUE network system
	//



	KQUEUESystem::KQUEUESystem(IHeap& heap)
		: AsyncIOPortSystem_Reactor(heap)
	{
	}

	Result KQUEUESystem::Initialize(uint netThreadCount)
	{
		Result result = AsyncIOSystem_Reactor::Initialize(netThreadCount);
		if (!result)
			return result;


		int hKQUEUE = kqueue();


		SetNativeIOSystemHandle((NativeHandle)(intptr_t)hEPoll);

		// client will use only 1 thread
		for (uint iThread = 0; iThread < netThreadCount; iThread++)
		{
			auto pNewWorker = new(GetHeap()) IOWorkerKQUEUE(this, iThread, hKQUEUE);
			pNewWorker->Start();
			AddIOWorker(pNewWorker);
		}

		return ResultCode::SUCCESS;
	}

	void KQUEUESystem::Terminate()
	{
		AsyncIOSystem_Reactor::Terminate();
	}




} // namespace Net
} // namespace SF

#else
void Dummp_AsyncIO_KQUEUE() {}
#endif


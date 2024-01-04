////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c)  Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Network system for EPOLL
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"

#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Multithread/SFSystemSynchronization.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Service/SFEngineService.h"
#include "Net/SFNetSocket.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetSystem_EPOLL.h"


#if EPOLL

#include <sys/epoll.h>




namespace SF {
namespace Net {


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

	EPOLLWorker::EPOLLWorker(bool bHandleSend, int hEpoll)
		: m_hEpoll(hEpoll)
		, m_HandleSend(bHandleSend)
	{
		if (m_hEpoll == 0)
		{
			m_hEpoll = epoll_create(1);
		}
	}

	EPOLLWorker::~EPOLLWorker()
	{

	}

	Result EPOLLWorker::RegisterSocket(SocketIO* cbInstance)
	{
		epoll_event epollEvent;

		memset(&epollEvent, 0, sizeof(epollEvent));
		epollEvent.events = EVENT_MASK;
		epollEvent.data.ptr = cbInstance;
		if (epoll_ctl(m_hEpoll, EPOLL_CTL_ADD, cbInstance->GetIOSocket(), &epollEvent) == -1) {
			SFLog(Net, Error, "epoll_ctl: RegisterSocket sock:{0}", cbInstance->GetIOSocket());
			return ResultCode::FAIL;
		}

		SFLog(Net, Info, "epoll register sock:{0}", cbInstance->GetIOSocket());

		return ResultCode::SUCCESS;
	}

	Result EPOLLWorker::UnregisterSocket(SocketIO* cbInstance)
	{
		epoll_event epollEvent;

		memset(&epollEvent, 0, sizeof(epollEvent));
		epollEvent.events = EVENT_MASK;
		epollEvent.data.ptr = cbInstance;
		if (epoll_ctl(m_hEpoll, EPOLL_CTL_DEL, cbInstance->GetIOSocket(), &epollEvent) == -1) {
			SFLog(Net, Error, "epoll_ctl: UnregisterSocket sock:{0}", cbInstance->GetIOSocket());
			return ResultCode::FAIL;
		}

		SFLog(Net, Info, "epoll unregister sock:{0}", cbInstance->GetIOSocket());

		return ResultCode::SUCCESS;
	}

	Result EPOLLWorker::HandleAccept(SF_SOCKET sock, SocketIO* pCallBack)
	{
		IOBUFFER_ACCEPT* pAcceptInfo = nullptr;
		ScopeContext hr([&pAcceptInfo](Result hr)
			{
				Util::SafeDelete(pAcceptInfo);
			});

		while (1)
		{
			// Accept will happened in network thread
			hr = pCallBack->Accept(pAcceptInfo);
			switch ((uint32_t)(Result)hr)
			{
			case (uint32_t)ResultCode::SUCCESS:
				if (pAcceptInfo->sockAccept != INVALID_SOCKET)
				{
					hr = pCallBack->OnIOAccept(hr, pAcceptInfo);
					pAcceptInfo = nullptr;
					if (!hr.IsSuccess())
						return hr;
				}
				else
				{
					return hr;
				}
				break;
			case (uint32_t)ResultCode::NOT_IMPLEMENTED:
				Assert(false); // Fix it!
				break;
			case (uint32_t)ResultCode::IO_TRY_AGAIN:
			case (uint32_t)ResultCode::IO_WOULDBLOCK:
			case (uint32_t)ResultCode::IO_IO_PENDING:
			case (uint32_t)ResultCode::INVALID_FILE_HANDLE:
				return hr;
			default:
				// some failure? try again
				break;
			}

			Util::SafeDelete(pAcceptInfo);
		}

		return hr;
	}

	Result EPOLLWorker::HandleRW(SF_SOCKET sock, unsigned int events, SocketIO* pCallBack)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;
		IOBUFFER_READ* pReadBuffer = nullptr;

		//  skip when the socket value is different
		if (pCallBack->GetIOSocket() != sock) return ResultCode::SUCCESS_FALSE;

		//if (!(events & (EPOLLIN | EPOLLOUT)))
		//{
		//	SFLog(Net, Error, "Error sock:{0}, event:{1}", sock, events);
		//	return ResultCode::UNEXPECTED;
		//}

		if (events & EPOLLIN)
		{
			while (hrErr)
			{
				// Read
				pReadBuffer = new(GetSystemHeap()) IOBUFFER_READ;
				hrErr = pCallBack->Recv(pReadBuffer);
				hr = hrErr;
				switch ((uint32_t)hrErr)
				{
				case (uint32_t)ResultCode::IO_TRY_AGAIN:
				case (uint32_t)ResultCode::IO_WOULDBLOCK:
				case (uint32_t)ResultCode::SUCCESS_FALSE:
					// These are expected return code
					hr = ResultCode::SUCCESS;
					break;
				case (uint32_t)ResultCode::IO_IO_PENDING:
					Assert(false);
					break;
				default:
					if (!hr.IsSuccess())
					{
						char stringBuffer[512];
						SFLog(Net, Info, "ERROR Epoll Recv fail sock:{0} events:{1} hr:{2}", sock, Service::NetSystem->GetNetIOSystem().EventFlagToString(sizeof(stringBuffer), stringBuffer, events), hrErr);
					}
					// fallthru
				case (uint32_t)ResultCode::SUCCESS:
					// toss data to working thread
					if (pReadBuffer != nullptr)
					{
						SFLog(Net, Debug3, "Recv From:{0}, To:{1}, Size{2}", pReadBuffer->NetAddr.From, pReadBuffer->NetAddr.To, pReadBuffer->TransferredSize);
						netChk(pCallBack->OnIORecvCompleted(hrErr, pReadBuffer));
					}
					pReadBuffer = nullptr;
					hr = hrErr;
					break;
				}

				// OnIORecvCompleted wouldn't delete anything
				Util::SafeDelete(pReadBuffer);
			}
		}

		if (m_HandleSend && (events & EPOLLOUT))
		{
			// This call will just poke working thread
			hr = pCallBack->OnWriteReady();
			if (!hr.IsSuccess())
			{
				netErr(hr);
			}
		}

	Proc_End:

		if (!hr.IsSuccess())
		{
			char stringBuffer[512];
			SFLog(Net, Info, "ERROR Epoll RW fail sock:{0}, events:{1} hr:{2}", sock, Service::NetSystem->GetNetIOSystem().EventFlagToString(sizeof(stringBuffer), stringBuffer, events), hr);
		}

		Util::SafeDelete(pReadBuffer);

		return hr;
	}

	void EPOLLWorker::Run()
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
				case (uint32_t)ResultCode::INVALID_ARG:
				default:
					SFLog(Net, Info, "ERROR EPOLL wait failed hr={0:X8}", hr);
					break;
				}
			}

			for (int iEvent = 0; iEvent < iNumEvents; iEvent++)
			{
				if (events[iEvent].data.ptr == nullptr)
				{
					SFLog(Net, Info, "ERROR EPOLL null handler, skipping...");
					continue;
				}

				auto& curEvent = events[iEvent];
				auto pCallback = (SocketIO*)curEvent.data.ptr;
				bool isListenSocket = pCallback->GetIOFlags().IsListenSocket != 0;
				SF_SOCKET sock = pCallback->GetIOSocket();

				// skip invalid handlers
				if (pCallback == nullptr || !pCallback->GetIsIORegistered())
					continue;

				if ((curEvent.events&ERROR_EVENT_MASK) != 0)
				{
					char stringBuffer[512];
					SFLog(Net, Info, "Closing epoll worker sock:{0}, event:{1}", sock, Service::NetSystem->GetNetIOSystem().EventFlagToString(sizeof(stringBuffer), stringBuffer, curEvent.events));
					Service::NetSystem->GetNetIOSystem().UnregisterFromNETIO(pCallback);
					pCallback->OnIOUnregistered();
					continue;
				}

				if (isListenSocket)
				{
					HandleAccept(sock, pCallback);
				}
				else
				{
					HandleRW(sock, curEvent.events, pCallback);
				}
			}

			// Check exit event
			if (CheckKillEvent(DurationMS(0)))
				break;

		} // while(1)

	}




	//// Constructor/destructor
	//EPOLLSendWorker::EPOLLSendWorker()
	//	: m_WriteQueue(Service::NetSystem->GetHeap())
	//{
	//}

	//EPOLLSendWorker::~EPOLLSendWorker()
	//{
	//	m_WriteQueue.Reset();
	//}

	//void EPOLLSendWorker::Run()
	//{
	//	Result hr = ResultCode::SUCCESS;
	//	IOBUFFER_WRITE* pSendBuffer = nullptr;
	//	DurationMS tickInterval(0);

	//	while (1)
	//	{
	//		hr = ResultCode::SUCCESS;

	//		// Check exit event
	//		if (CheckKillEvent(tickInterval))
	//			break;


	//		if (pSendBuffer == nullptr) m_WriteQueue.Dequeue(pSendBuffer);

	//		if (pSendBuffer == nullptr)
	//		{
	//			tickInterval = DurationMS(1);
	//			continue;
	//		}
	//		else
	//		{
	//			tickInterval = DurationMS(0);
	//		}

	//		switch (pSendBuffer->Operation)
	//		{
	//		case IOBUFFER_OPERATION::OP_TCPWRITE:
	//			Assert(false); // TCP packets will be sent by RW workers
	//			break;
	//		case IOBUFFER_OPERATION::OP_UDPWRITE:
	//			hr = Service::NetSystem->SendTo(pSendBuffer->SockWrite, pSendBuffer);
	//			switch ((uint32_t)hr)
	//			{
	//			case (uint32_t)ResultCode::IO_TRY_AGAIN:
	//				continue; // try again
	//				break;
	//			case (uint32_t)ResultCode::SUCCESS:
	//				break;
	//			default:
	//				SFLog(Net, Info, "ERROR UDP send failed {0:X8}", hr);
	//				// send fail
	//				break;
	//			}
	//			break;
	//		default:
	//			Assert(false);// This thread isn't designed to work on other stuffs
	//			break;
	//		}


	//		Util::SafeDelete(pSendBuffer);
	//		pSendBuffer = nullptr;
	//		

	//	} // while(1)


	//	Util::SafeDelete(pSendBuffer);
	//}




	////////////////////////////////////////////////////////////////////////////////
	//
	//	EPOLL network system
	//



	EPOLLSystem::EPOLLSystem()
		: m_ListenWorker(nullptr)
		, m_iTCPAssignIndex(0)
		, m_WorkerTCP(Service::NetSystem->GetHeap())
//		, m_UDPSendWorker(nullptr)
		, m_WorkerUDP(Service::NetSystem->GetHeap())
	{
	}

	Result EPOLLSystem::Initialize(uint netThreadCount)
	{
		if (m_ListenWorker != nullptr)
			return ResultCode::SUCCESS;


		int hEPollUDP = epoll_create(1);

		m_ListenWorker = new(Service::NetSystem->GetHeap()) EPOLLWorker(false);
		m_ListenWorker->Start();

		//m_UDPSendWorker = new(Service::NetSystem->GetHeap()) EPOLLSendWorker;
		//m_UDPSendWorker->Start();

		m_iTCPAssignIndex = 0;

		// client will use only 1 thread
		if (netThreadCount > 1)
		{
			// divide by 2
			netThreadCount >>= 1;


			for (uint iThread = 0; iThread < netThreadCount; iThread++)
			{
				auto pNewWorker = new(Service::NetSystem->GetHeap()) EPOLLWorker(true);
				m_WorkerTCP.push_back(pNewWorker);

				pNewWorker->Start();
			}

			// 
			for (uint iThread = 0; iThread < netThreadCount; iThread++)
			{
				auto pNewWorker = new(Service::NetSystem->GetHeap()) EPOLLWorker(false, hEPollUDP);
				m_WorkerUDP.push_back(pNewWorker);

				pNewWorker->Start();
			}

		}

		return ResultCode::SUCCESS;
	}

	void EPOLLSystem::Terminate()
	{
		if (m_ListenWorker)
		{
			m_ListenWorker->Stop(true);
			Service::NetSystem->GetHeap().Delete(m_ListenWorker);
		}
		m_ListenWorker = nullptr;

		// 
		for (uint iThread = 0; iThread < m_WorkerTCP.size(); iThread++)
		{
			m_WorkerTCP[iThread]->Stop(true);
			Service::NetSystem->GetHeap().Delete(m_WorkerTCP[iThread]);
		}
		m_WorkerTCP.Clear();


		//if (m_UDPSendWorker)
		//{
		//	m_UDPSendWorker->Stop(true);
		//	Service::NetSystem->GetHeap().Delete(m_UDPSendWorker);
		//}
		//m_UDPSendWorker = nullptr;

		// 
		int hEpoll = 0;
		for (uint iThread = 0; iThread < m_WorkerUDP.size(); iThread++)
		{
			auto pThread = m_WorkerUDP[iThread];
			hEpoll = pThread->GetEpollHandle();
			pThread->Stop(true);
			Service::NetSystem->GetHeap().Delete(pThread);
		}
		m_WorkerUDP.Clear();

		if (hEpoll != 0)
		{
			close(hEpoll);
		}
	}

	Result EPOLLSystem::MakeSocketNonBlocking(SF_SOCKET sfd)
	{
		int flags, s;

		flags = fcntl(sfd, F_GETFL, 0);
		if (flags == -1)
		{
			SFLog(Net, Error, "epoll_ctl: fcntl F_GETFL");
			return ResultCode::FAIL;
		}

		flags |= O_NONBLOCK;
		s = fcntl(sfd, F_SETFL, flags);
		if (s == -1)
		{
			SFLog(Net, Error, "epoll_ctl: fcntl F_SETFL");
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}


	//WriteBufferQueue* EPOLLSystem::GetWriteBufferQueue()
	//{
	//	if (m_UDPSendWorker == nullptr)
	//		return nullptr;

	//	return &m_UDPSendWorker->GetWriteQueue();
	//}


	//Result EPOLLSystem::RegisterSharedSocket(SocketType sockType, SocketIO* cbInstance)
	//{
	//	Assert(sockType == SocketType::DataGram);
	//	if (sockType != SocketType::DataGram)
	//		return ResultCode::UNEXPECTED;

	//	if (m_WorkerUDP.GetSize() < 1)
	//		return ResultCode::IO_NOTINITIALISED;

	//	if (cbInstance->GetWriteQueue() == nullptr)
	//	{
	//		Assert(sockType == SocketType::DataGram);
	//		cbInstance->SetWriteQueue(&m_UDPSendWorker->GetWriteQueue());
	//	}

	//	return ResultCode::SUCCESS;
	//}

	// Register the socket to EPOLL
	Result EPOLLSystem::RegisterToNETIO(SocketIO* cbInstance)
	{
		if (m_ListenWorker == nullptr)
			return ResultCode::IO_NOTINITIALISED;

		if (cbInstance->GetIOSockType() == SocketType::Stream) // TCP
		{
			// Listen worker will do all job when there is no other thread.
			if (cbInstance->GetIOFlags().IsListenSocket != 0 || m_WorkerTCP.size() == 0)
			{
				return m_ListenWorker->RegisterSocket(cbInstance);
			}
			else
			{
				auto assignIndex = m_iTCPAssignIndex.fetch_add(1,std::memory_order_relaxed) % m_WorkerTCP.size();
				cbInstance->SetAssignedIOWorker(assignIndex);
				m_WorkerTCP[assignIndex]->RegisterSocket(cbInstance);
			}
		}
		else
		{
			if (m_WorkerUDP.size() < 1)
			{
				Result hr = m_ListenWorker->RegisterSocket(cbInstance);
				if (hr.IsFailure()) return hr;
			}
			else
			{
				// UDP workers are sharing epoll, add any of them will work same.
				Result hr = m_WorkerUDP[0]->RegisterSocket(cbInstance);
				if (hr.IsFailure()) return hr;
			}
			cbInstance->SetAssignedIOWorker(0);
		}

		return ResultCode::SUCCESS;
	}

	Result EPOLLSystem::UnregisterFromNETIO(SocketIO* cbInstance)
	{
		if (m_ListenWorker == nullptr)
			return ResultCode::IO_NOTINITIALISED;

		SocketType sockType = cbInstance->GetIOSockType();

		if (sockType == SocketType::Stream) // TCP
		{
			if (cbInstance->GetIOFlags().IsListenSocket != 0 || m_WorkerTCP.size() == 0)
			{
				return m_ListenWorker->UnregisterSocket(cbInstance);
			}
			else
			{
				auto assignIndex = cbInstance->GetAssignedIOWorker();
				if (assignIndex >= 0 && assignIndex < (int)m_WorkerTCP.size())
				{
					m_WorkerTCP[assignIndex]->UnregisterSocket(cbInstance);
					cbInstance->SetAssignedIOWorker(-1);
				}
			}
		}
		else
		{
			if (m_WorkerUDP.size() < 1)
			{
				Result hr = m_ListenWorker->UnregisterSocket(cbInstance);
				if (hr.IsFailure()) return hr;
			}
			else
			{
				Result hr = m_WorkerUDP[0]->UnregisterSocket(cbInstance);
				if (hr.IsFailure()) return hr;
			}
			cbInstance->SetAssignedIOWorker(-1);
		}

		return ResultCode::SUCCESS;
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







} // namespace Net
} // namespace SF

#else
void Dummp_NetSystem_EPOLL() {}
#endif


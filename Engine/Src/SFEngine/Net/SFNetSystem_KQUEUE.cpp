////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2015 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Network system for KQUEUE
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"


#if KQUEUE

#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Multithread/SFSystemSynchronization.h"
#include "MemoryManager/SFMemoryPool.h"

#include "Service/SFEngineService.h"

#include "Net/SFNetSystem.h"
#include "Net/SFNetSystem_KQUEUE.h"

#include <sys/event.h>



namespace SF {
namespace Net {





	////////////////////////////////////////////////////////////////////////////////
	//
	//	KQUEUE thread worker
	//

	KQUEUEWorker::KQUEUEWorker(bool bHandleSend, int hKQUEUE)
		: m_hKQUEUE(hKQUEUE)
		, m_HandleSend(bHandleSend)
	{
		if (m_hKQUEUE == 0)
		{
			m_hKQUEUE = kqueue();
		}
	}

	KQUEUEWorker::~KQUEUEWorker()
	{

	}

	Result KQUEUEWorker::RegisterSocket(SocketIO* cbInstance)
	{
		struct kevent evSet;

		EV_SET(&evSet, cbInstance->GetIOSocket(), EVFILT_READ | EVFILT_WRITE , EV_ADD, 0, 0, cbInstance);
		if (kevent(m_hKQUEUE, &evSet, 1, NULL, 0, NULL) == -1)
		{
			SFLog(Net, Error, "KQUEUE_ctl: RegisterSocket");
			return GetLastNetSystemResult();
		}

		SFLog(Net, Info, "Socket Registered sock:{0}", cbInstance->GetIOSocket());

		return ResultCode::SUCCESS;
	}

	Result KQUEUEWorker::UnregisterSocket(SocketIO* cbInstance)
	{
		// This will be handled with EV_EOF
		//struct kevent evSet;

		//EV_SET(&evSet, cbInstance->GetIOSocket(), EVFILT_READ | EVFILT_WRITE, EV_DELETE, 0, 0, cbInstance);
		//if (kevent(m_hKQUEUE, &evSet, 1, NULL, 0, NULL) == -1)
		//{
		//	SFLog(Net, Error, "KQUEUE_ctl: UnregisterSocket");
		//	return GetLastNetSystemResult();
		//}

		return ResultCode::SUCCESS;
	}

	Result KQUEUEWorker::HandleAccept(SF_SOCKET sock, SocketIO* pCallBack)
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
					if (!hr)
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
				goto Proc_End;
			default:
				// some failure? try again
				break;
			}

			Util::SafeDelete(pAcceptInfo);
		}

		return hr;
	}

	Result KQUEUEWorker::HandleRW(SF_SOCKET sock, unsigned int events, SocketIO* pCallBack)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;
		IOBUFFER_READ* pReadBuffer = nullptr;

		if (!(events & (EVFILT_READ| EVFILT_WRITE)))
		{
			SFLog(Net, Error, "Error sock:{0}, event:{1}", sock, events);
			return ResultCode::UNEXPECTED;
		}

		if (events & EVFILT_READ)
		{
			while ((hrErr))
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
					if (!(hr))
					{
						SFLog(Net, Info, "ERROR KQUEUE Recv fail events:{0:X8} hr:{1:X8}", events, hrErr);
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

		if (m_HandleSend && ((events & EVFILT_WRITE) != 0))
		{
			// This call will just poke working thread
			hr = pCallBack->OnWriteReady();
			if (!(hr))
			{
				//netErr(hr);
				goto Proc_End;
			}
		}

	Proc_End:

		if (!(hr))
		{
			SFLog(Net, Info, "ERROR KQUEUE RW fail events:{0:X8} hr:{1:X8}", events, hr);
		}

		Util::SafeDelete(pReadBuffer);

		return hr;
	}

	void KQUEUEWorker::Run()
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
					SFLog(Net, Info, "ERROR KQUEUE null handler, skipping...");
					continue;
				}

				auto& curEvent = events[iEvent];
				auto pCallback = (SocketIO*)curEvent.udata;
				bool isListenSocket = pCallback->GetIOFlags().IsListenSocket != 0;
				SF_SOCKET sock = pCallback->GetIOSocket();

				// skip invalid handlers
				if (pCallback == nullptr || !pCallback->GetIsIORegistered())
					continue;

				if ((curEvent.flags&(EV_EOF)))
				{
					SFLog(Net, Info, "Closing epoll sock:{0}, event:{1}", sock, curEvent.flags);
					pCallback->OnIOUnregistered();
					continue;
				}

				if (isListenSocket)
				{
					HandleAccept(sock, pCallback);
				}
				else
				{
					bool hangup = false;
					//if ((curEvent.flags&EPOLLHUP) != 0)
					//{
					//	hangup = true;
					//	if (pCallback->GetIOSocket() == INVALID_SOCKET)
					//		pCallback->OnIOUnregistered();

					//	// Send error will be handled gracefully
					//	curEvent.flags |= EPOLLOUT;
					//}

					HandleRW(sock, curEvent.flags, pCallback);

					if (hangup && pCallback->GetIOSocket() == INVALID_SOCKET)
					{
						pCallback->OnIOUnregistered();
					}
				}

			}

			// Check exit event
			if (CheckKillEvent(DurationMS(0)))
				break;

		} // while(1)

	}




	//// Constructor/destructor
	//KQUEUESendWorker::KQUEUESendWorker()
	//	: m_WriteQueue(Service::NetSystem->GetHeap())
	//{
	//}

	//KQUEUESendWorker::~KQUEUESendWorker()
	//{
	//	m_WriteQueue.ClearQueue();
	//}

	//void KQUEUESendWorker::Run()
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
	//	KQUEUE network system
	//



	KQUEUESystem::KQUEUESystem()
		: m_ListenWorker(nullptr)
		, m_iTCPAssignIndex(0)
		, m_WorkerTCP(Service::NetSystem->GetHeap())
		//, m_UDPSendWorker(nullptr)
		, m_WorkerUDP(Service::NetSystem->GetHeap())
	{
	}

	Result KQUEUESystem::Initialize(uint netThreadCount)
	{
		if (m_ListenWorker != nullptr)
			return ResultCode::SUCCESS;

		int hKQUEUEUDP = kqueue();

		m_ListenWorker = new(Service::NetSystem->GetHeap()) KQUEUEWorker(false);
		m_ListenWorker->Start();

		//m_UDPSendWorker = new(Service::NetSystem->GetHeap()) KQUEUESendWorker;
		//m_UDPSendWorker->Start();

		m_iTCPAssignIndex = 0;

		if (netThreadCount > 1)
		{
			// 
			for (uint iThread = 0; iThread < netThreadCount; iThread++)
			{
				auto pNewWorker = new(Service::NetSystem->GetHeap()) KQUEUEWorker(true);
				pNewWorker->Start();
				m_WorkerTCP.push_back(std::forward<KQUEUEWorker*>(pNewWorker));
			}

			// 
			for (uint iThread = 0; iThread < netThreadCount; iThread++)
			{
				auto pNewWorker = new(Service::NetSystem->GetHeap()) KQUEUEWorker(false, hKQUEUEUDP);
				pNewWorker->Start();
				m_WorkerUDP.push_back(std::forward<KQUEUEWorker*>(pNewWorker));
			}
		}

		return ResultCode::SUCCESS;
	}

	void KQUEUESystem::Terminate()
	{
		if (m_ListenWorker)
		{
			m_ListenWorker->Stop(true);
			Service::NetSystem->GetHeap().Delete(m_ListenWorker);
		}
		m_ListenWorker = nullptr;

		// 
		for (auto itWorker : m_WorkerTCP)
		{
			itWorker->Stop(true);
			Service::NetSystem->GetHeap().Delete(itWorker);
		}
		m_WorkerTCP.Clear();


		//if (m_UDPSendWorker)
		//{
		//	m_UDPSendWorker->Stop(true);
		//	Service::NetSystem->GetHeap().Delete(m_UDPSendWorker);
		//}
		//m_UDPSendWorker = nullptr;

		// 
		int hKQUEUE = 0;
		for (auto itWorker : m_WorkerUDP)
		{
			hKQUEUE = itWorker->GetKQUEUEHandle();
			itWorker->Stop(true);
			Service::NetSystem->GetHeap().Delete(itWorker);
		}
		m_WorkerUDP.Clear();

		if (hKQUEUE != 0)
		{
			close(hKQUEUE);
		}
	}

	Result KQUEUESystem::MakeSocketNonBlocking(SF_SOCKET sfd)
	{
		int flags, s;

		flags = fcntl(sfd, F_GETFL, 0);
		if (flags == -1)
		{
			SFLog(Net, Error, "KQUEUE_ctl: fcntl F_GETFL");
			return ResultCode::FAIL;
		}

		flags |= O_NONBLOCK;
		s = fcntl(sfd, F_SETFL, flags);
		if (s == -1)
		{
			SFLog(Net, Error, "KQUEUE_ctl: fcntl F_SETFL");
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}

	// UDP shares the send queue
	//WriteBufferQueue* KQUEUESystem::GetWriteBufferQueue()
	//{
	//	if (m_UDPSendWorker == nullptr)
	//		return nullptr;

	//	return &m_UDPSendWorker->GetWriteQueue();
	//}


	//Result KQUEUESystem::RegisterSharedSocket(SocketType sockType, SocketIO* cbInstance)
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
	Result KQUEUESystem::RegisterToNETIO(SocketType sockType, SocketIO* cbInstance)
	{
		if (m_ListenWorker == nullptr)
			return ResultCode::IO_NOTINITIALISED;

		if (sockType == SocketType::Stream) // TCP
		{
			// Listen worker will do all job when there is no other thread.
			if (cbInstance->GetIOFlags().IsListenSocket != 0 || m_WorkerTCP.size() == 0)
			{
				return m_ListenWorker->RegisterSocket(cbInstance);
			}
			else
			{
				auto assignIndex = m_iTCPAssignIndex.fetch_add(1, std::memory_order_relaxed) % (int)m_WorkerTCP.size();
				cbInstance->SetAssignedIOWorker(assignIndex);
				m_WorkerTCP[assignIndex]->RegisterSocket(cbInstance);
			}
		}
		else
		{
			if (cbInstance->GetWriteQueue() == nullptr)
			{
				Assert(sockType == SocketType::DataGram);
				//cbInstance->SetWriteQueue(&m_UDPSendWorker->GetWriteQueue());
			}

			if (m_WorkerUDP.size() < 1)
			{
				Result hr = m_ListenWorker->RegisterSocket(cbInstance);
				if (!(hr)) return hr;
			}
			else
			{
				// UDP workers are sharing epoll, add any of them will work same.
				Result hr = m_WorkerUDP[0]->RegisterSocket(cbInstance);
				if (!(hr)) return hr;
			}
			cbInstance->SetAssignedIOWorker(0);
		}

		return ResultCode::SUCCESS;
	}

	Result KQUEUESystem::UnregisterFromNETIO(SocketIO* cbInstance)
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
				if (!(hr)) return hr;
			}
			else
			{
				Result hr = m_WorkerUDP[0]->UnregisterSocket(cbInstance);
				if (!(hr)) return hr;
			}
			cbInstance->SetAssignedIOWorker(-1);
		}

		return ResultCode::SUCCESS;
	}








} // namespace Net
} // namespace SF

#else
void Dummp_NetSystem_KQUEUE() {}
#endif


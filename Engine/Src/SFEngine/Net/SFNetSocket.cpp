////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Net socket + IO handling
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetSocket.h"
#include "Net/SFNetSystem_EPOLL.h"
#include "Net/SFNetSystem_KQUEUE.h"
#include "Net/SFNetSystem_WinIOCP.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Multithread/SFThread.h"
#include "Util/SFUtility.h"
#include "Container/SFSpinSharedBuffer.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Service/SFEngineService.h"
#include "Net/SFNetPacketData.h"



namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	// SocketIO interface
	//

	SocketIO::SocketIO(IHeap& heap)
		: m_Heap(heap)
		, m_IOStatus(IOStatus::None)
		//, m_pWriteQueues(nullptr)
		, m_PendingRecvCount(0)
		, m_PendingSendCount(0)
	{
	}

	SocketIO::~SocketIO()
	{
        if (GetIsIORegistered()) Service::NetSystem->UnregisterSocket(this);

        if (m_IOSocket != INVALID_SOCKET)
        {
            Service::NetSystem->CloseSocket(m_IOSocket);
            m_IOSocket = INVALID_SOCKET;
        }

		AssertRel(m_IOStatus == IOStatus::None);
		Assert(m_PendingSendCount == 0 && m_PendingRecvCount == 0);
	}

	void SocketIO::SetSocket(SockFamily sockFamily, SocketType socketType, SF_SOCKET socket)
	{
		m_IOSockFamily = sockFamily;
		m_IOSockType = socketType;
		m_IOSocket = socket;
	}

	void SocketIO::CloseSocket()
	{
		if (m_IOSocket != INVALID_SOCKET)
		{
			if(GetIsIORegistered()) Service::NetSystem->UnregisterSocket(this);
			Service::NetSystem->CloseSocket(m_IOSocket);
			m_IOSocket = INVALID_SOCKET;
		}
	}

	void SocketIO::SetAssignedIOWorker(int assignedIOWorker)
	{
		m_AssignedIOWorker = assignedIOWorker;
	}

	void SocketIO::OnIORegistered()
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

	void SocketIO::OnIOUnregistered()
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

	//Result SocketIO::ProcessSendQueue()
	//{
	//	Result hr = ResultCode::SUCCESS;
	//	IOBUFFER_WRITE* pSendBuffer = nullptr;

	//	auto writeQueue = m_pWriteQueues;
	//	if(writeQueue == nullptr) return ResultCode::INVALID_POINTER;

	//	while (1)
	//	{
	//		hr = writeQueue->GetFront(pSendBuffer);
	//		if (hr.IsFailure())
	//		{
	//			hr = ResultCode::SUCCESS;
	//			break;
	//		}

	//		hr = WriteBuffer(pSendBuffer);
	//		switch ((uint32_t)hr)
	//		{
	//		case (uint32_t)ResultCode::SUCCESS:
	//			writeQueue->Dequeue(pSendBuffer);
	//			break;
	//		case (uint32_t)ResultCode::IO_IO_PENDING:
	//			break;
	//		case (uint32_t)ResultCode::IO_WOULDBLOCK:  // WOULDBLOCK in linux can be try again
	//		case (uint32_t)ResultCode::IO_TRY_AGAIN:
	//		default:
	//			goto Proc_End;
	//			break;
	//		}
	//	}

	//Proc_End:

	//	return hr;
	//}



	//Result SocketIO::EnqueueBuffer(IOBUFFER_WRITE *pSendBuffer)
	//{
	//	auto writeQueue = m_pWriteQueues;
	//	if (writeQueue == nullptr) return ResultCode::INVALID_POINTER;

	//	return writeQueue->Enqueue(pSendBuffer);
	//}



	bool SocketIO::CanDelete()
	{
		if (GetIsIORegistered())
			return false;

		return ((GetPendingSendCount() + GetPendingRecvCount()) == 0);

	}

	// called when send completed
	Result SocketIO::OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE *pIOBuffer)
	{
		delete (pIOBuffer);
		DecPendingSendCount();
		return ResultCode::SUCCESS;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SocketIOUDP
	//	 - For UDP socket IO
	//

	SocketIOUDP::SocketIOUDP(IHeap& heap)
		: SocketIO(heap)
	{
	}

	// Pending recv New one
	Result SocketIOUDP::PendingRecv(IOBUFFER_READ *pRecvBuffer)
	{
		ScopeContext hr([&pRecvBuffer](Result hr)
			{
				SFLog(Net, Debug4, "SocketIOUDP::PendingRecv hr:{0}", hr);
				delete (pRecvBuffer);
			});
		Result hrErr = ResultCode::SUCCESS;
		m_LastPendingRecvResult = ResultCode::SUCCESS;

		if (!NetSystem::IsProactorSystem())
			return ResultCode::SUCCESS;

		if (pRecvBuffer != nullptr)
		{
			netCheck(pRecvBuffer->SetPendingTrue());
		}

		// This function can be called from net IO thread, so increasing first is required so that the SocketIO isn't released during pendingRecv handling
		IncPendingRecvCount();

		while (1)
		{
			// we need to check io status after increase pending count
			// If it's not registered we need to stop here
			if (!GetIsIORegistered())
			{
				// We have two possibility here. Out of memory or the the connection is released and waiting deletion
				hr = ResultCode::OUT_OF_MEMORY;
				DecPendingRecvCount();
				break;
			}

			if (pRecvBuffer == nullptr)
			{
				pRecvBuffer = new IOBUFFER_READ;
				hr = pRecvBuffer->SetPendingTrue();
				if (!hr.IsSuccess())
				{
					DecPendingRecvCount();
					break;
				}
			}

			if (pRecvBuffer == nullptr)
			{
				// out of memory
				hr = ResultCode::OUT_OF_MEMORY;
				DecPendingRecvCount();
				break;
			}

			hrErr = Recv(pRecvBuffer);
			switch ((uint32_t)hrErr)
			{
			case (uint32_t)ResultCode::SUCCESS: [[fallthrough]];
			case (uint32_t)ResultCode::IO_IO_PENDING: [[fallthrough]];
			case (uint32_t)ResultCode::IO_WOULDBLOCK:
				pRecvBuffer = nullptr;
				return hr;// success let's break out
				break;
			case (uint32_t)ResultCode::IO_TRY_AGAIN: [[fallthrough]];
			default:
				// some error, we need to try again
				m_LastPendingRecvResult = hrErr;
				break;
			}
		}

		return hr;
	}

	// Recv handling for UDP socket
	Result SocketIOUDP::Recv(IOBUFFER_READ* pIOBuffer)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;

		netChkPtr(pIOBuffer);

		pIOBuffer->SetupRecvUDP(GetUserSocketID());

		hrErr = Service::NetSystem->RecvFrom(this, pIOBuffer);
		hr = hrErr;
		switch ((uint32_t)hrErr)
		{
		case (uint32_t)ResultCode::SUCCESS_FALSE:
			Assert(false); // this is supposed not to be happened
			//hr = ResultCode::IO_TRY_AGAIN;
			break;
		case (uint32_t)ResultCode::SUCCESS:
		case (uint32_t)ResultCode::IO_IO_PENDING:
		case (uint32_t)ResultCode::IO_WOULDBLOCK:
			goto Proc_End;// success
			break;
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
		case (uint32_t)ResultCode::IO_NETUNREACH:
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
			// some remove has problem with connection
			// We should keep connection, but retry later
			SFLog(Net, Debug2, "UDP Remote has connection error err={0}, {1}", hrErr, pIOBuffer->NetAddr.From);
			//break;
		default:
			// Unknown error
			SFLog(Net, Debug3, "UDP Read Pending failed err={0:X8}", hrErr);
			//netErr( HRESULT_FROM_WIN32(iErr2) );
			break;
		};

	Proc_End:

		return hr;
	}

	// Send packet buffer to connection with network device
	Result SocketIOUDP::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;

		netChkPtr(pSendBuffer);

		hrErr = Service::NetSystem->SendTo(this, pSendBuffer);
		hr = hrErr;
		switch ((uint32_t)hrErr)
		{
		case (uint32_t)ResultCode::SUCCESS:
		case (uint32_t)ResultCode::IO_IO_PENDING:
			hr = ResultCode::SUCCESS;
			break;
        case (uint32_t)ResultCode::IO_WOULDBLOCK:
        case (uint32_t)ResultCode::IO_TRY_AGAIN:
            if (NetSystem::IsProactorSystem())
            {
                // Those are success with proactor system. The system will buffer the request and give notification when it is done
                hr = ResultCode::SUCCESS;
            }
            else
            {
                // Reactor pattern doesn't have internal buffering. You need to retry send again
                hr = ResultCode::IO_TRY_AGAIN;
            }
            break;
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTCONN:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			// Send fail by connection close
			// Need to disconnect
			//Disconnect("SendBufferUDP is failed");
			//hr = ResultCode::IO_CONNECTION_CLOSED;
			break;
		case (uint32_t)ResultCode::INVALID_POINTER:
			// Should I assert?
		default:
			hr = ResultCode::IO_IO_SEND_FAIL;
			break;
		};

	Proc_End:

		if (!hr.IsSuccess() && pSendBuffer != nullptr)
		{
			if (hr != ResultCode::IO_IO_SEND_FAIL)
			{
				// abnormal error, return error
				SFLog(Net, Debug1, "UDP Send Failed, CID:{0}, err:{1:X8}, hr:{2:X8}", GetUserSocketID(), hrErr, hr);
			}
			else
			{
				// regular error
				//SFLog(Net, Debug1, "UDP Send Failed, CID:{0}, err:{1:X8}, hr:{2:X8}", GetUserSocketID(), hrErr, hr);

				// return success and ignore further error handling
				return ResultCode::SUCCESS;
			}
		}
		else
		{
			//SFLog(Net, Error, "UDP Send ip:{0}, Len:{1}", GetRemoteInfo().PeerAddress, bufferLen);
		}

		return hr;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SocketIOTCP
	//	 - For TCP socket IO
	//

	SocketIOTCP::SocketIOTCP(IHeap& heap)
		: SocketIO(heap)
	{
	}

	// Accept handling
	Result SocketIOTCP::Accept(IOBUFFER_ACCEPT* &pAcceptInfo)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;
		SF_SOCKET sockAccept = INVALID_SOCKET;
		socklen_t iOptValue = 0;

		pAcceptInfo = new IOBUFFER_ACCEPT;
		netMem(pAcceptInfo);

		memset(pAcceptInfo, 0, sizeof(IOBUFFER_ACCEPT));

		sockAccept = Service::NetSystem->Socket(GetSocketFamily(), SocketType::Stream);
		if (sockAccept == INVALID_SOCKET)
		{
			SFLog(Net, Error, "Failed to Open Accept Socket {0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		pAcceptInfo->SetupAccept(sockAccept);

		// Set socket options
		//netChk(SetupSocketOption(pAcceptInfo->sockAccept));
		iOptValue = Net::Const::SVR_RECV_BUFFER_SIZE;
		if (setsockopt(sockAccept, SOL_SOCKET, SO_RCVBUF, (char *)&iOptValue, sizeof(iOptValue)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "Failed to change socket option SO_RCVBUF = {0}, err = {1:X8}", iOptValue, GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		iOptValue = Net::Const::SVR_SEND_BUFFER_SIZE;
		if (setsockopt(sockAccept, SOL_SOCKET, SO_SNDBUF, (char *)&iOptValue, sizeof(iOptValue)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "Failed to change socket option SO_SNDBUF = {0}, err = {1:X8}", iOptValue, GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}


		hrErr = Service::NetSystem->Accept(GetIOSocket(), pAcceptInfo);
		switch ((uint32_t)hrErr)
		{
		case (uint32_t)ResultCode::SUCCESS:
		case (uint32_t)ResultCode::IO_WOULDBLOCK:
		case (uint32_t)ResultCode::IO_IO_PENDING:
			// succeeded
			break;
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
			//SFLog(Net, Info, "TCP accept busy, try again {0} accepts are queued", m_PendingAccept.load(std::memory_order_relaxed));
		default:
			hr = hrErr;
			break;
		}

	Proc_End:

		if (hr.IsFailure())
		{
			Util::SafeDelete(pAcceptInfo);
		}

		return hr;
	}



	// Pending recv New one
	Result SocketIOTCP::PendingRecv(IOBUFFER_READ *pRecvBuffer)
	{
		Result hr = ResultCode::SUCCESS;
		m_LastPendingRecvResult = ResultCode::SUCCESS;

		if (!NetSystem::IsProactorSystem())
			return ResultCode::SUCCESS;

		//if (GetConnectionState() == ConnectionState::DISCONNECTED)
		//	return ResultCode::SUCCESS;

		//// On client side, we need to check writable status by calling connect again
		//if (m_IsClientConnection && !m_IsTCPSocketConnectionEstablished && GetConnectionState() == ConnectionState::CONNECTING)
		//{
		//	m_IsTCPSocketConnectionEstablished = Connect();
		//	if (!m_IsTCPSocketConnectionEstablished)
		//		return ResultCode::SUCCESS;
		//}

		if (GetPendingRecvCount() > 0)
			return ResultCode::SUCCESS;

		pRecvBuffer = new IOBUFFER_READ;
		hr = pRecvBuffer->SetPendingTrue();
		if (hr.IsFailure())
			return ResultCode::SUCCESS;

		IncPendingRecvCount();

		hr = Recv(pRecvBuffer);
		if (!hr.IsSuccess() && hr != ResultCode::IO_IO_PENDING && hr != ResultCode::IO_TRY_AGAIN)
		{
			SFLog(Net, Debug3, "Pending Recv failed, CID:{0}, pending:{1}, hr:{2}", GetUserSocketID(), GetPendingRecvCount(), hr);
			//Assert(false);
			// Failed, release pending flag
			pRecvBuffer->SetPendingFalse();
			DecPendingRecvCount();
			delete (pRecvBuffer);
		}
		else
		{
			SFLog(Net, Debug5, "Pending Recv CID:{0}, pending:{1}, hr:{2:X8}", GetUserSocketID(), GetPendingRecvCount(), hr);
		}

		return hr;
	}


	// Recv handling for TCP socket
	Result SocketIOTCP::Recv(IOBUFFER_READ* pIOBuffer)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;

		netChkPtr(pIOBuffer);
		pIOBuffer->SetupRecvTCP(GetUserSocketID());

		hrErr = Service::NetSystem->Recv(this, pIOBuffer);
		hr = hrErr;
		switch ((uint32_t)hrErr)
		{
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			SFLog(Net, Warning, "TCP Read failed, Connection Reset CID:{0}, err:{1:X8}, pending:{2}", GetUserSocketID(), hrErr, GetPendingRecvCount());
			break;
		default:
			//SFLog(Net, Error, "TCP Recv failed with CID {0}, err:{1:X8}", GetCID(), hrErr);
			goto Proc_End;
			break;
		case (uint32_t)ResultCode::IO_IO_PENDING:
		case (uint32_t)ResultCode::IO_WOULDBLOCK:
			// Recv is pended
			break;
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
		case (uint32_t)ResultCode::IO_NOTCONN:
			// try again
			break;
		case (uint32_t)ResultCode::SUCCESS_FALSE:
			hr = ResultCode::IO_TRY_AGAIN;
			break;
		case (uint32_t)ResultCode::SUCCESS:
			break;
		};

	Proc_End:

		return hr;
	}

	Result SocketIOTCP::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;

		netChkPtr(pSendBuffer);

		hrErr = Service::NetSystem->Send(this, pSendBuffer);
		hr = hrErr;
		switch ((uint32_t)hrErr)
		{
		case (uint32_t)ResultCode::SUCCESS:
		case (uint32_t)ResultCode::IO_IO_PENDING:
            // consider them as success
            hr = ResultCode::SUCCESS;
            break;
		case (uint32_t)ResultCode::IO_WOULDBLOCK:
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
            if (NetSystem::IsProactorSystem())
            {
                // those are success with proactor system. The system will buffer the request and give notification when it is done
                hr = ResultCode::SUCCESS;
            }
            else
            {
                // Partial success. Reactor pattern doesn't have internal buffering. You need to retry whole or partial send again
                hr = ResultCode::IO_TRY_AGAIN;
            }
			break;
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			// keep those errors for later handling
			break;
		default:
			hr = ResultCode::IO_IO_SEND_FAIL;
			//netErr(ResultCode::IO_IO_SEND_FAIL);
			break;
		};

	Proc_End:

		switch ((uint32_t)hr)
		{
		case (uint32_t)ResultCode::SUCCESS:
		case (uint32_t)ResultCode::SUCCESS_FALSE:
		case (uint32_t)ResultCode::IO_IO_SEND_FAIL:
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
			break;
		default:
			SFLog(Net, Error, "TCP Send Failed, CID:{0}, sock:{3},  err:{1:X8}, hr:{2:X8}", GetUserSocketID(), hrErr, hr, GetIOSocket());
			break;
		}


		return hr;
	}

} // namespace Net
} // namespace SF


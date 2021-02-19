////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Network system for IOCP. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Container/SFSpinSharedBuffer.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Util/SFToString.h"

#include "Net/SFNetSystem.h"
#include "Net/SFNetSocket.h"
#include "Net/SFNetSystem_WinIOCP.h"


#if SF_PLATFORM == SF_PLATFORM_WINDOWS



namespace SF {
namespace Net {


	Result GetLastNetSystemResult()
	{
		int ierr = WSAGetLastError();
		switch (ierr)
		{
		case 0: return ResultCode::SUCCESS;
		case WSAEINTR: return ResultCode::INTERRUPTED_SYSCALL;
		case WSAEBADF: return ResultCode::INVALID_FILE_HANDLE;
		case WSAEACCES: return ResultCode::NO_PERMITION;
		case WSAEFAULT: return ResultCode::INVALID_POINTER;
		case WSAEINVAL: return ResultCode::INVALID_ARG;
		case WSAEMFILE: return ResultCode::TOO_MANY_OPENED_FILE;
		case WSAEWOULDBLOCK: return ResultCode::IO_WOULDBLOCK;
		case WSAEINPROGRESS: return ResultCode::IO_INPROGRESS;
		case WSAEALREADY: return ResultCode::IO_ALREADY;
		case WSAENOTSOCK: return ResultCode::IO_NOTSOCK;
		case WSAEDESTADDRREQ: return ResultCode::IO_DESTADDRREQ;
		case WSAENETDOWN: return ResultCode::IO_NETDOWN;
		case WSAENETUNREACH: return ResultCode::IO_NETUNREACH;
		case WSAENETRESET: return ResultCode::IO_NETRESET;
		case WSAECONNABORTED: return ResultCode::IO_CONNABORTED;
		case WSAECONNRESET: return ResultCode::IO_CONNRESET;
		case WSAENOBUFS: return ResultCode::IO_NOBUFS;
		case WSAEISCONN: return ResultCode::IO_ISCONN;
		case WSAENOTCONN: return ResultCode::IO_NOTCONN;
		case WSAESHUTDOWN: return ResultCode::IO_SHUTDOWN;
		case WSAETOOMANYREFS: return ResultCode::IO_TOOMANYREFS;
		case WSAETIMEDOUT: return ResultCode::IO_TIMEDOUT;
		case WSAECONNREFUSED: return ResultCode::IO_CONNECTION_REFUSSED;
		case WSAELOOP: return ResultCode::IO_LOOP;
		case WSAENAMETOOLONG: return ResultCode::IO_NAMETOOLONG;

		case WSAEAFNOSUPPORT: return ResultCode::IO_INVALID_ADDRESS;
		case WSAEHOSTDOWN: return ResultCode::IO_HOSTDOWN;
		case WSAEHOSTUNREACH: return ResultCode::IO_HOSTUNREACH;
		case WSAENOTEMPTY: return ResultCode::IO_NOTEMPTY;
		case WSAEPROCLIM: return ResultCode::IO_PROCLIM;
		case WSASYSNOTREADY: return ResultCode::IO_SYSNOTREADY;
		case WSAVERNOTSUPPORTED: return ResultCode::IO_VERNOTSUPPORTED;
		case WSANOTINITIALISED: return ResultCode::IO_NOTINITIALISED;
		case WSAEDISCON: return ResultCode::IO_DISCON;
		case WSASYSCALLFAILURE: return ResultCode::IO_SYSCALLFAILURE;
		case WSAHOST_NOT_FOUND: return ResultCode::IO_HOST_NOT_FOUND;

		case WSATRY_AGAIN: return ResultCode::IO_TRY_AGAIN;
		case WSA_SECURE_HOST_NOT_FOUND: return ResultCode::IO_SECURE_HOST_NOT_FOUND;
		case WSA_IO_PENDING: return ResultCode::IO_IO_PENDING;
		case WSAEPROTOTYPE: return ResultCode::IO_PROTOTYPE;
		case WSAENOPROTOOPT: return ResultCode::IO_NOPROTOOPT;
		case WSAEOPNOTSUPP: return ResultCode::IO_OPNOTSUPP;
		case WSAEADDRINUSE: return ResultCode::IO_ADDRINUSE;
		default:
			SFLog(Net, Warning, "Unknown Winsock error {0}", ierr);
			return ResultCode::UNEXPECTED;
		}
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//


	// Clear Buffer
	void IOBUFFER::ClearBuffer()
	{
		if( hEvent != WSA_INVALID_EVENT )
			WSACloseEvent( hEvent );
		hEvent = WSA_INVALID_EVENT;
	}



	IOBUFFER_RWBASE::IOBUFFER_RWBASE()
	{
		memset(this, 0, sizeof(IOBUFFER_RWBASE));
	}
	



	IOBUFFER_WRITE::IOBUFFER_WRITE()
	{
		//memset( this, 0, sizeof(IOBUFFER_WRITE) );
		pSendBuff = nullptr;
		hEvent = WSA_INVALID_EVENT;
	}

	IOBUFFER_WRITE::~IOBUFFER_WRITE()
	{
		ClearBuffer();
	}


	IOBUFFER_READ::IOBUFFER_READ()
	{
		memset( this, 0, sizeof(IOBUFFER_READ) );
		hEvent = WSA_INVALID_EVENT;

		iSockLen = sizeof(sockaddr_storage);
	}

	IOBUFFER_READ::~IOBUFFER_READ()
	{
		ClearBuffer();
	}

	Result IOBUFFER_READ::SetPendingTrue()
	{
		bool expected = false;
		while (!bIsPending.compare_exchange_weak(expected, true, std::memory_order_seq_cst))
		{
			if (expected == true)
			{
				Assert(false);
				return ResultCode::FAIL;
			}

			expected = false;
		}
		return ResultCode::SUCCESS;
	}

	Result IOBUFFER_READ::SetPendingFalse()
	{
		bool expected = true;
		while (!bIsPending.compare_exchange_weak(expected, false, std::memory_order_seq_cst))
		{
			if (expected == true)
			{
				Assert(false);
				return ResultCode::FAIL;
			}

			expected = false;
		}
		return ResultCode::SUCCESS;
	}


	IOBUFFER_ACCEPT::IOBUFFER_ACCEPT()
		//:pConnection(nullptr)
	{
		memset( this, 0, sizeof(IOBUFFER_ACCEPT) );
		hEvent = WSA_INVALID_EVENT;
	}


	IOBUFFER_ACCEPT::~IOBUFFER_ACCEPT()
	{
		ClearBuffer();
	}







	////////////////////////////////////////////////////////////////////////////////
	//
	//	IOCP System
	//

	namespace IOCPSystem
	{


		////////////////////////////////////////////////////////////////////////////////
		//
		//	IOCP thread worker
		//


		IOCPWorker::IOCPWorker()
			: Thread("IOCPWorker")
		{
		}

		IOCPWorker::~IOCPWorker()
		{
		}


		void IOCPWorker::Run()
		{
			Result hr = ResultCode::SUCCESS;
			BOOL bResult;
			DWORD dwTransferred = 0;
			IOBUFFER *pOverlapped = nullptr;
			OVERLAPPED *pOverlappedSys = nullptr;
			ULONG_PTR ulKey = 0;
			int iErr = 0;
			int iLastError;

			while(!CheckKillEvent(DurationMS(0)))
			{
				dwTransferred = 0;
				pOverlapped = nullptr;
				pOverlappedSys = nullptr;
				ulKey = 0;
				iErr = 0;
				iLastError = 0;
				hr = ResultCode::SUCCESS;


				// Getting IOCP status
				bResult = GetQueuedCompletionStatus( m_hIOCP, &dwTransferred, (PULONG_PTR)&ulKey, &pOverlappedSys, INFINITE );
				pOverlapped = (IOBUFFER*)pOverlappedSys;

				// If End of IOCP signaled
				if( pOverlappedSys == nullptr || pOverlapped == nullptr )
				{
					// Release
					if (ulKey != 0)
					{
						SocketIO *pCallback = (SocketIO*)ulKey;
						assert(pCallback->GetPendingRecvCount() == 0 && pCallback->GetPendingSendCount() == 0);
						pCallback->OnIOUnregistered();
					}
					continue;
				}


				// Error mapping
				if( !bResult )
				{
					iLastError = GetLastError();
					hr = HRESULT_FROM_WIN32(iLastError);

					switch( iLastError )
					{
					case WSAECONNRESET:
					case WSAENOTSOCK:
					case ERROR_CONNECTION_ABORTED:
					case ERROR_HOST_UNREACHABLE:
					case ERROR_PROTOCOL_UNREACHABLE:
					case ERROR_PORT_UNREACHABLE:
					case ERROR_NETNAME_DELETED:
						hr = ResultCode::IO_CONNECTION_CLOSED;
						break;
					case ERROR_OPERATION_ABORTED:
						SFLog(Net, Info, "IOCP Operation aborted" );
						hr = ResultCode::IO_IO_ABORTED;
						break;
					default:
						SFLog(Net, Error, "IOCP Operation failed iErr={0}, hr={1:X8}", iLastError, hr );
						break;
					};
				}

				// Operation
				switch( pOverlapped->Operation )
				{
				case IOBUFFER_OPERATION::OP_TCPACCEPT:
					{
						IOBUFFER_ACCEPT *pAcceptOver = (IOBUFFER_ACCEPT*)pOverlapped;
						SocketIO *pCallback = (SocketIO*)ulKey;
						hr = pCallback->OnIOAccept( hr, pAcceptOver );
					}
					break;
				case IOBUFFER_OPERATION::OP_TCPWRITE:
				case IOBUFFER_OPERATION::OP_UDPWRITE:
					{
						IOBUFFER_WRITE *pIOBuffer = (IOBUFFER_WRITE*)pOverlapped;
						SocketIO *pCallback = (SocketIO*)ulKey;
						hr = pCallback->OnIOSendCompleted( hr, pIOBuffer );
					}
					break;
				case IOBUFFER_OPERATION::OP_TCPREAD:
				case IOBUFFER_OPERATION::OP_UDPREAD:
					if( ulKey ) // TCP operation
					{
						IOBUFFER_READ *pIOBuffer = (IOBUFFER_READ*)pOverlapped;
						SocketIO *pCallback = (SocketIO*)ulKey;
						pIOBuffer->TransferredSize = dwTransferred;
						SFLog(Net, Debug3, "Recv From:{0}, To:{1}, Size{2}", pIOBuffer->NetAddr.From, pIOBuffer->NetAddr.To, pIOBuffer->TransferredSize);
						hr = pCallback->OnIORecvCompleted( hr, pIOBuffer );
						pIOBuffer = nullptr;
						pOverlapped = nullptr;
					}
					else
					{
						AssertRel(!"Invalid Key at IOCP");
					}
					break;
				default:
					SFLog(Net, Error, "IOCP Invalid Overlapped Operation" );
					break;
				};


			} // while(1)

		}








		//////////////////////////////////////////////////////////////////
		//
		//	network IOCP System
		//

	


		IOCPSystem::IOCPSystem(IHeap& memoryManager)
			: m_Heap(memoryManager)
		{
		}

		IOCPSystem::~IOCPSystem()
		{
		}

		// Initialize IOCP
		Result IOCPSystem::Initialize( uint uiNumIOCPThread )
		{
			Result hr = ResultCode::SUCCESS;


			auto refCount = m_RefCount.fetch_add(1, std::memory_order_relaxed);

			if( GetNativeIOSystemHandle() != INVALID_NATIVE_HANDLE_VALUE )
			{
				return ResultCode::SUCCESS;// already initialized
			}

			WSADATA wsaData;
			int iErr = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iErr != 0)
			{
				SFLog(Net, Error, "Can't Initialize Winsock DLL err={0}", iErr);
				return iErr;
			}


			SYSTEM_INFO sysInfo;
			memset( &sysInfo, 0, sizeof(sysInfo) );
			GetSystemInfo( &sysInfo );

			// Correct if Incorrect thread count specified
			if( uiNumIOCPThread < 1 ) uiNumIOCPThread = 1;
			if( uiNumIOCPThread > (sysInfo.dwNumberOfProcessors*2) ) uiNumIOCPThread = sysInfo.dwNumberOfProcessors*2;


			// Create IOCP port
			auto nativeIOHandle = CreateIoCompletionPort( INVALID_NATIVE_HANDLE_VALUE, NULL, 0, 0 );
			if(nativeIOHandle == INVALID_NATIVE_HANDLE_VALUE )
				netChk(GetLastResultCode());

			SetNativeIOSystemHandle(nativeIOHandle);

			m_pWorkers.resize( uiNumIOCPThread );
			for( uint iThread = 0; iThread < uiNumIOCPThread; iThread++ )
			{
				m_pWorkers[iThread] = new(GetHeap()) IOCPWorker;
				m_pWorkers[iThread]->SetIOCPHandle(nativeIOHandle);
				m_pWorkers[iThread]->Start();
			}

			SFLog(Net, Info, "IOCP system started" );

		Proc_End:

			if( !(hr) )
			{
				Terminate();
			}
			return hr;
		}

		// Close IOCP
		void IOCPSystem::Terminate()
		{
			Result hr = ResultCode::SUCCESS;

			CounterType lCount = m_RefCount.fetch_sub(1, std::memory_order_relaxed) - 1;

			if( lCount > 0 )
				return;

			std::for_each(m_pWorkers.begin(), m_pWorkers.end(), [](IOCPWorker* pThread)
			{
				pThread->SetKillEvent();
			});

			// Stimulate threads
			if(GetNativeIOSystemHandle() != INVALID_NATIVE_HANDLE_VALUE )
			{
				// Send IOCP close signal
				if( !PostQueuedCompletionStatus(GetNativeIOSystemHandle(), 0, 0, NULL ) )
					netErr( GetLastResultCode() );

				CloseHandle(GetNativeIOSystemHandle());
				SetNativeIOSystemHandle(INVALID_NATIVE_HANDLE_VALUE);
			}

			// kill threads
			if( m_pWorkers.size() )
			{
				std::for_each( m_pWorkers.begin(), m_pWorkers.end(), [&]( IOCPWorker* pThread )
				{
					pThread->Stop( true );
					IHeap::Delete(pThread);
				});


				m_pWorkers.clear();
				m_pWorkers.shrink_to_fit();
			}

		Proc_End:

			if(GetNativeIOSystemHandle() != INVALID_NATIVE_HANDLE_VALUE)
			{
				// Send IOCP close signal
				CloseHandle(GetNativeIOSystemHandle());
				SetNativeIOSystemHandle(INVALID_NATIVE_HANDLE_VALUE);

				WSACleanup();
			}

			SFLog(Net, Info, "IOCP system closed" );

			return;
		}


		




	}; // namespace IOCPSystem







	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network system
	//




	WriteBufferQueue* NetSystem::GetWriteBufferQueue()
	{
		return nullptr;
	}


	///////////////////////////////////////////////////////////////////////////////
	// Socket handling 

	//Result RegisterSharedSocket(SockType sockType, SocketIO* cbInstance)
	//{
	//	Result hr = ResultCode::SUCCESS;

	//	netChkPtr(cbInstance);
	//	Assert(cbInstance->GetIOSocket() != INVALID_SOCKET);

	//	//netChk(EPOLLSystem::GetSystem().RegisterSharedSocket(sockType, cbInstance));

	//Proc_End:

	//	return hr;
	//}

	Result NetSystem::SetupCommonSocketOptions(SockType sockType, SockFamily sockFamily, SF_SOCKET socket, bool acceptedSocket)
	{
		Result hr;

		int iOptValue = m_RecvBufferSize;
		if (setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *)&iOptValue, sizeof(iOptValue)) < 0)
		{
			hr = GetLastNetSystemResult();
			SFLog(Net, Error, "Failed to change socket option SO_RCVBUF={0}, err={1}", iOptValue, hr);
			return hr;
		}

		iOptValue = m_SendBufferSize;
		if (setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *)&iOptValue, sizeof(iOptValue)) < 0)
		{
			hr = GetLastNetSystemResult();
			SFLog(Net, Error, "Failed to change socket option SO_SNDBUF={0}, err={1}", iOptValue, hr);
			return hr;
		}

		if (sockType == SockType::Stream)
		{
			iOptValue = 1;
			if (setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&iOptValue, sizeof(iOptValue)) < 0)
			{
				hr = GetLastNetSystemResult();
				SFLog(Net, Error, "Failed to change socket option TCP_NODELAY={0}, err={1}", iOptValue, hr);
				return hr;
			}
		}

		if (!acceptedSocket && sockFamily == SockFamily::IPV6)
		{
			iOptValue = 0;
			if (setsockopt(socket, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&iOptValue, sizeof(iOptValue)) < 0)
			{
				hr = GetLastNetSystemResult();
				SFLog(Net, Error, "Failed to change socket option IPV6_V6ONLY = {0}, err = {1}", iOptValue, hr);
				netCheck(hr);
			}
		}

		u_long iMode = true;// non block
		iMode = true;
		if (ioctlsocket(socket, FIONBIO, &iMode) < 0)
		{
			hr = GetLastNetSystemResult();
			SFLog(Net, Error, "Failed to change socket IO Mode to {0},  err = {1}", (uint32_t)iMode, hr);
			netCheck(hr);
		}

		return hr;
	}

	Result NetSystem::RegisterSocket(SocketIO* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;


		if (!CreateIoCompletionPort((HANDLE)cbInstance->GetIOSocket(), GetNetIOSystem().GetNativeIOSystemHandle(), (ULONG_PTR)cbInstance, 0))
		{
			hr = GetLastResultCode();
			SFLog(Net, Error, "Registering socket to IOCP is Failed, hr = {0:X8}", hr);
			netErr(ResultCode::UNEXPECTED);
		}

		cbInstance->OnIORegistered();

	Proc_End:

		return hr;
	}

	Result NetSystem::UnregisterSocket(SocketIO* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;

		//if (!PostQueuedCompletionStatus(GetNetIOSystem().GetNativeIOSystemHandle(), 0, (ULONG_PTR)cbInstance, 0))
		//{
		//	hr = GetLastResultCode();
		//	SFLog(Net, Error, "Registering socket to IOCP is Failed, hr = {0:X8}", hr);
		//	netErr(ResultCode::UNEXPECTED);
		//}

		// Just mark as unregistered
		cbInstance->OnIOUnregistered();

	Proc_End:

		return hr;
	}

	SF_SOCKET NetSystem::Socket(SockFamily domain, SockType type)
	{
		if (type == SockType::Stream)
		{
			return WSASocket(ToSockValue(domain), ToSockValue(type), IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
		}
		else
		{
			return WSASocket(ToSockValue(domain), ToSockValue(type), IPPROTO_UDP, nullptr, 0, WSA_FLAG_OVERLAPPED);
		}
	}

	void NetSystem::CloseSocket(SF_SOCKET sock)
	{
		//shutdown(sock, SHUT_RDWR);
		closesocket(sock);
	}


	Result NetSystem::Accept(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept)
	{
		Result hr = ResultCode::SUCCESS;

		netChkPtr(pAccept);

		if (!AcceptEx(sockListen, pAccept->sockAccept,
			pAccept->pAcceptInfo, 0,
			sizeof(sockaddr_storage), sizeof(sockaddr_storage),
			&pAccept->dwByteReceived, pAccept))
		{
			Result iErr = GetLastNetSystemResult();
			switch ((int32_t)iErr)
			{
			case (uint32_t)ResultCode::IO_NOTSOCK:// server closing or not initialized
				SFLog(Net, Error, "TCP Abnormal accept, Not socked {0:X8}", iErr);
				netErr(iErr);
				break;
			case (uint32_t)ResultCode::IO_IO_PENDING:
				//SFLog(Net, Info, "TCP accept pending {0} queued", m_pAcceptBuffer->GetUsedBufferCount());
				break;
			default:
				SFLog(Net, Error, "TCP Abnormal accept, err:{0:X8}", iErr);
				netErr(iErr);
				break;
			};
		}
		else
		{
			SFLog(Net, Error, "TCP Abnormal accept err={0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}


	Proc_End:

		return hr;
	}

	Result NetSystem::HandleAcceptedSocket(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept, sockaddr_storage& remoteAddr)
	{
		int iLenLocalAddr = 0, iLenRemoteAddr = 0;
		sockaddr_storage *pLocalAddr = nullptr, *pRemoteAddr = nullptr;

		if (setsockopt(pAccept->sockAccept, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char *)&sockListen, sizeof(SF_SOCKET)) == SOCKET_ERROR)
		{
			SFLog(Net, Info, "Failed set socket option SO_UPDATE_ACCEPT_CONTEXT err:{0:X8}", GetLastNetSystemResult());
			return ResultCode::FAIL;
		}


		GetAcceptExSockaddrs( (void*)pAccept->pAcceptInfo,
								0,
								sizeof(sockaddr_storage),
								sizeof(sockaddr_storage),
								(SOCKADDR**)&pLocalAddr, 
								&iLenLocalAddr, 
								(SOCKADDR**)&pRemoteAddr, 
								&iLenRemoteAddr );

		remoteAddr = *pRemoteAddr;

		return ResultCode::SUCCESS;
	}


	Result NetSystem::Recv(SF_SOCKET sock, IOBUFFER_READ* pBuffer)
	{
		INT iErr = 0;
		iErr = WSARecv(sock, &pBuffer->wsaBuff, 1, &pBuffer->dwNumberOfByte, &pBuffer->dwFlags, pBuffer, NULL);
		if (iErr == SOCKET_ERROR)
		{
			return GetLastNetSystemResult();
		}

		return ResultCode::SUCCESS;
	}

	Result NetSystem::RecvFrom(SF_SOCKET sock, IOBUFFER_READ* pBuffer)
	{
		INT iErr = 0;
		iErr = WSARecvFrom(sock, &pBuffer->wsaBuff, 1, NULL, &pBuffer->dwFlags, (sockaddr*)&pBuffer->NetAddr.From, &pBuffer->iSockLen, pBuffer, NULL);
		if (iErr == SOCKET_ERROR)
		{
			return GetLastNetSystemResult();
		}

		return ResultCode::SUCCESS;
	}

	Result NetSystem::Send(SF_SOCKET sock, IOBUFFER_WRITE* pBuffer)
	{
		INT iErr = WSASend(sock, &pBuffer->wsaBuff, 1, nullptr, 0, pBuffer, NULL);
		if (iErr == SOCKET_ERROR)
		{
			return GetLastNetSystemResult();
		}

		return ResultCode::SUCCESS;
	}

	Result NetSystem::SendTo(SF_SOCKET sock, IOBUFFER_WRITE* pBuffer)
	{
		const sockaddr_storage& dstAddress = pBuffer->NetAddr.To;
		INT iErr = WSASendTo(sock, &pBuffer->wsaBuff, 1, nullptr, 0, 
			(sockaddr*)&dstAddress, GetSockAddrSize(dstAddress),
			pBuffer, NULL);

		if (iErr == SOCKET_ERROR)
		{
			return GetLastNetSystemResult();
		}

		return ResultCode::SUCCESS;
	}





} // namespace Net
} // namespace SF


#else
void Dummp_NetSystem_WinIOCP() {}
#endif // SF_PLATFORM == SF_PLATFORM_WINDOWS

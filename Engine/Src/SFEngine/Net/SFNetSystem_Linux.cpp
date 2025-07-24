////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2015 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Network system linux shared. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Multithread/SFSystemSynchronization.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetSocket.h"
#include "Util/SFLog.h"


#if SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID | SF_PLATFORM == SF_PLATFORM_IOS


#include "Net/SFNetSystem_EPOLL.h"
#include "Net/SFNetSystem_KQUEUE.h"


// IOS doesnt' support 
#if SF_PLATFORM == SF_PLATFORM_IOS
#define MSG_NOSIGNAL 0
#endif



namespace SF {
namespace Net {

	Result GetLastNetSystemResult()
	{
		int ierr = errno;
		switch (ierr)
		{
		case 0: return ResultCode::SUCCESS;
		case EINTR: return ResultCode::INTERRUPTED_SYSCALL;
		case EBADF: return ResultCode::INVALID_FILE_HANDLE;
		case EACCES: return ResultCode::NO_PERMITION;
		case EFAULT: return ResultCode::INVALID_POINTER;
		case EINVAL: return ResultCode::INVALID_ARG;
		case EMFILE: return ResultCode::TOO_MANY_OPENED_FILE;
		case EWOULDBLOCK: return ResultCode::IO_WOULDBLOCK; // Linux epoll
#if EWOULDBLOCK != EAGAIN
		case EAGAIN: return ResultCode::IO_TRY_AGAIN;
#endif
		case EINPROGRESS: return ResultCode::IO_INPROGRESS;
		case EALREADY: return ResultCode::IO_ALREADY;
		case ENOTSOCK: return ResultCode::IO_NOTSOCK;
		case EDESTADDRREQ: return ResultCode::IO_DESTADDRREQ;
		case ENETDOWN: return ResultCode::IO_NETDOWN;
		case ENETUNREACH: return ResultCode::IO_NETUNREACH;
		case ENETRESET: return ResultCode::IO_NETRESET;
		case ECONNABORTED: return ResultCode::IO_CONNABORTED;
		case ECONNRESET: return ResultCode::IO_CONNRESET;
		case ENOBUFS: return ResultCode::IO_NOBUFS;
		case EISCONN: return ResultCode::IO_ISCONN;
		case ENOTCONN: return ResultCode::IO_NOTCONN;
		case ESHUTDOWN: return ResultCode::IO_SHUTDOWN;
		case EPIPE: return ResultCode::INVALID_PIPE;
		case ETOOMANYREFS: return ResultCode::IO_TOOMANYREFS;
		case ETIMEDOUT: return ResultCode::IO_TIMEDOUT;
		case ECONNREFUSED: return ResultCode::IO_CONNECTION_REFUSSED;
		case ELOOP: return ResultCode::IO_LOOP;
		case ENAMETOOLONG: return ResultCode::IO_NAMETOOLONG;

		case EHOSTDOWN: return ResultCode::IO_HOSTDOWN;
		case EHOSTUNREACH: return ResultCode::IO_HOSTUNREACH;
		case ENOTEMPTY: return ResultCode::IO_NOTEMPTY;
		case EPROTO: return ResultCode::IO_PROTO;
		case EPROTOTYPE: return ResultCode::IO_PROTOTYPE;
		case ENOPROTOOPT: return ResultCode::IO_NOPROTOOPT;
#if SF_PLATFORM != SF_PLATFORM_IOS
		case ENONET: return ResultCode::IO_NONET;
#endif
		case EOPNOTSUPP: return ResultCode::IO_OPNOTSUPP;
		case EADDRINUSE: return ResultCode::IO_ADDRINUSE;
			//case EPROCLIM: return ResultCode::IO_PROCLIM;
			//case SYSNOTREADY: return ResultCode::IO_SYSNOTREADY;
			//case VERNOTSUPPORTED: return ResultCode::IO_VERNOTSUPPORTED;
			//case NOTINITIALISED: return ResultCode::IO_NOTINITIALISED;
			//case EDISCON: return ResultCode::IO_DISCON;
			//case SYSCALLFAILURE: return ResultCode::IO_SYSCALLFAILURE;
			//case HOST_NOT_FOUND: return ResultCode::IO_HOST_NOT_FOUND;

			//case TRY_AGAIN: return ResultCode::IO_TRY_AGAIN;
			//case _SECURE_HOST_NOT_FOUND: return ResultCode::IO_SECURE_HOST_NOT_FOUND;
			//case WSA_IO_PENDING: return ResultCode::IO_IO_PENDING;
		default:
			SFLog(Net, Error, "Unknown sock error {0}", ierr);
			return GetLastResultCode();
		}
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//


	// Clear Buffer
	void IOBUFFER::ClearBuffer()
	{
	}



	IOBUFFER_RWBASE::IOBUFFER_RWBASE()
	{
		memset(this, 0, sizeof(IOBUFFER_RWBASE));
	}




	IOBUFFER_WRITE::IOBUFFER_WRITE()
	{
		SockWrite = INVALID_SOCKET;
        SendBufferSize = 0;
		pRawSendBuffer = nullptr;
	}

	IOBUFFER_WRITE::~IOBUFFER_WRITE()
	{
		ClearBuffer();
	}


	IOBUFFER_READ::IOBUFFER_READ()
	{
		memset(this, 0, sizeof(IOBUFFER_READ));
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
				return ResultCode::FAIL;
			}

			expected = false;
		}
		return ResultCode::SUCCESS;
	}


	IOBUFFER_ACCEPT::IOBUFFER_ACCEPT()
	{
		memset(this, 0, sizeof(IOBUFFER_ACCEPT));
	}


	IOBUFFER_ACCEPT::~IOBUFFER_ACCEPT()
	{
		ClearBuffer();
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	socket network system
	//


	//WriteBufferQueue* NetSystem::GetWriteBufferQueue()
	//{
	//	return GetNetIOSystem().GetWriteBufferQueue();
	//}


	///////////////////////////////////////////////////////////////////////////////
	// Socket handling 

	Result NetSystem::SetupCommonSocketOptions(SocketType sockType, SockFamily sockFamily, SF_SOCKET socket, bool acceptedSocket)
	{
		Result hr;
		int32_t iOptValue;

		iOptValue = m_RecvBufferSize;
		if (setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *)&iOptValue, sizeof(iOptValue)) < 0)
		{
			SFLog(Net, Error, "Failed to change socket option SO_RCVBUF={0}, err={1}", iOptValue, GetLastNetSystemResult());
			return ResultCode::UNEXPECTED;
		}

		iOptValue = m_SendBufferSize;
		if (setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *)&iOptValue, sizeof(iOptValue)) < 0)
		{
			SFLog(Net, Error, "Failed to change socket option SO_SNDBUF={0}, err={1}", iOptValue, GetLastNetSystemResult());
			return ResultCode::UNEXPECTED;
		}

		if (sockType == SocketType::Stream)
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
			iOptValue = FALSE;
			if (setsockopt(socket, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&iOptValue, sizeof(iOptValue)) < 0)
			{
				SFLog(Net, Error, "Failed to change socket option IPV6_V6ONLY = {0}, err = {1}", iOptValue, GetLastNetSystemResult());
				netCheck(ResultCode::UNEXPECTED);
			}
		}

		return hr;
	}

	Result NetSystem::RegisterSocket(SocketIO* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;
		//int iOptValue;

		netChkPtr(cbInstance);
		Assert(cbInstance->GetIOSocket() != INVALID_SOCKET);

		cbInstance->OnIORegistered();


		netChk(GetNetIOSystem().MakeSocketNonBlocking(cbInstance->GetIOSocket()));
		netChk(GetNetIOSystem().RegisterToNETIO(cbInstance));


	Proc_End:

		if (!hr.IsSuccess() && cbInstance != nullptr)
		{
			cbInstance->OnIOUnregistered();
		}

		return hr;
	}

	Result NetSystem::UnregisterSocket(SocketIO* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;

		netChkPtr(cbInstance);
		//Assert(cbInstance->GetIOSocket() != INVALID_SOCKET);

        SFLog(Net, Info, "NetSystem::UnregisterSocket sock:{0}", cbInstance->GetIOSocket());

        netChk(GetNetIOSystem().UnregisterFromNETIO(cbInstance));

		cbInstance->OnIOUnregistered();

	Proc_End:

		return hr;
	}

	//Result RegisterSharedSocket(SocketType sockType, SocketIO* cbInstance)
	//{
	//	Result hr = ResultCode::SUCCESS;

	//	netChkPtr(cbInstance);
	//	Assert(cbInstance->GetIOSocket() != INVALID_SOCKET);

	//	netChk(GetNetIOSystem().RegisterSharedSocket(sockType, cbInstance));

	//Proc_End:

	//	return hr;
	//}


	SF_SOCKET NetSystem::Socket(SockFamily domain, SocketType type)
	{
		return socket(ToSockValue(domain), ToSockValue(type), ToSockProto(type));
	}

	void NetSystem::CloseSocket(SF_SOCKET sock)
	{
		shutdown(sock, SHUT_RDWR);
		close(sock);
		SFLog(Net, Info, "CloseSocket sock:{0}", sock);
	}

	Result NetSystem::Accept(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept)
	{
		Result hr = ResultCode::SUCCESS;
		socklen_t len = sizeof(pAccept->sockAddr);

		netChkPtr(pAccept);

		// Android 19 doesn't support accept4
#ifdef SOCK_NONBLOCK
		pAccept->sockAccept = accept4(sockListen, (sockaddr*)&pAccept->sockAddr, &len, SOCK_NONBLOCK);
#else
		pAccept->sockAccept = accept(sockListen, (sockaddr*)&pAccept->sockAddr, &len);
#endif

		if (len == 0)
		{
			netErr(ResultCode::UNEXPECTED);
		}

		if(pAccept->sockAccept < 0)
		{
			Result err = GetLastNetSystemResult();
			switch ((uint32_t)err)
			{
			case (uint32_t)ResultCode::IO_WOULDBLOCK:
			case (uint32_t)ResultCode::IO_IO_PENDING:
				return hr = err;

			case (uint32_t)ResultCode::IO_TRY_AGAIN:
				// Nothing to accept for now
				return hr = err;

			case (uint32_t)ResultCode::IO_NETDOWN:
			case (uint32_t)ResultCode::IO_PROTO:
			case (uint32_t)ResultCode::IO_NOPROTOOPT:
			case (uint32_t)ResultCode::IO_HOSTDOWN:
			case (uint32_t)ResultCode::IO_NONET:
			case (uint32_t)ResultCode::IO_HOSTUNREACH:
			case (uint32_t)ResultCode::IO_OPNOTSUPP:
			case (uint32_t)ResultCode::IO_NETUNREACH:
			case (uint32_t)ResultCode::INVALID_FILE_HANDLE:
				// silently handle them
				hr = err;
				goto Proc_End;
			}

			SFLog(Net, Error, "TCP accept failed err={0}", err);
		}


	Proc_End:

		return hr;
	}

	Result NetSystem::HandleAcceptedSocket(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept, sockaddr_storage& remoteAddr)
	{
		socklen_t len;

		unused(sockListen);

		len = sizeof remoteAddr;
		getpeername(pAccept->sockAccept, (struct sockaddr*)&remoteAddr, &len);

		return ResultCode::SUCCESS;
	}


	Result NetSystem::Recv(Net::SocketIO* sock, IOBUFFER_READ* pBuffer)
	{
		ssize_t recvSize = recv(sock->GetIOSocket(), pBuffer->GetPayloadPtr(), IOBUFFER_READ::MaxPacketSize, MSG_DONTWAIT);
		if (recvSize < 0)
		{
			return GetLastNetSystemResult();
		}

		pBuffer->TransferredSize = static_cast<uint32_t>(recvSize);
		if (recvSize == 0)
		{
			return ResultCode::SUCCESS_FALSE;
		}

		return ResultCode::SUCCESS;
	}

	Result NetSystem::RecvFrom(Net::SocketIO* sock, IOBUFFER_READ* pBuffer)
	{
		Assert(pBuffer->iSockLen == sizeof(pBuffer->NetAddr.From));

		ssize_t recvSize = recvfrom(sock->GetIOSocket(), pBuffer->GetPayloadPtr(), IOBUFFER_READ::MaxPacketSize, MSG_DONTWAIT,
			(sockaddr*)&pBuffer->NetAddr.From, &pBuffer->iSockLen);
		if (recvSize < 0)
		{
			return GetLastNetSystemResult();
		}

		pBuffer->TransferredSize = static_cast<uint32_t>(recvSize);
		if (recvSize == 0)
		{
			return ResultCode::SUCCESS_FALSE;
		}

		return ResultCode::SUCCESS;
	}

    // https://stackoverflow.com/questions/64488670/how-to-write-to-a-nonblocking-socket-when-using-epoll
    //send / to() will send as many bytes as it can, returning how many bytes it was actually able to give the kernel to send.
    //If you are using a TCP socket, call send() in a loop until EITHER all of your bytes have been sent OR EAGAIN / EWOULDBLOCK is reported.In the latter case, stop the loop and cache the remaining bytes somewhere.
    //If you are using a UDP socket, send / to() can only send whole datagrams, so don't use a loop at all, and if EAGAIN/EWOULDBLOCK is reported then cache the entire datagram.
    //Whenever epoll indicates a socket is writable, send any cached bytes / datagrams for that socket as needed, removing only successful bytes / datgrams from the cache, until EITHER the cache is cleared OR EAGAIN / EWOULDBLOCK is reported.Leave unsent bytes / datagrams in the cache.
    //Whenever you need to send new TCP bytes, or a new UDP datagram, if the socket's cache is not empty then append the bytes/datagram to the end of the cache and move on, otherwise attempt to send the bytes/datagram immediately, caching if EAGAIN/EWOULDBLOCK is reported, as described above.

    Result NetSystem::Send(Net::SocketIO* sock, IOBUFFER_WRITE* pBuffer)
	{
        Result hr;
        if (pBuffer->SendBufferSize == pBuffer->TransferredSize)
            return ResultCode::SUCCESS;

		ssize_t sentSize = send(sock->GetIOSocket(), pBuffer->pRawSendBuffer + pBuffer->TransferredSize, pBuffer->SendBufferSize - pBuffer->TransferredSize, MSG_DONTWAIT | MSG_NOSIGNAL);
		if (sentSize < 0)
		{
			return GetLastNetSystemResult();
		}

		pBuffer->TransferredSize += static_cast<uint32_t>(sentSize);
        if (pBuffer->TransferredSize >= pBuffer->SendBufferSize)
        {
            hr = ResultCode::SUCCESS;
            sock->OnIOSendCompleted(hr, pBuffer);
            return hr;
        }
        else
        {
            // We have remain data to send, try again with updated offset
            return ResultCode::IO_TRY_AGAIN;
        }
	}

	Result NetSystem::SendTo(Net::SocketIO* sock, IOBUFFER_WRITE* pBuffer)
	{
		const sockaddr_storage& dstAddress = pBuffer->NetAddr.To;
		ssize_t sendSize = sendto(sock->GetIOSocket(), pBuffer->pRawSendBuffer, pBuffer->SendBufferSize, MSG_DONTWAIT | MSG_NOSIGNAL,
			(sockaddr*)&dstAddress, GetSockAddrSize(dstAddress));

		if (sendSize < 0)
		{
			return GetLastNetSystemResult();
		}

		pBuffer->TransferredSize = static_cast<uint32_t>(sendSize);
        if (pBuffer->TransferredSize >= pBuffer->SendBufferSize)
        {
            Result hr = ResultCode::SUCCESS;
            sock->OnIOSendCompleted(hr, pBuffer);
            return hr;
        }
        else
        {
            // We have remain data to send, try again with updated offset
            return ResultCode::IO_TRY_AGAIN;
        }
	}


} // namespace Net
} // namespace SF

#else
void Dummp_NetSystem_LINUX() {}
#endif


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network Server implementation 
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
#include "Util/SFToString.h"
#include "Util/SFLog.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFConnection.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetServerUDP.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFConnectionManagerTask.h"




namespace SF {
namespace Net {






	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP Server socket IO handler class
	//



	Result ServerUDPBase::MySocketIOAdapter::OnWriteReady()
	{
		return ProcessSendQueue();
	}

	Result ServerUDPBase::MySocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
	{
		auto hr = SocketIOUDP::WriteBuffer(pSendBuffer);
		switch ((uint32_t)hr)
		{
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTCONN:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			// Send fail by connection close
			// Need to close connection
			hr = ResultCode::IO_CONNECTION_CLOSED;
			break;
		}


	//Proc_End:

		return hr;
	}

	Result ServerUDPBase::MySocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
		return m_Owner.OnIORecvCompleted(hrRes, pIOBuffer);
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP Server class
	//

	ServerUDPBase::ServerUDPBase(IHeap& heap, ServerID InServerID, NetClass localClass)
		: ServerNet(heap, InServerID, localClass)
		, m_pRecvBuffers(nullptr)
		, m_MySocketIOAdapter(this)
	{
		// We will share the write queue in net system for UDP
		//m_MySocketIOAdapter.SetWriteQueue(new WriteBufferQueue);
		SetSocketIO(&m_MySocketIOAdapter);
	}

	ServerUDPBase::~ServerUDPBase()
	{
		if( m_pRecvBuffers )
			IHeap::Delete(m_pRecvBuffers);

		if (m_MySocketIOAdapter.GetWriteQueue()) IHeap::Delete(m_MySocketIOAdapter.GetWriteQueue());
	}

	
	// Open host and start listen
	Result ServerUDPBase::HostOpen( NetClass netCls, const char *strLocalIP, uint16_t usLocalPort )
	{
		Result hr = ResultCode::SUCCESS;
		SF_SOCKET socket = INVALID_SOCKET;

		sockaddr_storage bindAddr;

		if( GetSocket() != INVALID_SOCKET )
			return ResultCode::SUCCESS;

		netChk(ServerNet::HostOpen( netCls, strLocalIP, usLocalPort ) );

		SFLog(Net, Info, "Open Server UDP Host {0}:{1}", strLocalIP, usLocalPort );

		socket = Service::NetSystem->Socket(GetLocalAddress().SocketFamily, SockType::DataGram);
		if( socket == INVALID_SOCKET )
		{
			SFLog(Net, Error, "Failed to Open Server Socket {0:X8}", GetLastNetSystemResult());
			netErr( ResultCode::UNEXPECTED );
		}

		netChk(Service::NetSystem->SetupCommonSocketOptions(SockType::DataGram, GetLocalAddress().SocketFamily, socket));

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		{
			int iOptValue = 0;
			int iOptLen = sizeof(iOptValue);
			if (getsockopt(socket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&iOptValue, &iOptLen) == SOCKET_ERROR)
			{
				SFLog(Net, Error, "Failed to get socket option SO_MAX_MSG_SIZE = {0}, err = {1:X8}", iOptValue, GetLastNetSystemResult());
				netErr(ResultCode::UNEXPECTED);
			}
			if (iOptValue < Const::PACKET_SIZE_MAX)
			{
				SFLog(Net, Warning, "Socket max packet size too small, Change to socket maximum SocketMax={0}, SvrMax={1}, err = {2:X8}", iOptValue, (uint)Const::PACKET_SIZE_MAX, GetLastNetSystemResult());
			}
		}
#endif

		//bOptValue = TRUE;
		//if( setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptValue, sizeof(bOptValue)) == SOCKET_ERROR )
		//{
		//	hr = GetLastNetSystemResult();
		//	SFLog(Net, Error, "Failed to change socket option SO_REUSEADDR = {0}, err = {1:X8}", bOptValue, hr);
		//	netErr(hr);
		//}

		// enable dual stack all the time
		//if (GetLocalAddress().SocketFamily == SockFamily::IPV6)
		//{
		//	iOptValue = FALSE;
		//	if (setsockopt(socket, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&iOptValue, sizeof(iOptValue)) == SOCKET_ERROR)
		//	{
		//		hr = GetLastNetSystemResult();
		//		SFLog(Net, Error, "Failed to change socket option IPV6_V6ONLY = {0}, err = {1:X8}", iOptValue, hr);
		//		netErr(hr);
		//	}
		//}


		GetAnyBindAddr(GetSocketAddr(), bindAddr);
		if (bind(socket, (sockaddr*)&bindAddr, GetSocketAddrSize()) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "Socket bind failed, UDP err={0:X8}", GetLastNetSystemResult() );
			netErr( ResultCode::UNEXPECTED );
		}

		m_MySocketIOAdapter.SetSocket(GetLocalAddress().SocketFamily, SockType::DataGram, socket);
		socket = INVALID_SOCKET;

		netChk(Service::NetSystem->RegisterSocket(GetSocketIO()));



		// Ready recv
		if (NetSystem::IsProactorSystem())
		{
			if (m_pRecvBuffers) IHeap::Delete(m_pRecvBuffers);
			netMem(m_pRecvBuffers = new(GetHeap()) IOBUFFER_READ[Const::SVR_NUM_RECV_THREAD]);

			for (int uiRecv = 0; uiRecv < Const::SVR_NUM_RECV_THREAD; uiRecv++)
			{
				netChk(m_MySocketIOAdapter.PendingRecv(&m_pRecvBuffers[uiRecv]));
			}
		}



	Proc_End:

		if( !hr )
			HostClose();

		if( socket != INVALID_SOCKET )
			Service::NetSystem->CloseSocket( socket );

		SFLog(Net, Info, "HostOpen {0}, hr={1:X8}", GetLocalAddress(), hr );

		return hr;
	}

	// Close host and close all connections
	Result ServerUDPBase::HostClose()
	{
		ScopeContext hr([this](Result hr) 
			{
				SFLog(Net, Info, "HostClose {0}, hr={1:X8}", GetLocalAddress(), hr);
			});

		netCheck(ServerNet::HostClose() );

		if(GetSocketIO() != nullptr)
			GetSocketIO()->CloseSocket();

		return hr;
	}




	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP Server class
	//

	ServerUDP::ServerUDP(IHeap& heap, ServerID InServerID, NetClass localClass)
		:ServerUDPBase(heap, InServerID, localClass)
	{
	}

	ServerUDP::~ServerUDP()
	{
	}

	// called when reciving message
	Result ServerUDP::OnIORecvCompleted( Result hrRes, IOBUFFER_READ* &pIOBuffer )
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Connection> pConnection;
		bool bReleaseOnFail = false;
		sockaddr_storage from;
		if (pIOBuffer != nullptr) from = pIOBuffer->NetAddr.From;
		else memset(&from, 0, sizeof(from));


		if( !( hrRes ) )
		{
			switch((uint32_t)hrRes )
			{
			case (uint32_t)ResultCode::IO_CONNECTION_CLOSED:
			case (uint32_t)ResultCode::IO_IO_ABORTED:
				if ((Service::ConnectionManager->GetConnectionByAddr(from, pConnection)))
				{
					SFLog(Net, Info, "UDP bad connection state IP:{0}", from);
				}
				hr = hrRes;
				break;
			default:
				SFLog(Net, Error, "UDP Recv Msg Failed, SvrUDP, IP:{0}, hr={1:X8}", from, hrRes );
				break;
			};
		}
		else if(pIOBuffer != nullptr)
		{
			if(pIOBuffer->TransferredSize < sizeof(Message::MessageHeader) )// invalid packet size
				goto Proc_End;

			if (!Service::ConnectionManager->GetConnectionByAddr(pIOBuffer->NetAddr.From, pConnection))
			{
				// return if we are not accepting any new connection
				if (!GetIsEnableAccept())
					return hr;

				MsgNetCtrlConnect *pNetCtrl = (MsgNetCtrlConnect*)pIOBuffer->buffer;
				if (pNetCtrl->Length == sizeof(MsgNetCtrlConnect) && pNetCtrl->msgID.IDSeq.MsgID == PACKET_NETCTRL_CONNECT.IDSeq.MsgID && pNetCtrl->rtnMsgID.ID == SF_PROTOCOL_VERSION)
				{
					Service::ConnectionManager->NewUDPAddress(GetHeap(), this, GetSocket(), GetLocalPeerInfo(), PeerInfo(pNetCtrl->Peer.PeerClass, pIOBuffer->NetAddr.From, pNetCtrl->PeerID));
				}
				else if(pNetCtrl->msgID.ID == PACKET_NETCTRL_ACK)
				{
					// ignore this packet
				}
				else
				{
					// send disconnect
					SFLog(Net, Warning, "HackWarn : Not allowered connection try from {0}", pIOBuffer->NetAddr.From );
				}

			}
			else
			{
				netChk( pConnection->OnRecv(pIOBuffer->TransferredSize, (uint8_t*)pIOBuffer->buffer) );
			}
		}

	Proc_End:

		if( pConnection != nullptr )
		{
			if( bReleaseOnFail )
			{
				pConnection->CloseConnection("OnIORecvCompleted failed");
				pConnection->Dispose();
				pConnection = nullptr;
			}
		}

		if (pIOBuffer != nullptr)
		{
			if (NetSystem::IsProactorSystem())
			{
				pIOBuffer->SetPendingFalse();
				if (hrRes != Result(ResultCode::IO_IO_ABORTED))
				{
					GetSocketIO()->PendingRecv(pIOBuffer);
				}
			}
			else
			{
				IHeap::Delete(pIOBuffer);
				pIOBuffer = nullptr;
			}
		}

		GetSocketIO()->DecPendingRecvCount();

		return hr;
	}
	
	
	


} // namespace Net
} // namespace SF


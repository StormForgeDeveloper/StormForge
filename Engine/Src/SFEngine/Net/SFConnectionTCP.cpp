////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TCP Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemory.h"
#include "SFAssert.h"
#include "Util/SFTimeUtil.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFToString.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFNetToString.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionTCP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"






// define if emulate packet loss
//#ifdef _DEBUG
//#define UDP_PACKETLOS_EMULATE
//#endif


#ifdef UDP_PACKETLOS_EMULATE
	#define UDP_PACKETLOS_RATE	5
	#define UDP_PACKETLOS_BOUND	1
#endif // #ifdef UDP_PACKETLOS_EMULATE



namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Client Mobile UDP Network connection class
	//


	ConnectionTCP::MyNetSocketIOAdapter::MyNetSocketIOAdapter(ConnectionTCP &owner)
		: SocketIOTCP(owner.GetHeap())
		, m_Owner(owner)
	{
		SetUserSocketID(m_Owner.GetCID());
	}



	// Pending recv New one
	Result ConnectionTCP::MyNetSocketIOAdapter::PendingRecv(IOBUFFER_READ *pRecvBuffer)
	{
		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return ResultCode::SUCCESS;

		// On client side, we need to check writable status by calling connect again
		if (m_Owner.m_IsClientConnection && !m_Owner.m_IsTCPSocketConnectionEstablished && m_Owner.GetConnectionState() == ConnectionState::CONNECTING)
		{
			m_Owner.m_IsTCPSocketConnectionEstablished = m_Owner.Connect() == ResultCode::SUCCESS;
			if (!m_Owner.m_IsTCPSocketConnectionEstablished)
				return ResultCode::SUCCESS;
		}

		if (!NetSystem::IsProactorSystem())
			return ResultCode::SUCCESS;

		return SocketIOTCP::PendingRecv(pRecvBuffer);
	}

	// called when receiving TCP message
	Result ConnectionTCP::MyNetSocketIOAdapter::Recv(IOBUFFER_READ* pIOBuffer)
	{
		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return ResultCode::IO_CONNECTION_CLOSED;

		Result hr = SocketIOTCP::Recv(pIOBuffer);

		switch ((uint32_t)hr)
		{
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			// Send fail by connection close
			// Need to disconnect
			CloseConnection("Recv failed with error");
			hr = ResultCode::IO_CONNECTION_CLOSED;
			break;
		};


	//Proc_End:

		return hr;
	}

	// called when receiving message
	Result ConnectionTCP::MyNetSocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
		Result hr = ResultCode::SUCCESS;

		if (pIOBuffer == nullptr)
		{
			netErr(ResultCode::UNEXPECTED);
		}

		//if (pIOBuffer->CID != GetCID()) // We don't initialize CID any more. skip it
		//	netErr(ResultCode::INVALID_ARG);

		if (pIOBuffer != nullptr && pIOBuffer->Operation != IOBUFFER_OPERATION::OP_TCPREAD)
		{
			netErr(ResultCode::UNEXPECTED);
		}

		Assert(!NetSystem::IsProactorSystem() || pIOBuffer->bIsPending.load(std::memory_order_relaxed));

		// Pending recv count and registered status should be checked together so that we can prevent infinite pending recv
		// And PendingRecv should be decreased after new pending is happened
		if (GetIsIORegistered())
		{

			if (hrRes)
			{
				netChkPtr(pIOBuffer);

				if (!(hr = m_Owner.OnRecv(pIOBuffer->TransferredSize, (uint8_t*)pIOBuffer->buffer)))
					SFLog(Net, Debug3, "Read IO failed with CID {0}, hr={1:X8}", m_Owner.GetCID(), hr);
			}
			else
			{
				switch ((uint32_t)hrRes)
				{
				case (uint32_t)ResultCode::IO_CONNECTION_CLOSED:
					m_Owner.Disconnect("Recv failed, IO_CONNECTION_CLOSED");
					break;
				case (uint32_t)ResultCode::IO_IO_ABORTED:
					m_Owner.Disconnect("Recv fail, IO_IO_ABORTED");
					break;
				default:
					SFLog(Net, Debug3, "Recv Msg Failed, SvrTCP, CID {0}, hr={1:X8}", GetCID(), hrRes);
					break;
				};
			}
		}

	Proc_End:

		// decrease should be happened at last, and always
		if (NetSystem::IsProactorSystem())
		{
			DecPendingRecvCount();

			PendingRecv();
		}


		if (pIOBuffer != nullptr)
		{
			pIOBuffer->SetPendingFalse();
			Util::SafeDelete(pIOBuffer);
		}

		SFLog(Net, Debug3, "TCP Recv CID:{0}, pending:{1}, hr:{2:X8}", GetCID(), GetPendingRecvCount(), hr);

		return hr;

	}

	Result ConnectionTCP::MyNetSocketIOAdapter::OnWriteReady()
	{
		Result hr;
		if (GetEventHandler() != nullptr)
		{
			// This will only be happened on connection with server connection
			auto hrRes = GetEventHandler()->OnNetSendReadyMessage(&m_Owner);
			netChk(hrRes);
		}
		// process directly
		else
		{
			netChk(ProcessSendQueue());
		}

	Proc_End:

		return hr;
	}


	// Send message to connection with network device
	Result ConnectionTCP::MyNetSocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
	{
		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return ResultCode::IO_NOT_CONNECTED;

		Result hr = SocketIOTCP::WriteBuffer(pSendBuffer);
		switch ((uint32_t)hr)
		{
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			// Send fail by connection close
			// Need to disconnect
			m_Owner.Disconnect("Send failed by error");
			hr = ResultCode::IO_CONNECTION_CLOSED;
			break;
		case (uint32_t)ResultCode::IO_NOTCONN:
			m_Owner.m_IsTCPSocketConnectionEstablished = m_Owner.Connect() == ResultCode::SUCCESS;
			break;
		case (uint32_t)ResultCode::IO_IO_SEND_FAIL:
			break;
		};

		return hr;
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network connection class
	//

	// Constructor
	ConnectionTCP::ConnectionTCP(IHeap& heap)
		: Connection(heap, &m_NetIOAdapter)
		, m_NetIOAdapter(*this)
		, m_lGuarantedSent(0)
		, m_lGuarantedAck(0)
		, m_uiRecvTemUsed(0)
		, m_WriteBuffer(GetHeap())
		, m_uiSendNetCtrlCount(0)
		, m_IsClientConnection(false)
		, m_IsTCPSocketConnectionEstablished(true)
	{
		m_bufRecvTem.resize(Const::PACKET_SIZE_MAX * 2);

		SetHeartbeatTry(Const::TCP_HEARTBEAT_START_TIME);

		m_NetIOAdapter.SetWriteQueue(new(GetHeap()) WriteBufferQueue(GetHeap()));

		SetNetCtrlAction(NetCtrlCode_Ack, &m_HandleAck);
		SetNetCtrlAction(NetCtrlCode_Nack, &m_HandleNack);
		SetNetCtrlAction(NetCtrlCode_Heartbeat, &m_HandleHeartbeat);
		SetNetCtrlAction(NetCtrlCode_TimeSync, &m_HandleTimeSync);
		SetNetCtrlAction(NetCtrlCode_Connect, &m_HandleConnect);
		SetNetCtrlAction(NetCtrlCode_Disconnect, &m_HandleDisconnect);

	}

	ConnectionTCP::~ConnectionTCP()
	{
		if (GetSocket() != INVALID_SOCKET)
		{
			AssertRel(!m_NetIOAdapter.GetIsIORegistered());
			AssertRel(m_NetIOAdapter.GetAssignedIOWorker() == -1);

			m_NetIOAdapter.CloseSocket();
		}

		if (m_NetIOAdapter.GetWriteQueue()) IHeap::Delete(m_NetIOAdapter.GetWriteQueue());
	}


	bool ConnectionTCP::CanDelete()
	{
		return m_NetIOAdapter.CanDelete();
	}

	void ConnectionTCP::Dispose()
	{
		ClearQueues();

		super::Dispose();

		m_NetIOAdapter.CloseSocket();
	}



	// Clear Queue
	Result ConnectionTCP::ClearQueues()
	{
		return ResultCode::SUCCESS;
	}



	// Called on connection result
	void ConnectionTCP::OnConnectionResult( Result hrConnect )
	{
		Connection::OnConnectionResult( hrConnect );

		if( !hrConnect )
		{
			CloseConnection("Connecting failed");
		}
	}


	// Initialize connection
	Result ConnectionTCP::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		m_NetIOAdapter.CloseSocket();

		m_lGuarantedSent = 0;
		m_lGuarantedAck = 0;

		m_NetIOAdapter.ResetPendingRecvCount();
		m_NetIOAdapter.ResetPendingSendCount();


		m_uiSendNetCtrlCount = 0;
		m_uiRecvTemUsed = 0;

		m_IsClientConnection = false;
		m_IsTCPSocketConnectionEstablished = true; // accepted socket treated as if they are already connected

		Assert(local.PeerClass != NetClass::Unknown);

		// ignore incoming socket value
		return Connection::InitConnection(local, remote );
	}

	Result ConnectionTCP::Connect(PeerInfo local, const PeerInfo& remote)
	{
		Result hr = ResultCode::SUCCESS;
		SF_SOCKET socket = INVALID_SOCKET;
		NetAddress localAddress;
		int flag = 1;
		int result;

		if (StrUtil::IsNullOrEmpty(local.PeerAddress.Address))
		{
			if (remote.PeerAddress.SocketFamily == SockFamily::IPV4)
				Net::GetLocalAddressIPv4(local.PeerAddress);
			else
				Net::GetLocalAddressIPv6(local.PeerAddress);
		}

		socket = Service::NetSystem->Socket(local.PeerAddress.SocketFamily, SockType::Stream);
		if (socket == INVALID_SOCKET)
		{
			SFLog(Net, Error, "Failed to Open a Socket {0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		netChk(Service::NetSystem->SetupCommonSocketOptions(SockType::Stream, local.PeerAddress.SocketFamily, socket));

		netChk(InitConnection(local, remote));

		result = setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
		if (result < 0)
		{
			netChk(GetLastNetSystemResult());
		}

		m_NetIOAdapter.SetSocket(local.PeerAddress.SocketFamily, SockType::Stream, socket);

		socket = INVALID_SOCKET;

		netChk(Service::NetSystem->RegisterSocket(&m_NetIOAdapter));

		hr = Connect();

	Proc_End:

		if (socket != INVALID_SOCKET)
			Service::NetSystem->CloseSocket(socket);

		return hr;
	}

	Result ConnectionTCP::Connect()
	{
		Result hrConResult;
		int connResult;
		ScopeContext hr([this, &hrConResult](Result hr)
			{
				if (hrConResult != ResultCode::IO_ALREADY)
				{
					SFLog(Net, Debug, "Connect sock:{0}, to:{1}, hrCon:{2}, hr:{3}", GetSocket(), GetRemoteInfo().PeerAddress, hrConResult, hr);
				}

				if (!hr)
				{
					SetConnectionState(ConnectionState::DISCONNECTED);
					m_NetIOAdapter.CloseSocket();
				}
			});

		ResetZeroRecvCount();

		if (GetConnectionState() != ConnectionState::CONNECTING && GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			SFLog(Net, Error, "Invalid connection state to try connect {0}", GetConnectionState());
			return hr = ResultCode::IO_INVALID_CONNECTION_STATE;
		}

		connResult = connect(GetSocket(), (sockaddr*)&GetRemoteSockAddr(), GetRemoteSockAddrSize());
		if (connResult == SOCKET_ERROR)
		{
			hrConResult = GetLastNetSystemResult();
			if (hrConResult != ResultCode::IO_ALREADY)
			{
				SFLog(Net, Debug2, "TCP Connect result {0}", hrConResult);
			}
			switch ((uint32_t)hrConResult)
			{
			case (uint32_t)ResultCode::IO_INPROGRESS:
			case (uint32_t)ResultCode::IO_WOULDBLOCK:  // First call need to wait
			case (uint32_t)ResultCode::IO_ALREADY:		// called again, still need to wait
				hr = ResultCode::SUCCESS_FALSE;
				break;
			case (uint32_t)ResultCode::IO_ISCONN:		// Connection established
				hr = ResultCode::SUCCESS;
				break;
			default:
				SFLog(Net, Warning, "Connection try is failed, RemoteAddr:{0}, RemoteID:{1}, hr:{2:X8}", GetRemoteInfo().PeerAddress, GetRemoteInfo().PeerID, hrConResult);
				hr = hrConResult;
			}
		}

		m_IsClientConnection = true;
		m_IsTCPSocketConnectionEstablished = false; // only client side need to check this condition

		return hr;
	}

	// Close connection
	Result ConnectionTCP::CloseConnection(const char* reason)
	{
		Result hr = ResultCode::SUCCESS;

		//socket
		m_uiRecvTemUsed = 0;
		ResetZeroRecvCount();

		m_NetIOAdapter.CloseSocket();

		netCheck(Connection::CloseConnection(reason));

		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return hr;

		return hr;
	}


	// called when incoming message occur
	Result ConnectionTCP::OnRecv( uint uiBuffSize, const uint8_t* pBuff )
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pMsg;

		if( uiBuffSize == 0 )
		{
			IncZeroRecvCount();
			if( GetZeroRecvCount() > (uint32_t)Const::CONNECTION_ZEROPACKET_MAX )
			{
				SFLog(Net, Debug3, "TCP RecvBuf, too many zero size packet, {0}", GetZeroRecvCount());
				//ResetZeroRecvCount();
				Disconnect("Too many zero packets");
			}
			return hr;
		}

		SFLog(Net, Debug3, "TCP RecvBuf Len={0}", uiBuffSize);

		while( uiBuffSize > 0 )
		{
			Message::MessageHeader *pMsgHdr = NULL;

			ResetZeroRecvCount();

			if( m_uiRecvTemUsed == 0 )
			{
				pMsgHdr = (Message::MessageHeader*)pBuff;
				if( uiBuffSize < sizeof(Message::MessageHeader) || uiBuffSize < pMsgHdr->Length ) // too small to make packet
				{
					// send all data to recv temporary buffer and return
					m_uiRecvTemUsed = uiBuffSize;
					// relocate buffer if too small
					if( m_bufRecvTem.size() < uiBuffSize )
						m_bufRecvTem.resize( ((uiBuffSize+m_bufRecvTem.size()) / m_bufRecvTem.size()) * m_bufRecvTem.size() );

					memcpy( m_bufRecvTem.data(), pBuff, uiBuffSize );

					uiBuffSize = 0;
					break;
				}

				if( pMsgHdr->Length < sizeof(Message::MessageHeader) )
				{
					// too small invalid packet
					netCheck( ResultCode::UNEXPECTED );
				}

				netCheckMem( pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHdr->msgID.ID, pMsgHdr->Length, pBuff ) );

				hr = OnRecv( pMsg );
				pMsg = nullptr;
				netCheck( hr );

				uiBuffSize -= pMsgHdr->Length;
				pBuff += pMsgHdr->Length;
			}
			else
			{
				uint uiCopySize = 0;

				// copy header
				if( m_uiRecvTemUsed < sizeof(Message::MessageHeader) )
				{
					uiCopySize = (uint)sizeof(Message::MessageHeader) - m_uiRecvTemUsed;
					if( uiBuffSize < uiCopySize )
					{
						// buffer too small to make header. append data and return
						memcpy( m_bufRecvTem.data() + m_uiRecvTemUsed, pBuff, uiBuffSize );
						m_uiRecvTemUsed += uiBuffSize;
						break;
					}

					memcpy( m_bufRecvTem.data() + m_uiRecvTemUsed, pBuff, uiCopySize );

					uiBuffSize -= uiCopySize;
					pBuff += uiCopySize;
					m_uiRecvTemUsed += uiCopySize;

					if( m_uiRecvTemUsed < sizeof(Message::MessageHeader) )
						break;
				}

				pMsgHdr = (Message::MessageHeader*)m_bufRecvTem.data();

				// if Temporary buffer is too small then reallocate
				if( m_bufRecvTem.size() < pMsgHdr->Length )
					m_bufRecvTem.resize( pMsgHdr->Length );

				// append remain body
				if( pMsgHdr->Length < m_uiRecvTemUsed )
				{
					netCheck( ResultCode::IO_BADPACKET_SIZE );
				}

				uiCopySize = pMsgHdr->Length - m_uiRecvTemUsed;
				if( uiBuffSize < uiCopySize )
				{
					// buffer too small to make body. append data and return
					memcpy( m_bufRecvTem.data() + m_uiRecvTemUsed, pBuff, uiBuffSize );

					m_uiRecvTemUsed += uiBuffSize;

					// remain data will be occur at next parts of packet
					break;
				}

				// append remain body
				memcpy( m_bufRecvTem.data() + m_uiRecvTemUsed, pBuff, uiCopySize );
				uiBuffSize -= uiCopySize;
				pBuff += uiCopySize;
				m_uiRecvTemUsed = 0;

				netCheckMem( pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHdr->msgID.ID, pMsgHdr->Length, m_bufRecvTem.data() ) );

				hr = OnRecv( pMsg );
				pMsg = nullptr;
				netCheck( hr );
			}

		}

		return hr;
	}



	Result ConnectionTCP::OnRecv(SharedPointerT<Message::MessageData>& pMsg )
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageHeader *pMsgHeader = pMsg->GetMessageHeader();

		if( pMsgHeader->msgID.IDs.Type == Message::MSGTYPE_NETCONTROL )
		{
			SFLog(Net, Debug2, "TCP Ctrl Recv ip:{0}, msg:{1}, Len:{2}",
				GetRemoteInfo().PeerAddress, 
				pMsgHeader->msgID, pMsgHeader->Length );

			netCheck( ProcNetCtrl( (MsgNetCtrl*)pMsgHeader ) );
		}
		else
		{
			netCheck( pMsg->ValidateChecksumNDecrypt() );

			hr  = Connection::OnRecv( pMsg );
			pMsg = nullptr;
			netCheck( hr );
		}

		pMsg = nullptr;

		return hr;
	}

	Result ConnectionTCP::SendPending(uint uiCtrlCode, uint uiSequence, Message::MessageID returnMsgID, uint64_t UID)
	{
		return SendNetCtrl(uiCtrlCode, uiSequence, returnMsgID, UID);
	}

	Result ConnectionTCP::SendRaw(const SharedPointerT<Message::MessageData> &pMsg)
	{
		SFUniquePtr<IOBUFFER_WRITE> pSendBuffer;
		ScopeContext hr;

		if (!m_NetIOAdapter.GetIsIORegistered())
			return ResultCode::SUCCESS_FALSE;

		netCheckMem(pMsg);

		pSendBuffer.reset(new(GetIOHeap()) IOBUFFER_WRITE);
		netCheckMem(pSendBuffer.get());
		pSendBuffer->SetupSendTCP(SharedPointerT<Message::MessageData>(pMsg));

		m_NetIOAdapter.IncPendingSendCount();

		if (NetSystem::IsProactorSystem())
		{
			hr = m_NetIOAdapter.WriteBuffer(pSendBuffer.get());
		}
		else
		{
			hr = m_NetIOAdapter.EnqueueBuffer(pSendBuffer.get());
			m_NetIOAdapter.ProcessSendQueue();
		}

		if (hr)
			pSendBuffer.release();
		else
			m_NetIOAdapter.DecPendingSendCount();

		return hr;
	}

	// Send message to connected entity
	Result ConnectionTCP::Send(const SharedPointerT<Message::MessageData> &pMsg )
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageID msgID;

		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return ResultCode::IO_NOT_CONNECTED;

		Message::MessageHeader* pMsgHeader = pMsg->GetMessageHeader();
		msgID = pMsgHeader->msgID;

		if ((pMsgHeader->msgID.IDs.Type != Message::MSGTYPE_NETCONTROL && GetConnectionState() == ConnectionState::DISCONNECTING)
			|| GetConnectionState() == ConnectionState::DISCONNECTED)
		{
			// Send fail by connection closed
			goto Proc_End;
		}

		if( pMsg->GetMessageSize() > (uint)Const::INTER_PACKET_SIZE_MAX )
		{
			netErr( ResultCode::IO_BADPACKET_TOOBIG );
		}

		Protocol::PrintDebugMessage( "Send", pMsg );

		if( !pMsg->GetMessageHeader()->msgID.IDs.Reliability
			&& (m_lGuarantedSent - m_lGuarantedAck) > Const::GUARANT_PENDING_MAX)
		{
			// Drop if there are too many reliable packets
			netErr( ResultCode::IO_SEND_FAIL );
		}

		m_lGuarantedSent.fetch_add(1, std::memory_order_relaxed);

		pMsg->UpdateChecksumNEncrypt();

		netChk(SendRaw(pMsg));

	Proc_End:

		if(!(hr))
		{
		}
		else
		{
			if (msgID.IDs.Type == Message::MSGTYPE_NETCONTROL)
			{
				SFLog(Net, Debug2, "TCP Ctrl CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
			}
			else
			{
				SFLog(Net, Debug3, "TCP Send CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
			}
		}

		return hr;
	}

	// Update Send buffer Queue, TCP and UDP client connection
	Result ConnectionTCP::UpdateSendBufferQueue()
	{
		return m_NetIOAdapter.ProcessSendQueue();
	}

	// Update net control, process connection heartbeat, ... etc
	Result ConnectionTCP::TickUpdate()
	{
		Result hr = ResultCode::SUCCESS;

		if (GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			if (!GetIsIORegistered())
			{
				SFLog(Net, Debug, "Close connection because it's kicked from net IO, CID:{0}", GetCID());
				netCheck(CloseConnection("Kicked from IO system"));
			}
			else
			{
				// On client side, we need to check readable/writable status by calling connect again
				if (m_IsClientConnection && !m_IsTCPSocketConnectionEstablished && GetConnectionState() == ConnectionState::CONNECTING)
				{
					m_IsTCPSocketConnectionEstablished = Connect() == ResultCode::SUCCESS;
				}

				if (m_IsTCPSocketConnectionEstablished
					&& GetMyNetIOAdapter().GetPendingRecvCount() == 0
					&& GetNetIOHandler() != nullptr)
				{
					hr = GetNetIOHandler()->PendingRecv();
					if (hr == ResultCode::IO_NOTCONN)
					{
						SFLog(Net, Info, "Connection not connected CID:{0}", GetCID());
						CloseConnection("Can't recv if not connected");
					}
				}
			}
		}

		return super::TickUpdate();
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network client connection class
	//

	// Constructor
	ConnectionTCPClient::ConnectionTCPClient(IHeap& heap)
		: ConnectionTCP(heap)
	{
		//GetRecvBuffer()->SetupRecvTCP( GetCID() );
		// We can't set tick here. There is a small chance that tick update finished before this object's reference count got increased
		//SetTickGroup(EngineTaskTick::AsyncTick);

		SetNetCtrlAction(NetCtrlCode_TimeSyncRtn, &m_HandleTimeSyncRtn);

		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::CONNECTING, &m_SendConnect);
		AddStateAction(ConnectionState::CONNECTED, &m_TimeoutHeartbeat);
		AddStateAction(ConnectionState::CONNECTED, &m_SendHeartbeat);
		AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);
	}

	ConnectionTCPClient::~ConnectionTCPClient()
	{
	}

	// Initialize connection
	Result ConnectionTCPClient::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		if (local.PeerClass != NetClass::Client)
			return ResultCode::INVALID_ARG;

		Result hr = ConnectionTCP::InitConnection(local, remote );

		return hr;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network client connection class
	//

	// Constructor
	ConnectionTCPServer::ConnectionTCPServer(IHeap& heap)
		: ConnectionTCP(heap)
	{
		SetHeartbeatTry(Const::SVR_HEARTBEAT_TIME_PEER);

		Assert(GetMyNetIOAdapter().GetWriteQueue() != nullptr);

		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::CONNECTED, &m_TimeoutHeartbeat);
		AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);
	}

	ConnectionTCPServer::~ConnectionTCPServer()
	{
	}






} // namespace Net
} // namespace SF



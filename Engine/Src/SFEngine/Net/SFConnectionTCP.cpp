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
#include "Thread/SFThread.h"
#include "Memory/SFMemory.h"
#include "SFAssert.h"
#include "Util/SFTimeUtil.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "String/SFToString.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFNetToString.h"
#include "Net/SFConnection.h"
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
			m_Owner.m_IsTCPSocketConnectionEstablished = m_Owner.Connect();
			if (!m_Owner.m_IsTCPSocketConnectionEstablished)
				return ResultCode::SUCCESS;
		}

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

		if (pIOBuffer != nullptr && pIOBuffer->CID != GetCID())
			netErr(ResultCode::INVALID_ARG);

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

				PendingRecv();
			}
			else
			{
				switch ((uint32_t)hrRes)
				{
				case (uint32_t)ResultCode::IO_CONNECTION_CLOSED:
				case (uint32_t)ResultCode::IO_IO_ABORTED:
					m_Owner.Disconnect("Recv failed");;
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
			DecPendingRecvCount();

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
			m_Owner.m_IsTCPSocketConnectionEstablished = m_Owner.Connect();
			break;
		case (uint32_t)ResultCode::IO_IO_SEND_FAIL:
			// no further error handling
			hr = ResultCode::SUCCESS;
			break;
		};

	//Proc_End:

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

		SetHeartbitTry(Const::TCP_HEARTBIT_START_TIME);

		m_NetIOAdapter.SetWriteQueue(new(GetHeap()) WriteBufferQueue(GetHeap()));
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


	// Process network control message
	Result ConnectionTCP::ProcNetCtrl(const MsgNetCtrl* pNetCtrl)
	{
		Result hr = ResultCode::SUCCESS;

		switch (pNetCtrl->msgID.IDs.MsgCode)
		{
		case NetCtrlCode_Ack:
			if (pNetCtrl->rtnMsgID.IDs.Type == Message::MSGTYPE_NETCONTROL)
			{
				switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
				{
				case NetCtrlCode_Disconnect:
					if (GetConnectionState() != ConnectionState::DISCONNECTED)
						netChk(CloseConnection("Disconnect ack"));
					break;
				case NetCtrlCode_HeartBit:
					m_ulNetCtrlTime = Util::Time.GetTimeMs();
					break;
				case NetCtrlCode_Connect:
					if (GetConnectionState() == ConnectionState::CONNECTING)
					{
						Assert(pNetCtrl->Length == sizeof(MsgNetCtrlConnect));
						auto pConnectCtrl = ((MsgNetCtrlConnect*)pNetCtrl);
						GetRemoteInfo().SetInfo(pConnectCtrl->Peer.PeerClass, pConnectCtrl->Peer.PeerAddress, pConnectCtrl->Peer.PeerID);
						OnConnectionResult(ResultCode::SUCCESS);
					}
					break;
				};
			}
			else
			{
				// Remove from Guranted queue
				if (pNetCtrl->rtnMsgID.IDs.Reliability)
				{
					m_lGuarantedAck.fetch_add(1, std::memory_order_relaxed);
				}
			}

			break;
		case NetCtrlCode_Nack:
			if (pNetCtrl->rtnMsgID.IDs.Type == Message::MSGTYPE_NETCONTROL)// connecting process
			{
				switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
				{
				case NetCtrlCode_Disconnect:
					break;
				case NetCtrlCode_Connect:
					// Protocol version mismatch
					OnConnectionResult(ResultCode::IO_PROTOCOL_VERSION_MISMATCH);
					netChk(Disconnect("Protocol mismatch"));
					break;
				case NetCtrlCode_HeartBit:
					break;
				default:
					break;
				};
			}
			break;
		case NetCtrlCode_HeartBit:
			m_ulNetCtrlTime = Util::Time.GetTimeMs();
			netChk(SendNetCtrl(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
			break;
		case NetCtrlCode_Connect:
		{
			m_ulNetCtrlTime = Util::Time.GetTimeMs();

			if (pNetCtrl->Length < sizeof(MsgNetCtrlConnect))
			{
				SFLog(Net, Warning, "HackWarn : Invalid Connect packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netChk(CloseConnection("Invalid packet size during connect"));
				netErr(ResultCode::UNEXPECTED);
			}

			if (GetConnectionState() == ConnectionState::CONNECTING || GetConnectionState() == ConnectionState::CONNECTED)// ServerTCP connection will occure this case
			{
				const MsgNetCtrlConnect *pNetCtrlCon = (const MsgNetCtrlConnect*)pNetCtrl;
				uint recvProtocolVersion = pNetCtrl->rtnMsgID.ID;

				if (recvProtocolVersion != SF_PROTOCOL_VERSION)
				{
					netChk(SendNetCtrl(PACKET_NETCTRL_NACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
					if (GetConnectionState() != ConnectionState::CONNECTED)
						OnConnectionResult(ResultCode::IO_PROTOCOL_VERSION_MISMATCH);
					netChk(Disconnect("Protocol mismatch"));
				}
				else if (GetRemoteInfo().PeerClass != NetClass::Unknown && pNetCtrlCon->Peer.PeerClass != GetRemoteInfo().PeerClass)
				{
					netChk(SendNetCtrl(PACKET_NETCTRL_NACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
					if (GetConnectionState() != ConnectionState::CONNECTED)
						OnConnectionResult(ResultCode::IO_INVALID_NETCLASS);
					netChk(Disconnect("Invalid netclass"));
				}
				else
				{
					Assert(GetLocalInfo().PeerClass != NetClass::Unknown);
					netChk(SendNetCtrl(PACKET_NETCTRL_ACK, (uint)GetLocalInfo().PeerClass, pNetCtrl->msgID, GetLocalInfo().PeerID));
					if (GetConnectionState() != ConnectionState::CONNECTED)
					{
						GetRemoteInfo().SetInfo(pNetCtrlCon->Peer.PeerClass, pNetCtrlCon->Peer.PeerAddress, pNetCtrlCon->Peer.PeerID);
						OnConnectionResult(ResultCode::SUCCESS);
					}
				}
			}
			break;
		}
		case NetCtrlCode_Disconnect:
			netChk(SendNetCtrl(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
			netChk(SendNetCtrl(PACKET_NETCTRL_DISCONNECT, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
			netChk(CloseConnection("Disconnect received"));
			break;
		default:
			SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
			netChk(CloseConnection("Invalid net ctrl packet"));
			netErr(ResultCode::UNEXPECTED);
			break;
		};


	Proc_End:

		return hr;
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

		if( ( hrConnect ) )
		{
		}
		else
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
		m_IsTCPSocketConnectionEstablished = true;

		Assert(local.PeerClass != NetClass::Unknown);

		// ignore incoming socket value
		return Connection::InitConnection(local, remote );
	}

	Result ConnectionTCP::Connect(PeerInfo local, const PeerInfo& remote)
	{
		Result hr = ResultCode::SUCCESS;
		SOCKET socket = INVALID_SOCKET;
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
		Result hr = ResultCode::SUCCESS;
		Result hrConResult;
		int connResult;

		ResetZeroRecvCount();

		if (GetConnectionState() != ConnectionState::CONNECTING && GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			SFLog(Net, Error, "Invalid connection state to try connect {0}", GetConnectionState());
			hr = ResultCode::IO_INVALID_CONNECTION_STATE;
			goto Proc_End;
		}

		connResult = connect(GetSocket(), (sockaddr*)&GetRemoteSockAddr(), GetRemoteSockAddrSize());
		if (connResult == SOCKET_ERROR)
		{
			hrConResult = GetLastNetSystemResult();
			switch ((uint32_t)hrConResult)
			{
			case (uint32_t)ResultCode::IO_INPROGRESS:
			case (uint32_t)ResultCode::IO_WOULDBLOCK:  // First call need to wait
			case (uint32_t)ResultCode::IO_ALREADY:		// called again, still need to wait
				hr = ResultCode::SUCCESS_FALSE;
				break;
			case (uint32_t)ResultCode::IO_ISCONN:		// Connection estabalished
				hr = ResultCode::SUCCESS;
				break;
			default:
				SFLog(Net, Warning, "Connection try is failed, RemoteAddr:{0}, RemoteID:{1}, hr:{2:X8}", GetRemoteInfo().PeerAddress, GetRemoteInfo().PeerID, hrConResult);
				hr = hrConResult;
			}
		}

		m_IsClientConnection = true;
		m_IsTCPSocketConnectionEstablished = false; // only client side need to check this condition

	Proc_End:

		SFLog(Net, Debug, "Connect sock:{0}, to:{1}, hrCon:{2}, hr:{3}", GetSocket(), GetRemoteInfo().PeerAddress, hrConResult, hr);

		if (!(hr))
		{
			SetConnectionState(ConnectionState::DISCONNECTED);
			m_NetIOAdapter.CloseSocket();
		}

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

		netChk(Connection::CloseConnection(reason) );

		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			goto Proc_End;
		

	Proc_End:

		return hr;
	}



	// called when incoming message occure
	Result ConnectionTCP::OnRecv( uint uiBuffSize, const uint8_t* pBuff )
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pMsg;

		SFLog(Net, Debug3, "TCP RecvBuf Len={0}", uiBuffSize);

		if( uiBuffSize == 0 )
		{
			IncZeroRecvCount();
			if( GetZeroRecvCount() > (uint32_t)Const::CONNECTION_ZEROPACKET_MAX )
			{
				//Disconnect("Too many zero packets");
			}
			goto Proc_End;
		}

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
					netErr( ResultCode::UNEXPECTED );
				}

				netMem( pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHdr->msgID.ID, pMsgHdr->Length, pBuff ) );

				hr = OnRecv( pMsg );
				pMsg = nullptr;
				netChk( hr );

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
					netErr( ResultCode::IO_BADPACKET_SIZE );
				}

				uiCopySize = pMsgHdr->Length - m_uiRecvTemUsed;
				if( uiBuffSize < uiCopySize )
				{
					// buffer too small to make body. append data and return
					memcpy( m_bufRecvTem.data() + m_uiRecvTemUsed, pBuff, uiBuffSize );

					m_uiRecvTemUsed += uiBuffSize;

					// remain data will be occure at next parts of packet
					break;
				}

				// append remain body
				memcpy( m_bufRecvTem.data() + m_uiRecvTemUsed, pBuff, uiCopySize );
				uiBuffSize -= uiCopySize;
				pBuff += uiCopySize;
				m_uiRecvTemUsed = 0;

				netMem( pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHdr->msgID.ID, pMsgHdr->Length, m_bufRecvTem.data() ) );

				hr = OnRecv( pMsg );
				pMsg = nullptr;
				netChk( hr );
			}

		}

	Proc_End:

		pMsg = nullptr;

		return hr;
	}



	Result ConnectionTCP::OnRecv(SharedPointerT<Message::MessageData>& pMsg )
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageHeader *pMsgHeader = pMsg->GetMessageHeader();

		if( pMsgHeader->msgID.IDs.Type == Message::MSGTYPE_NETCONTROL )
		{
			SFLog(Net, Debug2, "TCP Ctrl Recv ip:{0}, msg:{1}, Len:%2%",
				GetRemoteInfo().PeerAddress, 
				pMsgHeader->msgID, pMsgHeader->Length );

			netChk( ProcNetCtrl( (MsgNetCtrl*)pMsgHeader ) );
		}
		else
		{
			netChk( pMsg->ValidateChecksumNDecrypt() );

			if( pMsgHeader->msgID.IDs.Reliability )
			{
				SendNetCtrl(PACKET_NETCTRL_ACK, pMsgHeader->msgID.IDSeq.Sequence, pMsgHeader->msgID);
			}

			hr  = Connection::OnRecv( pMsg );
			pMsg = nullptr;
			netChk( hr );
		}

	Proc_End:

		pMsg = nullptr;

		return hr;
	}


	Result ConnectionTCP::SendRaw(SharedPointerT<Message::MessageData> &pMsg)
	{
		Result hr = ResultCode::SUCCESS;
		IOBUFFER_WRITE *pSendBuffer = nullptr;

		if (!m_NetIOAdapter.GetIsIORegistered())
			return ResultCode::SUCCESS_FALSE;

		netChkPtr(pMsg);

		m_NetIOAdapter.IncPendingSendCount();

		netMem(pSendBuffer = new(GetIOHeap()) IOBUFFER_WRITE);
		pSendBuffer->SetupSendTCP(std::forward<SharedPointerT<Message::MessageData>>(pMsg));

		if (NetSystem::IsProactorSystem())
		{
			netChk(m_NetIOAdapter.WriteBuffer(pSendBuffer));
		}
		else
		{
			netChk(m_NetIOAdapter.EnqueueBuffer(pSendBuffer));
			m_NetIOAdapter.ProcessSendQueue();
		}
		pMsg = nullptr;
		pSendBuffer = nullptr;

	Proc_End:

		if (pSendBuffer != nullptr)
		{
			GetHeap().Free(pSendBuffer);
		}

		return hr;
	}

	// Send message to connected entity
	Result ConnectionTCP::Send(SharedPointerT<Message::MessageData> &pMsg )
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
			pMsg = nullptr;
			goto Proc_End;
		}

		if( pMsg->GetMessageSize() > (uint)Const::INTER_PACKET_SIZE_MAX )
		{
			pMsg = nullptr;
			netErr( ResultCode::IO_BADPACKET_TOOBIG );
		}

		Protocol::PrintDebugMessage( "Send", pMsg );

		if( !pMsg->GetMessageHeader()->msgID.IDs.Reliability
			&& (m_lGuarantedSent - m_lGuarantedAck) > Const::TCP_GUARANT_PENDING_MAX )
		{
			// Drop if there is too many reliable packets are pending
			netErr( ResultCode::IO_SEND_FAIL );
		}

		m_lGuarantedSent.fetch_add(1, std::memory_order_relaxed);

		pMsg->UpdateChecksumNEncrypt();

		netChk(SendRaw(pMsg));

		pMsg = nullptr;

	Proc_End:

		if(!(hr))
		{
			pMsg = nullptr;
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

	Result ConnectionTCP::SendNetCtrl(uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID)
	{
		Result hr = Connection::SendNetCtrl(uiCtrlCode, uiSequence, msgID, UID);
		if ((hr))
		{
			m_NetIOAdapter.IncPendingSendCount();
		}

		return hr;
	}

	// Update Send buffer Queue, TCP and UDP client connection
	Result ConnectionTCP::UpdateSendBufferQueue()
	{
		return m_NetIOAdapter.ProcessSendQueue();
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
	}

	ConnectionTCPClient::~ConnectionTCPClient()
	{
	}


	// Update net control, process connection heartbit, ... etc
	Result ConnectionTCPClient::TickUpdate()
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageID msgIDTem;

		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();

		if( GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			if (!GetIsIORegistered())
			{
				SFLog(Net, Debug, "Close connection because it's kicked from net IO, CID:{0}", GetCID());
				netChk(CloseConnection("Kicked from IO system"));
			}
			else
			{
				if(GetNetIOHandler() != nullptr)
					GetNetIOHandler()->PendingRecv();
			}
		}

		// connect/disconnect process
		msgIDTem.ID = PACKET_NETCTRL_NONE;
		switch (GetConnectionState())
		{
		case ConnectionState::CONNECTING:
			if (Util::TimeSince(m_ulNetCtrlTime) > GetConnectingTimeOut()) // connection time out
			{
				SFLog(Net, Debug, "Connecting Timeout CID:{0}", GetCID() );
				netChk( CloseConnection("Connecting timeout") );
			}
			else if(Util::TimeSince(m_ulNetCtrlTryTime) > Const::CONNECTION_RETRY_TIME ) // retry
			{
				m_ulNetCtrlTryTime = ulTimeCur;
				netChk(SendNetCtrl(PACKET_NETCTRL_CONNECT, (uint)GetLocalInfo().PeerClass, Message::MessageID(SF_PROTOCOL_VERSION), GetLocalInfo().PeerID));
			}

			goto Proc_End;
			break;
		case ConnectionState::DISCONNECTING:
			if( (ulTimeCur-m_ulNetCtrlTime) > DurationMS(Const::SVR_DISCONNECT_TIMEOUT) ) // connection time out
			{
				SFLog(Net, Debug, "Disconnecting Timeout CID:{0}", GetCID() );
				netChk( CloseConnection("Disconnecting") );
			}

			m_ulNetCtrlTryTime = ulTimeCur;
			goto Proc_End;
			break;
		case ConnectionState::CONNECTED:
			if(Util::TimeSince(m_ulNetCtrlTime) > Const::HEARTBIT_TIMEOUT ) // connection time out
			{
				SFLog(Net, Debug, "Connection Timeout CID:{1}", GetCID() );

				netChk( CloseConnection("Heartbit timeout") );
				m_ulNetCtrlTime = ulTimeCur;
				goto Proc_End;
			}
			else if( (ulTimeCur-m_ulNetCtrlTryTime) > DurationMS(GetHeartbitTry()) ) // heartbit time
			{
				m_ulNetCtrlTryTime = ulTimeCur;
				netChk( SendNetCtrl( PACKET_NETCTRL_HEARTBIT, 0, msgIDTem ) );
			}
			break;
		default:
			break;
		};


	Proc_End:


		return hr;
	}
	
		
	// Initialize connection
	Result ConnectionTCPClient::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		Result hr = ConnectionTCP::InitConnection(local, remote );
		SetLocalClass( NetClass::Client );

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
		SetHeartbitTry(Const::SVR_HEARTBIT_TIME_PEER);

		Assert(GetMyNetIOAdapter().GetWriteQueue() != nullptr);
	}

	ConnectionTCPServer::~ConnectionTCPServer()
	{
	}


	// Update net control, process connection heartbit, ... etc
	Result ConnectionTCPServer::TickUpdate()
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageID msgIDTem;

		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();

		if( GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			if (GetNetIOHandler() != nullptr)
				GetNetIOHandler()->PendingRecv();
		}

		// connect/disconnect process
		msgIDTem.ID = PACKET_NETCTRL_NONE;
		switch (GetConnectionState())
		{
		case ConnectionState::CONNECTING:
			if( (ulTimeCur-m_ulNetCtrlTime) > DurationMS(GetConnectingTimeOut()) ) // connection time out
			{
				SFLog(Net, Info, "Connecting Timeout CID:{0}", GetCID() );
				netChk( CloseConnection("Connecting timeout") );
			}

			goto Proc_End;
			break;
		case ConnectionState::DISCONNECTING:
			if( (ulTimeCur-m_ulNetCtrlTime) > DurationMS(Const::DISCONNECT_TIMEOUT) ) // connection time out
			{
				SFLog(Net, Info, "Disconnecting Timeout CID:{0}", GetCID() );
				netChk( CloseConnection("Disconnecting") );
			}

			m_ulNetCtrlTryTime = ulTimeCur;
			goto Proc_End;
			break;
		case ConnectionState::CONNECTED:
			if(Util::TimeSince(m_ulNetCtrlTime) > Const::HEARTBIT_TIMEOUT ) // connection time out
			{
				SFLog(Net, Info, "Connection Timeout CID:{0}", GetCID() );

				netChk( CloseConnection("heartbit timeout") );
				m_ulNetCtrlTime = ulTimeCur;
				goto Proc_End;
			}
			break;
		default:
			break;
		};


	Proc_End:


		return hr;
	}



} // namespace Net
} // namespace SF



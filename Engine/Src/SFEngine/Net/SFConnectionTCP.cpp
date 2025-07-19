////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "SFProtocol.h"

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

		return hr;
	}

	// called when receiving message
	Result ConnectionTCP::MyNetSocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
        ScopeContext hr([this, &pIOBuffer](Result hr)
            {
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

                SFLog(Net, Debug5, "TCP Recv CID:{0}, pending:{1}, hr:{2:X8}", GetCID(), GetPendingRecvCount(), hr);

            });

		if (pIOBuffer == nullptr)
		{
			netCheck(ResultCode::UNEXPECTED);
		}

		//if (pIOBuffer->CID != GetCID()) // We don't initialize CID any more. skip it
		//	netErr(ResultCode::INVALID_ARG);

		if (pIOBuffer != nullptr && pIOBuffer->Operation != IOBUFFER_OPERATION::OP_TCPREAD)
		{
            if (hrRes.IsSuccess())
            {
                netCheck(ResultCode::UNEXPECTED);
            }
            else
            {
                return hr;
            }
		}

		Assert(!NetSystem::IsProactorSystem() || pIOBuffer->bIsPending.load(std::memory_order_relaxed));

		// Pending recv count and registered status should be checked together so that we can prevent infinite pending recv
		// And PendingRecv should be decreased after new pending is happened
		if (GetIsIORegistered())
		{
			if (hrRes.IsSuccess())
			{
				netCheckPtr(pIOBuffer);

                hr = m_Owner.OnRecv(pIOBuffer->TransferredSize, (uint8_t*)pIOBuffer->GetPayloadPtr());
                if (hr.IsFailure())
                {
                    SFLog(Net, Debug3, "Read IO failed with CID {0}, hr={1:X8}", m_Owner.GetCID(), hr);
                }
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

		return hr;
	}

	Result ConnectionTCP::MyNetSocketIOAdapter::OnWriteReady()
	{
		Result hr;

        m_Owner.m_bWriteIsReady.store(true, std::memory_order_release);

		return hr;
	}

    Result ConnectionTCP::MyNetSocketIOAdapter::OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE* pIOBuffer)
    {
        if (m_Owner.m_SendBufferQueue.IsManagedAddress(pIOBuffer))
        {
            MutexScopeLock scopeLock(m_Owner.m_SendBufferQueueDequeueLock);

            m_Owner.m_SendBufferQueue.ReleaseRead(CircularBufferQueue::BufferItem::FromDataPtr(pIOBuffer));
            DecPendingSendCount();
            return ResultCode::SUCCESS;
        }
        else
        {
            // This path shouldn't be taken
            assert(false);
            return super::OnIOSendCompleted(hrRes, pIOBuffer);
        }
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
	ConnectionTCP::ConnectionTCP()
		: Connection(&m_NetIOAdapter)
		, m_NetIOAdapter(*this)
        , m_SendBufferQueue(GetSystemHeap(), Const::TCP_CONNECTION_SENDBUFFER_SIZE)
		, m_ReceivedDataSize(0)
		, m_uiSendNetCtrlCount(0)
		, m_IsClientConnection(false)
		, m_IsTCPSocketConnectionEstablished(true)
	{
		m_bufRecvTem.resize(Const::PACKET_SIZE_MAX * 2);

		//m_NetIOAdapter.SetWriteQueue(new(GetHeap()) WriteBufferQueue(GetHeap()));

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

		//if (m_NetIOAdapter.GetWriteQueue()) IHeap::Delete(m_NetIOAdapter.GetWriteQueue());
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

		if( !hrConnect.IsSuccess())
		{
			CloseConnection("Connecting failed");
		}
	}


	// Initialize connection
	Result ConnectionTCP::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		m_NetIOAdapter.CloseSocket();

		//m_lGuarantedSent = 0;
		//m_lGuarantedAck = 0;

		m_NetIOAdapter.ResetPendingRecvCount();
		m_NetIOAdapter.ResetPendingSendCount();


		m_uiSendNetCtrlCount = 0;
		m_ReceivedDataSize = 0;

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

		socket = Service::NetSystem->Socket(local.PeerAddress.SocketFamily, SocketType::Stream);
		if (socket == INVALID_SOCKET)
		{
			SFLog(Net, Error, "Failed to Open a Socket {0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		netChk(Service::NetSystem->SetupCommonSocketOptions(SocketType::Stream, local.PeerAddress.SocketFamily, socket));

		netChk(InitConnection(local, remote));

		result = setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
		if (result < 0)
		{
			netChk(GetLastNetSystemResult());
		}

		m_NetIOAdapter.SetSocket(local.PeerAddress.SocketFamily, SocketType::Stream, socket);

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

				if (!hr.IsSuccess())
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
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			// This is for Winsock 1.1, but happens with 2.2 sometimes?
			case (uint32_t)ResultCode::INVALID_ARG:
#endif
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
		m_ReceivedDataSize = 0;
		ResetZeroRecvCount();

		m_NetIOAdapter.CloseSocket();

		netCheck(Connection::CloseConnection(reason));

		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return hr;

		return hr;
	}


	// called when incoming message occur
	Result ConnectionTCP::OnRecv( uint uiBuffSize, uint8_t* pBuff )
	{
		Result hr = ResultCode::SUCCESS;

		if (uiBuffSize == 0)
		{
            if (!m_NetIOAdapter.GetIsIORegistered())
            {
                IncZeroRecvCount();
                if (GetZeroRecvCount() > (uint32_t)Const::CONNECTION_ZEROPACKET_MAX)
                {
                    SFLog(Net, Debug3, "TCP RecvBuf, too many zero size packet, {0}", GetZeroRecvCount());
                    //ResetZeroRecvCount();
                    Disconnect("Too many zero packets");
                }
            }
			return hr;
		}

		SFLog(Net, Debug5, "TCP RecvBuf Len={0}", uiBuffSize);

		while( uiBuffSize > 0 )
		{
			MessageHeader *pMsgHdr = NULL;

			ResetZeroRecvCount();

			// copy header portion first
			if (m_ReceivedDataSize < sizeof(MessageHeader))
			{
				uint requiredSizeForHeader = (uint)sizeof(MessageHeader) - m_ReceivedDataSize;

                uint copySize = std::min(uiBuffSize, requiredSizeForHeader);

                memcpy(m_bufRecvTem.data() + m_ReceivedDataSize, pBuff, copySize);
                m_ReceivedDataSize += copySize;
                uiBuffSize -= copySize;
                pBuff += copySize;

                // If we don't have enough data for header
                if (m_ReceivedDataSize < sizeof(MessageHeader))
                    break;
			}

            pMsgHdr = reinterpret_cast<MessageHeader*>(m_bufRecvTem.data());

            // If packet length is smaller than header size, the packet is likely corrupted
            if (pMsgHdr->MessageSize < m_ReceivedDataSize)
            {
                netCheck(ResultCode::IO_BADPACKET_SIZE);
            }

            // if Temporary buffer is too small then reallocate
            if (m_bufRecvTem.size() < pMsgHdr->MessageSize)
            {
                m_bufRecvTem.resize(AlignUp(pMsgHdr->MessageSize, 1024));

                // resize can move address
                pMsgHdr = reinterpret_cast<MessageHeader*>(m_bufRecvTem.data());
            }

			// Append remain payload
			uint requiredDataSizeForTheMessage = pMsgHdr->MessageSize - m_ReceivedDataSize;

            uint copySize = std::min(uiBuffSize, requiredDataSizeForTheMessage);
            memcpy(m_bufRecvTem.data() + m_ReceivedDataSize, pBuff, copySize);
            m_ReceivedDataSize += copySize;
            pBuff += copySize;
            uiBuffSize -= copySize;

            // Call recv callback if we have full message data
            if (m_ReceivedDataSize == pMsgHdr->MessageSize)
            {
                m_ReceivedDataSize = 0;

                hr = OnRecv(pMsgHdr);
                netCheck(hr);
            }
		}

		return hr;
	}



	Result ConnectionTCP::OnRecv(MessageHeader* pMsgHeader)
	{
		Result hr = ResultCode::SUCCESS;

		if( pMsgHeader->MessageId.GetMessageType() == EMessageType::NetCtrl )
		{
			SFLog(Net, Debug5, "TCP Ctrl Recv ip:{0}, msg:{1}, Len:{2}",
				GetRemoteInfo().PeerAddress, 
				pMsgHeader->MessageId, pMsgHeader->MessageSize);

			netCheck( ProcNetCtrl(reinterpret_cast<const MsgNetCtrlBuffer*>(pMsgHeader)) );
		}
		else
		{
			hr  = Connection::OnRecv(pMsgHeader);
			netCheck( hr );
		}

		return hr;
	}

    Result ConnectionTCP::SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0)
    {
        Result hr = ResultCode::SUCCESS;
        Result hrTem;

        MsgNetCtrlBuffer netCtrlBuffer{};
        MessageHeader* pHeader = &netCtrlBuffer.Header;

        netCheck(MakeNetCtrl(pHeader, uiCtrlCode, uiSequence, returnMsgID, parameter0));

        hrTem = SendRaw(pHeader);
        if (!hrTem.IsSuccess())
        {
            SFLog(Net, Debug4, "NetCtrl Send failed : CID:{0}, msg:{1:X8}, seq:{2}, hr={3:X8}",
                GetCID(),
                returnMsgID.ID,
                uiSequence,
                hrTem);

            // ignore IO send fail except connection closed
            if (hrTem == ((Result)ResultCode::IO_CONNECTION_CLOSED))
            {
                return hr;
            }
        }

        return hr;
    }

    Result ConnectionTCP::SendRaw(const MessageHeader* pMsgHeader)
    {
        Result hr;

        if (!m_NetIOAdapter.GetIsIORegistered())
            return ResultCode::SUCCESS_FALSE;

        netCheckMem(pMsgHeader);
        MessageID msgID = pMsgHeader->MessageId;

        uint uiPolicy = msgID.IDs.Protocol;
        if ((uiPolicy == 0 && msgID.IDs.Type != 0)
            || uiPolicy >= MessageProtocol::Max) // invalid policy
        {
            netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
        }

        CircularBufferQueue::ItemWritePtr itemWritePtr = m_SendBufferQueue.AllocateWrite(sizeof(IOBUFFER_WRITE) + pMsgHeader->MessageSize);
        if (!itemWritePtr)
        {
            if (pMsgHeader->MessageId.IDs.Reliability)
            {
                SFLog(Net, Warning, "ConnectionTCP::SendRaw, Send buffer overflow");
            }
            return hr = ResultCode::IO_SEND_FAIL;
        }

        IOBUFFER_WRITE* pSendBuffer = new(itemWritePtr.data()) IOBUFFER_WRITE;

        assert(pSendBuffer == itemWritePtr.data());

        MessageHeader* pNewHeader = reinterpret_cast<MessageHeader*>(pSendBuffer + 1);
        memcpy(pNewHeader, pMsgHeader, pMsgHeader->MessageSize);
        pSendBuffer->SetupSendTCP(pMsgHeader->MessageSize, reinterpret_cast<uint8_t*>(pNewHeader));

        // Release before handover to buffer send
        itemWritePtr.Reset();

        // kick send queue processing
        m_bWriteIsReady.store(true, std::memory_order_release);

        return hr;
    }

    Result ConnectionTCP::ProcessSendQueue()
    {
        Result hr;

        MutexScopeLock scopeLock(m_SendBufferQueueDequeueLock);

        CircularBufferQueue::ItemIterator itemPtr = m_SendBufferQueue.TailIterator();
        for (; itemPtr; ++itemPtr)
        {
            if (!itemPtr.StartRead())
                break;

            IOBUFFER_WRITE* pSendBuffer = reinterpret_cast<IOBUFFER_WRITE*>(itemPtr.data());

            // WriteBuffer will trigger OnIOSendCompleted if transfer is completed, and the item will be released
            hr = m_NetIOAdapter.WriteBuffer(pSendBuffer);
            if (!hr.IsSuccess())
            {
                // need to try again
                itemPtr.CancelRead();
                break;
            }

            // The read mode will be cleared in OnIOSendCompleted

            m_NetIOAdapter.IncPendingSendCount();
        }

        return hr;
    }


    Result ConnectionTCP::SendMsg(const MessageHeader* pMsgHeader)
    {
        MessageID msgID;

        ScopeContext hr([this, &msgID](Result hr)
            {
                if (hr)
                {
                    if (msgID.GetMessageType() == EMessageType::NetCtrl)
                    {
                        SFLog(Net, Debug6, "TCP Ctrl CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
                    }
                    else
                    {
                        SFLog(Net, Debug5, "TCP Send CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
                    }
                }

            });

        if (GetConnectionState() == ConnectionState::DISCONNECTED)
            return hr = ResultCode::IO_NOT_CONNECTED;

        msgID = pMsgHeader->MessageId;

        if ((pMsgHeader->MessageId.GetMessageType() != EMessageType::NetCtrl && GetConnectionState() == ConnectionState::DISCONNECTING)
            || GetConnectionState() == ConnectionState::DISCONNECTED)
        {
            // Send fail by connection closed
            return hr;
        }

        if (pMsgHeader->MessageSize > (uint)Const::TCP_PACKET_SIZE_MAX)
        {
            netCheck(ResultCode::IO_BADPACKET_TOOBIG);
        }

        Protocol::PrintDebugMessage("Send", pMsgHeader);

        netCheck(SendRaw(pMsgHeader));

        return hr;
    }

	// Update net control, process connection heartbeat, ... etc
	Result ConnectionTCP::TickUpdate()
	{
		Result hr;

        netCheck(super::TickUpdate());

        if (GetConnectionState() == ConnectionState::DISCONNECTED)
            return hr;


		if (!GetIsIORegistered())
		{
			SFLog(Net, Debug, "Close connection because it's kicked from net IO, CID:{0}", GetCID());
			netCheck(CloseConnection("Kicked from IO system"));
            return hr;
		}

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

        // tick update send queue
        bool bWriteIsReady = m_bWriteIsReady.exchange(false, std::memory_order_consume);
        if (bWriteIsReady) // if write ready is triggered this tick
        {
            ProcessSendQueue();
            //m_NetIOAdapter.ProcessSendQueue();
        }

        return hr;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network client connection class
	//

	// Constructor
	ConnectionTCPClient::ConnectionTCPClient()
		: ConnectionTCP()
	{
		// We can't set tick here. There is a small chance that tick update finished before this object's reference count got increased
		//SetTickGroup(EngineTaskTick::AsyncTick);

		SetNetCtrlAction(NetCtrlCode_TimeSyncRtn, &m_HandleTimeSyncRtn);

        AddStateAction(ConnectionState::WAITRW, &m_WaitRW);
		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::CONNECTING, &m_SendConnect);
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
	ConnectionTCPServer::ConnectionTCPServer()
		: ConnectionTCP()
	{
		//Assert(GetMyNetIOAdapter().GetWriteQueue() != nullptr);

		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);
	}

	ConnectionTCPServer::~ConnectionTCPServer()
	{
	}

} // namespace Net
} // namespace SF

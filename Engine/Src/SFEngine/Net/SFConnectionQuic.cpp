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
#include "Net/SFConnectionQuic.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"

#include "msquic.h"

namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Client Mobile UDP Network connection class
	//



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network connection class
	//

	// Constructor
	ConnectionQuic::ConnectionQuic(IHeap& heap)
		: Connection(heap, nullptr)
        , m_SendBufferQueue(heap, Const::TCP_CONNECTION_SENDBUFFER_SIZE)
		, m_ReceivedDataSize(0)
		, m_IsClientConnection(false)
	{
		m_bufRecvTem.resize(Const::PACKET_SIZE_MAX * 2);

		//m_NetIOAdapter.SetWriteQueue(new(GetHeap()) WriteBufferQueue(GetHeap()));

		//SetNetCtrlAction(NetCtrlCode_Ack, &m_HandleAck);
		//SetNetCtrlAction(NetCtrlCode_Nack, &m_HandleNack);
		//SetNetCtrlAction(NetCtrlCode_Heartbeat, &m_HandleHeartbeat);
		//SetNetCtrlAction(NetCtrlCode_TimeSync, &m_HandleTimeSync);
		//SetNetCtrlAction(NetCtrlCode_Connect, &m_HandleConnect);
		//SetNetCtrlAction(NetCtrlCode_Disconnect, &m_HandleDisconnect);

	}

	ConnectionQuic::~ConnectionQuic()
	{
	}


	bool ConnectionQuic::CanDelete()
	{
        return true;
	}

	void ConnectionQuic::Dispose()
	{
		ClearQueues();

		super::Dispose();
	}



	// Clear Queue
	Result ConnectionQuic::ClearQueues()
	{
		return ResultCode::SUCCESS;
	}



	// Called on connection result
	void ConnectionQuic::OnConnectionResult( Result hrConnect )
	{
		Connection::OnConnectionResult( hrConnect );

		if( !hrConnect.IsSuccess())
		{
			CloseConnection("Connecting failed");
		}
	}


	// Initialize connection
	Result ConnectionQuic::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
        Result hr;

		m_ReceivedDataSize = 0;

		m_IsClientConnection = false;

		Assert(local.PeerClass != NetClass::Unknown);

		// ignore incoming socket value
		SFCheck(Net, Connection::InitConnection(local, remote ));

        return hr;
	}

	Result ConnectionQuic::Connect(PeerInfo local, const PeerInfo& remote)
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
			netCheck(ResultCode::UNEXPECTED);
		}

		netCheck(Service::NetSystem->SetupCommonSocketOptions(SocketType::Stream, local.PeerAddress.SocketFamily, socket));

		netCheck(InitConnection(local, remote));

		result = setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
		if (result < 0)
		{
			netCheck(GetLastNetSystemResult());
		}

		socket = INVALID_SOCKET;


		if (socket != INVALID_SOCKET)
			Service::NetSystem->CloseSocket(socket);

		return hr;
	}

	// Close connection
	Result ConnectionQuic::CloseConnection(const char* reason)
	{
		Result hr = ResultCode::SUCCESS;

		//socket
		m_ReceivedDataSize = 0;
		ResetZeroRecvCount();

		netCheck(Connection::CloseConnection(reason));

		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return hr;

		return hr;
	}


	// called when incoming message occur
	Result ConnectionQuic::OnRecv( uint uiBuffSize, uint8_t* pBuff )
	{
		Result hr = ResultCode::SUCCESS;

		return hr;
	}



	Result ConnectionQuic::OnRecv(MessageHeader* pMsgHeader)
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

    Result ConnectionQuic::SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0)
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

    Result ConnectionQuic::SendRaw(const MessageHeader* pMsgHeader)
    {
        Result hr;

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
                SFLog(Net, Warning, "ConnectionQuic::SendRaw, Send buffer overflow");
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

    Result ConnectionQuic::ProcessSendQueue()
    {
        Result hr;

        MutexScopeLock scopeLock(m_SendBufferQueueDequeueLock);

        CircularBufferQueue::ItemIterator itemPtr = m_SendBufferQueue.TailIterator();
        for (; itemPtr; ++itemPtr)
        {
            if (!itemPtr.StartRead())
                break;

            //IOBUFFER_WRITE* pSendBuffer = reinterpret_cast<IOBUFFER_WRITE*>(itemPtr.data());

            //// WriteBuffer will trigger OnIOSendCompleted if transfer is completed, and the item will be released
            //hr = m_NetIOAdapter.WriteBuffer(pSendBuffer);
            //if (!hr.IsSuccess())
            //{
            //    // need to try again
            //    itemPtr.CancelRead();
            //    break;
            //}

            // The read mode will be cleared in OnIOSendCompleted

            //m_NetIOAdapter.IncPendingSendCount();
        }

        return hr;
    }


    Result ConnectionQuic::SendMsg(const MessageHeader* pMsgHeader)
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
	Result ConnectionQuic::TickUpdate()
	{
		Result hr;

        netCheck(super::TickUpdate());

        if (GetConnectionState() == ConnectionState::DISCONNECTED)
            return hr;


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
	ConnectionQuicClient::ConnectionQuicClient(IHeap& heap)
		: ConnectionQuic(heap)
	{
		// We can't set tick here. There is a small chance that tick update finished before this object's reference count got increased
		//SetTickGroup(EngineTaskTick::AsyncTick);

		//SetNetCtrlAction(NetCtrlCode_TimeSyncRtn, &m_HandleTimeSyncRtn);

  //      AddStateAction(ConnectionState::WAITRW, &m_WaitRW);
		//AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		//AddStateAction(ConnectionState::CONNECTING, &m_SendConnect);
		//AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		//AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);
	}

	ConnectionQuicClient::~ConnectionQuicClient()
	{
	}

	// Initialize connection
	Result ConnectionQuicClient::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		if (local.PeerClass != NetClass::Client)
			return ResultCode::INVALID_ARG;

		Result hr = ConnectionQuic::InitConnection(local, remote );

		return hr;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network client connection class
	//

	// Constructor
	ConnectionQuicServer::ConnectionQuicServer(IHeap& heap)
		: ConnectionQuic(heap)
	{
		//Assert(GetMyNetIOAdapter().GetWriteQueue() != nullptr);

		//AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		//AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		//AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);
	}

	ConnectionQuicServer::~ConnectionQuicServer()
	{
	}

} // namespace Net
} // namespace SF

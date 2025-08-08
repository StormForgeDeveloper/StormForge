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

#include "Online/Quic/SFQuicService.h"

#include "Net/SFNetToString.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionQuic.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"

#include <msquic.h>

namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//


    _IRQL_requires_max_(DISPATCH_LEVEL)
        _Function_class_(QUIC_CONNECTION_CALLBACK)
        QUIC_STATUS
        QUIC_API
        ConnectionQuic::QuicConnectionCallback(
            _In_ HQUIC QuicConnection,
            _In_opt_ void* Context,
            _Inout_ QUIC_CONNECTION_EVENT* Event
        )
    {
        auto* Connection = reinterpret_cast<ConnectionQuic*>(Context);

        switch (Event->Type) {
        case QUIC_CONNECTION_EVENT_CONNECTED:
            Connection->OnQuicConnected();
            break;
        case QUIC_CONNECTION_EVENT_DATAGRAM_STATE_CHANGED:
            Connection->OnQuicDatagramChanged(Event->DATAGRAM_STATE_CHANGED.SendEnabled, Event->DATAGRAM_STATE_CHANGED.MaxSendLength);
            break;
        case QUIC_CONNECTION_EVENT_SHUTDOWN_INITIATED_BY_TRANSPORT:
            //
            // The connection has been shut down by the transport. Generally, this
            // is the expected way for the connection to shut down with this
            // protocol.
            //
            if (Event->SHUTDOWN_INITIATED_BY_TRANSPORT.Status == QUIC_STATUS_CONNECTION_IDLE) {
                SFLog(Quic, Info, "CID:{} Successfully shut down on idle.", Connection->GetCID());
            }
            else {
                SFLog(Quic, Info, "CID:{} Shut down by transport, {:#08X}", Connection->GetCID(), (uint)Event->SHUTDOWN_INITIATED_BY_TRANSPORT.Status);
            }
            break;
        case QUIC_CONNECTION_EVENT_SHUTDOWN_INITIATED_BY_PEER:
            //
            // The connection was explicitly shut down by the peer.
            //
            SFLog(Quic, Info, "CID:{} Shut down by peer, {:#016X}", Connection->GetCID(), (unsigned long long)Event->SHUTDOWN_INITIATED_BY_PEER.ErrorCode);
            break;
        case QUIC_CONNECTION_EVENT_SHUTDOWN_COMPLETE:
            //
            // The connection has completed the shutdown process and is ready to be
            // safely cleaned up.
            //
            SFLog(Quic, Info, "CID:{} connection shutdown completed", Connection->GetCID());
            Connection->OnQuicConnectionShutdownComplete(Event->SHUTDOWN_COMPLETE.AppCloseInProgress);
            break;
        case QUIC_CONNECTION_EVENT_RESUMPTION_TICKET_RECEIVED:
            //
            // A resumption ticket (also called New Session Ticket or NST) was
            // received from the server.
            //
            SFLog(Quic, Debug, "CID:{} Resumption ticket received ({} bytes):", Connection->GetCID(), Event->RESUMPTION_TICKET_RECEIVED.ResumptionTicketLength);
            for (uint32_t i = 0; i < Event->RESUMPTION_TICKET_RECEIVED.ResumptionTicketLength; i++) {
                SFLog(Quic, Debug1, "{:#02X}", (uint8_t)Event->RESUMPTION_TICKET_RECEIVED.ResumptionTicket[i]);
            }
            break;
        case QUIC_CONNECTION_EVENT_IDEAL_PROCESSOR_CHANGED:
            SFLog(Quic, Debug,
                "CID:{} Ideal Processor is: {}, Partition Index {}",
                Connection->GetCID(),
                Event->IDEAL_PROCESSOR_CHANGED.IdealProcessor,
                Event->IDEAL_PROCESSOR_CHANGED.PartitionIndex);
            break;
        case QUIC_CONNECTION_EVENT_PEER_STREAM_STARTED:
            //
            // The peer has started/created a new stream. The app MUST set the
            // callback handler before returning.
            //
            SFLog(Quic, Debug, "[strm][{},{}] Peer started", Connection->GetCID(), Event->PEER_STREAM_STARTED.Stream);
            Connection->OnStreamStarted(Event->PEER_STREAM_STARTED.Stream);
            break;
        case QUIC_CONNECTION_EVENT_RESUMED:
            SFLog(Quic, Debug, "[strm][{},{}] Connection resume", Connection->GetCID());
            break;
        default:
            break;
        }

        return QUIC_STATUS_SUCCESS;
    }

    //
    // The clients's callback for stream events from MsQuic.
    //
    _IRQL_requires_max_(DISPATCH_LEVEL)
        _Function_class_(QUIC_STREAM_CALLBACK)
        QUIC_STATUS
        QUIC_API
        ConnectionQuic::StreamCallback(
            _In_ HQUIC Stream,
            _In_opt_ void* Context,
            _Inout_ QUIC_STREAM_EVENT* Event
        )
    {
        auto* Connection = reinterpret_cast<ConnectionQuic*>(Context);

        switch (Event->Type) {
        case QUIC_STREAM_EVENT_SEND_COMPLETE:
            //
            // A previous StreamSend call has completed, and the context is being
            // returned back to the app.
            //
            SFLog(Quic, Debug3, "[strm][{},{}] Data sent", Connection->GetCID(), Stream);
            Connection->OnSendCompleted(Stream, Event->SEND_COMPLETE.ClientContext);
            break;
        case QUIC_STREAM_EVENT_RECEIVE:
            //
            // Data was received from the peer on the stream.
            //
            SFLog(Quic, Debug3, "[strm][{},{}] Data received, abOffset:{}, count:{}, totalSize:{}", Connection->GetCID(), Stream, Event->RECEIVE.AbsoluteOffset, Event->RECEIVE.BufferCount, Event->RECEIVE.TotalBufferLength);
            Connection->OnRecvCompleted(Stream, Event->RECEIVE.BufferCount, Event->RECEIVE.Buffers, Event->RECEIVE.Flags);
            break;
        case QUIC_STREAM_EVENT_PEER_SEND_ABORTED:
            //
            // The peer gracefully shut down its send direction of the stream.
            //
            SFLog(Quic, Debug, "[strm][{},{}] Peer aborted", Connection->GetCID(), Stream);
            Connection->OnStreamPeerSendAborted(Stream);
            break;
        case QUIC_STREAM_EVENT_PEER_SEND_SHUTDOWN:
            //
            // The peer aborted its send direction of the stream.
            //
            SFLog(Quic, Debug, "[strm][{},{}] Peer shut down", Connection->GetCID(), Stream);
            Connection->OnStreamPeerSendShutdown(Stream);
            break;
        case QUIC_STREAM_EVENT_SHUTDOWN_COMPLETE:
            //
            // Both directions of the stream have been shut down and MsQuic is done
            // with the stream. It can now be safely cleaned up.
            //
            SFLog(Quic, Debug3, "[strm][{},{}] shutdown completely", Connection->GetCID(), Stream);
            Connection->OnStreamPeerShutdownCompleted(Stream, Event->SHUTDOWN_COMPLETE.AppCloseInProgress, Event->SHUTDOWN_COMPLETE.ConnectionClosedRemotely);
            break;
        default:
            break;
        }
        return QUIC_STATUS_SUCCESS;
    }



    void EncodeHexBuffer(
            _In_reads_(BufferLen) uint8_t* Buffer,
            _In_ uint8_t BufferLen,
            _Out_writes_bytes_(2 * BufferLen) char* HexString
        )
    {
#define HEX_TO_CHAR(x) ((x) > 9 ? ('a' + ((x) - 10)) : '0' + (x))
        for (uint8_t i = 0; i < BufferLen; i++) {
            HexString[i * 2] = HEX_TO_CHAR(Buffer[i] >> 4);
            HexString[i * 2 + 1] = HEX_TO_CHAR(Buffer[i] & 0xf);
        }
    }

    void WriteSslKeyLogFile(
            _In_z_ const char* FileName,
            _In_ QUIC_TLS_SECRETS* TlsSecrets
        )
    {
        printf("Writing SSLKEYLOGFILE at %s\n", FileName);
        FILE* File = NULL;
#ifdef _WIN32
        File = _fsopen(FileName, "ab", _SH_DENYNO);
#else
        File = fopen(FileName, "ab");
#endif

        if (File == NULL) {
            printf("Failed to open sslkeylogfile %s\n", FileName);
            return;
        }
        if (fseek(File, 0, SEEK_END) == 0 && ftell(File) == 0) {
            fprintf(File, "# TLS 1.3 secrets log file, generated by msquic\n");
        }

        char ClientRandomBuffer[(2 * sizeof(((QUIC_TLS_SECRETS*)0)->ClientRandom)) + 1] = { 0 };

        char TempHexBuffer[(2 * QUIC_TLS_SECRETS_MAX_SECRET_LEN) + 1] = { 0 };
        if (TlsSecrets->IsSet.ClientRandom) {
            EncodeHexBuffer(
                TlsSecrets->ClientRandom,
                (uint8_t)sizeof(TlsSecrets->ClientRandom),
                ClientRandomBuffer);
        }

        if (TlsSecrets->IsSet.ClientEarlyTrafficSecret) {
            EncodeHexBuffer(
                TlsSecrets->ClientEarlyTrafficSecret,
                TlsSecrets->SecretLength,
                TempHexBuffer);
            fprintf(
                File,
                "CLIENT_EARLY_TRAFFIC_SECRET %s %s\n",
                ClientRandomBuffer,
                TempHexBuffer);
        }

        if (TlsSecrets->IsSet.ClientHandshakeTrafficSecret) {
            EncodeHexBuffer(
                TlsSecrets->ClientHandshakeTrafficSecret,
                TlsSecrets->SecretLength,
                TempHexBuffer);
            fprintf(
                File,
                "CLIENT_HANDSHAKE_TRAFFIC_SECRET %s %s\n",
                ClientRandomBuffer,
                TempHexBuffer);
        }

        if (TlsSecrets->IsSet.ServerHandshakeTrafficSecret) {
            EncodeHexBuffer(
                TlsSecrets->ServerHandshakeTrafficSecret,
                TlsSecrets->SecretLength,
                TempHexBuffer);
            fprintf(
                File,
                "SERVER_HANDSHAKE_TRAFFIC_SECRET %s %s\n",
                ClientRandomBuffer,
                TempHexBuffer);
        }

        if (TlsSecrets->IsSet.ClientTrafficSecret0) {
            EncodeHexBuffer(
                TlsSecrets->ClientTrafficSecret0,
                TlsSecrets->SecretLength,
                TempHexBuffer);
            fprintf(
                File,
                "CLIENT_TRAFFIC_SECRET_0 %s %s\n",
                ClientRandomBuffer,
                TempHexBuffer);
        }

        if (TlsSecrets->IsSet.ServerTrafficSecret0) {
            EncodeHexBuffer(
                TlsSecrets->ServerTrafficSecret0,
                TlsSecrets->SecretLength,
                TempHexBuffer);
            fprintf(
                File,
                "SERVER_TRAFFIC_SECRET_0 %s %s\n",
                ClientRandomBuffer,
                TempHexBuffer);
        }

        fflush(File);
        fclose(File);
    }


	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network connection class
	//

	// Constructor
	ConnectionQuic::ConnectionQuic()
		: Connection(nullptr)
	{
        AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
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

        auto msQuic = Service::Quic->GetQuic();
        if (msQuic)
        {
            if (m_Stream)
            {
                msQuic->StreamClose(m_Stream);
            }

            if (m_Connection)
            {
                msQuic->ConnectionClose(m_Connection);
            }
        }
        m_Stream = nullptr;
        m_Connection = nullptr;


		super::Dispose();
	}

    void ConnectionQuic::SetDefaultStream(HQUIC stream)
    {
        if (m_Stream)
        {
            SFLog(Quic, Warning, "Replacing existing default stream {0} with new stream {1}", m_Stream, stream);

            auto msQuic = Service::Quic->GetQuic();
            if (msQuic)
            {
                msQuic->StreamClose(m_Stream);
            }
        }
        m_Stream = stream;
    }

    Result ConnectionQuic::OpenStream()
    {
        Result hr;

        auto msQuic = Service::Quic->GetQuic();
        SFCheckPtr(Quic, msQuic);

        HQUIC Stream{};
        QUIC_STATUS Status{};

        //
        // Create/allocate a new bidirectional stream. The stream is just allocated
        // and no QUIC stream identifier is assigned until it's started.
        //
        Status = msQuic->StreamOpen(GetQuicConnection(), QUIC_STREAM_OPEN_FLAG_NONE, StreamCallback, this, &Stream);
        if (QUIC_FAILED(Status))
        {
            SFLog(Quic, Error, "StreamOpen failed, Status:{:#08X}", Status);

            return Service::Quic->QuicStatusToResult(Status);
        }

        SFLog(Quic, Info, "[strm][{}:{}] Starting...", GetCID(), Stream);

        //
        // Starts the bidirectional stream. By default, the peer is not notified of
        // the stream being started until data is sent on the stream.
        //
        Status = msQuic->StreamStart(Stream, QUIC_STREAM_START_FLAG_NONE);
        if (QUIC_FAILED(Status))
        {
            SFLog(Quic, Error, "StreamStart failed, {:#08X}", Status);
            msQuic->StreamClose(Stream);
            return Service::Quic->QuicStatusToResult(Status);
        }

        SetDefaultStream(Stream);

        return hr;
    }

    Result ConnectionQuic::CloseStream(HQUIC stream)
    {
        Result hr;
        auto msQuic = Service::Quic->GetQuic();
        SFCheckPtr(Quic, msQuic);
        if (stream)
        {
            SFLog(Quic, Info, "[strm][{}:{}] Closing stream", GetCID(), stream);
            msQuic->StreamClose(stream);
            if (m_Stream == stream)
            {
                m_Stream = nullptr; // reset default stream
            }
        }

        return hr;
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

		Assert(local.PeerClass != NetClass::Unknown);

		// ignore incoming socket value
		SFCheck(Net, Connection::InitConnection(local, remote ));

        return hr;
	}

	Result ConnectionQuic::Connect(PeerInfo local, const PeerInfo& remote)
	{
		Result hr;

		if (StrUtil::IsNullOrEmpty(local.PeerAddress.Address))
		{
			if (remote.PeerAddress.SocketFamily == SockFamily::IPV4)
				Net::GetLocalAddressIPv4(local.PeerAddress);
			else
				Net::GetLocalAddressIPv6(local.PeerAddress);
		}

		netCheck(InitConnection(local, remote));

        SFCheckPtr(Quic, m_Connection);

		return hr;
	}

	// Close connection
	Result ConnectionQuic::CloseConnection(const char* reason)
	{
		Result hr = ResultCode::SUCCESS;

        if (GetConnectionState() == ConnectionState::DISCONNECTED)
            return hr;

        if (m_Connection)
        {
            auto msQuic = Service::Quic->GetQuic();
            if (msQuic)
            {
                msQuic->ConnectionShutdown(m_Connection, QUIC_CONNECTION_SHUTDOWN_FLAG_NONE, 0);
            }
            m_Connection = nullptr;
        }

		netCheck(super::CloseConnection(reason));

		return hr;
	}

    Result ConnectionQuic::Disconnect(const char* reason)
    {
        return CloseConnection(reason);
    }

    Result ConnectionQuic::SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0)
    {
        Result hr;
        Result hrTem;

        auto quicState = GetQuicState();
        if (quicState != EQuicState::Handshaking && quicState != EQuicState::Connected)
        {
            SFLog(Quic, Warning, "SendNetCtrl failed due to Quic state {0} not ready for sending", quicState);
            return ResultCode::IO_SYSNOTREADY;
        }

        MsgNetCtrlBuffer netCtrlBuffer{};
        MessageHeader* pHeader = &netCtrlBuffer.Header;

        SFCheck(Net, MakeNetCtrl(pHeader, uiCtrlCode, uiSequence, returnMsgID, parameter0));

        SFCheck(Net, SendToStream(GetDefaultStream(), pHeader));

        return hr;
    }

    Result ConnectionQuic::SendToStream(HQUIC Stream, const MessageHeader* pMsgHeader)
    {
        Result hr;

        auto quicState = GetQuicState();
        if (quicState != EQuicState::Handshaking && quicState != EQuicState::Connected)
        {
            SFLog(Quic, Warning, "SendNetCtrl failed due to Quic state {0} not ready for sending", quicState);
            return ResultCode::IO_SYSNOTREADY;
        }

        SFCheckPtr(Quic, pMsgHeader);
        MessageID msgID = pMsgHeader->MessageId;

        uint uiPolicy = msgID.IDs.Protocol;
        if ((uiPolicy == 0 && msgID.IDs.Type != 0)
            || uiPolicy >= MessageProtocol::Max) // invalid policy
        {
            netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
        }

        auto msQuic = Service::Quic->GetQuic();
        SFCheckPtr(Quic, msQuic);

        SFCheckPtr(Quic, Stream);
        
        QUIC_STATUS Status{};

        //
        // Allocates and builds the buffer to send over the stream.
        //
        uint8_t* SendBufferRaw = (uint8_t*)malloc(sizeof(QUIC_BUFFER) + pMsgHeader->MessageSize);
        if (SendBufferRaw == nullptr)
        {
            SFLog(Quic, Error, "SendBuffer allocation failed!\n");
            Status = QUIC_STATUS_OUT_OF_MEMORY;
            return Service::Quic->QuicStatusToResult(Status);
        }

        QUIC_BUFFER* SendBuffer = (QUIC_BUFFER*)SendBufferRaw;
        SendBuffer->Buffer = SendBufferRaw + sizeof(QUIC_BUFFER);
        SendBuffer->Length = pMsgHeader->MessageSize;

        SFLog(Quic, Debug3, "[strm][{}] Sending data... size:{}", Stream, SendBuffer->Length);

        QUIC_SEND_FLAGS sendFlags = QUIC_SEND_FLAG_ALLOW_0_RTT; // QUIC_SEND_FLAG_FIN
        //
        // Sends the buffer over the stream. Note the FIN flag is passed along with
        // the buffer. This indicates this is the last buffer on the stream and the
        // the stream is shut down (in the send direction) immediately after.
        //
        Status = msQuic->StreamSend(Stream, SendBuffer, 1, sendFlags, SendBuffer);
        if (QUIC_FAILED(Status))
        {
            SFLog(Quic, Error, "StreamSend failed, {}", Status);
            free(SendBufferRaw);
            return Service::Quic->QuicStatusToResult(Status);
        }


        //CircularBufferQueue::ItemWritePtr itemWritePtr = m_SendBufferQueue.AllocateWrite(sizeof(IOBUFFER_WRITE) + pMsgHeader->MessageSize);
        //if (!itemWritePtr)
        //{
        //    if (pMsgHeader->MessageId.IDs.Reliability)
        //    {
        //        SFLog(Net, Warning, "ConnectionTCP::SendRaw, Send buffer overflow");
        //    }
        //    return hr = ResultCode::IO_SEND_FAIL;
        //}

        //IOBUFFER_WRITE* pSendBuffer = new(itemWritePtr.data()) IOBUFFER_WRITE;

        //assert(pSendBuffer == itemWritePtr.data());

        //MessageHeader* pNewHeader = reinterpret_cast<MessageHeader*>(pSendBuffer + 1);
        //memcpy(pNewHeader, pMsgHeader, pMsgHeader->MessageSize);
        //pSendBuffer->SetupSendTCP(pMsgHeader->MessageSize, reinterpret_cast<uint8_t*>(pNewHeader));

        //// Release before handover to buffer send
        //itemWritePtr.Reset();

        //// kick send queue processing
        //m_bWriteIsReady.store(true, std::memory_order_release);

        return hr;
    }

    Result ConnectionQuic::SendThroughAny(const MessageHeader* pMsgHeader)
    {
        Result hr;

        if (!m_DatagramEnabled)
        {
            SendToStream(GetDefaultStream(), pMsgHeader);
        }

        QUIC_STATUS Status{};

        auto quicState = GetQuicState();
        if (quicState != EQuicState::Handshaking && quicState != EQuicState::Connected)
        {
            SFLog(Quic, Warning, "SendNetCtrl failed due to Quic state {0} not ready for sending", quicState);
            return ResultCode::IO_SYSNOTREADY;
        }

        auto msQuic = Service::Quic->GetQuic();
        SFCheckPtr(Quic, msQuic);

        //
        // Allocates and builds the buffer to send over the stream.
        //
        uint8_t* SendBufferRaw = (uint8_t*)malloc(sizeof(QUIC_BUFFER) + pMsgHeader->MessageSize);
        if (SendBufferRaw == nullptr)
        {
            SFLog(Quic, Error, "SendBuffer allocation failed!\n");
            Status = QUIC_STATUS_OUT_OF_MEMORY;
            return Service::Quic->QuicStatusToResult(Status);
        }

        QUIC_BUFFER* SendBuffer = (QUIC_BUFFER*)SendBufferRaw;
        SendBuffer->Buffer = SendBufferRaw + sizeof(QUIC_BUFFER);
        SendBuffer->Length = pMsgHeader->MessageSize;

        SFLog(Quic, Debug3, "[datagram][{}] Sending data... size:{}", SendBuffer->Length);

        QUIC_SEND_FLAGS sendFlags = QUIC_SEND_FLAG_ALLOW_0_RTT; // QUIC_SEND_FLAG_FIN

        Status = msQuic->DatagramSend(GetQuicConnection(), SendBuffer, 1, sendFlags, SendBuffer);
        if (QUIC_FAILED(Status))
        {
            SFLog(Quic, Error, "DatagramSend failed, {}", Status);
            free(SendBufferRaw);
            return Service::Quic->QuicStatusToResult(Status);
        }

        return hr;
    }

    Result ConnectionQuic::OnQuicConnected()
    {
        Result hr;

        // Do nothing. Each server/client connection should override this method

        return hr;
    }

    void ConnectionQuic::OnQuicDatagramChanged(bool bEnabled, uint maxPacketSize)
    {
        m_DatagramEnabled = bEnabled;
        m_MaxDatagramSize = maxPacketSize;
    }

    Result ConnectionQuic::OnStreamStarted(HQUIC Stream)
    {
        Result hr;

        if (m_Stream)
        {
            SFLog(Quic, Warning, "Replacing existing default stream {0} with new stream {1}", m_Stream, Stream);
            auto msQuic = Service::Quic->GetQuic();
            if (msQuic)
            {
                msQuic->StreamClose(m_Stream);
            }
        }

        SetDefaultStream(Stream);

        auto msQuic = Service::Quic->GetQuic();
        if (msQuic && Stream)
        {
            msQuic->SetCallbackHandler(Stream, (void*)&ConnectionQuic::StreamCallback, GetQuicConnection());
        }

        return hr;
    }

    void ConnectionQuic::OnSendCompleted(HQUIC Stream, void* sendContext)
    {
        free(sendContext);
    }

    // On recv  completed
    void ConnectionQuic::OnRecvCompleted(HQUIC Stream, uint bufferCount, const QUIC_BUFFER* buffers, QUIC_RECEIVE_FLAGS flags)
    {
        for (uint i = 0; i < bufferCount; ++i)
        {
            const QUIC_BUFFER& buffer = buffers[i];
            if (buffer.Length == 0)
                continue;

            //SFLog(Quic, Debug3, "[strm][{},{}] Received data, size:{}", GetCID(), Stream, buffer.Length);
            // Process received data
            Result hr = OnRecv(buffer.Length, buffer.Buffer);
            if (!hr.IsSuccess())
            {
                SFLog(Quic, Error, "OnRecv failed with error: {}", hr);
                // Handle error if needed
                break;
            }
        }
    }


	// called when incoming message occur
	Result ConnectionQuic::OnRecv( uint uiBuffSize, uint8_t* pBuff )
	{
		Result hr = ResultCode::SUCCESS;

        size_t prevSize = m_ReceivedData.size();
        m_ReceivedData.resize(m_ReceivedData.size() + uiBuffSize);
        memcpy(m_ReceivedData.data() + prevSize, pBuff, uiBuffSize);

        size_t processedSize = 0;
        while (m_ReceivedData.size() > sizeof(MessageHeader))
        {
            MessageHeader* pMsgHdr = reinterpret_cast<MessageHeader*>(m_ReceivedData.data());

            // If packet length is smaller than header size, the packet is likely corrupted
            if (pMsgHdr->MessageSize > m_ReceivedData.size())
            {
                // we need more data to process
                break;
            }

            processedSize += pMsgHdr->MessageSize;

            hr = OnRecv(pMsgHdr);
            if (hr.IsFailure())
            {
                SFLog(Quic, Error, "OnRecv failed with error: {}", hr);
                // disconnect if error occurs ?
                break;
            }
        }

        if (m_ReceivedData.size() > processedSize)
        {
            // Move remaining data to the front of the buffer
            memmove(m_ReceivedData.data(), m_ReceivedData.data() + processedSize, m_ReceivedData.size() - processedSize);
            m_ReceivedData.resize(m_ReceivedData.size() - processedSize);
        }
        else
        {
            // Clear the buffer if all data has been processed
            m_ReceivedData.clear();
        }

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

        //netCheck(SendRaw(pMsgHeader));

        return hr;
    }

	// Update net control, process connection heartbeat, ... etc
	Result ConnectionQuic::TickUpdate()
	{
		Result hr;

        netCheck(super::TickUpdate());

        if (GetConnectionState() == ConnectionState::DISCONNECTED)
            return hr;


        return hr;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Quic client connection class
	//


    QUIC_TLS_SECRETS ConnectionQuicClient::m_ClientSecrets;


	// Constructor
	ConnectionQuicClient::ConnectionQuicClient()
		: ConnectionQuic()
	{
		// We can't set tick here. There is a small chance that tick update finished before this object's reference count got increased
		//SetTickGroup(EngineTaskTick::AsyncTick);

        AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
	}

	ConnectionQuicClient::~ConnectionQuicClient()
	{
	}

    void ConnectionQuicClient::OnConnectionResult(Result hrConnect)
    {
        Connection::OnConnectionResult(hrConnect);


        if (!hrConnect.IsSuccess())
        {
            CloseConnection("Establishing a connection has been failed");
            return;
        }
    }

    Result ConnectionQuicClient::OnQuicConnected()
    {
        Result hr;

        SFCheck(Quic, super::OnQuicConnected());

        // Debugging SSL key log file
        std::string SslKeyLogFile = std::format("sslkey_{}.txt", GetCID());
        WriteSslKeyLogFile(SslKeyLogFile.c_str(), &m_ClientSecrets);


        SetQuicState(EQuicState::Handshaking);

        SFCheck(Quic, OpenStream());

        // Send NetCtrl Connect message
        SFCheck(Quic, SendNetCtrl(PACKET_NETCTRL_CONNECT, 0, {}, 0));

        return hr;
    }

    Result ConnectionQuicClient::OnQuicConnectionShutdownComplete(bool AppCloseInProgress)
    {
        Result hr;

        SFCheck(Quic, super::OnQuicConnectionShutdownComplete(AppCloseInProgress));

        if (!AppCloseInProgress)
        {
            CloseConnection("Shutdown has been requested by either peer or system.");
        }

        return hr;
    }

    void ConnectionQuicClient::OnQuicDatagramChanged(bool bEnabled, uint maxPacketSize)
    {
        SFLog(Quic, Info, "CID:{} Datagram changed: Enabled={}, MaxPacketSize={}", GetCID(), bEnabled, maxPacketSize);
    }

    Result ConnectionQuicClient::OnStreamPeerShutdownCompleted(HQUIC Stream, bool AppCloseInProgress, bool ConnectionClosedRemotely)
    {
        Result hr;

        SFCheck(Quic, super::OnStreamPeerShutdownCompleted(Stream, AppCloseInProgress, ConnectionClosedRemotely));

        if (!AppCloseInProgress)
        {
            CloseStream(Stream);
        }

        return hr;
    }

	// Initialize connection
	Result ConnectionQuicClient::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		if (local.PeerClass != NetClass::Client)
			return ResultCode::INVALID_ARG;

		Result hr = ConnectionQuic::InitConnection(local, remote );

        auto msQuic = Service::Quic->GetQuic();
        SFCheckPtr(Quic, msQuic);

        auto configuration = Service::Quic->GetConfiguration("client");
        SFCheckPtr(Quic, configuration);

        HQUIC connection{};
        QUIC_STATUS Status{};

        Status = msQuic->ConnectionOpen(Service::Quic->GetRegistration(), QuicConnectionCallback, this, &connection);
        SFCheck(Quic, Service::Quic->QuicStatusToResult(Status));


        Status = msQuic->SetParam(connection, QUIC_PARAM_CONN_TLS_SECRETS, sizeof(m_ClientSecrets), &m_ClientSecrets);
        if (QUIC_FAILED(Status))
        {
            SFLog(Quic, Error, "SetParam(QUIC_PARAM_CONN_TLS_SECRETS) failed, {:#08X}", Status);
            SFCheck(Quic, Service::Quic->QuicStatusToResult(Status));
        }

        // Start the connection
        QUIC_ADDRESS_FAMILY Family = remote.PeerAddress.SocketFamily == SockFamily::IPV4 ? QUIC_ADDRESS_FAMILY_INET : QUIC_ADDRESS_FAMILY_INET6;
        uint16_t ServerPort = 443;
            Status = msQuic->ConnectionStart(connection, configuration, Family, remote.PeerAddress.Address, ServerPort);
        if (QUIC_FAILED(Status))
        {
            msQuic->ConnectionClose(connection);
            SFCheck(Quic, Service::Quic->QuicStatusToResult(Status));
        }

        m_Configuration = configuration;

        SetQuicConnection(connection);

        SetQuicState(EQuicState::Connecting);

		return hr;
	}

} // namespace Net
} // namespace SF

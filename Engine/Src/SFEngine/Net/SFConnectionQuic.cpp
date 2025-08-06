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
	//	Client Mobile UDP Network connection class
	//



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network connection class
	//

	// Constructor
	ConnectionQuic::ConnectionQuic()
		: Connection(nullptr)
	{
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

        if (m_Connection)
        {
            auto msQuic = Service::Quic->GetQuic();
            if (msQuic)
                msQuic->ConnectionClose(m_Connection);
            m_Connection = nullptr;
        }

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
			SFLog(Net, Error, "Failed to Open a Socket {0}", GetLastNetSystemResult());
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
	//	TCP Network client connection class
	//

    _IRQL_requires_max_(DISPATCH_LEVEL)
        _Function_class_(QUIC_CONNECTION_CALLBACK)
        QUIC_STATUS
        QUIC_API
        QuicClientConnectionCallback(
            _In_ HQUIC QuicConnection,
            _In_opt_ void* Context,
            _Inout_ QUIC_CONNECTION_EVENT* Event
        )
    {
        auto* Connection = reinterpret_cast<ConnectionQuicClient*>(Context);

        //if (Event->Type == QUIC_CONNECTION_EVENT_CONNECTED) {
            //const char* SslKeyLogFile = getenv(SslKeyLogEnvVar);
            //if (SslKeyLogFile != NULL) {
            //    WriteSslKeyLogFile(SslKeyLogFile, &ClientSecrets);
            //}
        //}

        switch (Event->Type) {
        case QUIC_CONNECTION_EVENT_CONNECTED:
            Connection->OnConnectionResult(ResultCode::SUCCESS);
            break;
        case QUIC_CONNECTION_EVENT_SHUTDOWN_INITIATED_BY_TRANSPORT:
            //
            // The connection has been shut down by the transport. Generally, this
            // is the expected way for the connection to shut down with this
            // protocol, since we let idle timeout kill the connection.
            //
            if (Event->SHUTDOWN_INITIATED_BY_TRANSPORT.Status == QUIC_STATUS_CONNECTION_IDLE) {
                printf("[conn][%p] Successfully shut down on idle.\n", Connection);
            }
            else {
                printf("[conn][%p] Shut down by transport, 0x%x\n", Connection, Event->SHUTDOWN_INITIATED_BY_TRANSPORT.Status);
            }
            break;
        case QUIC_CONNECTION_EVENT_SHUTDOWN_INITIATED_BY_PEER:
            //
            // The connection was explicitly shut down by the peer.
            //
            printf("[conn][%p] Shut down by peer, 0x%llu\n", Connection, (unsigned long long)Event->SHUTDOWN_INITIATED_BY_PEER.ErrorCode);
            break;
        case QUIC_CONNECTION_EVENT_SHUTDOWN_COMPLETE:
            //
            // The connection has completed the shutdown process and is ready to be
            // safely cleaned up.
            //
            printf("[conn][%p] All done\n", Connection);
            if (!Event->SHUTDOWN_COMPLETE.AppCloseInProgress) {
                Connection->CloseConnection("Shutdown has been requested by either peer or system.");
            }
            break;
        case QUIC_CONNECTION_EVENT_RESUMPTION_TICKET_RECEIVED:
            //
            // A resumption ticket (also called New Session Ticket or NST) was
            // received from the server.
            //
            printf("[conn][%p] Resumption ticket received (%u bytes):\n", Connection, Event->RESUMPTION_TICKET_RECEIVED.ResumptionTicketLength);
            for (uint32_t i = 0; i < Event->RESUMPTION_TICKET_RECEIVED.ResumptionTicketLength; i++) {
                printf("%.2X", (uint8_t)Event->RESUMPTION_TICKET_RECEIVED.ResumptionTicket[i]);
            }
            printf("\n");
            break;
        case QUIC_CONNECTION_EVENT_IDEAL_PROCESSOR_CHANGED:
            printf(
                "[conn][%p] Ideal Processor is: %u, Partition Index %u\n",
                Connection,
                Event->IDEAL_PROCESSOR_CHANGED.IdealProcessor,
                Event->IDEAL_PROCESSOR_CHANGED.PartitionIndex);
            break;
        default:
            break;
        }
        return QUIC_STATUS_SUCCESS;
    }


	// Constructor
	ConnectionQuicClient::ConnectionQuicClient()
		: ConnectionQuic()
	{
		// We can't set tick here. There is a small chance that tick update finished before this object's reference count got increased
		//SetTickGroup(EngineTaskTick::AsyncTick);
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

        auto msQuic = Service::Quic->GetQuic();
        SFCheckPtr(Quic, msQuic);

        auto configuration = Service::Quic->GetConfiguration("client");
        SFCheckPtr(Quic, configuration);

        HQUIC connection{};
        m_Status = msQuic->ConnectionOpen(Service::Quic->GetRegistration(), QuicClientConnectionCallback, this, &connection);
        if (QUIC_FAILED(m_Status))
        {
            SFCheck(Quic, Service::Quic->QuicStatusToResult(m_Status));
        }

        // Start the connection
        QUIC_ADDRESS_FAMILY Family = remote.PeerAddress.SocketFamily == SockFamily::IPV4 ? QUIC_ADDRESS_FAMILY_INET : QUIC_ADDRESS_FAMILY_INET6;
        uint16_t ServerPort = 443;
        m_Status = msQuic->ConnectionStart(connection, configuration, Family, remote.PeerAddress.Address, ServerPort);
        if (QUIC_FAILED(m_Status))
        {
            msQuic->ConnectionClose(connection);
            SFCheck(Quic, Service::Quic->QuicStatusToResult(m_Status));
        }

        m_Configuration = configuration;

        SetQuicConnection(connection);

		return hr;
	}



} // namespace Net
} // namespace SF

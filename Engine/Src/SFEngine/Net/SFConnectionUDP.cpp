////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "Util/SFTimeUtil.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Net/SFConnectionUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Net/SFConnectionActions.h"
#include "Protocol/SFProtocol.h"


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
	//	Server UDP Network connection class
	//


	// Constructor
	ConnectionUDPServerPeer::ConnectionUDPServerPeer(IHeap& heap, SocketIOUDP* ioHandler)
		: ConnectionUDP(heap, ioHandler)
	{
		// limit server net retry maximum
		SetMaxGuarantedRetry( Const::UDP_CLI_RETRY_ONETIME_MAX );
	}

	ConnectionUDPServerPeer::~ConnectionUDPServerPeer()
	{
		m_RecvReliableWindow.Reset();
		m_SendReliableWindow.ClearWindow();
	}


	// Initialize packet synchronization
	Result ConnectionUDPServerPeer::InitSynchronization()
	{
		Result hr;

		netCheck(ConnectionUDP::InitSynchronization() );

		m_RecvReliableWindow.Reset();
		m_SendReliableWindow.ClearWindow();

		return hr;
	}
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server UDP Network connection class
	//

	// Constructor
	ConnectionUDPServer::ConnectionUDPServer(IHeap& heap, SocketIO* ioHandler)
		: ConnectionUDP(heap, ioHandler)
	{
		// limit server net retry maximum
		SetMaxGuarantedRetry( Const::UDP_CLI_RETRY_ONETIME_MAX );
	}

	ConnectionUDPServer::~ConnectionUDPServer()
	{
		ClearQueues();
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	client UDP Network connection class
	//


	ConnectionUDPClient::MyNetSocketIOAdapter::MyNetSocketIOAdapter(ConnectionUDPClient &owner)
		: SocketIOUDP(owner.GetHeap())
		, m_Owner(owner)
	{
		SetUserSocketID(m_Owner.GetCID());

	}


	Result ConnectionUDPClient::MyNetSocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
		Result hr = ResultCode::SUCCESS;

		if (pIOBuffer != nullptr && pIOBuffer->Operation != IOBUFFER_OPERATION::OP_UDPREAD)
		{
			netErr(ResultCode::UNEXPECTED);
		}


		// Pending recv count and registered status should be checked together so that we can prevent infinit pending recv
		// And PendingRecv should be decreased after new pending is happened
		if (GetIsIORegistered())
		{

			if (hrRes)
			{
				netChkPtr(pIOBuffer);

				if (!(hr = m_Owner.OnRecv(pIOBuffer->TransferredSize, pIOBuffer->GetPayloadPtr())))
					SFLog(Net, Debug3, "Read IO failed with CID {0}, hr={1:X8}", m_Owner.GetCID(), hr);

				m_Owner.PendingRecv();
			}
			else
			{
				// TODO: need to mark close connection
				m_Owner.Disconnect("Recv failed");
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

		return hr;
	}

	Result ConnectionUDPClient::MyNetSocketIOAdapter::OnWriteReady()
	{
        m_Owner.SendFlush();
        return ResultCode::SUCCESS;
	}


	// Send message to connection with network device
	Result ConnectionUDPClient::MyNetSocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
	{
		auto result = SocketIOUDP::WriteBuffer(pSendBuffer);
		switch ((uint32_t)result)
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
			// Need to disconnect
			result = ResultCode::IO_CONNECTION_CLOSED;
			m_Owner.Disconnect("SendBufferUDP is failed");
			break;
		}

		return result;

		//return m_Owner.SendBufferUDP(pSendBuffer);
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//	client UDP Network connection class
	//

	// Constructor
	ConnectionUDPClient::ConnectionUDPClient(IHeap& heap)
		: ConnectionUDP(heap, &m_NetIOAdapter)
		, m_NetIOAdapter(*this)
	{
		// limit client net retry maximum
		SetMaxGuarantedRetry( Const::UDP_CLI_RETRY_ONETIME_MAX );

		SetLocalClass( NetClass::Client );

		// We will share the write queue for UDP
		//SetWriteQueue(new WriteBufferQueue);

		//SetNetCtrlAction(NetCtrlCode_SyncReliable, &m_HandleSyncReliableClient);
		SetNetCtrlAction(NetCtrlCode_TimeSyncRtn, &m_HandleTimeSyncRtn);

		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::CONNECTING, &m_SendConnect);

		AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);
		//AddStateAction(ConnectionState::CONNECTED, &m_ActSendSync);

	}

	ConnectionUDPClient::~ConnectionUDPClient()
	{
		ClearQueues();
	}

	void ConnectionUDPClient::Dispose()
	{
		ConnectionUDP::Dispose();
		ClearQueues();
		m_NetIOAdapter.CloseSocket();
	}


	// Pending recv New one
	Result ConnectionUDPClient::PendingRecv()
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;
		UniquePtr<IOBUFFER_READ> pOver;

		if (!NetSystem::IsProactorSystem())
			return ResultCode::SUCCESS;

		m_NetIOAdapter.IncPendingRecvCount();


		while(1)
		{
			pOver.reset(new(GetSystemHeap()) IOBUFFER_READ);
			hrErr = m_NetIOAdapter.PendingRecv(pOver.get());
			switch ((uint32_t)hrErr)
			{
			case (uint32_t)ResultCode::SUCCESS:
			case (uint32_t)ResultCode::IO_IO_PENDING:
			case (uint32_t)ResultCode::IO_WOULDBLOCK:
				pOver.release();
				return hr;
			case (uint32_t)ResultCode::IO_TRY_AGAIN:
			default:
				m_NetIOAdapter.DecPendingRecvCount();
				Disconnect("Pending recv is failed");
				return hr;
			}
		}

		return hr;
	}


	// Initialize connection
	Result ConnectionUDPClient::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		m_NetIOAdapter.ResetPendingRecvCount();
		m_NetIOAdapter.ResetPendingSendCount();

		return Connection::InitConnection(local, remote);
	}


	// Connect to remote. InitConnection + Connect 
	// Local address will be auto detected
	Result ConnectionUDPClient::Connect(PeerInfo local, const PeerInfo& remote)
	{
		SF_SOCKET socket = INVALID_SOCKET;
		sockaddr_storage bindAddr;
		ScopeContext hr([this, &socket](Result hr) 
			{
				if (socket != INVALID_SOCKET)
					Service::NetSystem->CloseSocket(socket);
			});

		if (remote.PeerAddress.SocketFamily == SockFamily::IPV4)
			Net::GetLocalAddressIPv4(local.PeerAddress);
		else
			Net::GetLocalAddressIPv6(local.PeerAddress);

		socket = Service::NetSystem->Socket(local.PeerAddress.SocketFamily, SocketType::DataGram);
		if (socket == INVALID_SOCKET)
		{
			SFLog(Net, Error, "Failed to Open Client Socket {0:X8}", GetLastNetSystemResult());
			netCheck(ResultCode::UNEXPECTED);
		}

		netCheck(Service::NetSystem->SetupCommonSocketOptions(SocketType::DataGram, local.PeerAddress.SocketFamily, socket));

		bindAddr = (sockaddr_storage)local.PeerAddress;
		if (bind(socket, (sockaddr*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "Socket bind failed, UDP err={0:X8}", GetLastNetSystemResult());
			netCheck(ResultCode::UNEXPECTED);
		}
		local.PeerAddress = bindAddr;


		netCheck(InitConnection(local, remote));
		SFLog(Net, Info, "Initialize connection CID:{0}, Addr:{1}", GetCID(), remote.PeerAddress);

		m_NetIOAdapter.SetSocket(local.PeerAddress.SocketFamily, SocketType::DataGram, socket);

		socket = INVALID_SOCKET;

		netCheck(Service::NetSystem->RegisterSocket(&m_NetIOAdapter));

		netCheck(PendingRecv());

		//netCheck(Service::ConnectionManager->PendingWaitConnection(pConn));

		//netCheck( CliSystem::AddConnectionTask( &GetConnectionManager(), pConn ) );

		return hr;
	}


	// Reinitialize and set remote address
	Result ConnectionUDPClient::ReInitialize( const sockaddr_storage& socAddr )
	{
		SetConnectionState(ConnectionState::CONNECTING);

		UpdateConnectionTime();

		SetRemoteAddress( socAddr );

		m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
		m_ulNetCtrlTime = Util::Time.GetTimeMs();

		SetLocalClass( NetClass::Client );

		return ResultCode::SUCCESS;
	}

    Result ConnectionUDPClient::TickUpdate()
    {
        Result hr;

        netCheck(super::TickUpdate());

        // tick update send queue
        bool bWriteIsReady = m_bWriteIsReady.exchange(false, std::memory_order_consume);
        if (bWriteIsReady) // if write ready is triggered this tick
        {
            SendFlush();
        }

        return hr;
    }

} // namespace Net
} // namespace SF

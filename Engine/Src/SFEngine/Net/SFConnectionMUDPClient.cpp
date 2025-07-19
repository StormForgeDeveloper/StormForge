////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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
#include "Util/SFToString.h"
#include "Util/SFHasher32.h"
#include "SFProtocol.h"

#include "Net/SFConnectionMUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetToString.h"


namespace SF {
namespace Net {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Client Mobile UDP Network connection class
	//

	std::atomic<uint64_t> ConnectionMUDPClient::stm_CIDGen(0);

	ConnectionMUDPClient::MyNetSocketIOAdapter::MyNetSocketIOAdapter(ConnectionMUDPClient &owner)
		: SocketIOUDP(owner.GetHeap())
		, m_Owner(owner)
	{
		SetUserSocketID(m_Owner.GetCID());
	}

	Result ConnectionMUDPClient::MyNetSocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
		Result hr = ResultCode::SUCCESS;

		if (pIOBuffer != nullptr && pIOBuffer->Operation != IOBUFFER_OPERATION::OP_UDPREAD)
		{
			netErr(ResultCode::UNEXPECTED);
		}


		// Pending recv count and registered status should be checked together so that we can prevent infinite pending recv
		// And PendingRecv should be decreased after new pending is happened
		if (GetIsIORegistered())
		{

			if (hrRes)
			{
				netChkPtr(pIOBuffer);

                PacketHeader* pPacketHeader = reinterpret_cast<PacketHeader*>(pIOBuffer->GetPayloadPtr());
                MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(pPacketHeader + 1);

				if (!(hr = m_Owner.OnRecv(pIOBuffer->TransferredSize - sizeof(PacketHeader), reinterpret_cast<uint8_t*>(pHeader))))
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

    Result ConnectionMUDPClient::MyNetSocketIOAdapter::OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE* pIOBuffer)
    {
        return super::OnIOSendCompleted(hrRes, pIOBuffer);
    }

	Result ConnectionMUDPClient::MyNetSocketIOAdapter::OnWriteReady()
	{
        m_Owner.SendFlush();
        return ResultCode::SUCCESS;
	}

	// Send message to connection with network device
	Result ConnectionMUDPClient::MyNetSocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
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
			// Need to close connection
			result = ResultCode::IO_CONNECTION_CLOSED;
			m_Owner.Disconnect("SendBufferUDP is failed");
			break;
		}

		return result;
	}


	///////////////////////////////////////////////////////////////////////////////////////////
	//
	//	MyNetSocketIOManager
	//

	ConnectionMUDPClient::MyNetSocketIOManager::MyNetSocketIOManager(ConnectionMUDPClient& owner)
		: m_Owner(owner)
	{
	}

	void ConnectionMUDPClient::MyNetSocketIOManager::Init()
	{
		FreeCurrentHandler();
		FlushFreedHandlers();
	}

	Result ConnectionMUDPClient::MyNetSocketIOManager::NewIOHandler()
	{
		Result hr;
		SocketType socketType = SocketType::DataGram;
		SockFamily socketFamily = m_Owner.GetLocalInfo().PeerAddress.SocketFamily;
		sockaddr_storage bindAddr;

		auto socket = Service::NetSystem->Socket(socketFamily, socketType);
		if (socket == INVALID_SOCKET)
		{
			SFLog(Net, Error, "Failed to Open Client Socket {0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		netChk(Service::NetSystem->SetupCommonSocketOptions(socketType, socketFamily, socket));

		bindAddr = (sockaddr_storage)m_Owner.GetLocalInfo().PeerAddress;
		if (bind(socket, (sockaddr*)&bindAddr, (unsigned)Net::GetSockAddrSize(bindAddr)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "Socket bind failed, UDP err={0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		FreeCurrentHandler();


		if (m_ActiveAdapter == nullptr)
		{
			netMem(m_ActiveAdapter = new(m_Owner.GetHeap()) MyNetSocketIOAdapter(m_Owner));
			m_ActiveAdapter->SetSocket(socketFamily, socketType, socket);
			socket = INVALID_SOCKET;
			netChk(Service::NetSystem->RegisterSocket(m_ActiveAdapter));

			m_Owner.SetNetIOHandler(m_ActiveAdapter);
		}

		netChk(m_Owner.PendingRecv());


	Proc_End:

		if (socket != INVALID_SOCKET)
			Service::NetSystem->CloseSocket(socket);

		return hr;
	}


	void ConnectionMUDPClient::MyNetSocketIOManager::FreeCurrentHandler()
	{
		MutexScopeLock lock(m_ManagerLock);
		if (m_ActiveAdapter != nullptr)
		{
			m_ActiveAdapter->CloseSocket();

			if (!m_PendingFree.Enqueue(m_ActiveAdapter))
			{
				assert(false);
				// ?
			}

			m_ActiveAdapter = nullptr;
			m_Owner.SetNetIOHandler(nullptr);
		}
	}

	void ConnectionMUDPClient::MyNetSocketIOManager::FlushFreedHandlers()
	{
		MutexScopeLock lock(m_ManagerLock);

		if (m_PendingFreeCache != nullptr)
		{
			if (m_PendingFreeCache->CanDelete())
			{
				IHeap::Delete(m_PendingFreeCache);
				m_PendingFreeCache = nullptr;
			}
			else
			{
				return;
			}
		}

		auto itemCount = m_PendingFree.size();
		MyNetSocketIOAdapter* pPendingItem = nullptr;
		for (size_t iItem = 0; iItem < itemCount; iItem++)
		{
			if (!m_PendingFree.Dequeue(pPendingItem))
				break;

			if (pPendingItem != nullptr)
			{
				if (pPendingItem->CanDelete())
				{
					IHeap::Delete(pPendingItem);
					pPendingItem = nullptr;
				}
				else
				{
					break;
				}
			}
		}
	}

	bool ConnectionMUDPClient::MyNetSocketIOManager::ValidateNetIOAdapter()
	{
		Result hr;

		MutexScopeLock lock(m_ManagerLock);

		if (m_ActiveAdapter != nullptr)
		{
			if (!m_ActiveAdapter->GetLastResult())
				FreeCurrentHandler();
		}

		FlushFreedHandlers();

		// Create new one if not exists
		if(m_ActiveAdapter == nullptr)
			NewIOHandler();

	//Proc_End:

		return m_ActiveAdapter != nullptr;
	}

	bool ConnectionMUDPClient::MyNetSocketIOManager::CanDelete()
	{
		FlushFreedHandlers();

		// If there is something pending we need to wait
		if (m_PendingFreeCache != nullptr)
			return false;

		if (m_PendingFree.size() > 0)
			return false;

		// check 
		if (m_ActiveAdapter != nullptr)
			return m_ActiveAdapter->CanDelete();

		return true;
	}

	void ConnectionMUDPClient::MyNetSocketIOManager::Dispose()
	{
		FreeCurrentHandler();
		FlushFreedHandlers();
	}

	// Constructor
	ConnectionMUDPClient::ConnectionMUDPClient()
		: ConnectionMUDP(nullptr)
		, m_NetIOAdapterManager(*this)
		, m_ReliableSyncTime()
	{
		// We can't set tick here. There is a small chance that tick update finished before this object's reference count got increased
		//SetTickGroup(EngineTaskTick::AsyncTick);

		SetNetCtrlAction(NetCtrlCode_SyncReliable, &m_HandleSyncReliableClient);
		SetNetCtrlAction(NetCtrlCode_TimeSyncRtn, &m_HandleTimeSyncRtn);

		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::CONNECTING, &m_SendConnect);
		
		AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);

		AddStateAction(ConnectionState::CONNECTED, &m_ActSendSync);

        AddStateAction(ConnectionState::CONNECTING, &m_ValidateNetIO);
        AddStateAction(ConnectionState::CONNECTED, &m_ValidateNetIO);

		auto newCID = stm_CIDGen.fetch_add(1, std::memory_order_relaxed) + 1;
		if(newCID == 0)
			newCID = stm_CIDGen.fetch_add(1, std::memory_order_relaxed) + 1;
		SetCID(newCID);
	}

	ConnectionMUDPClient::~ConnectionMUDPClient()
	{
	}

	bool ConnectionMUDPClient::CanDelete()
	{
		return m_NetIOAdapterManager.CanDelete();
	}

	void ConnectionMUDPClient::Dispose()
	{
		ClearQueues();

		super::Dispose();

		m_NetIOAdapterManager.Dispose();
	}

	// Initialize connection
	Result ConnectionMUDPClient::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		m_NetIOAdapterManager.Init();

		return Connection::InitConnection(local, remote);
	}

	// Connect to remote. InitConnection + Connect 
	// Local address will be auto detected
	Result ConnectionMUDPClient::Connect(PeerInfo local, const PeerInfo& remote)
	{
		Result hr = ResultCode::SUCCESS;

		// detect local address
		if (StrUtil::IsNullOrEmpty(local.PeerAddress.Address))
		{
            local.PeerAddress.SocketFamily = remote.PeerAddress.SocketFamily;
			// Use Any address, so that it can support multiple nat devices
//			if (remote.PeerAddress.SocketFamily == SockFamily::IPV4)
//				Net::GetLocalAddressIPv4(local.PeerAddress);
//			else
//				Net::GetLocalAddressIPv6(local.PeerAddress);
		}

		m_ReliableSyncTime = Util::Time.GetTimeMs();

		netChk(InitConnection(local, remote));
		SFLog(Net, Custom3, "Initialize connection CID:{0}, Addr:{1}", GetCID(), remote.PeerAddress);


		m_NetIOAdapterManager.FreeCurrentHandler();
		netChk(m_NetIOAdapterManager.NewIOHandler());

		netChk(PendingRecv());


	Proc_End:

		//if (socket != INVALID_SOCKET)
		//	Service::NetSystem->CloseSocket(socket);

		return hr;
	}

	// Close connection
	Result ConnectionMUDPClient::CloseConnection(const char* reason)
	{
		m_NetIOAdapterManager.FreeCurrentHandler();
		m_NetIOAdapterManager.FlushFreedHandlers();

		return ConnectionMUDP::CloseConnection(reason);
	}


	//Result ConnectionMUDPClient::EnqueueBufferUDP(IOBUFFER_WRITE *pSendBuffer)
	//{
	//	auto pActiveIO = m_NetIOAdapterManager.GetActiveNetIOAdapter();
	//	if (pActiveIO != nullptr)
	//		return pActiveIO->EnqueueBuffer(pSendBuffer);
	//	else
	//		return ResultCode::UNEXPECTED;
	//}


	// Pending recv New one
	Result ConnectionMUDPClient::PendingRecv()
	{
		auto pActiveIO = m_NetIOAdapterManager.GetActiveNetIOAdapter();
		if (pActiveIO != nullptr)
			return pActiveIO->PendingRecv();
		else
			return ResultCode::UNEXPECTED;
	}


} // namespace Net
} // namespace SF

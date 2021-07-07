////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net Server 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Multithread/SFThread.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFConnectionUDP.h"
#include "Net/SFConnectionMUDP.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFConnectionManager.h"
#include "Container/SFSpinSharedBuffer.h"
#include "Container/SFCircularPageQueue.h"




namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP Server class
	//

	class ServerUDPBase : public ServerNet
	{
	public:

		// Socket IO handler
		class MySocketIOAdapter : public SocketIOUDP
		{
		private:
			ServerUDPBase& m_Owner;

		public:
			MySocketIOAdapter(ServerUDPBase* owner)
				: SocketIOUDP(owner->GetHeap())
				, m_Owner(*owner)
			{
			}

			virtual Result OnWriteReady() override;
			// called when send completed
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

			virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) override;
		};


	private:

		MySocketIOAdapter m_MySocketIOAdapter;

	public:
		ServerUDPBase(IHeap& heap, ServerID InServerID, NetClass localClass);
		virtual ~ServerUDPBase();

		// Open host and start listen
		virtual Result HostOpen( NetClass netCls, const char *strLocalIP, uint16_t usLocalPort ) override;

		// Close host and close all connections
		virtual Result HostClose() override;

		virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) = 0;
	};
	
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP Server class
	//

	class ServerUDP : public ServerUDPBase
	{
	public:
		ServerUDP(IHeap& heap, ServerID InServerID, NetClass localClass);
		virtual ~ServerUDP();
		
		// called when network message is received
		virtual Result OnIORecvCompleted( Result hrRes, IOBUFFER_READ* &pIOBuffer ) override;
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Mobile UDP Server class
	//

	class ServerMUDP : public ServerUDPBase
	{
	public:
		ServerMUDP(IHeap& heap, ServerID InServerID, NetClass localClass);
		virtual ~ServerMUDP();

		Result SendRaw(const sockaddr_storage& dstAddress, SharedPointerT<Message::MessageData> &pMsg);
		Result SendNetCtrl( const sockaddr_storage& dstAddress, uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID );
		
		// Register PeerID to map
		Result OnPacketWithoutConnection(const struct sockaddr_storage& from, const uint8_t* pData);

		// called when network message is received
		virtual Result OnIORecvCompleted( Result hrRes, IOBUFFER_READ* &pIOBuffer ) override;
	};




} // namespace Net
} // namespace SF




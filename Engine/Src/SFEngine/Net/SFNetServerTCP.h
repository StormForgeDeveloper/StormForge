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
#include "Thread/SFThread.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFConnection.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"
#include "Container/SFSpinSharedBuffer.h"
#include "Container/SFCircularPageQueue.h"
#include "Net/SFConnectionTCP.h"




namespace SF {
namespace Net {





	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Server class
	//

	class ServerTCP : public ServerNet
	{
	public:

		// Socket IO handler
		class MySocketIOAdapter : public SocketIOTCP
		{
		private:

			ServerTCP& m_Owner;

			SyncCounter m_PendingAccept;

		public:
			MySocketIOAdapter(ServerTCP* owner)
				: SocketIOTCP(owner->GetHeap())
				, m_Owner(*owner)
				, m_PendingAccept(0)
			{
			}

			// Pending Accept New one
			Result PendingAccept();

			// Get pending accept count
			CounterType GetPendingAccept() { return m_PendingAccept.load(std::memory_order_relaxed); }

			virtual Result Accept(IOBUFFER_ACCEPT* &pAcceptInfo) override;
			// called when New connection TCP accepted
			virtual Result OnIOAccept(Result hrRes, IOBUFFER_ACCEPT *pAcceptInfo) override;

			// called when network message is received
			virtual Result Recv(IOBUFFER_READ* pIOBuffer) override;
			virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) override;

			virtual Result OnWriteReady() override;
			// called when send completed
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

		};


	private:

		MySocketIOAdapter m_MySocketIOAdapter;


	protected:


	public:
		ServerTCP(IHeap& heap, ServerID InServerID, NetClass localClass);
		virtual ~ServerTCP();

		/////////////////////////////////////////////////////////////////////////////////////////////
		// callback


			// handle Socket accept
		virtual Result OnAcceptedSocket(SF_SOCKET acceptedSocket, const sockaddr_storage& remoteSockAddr, const PeerInfo& remoteInfo, ConnectionPtr &pConnOut);


		// Enable/Disable new connection acception
		virtual void SetIsEnableAccept( bool bIsEnable ) override;


		// Open host and start listen
		virtual Result HostOpen( NetClass netCls, const char *strLocalIP, uint16_t usLocalPort ) override;

		// Close host and close all connections
		virtual Result HostClose() override;

	};






} // namespace Net
} // namespace SF




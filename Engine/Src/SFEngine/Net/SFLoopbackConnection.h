////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Loopback fake connection 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Container/SFCircularPageQueue.h"
#include "Net/SFConnection.h"



namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network LoopbackConnection base class
	//

	class LoopbackConnection : public Connection
	{
	public:


		class MyNetSocketIOAdapter : public SocketIO
		{
		private:

		public:

			MyNetSocketIOAdapter(IHeap& heap)
				: SocketIO(heap) 
			{}

			// Send message to connection with network device
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override { return ResultCode::SUCCESS; }

			virtual Result PendingRecv(IOBUFFER_READ *pRecvBuffer = nullptr) override { unused(pRecvBuffer); return ResultCode::SUCCESS; }
			// called when receiving TCP message
			virtual Result Recv(IOBUFFER_READ* pIOBuffer) override { return ResultCode::SUCCESS; }
			virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) override { return ResultCode::SUCCESS; }

			virtual Result OnWriteReady() override { return ResultCode::SUCCESS; }

			// called when send completed
			virtual Result OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE *pIOBuffer) override { return ResultCode::SUCCESS; }
		};


	private:

		MyNetSocketIOAdapter m_NetIOAdapter;


	public:
		LoopbackConnection();
		virtual ~LoopbackConnection();

		// Initialize LoopbackConnection
		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote) override;


		//////////////////////////////////////////////////////////////////////////
		//
		//	virtual implementations
		//

		virtual Result Connect(PeerInfo local, const PeerInfo& remote) override { return ResultCode::SUCCESS; }

		// Disconnect connection
		virtual Result Disconnect(const char* reason) override;

		// Close connection immediately without notify
		virtual Result CloseConnection(const char* reason) override;

		virtual Result OnRecv(uint uiBuffSize, const uint8_t* pBuff) override { assert(false);  return ResultCode::SUCCESS; }
		// Send message to connected entity
		//virtual Result Send( Message::MessageData* &pMsg ) = 0;


		// Update net control, process connection heartbeat, ... etc
		virtual Result TickUpdate() override { return ResultCode::FAIL; }


		// Update send queue, Reliable UDP
		//virtual Result UpdateSendQueue() override { return ResultCode::FAIL; }
		// Update Send buffer Queue, TCP and UDP client connection
		virtual Result UpdateSendBufferQueue() override { return ResultCode::FAIL; }

	};


} // namespace Net
} // namespace SF




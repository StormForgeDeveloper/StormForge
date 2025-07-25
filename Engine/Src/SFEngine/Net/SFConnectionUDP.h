////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net connection classes. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Container/SFCircularPageQueue.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionUDPBase.h"
#include "Net/SFMessageWindow.h"
#include "Net/SFConnectionActions.h"


namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server UDP Network connection class
	//

    using ConnectionUDP = ConnectionUDPBase;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	client UDP Network connection class
	//

	class ConnectionUDPClient : public ConnectionUDP
	{
	public:

		class MyNetSocketIOAdapter : public SocketIOUDP
		{
		private:

			ConnectionUDPClient &m_Owner;

		public:

			MyNetSocketIOAdapter(ConnectionUDPClient &owner);


			// Send message to connection with network device
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

			virtual Result OnWriteReady() override;

            // called on packet recv
            virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ*& pIOBuffer) override;
            virtual Result OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE* pIOBuffer) override;
        };

	private:

		MyNetSocketIOAdapter m_NetIOAdapter;

		// Event actions
		//ConnectionMessageAction_MUDPHandleSyncReliableClient m_HandleSyncReliableClient;
		ConnectionMessageAction_HandleTimeSyncRtn m_HandleTimeSyncRtn;

		ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
		ConnectionStateAction_SendConnect m_SendConnect;
		ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
		ConnectionStateAction_SendDisconnect m_SendDisconnect;

		//ConnectionStateAction_SendSync m_ActSendSync;
        Atomic<bool> m_bWriteIsReady;

	public:
		// Constructor
		ConnectionUDPClient();
		~ConnectionUDPClient();

		virtual void Dispose() override;


		// Pending recv New one
		Result PendingRecv();


		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote) override;

		// Connect to remote. InitConnection + Connect 
		// Local address will be auto detected
		// @local: NetClass and ID should be assigned
		// @remote: remote information. Address should to be assigned
		Result Connect(PeerInfo local, const PeerInfo& remote) override;

		// Reinitialize and set remote address
		Result ReInitialize( const sockaddr_storage& socAddr );

        virtual Result TickUpdate() override;
	};


}  // namespace Net
} // namespace SF




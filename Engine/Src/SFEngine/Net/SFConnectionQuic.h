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

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFConnection.h"

#include <msquic.h>


namespace SF {
	namespace Net {



		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network connection class
		//

		class ConnectionQuic : public Connection
		{
		public:

			typedef Connection super;

        private:

            HQUIC m_Connection{};

        protected:
            // latest quic status
            QUIC_STATUS m_Status;

            void SetQuicConnection(HQUIC connection) { m_Connection = connection; }
            HQUIC GetQuicConnection() const { return m_Connection; }

		public:
			// Constructor
			ConnectionQuic();
			virtual ~ConnectionQuic();

            // Get quic configuration. client and server may act differently
            virtual HQUIC GetConfiguration() const = 0;

			virtual bool CanDelete() override;
			virtual void Dispose() override;

			SockFamily GetSocketFamily() const { return SockFamily::Quic; }

			// Clear Queue
			virtual Result ClearQueues() override;


			// Called on connection result
			virtual void OnConnectionResult(Result hrConnect) override;

			// Initialize connection
			virtual Result InitConnection(const PeerInfo& local, const PeerInfo& remote) override;

			// Connect to remote. InitConnection + Connect , doest InitConnection inside
			// Local address will be auto detected
			// @local: NetClass and ID should be assigned
			// @remote: remote information. Address should to be assigned
			virtual Result Connect(PeerInfo local, const PeerInfo& remote) override;

			// Close connection
			virtual Result CloseConnection(const char* reason) override;


			// Raw packet data recv
			virtual Result OnRecv(uint uiBuffSize, uint8_t* pBuff) override;

            // Parsed message data Recv
			virtual Result OnRecv(MessageHeader* pMsg) override;

			// Send message to connected entity
            virtual Result SendMsg(const MessageHeader* pMsg) override;

			// Update net control, process connection heartbeat, ... etc
			virtual Result TickUpdate() override;

		};


		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network client connection class
		//

		class ConnectionQuicClient : public ConnectionQuic
		{
		public:

			using super = ConnectionQuic;

		private:

            // quic configuration handle
            HQUIC m_Configuration{};


			//ConnectionMessageAction_HandleTimeSyncRtn m_HandleTimeSyncRtn;
   //         ConnectionStateAction_WaitRW m_WaitRW;
   //         ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
			//ConnectionStateAction_SendConnect m_SendConnect;
			//ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
			//ConnectionStateAction_SendDisconnect m_SendDisconnect;


		public:
			// Constructor
			ConnectionQuicClient();
			~ConnectionQuicClient();

            virtual HQUIC GetConfiguration() const override {
                return m_Configuration;
            }

			// Initialize connection
			virtual Result InitConnection(const PeerInfo& local, const PeerInfo& remote) override;
		};



	}  // namespace Net
} // namespace SF




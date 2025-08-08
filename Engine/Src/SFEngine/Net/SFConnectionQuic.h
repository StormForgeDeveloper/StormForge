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
#include "Online/Quic/SFQuicService.h"

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

            enum class EQuicState : uint8_t
            {
                None,           // None just created
                Connecting,     // Connecting sequence
                Handshaking,    // Quic Connected, handshaking
                Connected,      // fully Connected
                Disconnected,   // Disconnected
            };

            ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;

        private:

            // Quic connection handle
            HQUIC m_Connection{};

            // Default stream handle
            HQUIC m_Stream{};

            bool m_DatagramEnabled{ false }; // Datagram enabled
            uint m_MaxDatagramSize{ 0 }; // Maximum datagram size

            // Default datagram handle
            HQUIC m_Datagram{};

            // Quic state
            Atomic<EQuicState> m_QuicState{ EQuicState::None };

            // Received data buffer
            std::vector<uint8_t>	m_ReceivedData;

        protected:
            // latest quic status
            QUIC_STATUS m_Status;

            // Access Quic state
            void SetQuicState(EQuicState state) { m_QuicState.store(state, std::memory_order_release); }

            // Set Quic connection handle
            void SetQuicConnection(HQUIC connection) { m_Connection = connection; }

            // Set default stream handle
            void SetDefaultStream(HQUIC stream);

		public:
			// Constructor
			ConnectionQuic();
			virtual ~ConnectionQuic();

            // Get quic configuration. client and server may act differently
            virtual HQUIC GetConfiguration() const = 0;

            EQuicState GetQuicState() const { return m_QuicState.load(std::memory_order_relaxed); }
            HQUIC GetQuicConnection() const { return m_Connection; }
            HQUIC GetDefaultStream() const { return m_Stream; }

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
            virtual Result Disconnect(const char* reason) override;

			// Raw packet data recv
			virtual Result OnRecv(uint uiBuffSize, uint8_t* pBuff) override;

            // Parsed message data Recv
			virtual Result OnRecv(MessageHeader* pMsg) override;

			// Send message to connected entity
            virtual Result SendMsg(const MessageHeader* pMsg) override;

			// Update net control, process connection heartbeat, ... etc
			virtual Result TickUpdate() override;

        protected:
            // Open default stream
            Result OpenStream();

            // close stream
            Result CloseStream(HQUIC stream);

            // Send NetCtrl message
            virtual Result SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0) override;
            virtual Result SendPending(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0 = 0) override {
                // For Quic, we can send directly to default stream
                return SendNetCtrl(uiCtrlCode, uiSequence, returnMsgID, parameter0);
            }

            // Send packet through default stream
            Result SendToStream(HQUIC Stream, const MessageHeader* pMsgHeader);

            // Send packet through either default stream or datagram
            Result SendThroughAny(const MessageHeader* pMsgHeader);

            // quic connected
            virtual Result OnQuicConnected();
            virtual Result OnQuicConnectionShutdownComplete(bool AppCloseInProgress) { return ResultCode::SUCCESS; }

            // quic datagram changed
            virtual void OnQuicDatagramChanged(bool bEnabled, uint maxPacketSize);

            virtual Result OnStreamStarted(HQUIC Stream);
            virtual Result OnStreamPeerSendAborted(HQUIC Stream) { return ResultCode::SUCCESS; }
            virtual Result OnStreamPeerSendShutdown(HQUIC Stream) { return ResultCode::SUCCESS; }
            virtual Result OnStreamPeerShutdownCompleted(HQUIC Stream, bool AppCloseInProgress, bool ConnectionClosedRemotely) { return ResultCode::SUCCESS; }

            // On send completed
            void OnSendCompleted(HQUIC Stream, void* sendContext);

            // On recv  completed
            void OnRecvCompleted(HQUIC Stream, uint bufferCount, const QUIC_BUFFER* buffers, QUIC_RECEIVE_FLAGS flags);

            // connection callback
            static _IRQL_requires_max_(DISPATCH_LEVEL)
                _Function_class_(QUIC_CONNECTION_CALLBACK)
                QUIC_STATUS
                QUIC_API
                QuicConnectionCallback(
                    _In_ HQUIC QuicConnection,
                    _In_opt_ void* Context,
                    _Inout_ QUIC_CONNECTION_EVENT* Event
                );

            // Stream callback
            static _IRQL_requires_max_(DISPATCH_LEVEL)
                _Function_class_(QUIC_STREAM_CALLBACK)
                QUIC_STATUS
                QUIC_API
                StreamCallback(
                    _In_ HQUIC Stream,
                    _In_opt_ void* Context,
                    _Inout_ QUIC_STREAM_EVENT* Event
                );

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

            //
            // The struct to be filled with TLS secrets
            // for debugging packet captured with e.g. Wireshark.
            //
            static QUIC_TLS_SECRETS m_ClientSecrets;

		public:
			// Constructor
			ConnectionQuicClient();
			~ConnectionQuicClient();

            virtual HQUIC GetConfiguration() const override {
                return m_Configuration;
            }

			// Initialize connection
			virtual Result InitConnection(const PeerInfo& local, const PeerInfo& remote) override;

            virtual void OnConnectionResult(Result hrConnect) override;

        private:

            // Called when quic connected
            virtual Result OnQuicConnected() override;
            virtual Result OnQuicConnectionShutdownComplete(bool AppCloseInProgress) override;

            virtual void OnQuicDatagramChanged(bool bEnabled, uint maxPacketSize) override;
            virtual Result OnStreamPeerShutdownCompleted(HQUIC Stream, bool AppCloseInProgress, bool ConnectionClosedRemotely) override;

        };



	}  // namespace Net
} // namespace SF


template <>
struct std::formatter<SF::Net::ConnectionQuic::EQuicState>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::Net::ConnectionQuic::EQuicState value, FormatContext& ctx) const
    {
        static const char* Names[] = {
            "None",           // None just created
            "Connecting",     // Connecting sequence
            "Handshaking",    // Quic Connected, handshaking
            "Connected",      // fully Connected
            "Disconnected",    // Disconnected
            "Max"
        };
        int NumNames = sizeof(Names) / sizeof(Names[0]);

        return std::format_to(ctx.out(), "{}", Names[std::clamp(int(value), 0, NumNames)]);
    }
};






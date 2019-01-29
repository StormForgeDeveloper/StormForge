////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Net base type definitions. 
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFMessage.h"
#include "Net/SFNetCtrlIDs.h"
#if SF_PLATFORM != SF_PLATFORM_WINDOWS
#include <arpa/inet.h>
#include <netdb.h>
#endif


namespace SF {
namespace Net {
	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection Interface
	//
#if SF_PLATFORM != SF_PLATFORM_WINDOWS
	#define SOCKET_ERROR (-1)
#endif

	static constexpr int MAX_STRING_TEMP_BUFF_SIZE = 1024 + 512;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	connection state definitions
	//

	// Connection state
	enum class ConnectionState : uint8_t
	{
		NONE,				// None just created
		WAITING,			// Waiting accept
		UDP_WAITING,		// UDP incoming Waiting
		CONNECTING,		// Connecting sequence
		CHECKVERSION,		// Checking protocol version
		CONNECTED,		// Connected 
		DISCONNECTING,	// Disconnecting
		DISCONNECTED,		// Disconnected
		SLEEP,			// For Mobile connection
		Max
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection Interface
	//

	class INet;
	class Connection;
	class IConnectionEventHandler;



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Event definitions
	//

#pragma pack(push,2)

	union ConnectionEvent
	{
		// Type of connection event
		enum EventTypes : uint8_t
		{
			EVT_NONE,
			EVT_CONNECTION_RESULT,
			EVT_DISCONNECTED,
			EVT_STATE_CHANGE,
			EVT_ADDRESS_REMAPPED,
		};

		struct {
			EventTypes		EventType;

			// State changed
			ConnectionState State;

			// connection result
			Result hr;
		} Components;

		uint64_t Composited = 0;

		ConnectionEvent(void* ptr = nullptr) { Components.EventType = EventTypes::EVT_NONE;  assert(ptr == nullptr); }
		ConnectionEvent(EventTypes eventType, Result hrRes) { Components.EventType = eventType;  Components.hr = hrRes; }
		ConnectionEvent(EventTypes eventType, ConnectionState InState) { Components.EventType = eventType; Components.State = InState; }
		ConnectionEvent& operator =(const ConnectionEvent& src);
		bool operator == (const ConnectionEvent& src) const;
		bool operator != (const ConnectionEvent& src) const;
	};

	static_assert(sizeof(ConnectionEvent) <= sizeof(uint64_t), "Connection event should be remained under 8bytes");
#pragma pack(pop)

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection information
	//

	struct PeerInfo
	{
		// Local address
		NetAddress		PeerAddress;
		NetClass		PeerClass;

		// Local identification ID
		uint64_t		PeerID;

		PeerInfo();
		PeerInfo(const NetAddress& Addr);
		PeerInfo(NetClass Class, const NetAddress& Addr, uint64_t UID);
		PeerInfo(NetClass Class, uint64_t UID);

		void SetInfo(NetClass Class, const NetAddress& Addr, uint64_t UID);
		void SetInfo(NetClass Class, uint64_t UID);
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	IConnectionEventHandler Interface
	//

	class IConnectionEventHandler
	{
	public:
		virtual ~IConnectionEventHandler();

		virtual void OnConnectionEvent(Connection* pConn, const ConnectionEvent& evt) = 0;
		virtual Result OnRecvMessage(Connection* pConn, SharedPointerT<Message::MessageData>& pMsg) = 0;
		virtual Result OnNetSyncMessage(Connection* pConn);
		// Net send message
		virtual Result OnNetSendReadyMessage(Connection* pConn);
	};






#include "SFNetDef.inl"

} // namespace Net


template<> inline Net::ConnectionState DefaultValue<Net::ConnectionState>() { return Net::ConnectionState::NONE; }
template<> inline Net::PeerInfo DefaultValue<Net::PeerInfo>() { static Net::PeerInfo defaultValue; return defaultValue; }

} // namespace SF

#define netChkPtr(e)		do{ if( (e) == nullptr ) SFErrJmp(Net,ResultCode::INVALID_POINTER); } while(false)
#define netChk(e)			do{ Result hRes = e; if( !(hRes) ) SFErrJmp(Net,hRes); } while(false)
#define netMem(a)			do{ if( (a) == nullptr ) SFErrJmp(Net,ResultCode::OUT_OF_MEMORY); } while(false)
#define netErr(e)			SFErrJmp(Net,e)



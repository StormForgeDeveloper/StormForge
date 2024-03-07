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
#include "SFProtocol.h"
#include "Net/SFMessage.h"
#include "Net/SFNetCtrlIDs.h"
#if SF_PLATFORM != SF_PLATFORM_WINDOWS
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "Util/SFString.h"

namespace SF {
namespace Net {
	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection Interface
	//
#if SF_PLATFORM != SF_PLATFORM_WINDOWS
#ifndef SOCKET_ERROR
	#define SOCKET_ERROR (-1)
#endif
#endif

	static constexpr int MAX_STRING_TEMP_BUFF_SIZE = 1024 + 512;

	// Maximum packet size preventing fragmentation
	// https://en.wikipedia.org/wiki/IPv6_packet#Fragmentation
	static constexpr size_t MAX_PACKET_SIZE = 1280; 

	////////////////////////////////////////////////////////////////////////////////
	//
	//	connection state definitions
	//

	// Connection state
	enum class ConnectionState : uint8_t
	{
		NONE,			// None just created
		WAITRW,			// Waiting RW enabled state
		UDP_WAITING,	// UDP incoming Waiting
		CONNECTING,		// Connecting sequence
		CHECKVERSION,	// Checking protocol version
		CONNECTED,		// Connected 
		DISCONNECTING,	// Disconnecting
		DISCONNECTED,	// Disconnected
		SLEEP,			// For Mobile connection
		Max
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection Interface
	//

	class INet;
	class Connection;



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
			EVT_TIMESYNC_RESULT,
		};

		struct ConnectionEventComponents
		{
			// connection result
			Result hr;

			EventTypes		EventType = EventTypes::EVT_NONE;

			// State changed
			ConnectionState State = ConnectionState::NONE;

			ConnectionEventComponents() {}
			ConnectionEventComponents(EventTypes InEventType, ConnectionState InState, Result InHr)
				: hr(InHr)
				, EventType(InEventType)
				, State(InState)
			{}

		} Components;

		uint64_t Composited = 0;

		ConnectionEvent(void* ptr = nullptr)
			: Components()
		{ assert(ptr == nullptr); }

		ConnectionEvent(EventTypes eventType, Result hrRes)
			: Components(eventType, ConnectionState::NONE, hrRes)
		{}

		ConnectionEvent(EventTypes eventType, ConnectionState InState)
			: Components(eventType, InState, ResultCode::SUCCESS)
		{}

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
		NetClass		PeerClass = NetClass::Unknown;

		// Local identification ID
		uint64_t		PeerID = 0;

		PeerInfo() = default;
		PeerInfo(const NetAddress& Addr);
		PeerInfo(NetClass Class, const NetAddress& Addr, uint64_t UID);
		PeerInfo(NetClass Class, uint64_t UID);

		void SetInfo(NetClass Class, const NetAddress& Addr, uint64_t UID);
		void SetInfo(NetClass Class, uint64_t UID);

		bool operator == (const PeerInfo& op) const;
		bool operator != (const PeerInfo& op) const;
	};



#include "SFNetDef.inl"

} // namespace Net



	struct EndpointAddress
	{
		String MessageServer;
		String Channel;

		EndpointAddress(IHeap& heap = GetSystemHeap())
			: MessageServer(heap)
			, Channel(heap)
		{}

		EndpointAddress& operator = (const EndpointAddress& src);
		EndpointAddress& operator = (const char* srcAddress);
	};


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Message endpoint
	//		- message routing endpoint through messaging server
	//

	class MessageEndpoint : public SharedObject
	{
	public:
        virtual SharedPointerT<Net::Connection> GetConnection() const { return {}; }
		virtual bool IsSameEndpoint(const EndpointAddress& messageEndpoint) = 0;
        virtual Result SendMsg(const MessageHeader* messageData) = 0;
	};

    using MessageEndpointPtr = SharedPointerT<MessageEndpoint>;

} // namespace SF


#define netCheck(e) SFCheckResult(Net,e)
#define netCheckPtr(e) SFCheckPtr(Net,e)
#define netCheckMem(e) SFCheckMem(Net,e)


#define netChkPtr(e)		do{ if( (e) == nullptr ) SFErrJmp(Net,ResultCode::INVALID_POINTER); } while(false)
#define netChk(e)			do{ Result hRes = e; if( !(hRes) ) SFErrJmp(Net,hRes); } while(false)
#define netMem(a)			do{ if( (a) == nullptr ) SFErrJmp(Net,ResultCode::OUT_OF_MEMORY); } while(false)
#define netErr(e)			SFErrJmp(Net,e)



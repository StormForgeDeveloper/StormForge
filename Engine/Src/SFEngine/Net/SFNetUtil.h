////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetConst.h"
#include "Util/SFStrUtil.h"
#include "Container/SFHashTable.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Multithread/SFThread.h"
#include "Container/SFCircularPageQueue.h"
#include "Container/SFCircularBufferQueue.h"


namespace SF {

	enum class SockFamily : uint8_t;

namespace Net {

	struct IOBUFFER_WRITE;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Utility functions
	//

	Result Addr2SockAddr( const NetAddress &addr, sockaddr_in6 &sockAddr );
	Result Addr2SockAddr(const NetAddress &addr, sockaddr_in &sockAddr);
	Result Addr2SockAddr(const NetAddress &addr, sockaddr_storage &sockAddr);
	Result SetSockAddr( sockaddr_in6& sockAddr, const char *strAddr, uint16_t usPort );
	Result SetSockAddr(sockaddr_in& sockAddr, const char *strAddr, uint16_t usPort);
	Result SetSockAddr(sockaddr_storage& sockAddr, const char *strAddr, uint16_t usPort);
	Result GetLocalAddressBSD(SockFamily family, NetAddress &addr);
	Result GetLocalAddress(SockFamily family, NetAddress &addr);
	Result GetLocalAddressIPv4(NetAddress &addr);
	Result GetLocalAddressIPv6(NetAddress &addr);

	// Make bind addr with any address
	Result GetAnyBindAddr(const sockaddr_storage &sockAddr, sockaddr_storage&bindAddr);

	// Set local net address with family check. This will remove IPv6 wrapper for IPv4
	Result SetLocalNetAddress(NetAddress &netAddr, const char *strLocalAddress, uint16_t port);

	// Set net address with family check
	Result SetNetAddress(NetAddress &netAddr, const char *strAddress, uint16_t port);

	inline int GetSockAddrSize(const sockaddr_storage &sockAddr) { return sockAddr.ss_family == AF_INET6 ? (int)sizeof(sockaddr_in6) : (int)sizeof(sockaddr_in); }

	// Validate local IP
	Result CheckLocalAddress(SockFamily family, NetAddress &addr);

	/////////////////////////////////////////////////////////////////////////////////
	//
	// Socket value
	//

	// To native socket value
	int ToSockValue(SockFamily family);
	int ToSockValue(SocketType sockType);
	int ToSockProto(SocketType sockType);

	SockFamily ToSockFamily(int family);
	SocketType ToSockType(int family);

	bool operator == ( const sockaddr_in6 &op1, const sockaddr_in6 &op2 );
	bool operator != ( const sockaddr_in6 &op1, const sockaddr_in6 &op2 );

	bool operator == (const sockaddr_storage &op1, const sockaddr_storage &op2);
	bool operator != (const sockaddr_storage &op1, const sockaddr_storage &op2);

	bool operator == ( const NetAddress &op1, const NetAddress &op2 );
	bool operator != ( const NetAddress &op1, const NetAddress &op2 );


    // resolve address
    Result ResolveAddress(const char* address, Array<NetAddress>& outResolvedAddresses);


    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Scoped net system init/uninit
    //      - Initialize net related system in case you need to access net system before engine initialization
    //

    class NetSystemInitializer
    {
    public:
        NetSystemInitializer();
        ~NetSystemInitializer();
    };


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Packet message queue class
	//

	class MsgQueue : public CircularPageQueue<SharedPointerT<MessageData>>
	{
	public:
		typedef CircularPageQueue<SharedPointerT<MessageData>>super;

	public:
		MsgQueue(uint uiNumElePerPage = 512);
		virtual ~MsgQueue();

		// Clear queue element
        void Reset();
	};

	// Write buffer queue
	class WriteBufferQueue : public CircularPageQueueAtomic<IOBUFFER_WRITE*>
	{
	public:
		typedef CircularPageQueueAtomic<IOBUFFER_WRITE*> super;

	public:
		WriteBufferQueue(uint uiNumElePerPage = 512);
		virtual ~WriteBufferQueue();

		// Clear queue element
        void Reset();
    };





} // namespace Net
} // namespace SF




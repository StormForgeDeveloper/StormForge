////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network value definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"




namespace SF {
namespace Net {

////////////////////////////////////////////////////////////////////////////////
//
//	Category : Network
//

	namespace Const
	{
        // https://en.wikipedia.org/wiki/IPv6_packet
        // https://en.wikipedia.org/wiki/User_Datagram_Protocol
        // https://en.wikipedia.org/wiki/IPv6_packet#Fragmentation
        static constexpr int PACKET_SIZE_MAX                = 1280;

        static constexpr int PACKET_GATHER_MAX              = 36;
        static constexpr int PACKET_GATHER_SIZE_MAX         = PACKET_SIZE_MAX;

        static constexpr int INTER_PACKET_SIZE_MAX          = PACKET_SIZE_MAX; // Something can represent UDP frame max
        static constexpr int TCP_PACKET_SIZE_MAX = 50 * 1024;
        static constexpr int READ_PACKET_BUFFER_SIZE_MAX = 2048;

        static constexpr int CONMGR_THREAD_INTERVAL         = 1;		// Connection manager thread interval

		static constexpr int SVR_RECV_BUFFER_SIZE			= 1024*8;
		static constexpr int SVR_SEND_BUFFER_SIZE			= 1024*8;
		static constexpr int SVR_NUM_RECV_THREAD			= 4;        // Gradually deprecated

        static constexpr int TCP_ACCEPT_PENDING_MAX         = 10;
        static constexpr int TCP_CONNECTION_SENDBUFFER_SIZE = 256 * 1024; // 256

        static constexpr int UDP_CLI_RETRY_ONETIME_MAX      = 64;
        static constexpr int UDP_SVR_RETRY_ONETIME_MAX      = 64;
        static constexpr int UDP_CONNECTION_SENDBUFFER_SIZE = 256 * 1024; // 256

        static constexpr int CONNECTION_ZEROPACKET_MAX      = 20;
        static constexpr int CONNECTION_RETRY               = 700;

        static constexpr int MUDP_HEARTBEAT_START_TIME      = 1000 * 60;
        static constexpr int MUDP_HEARTBEAT_TIMEOUT         = 1000 * 60 * 10;

		constexpr int GUARANTEED_PENDING_MAX                   = 256;
		// If send queue has less than this count, the message will be sent quickly. per connection
		constexpr uint AGRESSIVE_SEND_COUNT                 = 20;

		constexpr DurationMS DISCONNECT_RETRY_TIME          = DurationMS(700);
		constexpr DurationMS DISCONNECT_TIMEOUT             = DurationMS(2200);
		constexpr DurationMS SVR_DISCONNECT_TIMEOUT         = DurationMS(2000);

		constexpr DurationMS SVR_CONNECTION_TIMEOUT         = DurationMS(10 * 60 * 1000);
		constexpr DurationMS SEND_RETRY_TIME                = DurationMS(1000);
		constexpr DurationMS MUDP_SEND_RETRY_TIME           = DurationMS(2000);
		constexpr DurationMS MUDP_SEND_RETRY_TIME_BOOSTED = DurationMS(200);
		constexpr DurationMS CONNECTION_RETRY_TIME          = DurationMS(500);

#if defined(_DEBUG) || defined(DEBUG)
		constexpr DurationMS CONNECTION_TIMEOUT = DurationMS(2 * 60 * 1000);
#else
		constexpr DurationMS CONNECTION_TIMEOUT = DurationMS(60 * 1000);
#endif
		constexpr DurationMS HEARTBEAT_TIMEOUT = DurationMS(60 * 1000);

		constexpr DurationMS RELIABLE_SYNC_POLLING_TIME = DurationMS(10 * 1000);
		constexpr DurationMS RELIABLE_SYNC_POLLING_TIME_BOOSTED = DurationMS(500);
		constexpr int RELIABLE_SEND_BOOST = 10;
	};

} // namespace Net
} // namespace SF

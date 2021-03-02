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
		enum NetConstEnum {
		PACKET_GATHER_MAX				= 36,
		PACKET_GATHER_SIZE_MAX			= 1024,

		PACKET_SIZE_MAX					= 1024,
		INTER_PACKET_SIZE_MAX			= 30*1024,

		CONMGR_THREAD_INTERVAL			= 1,		// Connection manager thread interval


		CLI_RECV_BUFFER_SIZE			= 1024*16,
		CLI_SEND_BUFFER_SIZE			= 1024*8,

		CLI_NUM_NETCTRL_THREAD			= 2,
		CLI_NUM_RECV_THREAD				= 1,
		CLI_CONNECTION_TASK_THREAD		= 1,
		CLI_NUM_RECV					= 4,
		CLI_CONNECTION_MAX				= 10,

		CLI_OVERBUFFER_COUNT			= 128, // 66*2

		CLI_GUARANTEDRETRY_ATONCE_MAX	= 4,

		CLI_PEERPUNCH_TIME				= 500,
		CLI_PEERPUNCH_COUNT				= 10,

		CLI_CONMAP_BUCKET_SIZE			= 16,


		SVR_RECV_BUFFER_SIZE			= 1024*8,
		SVR_SEND_BUFFER_SIZE			= 1024*8,

		SVR_INTERNAL_CONNECTION_MAX		= 256,

		SVR_NUM_NETCONTROL_THREAD		= 4,
		SVR_NUM_RECV_THREAD				= 4,
		SVR_CONNECTION_AUTORECOVERY		= 10*1000,

		SVR_OVERBUFFER_COUNT			= 8196,

		SVR_MAX_CONNECT_SEND			= 5,

#ifdef _DEBUG
		SVR_PRIVATE_CONNECTION_POOLCACHE	= 1,
		SVR_PUBLIC_CONNECTION_POOLCACHE	= 1,
#else
		SVR_PRIVATE_CONNECTION_POOLCACHE	= 128,
		SVR_PUBLIC_CONNECTION_POOLCACHE	= 50*1024,
#endif
		SVR_PUBLIC_CONNECTION_BUCKET_SIZE	= 100*1024,
		SVR_PRIVATE_CONNECTION_BUCKET_SIZE	= 256,

		TCP_ACCEPT_PENDING_MAX			= 10,
		TCP_ACCEPT_TRYALLOC_MAX			= 1000,

		UDP_CLI_RETRY_ONETIME_MAX		= 64,
		UDP_SVR_RETRY_ONETIME_MAX		= 64,

		CONNECTION_ZEROPACKET_MAX		= 20,
		CONNECTION_RETRY				= 700,

		MUDP_HEARTBEAT_START_TIME		= 1000*60,
		MUDP_HEARTBEAT_TIMEOUT			= 1000*60*10,

		//UDP_HEARTBEAT_TIMEOUT = 1000 * 60 * 10,
		};

		constexpr int GUARANT_PENDING_MAX = 1024;
		// If send queue has less than this count, the message will be sent quickly. per connection
		constexpr uint AGRESSIVE_SEND_COUNT = 20;

		constexpr DurationMS DISCONNECT_RETRY_TIME = DurationMS(700);
		constexpr DurationMS DISCONNECT_TIMEOUT = DurationMS(2200);
		constexpr DurationMS SVR_DISCONNECT_TIMEOUT = DurationMS(2000);

		constexpr DurationMS SVR_CONNECTION_TIMEOUT = DurationMS(10 * 60 * 1000);
		constexpr DurationMS SEND_RETRY_TIME = DurationMS(1000);
		constexpr DurationMS MUDP_SEND_RETRY_TIME = DurationMS(2000);
		constexpr DurationMS MUDP_SEND_RETRY_TIME_BOOSTED = DurationMS(200);
		constexpr DurationMS CONNECTION_RETRY_TIME = DurationMS(500);

		constexpr DurationMS SVR_HEARTBEAT_TIME_UDP = DurationMS(5 * 1000);

		constexpr DurationMS UDP_HEARTBEAT_TIME = DurationMS(20 * 1000);
		constexpr DurationMS TCP_HEARTBEAT_START_TIME = DurationMS(7 * 1000);

		constexpr DurationMS SVR_HEARTBEAT_TIME_PEER = DurationMS(30 * 1000);

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




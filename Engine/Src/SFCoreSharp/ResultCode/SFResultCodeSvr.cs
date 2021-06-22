﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated file, Svr
//
////////////////////////////////////////////////////////////////////////////////

using System;


namespace SF {
	public partial struct ResultCode {

		// Server service failed 
		public const int SVR_SERVICE_FAILED =                               unchecked((int)0xE7120000); 

		// Timed out 
		public const int SVR_TIMEOUT =                                      unchecked((int)0xE7120001); 

		// Transaction has invalid state transition 
		public const int SVR_TRANSACTION_INVALID_STATE =                    unchecked((int)0xE7120002); 

		// Server Transaction timed out 
		public const int SVR_INVALID_TRANSITION =                           unchecked((int)0xE7120003); 

		// Transaction process Time out 
		public const int SVR_TRANSACTION_TIMEOUT =                          unchecked((int)0xE7120004); 

		// Failed to route message 
		public const int SVR_ROUTEMSG_FAILED =                              unchecked((int)0xE7120005); 

		// No result handler 
		public const int SVR_NO_RESULT_HANDLER =                            unchecked((int)0xE7120006); 

		// No message handler 
		public const int SVR_NO_MESSAGE_HANDLER =                           unchecked((int)0xE7120007); 

		// Invalid server ID 
		public const int SVR_INVALID_SERVERID =                             unchecked((int)0xE7120008); 

		// Player not found 
		public const int SVR_PLAYER_NOT_FOUND =                             unchecked((int)0xE7120009); 

		// Player state is invalid 
		public const int SVR_INVALID_PLAYER_STATE =                         unchecked((int)0xE712000A); 

		// Invalid player game db data 
		public const int SVR_INVALID_PLAYER_GAMEDB =                        unchecked((int)0xE712000B); 

		// Not expected server message 
		public const int SVR_NOTEXPECTED_MESSAGE =                          unchecked((int)0xE712000C); 

		// Invalid entity UID 
		public const int SVR_INVALID_ENTITYUID =                            unchecked((int)0xE712000D); 

		// Cluster service not ready 
		public const int SVR_CLUSTER_NOTREADY =                             unchecked((int)0xE712000E); 

		// Invalid cluster type 
		public const int SVR_INVALID_CLUSTERTYPE =                          unchecked((int)0xE712000F); 

		// Invalid cluster ID 
		public const int SVR_INVALID_CLUSTERID =                            unchecked((int)0xE7120010); 

		// Invalid queue item 
		public const int SVR_INVALID_QUEUEITEM =                            unchecked((int)0xE7120011); 

		// Queue item is canceled 
		public const int SVR_QUEUEITEM_CANCELED =                           unchecked((int)0xE7120012); 

		// There is no item in queue 
		public const int SVR_NOITEM_INQUEUE =                               unchecked((int)0xE7120013); 

		// Already in queue 
		public const int SVR_ALREADY_INQUEUE =                              unchecked((int)0xE7120014); 

		// Queue item is reserved 
		public const int SVR_RESERVED_QUEUEITEM =                           unchecked((int)0xE7120015); 

		// Cluster doesn't have any assigned master 
		public const int SVR_CLUSTER_NOMASTER =                             unchecked((int)0xE7120016); 

		// Queue item is reserved for cancel 
		public const int SUCCESS_SVR_QUEUEITEM_CANCEL_PENDED =              unchecked((int)0x27120017); 

		// Purchase canceled 
		public const int SVR_PURCHASE_CANCELED =                            unchecked((int)0xE7120018); 

		// Invalid receipt info 
		public const int SVR_INVALID_PURCHASE_INFO =                        unchecked((int)0xE7120019); 

		// Invalid duplicated purchase 
		public const int SVR_INVALID_PURCHASE_DUPLICATED =                  unchecked((int)0xE712001A); 

		// External auth fail 
		public const int SVR_INVALID_EXTERNAL_AUTH =                        unchecked((int)0xE712001B); 

		// External server is not available 
		public const int SVR_EXTERNAL_SERVER_UNAVALIABLE =                  unchecked((int)0xE712001C); 

		// Invalid receipt result from server 
		public const int SVR_INVALID_PURCHASE_FORMAT =                      unchecked((int)0xE712001D); 

		// The protocol is not supported. 
		public const int SVR_CURL_UNSUPPORTED_PROTOCOL =                    unchecked((int)0xE712001E); 

		// CURL initialization is failed. 
		public const int SVR_CURL_FAILED_INIT =                             unchecked((int)0xE712001F); 

		// Invalid URL format. 
		public const int SVR_CURL_URL_MALFORMAT =                           unchecked((int)0xE7120020); 

		// Not a build-in feature. 
		public const int SVR_CURL_NOT_BUILT_IN =                            unchecked((int)0xE7120021); 

		// Failed to resolve URL. 
		public const int SVR_CURL_COULDNT_RESOLVE_PROXY =                   unchecked((int)0xE7120022); 

		// Failed to resolve URL. 
		public const int SVR_CURL_COULDNT_RESOLVE_HOST =                    unchecked((int)0xE7120023); 

		// Connection is failed 
		public const int SVR_CURL_COULDNT_CONNECT =                         unchecked((int)0xE7120024); 

		// HTTP Post can't be done. 
		public const int SVR_CURL_HTTP_POST_ERROR =                         unchecked((int)0xE7120025); 

		// Not supported SSL type. 
		public const int SVR_CURL_SSL_ENGINE_NOTFOUND =                     unchecked((int)0xE7120026); 

		// Not supported SSL type. 
		public const int SVR_CURL_SSL_ENGINE_SETFAILED =                    unchecked((int)0xE7120027); 

		// Network send failed 
		public const int SVR_CURL_SEND_ERROR =                              unchecked((int)0xE7120028); 

		// Network receive failed 
		public const int SVR_CURL_RECV_ERROR =                              unchecked((int)0xE7120029); 

		// Invalid SSL setting. 
		public const int SVR_CURL_USE_SSL_FAILED =                          unchecked((int)0xE712002A); 

		// No Connection is available now. 
		public const int SVR_CURL_NO_CONNECTION_AVAILABLE =                 unchecked((int)0xE712002B); 

		// Invalid state transition 
		public const int SVR_INVALID_STATE =                                unchecked((int)0xE712002C); 

		// Invalid purchase environment(public/test) 
		public const int SVR_INVALID_PURCHASE_MODE =                        unchecked((int)0xE712002D); 

		// Invalid Task group ID 
		public const int SVR_INVALID_TASK_GROUPID =                         unchecked((int)0xE712002E); 

	}
}




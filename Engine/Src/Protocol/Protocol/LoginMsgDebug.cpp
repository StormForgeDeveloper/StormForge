////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Login Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/LoginMsgDebug.h"
#include "Protocol/LoginMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// Login Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTraceLogin()
		{
 			// Cmd: Login with ID/PW request
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginCmd::MID.IDSeq.MsgID,&Message::Login::LoginCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginRes::MID.IDSeq.MsgID,&Message::Login::LoginRes::TraceOut));
			// Cmd: Login with steam login info
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginWithSteamCmd::MID.IDSeq.MsgID,&Message::Login::LoginWithSteamCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginWithSteamRes::MID.IDSeq.MsgID,&Message::Login::LoginWithSteamRes::TraceOut));
		}; // void RegisterDebugTraceLogin()


	}; // namespace Protocol
}; // namespace SF



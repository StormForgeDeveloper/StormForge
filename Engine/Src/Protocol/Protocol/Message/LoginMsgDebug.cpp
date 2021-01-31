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
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/LoginMsgDebug.h"
#include "Protocol/Message/LoginMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// Login Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTraceLogin()
		{
 			// Cmd: Login request
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginCmd::MID.IDSeq.MsgID,&Message::Login::LoginCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginRes::MID.IDSeq.MsgID,&Message::Login::LoginRes::TraceOut));
			// Cmd: Login request with Facebook UID
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginByFacebookCmd::MID.IDSeq.MsgID,&Message::Login::LoginByFacebookCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::LoginByFacebookRes::MID.IDSeq.MsgID,&Message::Login::LoginByFacebookRes::TraceOut));
			// Cmd: Login request
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::CreateRandomUserCmd::MID.IDSeq.MsgID,&Message::Login::CreateRandomUserCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::CreateRandomUserRes::MID.IDSeq.MsgID,&Message::Login::CreateRandomUserRes::TraceOut));
			// Cmd: Update my score and Get Ranking list
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::UpdateMyScoreCmd::MID.IDSeq.MsgID,&Message::Login::UpdateMyScoreCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::UpdateMyScoreRes::MID.IDSeq.MsgID,&Message::Login::UpdateMyScoreRes::TraceOut));
			// Cmd: Get Ranking lise
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::GetRankingListCmd::MID.IDSeq.MsgID,&Message::Login::GetRankingListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::GetRankingListRes::MID.IDSeq.MsgID,&Message::Login::GetRankingListRes::TraceOut));
			// Cmd: For network test
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::DataTestCmd::MID.IDSeq.MsgID,&Message::Login::DataTestCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::DataTestRes::MID.IDSeq.MsgID,&Message::Login::DataTestRes::TraceOut));
			// C2S: Heartbeat
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::HeartbeatC2SEvt::MID.IDSeq.MsgID,&Message::Login::HeartbeatC2SEvt::TraceOut));
			// Cmd: Write All!! User Score and Ranking list
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::DebugPrintALLRankingCmd::MID.IDSeq.MsgID,&Message::Login::DebugPrintALLRankingCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Login::DebugPrintALLRankingRes::MID.IDSeq.MsgID,&Message::Login::DebugPrintALLRankingRes::TraceOut));
		}; // void RegisterDebugTraceLogin()


	}; // namespace Protocol
}; // namespace SF



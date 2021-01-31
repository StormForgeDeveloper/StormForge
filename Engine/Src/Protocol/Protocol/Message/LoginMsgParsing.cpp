////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Login Message parsing implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/LoginMsgParsing.h"
#include "Protocol/Message/LoginMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 
		///////////////////////////////////////////////////////////////
		// Login message parser mapping

		extern std::unordered_map<uint32_t,HandleParseMessageTo> MessageParseToVariableMap;
		extern std::unordered_map<uint32_t,HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;

		void RegisterParserLogin()
		{
 			// Cmd: Login request
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginCmd::MID.IDSeq.MsgID,&Message::Login::LoginCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginCmd::MID.IDSeq.MsgID,&Message::Login::LoginCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginRes::MID.IDSeq.MsgID,&Message::Login::LoginRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginRes::MID.IDSeq.MsgID,&Message::Login::LoginRes::ParseMessageToMessageBase));
			// Cmd: Login request with Facebook UID
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginByFacebookCmd::MID.IDSeq.MsgID,&Message::Login::LoginByFacebookCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginByFacebookCmd::MID.IDSeq.MsgID,&Message::Login::LoginByFacebookCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginByFacebookRes::MID.IDSeq.MsgID,&Message::Login::LoginByFacebookRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginByFacebookRes::MID.IDSeq.MsgID,&Message::Login::LoginByFacebookRes::ParseMessageToMessageBase));
			// Cmd: Login request
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::CreateRandomUserCmd::MID.IDSeq.MsgID,&Message::Login::CreateRandomUserCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::CreateRandomUserCmd::MID.IDSeq.MsgID,&Message::Login::CreateRandomUserCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::CreateRandomUserRes::MID.IDSeq.MsgID,&Message::Login::CreateRandomUserRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::CreateRandomUserRes::MID.IDSeq.MsgID,&Message::Login::CreateRandomUserRes::ParseMessageToMessageBase));
			// Cmd: Update my score and Get Ranking list
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::UpdateMyScoreCmd::MID.IDSeq.MsgID,&Message::Login::UpdateMyScoreCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::UpdateMyScoreCmd::MID.IDSeq.MsgID,&Message::Login::UpdateMyScoreCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::UpdateMyScoreRes::MID.IDSeq.MsgID,&Message::Login::UpdateMyScoreRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::UpdateMyScoreRes::MID.IDSeq.MsgID,&Message::Login::UpdateMyScoreRes::ParseMessageToMessageBase));
			// Cmd: Get Ranking lise
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::GetRankingListCmd::MID.IDSeq.MsgID,&Message::Login::GetRankingListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::GetRankingListCmd::MID.IDSeq.MsgID,&Message::Login::GetRankingListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::GetRankingListRes::MID.IDSeq.MsgID,&Message::Login::GetRankingListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::GetRankingListRes::MID.IDSeq.MsgID,&Message::Login::GetRankingListRes::ParseMessageToMessageBase));
			// Cmd: For network test
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::DataTestCmd::MID.IDSeq.MsgID,&Message::Login::DataTestCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::DataTestCmd::MID.IDSeq.MsgID,&Message::Login::DataTestCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::DataTestRes::MID.IDSeq.MsgID,&Message::Login::DataTestRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::DataTestRes::MID.IDSeq.MsgID,&Message::Login::DataTestRes::ParseMessageToMessageBase));
			// C2S: Heartbeat
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::HeartbeatC2SEvt::MID.IDSeq.MsgID,&Message::Login::HeartbeatC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::HeartbeatC2SEvt::MID.IDSeq.MsgID,&Message::Login::HeartbeatC2SEvt::ParseMessageToMessageBase));
			// Cmd: Write All!! User Score and Ranking list
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::DebugPrintALLRankingCmd::MID.IDSeq.MsgID,&Message::Login::DebugPrintALLRankingCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::DebugPrintALLRankingCmd::MID.IDSeq.MsgID,&Message::Login::DebugPrintALLRankingCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::DebugPrintALLRankingRes::MID.IDSeq.MsgID,&Message::Login::DebugPrintALLRankingRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::DebugPrintALLRankingRes::MID.IDSeq.MsgID,&Message::Login::DebugPrintALLRankingRes::ParseMessageToMessageBase));
		}; // void RegisterParserLogin()


	}; // namespace Protocol
}; // namespace SF



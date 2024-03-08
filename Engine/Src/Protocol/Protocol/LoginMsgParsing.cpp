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
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/LoginMsgParsing.h"
#include "Protocol/LoginMsgClass.h"



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
 			// Cmd: Login with ID/PW request
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginCmd::MID.ID,&Message::Login::LoginCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginCmd::MID.ID,&Message::Login::LoginCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginRes::MID.ID,&Message::Login::LoginRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginRes::MID.ID,&Message::Login::LoginRes::ParseMessageToMessageBase));
			// Cmd: Login with steam login info
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginWithSteamCmd::MID.ID,&Message::Login::LoginWithSteamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginWithSteamCmd::MID.ID,&Message::Login::LoginWithSteamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Login::LoginWithSteamRes::MID.ID,&Message::Login::LoginWithSteamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Login::LoginWithSteamRes::MID.ID,&Message::Login::LoginWithSteamRes::ParseMessageToMessageBase));
		}; // void RegisterParserLogin()


	}; // namespace Protocol
}; // namespace SF



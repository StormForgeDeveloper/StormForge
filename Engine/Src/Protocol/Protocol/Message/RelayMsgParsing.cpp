////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Relay Message parsing implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/RelayMsgParsing.h"
#include "Protocol/Message/RelayMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 
		///////////////////////////////////////////////////////////////
		// Relay message parser mapping

		extern std::unordered_map<uint32_t,HandleParseMessageTo> MessageParseToVariableMap;
		extern std::unordered_map<uint32_t,HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;

		void RegisterParserRelay()
		{
 			// C2S: Event for Player Join request.
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::JoinRelayInstanceC2SEvt::MID.IDSeq.MsgID,&Message::Relay::JoinRelayInstanceC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::JoinRelayInstanceC2SEvt::MID.IDSeq.MsgID,&Message::Relay::JoinRelayInstanceC2SEvt::ParseMessageToMessageBase));
			// S2C: Event for joined player
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::JoinRelayInstanceResS2CEvt::MID.IDSeq.MsgID,&Message::Relay::JoinRelayInstanceResS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::JoinRelayInstanceResS2CEvt::MID.IDSeq.MsgID,&Message::Relay::JoinRelayInstanceResS2CEvt::ParseMessageToMessageBase));
			// C2S: Event for Player Join request.
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::LeaveRelayInstanceC2SEvt::MID.IDSeq.MsgID,&Message::Relay::LeaveRelayInstanceC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::LeaveRelayInstanceC2SEvt::MID.IDSeq.MsgID,&Message::Relay::LeaveRelayInstanceC2SEvt::ParseMessageToMessageBase));
			// S2C: Event for Player joined.
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::PlayerJoinS2CEvt::MID.IDSeq.MsgID,&Message::Relay::PlayerJoinS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::PlayerJoinS2CEvt::MID.IDSeq.MsgID,&Message::Relay::PlayerJoinS2CEvt::ParseMessageToMessageBase));
			// S2C: Event for Player left.
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::PlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Relay::PlayerLeftS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::PlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Relay::PlayerLeftS2CEvt::ParseMessageToMessageBase));
			// C2S: Relay packet
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::RelayPacketC2SEvt::MID.IDSeq.MsgID,&Message::Relay::RelayPacketC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::RelayPacketC2SEvt::MID.IDSeq.MsgID,&Message::Relay::RelayPacketC2SEvt::ParseMessageToMessageBase));
			// Cmd: Create stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::CreateStreamCmd::MID.IDSeq.MsgID,&Message::Relay::CreateStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::CreateStreamCmd::MID.IDSeq.MsgID,&Message::Relay::CreateStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::CreateStreamRes::MID.IDSeq.MsgID,&Message::Relay::CreateStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::CreateStreamRes::MID.IDSeq.MsgID,&Message::Relay::CreateStreamRes::ParseMessageToMessageBase));
			// Cmd: Open stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::FindStreamCmd::MID.IDSeq.MsgID,&Message::Relay::FindStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::FindStreamCmd::MID.IDSeq.MsgID,&Message::Relay::FindStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::FindStreamRes::MID.IDSeq.MsgID,&Message::Relay::FindStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::FindStreamRes::MID.IDSeq.MsgID,&Message::Relay::FindStreamRes::ParseMessageToMessageBase));
			// Cmd: Delete stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::DeleteStreamCmd::MID.IDSeq.MsgID,&Message::Relay::DeleteStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::DeleteStreamCmd::MID.IDSeq.MsgID,&Message::Relay::DeleteStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::DeleteStreamRes::MID.IDSeq.MsgID,&Message::Relay::DeleteStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::DeleteStreamRes::MID.IDSeq.MsgID,&Message::Relay::DeleteStreamRes::ParseMessageToMessageBase));
			// Cmd: Get stream list
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::GetStreamListCmd::MID.IDSeq.MsgID,&Message::Relay::GetStreamListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::GetStreamListCmd::MID.IDSeq.MsgID,&Message::Relay::GetStreamListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Relay::GetStreamListRes::MID.IDSeq.MsgID,&Message::Relay::GetStreamListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Relay::GetStreamListRes::MID.IDSeq.MsgID,&Message::Relay::GetStreamListRes::ParseMessageToMessageBase));
		}; // void RegisterParserRelay()


	}; // namespace Protocol
}; // namespace SF



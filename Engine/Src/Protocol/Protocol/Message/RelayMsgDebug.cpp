////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Relay Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/RelayMsgDebug.h"
#include "Protocol/Message/RelayMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// Relay Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTraceRelay()
		{
 			// C2S: Event for Player Join request.
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::JoinRelayInstanceC2SEvt::MID.IDSeq.MsgID,&Message::Relay::JoinRelayInstanceC2SEvt::TraceOut));
			// S2C: Event for joined player
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::JoinRelayInstanceResS2CEvt::MID.IDSeq.MsgID,&Message::Relay::JoinRelayInstanceResS2CEvt::TraceOut));
			// C2S: Event for Player Join request.
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::LeaveRelayInstanceC2SEvt::MID.IDSeq.MsgID,&Message::Relay::LeaveRelayInstanceC2SEvt::TraceOut));
			// S2C: Event for Player joined.
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::PlayerJoinS2CEvt::MID.IDSeq.MsgID,&Message::Relay::PlayerJoinS2CEvt::TraceOut));
			// S2C: Event for Player left.
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::PlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Relay::PlayerLeftS2CEvt::TraceOut));
			// C2S: Relay packet
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::RelayPacketC2SEvt::MID.IDSeq.MsgID,&Message::Relay::RelayPacketC2SEvt::TraceOut));
		}; // void RegisterDebugTraceRelay()


	}; // namespace Protocol
}; // namespace SF



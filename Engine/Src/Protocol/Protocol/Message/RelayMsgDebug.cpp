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
			// Cmd: Create stream instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::CreateStreamingCmd::MID.IDSeq.MsgID,&Message::Relay::CreateStreamingCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::CreateStreamingRes::MID.IDSeq.MsgID,&Message::Relay::CreateStreamingRes::TraceOut));
			// Cmd: Open stream instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::OpenStreamingCmd::MID.IDSeq.MsgID,&Message::Relay::OpenStreamingCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::OpenStreamingRes::MID.IDSeq.MsgID,&Message::Relay::OpenStreamingRes::TraceOut));
			// Cmd: Delete stream instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::DeleteStreamingCmd::MID.IDSeq.MsgID,&Message::Relay::DeleteStreamingCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::DeleteStreamingRes::MID.IDSeq.MsgID,&Message::Relay::DeleteStreamingRes::TraceOut));
			// Cmd: Create stream instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::GetStreamListCmd::MID.IDSeq.MsgID,&Message::Relay::GetStreamListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Relay::GetStreamListRes::MID.IDSeq.MsgID,&Message::Relay::GetStreamListRes::TraceOut));
		}; // void RegisterDebugTraceRelay()


	}; // namespace Protocol
}; // namespace SF



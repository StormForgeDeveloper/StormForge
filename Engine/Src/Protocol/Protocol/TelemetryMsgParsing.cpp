////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Telemetry Message parsing implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/TelemetryMsgParsing.h"
#include "Protocol/TelemetryMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 
		///////////////////////////////////////////////////////////////
		// Telemetry message parser mapping

		extern std::unordered_map<uint32_t,HandleParseMessageTo> MessageParseToVariableMap;
		extern std::unordered_map<uint32_t,HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;

		void RegisterParserTelemetry()
		{
 			// Cmd: Post telemetry event
			MessageParseToVariableMap.insert(std::make_pair(Message::Telemetry::PostEventCmd::MID.ID,&Message::Telemetry::PostEventCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Telemetry::PostEventCmd::MID.ID,&Message::Telemetry::PostEventCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Telemetry::PostEventRes::MID.ID,&Message::Telemetry::PostEventRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Telemetry::PostEventRes::MID.ID,&Message::Telemetry::PostEventRes::ParseMessageToMessageBase));
		}; // void RegisterParserTelemetry()


	}; // namespace Protocol
}; // namespace SF



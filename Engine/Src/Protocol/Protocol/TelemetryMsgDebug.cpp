////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Telemetry Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/TelemetryMsgDebug.h"
#include "Protocol/TelemetryMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// Telemetry Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTraceTelemetry()
		{
 			// Cmd: Post telemetry event
			MessageDebugTraceMap.insert(std::make_pair(Message::Telemetry::PostEventCmd::MID.ID,&Message::Telemetry::PostEventCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Telemetry::PostEventRes::MID.ID,&Message::Telemetry::PostEventRes::TraceOut));
		}; // void RegisterDebugTraceTelemetry()


	}; // namespace Protocol
}; // namespace SF



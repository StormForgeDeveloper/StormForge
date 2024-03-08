////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Generic Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/GenericMsgDebug.h"
#include "Protocol/GenericMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// Generic Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTraceGeneric()
		{
 			// Cmd: Generic failure message
			MessageDebugTraceMap.insert(std::make_pair(Message::Generic::GenericFailureCmd::MID.ID,&Message::Generic::GenericFailureCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Generic::GenericFailureRes::MID.ID,&Message::Generic::GenericFailureRes::TraceOut));
		}; // void RegisterDebugTraceGeneric()


	}; // namespace Protocol
}; // namespace SF



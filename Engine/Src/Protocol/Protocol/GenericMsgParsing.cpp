////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Generic Message parsing implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/GenericMsgParsing.h"
#include "Protocol/GenericMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 
		///////////////////////////////////////////////////////////////
		// Generic message parser mapping

		extern std::unordered_map<uint32_t,HandleParseMessageTo> MessageParseToVariableMap;
		extern std::unordered_map<uint32_t,HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;

		void RegisterParserGeneric()
		{
 			// Cmd: Generic failure message
			MessageParseToVariableMap.insert(std::make_pair(Message::Generic::GenericFailureCmd::MID.IDSeq.MsgID,&Message::Generic::GenericFailureCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Generic::GenericFailureCmd::MID.IDSeq.MsgID,&Message::Generic::GenericFailureCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Generic::GenericFailureRes::MID.IDSeq.MsgID,&Message::Generic::GenericFailureRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Generic::GenericFailureRes::MID.IDSeq.MsgID,&Message::Generic::GenericFailureRes::ParseMessageToMessageBase));
		}; // void RegisterParserGeneric()


	}; // namespace Protocol
}; // namespace SF



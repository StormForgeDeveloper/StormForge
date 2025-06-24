////////////////////////////////////////////////////////////////////////////////
// 
// StormForge
// 
// Author : Generated
// 
// Description : Generic MessageLog
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/GenericMessageID.h"




namespace SF
{
 

	class GenericMessageLog
	{
 		private:
		static bool stm_IsInitialized;
		static flatbuffers::Parser stm_Parser;

		public:
		static Result Initialize();

		static Result GenericFailureCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GenericFailureRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GenericTransactionCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GenericTransactionRes(const char* prefix, const MessageHeader* messageHeader);
		static Result HeartbeatC2SEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PostLogDataCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result PostLogDataRes(const char* prefix, const MessageHeader* messageHeader);

	}; // class GenericMessageLog


}; // namespace SF



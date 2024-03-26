////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Telemetry Message IDs
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Net/SFMessage.h"
#include "SFProtocol.h"


namespace SF
{
 	namespace Message
	{
 		namespace Telemetry
		{
 

			// Cmd: Post telemetry event
			constexpr MessageID MID_PostEventCmd(EMessageType::Command,1,MessageProtocol::Telemetry,0);
			constexpr MessageID MID_PostEventRes(EMessageType::Result,1,MessageProtocol::Telemetry,0);



		} // namespace Telemetry
	} // namespace Message
} // namespace SF




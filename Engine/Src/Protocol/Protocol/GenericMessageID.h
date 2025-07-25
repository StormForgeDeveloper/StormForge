﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Generic Message IDs
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Net/SFMessage.h"
#include "SFProtocol.h"


namespace SF
{
 	namespace Message
	{
 		namespace Generic
		{
 

			// Cmd: Generic failure message
			constexpr MessageID MID_GenericFailureCmd(EMessageType::Command,1,MessageProtocol::Generic,0);
			constexpr MessageID MID_GenericFailureRes(EMessageType::Result,1,MessageProtocol::Generic,0);

			// Cmd: Generic transaction result
			constexpr MessageID MID_GenericTransactionCmd(EMessageType::Command,1,MessageProtocol::Generic,1);
			constexpr MessageID MID_GenericTransactionRes(EMessageType::Result,1,MessageProtocol::Generic,1);

			// Cmd: Generic heartbeat
			constexpr MessageID MID_HeartbeatCmd(EMessageType::Command,1,MessageProtocol::Generic,2);
			constexpr MessageID MID_HeartbeatRes(EMessageType::Result,1,MessageProtocol::Generic,2);

			// Cmd: Post log data through gateway
			constexpr MessageID MID_PostLogDataCmd(EMessageType::Command,1,MessageProtocol::Generic,3);
			constexpr MessageID MID_PostLogDataRes(EMessageType::Result,1,MessageProtocol::Generic,3);



		} // namespace Generic
	} // namespace Message
} // namespace SF




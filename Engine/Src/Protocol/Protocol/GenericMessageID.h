////////////////////////////////////////////////////////////////////////////////
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

			// Cmd: Message bus send message warpper through gateway. it conveys other message inside
			constexpr MessageID MID_MessageBusSendCmd(EMessageType::Command,1,MessageProtocol::Generic,2);
			constexpr MessageID MID_MessageBusSendRes(EMessageType::Result,1,MessageProtocol::Generic,2);

			// Cmd: Listen to the message
			constexpr MessageID MID_MessageBusListenCmd(EMessageType::Command,1,MessageProtocol::Generic,3);
			constexpr MessageID MID_MessageBusListenRes(EMessageType::Result,1,MessageProtocol::Generic,3);

			// Cmd: Post log data through gateway
			constexpr MessageID MID_PostLogDataCmd(EMessageType::Command,1,MessageProtocol::Generic,4);
			constexpr MessageID MID_PostLogDataRes(EMessageType::Result,1,MessageProtocol::Generic,4);



		} // namespace Generic
	} // namespace Message
} // namespace SF




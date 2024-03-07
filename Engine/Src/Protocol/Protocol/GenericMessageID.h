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
			constexpr MessageID MID_GenericFailureCmd(MessageType::Command,1,MessageProtocol::Generic,0);
			constexpr MessageID MID_GenericFailureRes(MessageType::Result,1,MessageProtocol::Generic,0);



		} // namespace Generic
	} // namespace Message
} // namespace SF




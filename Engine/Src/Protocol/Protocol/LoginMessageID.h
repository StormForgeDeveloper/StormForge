////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Login Message IDs
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Net/SFMessage.h"
#include "SFProtocol.h"


namespace SF
{
 	namespace Message
	{
 		namespace Login
		{
 

			// Cmd: Login with ID/PW request
			constexpr MessageID MID_LoginCmd(EMessageType::Command,1,MessageProtocol::Login,0);
			constexpr MessageID MID_LoginRes(EMessageType::Result,1,MessageProtocol::Login,0);

			// Cmd: Login with steam login info
			constexpr MessageID MID_LoginWithSteamCmd(EMessageType::Command,1,MessageProtocol::Login,1);
			constexpr MessageID MID_LoginWithSteamRes(EMessageType::Result,1,MessageProtocol::Login,1);



		} // namespace Login
	} // namespace Message
} // namespace SF




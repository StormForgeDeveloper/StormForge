////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Login Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;


namespace SF.Net
{
 

	public static class MessageIDLogin
	{
 		// Cmd: Login with ID/PW request
		public static readonly MessageID LoginCmd = MessageID.MakeMessageID(MessageType.Command, 1, SF.MessageProtocol.Login, 0);
		public static readonly MessageID LoginRes = MessageID.MakeMessageID(MessageType.Result, 1, SF.MessageProtocol.Login, 0);

		// Cmd: Login with steam login info
		public static readonly MessageID LoginWithSteamCmd = MessageID.MakeMessageID(MessageType.Command, 1, SF.MessageProtocol.Login, 1);
		public static readonly MessageID LoginWithSteamRes = MessageID.MakeMessageID(MessageType.Result, 1, SF.MessageProtocol.Login, 1);

	}; // public static class MessageIDLogin




} // namespace SF.Net



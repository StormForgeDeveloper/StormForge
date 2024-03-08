﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Generic Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;


namespace SF.Net
{
 

	public static class MessageIDGeneric
	{
 		// Cmd: Generic failure message
		public static readonly MessageID GenericFailureCmd = MessageID.MakeMessageID(MessageType.Command, 1, SF.MessageProtocol.Generic, 0);
		public static readonly MessageID GenericFailureRes = MessageID.MakeMessageID(MessageType.Result, 1, SF.MessageProtocol.Generic, 0);

	}; // public static class MessageIDGeneric




} // namespace SF.Net


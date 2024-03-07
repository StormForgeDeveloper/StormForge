////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Telemetry Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;


namespace SF.Net
{
 

	public static class MessageIDTelemetry
	{
 		// Cmd: Post telemetry event
		public static readonly MessageID PostEventCmd = MessageID.MakeMessageID(MessageType.Command, 1, SF.MessageProtocol.Telemetry, 0);
		public static readonly MessageID PostEventRes = MessageID.MakeMessageID(MessageType.Result, 1, SF.MessageProtocol.Telemetry, 0);

	}; // public static class MessageIDTelemetry




} // namespace SF.Net



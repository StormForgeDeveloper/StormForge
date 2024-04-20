////////////////////////////////////////////////////////////////////////////////
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
		public static readonly MessageID GenericFailureCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Generic, 0);
		public static readonly MessageID GenericFailureRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Generic, 0);

		// Cmd: Generic transaction result
		public static readonly MessageID GenericTransactionCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Generic, 1);
		public static readonly MessageID GenericTransactionRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Generic, 1);

		// Cmd: Message bus send message warpper through gateway. it conveys other message inside
		public static readonly MessageID MessageBusSendCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Generic, 2);
		public static readonly MessageID MessageBusSendRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Generic, 2);

		// Cmd: Listen to the message
		public static readonly MessageID MessageBusListenCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Generic, 3);
		public static readonly MessageID MessageBusListenRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Generic, 3);

		// Cmd: Post log data through gateway
		public static readonly MessageID PostLogDataCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Generic, 4);
		public static readonly MessageID PostLogDataRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Generic, 4);

	}; // public static class MessageIDGeneric




} // namespace SF.Net



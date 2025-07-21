////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Game Network RPC send adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using SF;
using SF.Flat;
using SF.Flat.Game;
#nullable enable



namespace SF.Net
{
 

	public class GameRPCSendAdapter : RPCAdapter
	{
 


		public  GameRPCSendAdapter()
		{
 		} // public  GameRPCSendAdapter()
		public  GameRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  GameRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// C2S: Client heartbeat
		public Result  HeartbeatC2SEvt(  )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.HeartbeatC2SEvt.StartHeartbeatC2SEvt(builder);
			var packetOffset = SF.Flat.Game.HeartbeatC2SEvt.EndHeartbeatC2SEvt(builder);
			result = SendMessage(MessageIDGame.HeartbeatC2SEvt, builder, packetOffset.Value);
			return result;
		} // public Result  HeartbeatC2SEvt(  )


		// Cmd: Player connected from a login server and moved to game server
		public Result  JoinGameServerCmd( SF.TransactionID InTransactionID, SF.AccountID InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var AccIDOffset = builder.CreateAccountID(InAccID);
			SF.Flat.Game.JoinGameServerCmd.StartJoinGameServerCmd(builder);
			SF.Flat.Game.JoinGameServerCmd.AddAccId(builder, AccIDOffset);
			SF.Flat.Game.JoinGameServerCmd.AddTicket(builder, InTicket);
			SF.Flat.Game.JoinGameServerCmd.AddLoginEntityUid(builder, InLoginEntityUID);
			var packetOffset = SF.Flat.Game.JoinGameServerCmd.EndJoinGameServerCmd(builder);
			result = SendMessage(MessageIDGame.JoinGameServerCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  JoinGameServerCmd( SF.TransactionID InTransactionID, SF.AccountID InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )

		// Cmd: player completion statues
		public Result  GetAchievementStatsCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			SF.Flat.Game.GetAchievementStatsCmd.StartGetAchievementStatsCmd(builder);
			SF.Flat.Game.GetAchievementStatsCmd.AddCharacterId(builder, CharacterIDOffset);
			SF.Flat.Game.GetAchievementStatsCmd.AddAchievementStatIdfrom(builder, InAchievementStatIDFrom);
			SF.Flat.Game.GetAchievementStatsCmd.AddAchievementStatIdto(builder, InAchievementStatIDTo);
			var packetOffset = SF.Flat.Game.GetAchievementStatsCmd.EndGetAchievementStatsCmd(builder);
			result = SendMessage(MessageIDGame.GetAchievementStatsCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetAchievementStatsCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )

		// Cmd: Player complition state
		public Result  Dummy1Cmd( SF.TransactionID InTransactionID, System.String InComplitionState, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ComplitionStateOffset = builder.CreateString(InComplitionState);
			SF.Flat.Game.Dummy1Cmd.StartDummy1Cmd(builder);
			SF.Flat.Game.Dummy1Cmd.AddComplitionState(builder, ComplitionStateOffset);
			var packetOffset = SF.Flat.Game.Dummy1Cmd.EndDummy1Cmd(builder);
			result = SendMessage(MessageIDGame.Dummy1Cmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  Dummy1Cmd( SF.TransactionID InTransactionID, System.String InComplitionState, Action<SFMessage>? callback = null )

		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public Result  RegisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var GCMRegisteredIDOffset = builder.CreateString(InGCMRegisteredID);
			SF.Flat.Game.RegisterGCMCmd.StartRegisterGCMCmd(builder);
			SF.Flat.Game.RegisterGCMCmd.AddGcmregisteredId(builder, GCMRegisteredIDOffset);
			var packetOffset = SF.Flat.Game.RegisterGCMCmd.EndRegisterGCMCmd(builder);
			result = SendMessage(MessageIDGame.RegisterGCMCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RegisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )

		// Cmd: Unregister Google notification service ID
		public Result  UnregisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var GCMRegisteredIDOffset = builder.CreateString(InGCMRegisteredID);
			SF.Flat.Game.UnregisterGCMCmd.StartUnregisterGCMCmd(builder);
			SF.Flat.Game.UnregisterGCMCmd.AddGcmregisteredId(builder, GCMRegisteredIDOffset);
			var packetOffset = SF.Flat.Game.UnregisterGCMCmd.EndUnregisterGCMCmd(builder);
			result = SendMessage(MessageIDGame.UnregisterGCMCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UnregisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )

		// Cmd: Invite friend
		public Result  InviteFriendCmd( SF.TransactionID InTransactionID, SF.AccountID InFriendID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var FriendIDOffset = builder.CreateAccountID(InFriendID);
			SF.Flat.Game.InviteFriendCmd.StartInviteFriendCmd(builder);
			SF.Flat.Game.InviteFriendCmd.AddFriendId(builder, FriendIDOffset);
			var packetOffset = SF.Flat.Game.InviteFriendCmd.EndInviteFriendCmd(builder);
			result = SendMessage(MessageIDGame.InviteFriendCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  InviteFriendCmd( SF.TransactionID InTransactionID, SF.AccountID InFriendID, Action<SFMessage>? callback = null )

		// Cmd: Accept friend request
		public Result  AcceptFriendRequestCmd( SF.TransactionID InTransactionID, SF.AccountID InInviterID, PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InviterIDOffset = builder.CreateAccountID(InInviterID);
			var InviterPlatformIdOffset = builder.CreatePlayerPlatformID(InInviterPlatformId);
			SF.Flat.Game.AcceptFriendRequestCmd.StartAcceptFriendRequestCmd(builder);
			SF.Flat.Game.AcceptFriendRequestCmd.AddInviterId(builder, InviterIDOffset);
			SF.Flat.Game.AcceptFriendRequestCmd.AddInviterPlatformId(builder, InviterPlatformIdOffset);
			var packetOffset = SF.Flat.Game.AcceptFriendRequestCmd.EndAcceptFriendRequestCmd(builder);
			result = SendMessage(MessageIDGame.AcceptFriendRequestCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  AcceptFriendRequestCmd( SF.TransactionID InTransactionID, SF.AccountID InInviterID, PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )

		// Cmd: Remove friden form the friend list
		public Result  RemoveFriendCmd( SF.TransactionID InTransactionID, SF.AccountID InFriendID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var FriendIDOffset = builder.CreateAccountID(InFriendID);
			SF.Flat.Game.RemoveFriendCmd.StartRemoveFriendCmd(builder);
			SF.Flat.Game.RemoveFriendCmd.AddFriendId(builder, FriendIDOffset);
			var packetOffset = SF.Flat.Game.RemoveFriendCmd.EndRemoveFriendCmd(builder);
			result = SendMessage(MessageIDGame.RemoveFriendCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RemoveFriendCmd( SF.TransactionID InTransactionID, SF.AccountID InFriendID, Action<SFMessage>? callback = null )

		// Cmd: Get friend list
		public Result  GetFriendListCmd( SF.TransactionID InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GetFriendListCmd.StartGetFriendListCmd(builder);
			SF.Flat.Game.GetFriendListCmd.AddStartIndex(builder, InStartIndex);
			SF.Flat.Game.GetFriendListCmd.AddCount(builder, InCount);
			var packetOffset = SF.Flat.Game.GetFriendListCmd.EndGetFriendListCmd(builder);
			result = SendMessage(MessageIDGame.GetFriendListCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetFriendListCmd( SF.TransactionID InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )

		// Cmd: Query notification list
		public Result  GetNotificationListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GetNotificationListCmd.StartGetNotificationListCmd(builder);
			var packetOffset = SF.Flat.Game.GetNotificationListCmd.EndGetNotificationListCmd(builder);
			result = SendMessage(MessageIDGame.GetNotificationListCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetNotificationListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Delete notification
		public Result  DeleteNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.DeleteNotificationCmd.StartDeleteNotificationCmd(builder);
			SF.Flat.Game.DeleteNotificationCmd.AddNotificationId(builder, InNotificationID);
			var packetOffset = SF.Flat.Game.DeleteNotificationCmd.EndDeleteNotificationCmd(builder);
			result = SendMessage(MessageIDGame.DeleteNotificationCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  DeleteNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: Set notification is read
		public Result  SetNotificationReadCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.SetNotificationReadCmd.StartSetNotificationReadCmd(builder);
			SF.Flat.Game.SetNotificationReadCmd.AddNotificationId(builder, InNotificationID);
			var packetOffset = SF.Flat.Game.SetNotificationReadCmd.EndSetNotificationReadCmd(builder);
			result = SendMessage(MessageIDGame.SetNotificationReadCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  SetNotificationReadCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: Accept notification
		public Result  AcceptNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.AcceptNotificationCmd.StartAcceptNotificationCmd(builder);
			SF.Flat.Game.AcceptNotificationCmd.AddNotificationId(builder, InNotificationID);
			var packetOffset = SF.Flat.Game.AcceptNotificationCmd.EndAcceptNotificationCmd(builder);
			result = SendMessage(MessageIDGame.AcceptNotificationCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  AcceptNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformIdCmd( SF.TransactionID InTransactionID, PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlatformPlayerIdOffset = builder.CreatePlayerPlatformID(InPlatformPlayerId);
			SF.Flat.Game.FindPlayerByPlatformIdCmd.StartFindPlayerByPlatformIdCmd(builder);
			SF.Flat.Game.FindPlayerByPlatformIdCmd.AddPlatformPlayerId(builder, PlatformPlayerIdOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByPlatformIdCmd.EndFindPlayerByPlatformIdCmd(builder);
			result = SendMessage(MessageIDGame.FindPlayerByPlatformIdCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  FindPlayerByPlatformIdCmd( SF.TransactionID InTransactionID, PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )

		// Cmd: PlayerId conversion
		public Result  FindPlayerByCharacterNameCmd( SF.TransactionID InTransactionID, System.String InCharacterName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterNameOffset = builder.CreateString(InCharacterName);
			SF.Flat.Game.FindPlayerByCharacterNameCmd.StartFindPlayerByCharacterNameCmd(builder);
			SF.Flat.Game.FindPlayerByCharacterNameCmd.AddCharacterName(builder, CharacterNameOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByCharacterNameCmd.EndFindPlayerByCharacterNameCmd(builder);
			result = SendMessage(MessageIDGame.FindPlayerByCharacterNameCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  FindPlayerByCharacterNameCmd( SF.TransactionID InTransactionID, System.String InCharacterName, Action<SFMessage>? callback = null )

		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformUserNameCmd( SF.TransactionID InTransactionID, SF.EPlatform InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlatformTypeOffset = builder.CreatePlatform(InPlatformType);
			var PlatformUserNameOffset = builder.CreateString(InPlatformUserName);
			SF.Flat.Game.FindPlayerByPlatformUserNameCmd.StartFindPlayerByPlatformUserNameCmd(builder);
			SF.Flat.Game.FindPlayerByPlatformUserNameCmd.AddPlatformType(builder, PlatformTypeOffset);
			SF.Flat.Game.FindPlayerByPlatformUserNameCmd.AddPlatformUserName(builder, PlatformUserNameOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByPlatformUserNameCmd.EndFindPlayerByPlatformUserNameCmd(builder);
			result = SendMessage(MessageIDGame.FindPlayerByPlatformUserNameCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  FindPlayerByPlatformUserNameCmd( SF.TransactionID InTransactionID, SF.EPlatform InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )

		// Cmd: Query playerID list
		public Result  FindPlayerByEMailCmd( SF.TransactionID InTransactionID, System.String InPlayerEMail, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerEMailOffset = builder.CreateString(InPlayerEMail);
			SF.Flat.Game.FindPlayerByEMailCmd.StartFindPlayerByEMailCmd(builder);
			SF.Flat.Game.FindPlayerByEMailCmd.AddPlayerEmail(builder, PlayerEMailOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByEMailCmd.EndFindPlayerByEMailCmd(builder);
			result = SendMessage(MessageIDGame.FindPlayerByEMailCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  FindPlayerByEMailCmd( SF.TransactionID InTransactionID, System.String InPlayerEMail, Action<SFMessage>? callback = null )

		// Cmd: Query playerID list
		public Result  FindPlayerByPlayerIDCmd( SF.TransactionID InTransactionID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			SF.Flat.Game.FindPlayerByPlayerIDCmd.StartFindPlayerByPlayerIDCmd(builder);
			SF.Flat.Game.FindPlayerByPlayerIDCmd.AddPlayerId(builder, PlayerIDOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByPlayerIDCmd.EndFindPlayerByPlayerIDCmd(builder);
			result = SendMessage(MessageIDGame.FindPlayerByPlayerIDCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  FindPlayerByPlayerIDCmd( SF.TransactionID InTransactionID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: *Request Player Status Update
		public Result  RequestPlayerStatusUpdateCmd( SF.TransactionID InTransactionID, SF.AccountID[] InTargetPlayerID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var TargetPlayerIDOffset = builder.CreateAccountIDVector(InTargetPlayerID);
			SF.Flat.Game.RequestPlayerStatusUpdateCmd.StartRequestPlayerStatusUpdateCmd(builder);
			SF.Flat.Game.RequestPlayerStatusUpdateCmd.AddTargetPlayerId(builder, TargetPlayerIDOffset);
			var packetOffset = SF.Flat.Game.RequestPlayerStatusUpdateCmd.EndRequestPlayerStatusUpdateCmd(builder);
			result = SendMessage(MessageIDGame.RequestPlayerStatusUpdateCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RequestPlayerStatusUpdateCmd( SF.TransactionID InTransactionID, SF.AccountID[] InTargetPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Get Ranking list
		public Result  GetRankingListCmd( SF.TransactionID InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GetRankingListCmd.StartGetRankingListCmd(builder);
			SF.Flat.Game.GetRankingListCmd.AddRankingType(builder, InRankingType);
			SF.Flat.Game.GetRankingListCmd.AddBaseRanking(builder, InBaseRanking);
			SF.Flat.Game.GetRankingListCmd.AddCount(builder, InCount);
			var packetOffset = SF.Flat.Game.GetRankingListCmd.EndGetRankingListCmd(builder);
			result = SendMessage(MessageIDGame.GetRankingListCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetRankingListCmd( SF.TransactionID InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )

		// Cmd: Game user game play information
		public Result  GetUserGamePlayerInfoCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GetUserGamePlayerInfoCmd.StartGetUserGamePlayerInfoCmd(builder);
			var packetOffset = SF.Flat.Game.GetUserGamePlayerInfoCmd.EndGetUserGamePlayerInfoCmd(builder);
			result = SendMessage(MessageIDGame.GetUserGamePlayerInfoCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetUserGamePlayerInfoCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Game game play information
		public Result  GetGamePlayerInfoCmd( SF.TransactionID InTransactionID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			SF.Flat.Game.GetGamePlayerInfoCmd.StartGetGamePlayerInfoCmd(builder);
			SF.Flat.Game.GetGamePlayerInfoCmd.AddPlayerId(builder, PlayerIDOffset);
			var packetOffset = SF.Flat.Game.GetGamePlayerInfoCmd.EndGetGamePlayerInfoCmd(builder);
			result = SendMessage(MessageIDGame.GetGamePlayerInfoCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetGamePlayerInfoCmd( SF.TransactionID InTransactionID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Change NickName
		public Result  SetNickNameCmd( SF.TransactionID InTransactionID, System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var NickNameOffset = builder.CreateString(InNickName);
			SF.Flat.Game.SetNickNameCmd.StartSetNickNameCmd(builder);
			SF.Flat.Game.SetNickNameCmd.AddNickName(builder, NickNameOffset);
			SF.Flat.Game.SetNickNameCmd.AddIsCostFree(builder, InIsCostFree);
			var packetOffset = SF.Flat.Game.SetNickNameCmd.EndSetNickNameCmd(builder);
			result = SendMessage(MessageIDGame.SetNickNameCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  SetNickNameCmd( SF.TransactionID InTransactionID, System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )

		// Cmd: Create Party
		public Result  CreatePartyCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.CreatePartyCmd.StartCreatePartyCmd(builder);
			var packetOffset = SF.Flat.Game.CreatePartyCmd.EndCreatePartyCmd(builder);
			result = SendMessage(MessageIDGame.CreatePartyCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CreatePartyCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Join party
		public Result  JoinPartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, SF.AccountID InInviterID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InviterIDOffset = builder.CreateAccountID(InInviterID);
			SF.Flat.Game.JoinPartyCmd.StartJoinPartyCmd(builder);
			SF.Flat.Game.JoinPartyCmd.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.JoinPartyCmd.AddInviterId(builder, InviterIDOffset);
			var packetOffset = SF.Flat.Game.JoinPartyCmd.EndJoinPartyCmd(builder);
			result = SendMessage(MessageIDGame.JoinPartyCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  JoinPartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, SF.AccountID InInviterID, Action<SFMessage>? callback = null )

		// Cmd: Leave party command
		public Result  LeavePartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			SF.Flat.Game.LeavePartyCmd.StartLeavePartyCmd(builder);
			SF.Flat.Game.LeavePartyCmd.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.LeavePartyCmd.AddPlayerId(builder, PlayerIDOffset);
			var packetOffset = SF.Flat.Game.LeavePartyCmd.EndLeavePartyCmd(builder);
			result = SendMessage(MessageIDGame.LeavePartyCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  LeavePartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Kick player from the party
		public Result  PartyKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, SF.AccountID InPlayerID, SF.AccountID InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			var PlayerToKickOffset = builder.CreateAccountID(InPlayerToKick);
			SF.Flat.Game.PartyKickPlayerCmd.StartPartyKickPlayerCmd(builder);
			SF.Flat.Game.PartyKickPlayerCmd.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.PartyKickPlayerCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.Game.PartyKickPlayerCmd.AddPlayerToKick(builder, PlayerToKickOffset);
			var packetOffset = SF.Flat.Game.PartyKickPlayerCmd.EndPartyKickPlayerCmd(builder);
			result = SendMessage(MessageIDGame.PartyKickPlayerCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  PartyKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, SF.AccountID InPlayerID, SF.AccountID InPlayerToKick, Action<SFMessage>? callback = null )

		// Cmd: Invite a player to the party
		public Result  PartyInviteCmd( SF.TransactionID InTransactionID, SF.AccountID InInviteTargetID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InviteTargetIDOffset = builder.CreateAccountID(InInviteTargetID);
			SF.Flat.Game.PartyInviteCmd.StartPartyInviteCmd(builder);
			SF.Flat.Game.PartyInviteCmd.AddInviteTargetId(builder, InviteTargetIDOffset);
			var packetOffset = SF.Flat.Game.PartyInviteCmd.EndPartyInviteCmd(builder);
			result = SendMessage(MessageIDGame.PartyInviteCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  PartyInviteCmd( SF.TransactionID InTransactionID, SF.AccountID InInviteTargetID, Action<SFMessage>? callback = null )

		// Cmd: Send Party quick chat message
		public Result  PartyQuickChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.PartyQuickChatMessageCmd.StartPartyQuickChatMessageCmd(builder);
			SF.Flat.Game.PartyQuickChatMessageCmd.AddQuickChatId(builder, InQuickChatID);
			var packetOffset = SF.Flat.Game.PartyQuickChatMessageCmd.EndPartyQuickChatMessageCmd(builder);
			result = SendMessage(MessageIDGame.PartyQuickChatMessageCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  PartyQuickChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )

		// Cmd: Party chatting
		public Result  PartyChatMessageCmd( SF.TransactionID InTransactionID, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.Game.PartyChatMessageCmd.StartPartyChatMessageCmd(builder);
			SF.Flat.Game.PartyChatMessageCmd.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.Game.PartyChatMessageCmd.EndPartyChatMessageCmd(builder);
			result = SendMessage(MessageIDGame.PartyChatMessageCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  PartyChatMessageCmd( SF.TransactionID InTransactionID, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Join to a game instance
		public Result  RequestJoinGameInstanceCmd( SF.TransactionID InTransactionID, SF.GameInstanceUID InInsUID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InsUIDOffset = builder.CreateGameInstanceUID(InInsUID);
			SF.Flat.Game.RequestJoinGameInstanceCmd.StartRequestJoinGameInstanceCmd(builder);
			SF.Flat.Game.RequestJoinGameInstanceCmd.AddInsUid(builder, InsUIDOffset);
			var packetOffset = SF.Flat.Game.RequestJoinGameInstanceCmd.EndRequestJoinGameInstanceCmd(builder);
			result = SendMessage(MessageIDGame.RequestJoinGameInstanceCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RequestJoinGameInstanceCmd( SF.TransactionID InTransactionID, SF.GameInstanceUID InInsUID, Action<SFMessage>? callback = null )

		// Cmd: Leave game instance
		public Result  RequestLeaveGameInstanceCmd( SF.TransactionID InTransactionID, SF.GameInstanceUID InInsUID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InsUIDOffset = builder.CreateGameInstanceUID(InInsUID);
			SF.Flat.Game.RequestLeaveGameInstanceCmd.StartRequestLeaveGameInstanceCmd(builder);
			SF.Flat.Game.RequestLeaveGameInstanceCmd.AddInsUid(builder, InsUIDOffset);
			var packetOffset = SF.Flat.Game.RequestLeaveGameInstanceCmd.EndRequestLeaveGameInstanceCmd(builder);
			result = SendMessage(MessageIDGame.RequestLeaveGameInstanceCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RequestLeaveGameInstanceCmd( SF.TransactionID InTransactionID, SF.GameInstanceUID InInsUID, Action<SFMessage>? callback = null )

		// Cmd: Search game instance. directory based search schema.    @SearchClass: static/ugc and so on         @SearchDataID: data identification id. could be data table id   
		public Result  SearchGameInstanceCmd( SF.TransactionID InTransactionID, System.String InSearchClass, System.UInt64 InSearchDataID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var SearchClassOffset = builder.CreateString(InSearchClass);
			SF.Flat.Game.SearchGameInstanceCmd.StartSearchGameInstanceCmd(builder);
			SF.Flat.Game.SearchGameInstanceCmd.AddSearchClass(builder, SearchClassOffset);
			SF.Flat.Game.SearchGameInstanceCmd.AddSearchDataId(builder, InSearchDataID);
			var packetOffset = SF.Flat.Game.SearchGameInstanceCmd.EndSearchGameInstanceCmd(builder);
			result = SendMessage(MessageIDGame.SearchGameInstanceCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  SearchGameInstanceCmd( SF.TransactionID InTransactionID, System.String InSearchClass, System.UInt64 InSearchDataID, Action<SFMessage>? callback = null )

		// Cmd: Request Game match
		public Result  RequestGameMatchCmd( SF.TransactionID InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.RequestGameMatchCmd.StartRequestGameMatchCmd(builder);
			SF.Flat.Game.RequestGameMatchCmd.AddNumPlayer(builder, InNumPlayer);
			SF.Flat.Game.RequestGameMatchCmd.AddRequestRole(builder, InRequestRole);
			var packetOffset = SF.Flat.Game.RequestGameMatchCmd.EndRequestGameMatchCmd(builder);
			result = SendMessage(MessageIDGame.RequestGameMatchCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RequestGameMatchCmd( SF.TransactionID InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )

		// Cmd: Cancel Game match
		public Result  CancelGameMatchCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.CancelGameMatchCmd.StartCancelGameMatchCmd(builder);
			var packetOffset = SF.Flat.Game.CancelGameMatchCmd.EndCancelGameMatchCmd(builder);
			result = SendMessage(MessageIDGame.CancelGameMatchCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CancelGameMatchCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		public Result  GetMyUGCGamesCmd( SF.TransactionID InTransactionID, System.String InUGCCategory, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var UGCCategoryOffset = builder.CreateString(InUGCCategory);
			SF.Flat.Game.GetMyUGCGamesCmd.StartGetMyUGCGamesCmd(builder);
			SF.Flat.Game.GetMyUGCGamesCmd.AddUgccategory(builder, UGCCategoryOffset);
			var packetOffset = SF.Flat.Game.GetMyUGCGamesCmd.EndGetMyUGCGamesCmd(builder);
			result = SendMessage(MessageIDGame.GetMyUGCGamesCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetMyUGCGamesCmd( SF.TransactionID InTransactionID, System.String InUGCCategory, Action<SFMessage>? callback = null )

		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		public Result  RequestUGCGameInstanceCmd( SF.TransactionID InTransactionID, System.String InUGCCategory, System.Guid InUGCContentId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var UGCCategoryOffset = builder.CreateString(InUGCCategory);
			var UGCContentIdOffset = builder.CreateGuid(InUGCContentId);
			SF.Flat.Game.RequestUGCGameInstanceCmd.StartRequestUGCGameInstanceCmd(builder);
			SF.Flat.Game.RequestUGCGameInstanceCmd.AddUgccategory(builder, UGCCategoryOffset);
			SF.Flat.Game.RequestUGCGameInstanceCmd.AddUgccontentId(builder, UGCContentIdOffset);
			var packetOffset = SF.Flat.Game.RequestUGCGameInstanceCmd.EndRequestUGCGameInstanceCmd(builder);
			result = SendMessage(MessageIDGame.RequestUGCGameInstanceCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RequestUGCGameInstanceCmd( SF.TransactionID InTransactionID, System.String InUGCCategory, System.Guid InUGCContentId, Action<SFMessage>? callback = null )

		// Cmd: Buy shop item prepare
		public Result  BuyShopItemPrepareCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.BuyShopItemPrepareCmd.StartBuyShopItemPrepareCmd(builder);
			SF.Flat.Game.BuyShopItemPrepareCmd.AddShopItemId(builder, InShopItemID);
			var packetOffset = SF.Flat.Game.BuyShopItemPrepareCmd.EndBuyShopItemPrepareCmd(builder);
			result = SendMessage(MessageIDGame.BuyShopItemPrepareCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  BuyShopItemPrepareCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, Action<SFMessage>? callback = null )

		// Cmd: Buy shop item
		public Result  BuyShopItemCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlatformOffset = builder.CreateString(InPlatform);
			var PackageNameOffset = builder.CreateString(InPackageName);
			var PurchaseTransactionIDOffset = builder.CreateString(InPurchaseTransactionID);
			var PurchaseTokenOffset = builder.Createuint8Vector(InPurchaseToken);
			SF.Flat.Game.BuyShopItemCmd.StartBuyShopItemCmd(builder);
			SF.Flat.Game.BuyShopItemCmd.AddShopItemId(builder, InShopItemID);
			SF.Flat.Game.BuyShopItemCmd.AddPlatform(builder, PlatformOffset);
			SF.Flat.Game.BuyShopItemCmd.AddPackageName(builder, PackageNameOffset);
			SF.Flat.Game.BuyShopItemCmd.AddPurchaseTransactionId(builder, PurchaseTransactionIDOffset);
			SF.Flat.Game.BuyShopItemCmd.AddPurchaseToken(builder, PurchaseTokenOffset);
			var packetOffset = SF.Flat.Game.BuyShopItemCmd.EndBuyShopItemCmd(builder);
			result = SendMessage(MessageIDGame.BuyShopItemCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  BuyShopItemCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )

		// Cmd: Create or Join Chat channel
		public Result  CreateOrJoinChatChannelCmd( SF.TransactionID InTransactionID, System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChannelNameOffset = builder.CreateString(InChannelName);
			var PasscodeOffset = builder.CreateString(InPasscode);
			SF.Flat.Game.CreateOrJoinChatChannelCmd.StartCreateOrJoinChatChannelCmd(builder);
			SF.Flat.Game.CreateOrJoinChatChannelCmd.AddChannelName(builder, ChannelNameOffset);
			SF.Flat.Game.CreateOrJoinChatChannelCmd.AddPasscode(builder, PasscodeOffset);
			var packetOffset = SF.Flat.Game.CreateOrJoinChatChannelCmd.EndCreateOrJoinChatChannelCmd(builder);
			result = SendMessage(MessageIDGame.CreateOrJoinChatChannelCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CreateOrJoinChatChannelCmd( SF.TransactionID InTransactionID, System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )

		// Cmd: Join
		public Result  JoinChatChannelCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.AccountID InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var InviterIDOffset = builder.CreateAccountID(InInviterID);
			var PasscodeOffset = builder.CreateString(InPasscode);
			SF.Flat.Game.JoinChatChannelCmd.StartJoinChatChannelCmd(builder);
			SF.Flat.Game.JoinChatChannelCmd.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.JoinChatChannelCmd.AddInviterId(builder, InviterIDOffset);
			SF.Flat.Game.JoinChatChannelCmd.AddPasscode(builder, PasscodeOffset);
			var packetOffset = SF.Flat.Game.JoinChatChannelCmd.EndJoinChatChannelCmd(builder);
			result = SendMessage(MessageIDGame.JoinChatChannelCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  JoinChatChannelCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.AccountID InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )

		// Cmd: Leave ChatChannel command
		public Result  LeaveChatChannelCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			SF.Flat.Game.LeaveChatChannelCmd.StartLeaveChatChannelCmd(builder);
			SF.Flat.Game.LeaveChatChannelCmd.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.LeaveChatChannelCmd.AddPlayerId(builder, PlayerIDOffset);
			var packetOffset = SF.Flat.Game.LeaveChatChannelCmd.EndLeaveChatChannelCmd(builder);
			result = SendMessage(MessageIDGame.LeaveChatChannelCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  LeaveChatChannelCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Kick player from the ChatChannel
		public Result  ChatChannelKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.AccountID InPlayerID, SF.AccountID InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			var PlayerToKickOffset = builder.CreateAccountID(InPlayerToKick);
			SF.Flat.Game.ChatChannelKickPlayerCmd.StartChatChannelKickPlayerCmd(builder);
			SF.Flat.Game.ChatChannelKickPlayerCmd.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.ChatChannelKickPlayerCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.Game.ChatChannelKickPlayerCmd.AddPlayerToKick(builder, PlayerToKickOffset);
			var packetOffset = SF.Flat.Game.ChatChannelKickPlayerCmd.EndChatChannelKickPlayerCmd(builder);
			result = SendMessage(MessageIDGame.ChatChannelKickPlayerCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  ChatChannelKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.AccountID InPlayerID, SF.AccountID InPlayerToKick, Action<SFMessage>? callback = null )

		// Cmd: Chat channel sending chatting message
		public Result  ChatChannelChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var ChatMetaDataOffset = builder.CreateVariableTable(InChatMetaData);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.Game.ChatChannelChatMessageCmd.StartChatChannelChatMessageCmd(builder);
			SF.Flat.Game.ChatChannelChatMessageCmd.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.ChatChannelChatMessageCmd.AddChatMetaData(builder, ChatMetaDataOffset);
			SF.Flat.Game.ChatChannelChatMessageCmd.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.Game.ChatChannelChatMessageCmd.EndChatChannelChatMessageCmd(builder);
			result = SendMessage(MessageIDGame.ChatChannelChatMessageCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  ChatChannelChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Whisper(tell) other player chatting
		public Result  WhisperMessageCmd( SF.TransactionID InTransactionID, SF.AccountID InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ReceiverIDOffset = builder.CreatePlayerID(InReceiverID);
			var ReceiverNameOffset = builder.CreateString(InReceiverName);
			var ChatMetaDataOffset = builder.CreateVariableTable(InChatMetaData);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.Game.WhisperMessageCmd.StartWhisperMessageCmd(builder);
			SF.Flat.Game.WhisperMessageCmd.AddReceiverId(builder, ReceiverIDOffset);
			SF.Flat.Game.WhisperMessageCmd.AddReceiverName(builder, ReceiverNameOffset);
			SF.Flat.Game.WhisperMessageCmd.AddChatMetaData(builder, ChatMetaDataOffset);
			SF.Flat.Game.WhisperMessageCmd.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.Game.WhisperMessageCmd.EndWhisperMessageCmd(builder);
			result = SendMessage(MessageIDGame.WhisperMessageCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  WhisperMessageCmd( SF.TransactionID InTransactionID, SF.AccountID InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Create character
		public Result  CreateCharacterCmd( SF.TransactionID InTransactionID, System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterNameOffset = builder.CreateString(InCharacterName);
			var PublicDataOffset = builder.CreateVariableTable(InPublicData);
			var PrivateDataOffset = builder.CreateVariableTable(InPrivateData);
			SF.Flat.Game.CreateCharacterCmd.StartCreateCharacterCmd(builder);
			SF.Flat.Game.CreateCharacterCmd.AddCharacterName(builder, CharacterNameOffset);
			SF.Flat.Game.CreateCharacterCmd.AddPublicData(builder, PublicDataOffset);
			SF.Flat.Game.CreateCharacterCmd.AddPrivateData(builder, PrivateDataOffset);
			var packetOffset = SF.Flat.Game.CreateCharacterCmd.EndCreateCharacterCmd(builder);
			result = SendMessage(MessageIDGame.CreateCharacterCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CreateCharacterCmd( SF.TransactionID InTransactionID, System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )

		// Cmd: Delete character
		public Result  DeleteCharacterCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			SF.Flat.Game.DeleteCharacterCmd.StartDeleteCharacterCmd(builder);
			SF.Flat.Game.DeleteCharacterCmd.AddCharacterId(builder, CharacterIDOffset);
			var packetOffset = SF.Flat.Game.DeleteCharacterCmd.EndDeleteCharacterCmd(builder);
			result = SendMessage(MessageIDGame.DeleteCharacterCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  DeleteCharacterCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Get character list
		public Result  GetCharacterListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GetCharacterListCmd.StartGetCharacterListCmd(builder);
			var packetOffset = SF.Flat.Game.GetCharacterListCmd.EndGetCharacterListCmd(builder);
			result = SendMessage(MessageIDGame.GetCharacterListCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetCharacterListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: 
		public Result  GetCharacterDataCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			SF.Flat.Game.GetCharacterDataCmd.StartGetCharacterDataCmd(builder);
			SF.Flat.Game.GetCharacterDataCmd.AddCharacterId(builder, CharacterIDOffset);
			var packetOffset = SF.Flat.Game.GetCharacterDataCmd.EndGetCharacterDataCmd(builder);
			result = SendMessage(MessageIDGame.GetCharacterDataCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetCharacterDataCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Select character
		public Result  SelectCharacterCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			SF.Flat.Game.SelectCharacterCmd.StartSelectCharacterCmd(builder);
			SF.Flat.Game.SelectCharacterCmd.AddCharacterId(builder, CharacterIDOffset);
			var packetOffset = SF.Flat.Game.SelectCharacterCmd.EndSelectCharacterCmd(builder);
			result = SendMessage(MessageIDGame.SelectCharacterCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  SelectCharacterCmd( SF.TransactionID InTransactionID, SF.CharacterID InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		public Result  RequestServerNoticeUpdateCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.RequestServerNoticeUpdateCmd.StartRequestServerNoticeUpdateCmd(builder);
			var packetOffset = SF.Flat.Game.RequestServerNoticeUpdateCmd.EndRequestServerNoticeUpdateCmd(builder);
			result = SendMessage(MessageIDGame.RequestServerNoticeUpdateCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RequestServerNoticeUpdateCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: To call general functionality
		public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ParametersOffset = builder.CreateVariableTable(InParameters);
			SF.Flat.Game.CallFunctionCmd.StartCallFunctionCmd(builder);
			SF.Flat.Game.CallFunctionCmd.AddFunctionName(builder, InFunctionName);
			SF.Flat.Game.CallFunctionCmd.AddParameters(builder, ParametersOffset);
			var packetOffset = SF.Flat.Game.CallFunctionCmd.EndCallFunctionCmd(builder);
			result = SendMessage(MessageIDGame.CallFunctionCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )

	}; // public class GameRPCSendAdapter : RPCAdapter
	public class GameSvrRPCSendAdapter : RPCAdapter
	{
 


		public  GameSvrRPCSendAdapter()
		{
 		} // public  GameSvrRPCSendAdapter()
		public  GameSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  GameSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// Cmd: Player connected from a login server and moved to game server
		public Result  JoinGameServerRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InNickName, SF.GameInstanceUID InGameUID, System.UInt64 InPartyUID, SF.AccountID InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var NickNameOffset = builder.CreateString(InNickName);
			var GameUIDOffset = builder.CreateGameInstanceUID(InGameUID);
			var PartyLeaderIDOffset = builder.CreateAccountID(InPartyLeaderID);
			var MatchingTicketOffset = builder.CreateMatchingQueueTicket(InMatchingTicket);
			SF.Flat.Game.JoinGameServerRes.StartJoinGameServerRes(builder);
			SF.Flat.Game.JoinGameServerRes.AddNickName(builder, NickNameOffset);
			SF.Flat.Game.JoinGameServerRes.AddGameUid(builder, GameUIDOffset);
			SF.Flat.Game.JoinGameServerRes.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.JoinGameServerRes.AddPartyLeaderId(builder, PartyLeaderIDOffset);
			SF.Flat.Game.JoinGameServerRes.AddMatchingTicket(builder, MatchingTicketOffset);
			var packetOffset = SF.Flat.Game.JoinGameServerRes.EndJoinGameServerRes(builder);
			result = SendMessage(MessageIDGame.JoinGameServerRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  JoinGameServerRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InNickName, SF.GameInstanceUID InGameUID, System.UInt64 InPartyUID, SF.AccountID InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )


		// Cmd: player completion statues
		public Result  GetAchievementStatsRes( SF.TransactionID InTransactionID, SF.Result InResult, AchievementStat[] InAchievementStats )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var AchievementStatsOffset = builder.CreateAchievementStatVector(InAchievementStats);
			SF.Flat.Game.GetAchievementStatsRes.StartGetAchievementStatsRes(builder);
			SF.Flat.Game.GetAchievementStatsRes.AddAchievementStats(builder, AchievementStatsOffset);
			var packetOffset = SF.Flat.Game.GetAchievementStatsRes.EndGetAchievementStatsRes(builder);
			result = SendMessage(MessageIDGame.GetAchievementStatsRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetAchievementStatsRes( SF.TransactionID InTransactionID, SF.Result InResult, AchievementStat[] InAchievementStats )


		// Cmd: Player complition state
		public Result  Dummy1Res( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.Dummy1Res.StartDummy1Res(builder);
			var packetOffset = SF.Flat.Game.Dummy1Res.EndDummy1Res(builder);
			result = SendMessage(MessageIDGame.Dummy1Res, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  Dummy1Res( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public Result  RegisterGCMRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.RegisterGCMRes.StartRegisterGCMRes(builder);
			var packetOffset = SF.Flat.Game.RegisterGCMRes.EndRegisterGCMRes(builder);
			result = SendMessage(MessageIDGame.RegisterGCMRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RegisterGCMRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Unregister Google notification service ID
		public Result  UnregisterGCMRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.UnregisterGCMRes.StartUnregisterGCMRes(builder);
			var packetOffset = SF.Flat.Game.UnregisterGCMRes.EndUnregisterGCMRes(builder);
			result = SendMessage(MessageIDGame.UnregisterGCMRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UnregisterGCMRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Invite friend
		public Result  InviteFriendRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.InviteFriendRes.StartInviteFriendRes(builder);
			var packetOffset = SF.Flat.Game.InviteFriendRes.EndInviteFriendRes(builder);
			result = SendMessage(MessageIDGame.InviteFriendRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  InviteFriendRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Accept friend request
		public Result  AcceptFriendRequestRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.PlayerInformation InNewFriend )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var NewFriendOffset = builder.CreatePlayerInformation(InNewFriend);
			SF.Flat.Game.AcceptFriendRequestRes.StartAcceptFriendRequestRes(builder);
			SF.Flat.Game.AcceptFriendRequestRes.AddNewFriend(builder, NewFriendOffset);
			var packetOffset = SF.Flat.Game.AcceptFriendRequestRes.EndAcceptFriendRequestRes(builder);
			result = SendMessage(MessageIDGame.AcceptFriendRequestRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  AcceptFriendRequestRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.PlayerInformation InNewFriend )


		// S2C: Notification for friend request is accepted
		public Result  FriendRequestAcceptedS2CEvt( SF.PlayerInformation InAccepter )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var AccepterOffset = builder.CreatePlayerInformation(InAccepter);
			SF.Flat.Game.FriendRequestAcceptedS2CEvt.StartFriendRequestAcceptedS2CEvt(builder);
			SF.Flat.Game.FriendRequestAcceptedS2CEvt.AddAccepter(builder, AccepterOffset);
			var packetOffset = SF.Flat.Game.FriendRequestAcceptedS2CEvt.EndFriendRequestAcceptedS2CEvt(builder);
			result = SendMessage(MessageIDGame.FriendRequestAcceptedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  FriendRequestAcceptedS2CEvt( SF.PlayerInformation InAccepter )


		// Cmd: Remove friden form the friend list
		public Result  RemoveFriendRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InFriendID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var FriendIDOffset = builder.CreateAccountID(InFriendID);
			SF.Flat.Game.RemoveFriendRes.StartRemoveFriendRes(builder);
			SF.Flat.Game.RemoveFriendRes.AddFriendId(builder, FriendIDOffset);
			var packetOffset = SF.Flat.Game.RemoveFriendRes.EndRemoveFriendRes(builder);
			result = SendMessage(MessageIDGame.RemoveFriendRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RemoveFriendRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InFriendID )


		// S2C: Friend removed
		public Result  FriendRemovedS2CEvt( SF.AccountID InFriendID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var FriendIDOffset = builder.CreateAccountID(InFriendID);
			SF.Flat.Game.FriendRemovedS2CEvt.StartFriendRemovedS2CEvt(builder);
			SF.Flat.Game.FriendRemovedS2CEvt.AddFriendId(builder, FriendIDOffset);
			var packetOffset = SF.Flat.Game.FriendRemovedS2CEvt.EndFriendRemovedS2CEvt(builder);
			result = SendMessage(MessageIDGame.FriendRemovedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  FriendRemovedS2CEvt( SF.AccountID InFriendID )


		// Cmd: Get friend list
		public Result  GetFriendListRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.PlayerInformation[] InFriendList )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var FriendListOffset = builder.CreatePlayerInformationVector(InFriendList);
			SF.Flat.Game.GetFriendListRes.StartGetFriendListRes(builder);
			SF.Flat.Game.GetFriendListRes.AddMaxFriendSlot(builder, InMaxFriendSlot);
			SF.Flat.Game.GetFriendListRes.AddTotalNumberOfFriends(builder, InTotalNumberOfFriends);
			SF.Flat.Game.GetFriendListRes.AddStartIndex(builder, InStartIndex);
			SF.Flat.Game.GetFriendListRes.AddFriendList(builder, FriendListOffset);
			var packetOffset = SF.Flat.Game.GetFriendListRes.EndGetFriendListRes(builder);
			result = SendMessage(MessageIDGame.GetFriendListRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetFriendListRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.PlayerInformation[] InFriendList )


		// Cmd: Query notification list
		public Result  GetNotificationListRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GetNotificationListRes.StartGetNotificationListRes(builder);
			var packetOffset = SF.Flat.Game.GetNotificationListRes.EndGetNotificationListRes(builder);
			result = SendMessage(MessageIDGame.GetNotificationListRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetNotificationListRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Delete notification
		public Result  DeleteNotificationRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InNotificationID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.DeleteNotificationRes.StartDeleteNotificationRes(builder);
			SF.Flat.Game.DeleteNotificationRes.AddNotificationId(builder, InNotificationID);
			var packetOffset = SF.Flat.Game.DeleteNotificationRes.EndDeleteNotificationRes(builder);
			result = SendMessage(MessageIDGame.DeleteNotificationRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  DeleteNotificationRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InNotificationID )


		// Cmd: Set notification is read
		public Result  SetNotificationReadRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InNotificationID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.SetNotificationReadRes.StartSetNotificationReadRes(builder);
			SF.Flat.Game.SetNotificationReadRes.AddNotificationId(builder, InNotificationID);
			var packetOffset = SF.Flat.Game.SetNotificationReadRes.EndSetNotificationReadRes(builder);
			result = SendMessage(MessageIDGame.SetNotificationReadRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  SetNotificationReadRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InNotificationID )


		// Cmd: Accept notification
		public Result  AcceptNotificationRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InNotificationID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.AcceptNotificationRes.StartAcceptNotificationRes(builder);
			SF.Flat.Game.AcceptNotificationRes.AddNotificationId(builder, InNotificationID);
			var packetOffset = SF.Flat.Game.AcceptNotificationRes.EndAcceptNotificationRes(builder);
			result = SendMessage(MessageIDGame.AcceptNotificationRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  AcceptNotificationRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InNotificationID )


		// S2C: Notify new notification
		public Result  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, SF.VariableTable InParameters, System.Byte InIsRead, System.UInt64 InTimeStamp )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ParametersOffset = builder.CreateVariableTable(InParameters);
			SF.Flat.Game.NotifyS2CEvt.StartNotifyS2CEvt(builder);
			SF.Flat.Game.NotifyS2CEvt.AddNotificationId(builder, InNotificationID);
			SF.Flat.Game.NotifyS2CEvt.AddNotificationType(builder, InNotificationType);
			SF.Flat.Game.NotifyS2CEvt.AddParameters(builder, ParametersOffset);
			SF.Flat.Game.NotifyS2CEvt.AddIsRead(builder, InIsRead);
			SF.Flat.Game.NotifyS2CEvt.AddTimeStamp(builder, InTimeStamp);
			var packetOffset = SF.Flat.Game.NotifyS2CEvt.EndNotifyS2CEvt(builder);
			result = SendMessage(MessageIDGame.NotifyS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, SF.VariableTable InParameters, System.Byte InIsRead, System.UInt64 InTimeStamp )


		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformIdRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerId, PlayerPlatformID InPlayerPlatformId )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIdOffset = builder.CreatePlayerID(InPlayerId);
			var PlayerPlatformIdOffset = builder.CreatePlayerPlatformID(InPlayerPlatformId);
			SF.Flat.Game.FindPlayerByPlatformIdRes.StartFindPlayerByPlatformIdRes(builder);
			SF.Flat.Game.FindPlayerByPlatformIdRes.AddPlayerId(builder, PlayerIdOffset);
			SF.Flat.Game.FindPlayerByPlatformIdRes.AddPlayerPlatformId(builder, PlayerPlatformIdOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByPlatformIdRes.EndFindPlayerByPlatformIdRes(builder);
			result = SendMessage(MessageIDGame.FindPlayerByPlatformIdRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  FindPlayerByPlatformIdRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerId, PlayerPlatformID InPlayerPlatformId )


		// Cmd: PlayerId conversion
		public Result  FindPlayerByCharacterNameRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerId )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIdOffset = builder.CreatePlayerID(InPlayerId);
			SF.Flat.Game.FindPlayerByCharacterNameRes.StartFindPlayerByCharacterNameRes(builder);
			SF.Flat.Game.FindPlayerByCharacterNameRes.AddPlayerId(builder, PlayerIdOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByCharacterNameRes.EndFindPlayerByCharacterNameRes(builder);
			result = SendMessage(MessageIDGame.FindPlayerByCharacterNameRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  FindPlayerByCharacterNameRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerId )


		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformUserNameRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerId, PlayerPlatformID InPlayerPlatformId )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIdOffset = builder.CreatePlayerID(InPlayerId);
			var PlayerPlatformIdOffset = builder.CreatePlayerPlatformID(InPlayerPlatformId);
			SF.Flat.Game.FindPlayerByPlatformUserNameRes.StartFindPlayerByPlatformUserNameRes(builder);
			SF.Flat.Game.FindPlayerByPlatformUserNameRes.AddPlayerId(builder, PlayerIdOffset);
			SF.Flat.Game.FindPlayerByPlatformUserNameRes.AddPlayerPlatformId(builder, PlayerPlatformIdOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByPlatformUserNameRes.EndFindPlayerByPlatformUserNameRes(builder);
			result = SendMessage(MessageIDGame.FindPlayerByPlatformUserNameRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  FindPlayerByPlatformUserNameRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerId, PlayerPlatformID InPlayerPlatformId )


		// Cmd: Query playerID list
		public Result  FindPlayerByEMailRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.PlayerInformation InPlayer )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerOffset = builder.CreatePlayerInformation(InPlayer);
			SF.Flat.Game.FindPlayerByEMailRes.StartFindPlayerByEMailRes(builder);
			SF.Flat.Game.FindPlayerByEMailRes.AddPlayer(builder, PlayerOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByEMailRes.EndFindPlayerByEMailRes(builder);
			result = SendMessage(MessageIDGame.FindPlayerByEMailRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  FindPlayerByEMailRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.PlayerInformation InPlayer )


		// Cmd: Query playerID list
		public Result  FindPlayerByPlayerIDRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.PlayerInformation InPlayer )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerOffset = builder.CreatePlayerInformation(InPlayer);
			SF.Flat.Game.FindPlayerByPlayerIDRes.StartFindPlayerByPlayerIDRes(builder);
			SF.Flat.Game.FindPlayerByPlayerIDRes.AddPlayer(builder, PlayerOffset);
			var packetOffset = SF.Flat.Game.FindPlayerByPlayerIDRes.EndFindPlayerByPlayerIDRes(builder);
			result = SendMessage(MessageIDGame.FindPlayerByPlayerIDRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  FindPlayerByPlayerIDRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.PlayerInformation InPlayer )


		// Cmd: *Request Player Status Update
		public Result  RequestPlayerStatusUpdateRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.RequestPlayerStatusUpdateRes.StartRequestPlayerStatusUpdateRes(builder);
			var packetOffset = SF.Flat.Game.RequestPlayerStatusUpdateRes.EndRequestPlayerStatusUpdateRes(builder);
			result = SendMessage(MessageIDGame.RequestPlayerStatusUpdateRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RequestPlayerStatusUpdateRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: *Notify Player Status Updated
		public Result  NotifyPlayerStatusUpdatedS2CEvt( SF.AccountID InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt.StartNotifyPlayerStatusUpdatedS2CEvt(builder);
			SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt.AddLatestActiveTime(builder, InLatestActiveTime);
			SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt.AddIsInGame(builder, InIsInGame);
			var packetOffset = SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt.EndNotifyPlayerStatusUpdatedS2CEvt(builder);
			result = SendMessage(MessageIDGame.NotifyPlayerStatusUpdatedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  NotifyPlayerStatusUpdatedS2CEvt( SF.AccountID InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )


		// Cmd: Get Ranking list
		public Result  GetRankingListRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var RankingOffset = builder.CreateTotalRankingPlayerInformationVector(InRanking);
			SF.Flat.Game.GetRankingListRes.StartGetRankingListRes(builder);
			SF.Flat.Game.GetRankingListRes.AddRanking(builder, RankingOffset);
			var packetOffset = SF.Flat.Game.GetRankingListRes.EndGetRankingListRes(builder);
			result = SendMessage(MessageIDGame.GetRankingListRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetRankingListRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: Game user game play information
		public Result  GetUserGamePlayerInfoRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InAttributes )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var AttributesOffset = builder.CreateVariableTable(InAttributes);
			SF.Flat.Game.GetUserGamePlayerInfoRes.StartGetUserGamePlayerInfoRes(builder);
			SF.Flat.Game.GetUserGamePlayerInfoRes.AddAttributes(builder, AttributesOffset);
			var packetOffset = SF.Flat.Game.GetUserGamePlayerInfoRes.EndGetUserGamePlayerInfoRes(builder);
			result = SendMessage(MessageIDGame.GetUserGamePlayerInfoRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetUserGamePlayerInfoRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InAttributes )


		// Cmd: Game game play information
		public Result  GetGamePlayerInfoRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerID, SF.VariableTable InAttributes )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIDOffset = builder.CreateAccountID(InPlayerID);
			var AttributesOffset = builder.CreateVariableTable(InAttributes);
			SF.Flat.Game.GetGamePlayerInfoRes.StartGetGamePlayerInfoRes(builder);
			SF.Flat.Game.GetGamePlayerInfoRes.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.Game.GetGamePlayerInfoRes.AddAttributes(builder, AttributesOffset);
			var packetOffset = SF.Flat.Game.GetGamePlayerInfoRes.EndGetGamePlayerInfoRes(builder);
			result = SendMessage(MessageIDGame.GetGamePlayerInfoRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetGamePlayerInfoRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.AccountID InPlayerID, SF.VariableTable InAttributes )


		// S2C: Player level up event
		public Result  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.LevelUpS2CEvt.StartLevelUpS2CEvt(builder);
			SF.Flat.Game.LevelUpS2CEvt.AddCurrentTotalExp(builder, InCurrentTotalExp);
			SF.Flat.Game.LevelUpS2CEvt.AddCurrentLevel(builder, InCurrentLevel);
			var packetOffset = SF.Flat.Game.LevelUpS2CEvt.EndLevelUpS2CEvt(builder);
			result = SendMessage(MessageIDGame.LevelUpS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )


		// Cmd: Change NickName
		public Result  SetNickNameRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.SetNickNameRes.StartSetNickNameRes(builder);
			SF.Flat.Game.SetNickNameRes.AddTotalGem(builder, InTotalGem);
			SF.Flat.Game.SetNickNameRes.AddTotalGameMoney(builder, InTotalGameMoney);
			var packetOffset = SF.Flat.Game.SetNickNameRes.EndSetNickNameRes(builder);
			result = SendMessage(MessageIDGame.SetNickNameRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  SetNickNameRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// Cmd: Create Party
		public Result  CreatePartyRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InPartyUID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.CreatePartyRes.StartCreatePartyRes(builder);
			SF.Flat.Game.CreatePartyRes.AddPartyUid(builder, InPartyUID);
			var packetOffset = SF.Flat.Game.CreatePartyRes.EndCreatePartyRes(builder);
			result = SendMessage(MessageIDGame.CreatePartyRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CreatePartyRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InPartyUID )


		// Cmd: Join party
		public Result  JoinPartyRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InPartyUID, SF.AccountID InPartyLeaderID, System.Byte[] InChatHistoryData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PartyLeaderIDOffset = builder.CreateAccountID(InPartyLeaderID);
			var ChatHistoryDataOffset = builder.Createuint8Vector(InChatHistoryData);
			SF.Flat.Game.JoinPartyRes.StartJoinPartyRes(builder);
			SF.Flat.Game.JoinPartyRes.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.JoinPartyRes.AddPartyLeaderId(builder, PartyLeaderIDOffset);
			SF.Flat.Game.JoinPartyRes.AddChatHistoryData(builder, ChatHistoryDataOffset);
			var packetOffset = SF.Flat.Game.JoinPartyRes.EndJoinPartyRes(builder);
			result = SendMessage(MessageIDGame.JoinPartyRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  JoinPartyRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InPartyUID, SF.AccountID InPartyLeaderID, System.Byte[] InChatHistoryData )


		// S2C: Player Joined event
		public Result  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var JoinedPlayerOffset = builder.CreatePlayerInformation(InJoinedPlayer);
			SF.Flat.Game.PartyPlayerJoinedS2CEvt.StartPartyPlayerJoinedS2CEvt(builder);
			SF.Flat.Game.PartyPlayerJoinedS2CEvt.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.PartyPlayerJoinedS2CEvt.AddJoinedPlayer(builder, JoinedPlayerOffset);
			var packetOffset = SF.Flat.Game.PartyPlayerJoinedS2CEvt.EndPartyPlayerJoinedS2CEvt(builder);
			result = SendMessage(MessageIDGame.PartyPlayerJoinedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: Party leader changed event
		public Result  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, SF.AccountID InNewLeaderID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var NewLeaderIDOffset = builder.CreateAccountID(InNewLeaderID);
			SF.Flat.Game.PartyLeaderChangedS2CEvt.StartPartyLeaderChangedS2CEvt(builder);
			SF.Flat.Game.PartyLeaderChangedS2CEvt.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.PartyLeaderChangedS2CEvt.AddNewLeaderId(builder, NewLeaderIDOffset);
			var packetOffset = SF.Flat.Game.PartyLeaderChangedS2CEvt.EndPartyLeaderChangedS2CEvt(builder);
			result = SendMessage(MessageIDGame.PartyLeaderChangedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, SF.AccountID InNewLeaderID )


		// Cmd: Leave party command
		public Result  LeavePartyRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.LeavePartyRes.StartLeavePartyRes(builder);
			var packetOffset = SF.Flat.Game.LeavePartyRes.EndLeavePartyRes(builder);
			result = SendMessage(MessageIDGame.LeavePartyRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  LeavePartyRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Party Player left event
		public Result  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, SF.AccountID InLeftPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var LeftPlayerIDOffset = builder.CreateAccountID(InLeftPlayerID);
			SF.Flat.Game.PartyPlayerLeftS2CEvt.StartPartyPlayerLeftS2CEvt(builder);
			SF.Flat.Game.PartyPlayerLeftS2CEvt.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.PartyPlayerLeftS2CEvt.AddLeftPlayerId(builder, LeftPlayerIDOffset);
			var packetOffset = SF.Flat.Game.PartyPlayerLeftS2CEvt.EndPartyPlayerLeftS2CEvt(builder);
			result = SendMessage(MessageIDGame.PartyPlayerLeftS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, SF.AccountID InLeftPlayerID )


		// Cmd: Kick player from the party
		public Result  PartyKickPlayerRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.PartyKickPlayerRes.StartPartyKickPlayerRes(builder);
			var packetOffset = SF.Flat.Game.PartyKickPlayerRes.EndPartyKickPlayerRes(builder);
			result = SendMessage(MessageIDGame.PartyKickPlayerRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  PartyKickPlayerRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Party Player kicked message
		public Result  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, SF.AccountID InKickedPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var KickedPlayerIDOffset = builder.CreateAccountID(InKickedPlayerID);
			SF.Flat.Game.PartyPlayerKickedS2CEvt.StartPartyPlayerKickedS2CEvt(builder);
			SF.Flat.Game.PartyPlayerKickedS2CEvt.AddPartyUid(builder, InPartyUID);
			SF.Flat.Game.PartyPlayerKickedS2CEvt.AddKickedPlayerId(builder, KickedPlayerIDOffset);
			var packetOffset = SF.Flat.Game.PartyPlayerKickedS2CEvt.EndPartyPlayerKickedS2CEvt(builder);
			result = SendMessage(MessageIDGame.PartyPlayerKickedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, SF.AccountID InKickedPlayerID )


		// Cmd: Invite a player to the party
		public Result  PartyInviteRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.PartyInviteRes.StartPartyInviteRes(builder);
			var packetOffset = SF.Flat.Game.PartyInviteRes.EndPartyInviteRes(builder);
			result = SendMessage(MessageIDGame.PartyInviteRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  PartyInviteRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Party invite requested
		public Result  PartyInviteRequestedS2CEvt( SF.AccountID InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InviterIDOffset = builder.CreateAccountID(InInviterID);
			var InviterNameOffset = builder.CreateString(InInviterName);
			SF.Flat.Game.PartyInviteRequestedS2CEvt.StartPartyInviteRequestedS2CEvt(builder);
			SF.Flat.Game.PartyInviteRequestedS2CEvt.AddInviterId(builder, InviterIDOffset);
			SF.Flat.Game.PartyInviteRequestedS2CEvt.AddInviterName(builder, InviterNameOffset);
			SF.Flat.Game.PartyInviteRequestedS2CEvt.AddPartyToJoinUid(builder, InPartyToJoinUID);
			var packetOffset = SF.Flat.Game.PartyInviteRequestedS2CEvt.EndPartyInviteRequestedS2CEvt(builder);
			result = SendMessage(MessageIDGame.PartyInviteRequestedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PartyInviteRequestedS2CEvt( SF.AccountID InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )


		// Cmd: Send Party quick chat message
		public Result  PartyQuickChatMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.PartyQuickChatMessageRes.StartPartyQuickChatMessageRes(builder);
			var packetOffset = SF.Flat.Game.PartyQuickChatMessageRes.EndPartyQuickChatMessageRes(builder);
			result = SendMessage(MessageIDGame.PartyQuickChatMessageRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  PartyQuickChatMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Party Chatting message event
		public Result  PartyQuickChatMessageS2CEvt( SF.AccountID InSenderID, System.UInt32 InQuickChatID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var SenderIDOffset = builder.CreateAccountID(InSenderID);
			SF.Flat.Game.PartyQuickChatMessageS2CEvt.StartPartyQuickChatMessageS2CEvt(builder);
			SF.Flat.Game.PartyQuickChatMessageS2CEvt.AddSenderId(builder, SenderIDOffset);
			SF.Flat.Game.PartyQuickChatMessageS2CEvt.AddQuickChatId(builder, InQuickChatID);
			var packetOffset = SF.Flat.Game.PartyQuickChatMessageS2CEvt.EndPartyQuickChatMessageS2CEvt(builder);
			result = SendMessage(MessageIDGame.PartyQuickChatMessageS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PartyQuickChatMessageS2CEvt( SF.AccountID InSenderID, System.UInt32 InQuickChatID )


		// Cmd: Party chatting
		public Result  PartyChatMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.PartyChatMessageRes.StartPartyChatMessageRes(builder);
			var packetOffset = SF.Flat.Game.PartyChatMessageRes.EndPartyChatMessageRes(builder);
			result = SendMessage(MessageIDGame.PartyChatMessageRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  PartyChatMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Party Chatting message event
		public Result  PartyChatMessageS2CEvt( SF.AccountID InSenderID, System.String InSenderName, System.String InChatMessage )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var SenderIDOffset = builder.CreateAccountID(InSenderID);
			var SenderNameOffset = builder.CreateString(InSenderName);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.Game.PartyChatMessageS2CEvt.StartPartyChatMessageS2CEvt(builder);
			SF.Flat.Game.PartyChatMessageS2CEvt.AddSenderId(builder, SenderIDOffset);
			SF.Flat.Game.PartyChatMessageS2CEvt.AddSenderName(builder, SenderNameOffset);
			SF.Flat.Game.PartyChatMessageS2CEvt.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.Game.PartyChatMessageS2CEvt.EndPartyChatMessageS2CEvt(builder);
			result = SendMessage(MessageIDGame.PartyChatMessageS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PartyChatMessageS2CEvt( SF.AccountID InSenderID, System.String InSenderName, System.String InChatMessage )


		// Cmd: Join to a game instance
		public Result  RequestJoinGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.GameInstanceUID InInsUID, System.Byte[] InZoneCustomData, System.String InServerPublicAddress )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InsUIDOffset = builder.CreateGameInstanceUID(InInsUID);
			var ZoneCustomDataOffset = builder.CreatebyteVector(InZoneCustomData);
			var ServerPublicAddressOffset = builder.CreateString(InServerPublicAddress);
			SF.Flat.Game.RequestJoinGameInstanceRes.StartRequestJoinGameInstanceRes(builder);
			SF.Flat.Game.RequestJoinGameInstanceRes.AddInsUid(builder, InsUIDOffset);
			SF.Flat.Game.RequestJoinGameInstanceRes.AddZoneCustomData(builder, ZoneCustomDataOffset);
			SF.Flat.Game.RequestJoinGameInstanceRes.AddServerPublicAddress(builder, ServerPublicAddressOffset);
			var packetOffset = SF.Flat.Game.RequestJoinGameInstanceRes.EndRequestJoinGameInstanceRes(builder);
			result = SendMessage(MessageIDGame.RequestJoinGameInstanceRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RequestJoinGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.GameInstanceUID InInsUID, System.Byte[] InZoneCustomData, System.String InServerPublicAddress )


		// Cmd: Leave game instance
		public Result  RequestLeaveGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.RequestLeaveGameInstanceRes.StartRequestLeaveGameInstanceRes(builder);
			var packetOffset = SF.Flat.Game.RequestLeaveGameInstanceRes.EndRequestLeaveGameInstanceRes(builder);
			result = SendMessage(MessageIDGame.RequestLeaveGameInstanceRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RequestLeaveGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Search game instance. directory based search schema.    @SearchClass: static/ugc and so on         @SearchDataID: data identification id. could be data table id   
		public Result  SearchGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InSearchClass, System.UInt64 InSearchDataID, SF.VariableTable[] InGameInstances )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var SearchClassOffset = builder.CreateString(InSearchClass);
			var GameInstancesOffset = builder.CreateVariableTableVector(InGameInstances);
			SF.Flat.Game.SearchGameInstanceRes.StartSearchGameInstanceRes(builder);
			SF.Flat.Game.SearchGameInstanceRes.AddSearchClass(builder, SearchClassOffset);
			SF.Flat.Game.SearchGameInstanceRes.AddSearchDataId(builder, InSearchDataID);
			SF.Flat.Game.SearchGameInstanceRes.AddGameInstances(builder, GameInstancesOffset);
			var packetOffset = SF.Flat.Game.SearchGameInstanceRes.EndSearchGameInstanceRes(builder);
			result = SendMessage(MessageIDGame.SearchGameInstanceRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  SearchGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InSearchClass, System.UInt64 InSearchDataID, SF.VariableTable[] InGameInstances )


		// Cmd: Request Game match
		public Result  RequestGameMatchRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.RequestGameMatchRes.StartRequestGameMatchRes(builder);
			SF.Flat.Game.RequestGameMatchRes.AddTotalGem(builder, InTotalGem);
			SF.Flat.Game.RequestGameMatchRes.AddTotalGameMoney(builder, InTotalGameMoney);
			var packetOffset = SF.Flat.Game.RequestGameMatchRes.EndRequestGameMatchRes(builder);
			result = SendMessage(MessageIDGame.RequestGameMatchRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RequestGameMatchRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game matched
		public Result  GameMatchedS2CEvt( SF.GameInstanceUID InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InsUIDOffset = builder.CreateGameInstanceUID(InInsUID);
			var GameStateOffset = builder.CreateGameStateID(InGameState);
			var ChatHistoryDataOffset = builder.Createuint8Vector(InChatHistoryData);
			var GameLogDataOffset = builder.Createuint8Vector(InGameLogData);
			SF.Flat.Game.GameMatchedS2CEvt.StartGameMatchedS2CEvt(builder);
			SF.Flat.Game.GameMatchedS2CEvt.AddInsUid(builder, InsUIDOffset);
			SF.Flat.Game.GameMatchedS2CEvt.AddTimeStamp(builder, InTimeStamp);
			SF.Flat.Game.GameMatchedS2CEvt.AddGameState(builder, GameStateOffset);
			SF.Flat.Game.GameMatchedS2CEvt.AddDay(builder, InDay);
			SF.Flat.Game.GameMatchedS2CEvt.AddMaxPlayer(builder, InMaxPlayer);
			SF.Flat.Game.GameMatchedS2CEvt.AddPlayerIndex(builder, InPlayerIndex);
			SF.Flat.Game.GameMatchedS2CEvt.AddPlayerCharacter(builder, InPlayerCharacter);
			SF.Flat.Game.GameMatchedS2CEvt.AddRole(builder, InRole);
			SF.Flat.Game.GameMatchedS2CEvt.AddDead(builder, InDead);
			SF.Flat.Game.GameMatchedS2CEvt.AddChatHistoryData(builder, ChatHistoryDataOffset);
			SF.Flat.Game.GameMatchedS2CEvt.AddGameLogData(builder, GameLogDataOffset);
			SF.Flat.Game.GameMatchedS2CEvt.AddStamina(builder, InStamina);
			SF.Flat.Game.GameMatchedS2CEvt.AddTotalGem(builder, InTotalGem);
			SF.Flat.Game.GameMatchedS2CEvt.AddTotalGameMoney(builder, InTotalGameMoney);
			var packetOffset = SF.Flat.Game.GameMatchedS2CEvt.EndGameMatchedS2CEvt(builder);
			result = SendMessage(MessageIDGame.GameMatchedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  GameMatchedS2CEvt( SF.GameInstanceUID InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game match failed
		public Result  GameMatchFailedS2CEvt( SF.Result InFailedReason )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var FailedReasonOffset = builder.CreateResult(InFailedReason);
			SF.Flat.Game.GameMatchFailedS2CEvt.StartGameMatchFailedS2CEvt(builder);
			SF.Flat.Game.GameMatchFailedS2CEvt.AddFailedReason(builder, FailedReasonOffset);
			var packetOffset = SF.Flat.Game.GameMatchFailedS2CEvt.EndGameMatchFailedS2CEvt(builder);
			result = SendMessage(MessageIDGame.GameMatchFailedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  GameMatchFailedS2CEvt( SF.Result InFailedReason )


		// S2C: Game matching started
		public Result  GameMatchingStartedS2CEvt(  )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GameMatchingStartedS2CEvt.StartGameMatchingStartedS2CEvt(builder);
			var packetOffset = SF.Flat.Game.GameMatchingStartedS2CEvt.EndGameMatchingStartedS2CEvt(builder);
			result = SendMessage(MessageIDGame.GameMatchingStartedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  GameMatchingStartedS2CEvt(  )


		// Cmd: Cancel Game match
		public Result  CancelGameMatchRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.CancelGameMatchRes.StartCancelGameMatchRes(builder);
			var packetOffset = SF.Flat.Game.CancelGameMatchRes.EndCancelGameMatchRes(builder);
			result = SendMessage(MessageIDGame.CancelGameMatchRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CancelGameMatchRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: game matching canceled
		public Result  GameMatchingCanceledS2CEvt(  )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.GameMatchingCanceledS2CEvt.StartGameMatchingCanceledS2CEvt(builder);
			var packetOffset = SF.Flat.Game.GameMatchingCanceledS2CEvt.EndGameMatchingCanceledS2CEvt(builder);
			result = SendMessage(MessageIDGame.GameMatchingCanceledS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  GameMatchingCanceledS2CEvt(  )


		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		public Result  GetMyUGCGamesRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.UGCContentInfo[] InContentInfos )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ContentInfosOffset = builder.CreateUGCContentInfoVector(InContentInfos);
			SF.Flat.Game.GetMyUGCGamesRes.StartGetMyUGCGamesRes(builder);
			SF.Flat.Game.GetMyUGCGamesRes.AddContentInfos(builder, ContentInfosOffset);
			var packetOffset = SF.Flat.Game.GetMyUGCGamesRes.EndGetMyUGCGamesRes(builder);
			result = SendMessage(MessageIDGame.GetMyUGCGamesRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetMyUGCGamesRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.UGCContentInfo[] InContentInfos )


		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		public Result  RequestUGCGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InInstanceName )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InstanceNameOffset = builder.CreateString(InInstanceName);
			SF.Flat.Game.RequestUGCGameInstanceRes.StartRequestUGCGameInstanceRes(builder);
			SF.Flat.Game.RequestUGCGameInstanceRes.AddInstanceName(builder, InstanceNameOffset);
			var packetOffset = SF.Flat.Game.RequestUGCGameInstanceRes.EndRequestUGCGameInstanceRes(builder);
			result = SendMessage(MessageIDGame.RequestUGCGameInstanceRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RequestUGCGameInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InInstanceName )


		// S2C: Requested instance is ready and can join
		public Result  InstanceIsReadyS2CEvt( System.String InInstanceName, SF.GameInstanceUID InGameInstanceID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InstanceNameOffset = builder.CreateString(InInstanceName);
			var GameInstanceIDOffset = builder.CreateGameInstanceUID(InGameInstanceID);
			SF.Flat.Game.InstanceIsReadyS2CEvt.StartInstanceIsReadyS2CEvt(builder);
			SF.Flat.Game.InstanceIsReadyS2CEvt.AddInstanceName(builder, InstanceNameOffset);
			SF.Flat.Game.InstanceIsReadyS2CEvt.AddGameInstanceId(builder, GameInstanceIDOffset);
			var packetOffset = SF.Flat.Game.InstanceIsReadyS2CEvt.EndInstanceIsReadyS2CEvt(builder);
			result = SendMessage(MessageIDGame.InstanceIsReadyS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  InstanceIsReadyS2CEvt( System.String InInstanceName, SF.GameInstanceUID InGameInstanceID )


		// Cmd: Buy shop item prepare
		public Result  BuyShopItemPrepareRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InShopItemID, System.String InPurchaseID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PurchaseIDOffset = builder.CreateString(InPurchaseID);
			SF.Flat.Game.BuyShopItemPrepareRes.StartBuyShopItemPrepareRes(builder);
			SF.Flat.Game.BuyShopItemPrepareRes.AddShopItemId(builder, InShopItemID);
			SF.Flat.Game.BuyShopItemPrepareRes.AddPurchaseId(builder, PurchaseIDOffset);
			var packetOffset = SF.Flat.Game.BuyShopItemPrepareRes.EndBuyShopItemPrepareRes(builder);
			result = SendMessage(MessageIDGame.BuyShopItemPrepareRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  BuyShopItemPrepareRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InShopItemID, System.String InPurchaseID )


		// Cmd: Buy shop item
		public Result  BuyShopItemRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InShopItemID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.BuyShopItemRes.StartBuyShopItemRes(builder);
			SF.Flat.Game.BuyShopItemRes.AddShopItemId(builder, InShopItemID);
			var packetOffset = SF.Flat.Game.BuyShopItemRes.EndBuyShopItemRes(builder);
			result = SendMessage(MessageIDGame.BuyShopItemRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  BuyShopItemRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InShopItemID )


		// Cmd: Create or Join Chat channel
		public Result  CreateOrJoinChatChannelRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InChatUID, SF.AccountID InChannelLeaderID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var ChannelLeaderIDOffset = builder.CreatePlayerID(InChannelLeaderID);
			SF.Flat.Game.CreateOrJoinChatChannelRes.StartCreateOrJoinChatChannelRes(builder);
			SF.Flat.Game.CreateOrJoinChatChannelRes.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.CreateOrJoinChatChannelRes.AddChannelLeaderId(builder, ChannelLeaderIDOffset);
			var packetOffset = SF.Flat.Game.CreateOrJoinChatChannelRes.EndCreateOrJoinChatChannelRes(builder);
			result = SendMessage(MessageIDGame.CreateOrJoinChatChannelRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CreateOrJoinChatChannelRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InChatUID, SF.AccountID InChannelLeaderID )


		// Cmd: Join
		public Result  JoinChatChannelRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InChatUID, SF.AccountID InChannelLeaderID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var ChannelLeaderIDOffset = builder.CreatePlayerID(InChannelLeaderID);
			SF.Flat.Game.JoinChatChannelRes.StartJoinChatChannelRes(builder);
			SF.Flat.Game.JoinChatChannelRes.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.JoinChatChannelRes.AddChannelLeaderId(builder, ChannelLeaderIDOffset);
			var packetOffset = SF.Flat.Game.JoinChatChannelRes.EndJoinChatChannelRes(builder);
			result = SendMessage(MessageIDGame.JoinChatChannelRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  JoinChatChannelRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InChatUID, SF.AccountID InChannelLeaderID )


		// S2C: Player Joined event
		public Result  ChatChannelPlayerJoinedS2CEvt( System.UInt32 InChatUID, SF.PlayerInformation InJoinedPlayer )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var JoinedPlayerOffset = builder.CreatePlayerInformation(InJoinedPlayer);
			SF.Flat.Game.ChatChannelPlayerJoinedS2CEvt.StartChatChannelPlayerJoinedS2CEvt(builder);
			SF.Flat.Game.ChatChannelPlayerJoinedS2CEvt.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.ChatChannelPlayerJoinedS2CEvt.AddJoinedPlayer(builder, JoinedPlayerOffset);
			var packetOffset = SF.Flat.Game.ChatChannelPlayerJoinedS2CEvt.EndChatChannelPlayerJoinedS2CEvt(builder);
			result = SendMessage(MessageIDGame.ChatChannelPlayerJoinedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ChatChannelPlayerJoinedS2CEvt( System.UInt32 InChatUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: ChatChannel leader changed event
		public Result  ChatChannelLeaderChangedS2CEvt( System.UInt32 InChatUID, SF.AccountID InNewLeaderID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var NewLeaderIDOffset = builder.CreateAccountID(InNewLeaderID);
			SF.Flat.Game.ChatChannelLeaderChangedS2CEvt.StartChatChannelLeaderChangedS2CEvt(builder);
			SF.Flat.Game.ChatChannelLeaderChangedS2CEvt.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.ChatChannelLeaderChangedS2CEvt.AddNewLeaderId(builder, NewLeaderIDOffset);
			var packetOffset = SF.Flat.Game.ChatChannelLeaderChangedS2CEvt.EndChatChannelLeaderChangedS2CEvt(builder);
			result = SendMessage(MessageIDGame.ChatChannelLeaderChangedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ChatChannelLeaderChangedS2CEvt( System.UInt32 InChatUID, SF.AccountID InNewLeaderID )


		// Cmd: Leave ChatChannel command
		public Result  LeaveChatChannelRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.LeaveChatChannelRes.StartLeaveChatChannelRes(builder);
			var packetOffset = SF.Flat.Game.LeaveChatChannelRes.EndLeaveChatChannelRes(builder);
			result = SendMessage(MessageIDGame.LeaveChatChannelRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  LeaveChatChannelRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: ChatChannel Player left event
		public Result  ChatChannelPlayerLeftS2CEvt( System.UInt32 InChatUID, SF.AccountID InLeftPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var LeftPlayerIDOffset = builder.CreateAccountID(InLeftPlayerID);
			SF.Flat.Game.ChatChannelPlayerLeftS2CEvt.StartChatChannelPlayerLeftS2CEvt(builder);
			SF.Flat.Game.ChatChannelPlayerLeftS2CEvt.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.ChatChannelPlayerLeftS2CEvt.AddLeftPlayerId(builder, LeftPlayerIDOffset);
			var packetOffset = SF.Flat.Game.ChatChannelPlayerLeftS2CEvt.EndChatChannelPlayerLeftS2CEvt(builder);
			result = SendMessage(MessageIDGame.ChatChannelPlayerLeftS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ChatChannelPlayerLeftS2CEvt( System.UInt32 InChatUID, SF.AccountID InLeftPlayerID )


		// Cmd: Kick player from the ChatChannel
		public Result  ChatChannelKickPlayerRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.ChatChannelKickPlayerRes.StartChatChannelKickPlayerRes(builder);
			var packetOffset = SF.Flat.Game.ChatChannelKickPlayerRes.EndChatChannelKickPlayerRes(builder);
			result = SendMessage(MessageIDGame.ChatChannelKickPlayerRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  ChatChannelKickPlayerRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: ChatChannel Player kicked message
		public Result  ChatChannelPlayerKickedS2CEvt( System.UInt32 InChatUID, SF.AccountID InKickedPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChatUIDOffset = builder.CreateEntityUID(InChatUID);
			var KickedPlayerIDOffset = builder.CreateAccountID(InKickedPlayerID);
			SF.Flat.Game.ChatChannelPlayerKickedS2CEvt.StartChatChannelPlayerKickedS2CEvt(builder);
			SF.Flat.Game.ChatChannelPlayerKickedS2CEvt.AddChatUid(builder, ChatUIDOffset);
			SF.Flat.Game.ChatChannelPlayerKickedS2CEvt.AddKickedPlayerId(builder, KickedPlayerIDOffset);
			var packetOffset = SF.Flat.Game.ChatChannelPlayerKickedS2CEvt.EndChatChannelPlayerKickedS2CEvt(builder);
			result = SendMessage(MessageIDGame.ChatChannelPlayerKickedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ChatChannelPlayerKickedS2CEvt( System.UInt32 InChatUID, SF.AccountID InKickedPlayerID )


		// Cmd: Chat channel sending chatting message
		public Result  ChatChannelChatMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.ChatChannelChatMessageRes.StartChatChannelChatMessageRes(builder);
			var packetOffset = SF.Flat.Game.ChatChannelChatMessageRes.EndChatChannelChatMessageRes(builder);
			result = SendMessage(MessageIDGame.ChatChannelChatMessageRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  ChatChannelChatMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: ChatChannel Chatting message event
		public Result  ChatChannelChatMessageS2CEvt( SF.AccountID InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var SenderIDOffset = builder.CreatePlayerID(InSenderID);
			var ChatMetaDataOffset = builder.CreateVariableTable(InChatMetaData);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.Game.ChatChannelChatMessageS2CEvt.StartChatChannelChatMessageS2CEvt(builder);
			SF.Flat.Game.ChatChannelChatMessageS2CEvt.AddSenderId(builder, SenderIDOffset);
			SF.Flat.Game.ChatChannelChatMessageS2CEvt.AddChatMetaData(builder, ChatMetaDataOffset);
			SF.Flat.Game.ChatChannelChatMessageS2CEvt.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.Game.ChatChannelChatMessageS2CEvt.EndChatChannelChatMessageS2CEvt(builder);
			result = SendMessage(MessageIDGame.ChatChannelChatMessageS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ChatChannelChatMessageS2CEvt( SF.AccountID InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Whisper(tell) other player chatting
		public Result  WhisperMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.WhisperMessageRes.StartWhisperMessageRes(builder);
			var packetOffset = SF.Flat.Game.WhisperMessageRes.EndWhisperMessageRes(builder);
			result = SendMessage(MessageIDGame.WhisperMessageRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  WhisperMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Other player whispered(tell) to me message event
		public Result  WhisperMessageS2CEvt( SF.AccountID InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var SenderIDOffset = builder.CreatePlayerID(InSenderID);
			var ChatMetaDataOffset = builder.CreateVariableTable(InChatMetaData);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.Game.WhisperMessageS2CEvt.StartWhisperMessageS2CEvt(builder);
			SF.Flat.Game.WhisperMessageS2CEvt.AddSenderId(builder, SenderIDOffset);
			SF.Flat.Game.WhisperMessageS2CEvt.AddChatMetaData(builder, ChatMetaDataOffset);
			SF.Flat.Game.WhisperMessageS2CEvt.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.Game.WhisperMessageS2CEvt.EndWhisperMessageS2CEvt(builder);
			result = SendMessage(MessageIDGame.WhisperMessageS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhisperMessageS2CEvt( SF.AccountID InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Create character
		public Result  CreateCharacterRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.CharacterID InCharacterID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			SF.Flat.Game.CreateCharacterRes.StartCreateCharacterRes(builder);
			SF.Flat.Game.CreateCharacterRes.AddCharacterId(builder, CharacterIDOffset);
			var packetOffset = SF.Flat.Game.CreateCharacterRes.EndCreateCharacterRes(builder);
			result = SendMessage(MessageIDGame.CreateCharacterRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CreateCharacterRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.CharacterID InCharacterID )


		// Cmd: Delete character
		public Result  DeleteCharacterRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.DeleteCharacterRes.StartDeleteCharacterRes(builder);
			var packetOffset = SF.Flat.Game.DeleteCharacterRes.EndDeleteCharacterRes(builder);
			result = SendMessage(MessageIDGame.DeleteCharacterRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  DeleteCharacterRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Get character list
		public Result  GetCharacterListRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable[] InCharacters )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharactersOffset = builder.CreateVariableTableVector(InCharacters);
			SF.Flat.Game.GetCharacterListRes.StartGetCharacterListRes(builder);
			SF.Flat.Game.GetCharacterListRes.AddCharacters(builder, CharactersOffset);
			var packetOffset = SF.Flat.Game.GetCharacterListRes.EndGetCharacterListRes(builder);
			result = SendMessage(MessageIDGame.GetCharacterListRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetCharacterListRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable[] InCharacters )


		// Cmd: 
		public Result  GetCharacterDataRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InPrivateData, SF.VariableTable InEquipData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PrivateDataOffset = builder.CreateVariableTable(InPrivateData);
			var EquipDataOffset = builder.CreateVariableTable(InEquipData);
			SF.Flat.Game.GetCharacterDataRes.StartGetCharacterDataRes(builder);
			SF.Flat.Game.GetCharacterDataRes.AddPrivateData(builder, PrivateDataOffset);
			SF.Flat.Game.GetCharacterDataRes.AddEquipData(builder, EquipDataOffset);
			var packetOffset = SF.Flat.Game.GetCharacterDataRes.EndGetCharacterDataRes(builder);
			result = SendMessage(MessageIDGame.GetCharacterDataRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetCharacterDataRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InPrivateData, SF.VariableTable InEquipData )


		// Cmd: Select character
		public Result  SelectCharacterRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.CharacterID InCharacterID, SF.VariableTable InAttributes )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			var AttributesOffset = builder.CreateVariableTable(InAttributes);
			SF.Flat.Game.SelectCharacterRes.StartSelectCharacterRes(builder);
			SF.Flat.Game.SelectCharacterRes.AddCharacterId(builder, CharacterIDOffset);
			SF.Flat.Game.SelectCharacterRes.AddAttributes(builder, AttributesOffset);
			var packetOffset = SF.Flat.Game.SelectCharacterRes.EndSelectCharacterRes(builder);
			result = SendMessage(MessageIDGame.SelectCharacterRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  SelectCharacterRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.CharacterID InCharacterID, SF.VariableTable InAttributes )


		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		public Result  RequestServerNoticeUpdateRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Game.RequestServerNoticeUpdateRes.StartRequestServerNoticeUpdateRes(builder);
			var packetOffset = SF.Flat.Game.RequestServerNoticeUpdateRes.EndRequestServerNoticeUpdateRes(builder);
			result = SendMessage(MessageIDGame.RequestServerNoticeUpdateRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RequestServerNoticeUpdateRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Server Notice updated event
		public Result  ServerNoticeS2CEvt( System.SByte InNoticeCategory, System.String InServerNoticeMessage )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ServerNoticeMessageOffset = builder.CreateString(InServerNoticeMessage);
			SF.Flat.Game.ServerNoticeS2CEvt.StartServerNoticeS2CEvt(builder);
			SF.Flat.Game.ServerNoticeS2CEvt.AddNoticeCategory(builder, InNoticeCategory);
			SF.Flat.Game.ServerNoticeS2CEvt.AddServerNoticeMessage(builder, ServerNoticeMessageOffset);
			var packetOffset = SF.Flat.Game.ServerNoticeS2CEvt.EndServerNoticeS2CEvt(builder);
			result = SendMessage(MessageIDGame.ServerNoticeS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ServerNoticeS2CEvt( System.SByte InNoticeCategory, System.String InServerNoticeMessage )


		// Cmd: To call general functionality
		public Result  CallFunctionRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InResults )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ResultsOffset = builder.CreateVariableTable(InResults);
			SF.Flat.Game.CallFunctionRes.StartCallFunctionRes(builder);
			SF.Flat.Game.CallFunctionRes.AddResults(builder, ResultsOffset);
			var packetOffset = SF.Flat.Game.CallFunctionRes.EndCallFunctionRes(builder);
			result = SendMessage(MessageIDGame.CallFunctionRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CallFunctionRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InResults )


	}; // public class GameSvrRPCSendAdapter : RPCAdapter




} // namespace SF.Net
#nullable restore



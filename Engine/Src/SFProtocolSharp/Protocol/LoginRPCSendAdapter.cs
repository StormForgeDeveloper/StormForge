////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Login Network RPC send adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using SF;
using SF.Flat;
using SF.Flat.Login;
#nullable enable



namespace SF.Net
{
 

	public class LoginRPCSendAdapter : RPCAdapter
	{
 


		public  LoginRPCSendAdapter()
		{
 		} // public  LoginRPCSendAdapter()
		public  LoginRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  LoginRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// Cmd: Login with ID/PW request
		public Result  LoginCmd( System.String InUserId, System.String InPassword, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LoginCmd(InTransactionID, InUserId, InPassword, InGameID, callback);
		} // public Result  LoginCmd( System.String InUserId, System.String InPassword, System.String InGameID, Action<SFMessage>? callback = null )
		public Result  LoginCmd( SF.TransactionID InTransactionID, System.String InUserId, System.String InPassword, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var UserIdOffset = builder.CreateString(InUserId);
			var PasswordOffset = builder.CreateString(InPassword);
			var GameIDOffset = builder.CreateString(InGameID);
			SF.Flat.Login.LoginCmd.StartLoginCmd(builder);
			SF.Flat.Login.LoginCmd.AddUserId(builder, UserIdOffset);
			SF.Flat.Login.LoginCmd.AddPassword(builder, PasswordOffset);
			SF.Flat.Login.LoginCmd.AddGameId(builder, GameIDOffset);
			var packetOffset = SF.Flat.Login.LoginCmd.EndLoginCmd(builder);
			result = SendMessage(MessageIDLogin.LoginCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  LoginCmd( SF.TransactionID InTransactionID, System.String InUserId, System.String InPassword, System.String InGameID, Action<SFMessage>? callback = null )

		// Cmd: Login with steam login info
		public Result  LoginWithSteamCmd( System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LoginWithSteamCmd(InTransactionID, InSteamAppID, InSteamPlayerID, InSteamPlayerName, InSteamPlayerToken, InGameID, callback);
		} // public Result  LoginWithSteamCmd( System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )
		public Result  LoginWithSteamCmd( SF.TransactionID InTransactionID, System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var SteamPlayerNameOffset = builder.CreateString(InSteamPlayerName);
			var SteamPlayerTokenOffset = builder.CreateString(InSteamPlayerToken);
			var GameIDOffset = builder.CreateString(InGameID);
			SF.Flat.Login.LoginWithSteamCmd.StartLoginWithSteamCmd(builder);
			SF.Flat.Login.LoginWithSteamCmd.AddSteamAppId(builder, InSteamAppID);
			SF.Flat.Login.LoginWithSteamCmd.AddSteamPlayerId(builder, InSteamPlayerID);
			SF.Flat.Login.LoginWithSteamCmd.AddSteamPlayerName(builder, SteamPlayerNameOffset);
			SF.Flat.Login.LoginWithSteamCmd.AddSteamPlayerToken(builder, SteamPlayerTokenOffset);
			SF.Flat.Login.LoginWithSteamCmd.AddGameId(builder, GameIDOffset);
			var packetOffset = SF.Flat.Login.LoginWithSteamCmd.EndLoginWithSteamCmd(builder);
			result = SendMessage(MessageIDLogin.LoginWithSteamCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  LoginWithSteamCmd( SF.TransactionID InTransactionID, System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )

	}; // public class LoginRPCSendAdapter : RPCAdapter
	public class LoginSvrRPCSendAdapter : RPCAdapter
	{
 


		public  LoginSvrRPCSendAdapter()
		{
 		} // public  LoginSvrRPCSendAdapter()
		public  LoginSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  LoginSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// Cmd: Login with ID/PW request
		public Result  LoginRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InNickName, SF.AccountID InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var NickNameOffset = builder.CreateString(InNickName);
			var AccountIDOffset = builder.CreateAccountID(InAccountID);
			var BannedReasonOffset = builder.CreateString(InBannedReason);
			var GameServerAddressOffset = builder.CreateString(InGameServerAddress);
			SF.Flat.Login.LoginRes.StartLoginRes(builder);
			SF.Flat.Login.LoginRes.AddNickName(builder, NickNameOffset);
			SF.Flat.Login.LoginRes.AddAccountId(builder, AccountIDOffset);
			SF.Flat.Login.LoginRes.AddAuthTicket(builder, InAuthTicket);
			SF.Flat.Login.LoginRes.AddBannedReason(builder, BannedReasonOffset);
			SF.Flat.Login.LoginRes.AddGameServerAddress(builder, GameServerAddressOffset);
			var packetOffset = SF.Flat.Login.LoginRes.EndLoginRes(builder);
			result = SendMessage(MessageIDLogin.LoginRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  LoginRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InNickName, SF.AccountID InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )


		// Cmd: Login with steam login info
		public Result  LoginWithSteamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InNickName, SF.AccountID InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var NickNameOffset = builder.CreateString(InNickName);
			var AccountIDOffset = builder.CreateAccountID(InAccountID);
			var BannedReasonOffset = builder.CreateString(InBannedReason);
			var GameServerAddressOffset = builder.CreateString(InGameServerAddress);
			SF.Flat.Login.LoginWithSteamRes.StartLoginWithSteamRes(builder);
			SF.Flat.Login.LoginWithSteamRes.AddNickName(builder, NickNameOffset);
			SF.Flat.Login.LoginWithSteamRes.AddAccountId(builder, AccountIDOffset);
			SF.Flat.Login.LoginWithSteamRes.AddAuthTicket(builder, InAuthTicket);
			SF.Flat.Login.LoginWithSteamRes.AddBannedReason(builder, BannedReasonOffset);
			SF.Flat.Login.LoginWithSteamRes.AddGameServerAddress(builder, GameServerAddressOffset);
			var packetOffset = SF.Flat.Login.LoginWithSteamRes.EndLoginWithSteamRes(builder);
			result = SendMessage(MessageIDLogin.LoginWithSteamRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  LoginWithSteamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InNickName, SF.AccountID InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )


	}; // public class LoginSvrRPCSendAdapter : RPCAdapter




} // namespace SF.Net
#nullable restore



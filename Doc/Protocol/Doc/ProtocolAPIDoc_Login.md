***
 
 CopyRight (c) 2024 StormForge
 
 Description : Login Message Protocol API Document

***



Login Server Protocol.

namespace SF::Message::Login


# Protocol interface class NetPolicyLogin
## Login Request
Login with ID/PW request

1. Command interface

        Result LoginCmd(const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID)

		- TransactionID: type:TransactionID, 

		- user_id: type:String, Login user id

		- password: type:String, Login password

		- GameID: type:String, GameID/AppID

2. Result interface

C++: Cast message to LoginRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- NickName: type:String, Nickname of the player
		- AccountID: type:AccountID, AccountID
		- AuthTicket: type:AuthTicket, Login ticket
		- BannedReason: type:String, Banned reason if the account is banned
		- GameServerAddress: type:String, Game server network address to connect


## LoginWithSteam Request
Login with steam login info

1. Command interface

        Result LoginWithSteamCmd(const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID)

		- TransactionID: type:TransactionID, 

		- SteamAppID: type:uint64, Steam application id

		- SteamPlayerID: type:uint64, Steam player id

		- SteamPlayerName: type:String, Steam player profile name

		- SteamPlayerToken: type:String, Steam player login token

		- GameID: type:String, GameID/AppID

2. Result interface

C++: Cast message to LoginWithSteamRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- NickName: type:String, Nickname of the player
		- AccountID: type:AccountID, AccountID
		- AuthTicket: type:AuthTicket, Login ticket
		- BannedReason: type:String, Banned reason if the account is banned
		- GameServerAddress: type:String, Game server network address to connect









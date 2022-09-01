***
 
 CopyRight (c) 2022 StormForge
 
 Description : Login Message Protocol API Document

***



Game

namespace SF::Message::Login


# Protocol interface class NetPolicyLogin
## Login Request
Login request

1. Command interface

        Result LoginCmd(const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword)

		- OutTransactionID: TransactionID type. 

		- OutGameID: GameID type. Game ID, Conspiracy will be accepted

		- OutID: String type. UserID

		- OutPassword: String type. User Password

2. Result interface

C++: Cast message to LoginRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutGameServerAddr: NetAddress type. Game server address to connect
		- OutGameServerAddrIPV4: NetAddress type. Game server address to connect
		- OutAccID: AccountID type. AccountID for the player
		- OutTicket: AuthTicket type. Login session Ticket
		- OutLoginEntityUID: uint64 type. Login entity ID. This need to be used when you connect to the game server


## LoginByFacebook Request
Login request with Facebook UID

1. Command interface

        Result LoginByFacebookCmd(const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken)

		- OutTransactionID: TransactionID type. 

		- OutGameID: GameID type. Game ID, Conspiracy will be accepted

		- OutUID: uint64 type. Facebook UID. You can get when you login to facebook

		- OutFaceBookName: String type. Face book name

		- OutEMail: String type. email address of the player

		- OutFacebookToken: String type. Factbook token, reserved

2. Result interface

C++: Cast message to LoginByFacebookRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutGameServerAddr: NetAddress type. Game server address to connect
		- OutGameServerAddrIPV4: NetAddress type. Game server address to connect
		- OutAccID: AccountID type. AccountID for the player
		- OutTicket: AuthTicket type. Login session Ticket
		- OutLoginEntityUID: uint64 type. Login entity ID. This need to be used when you connect to the game server


## LoginBySteam Request
Login request with Facebook UID

1. Command interface

        Result LoginBySteamCmd(const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InSteamSessionId)

		- OutTransactionID: TransactionID type. 

		- OutGameID: GameID type. Game ID, Conspiracy will be accepted

		- OutUID: uint64 type. Steam UID.

		- OutSteamSessionId: String type. Steam login session Id. Used for verification

2. Result interface

C++: Cast message to LoginBySteamRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutGameServerAddr: NetAddress type. Game server address to connect
		- OutGameServerAddrIPV4: NetAddress type. Game server address to connect
		- OutAccID: AccountID type. AccountID for the player
		- OutTicket: AuthTicket type. Login session Ticket
		- OutLoginEntityUID: uint64 type. Login entity ID. This need to be used when you connect to the game server


## CreateRandomUser Request
Login request

1. Command interface

        Result CreateRandomUserCmd(const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone)

		- OutTransactionID: TransactionID type. 

		- OutGameID: GameID type. Game ID, Conspiracy will be accepted

		- OutCellPhone: String type. CellPhone

2. Result interface

C++: Cast message to CreateRandomUserRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutGameServerAddr: NetAddress type. Game server address to connect
		- OutGameServerAddrIPV4: NetAddress type. Game server address to connect
		- OutAccID: AccountID type. AccountID for the player
		- OutTicket: AuthTicket type. Login session Ticket
		- OutLoginEntityUID: uint64 type. Login entity ID. This need to be used when you connect to the game server


## UpdateMyScore Request
Update my score and Get Ranking list

1. Command interface

        Result UpdateMyScoreCmd(const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount)

		- OutTransactionID: TransactionID type. 

		- OutRankingScore: uint64 type. 

		- OutRankingType: RankingType type. 

		- OutCount: uint16 type. Number of ranking list to query after update

2. Result interface

C++: Cast message to UpdateMyScoreRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutRanking: TotalRankingPlayerInformation type. 


## GetRankingList Request
Get Ranking lise

1. Command interface

        Result GetRankingListCmd(const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount)

		- OutTransactionID: TransactionID type. 

		- OutRankingType: RankingType type. 

		- OutBaseRanking: uint8 type. Base ranking to query, 0 based ranking order

		- OutCount: uint8 type. Number of playerinformation to query

2. Result interface

C++: Cast message to GetRankingListRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutRanking: TotalRankingPlayerInformation type. 


## DataTest Request
For network test

1. Command interface

        Result DataTestCmd(const uint64_t &InTransactionID, const Array<uint8_t>& InTestData)

		- OutTransactionID: TransactionID type. 

		- OutTestData: uint8 type. 

2. Result interface

C++: Cast message to DataTestRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutTestData: uint8 type. 


## HeartbeatC2SEvt
Heartbeat

        Result HeartbeatC2SEvt()


## DebugPrintALLRanking Request
Write All!! User Score and Ranking list

1. Command interface

        Result DebugPrintALLRankingCmd(const uint64_t &InTransactionID, const char* InFileName)

		- OutTransactionID: TransactionID type. 

		- OutFileName: String type. 

2. Result interface

C++: Cast message to DebugPrintALLRankingRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 









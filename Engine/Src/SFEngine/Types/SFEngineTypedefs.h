////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "String/SFStringCrc32.h"
#include "String/SFStringCrc64.h"
#include "Math/SF3DMath.h"

////////////////////////////////////////////////////////////////////////////////
//
//	common SF types
//


namespace SF {


	using GameID = StringCrc32;


	// context ID type
	using Context = uint64_t;

	// Authentication ticket
	using AuthTicket = uint64_t;

	using AccountID = uint64_t;

	using PlayerID = uint64_t;

	using FacebookUID = uint64_t;


	// server ID
	using ServerID = uint32_t;




	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Entity Universal unique ID
	//


	union EntityUID;

	// Entity ID faculty, this means group of Entity
	enum class EntityFaculty : uint8_t
	{
		None,				// Faculty undefined
		Server,				// Faculty Server
		Service,			// Faculty Service
		User,				// Faculty User
		Game,				// Faculty Game
		GameInstance,		// Faculty Game Instance
		Party,				// Faculty Party
		MatchInstance,		// Faculty Match Instance
		Manager,			// Faculty Manager Instance
		ChatChannel,
		Max,
	};

	enum class DBClusterType
	{
		Normal,
		Sharding,
	};


	// server cluster ID
	//typedef uint32_t ClusterID;
	enum class ClusterID : uint32_t
	{
		Invalid = 0,
		ClusterManager,
		Monitoring,
		PlayerManager,
		Login,
		Game,
		GameInstanceManager,
		GamePartyManager,
		Ranking,
		ChatChannelManager,
		CharacterData,

		PurchaseValidateGoogle,
		PurchaseValidateIOS,

		Matching_Game_4,
		Matching_Game_8,
		//Matching_Game_10,
		//Matching_Game_12,

		MatchingQueue_Game_4x1,
		MatchingQueue_Game_4x2,
		MatchingQueue_Game_4x3,
		MatchingQueue_Game_4x1S,
		MatchingQueue_Game_4x1W,

		MatchingQueue_Game_8x1,
		MatchingQueue_Game_8x2,
		MatchingQueue_Game_8x3,
		MatchingQueue_Game_8x4,
		MatchingQueue_Game_8x5,
		MatchingQueue_Game_8x6,
		MatchingQueue_Game_8x7,
		MatchingQueue_Game_8x1S,
		MatchingQueue_Game_8x1W,

		Relay
		
	};

	static constexpr uint32_t ClusterID_MatchingQueue_Max = static_cast<uint32_t>(ClusterID::MatchingQueue_Game_8x1W);


	inline ClusterID operator++(ClusterID clusterID)
	{
		switch (clusterID)
		{
		case ClusterID::Matching_Game_8:
			return ClusterID::MatchingQueue_Game_4x1;
		default:
			return static_cast<ClusterID>((INT)clusterID + 1);
		};
	}

	inline ClusterID operator++(ClusterID& clusterID, int)
	{
		ClusterID oldValue = clusterID;
		clusterID = ++clusterID;
		return oldValue;
	}


	// Clustering model
	enum class ClusterType : uint32_t
	{
		Replication,		// Replica with master. master - write, others - read
		FreeReplication,	// Replica without master. plat relationship
		Ring,				// Circular queue cluster
		Shard,				// Sharded. only shares status
	};

	// Cluster Member ship mode
	enum class ClusterMembership : uint32_t
	{
		Master,
		Slave,
		//StatusWatcher,	// Service status watcher
		//Watcher,			// Service data watcher, Only effect with replica model
	};


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Entity unique ID in local
	//
	union EntityID
	{
		enum {
			MAX_IDBIT = 24,
		};


		struct {
			uint32_t			EntityLID : 24;	// Local entity ID
			uint32_t			FacultyID : 8;	// Local faculty ID
			uint32_t : 0;		// Local entity ID
		} Components;
		uint32_t ID;


		inline EntityID();
		inline EntityID(const EntityUID& entityUID);
		inline EntityID(const EntityID& entityID);
#if !defined(SWIG)
		inline EntityID(EntityFaculty facultyID, uint32_t entityLID);
#endif
		inline EntityID(uint32_t uiID);

		uint32_t GetEntityLID() const { return Components.EntityLID; }
		uint32_t GetFacultyID() const { return Components.FacultyID; }

		inline EntityID& operator = (const EntityID& entityID);

		//inline bool operator == ( const EntityID& src ) const;
		//inline bool operator != ( const EntityID& src ) const;
#if !defined(SWIG)
		inline operator uint32_t() const;
#endif
	};



	union EntityUID
	{
		struct {
			EntityID	EntID;		// Local entity ID
			ServerID	SvrID;		// Server ID
		} Components;
		uint64_t UID;

		inline EntityUID();
		inline EntityUID(const EntityUID& entityUID);
		inline EntityUID(ServerID serverID, uint32_t entityID);
		inline EntityUID(const Context& context);

		EntityID GetEntityID() const { return Components.EntID; }
		ServerID GetServerID() const { return Components.SvrID; }

		inline EntityUID& operator = (const EntityUID& entityUID);

		inline bool operator == (const EntityUID& src) const;
		inline bool operator != (const EntityUID& src) const;

#if !defined(SWIG)
		inline operator Context() const;
#endif
	};

	using GameInsUID = EntityUID;
	using PartyUID = EntityUID;
	using PlayerUID = EntityUID;




//#pragma pack(push)
#pragma pack(push,4)

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Transaction ID
	//

	union TransactionID
	{
		struct {
			EntityID	EntID;
			uint32_t		TransID;
		} Components;
		uint64_t ID;

		inline TransactionID();
		inline TransactionID(const TransactionID& transID);
		inline TransactionID(EntityID entityID, uint32_t transID);
		inline TransactionID(Context context);

		inline bool IsValid() const;

		EntityID GetEntityID() const { return Components.EntID; }
		uint32_t GetTransactionIndex() const { return Components.TransID; }

		inline TransactionID& operator = (const TransactionID& transID);

		inline operator uint64_t() const { return ID; }

		inline bool operator != (const TransactionID& src) const;
		inline bool operator == (const TransactionID& src) const;

	};




	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Server Route context
	//

	union RouteContext
	{
		struct {
			EntityUID	From;
			EntityUID	To;
		} Components;
		uint64_t ContextValue[2];

		inline RouteContext();
		inline RouteContext(const RouteContext& routeContext);
		inline RouteContext(EntityUID InFromID, EntityUID InToID);
		inline RouteContext(int initValue);

		EntityUID GetFrom() const { return Components.From; }
		EntityUID GetTo() const { return Components.To; }

		inline RouteContext& operator = (const RouteContext& src);

		inline bool operator == (const RouteContext& routeContext) const;

		// Get swaped context( From <==> To )
		inline RouteContext GetSwaped() const;

	};






	// Ranking type
	enum class RankingType : uint8_t
	{
		//Friend,
		World,
	};

	// Notification message
	enum class NotificationType : uint16_t
	{
		None,				// Not used
		MessageNotify,
		FriendRequest,
		GiftStamina,
	};


	// Player information
	struct PlayerInformation
	{
		enum {
			MAX_NAME = 64,
		};

		AccountID		PlayerID = 0;
		FacebookUID		FBUID = 0;
		char			NickName[MAX_NAME] = {0,};
		uint64_t			LastActiveTime = 0;
		uint32_t			Level = 0;
		uint32_t			IsPlayingGame = 0;

		PlayerInformation() {}
		PlayerInformation(const PlayerInformation& src);
		PlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime);
		Result InitPlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime);
		PlayerInformation& operator = (const PlayerInformation& src);
		bool operator == (const PlayerInformation& src) const;
	};


	struct RankingPlayerInformation : public PlayerInformation
	{
		uint32_t			WeeklyWin;
		uint32_t			WeeklyLose;

		RankingPlayerInformation();
		RankingPlayerInformation(const RankingPlayerInformation& src);
		RankingPlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime);
		RankingPlayerInformation& operator = (const RankingPlayerInformation& src);
		bool operator == (const RankingPlayerInformation& src) const;
	};



	struct FriendInformation : public RankingPlayerInformation
	{
		uint64_t			LastStaminaSent;

		FriendInformation();
		FriendInformation(const FriendInformation& src);
		FriendInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime, uint64_t LastStaminaSent);
		FriendInformation& operator = (const FriendInformation& src);
		bool operator == (const FriendInformation& src) const;
	};

	

	struct TotalRankingPlayerInformation
	{
		enum {
			MAX_NAME = 64,
		};

		uint32_t			RankingID;
		uint32_t			Ranking;
		AccountID			PlayerID;
		FacebookUID			FBUID;
		char				NickName[MAX_NAME];
		uint32_t			Level;
		uint32_t			ScoreLow;
		uint32_t			ScoreHigh;

		uint64_t GetScore() const
		{
			return ((uint64_t)ScoreHigh << 32) | (uint64_t)ScoreLow;
		}

		TotalRankingPlayerInformation();
		TotalRankingPlayerInformation(const TotalRankingPlayerInformation& src);
		TotalRankingPlayerInformation(uint32_t rankingID, uint32_t ranking, AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint scoreLow, uint scoreHigh);
		TotalRankingPlayerInformation& operator = (const TotalRankingPlayerInformation& src);

		void SetLongScore(uint64_t score)
		{
			ScoreLow = (uint32_t)score;
			ScoreHigh = (uint32_t)(score >> 32);
		}

		bool operator == (const TotalRankingPlayerInformation& src) const;
	};



	////////////////////////////////////////////////////////////////////////////
	// TODO : temp types
	typedef uint64_t AccountID;
	typedef uint64_t AuthTicket;


	// Player Role
	enum class PlayerRole : uint8_t
	{
		None,
		Villager,
		Werewolf,
		Seer,

		Medium,
		//Possessed,
		//Bodyguard,
		//Owlman,
		//Freemason,
		//Werehamster,
		//Mythomaniac,
		//Hunter,
		//Wizard,
		//Sorceress,
		//Prostitute,
		//Chosen,
		//AngelOfVillagers,
		//AngelOfWolves,
		//Paladin,
		//Sorcerer,
		//Condemned,
		//Redeemed,
		//Devil,
	};


	// Game flow state for Lupus in Tabula
	enum class GameStateID : uint8_t
	{
		None,
		FreeDebate,
		//FirstNightVote,
		//SecondNightVote,
		NightVote,
		//Mythomaniac,
		MorningDebate,
		VoteForSuspects,
		DefenceOfSuspects,
		VoteForHanging,
		End,
		Max,
	};

	// Game Winner
	enum class GameWinner : uint8_t
	{
		None,
		Werewolf,
		Villager,
		WereHamster,
		Max
	};

	// 
	enum class PlayerKilledReason : uint8_t
	{
		Unknown,
		BlockedByBodyguard,
		ByWerewolf,
		ByHanging,
	};

	// 
	enum class PlayerRevealedReason : uint8_t
	{
		None,
		Werewolf,
		SeersChoice,
		Medium,
		GameEnd,
	};

	enum class ChatType : uint8_t
	{
		Normal,         // Normal chat message
		Whisper,        // Whisper
		Info,           // Information
		System,         // System
		Role,           // Role chat in game
	};

	// Game log type
	enum class GameLogType : uint16_t
	{
		ChatMessage,            // Chatting message
		GameStateChange,        // Role chat in game
		Vote,                   // Vote
		VoteResult,             // Vote result
		PlayerKilled,           // Player killed
		GameEnd,                // Game End
	};

	enum class GameVoteType : uint16_t
	{
		Suspect,
		Hanging,
		Hunting,
		Max
	};



	// Unique ID in single machine
	union LocalUID
	{
		struct {
			uint32_t		Time;
			uint32_t		ID;
		};
		uint64_t			UID;

		inline LocalUID();
		inline LocalUID(const LocalUID& src);
		inline LocalUID(uint32_t time, uint32_t id);
		inline LocalUID(uint64_t initValue);

		inline LocalUID& operator = (const LocalUID& src);

		inline bool operator == (const LocalUID& op) const;
		inline bool operator != (const LocalUID& op) const;
#if !defined(SWIG)
		inline operator uint64_t () const;
#endif
	};


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Matching queue player information
	//
	struct MatchingQueueTicket
	{
		EntityUID		QueueUID;
		LocalUID		QueueItemID;

		MatchingQueueTicket();
		inline MatchingQueueTicket(const MatchingQueueTicket& src);
		inline MatchingQueueTicket(EntityUID queueUID, LocalUID itemID);
		inline MatchingQueueTicket(int initValue);

		inline MatchingQueueTicket& operator = (const MatchingQueueTicket& src);

		inline bool operator == (const MatchingQueueTicket& op) const;
		inline bool operator != (const MatchingQueueTicket& op) const;

		operator uint128_t() const { uint128_t val = { QueueUID, QueueItemID }; return val; }
	};



#pragma pack(push,4)

	// Relay player information 
	struct RelayPlayerInfo
	{
		uint64_t EndpointID;	// Endpoint id. unique in relay instance
		PlayerID RelayPlayerID; // PlayerID

		bool operator == (const RelayPlayerInfo& op1) const { return EndpointID == op1.EndpointID && RelayPlayerID == op1.RelayPlayerID; }
		bool operator != (const RelayPlayerInfo& op1) const { return EndpointID != op1.EndpointID || RelayPlayerID != op1.RelayPlayerID; }
	};

#pragma pack(pop)





	using PartyID = EntityID;

	// Game Instance
	using GameInsID = EntityID;

};


#include "SFEngineTypedefs.inl"





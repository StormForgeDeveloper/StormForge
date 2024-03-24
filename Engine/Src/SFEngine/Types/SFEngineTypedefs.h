////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Util/SFGuid.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "Math/SF3DMath.h"

////////////////////////////////////////////////////////////////////////////////
//
//	common SF types
//


namespace SF {

#pragma pack(push, 4)

	using GameID = StringCrc32;


	// context ID type
	using Context = uint64_t;

	// Authentication ticket
	using AuthTicket = uint64_t;

    using LogEntryID = uint32_t;

	using FacebookUID = uint64_t;

    using UGCID = uint64_t;

	// server ID
	using ServerID = uint32_t;




#pragma pack(push, 1)
    struct AchievementStat
    {
        uint32_t AchievementStatId;
        int32_t StatValue;
    };

    SF_FORCEINLINE bool operator == (const AchievementStat& op1, const AchievementStat& op2)
    {
        return op1.AchievementStatId == op2.AchievementStatId
            && op1.StatValue == op2.StatValue;
    }



#pragma pack(pop)

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Entity Universal unique ID
	//


	// Entity ID faculty, this means group of Entity
    // We might not need this anymore, just leaving as ph for legacy code
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
		ServiceInstance,		// Faculty generic service Instance
		Max,
	};

	enum class DBClusterType
	{
		Normal,
		Sharding,
	};


#define _SFCLUSTERID(x) x

	// server cluster ID
	enum class ClusterID : uint32_t
	{
        #include "SFClusterIDDef.inl"
	};

#undef _SFCLUSTERID

    // deprecated
    static constexpr uint32_t ClusterID_MatchingQueue_Max = static_cast<uint32_t>(ClusterID::Max);

	const char* ToString(ClusterID clusterId);
	StringCrc64 ToStringCrc64(ClusterID clusterId);

	inline ClusterID operator++(ClusterID clusterID)
	{
		return static_cast<ClusterID>((INT)clusterID + 1);
	}

	inline ClusterID operator++(ClusterID& clusterID, int)
	{
		ClusterID oldValue = clusterID;
		clusterID = ++clusterID;
		return oldValue;
	}

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
			uint32_t			EntityLID : 16;	// Local entity ID
			uint32_t			FacultyID : 4;	// Local faculty ID
            uint32_t			ServerID : 12;	// Server ID
			uint32_t : 0;
		} Components;
		uint32_t ID;


		inline EntityID();
		inline EntityID(const EntityID& entityID);
		inline EntityID(ServerID serverId, EntityFaculty facultyID, uint32_t entityLID);
		inline EntityID(uint32_t uiID);

		uint32_t GetServerID() const { return Components.ServerID; }
        uint32_t GetEntityLID() const { return Components.EntityLID; }
		uint32_t GetFacultyID() const { return Components.FacultyID; }

        bool IsValid() const { return ID != 0; }
		inline EntityID& operator = (const EntityID& entityID);

		//inline bool operator == ( const EntityID& src ) const;
		//inline bool operator != ( const EntityID& src ) const;
#if !defined(SWIG)
		inline operator uint32_t() const;
#endif
	};

    // We now use same type. will be merged gradually
    using EntityUID = EntityID;


	using GameInsUID = EntityUID;
    using GameInstanceUID = EntityUID;
	using PartyUID = EntityUID;
	using PlayerUID = EntityUID;





	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Transaction ID
	//

	union TransactionID
	{
		struct TransactionIDComponent {
            uint32_t	TransID = 0;
            EntityID	EntityId;

			TransactionIDComponent() {}
			TransactionIDComponent(EntityID InEntID, uint32_t InTransID)
				: EntityId(InEntID)
				, TransID(InTransID)
			{}
			TransactionIDComponent(const TransactionIDComponent& src)
				: EntityId(src.EntityId)
				, TransID(src.TransID)
			{}

		} Components{};
		uint64_t ID;

		inline TransactionID();
		inline TransactionID(const TransactionID& transID);
		inline TransactionID(EntityID entityID, uint32_t transID);
		inline TransactionID(Context context);

		inline bool IsValid() const;

		EntityID GetEntityID() const { return Components.EntityId; }
		uint32_t GetTransactionIndex() const { return Components.TransID; }

		inline TransactionID& operator = (const TransactionID& transID);

		inline operator uint64_t() const { return ID; }

		inline bool operator != (const TransactionID& src) const;
		inline bool operator == (const TransactionID& src) const;

	};




	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////
	////	Server Route context
	////

	//union RouteContext
	//{
	//	struct RouteContextComponents {
	//		EntityUID	From;
	//		EntityUID	To;

	//		RouteContextComponents() {}
	//		RouteContextComponents(EntityUID InFrom, EntityUID InTo)
	//			: From(InFrom)
	//			, To(InTo)
	//		{}
	//		RouteContextComponents(const RouteContextComponents& src)
	//			: From(src.From)
	//			, To(src.To)
	//		{}

	//	} Components;
	//	uint64_t ContextValue[2];

	//	SF_FORCEINLINE RouteContext()
	//		: Components()
	//	{}

	//	SF_FORCEINLINE RouteContext(const RouteContext& src)
	//		: Components(src.Components)
	//	{}
	//	SF_FORCEINLINE RouteContext(EntityUID InFromID, EntityUID InToID)
	//		: Components(InFromID, InToID)
	//	{}


	//	EntityUID GetFrom() const { return Components.From; }
	//	EntityUID GetTo() const { return Components.To; }

	//	inline RouteContext& operator = (const RouteContext& src);

	//	inline bool operator == (const RouteContext& routeContext) const;

	//	// Get swaped context( From <==> To )
	//	inline RouteContext GetSwaped() const;

	//};

	using AuthTicket = uint64_t;
	using PartyID = EntityID;
	using GameInsID = EntityID;
	using GameInsUID = EntityUID;



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



    struct AccountID : public Guid
    {
        AccountID()
        {
        }

        AccountID(const AccountID& other)
            : Guid(other)
        {
        }

        AccountID(const Guid& other)
            : Guid(other)
        {
        }

        AccountID(const uint8_t* bytes)
            : Guid(bytes)
        {
        }

        AccountID(uint64_t low, uint64_t high)
            : Guid(low, high)
        {
        }

    };

    using PlayerID = AccountID;

    typedef Guid CharacterID;


    enum class EPlatform : uint8_t
    {
        BR,         // Braves player Id
        Steam,      // Steam player Id
        Facebook,   // Facebook
    };

#pragma pack(push, 1)
    struct PlayerPlatformID
    {
        AccountID PlayerId{};
        EPlatform Platform{};

        PlayerPlatformID() = default;
        PlayerPlatformID(EPlatform platform, AccountID playerId)
            : Platform(platform)
            , PlayerId(playerId)
        {}
        PlayerPlatformID(const char* strId);
    };
#pragma pack(pop)

    SF_FORCEINLINE bool operator == (const PlayerPlatformID& op1, const PlayerPlatformID& op2)
    {
        return op1.Platform == op2.Platform
            && op1.PlayerId == op2.PlayerId;
    }


	// Player information
	struct PlayerInformation
	{
		enum {
			MAX_NAME = 63, // 64 -1 for PlayerPlatformID alignment
		};

        AccountID		PlayerID = {};
        PlayerPlatformID PlayerPlatformId{};
		char			NickName[MAX_NAME] = {0,};
		uint64_t			LastActiveTime = 0;
		uint32_t			Level = 0;
		uint32_t			IsPlayingGame = 0;

		PlayerInformation() {}
		PlayerInformation(const PlayerInformation& src);
		PlayerInformation(AccountID playerID, const PlayerPlatformID& playerPlatformId, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime);
		Result InitPlayerInformation(AccountID playerID, const PlayerPlatformID& playerPlatformId, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime);
		PlayerInformation& operator = (const PlayerInformation& src);
		bool operator == (const PlayerInformation& src) const;
	};

    // deprecated
	struct RankingPlayerInformation : public PlayerInformation
	{
		uint32_t			WeeklyWin;
		uint32_t			WeeklyLose;

		RankingPlayerInformation();
		RankingPlayerInformation(const RankingPlayerInformation& src);
		RankingPlayerInformation(AccountID playerID, const PlayerPlatformID& playerPlatformId, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime);
		RankingPlayerInformation& operator = (const RankingPlayerInformation& src);
		bool operator == (const RankingPlayerInformation& src) const;
	};


    // deprecated
	struct FriendInformation : public RankingPlayerInformation
	{
		uint64_t			LastStaminaSent;

		FriendInformation();
		FriendInformation(const FriendInformation& src);
		FriendInformation(AccountID playerID, const PlayerPlatformID& playerPlatformId, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime, uint64_t LastStaminaSent);
		FriendInformation& operator = (const FriendInformation& src);
		bool operator == (const FriendInformation& src) const;
	};

	
    // deprecated
	struct TotalRankingPlayerInformation
	{
		enum {
			MAX_NAME = 64,
		};

		uint32_t			RankingID;
		uint32_t			Ranking;
		AccountID			PlayerID;
		PlayerPlatformID	PlayerPlatformId;
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
		TotalRankingPlayerInformation(uint32_t rankingID, uint32_t ranking, AccountID playerID, const PlayerPlatformID& playerPlatformId, const char* nickName, uint level, uint scoreLow, uint scoreHigh);
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


	// Game chat message type 
	enum class ChatMessageType : uint8_t
	{
		Zone,
		ZoneGlobal,
		Whisper,
		Channel,
		System,
		Max
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

        inline bool IsValid() const { return UID != 0; }

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

        inline bool IsValid() const { return QueueUID.IsValid() && QueueItemID.IsValid(); }

		inline bool operator == (const MatchingQueueTicket& op) const;
		inline bool operator != (const MatchingQueueTicket& op) const;

		operator uint128_t() const { uint128_t val = { QueueUID, QueueItemID }; return val; }
	};



	// Relay player information 
	struct RelayPlayerInfo
	{
		uint64_t EndpointID;	// Endpoint id. unique in relay instance
		PlayerID RelayPlayerID; // PlayerID

		bool operator == (const RelayPlayerInfo& op1) const { return EndpointID == op1.EndpointID && RelayPlayerID == op1.RelayPlayerID; }
		bool operator != (const RelayPlayerInfo& op1) const { return EndpointID != op1.EndpointID || RelayPlayerID != op1.RelayPlayerID; }
	};

#pragma pack(pop)

};

template <> class std::hash<SF::AccountID>
{
public:
    size_t operator()(const SF::AccountID& guid) const
    {
        return guid.GetHash();
    }
};


#include "SFEngineTypedefs.inl"





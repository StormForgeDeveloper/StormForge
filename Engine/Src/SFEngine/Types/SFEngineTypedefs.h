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
#include "Util/SFString.h"
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
		Generic,			// Faculty Generic
		Server,				// Faculty Server
	};

    enum class EAccountRole : uint8_t
    {
        Player,
        Tester,
        Dev
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

	inline ClusterID& operator++(ClusterID& clusterID)
	{
        clusterID = static_cast<ClusterID>((INT)clusterID + 1);
        return clusterID;
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
	union EntityUID
	{
        static const EntityUID Invalid;

		enum {
			MAX_IDBIT = 24,
		};

		struct {
			uint32_t			EntityLID : 16;	// Local entity ID
			uint32_t			FacultyID : 1;	// Local faculty ID
            uint32_t			ServerID : 15;	// Server ID
			uint32_t : 0;
		} Components;
		uint32_t ID;


		EntityUID()
            :ID(0)
        {
        }

		EntityUID(const EntityUID& entityID)
            : ID(entityID.ID)
        {
        }

		EntityUID(ServerID serverId, EntityFaculty facultyID, uint32_t entityLID)
        {
            Components.ServerID = serverId;
            Components.FacultyID = (uint)facultyID;
            Components.EntityLID = entityLID & 0xFFFF; // to avoid wconversion warning
        }

		EntityUID(uint32_t uiID)
            :ID(uiID)
        {
        }

		uint32_t GetServerID() const { return Components.ServerID; }
        uint32_t GetEntityLID() const { return Components.EntityLID; }
		uint32_t GetFacultyID() const { return Components.FacultyID; }
        EntityUID GetServerEntityUID() const
        {
            return EntityUID(Components.ServerID, EntityFaculty::Server, 0);
        }

        bool IsValid() const { return ID != 0; }
		EntityUID& operator = (const EntityUID& entityID)
        {
            ID = entityID.ID;

            return *this;
        }

        inline bool operator > (const EntityUID& src) const { return ID > src.ID; }
        inline bool operator >= (const EntityUID& src) const { return ID >= src.ID; }
        inline bool operator < (const EntityUID& src) const { return ID < src.ID; }
        inline bool operator <= (const EntityUID& src) const { return ID <= src.ID; }

        inline bool operator == (const EntityUID& src) const { return ID == src.ID; }
		inline bool operator != ( const EntityUID& src ) const { return ID != src.ID; }

		explicit operator uint32_t() const { return (uint32_t)ID; }
	};

    // We now use same type. will be merged gradually
    using EntityID = EntityUID;


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
            EntityUID	EntityUid;

			TransactionIDComponent() {}
			TransactionIDComponent(EntityUID InEntID, uint32_t InTransID)
				: EntityUid(InEntID)
				, TransID(InTransID)
			{}
			TransactionIDComponent(const TransactionIDComponent& src)
				: EntityUid(src.EntityUid)
				, TransID(src.TransID)
			{}

		} Components{};
		uint64_t ID;

		TransactionID()
        {
        }

		TransactionID(const TransactionID& transID)
            : Components(transID.Components)
        {
        }

		TransactionID(EntityUID entityID, uint32_t transID)
            : Components(entityID, transID)
        {
        }


		TransactionID(Context context)
        {
            ID = context;
        }


		bool IsValid() const
        {
            TransactionID trans;
            return trans.ID != ID;
        }

        EntityUID GetEntityUID() const { return Components.EntityUid; }
		uint32_t GetTransactionIndex() const { return Components.TransID; }

		TransactionID& operator = (const TransactionID& transID)
        {
            ID = transID.ID;

            return *this;
        }

		operator uint64_t() const { return ID; }

		bool operator != (const TransactionID& src) const
        {
            return ID != src.ID;
        }

        bool operator == (const TransactionID& src) const
        {
            return ID == src.ID;
        }

	};



	using AuthTicket = uint64_t;
	using PartyID = EntityUID;
	using GameInsID = EntityUID;
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

        bool TryParse(const char* str);
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

    // generit attribute key and string value pair
    struct AttributeString
    {
        std::string Name;
        std::string Value;
    };

    // UGC contnet information
    struct UGCContentInfo
    {
        Guid UGCContentId;
        String Category;
        String DataPath;
        int64_t DataId;
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

    // UGC item info
    struct SUGCItemInfo
    {
        static constexpr int MaximumEffect = 2;

        uint32_t ItemTableId{};
        uint32_t UTCExpire{};            // UTC expire time stamp(sec)
        uint32_t EffectIds[MaximumEffect]{};

        bool operator == (const SUGCItemInfo& op) const {
            return ItemTableId == op.ItemTableId
                && UTCExpire == op.UTCExpire
                && EffectIds[0] == op.EffectIds[0]
                && EffectIds[1] == op.EffectIds[1];
        }
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

		operator uint128_t() const { uint128_t val = { (uint64_t)QueueUID.ID, QueueItemID }; return val; }
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


template <>
struct std::formatter<SF::ClusterID>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::ClusterID& value, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{}", ToString(value));
    }
};

template <>
struct std::formatter<SF::Guid>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::Guid& value, FormatContext& ctx) const {
        char buffer[37];
        buffer[36] = 0;
        value.ToString(buffer);
        return std::format_to(ctx.out(), "{}", buffer);
    }
};

template <>
struct std::formatter<SF::AccountID>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::AccountID& value, FormatContext& ctx) const {
        char buffer[37];
        buffer[36] = 0;
        value.ToString(buffer);
        return std::format_to(ctx.out(), "{}", buffer);
    }
};

template <>
struct std::formatter<SF::EntityUID>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::EntityUID& value, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{0:08X}", value.ID);
    }
};

template <>
struct std::formatter<SF::TransactionID>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::TransactionID& value, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{0:016X}", value.ID);
    }
};

template <>
struct std::formatter<SF::EPlatform>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::EPlatform& value, FormatContext& ctx) const {
        static const char* Names[] =
        {
            "BR",         // Braves player Id
            "Steam",      // Steam player Id
            "Facebook"   // Facebook
        };
        constexpr int MaxNames = sizeof(Names) / sizeof(Names[0]) - 1;

        return std::format_to(ctx.out(), "{}", Names[std::clamp<int>((int)value, 0, MaxNames)]);
    }
};

template <>
struct std::formatter<SF::PlayerPlatformID>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::PlayerPlatformID& value, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", value.Platform, value.PlayerId);
    }
};

template <>
struct std::formatter<SF::PlayerInformation>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::PlayerInformation& value, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "({}, {}, {}, {})", value.PlayerID, value.PlayerPlatformId, value.NickName, value.LastActiveTime);
    }
};



#include "SFEngineTypedefs.inl"





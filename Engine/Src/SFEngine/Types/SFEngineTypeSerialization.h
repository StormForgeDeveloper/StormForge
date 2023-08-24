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
#include "Types/SFEngineTypedefs.h"
#include "Math/SF3DMath.h"
#include "Net/SFNetDef.h"
#include "Stream/SFStream.h"

////////////////////////////////////////////////////////////////////////////////
//
//	
//


namespace SF {

	inline size_t SerializedSizeOf(const Net::PeerInfo& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, Net::PeerInfo& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const Net::PeerInfo& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const TransactionID& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, TransactionID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TransactionID& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const EntityUID& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, EntityUID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const EntityUID& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const RouteContext& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, RouteContext& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RouteContext& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const RankingType& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, RankingType& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RankingType& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const NotificationType& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, NotificationType& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const NotificationType& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const PlayerInformation& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, PlayerInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const PlayerInformation& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const RankingPlayerInformation& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, RankingPlayerInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RankingPlayerInformation& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const FriendInformation& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, FriendInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const FriendInformation& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const TotalRankingPlayerInformation& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, TotalRankingPlayerInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TotalRankingPlayerInformation& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const MatchingQueueTicket& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, MatchingQueueTicket& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const MatchingQueueTicket& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const ClusterID& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, ClusterID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const ClusterID& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const RelayPlayerInfo& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, RelayPlayerInfo& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RelayPlayerInfo& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const MessageID& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, MessageID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const MessageID& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const Net::ConnectionState& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, Net::ConnectionState& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const Net::ConnectionState& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const LocalUID& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, LocalUID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const LocalUID& data) { return output.Write(&data, sizeof(data)); }

    static_assert(sizeof(PlayerPlatformID) == 9, "Size mismatch!");
    inline size_t SerializedSizeOf(const PlayerPlatformID& Value) { return sizeof(Value); }
    inline Result operator >> (IInputStream& input, PlayerPlatformID& data) { return input.Read(&data, sizeof(data)); }
    inline Result operator << (IOutputStream& output, const PlayerPlatformID& data) { return output.Write(&data, sizeof(data)); }

    static_assert(sizeof(AchievementStat) == 8, "Size mismatch!");
    inline size_t SerializedSizeOf(const AchievementStat& Value) { return sizeof(Value); }
    inline Result operator >> (IInputStream& input, AchievementStat& data) { return input.Read(&data, sizeof(data)); }
    inline Result operator << (IOutputStream& output, const AchievementStat& data) { return output.Write(&data, sizeof(data)); }

};







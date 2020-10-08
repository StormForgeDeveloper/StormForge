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

	inline Result operator >> (IInputStream& input, Net::PeerInfo& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const Net::PeerInfo& data) { return output.Write(&data, sizeof(data)); }


	inline Result operator >> (IInputStream& input, TransactionID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TransactionID& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, EntityUID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const EntityUID& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, RouteContext& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RouteContext& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, RankingType& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RankingType& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, NotificationType& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const NotificationType& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, PlayerInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const PlayerInformation& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, RankingPlayerInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RankingPlayerInformation& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, FriendInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const FriendInformation& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, TotalRankingPlayerInformation& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TotalRankingPlayerInformation& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, MatchingQueueTicket& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const MatchingQueueTicket& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, ClusterMembership& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const ClusterMembership& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, ClusterType& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const ClusterType& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, ClusterID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const ClusterID& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, RelayPlayerInfo& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const RelayPlayerInfo& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, Message::MessageID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const Message::MessageID& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, Net::ConnectionState& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const Net::ConnectionState& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, LocalUID& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const LocalUID& data) { return output.Write(&data, sizeof(data)); }

};







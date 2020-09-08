////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Enumerator helper
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFEnum.h"
#include "String/SFStringCrc32.h"

#include <libxml/parser.h>
#include <libxml/tree.h>



namespace SF
{





	const char* Enum<DBClusterType>::GetName() const
	{
		return "DBClusterType";
	}

	static constexpr const char* __DBClusterType_NameList[] =
	{
		"Normal",
		"Sharding",
	};

	static constexpr StringCrc64 __DBClusterType_NameCrcList[] =
	{
		"Normal",
		"Sharding",
	};


	size_t Enum<DBClusterType>::GetNumberOfValues() const
	{
		return countof(__DBClusterType_NameList);
	}

	const char *const* Enum<DBClusterType>::GetValueNames() const
	{
		return __DBClusterType_NameList;
	}

	const char* Enum<DBClusterType>::GetValueName(DBClusterType value) const
	{

		return __DBClusterType_NameList[(int)value];
	}


	StringCrc64 Enum<DBClusterType>::GetValueNameCrc(DBClusterType value) const
	{
		return __DBClusterType_NameCrcList[(int)value];
	}

	DBClusterType Enum<DBClusterType>::GetValue(const char* valueName) const
	{
		StringCrc64 valueNameCrc = valueName;
		return GetValue(valueNameCrc);
	}

	DBClusterType Enum<DBClusterType>::GetValue(StringCrc64 valueName) const
	{
		StringCrc64 valueNameCrc = valueName;
		for (unsigned iEnum = 0; iEnum < countof(__DBClusterType_NameList); iEnum++)
		{
			if (__DBClusterType_NameCrcList[iEnum] == valueNameCrc)
				return (DBClusterType)iEnum;
		}

		return (DBClusterType)(0);
	}

	template<> class Enum<DBClusterType>;




	const char* Enum<ClusterID>::GetName() const
	{
		return "ClusterID";
	}


#define __CLUSTERID_NAMES__ \
	"Invalid",\
	"ClusterManager",\
	"Monitoring",\
	"PlayerManager",\
	"Login",\
	"Game",\
	"GameInstanceManager",\
	"GamePartyManager",\
	"Ranking",\
	"PurchaseValidateGoogle",\
	"PurchaseValidateIOS",\
	"Matching_Game_4",\
	"Matching_Game_8",\
	"MatchingQueue_Game_4x1",\
	"MatchingQueue_Game_4x2",\
	"MatchingQueue_Game_4x3",\
	"MatchingQueue_Game_4x1S",\
	"MatchingQueue_Game_4x1W",\
	"MatchingQueue_Game_8x1",\
	"MatchingQueue_Game_8x2",\
	"MatchingQueue_Game_8x3",\
	"MatchingQueue_Game_8x4",\
	"MatchingQueue_Game_8x5",\
	"MatchingQueue_Game_8x6",\
	"MatchingQueue_Game_8x7",\
	"MatchingQueue_Game_8x1S",\
	"MatchingQueue_Game_8x1W",\
	"Max",\



	static constexpr const char* __ClusterID_NameList[] =
	{
		__CLUSTERID_NAMES__
	};

	static constexpr StringCrc64 __ClusterID_NameCrcList[] =
	{
		__CLUSTERID_NAMES__
	};


	size_t Enum<ClusterID>::GetNumberOfValues() const
	{
		return countof(__ClusterID_NameList);
	}

	const char *const* Enum<ClusterID>::GetValueNames() const
	{
		return __ClusterID_NameList;
	}

	const char* Enum<ClusterID>::GetValueName(ClusterID value) const
	{
		return __ClusterID_NameList[(int)value];
	}


	StringCrc64 Enum<ClusterID>::GetValueNameCrc(ClusterID value) const
	{
		return __ClusterID_NameCrcList[(int)value];
	}

	ClusterID Enum<ClusterID>::GetValue(const char* valueName) const
	{
		StringCrc64 valueNameCrc = valueName;
		return GetValue(valueNameCrc);
	}

	ClusterID Enum<ClusterID>::GetValue(StringCrc64 valueName) const
	{
		StringCrc64 valueNameCrc = valueName;
		for (unsigned iEnum = 0; iEnum < countof(__ClusterID_NameList); iEnum++)
		{
			if (__ClusterID_NameCrcList[iEnum] == valueNameCrc)
				return (ClusterID)iEnum;
		}

		return (ClusterID)(0);
	}

	template<> class Enum<ClusterID>;


}



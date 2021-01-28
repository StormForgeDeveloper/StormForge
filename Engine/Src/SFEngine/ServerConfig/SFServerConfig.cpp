////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server Config
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFServerConfig.h"
#include "String/SFStringCrc32.h"



namespace SF
{
	namespace ServerConfig
	{

		const DBCluster* ServerService::FindDBCluster(const char* serverName) const
		{
			for (auto& itDB : DBClusters)
			{
				if (itDB->ClusterName == serverName)
					return itDB;
			}

			return nullptr;
		}

		const DBInstance* ServerService::FindDBInstance(const char* instanceName) const
		{
			for (auto& itItem : DBInstances)
			{
				if (itItem->InstanceName == instanceName)
					return itItem;
			}
			return nullptr;
		}

		DBInstance::DBInstance(IHeap& heap)
			: InstanceName(heap)
			, ConnectionString(heap)
			, UserID(heap)
			, Password(heap)
		{
			if (InstanceName == "account00")
			{
				assert(false);
			}
		}

	}



}



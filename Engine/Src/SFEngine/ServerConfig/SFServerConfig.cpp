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


	void ServerConfig::GameCluster::SetGameClusterID(const char* gameID)
	{
		GameClusterIDName = gameID;
		GameClusterID = Service::StringDB->AddNGetString32(gameID);
	}

	void ServerConfig::GameCluster::SetGameClusterID(GameID gameID)
	{
		GameClusterIDName = Service::StringDB->GetString(gameID);
		GameClusterID = gameID;
	}


	const ServerConfig::DBCluster* ServerConfig::GameCluster::FindDBCluster(const char* serverName) const
	{
		for (auto& itDB : DBClusters)
		{
			if (itDB->ClusterName == serverName)
				return itDB;
		}

		return nullptr;
	}

	const ServerConfig::GenericServer* ServerConfig::GameCluster::FindGenericServer(const char* serverName) const
	{
		for (auto& itServer : ModuleServers)
		{
			if (itServer->Name == serverName)
				return itServer;
		}
		for (auto& itServer : GameServers)
		{
			if (itServer->Name == serverName)
				return itServer;
		}
		for (auto& itServer : GameInstanceServers)
		{
			if (itServer->Name == serverName)
				return itServer;
		}

		return nullptr;
	}

	ServerConfig::DBInstance::DBInstance(IHeap& heap)
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



	ServerConfig::ServerConfig()
		: m_Heap(GetSystemHeap())
		, m_DBInstances(m_Heap)
		, m_DBClusters(m_Heap)
		, m_Servers(m_Heap)
		, m_GameClusters(m_Heap)
	{
	}

	ServerConfig::ServerConfig(IHeap& heap)
		: m_Heap(heap)
		, m_DBInstances(heap)
		, m_DBClusters(heap)
		, m_Servers(heap)
		, m_GameClusters(heap)
	{
	}

	ServerConfig::~ServerConfig()
	{
		Clear();
	}

	void ServerConfig::Clear()
	{
		for (auto& itItem : m_DBInstances)
		{
			IHeap::Delete(itItem);
		}
		m_DBInstances.Clear();

		for (auto& itItem : m_DBClusters)
		{
			IHeap::Delete(itItem);
		}
		m_DBClusters.Clear();

		for (auto& itItem : m_Servers)
		{
			IHeap::Delete(itItem);
		}
		m_Servers.Clear();

		for (auto& itItem : m_GameClusters)
		{
			IHeap::Delete(itItem);
		}
		m_GameClusters.Clear();
	}

	const ServerConfig::DBInstance* ServerConfig::FindDBInstance(const char* instanceName) const
	{
		for (auto& itItem : m_DBInstances)
		{
			if (itItem->InstanceName == instanceName)
				return itItem;
		}
		return nullptr;
	}

	const ServerConfig::DBCluster* ServerConfig::FindDBCluster(StringCrc64 clusterName) const
	{
		for (auto& itItem : m_DBClusters)
		{
			if (clusterName == StringCrc64(itItem->ClusterName))
				return itItem;
		}

		return nullptr;
	}

	ServerConfig::DBCluster* ServerConfig::FindDBCluster(StringCrc64 clusterName)
	{
		for (auto& itItem : m_DBClusters)
		{
			if (clusterName == StringCrc64(itItem->ClusterName))
				return itItem;
		}

		return nullptr;
	}

	const ServerConfig::GameCluster* ServerConfig::FindGameCluster(GameID game) const
	{
		for (auto& itCluster : m_GameClusters)
		{
			if (itCluster->GameClusterID == game)
				return itCluster;
		}

		return nullptr;
	}

	const ServerConfig::GenericServer* ServerConfig::FindGenericServer(const char* serverName) const
	{
		for (auto& itServer : m_Servers)
		{
			if (itServer->Name == serverName)
				return itServer;
		}

		for (auto& itCluster : m_GameClusters)
		{
			auto pFound = itCluster->FindGenericServer(serverName);
			if (pFound != nullptr)
				return pFound;
		}

		return nullptr;
	}

	bool ServerConfig::operator == (const ServerConfig& src) const
	{
		// TODO:
		//for (auto& itItem : m_DBInstances)
		//{
		//	bool bFound = false;
		//	for (auto& srcItem : src.GetDBInstances())
		//	{
		//		if (*itItem == *srcItem)
		//		{
		//			bFound = true;
		//			break;
		//		}
		//	}

		//	if (!bFound)
		//		return false;
		//}

		return true;
	}

}



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server Config
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"

#include "Zookeeper/SFZookeeper.h"
#include "ServerConfig/SFServerConfig.h"
#include "json/json.h"




namespace SF
{

	class ServerConfigJson
	{
	private:

		IHeap& m_Heap;

	private:

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node setting value parsing
		//


		Result ParseMessageEndpoint(const Json::Value& jsonObject, const char* keyName, EndpointAddress& outMessageEndpoint);
		Result ParseDataCenter(const Json::Value& jsonObject, const char* keyName, ServerConfig::DataCenterEndpoint& outDataCenter);
		Result ParseNetPrivate(const Json::Value& json, ServerConfig::NetPrivate& privateNet);
		Result ParseNetPublic(const Json::Value& json, ServerConfig::NetPublic& publicNet);
		Result ParseGenericServer(const Json::Value& json, ServerConfig::GenericServer* pGenericServer);
		Result ParseDBInstance(const Json::Value& json, ServerConfig::DBInstance* pDBInstance);
		Result ParseDBCluster(const Json::Value& json, ServerConfig::DBCluster* pDBCluster);
		Result ParseModule(const Json::Value& json, ServerConfig::ServerModule* &pServerModule);


		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node loading
		//

		Result LoadChildModules(const Json::Value& rootObject, ServerConfig::GenericServer *pServer);
		Result LoadDBInstances(const Json::Value& rootObject, Array<ServerConfig::DBInstance*>& dbInstances);
		Result LoadDBClusters(const Json::Value& rootObject, Array<ServerConfig::DBCluster*>& dbClusters);
        Result LoadJsonConfig(const Json::Value& rootObject, ServerConfig::ServerService* pServer);
		Result LoadGenericServer(const Json::Value& nodeObject, ServerConfig::GenericServer* pServer);

	public:

		// Constructor
		ServerConfigJson(IHeap& heap);
		~ServerConfigJson();

		// Heap
		IHeap& GetHeap() { return m_Heap; }

		// Load config from server
		Result LoadConfig(const String& configFile, ServerConfig::ServerService* pServerConfig);

	};
}


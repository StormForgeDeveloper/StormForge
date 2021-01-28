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


#include "String/SFStringCrc32.h"
#include "String/SFString.h"

#include "Zookeeper/SFZookeeper.h"
#include "ServerConfig/SFEnum.h"
#include "ServerConfig/SFServerConfig.h"
#include "json/json.h"




namespace SF
{

	class ServerConfigJson
	{
	public:


	private:

		ServerConfig& m_Config;

	private:



		static Json::Value ToJsonSafeString(const String& src);

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node setting value parsing
		//


		Result ParseNetPrivate(const Json::Value& json, ServerConfig::NetPrivate& privateNet);
		Result ParseNetPublic(const Json::Value& json, ServerConfig::NetPublic& publicNet);
		Result ParseGenericServer(const Json::Value& json, ServerConfig::GenericServer* pGenericServer);
		Result ParseDBInstance(const Json::Value& json, ServerConfig::DBInstance* pDBInstance);
		Result ParseDBCluster(const Json::Value& json, ServerConfig::DBCluster* pDBCluster);
		Result ParseModule(const Json::Value& json, ServerConfig::ServerModule* &pServerModule);
		Result ParseGameServer(const Json::Value& json, ServerConfig::GameServer* pGameServer);
		Result ParseGameInstanceServer(const Json::Value& json, ServerConfig::GameInstanceServer* pGameInstanceServer);


		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node loading
		//

		Result LoadChildModules(const Json::Value& rootObject, ServerConfig::GenericServer *pServer);
		Result LoadModuleServer(const Json::Value& nodeObject, ServerConfig::ModuleServer* &pServer);
		Result LoadDBClusters(const Json::Value& rootObject, Array<ServerConfig::DBCluster*>& dbClusters);
		Result LoadJsonConfig(const Json::Value& jsonValue);


		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node setting value generation
		//


		Json::Value ToJsonNetPrivate(const ServerConfig::NetPrivate& privateNet) const;
		Json::Value ToJsonNetPublic(const ServerConfig::NetPublic& publicNet) const;
		Json::Value ToJsonGenericServer(const ServerConfig::GenericServer* pGenericServer) const;
		Json::Value ToJsonDBInstance(const ServerConfig::DBInstance* pDBInstance) const;
		Json::Value ToJsonDBCluster(const ServerConfig::DBCluster* pDBCluster) const;
		Json::Value ToJsonModule(const ServerConfig::ServerModule* pServerModule) const;
		Json::Value ToJsonServerComponent(const ServerConfig::ServerComponent* pServerComponent) const;
		Json::Value ToJsonGameServer(const ServerConfig::GameServer* pGameServer) const;
		Json::Value ToJsonGameInstanceServer(const ServerConfig::GameInstanceServer* pGameInstanceServer) const;
		Json::Value ToJsonGameCluster(const ServerConfig::GameCluster* pGameCluster) const;



	public:

		// Constructor
		ServerConfigJson(ServerConfig& config);
		~ServerConfigJson();

		// Heap
		IHeap& GetHeap() { return m_Config.GetHeap(); }

		// Load config from server
		Result LoadConfig(const char* configFile);
		Result LoadConfig(const String& configFile);

	};
}


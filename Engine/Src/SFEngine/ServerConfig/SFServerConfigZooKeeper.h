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

#pragma once

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#include "String/SFFixedString32.h"
#include "String/SFString.h"

#include "ZooKeeper/SFZooKeeper.h"
#include "ServerConfig/SFEnum.h"
#include "ServerConfig/SFServerConfig.h"
#include "json/json.h"




namespace SF
{

	class ServerConfigZooKeeper
	{
	public:


	private:

		ServerConfig& m_Config;
		ZooKeeper& m_zkInstance;

	private:

		template<class Func>
		Result ForeachChild(const String& nodePath, Func func);

		Result GetNodeValue(const String& nodePath, Json::Value& jsonValue);
		Result SetNodeValue(const String& nodePath, const Json::Value& jsonValue);

		Result CreateNode(const String& parentNodePath, const char* nodeName, const Json::Value& nodeValue);

		

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
		Result ParseModule(const String& nodePath, const Json::Value& json, ServerConfig::ServerModule* &pServerModule);
		Result ParseGameServer(const Json::Value& json, ServerConfig::GameServer* pGameServer);
		Result ParseGameInstanceServer(const Json::Value& json, ServerConfig::GameInstanceServer* pGameInstanceServer);
		Result ParseGameCluster(const Json::Value& json, ServerConfig::GameCluster* pGameCluster);


		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node loading
		//

		Result LoadGameInstanceServer(ServerConfig::GameCluster* pGameCluster, const String& nodePath, ServerConfig::GameInstanceServer* &pServer);
		Result LoadGameServer(ServerConfig::GameCluster* pGameCluster, const String& nodePath, ServerConfig::GameServer* &pServer);
		Result LoadChildModules(const String& nodePath, ServerConfig::GenericServer *pServer);
		Result LoadModuleServer(ServerConfig::GameCluster* pGameCluster, const String& nodePath, ServerConfig::ModuleServer* &pServer);
		Result LoadDBClusters(ServerConfig::GameCluster* pGameCluster, const String& rootPath, Array<ServerConfig::DBCluster*>& dbClusters);
		Result LoadModuleServers(ServerConfig::GameCluster* pGameCluster, const String& rootPath, Array<ServerConfig::ModuleServer*>& servers);
		Result LoadGameCluster(const char* gameClusterID, const String& nodePath, ServerConfig::GameCluster* &pGameCluster);


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


		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node storing
		//

		Result StoreModules(const String& nodePath, const ServerConfig::GenericServer* pServer);
		Result StoreGameInstanceServer(const String& nodePath, const ServerConfig::GameInstanceServer* pServer);
		Result StoreGameServer(const String& nodePath, const ServerConfig::GameServer* pServer);
		Result StoreModuleServer(const String& nodePath, const ServerConfig::ModuleServer* pServer);

		Result StoreGameCluster(const String& nodePath, const ServerConfig::GameCluster* pGameCluster);



	public:

		// Constructor
		ServerConfigZooKeeper(ServerConfig& config, ZooKeeper& zkInstance);
		~ServerConfigZooKeeper();

		// Heap
		IHeap& GetHeap() { return m_Config.GetHeap(); }

		// Load config from server
		Result LoadConfig(const char* configNodeRoot);
		Result LoadConfig(const String& nodePath);

		// Store config to server
		Result StoreConfig(const char* configNodeRoot);
		Result StoreConfig(const String& nodePath);

	};
}
#endif

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


#include "SFServerConfigZookeeper.h"
#include "String/SFStringCrc32.h"
#include "Util/SFLog.h"
#include "String/SFStringFormat.h"

#include <libxml/parser.h>
#include <libxml/tree.h>



namespace SF
{

	ServerConfigZookeeper::ServerConfigZookeeper(ServerConfig& config, Zookeeper& zkInstance)
		: m_Config(config)
		, m_zkInstance(zkInstance)
	{
		assert(zkInstance.IsConnected());
	}

	ServerConfigZookeeper::~ServerConfigZookeeper()
	{
	}

	template<class Func>
	Result ServerConfigZookeeper::ForeachChild(const String& nodePath, Func func)
	{
		StaticArray<String, 32> childList(GetHeap());
		Result result = m_zkInstance.GetChildren(nodePath, childList);
		if (!result)
			return result;

		for (auto& itChildPath : childList)
		{
			result = func(itChildPath);
			if (!result)
				break;
		}

		return result;
	}

	Result ServerConfigZookeeper::GetNodeValue(const String& nodePath, Json::Value& jsonValue)
	{
		Result result = m_zkInstance.Get(nodePath, jsonValue);
		if (!result) return result;
		return result;
	}

	Result ServerConfigZookeeper::SetNodeValue(const String& nodePath, const Json::Value& jsonValue)
	{
		return m_zkInstance.Set(nodePath, jsonValue);
	}

	Result ServerConfigZookeeper::CreateNode(const String& parentNodePath, const char* nodeName, const Json::Value& nodeValue)
	{
		String fullPath;
		if(nodeName != nullptr)
			fullPath.Format("{0}/{1}", parentNodePath, nodeName);
		else
			fullPath = parentNodePath;

		return m_zkInstance.Create(fullPath, nodeValue, nullptr, 0, fullPath);
	}



	Json::Value ServerConfigZookeeper::ToJsonSafeString(const String& src)
	{
		static const char* NullString = "";
		auto cstr = (const char*)src;
		assert(cstr != nullptr);
		return Json::Value(cstr == nullptr ? NullString : cstr);
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Node setting value parsing
	//


	Result ServerConfigZookeeper::ParseNetPrivate(const Json::Value& itemValue, ServerConfig::NetPrivate& privateNet)
	{
		auto IP = itemValue.get("IP", Json::Value(""));
		privateNet.IP = IP.asCString();
		privateNet.Port = itemValue.get("Port", Json::Value("")).asUInt();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigZookeeper::ParseNetPublic(const Json::Value& itemValue, ServerConfig::NetPublic& publicNet)
	{
		auto IPV4 = itemValue.get("IPV4", Json::Value(""));
		auto IPV6 = itemValue.get("IPV6", Json::Value(""));
		auto ListenIP = itemValue.get("ListenIP", Json::Value(""));
		publicNet.IPV4 = IPV4.asCString();
		publicNet.IPV6 = IPV6.asCString();
		publicNet.ListenIP = ListenIP.asCString();
		publicNet.Port = itemValue.get("Port", Json::Value("")).asUInt();
		publicNet.MaxConnection = itemValue.get("MaxConnection", Json::Value("")).asUInt();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigZookeeper::ParseGenericServer(const Json::Value& itemValue, ServerConfig::GenericServer* pGenericServer)
	{
		pGenericServer->UID = itemValue.get("UID", Json::Value("")).asUInt();
		pGenericServer->WorkerThreadCount = itemValue.get("WorkerThreadCount", Json::Value(4)).asUInt();
		pGenericServer->NetIOThreadCount = itemValue.get("NetIOThreadCount", Json::Value(4)).asUInt();
		//pGenericServer->Name = itemValue["Name"].asCString();
		Result result = ParseNetPrivate(itemValue.get("NetPrivate",Json::Value(Json::objectValue)), pGenericServer->PrivateNet);
		if (!result) return result;

		return ResultCode::SUCCESS;
	}


	Result ServerConfigZookeeper::ParseDBInstance(const Json::Value& itemValue, ServerConfig::DBInstance* pDBInstance)
	{
		auto ConnectionString = itemValue.get("ConnectionString", Json::Value(""));
		auto UserID = itemValue.get("UserID", Json::Value(""));
		auto Password = itemValue.get("Password", Json::Value(""));

		//pDBInstance->InstanceName = itemValue["InstanceName"].asCString();
		pDBInstance->ConnectionString = ConnectionString.asCString();
		pDBInstance->UserID = UserID.asCString();
		pDBInstance->Password = Password.asCString();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigZookeeper::ParseDBCluster(const Json::Value& itemValue, ServerConfig::DBCluster* pDBCluster)
	{
		auto ClusterTypeString = itemValue.get("ClusterType", Json::Value("Normal"));
		auto DBInstanceName = itemValue.get("DBInstanceName", Json::Value(""));
		auto DBName = itemValue.get("DBName", Json::Value(""));

		pDBCluster->ClusterType = Enum<DBClusterType>().GetValue(ClusterTypeString.asCString());
		pDBCluster->DBInstanceName = DBInstanceName.asCString();
		pDBCluster->DBName = DBName.asCString();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigZookeeper::ParseModule(const String& moduleName, const Json::Value& itemValue, ServerConfig::ServerModule* &pServerModule)
	{
		Result result;


		switch (Crc32C(moduleName))
		{
		case "ModMatching_Game_8"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleMatching_8(GetHeap());
			pModule->UseBot = itemValue.get("UseBot",Json::Value(false)).asBool();
			pServerModule = pModule;
		}
			break;
		case "ModMatching_Game_4"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleMatching_4(GetHeap());
			pModule->UseBot = itemValue.get("UseBot", Json::Value(false)).asBool();
			pServerModule = pModule;
		}
			break;
		case "ModPurchaseValidateGoogle"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleGooglePurchaseValidate(GetHeap());
			auto Account = itemValue.get("Account", Json::Value(""));
			auto P12KeyFile = itemValue.get("P12KeyFile", Json::Value(""));
			auto AuthScopes = itemValue.get("AuthScopes", Json::Value(""));

			pModule->Account = Account.asCString();
			pModule->P12KeyFile = P12KeyFile.asCString();
			pModule->AuthScopes = AuthScopes.asCString();
			pServerModule = pModule;
		}
			break;
		case "ModPurchaseValidateIOS"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleIOSPurchaseValidate(GetHeap());
			auto URL = itemValue.get("URL", Json::Value(""));
			auto AltURL = itemValue.get("AltURL", Json::Value(""));

			pModule->URL = URL.asCString();
			pModule->AltURL = AltURL.asCString();
			pServerModule = pModule;
		}
			break;
		case "ModLogin"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModulePublicService(GetHeap());
			result = ParseNetPublic(itemValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
		}
			break;
		case "ModGameInstanceManager"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModulePublicService(GetHeap());
			result = ParseNetPublic(itemValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
		}
		break;
		case "ModGame"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModulePublicService(GetHeap());
			result = ParseNetPublic(itemValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
		}
			break;
		case "ModRelay"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleRelayService(GetHeap());
			result = ParseNetPublic(itemValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pModule->MaximumRelayInstances = itemValue.get("MaximumRelayInstances", Json::Value(pModule->MaximumRelayInstances)).asUInt();
			pServerModule = pModule;
		}
		break;
		case "NetPrivate"_crc:
			break;

		case "ModMatchingQueue_Game_8x1"_crc:
		case "ModMatchingQueue_Game_8x2"_crc:
		case "ModMatchingQueue_Game_8x3"_crc:
		case "ModMatchingQueue_Game_8x4"_crc:
		case "ModMatchingQueue_Game_8x5"_crc:
		case "ModMatchingQueue_Game_8x6"_crc:
		case "ModMatchingQueue_Game_8x7"_crc:
		case "ModMatchingQueue_Game_8x1S"_crc:
		case "ModMatchingQueue_Game_8x1W"_crc:
		case "ModMatchingQueue_Game_4x1"_crc:
		case "ModMatchingQueue_Game_4x2"_crc:
		case "ModMatchingQueue_Game_4x3"_crc:
		case "ModMatchingQueue_Game_4x1S"_crc:
		case "ModMatchingQueue_Game_4x1W"_crc:
		case "ModGamePartyManager"_crc:
		case "ModMonitoring"_crc:
		case "ModRanking"_crc:
		case "ModChatting"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModule(GetHeap());
			pServerModule = pModule;
		}
		break;
		default:
			assert(false);
			break;
		}

		if (pServerModule != nullptr)
			pServerModule->ModuleName = moduleName;

		return result;
	}


	Result ServerConfigZookeeper::ParseGameServer(const Json::Value& itemValue, ServerConfig::GameServer* pGameServer)
	{
		Result result = ParseGenericServer(itemValue, pGameServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigZookeeper::ParseGameInstanceServer(const Json::Value& itemValue, ServerConfig::GameInstanceServer* pGameInstanceServer)
	{
		Result result = ParseGenericServer(itemValue, pGameInstanceServer);
		if (!result)
			return result;
		
		return result;
	}

	Result ServerConfigZookeeper::ParseGameCluster(const Json::Value& json, ServerConfig::GameCluster* pGameCluster)
	{
		return ResultCode::SUCCESS;
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Node loading
	//

	Result ServerConfigZookeeper::LoadGameInstanceServer(ServerConfig::GameCluster* pGameCluster, const String& nodePath, ServerConfig::GameInstanceServer* &pServer)
	{
		Json::Value nodeValue;
		Result result = GetNodeValue(nodePath, nodeValue);
		if (!result)
			return result;

		pServer = new(GetHeap()) ServerConfig::GameInstanceServer(GetHeap());
		pServer->pGameCluster = pGameCluster;

		result = ParseGameInstanceServer(nodeValue, pServer);
		if (!result)
			return result;

		result = LoadChildModules(nodePath, pServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigZookeeper::LoadGameServer(ServerConfig::GameCluster* pGameCluster, const String& nodePath, ServerConfig::GameServer* &pServer)
	{
		Json::Value nodeValue;
		Result result = GetNodeValue(nodePath, nodeValue);
		if (!result)
			return result;

		pServer = new(GetHeap()) ServerConfig::GameServer(GetHeap());
		pServer->pGameCluster = pGameCluster;

		result = ParseGameServer(nodeValue, pServer);
		if (!result)
			return result;

		result = LoadChildModules(nodePath, pServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigZookeeper::LoadChildModules(const String& nodePath, ServerConfig::GenericServer *pServer)
	{

		Result result = ForeachChild(nodePath, [&](const String& childName)
		{
			Json::Value childValue;
			ServerConfig::ServerModule* pModule = nullptr;

			String childPath(GetHeap());
			childPath.Format("{0}/{1}", nodePath, childName);

			result = GetNodeValue(childPath, childValue);
			if (!result)
				return result;

			result = ParseModule(childName, childValue, pModule);
			if (!result)
				return result;

			if (pModule != nullptr)
				pServer->Modules.push_back(pModule);

			return result;
		});


		return result;
	}

	Result ServerConfigZookeeper::LoadModuleServer(ServerConfig::GameCluster* pGameCluster, const String& nodePath, ServerConfig::ModuleServer* &pServer)
	{
		Json::Value nodeValue;
		Result result = GetNodeValue(nodePath, nodeValue);
		if (!result)
			return result;


		pServer = new(GetHeap()) ServerConfig::ModuleServer(GetHeap());

		pServer->pGameCluster = pGameCluster;

		result = ParseGenericServer(nodeValue, pServer);
		if (!result) return result;

		result = LoadChildModules(nodePath, pServer);
		if (!result) return result;

		return result;
	}

	Result ServerConfigZookeeper::LoadDBClusters(ServerConfig::GameCluster* pGameCluster, const String& rootPath, Array<ServerConfig::DBCluster*>& dbClusters)
	{
		Result result = ForeachChild(rootPath, [&](const String& childName)
		{
			Json::Value nodeValue;

			String childPath(GetHeap());
			childPath.Format("{0}/{1}", rootPath, childName);

			result = GetNodeValue(childPath, nodeValue);
			if (!result)
				return result;

			ServerConfig::DBCluster* pDBCluster = nullptr;
			pDBCluster = new(GetHeap()) ServerConfig::DBCluster(GetHeap());

			pDBCluster->pGameCluster = pGameCluster;
			pDBCluster->ClusterName = childName;
			result = ParseDBCluster(nodeValue, pDBCluster);
			if (pDBCluster != nullptr)
				dbClusters.push_back(pDBCluster);

			return result;
		});

		return result;
	}

	Result ServerConfigZookeeper::LoadModuleServers(ServerConfig::GameCluster* pGameCluster, const String& rootPath, Array<ServerConfig::ModuleServer*>& servers)
	{
		Result result = ForeachChild(rootPath, [&](const String& childName)
		{
			String childPath(GetHeap());
			childPath.Format("{0}/{1}", rootPath, childName);

			ServerConfig::ModuleServer* pModuleServer = nullptr;
			result = LoadModuleServer(pGameCluster, childPath, pModuleServer);
			pModuleServer->Name = childName;
			if (pModuleServer != nullptr)
				servers.push_back(pModuleServer);

			return result;
		});

		return result;
	}

	Result ServerConfigZookeeper::LoadGameCluster(const char* gameClusterID, const String& nodePath, ServerConfig::GameCluster* &pGameCluster)
	{
		Result result;
		Json::Value clusterValue;
		result = GetNodeValue(nodePath, clusterValue);
		if (!result)
			return result;

		pGameCluster = new(GetHeap()) ServerConfig::GameCluster(GetHeap());
		pGameCluster->SetGameClusterID( gameClusterID );

		result = ParseGameCluster(clusterValue, pGameCluster);
		if (!result)
			return result;

		String rootPath;
		rootPath.Format("{0}/{1}", nodePath, "DBCluster");
		result = LoadDBClusters(pGameCluster, rootPath, pGameCluster->DBClusters);
		if (!result)
			return result;

		rootPath.Format("{0}/{1}", nodePath, "Server");
		result = LoadModuleServers(pGameCluster, rootPath, pGameCluster->ModuleServers);
		if (!result)
			return result;

		rootPath.Format("{0}/{1}", nodePath, "GameServer");
		result = ForeachChild(rootPath, [&](const String& nodeName)
		{
			String childPath(GetHeap());
			childPath.Format("{0}/{1}", rootPath, nodeName);

			ServerConfig::GameServer* pServer = nullptr;
			result = LoadGameServer(pGameCluster, childPath, pServer);
			pServer->Name = nodeName;
			if (pServer != nullptr)
				pGameCluster->GameServers.push_back(pServer);

			return result;
		});
		if (!result)
			return result;

		rootPath.Format("{0}/{1}", nodePath, "GameInstanceServer");
		result = ForeachChild(rootPath, [&](const String& nodeName)
		{
			String childPath(GetHeap());
			childPath.Format("{0}/{1}", rootPath, nodeName);

			ServerConfig::GameInstanceServer* pServer = nullptr;
			result = LoadGameInstanceServer(pGameCluster, childPath, pServer);
			pServer->Name = nodeName;
			if (pServer != nullptr)
				pGameCluster->GameInstanceServers.push_back(pServer);

			return result;
		});
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigZookeeper::LoadConfig(const String& nodePath)
	{
		FunctionContext result([](Result result) 
		{
			if (!result)
			{
				SFLog(Engine, Error, "ServerConfigZookeeper::LoadConfig, has failed {0}", result);
			}
		});
		String rootPath;

		m_Config.Clear();

		rootPath.Format("{0}/{1}", nodePath, "DBInstance");
		result = ForeachChild(rootPath, [&](const String& nodeName)
		{
			Json::Value nodeValue;

			String childPath(GetHeap());
			childPath.Format("{0}/{1}", rootPath, nodeName);

			result = GetNodeValue(childPath, nodeValue);
			if (!result)
				return result;

			ServerConfig::DBInstance* pDBInstance = new(GetHeap()) ServerConfig::DBInstance(GetHeap());
			pDBInstance->InstanceName = nodeName;
			result = ParseDBInstance(nodeValue, pDBInstance);
			if (pDBInstance != nullptr)
				m_Config.GetDBInstances().push_back(pDBInstance);

			return result;
		});
		if (!result)
			return result;

		rootPath.Format("{0}/{1}", nodePath, "DBCluster");
		result = LoadDBClusters(nullptr, rootPath, m_Config.GetDBClusters());
		if (!result)
			return result;

		rootPath.Format("{0}/{1}", nodePath, "Server");
		result = LoadModuleServers(nullptr, rootPath, m_Config.GetServers());
		if (!result)
			return result;

		rootPath.Format("{0}/{1}", nodePath, "GameCluster");
		result = ForeachChild(rootPath, [&](const String& nodeName)
		{
			Json::Value nodeValue;
			String childPath(GetHeap());
			childPath.Format("{0}/{1}", rootPath, nodeName);

			result = GetNodeValue(childPath, nodeValue);
			if (!result)
				return result;

			ServerConfig::GameCluster* pGameCluster = nullptr;
			result = LoadGameCluster(nodeName, childPath, pGameCluster);
			if (pGameCluster != nullptr)
			{
				m_Config.GetGameClusters().push_back(pGameCluster);
			}

			return result;
		});
		if (!result)
			return result;

		return result;
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Node setting value generation
	//


	Json::Value ServerConfigZookeeper::ToJsonNetPrivate(const ServerConfig::NetPrivate& privateNet) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["IP"] = ToJsonSafeString(privateNet.IP);
		itemValue["Port"] = Json::Value(privateNet.Port);

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonNetPublic(const ServerConfig::NetPublic& publicNet) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["IPV4"] = ToJsonSafeString(publicNet.IPV4);
		itemValue["IPV6"] = ToJsonSafeString(publicNet.IPV6);
		itemValue["ListenIP"] = ToJsonSafeString(publicNet.ListenIP);
		itemValue["Port"] = Json::Value(publicNet.Port);
		itemValue["MaxConnection"] = Json::Value(publicNet.MaxConnection);

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonGenericServer(const ServerConfig::GenericServer* pGenericServer) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["UID"] = Json::Value(pGenericServer->UID);
		//itemValue["Name"] = ToJsonSafeString(pGenericServer->Name);
		itemValue["NetPrivate"] = ToJsonNetPrivate(pGenericServer->PrivateNet);
		itemValue["WorkerThreadCount"] = Json::Value(pGenericServer->WorkerThreadCount);
		itemValue["NetIOThreadCount"] = Json::Value(pGenericServer->NetIOThreadCount);

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonDBInstance(const ServerConfig::DBInstance* pDBInstance) const
	{
		Json::Value itemValue(Json::objectValue);

		//itemValue["InstanceName"] = ToJsonSafeString(pDBInstance->InstanceName);
		itemValue["ConnectionString"] = ToJsonSafeString(pDBInstance->ConnectionString);
		itemValue["UserID"] = ToJsonSafeString(pDBInstance->UserID);
		itemValue["Password"] = ToJsonSafeString(pDBInstance->Password);

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonDBCluster(const ServerConfig::DBCluster* pDBCluster) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["ClusterType"] = ToJsonSafeString(Enum<DBClusterType>().GetValueName(pDBCluster->ClusterType));
		itemValue["DBInstanceName"] = ToJsonSafeString(pDBCluster->DBInstanceName);
		itemValue["DBName"] = ToJsonSafeString(pDBCluster->DBName);

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonModule(const ServerConfig::ServerModule* pServerModule) const
	{
		Json::Value itemValue(Json::objectValue);

		switch (Crc32C((const char*)pServerModule->ModuleName))
		{
		case "ModMatching_Game_8"_crc:
			itemValue["UseBot"] = Json::Value(((ServerConfig::ServerModuleMatching_8*)pServerModule)->UseBot);
			break;
		case "ModMatching_Game_4"_crc:
			itemValue["UseBot"] = Json::Value(((ServerConfig::ServerModuleMatching_4*)pServerModule)->UseBot);
			break;
		case "ModPurchaseValidateGoogle"_crc:
		{
			auto pModule = static_cast<const ServerConfig::ServerModuleGooglePurchaseValidate*>(pServerModule);
			itemValue["Account"] = ToJsonSafeString(pModule->Account);
			itemValue["P12KeyFile"] = ToJsonSafeString(pModule->P12KeyFile);
			itemValue["AuthScopes"] = ToJsonSafeString(pModule->AuthScopes);
		}
		break;
		case "ModPurchaseValidateIOS"_crc:
		{
			auto pModule = static_cast<const ServerConfig::ServerModuleIOSPurchaseValidate*>(pServerModule);
			itemValue["URL"] = ToJsonSafeString(pModule->URL);
			itemValue["AltURL"] = ToJsonSafeString(pModule->AltURL);
		}
		break;
		case "ModMonitoring"_crc:
			break;
		case "ModLogin"_crc:
		{
			auto pModule = static_cast<const ServerConfig::ServerModulePublicService*>(pServerModule);
			itemValue["NetPublic"] = ToJsonNetPublic(pModule->PublicNet);
		}
		break;
		case "ModRanking"_crc:
			break;
		case "ModGame"_crc:
		{
			auto pModule = static_cast<const ServerConfig::ServerModulePublicService*>(pServerModule);
			itemValue["NetPublic"] = ToJsonNetPublic(pModule->PublicNet);
		}
		break;
		case "ModRelay"_crc:
		{
			auto pModule = static_cast<const ServerConfig::ServerModuleRelayService*>(pServerModule);
			itemValue["NetPublic"] = ToJsonNetPublic(pModule->PublicNet);
			itemValue["MaximumRelayInstances"] = Json::Value(pModule->MaximumRelayInstances);
		}
		break;
		case "NetPrivate"_crc:
			break;
		case "ModMatchingQueue_Game_8x1"_crc:
		case "ModMatchingQueue_Game_8x2"_crc:
		case "ModMatchingQueue_Game_8x3"_crc:
		case "ModMatchingQueue_Game_8x4"_crc:
		case "ModMatchingQueue_Game_8x5"_crc:
		case "ModMatchingQueue_Game_8x6"_crc:
		case "ModMatchingQueue_Game_8x7"_crc:
		case "ModMatchingQueue_Game_8x1S"_crc:
		case "ModMatchingQueue_Game_8x1W"_crc:
		case "ModMatchingQueue_Game_4x1"_crc:
		case "ModMatchingQueue_Game_4x2"_crc:
		case "ModMatchingQueue_Game_4x3"_crc:
		case "ModMatchingQueue_Game_4x1S"_crc:
		case "ModMatchingQueue_Game_4x1W"_crc:
		case "ModGamePartyManager"_crc:
		case "ModChatting"_crc:
			break;
		default:
			assert(false);
			break;
		}


		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonServerComponent(const ServerConfig::ServerComponent* pServerComponent) const
	{
		Json::Value itemValue(Json::objectValue);

		switch (Crc32C((const char*)pServerComponent->ComponentName))
		{
		case "ComponentGoogle"_crc:
		{
			auto pComponent = static_cast<const ServerConfig::ServerComponentGoogle*>(pServerComponent);
			itemValue["Account"] = ToJsonSafeString(pComponent->Account);
			itemValue["P12KeyFile"] = ToJsonSafeString(pComponent->P12KeyFile);
			itemValue["AuthScopes"] = ToJsonSafeString(pComponent->AuthScopes);
		}
		break;
		case "ComponentIOS"_crc:
		{
			auto pComponent = static_cast<const ServerConfig::ServerComponentIOS*>(pServerComponent);
			itemValue["URL"] = ToJsonSafeString(pComponent->URL);
			itemValue["AltURL"] = ToJsonSafeString(pComponent->AltURL);
		}
		break;
		case "NetPrivate"_crc:
		case "NetPublic"_crc:
			break;
		default:
			assert(false);
			break;
		}

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonGameServer(const ServerConfig::GameServer* pGameServer) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue = ToJsonGenericServer(pGameServer);

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonGameInstanceServer(const ServerConfig::GameInstanceServer* pGameInstanceServer) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue = ToJsonGenericServer(pGameInstanceServer);

		return itemValue;
	}

	Json::Value ServerConfigZookeeper::ToJsonGameCluster(const ServerConfig::GameCluster* pGameCluster) const
	{
		Json::Value itemValue(Json::objectValue);

		return itemValue;
	}

	Result ServerConfigZookeeper::StoreModules(const String& nodePath, const ServerConfig::GenericServer* pServer)
	{
		Result result;

		for (auto& itModule : pServer->Modules)
		{
			Json::Value moduleValue = ToJsonModule(itModule);

			result = CreateNode(nodePath, itModule->ModuleName, moduleValue);
			if (!result)
				return result;
		}

		return result;
	}

	Result ServerConfigZookeeper::StoreGameInstanceServer(const String& nodePath, const ServerConfig::GameInstanceServer* pServer)
	{
		Json::Value nodeValue(Json::objectValue);
		nodeValue = ToJsonGameInstanceServer(pServer);

		Result result = CreateNode(nodePath, nullptr, nodeValue);
		if (!result)
			return result;

		result = StoreModules(nodePath, pServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigZookeeper::StoreGameServer(const String& nodePath, const ServerConfig::GameServer* pServer)
	{
		Result result;
		Json::Value nodeValue(Json::objectValue);

		nodeValue = ToJsonGameServer(pServer);

		result = CreateNode(nodePath, nullptr, nodeValue);
		if (!result)
			return result;

		result = StoreModules(nodePath, pServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigZookeeper::StoreModuleServer(const String& nodePath, const ServerConfig::ModuleServer* pServer)
	{
		Result result;
		Json::Value nodeValue(Json::objectValue);

		nodeValue = ToJsonGenericServer(pServer);
		result = CreateNode(nodePath, nullptr, nodeValue);
		if (!result)
			return result;

		result = StoreModules(nodePath, pServer);
		if(!result)
			return result;

		return result;
	}

	Result ServerConfigZookeeper::StoreGameCluster(const String& nodePath, const ServerConfig::GameCluster* pGameCluster)
	{
		Result result;

		// Destroy if already have it, and create new one
		if (m_zkInstance.Exists(nodePath))
			result = m_zkInstance.DeleteTree(nodePath);
		String outPath;
		result = m_zkInstance.Create(nodePath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		String rootPath;
		rootPath.Format("{0}/{1}", nodePath, "DBCluster");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		Json::Value clusterValue = ToJsonGameCluster(pGameCluster);
		result = SetNodeValue(nodePath, clusterValue);
		if (!result)
			return result;

		for (auto& itItem : pGameCluster->DBClusters)
		{
			Json::Value itemValue = ToJsonDBCluster(itItem);
			result = CreateNode(rootPath, itItem->ClusterName, itemValue);
			if (!result)
				return result;
		}

		// create root for module servers
		rootPath.Format("{0}/{1}", nodePath, "Server");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		for (auto& itServer : pGameCluster->ModuleServers)
		{
			String childPath;
			childPath.Format("{0}/{1}", rootPath, itServer->Name);

			result = StoreModuleServer(childPath, itServer);
			if (!result)
				return result;
		}

		// create root for module servers
		rootPath.Format("{0}/{1}", nodePath, "GameServer");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		for (auto& itServer : pGameCluster->GameServers)
		{
			String childPath;
			childPath.Format("{0}/{1}", rootPath, itServer->Name);

			result = StoreGameServer(childPath, itServer);
			if (!result)
				return result;
		}

		// create root for module servers
		rootPath.Format("{0}/{1}", nodePath, "GameInstanceServer");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		for (auto& itServer : pGameCluster->GameInstanceServers)
		{
			String childPath;
			childPath.Format("{0}/{1}", rootPath, itServer->Name);

			result = StoreGameInstanceServer(childPath, itServer);
			if (!result)
				return result;
		}

		return result;
	}


	Result ServerConfigZookeeper::StoreConfig(const String& nodePath)
	{
		Result result;

		if (m_zkInstance.Exists(nodePath))
			result = m_zkInstance.DeleteTree(nodePath);
		if (!result)
			return result;

		String outPath(GetHeap());
		StaticArray<uint8_t, 16> valueBuffer(GetHeap());
		result = m_zkInstance.Create(nodePath, valueBuffer, nullptr, 0, outPath);
		if (!result)
			return result;

		String rootPath;

		rootPath.Format("{0}/{1}", nodePath, "DBInstance");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		for (auto& itItem : m_Config.GetDBInstances())
		{
			Json::Value itemValue = ToJsonDBInstance(itItem);
			result = CreateNode(rootPath, itItem->InstanceName, itemValue);
			if (!result)
				return result;
		}


		rootPath.Format("{0}/{1}", nodePath, "DBCluster");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		for (auto& itItem : m_Config.GetDBClusters())
		{
			Json::Value itemValue = ToJsonDBCluster(itItem);
			result = CreateNode(rootPath, itItem->ClusterName, itemValue);
			if (!result)
				return result;
		}


		// create root for module servers
		rootPath.Format("{0}/{1}", nodePath, "Server");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		for (auto& itItem : m_Config.GetServers())
		{
			String childPath;
			childPath.Format("{0}/{1}", rootPath, itItem->Name);

			result = StoreModuleServer(childPath, itItem);
			if (!result)
				return result;
		}

		// create root for Game clusters
		rootPath.Format("{0}/{1}", nodePath, "GameCluster");
		result = m_zkInstance.Create(rootPath, Json::Value(Json::objectValue), nullptr, 0, outPath);
		if (!result)
			return result;

		for (auto& itItem : m_Config.GetGameClusters())
		{
			String childPath;
			childPath.Format("{0}/{1}", rootPath, itItem->GameClusterIDName);

			result = StoreGameCluster(childPath, itItem);
			if (!result)
				return result;
		}


		return result;
	}


	// Load config from server
	Result ServerConfigZookeeper::LoadConfig(const char* configNodeRoot)
	{
		return LoadConfig(String(GetHeap(), configNodeRoot));
	}

	// Store config to server
	Result ServerConfigZookeeper::StoreConfig(const char* configNodeRoot)
	{
		return StoreConfig(String(GetHeap(), configNodeRoot));
	}



}


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


#include "SFEnginePCH.h"

#include "SFServerConfigJson.h"
#include "String/SFStringCrc32.h"
#include "Util/SFLog.h"
#include "String/SFStringFormat.h"
#include "IO/SFFile.h"




namespace SF
{

	ServerConfigJson::ServerConfigJson(ServerConfig& config)
		: m_Config(config)
	{
	}

	ServerConfigJson::~ServerConfigJson()
	{
	}



	Json::Value ServerConfigJson::ToJsonSafeString(const String& src)
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


	Result ServerConfigJson::ParseNetPrivate(const Json::Value& itemValue, ServerConfig::NetPrivate& privateNet)
	{
		auto IP = itemValue.get("IP", Json::Value(""));
		privateNet.IP = IP.asCString();
		privateNet.Port = itemValue.get("Port", Json::Value("")).asUInt();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigJson::ParseNetPublic(const Json::Value& itemValue, ServerConfig::NetPublic& publicNet)
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

	Result ServerConfigJson::ParseGenericServer(const Json::Value& itemValue, ServerConfig::GenericServer* pGenericServer)
	{
		pGenericServer->UID = itemValue.get("UID", Json::Value("")).asUInt();
		pGenericServer->WorkerThreadCount = itemValue.get("WorkerThreadCount", Json::Value(4)).asUInt();
		pGenericServer->NetIOThreadCount = itemValue.get("NetIOThreadCount", Json::Value(4)).asUInt();
		pGenericServer->Executable = itemValue.get("Executable", Json::Value("")).asCString();
		//pGenericServer->Name = itemValue["Name"].asCString();
		Result result = ParseNetPrivate(itemValue.get("NetPrivate",Json::Value(Json::objectValue)), pGenericServer->PrivateNet);
		if (!result) return result;

		return ResultCode::SUCCESS;
	}


	Result ServerConfigJson::ParseDBInstance(const Json::Value& itemValue, ServerConfig::DBInstance* pDBInstance)
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

	Result ServerConfigJson::ParseDBCluster(const Json::Value& itemValue, ServerConfig::DBCluster* pDBCluster)
	{
		auto ClusterTypeString = itemValue.get("ClusterType", Json::Value("Normal"));
		auto DBInstanceName = itemValue.get("DBInstanceName", Json::Value(""));
		auto DBName = itemValue.get("DBName", Json::Value(""));

		pDBCluster->ClusterName = itemValue.get("Name", Json::Value("None")).asCString();
		pDBCluster->ClusterType = Enum<DBClusterType>().GetValue(ClusterTypeString.asCString());
		pDBCluster->DBInstanceName = DBInstanceName.asCString();
		pDBCluster->DBName = DBName.asCString();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigJson::ParseModule(const Json::Value& moduleValue, ServerConfig::ServerModule* &pServerModule)
	{
		Result result;

		auto moduleName = moduleValue.get("Name", Json::Value(""));

		switch (StringCrc32(moduleName.asCString()))
		{
		case "ModMatching_Game_8"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleMatching_8(GetHeap());
			pModule->UseBot = moduleValue.get("UseBot",Json::Value(false)).asBool();
			pServerModule = pModule;
		}
			break;
		case "ModMatching_Game_4"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleMatching_4(GetHeap());
			pModule->UseBot = moduleValue.get("UseBot", Json::Value(false)).asBool();
			pServerModule = pModule;
		}
			break;
		case "ModPurchaseValidateGoogle"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleGooglePurchaseValidate(GetHeap());
			auto Account = moduleValue.get("Account", Json::Value(""));
			auto P12KeyFile = moduleValue.get("P12KeyFile", Json::Value(""));
			auto AuthScopes = moduleValue.get("AuthScopes", Json::Value(""));

			pModule->Account = Account.asCString();
			pModule->P12KeyFile = P12KeyFile.asCString();
			pModule->AuthScopes = AuthScopes.asCString();
			pServerModule = pModule;
		}
			break;
		case "ModPurchaseValidateIOS"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleIOSPurchaseValidate(GetHeap());
			auto URL = moduleValue.get("URL", Json::Value(""));
			auto AltURL = moduleValue.get("AltURL", Json::Value(""));

			pModule->URL = URL.asCString();
			pModule->AltURL = AltURL.asCString();
			pServerModule = pModule;
			break;
		}
		case "ModLogin"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModulePublicService(GetHeap());
			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
			break;
		}
		case "ModGame"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModulePublicService(GetHeap());
			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
			break;
		}
		case "ModGameInstanceManager"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleGameInstanceManager(GetHeap());

			pModule->Name = moduleValue.get("Name", Json::Value("")).asCString();
			pModule->DataTable = moduleValue.get("DataTable", Json::Value("")).asCString();

			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
			break;
		}
		case "ModRelay"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleRelayService(GetHeap());
			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pModule->MaximumRelayInstances = moduleValue.get("MaximumRelayInstances", Json::Value(pModule->MaximumRelayInstances)).asUInt();
			pServerModule = pModule;
			break;
		}
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
			pServerModule->ModuleName = moduleName.asCString();

		return result;
	}


	Result ServerConfigJson::ParseGameServer(const Json::Value& itemValue, ServerConfig::GameServer* pGameServer)
	{
		Result result = ParseGenericServer(itemValue, pGameServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigJson::ParseGameInstanceServer(const Json::Value& itemValue, ServerConfig::GameInstanceServer* pGameInstanceServer)
	{
		Result result = ParseGenericServer(itemValue, pGameInstanceServer);
		if (!result)
			return result;
		
		return result;
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Node loading
	//

	Result ServerConfigJson::LoadChildModules(const Json::Value& rootObject, ServerConfig::GenericServer *pServer)
	{
		Json::Value ModuleArray;
		rootObject.get("Module", ModuleArray);
		if (!ModuleArray.isArray() || ModuleArray.size() == 0)
			return ResultCode::SUCCESS;

		Result result;

		for (auto& itModuleValue : ModuleArray)
		{
			ServerConfig::ServerModule* pModule = new(GetHeap()) ServerConfig::ServerModule(GetHeap());
			result = ParseModule(itModuleValue, pModule);
			if (!result)
				return result;

			if (pModule != nullptr)
				pServer->Modules.push_back(pModule);

			return result;
		}

		return result;
	}

	Result ServerConfigJson::LoadModuleServer(const Json::Value& nodeObject, ServerConfig::ModuleServer* &pServer)
	{
		pServer = new(GetHeap()) ServerConfig::ModuleServer(GetHeap());

		auto result = ParseGenericServer(nodeObject, pServer);
		if (!result) return result;

		result = LoadChildModules(nodeObject, pServer);
		if (!result) return result;

		return result;
	}

	Result ServerConfigJson::LoadDBClusters(const Json::Value& rootObject, Array<ServerConfig::DBCluster*>& dbClusters)
	{
		Json::Value DBClusterArray;
		rootObject.get("DBCluster", DBClusterArray);
		if (!DBClusterArray.isArray() || DBClusterArray.size() == 0)
			return ResultCode::SUCCESS;

		Result result;
		for (auto& itCluster : DBClusterArray)
		{
			if (!itCluster.isObject())
				continue;

			ServerConfig::DBCluster* pDBCluster = nullptr;
			pDBCluster = new(GetHeap()) ServerConfig::DBCluster(GetHeap());
			result = ParseDBCluster(itCluster, pDBCluster);
			if (pDBCluster != nullptr)
				dbClusters.push_back(pDBCluster);

			return result;
		}

		return result;
	}

	Result ServerConfigJson::LoadJsonConfig(const Json::Value& jsonValue)
	{
		Result result;

		auto gameClusterID = jsonValue.get("GameClusterId", Json::Value("")).asCString();
		ServerConfig::GameCluster gameCluster(GetHeap()); // TODO:

		result = LoadDBClusters(jsonValue, gameCluster.DBClusters);
		if (!result)
			return result;

		ServerConfig::ModuleServer* pModuleServer = nullptr;
		result = LoadModuleServer(jsonValue, pModuleServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigJson::LoadConfig(const String& configFilePath)
	{
		ScopeContext result([](Result result) 
		{
			if (!result)
			{
				SFLog(Engine, Error, "ServerConfigJson::LoadConfig, has failed {0}", result);
			}
		});

		Result hr;
		File file;
		file.Open(configFilePath, File::OpenMode::Read);
		if (!file.IsOpened())
			return hr = ResultCode::FAIL;

		auto fileSize = file.GetFileSize();
		StaticArray<uint8_t, 1024> buffer(GetHeap());
		buffer.resize(fileSize + 1);
		size_t readed = 0;
		hr = file.Read(buffer.data(), fileSize, readed);
		if (!hr)
			return hr;

		buffer[fileSize] = '\0';

		std::string errs;
		Json::CharReaderBuilder jsonBuilder;
		Json::Value jsonValue;
		UniquePtr<Json::CharReader> jsonReader(jsonBuilder.newCharReader());
		auto readStart = reinterpret_cast<const char*>(buffer.data());
		bool bRes = jsonReader->parse(readStart, readStart + buffer.size(), &jsonValue, &errs);
		if (!bRes)
		{
			SFLog(Net, Error, "ServerConfigJson::LoadConfig value parsing error:{0}", errs);
			return ResultCode::INVALID_STR_DATA;
		}

		return LoadJsonConfig(jsonValue);
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Node setting value generation
	//


	Json::Value ServerConfigJson::ToJsonNetPrivate(const ServerConfig::NetPrivate& privateNet) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["IP"] = ToJsonSafeString(privateNet.IP);
		itemValue["Port"] = Json::Value(privateNet.Port);

		return itemValue;
	}

	Json::Value ServerConfigJson::ToJsonNetPublic(const ServerConfig::NetPublic& publicNet) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["IPV4"] = ToJsonSafeString(publicNet.IPV4);
		itemValue["IPV6"] = ToJsonSafeString(publicNet.IPV6);
		itemValue["ListenIP"] = ToJsonSafeString(publicNet.ListenIP);
		itemValue["Port"] = Json::Value(publicNet.Port);
		itemValue["MaxConnection"] = Json::Value(publicNet.MaxConnection);

		return itemValue;
	}

	Json::Value ServerConfigJson::ToJsonGenericServer(const ServerConfig::GenericServer* pGenericServer) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["UID"] = Json::Value(pGenericServer->UID);
		//itemValue["Name"] = ToJsonSafeString(pGenericServer->Name);
		itemValue["Executable"] = ToJsonSafeString(pGenericServer->Executable);
		itemValue["NetPrivate"] = ToJsonNetPrivate(pGenericServer->PrivateNet);
		itemValue["WorkerThreadCount"] = Json::Value(pGenericServer->WorkerThreadCount);
		itemValue["NetIOThreadCount"] = Json::Value(pGenericServer->NetIOThreadCount);

		return itemValue;
	}

	Json::Value ServerConfigJson::ToJsonDBInstance(const ServerConfig::DBInstance* pDBInstance) const
	{
		Json::Value itemValue(Json::objectValue);

		//itemValue["InstanceName"] = ToJsonSafeString(pDBInstance->InstanceName);
		itemValue["ConnectionString"] = ToJsonSafeString(pDBInstance->ConnectionString);
		itemValue["UserID"] = ToJsonSafeString(pDBInstance->UserID);
		itemValue["Password"] = ToJsonSafeString(pDBInstance->Password);

		return itemValue;
	}

	Json::Value ServerConfigJson::ToJsonDBCluster(const ServerConfig::DBCluster* pDBCluster) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue["ClusterType"] = ToJsonSafeString(Enum<DBClusterType>().GetValueName(pDBCluster->ClusterType));
		itemValue["DBInstanceName"] = ToJsonSafeString(pDBCluster->DBInstanceName);
		itemValue["DBName"] = ToJsonSafeString(pDBCluster->DBName);

		return itemValue;
	}

	Json::Value ServerConfigJson::ToJsonModule(const ServerConfig::ServerModule* pServerModule) const
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
			break;
		}
		case "ModGameInstanceManager"_crc:
		{
			auto pModule = static_cast<const ServerConfig::ServerModuleGameInstanceManager*>(pServerModule);
			itemValue["Name"] = ToJsonSafeString(pModule->Name);
			itemValue["DataTable"] = ToJsonSafeString(pModule->DataTable);
			itemValue["NetPublic"] = ToJsonNetPublic(pModule->PublicNet);
			break;
		}
		case "ModRelay"_crc:
		{
			auto pModule = static_cast<const ServerConfig::ServerModuleRelayService*>(pServerModule);
			itemValue["NetPublic"] = ToJsonNetPublic(pModule->PublicNet);
			itemValue["MaximumRelayInstances"] = Json::Value(pModule->MaximumRelayInstances);
			break;
		}
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

	Json::Value ServerConfigJson::ToJsonServerComponent(const ServerConfig::ServerComponent* pServerComponent) const
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

	Json::Value ServerConfigJson::ToJsonGameServer(const ServerConfig::GameServer* pGameServer) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue = ToJsonGenericServer(pGameServer);

		return itemValue;
	}

	Json::Value ServerConfigJson::ToJsonGameInstanceServer(const ServerConfig::GameInstanceServer* pGameInstanceServer) const
	{
		Json::Value itemValue(Json::objectValue);

		itemValue = ToJsonGenericServer(pGameInstanceServer);

		return itemValue;
	}

	Json::Value ServerConfigJson::ToJsonGameCluster(const ServerConfig::GameCluster* pGameCluster) const
	{
		Json::Value itemValue(Json::objectValue);

		return itemValue;
	}


	// Load config from server
	Result ServerConfigJson::LoadConfig(const char* configFile)
	{
		return LoadConfig(String(GetHeap(), configFile));
	}



}



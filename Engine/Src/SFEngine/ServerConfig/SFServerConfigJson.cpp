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
#include "Util/SFStringCrc32.h"
#include "Util/SFLog.h"
#include "Util/SFStringFormat.h"
#include "IO/SFFile.h"




namespace SF
{

	ServerConfigJson::ServerConfigJson(IHeap& heap)
		: m_Heap(heap)
	{
	}

	ServerConfigJson::~ServerConfigJson()
	{
	}





	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Node setting value parsing
	//

	Result ServerConfigJson::ParseMessageEndpoint(const Json::Value& jsonObject, const char* keyName, EndpointAddress& outMessageEndpoint)
	{
		auto stringValue = jsonObject.get(keyName, Json::Value(Json::stringValue));

		outMessageEndpoint = stringValue.asCString();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigJson::ParseDataCenter(const Json::Value& jsonObject, const char* keyName, ServerConfig::DataCenterEndpoint& outDataCenter)
	{
		auto stringValue = jsonObject.get(keyName, Json::Value(Json::stringValue));
		auto splitIndex = StrUtil::Indexof(stringValue.asCString(), '/');
		if (splitIndex < 0)
			return ResultCode::FAIL;

		String dataCenterString = stringValue.asCString();
		outDataCenter.Server = dataCenterString.SubString(0, splitIndex);
		outDataCenter.Path = dataCenterString.SubString(splitIndex, (int)dataCenterString.length());

		return ResultCode::SUCCESS;
	}

	Result ServerConfigJson::ParseNetPrivate(const Json::Value& itemValue, ServerConfig::NetPrivate& privateNet)
	{
		auto IP = itemValue.get("IP", Json::Value(""));
		privateNet.IP = IP.asCString();
		privateNet.Port = itemValue.get("Port", Json::Value(Json::uintValue)).asUInt();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigJson::ParseNetPublic(const Json::Value& itemValue, ServerConfig::NetPublic& publicNet)
	{
		auto Protocol = itemValue.get("Protocol", Json::Value("TCP"));
		auto ListenIP = itemValue.get("ListenIP", Json::Value(""));
		publicNet.Protocol = Protocol.asCString();
		publicNet.ListenIP = ListenIP.asCString();
		publicNet.Port = (uint16_t)itemValue.get("Port", Json::Value("")).asUInt();
		publicNet.MaxConnection = itemValue.get("MaxConnection", Json::Value("")).asUInt();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigJson::ParseGenericServer(const Json::Value& itemValue, ServerConfig::GenericServer* pGenericServer)
	{
		auto Name = itemValue.get("Name", Json::Value(""));
		auto UID = itemValue.get("UID", Json::Value(Json::uintValue));
		auto WorkerThreadCount = itemValue.get("WorkerThreadCount", Json::Value(4));
		auto NetIOThreadCount = itemValue.get("NetIOThreadCount", Json::Value(4));
		//auto NetPrivate = itemValue.get("NetPrivate", Json::Value(Json::objectValue));

		pGenericServer->Name = Name.asCString();
		pGenericServer->UID = UID.asUInt();
		pGenericServer->WorkerThreadCount = WorkerThreadCount.asUInt();
		pGenericServer->NetIOThreadCount = NetIOThreadCount.asUInt();
		//Result result = ParseNetPrivate(NetPrivate, pGenericServer->PrivateNet);
		//if (!result) return result;

		return ResultCode::SUCCESS;
	}


	Result ServerConfigJson::ParseDBInstance(const Json::Value& itemValue, ServerConfig::DBInstance* pDBInstance)
	{
		auto Name = itemValue.get("Name", Json::Value(""));
		auto ConnectionString = itemValue.get("ConnectionString", Json::Value(""));
		auto UserID = itemValue.get("UserID", Json::Value(""));
		auto Password = itemValue.get("Password", Json::Value(""));

		pDBInstance->InstanceName = Name.asCString();
		pDBInstance->ConnectionString = ConnectionString.asCString();
		pDBInstance->UserID = UserID.asCString();
		pDBInstance->Password = Password.asCString();

		return ResultCode::SUCCESS;
	}

	Result ServerConfigJson::ParseDBCluster(const Json::Value& itemValue, ServerConfig::DBCluster* pDBCluster)
	{
		auto Name = itemValue.get("Name", Json::Value("None"));
		auto ClusterTypeString = itemValue.get("ClusterType", Json::Value("Normal"));
		auto DBInstanceName = itemValue.get("DBInstanceName", Json::Value(""));
		auto DBName = itemValue.get("DBName", Json::Value(""));
		auto DBCacheConnectionString = itemValue.get("DBCacheConnectionString", Json::Value(""));

		pDBCluster->ClusterName = Name.asCString();
		pDBCluster->ClusterType = StrUtil::StringCompairIgnoreCase("Normal", 7, ClusterTypeString.asCString(), -1) == true ? DBClusterType::Normal : DBClusterType::Sharding;
		pDBCluster->DBInstanceName = DBInstanceName.asCString();
		pDBCluster->DBName = DBName.asCString();
		pDBCluster->DBCacheConnectionString = DBCacheConnectionString.asCString();

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
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleMatching_8;
			pModule->UseBot = moduleValue.get("UseBot",Json::Value(false)).asBool();
			pServerModule = pModule;
		}
			break;
		case "ModMatching_Game_4"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleMatching_4;
			pModule->UseBot = moduleValue.get("UseBot", Json::Value(false)).asBool();
			pServerModule = pModule;
		}
			break;
		case "ModPurchaseValidateGoogle"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleGooglePurchaseValidate;
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
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleIOSPurchaseValidate;
			auto URL = moduleValue.get("URL", Json::Value(""));
			auto AltURL = moduleValue.get("AltURL", Json::Value(""));

			pModule->URL = URL.asCString();
			pModule->AltURL = AltURL.asCString();
			pServerModule = pModule;
			break;
		}
		case "ModLogin"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModulePublicService;
			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
			break;
		}
		case "ModGame"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModulePublicService;
			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
			break;
		}
        // Deprecated
		case "ModStaticGameInstanceManager"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleStaticGameInstanceManager;

			pModule->ZoneDBTable = moduleValue.get("ZoneDBTable", Json::Value("")).asCString();

			pServerModule = pModule;
			break;
		}
        // Deprecated
		case "ModGameInstanceManager"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleGameInstanceManager;

			pModule->ZoneDBTable = moduleValue.get("ZoneDBTable", Json::Value("")).asCString();

			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pServerModule = pModule;
			break;
		}
		case "ModRelay"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleRelayService;
			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);
			pModule->MaximumRelayInstances = moduleValue.get("MaximumRelayInstances", Json::Value(pModule->MaximumRelayInstances)).asUInt();
			pServerModule = pModule;
			break;
		}
		case "ModTelemetryFrontend"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModuleTelemetryFrontend;

			result = ParseNetPublic(moduleValue.get("NetPublic", Json::Value(Json::objectValue)), pModule->PublicNet);

			auto ClientId = moduleValue.get("ClientId", Json::Value(""));
			pModule->ClientId = ClientId.asCString();

			auto AuthKey = moduleValue.get("AuthKey", Json::Value(""));
			pModule->AuthKey = ClientId.asCString();

			auto SSLCertFile = moduleValue.get("SSLCertFile", Json::Value(""));
			pModule->SSLCertFile = SSLCertFile.asCString();

			auto SSLPrivateKeyFile = moduleValue.get("SSLPrivateKeyFile", Json::Value(""));
			pModule->SSLPrivateKeyFile = SSLPrivateKeyFile.asCString();

			pModule->NumNetThread = moduleValue.get("NumNetThread", Json::Value(1)).asInt();

			result = ParseDataCenter(moduleValue, "Destination", pModule->Destination);
			if (!result) return result;

			pServerModule = pModule;
			break;
		}
		case "NetPrivate"_crc:
			break;

		case "ModGamePartyManager"_crc:
		case "ModMonitoring"_crc:
		case "ModRanking"_crc:
		case "ModChatChannelManager"_crc:
		{
			auto pModule = new(GetHeap()) ServerConfig::ServerModule;
			pServerModule = pModule;
			break;
		}
		default:
			SFLog(System, Error, "Not supported server module name:{0}", moduleName.asCString());
			return ResultCode::NOT_SUPPORTED;
		}

		// Ignoring parsing error as not all of module requires it
		ParseMessageEndpoint(moduleValue, "ListenEndpoint", pServerModule->ServiceListenEndpoint);

		if (pServerModule != nullptr)
			pServerModule->ModuleName = moduleName.asCString();

		return result;
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Node loading
	//

	Result ServerConfigJson::LoadChildModules(const Json::Value& rootObject, ServerConfig::GenericServer *pServer)
	{
		Json::Value ModuleArray(Json::arrayValue);
		ModuleArray = rootObject.get("Module", ModuleArray);
		if (!ModuleArray.isArray() || ModuleArray.size() == 0)
			return ResultCode::SUCCESS;

		Result result;

		for (auto& itModuleValue : ModuleArray)
		{
			ServerConfig::ServerModule* pModule = new(GetHeap()) ServerConfig::ServerModule;
			result = ParseModule(itModuleValue, pModule);
			if (!result)
				return result;

			if (pModule != nullptr)
				pServer->Modules.push_back(pModule);

			if (!result)
				return result;
		}

		return result;
	}

	Result ServerConfigJson::LoadGenericServer(const Json::Value& nodeObject, ServerConfig::GenericServer* pServer)
	{
		auto result = ParseGenericServer(nodeObject, pServer);
		if (!result) return result;

		result = LoadChildModules(nodeObject, pServer);
		if (!result) return result;

		return result;
	}

	Result ServerConfigJson::LoadDBInstances(const Json::Value& rootObject, Array<ServerConfig::DBInstance*>& dbInstances)
	{
		Json::Value DBInstanceArray(Json::arrayValue);
		DBInstanceArray = rootObject.get("DBInstance", DBInstanceArray);
		if (!DBInstanceArray.isArray() || DBInstanceArray.size() == 0)
			return ResultCode::SUCCESS;

		Result result;
		for (auto& itInstance : DBInstanceArray)
		{
			if (!itInstance.isObject())
				continue;

			auto pDBInstance = new(GetHeap()) ServerConfig::DBInstance;
			result = ParseDBInstance(itInstance, pDBInstance);
			if (pDBInstance != nullptr)
				dbInstances.push_back(pDBInstance);

			if (!result)
				return result;
		}

		return result;
	}

	Result ServerConfigJson::LoadDBClusters(const Json::Value& rootObject, Array<ServerConfig::DBCluster*>& dbClusters)
	{
		Json::Value DBClusterArray(Json::arrayValue);
		DBClusterArray = rootObject.get("DBCluster", DBClusterArray);
		if (!DBClusterArray.isArray() || DBClusterArray.size() == 0)
			return ResultCode::SUCCESS;

		Result result;
		for (auto& itCluster : DBClusterArray)
		{
			if (!itCluster.isObject())
				continue;

			ServerConfig::DBCluster* pDBCluster = nullptr;
			pDBCluster = new(GetHeap()) ServerConfig::DBCluster;
			result = ParseDBCluster(itCluster, pDBCluster);
			if (pDBCluster != nullptr)
				dbClusters.push_back(pDBCluster);

			if (!result)
				return result;
		}

		return result;
	}

	Result ServerConfigJson::LoadJsonConfig(const Json::Value& rootObject, ServerConfig::ServerService* pServer)
	{
		Result result;

		auto gameClusterID = rootObject.get("GameClusterId", Json::Value("DefaultGame"));
		pServer->GameClusterName = gameClusterID.asCString();
		pServer->GameClusterID = gameClusterID.asCString();

        auto objectDirectory = rootObject.get("ObjectDirectory", Json::Value(""));
        pServer->ObjectDirectory = objectDirectory.asCString();

        auto objectDirectory2 = rootObject.get("ObjectDirectory2", Json::Value(""));
        pServer->ObjectDirectory2 = objectDirectory2.asCString();

        auto ObjectDirectoryAccessKey = rootObject.get("ObjectDirectoryAccessKey", Json::Value(""));
        pServer->ObjectDirectoryAccessKey = ObjectDirectoryAccessKey.asCString();

		result = ParseDataCenter(rootObject, "DataCenter", pServer->DataCenter);
		if (!result)
			return result;

		result = ParseMessageEndpoint(rootObject, "ServerEndpoint", pServer->ServerEndpointAddress);
		if (!result)
			return result;

		auto logFilePath = rootObject.get("LogFilePath", Json::Value(""));
		pServer->LogFilePath = logFilePath.asCString();

		auto logServer = rootObject.get("LogServer", Json::Value(""));
		pServer->LogServer = logServer.asCString();

        auto STUNServer = rootObject.get("STUNServer", Json::Value(""));
        pServer->STUNServer = STUNServer.asCString();

		auto dataPath = rootObject.get("DataPath", Json::Value(""));
		pServer->DataPath = dataPath.asCString();

        auto SteamAppId = rootObject.get("SteamAppId", Json::Value(0));
        pServer->SteamAppId = SteamAppId.asUInt64();

        auto SteamAPIKey = rootObject.get("SteamAPIKey", Json::Value(""));
        pServer->SteamAPIKey = SteamAPIKey.asCString();

		result = LoadDBInstances(rootObject, pServer->DBInstances);
		if (!result)
			return result;

		result = LoadDBClusters(rootObject, pServer->DBClusters);
		if (!result)
			return result;

		auto monitoringServer = rootObject.get("MonitoringServer", Json::Value(Json::nullValue));
		if (!monitoringServer.isNull())
		{
			pServer->MonitoringServer = new(GetHeap()) ServerConfig::GenericServer;
			result = LoadGenericServer(monitoringServer, pServer->MonitoringServer);
			if (!result)
				return result;
		}

		result = LoadGenericServer(rootObject, pServer);
		if (!result)
			return result;

		return result;
	}

	Result ServerConfigJson::LoadConfig(const String& configFilePath, ServerConfig::ServerService* pServerConfig)
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
            printf("[Error] ServerConfigJson::LoadConfig value parsing error:%s", errs.c_str());
			return ResultCode::INVALID_STR_DATA;
		}


		return LoadJsonConfig(jsonValue, pServerConfig);
	}





}



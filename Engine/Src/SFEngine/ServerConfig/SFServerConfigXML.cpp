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
#include "SFServerConfigXML.h"
#include "String/SFStringCrc32.h"

#include <libxml/parser.h>
#include <libxml/tree.h>



namespace SF
{

	ServerConfigXML::ServerConfigXML(ServerConfig& config)
		: m_Config(config)
	{
		
	}

	ServerConfigXML::~ServerConfigXML()
	{
	}

	template<class Func>
	Result ServerConfigXML::ForeachElement(xmlNode* pNode, Func func)
	{
		xmlNode *cur_node = nullptr;
		Result result;

		for (cur_node = pNode; cur_node; cur_node = cur_node->next)
		{
			if (cur_node->type != XML_ELEMENT_NODE)
				continue;

			Result result = func(cur_node);
			if (!result)
				break;
		}

		return result;
	}

	bool ServerConfigXML::ParseXMLBool(const char* value)
	{
		if (value == nullptr) return false;
		switch (Crc32C(value))
		{
		case "true"_crc:
		case "1"_crc:
			return true;
		}

		return false;
	}

	Result ServerConfigXML::ParseXMLNetPrivate(xmlNode* pNode, ServerConfig::NetPrivate& privateNet)
	{
		auto IP = (const char*)xmlGetProp(pNode, (xmlChar*)"IP");
		auto Port = (const char*)xmlGetProp(pNode, (xmlChar*)"Port");

		privateNet.IP = String(GetHeap(), IP);
		privateNet.Port = atoi(Port);

		return ResultCode::SUCCESS;
	}

	Result ServerConfigXML::ParseXMLNetPublic(xmlNode* pNode, ServerConfig::NetPublic& publicNet)
	{
		auto IPV4 = (const char*)xmlGetProp(pNode, (xmlChar*)"IPV4");
		auto IPV6 = (const char*)xmlGetProp(pNode, (xmlChar*)"IPV6");
		auto ListenIP = (const char*)xmlGetProp(pNode, (xmlChar*)"ListenIP");
		auto Port = (const char*)xmlGetProp(pNode, (xmlChar*)"Port");
		auto MaxConnection = (const char*)xmlGetProp(pNode, (xmlChar*)"MaxConnection");

		publicNet.IPV4 = String(GetHeap(), IPV4);
		publicNet.IPV6 = String(GetHeap(), IPV6);
		publicNet.ListenIP = String(GetHeap(), ListenIP);
		publicNet.Port = atoi(Port);
		if(MaxConnection != nullptr)
			publicNet.MaxConnection = atoi(MaxConnection);

		return ResultCode::SUCCESS;
	}

	Result ServerConfigXML::ParseXMLGenericServer(xmlNode* pNode, ServerConfig::GenericServer* pGenericServer)
	{
		auto UID = (const char*)xmlGetProp(pNode, (xmlChar*)"UID");
		auto WorkerThreadCount = (const char*)xmlGetProp(pNode, (xmlChar*)"WorkerThreadCount");
		auto NetIOThreadCount = (const char*)xmlGetProp(pNode, (xmlChar*)"NetIOThreadCount");
		auto Name = (const char*)xmlGetProp(pNode, (xmlChar*)"Name");
		auto Executable = (const char*)xmlGetProp(pNode, (xmlChar*)"Executable");
		const String privateNetString = String(GetHeap(), "NetPrivate");

		pGenericServer->UID = atoi(UID);
		if(WorkerThreadCount != nullptr)
			pGenericServer->WorkerThreadCount = atoi(WorkerThreadCount);
		if(NetIOThreadCount != nullptr)
			pGenericServer->NetIOThreadCount = atoi(NetIOThreadCount);
		pGenericServer->Name = String(GetHeap(), Name);
		pGenericServer->Executable = String(GetHeap(), Executable);

		Result result = ForeachElement(pNode->children, [&](xmlNode* pCurNode)
		{
			if (privateNetString == (const char*)pCurNode->name)
				return ParseXMLNetPrivate(pCurNode, pGenericServer->PrivateNet);
			else
			{
				ServerConfig::ServerModule* pServerModule = nullptr;
				auto result = ParseXMLModule(pCurNode, pServerModule);
				if (result)
				{
					if (pServerModule != nullptr)
						pGenericServer->Modules.push_back(pServerModule);
				}
			}

			return ResultCode::SUCCESS;
		});

		return result;
	}


	Result ServerConfigXML::ParseXMLDBInstance(xmlNode* pNode, ServerConfig::DBInstance* &pDBInstance)
	{
		auto InstanceName = (const char*)xmlGetProp(pNode, (xmlChar*)"InstanceName");
		auto ConnectionString = (const char*)xmlGetProp(pNode, (xmlChar*)"ConnectionString");
		auto UserID = (const char*)xmlGetProp(pNode, (xmlChar*)"UserID");
		auto Password = (const char*)xmlGetProp(pNode, (xmlChar*)"Password");

		if (InstanceName == nullptr
			|| ConnectionString == nullptr
			|| UserID == nullptr
			|| Password == nullptr)
			return ResultCode::INVALID_VALUE;

		pDBInstance = new(GetHeap()) ServerConfig::DBInstance(GetHeap());
		pDBInstance->InstanceName = String(GetHeap(), InstanceName);
		pDBInstance->ConnectionString = String(GetHeap(), ConnectionString);
		pDBInstance->UserID = String(GetHeap(), UserID);
		pDBInstance->Password = String(GetHeap(), Password);

		return ResultCode::SUCCESS;
	}

	Result ServerConfigXML::ParseXMLDBCluster(xmlNode* pNode, ServerConfig::DBCluster* &pDBCluster)
	{
		auto ClusterName = (const char*)xmlGetProp(pNode, (xmlChar*)"ClusterName");
		auto ClusterType = (const char*)xmlGetProp(pNode, (xmlChar*)"ClusterType");
		auto DBInstanceName = (const char*)xmlGetProp(pNode, (xmlChar*)"DBInstanceName");
		auto DBName = (const char*)xmlGetProp(pNode, (xmlChar*)"DBName");

		if (DBInstanceName == nullptr
			|| DBName == nullptr)
			return ResultCode::INVALID_VALUE;

		pDBCluster = new(GetHeap()) ServerConfig::DBCluster(GetHeap());
		pDBCluster->ClusterName = String(GetHeap(), ClusterName);
		pDBCluster->DBInstanceName = String(GetHeap(), DBInstanceName);
		pDBCluster->DBName = String(GetHeap(), DBName);
		if(ClusterType != nullptr)
			pDBCluster->ClusterType = Enum<DBClusterType>().GetValue(ClusterType);

		return ResultCode::SUCCESS;
	}

	Result ServerConfigXML::ParseXMLModule(xmlNode* pNode, ServerConfig::ServerModule* &pServerModule)
	{
		Result result;

		switch (Crc32C((const char*)pNode->name))
		{
		case "ModMatching_Game_8"_crc:
			pServerModule = new(GetHeap()) ServerConfig::ServerModuleMatching_8(GetHeap());
			((ServerConfig::ServerModuleMatching_8*)pServerModule)->UseBot = ParseXMLBool((const char*)xmlGetProp(pNode, (xmlChar*)"UseBot"));
			break;
		case "ModMatching_Game_4"_crc:
			pServerModule = new(GetHeap()) ServerConfig::ServerModuleMatching_4(GetHeap());
			((ServerConfig::ServerModuleMatching_4*)pServerModule)->UseBot = ParseXMLBool((const char*)xmlGetProp(pNode, (xmlChar*)"UseBot"));
			break;
		case "ModPurchaseValidateGoogle"_crc:
		{
			auto pGoogleValidate = new(GetHeap()) ServerConfig::ServerModuleGooglePurchaseValidate(GetHeap());
			pServerModule = pGoogleValidate;

			pGoogleValidate->Account = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"Account"));
			pGoogleValidate->P12KeyFile = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"P12KeyFile"));
			pGoogleValidate->AuthScopes = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"AuthScopes"));
			break;
		}
		case "ModPurchaseValidateIOS"_crc:
			pServerModule = new(GetHeap()) ServerConfig::ServerModuleIOSPurchaseValidate(GetHeap());
			((ServerConfig::ServerModuleIOSPurchaseValidate*)pServerModule)->URL = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"URL"));
			((ServerConfig::ServerModuleIOSPurchaseValidate*)pServerModule)->AltURL = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"AltURL"));
			break;
		case "ModLogin"_crc:
			pServerModule = new(GetHeap()) ServerConfig::ServerModulePublicService(GetHeap());
			result = ForeachElement(pNode->children, [&](xmlNode* pChild)
			{
				if(StringCrc32((const char*)pChild->name) == "NetPublic")
					return ParseXMLNetPublic(pChild, ((ServerConfig::ServerModulePublicService*)pServerModule)->PublicNet);

				return ResultCode::SUCCESS;
			});
			break;

		case "ModGame"_crc:
			pServerModule = new(GetHeap()) ServerConfig::ServerModulePublicService(GetHeap());
			result = ForeachElement(pNode->children, [&](xmlNode* pChild)
			{
				if (StringCrc32((const char*)pChild->name) == "NetPublic"_crc32c)
					return ParseXMLNetPublic(pChild, ((ServerConfig::ServerModulePublicService*)pServerModule)->PublicNet);

				return ResultCode::SUCCESS;
			});
			break;

		case "ModGameInstanceManager"_crc:
		{
			auto pInstanceManagerConfig = new(GetHeap()) ServerConfig::ServerModuleGameInstanceManager(GetHeap());
			pServerModule = pInstanceManagerConfig;

			pInstanceManagerConfig->Name = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"Name"));
			pInstanceManagerConfig->DataTable = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"DataTable"));

			result = ForeachElement(pNode->children, [&](xmlNode* pChild)
				{
					if (StringCrc32((const char*)pChild->name) == "NetPublic"_crc32c)
						return ParseXMLNetPublic(pChild, pInstanceManagerConfig->PublicNet);

					return ResultCode::SUCCESS;
				});
			break;
		}

		case "ModRelay"_crc:
			pServerModule = new(GetHeap()) ServerConfig::ServerModuleRelayService(GetHeap());
			result = ForeachElement(pNode->children, [&](xmlNode* pChild)
			{
				if (StringCrc32((const char*)pChild->name) == "NetPublic"_crc32c)
					return ParseXMLNetPublic(pChild, ((ServerConfig::ServerModulePublicService*)pServerModule)->PublicNet);

				return ResultCode::SUCCESS;
			});
			{
				auto MaximumRelayInstances = (const char*)xmlGetProp(pNode, (xmlChar*)"MaximumRelayInstances");
				if (MaximumRelayInstances != nullptr)
				{
					((ServerConfig::ServerModuleRelayService*)pServerModule)->MaximumRelayInstances = atoi(MaximumRelayInstances);

				}
			}
			break;
		case "NetPrivate"_crc:
			// Skip these They are not module
			return ResultCode::SUCCESS;
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
			pServerModule = new(GetHeap()) ServerConfig::ServerModule(GetHeap());
			break;
		default:
			return ResultCode::UNEXPECTED;
		}

		if(pServerModule != nullptr)
			pServerModule->ModuleName = String(GetHeap(), (const char*)pNode->name);

		return result;
	}

	Result ServerConfigXML::ParseXMLModuleServer(xmlNode* pNode, ServerConfig::ModuleServer* &pModuleServer)
	{
		pModuleServer = new(GetHeap()) ServerConfig::ModuleServer(GetHeap());
		auto result = ParseXMLGenericServer(pNode, pModuleServer);
		assert(result);

		return result;
	}


	Result ServerConfigXML::ParseXMLServerComponent(xmlNode* pNode, ServerConfig::ServerComponent* &pServerComponent)
	{
		switch (Crc32C((const char*)pNode->name))
		{
		case "ComponentGoogle"_crc:
			pServerComponent = new(GetHeap()) ServerConfig::ServerComponentGoogle(GetHeap());
			((ServerConfig::ServerComponentGoogle*)pServerComponent)->Account = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"Account"));
			((ServerConfig::ServerComponentGoogle*)pServerComponent)->P12KeyFile = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"P12KeyFile"));
			((ServerConfig::ServerComponentGoogle*)pServerComponent)->AuthScopes = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"AuthScopes"));
			break;
		case "ComponentIOS"_crc:
			pServerComponent = new(GetHeap()) ServerConfig::ServerComponentIOS(GetHeap());
			((ServerConfig::ServerComponentIOS*)pServerComponent)->URL = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"URL"));
			((ServerConfig::ServerComponentIOS*)pServerComponent)->AltURL = String(GetHeap(), (const char*)xmlGetProp(pNode, (xmlChar*)"AltURL"));
			break;
		case "NetPrivate"_crc:
		case "NetPublic"_crc:
			break;
		default:
			return ResultCode::NOT_IMPLEMENTED;
		}

		if (pServerComponent != nullptr)
			pServerComponent->ComponentName = (const char*)pNode->name;

		return ResultCode::SUCCESS;
	}


	Result ServerConfigXML::ParseXMLGameServer(xmlNode* pNode, ServerConfig::GameServer* &pGameServer)
	{
		pGameServer = new(GetHeap()) ServerConfig::GameServer(GetHeap());
		auto result = ParseXMLGenericServer(pNode, pGameServer);
		assert(result);

		return result;
	}


	Result ServerConfigXML::ParseXMLGameInstanceServer(xmlNode* pNode, ServerConfig::GameInstanceServer* &pGameInstanceServer)
	{
		pGameInstanceServer = new(GetHeap()) ServerConfig::GameInstanceServer(GetHeap());
		auto result = ParseXMLGenericServer(pNode, pGameInstanceServer);
		unused(result);
		assert(result);

		return ResultCode::SUCCESS;
	}


	Result ServerConfigXML::ParseXMLGameCluster(xmlNode* pNode, ServerConfig::GameCluster* &pGameCluster)
	{
		pGameCluster = new(GetHeap()) ServerConfig::GameCluster(GetHeap());

		pGameCluster->SetGameClusterID( (const char*)xmlGetProp(pNode, (xmlChar*)"GameID") );

		Result result;
		// Loop all child nodes
		result = ForeachElement(pNode->children, [&](xmlNode* pChild)
		{
			SFLog(System, Info, "Element, name: {0}\n", (const char*)pChild->name);

			switch (Crc32C((const char*)pChild->name))
			{
			case "GameDB"_crc:
			case "GameTransactionLogDB"_crc:
			{
				ServerConfig::DBCluster *pDBCluster = nullptr;
				result = ParseXMLDBCluster(pChild, pDBCluster);
				if (pDBCluster != nullptr)
				{
					pDBCluster->pGameCluster = pGameCluster;
					pGameCluster->DBClusters.push_back(pDBCluster);
				}
			}
				break;
			case "ModuleServer"_crc:
			{
				ServerConfig::ModuleServer* pModuleServer = nullptr;
				result = ParseXMLModuleServer(pChild, pModuleServer);
				if (pModuleServer != nullptr)
				{
					pModuleServer->pGameCluster = pGameCluster;
					pGameCluster->ModuleServers.push_back(pModuleServer);
				}
			}
			break;
			case "Game"_crc:
			{
				ServerConfig::GameServer* pServer = nullptr;
				result = ParseXMLGameServer(pChild, pServer);
				if (pServer != nullptr)
				{
					pServer->pGameCluster = pGameCluster;
					pGameCluster->GameServers.push_back(pServer);
				}
			}
			break;
			case "GameInstance"_crc:
			{
				ServerConfig::GameInstanceServer* pServer = nullptr;
				result = ParseXMLGameInstanceServer(pChild, pServer);
				if (pServer != nullptr)
				{
					pServer->pGameCluster = pGameCluster;
					pGameCluster->GameInstanceServers.push_back(pServer);
				}
			}
			break;
			}

			return result;
		});

		return result;
	}



	Result ServerConfigXML::ParseXMLServers(xmlNode* pNode)
	{
		Result result;
		// Loop all child nodes
		result = ForeachElement(pNode, [&](xmlNode* pCurNode)
		{

			SFLog(System, Info, "Element, name: {0}\n", (const char*)pCurNode->name);

			switch (Crc32C((const char*)pCurNode->name))
			{
			case "DBInstances"_crc:
			{
				ServerConfig::DBInstance* pDBInstance = nullptr;
				result = ParseXMLDBInstance(pCurNode, pDBInstance);
				if (result)
					m_Config.GetDBInstances().push_back(pDBInstance);
			}
			break;
			case "TableDB"_crc:
			case "AccountDB"_crc:
			case "LoginSessionDB"_crc:
			case "RankingDB"_crc:
			{
				ServerConfig::DBCluster* pDBCluster = nullptr;
				result = ParseXMLDBCluster(pCurNode, pDBCluster);
				if (result)
				{
					m_Config.GetDBClusters().push_back(pDBCluster);
				}
			}
			break;
			case "EntityServer"_crc: // Sore as a module server
			case "ModuleServer"_crc:
			{
				ServerConfig::ModuleServer* pModuleServer = nullptr;
				result = ParseXMLModuleServer(pCurNode, pModuleServer);
				m_Config.GetServers().push_back(pModuleServer);
			}
			break;
			case "GameCluster"_crc:
			{
				ServerConfig::GameCluster* pGameCluster = nullptr;
				result = ParseXMLGameCluster(pCurNode, pGameCluster);
				m_Config.GetGameClusters().push_back(pGameCluster);
			}
			break;
			}

			return result;
		});

		return result;
	}





	// Load config xml
	Result ServerConfigXML::LoadConfig(const char* configFilePath)
	{
		xmlDoc *doc = nullptr;
		xmlNode *root_element = nullptr;
		Result result;


		m_Config.Clear();

		/*parse the file and get the DOM */
		doc = xmlReadFile(configFilePath, nullptr, 0);

		if (doc == nullptr)
		{
			SFLog(System, Error, "Could not parse file {0}", configFilePath);
			return ResultCode::FAIL;
		}

		root_element = xmlDocGetRootElement(doc);

		if (!StrUtil::StringCompair((char*)root_element->name, -1, "Servers", -1))
		{
			SFLog(System, Error, "Invalid root node: {0}", (const char*)root_element->name);
			return ResultCode::FAIL;
		}

		result = ParseXMLServers(root_element->children);


		xmlFreeDoc(doc);
		xmlCleanupParser();

		return result;
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////
	////	Node setting xml generation
	////


	//xmlNode* ServerConfigXML::ToXMLNetPrivate(xmlNode* pParent, const ServerConfig::NetPrivate& privateNet) const
	//{
	//	const xmlChar* NodeName = (xmlChar*)"NetPrivate";
	//	auto newNode = pParent == nullptr ? 
	//						xmlNewNode(nullptr, NodeName) :
	//						xmlNewChild(pParent, nullptr, NodeName, nullptr);
	//	if (newNode == nullptr) return nullptr;

	//	String localBuffer(GetHeap());
	//	localBuffer.Format("{0}", privateNet.Port);
	//	xmlNewProp(newNode, (const xmlChar*)"IP", reinterpret_cast<const xmlChar*>((const char*)privateNet.IP));
	//	xmlNewProp(newNode, (const xmlChar*)"Port", reinterpret_cast<const xmlChar*>((const char*)localBuffer));

	//	return newNode;
	//}

	//xmlNode* ServerConfigXML::ToXMLNetPublic(xmlNode* pParent, const ServerConfig::NetPublic& publicNet) const
	//{
	//	const xmlChar* NodeName = (xmlChar*)"NetPublic";
	//	auto newNode = pParent == nullptr ?
	//		xmlNewNode(nullptr, NodeName) :
	//		xmlNewChild(pParent, nullptr, NodeName, nullptr);
	//	if (newNode == nullptr) return nullptr;

	//	String localBuffer(GetHeap());
	//	localBuffer.Format("{0}", publicNet.Port);

	//	String localBufferMaxConnection(GetHeap());
	//	localBufferMaxConnection.Format("{0}", publicNet.MaxConnection);

	//	xmlNewProp(newNode, (const xmlChar*)"IPV4", reinterpret_cast<const xmlChar*>((const char*)publicNet.IPV4));
	//	xmlNewProp(newNode, (const xmlChar*)"IPV6", reinterpret_cast<const xmlChar*>((const char*)publicNet.IPV6));
	//	xmlNewProp(newNode, (const xmlChar*)"ListenIP", reinterpret_cast<const xmlChar*>((const char*)publicNet.ListenIP));
	//	xmlNewProp(newNode, (const xmlChar*)"Port", reinterpret_cast<const xmlChar*>((const char*)localBuffer));
	//	xmlNewProp(newNode, (const xmlChar*)"MaxConnection", reinterpret_cast<const xmlChar*>((const char*)localBufferMaxConnection));

	//	return newNode;
	//}

	//xmlNode* ServerConfigXML::ToXMLGenericServer(const char* nodeName, const ServerConfig::GenericServer* pGenericServer) const
	//{
	//	auto newNode = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>(nodeName));
	//	if (newNode == nullptr) return nullptr;

	//	String localBuffer(GetHeap());
	//	localBuffer.Format("{0}", pGenericServer->UID);
	//	xmlNewProp(newNode, (const xmlChar*)"UID", reinterpret_cast<const xmlChar*>((const char*)localBuffer));
	//	xmlNewProp(newNode, (const xmlChar*)"Name", reinterpret_cast<const xmlChar*>((const char*)pGenericServer->Name));

	//	auto netPrivate = ToXMLNetPrivate(newNode, pGenericServer->PrivateNet);
	//	if (netPrivate == nullptr)
	//	{
	//		xmlFreeNode(newNode);
	//		return nullptr;
	//	}
	//	return newNode;
	//}

	//xmlNode* ServerConfigXML::ToXMLDBInstance(const ServerConfig::DBInstance* pDBInstance) const
	//{
	//	auto newNode = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>("DBInstances"));
	//	if (newNode == nullptr) return nullptr;

	//	xmlNewProp(newNode, (const xmlChar*)"InstanceName", reinterpret_cast<const xmlChar*>((const char*)pDBInstance->InstanceName));
	//	xmlNewProp(newNode, (const xmlChar*)"ConnectionString", reinterpret_cast<const xmlChar*>((const char*)pDBInstance->ConnectionString));
	//	xmlNewProp(newNode, (const xmlChar*)"UserID", reinterpret_cast<const xmlChar*>((const char*)pDBInstance->UserID));
	//	xmlNewProp(newNode, (const xmlChar*)"Password", reinterpret_cast<const xmlChar*>((const char*)pDBInstance->Password));

	//	return newNode;
	//}

	//xmlNode* ServerConfigXML::ToXMLDBCluster(const ServerConfig::DBCluster* pDBCluster) const
	//{
	//	auto newNode = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>("DBInstances"));
	//	if (newNode == nullptr) return nullptr;

	//	xmlNewProp(newNode, (const xmlChar*)"ClusterType", reinterpret_cast<const xmlChar*>(Enum<DBClusterType>().GetValueName(pDBCluster->ClusterType)));
	//	xmlNewProp(newNode, (const xmlChar*)"DBInstanceName", reinterpret_cast<const xmlChar*>((const char*)pDBCluster->DBInstanceName));
	//	xmlNewProp(newNode, (const xmlChar*)"DBName", reinterpret_cast<const xmlChar*>((const char*)pDBCluster->DBName));

	//	return newNode;
	//}

	//xmlNode* ServerConfigXML::ToXMLModule(const ServerConfig::ServerModule* pServerModule) const
	//{
	//	auto newNode = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>((const char*)pServerModule->ModuleName));
	//	if (newNode == nullptr) return nullptr;

	//	switch (Crc32C(pServerModule->ModuleName))
	//	{
	//	case "ModMatchingQueue_Game_8x1"_crc:	
	//	case "ModMatchingQueue_Game_8x2"_crc:	
	//	case "ModMatchingQueue_Game_8x3"_crc:	
	//	case "ModMatchingQueue_Game_8x4"_crc:	
	//	case "ModMatchingQueue_Game_8x5"_crc:	
	//	case "ModMatchingQueue_Game_8x6"_crc:	
	//	case "ModMatchingQueue_Game_8x7"_crc:	
	//	case "ModMatchingQueue_Game_8x1S"_crc:	
	//	case "ModMatchingQueue_Game_8x1W"_crc:	
	//	case "ModMatchingQueue_Game_4x1"_crc:	
	//	case "ModMatchingQueue_Game_4x2"_crc:	
	//	case "ModMatchingQueue_Game_4x3"_crc:	
	//	case "ModMatchingQueue_Game_4x1S"_crc:	
	//	case "ModMatchingQueue_Game_4x1W"_crc:	
	//	case "ModGamePartyManager"_crc:
	//	case "ModMonitoring"_crc:
	//	case "ModRanking"_crc:
	//		// The don't have things
	//		break;
	//	case "NetPrivate"_crc:
	//		// ignore
	//		break;
	//	case "ModMatching_Game_8"_crc:
	//	{
	//		auto pModule = static_cast<const ServerConfig::ServerModuleMatching_8*>(pServerModule);
	//		xmlNewProp(newNode, (const xmlChar*)"UseBot", reinterpret_cast<const xmlChar*>(pModule->UseBot ? "true" : "false"));
	//	}
	//	break;
	//	case "ModMatching_Game_4"_crc:
	//	{
	//		auto pModule = static_cast<const ServerConfig::ServerModuleMatching_4*>(pServerModule);
	//		xmlNewProp(newNode, (const xmlChar*)"UseBot", reinterpret_cast<const xmlChar*>(pModule->UseBot ? "true" : "false"));
	//	}
	//		break;
	//	case "ModPurchaseValidateGoogle"_crc:
	//	{
	//		auto pModule = static_cast<const ServerConfig::ServerModuleGooglePurchaseValidate*>(pServerModule);
	//		xmlNewProp(newNode, (const xmlChar*)"Account", reinterpret_cast<const xmlChar*>((const char*)pModule->Account));
	//		xmlNewProp(newNode, (const xmlChar*)"P12KeyFile", reinterpret_cast<const xmlChar*>((const char*)pModule->P12KeyFile));
	//		xmlNewProp(newNode, (const xmlChar*)"AuthScopes", reinterpret_cast<const xmlChar*>((const char*)pModule->AuthScopes));
	//	}
	//		break;
	//	case "ModPurchaseValidateIOS"_crc:
	//	{
	//		auto pModule = static_cast<const ServerConfig::ServerModuleIOSPurchaseValidate*>(pServerModule);
	//		xmlNewProp(newNode, (const xmlChar*)"URL", reinterpret_cast<const xmlChar*>((const char*)pModule->URL));
	//		xmlNewProp(newNode, (const xmlChar*)"AltURL", reinterpret_cast<const xmlChar*>((const char*)pModule->AltURL));
	//	}
	//		break;
	//	case "ModLogin"_crc:
	//	{
	//		auto pModule = static_cast<const ServerConfig::ServerModulePublicService*>(pServerModule);
	//		ToXMLNetPublic(newNode, pModule->PublicNet);
	//	}
	//	break;
	//	case "ModGame"_crc:
	//	{
	//		auto pModule = static_cast<const ServerConfig::ServerModulePublicService*>(pServerModule);
	//		ToXMLNetPublic(newNode, pModule->PublicNet);
	//	}
	//	break;
	//	default:
	//		return nullptr;
	//	}

	//	return nullptr;
	//}

	//xmlNode* ServerConfigXML::ToXMLServerComponent(const ServerConfig::ServerComponent* pServerComponent) const
	//{
	//	auto newNode = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>((const char*)pServerComponent->ComponentName));
	//	if (newNode == nullptr) return nullptr;

	//	switch (Crc32C(pServerComponent->ComponentName))
	//	{
	//	case "ComponentGoogle"_crc:
	//		{
	//			auto pComponent = static_cast<const ServerConfig::ServerComponentGoogle*>(pServerComponent);
	//			xmlNewProp(newNode, (const xmlChar*)"Account", reinterpret_cast<const xmlChar*>((const char*)pComponent->Account));
	//			xmlNewProp(newNode, (const xmlChar*)"P12KeyFile", reinterpret_cast<const xmlChar*>((const char*)pComponent->P12KeyFile));
	//			xmlNewProp(newNode, (const xmlChar*)"AuthScopes", reinterpret_cast<const xmlChar*>((const char*)pComponent->AuthScopes));
	//		}
	//		break;
	//	case "ComponentIOS"_crc:
	//		{
	//			auto pComponent = static_cast<const ServerConfig::ServerComponentIOS*>(pServerComponent);
	//			xmlNewProp(newNode, (const xmlChar*)"URL", reinterpret_cast<const xmlChar*>((const char*)pComponent->URL));
	//			xmlNewProp(newNode, (const xmlChar*)"AltURL", reinterpret_cast<const xmlChar*>((const char*)pComponent->AltURL));
	//		}
	//		break;
	//	default:
	//		xmlFreeNode(newNode);
	//		assert(false);
	//		return nullptr;
	//	}

	//	return newNode;
	//}

	//xmlNode* ServerConfigXML::ToXMLGameServer(const ServerConfig::GameServer* pGameServer) const
	//{
	//	//auto newNode = ToXML
	//	return nullptr;
	//}

	//xmlNode* ServerConfigXML::ToXMLGameInstanceServer(const ServerConfig::GameInstanceServer* pGameInstanceServer) const
	//{
	//	return nullptr;
	//}




}



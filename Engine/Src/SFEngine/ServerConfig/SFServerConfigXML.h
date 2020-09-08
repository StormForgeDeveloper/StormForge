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

#include "String/SFStringCrc32.h"
#include "String/SFString.h"

#include "ZooKeeper/SFZooKeeper.h"
#include "ServerConfig/SFEnum.h"
#include "ServerConfig/SFServerConfig.h"

typedef struct _xmlNode xmlNode;


namespace SF
{

	class ServerConfigXML
	{
	public:


	private:

		ServerConfig& m_Config;

	private:

		template<class Func>
		Result ForeachElement(xmlNode* pNode, Func fucn);

		bool ParseXMLBool(const char* value);

		Result ParseXMLGameCluster(xmlNode* pNode, ServerConfig::GameCluster* &pGameCluster);


	public:

		// Constructor
		ServerConfigXML(ServerConfig& config);
		~ServerConfigXML();

		// Heap
		IHeap& GetHeap() const { return m_Config.GetHeap(); }

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Node parsing
		//

		Result ParseXMLNetPrivate(xmlNode* pNode, ServerConfig::NetPrivate& privateNet);
		Result ParseXMLNetPublic(xmlNode* pNode, ServerConfig::NetPublic& publicNet);

		Result ParseXMLGenericServer(xmlNode* pNode, ServerConfig::GenericServer* pGenericServer);


		Result ParseXMLDBInstance(xmlNode* pNode, ServerConfig::DBInstance* &pDBInstance);
		Result ParseXMLDBCluster(xmlNode* pNode, ServerConfig::DBCluster* &pDBCluster);

		Result ParseXMLModule(xmlNode* pNode, ServerConfig::ServerModule* &pServerModule);
		Result ParseXMLModuleServer(xmlNode* pNode, ServerConfig::ModuleServer* &pModuleServer);
		Result ParseXMLServerComponent(xmlNode* pNode, ServerConfig::ServerComponent* &pServerComponent);
		Result ParseXMLGameServer(xmlNode* pNode, ServerConfig::GameServer* &pGameServer);
		Result ParseXMLGameInstanceServer(xmlNode* pNode, ServerConfig::GameInstanceServer* &pGameInstanceServer);

		Result ParseXMLServers(xmlNode* pNode);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////
		////	Node setting xml generation
		////


		//xmlNode* ToXMLNetPrivate(xmlNode* pParent, const ServerConfig::NetPrivate& privateNet) const;
		//xmlNode* ToXMLNetPublic(xmlNode* pParent, const ServerConfig::NetPublic& publicNet) const;
		//xmlNode* ToXMLGenericServer(const char* nodeName, const ServerConfig::GenericServer* pGenericServer) const;

		//xmlNode* ToXMLDBInstance(const ServerConfig::DBInstance* pDBInstance) const;
		//xmlNode* ToXMLDBCluster(const ServerConfig::DBCluster* pDBCluster) const;
		//xmlNode* ToXMLModule(const ServerConfig::ServerModule* pServerModule) const;
		//xmlNode* ToXMLServerComponent(const ServerConfig::ServerComponent* pServerComponent) const;
		//xmlNode* ToXMLGameServer(const ServerConfig::GameServer* pGameServer) const;
		//xmlNode* ToXMLGameInstanceServer(const ServerConfig::GameInstanceServer* pGameInstanceServer) const;


		// Load config xml
		Result LoadConfig(const char* configFilePath);


	};
}


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : ServerConfig
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Util/SFLog.h"
#include "Zookeeper/SFZookeeper.h"

#ifdef USE_ZOOKEEPER
#include "ServerConfig//SFServerConfig.h"
#include "ServerConfig//SFServerConfigXML.h"
#include "ServerConfig//SFServerConfigZookeeper.h"


using namespace SF;


typedef void(*NATIVE_FOREACH_CB_FUNCTION)(ServerConfig::GenericServer* pGenericServer);



SFDLL_EXPORT void* SFServerConfig_NativeCreateConfig()
{
	auto pServerConfig = new(GetSystemHeap()) ServerConfig(GetSystemHeap());
	return pServerConfig;
}

SFDLL_EXPORT void SFServerConfig_NativeDestroyConfig(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return;

	auto pServerConfig = (ServerConfig*)nativeHandle;
	IHeap::Delete(pServerConfig);
}

SFDLL_EXPORT int SFServerConfig_NativeLoadXML(intptr_t nativeHandle, const char* filePath)
{
	if (nativeHandle == 0)
		return ResultCode::INVALID_ARG;

	auto pServerConfig = (ServerConfig*)nativeHandle;
	ServerConfigXML xmlLoader(*pServerConfig);
	return (int32_t)xmlLoader.LoadConfig(filePath);
}

SFDLL_EXPORT int SFServerConfig_NativeLoadZookeeper(intptr_t nativeHandle, intptr_t nativeHandleZK, const char* zkNodePath)
{
	if (nativeHandle == 0 || nativeHandleZK == 0)
		return ResultCode::INVALID_ARG;

	auto pServerConfig = (ServerConfig*)nativeHandle;
	auto pZKInstance = (Zookeeper*)nativeHandleZK;

	ServerConfigZookeeper zooKeeperLoader(*pServerConfig, *pZKInstance);
	return (int32_t)zooKeeperLoader.LoadConfig(zkNodePath);
}

SFDLL_EXPORT int SFServerConfig_NativeStoreZookeeper(intptr_t nativeHandle, intptr_t nativeHandleZK, const char* zkNodePath)
{
	if (nativeHandle == 0 || nativeHandleZK == 0)
		return ResultCode::INVALID_ARG;

	auto pServerConfig = (ServerConfig*)nativeHandle;
	auto pZKInstance = (Zookeeper*)nativeHandleZK;

	ServerConfigZookeeper zooKeeperLoader(*pServerConfig, *pZKInstance);
	return (int32_t)zooKeeperLoader.StoreConfig(zkNodePath);
}


SFDLL_EXPORT void SFServerConfig_NativeForEachServer(intptr_t nativeHandle, NATIVE_FOREACH_CB_FUNCTION foreachCB)
{
	if (nativeHandle == 0)
		return;

	auto pServerConfig = (ServerConfig*)nativeHandle;

	for (auto& itServer : pServerConfig->GetServers())
	{
		foreachCB(itServer);
	}

	for (auto& itCluster : pServerConfig->GetGameClusters())
	{
		for (auto& itServer : itCluster->ModuleServers)
		{
			foreachCB(itServer);
		}
		for (auto& itServer : itCluster->GameServers)
		{
			foreachCB(itServer);
		}
		for (auto& itServer : itCluster->GameInstanceServers)
		{
			foreachCB(itServer);
		}
	}
}



SFDLL_EXPORT const char* SFServerConfig_NetPrivate_NativeIP(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return nullptr;

	auto pObject = (ServerConfig::NetPrivate*)nativeHandle;
	return pObject->IP;
}

SFDLL_EXPORT int SFServerConfig_NetPrivate_NativePort(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pObject = (ServerConfig::NetPrivate*)nativeHandle;
	return pObject->Port;
}

SFDLL_EXPORT uint64_t SFServerConfig_GenericServer_NativeGameID(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pObject = (ServerConfig::GenericServer*)nativeHandle;
	return pObject->pGameCluster != nullptr ? pObject->pGameCluster->GameClusterID : nullptr;
}

SFDLL_EXPORT uint SFServerConfig_GenericServer_NativeUID(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pObject = (ServerConfig::GenericServer*)nativeHandle;
	return pObject->UID;
}

SFDLL_EXPORT const char* SFServerConfig_GenericServer_NativeName(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pObject = (ServerConfig::GenericServer*)nativeHandle;
	return pObject->Name;
}

SFDLL_EXPORT const char* SFServerConfig_GenericServer_NativeExecutable(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pObject = (ServerConfig::GenericServer*)nativeHandle;
	return pObject->Executable;
}

SFDLL_EXPORT ServerConfig::NetPrivate* SFServerConfig_GenericServer_NativePrivateNet(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pObject = (ServerConfig::GenericServer*)nativeHandle;
	return &pObject->PrivateNet;
}


#endif

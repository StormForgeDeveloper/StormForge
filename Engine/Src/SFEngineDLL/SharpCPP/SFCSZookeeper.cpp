////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Zookeeper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"
#include "Zookeeper/SFZookeeper.h"

#ifdef USE_ZOOKEEPER

using namespace SF;


typedef void(*NATIVE_GETCHILDREN_CB_FUNCTION)(const char* stringPtr);



SFDLL_EXPORT  int SFZookeeper_Const_NODE_FLAG_EPHEMERAL()
{
	return Zookeeper::NODE_FLAG_EPHEMERAL;
}

SFDLL_EXPORT  int SFZookeeper_Const_NODE_FLAG_SEQUENCE()
{
	return Zookeeper::NODE_FLAG_SEQUENCE;
}

SFDLL_EXPORT  int SFZookeeper_Const_STATE_SESSION_EXPIRED()
{
	return Zookeeper::STATE_SESSION_EXPIRED;
}

SFDLL_EXPORT  int SFZookeeper_Const_STATE_CONNECTED()
{
	return Zookeeper::STATE_CONNECTED;
}

SFDLL_EXPORT  int SFZookeeper_Const_STATE_CONNECTING()
{
	return Zookeeper::STATE_CONNECTING;
}

SFDLL_EXPORT  int SFZookeeper_Const_EVENT_CREATED()
{
	return Zookeeper::EVENT_CREATED;
}

SFDLL_EXPORT  int SFZookeeper_Const_EVENT_DELETED()
{
	return Zookeeper::EVENT_DELETED;
}

SFDLL_EXPORT  int SFZookeeper_Const_EVENT_CHANGED()
{
	return Zookeeper::EVENT_CHANGED;
}

SFDLL_EXPORT  int SFZookeeper_Const_EVENT_CHILD()
{
	return Zookeeper::EVENT_CHILD;
}

SFDLL_EXPORT  int SFZookeeper_Const_EVENT_SESSION()
{
	return Zookeeper::EVENT_SESSION;
}

SFDLL_EXPORT  int SFZookeeper_Const_EVENT_NO_WATCHING()
{
	return Zookeeper::EVENT_NO_WATCHING;
}




SFDLL_EXPORT void* SFZookeeper_NativeCreateZookeeper()
{
	auto pObject = new(GetSystemHeap()) Zookeeper(GetSystemHeap());
	return pObject;
}

SFDLL_EXPORT void SFZookeeper_NativeDestroyZookeeper(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	IHeap::Delete(pZKInstance);
}

SFDLL_EXPORT int SFZookeeper_NativeGetState(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	return pZKInstance->GetState();
}

SFDLL_EXPORT bool SFZookeeper_NativeIsConnected(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return false;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	return pZKInstance->IsConnected();
}

SFDLL_EXPORT bool SFZookeeper_NativeConnect(intptr_t nativeHandle, const char* connectionString)
{
	if (nativeHandle == 0)
		return false;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	return pZKInstance->Connect(connectionString);
}

SFDLL_EXPORT void SFZookeeper_NativeClose(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	pZKInstance->Close();
}

SFDLL_EXPORT bool SFZookeeper_NativeWaitForConnected(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return false;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	return pZKInstance->WaitForConnected();
}

SFDLL_EXPORT bool SFZookeeper_NativeWaitForDisconnected(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return false;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	return pZKInstance->WaitForDisconnected();
}

SFDLL_EXPORT int SFZookeeper_NativeCreateNode(intptr_t nativeHandle, const char* path, const char* nodeValue, int flags)
{
	if (nativeHandle == 0)
		return (int32_t)ResultCode::FAIL;

	auto pZKInstance = (Zookeeper*)nativeHandle;

	String outPath;
	if (!StrUtil::IsNullOrEmpty(nodeValue))
	{
		auto strLen = (uint)strlen(nodeValue) + 1;
		ArrayView<uint8_t> valueBuffer(strLen, strLen, (uint8_t*)nodeValue);
		return (int32_t)pZKInstance->Create(path, valueBuffer, nullptr, flags, outPath);
	}
	else
	{
		DynamicArray<uint8_t> valueBuffer(pZKInstance->GetHeap());
		return (int32_t)pZKInstance->Create(path, valueBuffer, nullptr, flags, outPath);
	}
}

SFDLL_EXPORT bool SFZookeeper_NativeExists(intptr_t nativeHandle, const char* path)
{
	if (nativeHandle == 0)
		return false;

	auto pZKInstance = (Zookeeper*)nativeHandle;

	return pZKInstance->Exists(path);
}

SFDLL_EXPORT const char* SFZookeeper_NativeGet(intptr_t nativeHandle, const char* path)
{
	if (nativeHandle == 0)
		return nullptr;

	auto pZKInstance = (Zookeeper*)nativeHandle;

	StaticArray<uint8_t, 1024> value(GetSystemHeap());
	pZKInstance->Get(path, value);

	// It's going to be treated as string. we need to add null terminate for safety
	if (value.size() > 0)
	{
		value.push_back(0);
		return (const char*)value.data();
	}

	return nullptr;
}



SFDLL_EXPORT int32_t SFZookeeper_NativeGetChildren(intptr_t nativeHandle, const char* path, NATIVE_GETCHILDREN_CB_FUNCTION func, int watch)
{
	if (nativeHandle == 0)
		return (int32_t)ResultCode::NOT_INITIALIZED;

	auto pZKInstance = (Zookeeper*)nativeHandle;

	DynamicArray<String> children(GetSystemHeap());
	pZKInstance->GetChildren(path, children, watch != 0);
	for (auto& itChild : children)
	{
		func(itChild);
	}

	return (int32_t)ResultCode::SUCCESS;
}

SFDLL_EXPORT int32_t SFZookeeper_NativeDeleteAllChildren(intptr_t nativeHandle, const char* path)
{
	if (nativeHandle == 0)
		return (int32_t)ResultCode::NOT_INITIALIZED;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	StaticArray<String, 1024> children(GetSystemHeap());
	pZKInstance->GetChildren(path, children);
	char tempPath[512];
	for (auto& itChild : children)
	{
		StrUtil::Format(tempPath, "{0}/{1}", path, itChild);
		pZKInstance->DeleteTree(tempPath);
	}
	return (int32_t)ResultCode::SUCCESS;
}

SFDLL_EXPORT int32_t SFZookeeper_NativeDequeueEvent(intptr_t nativeHandle, intptr_t& nodePath, int& state, int& eventType)
{
	if (nativeHandle == 0)
		return (int32_t)ResultCode::NOT_INITIALIZED;

	auto pZKInstance = (Zookeeper*)nativeHandle;
	Zookeeper::ZKEvent zkEvent;
	auto result = pZKInstance->DequeueEvent(zkEvent);
	if (result)
	{
		nodePath = (intptr_t)zkEvent.Components.NodePath.ToString();
		state = zkEvent.Components.State;
		eventType = zkEvent.Components.EventType;
	}

	return (int32_t)result;
}

#endif

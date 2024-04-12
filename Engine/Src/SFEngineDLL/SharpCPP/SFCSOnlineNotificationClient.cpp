////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : OnlineNotificationClient interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Util/SFLog.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"
#include "Net/SFConnection.h"
#include "Net/SFMessage.h"
#include "SFProtocol.h"
#include "Online/SFOnlineNotificationClient.h"
#include "Interfaces/Sharp/SFCSUtil.h"


using namespace SF;


namespace SF
{
    typedef void(*ON_ONLINE_API_DATA)(const char* eventName, const char* messageData);
}

//////////////////////////////////////////////////////////////////////////////////////
//
//	interfacing
//

SFDLL_EXPORT intptr_t SFOnlineNotificationClient_NativeCreate()
{
	auto pOnlineNotificationClient = NewObject<OnlineNotificationClient>(GetEngineHeap());
	Service::EngineObjectManager->AddToDetainedRelease(pOnlineNotificationClient.StaticCast<SharedObject>());

	return NativeObjectToIntptr(pOnlineNotificationClient.get());
}

SFDLL_EXPORT int32_t SFOnlineNotificationClient_NativeConnect(intptr_t nativeHandle, const char* url, const char* env, const char* accessKey)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineNotificationClient = NativeToObject<OnlineNotificationClient>(nativeHandle);

	return (int32_t)pOnlineNotificationClient->Connect(env, url, accessKey);
}

SFDLL_EXPORT void SFOnlineNotificationClient_NativeDisconnect(intptr_t nativeHandle)
{
    if (nativeHandle == 0)
        return;

    auto pOnlineNotificationClient = NativeToObject<OnlineNotificationClient>(nativeHandle);

    pOnlineNotificationClient->Disconnect();
}

SFDLL_EXPORT int32_t SFOnlineNotificationClient_IsConnected(intptr_t nativeHandle)
{
    if (nativeHandle == 0)
        return (int)ResultCode::NOT_INITIALIZED;

    auto pOnlineNotificationClient = NativeToObject<OnlineNotificationClient>(nativeHandle);

    return (int32_t)pOnlineNotificationClient->IsConnected();
}

SFDLL_EXPORT int32_t SFOnlineNotificationClient_NativeTickUpdate(intptr_t nativeHandle, ON_ONLINE_API_DATA onOnlineEventData)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineNotificationClient = NativeToObject<OnlineNotificationClient>(nativeHandle);

    auto& recvQueue = pOnlineNotificationClient->GetRecvQueue();
    OnlineNotificationClient::APIResult* result{};
    while (recvQueue.Dequeue(result))
    {
        if (result)
        {
            onOnlineEventData(result->APIName, result->ResultPayload);
            IHeap::Delete(result);
        }
    }

	return (int)ResultCode::SUCCESS;

}

SFDLL_EXPORT int32_t SFOnlineNotificationClient_NativeRequest(intptr_t nativeHandle, const char* APIName)
{
    if (nativeHandle == 0)
        return (int)ResultCode::NOT_INITIALIZED;

    auto pOnlineNotificationClient = NativeToObject<OnlineNotificationClient>(nativeHandle);

    return (int32_t)pOnlineNotificationClient->Request(APIName);
}


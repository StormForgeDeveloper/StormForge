////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : OnlineAPIClient interface
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
#include "Online/SFOnlineAPIClient.h"
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

SFDLL_EXPORT intptr_t SFOnlineAPIClient_NativeCreate()
{
	auto pOnlineAPIClient = NewObject<OnlineAPIClient>(GetEngineHeap());
	Service::EngineObjectManager->AddToDetainedRelease(pOnlineAPIClient.StaticCast<SharedObject>());

	return NativeObjectToIntptr(pOnlineAPIClient.get());
}

SFDLL_EXPORT int32_t SFOnlineAPIClient_NativeConnect(intptr_t nativeHandle, const char* url, const char* accessKey)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineAPIClient = NativeToObject<OnlineAPIClient>(nativeHandle);

	return (int32_t)pOnlineAPIClient->Connect(url, accessKey);
}

SFDLL_EXPORT void SFOnlineAPIClient_NativeDisconnect(intptr_t nativeHandle)
{
    if (nativeHandle == 0)
        return;

    auto pOnlineAPIClient = NativeToObject<OnlineAPIClient>(nativeHandle);

    pOnlineAPIClient->Disconnect();
}

SFDLL_EXPORT int32_t SFOnlineAPIClient_IsConnected(intptr_t nativeHandle)
{
    if (nativeHandle == 0)
        return (int)ResultCode::NOT_INITIALIZED;

    auto pOnlineAPIClient = NativeToObject<OnlineAPIClient>(nativeHandle);

    return (int32_t)pOnlineAPIClient->IsConnected();
}

SFDLL_EXPORT int32_t SFOnlineAPIClient_NativeTickUpdate(intptr_t nativeHandle, ON_ONLINE_API_DATA onOnlineEventData)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineAPIClient = NativeToObject<OnlineAPIClient>(nativeHandle);

    auto& recvQueue = pOnlineAPIClient->GetRecvQueue();
    OnlineAPIClient::APIResult* result{};
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

SFDLL_EXPORT int32_t SFOnlineAPIClient_NativeRequest(intptr_t nativeHandle, const char* APIName)
{
    if (nativeHandle == 0)
        return (int)ResultCode::NOT_INITIALIZED;

    auto pOnlineAPIClient = NativeToObject<OnlineAPIClient>(nativeHandle);

    return (int32_t)pOnlineAPIClient->Request(APIName);
}


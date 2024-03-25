////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
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
#include "Online/SFOnlineClient.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Actor/Movement/SFActorMovementManager.h"
#include "Interfaces/Sharp/SFCSUtil.h"


namespace SF
{
	typedef void(*ONLINE_STATECHANGED_CALLBACK)(OnlineClient::OnlineState prevState, OnlineClient::OnlineState newState);

}

using namespace SF;





//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT intptr_t SFOnlineClient_NativeCreateOnlineClient()
{
	auto pOnlineClient = NewObject<OnlineClient>(GetEngineHeap());
	Service::EngineObjectManager->AddToDetainedRelease(pOnlineClient.StaticCast<SharedObject>());

	return NativeObjectToIntptr(pOnlineClient.get());
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeStartConnection(intptr_t nativeHandle, uint64_t transactionId, const char* gameId, const char* loginAddress,
    const char* userId, const char* password)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return (int32_t)pOnlineClient->StartConnection(transactionId, gameId, loginAddress, 0, nullptr, nullptr, userId, password);
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeStartConnectionSteam(intptr_t nativeHandle, uint64_t transactionId, const char* gameId, const char* loginAddress,
    uint64_t steamUserId, const char* steamUserName, const char* steamUserToken)
{
    if (nativeHandle == 0)
        return (int)ResultCode::NOT_INITIALIZED;

    auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

    return (int32_t)pOnlineClient->StartConnection(transactionId, gameId, loginAddress, steamUserId, steamUserName, steamUserToken, nullptr, nullptr);
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeJoinGameInstance(intptr_t nativeHandle, uint64_t transactionId, uint32_t gameInstanceUID)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return (int32_t)pOnlineClient->JoinGameInstance(transactionId, gameInstanceUID);
}

SFDLL_EXPORT void SFOnlineClient_NativeDisconnectAll(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	pOnlineClient->DisconnectAll();
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeGetOnlineState(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return int32_t(pOnlineClient->GetOnlineState());
}

SFDLL_EXPORT const void* SFOnlineClient_NativeGetPlayerId(intptr_t nativeHandle)
{
    if (nativeHandle == 0)
        return nullptr;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return reinterpret_cast<const void*>(&pOnlineClient->GetPlayerID());
}

SFDLL_EXPORT const void* SFOnlineClient_NativeGetCharacterId(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return nullptr;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return reinterpret_cast<const void*>(&pOnlineClient->GetCharacterId());
}

SFDLL_EXPORT uint32_t SFOnlineClient_NativeGetActorId(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return (uint)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->GetActorID();
}

SFDLL_EXPORT uint32_t SFOnlineClient_NativeGetGameId(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return (uint)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return (uint32_t)(pOnlineClient->GetGameId());
}

SFDLL_EXPORT uint32_t SFOnlineClient_NativeGetGameInstanceUID(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->GetGameInstanceUID();
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeUpdateGameTick(intptr_t nativeHandle, 
	ONLINE_STATECHANGED_CALLBACK stateChangedCallback, 
	SET_EVENT_FUNCTION setEventFunc, 
	ON_MESSAGE_FUNCTION onMessageFunc, 
	OnlineClient::ONLINE_TASK_FINISHED_CALLBACK onTaskFinished)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	auto eventHandler = [setEventFunc](Net::Connection* pConn, const Net::ConnectionEvent& evt)
	{
		setEventFunc(evt.Components.EventType, (int)evt.Components.hr, evt.Components.State);
	};

	auto messageHandler = [onMessageFunc](Net::Connection* pConn, const MessageHeader* pMsgData)
	{
            onMessageFunc(pMsgData->GetMessageID(), pMsgData->TransactionId, pMsgData->GetTransactionResult(), pMsgData->GetPayloadSize(), pMsgData->GetPayloadPtr());
	};


	if (pOnlineClient->GetConnectionGame() != nullptr)
	{
		pOnlineClient->GetConnectionGame()->GetConnectionEventDelegates().AddDelegateUnique(1, eventHandler);
		pOnlineClient->GetConnectionGame()->GetRecvMessageDelegates().AddDelegateUnique(1, messageHandler);
	}

	if (pOnlineClient->GetConnectionGameInstance() != nullptr)
	{
		pOnlineClient->GetConnectionGameInstance()->GetConnectionEventDelegates().AddDelegateUnique(1, eventHandler);
		pOnlineClient->GetConnectionGameInstance()->GetRecvMessageDelegates().AddDelegateUnique(1, messageHandler);
	}

	pOnlineClient->SetStateChangeCallback(stateChangedCallback);
	pOnlineClient->SetTaskFinishedCallback(onTaskFinished);

	pOnlineClient->UpdateGameTick();

	if (pOnlineClient->GetConnectionGame() != nullptr)
	{
		pOnlineClient->GetConnectionGame()->GetConnectionEventDelegates().RemoveDelegateAll(1);
		pOnlineClient->GetConnectionGame()->GetRecvMessageDelegates().RemoveDelegateAll(1);
	}

	if (pOnlineClient->GetConnectionGameInstance() != nullptr)
	{
		pOnlineClient->GetConnectionGameInstance()->GetConnectionEventDelegates().RemoveDelegateAll(1);
		pOnlineClient->GetConnectionGameInstance()->GetRecvMessageDelegates().RemoveDelegateAll(1);
	}

	pOnlineClient->SetStateChangeCallback(nullptr);
	pOnlineClient->SetTaskFinishedCallback(nullptr);

	return (int)ResultCode::SUCCESS;

}

SFDLL_EXPORT int32_t SFOnlineClient_NativeUpdateMovement(intptr_t nativeHandle, uint32_t& outDeltaFrames)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	outDeltaFrames = pOnlineClient->UpdateMovement();

	return (int)ResultCode::SUCCESS;
}

SFDLL_EXPORT uint64_t SFOnlineClient_NativeGetConnection(intptr_t nativeHandle, int32_t connectionIndex)
{
	if (nativeHandle == 0)
		return 0;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	switch (connectionIndex)
	{
	case 0:
		return 0; // Deprecated. legacy login
		break;
	case 1:
		return NativeObjectToIntptr(pOnlineClient->GetConnectionGame().get());
		break;
	case 2:
		return NativeObjectToIntptr(pOnlineClient->GetConnectionGameInstance().get());
		break;
	default:
		break;
	}

	return 0;
}

SFDLL_EXPORT uint32_t SFOnlineClient_NativeGetCurrentMoveFrame(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return (uint)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->GetCurrentMovementFrame();
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeSendMovement(intptr_t nativeHandle, const ActorMovement& newMove)
{
	if (nativeHandle == 0)
		return (int)ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	if (pOnlineClient->GetSendMovementManager() == nullptr)
		return (int)ResultCode::INVALID_STATE;

	// ActorMovement requires special memory alignment, copy incoming data to local storage to make it aligned
	ActorMovement tempMove = newMove;

	// make sure it has valid local actor id
	tempMove.ActorId = pOnlineClient->GetActorID();

	return int32_t(pOnlineClient->SendMovement(tempMove));
}


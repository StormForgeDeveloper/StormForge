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
#include "Protocol/SFProtocol.h"
#include "Online/SFOnlineClient.h"

#include "SFCSUtil.h"


namespace SF
{

}

using namespace SF;





//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT intptr_t SFOnlineClient_NativeCreateOnlineClient()
{
	auto pOnlineClient = new(Service::NetSystem->GetHeap()) OnlineClient();
	SharedReferenceInc inc(pOnlineClient);

	return NativeObjectToIntptr(pOnlineClient);
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeStartConnection(intptr_t nativeHandle, const char* gameId, const char* loginAddress, const char* userId, const char* password)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->StartConnection(gameId, loginAddress, userId, password);
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeJoinGameInstance(intptr_t nativeHandle, uint64_t gameInstanceUID)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->JoinGameInstance(gameInstanceUID);
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

SFDLL_EXPORT int32_t SFOnlineClient_NativeGetGameId(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->GetGameId();
}

SFDLL_EXPORT uint64_t SFOnlineClient_NativeGetGameInstanceUID(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return uint64_t(pOnlineClient->GetGameInstanceUID());
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeUpdateGameTick(intptr_t nativeHandle, SET_EVENT_FUNCTION setEventFunc, SET_MESSAGE_FUNCTION setMessageFunc, VariableMapBuilderCS::SET_FUNCTION setValueFunc, VariableMapBuilderCS::SET_ARRAY_FUNCTION setArrayValueFunc, ON_READY_FUNCTION onMessageReady)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;


	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);


	auto eventHandler = [setEventFunc](Net::Connection* pConn, const Net::ConnectionEvent& evt)
	{
		setEventFunc(evt.Components.EventType, evt.Components.hr, evt.Components.State);
	};

	auto messageHandler = [setMessageFunc, setValueFunc, setArrayValueFunc, onMessageReady](Net::Connection* pConn, SharedPointerT<Message::MessageData>& pMsgData)
	{
		setMessageFunc(pMsgData->GetMessageHeader()->msgID.IDSeq.MsgID);

		VariableMapBuilderCS builder(setValueFunc, setArrayValueFunc);
		SF::Protocol::ParseMessage(pMsgData, builder);

		onMessageReady();
	};


	if (pOnlineClient->GetConnectionLogin() != nullptr)
	{
		pOnlineClient->GetConnectionLogin()->GetConnectionEventDelegates().AddDelegateUnique(1, eventHandler);
		pOnlineClient->GetConnectionLogin()->GetRecvMessageDelegates().AddDelegateUnique(1, messageHandler);
	}

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


	pOnlineClient->UpdateGameTick();


	if (pOnlineClient->GetConnectionLogin() != nullptr)
	{
		pOnlineClient->GetConnectionLogin()->GetConnectionEventDelegates().RemoveDelegateAll(1);
		pOnlineClient->GetConnectionLogin()->GetRecvMessageDelegates().RemoveDelegateAll(1);
	}

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


	return ResultCode::SUCCESS;

}


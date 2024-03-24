////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StreamDB
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"
#include "Service/SFEngineService.h"
#include "Online/StreamDB/SFStreamDB.h"
#include "StreamDB/SFStreamDBDirectory.h"
#include "Interfaces/Sharp/SFCSUtil.h"


#ifdef USE_STREAMDB


using namespace SF;



SFDLL_EXPORT intptr_t StreamDB_NativeCreateDirectoryBroker()
{
	auto streamDBInstance = NewObject<StreamDBDirectoryBroker>(GetSystemHeap());
	Service::EngineObjectManager->AddToDetainedRelease(streamDBInstance.StaticCast<SharedObject>());
	return NativeObjectToIntptr(streamDBInstance.get());
}

SFDLL_EXPORT intptr_t StreamDB_NativeCreateDirectoryClient()
{
	auto streamDBInstance = NewObject<StreamDBDirectoryClient>(GetSystemHeap());
	Service::EngineObjectManager->AddToDetainedRelease(streamDBInstance.StaticCast<SharedObject>());
	return NativeObjectToIntptr(streamDBInstance.get());
}

SFDLL_EXPORT intptr_t StreamDB_NativeCreateProducer()
{
	SharedPointerT<StreamDBProducer> streamDBInstance = new(GetSystemHeap()) StreamDBProducer;
	Service::EngineObjectManager->AddToDetainedRelease(streamDBInstance.StaticCast<SharedObject>());
	return NativeObjectToIntptr(streamDBInstance.get());
}

SFDLL_EXPORT intptr_t StreamDB_NativeCreateConsumer()
{
	SharedPointerT<StreamDBConsumer> streamDBInstance = new(GetSystemHeap()) StreamDBConsumer;
	Service::EngineObjectManager->AddToDetainedRelease(streamDBInstance.StaticCast<SharedObject>());

	return NativeObjectToIntptr(streamDBInstance.get());
}



SFDLL_EXPORT int32_t StreamDB_NativeInitialize(intptr_t nativeHandle, const char* strBrokers, const char* strTopic)
{
	auto pStreamInstance = NativeToObject<StreamDB>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->Initialize(strBrokers, strTopic);
}

SFDLL_EXPORT const char* StreamDB_NativeGetTopic(intptr_t nativeHandle, const char* strBrokers, const char* strTopic)
{
	auto pStreamInstance = NativeToObject<StreamDB>(nativeHandle);
	if (pStreamInstance == nullptr)
		return nullptr;

	return pStreamInstance->GetTopic().data();
}

SFDLL_EXPORT int32_t StreamDBDirectory_NativeInitialize(intptr_t nativeHandle, const char* strBrokers)
{
	auto pStreamInstance = NativeToObject<StreamDBDirectory>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->Initialize(strBrokers);
}

SFDLL_EXPORT int32_t StreamDBDirectory_NativeRequestStreamList(intptr_t nativeHandle)
{
	auto pStreamInstance = NativeToObject<StreamDBDirectoryBroker>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::INVALID_POINTER;

	return (int32_t)pStreamInstance->RequestStreamList();
}

SFDLL_EXPORT int32_t StreamDBDirectory_NativeGetTopicCount(intptr_t nativeHandle)
{
	auto pStreamInstance = NativeToObject<StreamDBDirectoryBroker>(nativeHandle);
	if (pStreamInstance == nullptr)
		return 0;

	return static_cast<int32_t>(pStreamInstance->GetStreamList().size());
}

SFDLL_EXPORT const char* StreamDBDirectory_NativeGetTopic(intptr_t nativeHandle, int32_t index)
{
	auto pStreamInstance = NativeToObject<StreamDBDirectoryBroker>(nativeHandle);
	if (pStreamInstance == nullptr)
		return "";

	return pStreamInstance->GetStreamList()[index].data();
}


SFDLL_EXPORT int32_t StreamDBDirectory_NativePollMessage(intptr_t nativeHandle, ON_MESSAGE_FUNCTION onMessage)
{
	if (nativeHandle == 0)
		return (int)ResultCode::INVALID_ARG;

	auto pDirectoryBase = NativeToObject<StreamDBDirectory>(nativeHandle);

	// just to empty event queue, not important at this moment
	StreamDBDirectory::Event evt;
	pDirectoryBase->PollEvent(evt);

	MessageDataPtr pIMsg;
	if (!pDirectoryBase->PollMessage(pIMsg))
		return (int)ResultCode::NO_DATA_EXIST;

    onMessage(pIMsg->GetMessageHeader()->GetMessageID(), pIMsg->GetMessageHeader()->TransactionId, pIMsg->GetPayloadSize(), pIMsg->GetPayloadPtr());

	return (int)ResultCode::SUCCESS;
}


SFDLL_EXPORT int32_t StreamDBProducer_NativeSendRecord(intptr_t nativeHandle, int32_t dataSize, const uint8_t* data)
{
	auto pStreamInstance = NativeToObject<StreamDBProducer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->SendRecord(ArrayView<const uint8_t>(dataSize, data));
}

SFDLL_EXPORT int32_t StreamDBProducer_NativeFlush(intptr_t nativeHandle)
{
	auto pStreamInstance = NativeToObject<StreamDBProducer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->Flush();
}

SFDLL_EXPORT int64_t StreamDBConsumer_NativeToOffsetFromTail(intptr_t nativeHandle, int64_t offsetFromTail)
{
	auto pStreamInstance = NativeToObject<StreamDBConsumer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return -1;

	return pStreamInstance->ToOffsetFromTail(offsetFromTail);
}

SFDLL_EXPORT int32_t StreamDBConsumer_NativeRequestData(intptr_t nativeHandle, int64_t start_offset)
{
	auto pStreamInstance = NativeToObject<StreamDBConsumer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->RequestData(start_offset);
}

SFDLL_EXPORT int32_t StreamDBConsumer_NativePollData(intptr_t nativeHandle, int64_t& InOutmessageOffset, int64_t& InOutmessageTimeStamp, int32_t& InOutmessageDataSize, intptr_t& InOutmessageData)
{
	auto pStreamInstance = NativeToObject<StreamDBConsumer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int)ResultCode::UNEXPECTED;


	auto result = pStreamInstance->PollData();

	const SFUniquePtr<StreamMessageData>& messageData = pStreamInstance->GetLatestReceivedData();
	if (messageData)
	{
		InOutmessageOffset = messageData->GetOffset();
		InOutmessageTimeStamp = messageData->GetTimeStamp();
		InOutmessageDataSize = static_cast<int32_t>(messageData->size());
		InOutmessageData = reinterpret_cast<intptr_t>(messageData->data());
	}

	return (int32_t)result;
}


#endif

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
#include "StreamDB/SFStreamDB.h"
#include "SFCSUtil.h"

#ifdef USE_STREAMDB

using namespace SF;



SFDLL_EXPORT intptr_t StreamDB_NativeCreateDirectory()
{
	auto streamDBInstance = new(GetSystemHeap()) StreamDBDirectory;
	return reinterpret_cast<intptr_t>(static_cast<SharedObject*>(streamDBInstance));
}

SFDLL_EXPORT intptr_t StreamDB_NativeCreateProducer()
{
	auto streamDBInstance = new(GetSystemHeap()) StreamDBProducer;
	return reinterpret_cast<intptr_t>(static_cast<SharedObject*>(streamDBInstance));
}

SFDLL_EXPORT intptr_t StreamDB_NativeCreateConsumer()
{
	auto streamDBInstance = new(GetSystemHeap()) StreamDBConsumer;
	return reinterpret_cast<intptr_t>(static_cast<SharedObject*>(streamDBInstance));
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

SFDLL_EXPORT int32_t StreamDBDirectory_NativeRefreshTopicList(intptr_t nativeHandle)
{
	auto pStreamInstance = NativeToObject<StreamDBDirectory>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::INVALID_POINTER;

	return (int32_t)pStreamInstance->RefreshTopicList();
}

SFDLL_EXPORT int32_t StreamDBDirectory_NativeGetTopicCount(intptr_t nativeHandle)
{
	auto pStreamInstance = NativeToObject<StreamDBDirectory>(nativeHandle);
	if (pStreamInstance == nullptr)
		return 0;

	return static_cast<int32_t>(pStreamInstance->GetTopicList().size());
}

SFDLL_EXPORT const char* StreamDBDirectory_NativeGetTopic(intptr_t nativeHandle, int32_t index)
{
	auto pStreamInstance = NativeToObject<StreamDBDirectory>(nativeHandle);
	if (pStreamInstance == nullptr)
		return "";

	return pStreamInstance->GetTopicList()[index].data();
}

SFDLL_EXPORT int32_t StreamDBProducer_NativeSendRecord(intptr_t nativeHandle, int32_t dataSize, const uint8_t* data)
{
	auto pStreamInstance = NativeToObject<StreamDBProducer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->SendRecord(ArrayView<uint8_t>(dataSize, data));
}

SFDLL_EXPORT int32_t StreamDBProducer_NativeFlush(intptr_t nativeHandle)
{
	auto pStreamInstance = NativeToObject<StreamDBProducer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->Flush();
}

SFDLL_EXPORT int32_t StreamDBConsumer_NativeRequestData(intptr_t nativeHandle, int64_t start_offset)
{
	auto pStreamInstance = NativeToObject<StreamDBConsumer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return (int32_t)ResultCode::UNEXPECTED;

	return (int32_t)pStreamInstance->RequestData(start_offset);
}

SFDLL_EXPORT int32_t StreamDBConsumer_NativePollData(intptr_t nativeHandle, int32_t& InOutmessageDataSize, intptr_t& InOutmessageData)
{
	auto pStreamInstance = NativeToObject<StreamDBConsumer>(nativeHandle);
	if (pStreamInstance == nullptr)
		return ResultCode::UNEXPECTED;


	auto result = pStreamInstance->PollData();

	if (pStreamInstance->GetLatestReceivedData())
	{
		InOutmessageDataSize = static_cast<int32_t>(pStreamInstance->GetLatestReceivedData()->size());
		InOutmessageData = reinterpret_cast<intptr_t>(pStreamInstance->GetLatestReceivedData()->data());
	}

	return (int32_t)result;
}


#endif

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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
#include "Net/SFConnectionMUDP.h"
#include "Net/SFConnectionTCP.h"
#include "Net/SFMessage.h"
#include "SFProtocol.h"
#include "MessageBus/SFMessageHeader.h"

#include "Interfaces/Sharp/SFCSUtil.h"


using namespace SF;




//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT intptr_t SFConnection_NativeCreateConnection()
{
	auto pConnection = new(Service::NetSystem->GetHeap()) Net::ConnectionMUDPClient(Service::NetSystem->GetHeap());
	SharedReferenceInc inc(pConnection);
	return NativeObjectToIntptr(pConnection);
}

SFDLL_EXPORT intptr_t SFConnection_NativeCreateConnectionTCP()
{
	auto pConnection = new(Service::NetSystem->GetHeap()) Net::ConnectionTCPClient(Service::NetSystem->GetHeap());
	SharedReferenceInc inc(pConnection);

	return NativeObjectToIntptr(pConnection);
}

SFDLL_EXPORT int SFConnection_NativeConnect(intptr_t nativeHandle, uint64_t authTicket, const char* address, int port)
{
	if (nativeHandle == 0)
		return (int)ResultCode::INVALID_ARG;

	NetAddress remoteAddress(address, (uint16_t)port);

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);
	auto result = pConnection->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, remoteAddress, 0));
	if (result)
	{
		pConnection->SetTickGroup(EngineTaskTick::AsyncTick);
	}
	return (int)result;
}

SFDLL_EXPORT void SFConnection_NativeDispose(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return;

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);

	pConnection->DisconnectNRelease("Requested from CS");

	SharedReferenceDec dec(pConnection);
}

SFDLL_EXPORT void SFConnection_NativeDisconnect(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return;

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);
	pConnection->Disconnect("Requested from CS");
	pConnection->CloseConnection("Request from CS");
	pConnection->SetTickGroup(EngineTaskTick::None);
}

SFDLL_EXPORT uint64_t SFConnection_NativeGetLocalPeerID(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);
	return pConnection->GetLocalInfo().PeerID;
}

SFDLL_EXPORT void SFConnection_NativeSetLocalPeerID(intptr_t nativeHandle, uint64_t peerID)
{
	if (nativeHandle == 0)
		return;

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);
	pConnection->SetLocalID(peerID);
}

SFDLL_EXPORT uint64_t SFConnection_NativeGetCID(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);
	return pConnection->GetCID();
}

SFDLL_EXPORT int SFConnection_NativeGetState(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);
	return (int)pConnection->GetConnectionState();
}


SFDLL_EXPORT bool SFConnection_NativeDequeueEvent(intptr_t nativeHandle, Net::ConnectionEvent::EventTypes& eventType, int32_t& result, Net::ConnectionState& state)
{
	if (nativeHandle == 0)
		return false;

	auto pConnection = SF::NativeToObject<Net::Connection>(nativeHandle);

	Net::ConnectionEvent conEvent;
	auto hr = pConnection->DequeueConnectionEvent(conEvent);
	eventType = conEvent.Components.EventType;
	result = (int32_t)conEvent.Components.hr;
	state = conEvent.Components.State;

	return hr.IsSuccess();
}


SFDLL_EXPORT bool SFConnection_NativeDequeueMessage(intptr_t nativeHandle, ON_MESSAGE_FUNCTION onMessageFunc)
{
	if (nativeHandle == 0)
		return false;

	Net::Connection* pConnection = NativeToObject<Net::Connection>(nativeHandle);

    Net::Connection::MessageItemReadPtr itemPtr = pConnection->GetRecvMessageQueue().DequeueRead();
    if (!itemPtr)
        return false;

    const MessageHeader* pHeader = reinterpret_cast<const MessageHeader * >(itemPtr.data());

	onMessageFunc(pHeader->GetMessageID(), pHeader->TransactionId, pHeader->GetTransactionResult(), pHeader->GetPayloadSize(), pHeader->GetPayloadPtr());

	return true;
}


SFDLL_EXPORT bool SFConnection_NativeTimeSync(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return false;

	Net::Connection* pConnection = NativeToObject<Net::Connection>(nativeHandle);


	return pConnection->TimeSync().IsSuccess();
}

SFDLL_EXPORT int SFConnection_NativeSendMessage(intptr_t nativeHandle, int dataOffset, int dataSize, const uint8_t* dataPtr)
{
    if (nativeHandle == 0)
        return (int)ResultCode::INVALID_POINTER;

    if (dataPtr == nullptr)
        return (int)ResultCode::INVALID_ARG;

    Net::Connection* pConnection = NativeToObject<Net::Connection>(nativeHandle);

    auto* messageHeader = reinterpret_cast<const MessageHeader*>(dataPtr + dataOffset);
    if (messageHeader->MessageSize != dataSize)
        return (int)ResultCode::INVALID_DATA;

    return (int)pConnection->SendMsg(messageHeader);
}

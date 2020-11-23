////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Relay Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/Message/RelayMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// C2S: Event for Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_RelayJoinRelayInstanceC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, PlayerID InPlayerID, const char* InPlayerIdentifier )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::JoinRelayInstanceC2SEvt::Create(pConnection->GetHeap(), InRelayInstanceID, InPlayerID,InPlayerIdentifier);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayJoinRelayInstanceC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, PlayerID InPlayerID, const char* InPlayerIdentifier )



// C2S: Event for Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_RelayLeaveRelayInstanceC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, PlayerID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::LeaveRelayInstanceC2SEvt::Create(pConnection->GetHeap(), InRelayInstanceID, InPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayLeaveRelayInstanceC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, PlayerID InPlayerID )



// C2S: Relay packet
SFDLL_EXPORT int  CSSFNetAdapter_RelayRelayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::RelayPacketC2SEvt::Create(pConnection->GetHeap(), InRelayInstanceID, InSenderEndpointID, InTargetEndpointMask,SF::ArrayView<uint8_t>(_sizeOfInPayload, _sizeOfInPayload, const_cast<uint8_t*>(InPayload)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayRelayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )



// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetAdapter_RelayCreateStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::CreateStreamCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayCreateStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetAdapter_RelayFindStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::FindStreamCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayFindStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetAdapter_RelayDeleteStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::DeleteStreamCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayDeleteStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetAdapter_RelayGetStreamListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::GetStreamListCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayGetStreamListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket )




// S2C: Event for joined player
SFDLL_EXPORT int  CSSFNetAdapter_RelayJoinRelayInstanceResS2CEvt( intptr_t InNativeConnectionHandle, Result InResult, uint32_t InRelayInstanceID, uint32_t InMyEndpointID, uint16_t _sizeOfInMemberInfos,const RelayPlayerInfo* InMemberInfos )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::JoinRelayInstanceResS2CEvt::Create(pConnection->GetHeap(), InResult, InRelayInstanceID, InMyEndpointID,SF::ArrayView<RelayPlayerInfo>(_sizeOfInMemberInfos, _sizeOfInMemberInfos, const_cast<RelayPlayerInfo*>(InMemberInfos)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayJoinRelayInstanceResS2CEvt( intptr_t InNativeConnectionHandle, Result InResult, uint32_t InRelayInstanceID, uint32_t InMyEndpointID, uint16_t _sizeOfInMemberInfos,const RelayPlayerInfo* InMemberInfos )



// S2C: Event for Player joined.
SFDLL_EXPORT int  CSSFNetAdapter_RelayPlayerJoinS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, const RelayPlayerInfo& InJoinedPlayerInfo )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::PlayerJoinS2CEvt::Create(pConnection->GetHeap(), InRelayInstanceID,InJoinedPlayerInfo);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayPlayerJoinS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, const RelayPlayerInfo& InJoinedPlayerInfo )



// S2C: Event for Player left.
SFDLL_EXPORT int  CSSFNetAdapter_RelayPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, PlayerID InLeftPlayerID, uint32_t InKickedReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::PlayerLeftS2CEvt::Create(pConnection->GetHeap(), InRelayInstanceID, InLeftPlayerID, InKickedReason);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InRelayInstanceID, PlayerID InLeftPlayerID, uint32_t InKickedReason )



// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetAdapter_RelayCreateStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::CreateStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamServerAddr,InStreamServerAddrIPV4,InStreamUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayCreateStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )



// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetAdapter_RelayFindStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::FindStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamServerAddr,InStreamServerAddrIPV4,InStreamUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayFindStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )



// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetAdapter_RelayDeleteStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::DeleteStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayDeleteStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetAdapter_RelayGetStreamListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamNames )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Relay::GetStreamListRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamNames);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_RelayGetStreamListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamNames )










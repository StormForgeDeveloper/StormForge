﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// Cmd: Event for Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InPlayInstanceID, PlayerID InPlayerID, const char* InPlayerIdentifier )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::JoinGameInstanceCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayInstanceID, InPlayerID,InPlayerIdentifier);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InPlayInstanceID, PlayerID InPlayerID, const char* InPlayerIdentifier )


// C2S: Play packet
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InPlayInstanceID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayPacketC2SEvt::Create(pConnection->GetHeap(), InPlayInstanceID, InSenderEndpointID, InTargetEndpointMask,SF::ArrayView<uint8_t>(_sizeOfInPayload, _sizeOfInPayload, const_cast<uint8_t*>(InPayload)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint32_t InPlayInstanceID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )



// C2S: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayerMovementC2SEvt::Create(pConnection->GetHeap(), InGameInsUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::CreateStreamCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::FindStreamCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::DeleteStreamCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::GetStreamListCmd::Create(pConnection->GetHeap(), InTransactionID, InTicket);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AuthTicket InTicket )




// Cmd: Event for Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InPlayInstanceID, uint32_t InMyEndpointID, uint16_t _sizeOfInMemberInfos,const PlayerInformation* InMemberInfos )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::JoinGameInstanceRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayInstanceID, InMyEndpointID,SF::ArrayView<PlayerInformation>(_sizeOfInMemberInfos, _sizeOfInMemberInfos, const_cast<PlayerInformation*>(InMemberInfos)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InPlayInstanceID, uint32_t InMyEndpointID, uint16_t _sizeOfInMemberInfos,const PlayerInformation* InMemberInfos )



// S2C: Event for Player joined.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerJoinS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InPlayInstanceID, const PlayerInformation& InJoinedPlayerInfo )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayerJoinS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceID,InJoinedPlayerInfo);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerJoinS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InPlayInstanceID, const PlayerInformation& InJoinedPlayerInfo )



// S2C: Event for Player left.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InPlayInstanceID, PlayerID InLeftPlayerID, uint32_t InKickedReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayerLeftS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceID, InLeftPlayerID, InKickedReason);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InPlayInstanceID, PlayerID InLeftPlayerID, uint32_t InKickedReason )



// S2C: New Player in get view
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::NewPlayerInViewS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// S2C: Remove player from view
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::RemovePlayerFromViewS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayerMovementS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::CreateStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamServerAddr,InStreamServerAddrIPV4,InStreamUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )



// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::FindStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamServerAddr,InStreamServerAddrIPV4,InStreamUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InStreamServerAddr, const NetAddress& InStreamServerAddrIPV4, const char* InStreamUID )



// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::DeleteStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, intptr_t InStreamNames )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	auto& InStreamNamesArray_ = *NativeToObject<SF::ArrayObject<const char*>>(InStreamNames);
	MessageDataPtr pMessage = SF::Message::PlayInstance::GetStreamListRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamNamesArray_);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, intptr_t InStreamNames )









////////////////////////////////////////////////////////////////////////////////
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
#include "Protocol/PlayInstanceMsgClass.h"
#include "SharpCPP/SFCSUtil.h"



using namespace SF;


// Cmd: Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const char* InPlayerIdentifier )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::JoinPlayInstanceCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayInstanceUID, InPlayerID,InPlayerIdentifier);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const char* InPlayerIdentifier )


// C2S: Play packet
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayPacketC2SEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask,SF::ArrayView<uint8_t>(_sizeOfInPayload, _sizeOfInPayload, const_cast<uint8_t*>(InPayload)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )



// C2S: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const ActorMovement& InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayerMovementC2SEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InPlayerID,InMovement);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const ActorMovement& InMovement )



// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::ClientSyncReliableC2SEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInSyncData, _sizeOfInSyncData, InSyncData));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )



// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::ClientSyncC2SEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInSyncData, _sizeOfInSyncData, InSyncData));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )



// Cmd: Occupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId, uint32_t InUsageId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::OccupyMapObjectCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId, uint32_t InUsageId )


// Cmd: Unoccupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::UnoccupyMapObjectCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )


// Cmd: Use map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInUseParameters,uint8_t* InUseParameters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::UseMapObjectCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId,SF::ArrayView<uint8_t>(_sizeOfInUseParameters, _sizeOfInUseParameters, InUseParameters));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInUseParameters,uint8_t* InUseParameters )


// Cmd: Havest area
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceHarvestAreaCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InAreaId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::HarvestAreaCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InAreaId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceHarvestAreaCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InAreaId )


// Cmd: Send zone chatting
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int8_t InChatMessageType, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::ZoneChatCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InChatMessageType,InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int8_t InChatMessageType, const char* InChatMessage )


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


// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, StringCrc32 InFunctionName, PlayerID InPlayerID, uint16_t _sizeOfInParameters,uint8_t* InParameters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::CallFunctionCmd::Create(pConnection->GetHeap(), InTransactionID, InFunctionName, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, StringCrc32 InFunctionName, PlayerID InPlayerID, uint16_t _sizeOfInParameters,uint8_t* InParameters )




// Cmd: Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const ActorMovement& InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::JoinPlayInstanceRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID,InMovement);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const ActorMovement& InMovement )



// S2C: Player kicked event. this event will be broadcasted when a player kicked.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InKickedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayerKickedS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InKickedPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InKickedPlayerID )



// S2C: New actor in get view
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes, const ActorMovement& InMovement, StringCrc32 InState, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::NewActorInViewS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes),InMovement, InState,SF::ArrayView<uint8_t>(_sizeOfInStateValues, _sizeOfInStateValues, InStateValues));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes, const ActorMovement& InMovement, StringCrc32 InState, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )



// S2C: Remove actor from view
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InActorID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::RemoveActorFromViewS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InPlayerID, InActorID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InActorID )



// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, const ActorMovement& InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::ActorMovementS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceUID,InMovement);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, const ActorMovement& InMovement )



// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint16_t _sizeOfInMovement,const ActorMovement* InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::ActorMovementsS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceUID,SF::ArrayView<ActorMovement>(_sizeOfInMovement, _sizeOfInMovement, const_cast<ActorMovement*>(InMovement)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint16_t _sizeOfInMovement,const ActorMovement* InMovement )



// S2C: Player state change
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InState, uint32_t InMoveFrame, const Vector4& InPosition, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::PlayerStateChangedS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InPlayerID, InState, InMoveFrame,InPosition,SF::ArrayView<uint8_t>(_sizeOfInStateValues, _sizeOfInStateValues, InStateValues));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InState, uint32_t InMoveFrame, const Vector4& InPosition, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )



// Cmd: Occupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::OccupyMapObjectRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )



// Cmd: Unoccupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::UnoccupyMapObjectRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )



// Cmd: Use map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInResultAttributes,uint8_t* InResultAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::UseMapObjectRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId,SF::ArrayView<uint8_t>(_sizeOfInResultAttributes, _sizeOfInResultAttributes, InResultAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInResultAttributes,uint8_t* InResultAttributes )



// Cmd: Havest area
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceHarvestAreaRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InAreaId, uint16_t _sizeOfInResultAttributes,uint8_t* InResultAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::HarvestAreaRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InAreaId,SF::ArrayView<uint8_t>(_sizeOfInResultAttributes, _sizeOfInResultAttributes, InResultAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceHarvestAreaRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InAreaId, uint16_t _sizeOfInResultAttributes,uint8_t* InResultAttributes )



// Cmd: Send zone chatting
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::ZoneChatRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Player state change
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int8_t InChatMessageType, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::ZoneChatS2CEvt::Create(pConnection->GetHeap(), InPlayInstanceUID, InPlayerID, InChatMessageType,InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int8_t InChatMessageType, const char* InChatMessage )



// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::CreateStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamName )



// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::FindStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamName )



// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::DeleteStreamRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InStreamName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InStreamName )



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



// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::PlayInstance::CallFunctionRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInResults, _sizeOfInResults, InResults));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )










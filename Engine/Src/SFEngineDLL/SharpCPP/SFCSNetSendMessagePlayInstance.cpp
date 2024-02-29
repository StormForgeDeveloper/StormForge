////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/PlayInstanceMsgClass.h"
#include "Interfaces/Sharp/SFCSUtil.h"



using namespace SF;


// Cmd: Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const char* InPlayerIdentifier )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::JoinPlayInstanceCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID,InPlayerIdentifier);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::JoinPlayInstanceCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID,InPlayerIdentifier);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const char* InPlayerIdentifier )


// C2S: Play packet
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::PlayPacketC2SEvt::CalculateMessageSize( InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask,SF::ArrayView<uint8_t>(_sizeOfInPayload, _sizeOfInPayload, const_cast<uint8_t*>(InPayload)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::PlayPacketC2SEvt::Create(pMessage,  InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask,SF::ArrayView<uint8_t>(_sizeOfInPayload, _sizeOfInPayload, const_cast<uint8_t*>(InPayload)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayPacketC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint32_t InSenderEndpointID, uint32_t InTargetEndpointMask, uint16_t _sizeOfInPayload,const uint8_t* InPayload )



// C2S: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const ActorMovement& InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::PlayerMovementC2SEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID,InMovement);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::PlayerMovementC2SEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID,InMovement);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const ActorMovement& InMovement )



// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::ClientSyncReliableC2SEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInSyncData, _sizeOfInSyncData, InSyncData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::ClientSyncReliableC2SEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInSyncData, _sizeOfInSyncData, InSyncData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )



// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::ClientSyncC2SEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInSyncData, _sizeOfInSyncData, InSyncData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::ClientSyncC2SEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInSyncData, _sizeOfInSyncData, InSyncData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceClientSyncC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInSyncData,uint8_t* InSyncData )



// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const char* InPublicMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::SetCharacterPublicMessageCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID,InPublicMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::SetCharacterPublicMessageCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID,InPublicMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const char* InPublicMessage )


// Cmd: Request WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InTargetPlayerID, uint16_t _sizeOfInWhiteboardInfo,uint8_t* InWhiteboardInfo )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::RequestWhiteboardSharingCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InTargetPlayerID,SF::ArrayView<uint8_t>(_sizeOfInWhiteboardInfo, _sizeOfInWhiteboardInfo, InWhiteboardInfo));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::RequestWhiteboardSharingCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID, InTargetPlayerID,SF::ArrayView<uint8_t>(_sizeOfInWhiteboardInfo, _sizeOfInWhiteboardInfo, InWhiteboardInfo));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InTargetPlayerID, uint16_t _sizeOfInWhiteboardInfo,uint8_t* InWhiteboardInfo )


// Cmd: Accept WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InRequestedPlayerID, uint8_t InAnswer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::AcceptWhiteboardSharingCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InRequestedPlayerID, InAnswer);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::AcceptWhiteboardSharingCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID, InRequestedPlayerID, InAnswer);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InRequestedPlayerID, uint8_t InAnswer )


// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CloseWhiteboardSharingCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CloseWhiteboardSharingCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID )


// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )


// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )


// Cmd: Update whiteboard log entry
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InLogEntryID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntryID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntryID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InLogEntryID )


// Cmd: Occupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId, uint32_t InUsageId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::OccupyMapObjectCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::OccupyMapObjectCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId, uint32_t InUsageId )


// Cmd: Unoccupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::UnoccupyMapObjectCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::UnoccupyMapObjectCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )


// Cmd: Use map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInUseParameters,uint8_t* InUseParameters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::UseMapObjectCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId,SF::ArrayView<uint8_t>(_sizeOfInUseParameters, _sizeOfInUseParameters, InUseParameters));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::UseMapObjectCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId,SF::ArrayView<uint8_t>(_sizeOfInUseParameters, _sizeOfInUseParameters, InUseParameters));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInUseParameters,uint8_t* InUseParameters )


// Cmd: Send zone chatting
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int8_t InMessageType, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::ZoneChatCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::ZoneChatCmd::Create(pMessage, InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int8_t InMessageType, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )


// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, StringCrc32 InFunctionName, PlayerID InPlayerID, uint16_t _sizeOfInParameters,uint8_t* InParameters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CallFunctionCmd::CalculateMessageSize(InTransactionID, InFunctionName, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CallFunctionCmd::Create(pMessage, InTransactionID, InFunctionName, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, StringCrc32 InFunctionName, PlayerID InPlayerID, uint16_t _sizeOfInParameters,uint8_t* InParameters )


// C2S: Send coded voice data to server
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceSendVoiceDataC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t InFrameIndex, uint16_t _sizeOfInVoiceData,const uint8_t* InVoiceData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::SendVoiceDataC2SEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InFrameIndex,SF::ArrayView<uint8_t>(_sizeOfInVoiceData, _sizeOfInVoiceData, const_cast<uint8_t*>(InVoiceData)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::SendVoiceDataC2SEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InFrameIndex,SF::ArrayView<uint8_t>(_sizeOfInVoiceData, _sizeOfInVoiceData, const_cast<uint8_t*>(InVoiceData)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceSendVoiceDataC2SEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t InFrameIndex, uint16_t _sizeOfInVoiceData,const uint8_t* InVoiceData )



// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CreateStreamCmd::CalculateMessageSize(InTransactionID, InTicket,InStreamName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CreateStreamCmd::Create(pMessage, InTransactionID, InTicket,InStreamName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::FindStreamCmd::CalculateMessageSize(InTransactionID, InTicket,InStreamName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::FindStreamCmd::Create(pMessage, InTransactionID, InTicket,InStreamName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::DeleteStreamCmd::CalculateMessageSize(InTransactionID, InTicket,InStreamName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::DeleteStreamCmd::Create(pMessage, InTransactionID, InTicket,InStreamName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket, const char* InStreamName )


// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::GetStreamListCmd::CalculateMessageSize(InTransactionID, InTicket);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::GetStreamListCmd::Create(pMessage, InTransactionID, InTicket);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AuthTicket InTicket )




// Cmd: Player Join request.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, CharacterID InCharacterID, uint16_t _sizeOfInCharacterPrivateData,uint8_t* InCharacterPrivateData, const ActorMovement& InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::JoinPlayInstanceRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InCharacterID,SF::ArrayView<uint8_t>(_sizeOfInCharacterPrivateData, _sizeOfInCharacterPrivateData, InCharacterPrivateData),InMovement);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::JoinPlayInstanceRes::Create(pMessage, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InCharacterID,SF::ArrayView<uint8_t>(_sizeOfInCharacterPrivateData, _sizeOfInCharacterPrivateData, InCharacterPrivateData),InMovement);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, CharacterID InCharacterID, uint16_t _sizeOfInCharacterPrivateData,uint8_t* InCharacterPrivateData, const ActorMovement& InMovement )



// S2C: Player kicked event. this event will be broadcasted when a player kicked.
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InKickedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::PlayerKickedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InKickedPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::PlayerKickedS2CEvt::Create(pMessage,  InPlayInstanceUID, InKickedPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InKickedPlayerID )



// S2C: New actor in get view
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const PlayerPlatformID& InPlayerPlatformId, uint16_t _sizeOfInPublicData,uint8_t* InPublicData, uint16_t _sizeOfInEquipData,uint8_t* InEquipData, const ActorMovement& InMovement, StringCrc32 InState, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::NewActorInViewS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID,InPlayerPlatformId,SF::ArrayView<uint8_t>(_sizeOfInPublicData, _sizeOfInPublicData, InPublicData),SF::ArrayView<uint8_t>(_sizeOfInEquipData, _sizeOfInEquipData, InEquipData),InMovement, InState,SF::ArrayView<uint8_t>(_sizeOfInStateValues, _sizeOfInStateValues, InStateValues));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::NewActorInViewS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID,InPlayerPlatformId,SF::ArrayView<uint8_t>(_sizeOfInPublicData, _sizeOfInPublicData, InPublicData),SF::ArrayView<uint8_t>(_sizeOfInEquipData, _sizeOfInEquipData, InEquipData),InMovement, InState,SF::ArrayView<uint8_t>(_sizeOfInStateValues, _sizeOfInStateValues, InStateValues));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, const PlayerPlatformID& InPlayerPlatformId, uint16_t _sizeOfInPublicData,uint8_t* InPublicData, uint16_t _sizeOfInEquipData,uint8_t* InEquipData, const ActorMovement& InMovement, StringCrc32 InState, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )



// S2C: Remove actor from view
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint32_t InActorID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::RemoveActorFromViewS2CEvt::CalculateMessageSize( InPlayInstanceUID, InActorID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::RemoveActorFromViewS2CEvt::Create(pMessage,  InPlayInstanceUID, InActorID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint32_t InActorID )



// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, const ActorMovement& InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::ActorMovementS2CEvt::CalculateMessageSize( InPlayInstanceUID,InMovement);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::ActorMovementS2CEvt::Create(pMessage,  InPlayInstanceUID,InMovement);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, const ActorMovement& InMovement )



// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint16_t _sizeOfInMovement,const ActorMovement* InMovement )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::ActorMovementsS2CEvt::CalculateMessageSize( InPlayInstanceUID,SF::ArrayView<ActorMovement>(_sizeOfInMovement, _sizeOfInMovement, const_cast<ActorMovement*>(InMovement)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::ActorMovementsS2CEvt::Create(pMessage,  InPlayInstanceUID,SF::ArrayView<ActorMovement>(_sizeOfInMovement, _sizeOfInMovement, const_cast<ActorMovement*>(InMovement)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, uint16_t _sizeOfInMovement,const ActorMovement* InMovement )



// S2C: Player state change
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InState, uint32_t InMoveFrame, const Vector4& InPosition, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::PlayerStateChangedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InState, InMoveFrame,InPosition,SF::ArrayView<uint8_t>(_sizeOfInStateValues, _sizeOfInStateValues, InStateValues));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::PlayerStateChangedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InState, InMoveFrame,InPosition,SF::ArrayView<uint8_t>(_sizeOfInStateValues, _sizeOfInStateValues, InStateValues));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InState, uint32_t InMoveFrame, const Vector4& InPosition, uint16_t _sizeOfInStateValues,uint8_t* InStateValues )



// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::SetCharacterPublicMessageRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::SetCharacterPublicMessageRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Character's private data has changed
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCharacterPrivateDataChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InCharacterID, uint16_t _sizeOfInPrivateData,uint8_t* InPrivateData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InCharacterID,SF::ArrayView<uint8_t>(_sizeOfInPrivateData, _sizeOfInPrivateData, InPrivateData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InCharacterID,SF::ArrayView<uint8_t>(_sizeOfInPrivateData, _sizeOfInPrivateData, InPrivateData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCharacterPrivateDataChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InCharacterID, uint16_t _sizeOfInPrivateData,uint8_t* InPrivateData )



// S2C: Player public data has been changed
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCharacterPublicDataChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInPublicData,uint8_t* InPublicData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CharacterPublicDataChangedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInPublicData, _sizeOfInPublicData, InPublicData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CharacterPublicDataChangedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInPublicData, _sizeOfInPublicData, InPublicData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCharacterPublicDataChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInPublicData,uint8_t* InPublicData )



// Cmd: Request WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::RequestWhiteboardSharingRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::RequestWhiteboardSharingRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Accept WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::AcceptWhiteboardSharingRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::AcceptWhiteboardSharingRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CloseWhiteboardSharingRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CloseWhiteboardSharingRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InLogEntryID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::AddWhiteboardSharingLogEntryRes::CalculateMessageSize(InTransactionID, InResult, InLogEntryID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::AddWhiteboardSharingLogEntryRes::Create(pMessage, InTransactionID, InResult, InLogEntryID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InLogEntryID )



// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Update whiteboard log entry
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: WhiteboardSharing has been requested
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingRequestedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InRequestedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InRequestedPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InRequestedPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingRequestedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InRequestedPlayerID )



// S2C: WhiteboardSharing has been requested
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingRejectedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InRejectedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InRejectedPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InRejectedPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingRejectedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InRejectedPlayerID )



// S2C: WhiteboardSharing has been started
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingStartedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InOtherPlayerID, uint16_t _sizeOfInWhiteboardInfo,uint8_t* InWhiteboardInfo )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::WhiteboardSharingStartedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InOtherPlayerID,SF::ArrayView<uint8_t>(_sizeOfInWhiteboardInfo, _sizeOfInWhiteboardInfo, InWhiteboardInfo));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::WhiteboardSharingStartedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InOtherPlayerID,SF::ArrayView<uint8_t>(_sizeOfInWhiteboardInfo, _sizeOfInWhiteboardInfo, InWhiteboardInfo));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingStartedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InOtherPlayerID, uint16_t _sizeOfInWhiteboardInfo,uint8_t* InWhiteboardInfo )



// S2C: WhiteboardSharing has been closed
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingHasClosedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InClosedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InClosedPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InClosedPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingHasClosedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, PlayerID InClosedPlayerID )



// S2C: WhiteboardSharing new log entry has been added
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )



// S2C: WhiteboardSharing new log entry has been removed
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InLogEntryID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InLogEntryID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InLogEntryID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InLogEntryID )



// S2C: WhiteboardSharing new log entry has been updated
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInLogEntry, _sizeOfInLogEntry, InLogEntry));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint16_t _sizeOfInLogEntry,uint8_t* InLogEntry )



// Cmd: Occupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::OccupyMapObjectRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::OccupyMapObjectRes::Create(pMessage, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceOccupyMapObjectRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )



// Cmd: Unoccupy map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::UnoccupyMapObjectRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::UnoccupyMapObjectRes::Create(pMessage, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, uint32_t InMapObjectId )



// Cmd: Use map object
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInResultAttributes,uint8_t* InResultAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::UseMapObjectRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId,SF::ArrayView<uint8_t>(_sizeOfInResultAttributes, _sizeOfInResultAttributes, InResultAttributes));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::UseMapObjectRes::Create(pMessage, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId,SF::ArrayView<uint8_t>(_sizeOfInResultAttributes, _sizeOfInResultAttributes, InResultAttributes));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceUseMapObjectRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPlayInstanceUID, PlayerID InPlayerID, StringCrc32 InMapObjectId, uint16_t _sizeOfInResultAttributes,uint8_t* InResultAttributes )



// Cmd: Send zone chatting
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::ZoneChatRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::ZoneChatRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Player state change
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InSenderID, int8_t InMessageType, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::ZoneChatS2CEvt::CalculateMessageSize( InPlayInstanceUID, InSenderID, InMessageType,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::ZoneChatS2CEvt::Create(pMessage,  InPlayInstanceUID, InSenderID, InMessageType,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceZoneChatS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InSenderID, int8_t InMessageType, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )



// S2C: Effect modifier initial sync
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceLevelUpS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int64_t InCurrentExp, int32_t InCurrentLevel )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::LevelUpS2CEvt::CalculateMessageSize( InPlayInstanceUID, InPlayerID, InCurrentExp, InCurrentLevel);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::LevelUpS2CEvt::Create(pMessage,  InPlayInstanceUID, InPlayerID, InCurrentExp, InCurrentLevel);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceLevelUpS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPlayInstanceUID, PlayerID InPlayerID, int64_t InCurrentExp, int32_t InCurrentLevel )



// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CallFunctionRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInResults, _sizeOfInResults, InResults));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CallFunctionRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInResults, _sizeOfInResults, InResults));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCallFunctionRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )



// S2C: Voice data
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceVoiceDataS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InActorID, uint16_t InFrameIndex, uint16_t _sizeOfInVoiceData,const uint8_t* InVoiceData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::VoiceDataS2CEvt::CalculateMessageSize( InActorID, InFrameIndex,SF::ArrayView<uint8_t>(_sizeOfInVoiceData, _sizeOfInVoiceData, const_cast<uint8_t*>(InVoiceData)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::VoiceDataS2CEvt::Create(pMessage,  InActorID, InFrameIndex,SF::ArrayView<uint8_t>(_sizeOfInVoiceData, _sizeOfInVoiceData, const_cast<uint8_t*>(InVoiceData)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceVoiceDataS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InActorID, uint16_t InFrameIndex, uint16_t _sizeOfInVoiceData,const uint8_t* InVoiceData )



// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::CreateStreamRes::CalculateMessageSize(InTransactionID, InResult,InStreamName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::CreateStreamRes::Create(pMessage, InTransactionID, InResult,InStreamName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceCreateStreamRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InStreamName )



// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::FindStreamRes::CalculateMessageSize(InTransactionID, InResult,InStreamName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::FindStreamRes::Create(pMessage, InTransactionID, InResult,InStreamName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceFindStreamRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InStreamName )



// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InStreamName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::PlayInstance::DeleteStreamRes::CalculateMessageSize(InTransactionID, InResult,InStreamName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::DeleteStreamRes::Create(pMessage, InTransactionID, InResult,InStreamName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceDeleteStreamRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InStreamName )



// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, intptr_t InStreamNames )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	auto& InStreamNamesArray_ = *NativeToObject<SF::ArrayObject<const char*>>(InStreamNames);
	size_t messageSize = SF::Message::PlayInstance::GetStreamListRes::CalculateMessageSize(InTransactionID, InResult,InStreamNamesArray_);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::PlayInstance::GetStreamListRes::Create(pMessage, InTransactionID, InResult,InStreamNamesArray_);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_PlayInstanceGetStreamListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, intptr_t InStreamNames )










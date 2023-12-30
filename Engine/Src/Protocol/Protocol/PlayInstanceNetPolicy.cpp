////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : PlayInstance Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/PlayInstanceNetPolicy.h"
#include "Protocol/PlayInstanceMsgClass.h"



namespace SF
{
 	// Cmd: Player Join request.
	Result NetPolicyPlayInstance::JoinPlayInstanceCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::JoinPlayInstanceCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InPlayerIdentifier);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::JoinPlayInstanceCmd::Create(messageBuffer, InTransactionID, InPlayInstanceUID, InPlayerID, InPlayerIdentifier));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::JoinPlayInstanceCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
	// C2S: Play packet
	Result NetPolicyPlayInstance::PlayPacketC2SEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::PlayPacketC2SEvt::CalculateMessageSize(InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask, InPayload);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::PlayPacketC2SEvt::Create(messageBuffer, InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask, InPayload));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::PlayPacketC2SEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
	// C2S: Player Movement
	Result NetPolicyPlayInstance::PlayerMovementC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::PlayerMovementC2SEvt::CalculateMessageSize(InPlayInstanceUID, InPlayerID, InMovement);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::PlayerMovementC2SEvt::Create(messageBuffer, InPlayInstanceUID, InPlayerID, InMovement));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::PlayerMovementC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
	Result NetPolicyPlayInstance::ClientSyncReliableC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::ClientSyncReliableC2SEvt::CalculateMessageSize(InPlayInstanceUID, InPlayerID, InSyncData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::ClientSyncReliableC2SEvt::Create(messageBuffer, InPlayInstanceUID, InPlayerID, InSyncData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::ClientSyncReliableC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
	Result NetPolicyPlayInstance::ClientSyncC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::ClientSyncC2SEvt::CalculateMessageSize(InPlayInstanceUID, InPlayerID, InSyncData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::ClientSyncC2SEvt::Create(messageBuffer, InPlayInstanceUID, InPlayerID, InSyncData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::ClientSyncC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	// Cmd: Occupy map object
	Result NetPolicyPlayInstance::OccupyMapObjectCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::OccupyMapObjectCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::OccupyMapObjectCmd::Create(messageBuffer, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::OccupyMapObjectCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
	// Cmd: Unoccupy map object
	Result NetPolicyPlayInstance::UnoccupyMapObjectCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::UnoccupyMapObjectCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::UnoccupyMapObjectCmd::Create(messageBuffer, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::UnoccupyMapObjectCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Use map object
	Result NetPolicyPlayInstance::UseMapObjectCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::UseMapObjectCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUseParameters);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::UseMapObjectCmd::Create(messageBuffer, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUseParameters));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::UseMapObjectCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
	// Cmd: Send zone chatting
	Result NetPolicyPlayInstance::ZoneChatCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::ZoneChatCmd::CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType, InChatMetaData, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::ZoneChatCmd::Create(messageBuffer, InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType, InChatMetaData, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::ZoneChatCmd( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create stream instance
	Result NetPolicyPlayInstance::CreateStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::CreateStreamCmd::CalculateMessageSize(InTransactionID, InTicket, InStreamName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::CreateStreamCmd::Create(messageBuffer, InTransactionID, InTicket, InStreamName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::CreateStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Open stream instance
	Result NetPolicyPlayInstance::FindStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::FindStreamCmd::CalculateMessageSize(InTransactionID, InTicket, InStreamName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::FindStreamCmd::Create(messageBuffer, InTransactionID, InTicket, InStreamName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::FindStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Delete stream instance
	Result NetPolicyPlayInstance::DeleteStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::DeleteStreamCmd::CalculateMessageSize(InTransactionID, InTicket, InStreamName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::DeleteStreamCmd::Create(messageBuffer, InTransactionID, InTicket, InStreamName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::DeleteStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Get stream list
	Result NetPolicyPlayInstance::GetStreamListCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::GetStreamListCmd::CalculateMessageSize(InTransactionID, InTicket);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::GetStreamListCmd::Create(messageBuffer, InTransactionID, InTicket));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::GetStreamListCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket )
	// Cmd: To call general functionality
	Result NetPolicyPlayInstance::CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::CallFunctionCmd::CalculateMessageSize(InTransactionID, InFunctionName, InPlayerID, InParameters);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::CallFunctionCmd::Create(messageBuffer, InTransactionID, InFunctionName, InPlayerID, InParameters));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
	// C2S: Send coded voice data to server
	Result NetPolicyPlayInstance::SendVoiceDataC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InVoiceData )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::SendVoiceDataC2SEvt::CalculateMessageSize(InPlayInstanceUID, InPlayerID, InVoiceData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::SendVoiceDataC2SEvt::Create(messageBuffer, InPlayInstanceUID, InPlayerID, InVoiceData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyPlayInstance::SendVoiceDataC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InVoiceData )


	// Cmd: Player Join request.
	Result NetSvrPolicyPlayInstance::JoinPlayInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::JoinPlayInstanceRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InCharacterID, InCharacterPrivateData, InMovement);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::JoinPlayInstanceRes::Create(messageBuffer, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InCharacterID, InCharacterPrivateData, InMovement));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::JoinPlayInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
	// S2C: Player kicked event. this event will be broadcasted when a player kicked.
	Result NetSvrPolicyPlayInstance::PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::PlayerKickedS2CEvt::CalculateMessageSize(InPlayInstanceUID, InKickedPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::PlayerKickedS2CEvt::Create(messageBuffer, InPlayInstanceUID, InKickedPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	// S2C: New actor in get view
	Result NetSvrPolicyPlayInstance::NewActorInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::NewActorInViewS2CEvt::CalculateMessageSize(InPlayInstanceUID, InPlayerID, InPlayerPlatformId, InPublicData, InEquipData, InMovement, InState, InStateValues);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::NewActorInViewS2CEvt::Create(messageBuffer, InPlayInstanceUID, InPlayerID, InPlayerPlatformId, InPublicData, InEquipData, InMovement, InState, InStateValues));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::NewActorInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	// S2C: Remove actor from view
	Result NetSvrPolicyPlayInstance::RemoveActorFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::RemoveActorFromViewS2CEvt::CalculateMessageSize(InPlayInstanceUID, InActorID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::RemoveActorFromViewS2CEvt::Create(messageBuffer, InPlayInstanceUID, InActorID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::RemoveActorFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )
	// S2C: Player Movement
	Result NetSvrPolicyPlayInstance::ActorMovementS2CEvt( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::ActorMovementS2CEvt::CalculateMessageSize(InPlayInstanceUID, InMovement);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::ActorMovementS2CEvt::Create(messageBuffer, InPlayInstanceUID, InMovement));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::ActorMovementS2CEvt( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )
	// S2C: Player Movement
	Result NetSvrPolicyPlayInstance::ActorMovementsS2CEvt( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::ActorMovementsS2CEvt::CalculateMessageSize(InPlayInstanceUID, InMovement);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::ActorMovementsS2CEvt::Create(messageBuffer, InPlayInstanceUID, InMovement));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::ActorMovementsS2CEvt( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
	// S2C: Player state change
	Result NetSvrPolicyPlayInstance::PlayerStateChangedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::PlayerStateChangedS2CEvt::CalculateMessageSize(InPlayInstanceUID, InPlayerID, InState, InMoveFrame, InPosition, InStateValues);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::PlayerStateChangedS2CEvt::Create(messageBuffer, InPlayInstanceUID, InPlayerID, InState, InMoveFrame, InPosition, InStateValues));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::PlayerStateChangedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
	// Cmd: Occupy map object
	Result NetSvrPolicyPlayInstance::OccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::OccupyMapObjectRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::OccupyMapObjectRes::Create(messageBuffer, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::OccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Unoccupy map object
	Result NetSvrPolicyPlayInstance::UnoccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::UnoccupyMapObjectRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::UnoccupyMapObjectRes::Create(messageBuffer, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::UnoccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Use map object
	Result NetSvrPolicyPlayInstance::UseMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::UseMapObjectRes::CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId, InResultAttributes);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::UseMapObjectRes::Create(messageBuffer, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId, InResultAttributes));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::UseMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
	// Cmd: Send zone chatting
	Result NetSvrPolicyPlayInstance::ZoneChatRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::ZoneChatRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::ZoneChatRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::ZoneChatRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Player state change
	Result NetSvrPolicyPlayInstance::ZoneChatS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::ZoneChatS2CEvt::CalculateMessageSize(InPlayInstanceUID, InSenderID, InMessageType, InChatMetaData, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::ZoneChatS2CEvt::Create(messageBuffer, InPlayInstanceUID, InSenderID, InMessageType, InChatMetaData, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::ZoneChatS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	// S2C: Effect modifier initial sync
	Result NetSvrPolicyPlayInstance::LevelUpS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::LevelUpS2CEvt::CalculateMessageSize(InPlayInstanceUID, InPlayerID, InCurrentExp, InCurrentLevel);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::LevelUpS2CEvt::Create(messageBuffer, InPlayInstanceUID, InPlayerID, InCurrentExp, InCurrentLevel));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::LevelUpS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
	// Cmd: Create stream instance
	Result NetSvrPolicyPlayInstance::CreateStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::CreateStreamRes::CalculateMessageSize(InTransactionID, InResult, InStreamName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::CreateStreamRes::Create(messageBuffer, InTransactionID, InResult, InStreamName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::CreateStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Open stream instance
	Result NetSvrPolicyPlayInstance::FindStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::FindStreamRes::CalculateMessageSize(InTransactionID, InResult, InStreamName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::FindStreamRes::Create(messageBuffer, InTransactionID, InResult, InStreamName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::FindStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Delete stream instance
	Result NetSvrPolicyPlayInstance::DeleteStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::DeleteStreamRes::CalculateMessageSize(InTransactionID, InResult, InStreamName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::DeleteStreamRes::Create(messageBuffer, InTransactionID, InResult, InStreamName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::DeleteStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Get stream list
	Result NetSvrPolicyPlayInstance::GetStreamListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::GetStreamListRes::CalculateMessageSize(InTransactionID, InResult, InStreamNames);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::GetStreamListRes::Create(messageBuffer, InTransactionID, InResult, InStreamNames));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::GetStreamListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
	// Cmd: To call general functionality
	Result NetSvrPolicyPlayInstance::CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::CallFunctionRes::CalculateMessageSize(InTransactionID, InResult, InResults);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::CallFunctionRes::Create(messageBuffer, InTransactionID, InResult, InResults));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )
	// S2C: Voice data
	Result NetSvrPolicyPlayInstance::VoiceDataS2CEvt( const uint32_t &InActorID, const Array<uint8_t>& InVoiceData )
	{
 		Result hr;

		size_t messageSize = SF::Message::PlayInstance::VoiceDataS2CEvt::CalculateMessageSize(InActorID, InVoiceData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::PlayInstance::VoiceDataS2CEvt::Create(messageBuffer, InActorID, InVoiceData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyPlayInstance::VoiceDataS2CEvt( const uint32_t &InActorID, const Array<uint8_t>& InVoiceData )


}; // namespace SF



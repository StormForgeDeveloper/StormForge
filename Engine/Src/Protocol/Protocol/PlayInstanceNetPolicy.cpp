﻿////////////////////////////////////////////////////////////////////////////////
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
	Result NetPolicyPlayInstance::JoinPlayInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::JoinPlayInstanceCmd::Create(GetSystemHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InPlayerIdentifier);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::JoinPlayInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
	// C2S: Play packet
	Result NetPolicyPlayInstance::PlayPacketC2SEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayPacketC2SEvt::Create(GetSystemHeap(), InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask, InPayload);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::PlayPacketC2SEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
	// C2S: Player Movement
	Result NetPolicyPlayInstance::PlayerMovementC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayerMovementC2SEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InMovement);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::PlayerMovementC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
	Result NetPolicyPlayInstance::ClientSyncReliableC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::ClientSyncReliableC2SEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InSyncData);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::ClientSyncReliableC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
	Result NetPolicyPlayInstance::ClientSyncC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::ClientSyncC2SEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InSyncData);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::ClientSyncC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	// Cmd: Occupy map object
	Result NetPolicyPlayInstance::OccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::OccupyMapObjectCmd::Create(GetSystemHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::OccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
	// Cmd: Unoccupy map object
	Result NetPolicyPlayInstance::UnoccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::UnoccupyMapObjectCmd::Create(GetSystemHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::UnoccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Use map object
	Result NetPolicyPlayInstance::UseMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::UseMapObjectCmd::Create(GetSystemHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUseParameters);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::UseMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
	// Cmd: Send zone chatting
	Result NetPolicyPlayInstance::ZoneChatCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::ZoneChatCmd::Create(GetSystemHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType, InChatMetaData, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::ZoneChatCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create stream instance
	Result NetPolicyPlayInstance::CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::CreateStreamCmd::Create(GetSystemHeap(), InTransactionID, InTicket, InStreamName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Open stream instance
	Result NetPolicyPlayInstance::FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::FindStreamCmd::Create(GetSystemHeap(), InTransactionID, InTicket, InStreamName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Delete stream instance
	Result NetPolicyPlayInstance::DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::DeleteStreamCmd::Create(GetSystemHeap(), InTransactionID, InTicket, InStreamName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Get stream list
	Result NetPolicyPlayInstance::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::GetStreamListCmd::Create(GetSystemHeap(), InTransactionID, InTicket);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )
	// Cmd: To call general functionality
	Result NetPolicyPlayInstance::CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::CallFunctionCmd::Create(GetSystemHeap(), InTransactionID, InFunctionName, InPlayerID, InParameters);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
	// C2S: Send coded voice data to server
	Result NetPolicyPlayInstance::SendVoiceDataC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InVoiceData )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::SendVoiceDataC2SEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InVoiceData);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::SendVoiceDataC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InVoiceData )


	// Cmd: Player Join request.
	Result NetSvrPolicyPlayInstance::JoinPlayInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::JoinPlayInstanceRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InCharacterID, InCharacterPrivateData, InMovement);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::JoinPlayInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
	// S2C: Player kicked event. this event will be broadcasted when a player kicked.
	Result NetSvrPolicyPlayInstance::PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayerKickedS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InKickedPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	// S2C: New actor in get view
	Result NetSvrPolicyPlayInstance::NewActorInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::NewActorInViewS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InPlayerPlatformId, InPublicData, InEquipData, InMovement, InState, InStateValues);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::NewActorInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	// S2C: Remove actor from view
	Result NetSvrPolicyPlayInstance::RemoveActorFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::RemoveActorFromViewS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InActorID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::RemoveActorFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )
	// S2C: Player Movement
	Result NetSvrPolicyPlayInstance::ActorMovementS2CEvt( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::ActorMovementS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InMovement);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::ActorMovementS2CEvt( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )
	// S2C: Player Movement
	Result NetSvrPolicyPlayInstance::ActorMovementsS2CEvt( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::ActorMovementsS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InMovement);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::ActorMovementsS2CEvt( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
	// S2C: Player state change
	Result NetSvrPolicyPlayInstance::PlayerStateChangedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayerStateChangedS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InState, InMoveFrame, InPosition, InStateValues);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::PlayerStateChangedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
	// Cmd: Occupy map object
	Result NetSvrPolicyPlayInstance::OccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::OccupyMapObjectRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::OccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Unoccupy map object
	Result NetSvrPolicyPlayInstance::UnoccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::UnoccupyMapObjectRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::UnoccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Use map object
	Result NetSvrPolicyPlayInstance::UseMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::UseMapObjectRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId, InResultAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::UseMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
	// Cmd: Send zone chatting
	Result NetSvrPolicyPlayInstance::ZoneChatRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::ZoneChatRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::ZoneChatRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Player state change
	Result NetSvrPolicyPlayInstance::ZoneChatS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::ZoneChatS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InSenderID, InMessageType, InChatMetaData, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::ZoneChatS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	// S2C: Effect modifier initial sync
	Result NetSvrPolicyPlayInstance::LevelUpS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::LevelUpS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InCurrentExp, InCurrentLevel);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::LevelUpS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
	// Cmd: Create stream instance
	Result NetSvrPolicyPlayInstance::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::CreateStreamRes::Create(GetSystemHeap(), InTransactionID, InResult, InStreamName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Open stream instance
	Result NetSvrPolicyPlayInstance::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::FindStreamRes::Create(GetSystemHeap(), InTransactionID, InResult, InStreamName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Delete stream instance
	Result NetSvrPolicyPlayInstance::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::DeleteStreamRes::Create(GetSystemHeap(), InTransactionID, InResult, InStreamName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Get stream list
	Result NetSvrPolicyPlayInstance::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::GetStreamListRes::Create(GetSystemHeap(), InTransactionID, InResult, InStreamNames);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
	// Cmd: To call general functionality
	Result NetSvrPolicyPlayInstance::CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::CallFunctionRes::Create(GetSystemHeap(), InTransactionID, InResult, InResults);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )
	// S2C: Voice data
	Result NetSvrPolicyPlayInstance::VoiceDataS2CEvt( const uint32_t &InActorID, const Array<uint8_t>& InVoiceData )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::VoiceDataS2CEvt::Create(GetSystemHeap(), InActorID, InVoiceData);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::VoiceDataS2CEvt( const uint32_t &InActorID, const Array<uint8_t>& InVoiceData )


}; // namespace SF



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
	// Cmd: Havest area
	Result NetPolicyPlayInstance::HarvestAreaCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::HarvestAreaCmd::Create(GetSystemHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InAreaId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyPlayInstance::HarvestAreaCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId )
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


	// Cmd: Player Join request.
	Result NetSvrPolicyPlayInstance::JoinPlayInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::JoinPlayInstanceRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMovement);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::JoinPlayInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
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
	// S2C: New Player in get view
	Result NetSvrPolicyPlayInstance::NewPlayerInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::NewPlayerInViewS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InAttributes, InMovement, InState, InStateValues);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::NewPlayerInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	// S2C: Remove player from view
	Result NetSvrPolicyPlayInstance::RemovePlayerFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::RemovePlayerFromViewS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::RemovePlayerFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID )
	// S2C: Player Movement
	Result NetSvrPolicyPlayInstance::PlayerMovementS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayerMovementS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InMovement);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::PlayerMovementS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
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
	// Cmd: Havest area
	Result NetSvrPolicyPlayInstance::HarvestAreaRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId, const VariableTable &InResultAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::HarvestAreaRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InAreaId, InResultAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyPlayInstance::HarvestAreaRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId, const VariableTable &InResultAttributes )
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


}; // namespace SF



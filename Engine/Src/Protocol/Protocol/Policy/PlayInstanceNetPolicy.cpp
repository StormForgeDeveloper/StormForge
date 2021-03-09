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
#include "Protocol/Policy/PlayInstanceNetPolicy.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"



namespace SF
{
 	// Cmd: Event for Player Join request.
	Result NetPolicyPlayInstance::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::JoinGameInstanceCmd::Create(GetSystemHeap(), InTransactionID, InPlayInstanceUID, InPlayerID, InPlayerIdentifier);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetPolicyPlayInstance::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
	// C2S: Play packet
	Result NetPolicyPlayInstance::PlayPacketC2SEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayPacketC2SEvt::Create(GetSystemHeap(), InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask, InPayload);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

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

		return hr;

	}; // Result NetPolicyPlayInstance::PlayerMovementC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	// Cmd: Create stream instance
	Result NetPolicyPlayInstance::CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::CreateStreamCmd::Create(GetSystemHeap(), InTransactionID, InTicket, InStreamName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

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

		return hr;

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

		return hr;

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

		return hr;

	}; // Result NetPolicyPlayInstance::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )


	// Cmd: Event for Player Join request.
	Result NetSvrPolicyPlayInstance::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMovementFrame )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::JoinGameInstanceRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMovementFrame);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMovementFrame )
	// S2C: Player kicked event. this event will be broadcasted when a player kicked.
	Result NetSvrPolicyPlayInstance::PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayerKickedS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InKickedPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	// S2C: New Player in get view
	Result NetSvrPolicyPlayInstance::NewPlayerInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::NewPlayerInViewS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::NewPlayerInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
	// S2C: Remove player from view
	Result NetSvrPolicyPlayInstance::RemovePlayerFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::RemovePlayerFromViewS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::RemovePlayerFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
	// S2C: Player Movement
	Result NetSvrPolicyPlayInstance::PlayerMovementS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::PlayerMovementS2CEvt::Create(GetSystemHeap(), InPlayInstanceUID, InPlayerID, InMovement);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::PlayerMovementS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	// Cmd: Create stream instance
	Result NetSvrPolicyPlayInstance::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::CreateStreamRes::Create(GetSystemHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
	// Cmd: Open stream instance
	Result NetSvrPolicyPlayInstance::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::FindStreamRes::Create(GetSystemHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
	// Cmd: Delete stream instance
	Result NetSvrPolicyPlayInstance::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::DeleteStreamRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Get stream list
	Result NetSvrPolicyPlayInstance::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::PlayInstance::GetStreamListRes::Create(GetSystemHeap(), InTransactionID, InResult, InStreamNames);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

		return hr;

	}; // Result NetSvrPolicyPlayInstance::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )


}; // namespace SF



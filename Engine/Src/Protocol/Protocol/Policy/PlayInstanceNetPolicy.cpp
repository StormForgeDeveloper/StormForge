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
#include "Net/SFConnection.h"
#include "Protocol/Policy/PlayInstanceNetPolicy.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"



namespace SF
{
 	namespace Policy
	{
 		// Cmd: Event for Player Join request.
		Result NetPolicyPlayInstance::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint32_t &InPlayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::JoinGameInstanceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayInstanceID, InPlayerID, InPlayerIdentifier);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyPlayInstance::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint32_t &InPlayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
		// C2S: Play packet
		Result NetPolicyPlayInstance::PlayPacketC2SEvt( const uint32_t &InPlayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::PlayPacketC2SEvt::Create(m_pConnection->GetIOHeap(), InPlayInstanceID, InSenderEndpointID, InTargetEndpointMask, InPayload);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyPlayInstance::PlayPacketC2SEvt( const uint32_t &InPlayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
		// C2S: Player Movement
		Result NetPolicyPlayInstance::PlayerMovementC2SEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::PlayerMovementC2SEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyPlayInstance::PlayerMovementC2SEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// Cmd: Create stream instance
		Result NetPolicyPlayInstance::CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::CreateStreamCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyPlayInstance::CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Open stream instance
		Result NetPolicyPlayInstance::FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::FindStreamCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyPlayInstance::FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Delete stream instance
		Result NetPolicyPlayInstance::DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::DeleteStreamCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyPlayInstance::DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Get stream list
		Result NetPolicyPlayInstance::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::GetStreamListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyPlayInstance::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )


		// Cmd: Event for Player Join request.
		Result NetSvrPolicyPlayInstance::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InPlayInstanceID, const uint32_t &InMyEndpointID, const Array<PlayerInformation>& InMemberInfos )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::JoinGameInstanceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayInstanceID, InMyEndpointID, InMemberInfos);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InPlayInstanceID, const uint32_t &InMyEndpointID, const Array<PlayerInformation>& InMemberInfos )
		// S2C: Event for Player joined.
		Result NetSvrPolicyPlayInstance::PlayerJoinS2CEvt( const uint32_t &InPlayInstanceID, const PlayerInformation &InJoinedPlayerInfo )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::PlayerJoinS2CEvt::Create(m_pConnection->GetIOHeap(), InPlayInstanceID, InJoinedPlayerInfo);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::PlayerJoinS2CEvt( const uint32_t &InPlayInstanceID, const PlayerInformation &InJoinedPlayerInfo )
		// S2C: Event for Player left.
		Result NetSvrPolicyPlayInstance::PlayerLeftS2CEvt( const uint32_t &InPlayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::PlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InPlayInstanceID, InLeftPlayerID, InKickedReason);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::PlayerLeftS2CEvt( const uint32_t &InPlayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
		// S2C: New Player in get view
		Result NetSvrPolicyPlayInstance::NewPlayerInViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::NewPlayerInViewS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::NewPlayerInViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// S2C: Remove player from view
		Result NetSvrPolicyPlayInstance::RemovePlayerFromViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::RemovePlayerFromViewS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::RemovePlayerFromViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// S2C: Player Movement
		Result NetSvrPolicyPlayInstance::PlayerMovementS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::PlayerMovementS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::PlayerMovementS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// Cmd: Create stream instance
		Result NetSvrPolicyPlayInstance::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::CreateStreamRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		// Cmd: Open stream instance
		Result NetSvrPolicyPlayInstance::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::FindStreamRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		// Cmd: Delete stream instance
		Result NetSvrPolicyPlayInstance::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::DeleteStreamRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Get stream list
		Result NetSvrPolicyPlayInstance::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::PlayInstance::GetStreamListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamNames);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyPlayInstance::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )


	}; // namespace Policy
}; // namespace SF



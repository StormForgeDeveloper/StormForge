////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Relay Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFConnection.h"
#include "Protocol/Policy/RelayNetPolicy.h"
#include "Protocol/Message/RelayMsgClass.h"



namespace SF
{
 	namespace Policy
	{
 		// C2S: Event for Player Join request.
		Result NetPolicyRelay::JoinRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::JoinRelayInstanceC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InPlayerID, InPlayerIdentifier);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::JoinRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
		// C2S: Event for Player Join request.
		Result NetPolicyRelay::LeaveRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::LeaveRelayInstanceC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::LeaveRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
		// C2S: Relay packet
		Result NetPolicyRelay::RelayPacketC2SEvt( const uint32_t &InRelayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::RelayPacketC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InSenderEndpointID, InTargetEndpointMask, InPayload);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::RelayPacketC2SEvt( const uint32_t &InRelayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
		// Cmd: Create stream instance
		Result NetPolicyRelay::CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::CreateStreamCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Open stream instance
		Result NetPolicyRelay::FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::FindStreamCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Delete stream instance
		Result NetPolicyRelay::DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::DeleteStreamCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Get stream list
		Result NetPolicyRelay::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::GetStreamListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )


		// S2C: Event for joined player
		Result NetSvrPolicyRelay::JoinRelayInstanceResS2CEvt( const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyEndpointID, const Array<RelayPlayerInfo>& InMemberInfos )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::JoinRelayInstanceResS2CEvt::Create(m_pConnection->GetIOHeap(), InResult, InRelayInstanceID, InMyEndpointID, InMemberInfos);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::JoinRelayInstanceResS2CEvt( const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyEndpointID, const Array<RelayPlayerInfo>& InMemberInfos )
		// S2C: Event for Player joined.
		Result NetSvrPolicyRelay::PlayerJoinS2CEvt( const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::PlayerJoinS2CEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InJoinedPlayerInfo);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::PlayerJoinS2CEvt( const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
		// S2C: Event for Player left.
		Result NetSvrPolicyRelay::PlayerLeftS2CEvt( const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::PlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InLeftPlayerID, InKickedReason);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::PlayerLeftS2CEvt( const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
		// Cmd: Create stream instance
		Result NetSvrPolicyRelay::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::CreateStreamRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		// Cmd: Open stream instance
		Result NetSvrPolicyRelay::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::FindStreamRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		// Cmd: Delete stream instance
		Result NetSvrPolicyRelay::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::DeleteStreamRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Get stream list
		Result NetSvrPolicyRelay::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::GetStreamListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamNames);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )


	}; // namespace Policy
}; // namespace SF



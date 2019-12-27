////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromFOrge
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
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Relay::JoinRelayInstanceC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InPlayerID, InPlayerIdentifier);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyRelay::JoinRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
		// C2S: Event for Player Join request.
		Result NetPolicyRelay::LeaveRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Relay::LeaveRelayInstanceC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyRelay::LeaveRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
		// C2S: Relay packet
		Result NetPolicyRelay::RelayPacketC2SEvt( const uint32_t &InRelayInstanceID, const uint32_t &InSenderRelayID, const uint32_t &InTargetRelayMask, const Array<uint8_t>& InPayload )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Relay::RelayPacketC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InSenderRelayID, InTargetRelayMask, InPayload);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyRelay::RelayPacketC2SEvt( const uint32_t &InRelayInstanceID, const uint32_t &InSenderRelayID, const uint32_t &InTargetRelayMask, const Array<uint8_t>& InPayload )


		// S2C: Event for joined player
		Result NetSvrPolicyRelay::JoinRelayInstanceResS2CEvt( const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyPlayerRelayID, const Array<RelayPlayerInfo>& InMemberInfos )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Relay::JoinRelayInstanceResS2CEvt::Create(m_pConnection->GetIOHeap(), InResult, InRelayInstanceID, InMyPlayerRelayID, InMemberInfos);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyRelay::JoinRelayInstanceResS2CEvt( const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyPlayerRelayID, const Array<RelayPlayerInfo>& InMemberInfos )
		// S2C: Event for Player joined.
		Result NetSvrPolicyRelay::PlayerJoinS2CEvt( const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Relay::PlayerJoinS2CEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InJoinedPlayerInfo);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyRelay::PlayerJoinS2CEvt( const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
		// S2C: Event for Player left.
		Result NetSvrPolicyRelay::PlayerLeftS2CEvt( const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Relay::PlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InLeftPlayerID, InKickedReason);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyRelay::PlayerLeftS2CEvt( const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )


	}; // namespace Policy
}; // namespace SF



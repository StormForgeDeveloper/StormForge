////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Generic Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/GenericNetPolicy.h"
#include "Protocol/GenericMsgClass.h"



namespace SF
{
 	// Cmd: Generic failure message
	Result NetPolicyGeneric::GenericFailureCmd( const RouteContext &InRouteContext, const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Generic::GenericFailureCmd::CalculateMessageSize(InRouteContext, InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Generic::GenericFailureCmd::Create(messageBuffer, InRouteContext, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGeneric::GenericFailureCmd( const RouteContext &InRouteContext, const uint64_t &InTransactionID )


	// Cmd: Generic failure message
	Result NetSvrPolicyGeneric::GenericFailureRes( const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Generic::GenericFailureRes::CalculateMessageSize(InRouteContext, InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Generic::GenericFailureRes::Create(messageBuffer, InRouteContext, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGeneric::GenericFailureRes( const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )


}; // namespace SF



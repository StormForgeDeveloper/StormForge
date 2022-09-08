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
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Generic::GenericFailureCmd::Create(GetSystemHeap(), InRouteContext, InTransactionID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGeneric::GenericFailureCmd( const RouteContext &InRouteContext, const uint64_t &InTransactionID )


	// Cmd: Generic failure message
	Result NetSvrPolicyGeneric::GenericFailureRes( const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Generic::GenericFailureRes::Create(GetSystemHeap(), InRouteContext, InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGeneric::GenericFailureRes( const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )


}; // namespace SF



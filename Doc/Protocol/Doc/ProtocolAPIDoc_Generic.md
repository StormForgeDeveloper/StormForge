***
 
 CopyRight (c) 2024 StormForge
 
 Description : Generic Message Protocol API Document

***



Generic Protocol

namespace SF::Message::Generic


# Protocol interface class NetPolicyGeneric
## GenericFailure Request
Generic failure message

1. Command interface

        Result GenericFailureCmd(const RouteContext &InRouteContext, const TransactionID &InTransactionID)

		- RouteContext: type:RouteContext, 

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to GenericFailureRes to access values


		- RouteContext: type:RouteContext, 
		- TransactionID: type:TransactionID, 
		- Result: type:Result, 









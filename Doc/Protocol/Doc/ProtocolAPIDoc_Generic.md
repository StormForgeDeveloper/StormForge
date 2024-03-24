***
 
 CopyRight (c) 2024 StormForge
 
 Description : Generic Message Protocol API Document

***



Generic Protocol

namespace SF::Message::Generic


# Protocol interface class GenericRPCSendAdapter
## GenericFailure Request
Generic failure message

1. Command interface

        Result GenericFailureCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to GenericFailureRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## GenericTransaction Request
Generic transaction result

1. Command interface

        Result GenericTransactionCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to GenericTransactionRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- FinishedTransaction: type:TransactionID, TransactionId
		- Signature: type:String, Transaction signature









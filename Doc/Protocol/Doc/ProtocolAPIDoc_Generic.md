***
 
 CopyRight (c) 2025 StormForge
 
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


## Heartbeat Request
Generic heartbeat

1. Command interface

        Result HeartbeatCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to HeartbeatRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## PostLogData Request
Post log data through gateway

1. Command interface

        Result PostLogDataCmd(const TransactionID &InTransactionID, const char* InDestLogChannel, const Array<uint8_t>& InMessageData)

		- TransactionID: type:TransactionID, 

		- DestLogChannel: type:String, Destination log channel to post log data

		- MessageData: type:uint8, Message data

2. Result interface

C++: Cast message to PostLogDataRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 









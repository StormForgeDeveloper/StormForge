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


## MessageBusSend Request
Message bus send message warpper through gateway. it conveys other message inside

1. Command interface

        Result MessageBusSendCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to MessageBusSendRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- DestChannel: type:String, Destination channel to post message data
		- MessageData: type:uint8, Message data


## MessageBusListen Request
Listen to the message

1. Command interface

        Result MessageBusListenCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to MessageBusListenRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- ChannelToListen: type:String, Channel to listen to


## PostLogData Request
Post log data through gateway

1. Command interface

        Result PostLogDataCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to PostLogDataRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- DestLogChannel: type:String, Destination log channel to post log data
		- MessageData: type:uint8, Message data









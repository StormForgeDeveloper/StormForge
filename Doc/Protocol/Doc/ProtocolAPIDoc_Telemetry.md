***
 
 CopyRight (c) 2024 StormForge
 
 Description : Telemetry Message Protocol API Document

***



Telemetry Protocol

namespace SF::Message::Telemetry


# Protocol interface class NetPolicyTelemetry
## PostEvent Request
Post telemetry event

1. Command interface

        Result PostEventCmd(const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes)

		- TransactionID: type:TransactionID, 

		- EventName: type:String, Name of the event

		- TimeStamp: type:uint64, Linux UCT time64_t

		- AppID: type:String, Application Id, alternatively GameID

		- MachineID: type:String, Machine unique Id

		- EventID: type:uint32, event unique Id assigned by client

		- AccountID: type:AccountID, AccountId

		- IsPlayEvent: type:bool, true if it is a play event

		- SessionID: type:uint8, Session Id, UUID byte stream

		- Attributes: type:NamedVariable, Attributes, array of named variables

2. Result interface

C++: Cast message to PostEventRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 









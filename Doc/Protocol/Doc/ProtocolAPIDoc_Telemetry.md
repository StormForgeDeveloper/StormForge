***
 
 CopyRight (c) 2024 StormForge
 
 Description : Telemetry Message Protocol API Document

***



Telemetry Protocol

namespace SF::Message::Telemetry


# Protocol interface class TelemetryRPCSendAdapter
## PostEvent Request
Post telemetry event

1. Command interface

        Result PostEventCmd(const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const Guid &InTitle, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const bool &InIsPlayEvent, const Guid &InSessionID, const Array<NamedVariable>& InAttributes)

		- TransactionID: type:TransactionID, 

		- EventName: type:String, Name of the event

		- TimeStamp: type:uint64, Linux UCT time64_t

		- Title: type:Guid, TitleUID

		- MachineID: type:String, Machine unique Id

		- EventID: type:uint32, event unique Id assigned by client

		- AccountID: type:AccountID, AccountId

		- IsPlayEvent: type:bool, true if it is a play event

		- SessionID: type:Guid, Session Id, UUID byte stream

		- Attributes: type:NamedVariable, Attributes, array of named variables

2. Result interface

C++: Cast message to PostEventRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 









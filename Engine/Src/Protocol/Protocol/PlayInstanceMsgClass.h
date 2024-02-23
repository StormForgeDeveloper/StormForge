////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : PlayInstance Message parser definitions
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Protocol/SFProtocol.h"
#include "Net/SFMessage.h"
#include "Types/SFEngineTypedefs.h"
#include "Variable/SFVariableTable.h"
#include "Container/SFArray.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Variable/SFVariableMapBuilder.h"



namespace SF
{
 	namespace Message
	{
 		namespace PlayInstance
		{
 			// Cmd: Player Join request.
			class JoinPlayInstanceCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				const char* m_PlayerIdentifier{};
			public:
				JoinPlayInstanceCmd()
					{}

				JoinPlayInstanceCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinPlayInstanceCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const char* GetPlayerIdentifier() const	{ return m_PlayerIdentifier; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier );

			}; // class JoinPlayInstanceCmd : public MessageBase

			class JoinPlayInstanceRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				CharacterID m_CharacterID{};
				ArrayView<uint8_t> m_CharacterPrivateDataRaw;
				mutable bool m_CharacterPrivateDataHasParsed = false;
				mutable VariableTable m_CharacterPrivateData;
				ActorMovement m_Movement{};
			public:
				JoinPlayInstanceRes()
					{}

				JoinPlayInstanceRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinPlayInstanceRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const CharacterID& GetCharacterID() const	{ return m_CharacterID; };
				const Array<uint8_t>& GetCharacterPrivateDataRaw() const	{ return m_CharacterPrivateDataRaw; };
				const VariableTable& GetCharacterPrivateData() const;
				const ActorMovement& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement );

			}; // class JoinPlayInstanceRes : public MessageBase

			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			class PlayerKickedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_KickedPlayerID{};
			public:
				PlayerKickedS2CEvt()
					{}

				PlayerKickedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PlayerKickedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetKickedPlayerID() const	{ return m_KickedPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID );

			}; // class PlayerKickedS2CEvt : public MessageBase

			// C2S: Play packet
			class PlayPacketC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				uint32_t m_SenderEndpointID{};
				uint32_t m_TargetEndpointMask{};
				ArrayView<uint8_t> m_Payload;
			public:
				PlayPacketC2SEvt()
					{}

				PlayPacketC2SEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PlayPacketC2SEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const uint32_t& GetSenderEndpointID() const	{ return m_SenderEndpointID; };
				const uint32_t& GetTargetEndpointMask() const	{ return m_TargetEndpointMask; };
				const Array<uint8_t>& GetPayload() const	{ return m_Payload; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );

			}; // class PlayPacketC2SEvt : public MessageBase

			// S2C: New actor in get view
			class NewActorInViewS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				PlayerPlatformID m_PlayerPlatformId{};
				ArrayView<uint8_t> m_PublicDataRaw;
				mutable bool m_PublicDataHasParsed = false;
				mutable VariableTable m_PublicData;
				ArrayView<uint8_t> m_EquipDataRaw;
				mutable bool m_EquipDataHasParsed = false;
				mutable VariableTable m_EquipData;
				ActorMovement m_Movement{};
				StringCrc32 m_State{};
				ArrayView<uint8_t> m_StateValuesRaw;
				mutable bool m_StateValuesHasParsed = false;
				mutable VariableTable m_StateValues;
			public:
				NewActorInViewS2CEvt()
					{}

				NewActorInViewS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				NewActorInViewS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const PlayerPlatformID& GetPlayerPlatformId() const	{ return m_PlayerPlatformId; };
				const Array<uint8_t>& GetPublicDataRaw() const	{ return m_PublicDataRaw; };
				const VariableTable& GetPublicData() const;
				const Array<uint8_t>& GetEquipDataRaw() const	{ return m_EquipDataRaw; };
				const VariableTable& GetEquipData() const;
				const ActorMovement& GetMovement() const	{ return m_Movement; };
				const StringCrc32& GetState() const	{ return m_State; };
				const Array<uint8_t>& GetStateValuesRaw() const	{ return m_StateValuesRaw; };
				const VariableTable& GetStateValues() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues );

			}; // class NewActorInViewS2CEvt : public MessageBase

			// S2C: Remove actor from view
			class RemoveActorFromViewS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				uint32_t m_ActorID{};
			public:
				RemoveActorFromViewS2CEvt()
					{}

				RemoveActorFromViewS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RemoveActorFromViewS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const uint32_t& GetActorID() const	{ return m_ActorID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const uint32_t &InActorID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const uint32_t &InActorID );

			}; // class RemoveActorFromViewS2CEvt : public MessageBase

			// C2S: Player Movement
			class PlayerMovementC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ActorMovement m_Movement{};
			public:
				PlayerMovementC2SEvt()
					{}

				PlayerMovementC2SEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PlayerMovementC2SEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const ActorMovement& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );

			}; // class PlayerMovementC2SEvt : public MessageBase

			// S2C: Player Movement
			class ActorMovementS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				ActorMovement m_Movement{};
			public:
				ActorMovementS2CEvt()
					{}

				ActorMovementS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ActorMovementS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const ActorMovement& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement );

			}; // class ActorMovementS2CEvt : public MessageBase

			// S2C: Player Movement
			class ActorMovementsS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				ArrayView<ActorMovement> m_Movement;
			public:
				ActorMovementsS2CEvt()
					{}

				ActorMovementsS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ActorMovementsS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const Array<ActorMovement>& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement );

			}; // class ActorMovementsS2CEvt : public MessageBase

			// S2C: Player state change
			class PlayerStateChangedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				StringCrc32 m_State{};
				uint32_t m_MoveFrame{};
				Vector4 m_Position{};
				ArrayView<uint8_t> m_StateValuesRaw;
				mutable bool m_StateValuesHasParsed = false;
				mutable VariableTable m_StateValues;
			public:
				PlayerStateChangedS2CEvt()
					{}

				PlayerStateChangedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PlayerStateChangedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetState() const	{ return m_State; };
				const uint32_t& GetMoveFrame() const	{ return m_MoveFrame; };
				const Vector4& GetPosition() const	{ return m_Position; };
				const Array<uint8_t>& GetStateValuesRaw() const	{ return m_StateValuesRaw; };
				const VariableTable& GetStateValues() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues );

			}; // class PlayerStateChangedS2CEvt : public MessageBase

			// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			class ClientSyncReliableC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_SyncDataRaw;
				mutable bool m_SyncDataHasParsed = false;
				mutable VariableTable m_SyncData;
			public:
				ClientSyncReliableC2SEvt()
					{}

				ClientSyncReliableC2SEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ClientSyncReliableC2SEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetSyncDataRaw() const	{ return m_SyncDataRaw; };
				const VariableTable& GetSyncData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );

			}; // class ClientSyncReliableC2SEvt : public MessageBase

			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			class ClientSyncC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_SyncDataRaw;
				mutable bool m_SyncDataHasParsed = false;
				mutable VariableTable m_SyncData;
			public:
				ClientSyncC2SEvt()
					{}

				ClientSyncC2SEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ClientSyncC2SEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetSyncDataRaw() const	{ return m_SyncDataRaw; };
				const VariableTable& GetSyncData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );

			}; // class ClientSyncC2SEvt : public MessageBase

			// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
			class SetCharacterPublicMessageCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				const char* m_PublicMessage{};
			public:
				SetCharacterPublicMessageCmd()
					{}

				SetCharacterPublicMessageCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SetCharacterPublicMessageCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const char* GetPublicMessage() const	{ return m_PublicMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage );

			}; // class SetCharacterPublicMessageCmd : public MessageBase

			class SetCharacterPublicMessageRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
			public:
				SetCharacterPublicMessageRes()
					{}

				SetCharacterPublicMessageRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SetCharacterPublicMessageRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class SetCharacterPublicMessageRes : public MessageBase

			// S2C: Character's private data has changed
			class CharacterPrivateDataChangedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				uint32_t m_CharacterID{};
				ArrayView<uint8_t> m_PrivateDataRaw;
				mutable bool m_PrivateDataHasParsed = false;
				mutable VariableTable m_PrivateData;
			public:
				CharacterPrivateDataChangedS2CEvt()
					{}

				CharacterPrivateDataChangedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CharacterPrivateDataChangedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetCharacterID() const	{ return m_CharacterID; };
				const Array<uint8_t>& GetPrivateDataRaw() const	{ return m_PrivateDataRaw; };
				const VariableTable& GetPrivateData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const VariableTable &InPrivateData );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const Array<uint8_t>& InPrivateData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const Array<uint8_t>& InPrivateData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const VariableTable &InPrivateData );

			}; // class CharacterPrivateDataChangedS2CEvt : public MessageBase

			// S2C: Player public data has been changed
			class CharacterPublicDataChangedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_PublicDataRaw;
				mutable bool m_PublicDataHasParsed = false;
				mutable VariableTable m_PublicData;
			public:
				CharacterPublicDataChangedS2CEvt()
					{}

				CharacterPublicDataChangedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CharacterPublicDataChangedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetPublicDataRaw() const	{ return m_PublicDataRaw; };
				const VariableTable& GetPublicData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData );

			}; // class CharacterPublicDataChangedS2CEvt : public MessageBase

			// Cmd: Request WhiteboardSharing
			class RequestWhiteboardSharingCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				PlayerID m_TargetPlayerID{};
				ArrayView<uint8_t> m_WhiteboardInfoRaw;
				mutable bool m_WhiteboardInfoHasParsed = false;
				mutable VariableTable m_WhiteboardInfo;
			public:
				RequestWhiteboardSharingCmd()
					{}

				RequestWhiteboardSharingCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestWhiteboardSharingCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const PlayerID& GetTargetPlayerID() const	{ return m_TargetPlayerID; };
				const Array<uint8_t>& GetWhiteboardInfoRaw() const	{ return m_WhiteboardInfoRaw; };
				const VariableTable& GetWhiteboardInfo() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo );

			}; // class RequestWhiteboardSharingCmd : public MessageBase

			class RequestWhiteboardSharingRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
			public:
				RequestWhiteboardSharingRes()
					{}

				RequestWhiteboardSharingRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestWhiteboardSharingRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class RequestWhiteboardSharingRes : public MessageBase

			// Cmd: Accept WhiteboardSharing
			class AcceptWhiteboardSharingCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				PlayerID m_RequestedPlayerID{};
				uint8_t m_Answer{};
			public:
				AcceptWhiteboardSharingCmd()
					{}

				AcceptWhiteboardSharingCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AcceptWhiteboardSharingCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const PlayerID& GetRequestedPlayerID() const	{ return m_RequestedPlayerID; };
				const uint8_t& GetAnswer() const	{ return m_Answer; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer );

			}; // class AcceptWhiteboardSharingCmd : public MessageBase

			class AcceptWhiteboardSharingRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
			public:
				AcceptWhiteboardSharingRes()
					{}

				AcceptWhiteboardSharingRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AcceptWhiteboardSharingRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class AcceptWhiteboardSharingRes : public MessageBase

			// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
			class CloseWhiteboardSharingCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
			public:
				CloseWhiteboardSharingCmd()
					{}

				CloseWhiteboardSharingCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CloseWhiteboardSharingCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID );

			}; // class CloseWhiteboardSharingCmd : public MessageBase

			class CloseWhiteboardSharingRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
			public:
				CloseWhiteboardSharingRes()
					{}

				CloseWhiteboardSharingRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CloseWhiteboardSharingRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class CloseWhiteboardSharingRes : public MessageBase

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			class AddWhiteboardSharingLogEntryCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_LogEntryRaw;
				mutable bool m_LogEntryHasParsed = false;
				mutable VariableTable m_LogEntry;
			public:
				AddWhiteboardSharingLogEntryCmd()
					{}

				AddWhiteboardSharingLogEntryCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AddWhiteboardSharingLogEntryCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetLogEntryRaw() const	{ return m_LogEntryRaw; };
				const VariableTable& GetLogEntry() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );

			}; // class AddWhiteboardSharingLogEntryCmd : public MessageBase

			class AddWhiteboardSharingLogEntryRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				LogEntryID m_LogEntryID{};
			public:
				AddWhiteboardSharingLogEntryRes()
					{}

				AddWhiteboardSharingLogEntryRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AddWhiteboardSharingLogEntryRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const LogEntryID& GetLogEntryID() const	{ return m_LogEntryID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const LogEntryID &InLogEntryID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const LogEntryID &InLogEntryID );

			}; // class AddWhiteboardSharingLogEntryRes : public MessageBase

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			class UpdateWhiteboardSharingLogEntryCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_LogEntryRaw;
				mutable bool m_LogEntryHasParsed = false;
				mutable VariableTable m_LogEntry;
			public:
				UpdateWhiteboardSharingLogEntryCmd()
					{}

				UpdateWhiteboardSharingLogEntryCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UpdateWhiteboardSharingLogEntryCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetLogEntryRaw() const	{ return m_LogEntryRaw; };
				const VariableTable& GetLogEntry() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );

			}; // class UpdateWhiteboardSharingLogEntryCmd : public MessageBase

			class UpdateWhiteboardSharingLogEntryRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
			public:
				UpdateWhiteboardSharingLogEntryRes()
					{}

				UpdateWhiteboardSharingLogEntryRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UpdateWhiteboardSharingLogEntryRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class UpdateWhiteboardSharingLogEntryRes : public MessageBase

			// Cmd: Update whiteboard log entry
			class RemoveWhiteboardSharingLogEntryCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				LogEntryID m_LogEntryID{};
			public:
				RemoveWhiteboardSharingLogEntryCmd()
					{}

				RemoveWhiteboardSharingLogEntryCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RemoveWhiteboardSharingLogEntryCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const LogEntryID& GetLogEntryID() const	{ return m_LogEntryID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const LogEntryID &InLogEntryID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const LogEntryID &InLogEntryID );

			}; // class RemoveWhiteboardSharingLogEntryCmd : public MessageBase

			class RemoveWhiteboardSharingLogEntryRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
			public:
				RemoveWhiteboardSharingLogEntryRes()
					{}

				RemoveWhiteboardSharingLogEntryRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RemoveWhiteboardSharingLogEntryRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class RemoveWhiteboardSharingLogEntryRes : public MessageBase

			// S2C: WhiteboardSharing has been requested
			class WhiteboardSharingRequestedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				PlayerID m_RequestedPlayerID{};
			public:
				WhiteboardSharingRequestedS2CEvt()
					{}

				WhiteboardSharingRequestedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhiteboardSharingRequestedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const PlayerID& GetRequestedPlayerID() const	{ return m_RequestedPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID );

			}; // class WhiteboardSharingRequestedS2CEvt : public MessageBase

			// S2C: WhiteboardSharing has been requested
			class WhiteboardSharingRejectedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				PlayerID m_RejectedPlayerID{};
			public:
				WhiteboardSharingRejectedS2CEvt()
					{}

				WhiteboardSharingRejectedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhiteboardSharingRejectedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const PlayerID& GetRejectedPlayerID() const	{ return m_RejectedPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID );

			}; // class WhiteboardSharingRejectedS2CEvt : public MessageBase

			// S2C: WhiteboardSharing has been started
			class WhiteboardSharingStartedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				PlayerID m_OtherPlayerID{};
				ArrayView<uint8_t> m_WhiteboardInfoRaw;
				mutable bool m_WhiteboardInfoHasParsed = false;
				mutable VariableTable m_WhiteboardInfo;
			public:
				WhiteboardSharingStartedS2CEvt()
					{}

				WhiteboardSharingStartedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhiteboardSharingStartedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const PlayerID& GetOtherPlayerID() const	{ return m_OtherPlayerID; };
				const Array<uint8_t>& GetWhiteboardInfoRaw() const	{ return m_WhiteboardInfoRaw; };
				const VariableTable& GetWhiteboardInfo() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo );

			}; // class WhiteboardSharingStartedS2CEvt : public MessageBase

			// S2C: WhiteboardSharing has been closed
			class WhiteboardSharingHasClosedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				PlayerID m_ClosedPlayerID{};
			public:
				WhiteboardSharingHasClosedS2CEvt()
					{}

				WhiteboardSharingHasClosedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhiteboardSharingHasClosedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const PlayerID& GetClosedPlayerID() const	{ return m_ClosedPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID );

			}; // class WhiteboardSharingHasClosedS2CEvt : public MessageBase

			// S2C: WhiteboardSharing new log entry has been added
			class WhiteboardSharingNewLogEntryAddedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_LogEntryRaw;
				mutable bool m_LogEntryHasParsed = false;
				mutable VariableTable m_LogEntry;
			public:
				WhiteboardSharingNewLogEntryAddedS2CEvt()
					{}

				WhiteboardSharingNewLogEntryAddedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhiteboardSharingNewLogEntryAddedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetLogEntryRaw() const	{ return m_LogEntryRaw; };
				const VariableTable& GetLogEntry() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );

			}; // class WhiteboardSharingNewLogEntryAddedS2CEvt : public MessageBase

			// S2C: WhiteboardSharing new log entry has been removed
			class WhiteboardSharingNewLogEntryRemovedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				LogEntryID m_LogEntryID{};
			public:
				WhiteboardSharingNewLogEntryRemovedS2CEvt()
					{}

				WhiteboardSharingNewLogEntryRemovedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhiteboardSharingNewLogEntryRemovedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const LogEntryID& GetLogEntryID() const	{ return m_LogEntryID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const LogEntryID &InLogEntryID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const LogEntryID &InLogEntryID );

			}; // class WhiteboardSharingNewLogEntryRemovedS2CEvt : public MessageBase

			// S2C: WhiteboardSharing new log entry has been updated
			class WhiteboardSharingNewLogEntryUpdatedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_LogEntryRaw;
				mutable bool m_LogEntryHasParsed = false;
				mutable VariableTable m_LogEntry;
			public:
				WhiteboardSharingNewLogEntryUpdatedS2CEvt()
					{}

				WhiteboardSharingNewLogEntryUpdatedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhiteboardSharingNewLogEntryUpdatedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetLogEntryRaw() const	{ return m_LogEntryRaw; };
				const VariableTable& GetLogEntry() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );

			}; // class WhiteboardSharingNewLogEntryUpdatedS2CEvt : public MessageBase

			// Cmd: Occupy map object
			class OccupyMapObjectCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				uint32_t m_MapObjectId{};
				uint32_t m_UsageId{};
			public:
				OccupyMapObjectCmd()
					{}

				OccupyMapObjectCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				OccupyMapObjectCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };
				const uint32_t& GetUsageId() const	{ return m_UsageId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId );

			}; // class OccupyMapObjectCmd : public MessageBase

			class OccupyMapObjectRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				uint32_t m_MapObjectId{};
			public:
				OccupyMapObjectRes()
					{}

				OccupyMapObjectRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				OccupyMapObjectRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );

			}; // class OccupyMapObjectRes : public MessageBase

			// Cmd: Unoccupy map object
			class UnoccupyMapObjectCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				uint32_t m_MapObjectId{};
			public:
				UnoccupyMapObjectCmd()
					{}

				UnoccupyMapObjectCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UnoccupyMapObjectCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );

			}; // class UnoccupyMapObjectCmd : public MessageBase

			class UnoccupyMapObjectRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				uint32_t m_MapObjectId{};
			public:
				UnoccupyMapObjectRes()
					{}

				UnoccupyMapObjectRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UnoccupyMapObjectRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );

			}; // class UnoccupyMapObjectRes : public MessageBase

			// Cmd: Use map object
			class UseMapObjectCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				StringCrc32 m_MapObjectId{};
				ArrayView<uint8_t> m_UseParametersRaw;
				mutable bool m_UseParametersHasParsed = false;
				mutable VariableTable m_UseParameters;
			public:
				UseMapObjectCmd()
					{}

				UseMapObjectCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UseMapObjectCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetMapObjectId() const	{ return m_MapObjectId; };
				const Array<uint8_t>& GetUseParametersRaw() const	{ return m_UseParametersRaw; };
				const VariableTable& GetUseParameters() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters );

			}; // class UseMapObjectCmd : public MessageBase

			class UseMapObjectRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				StringCrc32 m_MapObjectId{};
				ArrayView<uint8_t> m_ResultAttributesRaw;
				mutable bool m_ResultAttributesHasParsed = false;
				mutable VariableTable m_ResultAttributes;
			public:
				UseMapObjectRes()
					{}

				UseMapObjectRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UseMapObjectRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetMapObjectId() const	{ return m_MapObjectId; };
				const Array<uint8_t>& GetResultAttributesRaw() const	{ return m_ResultAttributesRaw; };
				const VariableTable& GetResultAttributes() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes );

			}; // class UseMapObjectRes : public MessageBase

			// Cmd: Send zone chatting
			class ZoneChatCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				int8_t m_MessageType{};
				ArrayView<uint8_t> m_ChatMetaDataRaw;
				mutable bool m_ChatMetaDataHasParsed = false;
				mutable VariableTable m_ChatMetaData;
				const char* m_ChatMessage{};
			public:
				ZoneChatCmd()
					{}

				ZoneChatCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ZoneChatCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const int8_t& GetMessageType() const	{ return m_MessageType; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class ZoneChatCmd : public MessageBase

			class ZoneChatRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
			public:
				ZoneChatRes()
					{}

				ZoneChatRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ZoneChatRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class ZoneChatRes : public MessageBase

			// S2C: Player state change
			class ZoneChatS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_SenderID{};
				int8_t m_MessageType{};
				ArrayView<uint8_t> m_ChatMetaDataRaw;
				mutable bool m_ChatMetaDataHasParsed = false;
				mutable VariableTable m_ChatMetaData;
				const char* m_ChatMessage{};
			public:
				ZoneChatS2CEvt()
					{}

				ZoneChatS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ZoneChatS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetSenderID() const	{ return m_SenderID; };
				const int8_t& GetMessageType() const	{ return m_MessageType; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );
				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class ZoneChatS2CEvt : public MessageBase

			// S2C: Effect modifier initial sync
			class LevelUpS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				int64_t m_CurrentExp{};
				int32_t m_CurrentLevel{};
			public:
				LevelUpS2CEvt()
					{}

				LevelUpS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LevelUpS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const int64_t& GetCurrentExp() const	{ return m_CurrentExp; };
				const int32_t& GetCurrentLevel() const	{ return m_CurrentLevel; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel );

			}; // class LevelUpS2CEvt : public MessageBase

			// Cmd: To call general functionality
			class CallFunctionCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				StringCrc32 m_FunctionName{};
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_ParametersRaw;
				mutable bool m_ParametersHasParsed = false;
				mutable VariableTable m_Parameters;
			public:
				CallFunctionCmd()
					{}

				CallFunctionCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CallFunctionCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const StringCrc32& GetFunctionName() const	{ return m_FunctionName; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetParametersRaw() const	{ return m_ParametersRaw; };
				const VariableTable& GetParameters() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters );

			}; // class CallFunctionCmd : public MessageBase

			class CallFunctionRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				ArrayView<uint8_t> m_ResultsRaw;
				mutable bool m_ResultsHasParsed = false;
				mutable VariableTable m_Results;
			public:
				CallFunctionRes()
					{}

				CallFunctionRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CallFunctionRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetResultsRaw() const	{ return m_ResultsRaw; };
				const VariableTable& GetResults() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults );

			}; // class CallFunctionRes : public MessageBase

			// C2S: Send coded voice data to server
			class SendVoiceDataC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				uint16_t m_FrameIndex{};
				ArrayView<uint8_t> m_VoiceData;
			public:
				SendVoiceDataC2SEvt()
					{}

				SendVoiceDataC2SEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SendVoiceDataC2SEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint16_t& GetFrameIndex() const	{ return m_FrameIndex; };
				const Array<uint8_t>& GetVoiceData() const	{ return m_VoiceData; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData );

			}; // class SendVoiceDataC2SEvt : public MessageBase

			// S2C: Voice data
			class VoiceDataS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				uint32_t m_ActorID{};
				uint16_t m_FrameIndex{};
				ArrayView<uint8_t> m_VoiceData;
			public:
				VoiceDataS2CEvt()
					{}

				VoiceDataS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				VoiceDataS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint32_t& GetActorID() const	{ return m_ActorID; };
				const uint16_t& GetFrameIndex() const	{ return m_FrameIndex; };
				const Array<uint8_t>& GetVoiceData() const	{ return m_VoiceData; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData );
				static Result Create( MessageHeader* messageBuffer, const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData );

			}; // class VoiceDataS2CEvt : public MessageBase

			// Cmd: Create stream instance
			class CreateStreamCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				AuthTicket m_Ticket{};
				const char* m_StreamName{};
			public:
				CreateStreamCmd()
					{}

				CreateStreamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateStreamCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );

			}; // class CreateStreamCmd : public MessageBase

			class CreateStreamRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				const char* m_StreamName{};
			public:
				CreateStreamRes()
					{}

				CreateStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateStreamRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );

			}; // class CreateStreamRes : public MessageBase

			// Cmd: Open stream instance
			class FindStreamCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				AuthTicket m_Ticket{};
				const char* m_StreamName{};
			public:
				FindStreamCmd()
					{}

				FindStreamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindStreamCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );

			}; // class FindStreamCmd : public MessageBase

			class FindStreamRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				const char* m_StreamName{};
			public:
				FindStreamRes()
					{}

				FindStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindStreamRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );

			}; // class FindStreamRes : public MessageBase

			// Cmd: Delete stream instance
			class DeleteStreamCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				AuthTicket m_Ticket{};
				const char* m_StreamName{};
			public:
				DeleteStreamCmd()
					{}

				DeleteStreamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DeleteStreamCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );

			}; // class DeleteStreamCmd : public MessageBase

			class DeleteStreamRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				const char* m_StreamName{};
			public:
				DeleteStreamRes()
					{}

				DeleteStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DeleteStreamRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );

			}; // class DeleteStreamRes : public MessageBase

			// Cmd: Get stream list
			class GetStreamListCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				AuthTicket m_Ticket{};
			public:
				GetStreamListCmd()
					{}

				GetStreamListCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetStreamListCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket );

			}; // class GetStreamListCmd : public MessageBase

			class GetStreamListRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				DynamicArray<const char*> m_StreamNames;
			public:
				GetStreamListRes()
					{}

				GetStreamListRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetStreamListRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<const char*>& GetStreamNames() const	{ return m_StreamNames; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames );

			}; // class GetStreamListRes : public MessageBase





		}; // namespace PlayInstance
	}; // namespace Message
}; // namespace SF



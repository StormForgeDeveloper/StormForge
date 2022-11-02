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
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				const char* m_PlayerIdentifier{};
			public:
				JoinPlayInstanceCmd()
					{}

				JoinPlayInstanceCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const char* GetPlayerIdentifier() const	{ return m_PlayerIdentifier; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier );

			}; // class JoinPlayInstanceCmd : public MessageBase

			class JoinPlayInstanceRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				Result m_Result{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				ActorMovement m_Movement{};
			public:
				JoinPlayInstanceRes()
					{}

				JoinPlayInstanceRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const ActorMovement& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );

			}; // class JoinPlayInstanceRes : public MessageBase

			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			class PlayerKickedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				PlayerID m_KickedPlayerID{};
			public:
				PlayerKickedS2CEvt()
					{}

				PlayerKickedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetKickedPlayerID() const	{ return m_KickedPlayerID; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID );

			}; // class PlayerKickedS2CEvt : public MessageBase

			// C2S: Play packet
			class PlayPacketC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const uint32_t& GetSenderEndpointID() const	{ return m_SenderEndpointID; };
				const uint32_t& GetTargetEndpointMask() const	{ return m_TargetEndpointMask; };
				const Array<uint8_t>& GetPayload() const	{ return m_Payload; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );

			}; // class PlayPacketC2SEvt : public MessageBase

			// S2C: New actor in get view
			class NewActorInViewS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

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

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues );

			}; // class NewActorInViewS2CEvt : public MessageBase

			// S2C: Remove actor from view
			class RemoveActorFromViewS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				uint32_t m_ActorID{};
			public:
				RemoveActorFromViewS2CEvt()
					{}

				RemoveActorFromViewS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const uint32_t& GetActorID() const	{ return m_ActorID; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const uint32_t &InActorID );

			}; // class RemoveActorFromViewS2CEvt : public MessageBase

			// C2S: Player Movement
			class PlayerMovementC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const ActorMovement& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );

			}; // class PlayerMovementC2SEvt : public MessageBase

			// S2C: Player Movement
			class ActorMovementS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				ActorMovement m_Movement{};
			public:
				ActorMovementS2CEvt()
					{}

				ActorMovementS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const ActorMovement& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement );

			}; // class ActorMovementS2CEvt : public MessageBase

			// S2C: Player Movement
			class ActorMovementsS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_PlayInstanceUID{};
				ArrayView<ActorMovement> m_Movement;
			public:
				ActorMovementsS2CEvt()
					{}

				ActorMovementsS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const Array<ActorMovement>& GetMovement() const	{ return m_Movement; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement );

			}; // class ActorMovementsS2CEvt : public MessageBase

			// S2C: Player state change
			class PlayerStateChangedS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetState() const	{ return m_State; };
				const uint32_t& GetMoveFrame() const	{ return m_MoveFrame; };
				const Vector4& GetPosition() const	{ return m_Position; };
				const Array<uint8_t>& GetStateValuesRaw() const	{ return m_StateValuesRaw; };
				const VariableTable& GetStateValues() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues );

			}; // class PlayerStateChangedS2CEvt : public MessageBase

			// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			class ClientSyncReliableC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetSyncDataRaw() const	{ return m_SyncDataRaw; };
				const VariableTable& GetSyncData() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );

			}; // class ClientSyncReliableC2SEvt : public MessageBase

			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			class ClientSyncC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetSyncDataRaw() const	{ return m_SyncDataRaw; };
				const VariableTable& GetSyncData() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );

			}; // class ClientSyncC2SEvt : public MessageBase

			// Cmd: Occupy map object
			class OccupyMapObjectCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };
				const uint32_t& GetUsageId() const	{ return m_UsageId; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId );

			}; // class OccupyMapObjectCmd : public MessageBase

			class OccupyMapObjectRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );

			}; // class OccupyMapObjectRes : public MessageBase

			// Cmd: Unoccupy map object
			class UnoccupyMapObjectCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				uint64_t m_PlayInstanceUID{};
				PlayerID m_PlayerID{};
				uint32_t m_MapObjectId{};
			public:
				UnoccupyMapObjectCmd()
					{}

				UnoccupyMapObjectCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );

			}; // class UnoccupyMapObjectCmd : public MessageBase

			class UnoccupyMapObjectRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetMapObjectId() const	{ return m_MapObjectId; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );

			}; // class UnoccupyMapObjectRes : public MessageBase

			// Cmd: Use map object
			class UseMapObjectCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetMapObjectId() const	{ return m_MapObjectId; };
				const Array<uint8_t>& GetUseParametersRaw() const	{ return m_UseParametersRaw; };
				const VariableTable& GetUseParameters() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters );

			}; // class UseMapObjectCmd : public MessageBase

			class UseMapObjectRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetMapObjectId() const	{ return m_MapObjectId; };
				const Array<uint8_t>& GetResultAttributesRaw() const	{ return m_ResultAttributesRaw; };
				const VariableTable& GetResultAttributes() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes );

			}; // class UseMapObjectRes : public MessageBase

			// Cmd: Send zone chatting
			class ZoneChatCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const int8_t& GetMessageType() const	{ return m_MessageType; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class ZoneChatCmd : public MessageBase

			class ZoneChatRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				Result m_Result{};
			public:
				ZoneChatRes()
					{}

				ZoneChatRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult );

			}; // class ZoneChatRes : public MessageBase

			// S2C: Player state change
			class ZoneChatS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetSenderID() const	{ return m_SenderID; };
				const int8_t& GetMessageType() const	{ return m_MessageType; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class ZoneChatS2CEvt : public MessageBase

			// S2C: Effect modifier initial sync
			class LevelUpS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const int64_t& GetCurrentExp() const	{ return m_CurrentExp; };
				const int32_t& GetCurrentLevel() const	{ return m_CurrentLevel; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel );

			}; // class LevelUpS2CEvt : public MessageBase

			// Cmd: Create stream instance
			class CreateStreamCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				AuthTicket m_Ticket{};
				const char* m_StreamName{};
			public:
				CreateStreamCmd()
					{}

				CreateStreamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );

			}; // class CreateStreamCmd : public MessageBase

			class CreateStreamRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				Result m_Result{};
				const char* m_StreamName{};
			public:
				CreateStreamRes()
					{}

				CreateStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName );

			}; // class CreateStreamRes : public MessageBase

			// Cmd: Open stream instance
			class FindStreamCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				AuthTicket m_Ticket{};
				const char* m_StreamName{};
			public:
				FindStreamCmd()
					{}

				FindStreamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );

			}; // class FindStreamCmd : public MessageBase

			class FindStreamRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				Result m_Result{};
				const char* m_StreamName{};
			public:
				FindStreamRes()
					{}

				FindStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName );

			}; // class FindStreamRes : public MessageBase

			// Cmd: Delete stream instance
			class DeleteStreamCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				AuthTicket m_Ticket{};
				const char* m_StreamName{};
			public:
				DeleteStreamCmd()
					{}

				DeleteStreamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );

			}; // class DeleteStreamCmd : public MessageBase

			class DeleteStreamRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				Result m_Result{};
				const char* m_StreamName{};
			public:
				DeleteStreamRes()
					{}

				DeleteStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetStreamName() const	{ return m_StreamName; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName );

			}; // class DeleteStreamRes : public MessageBase

			// Cmd: Get stream list
			class GetStreamListCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				AuthTicket m_Ticket{};
			public:
				GetStreamListCmd()
					{}

				GetStreamListCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket );

			}; // class GetStreamListCmd : public MessageBase

			class GetStreamListRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
				Result m_Result{};
				DynamicArray<const char*> m_StreamNames;
			public:
				GetStreamListRes()
					{}

				GetStreamListRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<const char*>& GetStreamNames() const	{ return m_StreamNames; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames );

			}; // class GetStreamListRes : public MessageBase

			// Cmd: To call general functionality
			class CallFunctionCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const StringCrc32& GetFunctionName() const	{ return m_FunctionName; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetParametersRaw() const	{ return m_ParametersRaw; };
				const VariableTable& GetParameters() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters );

			}; // class CallFunctionCmd : public MessageBase

			class CallFunctionRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 1,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return uint64_t{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
				uint32_t GetRouteHopCount() { return uint32_t{}; }
				uint64_t GetSender() { return uint64_t{}; }
			private:
				uint64_t m_TransactionID{};
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

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetResultsRaw() const	{ return m_ResultsRaw; };
				const VariableTable& GetResults() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults );

			}; // class CallFunctionRes : public MessageBase





		}; // namespace PlayInstance
	}; // namespace Message
}; // namespace SF



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
 			// Cmd: Event for Player Join request.
			class JoinGameInstanceCmd : public MessageBase
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
				JoinGameInstanceCmd()
					{}

				JoinGameInstanceCmd( const MessageDataPtr &pMsg )
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

			}; // class JoinGameInstanceCmd : public MessageBase

			class JoinGameInstanceRes : public MessageBase
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
				JoinGameInstanceRes()
					{}

				JoinGameInstanceRes( const MessageDataPtr &pMsg )
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

			}; // class JoinGameInstanceRes : public MessageBase

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

			// S2C: New Player in get view
			class NewPlayerInViewS2CEvt : public MessageBase
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
				ArrayView<uint8_t> m_AttributesRaw;
				mutable bool m_AttributesHasParsed = false;
				mutable VariableTable m_Attributes;
				ActorMovement m_Movement{};
				StringCrc32 m_State{};
				ArrayView<uint8_t> m_StateValuesRaw;
				mutable bool m_StateValuesHasParsed = false;
				mutable VariableTable m_StateValues;
			public:
				NewPlayerInViewS2CEvt()
					{}

				NewPlayerInViewS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetAttributesRaw() const	{ return m_AttributesRaw; };
				const VariableTable& GetAttributes() const;
				const ActorMovement& GetMovement() const	{ return m_Movement; };
				const StringCrc32& GetState() const	{ return m_State; };
				const Array<uint8_t>& GetStateValuesRaw() const	{ return m_StateValuesRaw; };
				const VariableTable& GetStateValues() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues );

			}; // class NewPlayerInViewS2CEvt : public MessageBase

			// S2C: Remove player from view
			class RemovePlayerFromViewS2CEvt : public MessageBase
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
			public:
				RemovePlayerFromViewS2CEvt()
					{}

				RemovePlayerFromViewS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID );

			}; // class RemovePlayerFromViewS2CEvt : public MessageBase

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
			class PlayerMovementS2CEvt : public MessageBase
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
				PlayerMovementS2CEvt()
					{}

				PlayerMovementS2CEvt( const MessageDataPtr &pMsg )
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

			}; // class PlayerMovementS2CEvt : public MessageBase

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

			// Cmd: Havest area
			class HarvestAreaCmd : public MessageBase
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
				StringCrc32 m_AreaId{};
			public:
				HarvestAreaCmd()
					{}

				HarvestAreaCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetAreaId() const	{ return m_AreaId; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId );

			}; // class HarvestAreaCmd : public MessageBase

			class HarvestAreaRes : public MessageBase
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
				StringCrc32 m_AreaId{};
				ArrayView<uint8_t> m_ResultAttributesRaw;
				mutable bool m_ResultAttributesHasParsed = false;
				mutable VariableTable m_ResultAttributes;
			public:
				HarvestAreaRes()
					{}

				HarvestAreaRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPlayInstanceUID() const	{ return m_PlayInstanceUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const StringCrc32& GetAreaId() const	{ return m_AreaId; };
				const Array<uint8_t>& GetResultAttributesRaw() const	{ return m_ResultAttributesRaw; };
				const VariableTable& GetResultAttributes() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId, const Array<uint8_t>& InResultAttributes );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId, const VariableTable &InResultAttributes );

			}; // class HarvestAreaRes : public MessageBase

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
				NetAddress m_StreamServerAddr{};
				NetAddress m_StreamServerAddrIPV4{};
				const char* m_StreamUID{};
			public:
				CreateStreamRes()
					{}

				CreateStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const NetAddress& GetStreamServerAddr() const	{ return m_StreamServerAddr; };
				const NetAddress& GetStreamServerAddrIPV4() const	{ return m_StreamServerAddrIPV4; };
				const char* GetStreamUID() const	{ return m_StreamUID; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID );

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
				NetAddress m_StreamServerAddr{};
				NetAddress m_StreamServerAddrIPV4{};
				const char* m_StreamUID{};
			public:
				FindStreamRes()
					{}

				FindStreamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const NetAddress& GetStreamServerAddr() const	{ return m_StreamServerAddr; };
				const NetAddress& GetStreamServerAddrIPV4() const	{ return m_StreamServerAddrIPV4; };
				const char* GetStreamUID() const	{ return m_StreamUID; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID );

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
			public:
				DeleteStreamRes()
					{}

				DeleteStreamRes( const MessageDataPtr &pMsg )
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
				StringCrc32 m_FunctionName{};
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
				const Array<uint8_t>& GetParametersRaw() const	{ return m_ParametersRaw; };
				const VariableTable& GetParameters() const;

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage(const MessageData* pIMsg);
				static Result ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMsgBase);

				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters );
				static MessageData* Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters );

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



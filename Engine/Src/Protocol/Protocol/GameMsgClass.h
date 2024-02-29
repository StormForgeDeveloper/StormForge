﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Game Message parser definitions
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
 		namespace Game
		{
 			// C2S: Client heartbeat
			class HeartbeatC2SEvt : public MessageBase
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
			public:
				HeartbeatC2SEvt()
					{}

				HeartbeatC2SEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				HeartbeatC2SEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}


				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize(  );
				static Result Create( MessageHeader* messageBuffer );

			}; // class HeartbeatC2SEvt : public MessageBase

			// Cmd: Player connected from a login server and moved to game server
			class JoinGameServerCmd : public MessageBase
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
				AccountID m_AccID{};
				AuthTicket m_Ticket{};
				uint64_t m_LoginEntityUID{};
			public:
				JoinGameServerCmd()
					{}

				JoinGameServerCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinGameServerCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AccountID& GetAccID() const	{ return m_AccID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const uint64_t& GetLoginEntityUID() const	{ return m_LoginEntityUID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );

			}; // class JoinGameServerCmd : public MessageBase

			class JoinGameServerRes : public MessageBase
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
				const char* m_NickName{};
				uint64_t m_GameUID{};
				uint64_t m_PartyUID{};
				AccountID m_PartyLeaderID{};
				MatchingQueueTicket m_MatchingTicket{};
			public:
				JoinGameServerRes()
					{}

				JoinGameServerRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinGameServerRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetNickName() const	{ return m_NickName; };
				const uint64_t& GetGameUID() const	{ return m_GameUID; };
				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetPartyLeaderID() const	{ return m_PartyLeaderID; };
				const MatchingQueueTicket& GetMatchingTicket() const	{ return m_MatchingTicket; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket );

			}; // class JoinGameServerRes : public MessageBase

			// Cmd: player complition statues
			class GetAchievementStatsCmd : public MessageBase
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
				uint32_t m_CharacterID{};
				uint32_t m_AchievementStatIDFrom{};
				uint32_t m_AchievementStatIDTo{};
			public:
				GetAchievementStatsCmd()
					{}

				GetAchievementStatsCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetAchievementStatsCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetCharacterID() const	{ return m_CharacterID; };
				const uint32_t& GetAchievementStatIDFrom() const	{ return m_AchievementStatIDFrom; };
				const uint32_t& GetAchievementStatIDTo() const	{ return m_AchievementStatIDTo; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InCharacterID, const uint32_t &InAchievementStatIDFrom, const uint32_t &InAchievementStatIDTo );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InCharacterID, const uint32_t &InAchievementStatIDFrom, const uint32_t &InAchievementStatIDTo );

			}; // class GetAchievementStatsCmd : public MessageBase

			class GetAchievementStatsRes : public MessageBase
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
				ArrayView<AchievementStat> m_AchievementStats;
			public:
				GetAchievementStatsRes()
					{}

				GetAchievementStatsRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetAchievementStatsRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<AchievementStat>& GetAchievementStats() const	{ return m_AchievementStats; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<AchievementStat>& InAchievementStats );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<AchievementStat>& InAchievementStats );

			}; // class GetAchievementStatsRes : public MessageBase

			// Cmd: Player complition state
			class Dummy1Cmd : public MessageBase
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
				const char* m_ComplitionState{};
			public:
				Dummy1Cmd()
					{}

				Dummy1Cmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				Dummy1Cmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetComplitionState() const	{ return m_ComplitionState; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InComplitionState );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InComplitionState );

			}; // class Dummy1Cmd : public MessageBase

			class Dummy1Res : public MessageBase
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
				Dummy1Res()
					{}

				Dummy1Res( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				Dummy1Res( const MessageHeader* pHeader )
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

			}; // class Dummy1Res : public MessageBase

			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			class RegisterGCMCmd : public MessageBase
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
				const char* m_GCMRegisteredID{};
			public:
				RegisterGCMCmd()
					{}

				RegisterGCMCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RegisterGCMCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetGCMRegisteredID() const	{ return m_GCMRegisteredID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InGCMRegisteredID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InGCMRegisteredID );

			}; // class RegisterGCMCmd : public MessageBase

			class RegisterGCMRes : public MessageBase
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
				RegisterGCMRes()
					{}

				RegisterGCMRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RegisterGCMRes( const MessageHeader* pHeader )
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

			}; // class RegisterGCMRes : public MessageBase

			// Cmd: Unregister Google notification service ID
			class UnregisterGCMCmd : public MessageBase
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
				const char* m_GCMRegisteredID{};
			public:
				UnregisterGCMCmd()
					{}

				UnregisterGCMCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UnregisterGCMCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetGCMRegisteredID() const	{ return m_GCMRegisteredID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InGCMRegisteredID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InGCMRegisteredID );

			}; // class UnregisterGCMCmd : public MessageBase

			class UnregisterGCMRes : public MessageBase
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
				UnregisterGCMRes()
					{}

				UnregisterGCMRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UnregisterGCMRes( const MessageHeader* pHeader )
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

			}; // class UnregisterGCMRes : public MessageBase

			// Cmd: Invite friend
			class InviteFriendCmd : public MessageBase
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
				AccountID m_FriendID{};
			public:
				InviteFriendCmd()
					{}

				InviteFriendCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				InviteFriendCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AccountID& GetFriendID() const	{ return m_FriendID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AccountID &InFriendID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AccountID &InFriendID );

			}; // class InviteFriendCmd : public MessageBase

			class InviteFriendRes : public MessageBase
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
				InviteFriendRes()
					{}

				InviteFriendRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				InviteFriendRes( const MessageHeader* pHeader )
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

			}; // class InviteFriendRes : public MessageBase

			// Cmd: Accept friend request
			class AcceptFriendRequestCmd : public MessageBase
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
				AccountID m_InviterID{};
				PlayerPlatformID m_InviterPlatformId{};
			public:
				AcceptFriendRequestCmd()
					{}

				AcceptFriendRequestCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AcceptFriendRequestCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AccountID& GetInviterID() const	{ return m_InviterID; };
				const PlayerPlatformID& GetInviterPlatformId() const	{ return m_InviterPlatformId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId );

			}; // class AcceptFriendRequestCmd : public MessageBase

			class AcceptFriendRequestRes : public MessageBase
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
				FriendInformation m_NewFriend{};
			public:
				AcceptFriendRequestRes()
					{}

				AcceptFriendRequestRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AcceptFriendRequestRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const FriendInformation& GetNewFriend() const	{ return m_NewFriend; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend );

			}; // class AcceptFriendRequestRes : public MessageBase

			// S2C: Notification for friend request is accepted
			class FriendRequestAcceptedS2CEvt : public MessageBase
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
				FriendInformation m_Accepter{};
			public:
				FriendRequestAcceptedS2CEvt()
					{}

				FriendRequestAcceptedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FriendRequestAcceptedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const FriendInformation& GetAccepter() const	{ return m_Accepter; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const FriendInformation &InAccepter );
				static Result Create( MessageHeader* messageBuffer, const FriendInformation &InAccepter );

			}; // class FriendRequestAcceptedS2CEvt : public MessageBase

			// Cmd: Remove friden form the friend list
			class RemoveFriendCmd : public MessageBase
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
				AccountID m_FriendID{};
			public:
				RemoveFriendCmd()
					{}

				RemoveFriendCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RemoveFriendCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AccountID& GetFriendID() const	{ return m_FriendID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AccountID &InFriendID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AccountID &InFriendID );

			}; // class RemoveFriendCmd : public MessageBase

			class RemoveFriendRes : public MessageBase
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
				AccountID m_FriendID{};
			public:
				RemoveFriendRes()
					{}

				RemoveFriendRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RemoveFriendRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const AccountID& GetFriendID() const	{ return m_FriendID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InFriendID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const AccountID &InFriendID );

			}; // class RemoveFriendRes : public MessageBase

			// S2C: Friend removed
			class FriendRemovedS2CEvt : public MessageBase
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
				AccountID m_FriendID{};
			public:
				FriendRemovedS2CEvt()
					{}

				FriendRemovedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FriendRemovedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const AccountID& GetFriendID() const	{ return m_FriendID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const AccountID &InFriendID );
				static Result Create( MessageHeader* messageBuffer, const AccountID &InFriendID );

			}; // class FriendRemovedS2CEvt : public MessageBase

			// Cmd: Get friend list
			class GetFriendListCmd : public MessageBase
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
				uint16_t m_StartIndex{};
				uint16_t m_Count{};
			public:
				GetFriendListCmd()
					{}

				GetFriendListCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetFriendListCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint16_t& GetStartIndex() const	{ return m_StartIndex; };
				const uint16_t& GetCount() const	{ return m_Count; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount );

			}; // class GetFriendListCmd : public MessageBase

			class GetFriendListRes : public MessageBase
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
				uint16_t m_MaxFriendSlot{};
				uint16_t m_TotalNumberOfFriends{};
				uint16_t m_StartIndex{};
				ArrayView<FriendInformation> m_FriendList;
			public:
				GetFriendListRes()
					{}

				GetFriendListRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetFriendListRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint16_t& GetMaxFriendSlot() const	{ return m_MaxFriendSlot; };
				const uint16_t& GetTotalNumberOfFriends() const	{ return m_TotalNumberOfFriends; };
				const uint16_t& GetStartIndex() const	{ return m_StartIndex; };
				const Array<FriendInformation>& GetFriendList() const	{ return m_FriendList; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList );

			}; // class GetFriendListRes : public MessageBase

			// Cmd: Query notification list
			class GetNotificationListCmd : public MessageBase
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
			public:
				GetNotificationListCmd()
					{}

				GetNotificationListCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetNotificationListCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID );

			}; // class GetNotificationListCmd : public MessageBase

			class GetNotificationListRes : public MessageBase
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
				GetNotificationListRes()
					{}

				GetNotificationListRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetNotificationListRes( const MessageHeader* pHeader )
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

			}; // class GetNotificationListRes : public MessageBase

			// Cmd: Delete notification
			class DeleteNotificationCmd : public MessageBase
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
				uint32_t m_NotificationID{};
			public:
				DeleteNotificationCmd()
					{}

				DeleteNotificationCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DeleteNotificationCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetNotificationID() const	{ return m_NotificationID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InNotificationID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InNotificationID );

			}; // class DeleteNotificationCmd : public MessageBase

			class DeleteNotificationRes : public MessageBase
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
				uint32_t m_NotificationID{};
			public:
				DeleteNotificationRes()
					{}

				DeleteNotificationRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DeleteNotificationRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetNotificationID() const	{ return m_NotificationID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );

			}; // class DeleteNotificationRes : public MessageBase

			// Cmd: Set notification is read
			class SetNotificationReadCmd : public MessageBase
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
				uint32_t m_NotificationID{};
			public:
				SetNotificationReadCmd()
					{}

				SetNotificationReadCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SetNotificationReadCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetNotificationID() const	{ return m_NotificationID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InNotificationID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InNotificationID );

			}; // class SetNotificationReadCmd : public MessageBase

			class SetNotificationReadRes : public MessageBase
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
				uint32_t m_NotificationID{};
			public:
				SetNotificationReadRes()
					{}

				SetNotificationReadRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SetNotificationReadRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetNotificationID() const	{ return m_NotificationID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );

			}; // class SetNotificationReadRes : public MessageBase

			// Cmd: Accept notification
			class AcceptNotificationCmd : public MessageBase
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
				uint32_t m_NotificationID{};
			public:
				AcceptNotificationCmd()
					{}

				AcceptNotificationCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AcceptNotificationCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetNotificationID() const	{ return m_NotificationID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InNotificationID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InNotificationID );

			}; // class AcceptNotificationCmd : public MessageBase

			class AcceptNotificationRes : public MessageBase
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
				uint32_t m_NotificationID{};
			public:
				AcceptNotificationRes()
					{}

				AcceptNotificationRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				AcceptNotificationRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetNotificationID() const	{ return m_NotificationID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );

			}; // class AcceptNotificationRes : public MessageBase

			// S2C: Notify new notification
			class NotifyS2CEvt : public MessageBase
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
				uint32_t m_NotificationID{};
				StringCrc32 m_NotificationType{};
				ArrayView<uint8_t> m_ParametersRaw;
				mutable bool m_ParametersHasParsed = false;
				mutable VariableTable m_Parameters;
				uint8_t m_IsRead{};
				uint64_t m_TimeStamp{};
			public:
				NotifyS2CEvt()
					{}

				NotifyS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				NotifyS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint32_t& GetNotificationID() const	{ return m_NotificationID; };
				const StringCrc32& GetNotificationType() const	{ return m_NotificationType; };
				const Array<uint8_t>& GetParametersRaw() const	{ return m_ParametersRaw; };
				const VariableTable& GetParameters() const;
				const uint8_t& GetIsRead() const	{ return m_IsRead; };
				const uint64_t& GetTimeStamp() const	{ return m_TimeStamp; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp );
				static size_t CalculateMessageSize( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const Array<uint8_t>& InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp );
				static Result Create( MessageHeader* messageBuffer, const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const Array<uint8_t>& InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp );
				static Result Create( MessageHeader* messageBuffer, const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp );

			}; // class NotifyS2CEvt : public MessageBase

			// Cmd: PlayerId Conversion
			class FindPlayerByPlatformIdCmd : public MessageBase
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
				PlayerPlatformID m_PlatformPlayerId{};
			public:
				FindPlayerByPlatformIdCmd()
					{}

				FindPlayerByPlatformIdCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByPlatformIdCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const PlayerPlatformID& GetPlatformPlayerId() const	{ return m_PlatformPlayerId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const PlayerPlatformID &InPlatformPlayerId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const PlayerPlatformID &InPlatformPlayerId );

			}; // class FindPlayerByPlatformIdCmd : public MessageBase

			class FindPlayerByPlatformIdRes : public MessageBase
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
				PlayerID m_PlayerId{};
				PlayerPlatformID m_PlayerPlatformId{};
			public:
				FindPlayerByPlatformIdRes()
					{}

				FindPlayerByPlatformIdRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByPlatformIdRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const PlayerID& GetPlayerId() const	{ return m_PlayerId; };
				const PlayerPlatformID& GetPlayerPlatformId() const	{ return m_PlayerPlatformId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId );

			}; // class FindPlayerByPlatformIdRes : public MessageBase

			// Cmd: PlayerId conversion
			class FindPlayerByCharacterNameCmd : public MessageBase
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
				const char* m_CharacterName{};
			public:
				FindPlayerByCharacterNameCmd()
					{}

				FindPlayerByCharacterNameCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByCharacterNameCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetCharacterName() const	{ return m_CharacterName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InCharacterName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InCharacterName );

			}; // class FindPlayerByCharacterNameCmd : public MessageBase

			class FindPlayerByCharacterNameRes : public MessageBase
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
				PlayerID m_PlayerId{};
			public:
				FindPlayerByCharacterNameRes()
					{}

				FindPlayerByCharacterNameRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByCharacterNameRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const PlayerID& GetPlayerId() const	{ return m_PlayerId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId );

			}; // class FindPlayerByCharacterNameRes : public MessageBase

			// Cmd: PlayerId Conversion
			class FindPlayerByPlatformUserNameCmd : public MessageBase
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
				uint8_t m_PlatformType{};
				const char* m_PlatformUserName{};
			public:
				FindPlayerByPlatformUserNameCmd()
					{}

				FindPlayerByPlatformUserNameCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByPlatformUserNameCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint8_t& GetPlatformType() const	{ return m_PlatformType; };
				const char* GetPlatformUserName() const	{ return m_PlatformUserName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName );

			}; // class FindPlayerByPlatformUserNameCmd : public MessageBase

			class FindPlayerByPlatformUserNameRes : public MessageBase
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
				PlayerID m_PlayerId{};
				PlayerPlatformID m_PlayerPlatformId{};
			public:
				FindPlayerByPlatformUserNameRes()
					{}

				FindPlayerByPlatformUserNameRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByPlatformUserNameRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const PlayerID& GetPlayerId() const	{ return m_PlayerId; };
				const PlayerPlatformID& GetPlayerPlatformId() const	{ return m_PlayerPlatformId; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId );

			}; // class FindPlayerByPlatformUserNameRes : public MessageBase

			// Cmd: Query playerID list
			class FindPlayerByEMailCmd : public MessageBase
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
				const char* m_PlayerEMail{};
			public:
				FindPlayerByEMailCmd()
					{}

				FindPlayerByEMailCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByEMailCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetPlayerEMail() const	{ return m_PlayerEMail; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InPlayerEMail );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InPlayerEMail );

			}; // class FindPlayerByEMailCmd : public MessageBase

			class FindPlayerByEMailRes : public MessageBase
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
				PlayerInformation m_Player{};
			public:
				FindPlayerByEMailRes()
					{}

				FindPlayerByEMailRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByEMailRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const PlayerInformation& GetPlayer() const	{ return m_Player; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );

			}; // class FindPlayerByEMailRes : public MessageBase

			// Cmd: Query playerID list
			class FindPlayerByPlayerIDCmd : public MessageBase
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
				AccountID m_PlayerID{};
			public:
				FindPlayerByPlayerIDCmd()
					{}

				FindPlayerByPlayerIDCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByPlayerIDCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AccountID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AccountID &InPlayerID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AccountID &InPlayerID );

			}; // class FindPlayerByPlayerIDCmd : public MessageBase

			class FindPlayerByPlayerIDRes : public MessageBase
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
				PlayerInformation m_Player{};
			public:
				FindPlayerByPlayerIDRes()
					{}

				FindPlayerByPlayerIDRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				FindPlayerByPlayerIDRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const PlayerInformation& GetPlayer() const	{ return m_Player; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );

			}; // class FindPlayerByPlayerIDRes : public MessageBase

			// Cmd: *Request Player Status Update
			class RequestPlayerStatusUpdateCmd : public MessageBase
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
				ArrayView<AccountID> m_TargetPlayerID;
			public:
				RequestPlayerStatusUpdateCmd()
					{}

				RequestPlayerStatusUpdateCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestPlayerStatusUpdateCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Array<AccountID>& GetTargetPlayerID() const	{ return m_TargetPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID );

			}; // class RequestPlayerStatusUpdateCmd : public MessageBase

			class RequestPlayerStatusUpdateRes : public MessageBase
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
				RequestPlayerStatusUpdateRes()
					{}

				RequestPlayerStatusUpdateRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestPlayerStatusUpdateRes( const MessageHeader* pHeader )
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

			}; // class RequestPlayerStatusUpdateRes : public MessageBase

			// S2C: *Notify Player Status Updated
			class NotifyPlayerStatusUpdatedS2CEvt : public MessageBase
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
				AccountID m_PlayerID{};
				uint32_t m_LatestActiveTime{};
				uint8_t m_IsInGame{};
			public:
				NotifyPlayerStatusUpdatedS2CEvt()
					{}

				NotifyPlayerStatusUpdatedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				NotifyPlayerStatusUpdatedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const AccountID& GetPlayerID() const	{ return m_PlayerID; };
				const uint32_t& GetLatestActiveTime() const	{ return m_LatestActiveTime; };
				const uint8_t& GetIsInGame() const	{ return m_IsInGame; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame );
				static Result Create( MessageHeader* messageBuffer, const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame );

			}; // class NotifyPlayerStatusUpdatedS2CEvt : public MessageBase

			// Cmd: Get Ranking list
			class GetRankingListCmd : public MessageBase
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
				uint8_t m_RankingType{};
				uint8_t m_BaseRanking{};
				uint8_t m_Count{};
			public:
				GetRankingListCmd()
					{}

				GetRankingListCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetRankingListCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint8_t& GetRankingType() const	{ return m_RankingType; };
				const uint8_t& GetBaseRanking() const	{ return m_BaseRanking; };
				const uint8_t& GetCount() const	{ return m_Count; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );

			}; // class GetRankingListCmd : public MessageBase

			class GetRankingListRes : public MessageBase
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
				ArrayView<TotalRankingPlayerInformation> m_Ranking;
			public:
				GetRankingListRes()
					{}

				GetRankingListRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetRankingListRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<TotalRankingPlayerInformation>& GetRanking() const	{ return m_Ranking; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );

			}; // class GetRankingListRes : public MessageBase

			// Cmd: Game user game play information
			class GetUserGamePlayerInfoCmd : public MessageBase
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
			public:
				GetUserGamePlayerInfoCmd()
					{}

				GetUserGamePlayerInfoCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetUserGamePlayerInfoCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID );

			}; // class GetUserGamePlayerInfoCmd : public MessageBase

			class GetUserGamePlayerInfoRes : public MessageBase
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
				ArrayView<uint8_t> m_AttributesRaw;
				mutable bool m_AttributesHasParsed = false;
				mutable VariableTable m_Attributes;
			public:
				GetUserGamePlayerInfoRes()
					{}

				GetUserGamePlayerInfoRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetUserGamePlayerInfoRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetAttributesRaw() const	{ return m_AttributesRaw; };
				const VariableTable& GetAttributes() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InAttributes );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InAttributes );

			}; // class GetUserGamePlayerInfoRes : public MessageBase

			// Cmd: Game game play information
			class GetGamePlayerInfoCmd : public MessageBase
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
				AccountID m_PlayerID{};
			public:
				GetGamePlayerInfoCmd()
					{}

				GetGamePlayerInfoCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetGamePlayerInfoCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AccountID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AccountID &InPlayerID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AccountID &InPlayerID );

			}; // class GetGamePlayerInfoCmd : public MessageBase

			class GetGamePlayerInfoRes : public MessageBase
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
				AccountID m_PlayerID{};
				ArrayView<uint8_t> m_AttributesRaw;
				mutable bool m_AttributesHasParsed = false;
				mutable VariableTable m_Attributes;
			public:
				GetGamePlayerInfoRes()
					{}

				GetGamePlayerInfoRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetGamePlayerInfoRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const AccountID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetAttributesRaw() const	{ return m_AttributesRaw; };
				const VariableTable& GetAttributes() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const Array<uint8_t>& InAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const Array<uint8_t>& InAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes );

			}; // class GetGamePlayerInfoRes : public MessageBase

			// S2C: Player level up event
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
				uint64_t m_CurrentTotalExp{};
				uint32_t m_CurrentLevel{};
			public:
				LevelUpS2CEvt()
					{}

				LevelUpS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LevelUpS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetCurrentTotalExp() const	{ return m_CurrentTotalExp; };
				const uint32_t& GetCurrentLevel() const	{ return m_CurrentLevel; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel );

			}; // class LevelUpS2CEvt : public MessageBase

			// Cmd: Change NickName
			class SetNickNameCmd : public MessageBase
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
				const char* m_NickName{};
				uint8_t m_IsCostFree{};
			public:
				SetNickNameCmd()
					{}

				SetNickNameCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SetNickNameCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetNickName() const	{ return m_NickName; };
				const uint8_t& GetIsCostFree() const	{ return m_IsCostFree; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree );

			}; // class SetNickNameCmd : public MessageBase

			class SetNickNameRes : public MessageBase
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
				uint64_t m_TotalGem{};
				uint64_t m_TotalGameMoney{};
			public:
				SetNickNameRes()
					{}

				SetNickNameRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SetNickNameRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetTotalGem() const	{ return m_TotalGem; };
				const uint64_t& GetTotalGameMoney() const	{ return m_TotalGameMoney; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );

			}; // class SetNickNameRes : public MessageBase

			// Cmd: Create Party
			class CreatePartyCmd : public MessageBase
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
			public:
				CreatePartyCmd()
					{}

				CreatePartyCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreatePartyCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID );

			}; // class CreatePartyCmd : public MessageBase

			class CreatePartyRes : public MessageBase
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
				uint64_t m_PartyUID{};
			public:
				CreatePartyRes()
					{}

				CreatePartyRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreatePartyRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID );

			}; // class CreatePartyRes : public MessageBase

			// Cmd: Join party
			class JoinPartyCmd : public MessageBase
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
				uint64_t m_PartyUID{};
				AccountID m_InviterID{};
			public:
				JoinPartyCmd()
					{}

				JoinPartyCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinPartyCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetInviterID() const	{ return m_InviterID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID );

			}; // class JoinPartyCmd : public MessageBase

			class JoinPartyRes : public MessageBase
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
				uint64_t m_PartyUID{};
				AccountID m_PartyLeaderID{};
				ArrayView<uint8_t> m_ChatHistoryData;
			public:
				JoinPartyRes()
					{}

				JoinPartyRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinPartyRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetPartyLeaderID() const	{ return m_PartyLeaderID; };
				const Array<uint8_t>& GetChatHistoryData() const	{ return m_ChatHistoryData; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData );

			}; // class JoinPartyRes : public MessageBase

			// S2C: Player Joined event
			class PartyPlayerJoinedS2CEvt : public MessageBase
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
				uint64_t m_PartyUID{};
				PlayerInformation m_JoinedPlayer{};
			public:
				PartyPlayerJoinedS2CEvt()
					{}

				PartyPlayerJoinedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyPlayerJoinedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const PlayerInformation& GetJoinedPlayer() const	{ return m_JoinedPlayer; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer );

			}; // class PartyPlayerJoinedS2CEvt : public MessageBase

			// S2C: Party leader changed event
			class PartyLeaderChangedS2CEvt : public MessageBase
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
				uint64_t m_PartyUID{};
				AccountID m_NewLeaderID{};
			public:
				PartyLeaderChangedS2CEvt()
					{}

				PartyLeaderChangedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyLeaderChangedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetNewLeaderID() const	{ return m_NewLeaderID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InNewLeaderID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPartyUID, const AccountID &InNewLeaderID );

			}; // class PartyLeaderChangedS2CEvt : public MessageBase

			// Cmd: Leave party command
			class LeavePartyCmd : public MessageBase
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
				uint64_t m_PartyUID{};
				AccountID m_PlayerID{};
			public:
				LeavePartyCmd()
					{}

				LeavePartyCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LeavePartyCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID );

			}; // class LeavePartyCmd : public MessageBase

			class LeavePartyRes : public MessageBase
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
				LeavePartyRes()
					{}

				LeavePartyRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LeavePartyRes( const MessageHeader* pHeader )
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

			}; // class LeavePartyRes : public MessageBase

			// S2C: Party Player left event
			class PartyPlayerLeftS2CEvt : public MessageBase
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
				uint64_t m_PartyUID{};
				AccountID m_LeftPlayerID{};
			public:
				PartyPlayerLeftS2CEvt()
					{}

				PartyPlayerLeftS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyPlayerLeftS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetLeftPlayerID() const	{ return m_LeftPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPartyUID, const AccountID &InLeftPlayerID );

			}; // class PartyPlayerLeftS2CEvt : public MessageBase

			// Cmd: Kick player from the party
			class PartyKickPlayerCmd : public MessageBase
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
				uint64_t m_PartyUID{};
				AccountID m_PlayerID{};
				AccountID m_PlayerToKick{};
			public:
				PartyKickPlayerCmd()
					{}

				PartyKickPlayerCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyKickPlayerCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetPlayerID() const	{ return m_PlayerID; };
				const AccountID& GetPlayerToKick() const	{ return m_PlayerToKick; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );

			}; // class PartyKickPlayerCmd : public MessageBase

			class PartyKickPlayerRes : public MessageBase
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
				PartyKickPlayerRes()
					{}

				PartyKickPlayerRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyKickPlayerRes( const MessageHeader* pHeader )
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

			}; // class PartyKickPlayerRes : public MessageBase

			// S2C: Party Player kicked message
			class PartyPlayerKickedS2CEvt : public MessageBase
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
				uint64_t m_PartyUID{};
				AccountID m_KickedPlayerID{};
			public:
				PartyPlayerKickedS2CEvt()
					{}

				PartyPlayerKickedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyPlayerKickedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetPartyUID() const	{ return m_PartyUID; };
				const AccountID& GetKickedPlayerID() const	{ return m_KickedPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InPartyUID, const AccountID &InKickedPlayerID );

			}; // class PartyPlayerKickedS2CEvt : public MessageBase

			// Cmd: Invite a player to the party
			class PartyInviteCmd : public MessageBase
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
				AccountID m_InviteTargetID{};
			public:
				PartyInviteCmd()
					{}

				PartyInviteCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyInviteCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const AccountID& GetInviteTargetID() const	{ return m_InviteTargetID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const AccountID &InInviteTargetID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AccountID &InInviteTargetID );

			}; // class PartyInviteCmd : public MessageBase

			class PartyInviteRes : public MessageBase
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
				PartyInviteRes()
					{}

				PartyInviteRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyInviteRes( const MessageHeader* pHeader )
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

			}; // class PartyInviteRes : public MessageBase

			// S2C: Party invite requested
			class PartyInviteRequestedS2CEvt : public MessageBase
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
				AccountID m_InviterID{};
				const char* m_InviterName{};
				uint64_t m_PartyToJoinUID{};
			public:
				PartyInviteRequestedS2CEvt()
					{}

				PartyInviteRequestedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyInviteRequestedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const AccountID& GetInviterID() const	{ return m_InviterID; };
				const char* GetInviterName() const	{ return m_InviterName; };
				const uint64_t& GetPartyToJoinUID() const	{ return m_PartyToJoinUID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID );
				static Result Create( MessageHeader* messageBuffer, const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID );

			}; // class PartyInviteRequestedS2CEvt : public MessageBase

			// Cmd: Send Party quick chat message
			class PartyQuickChatMessageCmd : public MessageBase
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
				uint32_t m_QuickChatID{};
			public:
				PartyQuickChatMessageCmd()
					{}

				PartyQuickChatMessageCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyQuickChatMessageCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetQuickChatID() const	{ return m_QuickChatID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InQuickChatID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InQuickChatID );

			}; // class PartyQuickChatMessageCmd : public MessageBase

			class PartyQuickChatMessageRes : public MessageBase
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
				PartyQuickChatMessageRes()
					{}

				PartyQuickChatMessageRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyQuickChatMessageRes( const MessageHeader* pHeader )
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

			}; // class PartyQuickChatMessageRes : public MessageBase

			// S2C: Party Chatting message event
			class PartyQuickChatMessageS2CEvt : public MessageBase
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
				AccountID m_SenderID{};
				uint32_t m_QuickChatID{};
			public:
				PartyQuickChatMessageS2CEvt()
					{}

				PartyQuickChatMessageS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyQuickChatMessageS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const AccountID& GetSenderID() const	{ return m_SenderID; };
				const uint32_t& GetQuickChatID() const	{ return m_QuickChatID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const AccountID &InSenderID, const uint32_t &InQuickChatID );
				static Result Create( MessageHeader* messageBuffer, const AccountID &InSenderID, const uint32_t &InQuickChatID );

			}; // class PartyQuickChatMessageS2CEvt : public MessageBase

			// Cmd: Party chatting
			class PartyChatMessageCmd : public MessageBase
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
				const char* m_ChatMessage{};
			public:
				PartyChatMessageCmd()
					{}

				PartyChatMessageCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyChatMessageCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InChatMessage );

			}; // class PartyChatMessageCmd : public MessageBase

			class PartyChatMessageRes : public MessageBase
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
				PartyChatMessageRes()
					{}

				PartyChatMessageRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyChatMessageRes( const MessageHeader* pHeader )
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

			}; // class PartyChatMessageRes : public MessageBase

			// S2C: Party Chatting message event
			class PartyChatMessageS2CEvt : public MessageBase
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
				AccountID m_SenderID{};
				const char* m_SenderName{};
				const char* m_ChatMessage{};
			public:
				PartyChatMessageS2CEvt()
					{}

				PartyChatMessageS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PartyChatMessageS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const AccountID& GetSenderID() const	{ return m_SenderID; };
				const char* GetSenderName() const	{ return m_SenderName; };
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage );

			}; // class PartyChatMessageS2CEvt : public MessageBase

			// Cmd: Join to a game instance
			class JoinGameInstanceCmd : public MessageBase
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
				uint64_t m_InsUID{};
			public:
				JoinGameInstanceCmd()
					{}

				JoinGameInstanceCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinGameInstanceCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetInsUID() const	{ return m_InsUID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InInsUID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InInsUID );

			}; // class JoinGameInstanceCmd : public MessageBase

			class JoinGameInstanceRes : public MessageBase
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
				uint64_t m_InsUID{};
				const char* m_ServerPublicAddress{};
			public:
				JoinGameInstanceRes()
					{}

				JoinGameInstanceRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinGameInstanceRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetInsUID() const	{ return m_InsUID; };
				const char* GetServerPublicAddress() const	{ return m_ServerPublicAddress; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress );

			}; // class JoinGameInstanceRes : public MessageBase

			// Cmd: Leave game instance
			class LeaveGameInstanceCmd : public MessageBase
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
				uint64_t m_InsUID{};
			public:
				LeaveGameInstanceCmd()
					{}

				LeaveGameInstanceCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LeaveGameInstanceCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetInsUID() const	{ return m_InsUID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InInsUID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InInsUID );

			}; // class LeaveGameInstanceCmd : public MessageBase

			class LeaveGameInstanceRes : public MessageBase
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
				LeaveGameInstanceRes()
					{}

				LeaveGameInstanceRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LeaveGameInstanceRes( const MessageHeader* pHeader )
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

			}; // class LeaveGameInstanceRes : public MessageBase

			// Cmd: Search game instance
			class SearchGameInstanceCmd : public MessageBase
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
				const char* m_SearchKeyword{};
				uint32_t m_ZoneTableID{};
			public:
				SearchGameInstanceCmd()
					{}

				SearchGameInstanceCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SearchGameInstanceCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetSearchKeyword() const	{ return m_SearchKeyword; };
				const uint32_t& GetZoneTableID() const	{ return m_ZoneTableID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID );

			}; // class SearchGameInstanceCmd : public MessageBase

			class SearchGameInstanceRes : public MessageBase
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
				DynamicArray<VariableTable> m_GameInstances;
			public:
				SearchGameInstanceRes()
					{}

				SearchGameInstanceRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SearchGameInstanceRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<VariableTable>& GetGameInstances() const	{ return m_GameInstances; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances );

			}; // class SearchGameInstanceRes : public MessageBase

			// Cmd: Search game instance
			class GetCharacterDataInGameInstanceCmd : public MessageBase
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
				uint64_t m_GameInsUID{};
				PlayerID m_PlayerID{};
			public:
				GetCharacterDataInGameInstanceCmd()
					{}

				GetCharacterDataInGameInstanceCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetCharacterDataInGameInstanceCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetGameInsUID() const	{ return m_GameInsUID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID );

			}; // class GetCharacterDataInGameInstanceCmd : public MessageBase

			class GetCharacterDataInGameInstanceRes : public MessageBase
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
				PlayerID m_PlayerID{};
				ArrayView<uint8_t> m_GameInstancesRaw;
				mutable bool m_GameInstancesHasParsed = false;
				mutable VariableTable m_GameInstances;
			public:
				GetCharacterDataInGameInstanceRes()
					{}

				GetCharacterDataInGameInstanceRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetCharacterDataInGameInstanceRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const Array<uint8_t>& GetGameInstancesRaw() const	{ return m_GameInstancesRaw; };
				const VariableTable& GetGameInstances() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const Array<uint8_t>& InGameInstances );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const Array<uint8_t>& InGameInstances );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances );

			}; // class GetCharacterDataInGameInstanceRes : public MessageBase

			// Cmd: Request Game match
			class RequestGameMatchCmd : public MessageBase
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
				uint8_t m_NumPlayer{};
				uint8_t m_RequestRole{};
			public:
				RequestGameMatchCmd()
					{}

				RequestGameMatchCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestGameMatchCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint8_t& GetNumPlayer() const	{ return m_NumPlayer; };
				const uint8_t& GetRequestRole() const	{ return m_RequestRole; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole );

			}; // class RequestGameMatchCmd : public MessageBase

			class RequestGameMatchRes : public MessageBase
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
				uint64_t m_TotalGem{};
				uint64_t m_TotalGameMoney{};
			public:
				RequestGameMatchRes()
					{}

				RequestGameMatchRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestGameMatchRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetTotalGem() const	{ return m_TotalGem; };
				const uint64_t& GetTotalGameMoney() const	{ return m_TotalGameMoney; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );

			}; // class RequestGameMatchRes : public MessageBase

			// S2C: Game matched
			class GameMatchedS2CEvt : public MessageBase
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
				uint64_t m_InsUID{};
				uint32_t m_TimeStamp{};
				uint8_t m_GameState{};
				uint8_t m_Day{};
				uint8_t m_MaxPlayer{};
				uint8_t m_PlayerIndex{};
				uint8_t m_PlayerCharacter{};
				uint8_t m_Role{};
				uint8_t m_Dead{};
				ArrayView<uint8_t> m_ChatHistoryData;
				ArrayView<uint8_t> m_GameLogData;
				uint32_t m_Stamina{};
				uint64_t m_TotalGem{};
				uint64_t m_TotalGameMoney{};
			public:
				GameMatchedS2CEvt()
					{}

				GameMatchedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GameMatchedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetInsUID() const	{ return m_InsUID; };
				const uint32_t& GetTimeStamp() const	{ return m_TimeStamp; };
				const uint8_t& GetGameState() const	{ return m_GameState; };
				const uint8_t& GetDay() const	{ return m_Day; };
				const uint8_t& GetMaxPlayer() const	{ return m_MaxPlayer; };
				const uint8_t& GetPlayerIndex() const	{ return m_PlayerIndex; };
				const uint8_t& GetPlayerCharacter() const	{ return m_PlayerCharacter; };
				const uint8_t& GetRole() const	{ return m_Role; };
				const uint8_t& GetDead() const	{ return m_Dead; };
				const Array<uint8_t>& GetChatHistoryData() const	{ return m_ChatHistoryData; };
				const Array<uint8_t>& GetGameLogData() const	{ return m_GameLogData; };
				const uint32_t& GetStamina() const	{ return m_Stamina; };
				const uint64_t& GetTotalGem() const	{ return m_TotalGem; };
				const uint64_t& GetTotalGameMoney() const	{ return m_TotalGameMoney; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );

			}; // class GameMatchedS2CEvt : public MessageBase

			// S2C: Game match failed
			class GameMatchFailedS2CEvt : public MessageBase
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
				Result m_FailedReason{};
			public:
				GameMatchFailedS2CEvt()
					{}

				GameMatchFailedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GameMatchFailedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const Result& GetFailedReason() const	{ return m_FailedReason; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const Result &InFailedReason );
				static Result Create( MessageHeader* messageBuffer, const Result &InFailedReason );

			}; // class GameMatchFailedS2CEvt : public MessageBase

			// S2C: Game matching started
			class GameMatchingStartedS2CEvt : public MessageBase
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
			public:
				GameMatchingStartedS2CEvt()
					{}

				GameMatchingStartedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GameMatchingStartedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}


				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize(  );
				static Result Create( MessageHeader* messageBuffer );

			}; // class GameMatchingStartedS2CEvt : public MessageBase

			// Cmd: Cancel Game match
			class CancelGameMatchCmd : public MessageBase
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
			public:
				CancelGameMatchCmd()
					{}

				CancelGameMatchCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CancelGameMatchCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID );

			}; // class CancelGameMatchCmd : public MessageBase

			class CancelGameMatchRes : public MessageBase
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
				CancelGameMatchRes()
					{}

				CancelGameMatchRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CancelGameMatchRes( const MessageHeader* pHeader )
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

			}; // class CancelGameMatchRes : public MessageBase

			// S2C: game matching canceled
			class GameMatchingCanceledS2CEvt : public MessageBase
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
			public:
				GameMatchingCanceledS2CEvt()
					{}

				GameMatchingCanceledS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GameMatchingCanceledS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}


				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize(  );
				static Result Create( MessageHeader* messageBuffer );

			}; // class GameMatchingCanceledS2CEvt : public MessageBase

			// Cmd: Request UGC template list
			class GetUGCTemplatesCmd : public MessageBase
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
				DynamicArray<const char*> m_Tags;
			public:
				GetUGCTemplatesCmd()
					{}

				GetUGCTemplatesCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetUGCTemplatesCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Array<const char*>& GetTags() const	{ return m_Tags; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Array<const char*>& InTags );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Array<const char*>& InTags );

			}; // class GetUGCTemplatesCmd : public MessageBase

			class GetUGCTemplatesRes : public MessageBase
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
				uint64_t m_UGCIDs{};
			public:
				GetUGCTemplatesRes()
					{}

				GetUGCTemplatesRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetUGCTemplatesRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetUGCIDs() const	{ return m_UGCIDs; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCIDs );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCIDs );

			}; // class GetUGCTemplatesRes : public MessageBase

			// Cmd: Save UGC content data
			class SaveUGCCmd : public MessageBase
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
				ArrayView<uint8_t> m_UGCMetaDataRaw;
				mutable bool m_UGCMetaDataHasParsed = false;
				mutable VariableTable m_UGCMetaData;
				ArrayView<uint8_t> m_UGCContentsRaw;
				mutable bool m_UGCContentsHasParsed = false;
				mutable VariableTable m_UGCContents;
			public:
				SaveUGCCmd()
					{}

				SaveUGCCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SaveUGCCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Array<uint8_t>& GetUGCMetaDataRaw() const	{ return m_UGCMetaDataRaw; };
				const VariableTable& GetUGCMetaData() const;
				const Array<uint8_t>& GetUGCContentsRaw() const	{ return m_UGCContentsRaw; };
				const VariableTable& GetUGCContents() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const VariableTable &InUGCMetaData, const VariableTable &InUGCContents );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Array<uint8_t>& InUGCMetaData, const Array<uint8_t>& InUGCContents );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Array<uint8_t>& InUGCMetaData, const Array<uint8_t>& InUGCContents );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const VariableTable &InUGCMetaData, const VariableTable &InUGCContents );

			}; // class SaveUGCCmd : public MessageBase

			class SaveUGCRes : public MessageBase
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
				uint64_t m_UGCID{};
			public:
				SaveUGCRes()
					{}

				SaveUGCRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SaveUGCRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetUGCID() const	{ return m_UGCID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCID );

			}; // class SaveUGCRes : public MessageBase

			// Cmd: Request WhiteboardSharing
			class SearchUGCCmd : public MessageBase
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
				DynamicArray<const char*> m_Tags;
			public:
				SearchUGCCmd()
					{}

				SearchUGCCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SearchUGCCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Array<const char*>& GetTags() const	{ return m_Tags; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Array<const char*>& InTags );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Array<const char*>& InTags );

			}; // class SearchUGCCmd : public MessageBase

			class SearchUGCRes : public MessageBase
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
				SearchUGCRes()
					{}

				SearchUGCRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SearchUGCRes( const MessageHeader* pHeader )
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

			}; // class SearchUGCRes : public MessageBase

			// Cmd: Get UGC content info, name, thumb image and so on
			class GetUGCContentInfoCmd : public MessageBase
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
				uint64_t m_UGCID{};
			public:
				GetUGCContentInfoCmd()
					{}

				GetUGCContentInfoCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetUGCContentInfoCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetUGCID() const	{ return m_UGCID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InUGCID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InUGCID );

			}; // class GetUGCContentInfoCmd : public MessageBase

			class GetUGCContentInfoRes : public MessageBase
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
				ArrayView<uint8_t> m_UGCMetaDataRaw;
				mutable bool m_UGCMetaDataHasParsed = false;
				mutable VariableTable m_UGCMetaData;
			public:
				GetUGCContentInfoRes()
					{}

				GetUGCContentInfoRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetUGCContentInfoRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetUGCMetaDataRaw() const	{ return m_UGCMetaDataRaw; };
				const VariableTable& GetUGCMetaData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InUGCMetaData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InUGCMetaData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData );

			}; // class GetUGCContentInfoRes : public MessageBase

			// Cmd: Request WhiteboardSharing
			class DownloadUGCContentCmd : public MessageBase
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
				uint64_t m_UGCID{};
				uint8_t m_IsIncludeMetaData{};
			public:
				DownloadUGCContentCmd()
					{}

				DownloadUGCContentCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DownloadUGCContentCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetUGCID() const	{ return m_UGCID; };
				const uint8_t& GetIsIncludeMetaData() const	{ return m_IsIncludeMetaData; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InUGCID, const uint8_t &InIsIncludeMetaData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InUGCID, const uint8_t &InIsIncludeMetaData );

			}; // class DownloadUGCContentCmd : public MessageBase

			class DownloadUGCContentRes : public MessageBase
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
				ArrayView<uint8_t> m_UGCMetaDataRaw;
				mutable bool m_UGCMetaDataHasParsed = false;
				mutable VariableTable m_UGCMetaData;
			public:
				DownloadUGCContentRes()
					{}

				DownloadUGCContentRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DownloadUGCContentRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetUGCMetaDataRaw() const	{ return m_UGCMetaDataRaw; };
				const VariableTable& GetUGCMetaData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InUGCMetaData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InUGCMetaData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData );

			}; // class DownloadUGCContentRes : public MessageBase

			// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
			class RequestUGCZoneInstanceCmd : public MessageBase
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
				uint64_t m_UGCID{};
			public:
				RequestUGCZoneInstanceCmd()
					{}

				RequestUGCZoneInstanceCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestUGCZoneInstanceCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetUGCID() const	{ return m_UGCID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InUGCID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InUGCID );

			}; // class RequestUGCZoneInstanceCmd : public MessageBase

			class RequestUGCZoneInstanceRes : public MessageBase
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
				ArrayView<uint8_t> m_GameInstanceRaw;
				mutable bool m_GameInstanceHasParsed = false;
				mutable VariableTable m_GameInstance;
			public:
				RequestUGCZoneInstanceRes()
					{}

				RequestUGCZoneInstanceRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestUGCZoneInstanceRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetGameInstanceRaw() const	{ return m_GameInstanceRaw; };
				const VariableTable& GetGameInstance() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InGameInstance );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InGameInstance );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InGameInstance );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InGameInstance );

			}; // class RequestUGCZoneInstanceRes : public MessageBase

			// Cmd: Buy shop item prepare
			class BuyShopItemPrepareCmd : public MessageBase
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
				uint32_t m_ShopItemID{};
			public:
				BuyShopItemPrepareCmd()
					{}

				BuyShopItemPrepareCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				BuyShopItemPrepareCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetShopItemID() const	{ return m_ShopItemID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InShopItemID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InShopItemID );

			}; // class BuyShopItemPrepareCmd : public MessageBase

			class BuyShopItemPrepareRes : public MessageBase
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
				uint32_t m_ShopItemID{};
				const char* m_PurchaseID{};
			public:
				BuyShopItemPrepareRes()
					{}

				BuyShopItemPrepareRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				BuyShopItemPrepareRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetShopItemID() const	{ return m_ShopItemID; };
				const char* GetPurchaseID() const	{ return m_PurchaseID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID );

			}; // class BuyShopItemPrepareRes : public MessageBase

			// Cmd: Buy shop item
			class BuyShopItemCmd : public MessageBase
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
				uint32_t m_ShopItemID{};
				const char* m_Platform{};
				const char* m_PackageName{};
				const char* m_PurchaseTransactionID{};
				ArrayView<uint8_t> m_PurchaseToken;
			public:
				BuyShopItemCmd()
					{}

				BuyShopItemCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				BuyShopItemCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetShopItemID() const	{ return m_ShopItemID; };
				const char* GetPlatform() const	{ return m_Platform; };
				const char* GetPackageName() const	{ return m_PackageName; };
				const char* GetPurchaseTransactionID() const	{ return m_PurchaseTransactionID; };
				const Array<uint8_t>& GetPurchaseToken() const	{ return m_PurchaseToken; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken );

			}; // class BuyShopItemCmd : public MessageBase

			class BuyShopItemRes : public MessageBase
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
				uint32_t m_ShopItemID{};
			public:
				BuyShopItemRes()
					{}

				BuyShopItemRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				BuyShopItemRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetShopItemID() const	{ return m_ShopItemID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID );

			}; // class BuyShopItemRes : public MessageBase

			// Cmd: Create or Join Chat channel
			class CreateOrJoinChatChannelCmd : public MessageBase
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
				const char* m_ChannelName{};
				const char* m_Passcode{};
			public:
				CreateOrJoinChatChannelCmd()
					{}

				CreateOrJoinChatChannelCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateOrJoinChatChannelCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetChannelName() const	{ return m_ChannelName; };
				const char* GetPasscode() const	{ return m_Passcode; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode );

			}; // class CreateOrJoinChatChannelCmd : public MessageBase

			class CreateOrJoinChatChannelRes : public MessageBase
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
				uint64_t m_ChatUID{};
				PlayerID m_ChannelLeaderID{};
			public:
				CreateOrJoinChatChannelRes()
					{}

				CreateOrJoinChatChannelRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateOrJoinChatChannelRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const PlayerID& GetChannelLeaderID() const	{ return m_ChannelLeaderID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID );

			}; // class CreateOrJoinChatChannelRes : public MessageBase

			// Cmd: Join
			class JoinChatChannelCmd : public MessageBase
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
				uint64_t m_ChatUID{};
				AccountID m_InviterID{};
				const char* m_Passcode{};
			public:
				JoinChatChannelCmd()
					{}

				JoinChatChannelCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinChatChannelCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const AccountID& GetInviterID() const	{ return m_InviterID; };
				const char* GetPasscode() const	{ return m_Passcode; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode );

			}; // class JoinChatChannelCmd : public MessageBase

			class JoinChatChannelRes : public MessageBase
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
				uint64_t m_ChatUID{};
				PlayerID m_ChannelLeaderID{};
			public:
				JoinChatChannelRes()
					{}

				JoinChatChannelRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				JoinChatChannelRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const PlayerID& GetChannelLeaderID() const	{ return m_ChannelLeaderID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID );

			}; // class JoinChatChannelRes : public MessageBase

			// S2C: Player Joined event
			class ChatChannelPlayerJoinedS2CEvt : public MessageBase
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
				uint64_t m_ChatUID{};
				PlayerInformation m_JoinedPlayer{};
			public:
				ChatChannelPlayerJoinedS2CEvt()
					{}

				ChatChannelPlayerJoinedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelPlayerJoinedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const PlayerInformation& GetJoinedPlayer() const	{ return m_JoinedPlayer; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer );

			}; // class ChatChannelPlayerJoinedS2CEvt : public MessageBase

			// S2C: ChatChannel leader changed event
			class ChatChannelLeaderChangedS2CEvt : public MessageBase
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
				uint64_t m_ChatUID{};
				AccountID m_NewLeaderID{};
			public:
				ChatChannelLeaderChangedS2CEvt()
					{}

				ChatChannelLeaderChangedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelLeaderChangedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const AccountID& GetNewLeaderID() const	{ return m_NewLeaderID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InNewLeaderID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InChatUID, const AccountID &InNewLeaderID );

			}; // class ChatChannelLeaderChangedS2CEvt : public MessageBase

			// Cmd: Leave ChatChannel command
			class LeaveChatChannelCmd : public MessageBase
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
				uint64_t m_ChatUID{};
				AccountID m_PlayerID{};
			public:
				LeaveChatChannelCmd()
					{}

				LeaveChatChannelCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LeaveChatChannelCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const AccountID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID );

			}; // class LeaveChatChannelCmd : public MessageBase

			class LeaveChatChannelRes : public MessageBase
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
				LeaveChatChannelRes()
					{}

				LeaveChatChannelRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LeaveChatChannelRes( const MessageHeader* pHeader )
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

			}; // class LeaveChatChannelRes : public MessageBase

			// S2C: ChatChannel Player left event
			class ChatChannelPlayerLeftS2CEvt : public MessageBase
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
				uint64_t m_ChatUID{};
				AccountID m_LeftPlayerID{};
			public:
				ChatChannelPlayerLeftS2CEvt()
					{}

				ChatChannelPlayerLeftS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelPlayerLeftS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const AccountID& GetLeftPlayerID() const	{ return m_LeftPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InLeftPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InChatUID, const AccountID &InLeftPlayerID );

			}; // class ChatChannelPlayerLeftS2CEvt : public MessageBase

			// Cmd: Kick player from the ChatChannel
			class ChatChannelKickPlayerCmd : public MessageBase
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
				uint64_t m_ChatUID{};
				AccountID m_PlayerID{};
				AccountID m_PlayerToKick{};
			public:
				ChatChannelKickPlayerCmd()
					{}

				ChatChannelKickPlayerCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelKickPlayerCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const AccountID& GetPlayerID() const	{ return m_PlayerID; };
				const AccountID& GetPlayerToKick() const	{ return m_PlayerToKick; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );

			}; // class ChatChannelKickPlayerCmd : public MessageBase

			class ChatChannelKickPlayerRes : public MessageBase
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
				ChatChannelKickPlayerRes()
					{}

				ChatChannelKickPlayerRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelKickPlayerRes( const MessageHeader* pHeader )
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

			}; // class ChatChannelKickPlayerRes : public MessageBase

			// S2C: ChatChannel Player kicked message
			class ChatChannelPlayerKickedS2CEvt : public MessageBase
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
				uint64_t m_ChatUID{};
				AccountID m_KickedPlayerID{};
			public:
				ChatChannelPlayerKickedS2CEvt()
					{}

				ChatChannelPlayerKickedS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelPlayerKickedS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const AccountID& GetKickedPlayerID() const	{ return m_KickedPlayerID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InKickedPlayerID );
				static Result Create( MessageHeader* messageBuffer, const uint64_t &InChatUID, const AccountID &InKickedPlayerID );

			}; // class ChatChannelPlayerKickedS2CEvt : public MessageBase

			// Cmd: Chat channel sending chatting message
			class ChatChannelChatMessageCmd : public MessageBase
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
				uint64_t m_ChatUID{};
				ArrayView<uint8_t> m_ChatMetaDataRaw;
				mutable bool m_ChatMetaDataHasParsed = false;
				mutable VariableTable m_ChatMetaData;
				const char* m_ChatMessage{};
			public:
				ChatChannelChatMessageCmd()
					{}

				ChatChannelChatMessageCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelChatMessageCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetChatUID() const	{ return m_ChatUID; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InChatUID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InChatUID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class ChatChannelChatMessageCmd : public MessageBase

			class ChatChannelChatMessageRes : public MessageBase
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
				ChatChannelChatMessageRes()
					{}

				ChatChannelChatMessageRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelChatMessageRes( const MessageHeader* pHeader )
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

			}; // class ChatChannelChatMessageRes : public MessageBase

			// S2C: ChatChannel Chatting message event
			class ChatChannelChatMessageS2CEvt : public MessageBase
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
				PlayerID m_SenderID{};
				ArrayView<uint8_t> m_ChatMetaDataRaw;
				mutable bool m_ChatMetaDataHasParsed = false;
				mutable VariableTable m_ChatMetaData;
				const char* m_ChatMessage{};
			public:
				ChatChannelChatMessageS2CEvt()
					{}

				ChatChannelChatMessageS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ChatChannelChatMessageS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const PlayerID& GetSenderID() const	{ return m_SenderID; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage );
				static size_t CalculateMessageSize( const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class ChatChannelChatMessageS2CEvt : public MessageBase

			// Cmd: Whisper(tell) other player chatting
			class WhisperMessageCmd : public MessageBase
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
				PlayerID m_ReceiverID{};
				const char* m_ReceiverName{};
				ArrayView<uint8_t> m_ChatMetaDataRaw;
				mutable bool m_ChatMetaDataHasParsed = false;
				mutable VariableTable m_ChatMetaData;
				const char* m_ChatMessage{};
			public:
				WhisperMessageCmd()
					{}

				WhisperMessageCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhisperMessageCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const PlayerID& GetReceiverID() const	{ return m_ReceiverID; };
				const char* GetReceiverName() const	{ return m_ReceiverName; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class WhisperMessageCmd : public MessageBase

			class WhisperMessageRes : public MessageBase
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
				WhisperMessageRes()
					{}

				WhisperMessageRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhisperMessageRes( const MessageHeader* pHeader )
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

			}; // class WhisperMessageRes : public MessageBase

			// S2C: Other player whispered(tell) to me message event
			class WhisperMessageS2CEvt : public MessageBase
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
				PlayerID m_SenderID{};
				ArrayView<uint8_t> m_ChatMetaDataRaw;
				mutable bool m_ChatMetaDataHasParsed = false;
				mutable VariableTable m_ChatMetaData;
				const char* m_ChatMessage{};
			public:
				WhisperMessageS2CEvt()
					{}

				WhisperMessageS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				WhisperMessageS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const PlayerID& GetSenderID() const	{ return m_SenderID; };
				const Array<uint8_t>& GetChatMetaDataRaw() const	{ return m_ChatMetaDataRaw; };
				const VariableTable& GetChatMetaData() const;
				const char* GetChatMessage() const	{ return m_ChatMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage );
				static size_t CalculateMessageSize( const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage );
				static Result Create( MessageHeader* messageBuffer, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage );

			}; // class WhisperMessageS2CEvt : public MessageBase

			// Cmd: Create character
			class CreateCharacterCmd : public MessageBase
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
				const char* m_CharacterName{};
				ArrayView<uint8_t> m_PublicDataRaw;
				mutable bool m_PublicDataHasParsed = false;
				mutable VariableTable m_PublicData;
				ArrayView<uint8_t> m_PrivateDataRaw;
				mutable bool m_PrivateDataHasParsed = false;
				mutable VariableTable m_PrivateData;
			public:
				CreateCharacterCmd()
					{}

				CreateCharacterCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateCharacterCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetCharacterName() const	{ return m_CharacterName; };
				const Array<uint8_t>& GetPublicDataRaw() const	{ return m_PublicDataRaw; };
				const VariableTable& GetPublicData() const;
				const Array<uint8_t>& GetPrivateDataRaw() const	{ return m_PrivateDataRaw; };
				const VariableTable& GetPrivateData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InPrivateData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InPrivateData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData );

			}; // class CreateCharacterCmd : public MessageBase

			class CreateCharacterRes : public MessageBase
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
				uint32_t m_CharacterID{};
			public:
				CreateCharacterRes()
					{}

				CreateCharacterRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateCharacterRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetCharacterID() const	{ return m_CharacterID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InCharacterID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InCharacterID );

			}; // class CreateCharacterRes : public MessageBase

			// Cmd: Delete character
			class DeleteCharacterCmd : public MessageBase
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
				uint32_t m_CharacterID{};
			public:
				DeleteCharacterCmd()
					{}

				DeleteCharacterCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DeleteCharacterCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetCharacterID() const	{ return m_CharacterID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InCharacterID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InCharacterID );

			}; // class DeleteCharacterCmd : public MessageBase

			class DeleteCharacterRes : public MessageBase
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
				DeleteCharacterRes()
					{}

				DeleteCharacterRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DeleteCharacterRes( const MessageHeader* pHeader )
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

			}; // class DeleteCharacterRes : public MessageBase

			// Cmd: Get character list
			class GetCharacterListCmd : public MessageBase
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
			public:
				GetCharacterListCmd()
					{}

				GetCharacterListCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetCharacterListCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID );

			}; // class GetCharacterListCmd : public MessageBase

			class GetCharacterListRes : public MessageBase
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
				DynamicArray<VariableTable> m_Characters;
			public:
				GetCharacterListRes()
					{}

				GetCharacterListRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetCharacterListRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<VariableTable>& GetCharacters() const	{ return m_Characters; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters );

			}; // class GetCharacterListRes : public MessageBase

			// Cmd: 
			class GetCharacterDataCmd : public MessageBase
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
				uint32_t m_CharacterID{};
			public:
				GetCharacterDataCmd()
					{}

				GetCharacterDataCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetCharacterDataCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetCharacterID() const	{ return m_CharacterID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InCharacterID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InCharacterID );

			}; // class GetCharacterDataCmd : public MessageBase

			class GetCharacterDataRes : public MessageBase
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
				ArrayView<uint8_t> m_PrivateDataRaw;
				mutable bool m_PrivateDataHasParsed = false;
				mutable VariableTable m_PrivateData;
				ArrayView<uint8_t> m_EquipDataRaw;
				mutable bool m_EquipDataHasParsed = false;
				mutable VariableTable m_EquipData;
			public:
				GetCharacterDataRes()
					{}

				GetCharacterDataRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetCharacterDataRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetPrivateDataRaw() const	{ return m_PrivateDataRaw; };
				const VariableTable& GetPrivateData() const;
				const Array<uint8_t>& GetEquipDataRaw() const	{ return m_EquipDataRaw; };
				const VariableTable& GetEquipData() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InPrivateData, const Array<uint8_t>& InEquipData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InPrivateData, const Array<uint8_t>& InEquipData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData );

			}; // class GetCharacterDataRes : public MessageBase

			// Cmd: Select character
			class SelectCharacterCmd : public MessageBase
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
				uint32_t m_CharacterID{};
			public:
				SelectCharacterCmd()
					{}

				SelectCharacterCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SelectCharacterCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetCharacterID() const	{ return m_CharacterID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InCharacterID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InCharacterID );

			}; // class SelectCharacterCmd : public MessageBase

			class SelectCharacterRes : public MessageBase
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
				uint32_t m_CharacterID{};
				ArrayView<uint8_t> m_AttributesRaw;
				mutable bool m_AttributesHasParsed = false;
				mutable VariableTable m_Attributes;
			public:
				SelectCharacterRes()
					{}

				SelectCharacterRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				SelectCharacterRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetCharacterID() const	{ return m_CharacterID; };
				const Array<uint8_t>& GetAttributesRaw() const	{ return m_AttributesRaw; };
				const VariableTable& GetAttributes() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const Array<uint8_t>& InAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const Array<uint8_t>& InAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes );

			}; // class SelectCharacterRes : public MessageBase

			// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
			class RequestServerNoticeUpdateCmd : public MessageBase
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
			public:
				RequestServerNoticeUpdateCmd()
					{}

				RequestServerNoticeUpdateCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestServerNoticeUpdateCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID );

			}; // class RequestServerNoticeUpdateCmd : public MessageBase

			class RequestServerNoticeUpdateRes : public MessageBase
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
				RequestServerNoticeUpdateRes()
					{}

				RequestServerNoticeUpdateRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				RequestServerNoticeUpdateRes( const MessageHeader* pHeader )
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

			}; // class RequestServerNoticeUpdateRes : public MessageBase

			// S2C: Server Notice updated event
			class ServerNoticeS2CEvt : public MessageBase
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
				int8_t m_NoticeCategory{};
				const char* m_ServerNoticeMessage{};
			public:
				ServerNoticeS2CEvt()
					{}

				ServerNoticeS2CEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				ServerNoticeS2CEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const int8_t& GetNoticeCategory() const	{ return m_NoticeCategory; };
				const char* GetServerNoticeMessage() const	{ return m_ServerNoticeMessage; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const int8_t &InNoticeCategory, const char* InServerNoticeMessage );
				static Result Create( MessageHeader* messageBuffer, const int8_t &InNoticeCategory, const char* InServerNoticeMessage );

			}; // class ServerNoticeS2CEvt : public MessageBase

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
				const Array<uint8_t>& GetParametersRaw() const	{ return m_ParametersRaw; };
				const VariableTable& GetParameters() const;

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters );
				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters );

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





		}; // namespace Game
	}; // namespace Message
}; // namespace SF



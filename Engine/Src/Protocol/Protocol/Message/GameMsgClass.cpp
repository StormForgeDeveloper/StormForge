////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Game Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "String/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/Message/GameMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace Game
		{
 			// C2S: Client heart bit
			const MessageID HeartBitC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 0);
			Result HeartBitC2SEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;


				protocolChkPtr(pIMsg);




			Proc_End:

				return hr;

			}; // Result HeartBitC2SEvt::ParseMessage( MessageData* pIMsg )

			Result HeartBitC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				HeartBitC2SEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));



			Proc_End:

				return hr;

			}; // Result HeartBitC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result HeartBitC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) HeartBitC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result HeartBitC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* HeartBitC2SEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) );


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::HeartBitC2SEvt::MID, __uiMessageSize ) );



			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* HeartBitC2SEvt::Create( IHeap& memHeap )



			Result HeartBitC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				HeartBitC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "HeartBit:{0}:{1} ",
						prefix, pMsg->GetMessageHeader()->Length); 
				return ResultCode::SUCCESS;
			}; // Result HeartBitC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Player connected from a login server and moved to game server
			const MessageID JoinGameServerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 1);
			Result JoinGameServerCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_AccID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LoginEntityUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result JoinGameServerCmd::ParseMessage( MessageData* pIMsg )

			Result JoinGameServerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinGameServerCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());


			Proc_End:

				return hr;

			}; // Result JoinGameServerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinGameServerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinGameServerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameServerCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InAccID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));
				Protocol::PackParamCopy( pMsgData, &InLoginEntityUID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinGameServerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )



			Result JoinGameServerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameServerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGameServer:{0}:{1} , TransactionID:{2}, AccID:{3}, Ticket:{4}, LoginEntityUID:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameServerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinGameServerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 1);
			Result JoinGameServerRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfNickName = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfNickName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_NickName, pCur, iMsgSize, sizeof(char)*uiSizeOfNickName ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyLeaderID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_MatchingTicket, pCur, iMsgSize, sizeof(MatchingQueueTicket) ) );


			Proc_End:

				return hr;

			}; // Result JoinGameServerRes::ParseMessage( MessageData* pIMsg )

			Result JoinGameServerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinGameServerRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("GameUID", parser.GetGameUID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());
				variableBuilder.SetVariable("MatchingTicket", parser.GetMatchingTicket());


			Proc_End:

				return hr;

			}; // Result JoinGameServerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinGameServerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinGameServerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInNickNameLength = InNickName ? (uint16_t)(strlen(InNickName)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInNickNameLength 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(MatchingQueueTicket));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameServerRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &__uiInNickNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InNickName ? InNickName : "", __uiInNickNameLength );
				Protocol::PackParamCopy( pMsgData, &InGameUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPartyLeaderID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InMatchingTicket, sizeof(MatchingQueueTicket));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinGameServerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )



			Result JoinGameServerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameServerRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGameServer:{0}:{1} , TransactionID:{2}, Result:{3:X8}, NickName:{4,60}, GameUID:{5}, PartyUID:{6}, PartyLeaderID:{7}, MatchingTicket:{8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNickName(), parser.GetGameUID(), parser.GetPartyUID(), parser.GetPartyLeaderID(), parser.GetMatchingTicket()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameServerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: player complition statues
			const MessageID GetComplitionStateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 2);
			Result GetComplitionStateCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessage( MessageData* pIMsg )

			Result GetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetComplitionStateCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetComplitionStateCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetComplitionStateCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GetComplitionStateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetComplitionStateCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetComplitionState:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetComplitionStateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetComplitionStateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 2);
			Result GetComplitionStateRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfComplitionState = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfComplitionState, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ComplitionState, pCur, iMsgSize, sizeof(char)*uiSizeOfComplitionState ) );


			Proc_End:

				return hr;

			}; // Result GetComplitionStateRes::ParseMessage( MessageData* pIMsg )

			Result GetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetComplitionStateRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());


			Proc_End:

				return hr;

			}; // Result GetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetComplitionStateRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInComplitionStateLength = InComplitionState ? (uint16_t)(strlen(InComplitionState)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInComplitionStateLength 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetComplitionStateRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &__uiInComplitionStateLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InComplitionState ? InComplitionState : "", __uiInComplitionStateLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )



			Result GetComplitionStateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetComplitionStateRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetComplitionState:{0}:{1} , TransactionID:{2}, Result:{3:X8}, ComplitionState:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetComplitionState()); 
				return ResultCode::SUCCESS;
			}; // Result GetComplitionStateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Player complition state
			const MessageID SetComplitionStateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 3);
			Result SetComplitionStateCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfComplitionState = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfComplitionState, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ComplitionState, pCur, iMsgSize, sizeof(char)*uiSizeOfComplitionState ) );


			Proc_End:

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessage( MessageData* pIMsg )

			Result SetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetComplitionStateCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());


			Proc_End:

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetComplitionStateCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InComplitionState )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInComplitionStateLength = InComplitionState ? (uint16_t)(strlen(InComplitionState)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInComplitionStateLength 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetComplitionStateCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInComplitionStateLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InComplitionState ? InComplitionState : "", __uiInComplitionStateLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InComplitionState )



			Result SetComplitionStateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetComplitionStateCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetComplitionState:{0}:{1} , TransactionID:{2}, ComplitionState:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetComplitionState()); 
				return ResultCode::SUCCESS;
			}; // Result SetComplitionStateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID SetComplitionStateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 3);
			Result SetComplitionStateRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result SetComplitionStateRes::ParseMessage( MessageData* pIMsg )

			Result SetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetComplitionStateRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result SetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetComplitionStateRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetComplitionStateRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result SetComplitionStateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetComplitionStateRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetComplitionState:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result SetComplitionStateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			const MessageID RegisterGCMCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 4);
			Result RegisterGCMCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfGCMRegisteredID = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfGCMRegisteredID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_GCMRegisteredID, pCur, iMsgSize, sizeof(char)*uiSizeOfGCMRegisteredID ) );


			Proc_End:

				return hr;

			}; // Result RegisterGCMCmd::ParseMessage( MessageData* pIMsg )

			Result RegisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RegisterGCMCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());


			Proc_End:

				return hr;

			}; // Result RegisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RegisterGCMCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RegisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInGCMRegisteredIDLength = InGCMRegisteredID ? (uint16_t)(strlen(InGCMRegisteredID)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInGCMRegisteredIDLength 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RegisterGCMCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInGCMRegisteredIDLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InGCMRegisteredID ? InGCMRegisteredID : "", __uiInGCMRegisteredIDLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RegisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )



			Result RegisterGCMCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RegisterGCMCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RegisterGCM:{0}:{1} , TransactionID:{2}, GCMRegisteredID:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGCMRegisteredID()); 
				return ResultCode::SUCCESS;
			}; // Result RegisterGCMCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID RegisterGCMRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 4);
			Result RegisterGCMRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result RegisterGCMRes::ParseMessage( MessageData* pIMsg )

			Result RegisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RegisterGCMRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result RegisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RegisterGCMRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RegisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RegisterGCMRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RegisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result RegisterGCMRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RegisterGCMRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RegisterGCM:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result RegisterGCMRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Unregister Google notification service ID
			const MessageID UnregisterGCMCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 5);
			Result UnregisterGCMCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfGCMRegisteredID = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfGCMRegisteredID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_GCMRegisteredID, pCur, iMsgSize, sizeof(char)*uiSizeOfGCMRegisteredID ) );


			Proc_End:

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessage( MessageData* pIMsg )

			Result UnregisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UnregisterGCMCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());


			Proc_End:

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) UnregisterGCMCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* UnregisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInGCMRegisteredIDLength = InGCMRegisteredID ? (uint16_t)(strlen(InGCMRegisteredID)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInGCMRegisteredIDLength 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::UnregisterGCMCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInGCMRegisteredIDLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InGCMRegisteredID ? InGCMRegisteredID : "", __uiInGCMRegisteredIDLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* UnregisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )



			Result UnregisterGCMCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UnregisterGCMCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UnregisterGCM:{0}:{1} , TransactionID:{2}, GCMRegisteredID:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGCMRegisteredID()); 
				return ResultCode::SUCCESS;
			}; // Result UnregisterGCMCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID UnregisterGCMRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 5);
			Result UnregisterGCMRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result UnregisterGCMRes::ParseMessage( MessageData* pIMsg )

			Result UnregisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UnregisterGCMRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result UnregisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) UnregisterGCMRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* UnregisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::UnregisterGCMRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* UnregisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result UnregisterGCMRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UnregisterGCMRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UnregisterGCM:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result UnregisterGCMRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Invite friend
			const MessageID InviteFriendCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 6);
			Result InviteFriendCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_FriendID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result InviteFriendCmd::ParseMessage( MessageData* pIMsg )

			Result InviteFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				InviteFriendCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());


			Proc_End:

				return hr;

			}; // Result InviteFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) InviteFriendCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* InviteFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::InviteFriendCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InFriendID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* InviteFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )



			Result InviteFriendCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				InviteFriendCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "InviteFriend:{0}:{1} , TransactionID:{2}, FriendID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result InviteFriendCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID InviteFriendRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 6);
			Result InviteFriendRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result InviteFriendRes::ParseMessage( MessageData* pIMsg )

			Result InviteFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				InviteFriendRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result InviteFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) InviteFriendRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* InviteFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::InviteFriendRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* InviteFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result InviteFriendRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				InviteFriendRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "InviteFriend:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result InviteFriendRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Accept friend request
			const MessageID AcceptFriendRequestCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 7);
			Result AcceptFriendRequestCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_InviterID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_InviterFacebookUID, pCur, iMsgSize, sizeof(FacebookUID) ) );


			Proc_End:

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessage( MessageData* pIMsg )

			Result AcceptFriendRequestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AcceptFriendRequestCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterFacebookUID", parser.GetInviterFacebookUID());


			Proc_End:

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AcceptFriendRequestCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AcceptFriendRequestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(FacebookUID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptFriendRequestCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InInviterID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InInviterFacebookUID, sizeof(FacebookUID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AcceptFriendRequestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID )



			Result AcceptFriendRequestCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AcceptFriendRequestCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AcceptFriendRequest:{0}:{1} , TransactionID:{2}, InviterID:{3}, InviterFacebookUID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetInviterID(), parser.GetInviterFacebookUID()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptFriendRequestCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID AcceptFriendRequestRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 7);
			Result AcceptFriendRequestRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NewFriend, pCur, iMsgSize, sizeof(FriendInformation) ) );


			Proc_End:

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessage( MessageData* pIMsg )

			Result AcceptFriendRequestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AcceptFriendRequestRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NewFriend", parser.GetNewFriend());


			Proc_End:

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AcceptFriendRequestRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AcceptFriendRequestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(FriendInformation));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptFriendRequestRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InNewFriend, sizeof(FriendInformation));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AcceptFriendRequestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )



			Result AcceptFriendRequestRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AcceptFriendRequestRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AcceptFriendRequest:{0}:{1} , TransactionID:{2}, Result:{3:X8}, NewFriend:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNewFriend()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptFriendRequestRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Notification for friend request is accepted
			const MessageID FriendRequestAcceptedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 8);
			Result FriendRequestAcceptedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Accepter, pCur, iMsgSize, sizeof(FriendInformation) ) );


			Proc_End:

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result FriendRequestAcceptedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FriendRequestAcceptedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Accepter", parser.GetAccepter());


			Proc_End:

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) FriendRequestAcceptedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* FriendRequestAcceptedS2CEvt::Create( IHeap& memHeap, const FriendInformation &InAccepter )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(FriendInformation));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FriendRequestAcceptedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InAccepter, sizeof(FriendInformation));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* FriendRequestAcceptedS2CEvt::Create( IHeap& memHeap, const FriendInformation &InAccepter )



			Result FriendRequestAcceptedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FriendRequestAcceptedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FriendRequestAccepted:{0}:{1} , Accepter:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetAccepter()); 
				return ResultCode::SUCCESS;
			}; // Result FriendRequestAcceptedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Remove friden form the friend list
			const MessageID RemoveFriendCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 9);
			Result RemoveFriendCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_FriendID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result RemoveFriendCmd::ParseMessage( MessageData* pIMsg )

			Result RemoveFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RemoveFriendCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());


			Proc_End:

				return hr;

			}; // Result RemoveFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RemoveFriendCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RemoveFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RemoveFriendCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InFriendID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RemoveFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )



			Result RemoveFriendCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RemoveFriendCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RemoveFriend:{0}:{1} , TransactionID:{2}, FriendID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveFriendCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID RemoveFriendRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 9);
			Result RemoveFriendRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_FriendID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result RemoveFriendRes::ParseMessage( MessageData* pIMsg )

			Result RemoveFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RemoveFriendRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());


			Proc_End:

				return hr;

			}; // Result RemoveFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RemoveFriendRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RemoveFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RemoveFriendRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InFriendID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RemoveFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )



			Result RemoveFriendRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RemoveFriendRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RemoveFriend:{0}:{1} , TransactionID:{2}, Result:{3:X8}, FriendID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveFriendRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Friend removed
			const MessageID FriendRemovedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 10);
			Result FriendRemovedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_FriendID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result FriendRemovedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FriendRemovedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("FriendID", parser.GetFriendID());


			Proc_End:

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) FriendRemovedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* FriendRemovedS2CEvt::Create( IHeap& memHeap, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FriendRemovedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InFriendID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* FriendRemovedS2CEvt::Create( IHeap& memHeap, const AccountID &InFriendID )



			Result FriendRemovedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FriendRemovedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FriendRemoved:{0}:{1} , FriendID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result FriendRemovedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Get friend list
			const MessageID GetFriendListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 11);
			Result GetFriendListCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_StartIndex, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Count, pCur, iMsgSize, sizeof(uint16_t) ) );


			Proc_End:

				return hr;

			}; // Result GetFriendListCmd::ParseMessage( MessageData* pIMsg )

			Result GetFriendListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetFriendListCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("StartIndex", parser.GetStartIndex());
				variableBuilder.SetVariable("Count", parser.GetCount());


			Proc_End:

				return hr;

			}; // Result GetFriendListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetFriendListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetFriendListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint16_t)
					+ sizeof(uint16_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetFriendListCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InStartIndex, sizeof(uint16_t));
				Protocol::PackParamCopy( pMsgData, &InCount, sizeof(uint16_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetFriendListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )



			Result GetFriendListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetFriendListCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetFriendList:{0}:{1} , TransactionID:{2}, StartIndex:{3}, Count:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetStartIndex(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result GetFriendListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetFriendListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 11);
			Result GetFriendListRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofFriendList = 0; FriendInformation* pFriendList = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_MaxFriendSlot, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalNumberOfFriends, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_StartIndex, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofFriendList, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pFriendList, pCur, iMsgSize, sizeof(FriendInformation)*numberofFriendList ) );
				m_FriendList.SetLinkedBuffer(numberofFriendList, numberofFriendList, pFriendList);


			Proc_End:

				return hr;

			}; // Result GetFriendListRes::ParseMessage( MessageData* pIMsg )

			Result GetFriendListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetFriendListRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("MaxFriendSlot", parser.GetMaxFriendSlot());
				variableBuilder.SetVariable("TotalNumberOfFriends", parser.GetTotalNumberOfFriends());
				variableBuilder.SetVariable("StartIndex", parser.GetStartIndex());
				variableBuilder.SetVariable("FriendList", parser.GetFriendList());


			Proc_End:

				return hr;

			}; // Result GetFriendListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetFriendListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetFriendListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint16_t)
					+ sizeof(uint16_t)
					+ sizeof(uint16_t)
					+ sizeof(FriendInformation)*InFriendList.size() + sizeof(uint16_t));


				uint16_t numberOfInFriendList = (uint16_t)InFriendList.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetFriendListRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InMaxFriendSlot, sizeof(uint16_t));
				Protocol::PackParamCopy( pMsgData, &InTotalNumberOfFriends, sizeof(uint16_t));
				Protocol::PackParamCopy( pMsgData, &InStartIndex, sizeof(uint16_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInFriendList, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InFriendList.data(), (INT)(sizeof(FriendInformation)*InFriendList.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetFriendListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )



			Result GetFriendListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetFriendListRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetFriendList:{0}:{1} , TransactionID:{2}, Result:{3:X8}, MaxFriendSlot:{4}, TotalNumberOfFriends:{5}, StartIndex:{6}, FriendList:{7,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetMaxFriendSlot(), parser.GetTotalNumberOfFriends(), parser.GetStartIndex(), parser.GetFriendList()); 
				return ResultCode::SUCCESS;
			}; // Result GetFriendListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Query notification list
			const MessageID GetNotificationListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 12);
			Result GetNotificationListCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GetNotificationListCmd::ParseMessage( MessageData* pIMsg )

			Result GetNotificationListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetNotificationListCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result GetNotificationListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetNotificationListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetNotificationListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetNotificationListCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetNotificationListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GetNotificationListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetNotificationListCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetNotificationList:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetNotificationListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetNotificationListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 12);
			Result GetNotificationListRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result GetNotificationListRes::ParseMessage( MessageData* pIMsg )

			Result GetNotificationListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetNotificationListRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result GetNotificationListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetNotificationListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetNotificationListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetNotificationListRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetNotificationListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result GetNotificationListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetNotificationListRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetNotificationList:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result GetNotificationListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Delete notification
			const MessageID DeleteNotificationCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 13);
			Result DeleteNotificationCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NotificationID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessage( MessageData* pIMsg )

			Result DeleteNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DeleteNotificationCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());


			Proc_End:

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) DeleteNotificationCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* DeleteNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteNotificationCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InNotificationID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* DeleteNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )



			Result DeleteNotificationCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DeleteNotificationCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DeleteNotification:{0}:{1} , TransactionID:{2}, NotificationID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteNotificationCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID DeleteNotificationRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 13);
			Result DeleteNotificationRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NotificationID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result DeleteNotificationRes::ParseMessage( MessageData* pIMsg )

			Result DeleteNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DeleteNotificationRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());


			Proc_End:

				return hr;

			}; // Result DeleteNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) DeleteNotificationRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* DeleteNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteNotificationRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InNotificationID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* DeleteNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )



			Result DeleteNotificationRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DeleteNotificationRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DeleteNotification:{0}:{1} , TransactionID:{2}, Result:{3:X8}, NotificationID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteNotificationRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Set notification is read
			const MessageID SetNotificationReadCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 14);
			Result SetNotificationReadCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NotificationID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessage( MessageData* pIMsg )

			Result SetNotificationReadCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetNotificationReadCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());


			Proc_End:

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetNotificationReadCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetNotificationReadCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNotificationReadCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InNotificationID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetNotificationReadCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )



			Result SetNotificationReadCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetNotificationReadCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetNotificationRead:{0}:{1} , TransactionID:{2}, NotificationID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result SetNotificationReadCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID SetNotificationReadRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 14);
			Result SetNotificationReadRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NotificationID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result SetNotificationReadRes::ParseMessage( MessageData* pIMsg )

			Result SetNotificationReadRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetNotificationReadRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());


			Proc_End:

				return hr;

			}; // Result SetNotificationReadRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetNotificationReadRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetNotificationReadRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNotificationReadRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InNotificationID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetNotificationReadRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )



			Result SetNotificationReadRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetNotificationReadRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetNotificationRead:{0}:{1} , TransactionID:{2}, Result:{3:X8}, NotificationID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result SetNotificationReadRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Accept notification
			const MessageID AcceptNotificationCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 15);
			Result AcceptNotificationCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NotificationID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessage( MessageData* pIMsg )

			Result AcceptNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AcceptNotificationCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());


			Proc_End:

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AcceptNotificationCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AcceptNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptNotificationCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InNotificationID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AcceptNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )



			Result AcceptNotificationCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AcceptNotificationCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AcceptNotification:{0}:{1} , TransactionID:{2}, NotificationID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptNotificationCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID AcceptNotificationRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 15);
			Result AcceptNotificationRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NotificationID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result AcceptNotificationRes::ParseMessage( MessageData* pIMsg )

			Result AcceptNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AcceptNotificationRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());


			Proc_End:

				return hr;

			}; // Result AcceptNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AcceptNotificationRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AcceptNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptNotificationRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InNotificationID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AcceptNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )



			Result AcceptNotificationRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AcceptNotificationRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AcceptNotification:{0}:{1} , TransactionID:{2}, Result:{3:X8}, NotificationID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptNotificationRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Notify new notification
			const MessageID NotifyS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 16);
			Result NotifyS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfMessageText = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_NotificationID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NotificationType, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_MessageParam0, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_MessageParam1, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfMessageText, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_MessageText, pCur, iMsgSize, sizeof(char)*uiSizeOfMessageText ) );
				protocolChk( Protocol::StreamParamCopy( &m_IsRead, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TimeStamp, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result NotifyS2CEvt::ParseMessage( MessageData* pIMsg )

			Result NotifyS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				NotifyS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());
				variableBuilder.SetVariable("NotificationType", parser.GetNotificationType());
				variableBuilder.SetVariable("MessageParam0", parser.GetMessageParam0());
				variableBuilder.SetVariable("MessageParam1", parser.GetMessageParam1());
				variableBuilder.SetVariable("MessageText", parser.GetMessageText());
				variableBuilder.SetVariable("IsRead", parser.GetIsRead());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());


			Proc_End:

				return hr;

			}; // Result NotifyS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) NotifyS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* NotifyS2CEvt::Create( IHeap& memHeap, const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInMessageTextLength = InMessageText ? (uint16_t)(strlen(InMessageText)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInMessageTextLength 
					+ sizeof(uint32_t)
					+ sizeof(uint32_t)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(uint8_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::NotifyS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InNotificationID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InNotificationType, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InMessageParam0, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InMessageParam1, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInMessageTextLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InMessageText ? InMessageText : "", __uiInMessageTextLength );
				Protocol::PackParamCopy( pMsgData, &InIsRead, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InTimeStamp, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* NotifyS2CEvt::Create( IHeap& memHeap, const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )



			Result NotifyS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				NotifyS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Notify:{0}:{1} , NotificationID:{2}, NotificationType:{3}, MessageParam0:{4}, MessageParam1:{5}, MessageText:{6,60}, IsRead:{7}, TimeStamp:{8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetNotificationID(), parser.GetNotificationType(), parser.GetMessageParam0(), parser.GetMessageParam1(), parser.GetMessageText(), parser.GetIsRead(), parser.GetTimeStamp()); 
				return ResultCode::SUCCESS;
			}; // Result NotifyS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Query playerID list
			const MessageID FindPlayerByEMailCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 17);
			Result FindPlayerByEMailCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfPlayerEMail = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPlayerEMail, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_PlayerEMail, pCur, iMsgSize, sizeof(char)*uiSizeOfPlayerEMail ) );


			Proc_End:

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessage( MessageData* pIMsg )

			Result FindPlayerByEMailCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FindPlayerByEMailCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerEMail", parser.GetPlayerEMail());


			Proc_End:

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) FindPlayerByEMailCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* FindPlayerByEMailCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InPlayerEMail )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInPlayerEMailLength = InPlayerEMail ? (uint16_t)(strlen(InPlayerEMail)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInPlayerEMailLength 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByEMailCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInPlayerEMailLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPlayerEMail ? InPlayerEMail : "", __uiInPlayerEMailLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* FindPlayerByEMailCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InPlayerEMail )



			Result FindPlayerByEMailCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FindPlayerByEMailCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FindPlayerByEMail:{0}:{1} , TransactionID:{2}, PlayerEMail:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayerEMail()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByEMailCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID FindPlayerByEMailRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 17);
			Result FindPlayerByEMailRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Player, pCur, iMsgSize, sizeof(PlayerInformation) ) );


			Proc_End:

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessage( MessageData* pIMsg )

			Result FindPlayerByEMailRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FindPlayerByEMailRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", parser.GetPlayer());


			Proc_End:

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) FindPlayerByEMailRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* FindPlayerByEMailRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(PlayerInformation));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByEMailRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InPlayer, sizeof(PlayerInformation));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* FindPlayerByEMailRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )



			Result FindPlayerByEMailRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FindPlayerByEMailRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FindPlayerByEMail:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Player:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByEMailRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Query playerID list
			const MessageID FindPlayerByPlayerIDCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 18);
			Result FindPlayerByPlayerIDCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessage( MessageData* pIMsg )

			Result FindPlayerByPlayerIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FindPlayerByPlayerIDCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());


			Proc_End:

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* FindPlayerByPlayerIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlayerIDCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* FindPlayerByPlayerIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )



			Result FindPlayerByPlayerIDCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FindPlayerByPlayerIDCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FindPlayerByPlayerID:{0}:{1} , TransactionID:{2}, PlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlayerIDCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID FindPlayerByPlayerIDRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 18);
			Result FindPlayerByPlayerIDRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Player, pCur, iMsgSize, sizeof(PlayerInformation) ) );


			Proc_End:

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessage( MessageData* pIMsg )

			Result FindPlayerByPlayerIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FindPlayerByPlayerIDRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", parser.GetPlayer());


			Proc_End:

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* FindPlayerByPlayerIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(PlayerInformation));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlayerIDRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InPlayer, sizeof(PlayerInformation));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* FindPlayerByPlayerIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )



			Result FindPlayerByPlayerIDRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FindPlayerByPlayerIDRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FindPlayerByPlayerID:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Player:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlayerIDRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: *Request Player Status Update
			const MessageID RequestPlayerStatusUpdateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 19);
			Result RequestPlayerStatusUpdateCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofTargetPlayerID = 0; AccountID* pTargetPlayerID = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofTargetPlayerID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pTargetPlayerID, pCur, iMsgSize, sizeof(AccountID)*numberofTargetPlayerID ) );
				m_TargetPlayerID.SetLinkedBuffer(numberofTargetPlayerID, numberofTargetPlayerID, pTargetPlayerID);


			Proc_End:

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessage( MessageData* pIMsg )

			Result RequestPlayerStatusUpdateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RequestPlayerStatusUpdateCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayerID", parser.GetTargetPlayerID());


			Proc_End:

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RequestPlayerStatusUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)*InTargetPlayerID.size() + sizeof(uint16_t));


				uint16_t numberOfInTargetPlayerID = (uint16_t)InTargetPlayerID.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestPlayerStatusUpdateCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInTargetPlayerID, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InTargetPlayerID.data(), (INT)(sizeof(AccountID)*InTargetPlayerID.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RequestPlayerStatusUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )



			Result RequestPlayerStatusUpdateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RequestPlayerStatusUpdateCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RequestPlayerStatusUpdate:{0}:{1} , TransactionID:{2}, TargetPlayerID:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTargetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result RequestPlayerStatusUpdateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID RequestPlayerStatusUpdateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 19);
			Result RequestPlayerStatusUpdateRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessage( MessageData* pIMsg )

			Result RequestPlayerStatusUpdateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RequestPlayerStatusUpdateRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RequestPlayerStatusUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestPlayerStatusUpdateRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RequestPlayerStatusUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result RequestPlayerStatusUpdateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RequestPlayerStatusUpdateRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RequestPlayerStatusUpdate:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result RequestPlayerStatusUpdateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: *Notify Player Status Updated
			const MessageID NotifyPlayerStatusUpdatedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 20);
			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LatestActiveTime, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_IsInGame, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				NotifyPlayerStatusUpdatedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("LatestActiveTime", parser.GetLatestActiveTime());
				variableBuilder.SetVariable("IsInGame", parser.GetIsInGame());


			Proc_End:

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) NotifyPlayerStatusUpdatedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* NotifyPlayerStatusUpdatedS2CEvt::Create( IHeap& memHeap, const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(AccountID)
					+ sizeof(uint32_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::NotifyPlayerStatusUpdatedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InLatestActiveTime, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InIsInGame, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* NotifyPlayerStatusUpdatedS2CEvt::Create( IHeap& memHeap, const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )



			Result NotifyPlayerStatusUpdatedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				NotifyPlayerStatusUpdatedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "NotifyPlayerStatusUpdated:{0}:{1} , PlayerID:{2}, LatestActiveTime:{3}, IsInGame:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayerID(), parser.GetLatestActiveTime(), parser.GetIsInGame()); 
				return ResultCode::SUCCESS;
			}; // Result NotifyPlayerStatusUpdatedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Get Ranking lise
			const MessageID GetRankingListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 21);
			Result GetRankingListCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_RankingType, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_BaseRanking, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Count, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result GetRankingListCmd::ParseMessage( MessageData* pIMsg )

			Result GetRankingListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetRankingListCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingType", parser.GetRankingType());
				variableBuilder.SetVariable("BaseRanking", parser.GetBaseRanking());
				variableBuilder.SetVariable("Count", parser.GetCount());


			Proc_End:

				return hr;

			}; // Result GetRankingListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetRankingListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetRankingListCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InRankingType, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InBaseRanking, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InCount, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )



			Result GetRankingListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetRankingListCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetRankingList:{0}:{1} , TransactionID:{2}, RankingType:{3}, BaseRanking:{4}, Count:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetRankingType(), parser.GetBaseRanking(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetRankingListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 21);
			Result GetRankingListRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofRanking = 0; TotalRankingPlayerInformation* pRanking = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofRanking, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pRanking, pCur, iMsgSize, sizeof(TotalRankingPlayerInformation)*numberofRanking ) );
				m_Ranking.SetLinkedBuffer(numberofRanking, numberofRanking, pRanking);


			Proc_End:

				return hr;

			}; // Result GetRankingListRes::ParseMessage( MessageData* pIMsg )

			Result GetRankingListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetRankingListRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());


			Proc_End:

				return hr;

			}; // Result GetRankingListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetRankingListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetRankingListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(TotalRankingPlayerInformation)*InRanking.size() + sizeof(uint16_t));


				uint16_t numberOfInRanking = (uint16_t)InRanking.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetRankingListRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &numberOfInRanking, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InRanking.data(), (INT)(sizeof(TotalRankingPlayerInformation)*InRanking.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetRankingListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )



			Result GetRankingListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetRankingListRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetRankingList:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Ranking:{4,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetRanking()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Game user game play information
			const MessageID GetUserGamePlayerInfoCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 22);
			Result GetUserGamePlayerInfoCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessage( MessageData* pIMsg )

			Result GetUserGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetUserGamePlayerInfoCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetUserGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetUserGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GetUserGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetUserGamePlayerInfoCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetUserGamePlayerInfo:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetUserGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetUserGamePlayerInfoRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 22);
			Result GetUserGamePlayerInfoRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Level, pCur, iMsgSize, sizeof(int16_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Exp, pCur, iMsgSize, sizeof(int64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameMoney, pCur, iMsgSize, sizeof(int64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Gem, pCur, iMsgSize, sizeof(int64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Stamina, pCur, iMsgSize, sizeof(int16_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LastUpdateTime, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalPlayed, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlaySC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlaySM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlaySS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlaySC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlaySM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlaySS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlayNC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlayNM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlayNS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlayNC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlayNM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlayNS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WeeklyWin, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WeeklyLose, pCur, iMsgSize, sizeof(int32_t) ) );


			Proc_End:

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessage( MessageData* pIMsg )

			Result GetUserGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetUserGamePlayerInfoRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Level", parser.GetLevel());
				variableBuilder.SetVariable("Exp", parser.GetExp());
				variableBuilder.SetVariable("GameMoney", parser.GetGameMoney());
				variableBuilder.SetVariable("Gem", parser.GetGem());
				variableBuilder.SetVariable("Stamina", parser.GetStamina());
				variableBuilder.SetVariable("LastUpdateTime", parser.GetLastUpdateTime());
				variableBuilder.SetVariable("TotalPlayed", parser.GetTotalPlayed());
				variableBuilder.SetVariable("WinPlaySC", parser.GetWinPlaySC());
				variableBuilder.SetVariable("WinPlaySM", parser.GetWinPlaySM());
				variableBuilder.SetVariable("WinPlaySS", parser.GetWinPlaySS());
				variableBuilder.SetVariable("LosePlaySC", parser.GetLosePlaySC());
				variableBuilder.SetVariable("LosePlaySM", parser.GetLosePlaySM());
				variableBuilder.SetVariable("LosePlaySS", parser.GetLosePlaySS());
				variableBuilder.SetVariable("WinPlayNC", parser.GetWinPlayNC());
				variableBuilder.SetVariable("WinPlayNM", parser.GetWinPlayNM());
				variableBuilder.SetVariable("WinPlayNS", parser.GetWinPlayNS());
				variableBuilder.SetVariable("LosePlayNC", parser.GetLosePlayNC());
				variableBuilder.SetVariable("LosePlayNM", parser.GetLosePlayNM());
				variableBuilder.SetVariable("LosePlayNS", parser.GetLosePlayNS());
				variableBuilder.SetVariable("WeeklyWin", parser.GetWeeklyWin());
				variableBuilder.SetVariable("WeeklyLose", parser.GetWeeklyLose());


			Proc_End:

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetUserGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const int16_t &InLevel, const int64_t &InExp, const int64_t &InGameMoney, const int64_t &InGem, const int16_t &InStamina, const uint32_t &InLastUpdateTime, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(int16_t)
					+ sizeof(int64_t)
					+ sizeof(int64_t)
					+ sizeof(int64_t)
					+ sizeof(int16_t)
					+ sizeof(uint32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InLevel, sizeof(int16_t));
				Protocol::PackParamCopy( pMsgData, &InExp, sizeof(int64_t));
				Protocol::PackParamCopy( pMsgData, &InGameMoney, sizeof(int64_t));
				Protocol::PackParamCopy( pMsgData, &InGem, sizeof(int64_t));
				Protocol::PackParamCopy( pMsgData, &InStamina, sizeof(int16_t));
				Protocol::PackParamCopy( pMsgData, &InLastUpdateTime, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InTotalPlayed, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlaySC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlaySM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlaySS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlaySC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlaySM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlaySS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlayNC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlayNM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlayNS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlayNC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlayNM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlayNS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWeeklyWin, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWeeklyLose, sizeof(int32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetUserGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const int16_t &InLevel, const int64_t &InExp, const int64_t &InGameMoney, const int64_t &InGem, const int16_t &InStamina, const uint32_t &InLastUpdateTime, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )



			Result GetUserGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetUserGamePlayerInfoRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetUserGamePlayerInfo:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Level:{4}, Exp:{5}, GameMoney:{6}, Gem:{7}, Stamina:{8}, LastUpdateTime:{9}, TotalPlayed:{10}, WinPlaySC:{11}, WinPlaySM:{12}, WinPlaySS:{13}, LosePlaySC:{14}, LosePlaySM:{15}, LosePlaySS:{16}, WinPlayNC:{17}, WinPlayNM:{18}, WinPlayNS:{19}, LosePlayNC:{20}, LosePlayNM:{21}, LosePlayNS:{22}, WeeklyWin:{23}, WeeklyLose:{24}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetLevel(), parser.GetExp(), parser.GetGameMoney(), parser.GetGem(), parser.GetStamina(), parser.GetLastUpdateTime(), parser.GetTotalPlayed(), parser.GetWinPlaySC(), parser.GetWinPlaySM(), parser.GetWinPlaySS(), parser.GetLosePlaySC(), parser.GetLosePlaySM(), parser.GetLosePlaySS(), parser.GetWinPlayNC(), parser.GetWinPlayNM(), parser.GetWinPlayNS(), parser.GetLosePlayNC(), parser.GetLosePlayNM(), parser.GetLosePlayNS(), parser.GetWeeklyWin(), parser.GetWeeklyLose()); 
				return ResultCode::SUCCESS;
			}; // Result GetUserGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Game game play information
			const MessageID GetGamePlayerInfoCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 23);
			Result GetGamePlayerInfoCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessage( MessageData* pIMsg )

			Result GetGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetGamePlayerInfoCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());


			Proc_End:

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetGamePlayerInfoCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )



			Result GetGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetGamePlayerInfoCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetGamePlayerInfo:{0}:{1} , TransactionID:{2}, PlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result GetGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetGamePlayerInfoRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 23);
			Result GetGamePlayerInfoRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Level, pCur, iMsgSize, sizeof(int16_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalPlayed, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlaySC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlaySM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlaySS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlaySC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlaySM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlaySS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlayNC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlayNM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WinPlayNS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlayNC, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlayNM, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LosePlayNS, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WeeklyWin, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_WeeklyLose, pCur, iMsgSize, sizeof(int32_t) ) );


			Proc_End:

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessage( MessageData* pIMsg )

			Result GetGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetGamePlayerInfoRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Level", parser.GetLevel());
				variableBuilder.SetVariable("TotalPlayed", parser.GetTotalPlayed());
				variableBuilder.SetVariable("WinPlaySC", parser.GetWinPlaySC());
				variableBuilder.SetVariable("WinPlaySM", parser.GetWinPlaySM());
				variableBuilder.SetVariable("WinPlaySS", parser.GetWinPlaySS());
				variableBuilder.SetVariable("LosePlaySC", parser.GetLosePlaySC());
				variableBuilder.SetVariable("LosePlaySM", parser.GetLosePlaySM());
				variableBuilder.SetVariable("LosePlaySS", parser.GetLosePlaySS());
				variableBuilder.SetVariable("WinPlayNC", parser.GetWinPlayNC());
				variableBuilder.SetVariable("WinPlayNM", parser.GetWinPlayNM());
				variableBuilder.SetVariable("WinPlayNS", parser.GetWinPlayNS());
				variableBuilder.SetVariable("LosePlayNC", parser.GetLosePlayNC());
				variableBuilder.SetVariable("LosePlayNM", parser.GetLosePlayNM());
				variableBuilder.SetVariable("LosePlayNS", parser.GetLosePlayNS());
				variableBuilder.SetVariable("WeeklyWin", parser.GetWeeklyWin());
				variableBuilder.SetVariable("WeeklyLose", parser.GetWeeklyLose());


			Proc_End:

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetGamePlayerInfoRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const int16_t &InLevel, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(AccountID)
					+ sizeof(int16_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InLevel, sizeof(int16_t));
				Protocol::PackParamCopy( pMsgData, &InTotalPlayed, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlaySC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlaySM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlaySS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlaySC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlaySM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlaySS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlayNC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlayNM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWinPlayNS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlayNC, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlayNM, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InLosePlayNS, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWeeklyWin, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InWeeklyLose, sizeof(int32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const int16_t &InLevel, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )



			Result GetGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetGamePlayerInfoRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetGamePlayerInfo:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerID:{4}, Level:{5}, TotalPlayed:{6}, WinPlaySC:{7}, WinPlaySM:{8}, WinPlaySS:{9}, LosePlaySC:{10}, LosePlaySM:{11}, LosePlaySS:{12}, WinPlayNC:{13}, WinPlayNM:{14}, WinPlayNS:{15}, LosePlayNC:{16}, LosePlayNM:{17}, LosePlayNS:{18}, WeeklyWin:{19}, WeeklyLose:{20}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerID(), parser.GetLevel(), parser.GetTotalPlayed(), parser.GetWinPlaySC(), parser.GetWinPlaySM(), parser.GetWinPlaySS(), parser.GetLosePlaySC(), parser.GetLosePlaySM(), parser.GetLosePlaySS(), parser.GetWinPlayNC(), parser.GetWinPlayNM(), parser.GetWinPlayNS(), parser.GetLosePlayNC(), parser.GetLosePlayNM(), parser.GetLosePlayNS(), parser.GetWeeklyWin(), parser.GetWeeklyLose()); 
				return ResultCode::SUCCESS;
			}; // Result GetGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player level up event
			const MessageID LevelUpS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 24);
			Result LevelUpS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_CurrentTotalExp, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_CurrentLevel, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessage( MessageData* pIMsg )

			Result LevelUpS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LevelUpS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("CurrentTotalExp", parser.GetCurrentTotalExp());
				variableBuilder.SetVariable("CurrentLevel", parser.GetCurrentLevel());


			Proc_End:

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LevelUpS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LevelUpS2CEvt::Create( IHeap& memHeap, const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LevelUpS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InCurrentTotalExp, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InCurrentLevel, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LevelUpS2CEvt::Create( IHeap& memHeap, const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )



			Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LevelUpS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LevelUp:{0}:{1} , CurrentTotalExp:{2}, CurrentLevel:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetCurrentTotalExp(), parser.GetCurrentLevel()); 
				return ResultCode::SUCCESS;
			}; // Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Change NickName
			const MessageID SetNickNameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 25);
			Result SetNickNameCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfNickName = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfNickName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_NickName, pCur, iMsgSize, sizeof(char)*uiSizeOfNickName ) );
				protocolChk( Protocol::StreamParamCopy( &m_IsCostFree, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result SetNickNameCmd::ParseMessage( MessageData* pIMsg )

			Result SetNickNameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetNickNameCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("IsCostFree", parser.GetIsCostFree());


			Proc_End:

				return hr;

			}; // Result SetNickNameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetNickNameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetNickNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInNickNameLength = InNickName ? (uint16_t)(strlen(InNickName)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInNickNameLength 
					+ sizeof(uint64_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNickNameCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInNickNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InNickName ? InNickName : "", __uiInNickNameLength );
				Protocol::PackParamCopy( pMsgData, &InIsCostFree, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetNickNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )



			Result SetNickNameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetNickNameCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetNickName:{0}:{1} , TransactionID:{2}, NickName:{3,60}, IsCostFree:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetNickName(), parser.GetIsCostFree()); 
				return ResultCode::SUCCESS;
			}; // Result SetNickNameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID SetNickNameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 25);
			Result SetNickNameRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGem, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGameMoney, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result SetNickNameRes::ParseMessage( MessageData* pIMsg )

			Result SetNickNameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetNickNameRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());


			Proc_End:

				return hr;

			}; // Result SetNickNameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetNickNameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetNickNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNickNameRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InTotalGem, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGameMoney, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetNickNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )



			Result SetNickNameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetNickNameRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetNickName:{0}:{1} , TransactionID:{2}, Result:{3:X8}, TotalGem:{4}, TotalGameMoney:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result SetNickNameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Create Party
			const MessageID CreatePartyCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 26);
			Result CreatePartyCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result CreatePartyCmd::ParseMessage( MessageData* pIMsg )

			Result CreatePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreatePartyCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result CreatePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CreatePartyCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreatePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreatePartyCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* CreatePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result CreatePartyCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreatePartyCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateParty:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result CreatePartyCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CreatePartyRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 26);
			Result CreatePartyRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result CreatePartyRes::ParseMessage( MessageData* pIMsg )

			Result CreatePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreatePartyRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());


			Proc_End:

				return hr;

			}; // Result CreatePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CreatePartyRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreatePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreatePartyRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* CreatePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )



			Result CreatePartyRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreatePartyRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateParty:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PartyUID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPartyUID()); 
				return ResultCode::SUCCESS;
			}; // Result CreatePartyRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Join party
			const MessageID JoinPartyCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 27);
			Result JoinPartyCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_InviterID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result JoinPartyCmd::ParseMessage( MessageData* pIMsg )

			Result JoinPartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinPartyCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());


			Proc_End:

				return hr;

			}; // Result JoinPartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinPartyCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinPartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinPartyCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InInviterID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinPartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )



			Result JoinPartyCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinPartyCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinParty:{0}:{1} , TransactionID:{2}, PartyUID:{3}, InviterID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPartyUID(), parser.GetInviterID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPartyCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinPartyRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 27);
			Result JoinPartyRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofChatHistoryData = 0; uint8_t* pChatHistoryData = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyLeaderID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofChatHistoryData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pChatHistoryData, pCur, iMsgSize, sizeof(uint8_t)*numberofChatHistoryData ) );
				m_ChatHistoryData.SetLinkedBuffer(numberofChatHistoryData, numberofChatHistoryData, pChatHistoryData);


			Proc_End:

				return hr;

			}; // Result JoinPartyRes::ParseMessage( MessageData* pIMsg )

			Result JoinPartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinPartyRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());
				variableBuilder.SetVariable("ChatHistoryData", parser.GetChatHistoryData());


			Proc_End:

				return hr;

			}; // Result JoinPartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinPartyRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinPartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(uint8_t)*InChatHistoryData.size() + sizeof(uint16_t));


				uint16_t numberOfInChatHistoryData = (uint16_t)InChatHistoryData.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinPartyRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPartyLeaderID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &numberOfInChatHistoryData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InChatHistoryData.data(), (INT)(sizeof(uint8_t)*InChatHistoryData.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinPartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )



			Result JoinPartyRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinPartyRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinParty:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PartyUID:{4}, PartyLeaderID:{5}, ChatHistoryData:{6,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPartyUID(), parser.GetPartyLeaderID(), parser.GetChatHistoryData()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPartyRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Joined event
			const MessageID PartyPlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 28);
			Result PartyPlayerJoinedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayer, pCur, iMsgSize, sizeof(PlayerInformation) ) );


			Proc_End:

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PartyPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyPlayerJoinedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());


			Proc_End:

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyPlayerJoinedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(PlayerInformation));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerJoinedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayer, sizeof(PlayerInformation));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )



			Result PartyPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyPlayerJoinedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyPlayerJoined:{0}:{1} , PartyUID:{2}, JoinedPlayer:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPartyUID(), parser.GetJoinedPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result PartyPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Party leader changed event
			const MessageID PartyLeaderChangedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 29);
			Result PartyLeaderChangedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NewLeaderID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PartyLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyLeaderChangedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());


			Proc_End:

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyLeaderChangedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyLeaderChangedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InNewLeaderID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InNewLeaderID )



			Result PartyLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyLeaderChangedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyLeaderChanged:{0}:{1} , PartyUID:{2}, NewLeaderID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPartyUID(), parser.GetNewLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Leave party command
			const MessageID LeavePartyCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 30);
			Result LeavePartyCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result LeavePartyCmd::ParseMessage( MessageData* pIMsg )

			Result LeavePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LeavePartyCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());


			Proc_End:

				return hr;

			}; // Result LeavePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LeavePartyCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeavePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeavePartyCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LeavePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )



			Result LeavePartyCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeavePartyCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveParty:{0}:{1} , TransactionID:{2}, PartyUID:{3}, PlayerID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPartyUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result LeavePartyCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LeavePartyRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 30);
			Result LeavePartyRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result LeavePartyRes::ParseMessage( MessageData* pIMsg )

			Result LeavePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LeavePartyRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result LeavePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LeavePartyRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeavePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeavePartyRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LeavePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result LeavePartyRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeavePartyRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveParty:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result LeavePartyRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Party Player left event
			const MessageID PartyPlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 31);
			Result PartyPlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LeftPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PartyPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyPlayerLeftS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());


			Proc_End:

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyPlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerLeftS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InLeftPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )



			Result PartyPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyPlayerLeftS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyPlayerLeft:{0}:{1} , PartyUID:{2}, LeftPlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPartyUID(), parser.GetLeftPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Kick player from the party
			const MessageID PartyKickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 32);
			Result PartyKickPlayerCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerToKick, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessage( MessageData* pIMsg )

			Result PartyKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyKickPlayerCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());


			Proc_End:

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyKickPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyKickPlayerCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InPlayerToKick, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )



			Result PartyKickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyKickPlayerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyKickPlayer:{0}:{1} , TransactionID:{2}, PartyUID:{3}, PlayerID:{4}, PlayerToKick:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPartyUID(), parser.GetPlayerID(), parser.GetPlayerToKick()); 
				return ResultCode::SUCCESS;
			}; // Result PartyKickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID PartyKickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 32);
			Result PartyKickPlayerRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessage( MessageData* pIMsg )

			Result PartyKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyKickPlayerRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyKickPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyKickPlayerRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result PartyKickPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyKickPlayerRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyKickPlayer:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyKickPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Party Player kicked message
			const MessageID PartyPlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 33);
			Result PartyPlayerKickedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_KickedPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PartyPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyPlayerKickedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());


			Proc_End:

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyPlayerKickedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerKickedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InKickedPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )



			Result PartyPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyPlayerKickedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyPlayerKicked:{0}:{1} , PartyUID:{2}, KickedPlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPartyUID(), parser.GetKickedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Invite a player to the party
			const MessageID PartyInviteCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 34);
			Result PartyInviteCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_InviteTargetID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result PartyInviteCmd::ParseMessage( MessageData* pIMsg )

			Result PartyInviteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyInviteCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviteTargetID", parser.GetInviteTargetID());


			Proc_End:

				return hr;

			}; // Result PartyInviteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyInviteCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyInviteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InInviteTargetID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyInviteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviteTargetID )



			Result PartyInviteCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyInviteCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyInvite:{0}:{1} , TransactionID:{2}, InviteTargetID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetInviteTargetID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyInviteCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID PartyInviteRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 34);
			Result PartyInviteRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result PartyInviteRes::ParseMessage( MessageData* pIMsg )

			Result PartyInviteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyInviteRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result PartyInviteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyInviteRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyInviteRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyInviteRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result PartyInviteRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyInviteRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyInvite:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyInviteRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Party invite requested
			const MessageID PartyInviteRequestedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 35);
			Result PartyInviteRequestedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfInviterName = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_InviterID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfInviterName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_InviterName, pCur, iMsgSize, sizeof(char)*uiSizeOfInviterName ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyToJoinUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PartyInviteRequestedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyInviteRequestedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterName", parser.GetInviterName());
				variableBuilder.SetVariable("PartyToJoinUID", parser.GetPartyToJoinUID());


			Proc_End:

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyInviteRequestedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyInviteRequestedS2CEvt::Create( IHeap& memHeap, const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInInviterNameLength = InInviterName ? (uint16_t)(strlen(InInviterName)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInInviterNameLength 
					+ sizeof(AccountID)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteRequestedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InInviterID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &__uiInInviterNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InInviterName ? InInviterName : "", __uiInInviterNameLength );
				Protocol::PackParamCopy( pMsgData, &InPartyToJoinUID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyInviteRequestedS2CEvt::Create( IHeap& memHeap, const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )



			Result PartyInviteRequestedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyInviteRequestedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyInviteRequested:{0}:{1} , InviterID:{2}, InviterName:{3,60}, PartyToJoinUID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetInviterID(), parser.GetInviterName(), parser.GetPartyToJoinUID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyInviteRequestedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Send Party quick chat message
			const MessageID PartyQuickChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 36);
			Result PartyQuickChatMessageCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_QuickChatID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessage( MessageData* pIMsg )

			Result PartyQuickChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyQuickChatMessageCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());


			Proc_End:

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyQuickChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyQuickChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InQuickChatID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyQuickChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InQuickChatID )



			Result PartyQuickChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyQuickChatMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyQuickChatMessage:{0}:{1} , TransactionID:{2}, QuickChatID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetQuickChatID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyQuickChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID PartyQuickChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 36);
			Result PartyQuickChatMessageRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessage( MessageData* pIMsg )

			Result PartyQuickChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyQuickChatMessageRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyQuickChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyQuickChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyQuickChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result PartyQuickChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyQuickChatMessageRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyQuickChatMessage:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyQuickChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Party Chatting message event
			const MessageID PartyQuickChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 37);
			Result PartyQuickChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_SenderID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_QuickChatID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PartyQuickChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyQuickChatMessageS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());


			Proc_End:

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyQuickChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyQuickChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const uint32_t &InQuickChatID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(AccountID)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InSenderID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InQuickChatID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyQuickChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const uint32_t &InQuickChatID )



			Result PartyQuickChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyQuickChatMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyQuickChatMessage:{0}:{1} , SenderID:{2}, QuickChatID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetQuickChatID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyQuickChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Party chatting
			const MessageID PartyChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 38);
			Result PartyChatMessageCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfChatMessage = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfChatMessage, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ChatMessage, pCur, iMsgSize, sizeof(char)*uiSizeOfChatMessage ) );


			Proc_End:

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessage( MessageData* pIMsg )

			Result PartyChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyChatMessageCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());


			Proc_End:

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInChatMessageLength = InChatMessage ? (uint16_t)(strlen(InChatMessage)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInChatMessageLength 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInChatMessageLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InChatMessage ? InChatMessage : "", __uiInChatMessageLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage )



			Result PartyChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyChatMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyChatMessage:{0}:{1} , TransactionID:{2}, ChatMessage:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result PartyChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID PartyChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 38);
			Result PartyChatMessageRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result PartyChatMessageRes::ParseMessage( MessageData* pIMsg )

			Result PartyChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyChatMessageRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result PartyChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result PartyChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyChatMessageRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyChatMessage:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Party Chatting message event
			const MessageID PartyChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 39);
			Result PartyChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfSenderName = 0;
				uint16_t uiSizeOfChatMessage = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_SenderID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfSenderName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_SenderName, pCur, iMsgSize, sizeof(char)*uiSizeOfSenderName ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfChatMessage, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ChatMessage, pCur, iMsgSize, sizeof(char)*uiSizeOfChatMessage ) );


			Proc_End:

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PartyChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PartyChatMessageS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());


			Proc_End:

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PartyChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PartyChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInSenderNameLength = InSenderName ? (uint16_t)(strlen(InSenderName)+1) : 1;
				uint16_t __uiInChatMessageLength = InChatMessage ? (uint16_t)(strlen(InChatMessage)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInSenderNameLength + sizeof(uint16_t) + __uiInChatMessageLength 
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InSenderID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &__uiInSenderNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InSenderName ? InSenderName : "", __uiInSenderNameLength );
				Protocol::PackParamCopy( pMsgData, &__uiInChatMessageLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InChatMessage ? InChatMessage : "", __uiInChatMessageLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PartyChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )



			Result PartyChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyChatMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyChatMessage:{0}:{1} , SenderID:{2}, SenderName:{3,60}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetSenderName(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result PartyChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Join to a game
			const MessageID JoinGameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 40);
			Result JoinGameCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolChk( Protocol::StreamParamCopy( &m_InsUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result JoinGameCmd::ParseMessage( MessageData* pIMsg )

			Result JoinGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinGameCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());


			Proc_End:

				return hr;

			}; // Result JoinGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinGameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));
				Protocol::PackParamCopy( pMsgData, &InInsUID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )



			Result JoinGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGame:{0}:{1} , TransactionID:{2}, PlayerID:{3}, Ticket:{4}, InsUID:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayerID(), parser.GetTicket(), parser.GetInsUID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinGameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 40);
			Result JoinGameRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofChatHistoryData = 0; uint8_t* pChatHistoryData = nullptr;
				uint16_t numberofGameLogData = 0; uint8_t* pGameLogData = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_InsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TimeStamp, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameState, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Day, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_MaxPlayer, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerIndex, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerCharacter, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Role, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Dead, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofChatHistoryData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pChatHistoryData, pCur, iMsgSize, sizeof(uint8_t)*numberofChatHistoryData ) );
				m_ChatHistoryData.SetLinkedBuffer(numberofChatHistoryData, numberofChatHistoryData, pChatHistoryData);
				protocolChk( Protocol::StreamParamCopy( &numberofGameLogData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pGameLogData, pCur, iMsgSize, sizeof(uint8_t)*numberofGameLogData ) );
				m_GameLogData.SetLinkedBuffer(numberofGameLogData, numberofGameLogData, pGameLogData);


			Proc_End:

				return hr;

			}; // Result JoinGameRes::ParseMessage( MessageData* pIMsg )

			Result JoinGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinGameRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());
				variableBuilder.SetVariable("GameState", (int)parser.GetGameState());
				variableBuilder.SetVariable("Day", parser.GetDay());
				variableBuilder.SetVariable("MaxPlayer", parser.GetMaxPlayer());
				variableBuilder.SetVariable("PlayerIndex", parser.GetPlayerIndex());
				variableBuilder.SetVariable("PlayerCharacter", parser.GetPlayerCharacter());
				variableBuilder.SetVariable("Role", parser.GetRole());
				variableBuilder.SetVariable("Dead", parser.GetDead());
				variableBuilder.SetVariable("ChatHistoryData", parser.GetChatHistoryData());
				variableBuilder.SetVariable("GameLogData", parser.GetGameLogData());


			Proc_End:

				return hr;

			}; // Result JoinGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinGameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(uint32_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)*InChatHistoryData.size() + sizeof(uint16_t)
					+ sizeof(uint8_t)*InGameLogData.size() + sizeof(uint16_t));


				uint16_t numberOfInChatHistoryData = (uint16_t)InChatHistoryData.size(); 
				uint16_t numberOfInGameLogData = (uint16_t)InGameLogData.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTimeStamp, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InGameState, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InDay, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InMaxPlayer, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerIndex, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerCharacter, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InRole, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InDead, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInChatHistoryData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InChatHistoryData.data(), (INT)(sizeof(uint8_t)*InChatHistoryData.size())); 
				Protocol::PackParamCopy( pMsgData, &numberOfInGameLogData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InGameLogData.data(), (INT)(sizeof(uint8_t)*InGameLogData.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData )



			Result JoinGameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGame:{0}:{1} , TransactionID:{2}, Result:{3:X8}, InsUID:{4}, TimeStamp:{5}, GameState:{6}, Day:{7}, MaxPlayer:{8}, PlayerIndex:{9}, PlayerCharacter:{10}, Role:{11}, Dead:{12}, ChatHistoryData:{13,30}, GameLogData:{14,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetInsUID(), parser.GetTimeStamp(), (int)parser.GetGameState(), parser.GetDay(), parser.GetMaxPlayer(), parser.GetPlayerIndex(), parser.GetPlayerCharacter(), parser.GetRole(), parser.GetDead(), parser.GetChatHistoryData(), parser.GetGameLogData()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Joined in the game
			const MessageID PlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 41);
			Result PlayerJoinedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayer, pCur, iMsgSize, sizeof(PlayerInformation) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayerRole, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayerDead, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayerIndex, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayerCharacter, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result PlayerJoinedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerJoinedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());
				variableBuilder.SetVariable("JoinedPlayerRole", parser.GetJoinedPlayerRole());
				variableBuilder.SetVariable("JoinedPlayerDead", parser.GetJoinedPlayerDead());
				variableBuilder.SetVariable("JoinedPlayerIndex", parser.GetJoinedPlayerIndex());
				variableBuilder.SetVariable("JoinedPlayerCharacter", parser.GetJoinedPlayerCharacter());


			Proc_End:

				return hr;

			}; // Result PlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PlayerJoinedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer, const uint8_t &InJoinedPlayerRole, const uint8_t &InJoinedPlayerDead, const uint8_t &InJoinedPlayerIndex, const uint8_t &InJoinedPlayerCharacter )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(PlayerInformation)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerJoinedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayer, sizeof(PlayerInformation));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayerRole, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayerDead, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayerIndex, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayerCharacter, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer, const uint8_t &InJoinedPlayerRole, const uint8_t &InJoinedPlayerDead, const uint8_t &InJoinedPlayerIndex, const uint8_t &InJoinedPlayerCharacter )



			Result PlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerJoinedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerJoined:{0}:{1} , GameInsUID:{2}, JoinedPlayer:{3}, JoinedPlayerRole:{4}, JoinedPlayerDead:{5}, JoinedPlayerIndex:{6}, JoinedPlayerCharacter:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetJoinedPlayer(), parser.GetJoinedPlayerRole(), parser.GetJoinedPlayerDead(), parser.GetJoinedPlayerIndex(), parser.GetJoinedPlayerCharacter()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Leave Game
			const MessageID LeaveGameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 42);
			Result LeaveGameCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );


			Proc_End:

				return hr;

			}; // Result LeaveGameCmd::ParseMessage( MessageData* pIMsg )

			Result LeaveGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LeaveGameCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());


			Proc_End:

				return hr;

			}; // Result LeaveGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LeaveGameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LeaveGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeaveGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LeaveGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result LeaveGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveGameCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveGame:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LeaveGameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 42);
			Result LeaveGameRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result LeaveGameRes::ParseMessage( MessageData* pIMsg )

			Result LeaveGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LeaveGameRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result LeaveGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LeaveGameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LeaveGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeaveGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LeaveGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result LeaveGameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveGameRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveGame:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveGameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player left event
			const MessageID PlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 43);
			Result PlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LeftPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerLeftS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());


			Proc_End:

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerLeftS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InLeftPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID )



			Result PlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerLeftS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerLeft:{0}:{1} , GameInsUID:{2}, LeftPlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetLeftPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Kick player
			const MessageID KickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 44);
			Result KickPlayerCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerToKick, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result KickPlayerCmd::ParseMessage( MessageData* pIMsg )

			Result KickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				KickPlayerCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());


			Proc_End:

				return hr;

			}; // Result KickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result KickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) KickPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result KickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* KickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::KickPlayerCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InPlayerToKick, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* KickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )



			Result KickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				KickPlayerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "KickPlayer:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, PlayerToKick:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetPlayerToKick()); 
				return ResultCode::SUCCESS;
			}; // Result KickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID KickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 44);
			Result KickPlayerRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result KickPlayerRes::ParseMessage( MessageData* pIMsg )

			Result KickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				KickPlayerRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result KickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result KickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) KickPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result KickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* KickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::KickPlayerRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* KickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result KickPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				KickPlayerRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "KickPlayer:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result KickPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player kicked
			const MessageID PlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 45);
			Result PlayerKickedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_KickedPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerKickedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());


			Proc_End:

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PlayerKickedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerKickedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InKickedPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID )



			Result PlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerKickedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerKicked:{0}:{1} , GameInsUID:{2}, KickedPlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetKickedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Assign role + Game state reset
			const MessageID AssignRoleCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 46);
			Result AssignRoleCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );


			Proc_End:

				return hr;

			}; // Result AssignRoleCmd::ParseMessage( MessageData* pIMsg )

			Result AssignRoleCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AssignRoleCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());


			Proc_End:

				return hr;

			}; // Result AssignRoleCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AssignRoleCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AssignRoleCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AssignRoleCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AssignRoleCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AssignRoleCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AssignRoleCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result AssignRoleCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AssignRoleCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AssignRole:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result AssignRoleCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID AssignRoleRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 46);
			Result AssignRoleRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result AssignRoleRes::ParseMessage( MessageData* pIMsg )

			Result AssignRoleRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AssignRoleRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result AssignRoleRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AssignRoleRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AssignRoleRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AssignRoleRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AssignRoleRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AssignRoleRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AssignRoleRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result AssignRoleRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AssignRoleRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AssignRole:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result AssignRoleRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Role assigned event
			const MessageID RoleAssignedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 47);
			Result RoleAssignedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Role, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result RoleAssignedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result RoleAssignedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RoleAssignedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Role", parser.GetRole());


			Proc_End:

				return hr;

			}; // Result RoleAssignedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RoleAssignedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RoleAssignedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RoleAssignedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RoleAssignedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RoleAssignedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InRole, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RoleAssignedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole )



			Result RoleAssignedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RoleAssignedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RoleAssigned:{0}:{1} , GameInsUID:{2}, PlayerID:{3}, Role:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetRole()); 
				return ResultCode::SUCCESS;
			}; // Result RoleAssignedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Send chatting message to the game
			const MessageID ChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 48);
			Result ChatMessageCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfChatMessage = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfChatMessage, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ChatMessage, pCur, iMsgSize, sizeof(char)*uiSizeOfChatMessage ) );
				protocolChk( Protocol::StreamParamCopy( &m_Role, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result ChatMessageCmd::ParseMessage( MessageData* pIMsg )

			Result ChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatMessageCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());
				variableBuilder.SetVariable("Role", parser.GetRole());


			Proc_End:

				return hr;

			}; // Result ChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage, const uint8_t &InRole )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInChatMessageLength = InChatMessage ? (uint16_t)(strlen(InChatMessage)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInChatMessageLength 
					+ sizeof(uint64_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatMessageCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInChatMessageLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InChatMessage ? InChatMessage : "", __uiInChatMessageLength );
				Protocol::PackParamCopy( pMsgData, &InRole, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage, const uint8_t &InRole )



			Result ChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatMessage:{0}:{1} , TransactionID:{2}, ChatMessage:{3,60}, Role:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatMessage(), parser.GetRole()); 
				return ResultCode::SUCCESS;
			}; // Result ChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 48);
			Result ChatMessageRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result ChatMessageRes::ParseMessage( MessageData* pIMsg )

			Result ChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatMessageRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result ChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatMessageRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result ChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatMessageRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatMessage:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result ChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Chatting message event 
			const MessageID ChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 49);
			Result ChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfSenderName = 0;
				uint16_t uiSizeOfChatMessage = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_SenderID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Role, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfSenderName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_SenderName, pCur, iMsgSize, sizeof(char)*uiSizeOfSenderName ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfChatMessage, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ChatMessage, pCur, iMsgSize, sizeof(char)*uiSizeOfChatMessage ) );


			Proc_End:

				return hr;

			}; // Result ChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )

			Result ChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatMessageS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("Role", parser.GetRole());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());


			Proc_End:

				return hr;

			}; // Result ChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInSenderNameLength = InSenderName ? (uint16_t)(strlen(InSenderName)+1) : 1;
				uint16_t __uiInChatMessageLength = InChatMessage ? (uint16_t)(strlen(InChatMessage)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInSenderNameLength + sizeof(uint16_t) + __uiInChatMessageLength 
					+ sizeof(AccountID)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatMessageS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InSenderID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InRole, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &__uiInSenderNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InSenderName ? InSenderName : "", __uiInSenderNameLength );
				Protocol::PackParamCopy( pMsgData, &__uiInChatMessageLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InChatMessage ? InChatMessage : "", __uiInChatMessageLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage )



			Result ChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatMessage:{0}:{1} , SenderID:{2}, Role:{3}, SenderName:{4,60}, ChatMessage:{5,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetRole(), parser.GetSenderName(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Advance game
			const MessageID AdvanceGameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 50);
			Result AdvanceGameCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );


			Proc_End:

				return hr;

			}; // Result AdvanceGameCmd::ParseMessage( MessageData* pIMsg )

			Result AdvanceGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AdvanceGameCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());


			Proc_End:

				return hr;

			}; // Result AdvanceGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AdvanceGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AdvanceGameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AdvanceGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AdvanceGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AdvanceGameCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AdvanceGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result AdvanceGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AdvanceGameCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AdvanceGame:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result AdvanceGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID AdvanceGameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 50);
			Result AdvanceGameRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result AdvanceGameRes::ParseMessage( MessageData* pIMsg )

			Result AdvanceGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AdvanceGameRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result AdvanceGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AdvanceGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) AdvanceGameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result AdvanceGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* AdvanceGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AdvanceGameRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* AdvanceGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result AdvanceGameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AdvanceGameRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AdvanceGame:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result AdvanceGameRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: The game state is advanced
			const MessageID GameAdvancedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 51);
			Result GameAdvancedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TimeStamp, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameState, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Day, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result GameAdvancedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GameAdvancedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameAdvancedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());
				variableBuilder.SetVariable("GameState", (int)parser.GetGameState());
				variableBuilder.SetVariable("Day", parser.GetDay());


			Proc_End:

				return hr;

			}; // Result GameAdvancedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameAdvancedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameAdvancedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameAdvancedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameAdvancedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameAdvancedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTimeStamp, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InGameState, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InDay, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameAdvancedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay )



			Result GameAdvancedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameAdvancedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameAdvanced:{0}:{1} , GameInsUID:{2}, TimeStamp:{3}, GameState:{4}, Day:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetTimeStamp(), (int)parser.GetGameState(), parser.GetDay()); 
				return ResultCode::SUCCESS;
			}; // Result GameAdvancedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Game is ended
			const MessageID GameEndedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 52);
			Result GameEndedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Winner, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GainedExp, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GainedGameMoney, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result GameEndedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GameEndedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameEndedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Winner", (int)parser.GetWinner());
				variableBuilder.SetVariable("GainedExp", parser.GetGainedExp());
				variableBuilder.SetVariable("GainedGameMoney", parser.GetGainedGameMoney());


			Proc_End:

				return hr;

			}; // Result GameEndedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameEndedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameEndedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameEndedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameEndedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint8_t)
					+ sizeof(uint32_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameEndedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InWinner, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InGainedExp, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InGainedGameMoney, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameEndedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney )



			Result GameEndedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameEndedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameEnded:{0}:{1} , GameInsUID:{2}, Winner:{3}, GainedExp:{4}, GainedGameMoney:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), (int)parser.GetWinner(), parser.GetGainedExp(), parser.GetGainedGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result GameEndedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Vote game advance
			const MessageID VoteGameAdvanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 53);
			Result VoteGameAdvanceCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );


			Proc_End:

				return hr;

			}; // Result VoteGameAdvanceCmd::ParseMessage( MessageData* pIMsg )

			Result VoteGameAdvanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				VoteGameAdvanceCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());


			Proc_End:

				return hr;

			}; // Result VoteGameAdvanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteGameAdvanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) VoteGameAdvanceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result VoteGameAdvanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* VoteGameAdvanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteGameAdvanceCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* VoteGameAdvanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result VoteGameAdvanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VoteGameAdvanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "VoteGameAdvance:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result VoteGameAdvanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID VoteGameAdvanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 53);
			Result VoteGameAdvanceRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result VoteGameAdvanceRes::ParseMessage( MessageData* pIMsg )

			Result VoteGameAdvanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				VoteGameAdvanceRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result VoteGameAdvanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteGameAdvanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) VoteGameAdvanceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result VoteGameAdvanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* VoteGameAdvanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteGameAdvanceRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* VoteGameAdvanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result VoteGameAdvanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VoteGameAdvanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "VoteGameAdvance:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result VoteGameAdvanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: GameAdvance is Voted
			const MessageID GameAdvanceVotedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 54);
			Result GameAdvanceVotedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Voter, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result GameAdvanceVotedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GameAdvanceVotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameAdvanceVotedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Voter", parser.GetVoter());


			Proc_End:

				return hr;

			}; // Result GameAdvanceVotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameAdvanceVotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameAdvanceVotedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameAdvanceVotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameAdvanceVotedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InVoter )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameAdvanceVotedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InVoter, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameAdvanceVotedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InVoter )



			Result GameAdvanceVotedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameAdvanceVotedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameAdvanceVoted:{0}:{1} , GameInsUID:{2}, Voter:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetVoter()); 
				return ResultCode::SUCCESS;
			}; // Result GameAdvanceVotedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Vote
			const MessageID VoteCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 55);
			Result VoteCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolChk( Protocol::StreamParamCopy( &m_VoteTarget, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ActionSerial, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result VoteCmd::ParseMessage( MessageData* pIMsg )

			Result VoteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				VoteCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("VoteTarget", parser.GetVoteTarget());
				variableBuilder.SetVariable("ActionSerial", parser.GetActionSerial());


			Proc_End:

				return hr;

			}; // Result VoteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) VoteCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result VoteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* VoteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(AccountID)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));
				Protocol::PackParamCopy( pMsgData, &InVoteTarget, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InActionSerial, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* VoteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )



			Result VoteCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VoteCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Vote:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}, VoteTarget:{6}, ActionSerial:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket(), parser.GetVoteTarget(), parser.GetActionSerial()); 
				return ResultCode::SUCCESS;
			}; // Result VoteCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID VoteRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 55);
			Result VoteRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result VoteRes::ParseMessage( MessageData* pIMsg )

			Result VoteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				VoteRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result VoteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) VoteRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result VoteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* VoteRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* VoteRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result VoteRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VoteRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Vote:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result VoteRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Voted
			const MessageID VotedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 56);
			Result VotedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Voter, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_VotedTarget, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result VotedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result VotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				VotedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Voter", parser.GetVoter());
				variableBuilder.SetVariable("VotedTarget", parser.GetVotedTarget());


			Proc_End:

				return hr;

			}; // Result VotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) VotedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result VotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* VotedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VotedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InVoter, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InVotedTarget, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* VotedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget )



			Result VotedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VotedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Voted:{0}:{1} , GameInsUID:{2}, Voter:{3}, VotedTarget:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetVoter(), parser.GetVotedTarget()); 
				return ResultCode::SUCCESS;
			}; // Result VotedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Vote is ended
			const MessageID VoteEndS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 57);
			Result VoteEndS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofVoted = 0; AccountID* pVoted = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofVoted, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pVoted, pCur, iMsgSize, sizeof(AccountID)*numberofVoted ) );
				m_Voted.SetLinkedBuffer(numberofVoted, numberofVoted, pVoted);


			Proc_End:

				return hr;

			}; // Result VoteEndS2CEvt::ParseMessage( MessageData* pIMsg )

			Result VoteEndS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				VoteEndS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Voted", parser.GetVoted());


			Proc_End:

				return hr;

			}; // Result VoteEndS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteEndS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) VoteEndS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result VoteEndS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* VoteEndS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const Array<AccountID>& InVoted )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)*InVoted.size() + sizeof(uint16_t));


				uint16_t numberOfInVoted = (uint16_t)InVoted.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteEndS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInVoted, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InVoted.data(), (INT)(sizeof(AccountID)*InVoted.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* VoteEndS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const Array<AccountID>& InVoted )



			Result VoteEndS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VoteEndS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "VoteEnd:{0}:{1} , GameInsUID:{2}, Voted:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetVoted()); 
				return ResultCode::SUCCESS;
			}; // Result VoteEndS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Killed
			const MessageID PlayerKilledS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 58);
			Result PlayerKilledS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_KilledPlayer, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Reason, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result PlayerKilledS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerKilledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerKilledS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("KilledPlayer", parser.GetKilledPlayer());
				variableBuilder.SetVariable("Reason", (int)parser.GetReason());


			Proc_End:

				return hr;

			}; // Result PlayerKilledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerKilledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PlayerKilledS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PlayerKilledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerKilledS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerKilledS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InKilledPlayer, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InReason, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PlayerKilledS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason )



			Result PlayerKilledS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerKilledS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerKilled:{0}:{1} , GameInsUID:{2}, KilledPlayer:{3}, Reason:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetKilledPlayer(), (int)parser.GetReason()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerKilledS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Voted
			const MessageID PlayerRevealedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 59);
			Result PlayerRevealedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameInsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_RevealedPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Role, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Reason, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result PlayerRevealedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerRevealedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerRevealedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("RevealedPlayerID", parser.GetRevealedPlayerID());
				variableBuilder.SetVariable("Role", parser.GetRole());
				variableBuilder.SetVariable("Reason", (int)parser.GetReason());


			Proc_End:

				return hr;

			}; // Result PlayerRevealedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerRevealedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PlayerRevealedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PlayerRevealedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerRevealedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerRevealedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InRevealedPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InRole, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InReason, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PlayerRevealedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason )



			Result PlayerRevealedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerRevealedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerRevealed:{0}:{1} , GameInsUID:{2}, RevealedPlayerID:{3}, Role:{4}, Reason:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetRevealedPlayerID(), parser.GetRole(), (int)parser.GetReason()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerRevealedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Play again with the current players
			const MessageID GamePlayAgainCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 60);
			Result GamePlayAgainCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayAgainCmd::ParseMessage( MessageData* pIMsg )

			Result GamePlayAgainCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayAgainCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result GamePlayAgainCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayAgainCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayAgainCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayAgainCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayAgainCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayAgainCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayAgainCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GamePlayAgainCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayAgainCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayAgain:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayAgainCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GamePlayAgainRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 60);
			Result GamePlayAgainRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGem, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGameMoney, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayAgainRes::ParseMessage( MessageData* pIMsg )

			Result GamePlayAgainRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayAgainRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());


			Proc_End:

				return hr;

			}; // Result GamePlayAgainRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayAgainRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayAgainRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayAgainRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayAgainRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayAgainRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InTotalGem, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGameMoney, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayAgainRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )



			Result GamePlayAgainRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayAgainRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayAgain:{0}:{1} , TransactionID:{2}, Result:{3:X8}, TotalGem:{4}, TotalGameMoney:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayAgainRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
			const MessageID GamePlayAgainS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 61);
			Result GamePlayAgainS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LeadPlayer, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayAgainS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GamePlayAgainS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayAgainS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("LeadPlayer", parser.GetLeadPlayer());


			Proc_End:

				return hr;

			}; // Result GamePlayAgainS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayAgainS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayAgainS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayAgainS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayAgainS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InLeadPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayAgainS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InLeadPlayer, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayAgainS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InLeadPlayer )



			Result GamePlayAgainS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayAgainS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayAgain:{0}:{1} , PartyUID:{2}, LeadPlayer:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPartyUID(), parser.GetLeadPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayAgainS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Player. reveal a player
			const MessageID GameRevealPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 62);
			Result GameRevealPlayerCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofTargetPlayerID = 0; AccountID* pTargetPlayerID = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofTargetPlayerID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pTargetPlayerID, pCur, iMsgSize, sizeof(AccountID)*numberofTargetPlayerID ) );
				m_TargetPlayerID.SetLinkedBuffer(numberofTargetPlayerID, numberofTargetPlayerID, pTargetPlayerID);


			Proc_End:

				return hr;

			}; // Result GameRevealPlayerCmd::ParseMessage( MessageData* pIMsg )

			Result GameRevealPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameRevealPlayerCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayerID", parser.GetTargetPlayerID());


			Proc_End:

				return hr;

			}; // Result GameRevealPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameRevealPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameRevealPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameRevealPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameRevealPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID)*InTargetPlayerID.size() + sizeof(uint16_t));


				uint16_t numberOfInTargetPlayerID = (uint16_t)InTargetPlayerID.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameRevealPlayerCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInTargetPlayerID, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InTargetPlayerID.data(), (INT)(sizeof(AccountID)*InTargetPlayerID.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameRevealPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )



			Result GameRevealPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameRevealPlayerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameRevealPlayer:{0}:{1} , TransactionID:{2}, TargetPlayerID:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTargetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result GameRevealPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GameRevealPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 62);
			Result GameRevealPlayerRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofRevealedPlayerID = 0; AccountID* pRevealedPlayerID = nullptr;
				uint16_t numberofRevealedRole = 0; uint8_t* pRevealedRole = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofRevealedPlayerID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pRevealedPlayerID, pCur, iMsgSize, sizeof(AccountID)*numberofRevealedPlayerID ) );
				m_RevealedPlayerID.SetLinkedBuffer(numberofRevealedPlayerID, numberofRevealedPlayerID, pRevealedPlayerID);
				protocolChk( Protocol::StreamParamCopy( &numberofRevealedRole, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pRevealedRole, pCur, iMsgSize, sizeof(uint8_t)*numberofRevealedRole ) );
				m_RevealedRole.SetLinkedBuffer(numberofRevealedRole, numberofRevealedRole, pRevealedRole);
				protocolChk( Protocol::StreamParamCopy( &m_TotalGem, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGameMoney, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GameRevealPlayerRes::ParseMessage( MessageData* pIMsg )

			Result GameRevealPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameRevealPlayerRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("RevealedPlayerID", parser.GetRevealedPlayerID());
				variableBuilder.SetVariable("RevealedRole", parser.GetRevealedRole());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());


			Proc_End:

				return hr;

			}; // Result GameRevealPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameRevealPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameRevealPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameRevealPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameRevealPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<AccountID>& InRevealedPlayerID, const Array<uint8_t>& InRevealedRole, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(AccountID)*InRevealedPlayerID.size() + sizeof(uint16_t)
					+ sizeof(uint8_t)*InRevealedRole.size() + sizeof(uint16_t)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				uint16_t numberOfInRevealedPlayerID = (uint16_t)InRevealedPlayerID.size(); 
				uint16_t numberOfInRevealedRole = (uint16_t)InRevealedRole.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameRevealPlayerRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &numberOfInRevealedPlayerID, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InRevealedPlayerID.data(), (INT)(sizeof(AccountID)*InRevealedPlayerID.size())); 
				Protocol::PackParamCopy( pMsgData, &numberOfInRevealedRole, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InRevealedRole.data(), (INT)(sizeof(uint8_t)*InRevealedRole.size())); 
				Protocol::PackParamCopy( pMsgData, &InTotalGem, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGameMoney, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameRevealPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<AccountID>& InRevealedPlayerID, const Array<uint8_t>& InRevealedRole, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )



			Result GameRevealPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameRevealPlayerRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameRevealPlayer:{0}:{1} , TransactionID:{2}, Result:{3:X8}, RevealedPlayerID:{4,30}, RevealedRole:{5,30}, TotalGem:{6}, TotalGameMoney:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetRevealedPlayerID(), parser.GetRevealedRole(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result GameRevealPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Player. revive himself
			const MessageID GamePlayerReviveCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 63);
			Result GamePlayerReviveCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayerReviveCmd::ParseMessage( MessageData* pIMsg )

			Result GamePlayerReviveCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayerReviveCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result GamePlayerReviveCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerReviveCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayerReviveCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayerReviveCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayerReviveCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerReviveCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayerReviveCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GamePlayerReviveCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayerReviveCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayerRevive:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayerReviveCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GamePlayerReviveRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 63);
			Result GamePlayerReviveRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGem, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGameMoney, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayerReviveRes::ParseMessage( MessageData* pIMsg )

			Result GamePlayerReviveRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayerReviveRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());


			Proc_End:

				return hr;

			}; // Result GamePlayerReviveRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerReviveRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayerReviveRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayerReviveRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayerReviveRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerReviveRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InTotalGem, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGameMoney, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayerReviveRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )



			Result GamePlayerReviveRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayerReviveRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayerRevive:{0}:{1} , TransactionID:{2}, Result:{3:X8}, TotalGem:{4}, TotalGameMoney:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayerReviveRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player is revived
			const MessageID GamePlayerRevivedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 64);
			Result GamePlayerRevivedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RevivedPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayerRevivedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GamePlayerRevivedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayerRevivedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RevivedPlayerID", parser.GetRevivedPlayerID());


			Proc_End:

				return hr;

			}; // Result GamePlayerRevivedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerRevivedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayerRevivedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayerRevivedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayerRevivedS2CEvt::Create( IHeap& memHeap, const AccountID &InRevivedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerRevivedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRevivedPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayerRevivedS2CEvt::Create( IHeap& memHeap, const AccountID &InRevivedPlayerID )



			Result GamePlayerRevivedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayerRevivedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayerRevived:{0}:{1} , RevivedPlayerID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRevivedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayerRevivedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Player. reset ranking
			const MessageID GamePlayerResetRankCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 65);
			Result GamePlayerResetRankCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayerResetRankCmd::ParseMessage( MessageData* pIMsg )

			Result GamePlayerResetRankCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayerResetRankCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result GamePlayerResetRankCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerResetRankCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayerResetRankCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayerResetRankCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayerResetRankCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerResetRankCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayerResetRankCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GamePlayerResetRankCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayerResetRankCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayerResetRank:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayerResetRankCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GamePlayerResetRankRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 65);
			Result GamePlayerResetRankRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGem, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGameMoney, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GamePlayerResetRankRes::ParseMessage( MessageData* pIMsg )

			Result GamePlayerResetRankRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GamePlayerResetRankRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());


			Proc_End:

				return hr;

			}; // Result GamePlayerResetRankRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerResetRankRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GamePlayerResetRankRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GamePlayerResetRankRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GamePlayerResetRankRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerResetRankRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InTotalGem, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGameMoney, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GamePlayerResetRankRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )



			Result GamePlayerResetRankRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayerResetRankRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayerResetRank:{0}:{1} , TransactionID:{2}, Result:{3:X8}, TotalGem:{4}, TotalGameMoney:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayerResetRankRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Request Game match
			const MessageID RequestGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 66);
			Result RequestGameMatchCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NumPlayer, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_RequestRole, pCur, iMsgSize, sizeof(uint8_t) ) );


			Proc_End:

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessage( MessageData* pIMsg )

			Result RequestGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RequestGameMatchCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NumPlayer", parser.GetNumPlayer());
				variableBuilder.SetVariable("RequestRole", parser.GetRequestRole());


			Proc_End:

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RequestGameMatchCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RequestGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestGameMatchCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InNumPlayer, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InRequestRole, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RequestGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )



			Result RequestGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RequestGameMatchCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RequestGameMatch:{0}:{1} , TransactionID:{2}, NumPlayer:{3}, RequestRole:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetNumPlayer(), parser.GetRequestRole()); 
				return ResultCode::SUCCESS;
			}; // Result RequestGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID RequestGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 66);
			Result RequestGameMatchRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGem, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGameMoney, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result RequestGameMatchRes::ParseMessage( MessageData* pIMsg )

			Result RequestGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RequestGameMatchRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());


			Proc_End:

				return hr;

			}; // Result RequestGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RequestGameMatchRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RequestGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestGameMatchRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InTotalGem, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGameMoney, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RequestGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )



			Result RequestGameMatchRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RequestGameMatchRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RequestGameMatch:{0}:{1} , TransactionID:{2}, Result:{3:X8}, TotalGem:{4}, TotalGameMoney:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result RequestGameMatchRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Game matched
			const MessageID GameMatchedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 67);
			Result GameMatchedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofChatHistoryData = 0; uint8_t* pChatHistoryData = nullptr;
				uint16_t numberofGameLogData = 0; uint8_t* pGameLogData = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_InsUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TimeStamp, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameState, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Day, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_MaxPlayer, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerIndex, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerCharacter, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Role, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Dead, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofChatHistoryData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pChatHistoryData, pCur, iMsgSize, sizeof(uint8_t)*numberofChatHistoryData ) );
				m_ChatHistoryData.SetLinkedBuffer(numberofChatHistoryData, numberofChatHistoryData, pChatHistoryData);
				protocolChk( Protocol::StreamParamCopy( &numberofGameLogData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pGameLogData, pCur, iMsgSize, sizeof(uint8_t)*numberofGameLogData ) );
				m_GameLogData.SetLinkedBuffer(numberofGameLogData, numberofGameLogData, pGameLogData);
				protocolChk( Protocol::StreamParamCopy( &m_Stamina, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGem, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TotalGameMoney, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GameMatchedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameMatchedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("InsUID", parser.GetInsUID());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());
				variableBuilder.SetVariable("GameState", (int)parser.GetGameState());
				variableBuilder.SetVariable("Day", parser.GetDay());
				variableBuilder.SetVariable("MaxPlayer", parser.GetMaxPlayer());
				variableBuilder.SetVariable("PlayerIndex", parser.GetPlayerIndex());
				variableBuilder.SetVariable("PlayerCharacter", parser.GetPlayerCharacter());
				variableBuilder.SetVariable("Role", parser.GetRole());
				variableBuilder.SetVariable("Dead", parser.GetDead());
				variableBuilder.SetVariable("ChatHistoryData", parser.GetChatHistoryData());
				variableBuilder.SetVariable("GameLogData", parser.GetGameLogData());
				variableBuilder.SetVariable("Stamina", parser.GetStamina());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());


			Proc_End:

				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameMatchedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameMatchedS2CEvt::Create( IHeap& memHeap, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t)*InChatHistoryData.size() + sizeof(uint16_t)
					+ sizeof(uint8_t)*InGameLogData.size() + sizeof(uint16_t)
					+ sizeof(uint32_t)
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				uint16_t numberOfInChatHistoryData = (uint16_t)InChatHistoryData.size(); 
				uint16_t numberOfInGameLogData = (uint16_t)InGameLogData.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InInsUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTimeStamp, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InGameState, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InDay, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InMaxPlayer, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerIndex, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerCharacter, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InRole, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InDead, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInChatHistoryData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InChatHistoryData.data(), (INT)(sizeof(uint8_t)*InChatHistoryData.size())); 
				Protocol::PackParamCopy( pMsgData, &numberOfInGameLogData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InGameLogData.data(), (INT)(sizeof(uint8_t)*InGameLogData.size())); 
				Protocol::PackParamCopy( pMsgData, &InStamina, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGem, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTotalGameMoney, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameMatchedS2CEvt::Create( IHeap& memHeap, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )



			Result GameMatchedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameMatchedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameMatched:{0}:{1} , InsUID:{2}, TimeStamp:{3}, GameState:{4}, Day:{5}, MaxPlayer:{6}, PlayerIndex:{7}, PlayerCharacter:{8}, Role:{9}, Dead:{10}, ChatHistoryData:{11,30}, GameLogData:{12,30}, Stamina:{13}, TotalGem:{14}, TotalGameMoney:{15}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetInsUID(), parser.GetTimeStamp(), (int)parser.GetGameState(), parser.GetDay(), parser.GetMaxPlayer(), parser.GetPlayerIndex(), parser.GetPlayerCharacter(), parser.GetRole(), parser.GetDead(), parser.GetChatHistoryData(), parser.GetGameLogData(), parser.GetStamina(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Game match failed
			const MessageID GameMatchFailedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 68);
			Result GameMatchFailedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_FailedReason, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GameMatchFailedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameMatchFailedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("FailedReason", parser.GetFailedReason());


			Proc_End:

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameMatchFailedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameMatchFailedS2CEvt::Create( IHeap& memHeap, const Result &InFailedReason )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchFailedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InFailedReason, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameMatchFailedS2CEvt::Create( IHeap& memHeap, const Result &InFailedReason )



			Result GameMatchFailedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameMatchFailedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameMatchFailed:{0}:{1} , FailedReason:{2:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetFailedReason()); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchFailedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Game matching started
			const MessageID GameMatchingStartedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 69);
			Result GameMatchingStartedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;


				protocolChkPtr(pIMsg);




			Proc_End:

				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GameMatchingStartedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameMatchingStartedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));



			Proc_End:

				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameMatchingStartedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameMatchingStartedS2CEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) );


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchingStartedS2CEvt::MID, __uiMessageSize ) );



			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameMatchingStartedS2CEvt::Create( IHeap& memHeap )



			Result GameMatchingStartedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameMatchingStartedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameMatchingStarted:{0}:{1} ",
						prefix, pMsg->GetMessageHeader()->Length); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchingStartedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Cancel Game match
			const MessageID CancelGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 70);
			Result CancelGameMatchCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessage( MessageData* pIMsg )

			Result CancelGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CancelGameMatchCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());


			Proc_End:

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CancelGameMatchCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CancelGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CancelGameMatchCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* CancelGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result CancelGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CancelGameMatchCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CancelGameMatch:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result CancelGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CancelGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 70);
			Result CancelGameMatchRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result CancelGameMatchRes::ParseMessage( MessageData* pIMsg )

			Result CancelGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CancelGameMatchRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result CancelGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CancelGameMatchRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CancelGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CancelGameMatchRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* CancelGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result CancelGameMatchRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CancelGameMatchRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CancelGameMatch:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result CancelGameMatchRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: game matching canceled
			const MessageID GameMatchingCanceledS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 71);
			Result GameMatchingCanceledS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;


				protocolChkPtr(pIMsg);




			Proc_End:

				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessage( MessageData* pIMsg )

			Result GameMatchingCanceledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GameMatchingCanceledS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));



			Proc_End:

				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GameMatchingCanceledS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GameMatchingCanceledS2CEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) );


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchingCanceledS2CEvt::MID, __uiMessageSize ) );



			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GameMatchingCanceledS2CEvt::Create( IHeap& memHeap )



			Result GameMatchingCanceledS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameMatchingCanceledS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameMatchingCanceled:{0}:{1} ",
						prefix, pMsg->GetMessageHeader()->Length); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchingCanceledS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Buy shop item prepare
			const MessageID BuyShopItemPrepareCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 72);
			Result BuyShopItemPrepareCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ShopItemID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessage( MessageData* pIMsg )

			Result BuyShopItemPrepareCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				BuyShopItemPrepareCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());


			Proc_End:

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) BuyShopItemPrepareCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* BuyShopItemPrepareCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemPrepareCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InShopItemID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* BuyShopItemPrepareCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID )



			Result BuyShopItemPrepareCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				BuyShopItemPrepareCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "BuyShopItemPrepare:{0}:{1} , TransactionID:{2}, ShopItemID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetShopItemID()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemPrepareCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID BuyShopItemPrepareRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 72);
			Result BuyShopItemPrepareRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfPurchaseID = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ShopItemID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPurchaseID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_PurchaseID, pCur, iMsgSize, sizeof(char)*uiSizeOfPurchaseID ) );


			Proc_End:

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessage( MessageData* pIMsg )

			Result BuyShopItemPrepareRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				BuyShopItemPrepareRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());
				variableBuilder.SetVariable("PurchaseID", parser.GetPurchaseID());


			Proc_End:

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) BuyShopItemPrepareRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* BuyShopItemPrepareRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInPurchaseIDLength = InPurchaseID ? (uint16_t)(strlen(InPurchaseID)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInPurchaseIDLength 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemPrepareRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InShopItemID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &__uiInPurchaseIDLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPurchaseID ? InPurchaseID : "", __uiInPurchaseIDLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* BuyShopItemPrepareRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )



			Result BuyShopItemPrepareRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				BuyShopItemPrepareRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "BuyShopItemPrepare:{0}:{1} , TransactionID:{2}, Result:{3:X8}, ShopItemID:{4}, PurchaseID:{5,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetShopItemID(), parser.GetPurchaseID()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemPrepareRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Buy shop item
			const MessageID BuyShopItemCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 73);
			Result BuyShopItemCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfPlatform = 0;
				uint16_t uiSizeOfPackageName = 0;
				uint16_t uiSizeOfPurchaseTransactionID = 0;
				uint16_t numberofPurchaseToken = 0; uint8_t* pPurchaseToken = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ShopItemID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPlatform, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_Platform, pCur, iMsgSize, sizeof(char)*uiSizeOfPlatform ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPackageName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_PackageName, pCur, iMsgSize, sizeof(char)*uiSizeOfPackageName ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPurchaseTransactionID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_PurchaseTransactionID, pCur, iMsgSize, sizeof(char)*uiSizeOfPurchaseTransactionID ) );
				protocolChk( Protocol::StreamParamCopy( &numberofPurchaseToken, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pPurchaseToken, pCur, iMsgSize, sizeof(uint8_t)*numberofPurchaseToken ) );
				m_PurchaseToken.SetLinkedBuffer(numberofPurchaseToken, numberofPurchaseToken, pPurchaseToken);


			Proc_End:

				return hr;

			}; // Result BuyShopItemCmd::ParseMessage( MessageData* pIMsg )

			Result BuyShopItemCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				BuyShopItemCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());
				variableBuilder.SetVariable("Platform", parser.GetPlatform());
				variableBuilder.SetVariable("PackageName", parser.GetPackageName());
				variableBuilder.SetVariable("PurchaseTransactionID", parser.GetPurchaseTransactionID());
				variableBuilder.SetVariable("PurchaseToken", parser.GetPurchaseToken());


			Proc_End:

				return hr;

			}; // Result BuyShopItemCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) BuyShopItemCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* BuyShopItemCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInPlatformLength = InPlatform ? (uint16_t)(strlen(InPlatform)+1) : 1;
				uint16_t __uiInPackageNameLength = InPackageName ? (uint16_t)(strlen(InPackageName)+1) : 1;
				uint16_t __uiInPurchaseTransactionIDLength = InPurchaseTransactionID ? (uint16_t)(strlen(InPurchaseTransactionID)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInPlatformLength + sizeof(uint16_t) + __uiInPackageNameLength + sizeof(uint16_t) + __uiInPurchaseTransactionIDLength 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t)
					+ sizeof(uint8_t)*InPurchaseToken.size() + sizeof(uint16_t));


				uint16_t numberOfInPurchaseToken = (uint16_t)InPurchaseToken.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InShopItemID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &__uiInPlatformLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPlatform ? InPlatform : "", __uiInPlatformLength );
				Protocol::PackParamCopy( pMsgData, &__uiInPackageNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPackageName ? InPackageName : "", __uiInPackageNameLength );
				Protocol::PackParamCopy( pMsgData, &__uiInPurchaseTransactionIDLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPurchaseTransactionID ? InPurchaseTransactionID : "", __uiInPurchaseTransactionIDLength );
				Protocol::PackParamCopy( pMsgData, &numberOfInPurchaseToken, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InPurchaseToken.data(), (INT)(sizeof(uint8_t)*InPurchaseToken.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* BuyShopItemCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )



			Result BuyShopItemCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				BuyShopItemCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "BuyShopItem:{0}:{1} , TransactionID:{2}, ShopItemID:{3}, Platform:{4,60}, PackageName:{5,60}, PurchaseTransactionID:{6,60}, PurchaseToken:{7,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetShopItemID(), parser.GetPlatform(), parser.GetPackageName(), parser.GetPurchaseTransactionID(), parser.GetPurchaseToken()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID BuyShopItemRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 73);
			Result BuyShopItemRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ShopItemID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result BuyShopItemRes::ParseMessage( MessageData* pIMsg )

			Result BuyShopItemRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				BuyShopItemRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());


			Proc_End:

				return hr;

			}; // Result BuyShopItemRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) BuyShopItemRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* BuyShopItemRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InShopItemID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* BuyShopItemRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )



			Result BuyShopItemRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				BuyShopItemRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "BuyShopItem:{0}:{1} , TransactionID:{2}, Result:{3:X8}, ShopItemID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetShopItemID()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Create or Join Chat channel
			const MessageID CreateOrJoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 74);
			Result CreateOrJoinChatChannelCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfChannelName = 0;
				uint16_t uiSizeOfPasscode = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfChannelName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ChannelName, pCur, iMsgSize, sizeof(char)*uiSizeOfChannelName ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPasscode, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_Passcode, pCur, iMsgSize, sizeof(char)*uiSizeOfPasscode ) );


			Proc_End:

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessage( MessageData* pIMsg )

			Result CreateOrJoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreateOrJoinChatChannelCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChannelName", parser.GetChannelName());
				variableBuilder.SetVariable("Passcode", parser.GetPasscode());


			Proc_End:

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateOrJoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInChannelNameLength = InChannelName ? (uint16_t)(strlen(InChannelName)+1) : 1;
				uint16_t __uiInPasscodeLength = InPasscode ? (uint16_t)(strlen(InPasscode)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInChannelNameLength + sizeof(uint16_t) + __uiInPasscodeLength 
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateOrJoinChatChannelCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInChannelNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InChannelName ? InChannelName : "", __uiInChannelNameLength );
				Protocol::PackParamCopy( pMsgData, &__uiInPasscodeLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPasscode ? InPasscode : "", __uiInPasscodeLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* CreateOrJoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )



			Result CreateOrJoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateOrJoinChatChannelCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateOrJoinChatChannel:{0}:{1} , TransactionID:{2}, ChannelName:{3,60}, Passcode:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChannelName(), parser.GetPasscode()); 
				return ResultCode::SUCCESS;
			}; // Result CreateOrJoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CreateOrJoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 74);
			Result CreateOrJoinChatChannelRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessage( MessageData* pIMsg )

			Result CreateOrJoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreateOrJoinChatChannelRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());


			Proc_End:

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateOrJoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateOrJoinChatChannelRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* CreateOrJoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID )



			Result CreateOrJoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateOrJoinChatChannelRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateOrJoinChatChannel:{0}:{1} , TransactionID:{2}, Result:{3:X8}, ChatUID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetChatUID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateOrJoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Join
			const MessageID JoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 75);
			Result JoinChatChannelCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_InviterID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessage( MessageData* pIMsg )

			Result JoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinChatChannelCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());


			Proc_End:

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinChatChannelCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InInviterID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )



			Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinChatChannelCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinChatChannel:{0}:{1} , TransactionID:{2}, ChatUID:{3}, InviterID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetInviterID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 75);
			Result JoinChatChannelRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PartyLeaderID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result JoinChatChannelRes::ParseMessage( MessageData* pIMsg )

			Result JoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinChatChannelRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());


			Proc_End:

				return hr;

			}; // Result JoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinChatChannelRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InPartyUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPartyLeaderID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID )



			Result JoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinChatChannelRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinChatChannel:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PartyUID:{4}, PartyLeaderID:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPartyUID(), parser.GetPartyLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Joined event
			const MessageID ChatChannelPlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 76);
			Result ChatChannelPlayerJoinedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayer, pCur, iMsgSize, sizeof(PlayerInformation) ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelPlayerJoinedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());


			Proc_End:

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelPlayerJoinedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(PlayerInformation));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerJoinedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayer, sizeof(PlayerInformation));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )



			Result ChatChannelPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelPlayerJoinedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelPlayerJoined:{0}:{1} , ChatUID:{2}, JoinedPlayer:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetChatUID(), parser.GetJoinedPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: ChatChannel leader changed event
			const MessageID ChatChannelLeaderChangedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 77);
			Result ChatChannelLeaderChangedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_NewLeaderID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelLeaderChangedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());


			Proc_End:

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelLeaderChangedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InNewLeaderID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelLeaderChangedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InNewLeaderID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InNewLeaderID )



			Result ChatChannelLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelLeaderChangedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelLeaderChanged:{0}:{1} , ChatUID:{2}, NewLeaderID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetChatUID(), parser.GetNewLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Leave ChatChannel command
			const MessageID LeaveChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 78);
			Result LeaveChatChannelCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessage( MessageData* pIMsg )

			Result LeaveChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LeaveChatChannelCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());


			Proc_End:

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LeaveChatChannelCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeaveChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveChatChannelCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LeaveChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )



			Result LeaveChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveChatChannelCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveChatChannel:{0}:{1} , TransactionID:{2}, ChatUID:{3}, PlayerID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LeaveChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 78);
			Result LeaveChatChannelRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessage( MessageData* pIMsg )

			Result LeaveChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LeaveChatChannelRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LeaveChatChannelRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeaveChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveChatChannelRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LeaveChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result LeaveChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveChatChannelRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveChatChannel:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: ChatChannel Player left event
			const MessageID ChatChannelPlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 79);
			Result ChatChannelPlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LeftPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelPlayerLeftS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());


			Proc_End:

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelPlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerLeftS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InLeftPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InLeftPlayerID )



			Result ChatChannelPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelPlayerLeftS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelPlayerLeft:{0}:{1} , ChatUID:{2}, LeftPlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetChatUID(), parser.GetLeftPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Kick player from the ChatChannel
			const MessageID ChatChannelKickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 80);
			Result ChatChannelKickPlayerCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerToKick, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessage( MessageData* pIMsg )

			Result ChatChannelKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelKickPlayerCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());


			Proc_End:

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelKickPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(AccountID)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelKickPlayerCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InPlayerToKick, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )



			Result ChatChannelKickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelKickPlayerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelKickPlayer:{0}:{1} , TransactionID:{2}, ChatUID:{3}, PlayerID:{4}, PlayerToKick:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetPlayerID(), parser.GetPlayerToKick()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelKickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ChatChannelKickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 80);
			Result ChatChannelKickPlayerRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessage( MessageData* pIMsg )

			Result ChatChannelKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelKickPlayerRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelKickPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelKickPlayerRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result ChatChannelKickPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelKickPlayerRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelKickPlayer:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelKickPlayerRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: ChatChannel Player kicked message
			const MessageID ChatChannelPlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 81);
			Result ChatChannelPlayerKickedS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_KickedPlayerID, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessage( MessageData* pIMsg )

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelPlayerKickedS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());


			Proc_End:

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelPlayerKickedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerKickedS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InKickedPlayerID, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InKickedPlayerID )



			Result ChatChannelPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelPlayerKickedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelPlayerKicked:{0}:{1} , ChatUID:{2}, KickedPlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetChatUID(), parser.GetKickedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Party chatting
			const MessageID ChatChannelChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 82);
			Result ChatChannelChatMessageCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfChatMessage = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_ChatUID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfChatMessage, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ChatMessage, pCur, iMsgSize, sizeof(char)*uiSizeOfChatMessage ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessage( MessageData* pIMsg )

			Result ChatChannelChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelChatMessageCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());


			Proc_End:

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInChatMessageLength = InChatMessage ? (uint16_t)(strlen(InChatMessage)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInChatMessageLength 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InChatUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInChatMessageLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InChatMessage ? InChatMessage : "", __uiInChatMessageLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )



			Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelChatMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelChatMessage:{0}:{1} , TransactionID:{2}, ChatUID:{3}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ChatChannelChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 82);
			Result ChatChannelChatMessageRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessage( MessageData* pIMsg )

			Result ChatChannelChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelChatMessageRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result ChatChannelChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelChatMessageRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelChatMessage:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: ChatChannel Chatting message event
			const MessageID ChatChannelChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 83);
			Result ChatChannelChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfSenderName = 0;
				uint16_t uiSizeOfChatMessage = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_SenderID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfSenderName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_SenderName, pCur, iMsgSize, sizeof(char)*uiSizeOfSenderName ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfChatMessage, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ChatMessage, pCur, iMsgSize, sizeof(char)*uiSizeOfChatMessage ) );


			Proc_End:

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessage( MessageData* pIMsg )

			Result ChatChannelChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ChatChannelChatMessageS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());


			Proc_End:

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) ChatChannelChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInSenderNameLength = InSenderName ? (uint16_t)(strlen(InSenderName)+1) : 1;
				uint16_t __uiInChatMessageLength = InChatMessage ? (uint16_t)(strlen(InChatMessage)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInSenderNameLength + sizeof(uint16_t) + __uiInChatMessageLength 
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InSenderID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &__uiInSenderNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InSenderName ? InSenderName : "", __uiInSenderNameLength );
				Protocol::PackParamCopy( pMsgData, &__uiInChatMessageLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InChatMessage ? InChatMessage : "", __uiInChatMessageLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )



			Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelChatMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelChatMessage:{0}:{1} , SenderID:{2}, SenderName:{3,60}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetSenderName(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Give my stamina to other player
			const MessageID GiveStaminaCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 84);
			Result GiveStaminaCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TargetPlayer, pCur, iMsgSize, sizeof(AccountID) ) );


			Proc_End:

				return hr;

			}; // Result GiveStaminaCmd::ParseMessage( MessageData* pIMsg )

			Result GiveStaminaCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GiveStaminaCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayer", parser.GetTargetPlayer());


			Proc_End:

				return hr;

			}; // Result GiveStaminaCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GiveStaminaCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GiveStaminaCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GiveStaminaCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GiveStaminaCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InTargetPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(AccountID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GiveStaminaCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InTargetPlayer, sizeof(AccountID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GiveStaminaCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InTargetPlayer )



			Result GiveStaminaCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GiveStaminaCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GiveStamina:{0}:{1} , TransactionID:{2}, TargetPlayer:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTargetPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result GiveStaminaCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GiveStaminaRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 84);
			Result GiveStaminaRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TargetPlayer, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TimeStamp, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result GiveStaminaRes::ParseMessage( MessageData* pIMsg )

			Result GiveStaminaRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GiveStaminaRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TargetPlayer", parser.GetTargetPlayer());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());


			Proc_End:

				return hr;

			}; // Result GiveStaminaRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GiveStaminaRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GiveStaminaRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GiveStaminaRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GiveStaminaRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InTargetPlayer, const uint64_t &InTimeStamp )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(AccountID)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GiveStaminaRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InTargetPlayer, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTimeStamp, sizeof(uint64_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GiveStaminaRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InTargetPlayer, const uint64_t &InTimeStamp )



			Result GiveStaminaRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GiveStaminaRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GiveStamina:{0}:{1} , TransactionID:{2}, Result:{3:X8}, TargetPlayer:{4}, TimeStamp:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTargetPlayer(), parser.GetTimeStamp()); 
				return ResultCode::SUCCESS;
			}; // Result GiveStaminaRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: For debug, Change configue preset
			const MessageID SetPresetGameConfigIDCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 85);
			Result SetPresetGameConfigIDCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PresetID, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result SetPresetGameConfigIDCmd::ParseMessage( MessageData* pIMsg )

			Result SetPresetGameConfigIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetPresetGameConfigIDCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PresetID", parser.GetPresetID());


			Proc_End:

				return hr;

			}; // Result SetPresetGameConfigIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetPresetGameConfigIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetPresetGameConfigIDCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetPresetGameConfigIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetPresetGameConfigIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InPresetID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetPresetGameConfigIDCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InPresetID, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetPresetGameConfigIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InPresetID )



			Result SetPresetGameConfigIDCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetPresetGameConfigIDCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetPresetGameConfigID:{0}:{1} , TransactionID:{2}, PresetID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPresetID()); 
				return ResultCode::SUCCESS;
			}; // Result SetPresetGameConfigIDCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID SetPresetGameConfigIDRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 85);
			Result SetPresetGameConfigIDRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result SetPresetGameConfigIDRes::ParseMessage( MessageData* pIMsg )

			Result SetPresetGameConfigIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetPresetGameConfigIDRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result SetPresetGameConfigIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetPresetGameConfigIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) SetPresetGameConfigIDRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result SetPresetGameConfigIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* SetPresetGameConfigIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetPresetGameConfigIDRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* SetPresetGameConfigIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result SetPresetGameConfigIDRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetPresetGameConfigIDRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetPresetGameConfigID:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result SetPresetGameConfigIDRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: For Debug
			const MessageID GainGameResourceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 86);
			Result GainGameResourceCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Resource, pCur, iMsgSize, sizeof(int32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Value, pCur, iMsgSize, sizeof(int32_t) ) );


			Proc_End:

				return hr;

			}; // Result GainGameResourceCmd::ParseMessage( MessageData* pIMsg )

			Result GainGameResourceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GainGameResourceCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Resource", parser.GetResource());
				variableBuilder.SetVariable("Value", parser.GetValue());


			Proc_End:

				return hr;

			}; // Result GainGameResourceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GainGameResourceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GainGameResourceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GainGameResourceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GainGameResourceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const int32_t &InResource, const int32_t &InValue )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(int32_t)
					+ sizeof(int32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GainGameResourceCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResource, sizeof(int32_t));
				Protocol::PackParamCopy( pMsgData, &InValue, sizeof(int32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GainGameResourceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const int32_t &InResource, const int32_t &InValue )



			Result GainGameResourceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GainGameResourceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GainGameResource:{0}:{1} , TransactionID:{2}, Resource:{3}, Value:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResource(), parser.GetValue()); 
				return ResultCode::SUCCESS;
			}; // Result GainGameResourceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GainGameResourceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 86);
			Result GainGameResourceRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result GainGameResourceRes::ParseMessage( MessageData* pIMsg )

			Result GainGameResourceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GainGameResourceRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result GainGameResourceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GainGameResourceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GainGameResourceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GainGameResourceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GainGameResourceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GainGameResourceRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GainGameResourceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result GainGameResourceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GainGameResourceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GainGameResource:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result GainGameResourceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)



		}; // namespace Game
	}; // namespace Message
}; // namespace SF



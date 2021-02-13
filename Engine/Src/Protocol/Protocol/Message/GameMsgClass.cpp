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
 			// C2S: Client heartbeat
			const MessageID HeartbeatC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 0);
			Result HeartbeatC2SEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);



				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessage(const MessageData* pIMsg)

			Result HeartbeatC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				HeartbeatC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));


				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result HeartbeatC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) HeartbeatC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* HeartbeatC2SEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::HeartbeatC2SEvt::MID, __uiMessageSize ) );

				return hr;
			}; // MessageData* HeartbeatC2SEvt::Create( IHeap& memHeap )



			Result HeartbeatC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				HeartbeatC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Heartbeat:{0}:{1} ",
						prefix, pMsg->GetMessageHeader()->Length); 
				return ResultCode::SUCCESS;
			}; // Result HeartbeatC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Player connected from a login server and moved to game server
			const MessageID JoinGameServerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 1);
			Result JoinGameServerCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);

				return hr;

			}; // Result JoinGameServerCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinGameServerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameServerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result JoinGameServerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameServerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameServerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameServerCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);

				return hr;
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
			Result JoinGameServerRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_NickName, ArrayLen));
				protocolCheck(*input >> m_GameUID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PartyLeaderID);
				protocolCheck(*input >> m_MatchingTicket);

				return hr;

			}; // Result JoinGameServerRes::ParseMessage(const MessageData* pIMsg)

			Result JoinGameServerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameServerRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("GameUID", parser.GetGameUID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());
				variableBuilder.SetVariable("MatchingTicket", parser.GetMatchingTicket());

				return hr;

			}; // Result JoinGameServerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameServerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameServerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InGameUID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPartyLeaderID)
					+ SerializedSizeOf(InMatchingTicket)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameServerRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNickName);
				protocolCheck(*output << InGameUID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPartyLeaderID);
				protocolCheck(*output << InMatchingTicket);

				return hr;
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
			Result GetComplitionStateCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessage(const MessageData* pIMsg)

			Result GetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetComplitionStateCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetComplitionStateCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetComplitionStateCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
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
			Result GetComplitionStateRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ComplitionState, ArrayLen));

				return hr;

			}; // Result GetComplitionStateRes::ParseMessage(const MessageData* pIMsg)

			Result GetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetComplitionStateRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());

				return hr;

			}; // Result GetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetComplitionStateRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InComplitionState)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetComplitionStateRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InComplitionState);

				return hr;
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
			Result SetComplitionStateCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ComplitionState, ArrayLen));

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessage(const MessageData* pIMsg)

			Result SetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetComplitionStateCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetComplitionStateCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InComplitionState )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InComplitionState)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetComplitionStateCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InComplitionState);

				return hr;
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
			Result SetComplitionStateRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result SetComplitionStateRes::ParseMessage(const MessageData* pIMsg)

			Result SetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetComplitionStateRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result SetComplitionStateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetComplitionStateRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetComplitionStateRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result RegisterGCMCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GCMRegisteredID, ArrayLen));

				return hr;

			}; // Result RegisterGCMCmd::ParseMessage(const MessageData* pIMsg)

			Result RegisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RegisterGCMCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());

				return hr;

			}; // Result RegisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RegisterGCMCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RegisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGCMRegisteredID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RegisterGCMCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGCMRegisteredID);

				return hr;
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
			Result RegisterGCMRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RegisterGCMRes::ParseMessage(const MessageData* pIMsg)

			Result RegisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RegisterGCMRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RegisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RegisterGCMRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RegisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RegisterGCMRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result UnregisterGCMCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GCMRegisteredID, ArrayLen));

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessage(const MessageData* pIMsg)

			Result UnregisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnregisterGCMCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnregisterGCMCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* UnregisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGCMRegisteredID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::UnregisterGCMCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGCMRegisteredID);

				return hr;
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
			Result UnregisterGCMRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result UnregisterGCMRes::ParseMessage(const MessageData* pIMsg)

			Result UnregisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnregisterGCMRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result UnregisterGCMRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnregisterGCMRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* UnregisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::UnregisterGCMRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result InviteFriendCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result InviteFriendCmd::ParseMessage(const MessageData* pIMsg)

			Result InviteFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				InviteFriendCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result InviteFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) InviteFriendCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* InviteFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::InviteFriendCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFriendID);

				return hr;
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
			Result InviteFriendRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result InviteFriendRes::ParseMessage(const MessageData* pIMsg)

			Result InviteFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				InviteFriendRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result InviteFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) InviteFriendRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* InviteFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::InviteFriendRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result AcceptFriendRequestCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InviterID);
				protocolCheck(*input >> m_InviterFacebookUID);

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessage(const MessageData* pIMsg)

			Result AcceptFriendRequestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptFriendRequestCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterFacebookUID", parser.GetInviterFacebookUID());

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptFriendRequestCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AcceptFriendRequestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InInviterFacebookUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptFriendRequestCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInviterID);
				protocolCheck(*output << InInviterFacebookUID);

				return hr;
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
			Result AcceptFriendRequestRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NewFriend);

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessage(const MessageData* pIMsg)

			Result AcceptFriendRequestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptFriendRequestRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NewFriend", parser.GetNewFriend());

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptFriendRequestRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AcceptFriendRequestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNewFriend)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptFriendRequestRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNewFriend);

				return hr;
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
			Result FriendRequestAcceptedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_Accepter);

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result FriendRequestAcceptedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FriendRequestAcceptedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Accepter", parser.GetAccepter());

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FriendRequestAcceptedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FriendRequestAcceptedS2CEvt::Create( IHeap& memHeap, const FriendInformation &InAccepter )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InAccepter)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FriendRequestAcceptedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InAccepter);

				return hr;
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
			Result RemoveFriendCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result RemoveFriendCmd::ParseMessage(const MessageData* pIMsg)

			Result RemoveFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemoveFriendCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result RemoveFriendCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveFriendCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RemoveFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RemoveFriendCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFriendID);

				return hr;
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
			Result RemoveFriendRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result RemoveFriendRes::ParseMessage(const MessageData* pIMsg)

			Result RemoveFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemoveFriendRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result RemoveFriendRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveFriendRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RemoveFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RemoveFriendRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InFriendID);

				return hr;
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
			Result FriendRemovedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result FriendRemovedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FriendRemovedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FriendRemovedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FriendRemovedS2CEvt::Create( IHeap& memHeap, const AccountID &InFriendID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FriendRemovedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InFriendID);

				return hr;
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
			Result GetFriendListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_StartIndex);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result GetFriendListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetFriendListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetFriendListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("StartIndex", parser.GetStartIndex());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result GetFriendListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetFriendListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetFriendListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InStartIndex)
					+ SerializedSizeOf(InCount)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetFriendListCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InStartIndex);
				protocolCheck(*output << InCount);

				return hr;
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
			Result GetFriendListRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_MaxFriendSlot);
				protocolCheck(*input >> m_TotalNumberOfFriends);
				protocolCheck(*input >> m_StartIndex);
				protocolCheck(input->Read(ArrayLen));
				FriendInformation* FriendListPtr = nullptr;
				protocolCheck(input->ReadLink(FriendListPtr, ArrayLen));
				m_FriendList.SetLinkedBuffer(ArrayLen, FriendListPtr);

				return hr;

			}; // Result GetFriendListRes::ParseMessage(const MessageData* pIMsg)

			Result GetFriendListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetFriendListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("MaxFriendSlot", parser.GetMaxFriendSlot());
				variableBuilder.SetVariable("TotalNumberOfFriends", parser.GetTotalNumberOfFriends());
				variableBuilder.SetVariable("StartIndex", parser.GetStartIndex());
				variableBuilder.SetVariable("FriendList", parser.GetFriendList());

				return hr;

			}; // Result GetFriendListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetFriendListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetFriendListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInFriendList = (uint16_t)InFriendList.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InMaxFriendSlot)
					+ SerializedSizeOf(InTotalNumberOfFriends)
					+ SerializedSizeOf(InStartIndex)
					+ SerializedSizeOf(InFriendList)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetFriendListRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InMaxFriendSlot);
				protocolCheck(*output << InTotalNumberOfFriends);
				protocolCheck(*output << InStartIndex);
				protocolCheck(*output << InFriendList);

				return hr;
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
			Result GetNotificationListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetNotificationListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetNotificationListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetNotificationListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetNotificationListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetNotificationListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetNotificationListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetNotificationListCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
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
			Result GetNotificationListRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result GetNotificationListRes::ParseMessage(const MessageData* pIMsg)

			Result GetNotificationListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetNotificationListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result GetNotificationListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetNotificationListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetNotificationListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetNotificationListRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result DeleteNotificationCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessage(const MessageData* pIMsg)

			Result DeleteNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteNotificationCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteNotificationCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* DeleteNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteNotificationCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNotificationID);

				return hr;
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
			Result DeleteNotificationRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result DeleteNotificationRes::ParseMessage(const MessageData* pIMsg)

			Result DeleteNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteNotificationRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result DeleteNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteNotificationRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* DeleteNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteNotificationRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNotificationID);

				return hr;
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
			Result SetNotificationReadCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessage(const MessageData* pIMsg)

			Result SetNotificationReadCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNotificationReadCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNotificationReadCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetNotificationReadCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNotificationReadCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNotificationID);

				return hr;
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
			Result SetNotificationReadRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result SetNotificationReadRes::ParseMessage(const MessageData* pIMsg)

			Result SetNotificationReadRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNotificationReadRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result SetNotificationReadRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNotificationReadRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetNotificationReadRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNotificationReadRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNotificationID);

				return hr;
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
			Result AcceptNotificationCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessage(const MessageData* pIMsg)

			Result AcceptNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptNotificationCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptNotificationCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AcceptNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptNotificationCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNotificationID);

				return hr;
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
			Result AcceptNotificationRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result AcceptNotificationRes::ParseMessage(const MessageData* pIMsg)

			Result AcceptNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptNotificationRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result AcceptNotificationRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptNotificationRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AcceptNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptNotificationRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNotificationID);

				return hr;
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
			Result NotifyS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_NotificationID);
				protocolCheck(*input >> m_NotificationType);
				protocolCheck(*input >> m_MessageParam0);
				protocolCheck(*input >> m_MessageParam1);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_MessageText, ArrayLen));
				protocolCheck(*input >> m_IsRead);
				protocolCheck(*input >> m_TimeStamp);

				return hr;

			}; // Result NotifyS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result NotifyS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				NotifyS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());
				variableBuilder.SetVariable("NotificationType", parser.GetNotificationType());
				variableBuilder.SetVariable("MessageParam0", parser.GetMessageParam0());
				variableBuilder.SetVariable("MessageParam1", parser.GetMessageParam1());
				variableBuilder.SetVariable("MessageText", parser.GetMessageText());
				variableBuilder.SetVariable("IsRead", parser.GetIsRead());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());

				return hr;

			}; // Result NotifyS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NotifyS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* NotifyS2CEvt::Create( IHeap& memHeap, const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InNotificationID)
					+ SerializedSizeOf(InNotificationType)
					+ SerializedSizeOf(InMessageParam0)
					+ SerializedSizeOf(InMessageParam1)
					+ SerializedSizeOf(InMessageText)
					+ SerializedSizeOf(InIsRead)
					+ SerializedSizeOf(InTimeStamp)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::NotifyS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InNotificationID);
				protocolCheck(*output << InNotificationType);
				protocolCheck(*output << InMessageParam0);
				protocolCheck(*output << InMessageParam1);
				protocolCheck(*output << InMessageText);
				protocolCheck(*output << InIsRead);
				protocolCheck(*output << InTimeStamp);

				return hr;
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
			Result FindPlayerByEMailCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlayerEMail, ArrayLen));

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByEMailCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByEMailCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerEMail", parser.GetPlayerEMail());

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByEMailCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FindPlayerByEMailCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InPlayerEMail )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerEMail)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByEMailCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayerEMail);

				return hr;
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
			Result FindPlayerByEMailRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_Player);

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByEMailRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByEMailRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", parser.GetPlayer());

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByEMailRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FindPlayerByEMailRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByEMailRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayer);

				return hr;
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
			Result FindPlayerByPlayerIDCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByPlayerIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlayerIDCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FindPlayerByPlayerIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlayerIDCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayerID);

				return hr;
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
			Result FindPlayerByPlayerIDRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_Player);

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByPlayerIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlayerIDRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", parser.GetPlayer());

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FindPlayerByPlayerIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlayerIDRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayer);

				return hr;
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
			Result RequestPlayerStatusUpdateCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				AccountID* TargetPlayerIDPtr = nullptr;
				protocolCheck(input->ReadLink(TargetPlayerIDPtr, ArrayLen));
				m_TargetPlayerID.SetLinkedBuffer(ArrayLen, TargetPlayerIDPtr);

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessage(const MessageData* pIMsg)

			Result RequestPlayerStatusUpdateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestPlayerStatusUpdateCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayerID", parser.GetTargetPlayerID());

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RequestPlayerStatusUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInTargetPlayerID = (uint16_t)InTargetPlayerID.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTargetPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestPlayerStatusUpdateCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTargetPlayerID);

				return hr;
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
			Result RequestPlayerStatusUpdateRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessage(const MessageData* pIMsg)

			Result RequestPlayerStatusUpdateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestPlayerStatusUpdateRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RequestPlayerStatusUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestPlayerStatusUpdateRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_LatestActiveTime);
				protocolCheck(*input >> m_IsInGame);

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				NotifyPlayerStatusUpdatedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("LatestActiveTime", parser.GetLatestActiveTime());
				variableBuilder.SetVariable("IsInGame", parser.GetIsInGame());

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NotifyPlayerStatusUpdatedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* NotifyPlayerStatusUpdatedS2CEvt::Create( IHeap& memHeap, const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InLatestActiveTime)
					+ SerializedSizeOf(InIsInGame)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::NotifyPlayerStatusUpdatedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLatestActiveTime);
				protocolCheck(*output << InIsInGame);

				return hr;
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
			Result GetRankingListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_RankingType);
				protocolCheck(*input >> m_BaseRanking);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result GetRankingListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetRankingListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetRankingListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingType", parser.GetRankingType());
				variableBuilder.SetVariable("BaseRanking", parser.GetBaseRanking());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InRankingType)
					+ SerializedSizeOf(InBaseRanking)
					+ SerializedSizeOf(InCount)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetRankingListCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InRankingType);
				protocolCheck(*output << InBaseRanking);
				protocolCheck(*output << InCount);

				return hr;
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
			Result GetRankingListRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				TotalRankingPlayerInformation* RankingPtr = nullptr;
				protocolCheck(input->ReadLink(RankingPtr, ArrayLen));
				m_Ranking.SetLinkedBuffer(ArrayLen, RankingPtr);

				return hr;

			}; // Result GetRankingListRes::ParseMessage(const MessageData* pIMsg)

			Result GetRankingListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetRankingListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());

				return hr;

			}; // Result GetRankingListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetRankingListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInRanking = (uint16_t)InRanking.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InRanking)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetRankingListRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InRanking);

				return hr;
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
			Result GetUserGamePlayerInfoCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessage(const MessageData* pIMsg)

			Result GetUserGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetUserGamePlayerInfoCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetUserGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
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
			const VariableTable& GetUserGamePlayerInfoRes::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& GetUserGamePlayerInfoRes::GetAttributes() const
			Result GetUserGamePlayerInfoRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessage(const MessageData* pIMsg)

			Result GetUserGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetUserGamePlayerInfoRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetUserGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetUserGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes )

			MessageData* GetUserGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetUserGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )



			Result GetUserGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetUserGamePlayerInfoRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetUserGamePlayerInfo:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Attributes:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result GetUserGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Game game play information
			const MessageID GetGamePlayerInfoCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 23);
			Result GetGamePlayerInfoCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessage(const MessageData* pIMsg)

			Result GetGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetGamePlayerInfoCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetGamePlayerInfoCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayerID);

				return hr;
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
			const VariableTable& GetGamePlayerInfoRes::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& GetGamePlayerInfoRes::GetAttributes() const
			Result GetGamePlayerInfoRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessage(const MessageData* pIMsg)

			Result GetGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetGamePlayerInfoRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetGamePlayerInfoRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const Array<uint8_t>& InAttributes )

			MessageData* GetGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )



			Result GetGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetGamePlayerInfoRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetGamePlayerInfo:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerID:{4}, Attributes:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result GetGamePlayerInfoRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player level up event
			const MessageID LevelUpS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 24);
			Result LevelUpS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_CurrentTotalExp);
				protocolCheck(*input >> m_CurrentLevel);

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result LevelUpS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LevelUpS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("CurrentTotalExp", parser.GetCurrentTotalExp());
				variableBuilder.SetVariable("CurrentLevel", parser.GetCurrentLevel());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LevelUpS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LevelUpS2CEvt::Create( IHeap& memHeap, const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InCurrentTotalExp)
					+ SerializedSizeOf(InCurrentLevel)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LevelUpS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InCurrentTotalExp);
				protocolCheck(*output << InCurrentLevel);

				return hr;
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
			Result SetNickNameCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_NickName, ArrayLen));
				protocolCheck(*input >> m_IsCostFree);

				return hr;

			}; // Result SetNickNameCmd::ParseMessage(const MessageData* pIMsg)

			Result SetNickNameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNickNameCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("IsCostFree", parser.GetIsCostFree());

				return hr;

			}; // Result SetNickNameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNickNameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetNickNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InIsCostFree)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNickNameCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNickName);
				protocolCheck(*output << InIsCostFree);

				return hr;
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
			Result SetNickNameRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result SetNickNameRes::ParseMessage(const MessageData* pIMsg)

			Result SetNickNameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNickNameRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result SetNickNameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNickNameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetNickNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNickNameRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
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
			Result CreatePartyCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result CreatePartyCmd::ParseMessage(const MessageData* pIMsg)

			Result CreatePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreatePartyCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result CreatePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreatePartyCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreatePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreatePartyCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
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
			Result CreatePartyRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PartyUID);

				return hr;

			}; // Result CreatePartyRes::ParseMessage(const MessageData* pIMsg)

			Result CreatePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreatePartyRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());

				return hr;

			}; // Result CreatePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreatePartyRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreatePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPartyUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreatePartyRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPartyUID);

				return hr;
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
			Result JoinPartyCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_InviterID);

				return hr;

			}; // Result JoinPartyCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinPartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinPartyCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());

				return hr;

			}; // Result JoinPartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPartyCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinPartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InInviterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinPartyCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InInviterID);

				return hr;
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
			Result JoinPartyRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PartyLeaderID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatHistoryDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatHistoryDataPtr, ArrayLen));
				m_ChatHistoryData.SetLinkedBuffer(ArrayLen, ChatHistoryDataPtr);

				return hr;

			}; // Result JoinPartyRes::ParseMessage(const MessageData* pIMsg)

			Result JoinPartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinPartyRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());
				variableBuilder.SetVariable("ChatHistoryData", parser.GetChatHistoryData());

				return hr;

			}; // Result JoinPartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPartyRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinPartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInChatHistoryData = (uint16_t)InChatHistoryData.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPartyLeaderID)
					+ SerializedSizeOf(InChatHistoryData)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinPartyRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPartyLeaderID);
				protocolCheck(*output << InChatHistoryData);

				return hr;
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
			Result PartyPlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_JoinedPlayer);

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerJoinedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerJoinedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InJoinedPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerJoinedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InJoinedPlayer);

				return hr;
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
			Result PartyLeaderChangedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_NewLeaderID);

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyLeaderChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyLeaderChangedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InNewLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyLeaderChangedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InNewLeaderID);

				return hr;
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
			Result LeavePartyCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result LeavePartyCmd::ParseMessage(const MessageData* pIMsg)

			Result LeavePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeavePartyCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result LeavePartyCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeavePartyCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeavePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeavePartyCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPlayerID);

				return hr;
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
			Result LeavePartyRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeavePartyRes::ParseMessage(const MessageData* pIMsg)

			Result LeavePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeavePartyRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeavePartyRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeavePartyRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeavePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeavePartyRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result PartyPlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_LeftPlayerID);

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InLeftPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerLeftS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InLeftPlayerID);

				return hr;
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
			Result PartyKickPlayerCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerToKick);

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyKickPlayerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyKickPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerToKick)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyKickPlayerCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerToKick);

				return hr;
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
			Result PartyKickPlayerRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessage(const MessageData* pIMsg)

			Result PartyKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyKickPlayerRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyKickPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyKickPlayerRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result PartyPlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerKickedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerKickedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InKickedPlayerID);

				return hr;
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
			Result PartyInviteCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InviteTargetID);

				return hr;

			}; // Result PartyInviteCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyInviteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviteTargetID", parser.GetInviteTargetID());

				return hr;

			}; // Result PartyInviteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyInviteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInviteTargetID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInviteTargetID);

				return hr;
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
			Result PartyInviteRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyInviteRes::ParseMessage(const MessageData* pIMsg)

			Result PartyInviteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyInviteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyInviteRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result PartyInviteRequestedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_InviterID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_InviterName, ArrayLen));
				protocolCheck(*input >> m_PartyToJoinUID);

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyInviteRequestedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteRequestedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterName", parser.GetInviterName());
				variableBuilder.SetVariable("PartyToJoinUID", parser.GetPartyToJoinUID());

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteRequestedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyInviteRequestedS2CEvt::Create( IHeap& memHeap, const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InInviterName)
					+ SerializedSizeOf(InPartyToJoinUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteRequestedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InInviterID);
				protocolCheck(*output << InInviterName);
				protocolCheck(*output << InPartyToJoinUID);

				return hr;
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
			Result PartyQuickChatMessageCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_QuickChatID);

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyQuickChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyQuickChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InQuickChatID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InQuickChatID);

				return hr;
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
			Result PartyQuickChatMessageRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessage(const MessageData* pIMsg)

			Result PartyQuickChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyQuickChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result PartyQuickChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(*input >> m_QuickChatID);

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyQuickChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyQuickChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const uint32_t &InQuickChatID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InQuickChatID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InQuickChatID);

				return hr;
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
			Result PartyChatMessageCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatMessage);

				return hr;
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
			Result PartyChatMessageRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyChatMessageRes::ParseMessage(const MessageData* pIMsg)

			Result PartyChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			Result PartyChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SenderName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PartyChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InSenderName)
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InSenderName);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* PartyChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )



			Result PartyChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PartyChatMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PartyChatMessage:{0}:{1} , SenderID:{2}, SenderName:{3,60}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetSenderName(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result PartyChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Join to a game instance
			const MessageID JoinGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 40);
			Result JoinGameInstanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InsUID);

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InInsUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInsUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameInstanceCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInsUID);

				return hr;
			}; // MessageData* JoinGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InInsUID )



			Result JoinGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameInstanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGameInstance:{0}:{1} , TransactionID:{2}, InsUID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetInsUID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 40);
			Result JoinGameInstanceRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_InsUID);
				protocolCheck(*input >> m_ServerAddress);
				protocolCheck(*input >> m_ServerAddress4);

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result JoinGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());
				variableBuilder.SetVariable("ServerAddress", parser.GetServerAddress());
				variableBuilder.SetVariable("ServerAddress4", parser.GetServerAddress4());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const NetAddress &InServerAddress, const NetAddress &InServerAddress4 )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InInsUID)
					+ SerializedSizeOf(InServerAddress)
					+ SerializedSizeOf(InServerAddress4)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InInsUID);
				protocolCheck(*output << InServerAddress);
				protocolCheck(*output << InServerAddress4);

				return hr;
			}; // MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const NetAddress &InServerAddress, const NetAddress &InServerAddress4 )



			Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameInstanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGameInstance:{0}:{1} , TransactionID:{2}, Result:{3:X8}, InsUID:{4}, ServerAddress:{5}, ServerAddress4:{6}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetInsUID(), parser.GetServerAddress(), parser.GetServerAddress4()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Leave game instance
			const MessageID LeaveGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 41);
			Result LeaveGameInstanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InsUID);

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result LeaveGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameInstanceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeaveGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InInsUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInsUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameInstanceCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInsUID);

				return hr;
			}; // MessageData* LeaveGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InInsUID )



			Result LeaveGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveGameInstanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveGameInstance:{0}:{1} , TransactionID:{2}, InsUID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetInsUID()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LeaveGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 41);
			Result LeaveGameInstanceRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result LeaveGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameInstanceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeaveGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* LeaveGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result LeaveGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveGameInstanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveGameInstance:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Search game instance
			const MessageID SearchGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 42);
			Result SearchGameInstanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SearchKeyword, ArrayLen));

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result SearchGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SearchGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("SearchKeyword", parser.GetSearchKeyword());

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SearchGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SearchGameInstanceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SearchGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InSearchKeyword )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InSearchKeyword)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SearchGameInstanceCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InSearchKeyword);

				return hr;
			}; // MessageData* SearchGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InSearchKeyword )



			Result SearchGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SearchGameInstanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SearchGameInstance:{0}:{1} , TransactionID:{2}, SearchKeyword:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetSearchKeyword()); 
				return ResultCode::SUCCESS;
			}; // Result SearchGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID SearchGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 42);
			Result SearchGameInstanceRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				GameInstanceInfo* GameInstancesPtr = nullptr;
				protocolCheck(input->ReadLink(GameInstancesPtr, ArrayLen));
				m_GameInstances.SetLinkedBuffer(ArrayLen, GameInstancesPtr);

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result SearchGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SearchGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameInstances", parser.GetGameInstances());

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SearchGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SearchGameInstanceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SearchGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<GameInstanceInfo>& InGameInstances )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInGameInstances = (uint16_t)InGameInstances.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InGameInstances)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SearchGameInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameInstances);

				return hr;
			}; // MessageData* SearchGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<GameInstanceInfo>& InGameInstances )



			Result SearchGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SearchGameInstanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SearchGameInstance:{0}:{1} , TransactionID:{2}, Result:{3:X8}, GameInstances:{4,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameInstances()); 
				return ResultCode::SUCCESS;
			}; // Result SearchGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Search game instance
			const MessageID GetCharacterDataInGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 43);
			Result GetCharacterDataInGameInstanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterDataInGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataInGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataInGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataInGameInstanceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetCharacterDataInGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataInGameInstanceCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // MessageData* GetCharacterDataInGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )



			Result GetCharacterDataInGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetCharacterDataInGameInstanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetCharacterDataInGameInstance:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataInGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetCharacterDataInGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 43);
			const VariableTable& GetCharacterDataInGameInstanceRes::GetGameInstances() const
			{
 				if (!m_GameInstancesHasParsed)
				{
 					m_GameInstancesHasParsed = true;
					InputMemoryStream GameInstances_ReadStream(m_GameInstancesRaw);
					*GameInstances_ReadStream.ToInputStream() >> m_GameInstances;
				} // if (!m_GameInstancesHasParsed)
				return m_GameInstances;
			} // const VariableTable& GetCharacterDataInGameInstanceRes::GetGameInstances() const
			Result GetCharacterDataInGameInstanceRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* GameInstancesPtr = nullptr;
				protocolCheck(input->ReadLink(GameInstancesPtr, ArrayLen));
				m_GameInstancesRaw.SetLinkedBuffer(ArrayLen, GameInstancesPtr);

				return hr;

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterDataInGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataInGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("GameInstances", "VariableTable", parser.GetGameInstancesRaw());

				return hr;

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataInGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataInGameInstanceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetCharacterDataInGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const Array<uint8_t>& InGameInstances )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInGameInstances = static_cast<uint16_t>(SerializedSizeOf(InGameInstances)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInGameInstances
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataInGameInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InGameInstances);

				return hr;
			}; // MessageData* GetCharacterDataInGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const Array<uint8_t>& InGameInstances )

			MessageData* GetCharacterDataInGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInGameInstances = static_cast<uint16_t>(SerializedSizeOf(InGameInstances)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInGameInstances
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataInGameInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInGameInstances));
				protocolCheck(*output << InGameInstances);

				return hr;
			}; // MessageData* GetCharacterDataInGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )



			Result GetCharacterDataInGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetCharacterDataInGameInstanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetCharacterDataInGameInstance:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerID:{4}, GameInstances:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerID(), parser.GetGameInstances()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataInGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Join to a game
			const MessageID JoinGameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 44);
			Result JoinGameCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_InsUID);

				return hr;

			}; // Result JoinGameCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());

				return hr;

			}; // Result JoinGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InInsUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InInsUID);

				return hr;
			}; // MessageData* JoinGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )



			Result JoinGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGame:{0}:{1} , TransactionID:{2}, PlayerID:{3}, Ticket:{4}, InsUID:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayerID(), parser.GetTicket(), parser.GetInsUID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinGameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 44);
			Result JoinGameRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_InsUID);
				protocolCheck(*input >> m_TimeStamp);
				protocolCheck(*input >> m_GameState);
				protocolCheck(*input >> m_Day);
				protocolCheck(*input >> m_MaxPlayer);
				protocolCheck(*input >> m_PlayerIndex);
				protocolCheck(*input >> m_PlayerCharacter);
				protocolCheck(*input >> m_Role);
				protocolCheck(*input >> m_Dead);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatHistoryDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatHistoryDataPtr, ArrayLen));
				m_ChatHistoryData.SetLinkedBuffer(ArrayLen, ChatHistoryDataPtr);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* GameLogDataPtr = nullptr;
				protocolCheck(input->ReadLink(GameLogDataPtr, ArrayLen));
				m_GameLogData.SetLinkedBuffer(ArrayLen, GameLogDataPtr);

				return hr;

			}; // Result JoinGameRes::ParseMessage(const MessageData* pIMsg)

			Result JoinGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

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

				return hr;

			}; // Result JoinGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInChatHistoryData = (uint16_t)InChatHistoryData.size(); 
				uint16_t numberOfInGameLogData = (uint16_t)InGameLogData.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InInsUID)
					+ SerializedSizeOf(InTimeStamp)
					+ SerializedSizeOf(InGameState)
					+ SerializedSizeOf(InDay)
					+ SerializedSizeOf(InMaxPlayer)
					+ SerializedSizeOf(InPlayerIndex)
					+ SerializedSizeOf(InPlayerCharacter)
					+ SerializedSizeOf(InRole)
					+ SerializedSizeOf(InDead)
					+ SerializedSizeOf(InChatHistoryData)
					+ SerializedSizeOf(InGameLogData)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InInsUID);
				protocolCheck(*output << InTimeStamp);
				protocolCheck(*output << InGameState);
				protocolCheck(*output << InDay);
				protocolCheck(*output << InMaxPlayer);
				protocolCheck(*output << InPlayerIndex);
				protocolCheck(*output << InPlayerCharacter);
				protocolCheck(*output << InRole);
				protocolCheck(*output << InDead);
				protocolCheck(*output << InChatHistoryData);
				protocolCheck(*output << InGameLogData);

				return hr;
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
			const MessageID PlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 45);
			Result PlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_JoinedPlayer);

				return hr;

			}; // Result PlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerJoinedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());

				return hr;

			}; // Result PlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerJoinedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InJoinedPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerJoinedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InJoinedPlayer);

				return hr;
			}; // MessageData* PlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer )



			Result PlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerJoinedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerJoined:{0}:{1} , GameInsUID:{2}, JoinedPlayer:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetJoinedPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Leave Game
			const MessageID LeaveGameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 46);
			Result LeaveGameCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Ticket);

				return hr;

			}; // Result LeaveGameCmd::ParseMessage(const MessageData* pIMsg)

			Result LeaveGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());

				return hr;

			}; // Result LeaveGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeaveGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTicket)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTicket);

				return hr;
			}; // MessageData* LeaveGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result LeaveGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveGameCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveGame:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LeaveGameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 46);
			Result LeaveGameRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeaveGameRes::ParseMessage(const MessageData* pIMsg)

			Result LeaveGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeaveGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeaveGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID PlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 47);
			Result PlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_LeftPlayerID);

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InLeftPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerLeftS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InLeftPlayerID);

				return hr;
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
			const MessageID KickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 48);
			Result KickPlayerCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerToKick);

				return hr;

			}; // Result KickPlayerCmd::ParseMessage(const MessageData* pIMsg)

			Result KickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				KickPlayerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());

				return hr;

			}; // Result KickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result KickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) KickPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result KickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* KickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerToKick)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::KickPlayerCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerToKick);

				return hr;
			}; // MessageData* KickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )



			Result KickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				KickPlayerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "KickPlayer:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, PlayerToKick:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetPlayerToKick()); 
				return ResultCode::SUCCESS;
			}; // Result KickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID KickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 48);
			Result KickPlayerRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result KickPlayerRes::ParseMessage(const MessageData* pIMsg)

			Result KickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				KickPlayerRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result KickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result KickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) KickPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result KickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* KickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::KickPlayerRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID PlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 49);
			Result PlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerKickedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerKickedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InKickedPlayerID);

				return hr;
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
			const MessageID AssignRoleCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 50);
			Result AssignRoleCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Ticket);

				return hr;

			}; // Result AssignRoleCmd::ParseMessage(const MessageData* pIMsg)

			Result AssignRoleCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AssignRoleCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());

				return hr;

			}; // Result AssignRoleCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AssignRoleCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AssignRoleCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AssignRoleCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AssignRoleCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTicket)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AssignRoleCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTicket);

				return hr;
			}; // MessageData* AssignRoleCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result AssignRoleCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AssignRoleCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AssignRole:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result AssignRoleCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID AssignRoleRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 50);
			Result AssignRoleRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result AssignRoleRes::ParseMessage(const MessageData* pIMsg)

			Result AssignRoleRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AssignRoleRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result AssignRoleRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AssignRoleRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AssignRoleRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AssignRoleRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AssignRoleRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AssignRoleRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID RoleAssignedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 51);
			Result RoleAssignedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Role);

				return hr;

			}; // Result RoleAssignedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result RoleAssignedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RoleAssignedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Role", parser.GetRole());

				return hr;

			}; // Result RoleAssignedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RoleAssignedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RoleAssignedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RoleAssignedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RoleAssignedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InRole)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RoleAssignedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InRole);

				return hr;
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
			const MessageID ChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 52);
			Result ChatMessageCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));
				protocolCheck(*input >> m_Role);

				return hr;

			}; // Result ChatMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result ChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());
				variableBuilder.SetVariable("Role", parser.GetRole());

				return hr;

			}; // Result ChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage, const uint8_t &InRole )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatMessage)
					+ SerializedSizeOf(InRole)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatMessage);
				protocolCheck(*output << InRole);

				return hr;
			}; // MessageData* ChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage, const uint8_t &InRole )



			Result ChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatMessage:{0}:{1} , TransactionID:{2}, ChatMessage:{3,60}, Role:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatMessage(), parser.GetRole()); 
				return ResultCode::SUCCESS;
			}; // Result ChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 52);
			Result ChatMessageRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ChatMessageRes::ParseMessage(const MessageData* pIMsg)

			Result ChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatMessageRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID ChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 53);
			Result ChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(*input >> m_Role);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SenderName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result ChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("Role", parser.GetRole());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InRole)
					+ SerializedSizeOf(InSenderName)
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InRole);
				protocolCheck(*output << InSenderName);
				protocolCheck(*output << InChatMessage);

				return hr;
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
			const MessageID AdvanceGameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 54);
			Result AdvanceGameCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Ticket);

				return hr;

			}; // Result AdvanceGameCmd::ParseMessage(const MessageData* pIMsg)

			Result AdvanceGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AdvanceGameCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());

				return hr;

			}; // Result AdvanceGameCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AdvanceGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AdvanceGameCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AdvanceGameCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AdvanceGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTicket)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AdvanceGameCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTicket);

				return hr;
			}; // MessageData* AdvanceGameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result AdvanceGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				AdvanceGameCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "AdvanceGame:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result AdvanceGameCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID AdvanceGameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 54);
			Result AdvanceGameRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result AdvanceGameRes::ParseMessage(const MessageData* pIMsg)

			Result AdvanceGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AdvanceGameRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result AdvanceGameRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AdvanceGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AdvanceGameRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AdvanceGameRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* AdvanceGameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AdvanceGameRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID GameAdvancedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 55);
			Result GameAdvancedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_TimeStamp);
				protocolCheck(*input >> m_GameState);
				protocolCheck(*input >> m_Day);

				return hr;

			}; // Result GameAdvancedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameAdvancedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameAdvancedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());
				variableBuilder.SetVariable("GameState", (int)parser.GetGameState());
				variableBuilder.SetVariable("Day", parser.GetDay());

				return hr;

			}; // Result GameAdvancedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameAdvancedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameAdvancedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameAdvancedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameAdvancedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InTimeStamp)
					+ SerializedSizeOf(InGameState)
					+ SerializedSizeOf(InDay)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameAdvancedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InTimeStamp);
				protocolCheck(*output << InGameState);
				protocolCheck(*output << InDay);

				return hr;
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
			const MessageID GameEndedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 56);
			Result GameEndedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_Winner);
				protocolCheck(*input >> m_GainedExp);
				protocolCheck(*input >> m_GainedGameMoney);

				return hr;

			}; // Result GameEndedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameEndedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameEndedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Winner", (int)parser.GetWinner());
				variableBuilder.SetVariable("GainedExp", parser.GetGainedExp());
				variableBuilder.SetVariable("GainedGameMoney", parser.GetGainedGameMoney());

				return hr;

			}; // Result GameEndedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameEndedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameEndedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameEndedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameEndedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InWinner)
					+ SerializedSizeOf(InGainedExp)
					+ SerializedSizeOf(InGainedGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameEndedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InWinner);
				protocolCheck(*output << InGainedExp);
				protocolCheck(*output << InGainedGameMoney);

				return hr;
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
			const MessageID VoteGameAdvanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 57);
			Result VoteGameAdvanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Ticket);

				return hr;

			}; // Result VoteGameAdvanceCmd::ParseMessage(const MessageData* pIMsg)

			Result VoteGameAdvanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				VoteGameAdvanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());

				return hr;

			}; // Result VoteGameAdvanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteGameAdvanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) VoteGameAdvanceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result VoteGameAdvanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* VoteGameAdvanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTicket)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteGameAdvanceCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTicket);

				return hr;
			}; // MessageData* VoteGameAdvanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )



			Result VoteGameAdvanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VoteGameAdvanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "VoteGameAdvance:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result VoteGameAdvanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID VoteGameAdvanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 57);
			Result VoteGameAdvanceRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result VoteGameAdvanceRes::ParseMessage(const MessageData* pIMsg)

			Result VoteGameAdvanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				VoteGameAdvanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result VoteGameAdvanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteGameAdvanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) VoteGameAdvanceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result VoteGameAdvanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* VoteGameAdvanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteGameAdvanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID GameAdvanceVotedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 58);
			Result GameAdvanceVotedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_Voter);

				return hr;

			}; // Result GameAdvanceVotedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameAdvanceVotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameAdvanceVotedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Voter", parser.GetVoter());

				return hr;

			}; // Result GameAdvanceVotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameAdvanceVotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameAdvanceVotedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameAdvanceVotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameAdvanceVotedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InVoter )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InVoter)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameAdvanceVotedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InVoter);

				return hr;
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
			const MessageID VoteCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 59);
			Result VoteCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_VoteTarget);
				protocolCheck(*input >> m_ActionSerial);

				return hr;

			}; // Result VoteCmd::ParseMessage(const MessageData* pIMsg)

			Result VoteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				VoteCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("VoteTarget", parser.GetVoteTarget());
				variableBuilder.SetVariable("ActionSerial", parser.GetActionSerial());

				return hr;

			}; // Result VoteCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) VoteCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result VoteCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* VoteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InVoteTarget)
					+ SerializedSizeOf(InActionSerial)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InVoteTarget);
				protocolCheck(*output << InActionSerial);

				return hr;
			}; // MessageData* VoteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )



			Result VoteCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				VoteCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Vote:{0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}, Ticket:{5}, VoteTarget:{6}, ActionSerial:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetTicket(), parser.GetVoteTarget(), parser.GetActionSerial()); 
				return ResultCode::SUCCESS;
			}; // Result VoteCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID VoteRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 59);
			Result VoteRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result VoteRes::ParseMessage(const MessageData* pIMsg)

			Result VoteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				VoteRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result VoteRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) VoteRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result VoteRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* VoteRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID VotedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 60);
			Result VotedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_Voter);
				protocolCheck(*input >> m_VotedTarget);

				return hr;

			}; // Result VotedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result VotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				VotedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Voter", parser.GetVoter());
				variableBuilder.SetVariable("VotedTarget", parser.GetVotedTarget());

				return hr;

			}; // Result VotedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) VotedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result VotedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* VotedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InVoter)
					+ SerializedSizeOf(InVotedTarget)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VotedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InVoter);
				protocolCheck(*output << InVotedTarget);

				return hr;
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
			const MessageID VoteEndS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 61);
			Result VoteEndS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(input->Read(ArrayLen));
				AccountID* VotedPtr = nullptr;
				protocolCheck(input->ReadLink(VotedPtr, ArrayLen));
				m_Voted.SetLinkedBuffer(ArrayLen, VotedPtr);

				return hr;

			}; // Result VoteEndS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result VoteEndS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				VoteEndS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("Voted", parser.GetVoted());

				return hr;

			}; // Result VoteEndS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result VoteEndS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) VoteEndS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result VoteEndS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* VoteEndS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const Array<AccountID>& InVoted )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInVoted = (uint16_t)InVoted.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InVoted)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::VoteEndS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InVoted);

				return hr;
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
			const MessageID PlayerKilledS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 62);
			Result PlayerKilledS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_KilledPlayer);
				protocolCheck(*input >> m_Reason);

				return hr;

			}; // Result PlayerKilledS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerKilledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerKilledS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("KilledPlayer", parser.GetKilledPlayer());
				variableBuilder.SetVariable("Reason", (int)parser.GetReason());

				return hr;

			}; // Result PlayerKilledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerKilledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerKilledS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerKilledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerKilledS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InKilledPlayer)
					+ SerializedSizeOf(InReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerKilledS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InKilledPlayer);
				protocolCheck(*output << InReason);

				return hr;
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
			const MessageID PlayerRevealedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 63);
			Result PlayerRevealedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_RevealedPlayerID);
				protocolCheck(*input >> m_Role);
				protocolCheck(*input >> m_Reason);

				return hr;

			}; // Result PlayerRevealedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerRevealedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerRevealedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("RevealedPlayerID", parser.GetRevealedPlayerID());
				variableBuilder.SetVariable("Role", parser.GetRole());
				variableBuilder.SetVariable("Reason", (int)parser.GetReason());

				return hr;

			}; // Result PlayerRevealedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerRevealedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerRevealedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerRevealedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerRevealedS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InRevealedPlayerID)
					+ SerializedSizeOf(InRole)
					+ SerializedSizeOf(InReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PlayerRevealedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InRevealedPlayerID);
				protocolCheck(*output << InRole);
				protocolCheck(*output << InReason);

				return hr;
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
			const MessageID GamePlayAgainCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 64);
			Result GamePlayAgainCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GamePlayAgainCmd::ParseMessage(const MessageData* pIMsg)

			Result GamePlayAgainCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayAgainCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GamePlayAgainCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayAgainCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayAgainCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayAgainCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayAgainCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayAgainCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GamePlayAgainCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GamePlayAgainCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayAgainCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayAgain:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayAgainCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GamePlayAgainRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 64);
			Result GamePlayAgainRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result GamePlayAgainRes::ParseMessage(const MessageData* pIMsg)

			Result GamePlayAgainRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayAgainRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result GamePlayAgainRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayAgainRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayAgainRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayAgainRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayAgainRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayAgainRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
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
			const MessageID GamePlayAgainS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 65);
			Result GamePlayAgainS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_LeadPlayer);

				return hr;

			}; // Result GamePlayAgainS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GamePlayAgainS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayAgainS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("LeadPlayer", parser.GetLeadPlayer());

				return hr;

			}; // Result GamePlayAgainS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayAgainS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayAgainS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayAgainS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayAgainS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InLeadPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InLeadPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayAgainS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InLeadPlayer);

				return hr;
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
			const MessageID GameRevealPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 66);
			Result GameRevealPlayerCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				AccountID* TargetPlayerIDPtr = nullptr;
				protocolCheck(input->ReadLink(TargetPlayerIDPtr, ArrayLen));
				m_TargetPlayerID.SetLinkedBuffer(ArrayLen, TargetPlayerIDPtr);

				return hr;

			}; // Result GameRevealPlayerCmd::ParseMessage(const MessageData* pIMsg)

			Result GameRevealPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameRevealPlayerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayerID", parser.GetTargetPlayerID());

				return hr;

			}; // Result GameRevealPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameRevealPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameRevealPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameRevealPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameRevealPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInTargetPlayerID = (uint16_t)InTargetPlayerID.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTargetPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameRevealPlayerCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTargetPlayerID);

				return hr;
			}; // MessageData* GameRevealPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )



			Result GameRevealPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GameRevealPlayerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GameRevealPlayer:{0}:{1} , TransactionID:{2}, TargetPlayerID:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTargetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result GameRevealPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GameRevealPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 66);
			Result GameRevealPlayerRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				AccountID* RevealedPlayerIDPtr = nullptr;
				protocolCheck(input->ReadLink(RevealedPlayerIDPtr, ArrayLen));
				m_RevealedPlayerID.SetLinkedBuffer(ArrayLen, RevealedPlayerIDPtr);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* RevealedRolePtr = nullptr;
				protocolCheck(input->ReadLink(RevealedRolePtr, ArrayLen));
				m_RevealedRole.SetLinkedBuffer(ArrayLen, RevealedRolePtr);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result GameRevealPlayerRes::ParseMessage(const MessageData* pIMsg)

			Result GameRevealPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameRevealPlayerRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("RevealedPlayerID", parser.GetRevealedPlayerID());
				variableBuilder.SetVariable("RevealedRole", parser.GetRevealedRole());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result GameRevealPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameRevealPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameRevealPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameRevealPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameRevealPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<AccountID>& InRevealedPlayerID, const Array<uint8_t>& InRevealedRole, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInRevealedPlayerID = (uint16_t)InRevealedPlayerID.size(); 
				uint16_t numberOfInRevealedRole = (uint16_t)InRevealedRole.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InRevealedPlayerID)
					+ SerializedSizeOf(InRevealedRole)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameRevealPlayerRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InRevealedPlayerID);
				protocolCheck(*output << InRevealedRole);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
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
			const MessageID GamePlayerReviveCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 67);
			Result GamePlayerReviveCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GamePlayerReviveCmd::ParseMessage(const MessageData* pIMsg)

			Result GamePlayerReviveCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayerReviveCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GamePlayerReviveCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerReviveCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayerReviveCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayerReviveCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayerReviveCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerReviveCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GamePlayerReviveCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GamePlayerReviveCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayerReviveCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayerRevive:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayerReviveCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GamePlayerReviveRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 67);
			Result GamePlayerReviveRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result GamePlayerReviveRes::ParseMessage(const MessageData* pIMsg)

			Result GamePlayerReviveRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayerReviveRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result GamePlayerReviveRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerReviveRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayerReviveRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayerReviveRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayerReviveRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerReviveRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
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
			const MessageID GamePlayerRevivedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 68);
			Result GamePlayerRevivedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_RevivedPlayerID);

				return hr;

			}; // Result GamePlayerRevivedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GamePlayerRevivedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayerRevivedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RevivedPlayerID", parser.GetRevivedPlayerID());

				return hr;

			}; // Result GamePlayerRevivedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerRevivedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayerRevivedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayerRevivedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayerRevivedS2CEvt::Create( IHeap& memHeap, const AccountID &InRevivedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InRevivedPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerRevivedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InRevivedPlayerID);

				return hr;
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
			const MessageID GamePlayerResetRankCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 69);
			Result GamePlayerResetRankCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GamePlayerResetRankCmd::ParseMessage(const MessageData* pIMsg)

			Result GamePlayerResetRankCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayerResetRankCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GamePlayerResetRankCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerResetRankCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayerResetRankCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayerResetRankCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayerResetRankCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerResetRankCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GamePlayerResetRankCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GamePlayerResetRankCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GamePlayerResetRankCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GamePlayerResetRank:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GamePlayerResetRankCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GamePlayerResetRankRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 69);
			Result GamePlayerResetRankRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result GamePlayerResetRankRes::ParseMessage(const MessageData* pIMsg)

			Result GamePlayerResetRankRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GamePlayerResetRankRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result GamePlayerResetRankRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GamePlayerResetRankRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GamePlayerResetRankRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GamePlayerResetRankRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GamePlayerResetRankRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GamePlayerResetRankRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
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
			const MessageID RequestGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 70);
			Result RequestGameMatchCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NumPlayer);
				protocolCheck(*input >> m_RequestRole);

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessage(const MessageData* pIMsg)

			Result RequestGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestGameMatchCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NumPlayer", parser.GetNumPlayer());
				variableBuilder.SetVariable("RequestRole", parser.GetRequestRole());

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestGameMatchCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RequestGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNumPlayer)
					+ SerializedSizeOf(InRequestRole)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestGameMatchCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNumPlayer);
				protocolCheck(*output << InRequestRole);

				return hr;
			}; // MessageData* RequestGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )



			Result RequestGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RequestGameMatchCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RequestGameMatch:{0}:{1} , TransactionID:{2}, NumPlayer:{3}, RequestRole:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetNumPlayer(), parser.GetRequestRole()); 
				return ResultCode::SUCCESS;
			}; // Result RequestGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID RequestGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 70);
			Result RequestGameMatchRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result RequestGameMatchRes::ParseMessage(const MessageData* pIMsg)

			Result RequestGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestGameMatchRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result RequestGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestGameMatchRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* RequestGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestGameMatchRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
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
			const MessageID GameMatchedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 71);
			Result GameMatchedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_InsUID);
				protocolCheck(*input >> m_TimeStamp);
				protocolCheck(*input >> m_GameState);
				protocolCheck(*input >> m_Day);
				protocolCheck(*input >> m_MaxPlayer);
				protocolCheck(*input >> m_PlayerIndex);
				protocolCheck(*input >> m_PlayerCharacter);
				protocolCheck(*input >> m_Role);
				protocolCheck(*input >> m_Dead);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatHistoryDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatHistoryDataPtr, ArrayLen));
				m_ChatHistoryData.SetLinkedBuffer(ArrayLen, ChatHistoryDataPtr);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* GameLogDataPtr = nullptr;
				protocolCheck(input->ReadLink(GameLogDataPtr, ArrayLen));
				m_GameLogData.SetLinkedBuffer(ArrayLen, GameLogDataPtr);
				protocolCheck(*input >> m_Stamina);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameMatchedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

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

				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameMatchedS2CEvt::Create( IHeap& memHeap, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInChatHistoryData = (uint16_t)InChatHistoryData.size(); 
				uint16_t numberOfInGameLogData = (uint16_t)InGameLogData.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InInsUID)
					+ SerializedSizeOf(InTimeStamp)
					+ SerializedSizeOf(InGameState)
					+ SerializedSizeOf(InDay)
					+ SerializedSizeOf(InMaxPlayer)
					+ SerializedSizeOf(InPlayerIndex)
					+ SerializedSizeOf(InPlayerCharacter)
					+ SerializedSizeOf(InRole)
					+ SerializedSizeOf(InDead)
					+ SerializedSizeOf(InChatHistoryData)
					+ SerializedSizeOf(InGameLogData)
					+ SerializedSizeOf(InStamina)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InInsUID);
				protocolCheck(*output << InTimeStamp);
				protocolCheck(*output << InGameState);
				protocolCheck(*output << InDay);
				protocolCheck(*output << InMaxPlayer);
				protocolCheck(*output << InPlayerIndex);
				protocolCheck(*output << InPlayerCharacter);
				protocolCheck(*output << InRole);
				protocolCheck(*output << InDead);
				protocolCheck(*output << InChatHistoryData);
				protocolCheck(*output << InGameLogData);
				protocolCheck(*output << InStamina);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
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
			const MessageID GameMatchFailedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 72);
			Result GameMatchFailedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_FailedReason);

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameMatchFailedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchFailedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("FailedReason", parser.GetFailedReason());

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchFailedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameMatchFailedS2CEvt::Create( IHeap& memHeap, const Result &InFailedReason )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InFailedReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchFailedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InFailedReason);

				return hr;
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
			const MessageID GameMatchingStartedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 73);
			Result GameMatchingStartedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);



				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameMatchingStartedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchingStartedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));


				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchingStartedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameMatchingStartedS2CEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchingStartedS2CEvt::MID, __uiMessageSize ) );

				return hr;
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
			const MessageID CancelGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 74);
			Result CancelGameMatchCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessage(const MessageData* pIMsg)

			Result CancelGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CancelGameMatchCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CancelGameMatchCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CancelGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CancelGameMatchCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* CancelGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result CancelGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CancelGameMatchCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CancelGameMatch:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result CancelGameMatchCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CancelGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 74);
			Result CancelGameMatchRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result CancelGameMatchRes::ParseMessage(const MessageData* pIMsg)

			Result CancelGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CancelGameMatchRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result CancelGameMatchRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CancelGameMatchRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CancelGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CancelGameMatchRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID GameMatchingCanceledS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 75);
			Result GameMatchingCanceledS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);



				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameMatchingCanceledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchingCanceledS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));


				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchingCanceledS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GameMatchingCanceledS2CEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchingCanceledS2CEvt::MID, __uiMessageSize ) );

				return hr;
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
			const MessageID BuyShopItemPrepareCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 76);
			Result BuyShopItemPrepareCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ShopItemID);

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessage(const MessageData* pIMsg)

			Result BuyShopItemPrepareCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemPrepareCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemPrepareCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* BuyShopItemPrepareCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InShopItemID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemPrepareCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InShopItemID);

				return hr;
			}; // MessageData* BuyShopItemPrepareCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID )



			Result BuyShopItemPrepareCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				BuyShopItemPrepareCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "BuyShopItemPrepare:{0}:{1} , TransactionID:{2}, ShopItemID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetShopItemID()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemPrepareCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID BuyShopItemPrepareRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 76);
			Result BuyShopItemPrepareRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ShopItemID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PurchaseID, ArrayLen));

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessage(const MessageData* pIMsg)

			Result BuyShopItemPrepareRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemPrepareRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());
				variableBuilder.SetVariable("PurchaseID", parser.GetPurchaseID());

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemPrepareRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* BuyShopItemPrepareRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InShopItemID)
					+ SerializedSizeOf(InPurchaseID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemPrepareRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InShopItemID);
				protocolCheck(*output << InPurchaseID);

				return hr;
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
			const MessageID BuyShopItemCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 77);
			Result BuyShopItemCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ShopItemID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_Platform, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PackageName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PurchaseTransactionID, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PurchaseTokenPtr = nullptr;
				protocolCheck(input->ReadLink(PurchaseTokenPtr, ArrayLen));
				m_PurchaseToken.SetLinkedBuffer(ArrayLen, PurchaseTokenPtr);

				return hr;

			}; // Result BuyShopItemCmd::ParseMessage(const MessageData* pIMsg)

			Result BuyShopItemCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());
				variableBuilder.SetVariable("Platform", parser.GetPlatform());
				variableBuilder.SetVariable("PackageName", parser.GetPackageName());
				variableBuilder.SetVariable("PurchaseTransactionID", parser.GetPurchaseTransactionID());
				variableBuilder.SetVariable("PurchaseToken", parser.GetPurchaseToken());

				return hr;

			}; // Result BuyShopItemCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* BuyShopItemCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInPurchaseToken = (uint16_t)InPurchaseToken.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InShopItemID)
					+ SerializedSizeOf(InPlatform)
					+ SerializedSizeOf(InPackageName)
					+ SerializedSizeOf(InPurchaseTransactionID)
					+ SerializedSizeOf(InPurchaseToken)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InShopItemID);
				protocolCheck(*output << InPlatform);
				protocolCheck(*output << InPackageName);
				protocolCheck(*output << InPurchaseTransactionID);
				protocolCheck(*output << InPurchaseToken);

				return hr;
			}; // MessageData* BuyShopItemCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )



			Result BuyShopItemCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				BuyShopItemCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "BuyShopItem:{0}:{1} , TransactionID:{2}, ShopItemID:{3}, Platform:{4,60}, PackageName:{5,60}, PurchaseTransactionID:{6,60}, PurchaseToken:{7,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetShopItemID(), parser.GetPlatform(), parser.GetPackageName(), parser.GetPurchaseTransactionID(), parser.GetPurchaseToken()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID BuyShopItemRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 77);
			Result BuyShopItemRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ShopItemID);

				return hr;

			}; // Result BuyShopItemRes::ParseMessage(const MessageData* pIMsg)

			Result BuyShopItemRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());

				return hr;

			}; // Result BuyShopItemRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* BuyShopItemRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InShopItemID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InShopItemID);

				return hr;
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
			const MessageID CreateOrJoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 78);
			Result CreateOrJoinChatChannelCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChannelName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_Passcode, ArrayLen));

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessage(const MessageData* pIMsg)

			Result CreateOrJoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateOrJoinChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChannelName", parser.GetChannelName());
				variableBuilder.SetVariable("Passcode", parser.GetPasscode());

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateOrJoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChannelName)
					+ SerializedSizeOf(InPasscode)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateOrJoinChatChannelCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChannelName);
				protocolCheck(*output << InPasscode);

				return hr;
			}; // MessageData* CreateOrJoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )



			Result CreateOrJoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateOrJoinChatChannelCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateOrJoinChatChannel:{0}:{1} , TransactionID:{2}, ChannelName:{3,60}, Passcode:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChannelName(), parser.GetPasscode()); 
				return ResultCode::SUCCESS;
			}; // Result CreateOrJoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CreateOrJoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 78);
			Result CreateOrJoinChatChannelRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ChatUID);

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessage(const MessageData* pIMsg)

			Result CreateOrJoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateOrJoinChatChannelRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateOrJoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InChatUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateOrJoinChatChannelRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InChatUID);

				return hr;
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
			const MessageID JoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 79);
			Result JoinChatChannelCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_InviterID);

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinChatChannelCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InInviterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InInviterID);

				return hr;
			}; // MessageData* JoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )



			Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinChatChannelCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinChatChannel:{0}:{1} , TransactionID:{2}, ChatUID:{3}, InviterID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetInviterID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 79);
			Result JoinChatChannelRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PartyLeaderID);

				return hr;

			}; // Result JoinChatChannelRes::ParseMessage(const MessageData* pIMsg)

			Result JoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinChatChannelRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());

				return hr;

			}; // Result JoinChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinChatChannelRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPartyLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPartyLeaderID);

				return hr;
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
			const MessageID ChatChannelPlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 80);
			Result ChatChannelPlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_JoinedPlayer);

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerJoinedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerJoinedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InJoinedPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerJoinedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InJoinedPlayer);

				return hr;
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
			const MessageID ChatChannelLeaderChangedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 81);
			Result ChatChannelLeaderChangedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_NewLeaderID);

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelLeaderChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelLeaderChangedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InNewLeaderID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InNewLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelLeaderChangedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InNewLeaderID);

				return hr;
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
			const MessageID LeaveChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 82);
			Result LeaveChatChannelCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessage(const MessageData* pIMsg)

			Result LeaveChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveChatChannelCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeaveChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveChatChannelCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // MessageData* LeaveChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )



			Result LeaveChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveChatChannelCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveChatChannel:{0}:{1} , TransactionID:{2}, ChatUID:{3}, PlayerID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LeaveChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 82);
			Result LeaveChatChannelRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessage(const MessageData* pIMsg)

			Result LeaveChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveChatChannelRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveChatChannelRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* LeaveChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveChatChannelRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID ChatChannelPlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 83);
			Result ChatChannelPlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_LeftPlayerID);

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InLeftPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerLeftS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InLeftPlayerID);

				return hr;
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
			const MessageID ChatChannelKickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 84);
			Result ChatChannelKickPlayerCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerToKick);

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelKickPlayerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelKickPlayerCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerToKick)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelKickPlayerCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerToKick);

				return hr;
			}; // MessageData* ChatChannelKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )



			Result ChatChannelKickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelKickPlayerCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelKickPlayer:{0}:{1} , TransactionID:{2}, ChatUID:{3}, PlayerID:{4}, PlayerToKick:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetPlayerID(), parser.GetPlayerToKick()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelKickPlayerCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ChatChannelKickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 84);
			Result ChatChannelKickPlayerRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelKickPlayerRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelKickPlayerRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelKickPlayerRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID ChatChannelPlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 85);
			Result ChatChannelPlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerKickedS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerKickedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InKickedPlayerID);

				return hr;
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
			const MessageID ChatChannelChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 86);
			Result ChatChannelChatMessageCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )



			Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelChatMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelChatMessage:{0}:{1} , TransactionID:{2}, ChatUID:{3}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ChatChannelChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 86);
			Result ChatChannelChatMessageRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
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
			const MessageID ChatChannelChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 87);
			Result ChatChannelChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SenderName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InSenderName)
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InSenderName);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )



			Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelChatMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelChatMessage:{0}:{1} , SenderID:{2}, SenderName:{3,60}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetSenderName(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Create character
			const MessageID CreateCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 88);
			const VariableTable& CreateCharacterCmd::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& CreateCharacterCmd::GetAttributes() const
			Result CreateCharacterCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_CharacterName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result CreateCharacterCmd::ParseMessage(const MessageData* pIMsg)

			Result CreateCharacterCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateCharacterCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterName", parser.GetCharacterName());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result CreateCharacterCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateCharacterCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateCharacterCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterName);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InAttributes )

			MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateCharacterCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterName);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InAttributes )



			Result CreateCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateCharacterCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateCharacter:{0}:{1} , TransactionID:{2}, CharacterName:{3,60}, Attributes:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetCharacterName(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result CreateCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CreateCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 88);
			Result CreateCharacterRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result CreateCharacterRes::ParseMessage(const MessageData* pIMsg)

			Result CreateCharacterRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateCharacterRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result CreateCharacterRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateCharacterRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateCharacterRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* CreateCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )



			Result CreateCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateCharacterRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateCharacter:{0}:{1} , TransactionID:{2}, Result:{3:X8}, CharacterID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Delete character
			const MessageID DeleteCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 89);
			Result DeleteCharacterCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessage(const MessageData* pIMsg)

			Result DeleteCharacterCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteCharacterCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteCharacterCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* DeleteCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteCharacterCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* DeleteCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )



			Result DeleteCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DeleteCharacterCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DeleteCharacter:{0}:{1} , TransactionID:{2}, CharacterID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID DeleteCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 89);
			Result DeleteCharacterRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result DeleteCharacterRes::ParseMessage(const MessageData* pIMsg)

			Result DeleteCharacterRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteCharacterRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result DeleteCharacterRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteCharacterRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* DeleteCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteCharacterRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* DeleteCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result DeleteCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DeleteCharacterRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DeleteCharacter:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Get character list
			const MessageID GetCharacterListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 90);
			Result GetCharacterListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetCharacterListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetCharacterListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetCharacterListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterListCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GetCharacterListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )



			Result GetCharacterListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetCharacterListCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetCharacterList:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetCharacterListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 90);
			Result GetCharacterListRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				uint32_t* CharacterIDsPtr = nullptr;
				protocolCheck(input->ReadLink(CharacterIDsPtr, ArrayLen));
				m_CharacterIDs.SetLinkedBuffer(ArrayLen, CharacterIDsPtr);

				return hr;

			}; // Result GetCharacterListRes::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("CharacterIDs", parser.GetCharacterIDs());

				return hr;

			}; // Result GetCharacterListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetCharacterListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint32_t>& InCharacterIDs )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t numberOfInCharacterIDs = (uint16_t)InCharacterIDs.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterIDs)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterListRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacterIDs);

				return hr;
			}; // MessageData* GetCharacterListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint32_t>& InCharacterIDs )



			Result GetCharacterListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetCharacterListRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetCharacterList:{0}:{1} , TransactionID:{2}, Result:{3:X8}, CharacterIDs:{4,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacterIDs()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: 
			const MessageID GetCharacterDataCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 91);
			Result GetCharacterDataCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterDataCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetCharacterDataCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* GetCharacterDataCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )



			Result GetCharacterDataCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetCharacterDataCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetCharacterData:{0}:{1} , TransactionID:{2}, CharacterID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetCharacterDataRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 91);
			const VariableTable& GetCharacterDataRes::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& GetCharacterDataRes::GetAttributes() const
			Result GetCharacterDataRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result GetCharacterDataRes::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterDataRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetCharacterDataRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes )

			MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )



			Result GetCharacterDataRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetCharacterDataRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetCharacterData:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Attributes:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Select character
			const MessageID SelectCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 92);
			Result SelectCharacterCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result SelectCharacterCmd::ParseMessage(const MessageData* pIMsg)

			Result SelectCharacterCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SelectCharacterCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result SelectCharacterCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SelectCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SelectCharacterCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SelectCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SelectCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SelectCharacterCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* SelectCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )



			Result SelectCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SelectCharacterCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SelectCharacter:{0}:{1} , TransactionID:{2}, CharacterID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result SelectCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID SelectCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 92);
			Result SelectCharacterRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result SelectCharacterRes::ParseMessage(const MessageData* pIMsg)

			Result SelectCharacterRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SelectCharacterRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result SelectCharacterRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SelectCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SelectCharacterRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SelectCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SelectCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SelectCharacterRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* SelectCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )



			Result SelectCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SelectCharacterRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SelectCharacter:{0}:{1} , TransactionID:{2}, Result:{3:X8}, CharacterID:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result SelectCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Give my stamina to other player
			const MessageID GiveStaminaCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 93);
			Result GiveStaminaCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_TargetPlayer);

				return hr;

			}; // Result GiveStaminaCmd::ParseMessage(const MessageData* pIMsg)

			Result GiveStaminaCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GiveStaminaCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayer", parser.GetTargetPlayer());

				return hr;

			}; // Result GiveStaminaCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GiveStaminaCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GiveStaminaCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GiveStaminaCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GiveStaminaCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InTargetPlayer )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTargetPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GiveStaminaCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTargetPlayer);

				return hr;
			}; // MessageData* GiveStaminaCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InTargetPlayer )



			Result GiveStaminaCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GiveStaminaCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GiveStamina:{0}:{1} , TransactionID:{2}, TargetPlayer:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTargetPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result GiveStaminaCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GiveStaminaRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 93);
			Result GiveStaminaRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TargetPlayer);
				protocolCheck(*input >> m_TimeStamp);

				return hr;

			}; // Result GiveStaminaRes::ParseMessage(const MessageData* pIMsg)

			Result GiveStaminaRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GiveStaminaRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TargetPlayer", parser.GetTargetPlayer());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());

				return hr;

			}; // Result GiveStaminaRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GiveStaminaRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GiveStaminaRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GiveStaminaRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GiveStaminaRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InTargetPlayer, const uint64_t &InTimeStamp )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTargetPlayer)
					+ SerializedSizeOf(InTimeStamp)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GiveStaminaRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTargetPlayer);
				protocolCheck(*output << InTimeStamp);

				return hr;
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
			const MessageID SetPresetGameConfigIDCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 94);
			Result SetPresetGameConfigIDCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PresetID);

				return hr;

			}; // Result SetPresetGameConfigIDCmd::ParseMessage(const MessageData* pIMsg)

			Result SetPresetGameConfigIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetPresetGameConfigIDCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PresetID", parser.GetPresetID());

				return hr;

			}; // Result SetPresetGameConfigIDCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetPresetGameConfigIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetPresetGameConfigIDCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetPresetGameConfigIDCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetPresetGameConfigIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InPresetID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPresetID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetPresetGameConfigIDCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPresetID);

				return hr;
			}; // MessageData* SetPresetGameConfigIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InPresetID )



			Result SetPresetGameConfigIDCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetPresetGameConfigIDCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetPresetGameConfigID:{0}:{1} , TransactionID:{2}, PresetID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPresetID()); 
				return ResultCode::SUCCESS;
			}; // Result SetPresetGameConfigIDCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID SetPresetGameConfigIDRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 94);
			Result SetPresetGameConfigIDRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result SetPresetGameConfigIDRes::ParseMessage(const MessageData* pIMsg)

			Result SetPresetGameConfigIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetPresetGameConfigIDRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result SetPresetGameConfigIDRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetPresetGameConfigIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetPresetGameConfigIDRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetPresetGameConfigIDRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* SetPresetGameConfigIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetPresetGameConfigIDRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* SetPresetGameConfigIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result SetPresetGameConfigIDRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SetPresetGameConfigIDRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SetPresetGameConfigID:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result SetPresetGameConfigIDRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)



		}; // namespace Game
	}; // namespace Message
}; // namespace SF



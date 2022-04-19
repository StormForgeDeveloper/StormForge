////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Game Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/GameMsgClass.h"



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

			Result HeartbeatC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				HeartbeatC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));


				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result HeartbeatC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) HeartbeatC2SEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);

				return hr;

			}; // Result JoinGameServerCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinGameServerCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameServerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result JoinGameServerCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameServerCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result JoinGameServerRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
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
				variableBuilder.SetVariable("MatchingTicket", "MatchingQueueTicket", parser.GetMatchingTicket());

				return hr;

			}; // Result JoinGameServerRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameServerRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessage(const MessageData* pIMsg)

			Result GetComplitionStateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetComplitionStateCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetComplitionStateCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ComplitionState, ArrayLen));

				return hr;

			}; // Result GetComplitionStateRes::ParseMessage(const MessageData* pIMsg)

			Result GetComplitionStateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetComplitionStateRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());

				return hr;

			}; // Result GetComplitionStateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetComplitionStateRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ComplitionState, ArrayLen));

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessage(const MessageData* pIMsg)

			Result SetComplitionStateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetComplitionStateCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetComplitionStateCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result SetComplitionStateRes::ParseMessage(const MessageData* pIMsg)

			Result SetComplitionStateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetComplitionStateRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result SetComplitionStateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetComplitionStateRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GCMRegisteredID, ArrayLen));

				return hr;

			}; // Result RegisterGCMCmd::ParseMessage(const MessageData* pIMsg)

			Result RegisterGCMCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RegisterGCMCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());

				return hr;

			}; // Result RegisterGCMCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RegisterGCMCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RegisterGCMRes::ParseMessage(const MessageData* pIMsg)

			Result RegisterGCMRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RegisterGCMRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RegisterGCMRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RegisterGCMRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GCMRegisteredID, ArrayLen));

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessage(const MessageData* pIMsg)

			Result UnregisterGCMCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnregisterGCMCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnregisterGCMCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result UnregisterGCMRes::ParseMessage(const MessageData* pIMsg)

			Result UnregisterGCMRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnregisterGCMRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result UnregisterGCMRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnregisterGCMRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result InviteFriendCmd::ParseMessage(const MessageData* pIMsg)

			Result InviteFriendCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				InviteFriendCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result InviteFriendCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) InviteFriendCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result InviteFriendRes::ParseMessage(const MessageData* pIMsg)

			Result InviteFriendRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				InviteFriendRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result InviteFriendRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) InviteFriendRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InviterID);
				protocolCheck(*input >> m_InviterFacebookUID);

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessage(const MessageData* pIMsg)

			Result AcceptFriendRequestCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptFriendRequestCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterFacebookUID", parser.GetInviterFacebookUID());

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptFriendRequestCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NewFriend);

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessage(const MessageData* pIMsg)

			Result AcceptFriendRequestRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptFriendRequestRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NewFriend", "FriendInformation", parser.GetNewFriend());

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptFriendRequestRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_Accepter);

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result FriendRequestAcceptedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FriendRequestAcceptedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Accepter", "FriendInformation", parser.GetAccepter());

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FriendRequestAcceptedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result RemoveFriendCmd::ParseMessage(const MessageData* pIMsg)

			Result RemoveFriendCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemoveFriendCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result RemoveFriendCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveFriendCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result RemoveFriendRes::ParseMessage(const MessageData* pIMsg)

			Result RemoveFriendRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemoveFriendRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result RemoveFriendRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveFriendRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result FriendRemovedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FriendRemovedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FriendRemovedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_StartIndex);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result GetFriendListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetFriendListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetFriendListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("StartIndex", parser.GetStartIndex());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result GetFriendListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetFriendListCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result GetFriendListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
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

			}; // Result GetFriendListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetFriendListRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetNotificationListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetNotificationListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetNotificationListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetNotificationListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetNotificationListCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result GetNotificationListRes::ParseMessage(const MessageData* pIMsg)

			Result GetNotificationListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetNotificationListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result GetNotificationListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetNotificationListRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessage(const MessageData* pIMsg)

			Result DeleteNotificationCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteNotificationCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteNotificationCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result DeleteNotificationRes::ParseMessage(const MessageData* pIMsg)

			Result DeleteNotificationRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteNotificationRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result DeleteNotificationRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteNotificationRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessage(const MessageData* pIMsg)

			Result SetNotificationReadCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNotificationReadCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNotificationReadCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result SetNotificationReadRes::ParseMessage(const MessageData* pIMsg)

			Result SetNotificationReadRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNotificationReadRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result SetNotificationReadRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNotificationReadRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessage(const MessageData* pIMsg)

			Result AcceptNotificationCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptNotificationCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptNotificationCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result AcceptNotificationRes::ParseMessage(const MessageData* pIMsg)

			Result AcceptNotificationRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptNotificationRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result AcceptNotificationRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptNotificationRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result NotifyS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
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

			}; // Result NotifyS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NotifyS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlayerEMail, ArrayLen));

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByEMailCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByEMailCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerEMail", parser.GetPlayerEMail());

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByEMailCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_Player);

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByEMailRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByEMailRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", "PlayerInformation", parser.GetPlayer());

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByEMailRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByPlayerIDCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlayerIDCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_Player);

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessage(const MessageData* pIMsg)

			Result FindPlayerByPlayerIDRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlayerIDRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", "PlayerInformation", parser.GetPlayer());

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result RequestPlayerStatusUpdateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestPlayerStatusUpdateCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayerID", parser.GetTargetPlayerID());

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessage(const MessageData* pIMsg)

			Result RequestPlayerStatusUpdateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestPlayerStatusUpdateRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_LatestActiveTime);
				protocolCheck(*input >> m_IsInGame);

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				NotifyPlayerStatusUpdatedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("LatestActiveTime", parser.GetLatestActiveTime());
				variableBuilder.SetVariable("IsInGame", parser.GetIsInGame());

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NotifyPlayerStatusUpdatedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			// Cmd: Get Ranking list
			const MessageID GetRankingListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 21);
			Result GetRankingListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_RankingType);
				protocolCheck(*input >> m_BaseRanking);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result GetRankingListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetRankingListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetRankingListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingType", parser.GetRankingType());
				variableBuilder.SetVariable("BaseRanking", parser.GetBaseRanking());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result GetRankingListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetRankingListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());

				return hr;

			}; // Result GetRankingListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessage(const MessageData* pIMsg)

			Result GetUserGamePlayerInfoCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetUserGamePlayerInfoCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result GetUserGamePlayerInfoRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetUserGamePlayerInfoRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessage(const MessageData* pIMsg)

			Result GetGamePlayerInfoCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetGamePlayerInfoCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetGamePlayerInfoCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result GetGamePlayerInfoRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetGamePlayerInfoRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetGamePlayerInfoRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_CurrentTotalExp);
				protocolCheck(*input >> m_CurrentLevel);

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result LevelUpS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LevelUpS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("CurrentTotalExp", parser.GetCurrentTotalExp());
				variableBuilder.SetVariable("CurrentLevel", parser.GetCurrentLevel());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LevelUpS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_NickName, ArrayLen));
				protocolCheck(*input >> m_IsCostFree);

				return hr;

			}; // Result SetNickNameCmd::ParseMessage(const MessageData* pIMsg)

			Result SetNickNameCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNickNameCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("IsCostFree", parser.GetIsCostFree());

				return hr;

			}; // Result SetNickNameCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNickNameCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result SetNickNameRes::ParseMessage(const MessageData* pIMsg)

			Result SetNickNameRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNickNameRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result SetNickNameRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNickNameRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result CreatePartyCmd::ParseMessage(const MessageData* pIMsg)

			Result CreatePartyCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreatePartyCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result CreatePartyCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreatePartyCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PartyUID);

				return hr;

			}; // Result CreatePartyRes::ParseMessage(const MessageData* pIMsg)

			Result CreatePartyRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreatePartyRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());

				return hr;

			}; // Result CreatePartyRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreatePartyRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_InviterID);

				return hr;

			}; // Result JoinPartyCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinPartyCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinPartyCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());

				return hr;

			}; // Result JoinPartyCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPartyCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result JoinPartyRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
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

			}; // Result JoinPartyRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPartyRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_JoinedPlayer);

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyPlayerJoinedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerJoinedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("JoinedPlayer", "PlayerInformation", parser.GetJoinedPlayer());

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerJoinedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_NewLeaderID);

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyLeaderChangedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyLeaderChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyLeaderChangedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result LeavePartyCmd::ParseMessage(const MessageData* pIMsg)

			Result LeavePartyCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeavePartyCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result LeavePartyCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeavePartyCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeavePartyRes::ParseMessage(const MessageData* pIMsg)

			Result LeavePartyRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeavePartyRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeavePartyRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeavePartyRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_LeftPlayerID);

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyPlayerLeftS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerLeftS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerToKick);

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyKickPlayerCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyKickPlayerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyKickPlayerCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessage(const MessageData* pIMsg)

			Result PartyKickPlayerRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyKickPlayerRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyKickPlayerRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyPlayerKickedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerKickedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InviteTargetID);

				return hr;

			}; // Result PartyInviteCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyInviteCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviteTargetID", parser.GetInviteTargetID());

				return hr;

			}; // Result PartyInviteCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyInviteRes::ParseMessage(const MessageData* pIMsg)

			Result PartyInviteRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyInviteRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_InviterID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_InviterName, ArrayLen));
				protocolCheck(*input >> m_PartyToJoinUID);

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyInviteRequestedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteRequestedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterName", parser.GetInviterName());
				variableBuilder.SetVariable("PartyToJoinUID", parser.GetPartyToJoinUID());

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteRequestedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_QuickChatID);

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyQuickChatMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessage(const MessageData* pIMsg)

			Result PartyQuickChatMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(*input >> m_QuickChatID);

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PartyQuickChatMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result PartyChatMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyChatMessageRes::ParseMessage(const MessageData* pIMsg)

			Result PartyChatMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyChatMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result PartyChatMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InsUID);

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_InsUID);
				protocolCheck(*input >> m_ServerAddress4);
				protocolCheck(*input >> m_ServerAddress6);

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result JoinGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());
				variableBuilder.SetVariable("ServerAddress4", "NetAddress", parser.GetServerAddress4());
				variableBuilder.SetVariable("ServerAddress6", "NetAddress", parser.GetServerAddress6());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const NetAddress &InServerAddress4, const NetAddress &InServerAddress6 )
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
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InInsUID)
					+ SerializedSizeOf(InServerAddress4)
					+ SerializedSizeOf(InServerAddress6)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InInsUID);
				protocolCheck(*output << InServerAddress4);
				protocolCheck(*output << InServerAddress6);

				return hr;
			}; // MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const NetAddress &InServerAddress4, const NetAddress &InServerAddress6 )

			Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameInstanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGameInstance:{0}:{1} , TransactionID:{2}, Result:{3:X8}, InsUID:{4}, ServerAddress4:{5}, ServerAddress6:{6}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetInsUID(), parser.GetServerAddress4(), parser.GetServerAddress6()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Leave game instance
			const MessageID LeaveGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 41);
			Result LeaveGameInstanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InsUID);

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result LeaveGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameInstanceCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result LeaveGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameInstanceRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SearchKeyword, ArrayLen));

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result SearchGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SearchGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("SearchKeyword", parser.GetSearchKeyword());

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SearchGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SearchGameInstanceCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(m_GameInstances));

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result SearchGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SearchGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameInstances", parser.GetGameInstances());

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SearchGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SearchGameInstanceRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* SearchGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
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
			}; // MessageData* SearchGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )

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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterDataInGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataInGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataInGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataInGameInstanceCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result GetCharacterDataInGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataInGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("GameInstances", "VariableTable", parser.GetGameInstancesRaw());

				return hr;

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataInGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataInGameInstanceRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

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

			// Cmd: Request Game match
			const MessageID RequestGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 44);
			Result RequestGameMatchCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NumPlayer);
				protocolCheck(*input >> m_RequestRole);

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessage(const MessageData* pIMsg)

			Result RequestGameMatchCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestGameMatchCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NumPlayer", parser.GetNumPlayer());
				variableBuilder.SetVariable("RequestRole", parser.GetRequestRole());

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestGameMatchCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID RequestGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 44);
			Result RequestGameMatchRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result RequestGameMatchRes::ParseMessage(const MessageData* pIMsg)

			Result RequestGameMatchRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestGameMatchRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result RequestGameMatchRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestGameMatchRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID GameMatchedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 45);
			Result GameMatchedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result GameMatchedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
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

			}; // Result GameMatchedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID GameMatchFailedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 46);
			Result GameMatchFailedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_FailedReason);

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameMatchFailedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchFailedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("FailedReason", parser.GetFailedReason());

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchFailedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID GameMatchingStartedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 47);
			Result GameMatchingStartedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);



				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameMatchingStartedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchingStartedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));


				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchingStartedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID CancelGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 48);
			Result CancelGameMatchCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessage(const MessageData* pIMsg)

			Result CancelGameMatchCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CancelGameMatchCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CancelGameMatchCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID CancelGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 48);
			Result CancelGameMatchRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result CancelGameMatchRes::ParseMessage(const MessageData* pIMsg)

			Result CancelGameMatchRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CancelGameMatchRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result CancelGameMatchRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CancelGameMatchRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID GameMatchingCanceledS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 49);
			Result GameMatchingCanceledS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);



				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result GameMatchingCanceledS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchingCanceledS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));


				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchingCanceledS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID BuyShopItemPrepareCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 50);
			Result BuyShopItemPrepareCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ShopItemID);

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessage(const MessageData* pIMsg)

			Result BuyShopItemPrepareCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemPrepareCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemPrepareCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID BuyShopItemPrepareRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 50);
			Result BuyShopItemPrepareRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result BuyShopItemPrepareRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemPrepareRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());
				variableBuilder.SetVariable("PurchaseID", parser.GetPurchaseID());

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemPrepareRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID BuyShopItemCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 51);
			Result BuyShopItemCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result BuyShopItemCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
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

			}; // Result BuyShopItemCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID BuyShopItemRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 51);
			Result BuyShopItemRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ShopItemID);

				return hr;

			}; // Result BuyShopItemRes::ParseMessage(const MessageData* pIMsg)

			Result BuyShopItemRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());

				return hr;

			}; // Result BuyShopItemRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID CreateOrJoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 52);
			Result CreateOrJoinChatChannelCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result CreateOrJoinChatChannelCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateOrJoinChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChannelName", parser.GetChannelName());
				variableBuilder.SetVariable("Passcode", parser.GetPasscode());

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID CreateOrJoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 52);
			Result CreateOrJoinChatChannelRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_ChannelLeaderID);

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessage(const MessageData* pIMsg)

			Result CreateOrJoinChatChannelRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateOrJoinChatChannelRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("ChannelLeaderID", parser.GetChannelLeaderID());

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateOrJoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
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
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InChannelLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateOrJoinChatChannelRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InChannelLeaderID);

				return hr;
			}; // MessageData* CreateOrJoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )

			Result CreateOrJoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateOrJoinChatChannelRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateOrJoinChatChannel:{0}:{1} , TransactionID:{2}, Result:{3:X8}, ChatUID:{4}, ChannelLeaderID:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetChatUID(), parser.GetChannelLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateOrJoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Join
			const MessageID JoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 53);
			Result JoinChatChannelCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_InviterID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_Passcode, ArrayLen));

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinChatChannelCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("Passcode", parser.GetPasscode());

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinChatChannelCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )
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
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InPasscode)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InInviterID);
				protocolCheck(*output << InPasscode);

				return hr;
			}; // MessageData* JoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )

			Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinChatChannelCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinChatChannel:{0}:{1} , TransactionID:{2}, ChatUID:{3}, InviterID:{4}, Passcode:{5,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetInviterID(), parser.GetPasscode()); 
				return ResultCode::SUCCESS;
			}; // Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 53);
			Result JoinChatChannelRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_ChannelLeaderID);

				return hr;

			}; // Result JoinChatChannelRes::ParseMessage(const MessageData* pIMsg)

			Result JoinChatChannelRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinChatChannelRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("ChannelLeaderID", parser.GetChannelLeaderID());

				return hr;

			}; // Result JoinChatChannelRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinChatChannelRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
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
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InChannelLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InChannelLeaderID);

				return hr;
			}; // MessageData* JoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )

			Result JoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinChatChannelRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinChatChannel:{0}:{1} , TransactionID:{2}, Result:{3:X8}, ChatUID:{4}, ChannelLeaderID:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetChatUID(), parser.GetChannelLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinChatChannelRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Joined event
			const MessageID ChatChannelPlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 54);
			Result ChatChannelPlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_JoinedPlayer);

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerJoinedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("JoinedPlayer", "PlayerInformation", parser.GetJoinedPlayer());

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerJoinedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID ChatChannelLeaderChangedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 55);
			Result ChatChannelLeaderChangedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_NewLeaderID);

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelLeaderChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelLeaderChangedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID LeaveChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 56);
			Result LeaveChatChannelCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessage(const MessageData* pIMsg)

			Result LeaveChatChannelCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveChatChannelCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID LeaveChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 56);
			Result LeaveChatChannelRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessage(const MessageData* pIMsg)

			Result LeaveChatChannelRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveChatChannelRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveChatChannelRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID ChatChannelPlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 57);
			Result ChatChannelPlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_LeftPlayerID);

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerLeftS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID ChatChannelKickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 58);
			Result ChatChannelKickPlayerCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerToKick);

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelKickPlayerCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelKickPlayerCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelKickPlayerCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID ChatChannelKickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 58);
			Result ChatChannelKickPlayerRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelKickPlayerRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelKickPlayerRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelKickPlayerRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID ChatChannelPlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 59);
			Result ChatChannelPlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerKickedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			// Cmd: Chat channel sending chatting message
			const MessageID ChatChannelChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 60);
			const VariableTable& ChatChannelChatMessageCmd::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& ChatChannelChatMessageCmd::GetChatMetaData() const
			Result ChatChannelChatMessageCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatMetaDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatMetaDataPtr, ArrayLen));
				m_ChatMetaDataRaw.SetLinkedBuffer(ArrayLen, ChatMetaDataPtr);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelChatMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelChatMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelChatMessage:{0}:{1} , TransactionID:{2}, ChatUID:{3}, ChatMetaData:{4}, ChatMessage:{5,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ChatChannelChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 60);
			Result ChatChannelChatMessageRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelChatMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID ChatChannelChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 61);
			const VariableTable& ChatChannelChatMessageS2CEvt::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& ChatChannelChatMessageS2CEvt::GetChatMetaData() const
			Result ChatChannelChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatMetaDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatMetaDataPtr, ArrayLen));
				m_ChatMetaDataRaw.SetLinkedBuffer(ArrayLen, ChatMetaDataPtr);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ChatChannelChatMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ChatChannelChatMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ChatChannelChatMessage:{0}:{1} , SenderID:{2}, ChatMetaData:{3}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Wisper(tell) other player chatting
			const MessageID WisperMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 62);
			const VariableTable& WisperMessageCmd::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& WisperMessageCmd::GetChatMetaData() const
			Result WisperMessageCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_ReceiverID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ReceiverName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatMetaDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatMetaDataPtr, ArrayLen));
				m_ChatMetaDataRaw.SetLinkedBuffer(ArrayLen, ChatMetaDataPtr);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result WisperMessageCmd::ParseMessage(const MessageData* pIMsg)

			Result WisperMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				WisperMessageCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("ReceiverID", parser.GetReceiverID());
				variableBuilder.SetVariable("ReceiverName", parser.GetReceiverName());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result WisperMessageCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result WisperMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) WisperMessageCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WisperMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* WisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InReceiverID)
					+ SerializedSizeOf(InReceiverName)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WisperMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InReceiverID);
				protocolCheck(*output << InReceiverName);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* WisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InReceiverID)
					+ SerializedSizeOf(InReceiverName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WisperMessageCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InReceiverID);
				protocolCheck(*output << InReceiverName);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result WisperMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				WisperMessageCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "WisperMessage:{0}:{1} , TransactionID:{2}, ChatUID:{3}, ReceiverID:{4}, ReceiverName:{5,60}, ChatMetaData:{6}, ChatMessage:{7,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetReceiverID(), parser.GetReceiverName(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result WisperMessageCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID WisperMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 62);
			Result WisperMessageRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result WisperMessageRes::ParseMessage(const MessageData* pIMsg)

			Result WisperMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				WisperMessageRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result WisperMessageRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result WisperMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) WisperMessageRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WisperMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* WisperMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
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
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WisperMessageRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* WisperMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result WisperMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				WisperMessageRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "WisperMessage:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result WisperMessageRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Other player wispered(tell) to me message event
			const MessageID WisperMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 63);
			const VariableTable& WisperMessageS2CEvt::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& WisperMessageS2CEvt::GetChatMetaData() const
			Result WisperMessageS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatMetaDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatMetaDataPtr, ArrayLen));
				m_ChatMetaDataRaw.SetLinkedBuffer(ArrayLen, ChatMetaDataPtr);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result WisperMessageS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result WisperMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				WisperMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result WisperMessageS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result WisperMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) WisperMessageS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WisperMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* WisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WisperMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* WisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
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

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InSenderID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WisperMessageS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result WisperMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				WisperMessageS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "WisperMessage:{0}:{1} , SenderID:{2}, ChatMetaData:{3}, ChatMessage:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetSenderID(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result WisperMessageS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Create character
			const MessageID CreateCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 64);
			const VariableTable& CreateCharacterCmd::GetVisualData() const
			{
 				if (!m_VisualDataHasParsed)
				{
 					m_VisualDataHasParsed = true;
					InputMemoryStream VisualData_ReadStream(m_VisualDataRaw);
					*VisualData_ReadStream.ToInputStream() >> m_VisualData;
				} // if (!m_VisualDataHasParsed)
				return m_VisualData;
			} // const VariableTable& CreateCharacterCmd::GetVisualData() const
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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_CharacterName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				uint8_t* VisualDataPtr = nullptr;
				protocolCheck(input->ReadLink(VisualDataPtr, ArrayLen));
				m_VisualDataRaw.SetLinkedBuffer(ArrayLen, VisualDataPtr);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result CreateCharacterCmd::ParseMessage(const MessageData* pIMsg)

			Result CreateCharacterCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateCharacterCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterName", parser.GetCharacterName());
				variableBuilder.SetVariableArray("VisualData", "VariableTable", parser.GetVisualDataRaw());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result CreateCharacterCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateCharacterCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InVisualData, const Array<uint8_t>& InAttributes )
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

				uint16_t serializedSizeOfInVisualData = static_cast<uint16_t>(SerializedSizeOf(InVisualData)); 
				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
					+ serializedSizeOfInVisualData
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateCharacterCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterName);
				protocolCheck(*output << InVisualData);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InVisualData, const Array<uint8_t>& InAttributes )

			MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InVisualData, const VariableTable &InAttributes )
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

				uint16_t serializedSizeOfInVisualData = static_cast<uint16_t>(SerializedSizeOf(InVisualData)); 
				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInVisualData
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
				protocolCheck(output->Write(serializedSizeOfInVisualData));
				protocolCheck(*output << InVisualData);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InVisualData, const VariableTable &InAttributes )

			Result CreateCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateCharacterCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateCharacter:{0}:{1} , TransactionID:{2}, CharacterName:{3,60}, VisualData:{4}, Attributes:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetCharacterName(), parser.GetVisualData(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result CreateCharacterCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CreateCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 64);
			Result CreateCharacterRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result CreateCharacterRes::ParseMessage(const MessageData* pIMsg)

			Result CreateCharacterRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateCharacterRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result CreateCharacterRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateCharacterRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID DeleteCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 65);
			Result DeleteCharacterCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessage(const MessageData* pIMsg)

			Result DeleteCharacterCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteCharacterCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteCharacterCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID DeleteCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 65);
			Result DeleteCharacterRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result DeleteCharacterRes::ParseMessage(const MessageData* pIMsg)

			Result DeleteCharacterRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteCharacterRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result DeleteCharacterRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteCharacterRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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
			const MessageID GetCharacterListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 66);
			Result GetCharacterListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetCharacterListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetCharacterListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterListCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID GetCharacterListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 66);
			Result GetCharacterListRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(m_Characters));

				return hr;

			}; // Result GetCharacterListRes::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Characters", parser.GetCharacters());

				return hr;

			}; // Result GetCharacterListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterListRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetCharacterListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
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
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacters)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterListRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacters);

				return hr;
			}; // MessageData* GetCharacterListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )

			Result GetCharacterListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetCharacterListRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetCharacterList:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Characters:{4,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacters()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: 
			const MessageID GetCharacterDataCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 67);
			Result GetCharacterDataCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessage(const MessageData* pIMsg)

			Result GetCharacterDataCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID GetCharacterDataRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 67);
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
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
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

			Result GetCharacterDataRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetCharacterDataRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

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
			const MessageID SelectCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 68);
			Result SelectCharacterCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result SelectCharacterCmd::ParseMessage(const MessageData* pIMsg)

			Result SelectCharacterCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SelectCharacterCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result SelectCharacterCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SelectCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SelectCharacterCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SelectCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID SelectCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 68);
			const VariableTable& SelectCharacterRes::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& SelectCharacterRes::GetAttributes() const
			Result SelectCharacterRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_CharacterID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result SelectCharacterRes::ParseMessage(const MessageData* pIMsg)

			Result SelectCharacterRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SelectCharacterRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result SelectCharacterRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result SelectCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SelectCharacterRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SelectCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* SelectCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const Array<uint8_t>& InAttributes )
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

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SelectCharacterRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacterID);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* SelectCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const Array<uint8_t>& InAttributes )

			MessageData* SelectCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )
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

				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SelectCharacterRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacterID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* SelectCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )

			Result SelectCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				SelectCharacterRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "SelectCharacter:{0}:{1} , TransactionID:{2}, Result:{3:X8}, CharacterID:{4}, Attributes:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacterID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result SelectCharacterRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: To call general functionality
			const MessageID CallFunctionCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 69);
			const VariableTable& CallFunctionCmd::GetParameters() const
			{
 				if (!m_ParametersHasParsed)
				{
 					m_ParametersHasParsed = true;
					InputMemoryStream Parameters_ReadStream(m_ParametersRaw);
					*Parameters_ReadStream.ToInputStream() >> m_Parameters;
				} // if (!m_ParametersHasParsed)
				return m_Parameters;
			} // const VariableTable& CallFunctionCmd::GetParameters() const
			Result CallFunctionCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FunctionName);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ParametersPtr = nullptr;
				protocolCheck(input->ReadLink(ParametersPtr, ArrayLen));
				m_ParametersRaw.SetLinkedBuffer(ArrayLen, ParametersPtr);

				return hr;

			}; // Result CallFunctionCmd::ParseMessage(const MessageData* pIMsg)

			Result CallFunctionCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CallFunctionCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FunctionName", parser.GetFunctionName());
				variableBuilder.SetVariableArray("Parameters", "VariableTable", parser.GetParametersRaw());

				return hr;

			}; // Result CallFunctionCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CallFunctionCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CallFunctionCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CallFunctionCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters )
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

				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ serializedSizeOfInParameters
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFunctionName);
				protocolCheck(*output << InParameters);

				return hr;
			}; // MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters )

			MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )
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

				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFunctionName);
				protocolCheck(output->Write(serializedSizeOfInParameters));
				protocolCheck(*output << InParameters);

				return hr;
			}; // MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )

			Result CallFunctionCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CallFunctionCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CallFunction:{0}:{1} , TransactionID:{2}, FunctionName:{3}, Parameters:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetFunctionName(), parser.GetParameters()); 
				return ResultCode::SUCCESS;
			}; // Result CallFunctionCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CallFunctionRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_GAME, 69);
			const VariableTable& CallFunctionRes::GetResults() const
			{
 				if (!m_ResultsHasParsed)
				{
 					m_ResultsHasParsed = true;
					InputMemoryStream Results_ReadStream(m_ResultsRaw);
					*Results_ReadStream.ToInputStream() >> m_Results;
				} // if (!m_ResultsHasParsed)
				return m_Results;
			} // const VariableTable& CallFunctionRes::GetResults() const
			Result CallFunctionRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ResultsPtr = nullptr;
				protocolCheck(input->ReadLink(ResultsPtr, ArrayLen));
				m_ResultsRaw.SetLinkedBuffer(ArrayLen, ResultsPtr);

				return hr;

			}; // Result CallFunctionRes::ParseMessage(const MessageData* pIMsg)

			Result CallFunctionRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CallFunctionRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariableArray("Results", "VariableTable", parser.GetResultsRaw());

				return hr;

			}; // Result CallFunctionRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CallFunctionRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CallFunctionRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CallFunctionRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* CallFunctionRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )
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

				uint16_t serializedSizeOfInResults = static_cast<uint16_t>(SerializedSizeOf(InResults)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInResults
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InResults);

				return hr;
			}; // MessageData* CallFunctionRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )

			MessageData* CallFunctionRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )
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

				uint16_t serializedSizeOfInResults = static_cast<uint16_t>(SerializedSizeOf(InResults)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResults
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(output->Write(serializedSizeOfInResults));
				protocolCheck(*output << InResults);

				return hr;
			}; // MessageData* CallFunctionRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )

			Result CallFunctionRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CallFunctionRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CallFunction:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Results:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetResults()); 
				return ResultCode::SUCCESS;
			}; // Result CallFunctionRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)



		}; // namespace Game
	}; // namespace Message
}; // namespace SF



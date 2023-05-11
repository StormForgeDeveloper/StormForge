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
			const MessageID HeartbeatC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 0);
			Result HeartbeatC2SEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);



				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessage(const MessageHeader* pHeader)

			Result HeartbeatC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				HeartbeatC2SEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));


				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result HeartbeatC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) HeartbeatC2SEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result HeartbeatC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t HeartbeatC2SEvt::CalculateMessageSize(  )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
				);

				return __uiMessageSize;
			}; // size_t HeartbeatC2SEvt::CalculateMessageSize(  )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::HeartbeatC2SEvt::MID, __uiMessageSize ) );

				return hr;
			}; // MessageData* HeartbeatC2SEvt::Create( IHeap& memHeap )

			Result HeartbeatC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				HeartbeatC2SEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug7, "Game::Heartbeat, {0}:{1} ",
						prefix, pHeader->Length); 
				return ResultCode::SUCCESS;
			}; // Result HeartbeatC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Player connected from a login server and moved to game server
			const MessageID JoinGameServerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 1);
			Result JoinGameServerCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);

				return hr;

			}; // Result JoinGameServerCmd::ParseMessage(const MessageHeader* pHeader)

			Result JoinGameServerCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameServerCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result JoinGameServerCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameServerCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameServerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinGameServerCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
				);

				return __uiMessageSize;
			}; // size_t JoinGameServerCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameServerCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);

				return hr;
			}; // MessageData* JoinGameServerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )

			Result JoinGameServerCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinGameServerCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinGameServer, {0}:{1} , TransactionID:{2}, AccID:{3}, Ticket:{4}, LoginEntityUID:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameServerCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID JoinGameServerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 1);
			Result JoinGameServerRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result JoinGameServerRes::ParseMessage(const MessageHeader* pHeader)

			Result JoinGameServerRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameServerRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("GameUID", parser.GetGameUID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());
				variableBuilder.SetVariable("MatchingTicket", "MatchingQueueTicket", parser.GetMatchingTicket());

				return hr;

			}; // Result JoinGameServerRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameServerRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameServerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinGameServerRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InGameUID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPartyLeaderID)
					+ SerializedSizeOf(InMatchingTicket)
				);

				return __uiMessageSize;
			}; // size_t JoinGameServerRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InGameUID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPartyLeaderID)
					+ SerializedSizeOf(InMatchingTicket)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameServerRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNickName);
				protocolCheck(*output << InGameUID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPartyLeaderID);
				protocolCheck(*output << InMatchingTicket);

				return hr;
			}; // MessageData* JoinGameServerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )

			Result JoinGameServerRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinGameServerRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinGameServer, {0}:{1} , TransactionID:{2}, Result:{3:X8}, NickName:{4,60}, GameUID:{5}, PartyUID:{6}, PartyLeaderID:{7}, MatchingTicket:{8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNickName(), parser.GetGameUID(), parser.GetPartyUID(), parser.GetPartyLeaderID(), parser.GetMatchingTicket()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameServerRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: player complition statues
			const MessageID GetComplitionStateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 2);
			Result GetComplitionStateCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetComplitionStateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetComplitionStateCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetComplitionStateCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetComplitionStateCmd::CalculateMessageSize( const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t GetComplitionStateCmd::CalculateMessageSize( const uint64_t &InTransactionID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetComplitionStateCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result GetComplitionStateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetComplitionStateCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetComplitionState, {0}:{1} , TransactionID:{2}",
						prefix, pHeader->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetComplitionStateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetComplitionStateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 2);
			Result GetComplitionStateRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ComplitionState, ArrayLen));

				return hr;

			}; // Result GetComplitionStateRes::ParseMessage(const MessageHeader* pHeader)

			Result GetComplitionStateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetComplitionStateRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());

				return hr;

			}; // Result GetComplitionStateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetComplitionStateRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetComplitionStateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InComplitionState)
				);

				return __uiMessageSize;
			}; // size_t GetComplitionStateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InComplitionState)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetComplitionStateRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InComplitionState);

				return hr;
			}; // MessageData* GetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )

			Result GetComplitionStateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetComplitionStateRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetComplitionState, {0}:{1} , TransactionID:{2}, Result:{3:X8}, ComplitionState:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetComplitionState()); 
				return ResultCode::SUCCESS;
			}; // Result GetComplitionStateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Player complition state
			const MessageID SetComplitionStateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 3);
			Result SetComplitionStateCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ComplitionState, ArrayLen));

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessage(const MessageHeader* pHeader)

			Result SetComplitionStateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetComplitionStateCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ComplitionState", parser.GetComplitionState());

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetComplitionStateCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetComplitionStateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetComplitionStateCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InComplitionState )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InComplitionState)
				);

				return __uiMessageSize;
			}; // size_t SetComplitionStateCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InComplitionState )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InComplitionState)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetComplitionStateCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InComplitionState);

				return hr;
			}; // MessageData* SetComplitionStateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InComplitionState )

			Result SetComplitionStateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetComplitionStateCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SetComplitionState, {0}:{1} , TransactionID:{2}, ComplitionState:{3,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetComplitionState()); 
				return ResultCode::SUCCESS;
			}; // Result SetComplitionStateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID SetComplitionStateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 3);
			Result SetComplitionStateRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result SetComplitionStateRes::ParseMessage(const MessageHeader* pHeader)

			Result SetComplitionStateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetComplitionStateRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result SetComplitionStateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetComplitionStateRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetComplitionStateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetComplitionStateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t SetComplitionStateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetComplitionStateRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* SetComplitionStateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result SetComplitionStateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetComplitionStateRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SetComplitionState, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result SetComplitionStateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			const MessageID RegisterGCMCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 4);
			Result RegisterGCMCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GCMRegisteredID, ArrayLen));

				return hr;

			}; // Result RegisterGCMCmd::ParseMessage(const MessageHeader* pHeader)

			Result RegisterGCMCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RegisterGCMCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());

				return hr;

			}; // Result RegisterGCMCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RegisterGCMCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RegisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RegisterGCMCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGCMRegisteredID)
				);

				return __uiMessageSize;
			}; // size_t RegisterGCMCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InGCMRegisteredID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGCMRegisteredID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RegisterGCMCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGCMRegisteredID);

				return hr;
			}; // MessageData* RegisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )

			Result RegisterGCMCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RegisterGCMCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RegisterGCM, {0}:{1} , TransactionID:{2}, GCMRegisteredID:{3,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetGCMRegisteredID()); 
				return ResultCode::SUCCESS;
			}; // Result RegisterGCMCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID RegisterGCMRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 4);
			Result RegisterGCMRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RegisterGCMRes::ParseMessage(const MessageHeader* pHeader)

			Result RegisterGCMRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RegisterGCMRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RegisterGCMRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RegisterGCMRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RegisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RegisterGCMRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t RegisterGCMRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RegisterGCMRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* RegisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result RegisterGCMRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RegisterGCMRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RegisterGCM, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result RegisterGCMRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Unregister Google notification service ID
			const MessageID UnregisterGCMCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 5);
			Result UnregisterGCMCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GCMRegisteredID, ArrayLen));

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessage(const MessageHeader* pHeader)

			Result UnregisterGCMCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnregisterGCMCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GCMRegisteredID", parser.GetGCMRegisteredID());

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnregisterGCMCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnregisterGCMCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t UnregisterGCMCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGCMRegisteredID)
				);

				return __uiMessageSize;
			}; // size_t UnregisterGCMCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InGCMRegisteredID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGCMRegisteredID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::UnregisterGCMCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGCMRegisteredID);

				return hr;
			}; // MessageData* UnregisterGCMCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InGCMRegisteredID )

			Result UnregisterGCMCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UnregisterGCMCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::UnregisterGCM, {0}:{1} , TransactionID:{2}, GCMRegisteredID:{3,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetGCMRegisteredID()); 
				return ResultCode::SUCCESS;
			}; // Result UnregisterGCMCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID UnregisterGCMRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 5);
			Result UnregisterGCMRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result UnregisterGCMRes::ParseMessage(const MessageHeader* pHeader)

			Result UnregisterGCMRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnregisterGCMRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result UnregisterGCMRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnregisterGCMRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnregisterGCMRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t UnregisterGCMRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t UnregisterGCMRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::UnregisterGCMRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* UnregisterGCMRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result UnregisterGCMRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UnregisterGCMRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::UnregisterGCM, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result UnregisterGCMRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Invite friend
			const MessageID InviteFriendCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 6);
			Result InviteFriendCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result InviteFriendCmd::ParseMessage(const MessageHeader* pHeader)

			Result InviteFriendCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				InviteFriendCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result InviteFriendCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) InviteFriendCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result InviteFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t InviteFriendCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InFriendID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFriendID)
				);

				return __uiMessageSize;
			}; // size_t InviteFriendCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InFriendID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::InviteFriendCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFriendID);

				return hr;
			}; // MessageData* InviteFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )

			Result InviteFriendCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				InviteFriendCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::InviteFriend, {0}:{1} , TransactionID:{2}, FriendID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result InviteFriendCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID InviteFriendRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 6);
			Result InviteFriendRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result InviteFriendRes::ParseMessage(const MessageHeader* pHeader)

			Result InviteFriendRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				InviteFriendRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result InviteFriendRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) InviteFriendRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result InviteFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t InviteFriendRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t InviteFriendRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::InviteFriendRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* InviteFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result InviteFriendRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				InviteFriendRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::InviteFriend, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result InviteFriendRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Accept friend request
			const MessageID AcceptFriendRequestCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 7);
			Result AcceptFriendRequestCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InviterID);
				protocolCheck(*input >> m_InviterPlatformId);

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessage(const MessageHeader* pHeader)

			Result AcceptFriendRequestCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptFriendRequestCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterPlatformId", "PlayerPlatformID", parser.GetInviterPlatformId());

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptFriendRequestCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptFriendRequestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t AcceptFriendRequestCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InInviterPlatformId)
				);

				return __uiMessageSize;
			}; // size_t AcceptFriendRequestCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )


			MessageData* AcceptFriendRequestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InInviterPlatformId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptFriendRequestCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInviterID);
				protocolCheck(*output << InInviterPlatformId);

				return hr;
			}; // MessageData* AcceptFriendRequestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )

			Result AcceptFriendRequestCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AcceptFriendRequestCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::AcceptFriendRequest, {0}:{1} , TransactionID:{2}, InviterID:{3}, InviterPlatformId:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetInviterID(), parser.GetInviterPlatformId()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptFriendRequestCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID AcceptFriendRequestRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 7);
			Result AcceptFriendRequestRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NewFriend);

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessage(const MessageHeader* pHeader)

			Result AcceptFriendRequestRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptFriendRequestRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NewFriend", "FriendInformation", parser.GetNewFriend());

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptFriendRequestRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptFriendRequestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t AcceptFriendRequestRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNewFriend)
				);

				return __uiMessageSize;
			}; // size_t AcceptFriendRequestRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNewFriend)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptFriendRequestRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNewFriend);

				return hr;
			}; // MessageData* AcceptFriendRequestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )

			Result AcceptFriendRequestRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AcceptFriendRequestRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::AcceptFriendRequest, {0}:{1} , TransactionID:{2}, Result:{3:X8}, NewFriend:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNewFriend()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptFriendRequestRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Notification for friend request is accepted
			const MessageID FriendRequestAcceptedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 8);
			Result FriendRequestAcceptedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_Accepter);

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result FriendRequestAcceptedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FriendRequestAcceptedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("Accepter", "FriendInformation", parser.GetAccepter());

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FriendRequestAcceptedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FriendRequestAcceptedS2CEvt::CalculateMessageSize( const FriendInformation &InAccepter )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InAccepter)
				);

				return __uiMessageSize;
			}; // size_t FriendRequestAcceptedS2CEvt::CalculateMessageSize( const FriendInformation &InAccepter )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InAccepter)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FriendRequestAcceptedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InAccepter);

				return hr;
			}; // MessageData* FriendRequestAcceptedS2CEvt::Create( IHeap& memHeap, const FriendInformation &InAccepter )

			Result FriendRequestAcceptedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FriendRequestAcceptedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FriendRequestAccepted, {0}:{1} , Accepter:{2}",
						prefix, pHeader->Length, parser.GetAccepter()); 
				return ResultCode::SUCCESS;
			}; // Result FriendRequestAcceptedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Remove friden form the friend list
			const MessageID RemoveFriendCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 9);
			Result RemoveFriendCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result RemoveFriendCmd::ParseMessage(const MessageHeader* pHeader)

			Result RemoveFriendCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemoveFriendCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result RemoveFriendCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveFriendCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveFriendCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RemoveFriendCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InFriendID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFriendID)
				);

				return __uiMessageSize;
			}; // size_t RemoveFriendCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InFriendID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RemoveFriendCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFriendID);

				return hr;
			}; // MessageData* RemoveFriendCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InFriendID )

			Result RemoveFriendCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RemoveFriendCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RemoveFriend, {0}:{1} , TransactionID:{2}, FriendID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveFriendCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID RemoveFriendRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 9);
			Result RemoveFriendRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result RemoveFriendRes::ParseMessage(const MessageHeader* pHeader)

			Result RemoveFriendRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemoveFriendRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result RemoveFriendRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveFriendRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveFriendRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RemoveFriendRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InFriendID)
				);

				return __uiMessageSize;
			}; // size_t RemoveFriendRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RemoveFriendRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InFriendID);

				return hr;
			}; // MessageData* RemoveFriendRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )

			Result RemoveFriendRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RemoveFriendRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RemoveFriend, {0}:{1} , TransactionID:{2}, Result:{3:X8}, FriendID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveFriendRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Friend removed
			const MessageID FriendRemovedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 10);
			Result FriendRemovedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_FriendID);

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result FriendRemovedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FriendRemovedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("FriendID", parser.GetFriendID());

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FriendRemovedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FriendRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FriendRemovedS2CEvt::CalculateMessageSize( const AccountID &InFriendID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InFriendID)
				);

				return __uiMessageSize;
			}; // size_t FriendRemovedS2CEvt::CalculateMessageSize( const AccountID &InFriendID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InFriendID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FriendRemovedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InFriendID);

				return hr;
			}; // MessageData* FriendRemovedS2CEvt::Create( IHeap& memHeap, const AccountID &InFriendID )

			Result FriendRemovedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FriendRemovedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FriendRemoved, {0}:{1} , FriendID:{2}",
						prefix, pHeader->Length, parser.GetFriendID()); 
				return ResultCode::SUCCESS;
			}; // Result FriendRemovedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Get friend list
			const MessageID GetFriendListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 11);
			Result GetFriendListCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_StartIndex);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result GetFriendListCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetFriendListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetFriendListCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("StartIndex", parser.GetStartIndex());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result GetFriendListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetFriendListCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetFriendListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetFriendListCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InStartIndex)
					+ SerializedSizeOf(InCount)
				);

				return __uiMessageSize;
			}; // size_t GetFriendListCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InStartIndex)
					+ SerializedSizeOf(InCount)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetFriendListCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InStartIndex);
				protocolCheck(*output << InCount);

				return hr;
			}; // MessageData* GetFriendListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )

			Result GetFriendListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetFriendListCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetFriendList, {0}:{1} , TransactionID:{2}, StartIndex:{3}, Count:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetStartIndex(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result GetFriendListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetFriendListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 11);
			Result GetFriendListRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result GetFriendListRes::ParseMessage(const MessageHeader* pHeader)

			Result GetFriendListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetFriendListRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("MaxFriendSlot", parser.GetMaxFriendSlot());
				variableBuilder.SetVariable("TotalNumberOfFriends", parser.GetTotalNumberOfFriends());
				variableBuilder.SetVariable("StartIndex", parser.GetStartIndex());
				variableBuilder.SetVariable("FriendList", parser.GetFriendList());

				return hr;

			}; // Result GetFriendListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetFriendListRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetFriendListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetFriendListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InMaxFriendSlot)
					+ SerializedSizeOf(InTotalNumberOfFriends)
					+ SerializedSizeOf(InStartIndex)
					+ SerializedSizeOf(InFriendList)
				);

				return __uiMessageSize;
			}; // size_t GetFriendListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InMaxFriendSlot)
					+ SerializedSizeOf(InTotalNumberOfFriends)
					+ SerializedSizeOf(InStartIndex)
					+ SerializedSizeOf(InFriendList)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetFriendListRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InMaxFriendSlot);
				protocolCheck(*output << InTotalNumberOfFriends);
				protocolCheck(*output << InStartIndex);
				protocolCheck(*output << InFriendList);

				return hr;
			}; // MessageData* GetFriendListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )

			Result GetFriendListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetFriendListRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetFriendList, {0}:{1} , TransactionID:{2}, Result:{3:X8}, MaxFriendSlot:{4}, TotalNumberOfFriends:{5}, StartIndex:{6}, FriendList:{7,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetMaxFriendSlot(), parser.GetTotalNumberOfFriends(), parser.GetStartIndex(), parser.GetFriendList()); 
				return ResultCode::SUCCESS;
			}; // Result GetFriendListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Query notification list
			const MessageID GetNotificationListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 12);
			Result GetNotificationListCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetNotificationListCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetNotificationListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetNotificationListCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetNotificationListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetNotificationListCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetNotificationListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetNotificationListCmd::CalculateMessageSize( const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t GetNotificationListCmd::CalculateMessageSize( const uint64_t &InTransactionID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetNotificationListCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GetNotificationListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result GetNotificationListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetNotificationListCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetNotificationList, {0}:{1} , TransactionID:{2}",
						prefix, pHeader->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetNotificationListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetNotificationListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 12);
			Result GetNotificationListRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result GetNotificationListRes::ParseMessage(const MessageHeader* pHeader)

			Result GetNotificationListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetNotificationListRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result GetNotificationListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetNotificationListRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetNotificationListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetNotificationListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t GetNotificationListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetNotificationListRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* GetNotificationListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result GetNotificationListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetNotificationListRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetNotificationList, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result GetNotificationListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Delete notification
			const MessageID DeleteNotificationCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 13);
			Result DeleteNotificationCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessage(const MessageHeader* pHeader)

			Result DeleteNotificationCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteNotificationCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteNotificationCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t DeleteNotificationCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				return __uiMessageSize;
			}; // size_t DeleteNotificationCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InNotificationID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteNotificationCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNotificationID);

				return hr;
			}; // MessageData* DeleteNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )

			Result DeleteNotificationCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DeleteNotificationCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::DeleteNotification, {0}:{1} , TransactionID:{2}, NotificationID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteNotificationCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID DeleteNotificationRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 13);
			Result DeleteNotificationRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result DeleteNotificationRes::ParseMessage(const MessageHeader* pHeader)

			Result DeleteNotificationRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteNotificationRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result DeleteNotificationRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteNotificationRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t DeleteNotificationRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				return __uiMessageSize;
			}; // size_t DeleteNotificationRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteNotificationRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNotificationID);

				return hr;
			}; // MessageData* DeleteNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )

			Result DeleteNotificationRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DeleteNotificationRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::DeleteNotification, {0}:{1} , TransactionID:{2}, Result:{3:X8}, NotificationID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteNotificationRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Set notification is read
			const MessageID SetNotificationReadCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 14);
			Result SetNotificationReadCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessage(const MessageHeader* pHeader)

			Result SetNotificationReadCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNotificationReadCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNotificationReadCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNotificationReadCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetNotificationReadCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				return __uiMessageSize;
			}; // size_t SetNotificationReadCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InNotificationID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNotificationReadCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNotificationID);

				return hr;
			}; // MessageData* SetNotificationReadCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )

			Result SetNotificationReadCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetNotificationReadCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SetNotificationRead, {0}:{1} , TransactionID:{2}, NotificationID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result SetNotificationReadCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID SetNotificationReadRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 14);
			Result SetNotificationReadRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result SetNotificationReadRes::ParseMessage(const MessageHeader* pHeader)

			Result SetNotificationReadRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNotificationReadRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result SetNotificationReadRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNotificationReadRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNotificationReadRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetNotificationReadRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				return __uiMessageSize;
			}; // size_t SetNotificationReadRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNotificationReadRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNotificationID);

				return hr;
			}; // MessageData* SetNotificationReadRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )

			Result SetNotificationReadRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetNotificationReadRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SetNotificationRead, {0}:{1} , TransactionID:{2}, Result:{3:X8}, NotificationID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result SetNotificationReadRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Accept notification
			const MessageID AcceptNotificationCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 15);
			Result AcceptNotificationCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessage(const MessageHeader* pHeader)

			Result AcceptNotificationCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptNotificationCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptNotificationCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptNotificationCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t AcceptNotificationCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				return __uiMessageSize;
			}; // size_t AcceptNotificationCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InNotificationID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptNotificationCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNotificationID);

				return hr;
			}; // MessageData* AcceptNotificationCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InNotificationID )

			Result AcceptNotificationCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AcceptNotificationCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::AcceptNotification, {0}:{1} , TransactionID:{2}, NotificationID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptNotificationCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID AcceptNotificationRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 15);
			Result AcceptNotificationRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_NotificationID);

				return hr;

			}; // Result AcceptNotificationRes::ParseMessage(const MessageHeader* pHeader)

			Result AcceptNotificationRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				AcceptNotificationRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());

				return hr;

			}; // Result AcceptNotificationRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptNotificationRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptNotificationRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t AcceptNotificationRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				return __uiMessageSize;
			}; // size_t AcceptNotificationRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNotificationID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::AcceptNotificationRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNotificationID);

				return hr;
			}; // MessageData* AcceptNotificationRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )

			Result AcceptNotificationRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AcceptNotificationRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::AcceptNotification, {0}:{1} , TransactionID:{2}, Result:{3:X8}, NotificationID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNotificationID()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptNotificationRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Notify new notification
			const MessageID NotifyS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 16);
			const VariableTable& NotifyS2CEvt::GetParameters() const
			{
 				if (!m_ParametersHasParsed)
				{
 					m_ParametersHasParsed = true;
					InputMemoryStream Parameters_ReadStream(m_ParametersRaw);
					*Parameters_ReadStream.ToInputStream() >> m_Parameters;
				} // if (!m_ParametersHasParsed)
				return m_Parameters;
			} // const VariableTable& NotifyS2CEvt::GetParameters() const
			Result NotifyS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_NotificationID);
				protocolCheck(*input >> m_NotificationType);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ParametersPtr = nullptr;
				protocolCheck(input->ReadLink(ParametersPtr, ArrayLen));
				m_ParametersRaw.SetLinkedBuffer(ArrayLen, ParametersPtr);
				protocolCheck(*input >> m_IsRead);
				protocolCheck(*input >> m_TimeStamp);

				return hr;

			}; // Result NotifyS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result NotifyS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				NotifyS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("NotificationID", parser.GetNotificationID());
				variableBuilder.SetVariable("NotificationType", parser.GetNotificationType());
				variableBuilder.SetVariableArray("Parameters", "VariableTable", parser.GetParametersRaw());
				variableBuilder.SetVariable("IsRead", parser.GetIsRead());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());

				return hr;

			}; // Result NotifyS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NotifyS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NotifyS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t NotifyS2CEvt::CalculateMessageSize( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const Array<uint8_t>& InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
			{
 				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InNotificationID)
					+ SerializedSizeOf(InNotificationType)
					+ serializedSizeOfInParameters
					+ SerializedSizeOf(InIsRead)
					+ SerializedSizeOf(InTimeStamp)
				);

				return __uiMessageSize;
			}; // size_t NotifyS2CEvt::CalculateMessageSize( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const Array<uint8_t>& InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )

			size_t NotifyS2CEvt::CalculateMessageSize( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
			{
 				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InNotificationID)
					+ SerializedSizeOf(InNotificationType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
					+ SerializedSizeOf(InIsRead)
					+ SerializedSizeOf(InTimeStamp)
				);

				return __uiMessageSize;
			}; // size_t NotifyS2CEvt::CalculateMessageSize( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )

			MessageData* NotifyS2CEvt::Create( IHeap& memHeap, const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const Array<uint8_t>& InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint __uiMessageSize = (uint)CalculateMessageSize(InNotificationID, InNotificationType, InParameters, InIsRead, InTimeStamp);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::NotifyS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InNotificationID);
				protocolCheck(*output << InNotificationType);
				protocolCheck(*output << InParameters);
				protocolCheck(*output << InIsRead);
				protocolCheck(*output << InTimeStamp);

				return hr;
			}; // MessageData* NotifyS2CEvt::Create( IHeap& memHeap, const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const Array<uint8_t>& InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )

			MessageData* NotifyS2CEvt::Create( IHeap& memHeap, const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InNotificationID)
					+ SerializedSizeOf(InNotificationType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
					+ SerializedSizeOf(InIsRead)
					+ SerializedSizeOf(InTimeStamp)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::NotifyS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InNotificationID);
				protocolCheck(*output << InNotificationType);
				protocolCheck(output->Write(serializedSizeOfInParameters));
				protocolCheck(*output << InParameters);
				protocolCheck(*output << InIsRead);
				protocolCheck(*output << InTimeStamp);

				return hr;
			}; // MessageData* NotifyS2CEvt::Create( IHeap& memHeap, const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )

			Result NotifyS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				NotifyS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::Notify, {0}:{1} , NotificationID:{2}, NotificationType:{3}, Parameters:{4}, IsRead:{5}, TimeStamp:{6}",
						prefix, pHeader->Length, parser.GetNotificationID(), parser.GetNotificationType(), parser.GetParameters(), parser.GetIsRead(), parser.GetTimeStamp()); 
				return ResultCode::SUCCESS;
			}; // Result NotifyS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: PlayerId Conversion
			const MessageID FindPlayerByPlatformIdCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 17);
			Result FindPlayerByPlatformIdCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlatformPlayerId);

				return hr;

			}; // Result FindPlayerByPlatformIdCmd::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByPlatformIdCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlatformIdCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlatformPlayerId", "PlayerPlatformID", parser.GetPlatformPlayerId());

				return hr;

			}; // Result FindPlayerByPlatformIdCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlatformIdCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlatformIdCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlatformIdCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByPlatformIdCmd::CalculateMessageSize( const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlatformPlayerId)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByPlatformIdCmd::CalculateMessageSize( const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )


			MessageData* FindPlayerByPlatformIdCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlatformPlayerId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlatformIdCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlatformPlayerId);

				return hr;
			}; // MessageData* FindPlayerByPlatformIdCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )

			Result FindPlayerByPlatformIdCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByPlatformIdCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByPlatformId, {0}:{1} , TransactionID:{2}, PlatformPlayerId:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlatformPlayerId()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlatformIdCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID FindPlayerByPlatformIdRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 17);
			Result FindPlayerByPlatformIdRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayerId);
				protocolCheck(*input >> m_PlayerPlatformId);

				return hr;

			}; // Result FindPlayerByPlatformIdRes::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByPlatformIdRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlatformIdRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerId", parser.GetPlayerId());
				variableBuilder.SetVariable("PlayerPlatformId", "PlayerPlatformID", parser.GetPlayerPlatformId());

				return hr;

			}; // Result FindPlayerByPlatformIdRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlatformIdRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlatformIdRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlatformIdRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByPlatformIdRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerId)
					+ SerializedSizeOf(InPlayerPlatformId)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByPlatformIdRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )


			MessageData* FindPlayerByPlatformIdRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerId)
					+ SerializedSizeOf(InPlayerPlatformId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlatformIdRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerId);
				protocolCheck(*output << InPlayerPlatformId);

				return hr;
			}; // MessageData* FindPlayerByPlatformIdRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )

			Result FindPlayerByPlatformIdRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByPlatformIdRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByPlatformId, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerId:{4}, PlayerPlatformId:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerId(), parser.GetPlayerPlatformId()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlatformIdRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: PlayerId conversion
			const MessageID FindPlayerByCharacterNameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 18);
			Result FindPlayerByCharacterNameCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_CharacterName, ArrayLen));

				return hr;

			}; // Result FindPlayerByCharacterNameCmd::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByCharacterNameCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByCharacterNameCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterName", parser.GetCharacterName());

				return hr;

			}; // Result FindPlayerByCharacterNameCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByCharacterNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByCharacterNameCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByCharacterNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByCharacterNameCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InCharacterName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByCharacterNameCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InCharacterName )


			MessageData* FindPlayerByCharacterNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByCharacterNameCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterName);

				return hr;
			}; // MessageData* FindPlayerByCharacterNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName )

			Result FindPlayerByCharacterNameCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByCharacterNameCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByCharacterName, {0}:{1} , TransactionID:{2}, CharacterName:{3,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetCharacterName()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByCharacterNameCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID FindPlayerByCharacterNameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 18);
			Result FindPlayerByCharacterNameRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayerId);

				return hr;

			}; // Result FindPlayerByCharacterNameRes::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByCharacterNameRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByCharacterNameRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerId", parser.GetPlayerId());

				return hr;

			}; // Result FindPlayerByCharacterNameRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByCharacterNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByCharacterNameRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByCharacterNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByCharacterNameRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerId)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByCharacterNameRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )


			MessageData* FindPlayerByCharacterNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByCharacterNameRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerId);

				return hr;
			}; // MessageData* FindPlayerByCharacterNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )

			Result FindPlayerByCharacterNameRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByCharacterNameRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByCharacterName, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerId:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerId()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByCharacterNameRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: PlayerId Conversion
			const MessageID FindPlayerByPlatformUserNameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 19);
			Result FindPlayerByPlatformUserNameCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlatformType);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlatformUserName, ArrayLen));

				return hr;

			}; // Result FindPlayerByPlatformUserNameCmd::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByPlatformUserNameCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlatformUserNameCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlatformType", parser.GetPlatformType());
				variableBuilder.SetVariable("PlatformUserName", parser.GetPlatformUserName());

				return hr;

			}; // Result FindPlayerByPlatformUserNameCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlatformUserNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlatformUserNameCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlatformUserNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByPlatformUserNameCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlatformType)
					+ SerializedSizeOf(InPlatformUserName)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByPlatformUserNameCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )


			MessageData* FindPlayerByPlatformUserNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlatformType)
					+ SerializedSizeOf(InPlatformUserName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlatformUserNameCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlatformType);
				protocolCheck(*output << InPlatformUserName);

				return hr;
			}; // MessageData* FindPlayerByPlatformUserNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )

			Result FindPlayerByPlatformUserNameCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByPlatformUserNameCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByPlatformUserName, {0}:{1} , TransactionID:{2}, PlatformType:{3}, PlatformUserName:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlatformType(), parser.GetPlatformUserName()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlatformUserNameCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID FindPlayerByPlatformUserNameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 19);
			Result FindPlayerByPlatformUserNameRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayerId);
				protocolCheck(*input >> m_PlayerPlatformId);

				return hr;

			}; // Result FindPlayerByPlatformUserNameRes::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByPlatformUserNameRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlatformUserNameRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerId", parser.GetPlayerId());
				variableBuilder.SetVariable("PlayerPlatformId", "PlayerPlatformID", parser.GetPlayerPlatformId());

				return hr;

			}; // Result FindPlayerByPlatformUserNameRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlatformUserNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlatformUserNameRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlatformUserNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByPlatformUserNameRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerId)
					+ SerializedSizeOf(InPlayerPlatformId)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByPlatformUserNameRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )


			MessageData* FindPlayerByPlatformUserNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerId)
					+ SerializedSizeOf(InPlayerPlatformId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlatformUserNameRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerId);
				protocolCheck(*output << InPlayerPlatformId);

				return hr;
			}; // MessageData* FindPlayerByPlatformUserNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )

			Result FindPlayerByPlatformUserNameRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByPlatformUserNameRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByPlatformUserName, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerId:{4}, PlayerPlatformId:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerId(), parser.GetPlayerPlatformId()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlatformUserNameRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Query playerID list
			const MessageID FindPlayerByEMailCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 20);
			Result FindPlayerByEMailCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlayerEMail, ArrayLen));

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByEMailCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByEMailCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerEMail", parser.GetPlayerEMail());

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByEMailCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByEMailCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByEMailCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InPlayerEMail )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerEMail)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByEMailCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InPlayerEMail )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerEMail)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByEMailCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayerEMail);

				return hr;
			}; // MessageData* FindPlayerByEMailCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InPlayerEMail )

			Result FindPlayerByEMailCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByEMailCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByEMail, {0}:{1} , TransactionID:{2}, PlayerEMail:{3,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayerEMail()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByEMailCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID FindPlayerByEMailRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 20);
			Result FindPlayerByEMailRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_Player);

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByEMailRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByEMailRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", "PlayerInformation", parser.GetPlayer());

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByEMailRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByEMailRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByEMailRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayer)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByEMailRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByEMailRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayer);

				return hr;
			}; // MessageData* FindPlayerByEMailRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )

			Result FindPlayerByEMailRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByEMailRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByEMail, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Player:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByEMailRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Query playerID list
			const MessageID FindPlayerByPlayerIDCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 21);
			Result FindPlayerByPlayerIDCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByPlayerIDCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlayerIDCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlayerIDCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByPlayerIDCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerID)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByPlayerIDCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlayerIDCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // MessageData* FindPlayerByPlayerIDCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )

			Result FindPlayerByPlayerIDCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByPlayerIDCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByPlayerID, {0}:{1} , TransactionID:{2}, PlayerID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlayerIDCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID FindPlayerByPlayerIDRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 21);
			Result FindPlayerByPlayerIDRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_Player);

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessage(const MessageHeader* pHeader)

			Result FindPlayerByPlayerIDRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindPlayerByPlayerIDRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Player", "PlayerInformation", parser.GetPlayer());

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindPlayerByPlayerIDRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindPlayerByPlayerIDRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindPlayerByPlayerIDRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayer)
				);

				return __uiMessageSize;
			}; // size_t FindPlayerByPlayerIDRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::FindPlayerByPlayerIDRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayer);

				return hr;
			}; // MessageData* FindPlayerByPlayerIDRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )

			Result FindPlayerByPlayerIDRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindPlayerByPlayerIDRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::FindPlayerByPlayerID, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Player:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result FindPlayerByPlayerIDRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: *Request Player Status Update
			const MessageID RequestPlayerStatusUpdateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 22);
			Result RequestPlayerStatusUpdateCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				AccountID* TargetPlayerIDPtr = nullptr;
				protocolCheck(input->ReadLink(TargetPlayerIDPtr, ArrayLen));
				m_TargetPlayerID.SetLinkedBuffer(ArrayLen, TargetPlayerIDPtr);

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessage(const MessageHeader* pHeader)

			Result RequestPlayerStatusUpdateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestPlayerStatusUpdateCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TargetPlayerID", parser.GetTargetPlayerID());

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RequestPlayerStatusUpdateCmd::CalculateMessageSize( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTargetPlayerID)
				);

				return __uiMessageSize;
			}; // size_t RequestPlayerStatusUpdateCmd::CalculateMessageSize( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTargetPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestPlayerStatusUpdateCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTargetPlayerID);

				return hr;
			}; // MessageData* RequestPlayerStatusUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )

			Result RequestPlayerStatusUpdateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestPlayerStatusUpdateCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RequestPlayerStatusUpdate, {0}:{1} , TransactionID:{2}, TargetPlayerID:{3,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetTargetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result RequestPlayerStatusUpdateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID RequestPlayerStatusUpdateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 22);
			Result RequestPlayerStatusUpdateRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessage(const MessageHeader* pHeader)

			Result RequestPlayerStatusUpdateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestPlayerStatusUpdateRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestPlayerStatusUpdateRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestPlayerStatusUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RequestPlayerStatusUpdateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t RequestPlayerStatusUpdateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestPlayerStatusUpdateRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* RequestPlayerStatusUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result RequestPlayerStatusUpdateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestPlayerStatusUpdateRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RequestPlayerStatusUpdate, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result RequestPlayerStatusUpdateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: *Notify Player Status Updated
			const MessageID NotifyPlayerStatusUpdatedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 23);
			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_LatestActiveTime);
				protocolCheck(*input >> m_IsInGame);

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				NotifyPlayerStatusUpdatedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("LatestActiveTime", parser.GetLatestActiveTime());
				variableBuilder.SetVariable("IsInGame", parser.GetIsInGame());

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NotifyPlayerStatusUpdatedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t NotifyPlayerStatusUpdatedS2CEvt::CalculateMessageSize( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InLatestActiveTime)
					+ SerializedSizeOf(InIsInGame)
				);

				return __uiMessageSize;
			}; // size_t NotifyPlayerStatusUpdatedS2CEvt::CalculateMessageSize( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InLatestActiveTime)
					+ SerializedSizeOf(InIsInGame)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::NotifyPlayerStatusUpdatedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLatestActiveTime);
				protocolCheck(*output << InIsInGame);

				return hr;
			}; // MessageData* NotifyPlayerStatusUpdatedS2CEvt::Create( IHeap& memHeap, const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )

			Result NotifyPlayerStatusUpdatedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				NotifyPlayerStatusUpdatedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::NotifyPlayerStatusUpdated, {0}:{1} , PlayerID:{2}, LatestActiveTime:{3}, IsInGame:{4}",
						prefix, pHeader->Length, parser.GetPlayerID(), parser.GetLatestActiveTime(), parser.GetIsInGame()); 
				return ResultCode::SUCCESS;
			}; // Result NotifyPlayerStatusUpdatedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Get Ranking list
			const MessageID GetRankingListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 24);
			Result GetRankingListCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_RankingType);
				protocolCheck(*input >> m_BaseRanking);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result GetRankingListCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetRankingListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetRankingListCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingType", parser.GetRankingType());
				variableBuilder.SetVariable("BaseRanking", parser.GetBaseRanking());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetRankingListCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InRankingType)
					+ SerializedSizeOf(InBaseRanking)
					+ SerializedSizeOf(InCount)
				);

				return __uiMessageSize;
			}; // size_t GetRankingListCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InRankingType)
					+ SerializedSizeOf(InBaseRanking)
					+ SerializedSizeOf(InCount)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetRankingListCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InRankingType);
				protocolCheck(*output << InBaseRanking);
				protocolCheck(*output << InCount);

				return hr;
			}; // MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )

			Result GetRankingListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetRankingListCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetRankingList, {0}:{1} , TransactionID:{2}, RankingType:{3}, BaseRanking:{4}, Count:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetRankingType(), parser.GetBaseRanking(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetRankingListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 24);
			Result GetRankingListRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result GetRankingListRes::ParseMessage(const MessageHeader* pHeader)

			Result GetRankingListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetRankingListRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());

				return hr;

			}; // Result GetRankingListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetRankingListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InRanking)
				);

				return __uiMessageSize;
			}; // size_t GetRankingListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InRanking)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetRankingListRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InRanking);

				return hr;
			}; // MessageData* GetRankingListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )

			Result GetRankingListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetRankingListRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetRankingList, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Ranking:{4,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetRanking()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Game user game play information
			const MessageID GetUserGamePlayerInfoCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 25);
			Result GetUserGamePlayerInfoCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetUserGamePlayerInfoCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetUserGamePlayerInfoCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetUserGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetUserGamePlayerInfoCmd::CalculateMessageSize( const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t GetUserGamePlayerInfoCmd::CalculateMessageSize( const uint64_t &InTransactionID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GetUserGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result GetUserGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetUserGamePlayerInfoCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetUserGamePlayerInfo, {0}:{1} , TransactionID:{2}",
						prefix, pHeader->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetUserGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetUserGamePlayerInfoRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 25);
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
			Result GetUserGamePlayerInfoRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result GetUserGamePlayerInfoRes::ParseMessage(const MessageHeader* pHeader)

			Result GetUserGamePlayerInfoRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetUserGamePlayerInfoRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetUserGamePlayerInfoRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetUserGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t GetUserGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes )
			{
 				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInAttributes
				);

				return __uiMessageSize;
			}; // size_t GetUserGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InAttributes )

			size_t GetUserGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
			{
 				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				return __uiMessageSize;
			}; // size_t GetUserGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InAttributes);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetUserGamePlayerInfoRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetUserGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )

			Result GetUserGamePlayerInfoRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetUserGamePlayerInfoRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetUserGamePlayerInfo, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Attributes:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result GetUserGamePlayerInfoRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Game game play information
			const MessageID GetGamePlayerInfoCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 26);
			Result GetGamePlayerInfoCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetGamePlayerInfoCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetGamePlayerInfoCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetGamePlayerInfoCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetGamePlayerInfoCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetGamePlayerInfoCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerID)
				);

				return __uiMessageSize;
			}; // size_t GetGamePlayerInfoCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // MessageData* GetGamePlayerInfoCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InPlayerID )

			Result GetGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetGamePlayerInfoCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetGamePlayerInfo, {0}:{1} , TransactionID:{2}, PlayerID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result GetGamePlayerInfoCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetGamePlayerInfoRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 26);
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
			Result GetGamePlayerInfoRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result GetGamePlayerInfoRes::ParseMessage(const MessageHeader* pHeader)

			Result GetGamePlayerInfoRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetGamePlayerInfoRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetGamePlayerInfoRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetGamePlayerInfoRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t GetGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const Array<uint8_t>& InAttributes )
			{
 				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInAttributes
				);

				return __uiMessageSize;
			}; // size_t GetGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const Array<uint8_t>& InAttributes )

			size_t GetGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
			{
 				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				return __uiMessageSize;
			}; // size_t GetGamePlayerInfoRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InPlayerID, InAttributes);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetGamePlayerInfoRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* GetGamePlayerInfoRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )

			Result GetGamePlayerInfoRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetGamePlayerInfoRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetGamePlayerInfo, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerID:{4}, Attributes:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result GetGamePlayerInfoRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player level up event
			const MessageID LevelUpS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 27);
			Result LevelUpS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_CurrentTotalExp);
				protocolCheck(*input >> m_CurrentLevel);

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result LevelUpS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LevelUpS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("CurrentTotalExp", parser.GetCurrentTotalExp());
				variableBuilder.SetVariable("CurrentLevel", parser.GetCurrentLevel());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LevelUpS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LevelUpS2CEvt::CalculateMessageSize( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InCurrentTotalExp)
					+ SerializedSizeOf(InCurrentLevel)
				);

				return __uiMessageSize;
			}; // size_t LevelUpS2CEvt::CalculateMessageSize( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InCurrentTotalExp)
					+ SerializedSizeOf(InCurrentLevel)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LevelUpS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InCurrentTotalExp);
				protocolCheck(*output << InCurrentLevel);

				return hr;
			}; // MessageData* LevelUpS2CEvt::Create( IHeap& memHeap, const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )

			Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LevelUpS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::LevelUp, {0}:{1} , CurrentTotalExp:{2}, CurrentLevel:{3}",
						prefix, pHeader->Length, parser.GetCurrentTotalExp(), parser.GetCurrentLevel()); 
				return ResultCode::SUCCESS;
			}; // Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Change NickName
			const MessageID SetNickNameCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 28);
			Result SetNickNameCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_NickName, ArrayLen));
				protocolCheck(*input >> m_IsCostFree);

				return hr;

			}; // Result SetNickNameCmd::ParseMessage(const MessageHeader* pHeader)

			Result SetNickNameCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNickNameCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("IsCostFree", parser.GetIsCostFree());

				return hr;

			}; // Result SetNickNameCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNickNameCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNickNameCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetNickNameCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InIsCostFree)
				);

				return __uiMessageSize;
			}; // size_t SetNickNameCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InIsCostFree)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNickNameCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNickName);
				protocolCheck(*output << InIsCostFree);

				return hr;
			}; // MessageData* SetNickNameCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )

			Result SetNickNameCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetNickNameCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SetNickName, {0}:{1} , TransactionID:{2}, NickName:{3,60}, IsCostFree:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetNickName(), parser.GetIsCostFree()); 
				return ResultCode::SUCCESS;
			}; // Result SetNickNameCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID SetNickNameRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 28);
			Result SetNickNameRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result SetNickNameRes::ParseMessage(const MessageHeader* pHeader)

			Result SetNickNameRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SetNickNameRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result SetNickNameRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetNickNameRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetNickNameRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetNickNameRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				return __uiMessageSize;
			}; // size_t SetNickNameRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SetNickNameRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
			}; // MessageData* SetNickNameRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )

			Result SetNickNameRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetNickNameRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SetNickName, {0}:{1} , TransactionID:{2}, Result:{3:X8}, TotalGem:{4}, TotalGameMoney:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result SetNickNameRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Create Party
			const MessageID CreatePartyCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 29);
			Result CreatePartyCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result CreatePartyCmd::ParseMessage(const MessageHeader* pHeader)

			Result CreatePartyCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreatePartyCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result CreatePartyCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreatePartyCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreatePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CreatePartyCmd::CalculateMessageSize( const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t CreatePartyCmd::CalculateMessageSize( const uint64_t &InTransactionID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreatePartyCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* CreatePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result CreatePartyCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreatePartyCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CreateParty, {0}:{1} , TransactionID:{2}",
						prefix, pHeader->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result CreatePartyCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID CreatePartyRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 29);
			Result CreatePartyRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PartyUID);

				return hr;

			}; // Result CreatePartyRes::ParseMessage(const MessageHeader* pHeader)

			Result CreatePartyRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreatePartyRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());

				return hr;

			}; // Result CreatePartyRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreatePartyRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreatePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CreatePartyRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPartyUID)
				);

				return __uiMessageSize;
			}; // size_t CreatePartyRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPartyUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreatePartyRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPartyUID);

				return hr;
			}; // MessageData* CreatePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )

			Result CreatePartyRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreatePartyRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CreateParty, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PartyUID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPartyUID()); 
				return ResultCode::SUCCESS;
			}; // Result CreatePartyRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Join party
			const MessageID JoinPartyCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 30);
			Result JoinPartyCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_InviterID);

				return hr;

			}; // Result JoinPartyCmd::ParseMessage(const MessageHeader* pHeader)

			Result JoinPartyCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinPartyCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());

				return hr;

			}; // Result JoinPartyCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPartyCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinPartyCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InInviterID)
				);

				return __uiMessageSize;
			}; // size_t JoinPartyCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InInviterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinPartyCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InInviterID);

				return hr;
			}; // MessageData* JoinPartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )

			Result JoinPartyCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinPartyCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinParty, {0}:{1} , TransactionID:{2}, PartyUID:{3}, InviterID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPartyUID(), parser.GetInviterID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPartyCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID JoinPartyRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 30);
			Result JoinPartyRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result JoinPartyRes::ParseMessage(const MessageHeader* pHeader)

			Result JoinPartyRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinPartyRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());
				variableBuilder.SetVariable("ChatHistoryData", parser.GetChatHistoryData());

				return hr;

			}; // Result JoinPartyRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPartyRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinPartyRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPartyLeaderID)
					+ SerializedSizeOf(InChatHistoryData)
				);

				return __uiMessageSize;
			}; // size_t JoinPartyRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPartyLeaderID)
					+ SerializedSizeOf(InChatHistoryData)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinPartyRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPartyLeaderID);
				protocolCheck(*output << InChatHistoryData);

				return hr;
			}; // MessageData* JoinPartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )

			Result JoinPartyRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinPartyRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinParty, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PartyUID:{4}, PartyLeaderID:{5}, ChatHistoryData:{6,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPartyUID(), parser.GetPartyLeaderID(), parser.GetChatHistoryData()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPartyRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player Joined event
			const MessageID PartyPlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 31);
			Result PartyPlayerJoinedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_JoinedPlayer);

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PartyPlayerJoinedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerJoinedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("JoinedPlayer", "PlayerInformation", parser.GetJoinedPlayer());

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerJoinedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyPlayerJoinedS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InJoinedPlayer)
				);

				return __uiMessageSize;
			}; // size_t PartyPlayerJoinedS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InJoinedPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerJoinedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InJoinedPlayer);

				return hr;
			}; // MessageData* PartyPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )

			Result PartyPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyPlayerJoinedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyPlayerJoined, {0}:{1} , PartyUID:{2}, JoinedPlayer:{3}",
						prefix, pHeader->Length, parser.GetPartyUID(), parser.GetJoinedPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result PartyPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Party leader changed event
			const MessageID PartyLeaderChangedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 32);
			Result PartyLeaderChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_NewLeaderID);

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PartyLeaderChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyLeaderChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyLeaderChangedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyLeaderChangedS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InNewLeaderID)
				);

				return __uiMessageSize;
			}; // size_t PartyLeaderChangedS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InNewLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyLeaderChangedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InNewLeaderID);

				return hr;
			}; // MessageData* PartyLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InNewLeaderID )

			Result PartyLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyLeaderChangedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyLeaderChanged, {0}:{1} , PartyUID:{2}, NewLeaderID:{3}",
						prefix, pHeader->Length, parser.GetPartyUID(), parser.GetNewLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Leave party command
			const MessageID LeavePartyCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 33);
			Result LeavePartyCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result LeavePartyCmd::ParseMessage(const MessageHeader* pHeader)

			Result LeavePartyCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeavePartyCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result LeavePartyCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeavePartyCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeavePartyCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LeavePartyCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPlayerID)
				);

				return __uiMessageSize;
			}; // size_t LeavePartyCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeavePartyCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // MessageData* LeavePartyCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )

			Result LeavePartyCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LeavePartyCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::LeaveParty, {0}:{1} , TransactionID:{2}, PartyUID:{3}, PlayerID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPartyUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result LeavePartyCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID LeavePartyRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 33);
			Result LeavePartyRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeavePartyRes::ParseMessage(const MessageHeader* pHeader)

			Result LeavePartyRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeavePartyRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeavePartyRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeavePartyRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeavePartyRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LeavePartyRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t LeavePartyRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeavePartyRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* LeavePartyRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result LeavePartyRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LeavePartyRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::LeaveParty, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result LeavePartyRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Party Player left event
			const MessageID PartyPlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 34);
			Result PartyPlayerLeftS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_LeftPlayerID);

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PartyPlayerLeftS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerLeftS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyPlayerLeftS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InLeftPlayerID)
				);

				return __uiMessageSize;
			}; // size_t PartyPlayerLeftS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InLeftPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerLeftS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InLeftPlayerID);

				return hr;
			}; // MessageData* PartyPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )

			Result PartyPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyPlayerLeftS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyPlayerLeft, {0}:{1} , PartyUID:{2}, LeftPlayerID:{3}",
						prefix, pHeader->Length, parser.GetPartyUID(), parser.GetLeftPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Kick player from the party
			const MessageID PartyKickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 35);
			Result PartyKickPlayerCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerToKick);

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessage(const MessageHeader* pHeader)

			Result PartyKickPlayerCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyKickPlayerCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyKickPlayerCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyKickPlayerCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerToKick)
				);

				return __uiMessageSize;
			}; // size_t PartyKickPlayerCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerToKick)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyKickPlayerCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerToKick);

				return hr;
			}; // MessageData* PartyKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )

			Result PartyKickPlayerCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyKickPlayerCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyKickPlayer, {0}:{1} , TransactionID:{2}, PartyUID:{3}, PlayerID:{4}, PlayerToKick:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPartyUID(), parser.GetPlayerID(), parser.GetPlayerToKick()); 
				return ResultCode::SUCCESS;
			}; // Result PartyKickPlayerCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID PartyKickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 35);
			Result PartyKickPlayerRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessage(const MessageHeader* pHeader)

			Result PartyKickPlayerRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyKickPlayerRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyKickPlayerRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyKickPlayerRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t PartyKickPlayerRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyKickPlayerRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* PartyKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result PartyKickPlayerRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyKickPlayerRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyKickPlayer, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyKickPlayerRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Party Player kicked message
			const MessageID PartyPlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 36);
			Result PartyPlayerKickedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PartyUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PartyPlayerKickedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyPlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyPlayerKickedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyPlayerKickedS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				return __uiMessageSize;
			}; // size_t PartyPlayerKickedS2CEvt::CalculateMessageSize( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPartyUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyPlayerKickedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPartyUID);
				protocolCheck(*output << InKickedPlayerID);

				return hr;
			}; // MessageData* PartyPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )

			Result PartyPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyPlayerKickedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyPlayerKicked, {0}:{1} , PartyUID:{2}, KickedPlayerID:{3}",
						prefix, pHeader->Length, parser.GetPartyUID(), parser.GetKickedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Invite a player to the party
			const MessageID PartyInviteCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 37);
			Result PartyInviteCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InviteTargetID);

				return hr;

			}; // Result PartyInviteCmd::ParseMessage(const MessageHeader* pHeader)

			Result PartyInviteCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InviteTargetID", parser.GetInviteTargetID());

				return hr;

			}; // Result PartyInviteCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyInviteCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInviteTargetID)
				);

				return __uiMessageSize;
			}; // size_t PartyInviteCmd::CalculateMessageSize( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInviteTargetID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInviteTargetID);

				return hr;
			}; // MessageData* PartyInviteCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AccountID &InInviteTargetID )

			Result PartyInviteCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyInviteCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyInvite, {0}:{1} , TransactionID:{2}, InviteTargetID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetInviteTargetID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyInviteCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID PartyInviteRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 37);
			Result PartyInviteRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyInviteRes::ParseMessage(const MessageHeader* pHeader)

			Result PartyInviteRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyInviteRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyInviteRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t PartyInviteRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* PartyInviteRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result PartyInviteRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyInviteRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyInvite, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyInviteRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Party invite requested
			const MessageID PartyInviteRequestedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 38);
			Result PartyInviteRequestedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_InviterID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_InviterName, ArrayLen));
				protocolCheck(*input >> m_PartyToJoinUID);

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PartyInviteRequestedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyInviteRequestedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("InviterName", parser.GetInviterName());
				variableBuilder.SetVariable("PartyToJoinUID", parser.GetPartyToJoinUID());

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyInviteRequestedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyInviteRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyInviteRequestedS2CEvt::CalculateMessageSize( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InInviterName)
					+ SerializedSizeOf(InPartyToJoinUID)
				);

				return __uiMessageSize;
			}; // size_t PartyInviteRequestedS2CEvt::CalculateMessageSize( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InInviterName)
					+ SerializedSizeOf(InPartyToJoinUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyInviteRequestedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InInviterID);
				protocolCheck(*output << InInviterName);
				protocolCheck(*output << InPartyToJoinUID);

				return hr;
			}; // MessageData* PartyInviteRequestedS2CEvt::Create( IHeap& memHeap, const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )

			Result PartyInviteRequestedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyInviteRequestedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyInviteRequested, {0}:{1} , InviterID:{2}, InviterName:{3,60}, PartyToJoinUID:{4}",
						prefix, pHeader->Length, parser.GetInviterID(), parser.GetInviterName(), parser.GetPartyToJoinUID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyInviteRequestedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Send Party quick chat message
			const MessageID PartyQuickChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 39);
			Result PartyQuickChatMessageCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_QuickChatID);

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessage(const MessageHeader* pHeader)

			Result PartyQuickChatMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyQuickChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InQuickChatID)
				);

				return __uiMessageSize;
			}; // size_t PartyQuickChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InQuickChatID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InQuickChatID);

				return hr;
			}; // MessageData* PartyQuickChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InQuickChatID )

			Result PartyQuickChatMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyQuickChatMessageCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyQuickChatMessage, {0}:{1} , TransactionID:{2}, QuickChatID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetQuickChatID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyQuickChatMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID PartyQuickChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 39);
			Result PartyQuickChatMessageRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessage(const MessageHeader* pHeader)

			Result PartyQuickChatMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyQuickChatMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t PartyQuickChatMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* PartyQuickChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result PartyQuickChatMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyQuickChatMessageRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyQuickChatMessage, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyQuickChatMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Party Chatting message event
			const MessageID PartyQuickChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 40);
			Result PartyQuickChatMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(*input >> m_QuickChatID);

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PartyQuickChatMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyQuickChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("QuickChatID", parser.GetQuickChatID());

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyQuickChatMessageS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyQuickChatMessageS2CEvt::CalculateMessageSize( const AccountID &InSenderID, const uint32_t &InQuickChatID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InQuickChatID)
				);

				return __uiMessageSize;
			}; // size_t PartyQuickChatMessageS2CEvt::CalculateMessageSize( const AccountID &InSenderID, const uint32_t &InQuickChatID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InQuickChatID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyQuickChatMessageS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InQuickChatID);

				return hr;
			}; // MessageData* PartyQuickChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const uint32_t &InQuickChatID )

			Result PartyQuickChatMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyQuickChatMessageS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyQuickChatMessage, {0}:{1} , SenderID:{2}, QuickChatID:{3}",
						prefix, pHeader->Length, parser.GetSenderID(), parser.GetQuickChatID()); 
				return ResultCode::SUCCESS;
			}; // Result PartyQuickChatMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Party chatting
			const MessageID PartyChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 41);
			Result PartyChatMessageCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessage(const MessageHeader* pHeader)

			Result PartyChatMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InChatMessage )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t PartyChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InChatMessage )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* PartyChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChatMessage )

			Result PartyChatMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyChatMessageCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyChatMessage, {0}:{1} , TransactionID:{2}, ChatMessage:{3,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result PartyChatMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID PartyChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 41);
			Result PartyChatMessageRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PartyChatMessageRes::ParseMessage(const MessageHeader* pHeader)

			Result PartyChatMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PartyChatMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyChatMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t PartyChatMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* PartyChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result PartyChatMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyChatMessageRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyChatMessage, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PartyChatMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Party Chatting message event
			const MessageID PartyChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 42);
			Result PartyChatMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_SenderID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SenderName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PartyChatMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PartyChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("SenderName", parser.GetSenderName());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PartyChatMessageS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PartyChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PartyChatMessageS2CEvt::CalculateMessageSize( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InSenderName)
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t PartyChatMessageS2CEvt::CalculateMessageSize( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InSenderName)
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::PartyChatMessageS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InSenderName);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* PartyChatMessageS2CEvt::Create( IHeap& memHeap, const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )

			Result PartyChatMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PartyChatMessageS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::PartyChatMessage, {0}:{1} , SenderID:{2}, SenderName:{3,60}, ChatMessage:{4,60}",
						prefix, pHeader->Length, parser.GetSenderID(), parser.GetSenderName(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result PartyChatMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Join to a game instance
			const MessageID JoinGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 43);
			Result JoinGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InsUID);

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)

			Result JoinGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InInsUID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInsUID)
				);

				return __uiMessageSize;
			}; // size_t JoinGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InInsUID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInsUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameInstanceCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInsUID);

				return hr;
			}; // MessageData* JoinGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InInsUID )

			Result JoinGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinGameInstanceCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinGameInstance, {0}:{1} , TransactionID:{2}, InsUID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetInsUID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID JoinGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 43);
			Result JoinGameInstanceRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_InsUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ServerPublicAddress, ArrayLen));

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessage(const MessageHeader* pHeader)

			Result JoinGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());
				variableBuilder.SetVariable("ServerPublicAddress", parser.GetServerPublicAddress());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InInsUID)
					+ SerializedSizeOf(InServerPublicAddress)
				);

				return __uiMessageSize;
			}; // size_t JoinGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress )


			MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InInsUID)
					+ SerializedSizeOf(InServerPublicAddress)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinGameInstanceRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InInsUID);
				protocolCheck(*output << InServerPublicAddress);

				return hr;
			}; // MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress )

			Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinGameInstanceRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinGameInstance, {0}:{1} , TransactionID:{2}, Result:{3:X8}, InsUID:{4}, ServerPublicAddress:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetInsUID(), parser.GetServerPublicAddress()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Leave game instance
			const MessageID LeaveGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 44);
			Result LeaveGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_InsUID);

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)

			Result LeaveGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("InsUID", parser.GetInsUID());

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LeaveGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameInstanceCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LeaveGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InInsUID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInsUID)
				);

				return __uiMessageSize;
			}; // size_t LeaveGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InInsUID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InInsUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameInstanceCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InInsUID);

				return hr;
			}; // MessageData* LeaveGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InInsUID )

			Result LeaveGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LeaveGameInstanceCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::LeaveGameInstance, {0}:{1} , TransactionID:{2}, InsUID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetInsUID()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID LeaveGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 44);
			Result LeaveGameInstanceRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessage(const MessageHeader* pHeader)

			Result LeaveGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LeaveGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveGameInstanceRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LeaveGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t LeaveGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveGameInstanceRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* LeaveGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result LeaveGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LeaveGameInstanceRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::LeaveGameInstance, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Search game instance
			const MessageID SearchGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 45);
			Result SearchGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SearchKeyword, ArrayLen));
				protocolCheck(*input >> m_ZoneTableID);

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)

			Result SearchGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SearchGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("SearchKeyword", parser.GetSearchKeyword());
				variableBuilder.SetVariable("ZoneTableID", parser.GetZoneTableID());

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SearchGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SearchGameInstanceCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SearchGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SearchGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InSearchKeyword)
					+ SerializedSizeOf(InZoneTableID)
				);

				return __uiMessageSize;
			}; // size_t SearchGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )


			MessageData* SearchGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InSearchKeyword)
					+ SerializedSizeOf(InZoneTableID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SearchGameInstanceCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InSearchKeyword);
				protocolCheck(*output << InZoneTableID);

				return hr;
			}; // MessageData* SearchGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )

			Result SearchGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SearchGameInstanceCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SearchGameInstance, {0}:{1} , TransactionID:{2}, SearchKeyword:{3,60}, ZoneTableID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetSearchKeyword(), parser.GetZoneTableID()); 
				return ResultCode::SUCCESS;
			}; // Result SearchGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID SearchGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 45);
			Result SearchGameInstanceRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(m_GameInstances));

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessage(const MessageHeader* pHeader)

			Result SearchGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SearchGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameInstances", parser.GetGameInstances());

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SearchGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SearchGameInstanceRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SearchGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SearchGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InGameInstances)
				);

				return __uiMessageSize;
			}; // size_t SearchGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InGameInstances)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SearchGameInstanceRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameInstances);

				return hr;
			}; // MessageData* SearchGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )

			Result SearchGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SearchGameInstanceRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SearchGameInstance, {0}:{1} , TransactionID:{2}, Result:{3:X8}, GameInstances:{4,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameInstances()); 
				return ResultCode::SUCCESS;
			}; // Result SearchGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Search game instance
			const MessageID GetCharacterDataInGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 46);
			Result GetCharacterDataInGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetCharacterDataInGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataInGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataInGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataInGameInstanceCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataInGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetCharacterDataInGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
				);

				return __uiMessageSize;
			}; // size_t GetCharacterDataInGameInstanceCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataInGameInstanceCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // MessageData* GetCharacterDataInGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )

			Result GetCharacterDataInGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetCharacterDataInGameInstanceCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetCharacterDataInGameInstance, {0}:{1} , TransactionID:{2}, GameInsUID:{3}, PlayerID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetGameInsUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataInGameInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetCharacterDataInGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 46);
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
			Result GetCharacterDataInGameInstanceRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessage(const MessageHeader* pHeader)

			Result GetCharacterDataInGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataInGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("GameInstances", "VariableTable", parser.GetGameInstancesRaw());

				return hr;

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataInGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataInGameInstanceRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataInGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t GetCharacterDataInGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const Array<uint8_t>& InGameInstances )
			{
 				uint16_t serializedSizeOfInGameInstances = static_cast<uint16_t>(SerializedSizeOf(InGameInstances)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInGameInstances
				);

				return __uiMessageSize;
			}; // size_t GetCharacterDataInGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const Array<uint8_t>& InGameInstances )

			size_t GetCharacterDataInGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
			{
 				uint16_t serializedSizeOfInGameInstances = static_cast<uint16_t>(SerializedSizeOf(InGameInstances)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInGameInstances
				);

				return __uiMessageSize;
			}; // size_t GetCharacterDataInGameInstanceRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InPlayerID, InGameInstances);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataInGameInstanceRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInGameInstances
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataInGameInstanceRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInGameInstances));
				protocolCheck(*output << InGameInstances);

				return hr;
			}; // MessageData* GetCharacterDataInGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )

			Result GetCharacterDataInGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetCharacterDataInGameInstanceRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetCharacterDataInGameInstance, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayerID:{4}, GameInstances:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayerID(), parser.GetGameInstances()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataInGameInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Request Game match
			const MessageID RequestGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 47);
			Result RequestGameMatchCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_NumPlayer);
				protocolCheck(*input >> m_RequestRole);

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessage(const MessageHeader* pHeader)

			Result RequestGameMatchCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestGameMatchCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("NumPlayer", parser.GetNumPlayer());
				variableBuilder.SetVariable("RequestRole", parser.GetRequestRole());

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestGameMatchCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RequestGameMatchCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNumPlayer)
					+ SerializedSizeOf(InRequestRole)
				);

				return __uiMessageSize;
			}; // size_t RequestGameMatchCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InNumPlayer)
					+ SerializedSizeOf(InRequestRole)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestGameMatchCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InNumPlayer);
				protocolCheck(*output << InRequestRole);

				return hr;
			}; // MessageData* RequestGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )

			Result RequestGameMatchCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestGameMatchCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RequestGameMatch, {0}:{1} , TransactionID:{2}, NumPlayer:{3}, RequestRole:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetNumPlayer(), parser.GetRequestRole()); 
				return ResultCode::SUCCESS;
			}; // Result RequestGameMatchCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID RequestGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 47);
			Result RequestGameMatchRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_TotalGem);
				protocolCheck(*input >> m_TotalGameMoney);

				return hr;

			}; // Result RequestGameMatchRes::ParseMessage(const MessageHeader* pHeader)

			Result RequestGameMatchRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestGameMatchRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
				variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());

				return hr;

			}; // Result RequestGameMatchRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestGameMatchRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RequestGameMatchRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				return __uiMessageSize;
			}; // size_t RequestGameMatchRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTotalGem)
					+ SerializedSizeOf(InTotalGameMoney)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestGameMatchRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTotalGem);
				protocolCheck(*output << InTotalGameMoney);

				return hr;
			}; // MessageData* RequestGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )

			Result RequestGameMatchRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestGameMatchRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RequestGameMatch, {0}:{1} , TransactionID:{2}, Result:{3:X8}, TotalGem:{4}, TotalGameMoney:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result RequestGameMatchRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Game matched
			const MessageID GameMatchedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 48);
			Result GameMatchedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result GameMatchedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result GameMatchedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

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

			}; // Result GameMatchedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GameMatchedS2CEvt::CalculateMessageSize( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
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

				return __uiMessageSize;
			}; // size_t GameMatchedS2CEvt::CalculateMessageSize( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
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
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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

			Result GameMatchedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GameMatchedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GameMatched, {0}:{1} , InsUID:{2}, TimeStamp:{3}, GameState:{4}, Day:{5}, MaxPlayer:{6}, PlayerIndex:{7}, PlayerCharacter:{8}, Role:{9}, Dead:{10}, ChatHistoryData:{11,30}, GameLogData:{12,30}, Stamina:{13}, TotalGem:{14}, TotalGameMoney:{15}",
						prefix, pHeader->Length, parser.GetInsUID(), parser.GetTimeStamp(), (int)parser.GetGameState(), parser.GetDay(), parser.GetMaxPlayer(), parser.GetPlayerIndex(), parser.GetPlayerCharacter(), parser.GetRole(), parser.GetDead(), parser.GetChatHistoryData(), parser.GetGameLogData(), parser.GetStamina(), parser.GetTotalGem(), parser.GetTotalGameMoney()); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Game match failed
			const MessageID GameMatchFailedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 49);
			Result GameMatchFailedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_FailedReason);

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result GameMatchFailedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchFailedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("FailedReason", parser.GetFailedReason());

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchFailedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchFailedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GameMatchFailedS2CEvt::CalculateMessageSize( const Result &InFailedReason )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InFailedReason)
				);

				return __uiMessageSize;
			}; // size_t GameMatchFailedS2CEvt::CalculateMessageSize( const Result &InFailedReason )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InFailedReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchFailedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InFailedReason);

				return hr;
			}; // MessageData* GameMatchFailedS2CEvt::Create( IHeap& memHeap, const Result &InFailedReason )

			Result GameMatchFailedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GameMatchFailedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GameMatchFailed, {0}:{1} , FailedReason:{2:X8}",
						prefix, pHeader->Length, parser.GetFailedReason()); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchFailedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Game matching started
			const MessageID GameMatchingStartedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 50);
			Result GameMatchingStartedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);



				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result GameMatchingStartedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchingStartedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));


				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchingStartedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GameMatchingStartedS2CEvt::CalculateMessageSize(  )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
				);

				return __uiMessageSize;
			}; // size_t GameMatchingStartedS2CEvt::CalculateMessageSize(  )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchingStartedS2CEvt::MID, __uiMessageSize ) );

				return hr;
			}; // MessageData* GameMatchingStartedS2CEvt::Create( IHeap& memHeap )

			Result GameMatchingStartedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GameMatchingStartedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GameMatchingStarted, {0}:{1} ",
						prefix, pHeader->Length); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchingStartedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Cancel Game match
			const MessageID CancelGameMatchCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 51);
			Result CancelGameMatchCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessage(const MessageHeader* pHeader)

			Result CancelGameMatchCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CancelGameMatchCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CancelGameMatchCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CancelGameMatchCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CancelGameMatchCmd::CalculateMessageSize( const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t CancelGameMatchCmd::CalculateMessageSize( const uint64_t &InTransactionID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CancelGameMatchCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* CancelGameMatchCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result CancelGameMatchCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CancelGameMatchCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CancelGameMatch, {0}:{1} , TransactionID:{2}",
						prefix, pHeader->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result CancelGameMatchCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID CancelGameMatchRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 51);
			Result CancelGameMatchRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result CancelGameMatchRes::ParseMessage(const MessageHeader* pHeader)

			Result CancelGameMatchRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CancelGameMatchRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result CancelGameMatchRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CancelGameMatchRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CancelGameMatchRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CancelGameMatchRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t CancelGameMatchRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CancelGameMatchRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* CancelGameMatchRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result CancelGameMatchRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CancelGameMatchRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CancelGameMatch, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result CancelGameMatchRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: game matching canceled
			const MessageID GameMatchingCanceledS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 52);
			Result GameMatchingCanceledS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);



				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result GameMatchingCanceledS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GameMatchingCanceledS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));


				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GameMatchingCanceledS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GameMatchingCanceledS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GameMatchingCanceledS2CEvt::CalculateMessageSize(  )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
				);

				return __uiMessageSize;
			}; // size_t GameMatchingCanceledS2CEvt::CalculateMessageSize(  )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GameMatchingCanceledS2CEvt::MID, __uiMessageSize ) );

				return hr;
			}; // MessageData* GameMatchingCanceledS2CEvt::Create( IHeap& memHeap )

			Result GameMatchingCanceledS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GameMatchingCanceledS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GameMatchingCanceled, {0}:{1} ",
						prefix, pHeader->Length); 
				return ResultCode::SUCCESS;
			}; // Result GameMatchingCanceledS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Buy shop item prepare
			const MessageID BuyShopItemPrepareCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 53);
			Result BuyShopItemPrepareCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ShopItemID);

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessage(const MessageHeader* pHeader)

			Result BuyShopItemPrepareCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemPrepareCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemPrepareCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemPrepareCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t BuyShopItemPrepareCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InShopItemID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InShopItemID)
				);

				return __uiMessageSize;
			}; // size_t BuyShopItemPrepareCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InShopItemID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InShopItemID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemPrepareCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InShopItemID);

				return hr;
			}; // MessageData* BuyShopItemPrepareCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID )

			Result BuyShopItemPrepareCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				BuyShopItemPrepareCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::BuyShopItemPrepare, {0}:{1} , TransactionID:{2}, ShopItemID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetShopItemID()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemPrepareCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID BuyShopItemPrepareRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 53);
			Result BuyShopItemPrepareRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ShopItemID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PurchaseID, ArrayLen));

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessage(const MessageHeader* pHeader)

			Result BuyShopItemPrepareRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemPrepareRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());
				variableBuilder.SetVariable("PurchaseID", parser.GetPurchaseID());

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemPrepareRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemPrepareRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t BuyShopItemPrepareRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InShopItemID)
					+ SerializedSizeOf(InPurchaseID)
				);

				return __uiMessageSize;
			}; // size_t BuyShopItemPrepareRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InShopItemID)
					+ SerializedSizeOf(InPurchaseID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemPrepareRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InShopItemID);
				protocolCheck(*output << InPurchaseID);

				return hr;
			}; // MessageData* BuyShopItemPrepareRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )

			Result BuyShopItemPrepareRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				BuyShopItemPrepareRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::BuyShopItemPrepare, {0}:{1} , TransactionID:{2}, Result:{3:X8}, ShopItemID:{4}, PurchaseID:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetShopItemID(), parser.GetPurchaseID()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemPrepareRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Buy shop item
			const MessageID BuyShopItemCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 54);
			Result BuyShopItemCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result BuyShopItemCmd::ParseMessage(const MessageHeader* pHeader)

			Result BuyShopItemCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());
				variableBuilder.SetVariable("Platform", parser.GetPlatform());
				variableBuilder.SetVariable("PackageName", parser.GetPackageName());
				variableBuilder.SetVariable("PurchaseTransactionID", parser.GetPurchaseTransactionID());
				variableBuilder.SetVariable("PurchaseToken", parser.GetPurchaseToken());

				return hr;

			}; // Result BuyShopItemCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t BuyShopItemCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InShopItemID)
					+ SerializedSizeOf(InPlatform)
					+ SerializedSizeOf(InPackageName)
					+ SerializedSizeOf(InPurchaseTransactionID)
					+ SerializedSizeOf(InPurchaseToken)
				);

				return __uiMessageSize;
			}; // size_t BuyShopItemCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InShopItemID)
					+ SerializedSizeOf(InPlatform)
					+ SerializedSizeOf(InPackageName)
					+ SerializedSizeOf(InPurchaseTransactionID)
					+ SerializedSizeOf(InPurchaseToken)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InShopItemID);
				protocolCheck(*output << InPlatform);
				protocolCheck(*output << InPackageName);
				protocolCheck(*output << InPurchaseTransactionID);
				protocolCheck(*output << InPurchaseToken);

				return hr;
			}; // MessageData* BuyShopItemCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )

			Result BuyShopItemCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				BuyShopItemCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::BuyShopItem, {0}:{1} , TransactionID:{2}, ShopItemID:{3}, Platform:{4,60}, PackageName:{5,60}, PurchaseTransactionID:{6,60}, PurchaseToken:{7,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetShopItemID(), parser.GetPlatform(), parser.GetPackageName(), parser.GetPurchaseTransactionID(), parser.GetPurchaseToken()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID BuyShopItemRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 54);
			Result BuyShopItemRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ShopItemID);

				return hr;

			}; // Result BuyShopItemRes::ParseMessage(const MessageHeader* pHeader)

			Result BuyShopItemRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				BuyShopItemRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ShopItemID", parser.GetShopItemID());

				return hr;

			}; // Result BuyShopItemRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) BuyShopItemRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result BuyShopItemRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t BuyShopItemRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InShopItemID)
				);

				return __uiMessageSize;
			}; // size_t BuyShopItemRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InShopItemID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::BuyShopItemRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InShopItemID);

				return hr;
			}; // MessageData* BuyShopItemRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )

			Result BuyShopItemRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				BuyShopItemRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::BuyShopItem, {0}:{1} , TransactionID:{2}, Result:{3:X8}, ShopItemID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetShopItemID()); 
				return ResultCode::SUCCESS;
			}; // Result BuyShopItemRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Create or Join Chat channel
			const MessageID CreateOrJoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 55);
			Result CreateOrJoinChatChannelCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChannelName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_Passcode, ArrayLen));

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessage(const MessageHeader* pHeader)

			Result CreateOrJoinChatChannelCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateOrJoinChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChannelName", parser.GetChannelName());
				variableBuilder.SetVariable("Passcode", parser.GetPasscode());

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateOrJoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CreateOrJoinChatChannelCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChannelName)
					+ SerializedSizeOf(InPasscode)
				);

				return __uiMessageSize;
			}; // size_t CreateOrJoinChatChannelCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChannelName)
					+ SerializedSizeOf(InPasscode)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateOrJoinChatChannelCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChannelName);
				protocolCheck(*output << InPasscode);

				return hr;
			}; // MessageData* CreateOrJoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )

			Result CreateOrJoinChatChannelCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateOrJoinChatChannelCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CreateOrJoinChatChannel, {0}:{1} , TransactionID:{2}, ChannelName:{3,60}, Passcode:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetChannelName(), parser.GetPasscode()); 
				return ResultCode::SUCCESS;
			}; // Result CreateOrJoinChatChannelCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID CreateOrJoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 55);
			Result CreateOrJoinChatChannelRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_ChannelLeaderID);

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessage(const MessageHeader* pHeader)

			Result CreateOrJoinChatChannelRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateOrJoinChatChannelRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("ChannelLeaderID", parser.GetChannelLeaderID());

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateOrJoinChatChannelRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateOrJoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CreateOrJoinChatChannelRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InChannelLeaderID)
				);

				return __uiMessageSize;
			}; // size_t CreateOrJoinChatChannelRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InChannelLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateOrJoinChatChannelRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InChannelLeaderID);

				return hr;
			}; // MessageData* CreateOrJoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )

			Result CreateOrJoinChatChannelRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateOrJoinChatChannelRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CreateOrJoinChatChannel, {0}:{1} , TransactionID:{2}, Result:{3:X8}, ChatUID:{4}, ChannelLeaderID:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetChatUID(), parser.GetChannelLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateOrJoinChatChannelRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Join
			const MessageID JoinChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 56);
			Result JoinChatChannelCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_InviterID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_Passcode, ArrayLen));

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessage(const MessageHeader* pHeader)

			Result JoinChatChannelCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("InviterID", parser.GetInviterID());
				variableBuilder.SetVariable("Passcode", parser.GetPasscode());

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinChatChannelCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinChatChannelCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InPasscode)
				);

				return __uiMessageSize;
			}; // size_t JoinChatChannelCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InInviterID)
					+ SerializedSizeOf(InPasscode)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InInviterID);
				protocolCheck(*output << InPasscode);

				return hr;
			}; // MessageData* JoinChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )

			Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinChatChannelCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinChatChannel, {0}:{1} , TransactionID:{2}, ChatUID:{3}, InviterID:{4}, Passcode:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetInviterID(), parser.GetPasscode()); 
				return ResultCode::SUCCESS;
			}; // Result JoinChatChannelCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID JoinChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 56);
			Result JoinChatChannelRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_ChannelLeaderID);

				return hr;

			}; // Result JoinChatChannelRes::ParseMessage(const MessageHeader* pHeader)

			Result JoinChatChannelRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinChatChannelRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("ChannelLeaderID", parser.GetChannelLeaderID());

				return hr;

			}; // Result JoinChatChannelRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinChatChannelRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinChatChannelRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InChannelLeaderID)
				);

				return __uiMessageSize;
			}; // size_t JoinChatChannelRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InChannelLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::JoinChatChannelRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InChannelLeaderID);

				return hr;
			}; // MessageData* JoinChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )

			Result JoinChatChannelRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinChatChannelRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::JoinChatChannel, {0}:{1} , TransactionID:{2}, Result:{3:X8}, ChatUID:{4}, ChannelLeaderID:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetChatUID(), parser.GetChannelLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result JoinChatChannelRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player Joined event
			const MessageID ChatChannelPlayerJoinedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 57);
			Result ChatChannelPlayerJoinedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_JoinedPlayer);

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerJoinedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("JoinedPlayer", "PlayerInformation", parser.GetJoinedPlayer());

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerJoinedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ChatChannelPlayerJoinedS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InJoinedPlayer)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelPlayerJoinedS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InJoinedPlayer)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerJoinedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InJoinedPlayer);

				return hr;
			}; // MessageData* ChatChannelPlayerJoinedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )

			Result ChatChannelPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelPlayerJoinedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelPlayerJoined, {0}:{1} , ChatUID:{2}, JoinedPlayer:{3}",
						prefix, pHeader->Length, parser.GetChatUID(), parser.GetJoinedPlayer()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelPlayerJoinedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: ChatChannel leader changed event
			const MessageID ChatChannelLeaderChangedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 58);
			Result ChatChannelLeaderChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_NewLeaderID);

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelLeaderChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("NewLeaderID", parser.GetNewLeaderID());

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelLeaderChangedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ChatChannelLeaderChangedS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InNewLeaderID)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelLeaderChangedS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InNewLeaderID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InNewLeaderID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelLeaderChangedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InNewLeaderID);

				return hr;
			}; // MessageData* ChatChannelLeaderChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InNewLeaderID )

			Result ChatChannelLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelLeaderChangedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelLeaderChanged, {0}:{1} , ChatUID:{2}, NewLeaderID:{3}",
						prefix, pHeader->Length, parser.GetChatUID(), parser.GetNewLeaderID()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelLeaderChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Leave ChatChannel command
			const MessageID LeaveChatChannelCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 59);
			Result LeaveChatChannelCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessage(const MessageHeader* pHeader)

			Result LeaveChatChannelCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveChatChannelCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveChatChannelCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveChatChannelCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LeaveChatChannelCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InPlayerID)
				);

				return __uiMessageSize;
			}; // size_t LeaveChatChannelCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveChatChannelCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // MessageData* LeaveChatChannelCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )

			Result LeaveChatChannelCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LeaveChatChannelCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::LeaveChatChannel, {0}:{1} , TransactionID:{2}, ChatUID:{3}, PlayerID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveChatChannelCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID LeaveChatChannelRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 59);
			Result LeaveChatChannelRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessage(const MessageHeader* pHeader)

			Result LeaveChatChannelRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LeaveChatChannelRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveChatChannelRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveChatChannelRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LeaveChatChannelRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t LeaveChatChannelRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::LeaveChatChannelRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* LeaveChatChannelRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result LeaveChatChannelRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LeaveChatChannelRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::LeaveChatChannel, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveChatChannelRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: ChatChannel Player left event
			const MessageID ChatChannelPlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 60);
			Result ChatChannelPlayerLeftS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_LeftPlayerID);

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerLeftS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ChatChannelPlayerLeftS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InLeftPlayerID)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelPlayerLeftS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InLeftPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerLeftS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InLeftPlayerID);

				return hr;
			}; // MessageData* ChatChannelPlayerLeftS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InLeftPlayerID )

			Result ChatChannelPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelPlayerLeftS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelPlayerLeft, {0}:{1} , ChatUID:{2}, LeftPlayerID:{3}",
						prefix, pHeader->Length, parser.GetChatUID(), parser.GetLeftPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelPlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Kick player from the ChatChannel
			const MessageID ChatChannelKickPlayerCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 61);
			Result ChatChannelKickPlayerCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerToKick);

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelKickPlayerCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelKickPlayerCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerToKick", parser.GetPlayerToKick());

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelKickPlayerCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelKickPlayerCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ChatChannelKickPlayerCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerToKick)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelKickPlayerCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerToKick)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelKickPlayerCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerToKick);

				return hr;
			}; // MessageData* ChatChannelKickPlayerCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )

			Result ChatChannelKickPlayerCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelKickPlayerCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelKickPlayer, {0}:{1} , TransactionID:{2}, ChatUID:{3}, PlayerID:{4}, PlayerToKick:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetPlayerID(), parser.GetPlayerToKick()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelKickPlayerCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID ChatChannelKickPlayerRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 61);
			Result ChatChannelKickPlayerRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelKickPlayerRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelKickPlayerRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelKickPlayerRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelKickPlayerRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ChatChannelKickPlayerRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelKickPlayerRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelKickPlayerRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* ChatChannelKickPlayerRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result ChatChannelKickPlayerRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelKickPlayerRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelKickPlayer, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelKickPlayerRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: ChatChannel Player kicked message
			const MessageID ChatChannelPlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 62);
			Result ChatChannelPlayerKickedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ChatUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelPlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelPlayerKickedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ChatChannelPlayerKickedS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelPlayerKickedS2CEvt::CalculateMessageSize( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InChatUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelPlayerKickedS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InChatUID);
				protocolCheck(*output << InKickedPlayerID);

				return hr;
			}; // MessageData* ChatChannelPlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InChatUID, const AccountID &InKickedPlayerID )

			Result ChatChannelPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelPlayerKickedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelPlayerKicked, {0}:{1} , ChatUID:{2}, KickedPlayerID:{3}",
						prefix, pHeader->Length, parser.GetChatUID(), parser.GetKickedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelPlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Chat channel sending chatting message
			const MessageID ChatChannelChatMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 63);
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
			Result ChatChannelChatMessageCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result ChatChannelChatMessageCmd::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelChatMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ChatUID", parser.GetChatUID());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t ChatChannelChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			size_t ChatChannelChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelChatMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InChatUID, InChatMetaData, InChatMessage);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InChatUID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InChatUID);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelChatMessageCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelChatMessage, {0}:{1} , TransactionID:{2}, ChatUID:{3}, ChatMetaData:{4}, ChatMessage:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetChatUID(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID ChatChannelChatMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 63);
			Result ChatChannelChatMessageRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelChatMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ChatChannelChatMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelChatMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* ChatChannelChatMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result ChatChannelChatMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelChatMessageRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelChatMessage, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: ChatChannel Chatting message event
			const MessageID ChatChannelChatMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 64);
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
			Result ChatChannelChatMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ChatChannelChatMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ChatChannelChatMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ChatChannelChatMessageS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t ChatChannelChatMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelChatMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			size_t ChatChannelChatMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ChatChannelChatMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InSenderID, InChatMetaData, InChatMessage);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ChatChannelChatMessageS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ChatChannelChatMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ChatChannelChatMessageS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ChatChannelChatMessage, {0}:{1} , SenderID:{2}, ChatMetaData:{3}, ChatMessage:{4,60}",
						prefix, pHeader->Length, parser.GetSenderID(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ChatChannelChatMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Whisper(tell) other player chatting
			const MessageID WhisperMessageCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 65);
			const VariableTable& WhisperMessageCmd::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& WhisperMessageCmd::GetChatMetaData() const
			Result WhisperMessageCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
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

			}; // Result WhisperMessageCmd::ParseMessage(const MessageHeader* pHeader)

			Result WhisperMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				WhisperMessageCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("ReceiverID", parser.GetReceiverID());
				variableBuilder.SetVariable("ReceiverName", parser.GetReceiverName());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result WhisperMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhisperMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhisperMessageCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhisperMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t WhisperMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InReceiverID)
					+ SerializedSizeOf(InReceiverName)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t WhisperMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			size_t WhisperMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InReceiverID)
					+ SerializedSizeOf(InReceiverName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t WhisperMessageCmd::CalculateMessageSize( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )

			MessageData* WhisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InReceiverID, InReceiverName, InChatMetaData, InChatMessage);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WhisperMessageCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InReceiverID);
				protocolCheck(*output << InReceiverName);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WhisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* WhisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InReceiverID)
					+ SerializedSizeOf(InReceiverName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WhisperMessageCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InReceiverID);
				protocolCheck(*output << InReceiverName);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WhisperMessageCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result WhisperMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhisperMessageCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::WhisperMessage, {0}:{1} , TransactionID:{2}, ReceiverID:{3}, ReceiverName:{4,60}, ChatMetaData:{5}, ChatMessage:{6,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetReceiverID(), parser.GetReceiverName(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result WhisperMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID WhisperMessageRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 65);
			Result WhisperMessageRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result WhisperMessageRes::ParseMessage(const MessageHeader* pHeader)

			Result WhisperMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				WhisperMessageRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result WhisperMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhisperMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhisperMessageRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhisperMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t WhisperMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t WhisperMessageRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


			MessageData* WhisperMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WhisperMessageRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* WhisperMessageRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result WhisperMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhisperMessageRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::WhisperMessage, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result WhisperMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Other player whispered(tell) to me message event
			const MessageID WhisperMessageS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 66);
			const VariableTable& WhisperMessageS2CEvt::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& WhisperMessageS2CEvt::GetChatMetaData() const
			Result WhisperMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result WhisperMessageS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhisperMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				WhisperMessageS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result WhisperMessageS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhisperMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhisperMessageS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhisperMessageS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t WhisperMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t WhisperMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			size_t WhisperMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t WhisperMessageS2CEvt::CalculateMessageSize( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )

			MessageData* WhisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint __uiMessageSize = (uint)CalculateMessageSize(InSenderID, InChatMetaData, InChatMessage);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WhisperMessageS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WhisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* WhisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InSenderID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::WhisperMessageS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InSenderID);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* WhisperMessageS2CEvt::Create( IHeap& memHeap, const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result WhisperMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhisperMessageS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::WhisperMessage, {0}:{1} , SenderID:{2}, ChatMetaData:{3}, ChatMessage:{4,60}",
						prefix, pHeader->Length, parser.GetSenderID(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result WhisperMessageS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Create character
			const MessageID CreateCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 67);
			const VariableTable& CreateCharacterCmd::GetPublicData() const
			{
 				if (!m_PublicDataHasParsed)
				{
 					m_PublicDataHasParsed = true;
					InputMemoryStream PublicData_ReadStream(m_PublicDataRaw);
					*PublicData_ReadStream.ToInputStream() >> m_PublicData;
				} // if (!m_PublicDataHasParsed)
				return m_PublicData;
			} // const VariableTable& CreateCharacterCmd::GetPublicData() const
			const VariableTable& CreateCharacterCmd::GetPrivateData() const
			{
 				if (!m_PrivateDataHasParsed)
				{
 					m_PrivateDataHasParsed = true;
					InputMemoryStream PrivateData_ReadStream(m_PrivateDataRaw);
					*PrivateData_ReadStream.ToInputStream() >> m_PrivateData;
				} // if (!m_PrivateDataHasParsed)
				return m_PrivateData;
			} // const VariableTable& CreateCharacterCmd::GetPrivateData() const
			Result CreateCharacterCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_CharacterName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PublicDataPtr = nullptr;
				protocolCheck(input->ReadLink(PublicDataPtr, ArrayLen));
				m_PublicDataRaw.SetLinkedBuffer(ArrayLen, PublicDataPtr);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PrivateDataPtr = nullptr;
				protocolCheck(input->ReadLink(PrivateDataPtr, ArrayLen));
				m_PrivateDataRaw.SetLinkedBuffer(ArrayLen, PrivateDataPtr);

				return hr;

			}; // Result CreateCharacterCmd::ParseMessage(const MessageHeader* pHeader)

			Result CreateCharacterCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateCharacterCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterName", parser.GetCharacterName());
				variableBuilder.SetVariableArray("PublicData", "VariableTable", parser.GetPublicDataRaw());
				variableBuilder.SetVariableArray("PrivateData", "VariableTable", parser.GetPrivateDataRaw());

				return hr;

			}; // Result CreateCharacterCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateCharacterCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t CreateCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InPrivateData )
			{
 				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
					+ serializedSizeOfInPublicData
					+ serializedSizeOfInPrivateData
				);

				return __uiMessageSize;
			}; // size_t CreateCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InPrivateData )

			size_t CreateCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )
			{
 				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPublicData
					+ sizeof(uint16_t)
					+ serializedSizeOfInPrivateData
				);

				return __uiMessageSize;
			}; // size_t CreateCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )

			MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InPrivateData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InCharacterName, InPublicData, InPrivateData);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateCharacterCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterName);
				protocolCheck(*output << InPublicData);
				protocolCheck(*output << InPrivateData);

				return hr;
			}; // MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InPrivateData )

			MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPublicData
					+ sizeof(uint16_t)
					+ serializedSizeOfInPrivateData
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateCharacterCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterName);
				protocolCheck(output->Write(serializedSizeOfInPublicData));
				protocolCheck(*output << InPublicData);
				protocolCheck(output->Write(serializedSizeOfInPrivateData));
				protocolCheck(*output << InPrivateData);

				return hr;
			}; // MessageData* CreateCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )

			Result CreateCharacterCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateCharacterCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CreateCharacter, {0}:{1} , TransactionID:{2}, CharacterName:{3,60}, PublicData:{4}, PrivateData:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetCharacterName(), parser.GetPublicData(), parser.GetPrivateData()); 
				return ResultCode::SUCCESS;
			}; // Result CreateCharacterCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID CreateCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 67);
			Result CreateCharacterRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result CreateCharacterRes::ParseMessage(const MessageHeader* pHeader)

			Result CreateCharacterRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateCharacterRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result CreateCharacterRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateCharacterRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CreateCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
				);

				return __uiMessageSize;
			}; // size_t CreateCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CreateCharacterRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* CreateCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )

			Result CreateCharacterRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateCharacterRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CreateCharacter, {0}:{1} , TransactionID:{2}, Result:{3:X8}, CharacterID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateCharacterRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Delete character
			const MessageID DeleteCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 68);
			Result DeleteCharacterCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessage(const MessageHeader* pHeader)

			Result DeleteCharacterCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteCharacterCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DeleteCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteCharacterCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t DeleteCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				return __uiMessageSize;
			}; // size_t DeleteCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InCharacterID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteCharacterCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* DeleteCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )

			Result DeleteCharacterCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DeleteCharacterCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::DeleteCharacter, {0}:{1} , TransactionID:{2}, CharacterID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteCharacterCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID DeleteCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 68);
			Result DeleteCharacterRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result DeleteCharacterRes::ParseMessage(const MessageHeader* pHeader)

			Result DeleteCharacterRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteCharacterRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result DeleteCharacterRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DeleteCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteCharacterRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t DeleteCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t DeleteCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::DeleteCharacterRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* DeleteCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result DeleteCharacterRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DeleteCharacterRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::DeleteCharacter, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteCharacterRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Get character list
			const MessageID GetCharacterListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 69);
			Result GetCharacterListCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GetCharacterListCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetCharacterListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterListCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GetCharacterListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetCharacterListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterListCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetCharacterListCmd::CalculateMessageSize( const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t GetCharacterListCmd::CalculateMessageSize( const uint64_t &InTransactionID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterListCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* GetCharacterListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result GetCharacterListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetCharacterListCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetCharacterList, {0}:{1} , TransactionID:{2}",
						prefix, pHeader->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetCharacterListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 69);
			Result GetCharacterListRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(m_Characters));

				return hr;

			}; // Result GetCharacterListRes::ParseMessage(const MessageHeader* pHeader)

			Result GetCharacterListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterListRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Characters", parser.GetCharacters());

				return hr;

			}; // Result GetCharacterListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetCharacterListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterListRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetCharacterListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacters)
				);

				return __uiMessageSize;
			}; // size_t GetCharacterListRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacters)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterListRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacters);

				return hr;
			}; // MessageData* GetCharacterListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )

			Result GetCharacterListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetCharacterListRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetCharacterList, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Characters:{4,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacters()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: 
			const MessageID GetCharacterDataCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 70);
			Result GetCharacterDataCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetCharacterDataCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetCharacterDataCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				return __uiMessageSize;
			}; // size_t GetCharacterDataCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InCharacterID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* GetCharacterDataCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )

			Result GetCharacterDataCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetCharacterDataCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetCharacterData, {0}:{1} , TransactionID:{2}, CharacterID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetCharacterDataRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 70);
			const VariableTable& GetCharacterDataRes::GetPrivateData() const
			{
 				if (!m_PrivateDataHasParsed)
				{
 					m_PrivateDataHasParsed = true;
					InputMemoryStream PrivateData_ReadStream(m_PrivateDataRaw);
					*PrivateData_ReadStream.ToInputStream() >> m_PrivateData;
				} // if (!m_PrivateDataHasParsed)
				return m_PrivateData;
			} // const VariableTable& GetCharacterDataRes::GetPrivateData() const
			const VariableTable& GetCharacterDataRes::GetEquipData() const
			{
 				if (!m_EquipDataHasParsed)
				{
 					m_EquipDataHasParsed = true;
					InputMemoryStream EquipData_ReadStream(m_EquipDataRaw);
					*EquipData_ReadStream.ToInputStream() >> m_EquipData;
				} // if (!m_EquipDataHasParsed)
				return m_EquipData;
			} // const VariableTable& GetCharacterDataRes::GetEquipData() const
			Result GetCharacterDataRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PrivateDataPtr = nullptr;
				protocolCheck(input->ReadLink(PrivateDataPtr, ArrayLen));
				m_PrivateDataRaw.SetLinkedBuffer(ArrayLen, PrivateDataPtr);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* EquipDataPtr = nullptr;
				protocolCheck(input->ReadLink(EquipDataPtr, ArrayLen));
				m_EquipDataRaw.SetLinkedBuffer(ArrayLen, EquipDataPtr);

				return hr;

			}; // Result GetCharacterDataRes::ParseMessage(const MessageHeader* pHeader)

			Result GetCharacterDataRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetCharacterDataRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariableArray("PrivateData", "VariableTable", parser.GetPrivateDataRaw());
				variableBuilder.SetVariableArray("EquipData", "VariableTable", parser.GetEquipDataRaw());

				return hr;

			}; // Result GetCharacterDataRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetCharacterDataRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetCharacterDataRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetCharacterDataRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t GetCharacterDataRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InPrivateData, const Array<uint8_t>& InEquipData )
			{
 				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInPrivateData
					+ serializedSizeOfInEquipData
				);

				return __uiMessageSize;
			}; // size_t GetCharacterDataRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InPrivateData, const Array<uint8_t>& InEquipData )

			size_t GetCharacterDataRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )
			{
 				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPrivateData
					+ sizeof(uint16_t)
					+ serializedSizeOfInEquipData
				);

				return __uiMessageSize;
			}; // size_t GetCharacterDataRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )

			MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InPrivateData, const Array<uint8_t>& InEquipData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InPrivateData, InEquipData);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPrivateData);
				protocolCheck(*output << InEquipData);

				return hr;
			}; // MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InPrivateData, const Array<uint8_t>& InEquipData )

			MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPrivateData
					+ sizeof(uint16_t)
					+ serializedSizeOfInEquipData
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::GetCharacterDataRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(output->Write(serializedSizeOfInPrivateData));
				protocolCheck(*output << InPrivateData);
				protocolCheck(output->Write(serializedSizeOfInEquipData));
				protocolCheck(*output << InEquipData);

				return hr;
			}; // MessageData* GetCharacterDataRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )

			Result GetCharacterDataRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetCharacterDataRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::GetCharacterData, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PrivateData:{4}, EquipData:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPrivateData(), parser.GetEquipData()); 
				return ResultCode::SUCCESS;
			}; // Result GetCharacterDataRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Select character
			const MessageID SelectCharacterCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 71);
			Result SelectCharacterCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_CharacterID);

				return hr;

			}; // Result SelectCharacterCmd::ParseMessage(const MessageHeader* pHeader)

			Result SelectCharacterCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SelectCharacterCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());

				return hr;

			}; // Result SelectCharacterCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SelectCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SelectCharacterCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SelectCharacterCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SelectCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				return __uiMessageSize;
			}; // size_t SelectCharacterCmd::CalculateMessageSize( const uint64_t &InTransactionID, const uint32_t &InCharacterID )


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

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InCharacterID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SelectCharacterCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InCharacterID);

				return hr;
			}; // MessageData* SelectCharacterCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InCharacterID )

			Result SelectCharacterCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SelectCharacterCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SelectCharacter, {0}:{1} , TransactionID:{2}, CharacterID:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetCharacterID()); 
				return ResultCode::SUCCESS;
			}; // Result SelectCharacterCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID SelectCharacterRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 71);
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
			Result SelectCharacterRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result SelectCharacterRes::ParseMessage(const MessageHeader* pHeader)

			Result SelectCharacterRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				SelectCharacterRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());
				variableBuilder.SetVariableArray("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result SelectCharacterRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SelectCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) SelectCharacterRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SelectCharacterRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t SelectCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const Array<uint8_t>& InAttributes )
			{
 				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
					+ serializedSizeOfInAttributes
				);

				return __uiMessageSize;
			}; // size_t SelectCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const Array<uint8_t>& InAttributes )

			size_t SelectCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )
			{
 				uint16_t serializedSizeOfInAttributes = static_cast<uint16_t>(SerializedSizeOf(InAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				return __uiMessageSize;
			}; // size_t SelectCharacterRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InCharacterID, InAttributes);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SelectCharacterRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::SelectCharacterRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InCharacterID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* SelectCharacterRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )

			Result SelectCharacterRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SelectCharacterRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::SelectCharacter, {0}:{1} , TransactionID:{2}, Result:{3:X8}, CharacterID:{4}, Attributes:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetCharacterID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result SelectCharacterRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
			const MessageID RequestServerNoticeUpdateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 72);
			Result RequestServerNoticeUpdateCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result RequestServerNoticeUpdateCmd::ParseMessage(const MessageHeader* pHeader)

			Result RequestServerNoticeUpdateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestServerNoticeUpdateCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result RequestServerNoticeUpdateCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestServerNoticeUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestServerNoticeUpdateCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestServerNoticeUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RequestServerNoticeUpdateCmd::CalculateMessageSize( const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t RequestServerNoticeUpdateCmd::CalculateMessageSize( const uint64_t &InTransactionID )


			MessageData* RequestServerNoticeUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestServerNoticeUpdateCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* RequestServerNoticeUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result RequestServerNoticeUpdateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestServerNoticeUpdateCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RequestServerNoticeUpdate, {0}:{1} , TransactionID:{2}",
						prefix, pHeader->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result RequestServerNoticeUpdateCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID RequestServerNoticeUpdateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 72);
			Result RequestServerNoticeUpdateRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RequestServerNoticeUpdateRes::ParseMessage(const MessageHeader* pHeader)

			Result RequestServerNoticeUpdateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RequestServerNoticeUpdateRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RequestServerNoticeUpdateRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestServerNoticeUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestServerNoticeUpdateRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestServerNoticeUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RequestServerNoticeUpdateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t RequestServerNoticeUpdateRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult )


			MessageData* RequestServerNoticeUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::RequestServerNoticeUpdateRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* RequestServerNoticeUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result RequestServerNoticeUpdateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestServerNoticeUpdateRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::RequestServerNoticeUpdate, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result RequestServerNoticeUpdateRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Server Notice updated event
			const MessageID ServerNoticeS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 73);
			Result ServerNoticeS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_NoticeCategory);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ServerNoticeMessage, ArrayLen));

				return hr;

			}; // Result ServerNoticeS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ServerNoticeS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ServerNoticeS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("NoticeCategory", parser.GetNoticeCategory());
				variableBuilder.SetVariable("ServerNoticeMessage", parser.GetServerNoticeMessage());

				return hr;

			}; // Result ServerNoticeS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ServerNoticeS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ServerNoticeS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ServerNoticeS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ServerNoticeS2CEvt::CalculateMessageSize( const int8_t &InNoticeCategory, const char* InServerNoticeMessage )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InNoticeCategory)
					+ SerializedSizeOf(InServerNoticeMessage)
				);

				return __uiMessageSize;
			}; // size_t ServerNoticeS2CEvt::CalculateMessageSize( const int8_t &InNoticeCategory, const char* InServerNoticeMessage )


			MessageData* ServerNoticeS2CEvt::Create( IHeap& memHeap, const int8_t &InNoticeCategory, const char* InServerNoticeMessage )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InNoticeCategory)
					+ SerializedSizeOf(InServerNoticeMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::ServerNoticeS2CEvt::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InNoticeCategory);
				protocolCheck(*output << InServerNoticeMessage);

				return hr;
			}; // MessageData* ServerNoticeS2CEvt::Create( IHeap& memHeap, const int8_t &InNoticeCategory, const char* InServerNoticeMessage )

			Result ServerNoticeS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ServerNoticeS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::ServerNotice, {0}:{1} , NoticeCategory:{2}, ServerNoticeMessage:{3,60}",
						prefix, pHeader->Length, parser.GetNoticeCategory(), parser.GetServerNoticeMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ServerNoticeS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: To call general functionality
			const MessageID CallFunctionCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 74);
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
			Result CallFunctionCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result CallFunctionCmd::ParseMessage(const MessageHeader* pHeader)

			Result CallFunctionCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CallFunctionCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FunctionName", parser.GetFunctionName());
				variableBuilder.SetVariableArray("Parameters", "VariableTable", parser.GetParametersRaw());

				return hr;

			}; // Result CallFunctionCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CallFunctionCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CallFunctionCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CallFunctionCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t CallFunctionCmd::CalculateMessageSize( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters )
			{
 				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ serializedSizeOfInParameters
				);

				return __uiMessageSize;
			}; // size_t CallFunctionCmd::CalculateMessageSize( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters )

			size_t CallFunctionCmd::CalculateMessageSize( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )
			{
 				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
				);

				return __uiMessageSize;
			}; // size_t CallFunctionCmd::CalculateMessageSize( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InFunctionName, InParameters);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFunctionName);
				protocolCheck(output->Write(serializedSizeOfInParameters));
				protocolCheck(*output << InParameters);

				return hr;
			}; // MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )

			Result CallFunctionCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CallFunctionCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CallFunction, {0}:{1} , TransactionID:{2}, FunctionName:{3}, Parameters:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetFunctionName(), parser.GetParameters()); 
				return ResultCode::SUCCESS;
			}; // Result CallFunctionCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID CallFunctionRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GAME, 74);
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
			Result CallFunctionRes::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result CallFunctionRes::ParseMessage(const MessageHeader* pHeader)

			Result CallFunctionRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CallFunctionRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariableArray("Results", "VariableTable", parser.GetResultsRaw());

				return hr;

			}; // Result CallFunctionRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CallFunctionRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CallFunctionRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CallFunctionRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t CallFunctionRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )
			{
 				uint16_t serializedSizeOfInResults = static_cast<uint16_t>(SerializedSizeOf(InResults)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInResults
				);

				return __uiMessageSize;
			}; // size_t CallFunctionRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )

			size_t CallFunctionRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )
			{
 				uint16_t serializedSizeOfInResults = static_cast<uint16_t>(SerializedSizeOf(InResults)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResults
				);

				return __uiMessageSize;
			}; // size_t CallFunctionRes::CalculateMessageSize( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )

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

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InResults);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

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
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResults
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Game::CallFunctionRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(output->Write(serializedSizeOfInResults));
				protocolCheck(*output << InResults);

				return hr;
			}; // MessageData* CallFunctionRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )

			Result CallFunctionRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CallFunctionRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Game::CallFunction, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Results:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetResults()); 
				return ResultCode::SUCCESS;
			}; // Result CallFunctionRes::TraceOut(const char* prefix, const MessageHeader* pHeader)



		}; // namespace Game
	}; // namespace Message
}; // namespace SF



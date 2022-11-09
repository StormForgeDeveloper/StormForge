////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Login Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/LoginMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace Login
		{
 			// Cmd: Login request
			const MessageID LoginCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 0);
			Result LoginCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ID, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_Password, ArrayLen));

				return hr;

			}; // Result LoginCmd::ParseMessage(const MessageData* pIMsg)

			Result LoginCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("ID", parser.GetID());
				variableBuilder.SetVariable("Password", parser.GetPassword());

				return hr;

			}; // Result LoginCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* LoginCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InID)
					+ SerializedSizeOf(InPassword)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InID);
				protocolCheck(*output << InPassword);

				return hr;
			}; // MessageData* LoginCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )

			Result LoginCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Login:{0}:{1} , TransactionID:{2}, GameID:{3}, ID:{4,60}, Password:{5,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetID(), parser.GetPassword()); 
				return ResultCode::SUCCESS;
			}; // Result LoginCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LoginRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 0);
			Result LoginRes::ParseMessage(const MessageData* pIMsg)
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
				protocolCheck(*input >> m_GameServerAddr);
				protocolCheck(*input >> m_GameServerAddrIPV4);
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ErrorReason, ArrayLen));

				return hr;

			}; // Result LoginRes::ParseMessage(const MessageData* pIMsg)

			Result LoginRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", "NetAddress", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", "NetAddress", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());
				variableBuilder.SetVariable("ErrorReason", parser.GetErrorReason());

				return hr;

			}; // Result LoginRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* LoginRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameServerAddr)
					+ SerializedSizeOf(InGameServerAddrIPV4)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
					+ SerializedSizeOf(InErrorReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerAddr);
				protocolCheck(*output << InGameServerAddrIPV4);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);
				protocolCheck(*output << InErrorReason);

				return hr;
			}; // MessageData* LoginRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )

			Result LoginRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Login:{0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerAddr:{4}, GameServerAddrIPV4:{5}, AccID:{6}, Ticket:{7}, LoginEntityUID:{8}, ErrorReason:{9,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID(), parser.GetErrorReason()); 
				return ResultCode::SUCCESS;
			}; // Result LoginRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Login request with Facebook UID
			const MessageID LoginByFacebookCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 1);
			Result LoginByFacebookCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameID);
				protocolCheck(*input >> m_UID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_FaceBookName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_EMail, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_FacebookToken, ArrayLen));

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessage(const MessageData* pIMsg)

			Result LoginByFacebookCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginByFacebookCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("UID", parser.GetUID());
				variableBuilder.SetVariable("FaceBookName", parser.GetFaceBookName());
				variableBuilder.SetVariable("EMail", parser.GetEMail());
				variableBuilder.SetVariable("FacebookToken", parser.GetFacebookToken());

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginByFacebookCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* LoginByFacebookCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InUID)
					+ SerializedSizeOf(InFaceBookName)
					+ SerializedSizeOf(InEMail)
					+ SerializedSizeOf(InFacebookToken)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InUID);
				protocolCheck(*output << InFaceBookName);
				protocolCheck(*output << InEMail);
				protocolCheck(*output << InFacebookToken);

				return hr;
			}; // MessageData* LoginByFacebookCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )

			Result LoginByFacebookCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginByFacebookCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LoginByFacebook:{0}:{1} , TransactionID:{2}, GameID:{3}, UID:{4}, FaceBookName:{5,60}, EMail:{6,60}, FacebookToken:{7,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetUID(), parser.GetFaceBookName(), parser.GetEMail(), parser.GetFacebookToken()); 
				return ResultCode::SUCCESS;
			}; // Result LoginByFacebookCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LoginByFacebookRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 1);
			Result LoginByFacebookRes::ParseMessage(const MessageData* pIMsg)
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
				protocolCheck(*input >> m_GameServerAddr);
				protocolCheck(*input >> m_GameServerAddrIPV4);
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ErrorReason, ArrayLen));

				return hr;

			}; // Result LoginByFacebookRes::ParseMessage(const MessageData* pIMsg)

			Result LoginByFacebookRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginByFacebookRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", "NetAddress", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", "NetAddress", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());
				variableBuilder.SetVariable("ErrorReason", parser.GetErrorReason());

				return hr;

			}; // Result LoginByFacebookRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginByFacebookRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameServerAddr)
					+ SerializedSizeOf(InGameServerAddrIPV4)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
					+ SerializedSizeOf(InErrorReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerAddr);
				protocolCheck(*output << InGameServerAddrIPV4);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);
				protocolCheck(*output << InErrorReason);

				return hr;
			}; // MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )

			Result LoginByFacebookRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginByFacebookRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LoginByFacebook:{0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerAddr:{4}, GameServerAddrIPV4:{5}, AccID:{6}, Ticket:{7}, LoginEntityUID:{8}, ErrorReason:{9,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID(), parser.GetErrorReason()); 
				return ResultCode::SUCCESS;
			}; // Result LoginByFacebookRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Login request with Facebook UID
			const MessageID LoginBySteamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 2);
			Result LoginBySteamCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameID);
				protocolCheck(*input >> m_SteamUserID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SteamUserName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SteamUserToken, ArrayLen));

				return hr;

			}; // Result LoginBySteamCmd::ParseMessage(const MessageData* pIMsg)

			Result LoginBySteamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginBySteamCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("SteamUserID", parser.GetSteamUserID());
				variableBuilder.SetVariable("SteamUserName", parser.GetSteamUserName());
				variableBuilder.SetVariable("SteamUserToken", parser.GetSteamUserToken());

				return hr;

			}; // Result LoginBySteamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginBySteamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginBySteamCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginBySteamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* LoginBySteamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InSteamUserID)
					+ SerializedSizeOf(InSteamUserName)
					+ SerializedSizeOf(InSteamUserToken)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginBySteamCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InSteamUserID);
				protocolCheck(*output << InSteamUserName);
				protocolCheck(*output << InSteamUserToken);

				return hr;
			}; // MessageData* LoginBySteamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )

			Result LoginBySteamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginBySteamCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LoginBySteam:{0}:{1} , TransactionID:{2}, GameID:{3}, SteamUserID:{4}, SteamUserName:{5,60}, SteamUserToken:{6,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetSteamUserID(), parser.GetSteamUserName(), parser.GetSteamUserToken()); 
				return ResultCode::SUCCESS;
			}; // Result LoginBySteamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID LoginBySteamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 2);
			Result LoginBySteamRes::ParseMessage(const MessageData* pIMsg)
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
				protocolCheck(*input >> m_GameServerAddr);
				protocolCheck(*input >> m_GameServerAddrIPV4);
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ErrorReason, ArrayLen));

				return hr;

			}; // Result LoginBySteamRes::ParseMessage(const MessageData* pIMsg)

			Result LoginBySteamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginBySteamRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", "NetAddress", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", "NetAddress", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());
				variableBuilder.SetVariable("ErrorReason", parser.GetErrorReason());

				return hr;

			}; // Result LoginBySteamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginBySteamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginBySteamRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginBySteamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* LoginBySteamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameServerAddr)
					+ SerializedSizeOf(InGameServerAddrIPV4)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
					+ SerializedSizeOf(InErrorReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginBySteamRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerAddr);
				protocolCheck(*output << InGameServerAddrIPV4);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);
				protocolCheck(*output << InErrorReason);

				return hr;
			}; // MessageData* LoginBySteamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )

			Result LoginBySteamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginBySteamRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LoginBySteam:{0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerAddr:{4}, GameServerAddrIPV4:{5}, AccID:{6}, Ticket:{7}, LoginEntityUID:{8}, ErrorReason:{9,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID(), parser.GetErrorReason()); 
				return ResultCode::SUCCESS;
			}; // Result LoginBySteamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Login request
			const MessageID CreateRandomUserCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 3);
			Result CreateRandomUserCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_CellPhone, ArrayLen));

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessage(const MessageData* pIMsg)

			Result CreateRandomUserCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateRandomUserCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("CellPhone", parser.GetCellPhone());

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateRandomUserCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateRandomUserCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InCellPhone)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InCellPhone);

				return hr;
			}; // MessageData* CreateRandomUserCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )

			Result CreateRandomUserCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateRandomUserCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateRandomUser:{0}:{1} , TransactionID:{2}, GameID:{3}, CellPhone:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetCellPhone()); 
				return ResultCode::SUCCESS;
			}; // Result CreateRandomUserCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CreateRandomUserRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 3);
			Result CreateRandomUserRes::ParseMessage(const MessageData* pIMsg)
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
				protocolCheck(*input >> m_GameServerAddr);
				protocolCheck(*input >> m_GameServerAddrIPV4);
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);

				return hr;

			}; // Result CreateRandomUserRes::ParseMessage(const MessageData* pIMsg)

			Result CreateRandomUserRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateRandomUserRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", "NetAddress", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", "NetAddress", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result CreateRandomUserRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateRandomUserRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateRandomUserRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InGameServerAddr)
					+ SerializedSizeOf(InGameServerAddrIPV4)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerAddr);
				protocolCheck(*output << InGameServerAddrIPV4);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);

				return hr;
			}; // MessageData* CreateRandomUserRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )

			Result CreateRandomUserRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateRandomUserRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateRandomUser:{0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerAddr:{4}, GameServerAddrIPV4:{5}, AccID:{6}, Ticket:{7}, LoginEntityUID:{8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateRandomUserRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
			const MessageID PreLoginRequestServerNoticeUpdateCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 4);
			Result PreLoginRequestServerNoticeUpdateCmd::ParseMessage(const MessageData* pIMsg)
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

			}; // Result PreLoginRequestServerNoticeUpdateCmd::ParseMessage(const MessageData* pIMsg)

			Result PreLoginRequestServerNoticeUpdateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PreLoginRequestServerNoticeUpdateCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result PreLoginRequestServerNoticeUpdateCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PreLoginRequestServerNoticeUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PreLoginRequestServerNoticeUpdateCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PreLoginRequestServerNoticeUpdateCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* PreLoginRequestServerNoticeUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )
			{
 				MessageData *pNewMsg = nullptr;
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

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::PreLoginRequestServerNoticeUpdateCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);

				return hr;
			}; // MessageData* PreLoginRequestServerNoticeUpdateCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID )

			Result PreLoginRequestServerNoticeUpdateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PreLoginRequestServerNoticeUpdateCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PreLoginRequestServerNoticeUpdate:{0}:{1} , TransactionID:{2}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result PreLoginRequestServerNoticeUpdateCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID PreLoginRequestServerNoticeUpdateRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 4);
			Result PreLoginRequestServerNoticeUpdateRes::ParseMessage(const MessageData* pIMsg)
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

			}; // Result PreLoginRequestServerNoticeUpdateRes::ParseMessage(const MessageData* pIMsg)

			Result PreLoginRequestServerNoticeUpdateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PreLoginRequestServerNoticeUpdateRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PreLoginRequestServerNoticeUpdateRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PreLoginRequestServerNoticeUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PreLoginRequestServerNoticeUpdateRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PreLoginRequestServerNoticeUpdateRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* PreLoginRequestServerNoticeUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
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

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::PreLoginRequestServerNoticeUpdateRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* PreLoginRequestServerNoticeUpdateRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result PreLoginRequestServerNoticeUpdateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PreLoginRequestServerNoticeUpdateRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PreLoginRequestServerNoticeUpdate:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PreLoginRequestServerNoticeUpdateRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Server Notice updated event
			const MessageID PreLoginServerNoticeS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 5);
			Result PreLoginServerNoticeS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_NoticeCategory);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ServerNoticeMessage, ArrayLen));

				return hr;

			}; // Result PreLoginServerNoticeS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PreLoginServerNoticeS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PreLoginServerNoticeS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("NoticeCategory", parser.GetNoticeCategory());
				variableBuilder.SetVariable("ServerNoticeMessage", parser.GetServerNoticeMessage());

				return hr;

			}; // Result PreLoginServerNoticeS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PreLoginServerNoticeS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PreLoginServerNoticeS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PreLoginServerNoticeS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* PreLoginServerNoticeS2CEvt::Create( IHeap& memHeap, const int8_t &InNoticeCategory, const char* InServerNoticeMessage )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InNoticeCategory)
					+ SerializedSizeOf(InServerNoticeMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::PreLoginServerNoticeS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InNoticeCategory);
				protocolCheck(*output << InServerNoticeMessage);

				return hr;
			}; // MessageData* PreLoginServerNoticeS2CEvt::Create( IHeap& memHeap, const int8_t &InNoticeCategory, const char* InServerNoticeMessage )

			Result PreLoginServerNoticeS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PreLoginServerNoticeS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PreLoginServerNotice:{0}:{1} , NoticeCategory:{2}, ServerNoticeMessage:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetNoticeCategory(), parser.GetServerNoticeMessage()); 
				return ResultCode::SUCCESS;
			}; // Result PreLoginServerNoticeS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Update my score and Get Ranking list
			const MessageID UpdateMyScoreCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 6);
			Result UpdateMyScoreCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_RankingScore);
				protocolCheck(*input >> m_RankingType);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessage(const MessageData* pIMsg)

			Result UpdateMyScoreCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UpdateMyScoreCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingScore", parser.GetRankingScore());
				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateMyScoreCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* UpdateMyScoreCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InRankingScore)
					+ SerializedSizeOf(InRankingType)
					+ SerializedSizeOf(InCount)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InRankingScore);
				protocolCheck(*output << InRankingType);
				protocolCheck(*output << InCount);

				return hr;
			}; // MessageData* UpdateMyScoreCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )

			Result UpdateMyScoreCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UpdateMyScoreCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UpdateMyScore:{0}:{1} , TransactionID:{2}, RankingScore:{3}, RankingType:{4}, Count:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetRankingScore(), (int)parser.GetRankingType(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateMyScoreCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID UpdateMyScoreRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 6);
			Result UpdateMyScoreRes::ParseMessage(const MessageData* pIMsg)
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

			}; // Result UpdateMyScoreRes::ParseMessage(const MessageData* pIMsg)

			Result UpdateMyScoreRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UpdateMyScoreRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateMyScoreRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* UpdateMyScoreRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				MessageData *pNewMsg = nullptr;
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

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InRanking);

				return hr;
			}; // MessageData* UpdateMyScoreRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )

			Result UpdateMyScoreRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UpdateMyScoreRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UpdateMyScore:{0}:{1} , TransactionID:{2}, Result:{3:X8}, Ranking:{4,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetRanking()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateMyScoreRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Get Ranking lise
			const MessageID GetRankingListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 7);
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
				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
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


			MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
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

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InRankingType);
				protocolCheck(*output << InBaseRanking);
				protocolCheck(*output << InCount);

				return hr;
			}; // MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )

			Result GetRankingListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetRankingListCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetRankingList:{0}:{1} , TransactionID:{2}, RankingType:{3}, BaseRanking:{4}, Count:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), (int)parser.GetRankingType(), parser.GetBaseRanking(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetRankingListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 7);
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

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListRes::MID, __uiMessageSize ) );
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

			// Cmd: For network test
			const MessageID DataTestCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 8);
			Result DataTestCmd::ParseMessage(const MessageData* pIMsg)
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
				uint8_t* TestDataPtr = nullptr;
				protocolCheck(input->ReadLink(TestDataPtr, ArrayLen));
				m_TestData.SetLinkedBuffer(ArrayLen, TestDataPtr);

				return hr;

			}; // Result DataTestCmd::ParseMessage(const MessageData* pIMsg)

			Result DataTestCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DataTestCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TestData", parser.GetTestData());

				return hr;

			}; // Result DataTestCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DataTestCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* DataTestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InTestData)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTestData);

				return hr;
			}; // MessageData* DataTestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )

			Result DataTestCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DataTestCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DataTest:{0}:{1} , TransactionID:{2}, TestData:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTestData()); 
				return ResultCode::SUCCESS;
			}; // Result DataTestCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID DataTestRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 8);
			Result DataTestRes::ParseMessage(const MessageData* pIMsg)
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
				uint8_t* TestDataPtr = nullptr;
				protocolCheck(input->ReadLink(TestDataPtr, ArrayLen));
				m_TestData.SetLinkedBuffer(ArrayLen, TestDataPtr);

				return hr;

			}; // Result DataTestRes::ParseMessage(const MessageData* pIMsg)

			Result DataTestRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DataTestRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TestData", parser.GetTestData());

				return hr;

			}; // Result DataTestRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DataTestRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* DataTestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InTestData)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTestData);

				return hr;
			}; // MessageData* DataTestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )

			Result DataTestRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DataTestRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DataTest:{0}:{1} , TransactionID:{2}, Result:{3:X8}, TestData:{4,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTestData()); 
				return ResultCode::SUCCESS;
			}; // Result DataTestRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Heartbeat
			const MessageID HeartbeatC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 9);
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

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::HeartbeatC2SEvt::MID, __uiMessageSize ) );

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

			// Cmd: Write All!! User Score and Ranking list
			const MessageID DebugPrintALLRankingCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 10);
			Result DebugPrintALLRankingCmd::ParseMessage(const MessageData* pIMsg)
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
				protocolCheck(input->ReadLink(m_FileName, ArrayLen));

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessage(const MessageData* pIMsg)

			Result DebugPrintALLRankingCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DebugPrintALLRankingCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FileName", parser.GetFileName());

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DebugPrintALLRankingCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* DebugPrintALLRankingCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InFileName )
			{
 				MessageData *pNewMsg = nullptr;
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
					+ SerializedSizeOf(InFileName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFileName);

				return hr;
			}; // MessageData* DebugPrintALLRankingCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InFileName )

			Result DebugPrintALLRankingCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DebugPrintALLRankingCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DebugPrintALLRanking:{0}:{1} , TransactionID:{2}, FileName:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetFileName()); 
				return ResultCode::SUCCESS;
			}; // Result DebugPrintALLRankingCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID DebugPrintALLRankingRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 10);
			Result DebugPrintALLRankingRes::ParseMessage(const MessageData* pIMsg)
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

			}; // Result DebugPrintALLRankingRes::ParseMessage(const MessageData* pIMsg)

			Result DebugPrintALLRankingRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DebugPrintALLRankingRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DebugPrintALLRankingRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* DebugPrintALLRankingRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
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

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* DebugPrintALLRankingRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result DebugPrintALLRankingRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DebugPrintALLRankingRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DebugPrintALLRanking:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result DebugPrintALLRankingRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)



		}; // namespace Login
	}; // namespace Message
}; // namespace SF



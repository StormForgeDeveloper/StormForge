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
			const MessageID LoginCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 0);
			Result LoginCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result LoginCmd::ParseMessage(const MessageHeader* pHeader)

			Result LoginCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("ID", parser.GetID());
				variableBuilder.SetVariable("Password", parser.GetPassword());

				return hr;

			}; // Result LoginCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InID)
					+ SerializedSizeOf(InPassword)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InID);
				protocolCheck(*output << InPassword);

				return hr;
			}; // MessageData* LoginCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )

			Result LoginCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::Login, {0}:{1} , TransactionID:{2}, GameID:{3}, ID:{4,60}, Password:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetID(), parser.GetPassword()); 
				return ResultCode::SUCCESS;
			}; // Result LoginCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID LoginRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 0);
			Result LoginRes::ParseMessage(const MessageHeader* pHeader)
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
				protocolCheck(input->ReadLink(m_GameServerPublicAddress, ArrayLen));
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ErrorReason, ArrayLen));

				return hr;

			}; // Result LoginRes::ParseMessage(const MessageHeader* pHeader)

			Result LoginRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerPublicAddress", parser.GetGameServerPublicAddress());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());
				variableBuilder.SetVariable("ErrorReason", parser.GetErrorReason());

				return hr;

			}; // Result LoginRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			MessageData* LoginRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InGameServerPublicAddress)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
					+ SerializedSizeOf(InErrorReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerPublicAddress);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);
				protocolCheck(*output << InErrorReason);

				return hr;
			}; // MessageData* LoginRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )

			Result LoginRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::Login, {0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerPublicAddress:{4,60}, AccID:{5}, Ticket:{6}, LoginEntityUID:{7}, ErrorReason:{8,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerPublicAddress(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID(), parser.GetErrorReason()); 
				return ResultCode::SUCCESS;
			}; // Result LoginRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Login request with Facebook UID
			const MessageID LoginByFacebookCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 1);
			Result LoginByFacebookCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result LoginByFacebookCmd::ParseMessage(const MessageHeader* pHeader)

			Result LoginByFacebookCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginByFacebookCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("UID", parser.GetUID());
				variableBuilder.SetVariable("FaceBookName", parser.GetFaceBookName());
				variableBuilder.SetVariable("EMail", parser.GetEMail());
				variableBuilder.SetVariable("FacebookToken", parser.GetFacebookToken());

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginByFacebookCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InUID)
					+ SerializedSizeOf(InFaceBookName)
					+ SerializedSizeOf(InEMail)
					+ SerializedSizeOf(InFacebookToken)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InUID);
				protocolCheck(*output << InFaceBookName);
				protocolCheck(*output << InEMail);
				protocolCheck(*output << InFacebookToken);

				return hr;
			}; // MessageData* LoginByFacebookCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )

			Result LoginByFacebookCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginByFacebookCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::LoginByFacebook, {0}:{1} , TransactionID:{2}, GameID:{3}, UID:{4}, FaceBookName:{5,60}, EMail:{6,60}, FacebookToken:{7,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetUID(), parser.GetFaceBookName(), parser.GetEMail(), parser.GetFacebookToken()); 
				return ResultCode::SUCCESS;
			}; // Result LoginByFacebookCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID LoginByFacebookRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 1);
			Result LoginByFacebookRes::ParseMessage(const MessageHeader* pHeader)
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
				protocolCheck(input->ReadLink(m_GameServerPublicAddress, ArrayLen));
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ErrorReason, ArrayLen));

				return hr;

			}; // Result LoginByFacebookRes::ParseMessage(const MessageHeader* pHeader)

			Result LoginByFacebookRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginByFacebookRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerPublicAddress", parser.GetGameServerPublicAddress());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());
				variableBuilder.SetVariable("ErrorReason", parser.GetErrorReason());

				return hr;

			}; // Result LoginByFacebookRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginByFacebookRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InGameServerPublicAddress)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
					+ SerializedSizeOf(InErrorReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerPublicAddress);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);
				protocolCheck(*output << InErrorReason);

				return hr;
			}; // MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )

			Result LoginByFacebookRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginByFacebookRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::LoginByFacebook, {0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerPublicAddress:{4,60}, AccID:{5}, Ticket:{6}, LoginEntityUID:{7}, ErrorReason:{8,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerPublicAddress(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID(), parser.GetErrorReason()); 
				return ResultCode::SUCCESS;
			}; // Result LoginByFacebookRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Login request with Facebook UID
			const MessageID LoginBySteamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 2);
			Result LoginBySteamCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result LoginBySteamCmd::ParseMessage(const MessageHeader* pHeader)

			Result LoginBySteamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginBySteamCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("SteamUserID", parser.GetSteamUserID());
				variableBuilder.SetVariable("SteamUserName", parser.GetSteamUserName());
				variableBuilder.SetVariable("SteamUserToken", parser.GetSteamUserToken());

				return hr;

			}; // Result LoginBySteamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginBySteamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginBySteamCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginBySteamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InSteamUserID)
					+ SerializedSizeOf(InSteamUserName)
					+ SerializedSizeOf(InSteamUserToken)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginBySteamCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InSteamUserID);
				protocolCheck(*output << InSteamUserName);
				protocolCheck(*output << InSteamUserToken);

				return hr;
			}; // MessageData* LoginBySteamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )

			Result LoginBySteamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginBySteamCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::LoginBySteam, {0}:{1} , TransactionID:{2}, GameID:{3}, SteamUserID:{4}, SteamUserName:{5,60}, SteamUserToken:{6,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetSteamUserID(), parser.GetSteamUserName(), parser.GetSteamUserToken()); 
				return ResultCode::SUCCESS;
			}; // Result LoginBySteamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID LoginBySteamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 2);
			Result LoginBySteamRes::ParseMessage(const MessageHeader* pHeader)
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
				protocolCheck(input->ReadLink(m_GameServerPublicAddress, ArrayLen));
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ErrorReason, ArrayLen));

				return hr;

			}; // Result LoginBySteamRes::ParseMessage(const MessageHeader* pHeader)

			Result LoginBySteamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LoginBySteamRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerPublicAddress", parser.GetGameServerPublicAddress());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());
				variableBuilder.SetVariable("ErrorReason", parser.GetErrorReason());

				return hr;

			}; // Result LoginBySteamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginBySteamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginBySteamRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginBySteamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			MessageData* LoginBySteamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InGameServerPublicAddress)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
					+ SerializedSizeOf(InErrorReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginBySteamRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerPublicAddress);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);
				protocolCheck(*output << InErrorReason);

				return hr;
			}; // MessageData* LoginBySteamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )

			Result LoginBySteamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginBySteamRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::LoginBySteam, {0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerPublicAddress:{4,60}, AccID:{5}, Ticket:{6}, LoginEntityUID:{7}, ErrorReason:{8,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerPublicAddress(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID(), parser.GetErrorReason()); 
				return ResultCode::SUCCESS;
			}; // Result LoginBySteamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Login request
			const MessageID CreateRandomUserCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 3);
			Result CreateRandomUserCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_GameID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_CellPhone, ArrayLen));

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessage(const MessageHeader* pHeader)

			Result CreateRandomUserCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateRandomUserCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("CellPhone", parser.GetCellPhone());

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateRandomUserCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InGameID)
					+ SerializedSizeOf(InCellPhone)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InGameID);
				protocolCheck(*output << InCellPhone);

				return hr;
			}; // MessageData* CreateRandomUserCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )

			Result CreateRandomUserCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateRandomUserCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::CreateRandomUser, {0}:{1} , TransactionID:{2}, GameID:{3}, CellPhone:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetGameID(), parser.GetCellPhone()); 
				return ResultCode::SUCCESS;
			}; // Result CreateRandomUserCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID CreateRandomUserRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 3);
			Result CreateRandomUserRes::ParseMessage(const MessageHeader* pHeader)
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
				protocolCheck(input->ReadLink(m_GameServerPublicAddress, ArrayLen));
				protocolCheck(*input >> m_AccID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(*input >> m_LoginEntityUID);

				return hr;

			}; // Result CreateRandomUserRes::ParseMessage(const MessageHeader* pHeader)

			Result CreateRandomUserRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateRandomUserRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerPublicAddress", parser.GetGameServerPublicAddress());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result CreateRandomUserRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateRandomUserRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			MessageData* CreateRandomUserRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InGameServerPublicAddress)
					+ SerializedSizeOf(InAccID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InLoginEntityUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InGameServerPublicAddress);
				protocolCheck(*output << InAccID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InLoginEntityUID);

				return hr;
			}; // MessageData* CreateRandomUserRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )

			Result CreateRandomUserRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateRandomUserRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::CreateRandomUser, {0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerPublicAddress:{4,60}, AccID:{5}, Ticket:{6}, LoginEntityUID:{7}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerPublicAddress(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateRandomUserRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Update my score and Get Ranking list
			const MessageID UpdateMyScoreCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 4);
			Result UpdateMyScoreCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_RankingScore);
				protocolCheck(*input >> m_RankingType);
				protocolCheck(*input >> m_Count);

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessage(const MessageHeader* pHeader)

			Result UpdateMyScoreCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UpdateMyScoreCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingScore", parser.GetRankingScore());
				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateMyScoreCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InRankingScore)
					+ SerializedSizeOf(InRankingType)
					+ SerializedSizeOf(InCount)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InRankingScore);
				protocolCheck(*output << InRankingType);
				protocolCheck(*output << InCount);

				return hr;
			}; // MessageData* UpdateMyScoreCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )

			Result UpdateMyScoreCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UpdateMyScoreCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::UpdateMyScore, {0}:{1} , TransactionID:{2}, RankingScore:{3}, RankingType:{4}, Count:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetRankingScore(), (int)parser.GetRankingType(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateMyScoreCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID UpdateMyScoreRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 4);
			Result UpdateMyScoreRes::ParseMessage(const MessageHeader* pHeader)
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

			}; // Result UpdateMyScoreRes::ParseMessage(const MessageHeader* pHeader)

			Result UpdateMyScoreRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UpdateMyScoreRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateMyScoreRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InRanking)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InRanking);

				return hr;
			}; // MessageData* UpdateMyScoreRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )

			Result UpdateMyScoreRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UpdateMyScoreRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::UpdateMyScore, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Ranking:{4,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetRanking()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateMyScoreRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Get Ranking lise
			const MessageID GetRankingListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 5);
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
				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InRankingType)
					+ SerializedSizeOf(InBaseRanking)
					+ SerializedSizeOf(InCount)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InRankingType);
				protocolCheck(*output << InBaseRanking);
				protocolCheck(*output << InCount);

				return hr;
			}; // MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )

			Result GetRankingListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetRankingListCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::GetRankingList, {0}:{1} , TransactionID:{2}, RankingType:{3}, BaseRanking:{4}, Count:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), (int)parser.GetRankingType(), parser.GetBaseRanking(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GetRankingListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 5);
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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InRanking)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListRes::MID, __uiMessageSize ) );
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
				SFLog(Net, Debug1, "Login::GetRankingList, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Ranking:{4,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetRanking()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: For network test
			const MessageID DataTestCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 6);
			Result DataTestCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* TestDataPtr = nullptr;
				protocolCheck(input->ReadLink(TestDataPtr, ArrayLen));
				m_TestData.SetLinkedBuffer(ArrayLen, TestDataPtr);

				return hr;

			}; // Result DataTestCmd::ParseMessage(const MessageHeader* pHeader)

			Result DataTestCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DataTestCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TestData", parser.GetTestData());

				return hr;

			}; // Result DataTestCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DataTestCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTestData)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTestData);

				return hr;
			}; // MessageData* DataTestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )

			Result DataTestCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DataTestCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::DataTest, {0}:{1} , TransactionID:{2}, TestData:{3,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetTestData()); 
				return ResultCode::SUCCESS;
			}; // Result DataTestCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID DataTestRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 6);
			Result DataTestRes::ParseMessage(const MessageHeader* pHeader)
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
				uint8_t* TestDataPtr = nullptr;
				protocolCheck(input->ReadLink(TestDataPtr, ArrayLen));
				m_TestData.SetLinkedBuffer(ArrayLen, TestDataPtr);

				return hr;

			}; // Result DataTestRes::ParseMessage(const MessageHeader* pHeader)

			Result DataTestRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DataTestRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TestData", parser.GetTestData());

				return hr;

			}; // Result DataTestRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DataTestRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InTestData)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InTestData);

				return hr;
			}; // MessageData* DataTestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )

			Result DataTestRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DataTestRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::DataTest, {0}:{1} , TransactionID:{2}, Result:{3:X8}, TestData:{4,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetTestData()); 
				return ResultCode::SUCCESS;
			}; // Result DataTestRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// C2S: Heartbeat
			const MessageID HeartbeatC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 7);
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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::HeartbeatC2SEvt::MID, __uiMessageSize ) );

				return hr;
			}; // MessageData* HeartbeatC2SEvt::Create( IHeap& memHeap )

			Result HeartbeatC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				HeartbeatC2SEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::Heartbeat, {0}:{1} ",
						prefix, pHeader->Length); 
				return ResultCode::SUCCESS;
			}; // Result HeartbeatC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Write All!! User Score and Ranking list
			const MessageID DebugPrintALLRankingCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 8);
			Result DebugPrintALLRankingCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				ScopeContext hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_FileName, ArrayLen));

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessage(const MessageHeader* pHeader)

			Result DebugPrintALLRankingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DebugPrintALLRankingCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FileName", parser.GetFileName());

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DebugPrintALLRankingCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFileName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingCmd::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFileName);

				return hr;
			}; // MessageData* DebugPrintALLRankingCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InFileName )

			Result DebugPrintALLRankingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DebugPrintALLRankingCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::DebugPrintALLRanking, {0}:{1} , TransactionID:{2}, FileName:{3,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetFileName()); 
				return ResultCode::SUCCESS;
			}; // Result DebugPrintALLRankingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID DebugPrintALLRankingRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_LOGIN, 8);
			Result DebugPrintALLRankingRes::ParseMessage(const MessageHeader* pHeader)
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

			}; // Result DebugPrintALLRankingRes::ParseMessage(const MessageHeader* pHeader)

			Result DebugPrintALLRankingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DebugPrintALLRankingRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DebugPrintALLRankingRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


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

				unsigned __uiMessageSize = (unsigned)(Message::MobileHeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingRes::MID, __uiMessageSize ) );
				ArrayView<uint8_t> BufferView(pNewMsg->GetPayload());
				BufferView.resize(0);
				OutputMemoryStream outputStream(BufferView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* DebugPrintALLRankingRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result DebugPrintALLRankingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DebugPrintALLRankingRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::DebugPrintALLRanking, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result DebugPrintALLRankingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)



		}; // namespace Login
	}; // namespace Message
}; // namespace SF



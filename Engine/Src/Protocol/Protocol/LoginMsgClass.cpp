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
#include "SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "SFProtocolHelper.h"
#include "Protocol/LoginMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace Login
		{
 			// Cmd: Login with ID/PW request
			Result LoginCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_user_id, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_password, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GameID, ArrayLen));

				return hr;

			}; // Result LoginCmd::ParseMessage(const MessageHeader* pHeader)

			Result LoginCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("user_id", parser.Getuser_id());
				variableBuilder.SetVariable("password", parser.Getpassword());
				variableBuilder.SetVariable("GameID", parser.GetGameID());

				return hr;

			}; // Result LoginCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LoginCmd::CalculateMessageSize( const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(Inuser_id)
					+ SerializedSizeOf(Inpassword)
					+ SerializedSizeOf(InGameID)
				);

				return __uiMessageSize;
			}; // size_t LoginCmd::CalculateMessageSize( const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID )


			Result LoginCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(Inuser_id)
					+ SerializedSizeOf(Inpassword)
					+ SerializedSizeOf(InGameID)
				);

				messageBuffer->msgID = LoginCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << Inuser_id);
				protocolCheck(*output << Inpassword);
				protocolCheck(*output << InGameID);

				return hr;
			}; // Result LoginCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID )

			Result LoginCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::Login, {0}:{1} , TransactionID:{2}, user_id:{3,60}, password:{4,60}, GameID:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.Getuser_id(), parser.Getpassword(), parser.GetGameID()); 
				return ResultCode::SUCCESS;
			}; // Result LoginCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result LoginRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_NickName, ArrayLen));
				protocolCheck(*input >> m_AccountID);
				protocolCheck(*input >> m_AuthTicket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_BannedReason, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GameServerAddress, ArrayLen));

				return hr;

			}; // Result LoginRes::ParseMessage(const MessageHeader* pHeader)

			Result LoginRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("AccountID", parser.GetAccountID());
				variableBuilder.SetVariable("AuthTicket", parser.GetAuthTicket());
				variableBuilder.SetVariable("BannedReason", parser.GetBannedReason());
				variableBuilder.SetVariable("GameServerAddress", parser.GetGameServerAddress());

				return hr;

			}; // Result LoginRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LoginRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InAccountID)
					+ SerializedSizeOf(InAuthTicket)
					+ SerializedSizeOf(InBannedReason)
					+ SerializedSizeOf(InGameServerAddress)
				);

				return __uiMessageSize;
			}; // size_t LoginRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )


			Result LoginRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InAccountID)
					+ SerializedSizeOf(InAuthTicket)
					+ SerializedSizeOf(InBannedReason)
					+ SerializedSizeOf(InGameServerAddress)
				);

				messageBuffer->msgID = LoginRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNickName);
				protocolCheck(*output << InAccountID);
				protocolCheck(*output << InAuthTicket);
				protocolCheck(*output << InBannedReason);
				protocolCheck(*output << InGameServerAddress);

				return hr;
			}; // Result LoginRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )

			Result LoginRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::Login, {0}:{1} , TransactionID:{2}, Result:{3:X8}, NickName:{4,60}, AccountID:{5}, AuthTicket:{6}, BannedReason:{7,60}, GameServerAddress:{8,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNickName(), parser.GetAccountID(), parser.GetAuthTicket(), parser.GetBannedReason(), parser.GetGameServerAddress()); 
				return ResultCode::SUCCESS;
			}; // Result LoginRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Login with steam login info
			Result LoginWithSteamCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_SteamAppID);
				protocolCheck(*input >> m_SteamPlayerID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SteamPlayerName, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_SteamPlayerToken, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GameID, ArrayLen));

				return hr;

			}; // Result LoginWithSteamCmd::ParseMessage(const MessageHeader* pHeader)

			Result LoginWithSteamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginWithSteamCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("SteamAppID", parser.GetSteamAppID());
				variableBuilder.SetVariable("SteamPlayerID", parser.GetSteamPlayerID());
				variableBuilder.SetVariable("SteamPlayerName", parser.GetSteamPlayerName());
				variableBuilder.SetVariable("SteamPlayerToken", parser.GetSteamPlayerToken());
				variableBuilder.SetVariable("GameID", parser.GetGameID());

				return hr;

			}; // Result LoginWithSteamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginWithSteamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginWithSteamCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginWithSteamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LoginWithSteamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InSteamAppID)
					+ SerializedSizeOf(InSteamPlayerID)
					+ SerializedSizeOf(InSteamPlayerName)
					+ SerializedSizeOf(InSteamPlayerToken)
					+ SerializedSizeOf(InGameID)
				);

				return __uiMessageSize;
			}; // size_t LoginWithSteamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID )


			Result LoginWithSteamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InSteamAppID)
					+ SerializedSizeOf(InSteamPlayerID)
					+ SerializedSizeOf(InSteamPlayerName)
					+ SerializedSizeOf(InSteamPlayerToken)
					+ SerializedSizeOf(InGameID)
				);

				messageBuffer->msgID = LoginWithSteamCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InSteamAppID);
				protocolCheck(*output << InSteamPlayerID);
				protocolCheck(*output << InSteamPlayerName);
				protocolCheck(*output << InSteamPlayerToken);
				protocolCheck(*output << InGameID);

				return hr;
			}; // Result LoginWithSteamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID )

			Result LoginWithSteamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginWithSteamCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::LoginWithSteam, {0}:{1} , TransactionID:{2}, SteamAppID:{3}, SteamPlayerID:{4}, SteamPlayerName:{5,60}, SteamPlayerToken:{6,60}, GameID:{7,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetSteamAppID(), parser.GetSteamPlayerID(), parser.GetSteamPlayerName(), parser.GetSteamPlayerToken(), parser.GetGameID()); 
				return ResultCode::SUCCESS;
			}; // Result LoginWithSteamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result LoginWithSteamRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_NickName, ArrayLen));
				protocolCheck(*input >> m_AccountID);
				protocolCheck(*input >> m_AuthTicket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_BannedReason, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_GameServerAddress, ArrayLen));

				return hr;

			}; // Result LoginWithSteamRes::ParseMessage(const MessageHeader* pHeader)

			Result LoginWithSteamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginWithSteamRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("NickName", parser.GetNickName());
				variableBuilder.SetVariable("AccountID", parser.GetAccountID());
				variableBuilder.SetVariable("AuthTicket", parser.GetAuthTicket());
				variableBuilder.SetVariable("BannedReason", parser.GetBannedReason());
				variableBuilder.SetVariable("GameServerAddress", parser.GetGameServerAddress());

				return hr;

			}; // Result LoginWithSteamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LoginWithSteamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginWithSteamRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginWithSteamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LoginWithSteamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InAccountID)
					+ SerializedSizeOf(InAuthTicket)
					+ SerializedSizeOf(InBannedReason)
					+ SerializedSizeOf(InGameServerAddress)
				);

				return __uiMessageSize;
			}; // size_t LoginWithSteamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )


			Result LoginWithSteamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InNickName)
					+ SerializedSizeOf(InAccountID)
					+ SerializedSizeOf(InAuthTicket)
					+ SerializedSizeOf(InBannedReason)
					+ SerializedSizeOf(InGameServerAddress)
				);

				messageBuffer->msgID = LoginWithSteamRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InNickName);
				protocolCheck(*output << InAccountID);
				protocolCheck(*output << InAuthTicket);
				protocolCheck(*output << InBannedReason);
				protocolCheck(*output << InGameServerAddress);

				return hr;
			}; // Result LoginWithSteamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )

			Result LoginWithSteamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LoginWithSteamRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Login::LoginWithSteam, {0}:{1} , TransactionID:{2}, Result:{3:X8}, NickName:{4,60}, AccountID:{5}, AuthTicket:{6}, BannedReason:{7,60}, GameServerAddress:{8,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetNickName(), parser.GetAccountID(), parser.GetAuthTicket(), parser.GetBannedReason(), parser.GetGameServerAddress()); 
				return ResultCode::SUCCESS;
			}; // Result LoginWithSteamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)



		}; // namespace Login
	}; // namespace Message
}; // namespace SF



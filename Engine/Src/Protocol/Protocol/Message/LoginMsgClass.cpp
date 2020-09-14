////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Login Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "String/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/Message/LoginMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace Login
		{
 			// Cmd: Login request
			const MessageID LoginCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 0);
			Result LoginCmd::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfID = 0;
				uint16_t uiSizeOfPassword = 0;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &uiSizeOfID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( m_ID, pCur, iMsgSize, sizeof(char)*uiSizeOfID ) );
				protocolCheck( Protocol::StreamParamCopy( &uiSizeOfPassword, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( m_Password, pCur, iMsgSize, sizeof(char)*uiSizeOfPassword ) );

				return hr;

			}; // Result LoginCmd::ParseMessage( MessageData* pIMsg )

			Result LoginCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				LoginCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("ID", parser.GetID());
				variableBuilder.SetVariable("Password", parser.GetPassword());

				return hr;

			}; // Result LoginCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInIDLength = InID ? (uint16_t)(strlen(InID)+1) : 1;
				uint16_t __uiInPasswordLength = InPassword ? (uint16_t)(strlen(InPassword)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInIDLength + sizeof(uint16_t) + __uiInPasswordLength 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &__uiInIDLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InID ? InID : "", __uiInIDLength );
				Protocol::PackParamCopy( pMsgData, &__uiInPasswordLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPassword ? InPassword : "", __uiInPasswordLength );

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
			Result LoginRes::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameServerAddr, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameServerAddrIPV4, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_AccID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_LoginEntityUID, pCur, iMsgSize, sizeof(uint64_t) ) );

				return hr;

			}; // Result LoginRes::ParseMessage( MessageData* pIMsg )

			Result LoginRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				LoginRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result LoginRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(NetAddress)
					+ sizeof(NetAddress)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddr, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddrIPV4, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InAccID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));
				Protocol::PackParamCopy( pMsgData, &InLoginEntityUID, sizeof(uint64_t));

				return hr;
			}; // MessageData* LoginRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )



			Result LoginRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Login:{0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerAddr:{4}, GameServerAddrIPV4:{5}, AccID:{6}, Ticket:{7}, LoginEntityUID:{8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result LoginRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Login request with Facebook UID
			const MessageID LoginByFacebookCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 1);
			Result LoginByFacebookCmd::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfFaceBookName = 0;
				uint16_t uiSizeOfEMail = 0;
				uint16_t uiSizeOfFacebookToken = 0;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_UID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &uiSizeOfFaceBookName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( m_FaceBookName, pCur, iMsgSize, sizeof(char)*uiSizeOfFaceBookName ) );
				protocolCheck( Protocol::StreamParamCopy( &uiSizeOfEMail, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( m_EMail, pCur, iMsgSize, sizeof(char)*uiSizeOfEMail ) );
				protocolCheck( Protocol::StreamParamCopy( &uiSizeOfFacebookToken, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( m_FacebookToken, pCur, iMsgSize, sizeof(char)*uiSizeOfFacebookToken ) );

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessage( MessageData* pIMsg )

			Result LoginByFacebookCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				LoginByFacebookCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("UID", parser.GetUID());
				variableBuilder.SetVariable("FaceBookName", parser.GetFaceBookName());
				variableBuilder.SetVariable("EMail", parser.GetEMail());
				variableBuilder.SetVariable("FacebookToken", parser.GetFacebookToken());

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginByFacebookCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginByFacebookCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInFaceBookNameLength = InFaceBookName ? (uint16_t)(strlen(InFaceBookName)+1) : 1;
				uint16_t __uiInEMailLength = InEMail ? (uint16_t)(strlen(InEMail)+1) : 1;
				uint16_t __uiInFacebookTokenLength = InFacebookToken ? (uint16_t)(strlen(InFacebookToken)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInFaceBookNameLength + sizeof(uint16_t) + __uiInEMailLength + sizeof(uint16_t) + __uiInFacebookTokenLength 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t)
					+ sizeof(uint64_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInFaceBookNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InFaceBookName ? InFaceBookName : "", __uiInFaceBookNameLength );
				Protocol::PackParamCopy( pMsgData, &__uiInEMailLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InEMail ? InEMail : "", __uiInEMailLength );
				Protocol::PackParamCopy( pMsgData, &__uiInFacebookTokenLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InFacebookToken ? InFacebookToken : "", __uiInFacebookTokenLength );

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
			Result LoginByFacebookRes::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameServerAddr, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameServerAddrIPV4, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_AccID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_LoginEntityUID, pCur, iMsgSize, sizeof(uint64_t) ) );

				return hr;

			}; // Result LoginByFacebookRes::ParseMessage( MessageData* pIMsg )

			Result LoginByFacebookRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				LoginByFacebookRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result LoginByFacebookRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LoginByFacebookRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(NetAddress)
					+ sizeof(NetAddress)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddr, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddrIPV4, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InAccID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));
				Protocol::PackParamCopy( pMsgData, &InLoginEntityUID, sizeof(uint64_t));

				return hr;
			}; // MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )



			Result LoginByFacebookRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LoginByFacebookRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LoginByFacebook:{0}:{1} , TransactionID:{2}, Result:{3:X8}, GameServerAddr:{4}, GameServerAddrIPV4:{5}, AccID:{6}, Ticket:{7}, LoginEntityUID:{8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result LoginByFacebookRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Login request
			const MessageID CreateRandomUserCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 2);
			Result CreateRandomUserCmd::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfCellPhone = 0;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &uiSizeOfCellPhone, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( m_CellPhone, pCur, iMsgSize, sizeof(char)*uiSizeOfCellPhone ) );

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessage( MessageData* pIMsg )

			Result CreateRandomUserCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				CreateRandomUserCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("CellPhone", parser.GetCellPhone());

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateRandomUserCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateRandomUserCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInCellPhoneLength = InCellPhone ? (uint16_t)(strlen(InCellPhone)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInCellPhoneLength 
					+ sizeof(uint64_t)
					+ sizeof(uint32_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InGameID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &__uiInCellPhoneLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InCellPhone ? InCellPhone : "", __uiInCellPhoneLength );

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

			const MessageID CreateRandomUserRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 2);
			Result CreateRandomUserRes::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameServerAddr, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_GameServerAddrIPV4, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_AccID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_LoginEntityUID, pCur, iMsgSize, sizeof(uint64_t) ) );

				return hr;

			}; // Result CreateRandomUserRes::ParseMessage( MessageData* pIMsg )

			Result CreateRandomUserRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				CreateRandomUserRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());

				return hr;

			}; // Result CreateRandomUserRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateRandomUserRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateRandomUserRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(NetAddress)
					+ sizeof(NetAddress)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddr, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddrIPV4, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InAccID, sizeof(AccountID));
				Protocol::PackParamCopy( pMsgData, &InTicket, sizeof(AuthTicket));
				Protocol::PackParamCopy( pMsgData, &InLoginEntityUID, sizeof(uint64_t));

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

			// Cmd: Update my score and Get Ranking list
			const MessageID UpdateMyScoreCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 3);
			Result UpdateMyScoreCmd::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_RankingScore, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_RankingType, pCur, iMsgSize, sizeof(RankingType) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Count, pCur, iMsgSize, sizeof(uint16_t) ) );

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessage( MessageData* pIMsg )

			Result UpdateMyScoreCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				UpdateMyScoreCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingScore", parser.GetRankingScore());
				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateMyScoreCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* UpdateMyScoreCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint64_t)
					+ sizeof(RankingType)
					+ sizeof(uint16_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InRankingScore, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InRankingType, sizeof(RankingType));
				Protocol::PackParamCopy( pMsgData, &InCount, sizeof(uint16_t));

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

			const MessageID UpdateMyScoreRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 3);
			Result UpdateMyScoreRes::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofRanking = 0; TotalRankingPlayerInformation* pRanking = nullptr;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolCheck( Protocol::StreamParamCopy( &numberofRanking, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( pRanking, pCur, iMsgSize, sizeof(TotalRankingPlayerInformation)*numberofRanking ) );
				m_Ranking.SetLinkedBuffer(numberofRanking, numberofRanking, pRanking);

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessage( MessageData* pIMsg )

			Result UpdateMyScoreRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				UpdateMyScoreRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateMyScoreRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* UpdateMyScoreRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(TotalRankingPlayerInformation)*InRanking.size() + sizeof(uint16_t));


				uint16_t numberOfInRanking = (uint16_t)InRanking.size(); 
				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &numberOfInRanking, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InRanking.data(), (INT)(sizeof(TotalRankingPlayerInformation)*InRanking.size())); 

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
			const MessageID GetRankingListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 4);
			Result GetRankingListCmd::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_RankingType, pCur, iMsgSize, sizeof(RankingType) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_BaseRanking, pCur, iMsgSize, sizeof(uint8_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Count, pCur, iMsgSize, sizeof(uint8_t) ) );

				return hr;

			}; // Result GetRankingListCmd::ParseMessage( MessageData* pIMsg )

			Result GetRankingListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				GetRankingListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
				variableBuilder.SetVariable("BaseRanking", parser.GetBaseRanking());
				variableBuilder.SetVariable("Count", parser.GetCount());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetRankingListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(RankingType)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InRankingType, sizeof(RankingType));
				Protocol::PackParamCopy( pMsgData, &InBaseRanking, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InCount, sizeof(uint8_t));

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

			const MessageID GetRankingListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 4);
			Result GetRankingListRes::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofRanking = 0; TotalRankingPlayerInformation* pRanking = nullptr;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolCheck( Protocol::StreamParamCopy( &numberofRanking, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( pRanking, pCur, iMsgSize, sizeof(TotalRankingPlayerInformation)*numberofRanking ) );
				m_Ranking.SetLinkedBuffer(numberofRanking, numberofRanking, pRanking);

				return hr;

			}; // Result GetRankingListRes::ParseMessage( MessageData* pIMsg )

			Result GetRankingListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				GetRankingListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());

				return hr;

			}; // Result GetRankingListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetRankingListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetRankingListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(TotalRankingPlayerInformation)*InRanking.size() + sizeof(uint16_t));


				uint16_t numberOfInRanking = (uint16_t)InRanking.size(); 
				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &numberOfInRanking, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InRanking.data(), (INT)(sizeof(TotalRankingPlayerInformation)*InRanking.size())); 

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
			const MessageID DataTestCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 5);
			Result DataTestCmd::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofTestData = 0; uint8_t* pTestData = nullptr;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &numberofTestData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( pTestData, pCur, iMsgSize, sizeof(uint8_t)*numberofTestData ) );
				m_TestData.SetLinkedBuffer(numberofTestData, numberofTestData, pTestData);

				return hr;

			}; // Result DataTestCmd::ParseMessage( MessageData* pIMsg )

			Result DataTestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				DataTestCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("TestData", parser.GetTestData());

				return hr;

			}; // Result DataTestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DataTestCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* DataTestCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(uint8_t)*InTestData.size() + sizeof(uint16_t));


				uint16_t numberOfInTestData = (uint16_t)InTestData.size(); 
				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInTestData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InTestData.data(), (INT)(sizeof(uint8_t)*InTestData.size())); 

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

			const MessageID DataTestRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 5);
			Result DataTestRes::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofTestData = 0; uint8_t* pTestData = nullptr;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolCheck( Protocol::StreamParamCopy( &numberofTestData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( pTestData, pCur, iMsgSize, sizeof(uint8_t)*numberofTestData ) );
				m_TestData.SetLinkedBuffer(numberofTestData, numberofTestData, pTestData);

				return hr;

			}; // Result DataTestRes::ParseMessage( MessageData* pIMsg )

			Result DataTestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				DataTestRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TestData", parser.GetTestData());

				return hr;

			}; // Result DataTestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DataTestRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* DataTestRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result)
					+ sizeof(uint8_t)*InTestData.size() + sizeof(uint16_t));


				uint16_t numberOfInTestData = (uint16_t)InTestData.size(); 
				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &numberOfInTestData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InTestData.data(), (INT)(sizeof(uint8_t)*InTestData.size())); 

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

			// C2S: Heartbit
			const MessageID HeartBitC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 6);
			Result HeartBitC2SEvt::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;


				protocolCheckPtr(pIMsg);



				return hr;

			}; // Result HeartBitC2SEvt::ParseMessage( MessageData* pIMsg )

			Result HeartBitC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				HeartBitC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));


				return hr;

			}; // Result HeartBitC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result HeartBitC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) HeartBitC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result HeartBitC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* HeartBitC2SEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) );


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::HeartBitC2SEvt::MID, __uiMessageSize ) );


				return hr;
			}; // MessageData* HeartBitC2SEvt::Create( IHeap& memHeap )



			Result HeartBitC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				HeartBitC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "HeartBit:{0}:{1} ",
						prefix, pMsg->GetMessageHeader()->Length); 
				return ResultCode::SUCCESS;
			}; // Result HeartBitC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Write All!! User Score and Ranking list
			const MessageID DebugPrintALLRankingCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 7);
			Result DebugPrintALLRankingCmd::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfFileName = 0;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &uiSizeOfFileName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolCheck( Protocol::StreamParamLnk( m_FileName, pCur, iMsgSize, sizeof(char)*uiSizeOfFileName ) );

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessage( MessageData* pIMsg )

			Result DebugPrintALLRankingCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				DebugPrintALLRankingCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FileName", parser.GetFileName());

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DebugPrintALLRankingCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* DebugPrintALLRankingCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const char* InFileName )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInFileNameLength = InFileName ? (uint16_t)(strlen(InFileName)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInFileNameLength 
					+ sizeof(uint64_t));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInFileNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InFileName ? InFileName : "", __uiInFileNameLength );

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

			const MessageID DebugPrintALLRankingRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 7);
			Result DebugPrintALLRankingRes::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolCheckPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolCheck( Protocol::StreamParamCopy( &m_TransactionID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolCheck( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessage( MessageData* pIMsg )

			Result DebugPrintALLRankingRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				DebugPrintALLRankingRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DebugPrintALLRankingRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* DebugPrintALLRankingRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				FunctionContext hr([pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						delete pNewMsg;
						return nullptr;
					}
					return pNewMsg;
				});

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(Result));


				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InTransactionID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));

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



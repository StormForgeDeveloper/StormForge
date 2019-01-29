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
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfID = 0;
				uint16_t uiSizeOfPassword = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfID, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_ID, pCur, iMsgSize, sizeof(char)*uiSizeOfID ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPassword, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_Password, pCur, iMsgSize, sizeof(char)*uiSizeOfPassword ) );


			Proc_End:

				return hr;

			}; // Result LoginCmd::ParseMessage( MessageData* pIMsg )

			Result LoginCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("ID", parser.GetID());
				variableBuilder.SetVariable("Password", parser.GetPassword());


			Proc_End:

				return hr;

			}; // Result LoginCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LoginCmd(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LoginCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginCmd::Create( IHeap& memHeap, const uint32_t &InGameID, const char* InID, const char* InPassword )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInIDLength = InID ? (uint16_t)(strlen(InID)+1) : 1;
				uint16_t __uiInPasswordLength = InPassword ? (uint16_t)(strlen(InPassword)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInIDLength + sizeof(uint16_t) + __uiInPasswordLength 
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &__uiInIDLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InID ? InID : "", __uiInIDLength );
				Protocol::PackParamCopy( pMsgData, &__uiInPasswordLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPassword ? InPassword : "", __uiInPasswordLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LoginCmd::Create( IHeap& memHeap, const uint32_t &InGameID, const char* InID, const char* InPassword )



			Result LoginCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				LoginCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Login:{0}:{1} , GameID:{2}, ID:{3,60}, Password:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameID(), parser.GetID(), parser.GetPassword()); 
				return ResultCode::SUCCESS;
			}; // Result LoginCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			const MessageID LoginRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 0);
			Result LoginRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameServerAddr, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameServerAddrIPV4, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolChk( Protocol::StreamParamCopy( &m_AccID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LoginEntityUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result LoginRes::ParseMessage( MessageData* pIMsg )

			Result LoginRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());


			Proc_End:

				return hr;

			}; // Result LoginRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LoginRes(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LoginRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginRes::Create( IHeap& memHeap, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result)
					+ sizeof(NetAddress)
					+ sizeof(NetAddress)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddr, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddrIPV4, sizeof(NetAddress));
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

			}; // MessageData* LoginRes::Create( IHeap& memHeap, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )



			Result LoginRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				LoginRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "Login:{0}:{1} , Result:{2:X8}, GameServerAddr:{3}, GameServerAddrIPV4:{4}, AccID:{5}, Ticket:{6}, LoginEntityUID:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result LoginRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			// Cmd: Login request with Facebook UID
			const MessageID LoginByFacebookCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 1);
			Result LoginByFacebookCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfFaceBookName = 0;
				uint16_t uiSizeOfEMail = 0;
				uint16_t uiSizeOfFacebookToken = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_UID, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfFaceBookName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_FaceBookName, pCur, iMsgSize, sizeof(char)*uiSizeOfFaceBookName ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfEMail, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_EMail, pCur, iMsgSize, sizeof(char)*uiSizeOfEMail ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfFacebookToken, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_FacebookToken, pCur, iMsgSize, sizeof(char)*uiSizeOfFacebookToken ) );


			Proc_End:

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessage( MessageData* pIMsg )

			Result LoginByFacebookCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginByFacebookCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("UID", parser.GetUID());
				variableBuilder.SetVariable("FaceBookName", parser.GetFaceBookName());
				variableBuilder.SetVariable("EMail", parser.GetEMail());
				variableBuilder.SetVariable("FacebookToken", parser.GetFacebookToken());


			Proc_End:

				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LoginByFacebookCmd(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LoginByFacebookCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginByFacebookCmd::Create( IHeap& memHeap, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInFaceBookNameLength = InFaceBookName ? (uint16_t)(strlen(InFaceBookName)+1) : 1;
				uint16_t __uiInEMailLength = InEMail ? (uint16_t)(strlen(InEMail)+1) : 1;
				uint16_t __uiInFacebookTokenLength = InFacebookToken ? (uint16_t)(strlen(InFacebookToken)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInFaceBookNameLength + sizeof(uint16_t) + __uiInEMailLength + sizeof(uint16_t) + __uiInFacebookTokenLength 
					+ sizeof(uint32_t)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InUID, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &__uiInFaceBookNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InFaceBookName ? InFaceBookName : "", __uiInFaceBookNameLength );
				Protocol::PackParamCopy( pMsgData, &__uiInEMailLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InEMail ? InEMail : "", __uiInEMailLength );
				Protocol::PackParamCopy( pMsgData, &__uiInFacebookTokenLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InFacebookToken ? InFacebookToken : "", __uiInFacebookTokenLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LoginByFacebookCmd::Create( IHeap& memHeap, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )



			Result LoginByFacebookCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				LoginByFacebookCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LoginByFacebook:{0}:{1} , GameID:{2}, UID:{3}, FaceBookName:{4,60}, EMail:{5,60}, FacebookToken:{6,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameID(), parser.GetUID(), parser.GetFaceBookName(), parser.GetEMail(), parser.GetFacebookToken()); 
				return ResultCode::SUCCESS;
			}; // Result LoginByFacebookCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			const MessageID LoginByFacebookRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 1);
			Result LoginByFacebookRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameServerAddr, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameServerAddrIPV4, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolChk( Protocol::StreamParamCopy( &m_AccID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LoginEntityUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result LoginByFacebookRes::ParseMessage( MessageData* pIMsg )

			Result LoginByFacebookRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LoginByFacebookRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());


			Proc_End:

				return hr;

			}; // Result LoginByFacebookRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LoginByFacebookRes(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LoginByFacebookRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result)
					+ sizeof(NetAddress)
					+ sizeof(NetAddress)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::LoginByFacebookRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddr, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddrIPV4, sizeof(NetAddress));
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

			}; // MessageData* LoginByFacebookRes::Create( IHeap& memHeap, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )



			Result LoginByFacebookRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				LoginByFacebookRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LoginByFacebook:{0}:{1} , Result:{2:X8}, GameServerAddr:{3}, GameServerAddrIPV4:{4}, AccID:{5}, Ticket:{6}, LoginEntityUID:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result LoginByFacebookRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			// Cmd: Login request
			const MessageID CreateRandomUserCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 2);
			Result CreateRandomUserCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfCellPhone = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_GameID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfCellPhone, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_CellPhone, pCur, iMsgSize, sizeof(char)*uiSizeOfCellPhone ) );


			Proc_End:

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessage( MessageData* pIMsg )

			Result CreateRandomUserCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreateRandomUserCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameID", parser.GetGameID());
				variableBuilder.SetVariable("CellPhone", parser.GetCellPhone());


			Proc_End:

				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CreateRandomUserCmd(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CreateRandomUserCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateRandomUserCmd::Create( IHeap& memHeap, const uint32_t &InGameID, const char* InCellPhone )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInCellPhoneLength = InCellPhone ? (uint16_t)(strlen(InCellPhone)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInCellPhoneLength 
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InGameID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &__uiInCellPhoneLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InCellPhone ? InCellPhone : "", __uiInCellPhoneLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* CreateRandomUserCmd::Create( IHeap& memHeap, const uint32_t &InGameID, const char* InCellPhone )



			Result CreateRandomUserCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				CreateRandomUserCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateRandomUser:{0}:{1} , GameID:{2}, CellPhone:{3,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameID(), parser.GetCellPhone()); 
				return ResultCode::SUCCESS;
			}; // Result CreateRandomUserCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			const MessageID CreateRandomUserRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 2);
			Result CreateRandomUserRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameServerAddr, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolChk( Protocol::StreamParamCopy( &m_GameServerAddrIPV4, pCur, iMsgSize, sizeof(NetAddress) ) );
				protocolChk( Protocol::StreamParamCopy( &m_AccID, pCur, iMsgSize, sizeof(AccountID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Ticket, pCur, iMsgSize, sizeof(AuthTicket) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LoginEntityUID, pCur, iMsgSize, sizeof(uint64_t) ) );


			Proc_End:

				return hr;

			}; // Result CreateRandomUserRes::ParseMessage( MessageData* pIMsg )

			Result CreateRandomUserRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreateRandomUserRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("GameServerAddr", parser.GetGameServerAddr());
				variableBuilder.SetVariable("GameServerAddrIPV4", parser.GetGameServerAddrIPV4());
				variableBuilder.SetVariable("AccID", parser.GetAccID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("LoginEntityUID", parser.GetLoginEntityUID());


			Proc_End:

				return hr;

			}; // Result CreateRandomUserRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) CreateRandomUserRes(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result CreateRandomUserRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* CreateRandomUserRes::Create( IHeap& memHeap, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result)
					+ sizeof(NetAddress)
					+ sizeof(NetAddress)
					+ sizeof(AccountID)
					+ sizeof(AuthTicket)
					+ sizeof(uint64_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::CreateRandomUserRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddr, sizeof(NetAddress));
				Protocol::PackParamCopy( pMsgData, &InGameServerAddrIPV4, sizeof(NetAddress));
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

			}; // MessageData* CreateRandomUserRes::Create( IHeap& memHeap, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )



			Result CreateRandomUserRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				CreateRandomUserRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateRandomUser:{0}:{1} , Result:{2:X8}, GameServerAddr:{3}, GameServerAddrIPV4:{4}, AccID:{5}, Ticket:{6}, LoginEntityUID:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetGameServerAddr(), parser.GetGameServerAddrIPV4(), parser.GetAccID(), parser.GetTicket(), parser.GetLoginEntityUID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateRandomUserRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			// Cmd: Update my score and Get Ranking list
			const MessageID UpdateMyScoreCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 3);
			Result UpdateMyScoreCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RankingScore, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_RankingType, pCur, iMsgSize, sizeof(RankingType) ) );
				protocolChk( Protocol::StreamParamCopy( &m_Count, pCur, iMsgSize, sizeof(uint16_t) ) );


			Proc_End:

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessage( MessageData* pIMsg )

			Result UpdateMyScoreCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UpdateMyScoreCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RankingScore", parser.GetRankingScore());
				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
				variableBuilder.SetVariable("Count", parser.GetCount());


			Proc_End:

				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) UpdateMyScoreCmd(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result UpdateMyScoreCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* UpdateMyScoreCmd::Create( IHeap& memHeap, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint64_t)
					+ sizeof(RankingType)
					+ sizeof(uint16_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRankingScore, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &InRankingType, sizeof(RankingType));
				Protocol::PackParamCopy( pMsgData, &InCount, sizeof(uint16_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* UpdateMyScoreCmd::Create( IHeap& memHeap, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )



			Result UpdateMyScoreCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				UpdateMyScoreCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UpdateMyScore:{0}:{1} , RankingScore:{2}, RankingType:{3}, Count:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRankingScore(), (int)parser.GetRankingType(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateMyScoreCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			const MessageID UpdateMyScoreRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 3);
			Result UpdateMyScoreRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofRanking = 0; TotalRankingPlayerInformation* pRanking = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofRanking, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pRanking, pCur, iMsgSize, sizeof(TotalRankingPlayerInformation)*numberofRanking ) );
				m_Ranking.SetLinkedBuffer(numberofRanking, numberofRanking, pRanking);


			Proc_End:

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessage( MessageData* pIMsg )

			Result UpdateMyScoreRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UpdateMyScoreRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());


			Proc_End:

				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) UpdateMyScoreRes(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result UpdateMyScoreRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* UpdateMyScoreRes::Create( IHeap& memHeap, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result)
					+ sizeof(TotalRankingPlayerInformation)*InRanking.size() + sizeof(uint16_t));


				uint16_t numberOfInRanking = (uint16_t)InRanking.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::UpdateMyScoreRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

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

			}; // MessageData* UpdateMyScoreRes::Create( IHeap& memHeap, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )



			Result UpdateMyScoreRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				UpdateMyScoreRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UpdateMyScore:{0}:{1} , Result:{2:X8}, Ranking:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetRanking()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateMyScoreRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			// Cmd: Get Ranking lise
			const MessageID GetRankingListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 4);
			Result GetRankingListCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RankingType, pCur, iMsgSize, sizeof(RankingType) ) );
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

				variableBuilder.SetVariable("RankingType", (int)parser.GetRankingType());
				variableBuilder.SetVariable("BaseRanking", parser.GetBaseRanking());
				variableBuilder.SetVariable("Count", parser.GetCount());


			Proc_End:

				return hr;

			}; // Result GetRankingListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetRankingListCmd(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetRankingListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetRankingListCmd::Create( IHeap& memHeap, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(RankingType)
					+ sizeof(uint8_t)
					+ sizeof(uint8_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRankingType, sizeof(RankingType));
				Protocol::PackParamCopy( pMsgData, &InBaseRanking, sizeof(uint8_t));
				Protocol::PackParamCopy( pMsgData, &InCount, sizeof(uint8_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* GetRankingListCmd::Create( IHeap& memHeap, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )



			Result GetRankingListCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				GetRankingListCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetRankingList:{0}:{1} , RankingType:{2}, BaseRanking:{3}, Count:{4}",
						prefix, pMsg->GetMessageHeader()->Length, (int)parser.GetRankingType(), parser.GetBaseRanking(), parser.GetCount()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			const MessageID GetRankingListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 4);
			Result GetRankingListRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofRanking = 0; TotalRankingPlayerInformation* pRanking = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

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

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("Ranking", parser.GetRanking());


			Proc_End:

				return hr;

			}; // Result GetRankingListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) GetRankingListRes(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result GetRankingListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* GetRankingListRes::Create( IHeap& memHeap, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result)
					+ sizeof(TotalRankingPlayerInformation)*InRanking.size() + sizeof(uint16_t));


				uint16_t numberOfInRanking = (uint16_t)InRanking.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::GetRankingListRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

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

			}; // MessageData* GetRankingListRes::Create( IHeap& memHeap, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )



			Result GetRankingListRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				GetRankingListRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetRankingList:{0}:{1} , Result:{2:X8}, Ranking:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetRanking()); 
				return ResultCode::SUCCESS;
			}; // Result GetRankingListRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			// Cmd: For network test
			const MessageID DataTestCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 5);
			Result DataTestCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofTestData = 0; uint8_t* pTestData = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &numberofTestData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pTestData, pCur, iMsgSize, sizeof(uint8_t)*numberofTestData ) );
				m_TestData.SetLinkedBuffer(numberofTestData, numberofTestData, pTestData);


			Proc_End:

				return hr;

			}; // Result DataTestCmd::ParseMessage( MessageData* pIMsg )

			Result DataTestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DataTestCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TestData", parser.GetTestData());


			Proc_End:

				return hr;

			}; // Result DataTestCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) DataTestCmd(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result DataTestCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* DataTestCmd::Create( IHeap& memHeap, const Array<uint8_t>& InTestData )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(uint8_t)*InTestData.size() + sizeof(uint16_t));


				uint16_t numberOfInTestData = (uint16_t)InTestData.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &numberOfInTestData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InTestData.data(), (INT)(sizeof(uint8_t)*InTestData.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* DataTestCmd::Create( IHeap& memHeap, const Array<uint8_t>& InTestData )



			Result DataTestCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				DataTestCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DataTest:{0}:{1} , TestData:{2,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTestData()); 
				return ResultCode::SUCCESS;
			}; // Result DataTestCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			const MessageID DataTestRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 5);
			Result DataTestRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofTestData = 0; uint8_t* pTestData = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofTestData, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pTestData, pCur, iMsgSize, sizeof(uint8_t)*numberofTestData ) );
				m_TestData.SetLinkedBuffer(numberofTestData, numberofTestData, pTestData);


			Proc_End:

				return hr;

			}; // Result DataTestRes::ParseMessage( MessageData* pIMsg )

			Result DataTestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DataTestRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("TestData", parser.GetTestData());


			Proc_End:

				return hr;

			}; // Result DataTestRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) DataTestRes(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result DataTestRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* DataTestRes::Create( IHeap& memHeap, const Result &InResult, const Array<uint8_t>& InTestData )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result)
					+ sizeof(uint8_t)*InTestData.size() + sizeof(uint16_t));


				uint16_t numberOfInTestData = (uint16_t)InTestData.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DataTestRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &numberOfInTestData, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InTestData.data(), (INT)(sizeof(uint8_t)*InTestData.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* DataTestRes::Create( IHeap& memHeap, const Result &InResult, const Array<uint8_t>& InTestData )



			Result DataTestRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				DataTestRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DataTest:{0}:{1} , Result:{2:X8}, TestData:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetTestData()); 
				return ResultCode::SUCCESS;
			}; // Result DataTestRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			// C2S: Heartbit
			const MessageID HeartBitC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 6);
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

			Result HeartBitC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) HeartBitC2SEvt(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result HeartBitC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* HeartBitC2SEvt::Create( IHeap& memHeap )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) );


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::HeartBitC2SEvt::MID, __uiMessageSize ) );



			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* HeartBitC2SEvt::Create( IHeap& memHeap )



			Result HeartBitC2SEvt::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				HeartBitC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "HeartBit:{0}:{1} ",
						prefix, pMsg->GetMessageHeader()->Length); 
				return ResultCode::SUCCESS;
			}; // Result HeartBitC2SEvt::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			// Cmd: Write All!! User Score and Ranking list
			const MessageID DebugPrintALLRankingCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 7);
			Result DebugPrintALLRankingCmd::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfFileName = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &uiSizeOfFileName, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_FileName, pCur, iMsgSize, sizeof(char)*uiSizeOfFileName ) );


			Proc_End:

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessage( MessageData* pIMsg )

			Result DebugPrintALLRankingCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DebugPrintALLRankingCmd parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("FileName", parser.GetFileName());


			Proc_End:

				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) DebugPrintALLRankingCmd(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result DebugPrintALLRankingCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* DebugPrintALLRankingCmd::Create( IHeap& memHeap, const char* InFileName )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInFileNameLength = InFileName ? (uint16_t)(strlen(InFileName)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) +  + sizeof(uint16_t) + __uiInFileNameLength );


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingCmd::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &__uiInFileNameLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InFileName ? InFileName : "", __uiInFileNameLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* DebugPrintALLRankingCmd::Create( IHeap& memHeap, const char* InFileName )



			Result DebugPrintALLRankingCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				DebugPrintALLRankingCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DebugPrintALLRanking:{0}:{1} , FileName:{2,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetFileName()); 
				return ResultCode::SUCCESS;
			}; // Result DebugPrintALLRankingCmd::TraceOut(const char* prefix, MessageDataPtr& pMsg)

			const MessageID DebugPrintALLRankingRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_LOGIN, 7);
			Result DebugPrintALLRankingRes::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );


			Proc_End:

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessage( MessageData* pIMsg )

			Result DebugPrintALLRankingRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DebugPrintALLRankingRes parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());


			Proc_End:

				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) DebugPrintALLRankingRes(pIMsg));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result DebugPrintALLRankingRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* DebugPrintALLRankingRes::Create( IHeap& memHeap, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MobileMessageHeader) 
					+ sizeof(Result));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Login::DebugPrintALLRankingRes::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* DebugPrintALLRankingRes::Create( IHeap& memHeap, const Result &InResult )



			Result DebugPrintALLRankingRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)
			{
 				DebugPrintALLRankingRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DebugPrintALLRanking:{0}:{1} , Result:{2:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result DebugPrintALLRankingRes::TraceOut(const char* prefix, MessageDataPtr& pMsg)



		}; // namespace Login
	}; // namespace Message
}; // namespace SF



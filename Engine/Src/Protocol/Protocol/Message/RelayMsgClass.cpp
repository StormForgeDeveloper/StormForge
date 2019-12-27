////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Relay Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "String/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/Message/RelayMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace Relay
		{
 			// C2S: Event for Player Join request.
			const MessageID JoinRelayInstanceC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_RELAY, 0);
			Result JoinRelayInstanceC2SEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t uiSizeOfPlayerIdentifier = 0;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RelayInstanceID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(PlayerID) ) );
				protocolChk( Protocol::StreamParamCopy( &uiSizeOfPlayerIdentifier, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( m_PlayerIdentifier, pCur, iMsgSize, sizeof(char)*uiSizeOfPlayerIdentifier ) );


			Proc_End:

				return hr;

			}; // Result JoinRelayInstanceC2SEvt::ParseMessage( MessageData* pIMsg )

			Result JoinRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinRelayInstanceC2SEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerIdentifier", parser.GetPlayerIdentifier());


			Proc_End:

				return hr;

			}; // Result JoinRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinRelayInstanceC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinRelayInstanceC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				uint16_t __uiInPlayerIdentifierLength = InPlayerIdentifier ? (uint16_t)(strlen(InPlayerIdentifier)+1) : 1;
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) +  + sizeof(uint16_t) + __uiInPlayerIdentifierLength 
					+ sizeof(uint32_t)
					+ sizeof(PlayerID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::JoinRelayInstanceC2SEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRelayInstanceID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(PlayerID));
				Protocol::PackParamCopy( pMsgData, &__uiInPlayerIdentifierLength, sizeof(uint16_t) );
				Protocol::PackParamCopy( pMsgData, InPlayerIdentifier ? InPlayerIdentifier : "", __uiInPlayerIdentifierLength );


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinRelayInstanceC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )



			Result JoinRelayInstanceC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinRelayInstanceC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinRelayInstance:{0}:{1} , RelayInstanceID:{2}, PlayerID:{3}, PlayerIdentifier:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRelayInstanceID(), parser.GetPlayerID(), parser.GetPlayerIdentifier()); 
				return ResultCode::SUCCESS;
			}; // Result JoinRelayInstanceC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Event for joined player
			const MessageID JoinRelayInstanceResS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_RELAY, 1);
			Result JoinRelayInstanceResS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofMemberInfos = 0; RelayPlayerInfo* pMemberInfos = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_Result, pCur, iMsgSize, sizeof(Result) ) );
				protocolChk( Protocol::StreamParamCopy( &m_RelayInstanceID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_MyPlayerRelayID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofMemberInfos, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pMemberInfos, pCur, iMsgSize, sizeof(RelayPlayerInfo)*numberofMemberInfos ) );
				m_MemberInfos.SetLinkedBuffer(numberofMemberInfos, numberofMemberInfos, pMemberInfos);


			Proc_End:

				return hr;

			}; // Result JoinRelayInstanceResS2CEvt::ParseMessage( MessageData* pIMsg )

			Result JoinRelayInstanceResS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinRelayInstanceResS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("MyPlayerRelayID", parser.GetMyPlayerRelayID());
				variableBuilder.SetVariable("MemberInfos", parser.GetMemberInfos());


			Proc_End:

				return hr;

			}; // Result JoinRelayInstanceResS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinRelayInstanceResS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) JoinRelayInstanceResS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result JoinRelayInstanceResS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinRelayInstanceResS2CEvt::Create( IHeap& memHeap, const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyPlayerRelayID, const Array<RelayPlayerInfo>& InMemberInfos )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ sizeof(Result)
					+ sizeof(uint32_t)
					+ sizeof(uint32_t)
					+ sizeof(RelayPlayerInfo)*InMemberInfos.size() + sizeof(uint16_t));


				uint16_t numberOfInMemberInfos = (uint16_t)InMemberInfos.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::JoinRelayInstanceResS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InResult, sizeof(Result));
				Protocol::PackParamCopy( pMsgData, &InRelayInstanceID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InMyPlayerRelayID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInMemberInfos, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InMemberInfos.data(), (INT)(sizeof(RelayPlayerInfo)*InMemberInfos.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* JoinRelayInstanceResS2CEvt::Create( IHeap& memHeap, const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyPlayerRelayID, const Array<RelayPlayerInfo>& InMemberInfos )



			Result JoinRelayInstanceResS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinRelayInstanceResS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinRelayInstanceRes:{0}:{1} , Result:{2:X8}, RelayInstanceID:{3}, MyPlayerRelayID:{4}, MemberInfos:{5,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetRelayInstanceID(), parser.GetMyPlayerRelayID(), parser.GetMemberInfos()); 
				return ResultCode::SUCCESS;
			}; // Result JoinRelayInstanceResS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Event for Player Join request.
			const MessageID LeaveRelayInstanceC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_RELAY, 2);
			Result LeaveRelayInstanceC2SEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RelayInstanceID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_PlayerID, pCur, iMsgSize, sizeof(PlayerID) ) );


			Proc_End:

				return hr;

			}; // Result LeaveRelayInstanceC2SEvt::ParseMessage( MessageData* pIMsg )

			Result LeaveRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LeaveRelayInstanceC2SEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());


			Proc_End:

				return hr;

			}; // Result LeaveRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) LeaveRelayInstanceC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result LeaveRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeaveRelayInstanceC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ sizeof(uint32_t)
					+ sizeof(PlayerID));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::LeaveRelayInstanceC2SEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRelayInstanceID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InPlayerID, sizeof(PlayerID));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* LeaveRelayInstanceC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )



			Result LeaveRelayInstanceC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LeaveRelayInstanceC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LeaveRelayInstance:{0}:{1} , RelayInstanceID:{2}, PlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRelayInstanceID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result LeaveRelayInstanceC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Event for Player joined.
			const MessageID PlayerJoinS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_RELAY, 3);
			Result PlayerJoinS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RelayInstanceID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_JoinedPlayerInfo, pCur, iMsgSize, sizeof(RelayPlayerInfo) ) );


			Proc_End:

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerJoinS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerJoinS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("JoinedPlayerInfo", parser.GetJoinedPlayerInfo());


			Proc_End:

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerJoinS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) PlayerJoinS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerJoinS2CEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ sizeof(uint32_t)
					+ sizeof(RelayPlayerInfo));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::PlayerJoinS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRelayInstanceID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InJoinedPlayerInfo, sizeof(RelayPlayerInfo));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PlayerJoinS2CEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )



			Result PlayerJoinS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerJoinS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerJoin:{0}:{1} , RelayInstanceID:{2}, JoinedPlayerInfo:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRelayInstanceID(), parser.GetJoinedPlayerInfo()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerJoinS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Event for Player left.
			const MessageID PlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_RELAY, 4);
			Result PlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RelayInstanceID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_LeftPlayerID, pCur, iMsgSize, sizeof(PlayerID) ) );
				protocolChk( Protocol::StreamParamCopy( &m_KickedReason, pCur, iMsgSize, sizeof(uint32_t) ) );


			Proc_End:

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerLeftS2CEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());
				variableBuilder.SetVariable("KickedReason", parser.GetKickedReason());


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

			MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ sizeof(uint32_t)
					+ sizeof(PlayerID)
					+ sizeof(uint32_t));


				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::PlayerLeftS2CEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRelayInstanceID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InLeftPlayerID, sizeof(PlayerID));
				Protocol::PackParamCopy( pMsgData, &InKickedReason, sizeof(uint32_t));


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )



			Result PlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerLeftS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerLeft:{0}:{1} , RelayInstanceID:{2}, LeftPlayerID:{3}, KickedReason:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRelayInstanceID(), parser.GetLeftPlayerID(), parser.GetKickedReason()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Relay packet
			const MessageID RelayPacketC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_RELAY, 5);
			Result RelayPacketC2SEvt::ParseMessage( MessageData* pIMsg )
			{
 				Result hr;

				int iMsgSize;
				uint8_t* pCur;
				uint16_t numberofPayload = 0; uint8_t* pPayload = nullptr;

				protocolChkPtr(pIMsg);

				iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				pCur = pIMsg->GetMessageData();

				protocolChk( Protocol::StreamParamCopy( &m_RelayInstanceID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_SenderRelayID, pCur, iMsgSize, sizeof(uint32_t) ) );
				protocolChk( Protocol::StreamParamCopy( &m_TargetRelayMask, pCur, iMsgSize, sizeof(uint64_t) ) );
				protocolChk( Protocol::StreamParamCopy( &numberofPayload, pCur, iMsgSize, sizeof(uint16_t) ) );
				protocolChk( Protocol::StreamParamLnk( pPayload, pCur, iMsgSize, sizeof(uint8_t)*numberofPayload ) );
				m_Payload.SetLinkedBuffer(numberofPayload, numberofPayload, pPayload);


			Proc_End:

				return hr;

			}; // Result RelayPacketC2SEvt::ParseMessage( MessageData* pIMsg )

			Result RelayPacketC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RelayPacketC2SEvt parser;
				protocolChk(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("SenderRelayID", parser.GetSenderRelayID());
				variableBuilder.SetVariable("TargetRelayMask", parser.GetTargetRelayMask());
				variableBuilder.SetVariable("Payload", parser.GetPayload());


			Proc_End:

				return hr;

			}; // Result RelayPacketC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RelayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolMem(pMessageBase = new(memHeap) RelayPacketC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolChk(pMessageBase->ParseMsg());

			Proc_End:
				return hr;

			}; // Result RelayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RelayPacketC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const uint32_t &InSenderRelayID, const uint64_t &InTargetRelayMask, const Array<uint8_t>& InPayload )
			{
 				MessageData *pNewMsg = nullptr;
				Result hr;

				uint8_t *pMsgData = nullptr;

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ sizeof(uint32_t)
					+ sizeof(uint32_t)
					+ sizeof(uint64_t)
					+ sizeof(uint8_t)*InPayload.size() + sizeof(uint16_t));


				uint16_t numberOfInPayload = (uint16_t)InPayload.size(); 
				protocolMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::RelayPacketC2SEvt::MID, __uiMessageSize ) );

				pMsgData = pNewMsg->GetMessageData();

				Protocol::PackParamCopy( pMsgData, &InRelayInstanceID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InSenderRelayID, sizeof(uint32_t));
				Protocol::PackParamCopy( pMsgData, &InTargetRelayMask, sizeof(uint64_t));
				Protocol::PackParamCopy( pMsgData, &numberOfInPayload, sizeof(uint16_t)); 
				Protocol::PackParamCopy( pMsgData, InPayload.data(), (INT)(sizeof(uint8_t)*InPayload.size())); 


			Proc_End:

				if(!hr)
				{
 					if(pNewMsg != nullptr) delete pNewMsg;
					pNewMsg = nullptr;
				}
				return pNewMsg;

			}; // MessageData* RelayPacketC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const uint32_t &InSenderRelayID, const uint64_t &InTargetRelayMask, const Array<uint8_t>& InPayload )



			Result RelayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RelayPacketC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RelayPacket:{0}:{1} , RelayInstanceID:{2}, SenderRelayID:{3}, TargetRelayMask:{4}, Payload:{5,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRelayInstanceID(), parser.GetSenderRelayID(), parser.GetTargetRelayMask(), parser.GetPayload()); 
				return ResultCode::SUCCESS;
			}; // Result RelayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)



		}; // namespace Relay
	}; // namespace Message
}; // namespace SF



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
 				FunctionContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;

				protocolCheck(input->Read(m_RelayInstanceID));
				protocolCheck(input->Read(m_PlayerID));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlayerIdentifier, ArrayLen));

				return hr;

			}; // Result JoinRelayInstanceC2SEvt::ParseMessage( MessageData* pIMsg )

			Result JoinRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				JoinRelayInstanceC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerIdentifier", parser.GetPlayerIdentifier());

				return hr;

			}; // Result JoinRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinRelayInstanceC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinRelayInstanceC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					, SerializedSizeOf(InRelayInstanceID)
					, SerializedSizeOf(InPlayerID)
					, SerializedSizeOf(InPlayerIdentifier)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::JoinRelayInstanceC2SEvt::MID, __uiMessageSize ) );
				size_t MsgDataSize = (int)((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(output->Write(InRelayInstanceID));
				protocolCheck(output->Write(InPlayerID));
				protocolCheck(output->Write(InPlayerIdentifier));

				return hr;
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
 				FunctionContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;

				protocolCheck(input->Read(m_Result));
				protocolCheck(input->Read(m_RelayInstanceID));
				protocolCheck(input->Read(m_MyEndpointID));
				protocolCheck(input->Read(ArrayLen));
				RelayPlayerInfo* MemberInfosPtr = nullptr;
				protocolCheck(input->ReadLink(MemberInfosPtr, ArrayLen));
				m_MemberInfos.SetLinkedBuffer(ArrayLen, MemberInfosPtr);

				return hr;

			}; // Result JoinRelayInstanceResS2CEvt::ParseMessage( MessageData* pIMsg )

			Result JoinRelayInstanceResS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				JoinRelayInstanceResS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("MyEndpointID", parser.GetMyEndpointID());
				variableBuilder.SetVariable("MemberInfos", parser.GetMemberInfos());

				return hr;

			}; // Result JoinRelayInstanceResS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinRelayInstanceResS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinRelayInstanceResS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinRelayInstanceResS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinRelayInstanceResS2CEvt::Create( IHeap& memHeap, const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyEndpointID, const Array<RelayPlayerInfo>& InMemberInfos )
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

				uint16_t numberOfInMemberInfos = (uint16_t)InMemberInfos.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					, SerializedSizeOf(InResult)
					, SerializedSizeOf(InRelayInstanceID)
					, SerializedSizeOf(InMyEndpointID)
					, SerializedSizeOf(InMemberInfos)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::JoinRelayInstanceResS2CEvt::MID, __uiMessageSize ) );
				size_t MsgDataSize = (int)((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(output->Write(InResult));
				protocolCheck(output->Write(InRelayInstanceID));
				protocolCheck(output->Write(InMyEndpointID));
				protocolCheck(output->Write(InMemberInfos));

				return hr;
			}; // MessageData* JoinRelayInstanceResS2CEvt::Create( IHeap& memHeap, const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyEndpointID, const Array<RelayPlayerInfo>& InMemberInfos )



			Result JoinRelayInstanceResS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinRelayInstanceResS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinRelayInstanceRes:{0}:{1} , Result:{2:X8}, RelayInstanceID:{3}, MyEndpointID:{4}, MemberInfos:{5,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetResult(), parser.GetRelayInstanceID(), parser.GetMyEndpointID(), parser.GetMemberInfos()); 
				return ResultCode::SUCCESS;
			}; // Result JoinRelayInstanceResS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Event for Player Join request.
			const MessageID LeaveRelayInstanceC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_RELAY, 2);
			Result LeaveRelayInstanceC2SEvt::ParseMessage( MessageData* pIMsg )
			{
 				FunctionContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;

				protocolCheck(input->Read(m_RelayInstanceID));
				protocolCheck(input->Read(m_PlayerID));

				return hr;

			}; // Result LeaveRelayInstanceC2SEvt::ParseMessage( MessageData* pIMsg )

			Result LeaveRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				LeaveRelayInstanceC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result LeaveRelayInstanceC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result LeaveRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) LeaveRelayInstanceC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LeaveRelayInstanceC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* LeaveRelayInstanceC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					, SerializedSizeOf(InRelayInstanceID)
					, SerializedSizeOf(InPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::LeaveRelayInstanceC2SEvt::MID, __uiMessageSize ) );
				size_t MsgDataSize = (int)((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(output->Write(InRelayInstanceID));
				protocolCheck(output->Write(InPlayerID));

				return hr;
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
 				FunctionContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;

				protocolCheck(input->Read(m_RelayInstanceID));
				protocolCheck(input->Read(m_JoinedPlayerInfo));

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerJoinS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				PlayerJoinS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("JoinedPlayerInfo", parser.GetJoinedPlayerInfo());

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerJoinS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerJoinS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerJoinS2CEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					, SerializedSizeOf(InRelayInstanceID)
					, SerializedSizeOf(InJoinedPlayerInfo)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::PlayerJoinS2CEvt::MID, __uiMessageSize ) );
				size_t MsgDataSize = (int)((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(output->Write(InRelayInstanceID));
				protocolCheck(output->Write(InJoinedPlayerInfo));

				return hr;
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
 				FunctionContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;

				protocolCheck(input->Read(m_RelayInstanceID));
				protocolCheck(input->Read(m_LeftPlayerID));
				protocolCheck(input->Read(m_KickedReason));

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessage( MessageData* pIMsg )

			Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				PlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());
				variableBuilder.SetVariable("KickedReason", parser.GetKickedReason());

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					, SerializedSizeOf(InRelayInstanceID)
					, SerializedSizeOf(InLeftPlayerID)
					, SerializedSizeOf(InKickedReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::PlayerLeftS2CEvt::MID, __uiMessageSize ) );
				size_t MsgDataSize = (int)((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(output->Write(InRelayInstanceID));
				protocolCheck(output->Write(InLeftPlayerID));
				protocolCheck(output->Write(InKickedReason));

				return hr;
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
 				FunctionContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;

				protocolCheck(input->Read(m_RelayInstanceID));
				protocolCheck(input->Read(m_SenderEndpointID));
				protocolCheck(input->Read(m_TargetEndpointMask));
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PayloadPtr = nullptr;
				protocolCheck(input->ReadLink(PayloadPtr, ArrayLen));
				m_Payload.SetLinkedBuffer(ArrayLen, PayloadPtr);

				return hr;

			}; // Result RelayPacketC2SEvt::ParseMessage( MessageData* pIMsg )

			Result RelayPacketC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				FunctionContext hr;


				RelayPacketC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("RelayInstanceID", parser.GetRelayInstanceID());
				variableBuilder.SetVariable("SenderEndpointID", parser.GetSenderEndpointID());
				variableBuilder.SetVariable("TargetEndpointMask", parser.GetTargetEndpointMask());
				variableBuilder.SetVariable("Payload", parser.GetPayload());

				return hr;

			}; // Result RelayPacketC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RelayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				FunctionContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RelayPacketC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RelayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RelayPacketC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
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

				uint16_t numberOfInPayload = (uint16_t)InPayload.size(); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					, SerializedSizeOf(InRelayInstanceID)
					, SerializedSizeOf(InSenderEndpointID)
					, SerializedSizeOf(InTargetEndpointMask)
					, SerializedSizeOf(InPayload)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, Relay::RelayPacketC2SEvt::MID, __uiMessageSize ) );
				size_t MsgDataSize = (int)((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(output->Write(InRelayInstanceID));
				protocolCheck(output->Write(InSenderEndpointID));
				protocolCheck(output->Write(InTargetEndpointMask));
				protocolCheck(output->Write(InPayload));

				return hr;
			}; // MessageData* RelayPacketC2SEvt::Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )



			Result RelayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RelayPacketC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RelayPacket:{0}:{1} , RelayInstanceID:{2}, SenderEndpointID:{3}, TargetEndpointMask:{4}, Payload:{5,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetRelayInstanceID(), parser.GetSenderEndpointID(), parser.GetTargetEndpointMask(), parser.GetPayload()); 
				return ResultCode::SUCCESS;
			}; // Result RelayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)



		}; // namespace Relay
	}; // namespace Message
}; // namespace SF



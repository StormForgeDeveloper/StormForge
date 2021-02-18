////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : PlayInstance Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace PlayInstance
		{
 			// Cmd: Event for Player Join request.
			const MessageID JoinGameInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 0);
			Result JoinGameInstanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlayerIdentifier, ArrayLen));

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceID", parser.GetPlayInstanceID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerIdentifier", parser.GetPlayerIdentifier());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InPlayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerIdentifier)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::JoinGameInstanceCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerIdentifier);

				return hr;
			}; // MessageData* JoinGameInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint32_t &InPlayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )



			Result JoinGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameInstanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGameInstance:{0}:{1} , TransactionID:{2}, PlayInstanceID:{3}, PlayerID:{4}, PlayerIdentifier:{5,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayInstanceID(), parser.GetPlayerID(), parser.GetPlayerIdentifier()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinGameInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 0);
			Result JoinGameInstanceRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayInstanceID);
				protocolCheck(*input >> m_MyEndpointID);
				protocolCheck(input->Read(ArrayLen));
				PlayerInformation* MemberInfosPtr = nullptr;
				protocolCheck(input->ReadLink(MemberInfosPtr, ArrayLen));
				m_MemberInfos.SetLinkedBuffer(ArrayLen, MemberInfosPtr);

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result JoinGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinGameInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceID", parser.GetPlayInstanceID());
				variableBuilder.SetVariable("MyEndpointID", parser.GetMyEndpointID());
				variableBuilder.SetVariable("MemberInfos", parser.GetMemberInfos());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinGameInstanceRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinGameInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InPlayInstanceID, const uint32_t &InMyEndpointID, const Array<PlayerInformation>& InMemberInfos )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceID)
					+ SerializedSizeOf(InMyEndpointID)
					+ SerializedSizeOf(InMemberInfos)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::JoinGameInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceID);
				protocolCheck(*output << InMyEndpointID);
				protocolCheck(*output << InMemberInfos);

				return hr;
			}; // MessageData* JoinGameInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InPlayInstanceID, const uint32_t &InMyEndpointID, const Array<PlayerInformation>& InMemberInfos )



			Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinGameInstanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinGameInstance:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceID:{4}, MyEndpointID:{5}, MemberInfos:{6,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceID(), parser.GetMyEndpointID(), parser.GetMemberInfos()); 
				return ResultCode::SUCCESS;
			}; // Result JoinGameInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Event for Player joined.
			const MessageID PlayerJoinS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 1);
			Result PlayerJoinS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceID);
				protocolCheck(*input >> m_JoinedPlayerInfo);

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerJoinS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerJoinS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceID", parser.GetPlayInstanceID());
				variableBuilder.SetVariable("JoinedPlayerInfo", parser.GetJoinedPlayerInfo());

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerJoinS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerJoinS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerJoinS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerJoinS2CEvt::Create( IHeap& memHeap, const uint32_t &InPlayInstanceID, const PlayerInformation &InJoinedPlayerInfo )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceID)
					+ SerializedSizeOf(InJoinedPlayerInfo)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerJoinS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceID);
				protocolCheck(*output << InJoinedPlayerInfo);

				return hr;
			}; // MessageData* PlayerJoinS2CEvt::Create( IHeap& memHeap, const uint32_t &InPlayInstanceID, const PlayerInformation &InJoinedPlayerInfo )



			Result PlayerJoinS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerJoinS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerJoin:{0}:{1} , PlayInstanceID:{2}, JoinedPlayerInfo:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceID(), parser.GetJoinedPlayerInfo()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerJoinS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Event for Player left.
			const MessageID PlayerLeftS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 2);
			Result PlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceID);
				protocolCheck(*input >> m_LeftPlayerID);
				protocolCheck(*input >> m_KickedReason);

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerLeftS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceID", parser.GetPlayInstanceID());
				variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());
				variableBuilder.SetVariable("KickedReason", parser.GetKickedReason());

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerLeftS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerLeftS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint32_t &InPlayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceID)
					+ SerializedSizeOf(InLeftPlayerID)
					+ SerializedSizeOf(InKickedReason)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerLeftS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceID);
				protocolCheck(*output << InLeftPlayerID);
				protocolCheck(*output << InKickedReason);

				return hr;
			}; // MessageData* PlayerLeftS2CEvt::Create( IHeap& memHeap, const uint32_t &InPlayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )



			Result PlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerLeftS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerLeft:{0}:{1} , PlayInstanceID:{2}, LeftPlayerID:{3}, KickedReason:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceID(), parser.GetLeftPlayerID(), parser.GetKickedReason()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerLeftS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Play packet
			const MessageID PlayPacketC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 3);
			Result PlayPacketC2SEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceID);
				protocolCheck(*input >> m_SenderEndpointID);
				protocolCheck(*input >> m_TargetEndpointMask);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PayloadPtr = nullptr;
				protocolCheck(input->ReadLink(PayloadPtr, ArrayLen));
				m_Payload.SetLinkedBuffer(ArrayLen, PayloadPtr);

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayPacketC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayPacketC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceID", parser.GetPlayInstanceID());
				variableBuilder.SetVariable("SenderEndpointID", parser.GetSenderEndpointID());
				variableBuilder.SetVariable("TargetEndpointMask", parser.GetTargetEndpointMask());
				variableBuilder.SetVariable("Payload", parser.GetPayload());

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayPacketC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayPacketC2SEvt::Create( IHeap& memHeap, const uint32_t &InPlayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceID)
					+ SerializedSizeOf(InSenderEndpointID)
					+ SerializedSizeOf(InTargetEndpointMask)
					+ SerializedSizeOf(InPayload)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayPacketC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceID);
				protocolCheck(*output << InSenderEndpointID);
				protocolCheck(*output << InTargetEndpointMask);
				protocolCheck(*output << InPayload);

				return hr;
			}; // MessageData* PlayPacketC2SEvt::Create( IHeap& memHeap, const uint32_t &InPlayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )



			Result PlayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayPacketC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayPacket:{0}:{1} , PlayInstanceID:{2}, SenderEndpointID:{3}, TargetEndpointMask:{4}, Payload:{5,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceID(), parser.GetSenderEndpointID(), parser.GetTargetEndpointMask(), parser.GetPayload()); 
				return ResultCode::SUCCESS;
			}; // Result PlayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: New Player in get view
			const MessageID NewPlayerInViewS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 4);
			const VariableTable& NewPlayerInViewS2CEvt::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& NewPlayerInViewS2CEvt::GetAttributes() const
			Result NewPlayerInViewS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result NewPlayerInViewS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result NewPlayerInViewS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				NewPlayerInViewS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result NewPlayerInViewS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NewPlayerInViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NewPlayerInViewS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NewPlayerInViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* NewPlayerInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::NewPlayerInViewS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* NewPlayerInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )

			MessageData* NewPlayerInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::NewPlayerInViewS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* NewPlayerInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )



			Result NewPlayerInViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				NewPlayerInViewS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "NewPlayerInView:{0}:{1} , GameInsUID:{2}, PlayerID:{3}, Attributes:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result NewPlayerInViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Remove player from view
			const MessageID RemovePlayerFromViewS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 5);
			const VariableTable& RemovePlayerFromViewS2CEvt::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& RemovePlayerFromViewS2CEvt::GetAttributes() const
			Result RemovePlayerFromViewS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result RemovePlayerFromViewS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result RemovePlayerFromViewS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemovePlayerFromViewS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result RemovePlayerFromViewS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemovePlayerFromViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemovePlayerFromViewS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemovePlayerFromViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* RemovePlayerFromViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::RemovePlayerFromViewS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* RemovePlayerFromViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )

			MessageData* RemovePlayerFromViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::RemovePlayerFromViewS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* RemovePlayerFromViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )



			Result RemovePlayerFromViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RemovePlayerFromViewS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RemovePlayerFromView:{0}:{1} , GameInsUID:{2}, PlayerID:{3}, Attributes:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result RemovePlayerFromViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Player Movement
			const MessageID PlayerMovementC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 6);
			const VariableTable& PlayerMovementC2SEvt::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& PlayerMovementC2SEvt::GetAttributes() const
			Result PlayerMovementC2SEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerMovementC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerMovementC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerMovementC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerMovementC2SEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerMovementC2SEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerMovementC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* PlayerMovementC2SEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )

			MessageData* PlayerMovementC2SEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerMovementC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* PlayerMovementC2SEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )



			Result PlayerMovementC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerMovementC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerMovement:{0}:{1} , GameInsUID:{2}, PlayerID:{3}, Attributes:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerMovementC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Movement
			const MessageID PlayerMovementS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 7);
			const VariableTable& PlayerMovementS2CEvt::GetAttributes() const
			{
 				if (!m_AttributesHasParsed)
				{
 					m_AttributesHasParsed = true;
					InputMemoryStream Attributes_ReadStream(m_AttributesRaw);
					*Attributes_ReadStream.ToInputStream() >> m_Attributes;
				} // if (!m_AttributesHasParsed)
				return m_Attributes;
			} // const VariableTable& PlayerMovementS2CEvt::GetAttributes() const
			Result PlayerMovementS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_GameInsUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_AttributesRaw.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result PlayerMovementS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerMovementS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerMovementS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Attributes", "VariableTable", parser.GetAttributesRaw());

				return hr;

			}; // Result PlayerMovementS2CEvt::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerMovementS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerMovementS2CEvt(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerMovementS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerMovementS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerMovementS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* PlayerMovementS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes )

			MessageData* PlayerMovementS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InGameInsUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerMovementS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InGameInsUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInAttributes));
				protocolCheck(*output << InAttributes);

				return hr;
			}; // MessageData* PlayerMovementS2CEvt::Create( IHeap& memHeap, const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )



			Result PlayerMovementS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerMovementS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerMovement:{0}:{1} , GameInsUID:{2}, PlayerID:{3}, Attributes:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetGameInsUID(), parser.GetPlayerID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerMovementS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Create stream instance
			const MessageID CreateStreamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 8);
			Result CreateStreamCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result CreateStreamCmd::ParseMessage(const MessageData* pIMsg)

			Result CreateStreamCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateStreamCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result CreateStreamCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateStreamCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateStreamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::CreateStreamCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // MessageData* CreateStreamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )



			Result CreateStreamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateStreamCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateStream:{0}:{1} , TransactionID:{2}, Ticket:{3}, StreamName:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTicket(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result CreateStreamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CreateStreamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 8);
			Result CreateStreamRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_StreamServerAddr);
				protocolCheck(*input >> m_StreamServerAddrIPV4);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamUID, ArrayLen));

				return hr;

			}; // Result CreateStreamRes::ParseMessage(const MessageData* pIMsg)

			Result CreateStreamRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateStreamRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamServerAddr", parser.GetStreamServerAddr());
				variableBuilder.SetVariable("StreamServerAddrIPV4", parser.GetStreamServerAddrIPV4());
				variableBuilder.SetVariable("StreamUID", parser.GetStreamUID());

				return hr;

			}; // Result CreateStreamRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateStreamRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateStreamRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateStreamRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamServerAddr)
					+ SerializedSizeOf(InStreamServerAddrIPV4)
					+ SerializedSizeOf(InStreamUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::CreateStreamRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamServerAddr);
				protocolCheck(*output << InStreamServerAddrIPV4);
				protocolCheck(*output << InStreamUID);

				return hr;
			}; // MessageData* CreateStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )



			Result CreateStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateStreamRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateStream:{0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamServerAddr:{4}, StreamServerAddrIPV4:{5}, StreamUID:{6,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamServerAddr(), parser.GetStreamServerAddrIPV4(), parser.GetStreamUID()); 
				return ResultCode::SUCCESS;
			}; // Result CreateStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Open stream instance
			const MessageID FindStreamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 9);
			Result FindStreamCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result FindStreamCmd::ParseMessage(const MessageData* pIMsg)

			Result FindStreamCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindStreamCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result FindStreamCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindStreamCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FindStreamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::FindStreamCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // MessageData* FindStreamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )



			Result FindStreamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FindStreamCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FindStream:{0}:{1} , TransactionID:{2}, Ticket:{3}, StreamName:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTicket(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result FindStreamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID FindStreamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 9);
			Result FindStreamRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_StreamServerAddr);
				protocolCheck(*input >> m_StreamServerAddrIPV4);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamUID, ArrayLen));

				return hr;

			}; // Result FindStreamRes::ParseMessage(const MessageData* pIMsg)

			Result FindStreamRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindStreamRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamServerAddr", parser.GetStreamServerAddr());
				variableBuilder.SetVariable("StreamServerAddrIPV4", parser.GetStreamServerAddrIPV4());
				variableBuilder.SetVariable("StreamUID", parser.GetStreamUID());

				return hr;

			}; // Result FindStreamRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindStreamRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindStreamRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindStreamRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* FindStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamServerAddr)
					+ SerializedSizeOf(InStreamServerAddrIPV4)
					+ SerializedSizeOf(InStreamUID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::FindStreamRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamServerAddr);
				protocolCheck(*output << InStreamServerAddrIPV4);
				protocolCheck(*output << InStreamUID);

				return hr;
			}; // MessageData* FindStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )



			Result FindStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FindStreamRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FindStream:{0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamServerAddr:{4}, StreamServerAddrIPV4:{5}, StreamUID:{6,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamServerAddr(), parser.GetStreamServerAddrIPV4(), parser.GetStreamUID()); 
				return ResultCode::SUCCESS;
			}; // Result FindStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Delete stream instance
			const MessageID DeleteStreamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 10);
			Result DeleteStreamCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result DeleteStreamCmd::ParseMessage(const MessageData* pIMsg)

			Result DeleteStreamCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteStreamCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result DeleteStreamCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteStreamCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* DeleteStreamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::DeleteStreamCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // MessageData* DeleteStreamCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )



			Result DeleteStreamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DeleteStreamCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DeleteStream:{0}:{1} , TransactionID:{2}, Ticket:{3}, StreamName:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTicket(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteStreamCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID DeleteStreamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 10);
			Result DeleteStreamRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result DeleteStreamRes::ParseMessage(const MessageData* pIMsg)

			Result DeleteStreamRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteStreamRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result DeleteStreamRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteStreamRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteStreamRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteStreamRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* DeleteStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::DeleteStreamRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* DeleteStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )



			Result DeleteStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DeleteStreamRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DeleteStream:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Get stream list
			const MessageID GetStreamListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 11);
			Result GetStreamListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);

				return hr;

			}; // Result GetStreamListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetStreamListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetStreamListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());

				return hr;

			}; // Result GetStreamListCmd::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetStreamListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetStreamListCmd(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetStreamListCmd::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetStreamListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::GetStreamListCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);

				return hr;
			}; // MessageData* GetStreamListCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const AuthTicket &InTicket )



			Result GetStreamListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetStreamListCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetStreamList:{0}:{1} , TransactionID:{2}, Ticket:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result GetStreamListCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID GetStreamListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 11);
			Result GetStreamListRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->ReadArrayLink(m_StreamNames));

				return hr;

			}; // Result GetStreamListRes::ParseMessage(const MessageData* pIMsg)

			Result GetStreamListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetStreamListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamNames", parser.GetStreamNames());

				return hr;

			}; // Result GetStreamListRes::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetStreamListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetStreamListRes(std::forward<MessageDataPtr>(pIMsg)));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetStreamListRes::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMessageBase )


			MessageData* GetStreamListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
			{
 				MessageData *pNewMsg = nullptr;
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

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamNames)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::GetStreamListRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamNames);

				return hr;
			}; // MessageData* GetStreamListRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )



			Result GetStreamListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				GetStreamListRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "GetStreamList:{0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamNames:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamNames()); 
				return ResultCode::SUCCESS;
			}; // Result GetStreamListRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)



		}; // namespace PlayInstance
	}; // namespace Message
}; // namespace SF



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
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
#include "Protocol/PlayInstanceMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace PlayInstance
		{
 			// Cmd: Player Join request.
			const MessageID JoinPlayInstanceCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 0);
			Result JoinPlayInstanceCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlayerIdentifier, ArrayLen));

				return hr;

			}; // Result JoinPlayInstanceCmd::ParseMessage(const MessageData* pIMsg)

			Result JoinPlayInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinPlayInstanceCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerIdentifier", parser.GetPlayerIdentifier());

				return hr;

			}; // Result JoinPlayInstanceCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPlayInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPlayInstanceCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPlayInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* JoinPlayInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerIdentifier)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::JoinPlayInstanceCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerIdentifier);

				return hr;
			}; // MessageData* JoinPlayInstanceCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )

			Result JoinPlayInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinPlayInstanceCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinPlayInstance:{0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, PlayerIdentifier:{5,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetPlayerIdentifier()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPlayInstanceCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID JoinPlayInstanceRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 0);
			const VariableTable& JoinPlayInstanceRes::GetCharacterPrivateData() const
			{
 				if (!m_CharacterPrivateDataHasParsed)
				{
 					m_CharacterPrivateDataHasParsed = true;
					InputMemoryStream CharacterPrivateData_ReadStream(m_CharacterPrivateDataRaw);
					*CharacterPrivateData_ReadStream.ToInputStream() >> m_CharacterPrivateData;
				} // if (!m_CharacterPrivateDataHasParsed)
				return m_CharacterPrivateData;
			} // const VariableTable& JoinPlayInstanceRes::GetCharacterPrivateData() const
			Result JoinPlayInstanceRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_CharacterID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* CharacterPrivateDataPtr = nullptr;
				protocolCheck(input->ReadLink(CharacterPrivateDataPtr, ArrayLen));
				m_CharacterPrivateDataRaw.SetLinkedBuffer(ArrayLen, CharacterPrivateDataPtr);
				protocolCheck(*input >> m_Movement);

				return hr;

			}; // Result JoinPlayInstanceRes::ParseMessage(const MessageData* pIMsg)

			Result JoinPlayInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				JoinPlayInstanceRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());
				variableBuilder.SetVariableArray("CharacterPrivateData", "VariableTable", parser.GetCharacterPrivateDataRaw());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result JoinPlayInstanceRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result JoinPlayInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPlayInstanceRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPlayInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* JoinPlayInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInCharacterPrivateData = static_cast<uint16_t>(SerializedSizeOf(InCharacterPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ serializedSizeOfInCharacterPrivateData
					+ SerializedSizeOf(InMovement)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::JoinPlayInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCharacterID);
				protocolCheck(*output << InCharacterPrivateData);
				protocolCheck(*output << InMovement);

				return hr;
			}; // MessageData* JoinPlayInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement )

			MessageData* JoinPlayInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInCharacterPrivateData = static_cast<uint16_t>(SerializedSizeOf(InCharacterPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInCharacterPrivateData
					+ SerializedSizeOf(InMovement)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::JoinPlayInstanceRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCharacterID);
				protocolCheck(output->Write(serializedSizeOfInCharacterPrivateData));
				protocolCheck(*output << InCharacterPrivateData);
				protocolCheck(*output << InMovement);

				return hr;
			}; // MessageData* JoinPlayInstanceRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )

			Result JoinPlayInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				JoinPlayInstanceRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "JoinPlayInstance:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, CharacterID:{6}, CharacterPrivateData:{7}, Movement:{8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetCharacterID(), parser.GetCharacterPrivateData(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPlayInstanceRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			const MessageID PlayerKickedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 1);
			Result PlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerKickedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerKickedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerKickedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InKickedPlayerID);

				return hr;
			}; // MessageData* PlayerKickedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )

			Result PlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerKickedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerKicked:{0}:{1} , PlayInstanceUID:{2}, KickedPlayerID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetKickedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Play packet
			const MessageID PlayPacketC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 2);
			Result PlayPacketC2SEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_SenderEndpointID);
				protocolCheck(*input >> m_TargetEndpointMask);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PayloadPtr = nullptr;
				protocolCheck(input->ReadLink(PayloadPtr, ArrayLen));
				m_Payload.SetLinkedBuffer(ArrayLen, PayloadPtr);

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayPacketC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayPacketC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("SenderEndpointID", parser.GetSenderEndpointID());
				variableBuilder.SetVariable("TargetEndpointMask", parser.GetTargetEndpointMask());
				variableBuilder.SetVariable("Payload", parser.GetPayload());

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayPacketC2SEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayPacketC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderEndpointID)
					+ SerializedSizeOf(InTargetEndpointMask)
					+ SerializedSizeOf(InPayload)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayPacketC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InSenderEndpointID);
				protocolCheck(*output << InTargetEndpointMask);
				protocolCheck(*output << InPayload);

				return hr;
			}; // MessageData* PlayPacketC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )

			Result PlayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayPacketC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayPacket:{0}:{1} , PlayInstanceUID:{2}, SenderEndpointID:{3}, TargetEndpointMask:{4}, Payload:{5,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetSenderEndpointID(), parser.GetTargetEndpointMask(), parser.GetPayload()); 
				return ResultCode::SUCCESS;
			}; // Result PlayPacketC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: New actor in get view
			const MessageID NewActorInViewS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 3);
			const VariableTable& NewActorInViewS2CEvt::GetPublicData() const
			{
 				if (!m_PublicDataHasParsed)
				{
 					m_PublicDataHasParsed = true;
					InputMemoryStream PublicData_ReadStream(m_PublicDataRaw);
					*PublicData_ReadStream.ToInputStream() >> m_PublicData;
				} // if (!m_PublicDataHasParsed)
				return m_PublicData;
			} // const VariableTable& NewActorInViewS2CEvt::GetPublicData() const
			const VariableTable& NewActorInViewS2CEvt::GetEquipData() const
			{
 				if (!m_EquipDataHasParsed)
				{
 					m_EquipDataHasParsed = true;
					InputMemoryStream EquipData_ReadStream(m_EquipDataRaw);
					*EquipData_ReadStream.ToInputStream() >> m_EquipData;
				} // if (!m_EquipDataHasParsed)
				return m_EquipData;
			} // const VariableTable& NewActorInViewS2CEvt::GetEquipData() const
			const VariableTable& NewActorInViewS2CEvt::GetStateValues() const
			{
 				if (!m_StateValuesHasParsed)
				{
 					m_StateValuesHasParsed = true;
					InputMemoryStream StateValues_ReadStream(m_StateValuesRaw);
					*StateValues_ReadStream.ToInputStream() >> m_StateValues;
				} // if (!m_StateValuesHasParsed)
				return m_StateValues;
			} // const VariableTable& NewActorInViewS2CEvt::GetStateValues() const
			Result NewActorInViewS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_PlayerPlatformId);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PublicDataPtr = nullptr;
				protocolCheck(input->ReadLink(PublicDataPtr, ArrayLen));
				m_PublicDataRaw.SetLinkedBuffer(ArrayLen, PublicDataPtr);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* EquipDataPtr = nullptr;
				protocolCheck(input->ReadLink(EquipDataPtr, ArrayLen));
				m_EquipDataRaw.SetLinkedBuffer(ArrayLen, EquipDataPtr);
				protocolCheck(*input >> m_Movement);
				protocolCheck(*input >> m_State);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* StateValuesPtr = nullptr;
				protocolCheck(input->ReadLink(StateValuesPtr, ArrayLen));
				m_StateValuesRaw.SetLinkedBuffer(ArrayLen, StateValuesPtr);

				return hr;

			}; // Result NewActorInViewS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result NewActorInViewS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				NewActorInViewS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerPlatformId", "PlayerPlatformID", parser.GetPlayerPlatformId());
				variableBuilder.SetVariableArray("PublicData", "VariableTable", parser.GetPublicDataRaw());
				variableBuilder.SetVariableArray("EquipData", "VariableTable", parser.GetEquipDataRaw());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());
				variableBuilder.SetVariable("State", parser.GetState());
				variableBuilder.SetVariableArray("StateValues", "VariableTable", parser.GetStateValuesRaw());

				return hr;

			}; // Result NewActorInViewS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result NewActorInViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) NewActorInViewS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NewActorInViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* NewActorInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues )
			{
 				MessageData *pNewMsg = nullptr;
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
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerPlatformId)
					+ serializedSizeOfInPublicData
					+ serializedSizeOfInEquipData
					+ SerializedSizeOf(InMovement)
					+ SerializedSizeOf(InState)
					+ serializedSizeOfInStateValues
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::NewActorInViewS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerPlatformId);
				protocolCheck(*output << InPublicData);
				protocolCheck(*output << InEquipData);
				protocolCheck(*output << InMovement);
				protocolCheck(*output << InState);
				protocolCheck(*output << InStateValues);

				return hr;
			}; // MessageData* NewActorInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues )

			MessageData* NewActorInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
			{
 				MessageData *pNewMsg = nullptr;
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
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerPlatformId)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPublicData
					+ sizeof(uint16_t)
					+ serializedSizeOfInEquipData
					+ SerializedSizeOf(InMovement)
					+ SerializedSizeOf(InState)
					+ sizeof(uint16_t)
					+ serializedSizeOfInStateValues
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::NewActorInViewS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerPlatformId);
				protocolCheck(output->Write(serializedSizeOfInPublicData));
				protocolCheck(*output << InPublicData);
				protocolCheck(output->Write(serializedSizeOfInEquipData));
				protocolCheck(*output << InEquipData);
				protocolCheck(*output << InMovement);
				protocolCheck(*output << InState);
				protocolCheck(output->Write(serializedSizeOfInStateValues));
				protocolCheck(*output << InStateValues);

				return hr;
			}; // MessageData* NewActorInViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )

			Result NewActorInViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				NewActorInViewS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "NewActorInView:{0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, PlayerPlatformId:{4}, PublicData:{5}, EquipData:{6}, Movement:{7}, State:{8}, StateValues:{9}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetPlayerPlatformId(), parser.GetPublicData(), parser.GetEquipData(), parser.GetMovement(), parser.GetState(), parser.GetStateValues()); 
				return ResultCode::SUCCESS;
			}; // Result NewActorInViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Remove actor from view
			const MessageID RemoveActorFromViewS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 4);
			Result RemoveActorFromViewS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_ActorID);

				return hr;

			}; // Result RemoveActorFromViewS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result RemoveActorFromViewS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				RemoveActorFromViewS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("ActorID", parser.GetActorID());

				return hr;

			}; // Result RemoveActorFromViewS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result RemoveActorFromViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveActorFromViewS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveActorFromViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* RemoveActorFromViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InActorID)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::RemoveActorFromViewS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InActorID);

				return hr;
			}; // MessageData* RemoveActorFromViewS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )

			Result RemoveActorFromViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				RemoveActorFromViewS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "RemoveActorFromView:{0}:{1} , PlayInstanceUID:{2}, ActorID:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetActorID()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveActorFromViewS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Player Movement
			const MessageID PlayerMovementC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 5);
			Result PlayerMovementC2SEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Movement);

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerMovementC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerMovementC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerMovementC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerMovementC2SEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* PlayerMovementC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMovement)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerMovementC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMovement);

				return hr;
			}; // MessageData* PlayerMovementC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )

			Result PlayerMovementC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerMovementC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug3, "PlayerMovement:{0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, Movement:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerMovementC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Movement
			const MessageID ActorMovementS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 6);
			Result ActorMovementS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_Movement);

				return hr;

			}; // Result ActorMovementS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ActorMovementS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ActorMovementS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result ActorMovementS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ActorMovementS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ActorMovementS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ActorMovementS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* ActorMovementS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InMovement)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ActorMovementS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InMovement);

				return hr;
			}; // MessageData* ActorMovementS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )

			Result ActorMovementS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ActorMovementS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug4, "ActorMovement:{0}:{1} , PlayInstanceUID:{2}, Movement:{3}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result ActorMovementS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player Movement
			const MessageID ActorMovementsS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 7);
			Result ActorMovementsS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(input->Read(ArrayLen));
				ActorMovement* MovementPtr = nullptr;
				protocolCheck(input->ReadLink(MovementPtr, ArrayLen));
				m_Movement.SetLinkedBuffer(ArrayLen, MovementPtr);

				return hr;

			}; // Result ActorMovementsS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ActorMovementsS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ActorMovementsS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariableArray("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result ActorMovementsS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ActorMovementsS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ActorMovementsS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ActorMovementsS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* ActorMovementsS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InMovement)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ActorMovementsS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InMovement);

				return hr;
			}; // MessageData* ActorMovementsS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )

			Result ActorMovementsS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ActorMovementsS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug4, "ActorMovements:{0}:{1} , PlayInstanceUID:{2}, Movement:{3,30}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result ActorMovementsS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player state change
			const MessageID PlayerStateChangedS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 8);
			const VariableTable& PlayerStateChangedS2CEvt::GetStateValues() const
			{
 				if (!m_StateValuesHasParsed)
				{
 					m_StateValuesHasParsed = true;
					InputMemoryStream StateValues_ReadStream(m_StateValuesRaw);
					*StateValues_ReadStream.ToInputStream() >> m_StateValues;
				} // if (!m_StateValuesHasParsed)
				return m_StateValues;
			} // const VariableTable& PlayerStateChangedS2CEvt::GetStateValues() const
			Result PlayerStateChangedS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_State);
				protocolCheck(*input >> m_MoveFrame);
				protocolCheck(*input >> m_Position);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* StateValuesPtr = nullptr;
				protocolCheck(input->ReadLink(StateValuesPtr, ArrayLen));
				m_StateValuesRaw.SetLinkedBuffer(ArrayLen, StateValuesPtr);

				return hr;

			}; // Result PlayerStateChangedS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result PlayerStateChangedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				PlayerStateChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("State", parser.GetState());
				variableBuilder.SetVariable("MoveFrame", parser.GetMoveFrame());
				variableBuilder.SetVariable("Position", "Vector4", parser.GetPosition());
				variableBuilder.SetVariableArray("StateValues", "VariableTable", parser.GetStateValuesRaw());

				return hr;

			}; // Result PlayerStateChangedS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result PlayerStateChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerStateChangedS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerStateChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* PlayerStateChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InState)
					+ SerializedSizeOf(InMoveFrame)
					+ SerializedSizeOf(InPosition)
					+ serializedSizeOfInStateValues
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerStateChangedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InState);
				protocolCheck(*output << InMoveFrame);
				protocolCheck(*output << InPosition);
				protocolCheck(*output << InStateValues);

				return hr;
			}; // MessageData* PlayerStateChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues )

			MessageData* PlayerStateChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InState)
					+ SerializedSizeOf(InMoveFrame)
					+ SerializedSizeOf(InPosition)
					+ sizeof(uint16_t)
					+ serializedSizeOfInStateValues
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::PlayerStateChangedS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InState);
				protocolCheck(*output << InMoveFrame);
				protocolCheck(*output << InPosition);
				protocolCheck(output->Write(serializedSizeOfInStateValues));
				protocolCheck(*output << InStateValues);

				return hr;
			}; // MessageData* PlayerStateChangedS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )

			Result PlayerStateChangedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				PlayerStateChangedS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "PlayerStateChanged:{0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, State:{4}, MoveFrame:{5}, Position:{6}, StateValues:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetState(), parser.GetMoveFrame(), parser.GetPosition(), parser.GetStateValues()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerStateChangedS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			const MessageID ClientSyncReliableC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 9);
			const VariableTable& ClientSyncReliableC2SEvt::GetSyncData() const
			{
 				if (!m_SyncDataHasParsed)
				{
 					m_SyncDataHasParsed = true;
					InputMemoryStream SyncData_ReadStream(m_SyncDataRaw);
					*SyncData_ReadStream.ToInputStream() >> m_SyncData;
				} // if (!m_SyncDataHasParsed)
				return m_SyncData;
			} // const VariableTable& ClientSyncReliableC2SEvt::GetSyncData() const
			Result ClientSyncReliableC2SEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* SyncDataPtr = nullptr;
				protocolCheck(input->ReadLink(SyncDataPtr, ArrayLen));
				m_SyncDataRaw.SetLinkedBuffer(ArrayLen, SyncDataPtr);

				return hr;

			}; // Result ClientSyncReliableC2SEvt::ParseMessage(const MessageData* pIMsg)

			Result ClientSyncReliableC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ClientSyncReliableC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("SyncData", "VariableTable", parser.GetSyncDataRaw());

				return hr;

			}; // Result ClientSyncReliableC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ClientSyncReliableC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ClientSyncReliableC2SEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ClientSyncReliableC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* ClientSyncReliableC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInSyncData
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ClientSyncReliableC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InSyncData);

				return hr;
			}; // MessageData* ClientSyncReliableC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )

			MessageData* ClientSyncReliableC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInSyncData
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ClientSyncReliableC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInSyncData));
				protocolCheck(*output << InSyncData);

				return hr;
			}; // MessageData* ClientSyncReliableC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )

			Result ClientSyncReliableC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ClientSyncReliableC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ClientSyncReliable:{0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, SyncData:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetSyncData()); 
				return ResultCode::SUCCESS;
			}; // Result ClientSyncReliableC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			const MessageID ClientSyncC2SEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 10);
			const VariableTable& ClientSyncC2SEvt::GetSyncData() const
			{
 				if (!m_SyncDataHasParsed)
				{
 					m_SyncDataHasParsed = true;
					InputMemoryStream SyncData_ReadStream(m_SyncDataRaw);
					*SyncData_ReadStream.ToInputStream() >> m_SyncData;
				} // if (!m_SyncDataHasParsed)
				return m_SyncData;
			} // const VariableTable& ClientSyncC2SEvt::GetSyncData() const
			Result ClientSyncC2SEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* SyncDataPtr = nullptr;
				protocolCheck(input->ReadLink(SyncDataPtr, ArrayLen));
				m_SyncDataRaw.SetLinkedBuffer(ArrayLen, SyncDataPtr);

				return hr;

			}; // Result ClientSyncC2SEvt::ParseMessage(const MessageData* pIMsg)

			Result ClientSyncC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ClientSyncC2SEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("SyncData", "VariableTable", parser.GetSyncDataRaw());

				return hr;

			}; // Result ClientSyncC2SEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ClientSyncC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ClientSyncC2SEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ClientSyncC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* ClientSyncC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInSyncData
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ClientSyncC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InSyncData);

				return hr;
			}; // MessageData* ClientSyncC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )

			MessageData* ClientSyncC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInSyncData
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ClientSyncC2SEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInSyncData));
				protocolCheck(*output << InSyncData);

				return hr;
			}; // MessageData* ClientSyncC2SEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )

			Result ClientSyncC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ClientSyncC2SEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ClientSync:{0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, SyncData:{4}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetSyncData()); 
				return ResultCode::SUCCESS;
			}; // Result ClientSyncC2SEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Occupy map object
			const MessageID OccupyMapObjectCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 11);
			Result OccupyMapObjectCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);
				protocolCheck(*input >> m_UsageId);

				return hr;

			}; // Result OccupyMapObjectCmd::ParseMessage(const MessageData* pIMsg)

			Result OccupyMapObjectCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				OccupyMapObjectCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());
				variableBuilder.SetVariable("UsageId", parser.GetUsageId());

				return hr;

			}; // Result OccupyMapObjectCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result OccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) OccupyMapObjectCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result OccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* OccupyMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ SerializedSizeOf(InUsageId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::OccupyMapObjectCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(*output << InUsageId);

				return hr;
			}; // MessageData* OccupyMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )

			Result OccupyMapObjectCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				OccupyMapObjectCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "OccupyMapObject:{0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MapObjectId:{5}, UsageId:{6}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId(), parser.GetUsageId()); 
				return ResultCode::SUCCESS;
			}; // Result OccupyMapObjectCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID OccupyMapObjectRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 11);
			Result OccupyMapObjectRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);

				return hr;

			}; // Result OccupyMapObjectRes::ParseMessage(const MessageData* pIMsg)

			Result OccupyMapObjectRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				OccupyMapObjectRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());

				return hr;

			}; // Result OccupyMapObjectRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result OccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) OccupyMapObjectRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result OccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* OccupyMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::OccupyMapObjectRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);

				return hr;
			}; // MessageData* OccupyMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )

			Result OccupyMapObjectRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				OccupyMapObjectRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "OccupyMapObject:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, MapObjectId:{6}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId()); 
				return ResultCode::SUCCESS;
			}; // Result OccupyMapObjectRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Unoccupy map object
			const MessageID UnoccupyMapObjectCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 12);
			Result UnoccupyMapObjectCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);

				return hr;

			}; // Result UnoccupyMapObjectCmd::ParseMessage(const MessageData* pIMsg)

			Result UnoccupyMapObjectCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnoccupyMapObjectCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());

				return hr;

			}; // Result UnoccupyMapObjectCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnoccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnoccupyMapObjectCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnoccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* UnoccupyMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::UnoccupyMapObjectCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);

				return hr;
			}; // MessageData* UnoccupyMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )

			Result UnoccupyMapObjectCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UnoccupyMapObjectCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UnoccupyMapObject:{0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MapObjectId:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId()); 
				return ResultCode::SUCCESS;
			}; // Result UnoccupyMapObjectCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID UnoccupyMapObjectRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 12);
			Result UnoccupyMapObjectRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);

				return hr;

			}; // Result UnoccupyMapObjectRes::ParseMessage(const MessageData* pIMsg)

			Result UnoccupyMapObjectRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UnoccupyMapObjectRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());

				return hr;

			}; // Result UnoccupyMapObjectRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UnoccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnoccupyMapObjectRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnoccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* UnoccupyMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::UnoccupyMapObjectRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);

				return hr;
			}; // MessageData* UnoccupyMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )

			Result UnoccupyMapObjectRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UnoccupyMapObjectRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UnoccupyMapObject:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, MapObjectId:{6}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId()); 
				return ResultCode::SUCCESS;
			}; // Result UnoccupyMapObjectRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Use map object
			const MessageID UseMapObjectCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 13);
			const VariableTable& UseMapObjectCmd::GetUseParameters() const
			{
 				if (!m_UseParametersHasParsed)
				{
 					m_UseParametersHasParsed = true;
					InputMemoryStream UseParameters_ReadStream(m_UseParametersRaw);
					*UseParameters_ReadStream.ToInputStream() >> m_UseParameters;
				} // if (!m_UseParametersHasParsed)
				return m_UseParameters;
			} // const VariableTable& UseMapObjectCmd::GetUseParameters() const
			Result UseMapObjectCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* UseParametersPtr = nullptr;
				protocolCheck(input->ReadLink(UseParametersPtr, ArrayLen));
				m_UseParametersRaw.SetLinkedBuffer(ArrayLen, UseParametersPtr);

				return hr;

			}; // Result UseMapObjectCmd::ParseMessage(const MessageData* pIMsg)

			Result UseMapObjectCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UseMapObjectCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());
				variableBuilder.SetVariableArray("UseParameters", "VariableTable", parser.GetUseParametersRaw());

				return hr;

			}; // Result UseMapObjectCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UseMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UseMapObjectCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UseMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* UseMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInUseParameters = static_cast<uint16_t>(SerializedSizeOf(InUseParameters)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ serializedSizeOfInUseParameters
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::UseMapObjectCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(*output << InUseParameters);

				return hr;
			}; // MessageData* UseMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters )

			MessageData* UseMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInUseParameters = static_cast<uint16_t>(SerializedSizeOf(InUseParameters)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ sizeof(uint16_t)
					+ serializedSizeOfInUseParameters
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::UseMapObjectCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(output->Write(serializedSizeOfInUseParameters));
				protocolCheck(*output << InUseParameters);

				return hr;
			}; // MessageData* UseMapObjectCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )

			Result UseMapObjectCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UseMapObjectCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UseMapObject:{0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MapObjectId:{5}, UseParameters:{6}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId(), parser.GetUseParameters()); 
				return ResultCode::SUCCESS;
			}; // Result UseMapObjectCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID UseMapObjectRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 13);
			const VariableTable& UseMapObjectRes::GetResultAttributes() const
			{
 				if (!m_ResultAttributesHasParsed)
				{
 					m_ResultAttributesHasParsed = true;
					InputMemoryStream ResultAttributes_ReadStream(m_ResultAttributesRaw);
					*ResultAttributes_ReadStream.ToInputStream() >> m_ResultAttributes;
				} // if (!m_ResultAttributesHasParsed)
				return m_ResultAttributes;
			} // const VariableTable& UseMapObjectRes::GetResultAttributes() const
			Result UseMapObjectRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ResultAttributesPtr = nullptr;
				protocolCheck(input->ReadLink(ResultAttributesPtr, ArrayLen));
				m_ResultAttributesRaw.SetLinkedBuffer(ArrayLen, ResultAttributesPtr);

				return hr;

			}; // Result UseMapObjectRes::ParseMessage(const MessageData* pIMsg)

			Result UseMapObjectRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				UseMapObjectRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());
				variableBuilder.SetVariableArray("ResultAttributes", "VariableTable", parser.GetResultAttributesRaw());

				return hr;

			}; // Result UseMapObjectRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result UseMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) UseMapObjectRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UseMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* UseMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInResultAttributes = static_cast<uint16_t>(SerializedSizeOf(InResultAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ serializedSizeOfInResultAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::UseMapObjectRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(*output << InResultAttributes);

				return hr;
			}; // MessageData* UseMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes )

			MessageData* UseMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				uint16_t serializedSizeOfInResultAttributes = static_cast<uint16_t>(SerializedSizeOf(InResultAttributes)); 
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResultAttributes
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::UseMapObjectRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(output->Write(serializedSizeOfInResultAttributes));
				protocolCheck(*output << InResultAttributes);

				return hr;
			}; // MessageData* UseMapObjectRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )

			Result UseMapObjectRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				UseMapObjectRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "UseMapObject:{0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, MapObjectId:{6}, ResultAttributes:{7}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId(), parser.GetResultAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result UseMapObjectRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Send zone chatting
			const MessageID ZoneChatCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 14);
			const VariableTable& ZoneChatCmd::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& ZoneChatCmd::GetChatMetaData() const
			Result ZoneChatCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MessageType);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatMetaDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatMetaDataPtr, ArrayLen));
				m_ChatMetaDataRaw.SetLinkedBuffer(ArrayLen, ChatMetaDataPtr);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result ZoneChatCmd::ParseMessage(const MessageData* pIMsg)

			Result ZoneChatCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ZoneChatCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MessageType", parser.GetMessageType());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ZoneChatCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ZoneChatCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ZoneChatCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ZoneChatCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* ZoneChatCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMessageType)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ZoneChatCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMessageType);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ZoneChatCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* ZoneChatCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMessageType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ZoneChatCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMessageType);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ZoneChatCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ZoneChatCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ZoneChatCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ZoneChat:{0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MessageType:{5}, ChatMetaData:{6}, ChatMessage:{7,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMessageType(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ZoneChatCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID ZoneChatRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 14);
			Result ZoneChatRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ZoneChatRes::ParseMessage(const MessageData* pIMsg)

			Result ZoneChatRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ZoneChatRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ZoneChatRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ZoneChatRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ZoneChatRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ZoneChatRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* ZoneChatRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ZoneChatRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // MessageData* ZoneChatRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult )

			Result ZoneChatRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ZoneChatRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ZoneChat:{0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result ZoneChatRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Player state change
			const MessageID ZoneChatS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 15);
			const VariableTable& ZoneChatS2CEvt::GetChatMetaData() const
			{
 				if (!m_ChatMetaDataHasParsed)
				{
 					m_ChatMetaDataHasParsed = true;
					InputMemoryStream ChatMetaData_ReadStream(m_ChatMetaDataRaw);
					*ChatMetaData_ReadStream.ToInputStream() >> m_ChatMetaData;
				} // if (!m_ChatMetaDataHasParsed)
				return m_ChatMetaData;
			} // const VariableTable& ZoneChatS2CEvt::GetChatMetaData() const
			Result ZoneChatS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_SenderID);
				protocolCheck(*input >> m_MessageType);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* ChatMetaDataPtr = nullptr;
				protocolCheck(input->ReadLink(ChatMetaDataPtr, ArrayLen));
				m_ChatMetaDataRaw.SetLinkedBuffer(ArrayLen, ChatMetaDataPtr);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_ChatMessage, ArrayLen));

				return hr;

			}; // Result ZoneChatS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result ZoneChatS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				ZoneChatS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("MessageType", parser.GetMessageType());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ZoneChatS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result ZoneChatS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) ZoneChatS2CEvt(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ZoneChatS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )

			MessageData* ZoneChatS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InMessageType)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ZoneChatS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InMessageType);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ZoneChatS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			MessageData* ZoneChatS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InMessageType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::ZoneChatS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InMessageType);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // MessageData* ZoneChatS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ZoneChatS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				ZoneChatS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "ZoneChat:{0}:{1} , PlayInstanceUID:{2}, SenderID:{3}, MessageType:{4}, ChatMetaData:{5}, ChatMessage:{6,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetSenderID(), parser.GetMessageType(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ZoneChatS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// S2C: Effect modifier initial sync
			const MessageID LevelUpS2CEvt::MID = MessageID(MSGTYPE_EVENT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 16);
			Result LevelUpS2CEvt::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_CurrentExp);
				protocolCheck(*input >> m_CurrentLevel);

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessage(const MessageData* pIMsg)

			Result LevelUpS2CEvt::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				LevelUpS2CEvt parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("CurrentExp", parser.GetCurrentExp());
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


			MessageData* LevelUpS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCurrentExp)
					+ SerializedSizeOf(InCurrentLevel)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::LevelUpS2CEvt::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCurrentExp);
				protocolCheck(*output << InCurrentLevel);

				return hr;
			}; // MessageData* LevelUpS2CEvt::Create( IHeap& memHeap, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )

			Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				LevelUpS2CEvt parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "LevelUp:{0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, CurrentExp:{4}, CurrentLevel:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetCurrentExp(), parser.GetCurrentLevel()); 
				return ResultCode::SUCCESS;
			}; // Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Create stream instance
			const MessageID CreateStreamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 17);
			Result CreateStreamCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result CreateStreamCmd::ParseMessage(const MessageData* pIMsg)

			Result CreateStreamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateStreamCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result CreateStreamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateStreamCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID CreateStreamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 17);
			Result CreateStreamRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result CreateStreamRes::ParseMessage(const MessageData* pIMsg)

			Result CreateStreamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				CreateStreamRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result CreateStreamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result CreateStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateStreamRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* CreateStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::CreateStreamRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // MessageData* CreateStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )

			Result CreateStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CreateStreamRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CreateStream:{0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamName:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result CreateStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Open stream instance
			const MessageID FindStreamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 18);
			Result FindStreamCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result FindStreamCmd::ParseMessage(const MessageData* pIMsg)

			Result FindStreamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindStreamCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result FindStreamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindStreamCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID FindStreamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 18);
			Result FindStreamRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result FindStreamRes::ParseMessage(const MessageData* pIMsg)

			Result FindStreamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				FindStreamRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result FindStreamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result FindStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindStreamRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* FindStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::FindStreamRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // MessageData* FindStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )

			Result FindStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				FindStreamRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "FindStream:{0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamName:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result FindStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Delete stream instance
			const MessageID DeleteStreamCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 19);
			Result DeleteStreamCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result DeleteStreamCmd::ParseMessage(const MessageData* pIMsg)

			Result DeleteStreamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteStreamCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result DeleteStreamCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteStreamCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID DeleteStreamRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 19);
			Result DeleteStreamRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result DeleteStreamRes::ParseMessage(const MessageData* pIMsg)

			Result DeleteStreamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				DeleteStreamRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result DeleteStreamRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result DeleteStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteStreamRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


			MessageData* DeleteStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				MessageData *pNewMsg = nullptr;
				ScopeContext hr([&pNewMsg](Result hr) -> MessageData*
				{
 					if(!hr && pNewMsg != nullptr)
					{
 						IHeap::Delete(pNewMsg);
						return nullptr;
					}
					return pNewMsg;
				});

				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::DeleteStreamRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // MessageData* DeleteStreamRes::Create( IHeap& memHeap, const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName )

			Result DeleteStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				DeleteStreamRes parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "DeleteStream:{0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamName:{4,60}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteStreamRes::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			// Cmd: Get stream list
			const MessageID GetStreamListCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 20);
			Result GetStreamListCmd::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);

				return hr;

			}; // Result GetStreamListCmd::ParseMessage(const MessageData* pIMsg)

			Result GetStreamListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetStreamListCmd parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());

				return hr;

			}; // Result GetStreamListCmd::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetStreamListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetStreamListCmd(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetStreamListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			const MessageID GetStreamListRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 20);
			Result GetStreamListRes::ParseMessage(const MessageData* pIMsg)
			{
 				ScopeContext hr;


				protocolCheckPtr(pIMsg);

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->ReadArrayLink(m_StreamNames));

				return hr;

			}; // Result GetStreamListRes::ParseMessage(const MessageData* pIMsg)

			Result GetStreamListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )
			{
 				ScopeContext hr;


				GetStreamListRes parser;
				protocolCheck(parser.ParseMessage(*pIMsg));

				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamNames", parser.GetStreamNames());

				return hr;

			}; // Result GetStreamListRes::ParseMessageTo(const MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )

			Result GetStreamListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )
			{
 				ScopeContext hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetStreamListRes(pIMsg));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetStreamListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageDataPtr& pIMsg, MessageBase* &pMessageBase )


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

			// Cmd: To call general functionality
			const MessageID CallFunctionCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 21);
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

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_FunctionName);
				protocolCheck(*input >> m_PlayerID);
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
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
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

			MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInParameters
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::CallFunctionCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFunctionName);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InParameters);

				return hr;
			}; // MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters )

			MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
			{
 				MessageData *pNewMsg = nullptr;
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::CallFunctionCmd::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
				ArrayView<uint8_t> BufferView(MsgDataSize, 0, pNewMsg->GetMessageData());
				OutputMemoryStream outputStream(BufferView);
				auto* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFunctionName);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInParameters));
				protocolCheck(*output << InParameters);

				return hr;
			}; // MessageData* CallFunctionCmd::Create( IHeap& memHeap, const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )

			Result CallFunctionCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)
			{
 				CallFunctionCmd parser;
				parser.ParseMessage(*pMsg);
				SFLog(Net, Debug1, "CallFunction:{0}:{1} , TransactionID:{2}, FunctionName:{3}, PlayerID:{4}, Parameters:{5}",
						prefix, pMsg->GetMessageHeader()->Length, parser.GetTransactionID(), parser.GetFunctionName(), parser.GetPlayerID(), parser.GetParameters()); 
				return ResultCode::SUCCESS;
			}; // Result CallFunctionCmd::TraceOut(const char* prefix, const MessageDataPtr& pMsg)

			const MessageID CallFunctionRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_PLAYINSTANCE, 21);
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

				size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInResults
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::CallFunctionRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
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
				unsigned __uiMessageSize = (unsigned)(sizeof(MessageHeader) 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResults
				);

				protocolCheckMem( pNewMsg = MessageData::NewMessage( memHeap, PlayInstance::CallFunctionRes::MID, __uiMessageSize ) );
				auto MsgDataSize = static_cast<uint>((size_t)pNewMsg->GetMessageSize() - sizeof(MessageHeader));
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



		}; // namespace PlayInstance
	}; // namespace Message
}; // namespace SF



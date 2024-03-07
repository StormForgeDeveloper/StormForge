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
#include "SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "SFProtocolHelper.h"
#include "Protocol/PlayInstanceMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace PlayInstance
		{
 			// Cmd: Player Join request.
			Result JoinPlayInstanceCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PlayerIdentifier, ArrayLen));

				return hr;

			}; // Result JoinPlayInstanceCmd::ParseMessage(const MessageHeader* pHeader)

			Result JoinPlayInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinPlayInstanceCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerIdentifier", parser.GetPlayerIdentifier());

				return hr;

			}; // Result JoinPlayInstanceCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinPlayInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPlayInstanceCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPlayInstanceCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t JoinPlayInstanceCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerIdentifier)
				);

				return __uiMessageSize;
			}; // size_t JoinPlayInstanceCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )


			Result JoinPlayInstanceCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerIdentifier)
				);

				messageBuffer->msgID = JoinPlayInstanceCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerIdentifier);

				return hr;
			}; // Result JoinPlayInstanceCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )

			Result JoinPlayInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinPlayInstanceCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::JoinPlayInstance, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, PlayerIdentifier:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetPlayerIdentifier()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPlayInstanceCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

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
			Result JoinPlayInstanceRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result JoinPlayInstanceRes::ParseMessage(const MessageHeader* pHeader)

			Result JoinPlayInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				JoinPlayInstanceRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());
				variableBuilder.SetVariableArray("CharacterPrivateData", "VariableTable", parser.GetCharacterPrivateDataRaw());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result JoinPlayInstanceRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result JoinPlayInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) JoinPlayInstanceRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result JoinPlayInstanceRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t JoinPlayInstanceRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement )
			{
 				uint16_t serializedSizeOfInCharacterPrivateData = static_cast<uint16_t>(SerializedSizeOf(InCharacterPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ serializedSizeOfInCharacterPrivateData
					+ SerializedSizeOf(InMovement)
				);

				return __uiMessageSize;
			}; // size_t JoinPlayInstanceRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement )

			size_t JoinPlayInstanceRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
			{
 				uint16_t serializedSizeOfInCharacterPrivateData = static_cast<uint16_t>(SerializedSizeOf(InCharacterPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInCharacterPrivateData
					+ SerializedSizeOf(InMovement)
				);

				return __uiMessageSize;
			}; // size_t JoinPlayInstanceRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )

			Result JoinPlayInstanceRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InCharacterID, InCharacterPrivateData, InMovement);

				messageBuffer->msgID = JoinPlayInstanceRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCharacterID);
				protocolCheck(*output << InCharacterPrivateData);
				protocolCheck(*output << InMovement);

				return hr;
			}; // Result JoinPlayInstanceRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InCharacterPrivateData, const ActorMovement &InMovement )

			Result JoinPlayInstanceRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
			{
 				Result hr;

				uint16_t serializedSizeOfInCharacterPrivateData = static_cast<uint16_t>(SerializedSizeOf(InCharacterPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInCharacterPrivateData
					+ SerializedSizeOf(InMovement)
				);

				messageBuffer->msgID = JoinPlayInstanceRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCharacterID);
				protocolCheck(output->Write(serializedSizeOfInCharacterPrivateData));
				protocolCheck(*output << InCharacterPrivateData);
				protocolCheck(*output << InMovement);

				return hr;
			}; // Result JoinPlayInstanceRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )

			Result JoinPlayInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				JoinPlayInstanceRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::JoinPlayInstance, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, CharacterID:{6}, CharacterPrivateData:{7}, Movement:{8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetCharacterID(), parser.GetCharacterPrivateData(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result JoinPlayInstanceRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			Result PlayerKickedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_KickedPlayerID);

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PlayerKickedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerKickedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("KickedPlayerID", parser.GetKickedPlayerID());

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerKickedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerKickedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PlayerKickedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				return __uiMessageSize;
			}; // size_t PlayerKickedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )


			Result PlayerKickedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InKickedPlayerID)
				);

				messageBuffer->msgID = PlayerKickedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InKickedPlayerID);

				return hr;
			}; // Result PlayerKickedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID )

			Result PlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PlayerKickedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::PlayerKicked, {0}:{1} , PlayInstanceUID:{2}, KickedPlayerID:{3}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetKickedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerKickedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// C2S: Play packet
			Result PlayPacketC2SEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result PlayPacketC2SEvt::ParseMessage(const MessageHeader* pHeader)

			Result PlayPacketC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayPacketC2SEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("SenderEndpointID", parser.GetSenderEndpointID());
				variableBuilder.SetVariable("TargetEndpointMask", parser.GetTargetEndpointMask());
				variableBuilder.SetVariable("Payload", parser.GetPayload());

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PlayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayPacketC2SEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayPacketC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PlayPacketC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderEndpointID)
					+ SerializedSizeOf(InTargetEndpointMask)
					+ SerializedSizeOf(InPayload)
				);

				return __uiMessageSize;
			}; // size_t PlayPacketC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )


			Result PlayPacketC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderEndpointID)
					+ SerializedSizeOf(InTargetEndpointMask)
					+ SerializedSizeOf(InPayload)
				);

				messageBuffer->msgID = PlayPacketC2SEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InSenderEndpointID);
				protocolCheck(*output << InTargetEndpointMask);
				protocolCheck(*output << InPayload);

				return hr;
			}; // Result PlayPacketC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )

			Result PlayPacketC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PlayPacketC2SEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::PlayPacket, {0}:{1} , PlayInstanceUID:{2}, SenderEndpointID:{3}, TargetEndpointMask:{4}, Payload:{5,30}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetSenderEndpointID(), parser.GetTargetEndpointMask(), parser.GetPayload()); 
				return ResultCode::SUCCESS;
			}; // Result PlayPacketC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: New actor in get view
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
			Result NewActorInViewS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result NewActorInViewS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result NewActorInViewS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				NewActorInViewS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PlayerPlatformId", "PlayerPlatformID", parser.GetPlayerPlatformId());
				variableBuilder.SetVariableArray("PublicData", "VariableTable", parser.GetPublicDataRaw());
				variableBuilder.SetVariableArray("EquipData", "VariableTable", parser.GetEquipDataRaw());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());
				variableBuilder.SetVariable("State", parser.GetState());
				variableBuilder.SetVariableArray("StateValues", "VariableTable", parser.GetStateValuesRaw());

				return hr;

			}; // Result NewActorInViewS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result NewActorInViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) NewActorInViewS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result NewActorInViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t NewActorInViewS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues )
			{
 				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPlayerPlatformId)
					+ serializedSizeOfInPublicData
					+ serializedSizeOfInEquipData
					+ SerializedSizeOf(InMovement)
					+ SerializedSizeOf(InState)
					+ serializedSizeOfInStateValues
				);

				return __uiMessageSize;
			}; // size_t NewActorInViewS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues )

			size_t NewActorInViewS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
			{
 				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
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

				return __uiMessageSize;
			}; // size_t NewActorInViewS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )

			Result NewActorInViewS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InPlayerPlatformId, InPublicData, InEquipData, InMovement, InState, InStateValues);

				messageBuffer->msgID = NewActorInViewS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPlayerPlatformId);
				protocolCheck(*output << InPublicData);
				protocolCheck(*output << InEquipData);
				protocolCheck(*output << InMovement);
				protocolCheck(*output << InState);
				protocolCheck(*output << InStateValues);

				return hr;
			}; // Result NewActorInViewS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues )

			Result NewActorInViewS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
			{
 				Result hr;

				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				uint16_t serializedSizeOfInEquipData = static_cast<uint16_t>(SerializedSizeOf(InEquipData)); 
				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
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

				messageBuffer->msgID = NewActorInViewS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

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
			}; // Result NewActorInViewS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )

			Result NewActorInViewS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				NewActorInViewS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::NewActorInView, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, PlayerPlatformId:{4}, PublicData:{5}, EquipData:{6}, Movement:{7}, State:{8}, StateValues:{9}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetPlayerPlatformId(), parser.GetPublicData(), parser.GetEquipData(), parser.GetMovement(), parser.GetState(), parser.GetStateValues()); 
				return ResultCode::SUCCESS;
			}; // Result NewActorInViewS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Remove actor from view
			Result RemoveActorFromViewS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_ActorID);

				return hr;

			}; // Result RemoveActorFromViewS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result RemoveActorFromViewS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RemoveActorFromViewS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("ActorID", parser.GetActorID());

				return hr;

			}; // Result RemoveActorFromViewS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RemoveActorFromViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveActorFromViewS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveActorFromViewS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RemoveActorFromViewS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InActorID)
				);

				return __uiMessageSize;
			}; // size_t RemoveActorFromViewS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )


			Result RemoveActorFromViewS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InActorID)
				);

				messageBuffer->msgID = RemoveActorFromViewS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InActorID);

				return hr;
			}; // Result RemoveActorFromViewS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const uint32_t &InActorID )

			Result RemoveActorFromViewS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RemoveActorFromViewS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::RemoveActorFromView, {0}:{1} , PlayInstanceUID:{2}, ActorID:{3}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetActorID()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveActorFromViewS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// C2S: Player Movement
			Result PlayerMovementC2SEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_Movement);

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessage(const MessageHeader* pHeader)

			Result PlayerMovementC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerMovementC2SEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PlayerMovementC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerMovementC2SEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerMovementC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PlayerMovementC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMovement)
				);

				return __uiMessageSize;
			}; // size_t PlayerMovementC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )


			Result PlayerMovementC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMovement)
				);

				messageBuffer->msgID = PlayerMovementC2SEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMovement);

				return hr;
			}; // Result PlayerMovementC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )

			Result PlayerMovementC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PlayerMovementC2SEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug3, "PlayInstance::PlayerMovement, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, Movement:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerMovementC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player Movement
			Result ActorMovementS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_Movement);

				return hr;

			}; // Result ActorMovementS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ActorMovementS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ActorMovementS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result ActorMovementS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ActorMovementS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) ActorMovementS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ActorMovementS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ActorMovementS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InMovement)
				);

				return __uiMessageSize;
			}; // size_t ActorMovementS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )


			Result ActorMovementS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InMovement)
				);

				messageBuffer->msgID = ActorMovementS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InMovement);

				return hr;
			}; // Result ActorMovementS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement )

			Result ActorMovementS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ActorMovementS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug4, "PlayInstance::ActorMovement, {0}:{1} , PlayInstanceUID:{2}, Movement:{3}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result ActorMovementS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player Movement
			Result ActorMovementsS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(input->Read(ArrayLen));
				ActorMovement* MovementPtr = nullptr;
				protocolCheck(input->ReadLink(MovementPtr, ArrayLen));
				m_Movement.SetLinkedBuffer(ArrayLen, MovementPtr);

				return hr;

			}; // Result ActorMovementsS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ActorMovementsS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ActorMovementsS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariableArray("Movement", "ActorMovement", parser.GetMovement());

				return hr;

			}; // Result ActorMovementsS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ActorMovementsS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) ActorMovementsS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ActorMovementsS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ActorMovementsS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InMovement)
				);

				return __uiMessageSize;
			}; // size_t ActorMovementsS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )


			Result ActorMovementsS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InMovement)
				);

				messageBuffer->msgID = ActorMovementsS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InMovement);

				return hr;
			}; // Result ActorMovementsS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement )

			Result ActorMovementsS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ActorMovementsS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug4, "PlayInstance::ActorMovements, {0}:{1} , PlayInstanceUID:{2}, Movement:{3,30}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetMovement()); 
				return ResultCode::SUCCESS;
			}; // Result ActorMovementsS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player state change
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
			Result PlayerStateChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result PlayerStateChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result PlayerStateChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PlayerStateChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("State", parser.GetState());
				variableBuilder.SetVariable("MoveFrame", parser.GetMoveFrame());
				variableBuilder.SetVariable("Position", "Vector4", parser.GetPosition());
				variableBuilder.SetVariableArray("StateValues", "VariableTable", parser.GetStateValuesRaw());

				return hr;

			}; // Result PlayerStateChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PlayerStateChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) PlayerStateChangedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PlayerStateChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t PlayerStateChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues )
			{
 				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InState)
					+ SerializedSizeOf(InMoveFrame)
					+ SerializedSizeOf(InPosition)
					+ serializedSizeOfInStateValues
				);

				return __uiMessageSize;
			}; // size_t PlayerStateChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues )

			size_t PlayerStateChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
			{
 				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InState)
					+ SerializedSizeOf(InMoveFrame)
					+ SerializedSizeOf(InPosition)
					+ sizeof(uint16_t)
					+ serializedSizeOfInStateValues
				);

				return __uiMessageSize;
			}; // size_t PlayerStateChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )

			Result PlayerStateChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InState, InMoveFrame, InPosition, InStateValues);

				messageBuffer->msgID = PlayerStateChangedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InState);
				protocolCheck(*output << InMoveFrame);
				protocolCheck(*output << InPosition);
				protocolCheck(*output << InStateValues);

				return hr;
			}; // Result PlayerStateChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues )

			Result PlayerStateChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
			{
 				Result hr;

				uint16_t serializedSizeOfInStateValues = static_cast<uint16_t>(SerializedSizeOf(InStateValues)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InState)
					+ SerializedSizeOf(InMoveFrame)
					+ SerializedSizeOf(InPosition)
					+ sizeof(uint16_t)
					+ serializedSizeOfInStateValues
				);

				messageBuffer->msgID = PlayerStateChangedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InState);
				protocolCheck(*output << InMoveFrame);
				protocolCheck(*output << InPosition);
				protocolCheck(output->Write(serializedSizeOfInStateValues));
				protocolCheck(*output << InStateValues);

				return hr;
			}; // Result PlayerStateChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )

			Result PlayerStateChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PlayerStateChangedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::PlayerStateChanged, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, State:{4}, MoveFrame:{5}, Position:{6}, StateValues:{7}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetState(), parser.GetMoveFrame(), parser.GetPosition(), parser.GetStateValues()); 
				return ResultCode::SUCCESS;
			}; // Result PlayerStateChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
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
			Result ClientSyncReliableC2SEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result ClientSyncReliableC2SEvt::ParseMessage(const MessageHeader* pHeader)

			Result ClientSyncReliableC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ClientSyncReliableC2SEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("SyncData", "VariableTable", parser.GetSyncDataRaw());

				return hr;

			}; // Result ClientSyncReliableC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ClientSyncReliableC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) ClientSyncReliableC2SEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ClientSyncReliableC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t ClientSyncReliableC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )
			{
 				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInSyncData
				);

				return __uiMessageSize;
			}; // size_t ClientSyncReliableC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )

			size_t ClientSyncReliableC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
			{
 				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInSyncData
				);

				return __uiMessageSize;
			}; // size_t ClientSyncReliableC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )

			Result ClientSyncReliableC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InSyncData);

				messageBuffer->msgID = ClientSyncReliableC2SEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InSyncData);

				return hr;
			}; // Result ClientSyncReliableC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )

			Result ClientSyncReliableC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
			{
 				Result hr;

				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInSyncData
				);

				messageBuffer->msgID = ClientSyncReliableC2SEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInSyncData));
				protocolCheck(*output << InSyncData);

				return hr;
			}; // Result ClientSyncReliableC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )

			Result ClientSyncReliableC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ClientSyncReliableC2SEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::ClientSyncReliable, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, SyncData:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetSyncData()); 
				return ResultCode::SUCCESS;
			}; // Result ClientSyncReliableC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
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
			Result ClientSyncC2SEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result ClientSyncC2SEvt::ParseMessage(const MessageHeader* pHeader)

			Result ClientSyncC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ClientSyncC2SEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("SyncData", "VariableTable", parser.GetSyncDataRaw());

				return hr;

			}; // Result ClientSyncC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ClientSyncC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) ClientSyncC2SEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ClientSyncC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t ClientSyncC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )
			{
 				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInSyncData
				);

				return __uiMessageSize;
			}; // size_t ClientSyncC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )

			size_t ClientSyncC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
			{
 				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInSyncData
				);

				return __uiMessageSize;
			}; // size_t ClientSyncC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )

			Result ClientSyncC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InSyncData);

				messageBuffer->msgID = ClientSyncC2SEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InSyncData);

				return hr;
			}; // Result ClientSyncC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData )

			Result ClientSyncC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
			{
 				Result hr;

				uint16_t serializedSizeOfInSyncData = static_cast<uint16_t>(SerializedSizeOf(InSyncData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInSyncData
				);

				messageBuffer->msgID = ClientSyncC2SEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInSyncData));
				protocolCheck(*output << InSyncData);

				return hr;
			}; // Result ClientSyncC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )

			Result ClientSyncC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ClientSyncC2SEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::ClientSync, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, SyncData:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetSyncData()); 
				return ResultCode::SUCCESS;
			}; // Result ClientSyncC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
			Result SetCharacterPublicMessageCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_PublicMessage, ArrayLen));

				return hr;

			}; // Result SetCharacterPublicMessageCmd::ParseMessage(const MessageHeader* pHeader)

			Result SetCharacterPublicMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetCharacterPublicMessageCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("PublicMessage", parser.GetPublicMessage());

				return hr;

			}; // Result SetCharacterPublicMessageCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetCharacterPublicMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetCharacterPublicMessageCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetCharacterPublicMessageCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetCharacterPublicMessageCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPublicMessage)
				);

				return __uiMessageSize;
			}; // size_t SetCharacterPublicMessageCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage )


			Result SetCharacterPublicMessageCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InPublicMessage)
				);

				messageBuffer->msgID = SetCharacterPublicMessageCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPublicMessage);

				return hr;
			}; // Result SetCharacterPublicMessageCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage )

			Result SetCharacterPublicMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetCharacterPublicMessageCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::SetCharacterPublicMessage, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, PublicMessage:{5,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetPublicMessage()); 
				return ResultCode::SUCCESS;
			}; // Result SetCharacterPublicMessageCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result SetCharacterPublicMessageRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result SetCharacterPublicMessageRes::ParseMessage(const MessageHeader* pHeader)

			Result SetCharacterPublicMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SetCharacterPublicMessageRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result SetCharacterPublicMessageRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SetCharacterPublicMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) SetCharacterPublicMessageRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SetCharacterPublicMessageRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SetCharacterPublicMessageRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t SetCharacterPublicMessageRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result SetCharacterPublicMessageRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = SetCharacterPublicMessageRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result SetCharacterPublicMessageRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result SetCharacterPublicMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SetCharacterPublicMessageRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::SetCharacterPublicMessage, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result SetCharacterPublicMessageRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Character's private data has changed
			const VariableTable& CharacterPrivateDataChangedS2CEvt::GetPrivateData() const
			{
 				if (!m_PrivateDataHasParsed)
				{
 					m_PrivateDataHasParsed = true;
					InputMemoryStream PrivateData_ReadStream(m_PrivateDataRaw);
					*PrivateData_ReadStream.ToInputStream() >> m_PrivateData;
				} // if (!m_PrivateDataHasParsed)
				return m_PrivateData;
			} // const VariableTable& CharacterPrivateDataChangedS2CEvt::GetPrivateData() const
			Result CharacterPrivateDataChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_CharacterID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PrivateDataPtr = nullptr;
				protocolCheck(input->ReadLink(PrivateDataPtr, ArrayLen));
				m_PrivateDataRaw.SetLinkedBuffer(ArrayLen, PrivateDataPtr);

				return hr;

			}; // Result CharacterPrivateDataChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result CharacterPrivateDataChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CharacterPrivateDataChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("CharacterID", parser.GetCharacterID());
				variableBuilder.SetVariableArray("PrivateData", "VariableTable", parser.GetPrivateDataRaw());

				return hr;

			}; // Result CharacterPrivateDataChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CharacterPrivateDataChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CharacterPrivateDataChangedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CharacterPrivateDataChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t CharacterPrivateDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const Array<uint8_t>& InPrivateData )
			{
 				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ serializedSizeOfInPrivateData
				);

				return __uiMessageSize;
			}; // size_t CharacterPrivateDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const Array<uint8_t>& InPrivateData )

			size_t CharacterPrivateDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const VariableTable &InPrivateData )
			{
 				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPrivateData
				);

				return __uiMessageSize;
			}; // size_t CharacterPrivateDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const VariableTable &InPrivateData )

			Result CharacterPrivateDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const Array<uint8_t>& InPrivateData )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InCharacterID, InPrivateData);

				messageBuffer->msgID = CharacterPrivateDataChangedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCharacterID);
				protocolCheck(*output << InPrivateData);

				return hr;
			}; // Result CharacterPrivateDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const Array<uint8_t>& InPrivateData )

			Result CharacterPrivateDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const VariableTable &InPrivateData )
			{
 				Result hr;

				uint16_t serializedSizeOfInPrivateData = static_cast<uint16_t>(SerializedSizeOf(InPrivateData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCharacterID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPrivateData
				);

				messageBuffer->msgID = CharacterPrivateDataChangedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCharacterID);
				protocolCheck(output->Write(serializedSizeOfInPrivateData));
				protocolCheck(*output << InPrivateData);

				return hr;
			}; // Result CharacterPrivateDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const VariableTable &InPrivateData )

			Result CharacterPrivateDataChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CharacterPrivateDataChangedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CharacterPrivateDataChanged, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, CharacterID:{4}, PrivateData:{5}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetCharacterID(), parser.GetPrivateData()); 
				return ResultCode::SUCCESS;
			}; // Result CharacterPrivateDataChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player public data has been changed
			const VariableTable& CharacterPublicDataChangedS2CEvt::GetPublicData() const
			{
 				if (!m_PublicDataHasParsed)
				{
 					m_PublicDataHasParsed = true;
					InputMemoryStream PublicData_ReadStream(m_PublicDataRaw);
					*PublicData_ReadStream.ToInputStream() >> m_PublicData;
				} // if (!m_PublicDataHasParsed)
				return m_PublicData;
			} // const VariableTable& CharacterPublicDataChangedS2CEvt::GetPublicData() const
			Result CharacterPublicDataChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* PublicDataPtr = nullptr;
				protocolCheck(input->ReadLink(PublicDataPtr, ArrayLen));
				m_PublicDataRaw.SetLinkedBuffer(ArrayLen, PublicDataPtr);

				return hr;

			}; // Result CharacterPublicDataChangedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result CharacterPublicDataChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CharacterPublicDataChangedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("PublicData", "VariableTable", parser.GetPublicDataRaw());

				return hr;

			}; // Result CharacterPublicDataChangedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CharacterPublicDataChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CharacterPublicDataChangedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CharacterPublicDataChangedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t CharacterPublicDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData )
			{
 				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInPublicData
				);

				return __uiMessageSize;
			}; // size_t CharacterPublicDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData )

			size_t CharacterPublicDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData )
			{
 				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPublicData
				);

				return __uiMessageSize;
			}; // size_t CharacterPublicDataChangedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData )

			Result CharacterPublicDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InPublicData);

				messageBuffer->msgID = CharacterPublicDataChangedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InPublicData);

				return hr;
			}; // Result CharacterPublicDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData )

			Result CharacterPublicDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData )
			{
 				Result hr;

				uint16_t serializedSizeOfInPublicData = static_cast<uint16_t>(SerializedSizeOf(InPublicData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInPublicData
				);

				messageBuffer->msgID = CharacterPublicDataChangedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInPublicData));
				protocolCheck(*output << InPublicData);

				return hr;
			}; // Result CharacterPublicDataChangedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData )

			Result CharacterPublicDataChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CharacterPublicDataChangedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CharacterPublicDataChanged, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, PublicData:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetPublicData()); 
				return ResultCode::SUCCESS;
			}; // Result CharacterPublicDataChangedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Request WhiteboardSharing
			const VariableTable& RequestWhiteboardSharingCmd::GetWhiteboardInfo() const
			{
 				if (!m_WhiteboardInfoHasParsed)
				{
 					m_WhiteboardInfoHasParsed = true;
					InputMemoryStream WhiteboardInfo_ReadStream(m_WhiteboardInfoRaw);
					*WhiteboardInfo_ReadStream.ToInputStream() >> m_WhiteboardInfo;
				} // if (!m_WhiteboardInfoHasParsed)
				return m_WhiteboardInfo;
			} // const VariableTable& RequestWhiteboardSharingCmd::GetWhiteboardInfo() const
			Result RequestWhiteboardSharingCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_TargetPlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* WhiteboardInfoPtr = nullptr;
				protocolCheck(input->ReadLink(WhiteboardInfoPtr, ArrayLen));
				m_WhiteboardInfoRaw.SetLinkedBuffer(ArrayLen, WhiteboardInfoPtr);

				return hr;

			}; // Result RequestWhiteboardSharingCmd::ParseMessage(const MessageHeader* pHeader)

			Result RequestWhiteboardSharingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RequestWhiteboardSharingCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("TargetPlayerID", parser.GetTargetPlayerID());
				variableBuilder.SetVariableArray("WhiteboardInfo", "VariableTable", parser.GetWhiteboardInfoRaw());

				return hr;

			}; // Result RequestWhiteboardSharingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestWhiteboardSharingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestWhiteboardSharingCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestWhiteboardSharingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t RequestWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo )
			{
 				uint16_t serializedSizeOfInWhiteboardInfo = static_cast<uint16_t>(SerializedSizeOf(InWhiteboardInfo)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTargetPlayerID)
					+ serializedSizeOfInWhiteboardInfo
				);

				return __uiMessageSize;
			}; // size_t RequestWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo )

			size_t RequestWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo )
			{
 				uint16_t serializedSizeOfInWhiteboardInfo = static_cast<uint16_t>(SerializedSizeOf(InWhiteboardInfo)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTargetPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInWhiteboardInfo
				);

				return __uiMessageSize;
			}; // size_t RequestWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo )

			Result RequestWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InTargetPlayerID, InWhiteboardInfo);

				messageBuffer->msgID = RequestWhiteboardSharingCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTargetPlayerID);
				protocolCheck(*output << InWhiteboardInfo);

				return hr;
			}; // Result RequestWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo )

			Result RequestWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo )
			{
 				Result hr;

				uint16_t serializedSizeOfInWhiteboardInfo = static_cast<uint16_t>(SerializedSizeOf(InWhiteboardInfo)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InTargetPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInWhiteboardInfo
				);

				messageBuffer->msgID = RequestWhiteboardSharingCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InTargetPlayerID);
				protocolCheck(output->Write(serializedSizeOfInWhiteboardInfo));
				protocolCheck(*output << InWhiteboardInfo);

				return hr;
			}; // Result RequestWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo )

			Result RequestWhiteboardSharingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestWhiteboardSharingCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::RequestWhiteboardSharing, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, TargetPlayerID:{5}, WhiteboardInfo:{6}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetTargetPlayerID(), parser.GetWhiteboardInfo()); 
				return ResultCode::SUCCESS;
			}; // Result RequestWhiteboardSharingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result RequestWhiteboardSharingRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RequestWhiteboardSharingRes::ParseMessage(const MessageHeader* pHeader)

			Result RequestWhiteboardSharingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RequestWhiteboardSharingRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RequestWhiteboardSharingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RequestWhiteboardSharingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) RequestWhiteboardSharingRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RequestWhiteboardSharingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RequestWhiteboardSharingRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t RequestWhiteboardSharingRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result RequestWhiteboardSharingRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = RequestWhiteboardSharingRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result RequestWhiteboardSharingRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result RequestWhiteboardSharingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RequestWhiteboardSharingRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::RequestWhiteboardSharing, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result RequestWhiteboardSharingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Accept WhiteboardSharing
			Result AcceptWhiteboardSharingCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_RequestedPlayerID);
				protocolCheck(*input >> m_Answer);

				return hr;

			}; // Result AcceptWhiteboardSharingCmd::ParseMessage(const MessageHeader* pHeader)

			Result AcceptWhiteboardSharingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AcceptWhiteboardSharingCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("RequestedPlayerID", parser.GetRequestedPlayerID());
				variableBuilder.SetVariable("Answer", parser.GetAnswer());

				return hr;

			}; // Result AcceptWhiteboardSharingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AcceptWhiteboardSharingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptWhiteboardSharingCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptWhiteboardSharingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t AcceptWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InRequestedPlayerID)
					+ SerializedSizeOf(InAnswer)
				);

				return __uiMessageSize;
			}; // size_t AcceptWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer )


			Result AcceptWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InRequestedPlayerID)
					+ SerializedSizeOf(InAnswer)
				);

				messageBuffer->msgID = AcceptWhiteboardSharingCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InRequestedPlayerID);
				protocolCheck(*output << InAnswer);

				return hr;
			}; // Result AcceptWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer )

			Result AcceptWhiteboardSharingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AcceptWhiteboardSharingCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::AcceptWhiteboardSharing, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, RequestedPlayerID:{5}, Answer:{6}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetRequestedPlayerID(), parser.GetAnswer()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptWhiteboardSharingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result AcceptWhiteboardSharingRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result AcceptWhiteboardSharingRes::ParseMessage(const MessageHeader* pHeader)

			Result AcceptWhiteboardSharingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AcceptWhiteboardSharingRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result AcceptWhiteboardSharingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AcceptWhiteboardSharingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) AcceptWhiteboardSharingRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AcceptWhiteboardSharingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t AcceptWhiteboardSharingRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t AcceptWhiteboardSharingRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result AcceptWhiteboardSharingRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = AcceptWhiteboardSharingRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result AcceptWhiteboardSharingRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result AcceptWhiteboardSharingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AcceptWhiteboardSharingRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::AcceptWhiteboardSharing, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result AcceptWhiteboardSharingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
			Result CloseWhiteboardSharingCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);

				return hr;

			}; // Result CloseWhiteboardSharingCmd::ParseMessage(const MessageHeader* pHeader)

			Result CloseWhiteboardSharingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CloseWhiteboardSharingCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());

				return hr;

			}; // Result CloseWhiteboardSharingCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CloseWhiteboardSharingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CloseWhiteboardSharingCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CloseWhiteboardSharingCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CloseWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
				);

				return __uiMessageSize;
			}; // size_t CloseWhiteboardSharingCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID )


			Result CloseWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
				);

				messageBuffer->msgID = CloseWhiteboardSharingCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);

				return hr;
			}; // Result CloseWhiteboardSharingCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID )

			Result CloseWhiteboardSharingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CloseWhiteboardSharingCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CloseWhiteboardSharing, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result CloseWhiteboardSharingCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result CloseWhiteboardSharingRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result CloseWhiteboardSharingRes::ParseMessage(const MessageHeader* pHeader)

			Result CloseWhiteboardSharingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CloseWhiteboardSharingRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result CloseWhiteboardSharingRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CloseWhiteboardSharingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CloseWhiteboardSharingRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CloseWhiteboardSharingRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CloseWhiteboardSharingRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t CloseWhiteboardSharingRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result CloseWhiteboardSharingRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = CloseWhiteboardSharingRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result CloseWhiteboardSharingRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result CloseWhiteboardSharingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CloseWhiteboardSharingRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CloseWhiteboardSharing, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result CloseWhiteboardSharingRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			const VariableTable& AddWhiteboardSharingLogEntryCmd::GetLogEntry() const
			{
 				if (!m_LogEntryHasParsed)
				{
 					m_LogEntryHasParsed = true;
					InputMemoryStream LogEntry_ReadStream(m_LogEntryRaw);
					*LogEntry_ReadStream.ToInputStream() >> m_LogEntry;
				} // if (!m_LogEntryHasParsed)
				return m_LogEntry;
			} // const VariableTable& AddWhiteboardSharingLogEntryCmd::GetLogEntry() const
			Result AddWhiteboardSharingLogEntryCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* LogEntryPtr = nullptr;
				protocolCheck(input->ReadLink(LogEntryPtr, ArrayLen));
				m_LogEntryRaw.SetLinkedBuffer(ArrayLen, LogEntryPtr);

				return hr;

			}; // Result AddWhiteboardSharingLogEntryCmd::ParseMessage(const MessageHeader* pHeader)

			Result AddWhiteboardSharingLogEntryCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AddWhiteboardSharingLogEntryCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("LogEntry", "VariableTable", parser.GetLogEntryRaw());

				return hr;

			}; // Result AddWhiteboardSharingLogEntryCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AddWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) AddWhiteboardSharingLogEntryCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AddWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t AddWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t AddWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			size_t AddWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t AddWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result AddWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntry);

				messageBuffer->msgID = AddWhiteboardSharingLogEntryCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result AddWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			Result AddWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				Result hr;

				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				messageBuffer->msgID = AddWhiteboardSharingLogEntryCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInLogEntry));
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result AddWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result AddWhiteboardSharingLogEntryCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AddWhiteboardSharingLogEntryCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::AddWhiteboardSharingLogEntry, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, LogEntry:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetLogEntry()); 
				return ResultCode::SUCCESS;
			}; // Result AddWhiteboardSharingLogEntryCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result AddWhiteboardSharingLogEntryRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_LogEntryID);

				return hr;

			}; // Result AddWhiteboardSharingLogEntryRes::ParseMessage(const MessageHeader* pHeader)

			Result AddWhiteboardSharingLogEntryRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				AddWhiteboardSharingLogEntryRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("LogEntryID", "LogEntryID", parser.GetLogEntryID());

				return hr;

			}; // Result AddWhiteboardSharingLogEntryRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result AddWhiteboardSharingLogEntryRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) AddWhiteboardSharingLogEntryRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result AddWhiteboardSharingLogEntryRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t AddWhiteboardSharingLogEntryRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InLogEntryID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InLogEntryID)
				);

				return __uiMessageSize;
			}; // size_t AddWhiteboardSharingLogEntryRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InLogEntryID )


			Result AddWhiteboardSharingLogEntryRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InLogEntryID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InLogEntryID)
				);

				messageBuffer->msgID = AddWhiteboardSharingLogEntryRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InLogEntryID);

				return hr;
			}; // Result AddWhiteboardSharingLogEntryRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InLogEntryID )

			Result AddWhiteboardSharingLogEntryRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				AddWhiteboardSharingLogEntryRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::AddWhiteboardSharingLogEntry, {0}:{1} , TransactionID:{2}, Result:{3:X8}, LogEntryID:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetLogEntryID()); 
				return ResultCode::SUCCESS;
			}; // Result AddWhiteboardSharingLogEntryRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			const VariableTable& UpdateWhiteboardSharingLogEntryCmd::GetLogEntry() const
			{
 				if (!m_LogEntryHasParsed)
				{
 					m_LogEntryHasParsed = true;
					InputMemoryStream LogEntry_ReadStream(m_LogEntryRaw);
					*LogEntry_ReadStream.ToInputStream() >> m_LogEntry;
				} // if (!m_LogEntryHasParsed)
				return m_LogEntry;
			} // const VariableTable& UpdateWhiteboardSharingLogEntryCmd::GetLogEntry() const
			Result UpdateWhiteboardSharingLogEntryCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* LogEntryPtr = nullptr;
				protocolCheck(input->ReadLink(LogEntryPtr, ArrayLen));
				m_LogEntryRaw.SetLinkedBuffer(ArrayLen, LogEntryPtr);

				return hr;

			}; // Result UpdateWhiteboardSharingLogEntryCmd::ParseMessage(const MessageHeader* pHeader)

			Result UpdateWhiteboardSharingLogEntryCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UpdateWhiteboardSharingLogEntryCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("LogEntry", "VariableTable", parser.GetLogEntryRaw());

				return hr;

			}; // Result UpdateWhiteboardSharingLogEntryCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UpdateWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateWhiteboardSharingLogEntryCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t UpdateWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t UpdateWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			size_t UpdateWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t UpdateWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result UpdateWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntry);

				messageBuffer->msgID = UpdateWhiteboardSharingLogEntryCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result UpdateWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			Result UpdateWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				Result hr;

				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				messageBuffer->msgID = UpdateWhiteboardSharingLogEntryCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInLogEntry));
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result UpdateWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result UpdateWhiteboardSharingLogEntryCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UpdateWhiteboardSharingLogEntryCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::UpdateWhiteboardSharingLogEntry, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, LogEntry:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetLogEntry()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateWhiteboardSharingLogEntryCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result UpdateWhiteboardSharingLogEntryRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result UpdateWhiteboardSharingLogEntryRes::ParseMessage(const MessageHeader* pHeader)

			Result UpdateWhiteboardSharingLogEntryRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UpdateWhiteboardSharingLogEntryRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result UpdateWhiteboardSharingLogEntryRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UpdateWhiteboardSharingLogEntryRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) UpdateWhiteboardSharingLogEntryRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UpdateWhiteboardSharingLogEntryRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t UpdateWhiteboardSharingLogEntryRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t UpdateWhiteboardSharingLogEntryRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result UpdateWhiteboardSharingLogEntryRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = UpdateWhiteboardSharingLogEntryRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result UpdateWhiteboardSharingLogEntryRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result UpdateWhiteboardSharingLogEntryRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UpdateWhiteboardSharingLogEntryRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::UpdateWhiteboardSharingLogEntry, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result UpdateWhiteboardSharingLogEntryRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Update whiteboard log entry
			Result RemoveWhiteboardSharingLogEntryCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_LogEntryID);

				return hr;

			}; // Result RemoveWhiteboardSharingLogEntryCmd::ParseMessage(const MessageHeader* pHeader)

			Result RemoveWhiteboardSharingLogEntryCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RemoveWhiteboardSharingLogEntryCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("LogEntryID", "LogEntryID", parser.GetLogEntryID());

				return hr;

			}; // Result RemoveWhiteboardSharingLogEntryCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RemoveWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveWhiteboardSharingLogEntryCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RemoveWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InLogEntryID)
				);

				return __uiMessageSize;
			}; // size_t RemoveWhiteboardSharingLogEntryCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )


			Result RemoveWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InLogEntryID)
				);

				messageBuffer->msgID = RemoveWhiteboardSharingLogEntryCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLogEntryID);

				return hr;
			}; // Result RemoveWhiteboardSharingLogEntryCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )

			Result RemoveWhiteboardSharingLogEntryCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RemoveWhiteboardSharingLogEntryCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::RemoveWhiteboardSharingLogEntry, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, LogEntryID:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetLogEntryID()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveWhiteboardSharingLogEntryCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result RemoveWhiteboardSharingLogEntryRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result RemoveWhiteboardSharingLogEntryRes::ParseMessage(const MessageHeader* pHeader)

			Result RemoveWhiteboardSharingLogEntryRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				RemoveWhiteboardSharingLogEntryRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result RemoveWhiteboardSharingLogEntryRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result RemoveWhiteboardSharingLogEntryRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) RemoveWhiteboardSharingLogEntryRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result RemoveWhiteboardSharingLogEntryRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t RemoveWhiteboardSharingLogEntryRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t RemoveWhiteboardSharingLogEntryRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result RemoveWhiteboardSharingLogEntryRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = RemoveWhiteboardSharingLogEntryRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result RemoveWhiteboardSharingLogEntryRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result RemoveWhiteboardSharingLogEntryRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				RemoveWhiteboardSharingLogEntryRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::RemoveWhiteboardSharingLogEntry, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result RemoveWhiteboardSharingLogEntryRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: WhiteboardSharing has been requested
			Result WhiteboardSharingRequestedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_RequestedPlayerID);

				return hr;

			}; // Result WhiteboardSharingRequestedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhiteboardSharingRequestedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				WhiteboardSharingRequestedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("RequestedPlayerID", parser.GetRequestedPlayerID());

				return hr;

			}; // Result WhiteboardSharingRequestedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhiteboardSharingRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhiteboardSharingRequestedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhiteboardSharingRequestedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t WhiteboardSharingRequestedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InRequestedPlayerID)
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingRequestedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID )


			Result WhiteboardSharingRequestedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InRequestedPlayerID)
				);

				messageBuffer->msgID = WhiteboardSharingRequestedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InRequestedPlayerID);

				return hr;
			}; // Result WhiteboardSharingRequestedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID )

			Result WhiteboardSharingRequestedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhiteboardSharingRequestedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::WhiteboardSharingRequested, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, RequestedPlayerID:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetRequestedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result WhiteboardSharingRequestedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: WhiteboardSharing has been requested
			Result WhiteboardSharingRejectedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_RejectedPlayerID);

				return hr;

			}; // Result WhiteboardSharingRejectedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhiteboardSharingRejectedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				WhiteboardSharingRejectedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("RejectedPlayerID", parser.GetRejectedPlayerID());

				return hr;

			}; // Result WhiteboardSharingRejectedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhiteboardSharingRejectedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhiteboardSharingRejectedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhiteboardSharingRejectedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t WhiteboardSharingRejectedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InRejectedPlayerID)
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingRejectedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID )


			Result WhiteboardSharingRejectedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InRejectedPlayerID)
				);

				messageBuffer->msgID = WhiteboardSharingRejectedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InRejectedPlayerID);

				return hr;
			}; // Result WhiteboardSharingRejectedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID )

			Result WhiteboardSharingRejectedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhiteboardSharingRejectedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::WhiteboardSharingRejected, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, RejectedPlayerID:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetRejectedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result WhiteboardSharingRejectedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: WhiteboardSharing has been started
			const VariableTable& WhiteboardSharingStartedS2CEvt::GetWhiteboardInfo() const
			{
 				if (!m_WhiteboardInfoHasParsed)
				{
 					m_WhiteboardInfoHasParsed = true;
					InputMemoryStream WhiteboardInfo_ReadStream(m_WhiteboardInfoRaw);
					*WhiteboardInfo_ReadStream.ToInputStream() >> m_WhiteboardInfo;
				} // if (!m_WhiteboardInfoHasParsed)
				return m_WhiteboardInfo;
			} // const VariableTable& WhiteboardSharingStartedS2CEvt::GetWhiteboardInfo() const
			Result WhiteboardSharingStartedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_OtherPlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* WhiteboardInfoPtr = nullptr;
				protocolCheck(input->ReadLink(WhiteboardInfoPtr, ArrayLen));
				m_WhiteboardInfoRaw.SetLinkedBuffer(ArrayLen, WhiteboardInfoPtr);

				return hr;

			}; // Result WhiteboardSharingStartedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhiteboardSharingStartedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				WhiteboardSharingStartedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("OtherPlayerID", parser.GetOtherPlayerID());
				variableBuilder.SetVariableArray("WhiteboardInfo", "VariableTable", parser.GetWhiteboardInfoRaw());

				return hr;

			}; // Result WhiteboardSharingStartedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhiteboardSharingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhiteboardSharingStartedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhiteboardSharingStartedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t WhiteboardSharingStartedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo )
			{
 				uint16_t serializedSizeOfInWhiteboardInfo = static_cast<uint16_t>(SerializedSizeOf(InWhiteboardInfo)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InOtherPlayerID)
					+ serializedSizeOfInWhiteboardInfo
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingStartedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo )

			size_t WhiteboardSharingStartedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo )
			{
 				uint16_t serializedSizeOfInWhiteboardInfo = static_cast<uint16_t>(SerializedSizeOf(InWhiteboardInfo)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InOtherPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInWhiteboardInfo
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingStartedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo )

			Result WhiteboardSharingStartedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InOtherPlayerID, InWhiteboardInfo);

				messageBuffer->msgID = WhiteboardSharingStartedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InOtherPlayerID);
				protocolCheck(*output << InWhiteboardInfo);

				return hr;
			}; // Result WhiteboardSharingStartedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo )

			Result WhiteboardSharingStartedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo )
			{
 				Result hr;

				uint16_t serializedSizeOfInWhiteboardInfo = static_cast<uint16_t>(SerializedSizeOf(InWhiteboardInfo)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InOtherPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInWhiteboardInfo
				);

				messageBuffer->msgID = WhiteboardSharingStartedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InOtherPlayerID);
				protocolCheck(output->Write(serializedSizeOfInWhiteboardInfo));
				protocolCheck(*output << InWhiteboardInfo);

				return hr;
			}; // Result WhiteboardSharingStartedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo )

			Result WhiteboardSharingStartedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhiteboardSharingStartedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::WhiteboardSharingStarted, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, OtherPlayerID:{4}, WhiteboardInfo:{5}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetOtherPlayerID(), parser.GetWhiteboardInfo()); 
				return ResultCode::SUCCESS;
			}; // Result WhiteboardSharingStartedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: WhiteboardSharing has been closed
			Result WhiteboardSharingHasClosedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_ClosedPlayerID);

				return hr;

			}; // Result WhiteboardSharingHasClosedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhiteboardSharingHasClosedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				WhiteboardSharingHasClosedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("ClosedPlayerID", parser.GetClosedPlayerID());

				return hr;

			}; // Result WhiteboardSharingHasClosedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhiteboardSharingHasClosedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhiteboardSharingHasClosedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhiteboardSharingHasClosedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t WhiteboardSharingHasClosedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InClosedPlayerID)
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingHasClosedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID )


			Result WhiteboardSharingHasClosedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InClosedPlayerID)
				);

				messageBuffer->msgID = WhiteboardSharingHasClosedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InClosedPlayerID);

				return hr;
			}; // Result WhiteboardSharingHasClosedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID )

			Result WhiteboardSharingHasClosedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhiteboardSharingHasClosedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::WhiteboardSharingHasClosed, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, ClosedPlayerID:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetClosedPlayerID()); 
				return ResultCode::SUCCESS;
			}; // Result WhiteboardSharingHasClosedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: WhiteboardSharing new log entry has been added
			const VariableTable& WhiteboardSharingNewLogEntryAddedS2CEvt::GetLogEntry() const
			{
 				if (!m_LogEntryHasParsed)
				{
 					m_LogEntryHasParsed = true;
					InputMemoryStream LogEntry_ReadStream(m_LogEntryRaw);
					*LogEntry_ReadStream.ToInputStream() >> m_LogEntry;
				} // if (!m_LogEntryHasParsed)
				return m_LogEntry;
			} // const VariableTable& WhiteboardSharingNewLogEntryAddedS2CEvt::GetLogEntry() const
			Result WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* LogEntryPtr = nullptr;
				protocolCheck(input->ReadLink(LogEntryPtr, ArrayLen));
				m_LogEntryRaw.SetLinkedBuffer(ArrayLen, LogEntryPtr);

				return hr;

			}; // Result WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				WhiteboardSharingNewLogEntryAddedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("LogEntry", "VariableTable", parser.GetLogEntryRaw());

				return hr;

			}; // Result WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhiteboardSharingNewLogEntryAddedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t WhiteboardSharingNewLogEntryAddedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingNewLogEntryAddedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			size_t WhiteboardSharingNewLogEntryAddedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingNewLogEntryAddedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result WhiteboardSharingNewLogEntryAddedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InLogEntry);

				messageBuffer->msgID = WhiteboardSharingNewLogEntryAddedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result WhiteboardSharingNewLogEntryAddedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			Result WhiteboardSharingNewLogEntryAddedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				Result hr;

				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				messageBuffer->msgID = WhiteboardSharingNewLogEntryAddedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInLogEntry));
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result WhiteboardSharingNewLogEntryAddedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result WhiteboardSharingNewLogEntryAddedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhiteboardSharingNewLogEntryAddedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::WhiteboardSharingNewLogEntryAdded, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, LogEntry:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetLogEntry()); 
				return ResultCode::SUCCESS;
			}; // Result WhiteboardSharingNewLogEntryAddedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: WhiteboardSharing new log entry has been removed
			Result WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_LogEntryID);

				return hr;

			}; // Result WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				WhiteboardSharingNewLogEntryRemovedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("LogEntryID", "LogEntryID", parser.GetLogEntryID());

				return hr;

			}; // Result WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhiteboardSharingNewLogEntryRemovedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t WhiteboardSharingNewLogEntryRemovedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InLogEntryID)
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingNewLogEntryRemovedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )


			Result WhiteboardSharingNewLogEntryRemovedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InLogEntryID)
				);

				messageBuffer->msgID = WhiteboardSharingNewLogEntryRemovedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLogEntryID);

				return hr;
			}; // Result WhiteboardSharingNewLogEntryRemovedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )

			Result WhiteboardSharingNewLogEntryRemovedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhiteboardSharingNewLogEntryRemovedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::WhiteboardSharingNewLogEntryRemoved, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, LogEntryID:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetLogEntryID()); 
				return ResultCode::SUCCESS;
			}; // Result WhiteboardSharingNewLogEntryRemovedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: WhiteboardSharing new log entry has been updated
			const VariableTable& WhiteboardSharingNewLogEntryUpdatedS2CEvt::GetLogEntry() const
			{
 				if (!m_LogEntryHasParsed)
				{
 					m_LogEntryHasParsed = true;
					InputMemoryStream LogEntry_ReadStream(m_LogEntryRaw);
					*LogEntry_ReadStream.ToInputStream() >> m_LogEntry;
				} // if (!m_LogEntryHasParsed)
				return m_LogEntry;
			} // const VariableTable& WhiteboardSharingNewLogEntryUpdatedS2CEvt::GetLogEntry() const
			Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* LogEntryPtr = nullptr;
				protocolCheck(input->ReadLink(LogEntryPtr, ArrayLen));
				m_LogEntryRaw.SetLinkedBuffer(ArrayLen, LogEntryPtr);

				return hr;

			}; // Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				WhiteboardSharingNewLogEntryUpdatedS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("LogEntry", "VariableTable", parser.GetLogEntryRaw());

				return hr;

			}; // Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) WhiteboardSharingNewLogEntryUpdatedS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t WhiteboardSharingNewLogEntryUpdatedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingNewLogEntryUpdatedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			size_t WhiteboardSharingNewLogEntryUpdatedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				return __uiMessageSize;
			}; // size_t WhiteboardSharingNewLogEntryUpdatedS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InPlayerID, InLogEntry);

				messageBuffer->msgID = WhiteboardSharingNewLogEntryUpdatedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry )

			Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
			{
 				Result hr;

				uint16_t serializedSizeOfInLogEntry = static_cast<uint16_t>(SerializedSizeOf(InLogEntry)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInLogEntry
				);

				messageBuffer->msgID = WhiteboardSharingNewLogEntryUpdatedS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInLogEntry));
				protocolCheck(*output << InLogEntry);

				return hr;
			}; // Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )

			Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				WhiteboardSharingNewLogEntryUpdatedS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::WhiteboardSharingNewLogEntryUpdated, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, LogEntry:{4}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetLogEntry()); 
				return ResultCode::SUCCESS;
			}; // Result WhiteboardSharingNewLogEntryUpdatedS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Occupy map object
			Result OccupyMapObjectCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);
				protocolCheck(*input >> m_UsageId);

				return hr;

			}; // Result OccupyMapObjectCmd::ParseMessage(const MessageHeader* pHeader)

			Result OccupyMapObjectCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				OccupyMapObjectCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());
				variableBuilder.SetVariable("UsageId", parser.GetUsageId());

				return hr;

			}; // Result OccupyMapObjectCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result OccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) OccupyMapObjectCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result OccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t OccupyMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ SerializedSizeOf(InUsageId)
				);

				return __uiMessageSize;
			}; // size_t OccupyMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )


			Result OccupyMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ SerializedSizeOf(InUsageId)
				);

				messageBuffer->msgID = OccupyMapObjectCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(*output << InUsageId);

				return hr;
			}; // Result OccupyMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )

			Result OccupyMapObjectCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				OccupyMapObjectCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::OccupyMapObject, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MapObjectId:{5}, UsageId:{6}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId(), parser.GetUsageId()); 
				return ResultCode::SUCCESS;
			}; // Result OccupyMapObjectCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result OccupyMapObjectRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);

				return hr;

			}; // Result OccupyMapObjectRes::ParseMessage(const MessageHeader* pHeader)

			Result OccupyMapObjectRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				OccupyMapObjectRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());

				return hr;

			}; // Result OccupyMapObjectRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result OccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) OccupyMapObjectRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result OccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t OccupyMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				return __uiMessageSize;
			}; // size_t OccupyMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )


			Result OccupyMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				messageBuffer->msgID = OccupyMapObjectRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);

				return hr;
			}; // Result OccupyMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )

			Result OccupyMapObjectRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				OccupyMapObjectRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::OccupyMapObject, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, MapObjectId:{6}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId()); 
				return ResultCode::SUCCESS;
			}; // Result OccupyMapObjectRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Unoccupy map object
			Result UnoccupyMapObjectCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);

				return hr;

			}; // Result UnoccupyMapObjectCmd::ParseMessage(const MessageHeader* pHeader)

			Result UnoccupyMapObjectCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UnoccupyMapObjectCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());

				return hr;

			}; // Result UnoccupyMapObjectCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UnoccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnoccupyMapObjectCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnoccupyMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t UnoccupyMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				return __uiMessageSize;
			}; // size_t UnoccupyMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )


			Result UnoccupyMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				messageBuffer->msgID = UnoccupyMapObjectCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);

				return hr;
			}; // Result UnoccupyMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )

			Result UnoccupyMapObjectCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UnoccupyMapObjectCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::UnoccupyMapObject, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MapObjectId:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId()); 
				return ResultCode::SUCCESS;
			}; // Result UnoccupyMapObjectCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result UnoccupyMapObjectRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_MapObjectId);

				return hr;

			}; // Result UnoccupyMapObjectRes::ParseMessage(const MessageHeader* pHeader)

			Result UnoccupyMapObjectRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UnoccupyMapObjectRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());

				return hr;

			}; // Result UnoccupyMapObjectRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UnoccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) UnoccupyMapObjectRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UnoccupyMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t UnoccupyMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				return __uiMessageSize;
			}; // size_t UnoccupyMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )


			Result UnoccupyMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
				);

				messageBuffer->msgID = UnoccupyMapObjectRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);

				return hr;
			}; // Result UnoccupyMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )

			Result UnoccupyMapObjectRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UnoccupyMapObjectRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::UnoccupyMapObject, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, MapObjectId:{6}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId()); 
				return ResultCode::SUCCESS;
			}; // Result UnoccupyMapObjectRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Use map object
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
			Result UseMapObjectCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result UseMapObjectCmd::ParseMessage(const MessageHeader* pHeader)

			Result UseMapObjectCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UseMapObjectCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());
				variableBuilder.SetVariableArray("UseParameters", "VariableTable", parser.GetUseParametersRaw());

				return hr;

			}; // Result UseMapObjectCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UseMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) UseMapObjectCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UseMapObjectCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t UseMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters )
			{
 				uint16_t serializedSizeOfInUseParameters = static_cast<uint16_t>(SerializedSizeOf(InUseParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ serializedSizeOfInUseParameters
				);

				return __uiMessageSize;
			}; // size_t UseMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters )

			size_t UseMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
			{
 				uint16_t serializedSizeOfInUseParameters = static_cast<uint16_t>(SerializedSizeOf(InUseParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ sizeof(uint16_t)
					+ serializedSizeOfInUseParameters
				);

				return __uiMessageSize;
			}; // size_t UseMapObjectCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )

			Result UseMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUseParameters);

				messageBuffer->msgID = UseMapObjectCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(*output << InUseParameters);

				return hr;
			}; // Result UseMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters )

			Result UseMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
			{
 				Result hr;

				uint16_t serializedSizeOfInUseParameters = static_cast<uint16_t>(SerializedSizeOf(InUseParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ sizeof(uint16_t)
					+ serializedSizeOfInUseParameters
				);

				messageBuffer->msgID = UseMapObjectCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(output->Write(serializedSizeOfInUseParameters));
				protocolCheck(*output << InUseParameters);

				return hr;
			}; // Result UseMapObjectCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )

			Result UseMapObjectCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UseMapObjectCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::UseMapObject, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MapObjectId:{5}, UseParameters:{6}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId(), parser.GetUseParameters()); 
				return ResultCode::SUCCESS;
			}; // Result UseMapObjectCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

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
			Result UseMapObjectRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result UseMapObjectRes::ParseMessage(const MessageHeader* pHeader)

			Result UseMapObjectRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				UseMapObjectRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MapObjectId", parser.GetMapObjectId());
				variableBuilder.SetVariableArray("ResultAttributes", "VariableTable", parser.GetResultAttributesRaw());

				return hr;

			}; // Result UseMapObjectRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result UseMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) UseMapObjectRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result UseMapObjectRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t UseMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes )
			{
 				uint16_t serializedSizeOfInResultAttributes = static_cast<uint16_t>(SerializedSizeOf(InResultAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ serializedSizeOfInResultAttributes
				);

				return __uiMessageSize;
			}; // size_t UseMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes )

			size_t UseMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
			{
 				uint16_t serializedSizeOfInResultAttributes = static_cast<uint16_t>(SerializedSizeOf(InResultAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResultAttributes
				);

				return __uiMessageSize;
			}; // size_t UseMapObjectRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )

			Result UseMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId, InResultAttributes);

				messageBuffer->msgID = UseMapObjectRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(*output << InResultAttributes);

				return hr;
			}; // Result UseMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InResultAttributes )

			Result UseMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
			{
 				Result hr;

				uint16_t serializedSizeOfInResultAttributes = static_cast<uint16_t>(SerializedSizeOf(InResultAttributes)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMapObjectId)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResultAttributes
				);

				messageBuffer->msgID = UseMapObjectRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMapObjectId);
				protocolCheck(output->Write(serializedSizeOfInResultAttributes));
				protocolCheck(*output << InResultAttributes);

				return hr;
			}; // Result UseMapObjectRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )

			Result UseMapObjectRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				UseMapObjectRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::UseMapObject, {0}:{1} , TransactionID:{2}, Result:{3:X8}, PlayInstanceUID:{4}, PlayerID:{5}, MapObjectId:{6}, ResultAttributes:{7}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMapObjectId(), parser.GetResultAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result UseMapObjectRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Send zone chatting
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
			Result ZoneChatCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result ZoneChatCmd::ParseMessage(const MessageHeader* pHeader)

			Result ZoneChatCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ZoneChatCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("MessageType", parser.GetMessageType());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ZoneChatCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ZoneChatCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) ZoneChatCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ZoneChatCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t ZoneChatCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMessageType)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ZoneChatCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			size_t ZoneChatCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMessageType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ZoneChatCmd::CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ZoneChatCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType, InChatMetaData, InChatMessage);

				messageBuffer->msgID = ZoneChatCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMessageType);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // Result ZoneChatCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			Result ZoneChatCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				Result hr;

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InMessageType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				messageBuffer->msgID = ZoneChatCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InMessageType);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // Result ZoneChatCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ZoneChatCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ZoneChatCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::ZoneChat, {0}:{1} , TransactionID:{2}, PlayInstanceUID:{3}, PlayerID:{4}, MessageType:{5}, ChatMetaData:{6}, ChatMessage:{7,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetMessageType(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ZoneChatCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result ZoneChatRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result ZoneChatRes::ParseMessage(const MessageHeader* pHeader)

			Result ZoneChatRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ZoneChatRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result ZoneChatRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ZoneChatRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) ZoneChatRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ZoneChatRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t ZoneChatRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t ZoneChatRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result ZoneChatRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = ZoneChatRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result ZoneChatRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result ZoneChatRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ZoneChatRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::ZoneChat, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result ZoneChatRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Player state change
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
			Result ZoneChatS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result ZoneChatS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result ZoneChatS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				ZoneChatS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("SenderID", parser.GetSenderID());
				variableBuilder.SetVariable("MessageType", parser.GetMessageType());
				variableBuilder.SetVariableArray("ChatMetaData", "VariableTable", parser.GetChatMetaDataRaw());
				variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());

				return hr;

			}; // Result ZoneChatS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result ZoneChatS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) ZoneChatS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result ZoneChatS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t ZoneChatS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InMessageType)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ZoneChatS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			size_t ZoneChatS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InMessageType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				return __uiMessageSize;
			}; // size_t ZoneChatS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ZoneChatS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InPlayInstanceUID, InSenderID, InMessageType, InChatMetaData, InChatMessage);

				messageBuffer->msgID = ZoneChatS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InMessageType);
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // Result ZoneChatS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage )

			Result ZoneChatS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
			{
 				Result hr;

				uint16_t serializedSizeOfInChatMetaData = static_cast<uint16_t>(SerializedSizeOf(InChatMetaData)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InSenderID)
					+ SerializedSizeOf(InMessageType)
					+ sizeof(uint16_t)
					+ serializedSizeOfInChatMetaData
					+ SerializedSizeOf(InChatMessage)
				);

				messageBuffer->msgID = ZoneChatS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InSenderID);
				protocolCheck(*output << InMessageType);
				protocolCheck(output->Write(serializedSizeOfInChatMetaData));
				protocolCheck(*output << InChatMetaData);
				protocolCheck(*output << InChatMessage);

				return hr;
			}; // Result ZoneChatS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )

			Result ZoneChatS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				ZoneChatS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::ZoneChat, {0}:{1} , PlayInstanceUID:{2}, SenderID:{3}, MessageType:{4}, ChatMetaData:{5}, ChatMessage:{6,60}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetSenderID(), parser.GetMessageType(), parser.GetChatMetaData(), parser.GetChatMessage()); 
				return ResultCode::SUCCESS;
			}; // Result ZoneChatS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Effect modifier initial sync
			Result LevelUpS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_CurrentExp);
				protocolCheck(*input >> m_CurrentLevel);

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result LevelUpS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				LevelUpS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("CurrentExp", parser.GetCurrentExp());
				variableBuilder.SetVariable("CurrentLevel", parser.GetCurrentLevel());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) LevelUpS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result LevelUpS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t LevelUpS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCurrentExp)
					+ SerializedSizeOf(InCurrentLevel)
				);

				return __uiMessageSize;
			}; // size_t LevelUpS2CEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )


			Result LevelUpS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InCurrentExp)
					+ SerializedSizeOf(InCurrentLevel)
				);

				messageBuffer->msgID = LevelUpS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InCurrentExp);
				protocolCheck(*output << InCurrentLevel);

				return hr;
			}; // Result LevelUpS2CEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )

			Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				LevelUpS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::LevelUp, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, CurrentExp:{4}, CurrentLevel:{5}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetCurrentExp(), parser.GetCurrentLevel()); 
				return ResultCode::SUCCESS;
			}; // Result LevelUpS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: To call general functionality
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
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
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

			}; // Result CallFunctionCmd::ParseMessage(const MessageHeader* pHeader)

			Result CallFunctionCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CallFunctionCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("FunctionName", parser.GetFunctionName());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariableArray("Parameters", "VariableTable", parser.GetParametersRaw());

				return hr;

			}; // Result CallFunctionCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CallFunctionCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CallFunctionCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CallFunctionCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t CallFunctionCmd::CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters )
			{
 				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ SerializedSizeOf(InPlayerID)
					+ serializedSizeOfInParameters
				);

				return __uiMessageSize;
			}; // size_t CallFunctionCmd::CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters )

			size_t CallFunctionCmd::CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
			{
 				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
				);

				return __uiMessageSize;
			}; // size_t CallFunctionCmd::CalculateMessageSize( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )

			Result CallFunctionCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InFunctionName, InPlayerID, InParameters);

				messageBuffer->msgID = CallFunctionCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFunctionName);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InParameters);

				return hr;
			}; // Result CallFunctionCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters )

			Result CallFunctionCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
			{
 				Result hr;

				uint16_t serializedSizeOfInParameters = static_cast<uint16_t>(SerializedSizeOf(InParameters)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InFunctionName)
					+ SerializedSizeOf(InPlayerID)
					+ sizeof(uint16_t)
					+ serializedSizeOfInParameters
				);

				messageBuffer->msgID = CallFunctionCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InFunctionName);
				protocolCheck(*output << InPlayerID);
				protocolCheck(output->Write(serializedSizeOfInParameters));
				protocolCheck(*output << InParameters);

				return hr;
			}; // Result CallFunctionCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )

			Result CallFunctionCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CallFunctionCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CallFunction, {0}:{1} , TransactionID:{2}, FunctionName:{3}, PlayerID:{4}, Parameters:{5}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetFunctionName(), parser.GetPlayerID(), parser.GetParameters()); 
				return ResultCode::SUCCESS;
			}; // Result CallFunctionCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

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
 				Result hr;


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
 				Result hr;


				CallFunctionRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariableArray("Results", "VariableTable", parser.GetResultsRaw());

				return hr;

			}; // Result CallFunctionRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CallFunctionRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CallFunctionRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CallFunctionRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )

			size_t CallFunctionRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )
			{
 				uint16_t serializedSizeOfInResults = static_cast<uint16_t>(SerializedSizeOf(InResults)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ serializedSizeOfInResults
				);

				return __uiMessageSize;
			}; // size_t CallFunctionRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )

			size_t CallFunctionRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )
			{
 				uint16_t serializedSizeOfInResults = static_cast<uint16_t>(SerializedSizeOf(InResults)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResults
				);

				return __uiMessageSize;
			}; // size_t CallFunctionRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )

			Result CallFunctionRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )
			{
 				Result hr;

				uint __uiMessageSize = (uint)CalculateMessageSize(InTransactionID, InResult, InResults);

				messageBuffer->msgID = CallFunctionRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InResults);

				return hr;
			}; // Result CallFunctionRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InResults )

			Result CallFunctionRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )
			{
 				Result hr;

				uint16_t serializedSizeOfInResults = static_cast<uint16_t>(SerializedSizeOf(InResults)); 
				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ sizeof(uint16_t)
					+ serializedSizeOfInResults
				);

				messageBuffer->msgID = CallFunctionRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(output->Write(serializedSizeOfInResults));
				protocolCheck(*output << InResults);

				return hr;
			}; // Result CallFunctionRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )

			Result CallFunctionRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CallFunctionRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CallFunction, {0}:{1} , TransactionID:{2}, Result:{3:X8}, Results:{4}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetResults()); 
				return ResultCode::SUCCESS;
			}; // Result CallFunctionRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// C2S: Send coded voice data to server
			Result SendVoiceDataC2SEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_PlayInstanceUID);
				protocolCheck(*input >> m_PlayerID);
				protocolCheck(*input >> m_FrameIndex);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* VoiceDataPtr = nullptr;
				protocolCheck(input->ReadLink(VoiceDataPtr, ArrayLen));
				m_VoiceData.SetLinkedBuffer(ArrayLen, VoiceDataPtr);

				return hr;

			}; // Result SendVoiceDataC2SEvt::ParseMessage(const MessageHeader* pHeader)

			Result SendVoiceDataC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				SendVoiceDataC2SEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("PlayInstanceUID", parser.GetPlayInstanceUID());
				variableBuilder.SetVariable("PlayerID", parser.GetPlayerID());
				variableBuilder.SetVariable("FrameIndex", parser.GetFrameIndex());
				variableBuilder.SetVariable("VoiceData", parser.GetVoiceData());

				return hr;

			}; // Result SendVoiceDataC2SEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result SendVoiceDataC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) SendVoiceDataC2SEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result SendVoiceDataC2SEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t SendVoiceDataC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InFrameIndex)
					+ SerializedSizeOf(InVoiceData)
				);

				return __uiMessageSize;
			}; // size_t SendVoiceDataC2SEvt::CalculateMessageSize( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )


			Result SendVoiceDataC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InPlayInstanceUID)
					+ SerializedSizeOf(InPlayerID)
					+ SerializedSizeOf(InFrameIndex)
					+ SerializedSizeOf(InVoiceData)
				);

				messageBuffer->msgID = SendVoiceDataC2SEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InPlayInstanceUID);
				protocolCheck(*output << InPlayerID);
				protocolCheck(*output << InFrameIndex);
				protocolCheck(*output << InVoiceData);

				return hr;
			}; // Result SendVoiceDataC2SEvt::Create( MessageHeader* messageBuffer, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )

			Result SendVoiceDataC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				SendVoiceDataC2SEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug6, "PlayInstance::SendVoiceData, {0}:{1} , PlayInstanceUID:{2}, PlayerID:{3}, FrameIndex:{4}, VoiceData:{5,30}",
						prefix, pHeader->Length, parser.GetPlayInstanceUID(), parser.GetPlayerID(), parser.GetFrameIndex(), parser.GetVoiceData()); 
				return ResultCode::SUCCESS;
			}; // Result SendVoiceDataC2SEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// S2C: Voice data
			Result VoiceDataS2CEvt::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_ActorID);
				protocolCheck(*input >> m_FrameIndex);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* VoiceDataPtr = nullptr;
				protocolCheck(input->ReadLink(VoiceDataPtr, ArrayLen));
				m_VoiceData.SetLinkedBuffer(ArrayLen, VoiceDataPtr);

				return hr;

			}; // Result VoiceDataS2CEvt::ParseMessage(const MessageHeader* pHeader)

			Result VoiceDataS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				VoiceDataS2CEvt parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("ActorID", parser.GetActorID());
				variableBuilder.SetVariable("FrameIndex", parser.GetFrameIndex());
				variableBuilder.SetVariable("VoiceData", parser.GetVoiceData());

				return hr;

			}; // Result VoiceDataS2CEvt::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result VoiceDataS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) VoiceDataS2CEvt(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result VoiceDataS2CEvt::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t VoiceDataS2CEvt::CalculateMessageSize( const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InActorID)
					+ SerializedSizeOf(InFrameIndex)
					+ SerializedSizeOf(InVoiceData)
				);

				return __uiMessageSize;
			}; // size_t VoiceDataS2CEvt::CalculateMessageSize( const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )


			Result VoiceDataS2CEvt::Create( MessageHeader* messageBuffer, const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InActorID)
					+ SerializedSizeOf(InFrameIndex)
					+ SerializedSizeOf(InVoiceData)
				);

				messageBuffer->msgID = VoiceDataS2CEvt::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InActorID);
				protocolCheck(*output << InFrameIndex);
				protocolCheck(*output << InVoiceData);

				return hr;
			}; // Result VoiceDataS2CEvt::Create( MessageHeader* messageBuffer, const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )

			Result VoiceDataS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				VoiceDataS2CEvt parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug6, "PlayInstance::VoiceData, {0}:{1} , ActorID:{2}, FrameIndex:{3}, VoiceData:{4,30}",
						prefix, pHeader->Length, parser.GetActorID(), parser.GetFrameIndex(), parser.GetVoiceData()); 
				return ResultCode::SUCCESS;
			}; // Result VoiceDataS2CEvt::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Create stream instance
			Result CreateStreamCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result CreateStreamCmd::ParseMessage(const MessageHeader* pHeader)

			Result CreateStreamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreateStreamCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result CreateStreamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateStreamCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CreateStreamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				return __uiMessageSize;
			}; // size_t CreateStreamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )


			Result CreateStreamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				messageBuffer->msgID = CreateStreamCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // Result CreateStreamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )

			Result CreateStreamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateStreamCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CreateStream, {0}:{1} , TransactionID:{2}, Ticket:{3}, StreamName:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetTicket(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result CreateStreamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result CreateStreamRes::ParseMessage(const MessageHeader* pHeader)
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
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result CreateStreamRes::ParseMessage(const MessageHeader* pHeader)

			Result CreateStreamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				CreateStreamRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result CreateStreamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result CreateStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) CreateStreamRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result CreateStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t CreateStreamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				return __uiMessageSize;
			}; // size_t CreateStreamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )


			Result CreateStreamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				messageBuffer->msgID = CreateStreamRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // Result CreateStreamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )

			Result CreateStreamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				CreateStreamRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::CreateStream, {0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamName:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result CreateStreamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Open stream instance
			Result FindStreamCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result FindStreamCmd::ParseMessage(const MessageHeader* pHeader)

			Result FindStreamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FindStreamCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result FindStreamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindStreamCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindStreamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				return __uiMessageSize;
			}; // size_t FindStreamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )


			Result FindStreamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				messageBuffer->msgID = FindStreamCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // Result FindStreamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )

			Result FindStreamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindStreamCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::FindStream, {0}:{1} , TransactionID:{2}, Ticket:{3}, StreamName:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetTicket(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result FindStreamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result FindStreamRes::ParseMessage(const MessageHeader* pHeader)
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
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result FindStreamRes::ParseMessage(const MessageHeader* pHeader)

			Result FindStreamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				FindStreamRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result FindStreamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result FindStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) FindStreamRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result FindStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t FindStreamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				return __uiMessageSize;
			}; // size_t FindStreamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )


			Result FindStreamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				messageBuffer->msgID = FindStreamRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // Result FindStreamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )

			Result FindStreamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				FindStreamRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::FindStream, {0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamName:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result FindStreamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Delete stream instance
			Result DeleteStreamCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result DeleteStreamCmd::ParseMessage(const MessageHeader* pHeader)

			Result DeleteStreamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DeleteStreamCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result DeleteStreamCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DeleteStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteStreamCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteStreamCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t DeleteStreamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				return __uiMessageSize;
			}; // size_t DeleteStreamCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )


			Result DeleteStreamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
					+ SerializedSizeOf(InStreamName)
				);

				messageBuffer->msgID = DeleteStreamCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // Result DeleteStreamCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )

			Result DeleteStreamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DeleteStreamCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::DeleteStream, {0}:{1} , TransactionID:{2}, Ticket:{3}, StreamName:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetTicket(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteStreamCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result DeleteStreamRes::ParseMessage(const MessageHeader* pHeader)
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
				protocolCheck(input->ReadLink(m_StreamName, ArrayLen));

				return hr;

			}; // Result DeleteStreamRes::ParseMessage(const MessageHeader* pHeader)

			Result DeleteStreamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				DeleteStreamRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamName", parser.GetStreamName());

				return hr;

			}; // Result DeleteStreamRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result DeleteStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) DeleteStreamRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result DeleteStreamRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t DeleteStreamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				return __uiMessageSize;
			}; // size_t DeleteStreamRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )


			Result DeleteStreamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamName)
				);

				messageBuffer->msgID = DeleteStreamRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamName);

				return hr;
			}; // Result DeleteStreamRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )

			Result DeleteStreamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				DeleteStreamRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::DeleteStream, {0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamName:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamName()); 
				return ResultCode::SUCCESS;
			}; // Result DeleteStreamRes::TraceOut(const char* prefix, const MessageHeader* pHeader)

			// Cmd: Get stream list
			Result GetStreamListCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Ticket);

				return hr;

			}; // Result GetStreamListCmd::ParseMessage(const MessageHeader* pHeader)

			Result GetStreamListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetStreamListCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Ticket", parser.GetTicket());

				return hr;

			}; // Result GetStreamListCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetStreamListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetStreamListCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetStreamListCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetStreamListCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
				);

				return __uiMessageSize;
			}; // size_t GetStreamListCmd::CalculateMessageSize( const TransactionID &InTransactionID, const AuthTicket &InTicket )


			Result GetStreamListCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InTicket)
				);

				messageBuffer->msgID = GetStreamListCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InTicket);

				return hr;
			}; // Result GetStreamListCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const AuthTicket &InTicket )

			Result GetStreamListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetStreamListCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::GetStreamList, {0}:{1} , TransactionID:{2}, Ticket:{3}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetTicket()); 
				return ResultCode::SUCCESS;
			}; // Result GetStreamListCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result GetStreamListRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);
				protocolCheck(input->ReadArrayLink(m_StreamNames));

				return hr;

			}; // Result GetStreamListRes::ParseMessage(const MessageHeader* pHeader)

			Result GetStreamListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GetStreamListRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());
				variableBuilder.SetVariable("StreamNames", parser.GetStreamNames());

				return hr;

			}; // Result GetStreamListRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GetStreamListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) GetStreamListRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GetStreamListRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GetStreamListRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamNames)
				);

				return __uiMessageSize;
			}; // size_t GetStreamListRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )


			Result GetStreamListRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
					+ SerializedSizeOf(InStreamNames)
				);

				messageBuffer->msgID = GetStreamListRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);
				protocolCheck(*output << InStreamNames);

				return hr;
			}; // Result GetStreamListRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )

			Result GetStreamListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GetStreamListRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "PlayInstance::GetStreamList, {0}:{1} , TransactionID:{2}, Result:{3:X8}, StreamNames:{4,60}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult(), parser.GetStreamNames()); 
				return ResultCode::SUCCESS;
			}; // Result GetStreamListRes::TraceOut(const char* prefix, const MessageHeader* pHeader)



		}; // namespace PlayInstance
	}; // namespace Message
}; // namespace SF



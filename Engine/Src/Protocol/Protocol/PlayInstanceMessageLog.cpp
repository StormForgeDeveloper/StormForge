﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : PlayInstance Message log implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Protocol/PlayInstanceMessageLog.h"
#include "Protocol/PlayInstance_generated.h"
#ifdef ERROR
#undef ERROR
#endif
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"



namespace SF
{
 	Result PlayInstanceMessageLog::Initialize()
	{
 		Result hr;

		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_JoinPlayInstanceCmd,&JoinPlayInstanceCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_JoinPlayInstanceRes,&JoinPlayInstanceRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_PlayerKickedS2CEvt,&PlayerKickedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_PlayPacketC2SEvt,&PlayPacketC2SEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_NewActorInViewS2CEvt,&NewActorInViewS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_RemoveActorFromViewS2CEvt,&RemoveActorFromViewS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_PlayerMovementC2SEvt,&PlayerMovementC2SEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_ActorMovementS2CEvt,&ActorMovementS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_ActorMovementsS2CEvt,&ActorMovementsS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_PlayerStateChangedS2CEvt,&PlayerStateChangedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_ClientSyncReliableC2SEvt,&ClientSyncReliableC2SEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_ClientSyncC2SEvt,&ClientSyncC2SEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_SetCharacterPublicMessageCmd,&SetCharacterPublicMessageCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_SetCharacterPublicMessageRes,&SetCharacterPublicMessageRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CharacterPrivateDataChangedS2CEvt,&CharacterPrivateDataChangedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CharacterPublicDataChangedS2CEvt,&CharacterPublicDataChangedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_RequestWhiteboardSharingCmd,&RequestWhiteboardSharingCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_RequestWhiteboardSharingRes,&RequestWhiteboardSharingRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_AcceptWhiteboardSharingCmd,&AcceptWhiteboardSharingCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_AcceptWhiteboardSharingRes,&AcceptWhiteboardSharingRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CloseWhiteboardSharingCmd,&CloseWhiteboardSharingCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CloseWhiteboardSharingRes,&CloseWhiteboardSharingRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_AddWhiteboardSharingLogEntryCmd,&AddWhiteboardSharingLogEntryCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_AddWhiteboardSharingLogEntryRes,&AddWhiteboardSharingLogEntryRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_UpdateWhiteboardSharingLogEntryCmd,&UpdateWhiteboardSharingLogEntryCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_UpdateWhiteboardSharingLogEntryRes,&UpdateWhiteboardSharingLogEntryRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_RemoveWhiteboardSharingLogEntryCmd,&RemoveWhiteboardSharingLogEntryCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_RemoveWhiteboardSharingLogEntryRes,&RemoveWhiteboardSharingLogEntryRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_WhiteboardSharingRequestedS2CEvt,&WhiteboardSharingRequestedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_WhiteboardSharingRejectedS2CEvt,&WhiteboardSharingRejectedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_WhiteboardSharingStartedS2CEvt,&WhiteboardSharingStartedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_WhiteboardSharingHasClosedS2CEvt,&WhiteboardSharingHasClosedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_WhiteboardSharingNewLogEntryAddedS2CEvt,&WhiteboardSharingNewLogEntryAddedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_WhiteboardSharingNewLogEntryRemovedS2CEvt,&WhiteboardSharingNewLogEntryRemovedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_WhiteboardSharingNewLogEntryUpdatedS2CEvt,&WhiteboardSharingNewLogEntryUpdatedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_OccupyMapObjectCmd,&OccupyMapObjectCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_OccupyMapObjectRes,&OccupyMapObjectRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_UnoccupyMapObjectCmd,&UnoccupyMapObjectCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_UnoccupyMapObjectRes,&UnoccupyMapObjectRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_UseMapObjectCmd,&UseMapObjectCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_UseMapObjectRes,&UseMapObjectRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_ZoneChatCmd,&ZoneChatCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_ZoneChatRes,&ZoneChatRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_ZoneChatS2CEvt,&ZoneChatS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_LevelUpS2CEvt,&LevelUpS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CallFunctionCmd,&CallFunctionCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CallFunctionRes,&CallFunctionRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_SendVoiceDataC2SEvt,&SendVoiceDataC2SEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_VoiceDataS2CEvt,&VoiceDataS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CreateStreamCmd,&CreateStreamCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_CreateStreamRes,&CreateStreamRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_FindStreamCmd,&FindStreamCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_FindStreamRes,&FindStreamRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_DeleteStreamCmd,&DeleteStreamCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_DeleteStreamRes,&DeleteStreamRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_GetStreamListCmd,&GetStreamListCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::MID_GetStreamListRes,&GetStreamListRes));


		Protocol::LoadFlatSchema("PlayInstance.fbs");

		return hr;
	}; // Result PlayInstanceMessageLog::Initialize()
	Result PlayInstanceMessageLog::JoinPlayInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.JoinPlayInstanceCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:JoinPlayInstanceCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::JoinPlayInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::JoinPlayInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.JoinPlayInstanceRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:JoinPlayInstanceRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::JoinPlayInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::PlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.PlayerKickedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:PlayerKickedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::PlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::PlayPacketC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.PlayPacketC2SEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:PlayPacketC2SEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::PlayPacketC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::NewActorInViewS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.NewActorInViewS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:NewActorInViewS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::NewActorInViewS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::RemoveActorFromViewS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:RemoveActorFromViewS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::RemoveActorFromViewS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::PlayerMovementC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.PlayerMovementC2SEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:PlayerMovementC2SEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::PlayerMovementC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::ActorMovementS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.ActorMovementS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:ActorMovementS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::ActorMovementS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::ActorMovementsS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.ActorMovementsS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:ActorMovementsS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::ActorMovementsS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::PlayerStateChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.PlayerStateChangedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:PlayerStateChangedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::PlayerStateChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::ClientSyncReliableC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.ClientSyncReliableC2SEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:ClientSyncReliableC2SEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::ClientSyncReliableC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::ClientSyncC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.ClientSyncC2SEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:ClientSyncC2SEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::ClientSyncC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::SetCharacterPublicMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.SetCharacterPublicMessageCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:SetCharacterPublicMessageCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::SetCharacterPublicMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::SetCharacterPublicMessageRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.SetCharacterPublicMessageRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:SetCharacterPublicMessageRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::SetCharacterPublicMessageRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CharacterPrivateDataChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CharacterPrivateDataChangedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CharacterPrivateDataChangedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CharacterPrivateDataChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CharacterPublicDataChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CharacterPublicDataChangedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CharacterPublicDataChangedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CharacterPublicDataChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::RequestWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.RequestWhiteboardSharingCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:RequestWhiteboardSharingCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::RequestWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::RequestWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.RequestWhiteboardSharingRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:RequestWhiteboardSharingRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::RequestWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::AcceptWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.AcceptWhiteboardSharingCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:AcceptWhiteboardSharingCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::AcceptWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::AcceptWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.AcceptWhiteboardSharingRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:AcceptWhiteboardSharingRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::AcceptWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CloseWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CloseWhiteboardSharingCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CloseWhiteboardSharingCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CloseWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CloseWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CloseWhiteboardSharingRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CloseWhiteboardSharingRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CloseWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::AddWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:AddWhiteboardSharingLogEntryCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::AddWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::AddWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:AddWhiteboardSharingLogEntryRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::AddWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::UpdateWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:UpdateWhiteboardSharingLogEntryCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::UpdateWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::UpdateWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:UpdateWhiteboardSharingLogEntryRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::UpdateWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::RemoveWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:RemoveWhiteboardSharingLogEntryCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::RemoveWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::RemoveWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:RemoveWhiteboardSharingLogEntryRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::RemoveWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::WhiteboardSharingRequestedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:WhiteboardSharingRequestedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::WhiteboardSharingRequestedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::WhiteboardSharingRejectedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.WhiteboardSharingRejectedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:WhiteboardSharingRejectedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::WhiteboardSharingRejectedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::WhiteboardSharingStartedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.WhiteboardSharingStartedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:WhiteboardSharingStartedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::WhiteboardSharingStartedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::WhiteboardSharingHasClosedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.WhiteboardSharingHasClosedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:WhiteboardSharingHasClosedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::WhiteboardSharingHasClosedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::WhiteboardSharingNewLogEntryAddedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:WhiteboardSharingNewLogEntryAddedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::WhiteboardSharingNewLogEntryAddedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::WhiteboardSharingNewLogEntryRemovedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:WhiteboardSharingNewLogEntryRemovedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::WhiteboardSharingNewLogEntryRemovedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::WhiteboardSharingNewLogEntryUpdatedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:WhiteboardSharingNewLogEntryUpdatedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::WhiteboardSharingNewLogEntryUpdatedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::OccupyMapObjectCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.OccupyMapObjectCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:OccupyMapObjectCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::OccupyMapObjectCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::OccupyMapObjectRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.OccupyMapObjectRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:OccupyMapObjectRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::OccupyMapObjectRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::UnoccupyMapObjectCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.UnoccupyMapObjectCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:UnoccupyMapObjectCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::UnoccupyMapObjectCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::UnoccupyMapObjectRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.UnoccupyMapObjectRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:UnoccupyMapObjectRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::UnoccupyMapObjectRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::UseMapObjectCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.UseMapObjectCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:UseMapObjectCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::UseMapObjectCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::UseMapObjectRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.UseMapObjectRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:UseMapObjectRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::UseMapObjectRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::ZoneChatCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.ZoneChatCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:ZoneChatCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::ZoneChatCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::ZoneChatRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.ZoneChatRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:ZoneChatRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::ZoneChatRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::ZoneChatS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.ZoneChatS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:ZoneChatS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::ZoneChatS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::LevelUpS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.LevelUpS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:LevelUpS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::LevelUpS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CallFunctionCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CallFunctionCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CallFunctionCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CallFunctionCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CallFunctionRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CallFunctionRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CallFunctionRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CallFunctionRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::SendVoiceDataC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.SendVoiceDataC2SEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:SendVoiceDataC2SEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::SendVoiceDataC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::VoiceDataS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.VoiceDataS2CEvt")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:VoiceDataS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::VoiceDataS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CreateStreamCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CreateStreamCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CreateStreamCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CreateStreamCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::CreateStreamRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.CreateStreamRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:CreateStreamRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::CreateStreamRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::FindStreamCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.FindStreamCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:FindStreamCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::FindStreamCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::FindStreamRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.FindStreamRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:FindStreamRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::FindStreamRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::DeleteStreamCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.DeleteStreamCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:DeleteStreamCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::DeleteStreamCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::DeleteStreamRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.DeleteStreamRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:DeleteStreamRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::DeleteStreamRes(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::GetStreamListCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.GetStreamListCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:GetStreamListCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::GetStreamListCmd(const char* prefix, const MessageHeader* messageHeader)
	Result PlayInstanceMessageLog::GetStreamListRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.PlayInstance.GetStreamListRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} PlayInstance:GetStreamListRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result PlayInstanceMessageLog::GetStreamListRes(const char* prefix, const MessageHeader* messageHeader)


}; // namespace SF


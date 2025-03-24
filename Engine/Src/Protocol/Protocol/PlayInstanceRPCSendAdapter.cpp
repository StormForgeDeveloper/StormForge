////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : PlayInstance Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/PlayInstanceRPCSendAdapter.h"
#include "Protocol/PlayInstanceMessageID.h"
#include "PlayInstance_generated.h"



namespace SF
{
 	// Cmd: Player Join request.
	Result PlayInstanceRPCSendAdapter::JoinPlayInstanceCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier, const uint32_t &InCustomZoneDataVersion )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto PlayerIdentifierOffset = SF::Flat::Helper::CreateString(fbb, InPlayerIdentifier);
		SF::Flat::PlayInstance::JoinPlayInstanceCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_player_identifier(PlayerIdentifierOffset);
		_builder.add_custom_zone_data_version(InCustomZoneDataVersion);
		flatbuffers::Offset<SF::Flat::PlayInstance::JoinPlayInstanceCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_JoinPlayInstanceCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::JoinPlayInstanceCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier, const uint32_t &InCustomZoneDataVersion )
	// C2S: Play packet
	Result PlayInstanceRPCSendAdapter::PlayPacketC2SEvt( const GameInstanceUID &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PayloadOffset = SF::Flat::Helper::Createuint8Vector(fbb, InPayload);
		SF::Flat::PlayInstance::PlayPacketC2SEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_sender_endpoint_id(InSenderEndpointID);
		_builder.add_target_endpoint_mask(InTargetEndpointMask);
		_builder.add_payload(PayloadOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::PlayPacketC2SEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_PlayPacketC2SEvt, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::PlayPacketC2SEvt( const GameInstanceUID &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
	// C2S: Player Movement
	Result PlayInstanceRPCSendAdapter::PlayerMovementC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto MovementOffset = SF::Flat::Helper::CreateActorMovement(fbb, InMovement);
		SF::Flat::PlayInstance::PlayerMovementC2SEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_movement(MovementOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::PlayerMovementC2SEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_PlayerMovementC2SEvt, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::PlayerMovementC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement )
	// C2S: Reliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
	Result PlayInstanceRPCSendAdapter::ClientSyncReliableC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto SyncDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InSyncData);
		SF::Flat::PlayInstance::ClientSyncReliableC2SEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_sync_data(SyncDataOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::ClientSyncReliableC2SEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_ClientSyncReliableC2SEvt, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::ClientSyncReliableC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
	Result PlayInstanceRPCSendAdapter::ClientSyncC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto SyncDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InSyncData);
		SF::Flat::PlayInstance::ClientSyncC2SEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_sync_data(SyncDataOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::ClientSyncC2SEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_ClientSyncC2SEvt, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::ClientSyncC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData )
	// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
	Result PlayInstanceRPCSendAdapter::SetCharacterPublicMessageCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto PublicMessageOffset = SF::Flat::Helper::CreateString(fbb, InPublicMessage);
		SF::Flat::PlayInstance::SetCharacterPublicMessageCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_public_message(PublicMessageOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::SetCharacterPublicMessageCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_SetCharacterPublicMessageCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::SetCharacterPublicMessageCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage )
	// Cmd: Request WhiteboardSharing
	Result PlayInstanceRPCSendAdapter::RequestWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto TargetPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InTargetPlayerID);
		auto WhiteboardInfoOffset = SF::Flat::Helper::CreateVariableTable(fbb, InWhiteboardInfo);
		SF::Flat::PlayInstance::RequestWhiteboardSharingCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_target_player_id(TargetPlayerIDOffset);
		_builder.add_whiteboard_info(WhiteboardInfoOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::RequestWhiteboardSharingCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_RequestWhiteboardSharingCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::RequestWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo )
	// Cmd: Accept WhiteboardSharing
	Result PlayInstanceRPCSendAdapter::AcceptWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto RequestedPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InRequestedPlayerID);
		SF::Flat::PlayInstance::AcceptWhiteboardSharingCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_requested_player_id(RequestedPlayerIDOffset);
		_builder.add_answer(InAnswer);
		flatbuffers::Offset<SF::Flat::PlayInstance::AcceptWhiteboardSharingCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_AcceptWhiteboardSharingCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::AcceptWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer )
	// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
	Result PlayInstanceRPCSendAdapter::CloseWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::CloseWhiteboardSharingCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::CloseWhiteboardSharingCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_CloseWhiteboardSharingCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::CloseWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID )
	// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
	Result PlayInstanceRPCSendAdapter::AddWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto LogEntryOffset = SF::Flat::Helper::CreateVariableTable(fbb, InLogEntry);
		SF::Flat::PlayInstance::AddWhiteboardSharingLogEntryCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_log_entry(LogEntryOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::AddWhiteboardSharingLogEntryCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_AddWhiteboardSharingLogEntryCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::AddWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
	Result PlayInstanceRPCSendAdapter::UpdateWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto LogEntryOffset = SF::Flat::Helper::CreateVariableTable(fbb, InLogEntry);
		SF::Flat::PlayInstance::UpdateWhiteboardSharingLogEntryCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_log_entry(LogEntryOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UpdateWhiteboardSharingLogEntryCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_UpdateWhiteboardSharingLogEntryCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::UpdateWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	// Cmd: Update whiteboard log entry
	Result PlayInstanceRPCSendAdapter::RemoveWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::RemoveWhiteboardSharingLogEntryCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_log_entry_id(InLogEntryID);
		flatbuffers::Offset<SF::Flat::PlayInstance::RemoveWhiteboardSharingLogEntryCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_RemoveWhiteboardSharingLogEntryCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::RemoveWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
	// Cmd: Occupy map object
	Result PlayInstanceRPCSendAdapter::OccupyMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::OccupyMapObjectCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_map_object_id(InMapObjectId);
		_builder.add_usage_id(InUsageId);
		flatbuffers::Offset<SF::Flat::PlayInstance::OccupyMapObjectCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_OccupyMapObjectCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::OccupyMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId )
	// Cmd: Unoccupy map object
	Result PlayInstanceRPCSendAdapter::UnoccupyMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::UnoccupyMapObjectCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_map_object_id(InMapObjectId);
		flatbuffers::Offset<SF::Flat::PlayInstance::UnoccupyMapObjectCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_UnoccupyMapObjectCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::UnoccupyMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Use map object
	Result PlayInstanceRPCSendAdapter::UseMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto UseParametersOffset = SF::Flat::Helper::CreateVariableTable(fbb, InUseParameters);
		SF::Flat::PlayInstance::UseMapObjectCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_map_object_id(InMapObjectId);
		_builder.add_use_parameters(UseParametersOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UseMapObjectCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_UseMapObjectCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::UseMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters )
	// Cmd: Send zone chatting
	Result PlayInstanceRPCSendAdapter::ZoneChatCmd( const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto ChatMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InChatMetaData);
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::PlayInstance::ZoneChatCmdBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_message_type(InMessageType);
		_builder.add_chat_meta_data(ChatMetaDataOffset);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::ZoneChatCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_ZoneChatCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::ZoneChatCmd( const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: To call general functionality
	Result PlayInstanceRPCSendAdapter::CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto ParametersOffset = SF::Flat::Helper::CreateVariableTable(fbb, InParameters);
		SF::Flat::PlayInstance::CallFunctionCmdBuilder _builder(fbb);
		_builder.add_function_name(InFunctionName);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_parameters(ParametersOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::CallFunctionCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_CallFunctionCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters )
	// C2S: Send coded voice data to server
	Result PlayInstanceRPCSendAdapter::SendVoiceDataC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto VoiceDataOffset = SF::Flat::Helper::Createuint8Vector(fbb, InVoiceData);
		SF::Flat::PlayInstance::SendVoiceDataC2SEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_frame_index(InFrameIndex);
		_builder.add_voice_data(VoiceDataOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::SendVoiceDataC2SEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_SendVoiceDataC2SEvt, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::SendVoiceDataC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
	// Cmd: UGC zone edit command
	Result PlayInstanceRPCSendAdapter::UGCEditAddCmd( const TransactionID &InTransactionID, const StringCrc32 &InEntityType, const uint32_t &InTableId, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PositionOffset = SF::Flat::Helper::CreateVector4(fbb, InPosition);
		auto RotationOffset = SF::Flat::Helper::CreateVector4(fbb, InRotation);
		auto ScaleOffset = SF::Flat::Helper::CreateVector4(fbb, InScale);
		SF::Flat::PlayInstance::UGCEditAddCmdBuilder _builder(fbb);
		_builder.add_entity_type(InEntityType);
		_builder.add_table_id(InTableId);
		_builder.add_position(PositionOffset);
		_builder.add_rotation(RotationOffset);
		_builder.add_scale(ScaleOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditAddCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_UGCEditAddCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::UGCEditAddCmd( const TransactionID &InTransactionID, const StringCrc32 &InEntityType, const uint32_t &InTableId, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale )
	// Cmd: UGC zone edit command
	Result PlayInstanceRPCSendAdapter::UGCEditMoveCmd( const TransactionID &InTransactionID, const uint32_t &InInstanceId, const StringCrc32 &InEntityType, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PositionOffset = SF::Flat::Helper::CreateVector4(fbb, InPosition);
		auto RotationOffset = SF::Flat::Helper::CreateVector4(fbb, InRotation);
		auto ScaleOffset = SF::Flat::Helper::CreateVector4(fbb, InScale);
		SF::Flat::PlayInstance::UGCEditMoveCmdBuilder _builder(fbb);
		_builder.add_instance_id(InInstanceId);
		_builder.add_entity_type(InEntityType);
		_builder.add_position(PositionOffset);
		_builder.add_rotation(RotationOffset);
		_builder.add_scale(ScaleOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditMoveCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_UGCEditMoveCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::UGCEditMoveCmd( const TransactionID &InTransactionID, const uint32_t &InInstanceId, const StringCrc32 &InEntityType, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale )
	// Cmd: UGC zone edit command
	Result PlayInstanceRPCSendAdapter::UGCEditDeleteCmd( const TransactionID &InTransactionID, const uint32_t &InInstanceId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::UGCEditDeleteCmdBuilder _builder(fbb);
		_builder.add_instance_id(InInstanceId);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditDeleteCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_UGCEditDeleteCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::UGCEditDeleteCmd( const TransactionID &InTransactionID, const uint32_t &InInstanceId )
	// Cmd: UGC zone edit command
	Result PlayInstanceRPCSendAdapter::UGCEditClaimBackCmd( const TransactionID &InTransactionID, const uint32_t &InInstanceId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::UGCEditClaimBackCmdBuilder _builder(fbb);
		_builder.add_instance_id(InInstanceId);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditClaimBackCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_UGCEditClaimBackCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::UGCEditClaimBackCmd( const TransactionID &InTransactionID, const uint32_t &InInstanceId )
	// Cmd: Create stream instance
	Result PlayInstanceRPCSendAdapter::CreateStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto StreamNameOffset = SF::Flat::Helper::CreateString(fbb, InStreamName);
		SF::Flat::PlayInstance::CreateStreamCmdBuilder _builder(fbb);
		_builder.add_ticket(InTicket);
		_builder.add_stream_name(StreamNameOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::CreateStreamCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_CreateStreamCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::CreateStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Open stream instance
	Result PlayInstanceRPCSendAdapter::FindStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto StreamNameOffset = SF::Flat::Helper::CreateString(fbb, InStreamName);
		SF::Flat::PlayInstance::FindStreamCmdBuilder _builder(fbb);
		_builder.add_ticket(InTicket);
		_builder.add_stream_name(StreamNameOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::FindStreamCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_FindStreamCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::FindStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Delete stream instance
	Result PlayInstanceRPCSendAdapter::DeleteStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto StreamNameOffset = SF::Flat::Helper::CreateString(fbb, InStreamName);
		SF::Flat::PlayInstance::DeleteStreamCmdBuilder _builder(fbb);
		_builder.add_ticket(InTicket);
		_builder.add_stream_name(StreamNameOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::DeleteStreamCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_DeleteStreamCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::DeleteStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
	// Cmd: Get stream list
	Result PlayInstanceRPCSendAdapter::GetStreamListCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::GetStreamListCmdBuilder _builder(fbb);
		_builder.add_ticket(InTicket);
		flatbuffers::Offset<SF::Flat::PlayInstance::GetStreamListCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::PlayInstance::MID_GetStreamListCmd, fbb));


		return hr;
	}; // Result PlayInstanceRPCSendAdapter::GetStreamListCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket )


	// Cmd: Player Join request.
	Result PlayInstanceSvrRPCSendAdapter::JoinPlayInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		auto CharacterPrivateDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InCharacterPrivateData);
		auto MovementOffset = SF::Flat::Helper::CreateActorMovement(fbb, InMovement);
		SF::Flat::PlayInstance::JoinPlayInstanceResBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_character_id(CharacterIDOffset);
		_builder.add_character_private_data(CharacterPrivateDataOffset);
		_builder.add_movement(MovementOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::JoinPlayInstanceRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_JoinPlayInstanceRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::JoinPlayInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement )
	// S2C: Player kicked event. this event will be broadcasted when a player kicked.
	Result PlayInstanceSvrRPCSendAdapter::PlayerKickedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto KickedPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InKickedPlayerID);
		SF::Flat::PlayInstance::PlayerKickedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_kicked_player_id(KickedPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::PlayerKickedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_PlayerKickedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::PlayerKickedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InKickedPlayerID )
	// S2C: New actor in get view
	Result PlayInstanceSvrRPCSendAdapter::NewActorInViewS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto PlayerPlatformIdOffset = SF::Flat::Helper::CreatePlayerPlatformID(fbb, InPlayerPlatformId);
		auto PublicDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InPublicData);
		auto EquipDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InEquipData);
		auto MovementOffset = SF::Flat::Helper::CreateActorMovement(fbb, InMovement);
		auto StateValuesOffset = SF::Flat::Helper::CreateVariableTable(fbb, InStateValues);
		SF::Flat::PlayInstance::NewActorInViewS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_player_platform_id(PlayerPlatformIdOffset);
		_builder.add_public_data(PublicDataOffset);
		_builder.add_equip_data(EquipDataOffset);
		_builder.add_movement(MovementOffset);
		_builder.add_state(InState);
		_builder.add_state_values(StateValuesOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::NewActorInViewS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_NewActorInViewS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::NewActorInViewS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues )
	// S2C: Remove actor from view
	Result PlayInstanceSvrRPCSendAdapter::RemoveActorFromViewS2CEvt( const GameInstanceUID &InPlayInstanceUID, const uint32_t &InActorID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		SF::Flat::PlayInstance::RemoveActorFromViewS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_actor_id(InActorID);
		flatbuffers::Offset<SF::Flat::PlayInstance::RemoveActorFromViewS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_RemoveActorFromViewS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::RemoveActorFromViewS2CEvt( const GameInstanceUID &InPlayInstanceUID, const uint32_t &InActorID )
	// S2C: Player Movement
	Result PlayInstanceSvrRPCSendAdapter::ActorMovementS2CEvt( const GameInstanceUID &InPlayInstanceUID, const ActorMovement &InMovement )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto MovementOffset = SF::Flat::Helper::CreateActorMovement(fbb, InMovement);
		SF::Flat::PlayInstance::ActorMovementS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_movement(MovementOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::ActorMovementS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_ActorMovementS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::ActorMovementS2CEvt( const GameInstanceUID &InPlayInstanceUID, const ActorMovement &InMovement )
	// S2C: Player Movement
	Result PlayInstanceSvrRPCSendAdapter::ActorMovementsS2CEvt( const GameInstanceUID &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto MovementOffset = SF::Flat::Helper::CreateActorMovementVector(fbb, InMovement);
		SF::Flat::PlayInstance::ActorMovementsS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_movement(MovementOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::ActorMovementsS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_ActorMovementsS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::ActorMovementsS2CEvt( const GameInstanceUID &InPlayInstanceUID, const Array<ActorMovement>& InMovement )
	// S2C: Player state change
	Result PlayInstanceSvrRPCSendAdapter::PlayerStateChangedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto PositionOffset = SF::Flat::Helper::CreateVector4(fbb, InPosition);
		auto StateValuesOffset = SF::Flat::Helper::CreateVariableTable(fbb, InStateValues);
		SF::Flat::PlayInstance::PlayerStateChangedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_state(InState);
		_builder.add_move_frame(InMoveFrame);
		_builder.add_position(PositionOffset);
		_builder.add_state_values(StateValuesOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::PlayerStateChangedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_PlayerStateChangedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::PlayerStateChangedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues )
	// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
	Result PlayInstanceSvrRPCSendAdapter::SetCharacterPublicMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::SetCharacterPublicMessageResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::SetCharacterPublicMessageRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_SetCharacterPublicMessageRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::SetCharacterPublicMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Character's private data has changed
	Result PlayInstanceSvrRPCSendAdapter::CharacterPrivateDataChangedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InPrivateData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		auto PrivateDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InPrivateData);
		SF::Flat::PlayInstance::CharacterPrivateDataChangedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_character_id(CharacterIDOffset);
		_builder.add_private_data(PrivateDataOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::CharacterPrivateDataChangedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_CharacterPrivateDataChangedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::CharacterPrivateDataChangedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InPrivateData )
	// S2C: Player public data has been changed
	Result PlayInstanceSvrRPCSendAdapter::CharacterPublicDataChangedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto PublicDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InPublicData);
		SF::Flat::PlayInstance::CharacterPublicDataChangedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_public_data(PublicDataOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::CharacterPublicDataChangedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_CharacterPublicDataChangedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::CharacterPublicDataChangedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData )
	// Cmd: Request WhiteboardSharing
	Result PlayInstanceSvrRPCSendAdapter::RequestWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::RequestWhiteboardSharingResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::RequestWhiteboardSharingRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_RequestWhiteboardSharingRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::RequestWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Accept WhiteboardSharing
	Result PlayInstanceSvrRPCSendAdapter::AcceptWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::AcceptWhiteboardSharingResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::AcceptWhiteboardSharingRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_AcceptWhiteboardSharingRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::AcceptWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
	Result PlayInstanceSvrRPCSendAdapter::CloseWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::CloseWhiteboardSharingResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::CloseWhiteboardSharingRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_CloseWhiteboardSharingRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::CloseWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
	Result PlayInstanceSvrRPCSendAdapter::AddWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InLogEntryID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::AddWhiteboardSharingLogEntryResBuilder _builder(fbb);
		_builder.add_log_entry_id(InLogEntryID);
		flatbuffers::Offset<SF::Flat::PlayInstance::AddWhiteboardSharingLogEntryRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_AddWhiteboardSharingLogEntryRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::AddWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InLogEntryID )
	// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
	Result PlayInstanceSvrRPCSendAdapter::UpdateWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::UpdateWhiteboardSharingLogEntryResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::UpdateWhiteboardSharingLogEntryRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_UpdateWhiteboardSharingLogEntryRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UpdateWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Update whiteboard log entry
	Result PlayInstanceSvrRPCSendAdapter::RemoveWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::RemoveWhiteboardSharingLogEntryResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::RemoveWhiteboardSharingLogEntryRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_RemoveWhiteboardSharingLogEntryRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::RemoveWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: WhiteboardSharing has been requested
	Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingRequestedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto RequestedPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InRequestedPlayerID);
		SF::Flat::PlayInstance::WhiteboardSharingRequestedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_requested_player_id(RequestedPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::WhiteboardSharingRequestedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_WhiteboardSharingRequestedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingRequestedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID )
	// S2C: WhiteboardSharing has been requested
	Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingRejectedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto RejectedPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InRejectedPlayerID);
		SF::Flat::PlayInstance::WhiteboardSharingRejectedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_rejected_player_id(RejectedPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::WhiteboardSharingRejectedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_WhiteboardSharingRejectedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingRejectedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID )
	// S2C: WhiteboardSharing has been started
	Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingStartedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto OtherPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InOtherPlayerID);
		auto WhiteboardInfoOffset = SF::Flat::Helper::CreateVariableTable(fbb, InWhiteboardInfo);
		SF::Flat::PlayInstance::WhiteboardSharingStartedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_other_player_id(OtherPlayerIDOffset);
		_builder.add_whiteboard_info(WhiteboardInfoOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::WhiteboardSharingStartedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_WhiteboardSharingStartedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingStartedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo )
	// S2C: WhiteboardSharing has been closed
	Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingHasClosedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto ClosedPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InClosedPlayerID);
		SF::Flat::PlayInstance::WhiteboardSharingHasClosedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_closed_player_id(ClosedPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::WhiteboardSharingHasClosedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_WhiteboardSharingHasClosedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingHasClosedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID )
	// S2C: WhiteboardSharing new log entry has been added
	Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingNewLogEntryAddedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto LogEntryOffset = SF::Flat::Helper::CreateVariableTable(fbb, InLogEntry);
		SF::Flat::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_log_entry(LogEntryOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_WhiteboardSharingNewLogEntryAddedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingNewLogEntryAddedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	// S2C: WhiteboardSharing new log entry has been removed
	Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingNewLogEntryRemovedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_log_entry_id(InLogEntryID);
		flatbuffers::Offset<SF::Flat::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_WhiteboardSharingNewLogEntryRemovedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingNewLogEntryRemovedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID )
	// S2C: WhiteboardSharing new log entry has been updated
	Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingNewLogEntryUpdatedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto LogEntryOffset = SF::Flat::Helper::CreateVariableTable(fbb, InLogEntry);
		SF::Flat::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_log_entry(LogEntryOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_WhiteboardSharingNewLogEntryUpdatedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::WhiteboardSharingNewLogEntryUpdatedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry )
	// Cmd: Occupy map object
	Result PlayInstanceSvrRPCSendAdapter::OccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::OccupyMapObjectResBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_map_object_id(InMapObjectId);
		flatbuffers::Offset<SF::Flat::PlayInstance::OccupyMapObjectRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_OccupyMapObjectRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::OccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Unoccupy map object
	Result PlayInstanceSvrRPCSendAdapter::UnoccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::UnoccupyMapObjectResBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_map_object_id(InMapObjectId);
		flatbuffers::Offset<SF::Flat::PlayInstance::UnoccupyMapObjectRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_UnoccupyMapObjectRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UnoccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId )
	// Cmd: Use map object
	Result PlayInstanceSvrRPCSendAdapter::UseMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto ResultAttributesOffset = SF::Flat::Helper::CreateVariableTable(fbb, InResultAttributes);
		SF::Flat::PlayInstance::UseMapObjectResBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_map_object_id(InMapObjectId);
		_builder.add_result_attributes(ResultAttributesOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UseMapObjectRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_UseMapObjectRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UseMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes )
	// Cmd: Send zone chatting
	Result PlayInstanceSvrRPCSendAdapter::ZoneChatRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::ZoneChatResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::ZoneChatRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_ZoneChatRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::ZoneChatRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Player state change
	Result PlayInstanceSvrRPCSendAdapter::ZoneChatS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto SenderIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InSenderID);
		auto ChatMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InChatMetaData);
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::PlayInstance::ZoneChatS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_sender_id(SenderIDOffset);
		_builder.add_message_type(InMessageType);
		_builder.add_chat_meta_data(ChatMetaDataOffset);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::ZoneChatS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_ZoneChatS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::ZoneChatS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage )
	// S2C: Effect modifier initial sync
	Result PlayInstanceSvrRPCSendAdapter::LevelUpS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InPlayInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::PlayInstance::LevelUpS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_current_exp(InCurrentExp);
		_builder.add_current_level(InCurrentLevel);
		flatbuffers::Offset<SF::Flat::PlayInstance::LevelUpS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_LevelUpS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::LevelUpS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel )
	// Cmd: To call general functionality
	Result PlayInstanceSvrRPCSendAdapter::CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ResultsOffset = SF::Flat::Helper::CreateVariableTable(fbb, InResults);
		SF::Flat::PlayInstance::CallFunctionResBuilder _builder(fbb);
		_builder.add_results(ResultsOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::CallFunctionRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_CallFunctionRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )
	// S2C: Voice data
	Result PlayInstanceSvrRPCSendAdapter::VoiceDataS2CEvt( const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto VoiceDataOffset = SF::Flat::Helper::Createuint8Vector(fbb, InVoiceData);
		SF::Flat::PlayInstance::VoiceDataS2CEvtBuilder _builder(fbb);
		_builder.add_actor_id(InActorID);
		_builder.add_frame_index(InFrameIndex);
		_builder.add_voice_data(VoiceDataOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::VoiceDataS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_VoiceDataS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::VoiceDataS2CEvt( const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData )
	// Cmd: UGC zone edit command
	Result PlayInstanceSvrRPCSendAdapter::UGCEditAddRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InInstanceId, const uint32_t &InTimeOffset, const Array<VariableTable>& InInvenChanges )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InvenChangesOffset = SF::Flat::Helper::CreateVariableTableVector(fbb, InInvenChanges);
		SF::Flat::PlayInstance::UGCEditAddResBuilder _builder(fbb);
		_builder.add_instance_id(InInstanceId);
		_builder.add_time_offset(InTimeOffset);
		_builder.add_inven_changes(InvenChangesOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditAddRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_UGCEditAddRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UGCEditAddRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InInstanceId, const uint32_t &InTimeOffset, const Array<VariableTable>& InInvenChanges )
	// Cmd: UGC zone edit command
	Result PlayInstanceSvrRPCSendAdapter::UGCEditMoveRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::UGCEditMoveResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditMoveRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_UGCEditMoveRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UGCEditMoveRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: UGC zone edit command
	Result PlayInstanceSvrRPCSendAdapter::UGCEditDeleteRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::PlayInstance::UGCEditDeleteResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditDeleteRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_UGCEditDeleteRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UGCEditDeleteRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: UGC zone edit command
	Result PlayInstanceSvrRPCSendAdapter::UGCEditClaimBackRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InInstanceId, const Array<VariableTable>& InInvenChanges )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InvenChangesOffset = SF::Flat::Helper::CreateVariableTableVector(fbb, InInvenChanges);
		SF::Flat::PlayInstance::UGCEditClaimBackResBuilder _builder(fbb);
		_builder.add_instance_id(InInstanceId);
		_builder.add_inven_changes(InvenChangesOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditClaimBackRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_UGCEditClaimBackRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UGCEditClaimBackRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InInstanceId, const Array<VariableTable>& InInvenChanges )
	// S2C: UGC zone edited event
	Result PlayInstanceSvrRPCSendAdapter::UGCEditAddedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const StringCrc32 &InEntityType, const uint32_t &InTableId, const uint32_t &InTimeOffset, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale, const uint32_t &InInstanceId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto OperatorPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InOperatorPlayerID);
		auto PositionOffset = SF::Flat::Helper::CreateVector4(fbb, InPosition);
		auto RotationOffset = SF::Flat::Helper::CreateVector4(fbb, InRotation);
		auto ScaleOffset = SF::Flat::Helper::CreateVector4(fbb, InScale);
		SF::Flat::PlayInstance::UGCEditAddedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_operator_player_id(OperatorPlayerIDOffset);
		_builder.add_entity_type(InEntityType);
		_builder.add_table_id(InTableId);
		_builder.add_time_offset(InTimeOffset);
		_builder.add_position(PositionOffset);
		_builder.add_rotation(RotationOffset);
		_builder.add_scale(ScaleOffset);
		_builder.add_instance_id(InInstanceId);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditAddedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_UGCEditAddedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UGCEditAddedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const StringCrc32 &InEntityType, const uint32_t &InTableId, const uint32_t &InTimeOffset, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale, const uint32_t &InInstanceId )
	// S2C: UGC zone edited event
	Result PlayInstanceSvrRPCSendAdapter::UGCEditRemovedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const uint32_t &InInstanceId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto OperatorPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InOperatorPlayerID);
		SF::Flat::PlayInstance::UGCEditRemovedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_operator_player_id(OperatorPlayerIDOffset);
		_builder.add_instance_id(InInstanceId);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditRemovedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_UGCEditRemovedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UGCEditRemovedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const uint32_t &InInstanceId )
	// S2C: UGC zone edited event
	Result PlayInstanceSvrRPCSendAdapter::UGCEditMovedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InPlayInstanceUID);
		auto OperatorPlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InOperatorPlayerID);
		auto PositionOffset = SF::Flat::Helper::CreateVector4(fbb, InPosition);
		auto RotationOffset = SF::Flat::Helper::CreateVector4(fbb, InRotation);
		auto ScaleOffset = SF::Flat::Helper::CreateVector4(fbb, InScale);
		SF::Flat::PlayInstance::UGCEditMovedS2CEvtBuilder _builder(fbb);
		_builder.add_play_instance_uid(PlayInstanceUIDOffset);
		_builder.add_operator_player_id(OperatorPlayerIDOffset);
		_builder.add_position(PositionOffset);
		_builder.add_rotation(RotationOffset);
		_builder.add_scale(ScaleOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::UGCEditMovedS2CEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::PlayInstance::MID_UGCEditMovedS2CEvt, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::UGCEditMovedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const Vector4 &InPosition, const Vector4 &InRotation, const Vector4 &InScale )
	// Cmd: Create stream instance
	Result PlayInstanceSvrRPCSendAdapter::CreateStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto StreamNameOffset = SF::Flat::Helper::CreateString(fbb, InStreamName);
		SF::Flat::PlayInstance::CreateStreamResBuilder _builder(fbb);
		_builder.add_stream_name(StreamNameOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::CreateStreamRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_CreateStreamRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::CreateStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Open stream instance
	Result PlayInstanceSvrRPCSendAdapter::FindStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto StreamNameOffset = SF::Flat::Helper::CreateString(fbb, InStreamName);
		SF::Flat::PlayInstance::FindStreamResBuilder _builder(fbb);
		_builder.add_stream_name(StreamNameOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::FindStreamRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_FindStreamRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::FindStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Delete stream instance
	Result PlayInstanceSvrRPCSendAdapter::DeleteStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto StreamNameOffset = SF::Flat::Helper::CreateString(fbb, InStreamName);
		SF::Flat::PlayInstance::DeleteStreamResBuilder _builder(fbb);
		_builder.add_stream_name(StreamNameOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::DeleteStreamRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_DeleteStreamRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::DeleteStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName )
	// Cmd: Get stream list
	Result PlayInstanceSvrRPCSendAdapter::GetStreamListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto StreamNamesOffset = SF::Flat::Helper::CreateStringVector(fbb, InStreamNames);
		SF::Flat::PlayInstance::GetStreamListResBuilder _builder(fbb);
		_builder.add_stream_names(StreamNamesOffset);
		flatbuffers::Offset<SF::Flat::PlayInstance::GetStreamListRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::PlayInstance::MID_GetStreamListRes, fbb));


		return hr;
	}; // Result PlayInstanceSvrRPCSendAdapter::GetStreamListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames )


}; // namespace SF



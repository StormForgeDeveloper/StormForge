////////////////////////////////////////////////////////////////////////////////
// 
// StormForge
// 
// Author : Generated
// 
// Description : PlayInstance MessageLog
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/PlayInstanceMessageID.h"




namespace SF
{
 

	class PlayInstanceMessageLog
	{
 		private:

		public:
		static Result Initialize();

		static Result JoinPlayInstanceCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinPlayInstanceRes(const char* prefix, const MessageHeader* messageHeader);
		static Result PlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PlayPacketC2SEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result NewActorInViewS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result RemoveActorFromViewS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PlayerMovementC2SEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result ActorMovementS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result ActorMovementsS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PlayerStateChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result ClientSyncReliableC2SEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result ClientSyncC2SEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result SetCharacterPublicMessageCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result SetCharacterPublicMessageRes(const char* prefix, const MessageHeader* messageHeader);
		static Result CharacterPrivateDataChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result CharacterPublicDataChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader);
		static Result AcceptWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result AcceptWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader);
		static Result CloseWhiteboardSharingCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CloseWhiteboardSharingRes(const char* prefix, const MessageHeader* messageHeader);
		static Result AddWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result AddWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader);
		static Result UpdateWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result UpdateWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader);
		static Result RemoveWhiteboardSharingLogEntryCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RemoveWhiteboardSharingLogEntryRes(const char* prefix, const MessageHeader* messageHeader);
		static Result WhiteboardSharingRequestedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result WhiteboardSharingRejectedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result WhiteboardSharingStartedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result WhiteboardSharingHasClosedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result WhiteboardSharingNewLogEntryAddedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result WhiteboardSharingNewLogEntryRemovedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result WhiteboardSharingNewLogEntryUpdatedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result OccupyMapObjectCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result OccupyMapObjectRes(const char* prefix, const MessageHeader* messageHeader);
		static Result UnoccupyMapObjectCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result UnoccupyMapObjectRes(const char* prefix, const MessageHeader* messageHeader);
		static Result UseMapObjectCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result UseMapObjectRes(const char* prefix, const MessageHeader* messageHeader);
		static Result ZoneChatCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result ZoneChatRes(const char* prefix, const MessageHeader* messageHeader);
		static Result ZoneChatS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result LevelUpS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result CallFunctionCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CallFunctionRes(const char* prefix, const MessageHeader* messageHeader);
		static Result SendVoiceDataC2SEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result VoiceDataS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result CreateStreamCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CreateStreamRes(const char* prefix, const MessageHeader* messageHeader);
		static Result FindStreamCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result FindStreamRes(const char* prefix, const MessageHeader* messageHeader);
		static Result DeleteStreamCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result DeleteStreamRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetStreamListCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetStreamListRes(const char* prefix, const MessageHeader* messageHeader);

	}; // class PlayInstanceMessageLog


}; // namespace SF



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Actor movement
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Math/SF3DMath.h"

namespace SF
{
	#pragma pack(push, 4)
	struct SF_DECLARE_ALIGN ActorMovement
	{
		static constexpr size_t MaxSavedMove = 8;
		static constexpr uint32_t FramesPerSeconds = 60;
		static constexpr uint32_t DeltaMSPerFrame = 1000 / FramesPerSeconds;
		static constexpr float DeltaSecondsPerFrame = 1.0 / (float)FramesPerSeconds;
		static constexpr float MoveFrameTimeoutSeconds = 10;
		static constexpr uint32_t MoveFrameTimeout = static_cast<uint32_t>(MoveFrameTimeoutSeconds * FramesPerSeconds);
		static constexpr size_t SizeOfActorMovement = sizeof(Vector4) + sizeof(Vector4) + sizeof(float) + sizeof(uint32_t) + sizeof(uint32_t);

		Vector4 Position = Vector4::Zero();
		Vector4 LinearVelocity = Vector4::Zero();

		// Look direction
		float AngularYaw = 0; // No pitch and roll
		uint32_t MoveFrame = 0;
		uint32_t MovementState = 0; // can be 8bit, just for C# size match

		Result CanMerge(const ActorMovement* pNextMove) const;

		Result SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove) const;

		bool operator == (const ActorMovement& src) const;
		bool operator != (const ActorMovement& src) const;

		ActorMovement& operator=(const ActorMovement& src);
	};
	#pragma pack(pop)


	inline size_t SerializedSizeOf(const ActorMovement& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, ActorMovement& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const ActorMovement& data) { return output.Write(&data, sizeof(data)); }


	Result _ToString(ToStringContext& context, const ActorMovement& value);


	DECLARE_BOXING_TEMPLETE_BYREFERENCE(ActorMovement);


}


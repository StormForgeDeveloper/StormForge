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

#include "SFEnginePCH.h"

#include "Actor/Movement/SFActorMovement.h"
#include "Math/SF3DMathSerialization.h"


namespace SF
{

	//constexpr size_t ActorMovement::MaxSavedMove;
	//constexpr uint32_t ActorMovement::FramesPerSeconds;
	//constexpr uint32_t ActorMovement::DeltaMSPerFrame;
	//constexpr float ActorMovement::DeltaSecondsPerFrame;
	//constexpr float ActorMovement::MoveFrameTimeoutSeconds;
	//constexpr int32_t ActorMovement::MoveFrameTimeout;
	//constexpr size_t ActorMovement::SizeOfActorMovement;


	Result ActorMovement::CanMerge(const ActorMovement* pNextMove) const
	{
		const float fMergeThreshold = 0.01f;

		if (MovementState != pNextMove->MovementState)
			return ResultCode::FAIL;

		float deltaTime = (pNextMove->MoveFrame - MoveFrame) * DeltaSecondsPerFrame;
		if (deltaTime > MoveFrameTimeoutSeconds) // Don't merge if the time exceeded
			return ResultCode::FAIL;

		if (Math::Abs(AngularYaw - pNextMove->AngularYaw) > fMergeThreshold)
			return ResultCode::FAIL;

		if ((LinearVelocity - pNextMove->LinearVelocity).SquareLength3() > fMergeThreshold)
			return ResultCode::FAIL;

		auto expectedPos = (Position + LinearVelocity * deltaTime);
		if ((expectedPos - pNextMove->Position).SquareLength3() > fMergeThreshold)
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	Result ActorMovement::SimulateCurrentMove(uint32_t InMoveFrame, ActorMovement& outCurMove) const
	{
		int32_t deltaFrames(InMoveFrame - MoveFrame);
		if (deltaFrames <= 0) // If the move is future or current frame.
		{
			// just make copy
			outCurMove = *this;
			outCurMove.MoveFrame = InMoveFrame;
			return ResultCode::SUCCESS;
		}

		if (deltaFrames > MoveFrameTimeout)
		{
			// Timed out. Let's stop everything
			deltaFrames = MoveFrameTimeout;
			float deltaTime = DeltaSecondsPerFrame * (deltaFrames);

			outCurMove = *this;
			outCurMove.MoveFrame = InMoveFrame;
			outCurMove.Position = Position + LinearVelocity * deltaTime;
			outCurMove.LinearVelocity = Vector4::Zero();
			return ResultCode::SUCCESS_FALSE;
		}

		float deltaTime = DeltaSecondsPerFrame * (deltaFrames);
		outCurMove = *this; // copy all other properties
		outCurMove.MoveFrame = InMoveFrame;
		outCurMove.Position = Position + LinearVelocity * deltaTime;

		return ResultCode::SUCCESS;
	}

	bool ActorMovement::operator == (const ActorMovement& src) const
	{
		return memcmp(this, &src, SizeOfActorMovement) == 0;
	}

	bool ActorMovement::operator != (const ActorMovement& src) const
	{
		return memcmp(this, &src, SizeOfActorMovement) != 0;
	}

	ActorMovement& ActorMovement::operator=(const ActorMovement& src)
	{
		memcpy(this, &src, sizeof(ActorMovement));

		return *this;
	}

	Result _ToString(ToStringContext& context, const ActorMovement& value)
	{
        if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(ActID:"))
            return ResultCode::FAIL;

        if (!_ToString(context, value.ActorId))
            return ResultCode::FAIL;

        if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ",F:"))
			return ResultCode::FAIL;

		auto oldRadis = context.Radix;
		context.Radix = 16;
		if (!_IToA(context, value.MoveFrame))
			return ResultCode::FAIL;
		context.Radix = oldRadis;
		
		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ",P:"))
			return ResultCode::FAIL;

		if (!_ToString(context, value.Position))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ",V:"))
			return ResultCode::FAIL;

		if (!_ToString(context, value.LinearVelocity))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ",A:"))
			return ResultCode::FAIL;

		if (!_ToString(context, value.AngularYaw))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ",S:"))
			return ResultCode::FAIL;

		if (!_ToString(context, value.MovementState))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ")"))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(ActorMovement)



}

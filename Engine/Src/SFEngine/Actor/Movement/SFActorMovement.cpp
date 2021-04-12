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

	constexpr size_t ActorMovement::MaxSavedMove;
	constexpr uint32_t ActorMovement::FramesPerSeconds;
	constexpr uint32_t ActorMovement::DeltaMSPerFrame;
	constexpr float ActorMovement::DeltaSecondsPerFrame;
	constexpr float ActorMovement::MoveFrameTimeoutSeconds;
	constexpr uint32_t ActorMovement::MoveFrameTimeout;
	constexpr size_t ActorMovement::SizeOfActorMovement;


	Result ActorMovement::CanMerge(const ActorMovement* pNextMove) const
	{
		const float fMergeThreshold = 0.01;

		if (MovementState != pNextMove->MovementState)
			return ResultCode::FAIL;

		float deltaTime = (pNextMove->MoveFrame - MoveFrame) * DeltaSecondsPerFrame;
		if (deltaTime > MoveFrameTimeoutSeconds) // Don't merge if the time exceeded
			return ResultCode::FAIL;

		if (Util::Abs(AngularYaw - pNextMove->AngularYaw) > fMergeThreshold)
			return ResultCode::FAIL;

		if ((LinearVelocity - pNextMove->LinearVelocity).SquareLength3() > fMergeThreshold)
			return ResultCode::FAIL;

		auto expectedPos = (Position + LinearVelocity * deltaTime);
		if ((expectedPos - pNextMove->Position).SquareLength3() > fMergeThreshold)
			return ResultCode::FAIL;

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
		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(F:"))
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




	/// <summary>
	/// ActorMovementManager
	/// </summary>
	ActorMovementManager::ActorMovementManager()
	{
	}

	ActorMovementManager::~ActorMovementManager()
	{
		m_Moves.ClearQueue();
	}

	Result ActorMovementManager::EnqueueMovement(const ActorMovement& newMove)
	{
			if (newMove.MoveFrame <= m_LatestQueuedFrame)
				return ResultCode::INVALID_FRAME; // drop old frames

			if (m_Moves.IsFull())
			{
				ActorMovement pRemove;
				m_Moves.Dequeue(pRemove);
			}

			m_LatestQueuedFrame = newMove.MoveFrame;

			return m_Moves.Enqueue(newMove);
	}

	Result ActorMovementManager::DequeueMovement(ActorMovement& movement)
	{
		return m_Moves.Dequeue(movement);
	}





	////////////////////////////////////////////////////////////////////////////////////////
	//
	// SendingActorMovementManager
	//

	SendingActorMovementManager::SendingActorMovementManager()
	{
	}

	SendingActorMovementManager::~SendingActorMovementManager()
	{
	}


	Result SendingActorMovementManager::EnqueueMovement(const ActorMovement& newMove)
	{
		if (newMove.MoveFrame <= m_LatestQueuedFrame)
			return ResultCode::SUCCESS_FALSE; // drop old frames

		if (m_LatestEnqueued.CanMerge(&newMove))
		{
			return ResultCode::SUCCESS;
		}

		m_LatestEnqueued = newMove;

		return super::EnqueueMovement(newMove);
	}







	////////////////////////////////////////////////////////////////////////////////////////
	//
	// Received actor movement 
	//

	ReceivedActorMovementManager::ReceivedActorMovementManager()
	{
		ResetMove();
	}

	bool ReceivedActorMovementManager::CanBeMerged(const ActorMovement& a, const ActorMovement& b, float deltaTime)
	{
		auto diff = (b.Position - (a.Position + a.LinearVelocity * deltaTime)).Length3()
			+ (b.LinearVelocity - a.LinearVelocity).Length3();

		return diff < 0.1; // TODO: test expected?
	}

	void ReceivedActorMovementManager::ResetMove()
	{
		m_LatestMove = {};
		m_LatestFrame = 0;

		m_Moves.ClearQueue();
	}

	Result ReceivedActorMovementManager::SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove)
	{
		if (m_LatestFrame > MoveFrame)
			return ResultCode::IO_INVALID_SEQUENCE;// drop out of sequenced move

		auto prevFrame = m_LatestMove.MoveFrame;

		const ActorMovement* move1 = nullptr, * move2 = nullptr;

		while (true)
		{
			move1 = nullptr;
			move2 = nullptr;

			if (m_Moves.size() == 0)
			{
				// No new movement to calculate
				break;
			}

			move1 = &m_Moves[0];
			if (MoveFrame < move1->MoveFrame)
			{
				move1 = nullptr;
				break;
			}

			// only one move, just simulate expected pos
			if (m_Moves.size() < 2)
				break;

			// we found two moves with expected time
			move2 = &m_Moves[1];
			if (move2->MoveFrame > MoveFrame)
				break;

			// We don't need move1 anymore, free it
			ActorMovement pRemove;
			m_Moves.Dequeue(pRemove);

			// Start over
		}


		float deltaTime = DeltaSecondsPerFrame * (MoveFrame - prevFrame);
		m_MoveExpected = {};

		if (move1 == nullptr)
		{
			Simulate(MoveFrame, m_LatestMove, m_MoveExpected);
			SFLog(Net, Debug7, "ReceivedActorMovementManager::SimulateCurrentMove move1:{0}, last:{0}, result:{1}", m_LatestMove, m_MoveExpected);
		}
		else if (move2 == nullptr)
		{
			// No next frame information
			Simulate(MoveFrame, *move1, m_MoveExpected);
			// At the beginning, m_LatestMove holds invalid movement. No need for delta blending
			m_LatestMove = m_MoveExpected;
			SFLog(Net, Debug7, "ReceivedActorMovementManager::SimulateCurrentMove move1:{0}, result:{1}", *move1, m_MoveExpected);
		}
		else
		{
			Simulate(*move1, *move2, MoveFrame, deltaTime, m_MoveExpected);
			SFLog(Net, Debug7, "ReceivedActorMovementManager::SimulateCurrentMove move1:{0}, move2:{1}, result:{2}", *move1, *move2, m_MoveExpected);
		}

		Vector4& Pc = m_LatestMove.Position;
		Vector4& Pe = m_MoveExpected.Position;
		Vector4 Vart = CalculateArtificialDelta(Pc, Pe, deltaTime);

		m_LatestMove.Position += Vart;
		m_LatestMove.LinearVelocity = m_MoveExpected.LinearVelocity;
		m_LatestMove.MovementState = m_MoveExpected.MovementState;
		m_LatestMove.AngularYaw = m_MoveExpected.AngularYaw;
		m_LatestMove.MoveFrame = MoveFrame;
		outCurMove = m_LatestMove;

		SFLog(Net, Debug6, "ReceivedActorMovementManager::SimulateCurrentMove Vart:{0}, lastResult:{1}", Vart, m_LatestMove);

		return ResultCode::SUCCESS;
	}



	// a * (1 - t) + b * t
	void ReceivedActorMovementManager::Simulate(const ActorMovement& a, const ActorMovement& b, uint32_t moveFrame, float t, ActorMovement& result)
	{
		float t1 = 1 - t;
		result.Position = a.Position * t1 + b.Position * t;
		result.AngularYaw = a.AngularYaw * t1 + b.AngularYaw * t;

		result.MoveFrame = moveFrame;
		result.LinearVelocity = a.LinearVelocity;
		result.MovementState = a.MovementState;
	}

	void ReceivedActorMovementManager::Simulate(uint32_t MoveFrame, const ActorMovement& movement, ActorMovement& outCurMove)
	{
		if (movement.MoveFrame > MoveFrame)
		{
			assert(false); // unexpected
			outCurMove = m_LatestMove;
			outCurMove.LinearVelocity = Vector4::Zero();
			return;
		}

		// ActorMovement timeout, let it stop
		if ((MoveFrame - movement.MoveFrame) > MoveFrameTimeout)
		{
			// Let's stop everything
			outCurMove = m_LatestMove;
			outCurMove.LinearVelocity = Vector4::Zero();
			return;
		}

		float deltaTime = DeltaSecondsPerFrame * (MoveFrame - movement.MoveFrame);
		outCurMove = movement;
		outCurMove.Position = movement.Position + movement.LinearVelocity * deltaTime;
	}


	Vector4 ReceivedActorMovementManager::CalculateArtificialDelta(const Vector4& Pc, const Vector4& Pe, float deltaTime)
	{
		static const float MinDistance = 0.1;
		static const float MaxDistance = 10000;
		static const float BlendSpeed = 0.5;
		static const float InvBlendSpeed = 1.0 / BlendSpeed;

		if (deltaTime < std::numeric_limits<float>::epsilon())
			return Vector4::Zero();

		auto vDiff = Pe - Pc;
		auto distance = vDiff.SquareLength3();

		if (distance < MinDistance) // merge them if they are close enough
			return vDiff;

		//if (distance > MaxDistance)
		//{
		//	vDiff *= MaxDistance / distance;
		//}

		return vDiff * InvBlendSpeed;
	}
}

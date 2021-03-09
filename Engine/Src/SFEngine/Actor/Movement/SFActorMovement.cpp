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


	Result ActorMovement::TryMerge(const ActorMovement* pNextMove)
	{
		const float fMergeThreshold = 0.01;

		if (MovementState != pNextMove->MovementState)
			return ResultCode::FAIL;

		if (Util::Abs(AngularYaw - pNextMove->AngularYaw) > fMergeThreshold)
			return ResultCode::FAIL;

		if ((LinearVelocity - pNextMove->LinearVelocity).SquareLength3() > fMergeThreshold)
			return ResultCode::FAIL;

		float deltaTime = (pNextMove->MoveFrame - MoveFrame) * DeltaSecondsPerFrame;
		auto expectedPos = (Position + LinearVelocity * deltaTime);
		if ((expectedPos - pNextMove->Position).SquareLength3() > fMergeThreshold)
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	bool ActorMovement::operator == (const ActorMovement& src) const
	{
		return memcmp(this, &src, sizeof(ActorMovement)) == 0;
	}

	bool ActorMovement::operator != (const ActorMovement& src) const
	{
		return memcmp(this, &src, sizeof(ActorMovement)) != 0;
	}

	ActorMovement& ActorMovement::operator=(const ActorMovement& src)
	{
		memcpy(this, &src, sizeof(ActorMovement));

		return *this;
	}

	Result _ToString(ToStringContext& context, const ActorMovement& value)
	{
		if (!_ToString(context, value.Position))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":"))
			return ResultCode::FAIL;

		if (!_ToString(context, value.LinearVelocity))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(ActorMovement)




	/// <summary>
	/// ActorMovementManager
	/// </summary>
	ActorMovementManager::ActorMovementManager()
	{
		for (auto& itMove : m_MovementBuffer)
		{
			ActorMovement* pMovement = &itMove;
			m_FreeMoves.Enqueue(pMovement);
		}
	}

	ActorMovementManager::~ActorMovementManager()
	{
		m_Moves.ClearQueue();
		ResetFreeMove();
	}

	ActorMovement* ActorMovementManager::GetFreeMovement()
	{
		ActorMovement* pMove = nullptr;

		m_FreeMoves.Dequeue(pMove);

		return pMove;
	}

	void ActorMovementManager::FreeMovement(ActorMovement* pMove)
	{
		if (pMove == nullptr)
			return;

		m_FreeMoves.Enqueue(pMove);
	}

	bool ActorMovementManager::IsValidFreeMove(ActorMovement* pMove)
	{
		auto pMovePtr = uintptr_t(pMove);
		return pMovePtr >= uintptr_t(m_MovementBuffer) && pMovePtr < uintptr_t(m_MovementBuffer + countof(m_MovementBuffer));
	}

	void ActorMovementManager::ResetFreeMove()
	{
		m_FreeMoves.ClearQueue();

		for (uint iMove = 0; iMove < countof(m_MovementBuffer); iMove++)
		{
			m_MovementBuffer[iMove] = {};
			m_FreeMoves.Enqueue(&m_MovementBuffer[iMove]);
		}
	}

	Result ActorMovementManager::EnqueueMovement(const ActorMovement& newMove)
	{
			auto pNewMove = GetFreeMovement();
			if (pNewMove == nullptr)
				DequeueMovement(pNewMove); // remove oldest one and use it

			*pNewMove = newMove;

			return EnqueueMovement_Internal(pNewMove);
	}

	Result ActorMovementManager::EnqueueMovement_Internal(ActorMovement* pMove)
	{
		if (pMove == nullptr)
			return ResultCode::INVALID_ARG;

		if (pMove->MoveFrame <= m_LatestQueuedFrame)
			return ResultCode::SUCCESS_FALSE; // drop old frames

		if (m_Moves.IsFull())
		{
			ActorMovement* pRemove = nullptr;
			m_Moves.Dequeue(pRemove);
			if (pRemove)
				FreeMovement(pRemove);
		}

		return m_Moves.Enqueue(pMove);
	}

	Result ActorMovementManager::DequeueMovement(ActorMovement*& pMove)
	{
		return m_Moves.Dequeue(pMove);
	}






	SendingActorMovementManager::SendingActorMovementManager()
	{
	}

	SendingActorMovementManager::~SendingActorMovementManager()
	{
	}


	Result SendingActorMovementManager::EnqueueMovement_Internal(ActorMovement* pMove)
	{
		if (pMove == nullptr)
			return ResultCode::INVALID_ARG;


		if (pMove->MoveFrame <= m_LatestQueuedFrame)
			return ResultCode::SUCCESS_FALSE; // drop old frames

		if (m_Moves.size() > 0)
		{
			auto lastMove = m_Moves[m_Moves.size() - 1];
			if (lastMove->TryMerge(pMove))
			{
				FreeMovement(pMove);
				return ResultCode::SUCCESS;
			}
		}

		return super::EnqueueMovement_Internal(pMove);
	}









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

		ResetFreeMove();
	}

	Result ReceivedActorMovementManager::SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove)
	{
		if (m_LatestFrame > MoveFrame)
			return ResultCode::IO_INVALID_SEQUENCE;// drop out of sequenced move

		auto prevFrame = m_LatestFrame;
		m_LatestFrame = MoveFrame;

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

			move1 = m_Moves[0];
			if (MoveFrame < move1->MoveFrame)
			{
				move1 = nullptr;
				break;
			}

			// only one move, just simulate expected pos
			if (m_Moves.size() < 2)
				break;

			// we found two moves with expected time
			move2 = m_Moves[1];
			if (move2->MoveFrame > MoveFrame)
				break;

			// We don't need move1 anymore, free it
			ActorMovement* pRemove = nullptr;
			m_Moves.Dequeue(pRemove);
			FreeMovement(pRemove);

			// Start over
		}


		float deltaTime = DeltaSecondsPerFrame * (MoveFrame - prevFrame);
		m_MoveExpected = {};

		if (move1 == nullptr)
		{
			Simulate(MoveFrame, m_LatestMove, m_MoveExpected);
		}
		else if (move2 == nullptr)
		{
			// No next frame information
			Simulate(MoveFrame, *move1, m_MoveExpected);
		}
		else
		{
			Simulate(*move1, *move2, MoveFrame, deltaTime, m_MoveExpected);
		}

		Vector4& Pc = m_LatestMove.Position;
		Vector4& Pe = m_MoveExpected.Position;
		Vector4 Vart = CalculateArtificialDelta(Pc, Pe, deltaTime);

		m_LatestMove.Position += Vart * deltaTime;
		m_LatestMove.LinearVelocity = m_MoveExpected.LinearVelocity;
		m_LatestMove.MovementState = m_MoveExpected.MovementState;
		m_LatestMove.AngularYaw = m_MoveExpected.AngularYaw;
		outCurMove = m_LatestMove;

		return ResultCode::SUCCESS;
	}

	Result ReceivedActorMovementManager::EnqueueMovement_Internal(ActorMovement* pMove)
	{
		if (pMove == nullptr)
			return ResultCode::INVALID_ARG;

		if (pMove->MoveFrame <= m_LatestQueuedFrame)
			return ResultCode::SUCCESS_FALSE; // drop old frames

		if (m_Moves.IsFull())
		{
			ActorMovement* pRemove = nullptr;
			m_Moves.Dequeue(pRemove);
			if (pRemove)
				FreeMovement(pRemove);
		}

		return m_Moves.Enqueue(pMove);
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
			outCurMove = {};
			return;
		}

		// ActorMovement timeout, let it stop
		if ((MoveFrame - movement.MoveFrame) > MoveFrameTimeout)
		{
			// Let's stop everything
			outCurMove = {};
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

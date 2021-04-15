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

#include "Actor/Movement/SFActorMovementManager.h"
#include "Math/SF3DMathSerialization.h"


namespace SF
{

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

	ActorMovementReplayManager::ActorMovementReplayManager()
	{
		ResetMove();
	}


	void ActorMovementReplayManager::ResetMove()
	{
		ResetMove({});
	}

	void ActorMovementReplayManager::ResetMove(const ActorMovement& newMove)
	{
		m_MoveResult = newMove;
		m_MoveExpected = newMove;
		m_LatestFrame = newMove.MoveFrame;

		m_Moves.ClearQueue();

		EnqueueMovement(newMove);
	}

	Result ActorMovementReplayManager::EnqueueMovement(const ActorMovement& newMove)
	{
		m_LatestReceivedMove = newMove;
		return super::EnqueueMovement(newMove);
	}

	Result ActorMovementReplayManager::SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove)
	{
		if (m_LatestFrame > MoveFrame)
		{
			m_MoveResult.MoveFrame = MoveFrame;
			outCurMove = m_MoveResult;
			return ResultCode::SUCCESS_FALSE;// drop out of sequenced move
		}

		// No movement yet or the first one still future
		if (m_Moves.size() == 0 || MoveFrame < m_Moves[0].MoveFrame)
		{
			// No new movement to calculate
			m_MoveResult.SimulateCurrentMove(MoveFrame, m_MoveExpected);
			m_MoveResult = m_MoveExpected;
			outCurMove = m_MoveExpected;
			return ResultCode::SUCCESS;
		}

		const ActorMovement* move1 = nullptr, * move2 = nullptr;

		while (true)
		{
			move1 = &m_Moves[0];
			move2 = nullptr;

			// only one move, just simulate expected pos
			if (m_Moves.size() < 2)
				break;

			// we found two moves with expected time
			move2 = &m_Moves[1];
			if (move2->MoveFrame > MoveFrame)
				break;

			// We don't need move1 anymore, free it
			ActorMovement removeMove;
			m_Moves.Dequeue(removeMove);
			// Start over
		}


		m_MoveExpected = {};

		if (move2 == nullptr)
		{
			// No next frame information
			move1->SimulateCurrentMove(MoveFrame, m_MoveExpected);
			// At the beginning, m_MoveResult holds invalid movement. No need for delta blending
			m_MoveResult = m_MoveExpected;
			outCurMove = m_MoveResult;
			SFLog(Net, Debug7, "ActorMovementReplayManager::SimulateCurrentMove move1:{0}, result:{1}", *move1, m_MoveExpected);
			return ResultCode::SUCCESS;
		}

		// We have two moves
		auto prevFrame = m_MoveResult.MoveFrame;
		float deltaTime = DeltaSecondsPerFrame * (MoveFrame - prevFrame);
		float interpolationTime = DeltaSecondsPerFrame * (MoveFrame - move1->MoveFrame);

		Simulate(*move1, *move2, interpolationTime, m_MoveExpected);
		m_MoveExpected.MoveFrame = MoveFrame;

		SFLog(Net, Debug7, "ActorMovementReplayManager::SimulateCurrentMove move1:{0}, move2:{1}, result:{2}", *move1, *move2, m_MoveExpected);

		Vector4& Pc = m_MoveResult.Position;
		Vector4& Pe = m_MoveExpected.Position;
		Vector4 Vart = CalculateArtificialDelta(Pc, Pe);

		m_MoveResult.Position += Vart;
		m_MoveResult.LinearVelocity = m_MoveExpected.LinearVelocity + Vart;
		m_MoveResult.MovementState = m_MoveExpected.MovementState;
		m_MoveResult.AngularYaw = m_MoveExpected.AngularYaw;
		m_MoveResult.MoveFrame = MoveFrame;
		outCurMove = m_MoveResult;

		SFLog(Net, Debug6, "ActorMovementReplayManager::SimulateCurrentMove Vart:{0}, lastResult:{1}", Vart, m_MoveResult);

		return ResultCode::SUCCESS;
	}

	// a * (1 - t) + b * t
	void ActorMovementReplayManager::Simulate(const ActorMovement& a, const ActorMovement& b, float deltaTime, ActorMovement& result)
	{
		float t = deltaTime / (ActorMovement::DeltaSecondsPerFrame * (b.MoveFrame - a.MoveFrame));
		assert(t > 0);
		//float t1 = 1 - t;
		//Vector4 interpolatedPos = a.Position + (b.Position - -a.Position) * t; // a.Position * (1 - t) + b.Position * t;
		//Vector4 simulatedPos = a.Position + a.LinearVelocity * deltaTime;
		Vector4 interpolationDelta = (b.Position - a.Position) * t;
		Vector4 simulationDelta = a.LinearVelocity * deltaTime;
		Vector4 delta = simulationDelta + (interpolationDelta - simulationDelta) * t;

		// Interpolated pos affects more when it closes to b
		//result.Position = simulatedPos + (interpolatedPos - simulatedPos) * t; 
		result.Position = a.Position + delta;
		result.AngularYaw = a.AngularYaw + (b.AngularYaw - a.AngularYaw) * t;

		result.LinearVelocity = deltaTime > std::numeric_limits<float>::epsilon() ? delta / deltaTime : Vector4::Zero();
		result.MovementState = a.MovementState;
	}

	Vector4 ActorMovementReplayManager::CalculateArtificialDelta(const Vector4& Pc, const Vector4& Pe)
	{
		static const float MinDistance = 0.2f;
		static const float MinSquareDistance = MinDistance * MinDistance;
		static const float MaxDistance = 10000;
		static const float BlendSpeed = 0.1;
		auto vDiff = Pe - Pc;
		auto distance = vDiff.SquareLength3();

		if (distance < MinSquareDistance) // merge them if they are close enough
			return vDiff;

		return vDiff * BlendSpeed;
	}


	////////////////////////////////////////////////////////////////////////////////////////
	//
	// Received actor movement 
	//

	ReceivedActorMovementManager::ReceivedActorMovementManager()
	{
		ResetMove();
	}

	void ReceivedActorMovementManager::ResetMove()
	{
		ResetMove({});
	}

	void ReceivedActorMovementManager::ResetMove(const ActorMovement& newMove)
	{
		m_LatestReceivedMove = newMove;
		m_MoveResult = newMove;
	}

	Result ReceivedActorMovementManager::SimulateCurrentMove(uint32_t InMoveFrame, ActorMovement& outCurMove)
	{
		if (m_LatestReceivedMove.MoveFrame > InMoveFrame)
		{
			outCurMove = m_LatestReceivedMove;
			outCurMove.MoveFrame = InMoveFrame;

			return ResultCode::SUCCESS;
		}

		auto prevFrame = m_LatestReceivedMove.MoveFrame;
		int32_t deltaFrames(InMoveFrame - m_LatestReceivedMove.MoveFrame);
		if (deltaFrames == 0)
		{
			outCurMove = m_LatestReceivedMove;
			outCurMove.MoveFrame = InMoveFrame;

			return ResultCode::SUCCESS;
		}

		float deltaTime = ActorMovement::DeltaSecondsPerFrame * (deltaFrames);
		m_LatestReceivedMove.SimulateCurrentMove(InMoveFrame, m_MoveExpected);

		Vector4& Pc = m_MoveResult.Position; // current position
		Vector4& Pe = m_MoveExpected.Position;
		Vector4 Vart = BlendDelta(Pc, Pe);

		m_MoveResult.Position += Vart;
		m_MoveResult.LinearVelocity = m_MoveExpected.LinearVelocity + Vart;
		m_MoveResult.MovementState = m_MoveExpected.MovementState;
		m_MoveResult.AngularYaw = m_MoveExpected.AngularYaw;
		m_MoveResult.MoveFrame = InMoveFrame;
		outCurMove = m_MoveResult;

		SFLog(Net, Debug6, "ActorMovementReplayManager::SimulateCurrentMove Vart:{0}, lastResult:{1}", Vart, m_MoveResult);

		return ResultCode::SUCCESS;
	}

	// Queue style operation
	Result ReceivedActorMovementManager::EnqueueMovement(const ActorMovement& newMove)
	{
		if (newMove.MoveFrame < m_LatestReceivedMove.MoveFrame)
			return ResultCode::SUCCESS_FALSE;

		m_LatestReceivedMove = newMove;

		return ResultCode::SUCCESS;
	}

	Vector4 ReceivedActorMovementManager::BlendDelta(const Vector4& Pc, const Vector4& Pe)
	{
		static const float MinDistance = 0.2f;
		static const float MinSquareDistance = MinDistance * MinDistance;
		static const float MaxDistance = 10000;
		static const float BlendSpeed = 0.1f;

		auto vDiff = Pe - Pc;
		auto distance = vDiff.SquareLength3();

		if (distance < MinSquareDistance) // merge them if they are close enough
			return vDiff;

		return vDiff * BlendSpeed;
	}

}

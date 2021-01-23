////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : String basic test
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Thread/SFSystemSynchronization.h"
#include "Thread/SFThread.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "String/SFToString.h"
#include "UnitTest_Movement.h"
#include "Math/SF3DMath.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;



static constexpr uint32_t FramesPerSeconds = 60;
static constexpr float DeltaSecondsPerFrame = 1.0 / (float)FramesPerSeconds;
static constexpr size_t MaxSavedMove = 6;
static constexpr float MoveFrameTimeout = 10 * FramesPerSeconds;

#pragma pack(push, 4)
struct Movement
{
	Vector4 Position = Vector4::Zero();
	Vector4 LinearVelocity = Vector4::Zero();
	// Look direction
	float AngularYaw = 0; // Not pitch and roll
	uint32_t MoveFrame = 0;
	uint8_t MovementState = 0;





	Result TryMerge(const Movement* pNextMove)
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
};
#pragma pack(pop)


class MovementManager
{
public:

	MovementManager()
	{
		for (auto& itMove : m_MovementBuffer)
		{
			Movement* pMovement = &itMove;
			m_FreeMoves.Enqueue(pMovement);
		}
	}

	virtual ~MovementManager()
	{
		ResetFreeMove();
	}

	Movement* GetFreeMovement()
	{
		Movement* pMove = nullptr;

		m_FreeMoves.Dequeue(pMove);

		return pMove;
	}

	void FreeMovement(Movement* pMove)
	{
		if (pMove == nullptr)
			return;

		m_FreeMoves.Enqueue(pMove);
	}

	bool IsValidFreeMove(Movement* pMove)
	{
		auto pMovePtr = uintptr_t(pMove);
		return pMovePtr >= uintptr_t(m_MovementBuffer) && pMovePtr < uintptr_t(m_MovementBuffer + countof(m_MovementBuffer));
	}

	void ResetFreeMove()
	{
		m_FreeMoves.ClearQueue();

		for (uint iMove = 0; iMove < countof(m_MovementBuffer); iMove++)
		{
			m_MovementBuffer[iMove] = {};
			m_FreeMoves.Enqueue(&m_MovementBuffer[iMove]);
		}
	}

private:

	// Free move management
	Movement m_MovementBuffer[MaxSavedMove * 2];
	CircularQueue<Movement*, MaxSavedMove * 3> m_FreeMoves;

};


class SendingMovementManager : public MovementManager
{
public:

	SendingMovementManager()
	{
	}

	virtual ~SendingMovementManager()
	{
		m_Moves.ClearQueue();
	}


	Result EnqueueMovement(const Movement& newMove)
	{
		auto pNewMove = GetFreeMovement();
		if (pNewMove == nullptr)
			DequeueMovement(pNewMove); // remove oldest one and use it

		*pNewMove = newMove;

		return EnqueueMovement(pNewMove);
	}

	Result EnqueueMovement(Movement* pMove)
	{
		assert(IsValidFreeMove(pMove));

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

		// This unlikely hit. just leaving it as fail safe code
		if (m_Moves.IsFull())
		{
			Movement* pRemove = nullptr;
			m_Moves.Dequeue(pRemove);
			if (pRemove)
				FreeMovement(pRemove);
		}

		return m_Moves.Enqueue(pMove);
	}

	Result DequeueMovement(Movement* &pMove)
	{
		return m_Moves.Dequeue(pMove);
	}

private:

	uint32_t m_LatestQueuedFrame = 0;
	CircularQueue<Movement*, MaxSavedMove> m_Moves;

};


class ReceivedMovementManager : public MovementManager
{
public:

	ReceivedMovementManager()
	{
		ResetMove();
	}

	bool CanBeMerged(const Movement& a, const Movement& b, float deltaTime)
	{
		auto diff = (b.Position - (a.Position + a.LinearVelocity * deltaTime)).Length3()
			+ (b.LinearVelocity - a.LinearVelocity).Length3();

		return diff < 0.1; // TODO: test expected?
	}

	void ResetMove()
	{
		m_LastestMove = {};
		m_LatestFrame = 0;

		m_Moves.ClearQueue();

		ResetFreeMove();
	}

	Result SimulateCurrentMove(uint32_t MoveFrame, Movement& outCurMove)
	{
		if (m_LatestFrame > MoveFrame)
			return ResultCode::IO_INVALID_SEQUENCE;// drop out of sequenced move

		auto prevFrame = m_LatestFrame;
		m_LatestFrame = MoveFrame;

		const Movement *move1 = nullptr, *move2 = nullptr;

		while(true)
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
			Movement* pRemove = nullptr;
			m_Moves.Dequeue(pRemove);
			FreeMovement(pRemove);

			// Start over
		}


		float deltaTime = DeltaSecondsPerFrame * (MoveFrame - prevFrame);
		m_MoveExpected = {};

		if (move1 == nullptr)
		{
			Simulate(MoveFrame, m_LastestMove, m_MoveExpected);
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

		Vector4& Pc = m_LastestMove.Position;
		Vector4& Pe = m_MoveExpected.Position;
		Vector4 Vart = CalculateArtificialDelta(Pc, Pe, deltaTime);

		m_LastestMove.Position += Vart * deltaTime;
		m_LastestMove.LinearVelocity = m_MoveExpected.LinearVelocity;
		m_LastestMove.MovementState = m_MoveExpected.MovementState;
		m_LastestMove.AngularYaw = m_MoveExpected.AngularYaw;
		outCurMove = m_LastestMove;

		return ResultCode::SUCCESS;
	}

	Result EnqueueMovement(const Movement& pMove)
	{
		auto pNewMove = GetFreeMovement();
		*pNewMove = pMove;

		return EnqueueMovement(pNewMove);
	}

	Result EnqueueMovement(Movement* pMove)
	{
		if (pMove == nullptr)
			return ResultCode::INVALID_ARG;

		if (pMove->MoveFrame <= m_LatestQueuedFrame)
			return ResultCode::SUCCESS_FALSE; // drop old frames

		if (m_Moves.IsFull())
		{
			Movement* pRemove = nullptr;
			m_Moves.Dequeue(pRemove);
			if (pRemove)
				FreeMovement(pRemove);
		}

		return m_Moves.Enqueue(pMove);
	}


private:


	// a * (1 - t) + b * t
	void Simulate(const Movement& a, const Movement& b, uint32_t moveFrame, float t, Movement& result)
	{
		float t1 = 1 - t;
		result.Position = a.Position * t1 + b.Position * t;
		result.AngularYaw = a.AngularYaw * t1 + b.AngularYaw * t;

		result.MoveFrame = moveFrame;
		result.LinearVelocity = a.LinearVelocity;
		result.MovementState = a.MovementState;
	}

	void Simulate(uint32_t MoveFrame, const Movement& movement, Movement& outCurMove)
	{
		if (movement.MoveFrame > MoveFrame)
		{
			assert(false); // unexpected
			outCurMove = {};
			return;
		}

		// Movement timeout, let it stop
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


	Vector4 CalculateArtificialDelta(const Vector4& Pc, const Vector4& Pe, float deltaTime)
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


private:

	// Latest calculation information
	uint32_t m_LatestFrame = 0;
	uint32_t m_LatestQueuedFrame = 0;
	Movement m_LastestMove{};
	Movement m_MoveExpected{};

	// saved moves
	CircularQueue<Movement*, MaxSavedMove> m_Moves;
};


TEST_F(MovementTest, Calculation)
{
	const float MaxSpeed = 100;
	const int TestFrameMax = 10 * 60 * 60 * 60; // 10 hours amount
	uint32_t sendFrame = 0;
	Movement curMove;

	uint32_t recvFrame = 0;
	Movement replicatedMove;

	SendingMovementManager sendingMove;
	ReceivedMovementManager receivedMove;

	int iSrcFrame = 0;
	int iDestFrame = 0;
	while (iSrcFrame < TestFrameMax && iDestFrame <= TestFrameMax)
	{
		auto srcGenCount = Util::Random.Rand(0, 2);
		for (int iGen = 0; iGen <= srcGenCount && iSrcFrame < TestFrameMax; iGen++)
		{
			auto newFrame = ++iSrcFrame;

			// TODO: Gen move data
			auto skipFrame = Util::Random.Rand(100);
			if (skipFrame <= 0)
				continue;

			float deltaTime = DeltaSecondsPerFrame * (newFrame - curMove.MoveFrame);
			curMove.Position = curMove.Position + curMove.LinearVelocity * deltaTime;

			auto moving = Util::Random.Rand(0, 10) < 5;
			Vector4 movDir = Vector4::Zero();
			if (moving)
			{
				auto changeDir = Util::Random.Rand(0, 9) < 2;
				auto speed = Util::Random.RandF() * MaxSpeed;
				movDir = Vector4(Util::Random.RandF(), Util::Random.RandF(), Util::Random.RandF());
				movDir.Normalize3();
				movDir.Scale3(speed);
			}
			else
			{
				curMove.LinearVelocity = Vector4::Zero();
			}

			curMove.MoveFrame = newFrame;
			curMove.LinearVelocity = movDir;
			curMove.MovementState = Util::Random.Rand(0, 10) < 3 ? 1 : 0;

			auto result = sendingMove.EnqueueMovement(curMove);
			assert(result == ResultCode::SUCCESS || result == ResultCode::OUT_OF_MEMORY);
		}


		// pump  sending move to 
		Movement* pMove = nullptr;
		while (sendingMove.DequeueMovement(pMove))
		{
			receivedMove.EnqueueMovement(*pMove);

			sendingMove.FreeMovement(pMove);
		}

		// read and processing
		auto dstProcessCount = Util::Random.Rand(0, 2);
		for (int iProcess = 0; iProcess <= dstProcessCount && iDestFrame < TestFrameMax; iDestFrame++, iProcess++)
		{
			EXPECT_EQ(ResultCode::SUCCESS, receivedMove.SimulateCurrentMove(iDestFrame, replicatedMove));
		}


	}

}


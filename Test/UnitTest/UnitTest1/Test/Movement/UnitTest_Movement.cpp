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
#include "Actor/Movement/SFActorMovement.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




TEST_F(MovementTest, ActorMovementSimple)
{
	const float MaxSpeed = 100;
	const int TestFrameMax = 10 * 60 * 60 * 60; // 10 hours amount
	uint32_t sendFrame = 0;
	ActorMovement curMove;

	uint32_t recvFrame = 0;
	ActorMovement replicatedMove;

	SharedPointerT<SendingActorMovementManager> sendingMove = new(GetHeap()) SendingActorMovementManager;
	SharedPointerT <ReceivedActorMovementManager> receivedMove = new(GetHeap()) ReceivedActorMovementManager;

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

			float deltaTime = ActorMovement::DeltaSecondsPerFrame * (newFrame - curMove.MoveFrame);
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

			auto result = sendingMove->EnqueueMovement(curMove);
			assert(result == ResultCode::SUCCESS || result == ResultCode::OUT_OF_MEMORY);
		}


		// pump  sending move to 
		ActorMovement* pMove = nullptr;
		while (sendingMove->DequeueMovement(pMove))
		{
			receivedMove->EnqueueMovement(*pMove);

			sendingMove->FreeMovement(pMove);
		}

		// read and processing
		auto dstProcessCount = Util::Random.Rand(0, 2);
		for (int iProcess = 0; iProcess <= dstProcessCount && iDestFrame < TestFrameMax; iDestFrame++, iProcess++)
		{
			EXPECT_EQ(ResultCode::SUCCESS, receivedMove->SimulateCurrentMove(iDestFrame, replicatedMove));
		}


	}

}


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
#include "Object/SFSharedObject.h"
#include "Container/SFCircularQueue.h"
#include "Actor/Movement/SFActorMovement.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////////////////////////
	//
	// actor movement manager base
	//
	class ActorMovementManager : public SharedObject
	{
	public:
		static constexpr size_t MaxSavedMove = ActorMovement::MaxSavedMove;
		static constexpr uint32_t FramesPerSeconds = ActorMovement::FramesPerSeconds;
		static constexpr float DeltaSecondsPerFrame = ActorMovement::DeltaSecondsPerFrame;
		static constexpr float MoveFrameTimeoutSeconds = ActorMovement::MoveFrameTimeoutSeconds;
		static constexpr uint32_t MoveFrameTimeout = ActorMovement::MoveFrameTimeout;

	public:

		ActorMovementManager();

		virtual ~ActorMovementManager();

		// Queue style operation
		virtual Result EnqueueMovement(const ActorMovement& newMove);

		virtual Result DequeueMovement(ActorMovement& pMove);

	protected:
		uint32_t m_LatestQueuedFrame = 0;
		CircularQueue<ActorMovement, MaxSavedMove> m_Moves;
	};


	////////////////////////////////////////////////////////////////////////////////////////
	//
	// SendingActorMovementManager
	//

	class SendingActorMovementManager : public ActorMovementManager
	{
	public:

		using super = ActorMovementManager;

	public:

		SendingActorMovementManager();

		virtual ~SendingActorMovementManager();

		virtual Result EnqueueMovement(const ActorMovement& newMove) override;

	private:

		ActorMovement m_LatestEnqueued{};
	};


	////////////////////////////////////////////////////////////////////////////////////////
	//
	// Actor Movement replay
	//
	class ActorMovementReplayManager : public ActorMovementManager
	{
	public:

		ActorMovementReplayManager();

		bool CanBeMerged(const ActorMovement& a, const ActorMovement& b, float deltaTime);

		void ResetMove();

		const ActorMovement& GetLatestMovement() const { return m_LatestMove; }

		Result SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove);

	private:


		// a * (1 - t) + b * t
		void Simulate(const ActorMovement& a, const ActorMovement& b, uint32_t moveFrame, float t, ActorMovement& result);

		Vector4 CalculateArtificialDelta(const Vector4& Pc, const Vector4& Pe, float deltaTime);


	private:

		// Latest calculation information
		uint32_t m_LatestFrame = 0;
		ActorMovement m_LatestMove{};
		ActorMovement m_MoveExpected{};
	};



	////////////////////////////////////////////////////////////////////////////////////////
	//
	// Received actor movement 
	//
	class ReceivedActorMovementManager : public SharedObject
	{
	public:

		ReceivedActorMovementManager();

		void ResetMove();
		void ResetMove(const ActorMovement& newMove);

		const ActorMovement& GetLatestReceivedMovement() const { return m_LatestReceivedMove; }

		const ActorMovement& GetLatestMovementResult() const { return m_MoveResult; }

		Result SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove);

		// Queue style operation
		virtual Result EnqueueMovement(const ActorMovement& newMove);

	private:

		Vector4 BlendDelta(const Vector4& Pc, const Vector4& Pe);


	private:

		// Latest calculation information
		ActorMovement m_LatestReceivedMove{};
		ActorMovement m_MoveExpected{};
		ActorMovement m_MoveResult{};
	};

}


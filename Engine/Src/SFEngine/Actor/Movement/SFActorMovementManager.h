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

		ActorMovementManager(ActorID actorId);

		virtual ~ActorMovementManager();

		SF_FORCEINLINE ActorID GetActorID() const { return m_ActorId; }

		// Queue style operation
		virtual Result EnqueueMovement(const ActorMovement& newMove);

		virtual Result DequeueMovement(ActorMovement& pMove);

	protected:

		ActorID m_ActorId{};

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

		void SetActorID(ActorID actorId) { m_ActorId = actorId; }
        void InitMovement(const ActorMovement& movement);

        const ActorMovement& GetLatestMovement() const { return m_LatestEnqueued; }

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
		using super = ActorMovementManager;

		ActorMovementReplayManager(ActorID actorId);

		void ResetMove();
		void ResetMove(const ActorMovement& newMove);

		const ActorMovement& GetMovementResult() const { return m_MoveResult; }
		const ActorMovement& GetReceivedMovement() const { return m_LatestReceivedMove; }
		const ActorMovement& GetMovementExpected() const { return m_MoveExpected; }

		virtual Result EnqueueMovement(const ActorMovement& newMove) override;

		Result SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove);

	private:


		// a * (1 - t) + b * t
		void Simulate(const ActorMovement& a, const ActorMovement& b, float t, ActorMovement& result);

		Vector4 CalculateArtificialDelta(const Vector4& Pc, const Vector4& Pe);


	private:

		// Latest calculation information
		uint32_t m_LatestFrame = 0;
		ActorMovement m_MoveResult{};
		ActorMovement m_LatestReceivedMove{};
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

		const ActorMovement& GetReceivedMovement() const { return m_LatestReceivedMove; }
		const ActorMovement& GetMovementExpected() const { return m_MoveExpected; }
		const ActorMovement& GetMovementResult() const { return m_MoveResult; }

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


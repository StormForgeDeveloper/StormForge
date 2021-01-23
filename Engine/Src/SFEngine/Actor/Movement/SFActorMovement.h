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



namespace SF
{

	#pragma pack(push, 4)
	struct ActorMovement
	{
		static constexpr size_t MaxSavedMove = 8;
		static constexpr uint32_t FramesPerSeconds = 60;
		static constexpr float DeltaSecondsPerFrame = 1.0 / (float)FramesPerSeconds;
		static constexpr float MoveFrameTimeout = 10 * FramesPerSeconds;


		Vector4 Position = Vector4::Zero();
		Vector4 LinearVelocity = Vector4::Zero();

		// Look direction
		float AngularYaw = 0; // No pitch and roll
		uint32_t MoveFrame = 0;
		uint8_t MovementState = 0;


		Result TryMerge(const ActorMovement* pNextMove);
	
	};
	#pragma pack(pop)


	class ActorMovementManager
	{
	public:
		static constexpr size_t MaxSavedMove = ActorMovement::MaxSavedMove;
		static constexpr uint32_t FramesPerSeconds = ActorMovement::FramesPerSeconds;
		static constexpr float DeltaSecondsPerFrame = ActorMovement::DeltaSecondsPerFrame;
		static constexpr float MoveFrameTimeout = ActorMovement::MoveFrameTimeout;

	public:

		ActorMovementManager();

		virtual ~ActorMovementManager();

		ActorMovement* GetFreeMovement();

		void FreeMovement(ActorMovement* pMove);

		bool IsValidFreeMove(ActorMovement* pMove);

		void ResetFreeMove();


	private:

		// Free move management
		ActorMovement m_MovementBuffer[MaxSavedMove * 2];
		CircularQueue<ActorMovement*, MaxSavedMove * 3> m_FreeMoves;

	};


	class SendingActorMovementManager : public ActorMovementManager
	{
	public:

		SendingActorMovementManager();

		virtual ~SendingActorMovementManager();


		Result EnqueueMovement(const ActorMovement& newMove);

		Result EnqueueMovement(ActorMovement* pMove);

		Result DequeueMovement(ActorMovement*& pMove);

	private:

		uint32_t m_LatestQueuedFrame = 0;
		CircularQueue<ActorMovement*, MaxSavedMove> m_Moves;

	};


	class ReceivedActorMovementManager : public ActorMovementManager
	{
	public:

		ReceivedActorMovementManager();

		bool CanBeMerged(const ActorMovement& a, const ActorMovement& b, float deltaTime);

		void ResetMove();

		Result SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove);

		Result EnqueueMovement(const ActorMovement& pMove);

		Result EnqueueMovement(ActorMovement* pMove);

	private:


		// a * (1 - t) + b * t
		void Simulate(const ActorMovement& a, const ActorMovement& b, uint32_t moveFrame, float t, ActorMovement& result);
		void Simulate(uint32_t MoveFrame, const ActorMovement& movement, ActorMovement& outCurMove);

		Vector4 CalculateArtificialDelta(const Vector4& Pc, const Vector4& Pe, float deltaTime);


	private:

		// Latest calculation information
		uint32_t m_LatestFrame = 0;
		uint32_t m_LatestQueuedFrame = 0;
		ActorMovement m_LastestMove{};
		ActorMovement m_MoveExpected{};

		// saved moves
		CircularQueue<ActorMovement*, MaxSavedMove> m_Moves;
	};


}


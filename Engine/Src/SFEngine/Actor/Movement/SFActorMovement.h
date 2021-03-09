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
		static constexpr float MoveFrameTimeout = 10 * FramesPerSeconds;

		Vector4 Position = Vector4::Zero();
		Vector4 LinearVelocity = Vector4::Zero();

		// Look direction
		float AngularYaw = 0; // No pitch and roll
		uint32_t MoveFrame = 0;
		uint32_t MovementState = 0; // can be 8bit, just for C# size match

		Result TryMerge(const ActorMovement* pNextMove);


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
		static constexpr float MoveFrameTimeout = ActorMovement::MoveFrameTimeout;

	public:

		ActorMovementManager();

		virtual ~ActorMovementManager();

		ActorMovement* GetFreeMovement();

		void FreeMovement(ActorMovement* pMove);

		bool IsValidFreeMove(ActorMovement* pMove);


		void ResetFreeMove();

		// Queue style operation
		Result EnqueueMovement(const ActorMovement& newMove);

		Result DequeueMovement(ActorMovement*& pMove);


	protected:
		virtual Result EnqueueMovement_Internal(ActorMovement* pMove);

	private:

		// Free move management
		ActorMovement m_MovementBuffer[MaxSavedMove * 2];
		CircularQueue<ActorMovement*, MaxSavedMove * 3> m_FreeMoves;

	protected:
		uint32_t m_LatestQueuedFrame = 0;
		CircularQueue<ActorMovement*, MaxSavedMove> m_Moves;
	};


	class SendingActorMovementManager : public ActorMovementManager
	{
	public:
		using super = ActorMovementManager;

		SendingActorMovementManager();

		virtual ~SendingActorMovementManager();

	protected:
		virtual Result EnqueueMovement_Internal(ActorMovement* pMove) override;

	private:

	};


	////////////////////////////////////////////////////////////////////////////////////////
	//
	// Received actor movement 
	//
	class ReceivedActorMovementManager : public ActorMovementManager
	{
	public:

		ReceivedActorMovementManager();

		bool CanBeMerged(const ActorMovement& a, const ActorMovement& b, float deltaTime);

		void ResetMove();

		const ActorMovement& GetLatestMovement() const { return m_LatestMove; }

		Result SimulateCurrentMove(uint32_t MoveFrame, ActorMovement& outCurMove);

	protected:
		virtual Result EnqueueMovement_Internal(ActorMovement* pMove) override;

	private:


		// a * (1 - t) + b * t
		void Simulate(const ActorMovement& a, const ActorMovement& b, uint32_t moveFrame, float t, ActorMovement& result);
		void Simulate(uint32_t MoveFrame, const ActorMovement& movement, ActorMovement& outCurMove);

		Vector4 CalculateArtificialDelta(const Vector4& Pc, const Vector4& Pe, float deltaTime);


	private:

		// Latest calculation information
		uint32_t m_LatestFrame = 0;
		ActorMovement m_LatestMove{};
		ActorMovement m_MoveExpected{};
	};


}


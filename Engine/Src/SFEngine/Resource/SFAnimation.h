////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource Animation
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"


namespace SF
{

	////////////////////////////////////////////////////////////////////
	//
	//	Animation enumerations
	//

	enum class AnimationTarget : uint8_t
	{
		None,
		Translation,
		Rotation,
		Scale,
		TexCoordTranslation,
		TexCoordRotation,
		TexCoordScale,
		TexImage,
	};

	enum class AnimationFormat : uint8_t
	{
		Invalid,
		Bool,
		Int8,
		Int16,
		Int32,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Image,
	};

	struct AnimationInitParameter
	{
		int dummy;
	};


	////////////////////////////////////////////////////////////////////
	//
	//	Animation
	//

	class Animation : public Resource
	{
	public:


		////////////////////////////////////////////////////////////////////
		//
		//	Type definitions
		//

#pragma pack(push,1)
		struct ChannelDescription
		{
			// Animation format
			AnimationFormat AniFormat;

			// Animation target
			AnimationTarget AniTarget;

			// Dummy
			uint8_t Dummy[2];

			// Animation frame data size
			uint32_t FrameSize;
		};
#pragma pack(pop)

	private:

		// Channel description array
		DynamicArray<ChannelDescription> m_ChannelDesc;

		// Animation frame data size
		size_t m_FrameDataSize = 0;

		// Frame count
		size_t m_FrameCount = 0;

		// Animation data
		uint8_t* m_AniData = nullptr;


	public:
		Animation(IHeap& heap, const CallTrack& callTrack = CallTrack());
		virtual ~Animation();

		// Clear resource
		void ClearResource();

		// Dispose
		virtual void Dispose() override;

		// Initialize resource
		Result Init(const AnimationInitParameter& initParameters);

		// Get frame data size
		size_t GetFrameDataSize() const { return m_FrameDataSize; }

		// Get number of frames
		size_t GetFrameCount() const { return m_FrameCount; }
	};


	typedef SharedPointerT<Animation> AnimationPtr;
	extern template class SharedPointerT<Animation>;

}


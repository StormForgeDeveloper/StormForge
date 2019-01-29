////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource Animation
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFAnimation.h"
#include "Service/SFEngineService.h"


namespace SF
{

	template class SharedPointerT<Animation>;




	Animation::Animation(IHeap& heap, const CallTrack& callTrack)
		: Resource(heap, "Animation", callTrack)
		, m_ChannelDesc(heap)
	{
	}

	Animation::~Animation()
	{
		ClearResource();
	}

	void Animation::ClearResource()
	{
		delete[] m_AniData;
		m_AniData = nullptr;
	}

	void Animation::Dispose()
	{
		ClearResource();
		Resource::Dispose();
	}


	Result Animation::Init(const AnimationInitParameter& initParameters)
	{
		ClearResource();

		return ResultCode::SUCCESS;
	}



}


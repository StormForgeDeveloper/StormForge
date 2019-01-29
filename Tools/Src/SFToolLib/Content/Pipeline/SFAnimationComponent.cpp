////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Animation component
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFToolLibPCH.h"
#include "SFAnimationComponent.h"

#include "SFAnimationSequence.h"


namespace SF
{


	SFAnimationComponent::SFAnimationComponent(UMNodeContent& owner)
		: SFNodeContentComponent(owner)
	{
	}

	SFAnimationComponent::~SFAnimationComponent()
	{
		std::for_each(m_AnimationSequences.begin(), m_AnimationSequences.end(), [](UMAnimationSequence* pSequence)
		{
			delete pSequence;
		});
		m_AnimationSequences.clear();
	}

	// Initialize components after load/create
	bool SFAnimationComponent::InitializeComponent()
	{

		return true;
	}


	// Add animation sequence
	void SFAnimationComponent::AddAnimationSequence(UMAnimationSequence* pNewSequence)
	{
		assert(pNewSequence != nullptr);

		m_AnimationSequences.push_back(pNewSequence);
	}

	// foreach sequences
	void SFAnimationComponent::ForeachAnimationSequence(std::function<void(SFAnimationSequence* pSequence)> func)
	{
		std::for_each(m_AnimationSequences.begin(), m_AnimationSequences.end(), func);
	}

}

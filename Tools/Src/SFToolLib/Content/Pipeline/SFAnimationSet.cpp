
#include "stdafx.h"
#include "UMAnimationSet.h"
#include "UMAnimationComponent.h"
#include "UMAnimationSet.h"
#include "UMAnimationSequence.h"



UMAnimationSet::UMAnimationSet()
{
}

UMAnimationSet::~UMAnimationSet()
{
	std::for_each(m_AnimationSequences.begin(), m_AnimationSequences.end(), [](UMAnimationSequence* pSequence)
	{
		delete pSequence;
	});
	m_AnimationSequences.clear();
}


// Add animation sequence
void UMAnimationSet::AddAnimationSequence(UMAnimationSequence* pNewSequence)
{
	assert(pNewSequence!=nullptr);

	m_AnimationSequences.push_back(pNewSequence);
}

// foreach sequences
void UMAnimationSet::ForeachAnimationSequence( std::function<void(UMAnimationSequence* pSequence)> func )
{
	std::for_each(m_AnimationSequences.begin(), m_AnimationSequences.end(), func);
}






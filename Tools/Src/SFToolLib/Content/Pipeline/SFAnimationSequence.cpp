////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Animation sequence
//
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SFAnimationSet.h"
#include "SFAnimationComponent.h"
#include "SFAnimationSequence.h"
#include "SFAnimationCurve.h"



SFAnimationSequence::SFAnimationSequence()
	:m_pTargetNode(nullptr)
{
}

SFAnimationSequence::~SFAnimationSequence()
{
	std::for_each(m_AnimationCurves.begin(), m_AnimationCurves.end(), [](SFAnimationCurve* pCurve)
	{
		delete pCurve;
	});
	m_AnimationCurves.clear();
}


// Add animation sequence
void SFAnimationSequence::AddAnimationCurve(SFAnimationCurve* pNewSequence)
{
	assert(pNewSequence!=nullptr);

	m_AnimationCurves.push_back(pNewSequence);
}

// foreach sequences
void SFAnimationSequence::ForeachAnimationCurve( std::function<void(SFAnimationCurve*)> func )
{
	std::for_each(m_AnimationCurves.begin(), m_AnimationCurves.end(), func);
}




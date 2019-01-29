
#include "stdafx.h"
#include "UMAnimationSet.h"
#include "SFAnimationCurve.h"




SFAnimationCurve::SFAnimationCurve()
{
}

SFAnimationCurve::~SFAnimationCurve()
{
	std::for_each(m_Keyframes.begin(), m_Keyframes.end(), [](KeyFrame* keyframe)
	{
		delete keyframe;
	});
	m_Keyframes.clear();
}

void SFAnimationCurve::GetPeriod(float &startTime, float &endTime)
{
	startTime = 0;
	endTime = 0;

	if( m_Keyframes.size() == 0 )
		return;

	startTime = m_Keyframes[0]->Time;
	endTime = m_Keyframes[m_Keyframes.size()-1]->Time;
}

float SFAnimationCurve::GetDuration()
{
	if( m_Keyframes.size() == 0 )
		return 0;

	float startTime = m_Keyframes[0]->Time;
	float endTime = m_Keyframes[m_Keyframes.size()-1]->Time;

	return endTime - startTime;
}

// Initialize Curve
bool SFAnimationCurve::InitializeCurve( InterpolationType interpolation, PlayType playType, UINT numberOfElement )
{
	m_InterpolationType = interpolation;
	m_PlayType = playType;
	m_NumberOfElement = numberOfElement;

	return true;
}

// Add Keyframe
void SFAnimationCurve::AddKeyframe( KeyFrame* keyframe )
{
	m_Keyframes.push_back(keyframe);
}


// foreach sequences
void SFAnimationCurve::ForeachKeyframe( std::function<void(KeyFrame*)> func )
{
	std::for_each(m_Keyframes.begin(), m_Keyframes.end(), func);
}




#pragma once

#include "UMTypedef.h"
#include "UMNodeContentComponent.h"




class SFAnimationCurve
{
public:

	struct KeyFrame
	{
		float Time;
		float Values[1];
	};

	enum class InterpolationType
	{
		Linear,
		Slerp,
		Spline,
		Squad,
		Step
	};
	
	enum class PlayType
	{
		Once,
		Loop,
	};

private:

	// Interpolation type
	InterpolationType m_InterpolationType;

	// Play type
	PlayType m_PlayType;

	// number of element
	UINT m_NumberOfElement;

	// number of keyframe
	SFArray<KeyFrame*> m_Keyframes;


public:

	SFAnimationCurve();
	virtual ~SFAnimationCurve();

	InterpolationType GetInterpolationType()							{ return m_InterpolationType; }
	PlayType GetPlayType()												{ return m_PlayType; }
	UINT GetNumElement()												{ return m_NumberOfElement; }
	UINT GetNumKeyFrame()												{ return m_Keyframes.size(); }
	KeyFrame* GetKeyFrame(UINT iKey)									{ return m_Keyframes[iKey]; }
	void GetPeriod(float &startTime, float &endTime);

	float GetDuration();

	// Initialize Curve
	bool InitializeCurve( InterpolationType interpolation, PlayType playType, UINT numberOfElement );

	// Add Keyframe
	void AddKeyframe( KeyFrame* keyframe );

	// foreach sequences
	void ForeachKeyframe( std::function<void(KeyFrame*)> func );
};






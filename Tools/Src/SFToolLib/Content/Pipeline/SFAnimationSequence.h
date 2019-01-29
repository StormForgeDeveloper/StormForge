
#pragma once

#include "SFTypedef.h"


class SFAnimationComponent;
class SFAnimationCurve;
class SFNodeContentObject;
class SFObject;

class SFAnimationSequence
{
public:
	
	// Target name
	//SFString m_TargetName;
	SFObject *m_pTargetNode;

	// Animation target property name
	SFString m_TargetPropertyName;


	SFArray<SFAnimationCurve*> m_AnimationCurves;


private:

public:

	SFAnimationSequence();
	virtual ~SFAnimationSequence();

	// Target
	void SetTarget(SFObject *pTargetNode)								{ m_pTargetNode = pTargetNode; }
	SFObject* GetTarget()												{ return m_pTargetNode; }
	
	void SetTargetProperty(const char *pTargetProperty)					{ m_TargetPropertyName = pTargetProperty; }
	const SFString& GetTargetProperty()									{ return m_TargetPropertyName; }

	// Add animation curve
	void AddAnimationCurve(SFAnimationCurve* pCurve);

	// Get 
	UINT GetNumberOfAnimationCurves()									{ return m_AnimationCurves.size(); }

	SFAnimationCurve* GetAnimationCurve( UINT index )					{ return (index >= 0 && index < m_AnimationCurves.size()) ? m_AnimationCurves[index] : nullptr; }

	// foreach curves
	void ForeachAnimationCurve( std::function<void(SFAnimationCurve* pCurve)> func );

};






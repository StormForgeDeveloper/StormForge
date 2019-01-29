
#pragma once

#include "UMTypedef.h"
#include "UMNodeContentComponent.h"


class UMAnimationComponent;
class UMAnimationSequence;

class UMAnimationSet
{
public:

	UMArray<UMAnimationSequence*> m_AnimationSequences;


private:

public:

	UMAnimationSet();
	virtual ~UMAnimationSet();

	// Add animation sequence
	void AddAnimationSequence(UMAnimationSequence* pNewSequence);

	// Get 
	UINT GetNumberOfAnimationSequence() { return m_AnimationSequences.size(); }

	// foreach sequences
	void ForeachAnimationSequence( std::function<void(UMAnimationSequence* pSequence)> func );
};






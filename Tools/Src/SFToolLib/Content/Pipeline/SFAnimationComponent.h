
#pragma once

#include "SFTypedef.h"
#include "SFNodeContentComponent.h"

class SFAnimationSequence;

class SFAnimationComponent : public SFNodeContentComponent
{
public:

private:

	SFArray<SFAnimationSequence*> m_AnimationSequences;

public:

	SFAnimationComponent( UMNodeContent& owner );
	virtual ~SFAnimationComponent();

	// Initialize components after load/create
	virtual bool InitializeComponent();

	// Add animation sequence
	void AddAnimationSequence(UMAnimationSequence* pNewSequence);

	// Get 
	UINT GetNumberOfAnimationSequence() { return m_AnimationSequences.size(); }

	// foreach sequences
	void ForeachAnimationSequence( std::function<void(UMAnimationSequence* pSequence)> func );
};






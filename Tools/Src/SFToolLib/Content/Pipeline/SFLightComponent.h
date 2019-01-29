
#pragma once

#include "UMTypedef.h"
#include "UMNodeContentComponent.h"

class UMLightComponent : public UMNodeContentComponent
{
public:

	enum LightMode
	{
		AMBIENT =	128,
		DIRECTIONAL =	129,
		OMNI =	130,
		SPOT =	131,
	};


	float       attenuationConstant;
	float       attenuationLinear;
	float       attenuationQuadratic;
	UMColor     color;
	LightMode   mode;
	float       intensity;
	float       spotAngle;
	float       spotExponent;


public:

	UMLightComponent( UMNodeContent& owner );
	virtual ~UMLightComponent();

	// Initialize components after load/create
	virtual bool InitializeComponent();

};





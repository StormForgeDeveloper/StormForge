
#include "stdafx.h"
#include "UMTransfoSFComponent.h"



UMTransfoSFComponent::UMTransfoSFComponent( UMNodeContent& owner )
	:UMNodeContentComponent(owner)
{
}

UMTransfoSFComponent::~UMTransfoSFComponent()
{
}

// Initialize components after load/create
bool UMTransfoSFComponent::InitializeComponent()
{

	return true;
}


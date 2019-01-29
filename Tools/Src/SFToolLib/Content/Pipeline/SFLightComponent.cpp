
#include "stdafx.h"
#include "UMLightComponent.h"




UMLightComponent::UMLightComponent( UMNodeContent& owner )
	:UMNodeContentComponent(owner)
{
}

UMLightComponent::~UMLightComponent()
{
}

// Initialize components after load/create
bool UMLightComponent::InitializeComponent()
{

	return true;
}



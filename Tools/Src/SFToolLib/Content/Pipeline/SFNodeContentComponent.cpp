
#include "stdafx.h"

#include "UMNodeContentComponent.h"
#include "UMNodeContent.h"



UMNodeContentComponent::UMNodeContentComponent( UMNodeContent& owner )
	:m_Owner(&owner)
{
}

UMNodeContentComponent::~UMNodeContentComponent()
{
}

void UMNodeContentComponent::SwitchComponentOwner( UMNodeContent& newOwner )
{
	assert(m_Owner != nullptr);
	assert(&newOwner != nullptr);
	m_Owner->RemoveComponentOwnership(this);
	m_Owner = &newOwner;
	newOwner.AddComponent(this);
}

// Initialize components after load/create
bool UMNodeContentComponent::InitializeComponent()
{
	return true;
}


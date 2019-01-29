
#include "stdafx.h"
#include "UMCameraComponent.h"




UMCameraComponent::UMCameraComponent( UMNodeContent& owner )
	:UMNodeContentComponent(owner)
{
}

UMCameraComponent::~UMCameraComponent()
{
}

// Initialize components after load/create
bool UMCameraComponent::InitializeComponent()
{

	return true;
}

// Set perspective camera parameters
void UMCameraComponent::SetPerspective( float fov, float aspectRatio, float fNear, float fFar )
{
	m_Fovy = fov;
    m_AspectRatio = aspectRatio;
    m_Near = fNear;
    m_Far = fFar;
}




#pragma once

#include "UMTypedef.h"
#include "UMNodeContentComponent.h"



class UMCameraComponent : public UMNodeContentComponent
{
public:

	enum CameraType {
		GENERIC = 48,
		PARALLEL =	49,
		PERSPECTIVE =	50,
		SCREEN =	51,
	};


private:

	CameraType m_CameraType;

	float       m_Fovy;
    float       m_AspectRatio;
    float       m_Near;
    float       m_Far;

public:

	UMCameraComponent( UMNodeContent& owner );
	virtual ~UMCameraComponent();

	// Initialize components after load/create
	virtual bool InitializeComponent();

	// Set perspective camera parameters
	void SetPerspective( float fov, float aspectRatio, float fNear, float fFar );

	float GetFOV() { return m_Fovy; }
	float GetAspectRatio() { return m_AspectRatio; }
	float GetNear() { return m_Near; }
	float GetFar() { return m_Far; }
};






////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : GLES Graphic Device
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/SFGraphicDeviceGLES.h"


#if HAVE_GLES

#ifdef __ANDROID__
#include <GLES/gl.h>
#elif __APPLE__
#include <OpenGLES/ES1/gl.h>
#endif

namespace SF
{

	GraphicDeviceGLES::GraphicDeviceGLES()
	{
	}

	GraphicDeviceGLES::~GraphicDeviceGLES()
	{
	}

	// Initialize component
	Result GraphicDeviceGLES::Initialize()
	{
		GraphicDevice::Initialize();


		return ResultCode::SUCCESS;
	}

	// Terminate component
	void GraphicDeviceGLES::Deinitialize()
	{

		GraphicDevice::Deinitialize();
	}

	void GraphicDeviceGLES::InitDisplay(NativeWindow pWindow)
	{
		GraphicDevice::InitDisplay(pWindow);
	}

	void GraphicDeviceGLES::DeinitDisplay()
	{
		GraphicDevice::DeinitDisplay();

	}

	void GraphicDeviceGLES::OnResize()
	{
		GraphicDevice::OnResize();
	}

	bool GraphicDeviceGLES::BeginFrame()
	{
		if (!GraphicDevice::BeginFrame())
			return false;

		// Skip if not initialized
		if (GetNativeWindow() == nullptr)
			return false;


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return true;
	}

	void GraphicDeviceGLES::EndFrame()
	{
		// Skip if not initialized
		if (GetNativeWindow() == nullptr)
			return;

		GraphicDevice::EndFrame();
	}

}

#else
void GraphicDeviceGLES_Dummy() {}
#endif

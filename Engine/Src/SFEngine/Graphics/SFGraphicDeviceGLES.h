////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : GLES Graphic Device
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Graphics/SFGraphicDevice.h"

#if HAVE_GLES


#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES/gl.h>
#elif __APPLE__
#include <OpenGLES/ES1/gl.h>
#endif


namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	Render command
	//
	class GraphicDeviceGLES : public GraphicDevice
	{
	private:


	protected:

	public:
		GraphicDeviceGLES();
		virtual ~GraphicDeviceGLES();


		// Initialize component
		virtual Result Initialize() override;
		// Terminate component
		virtual void Deinitialize() override;


		virtual void InitDisplay(NativeWindow pWindow) override;
		virtual void DeinitDisplay() override;
		virtual void OnResize() override;

		virtual bool BeginFrame() override;
		virtual void EndFrame() override;
	};




}


#endif

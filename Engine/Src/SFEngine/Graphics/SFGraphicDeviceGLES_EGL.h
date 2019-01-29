////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : GLES with EGL graphics device
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Graphics/SFGraphicDeviceGLES.h"

#if HAVE_EGL


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
	class GraphicDeviceGLES_EGL : public GraphicDeviceGLES
	{
	public:
		typedef GraphicDeviceGLES super;

	private:

		EGLDisplay m_Display;
		EGLSurface m_Surface;
		EGLContext m_Context;

	protected:

	public:
		GraphicDeviceGLES_EGL();
		virtual ~GraphicDeviceGLES_EGL();

		EGLDisplay GetDisplay() { return m_Display; }
		EGLSurface GetSurface() { return m_Surface; }
		EGLContext GetContext() { return m_Context; }

		// Initialize component
		virtual Result Initialize() override;
		// Terminate component
		virtual void Deinitialize() override;


		virtual void InitDisplay(NativeWindow pWindow) override;
		virtual void DeinitDisplay() override;

		virtual bool BeginFrame() override;
		virtual void EndFrame() override;
	};




}


#endif

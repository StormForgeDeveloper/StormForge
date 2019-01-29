////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : GLES with EGL graphics device
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/SFGraphicDeviceGLES_EGL.h"


#if HAVE_EGL

#ifdef __ANDROID__
#include <GLES/gl.h>
#elif __APPLE__
#include <OpenGLES/ES1/gl.h>
#endif

namespace SF
{

	GraphicDeviceGLES_EGL::GraphicDeviceGLES_EGL()
	{
	}

	GraphicDeviceGLES_EGL::~GraphicDeviceGLES_EGL()
	{
	}

	// Initialize component
	Result GraphicDeviceGLES_EGL::Initialize()
	{
		super::Initialize();

		return ResultCode::SUCCESS;
	}

	// Terminate component
	void GraphicDeviceGLES_EGL::Deinitialize()
	{

		super::Deinitialize();
	}

	void GraphicDeviceGLES_EGL::InitDisplay(NativeWindow pWindow)
	{
		// TODO: initialize graphics
		// initialize OpenGL ES and EGL

		/*
		* Here specify the attributes of the desired configuration.
		* Below, we select an EGLConfig with at least 8 bits per color
		* component compatible with on-screen windows
		*/
		const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
		};
		EGLint w, h, format;
		EGLint numConfigs;
		EGLConfig config;
		EGLSurface surface;
		EGLContext context;

		EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		eglInitialize(display, 0, 0);

		/* Here, the application chooses the configuration it desires. In this
		* sample, we have a very simplified selection process, where we pick
		* the first EGLConfig that matches our criteria */
		eglChooseConfig(display, attribs, &config, 1, &numConfigs);

#if SF_PLATFORM == SF_PLATFORM_ANDROID
		/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
		* guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
		* As soon as we picked a EGLConfig, we can safely reconfigure the
		* ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
		eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

		ANativeWindow_setBuffersGeometry(pWindow, 0, 0, format);
#endif

		surface = eglCreateWindowSurface(display, config, pWindow, NULL);
		context = eglCreateContext(display, config, NULL, NULL);

		if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
			SFLog(System, Error, "Unable to eglMakeCurrent");
			return;
		}

		eglQuerySurface(display, surface, EGL_WIDTH, &w);
		eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		m_Display = display;
		m_Context = context;
		m_Surface = surface;

		SetWindow(pWindow, w, h);


		super::InitDisplay(pWindow);
	}

	void GraphicDeviceGLES_EGL::DeinitDisplay()
	{
		super::DeinitDisplay();

		if (m_Display == EGL_NO_DISPLAY)
			return;

		SetWindow(nullptr, 0, 0);

		// deinitialize graphics
		if (m_Display != EGL_NO_DISPLAY) {
			eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			if (m_Context != EGL_NO_CONTEXT) {
				eglDestroyContext(m_Display, m_Context);
			}
			if (m_Surface != EGL_NO_SURFACE) {
				eglDestroySurface(m_Display, m_Surface);
			}
			eglTerminate(m_Display);
		}


		m_Display = EGL_NO_DISPLAY;
		m_Context = EGL_NO_CONTEXT;
		m_Surface = EGL_NO_SURFACE;
	}

	bool GraphicDeviceGLES_EGL::BeginFrame()
	{
		if (GetNativeWindow() == nullptr)
			return false;

		if (!super::BeginFrame())
			return false;



		eglMakeCurrent(GetDisplay(), GetSurface(), GetSurface(), GetContext());
		return true;
	}

	void GraphicDeviceGLES_EGL::EndFrame()
	{
		if (GetNativeWindow() != nullptr)
			return;


		eglSwapBuffers(GetDisplay(), GetSurface());
		super::EndFrame();
	}

}

#else
void GraphicDeviceGLES_EGL_Dummy() {}
#endif

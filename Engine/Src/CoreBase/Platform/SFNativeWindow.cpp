////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Native window 
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Platform/SFNativeWindow.h"




namespace SF {
	
	int NativeWindow_GetWidth(NativeWindow pWindow)
	{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		RECT rect;
		GetClientRect(pWindow, &rect);
		return rect.right - rect.left;
#elif SF_PLATFORM == SF_PLATFORM_ANDROID
		return ANativeWindow_getWidth(pWindow);
#elif SF_PLATFORM == SF_PLATFORM_IOS
		// TODO:
		return 0;
#else
		return 0;
		//COMPILETIME_WARNING("Native windows type hasn't implemented");
#endif
	}

	int NativeWindow_GetHeight(NativeWindow pWindow)
	{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		RECT rect;
		GetClientRect(pWindow, &rect);
		return rect.bottom - rect.top;
#elif SF_PLATFORM == SF_PLATFORM_ANDROID
		return ANativeWindow_getHeight(pWindow);
#elif SF_PLATFORM == SF_PLATFORM_IOS
		// TODO:
		return 0;
#else
		return 0;
		//COMPILETIME_WARNING("Native windows type hasn't implemented");
#endif
	}


};	// namespace SF



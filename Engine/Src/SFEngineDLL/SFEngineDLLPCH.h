// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#include "SFTypedefs.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"


// TODO: reference additional headers your program requires here
#if SF_PLATFORM == SF_PLATFORM_ANDROID


#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include <android/log.h>
#include <android/configuration.h>
#include <android/native_activity.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/sensor.h>
#include <android/looper.h>

#include <EGL/egl.h>

#ifdef __ANDROID__
#include <GLES/gl.h>
#elif __APPLE__
#include <OpenGLES/ES1/gl.h>
#endif

#include <poll.h>
#include <pthread.h>
#include <sched.h>


#endif

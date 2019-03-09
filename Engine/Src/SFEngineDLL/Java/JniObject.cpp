////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 StormForge
// 
// Author : KyungKun Ko
//
// Description : Object
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"

#if SF_PLATFORM == SF_PLATFORM_ANDROID


#include <jni.h>
#include <android/configuration.h>
#include <android/native_activity.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/Android/AndroidApp.h"
#include "Application/Android/AndroidAppTasks.h"


#include "Util/SFLog.h"
#include "Object/SFObject.h"




namespace SF
{

}

using namespace SF;

extern "C"
{


	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection interface
	//

	JNIEXPORT void JNICALL Java_com_SF_SFObject_NativeAddReference(JNIEnv* env, jobject thisConnection, jlong nativeHandle)
	{
		SharedReferenceInc((SharedObject*)nativeHandle);
	}

	JNIEXPORT void JNICALL Java_com_SF_SFObject_NativeRelease(JNIEnv* env, jobject thisConnection, jlong nativeHandle)
	{
		SharedReferenceDec((SharedObject*)nativeHandle);
	}

	
}

#endif


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 StormForge
// 
// Author : KyungKun Ko
//
// Description : Connection
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
#include "Service/SFEngineService.h"
#include "Net/SFConnectionMUDP.h"
#include "Net/SFMessage.h"
#include "SFProtocol.h"

#include "JniUtil.h"


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

	JNIEXPORT jlong JNICALL Java_com_SF_SFConnection_NativeCreateConnection(JNIEnv* env)
	{
		auto pConnection = new Net::ConnectionMUDPClient();
		return (jlong)(Net::Connection*)pConnection;
	}

	//JNIEXPORT void JNICALL Java_com_SF_SFConnection_NativeDestroyConnection(JNIEnv* env, jobject thisConnection, jlong nativeHandle)
	//{
	//	if (nativeHandle == 0)
	//		return;

	//	auto pConnection = (Net::Connection*)nativeHandle;
	//	pConnection->
	//}

	JNIEXPORT int JNICALL Java_com_SF_SFConnection_NativeConnect(JNIEnv* env, jobject thisConnection, jlong nativeHandle, long authTicket, jstring address, int port)
	{
		if (nativeHandle == 0)
			return ResultCode::INVALID_ARG;

		const char *nativeAddress = env->GetStringUTFChars(address, 0);
		NetAddress remoteAddress(nativeAddress, port);
		env->ReleaseStringUTFChars(address, nativeAddress);

		auto pConnection = (Net::Connection*)nativeHandle;
		return pConnection->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, remoteAddress, 0));
	}

	JNIEXPORT void JNICALL Java_com_SF_SFConnection_NativeDisconnect(JNIEnv* env, jobject thisConnection, jlong nativeHandle)
	{
		if (nativeHandle == 0)
			return;

		auto pConnection = (Net::Connection*)nativeHandle;
		pConnection->Disconnect("Requested from java");
	}

	JNIEXPORT int JNICALL Java_com_SF_SFConnection_NativeGetState(JNIEnv* env, jobject thisConnection, jlong nativeHandle)
	{
		if (nativeHandle == 0)
			return 0;

		auto pConnection = (Net::Connection*)nativeHandle;
		return (int)pConnection->GetConnectionState();
	}


	jobject GetEnumFieldValue(JNIEnv* env, const char* enumTypePath, const char* enumValueName)
	{
		char enumTypeSig[1024];
		StrUtil::Format(enumTypeSig, "L{0};", enumTypePath);
		jclass jclsEventTypes = env->FindClass(enumTypePath);
		jfieldID eventTypeFiledID = env->GetStaticFieldID(jclsEventTypes, enumValueName, enumTypeSig);
		jobject enumValue = env->GetStaticObjectField(jclsEventTypes, eventTypeFiledID);
		return enumValue;
	}

	JNIEXPORT jobject JNICALL Java_com_SF_SFConnection_NativeDequeueEvent(JNIEnv* env, jobject thisConnection, jlong nativeHandle)
	{
		if (nativeHandle == 0)
			return 0;

		auto pConnection = (Net::Connection*)nativeHandle;

		// Create java event object
		static jclass jcls = env->FindClass("java/com/sf/SFConnection$Event");
		//jmethodID mID1 = env->GetMethodID(jcls, "<init>", "()V"); // default constructor
		static jmethodID connectionStatusConstructorID = env->GetMethodID(jcls, "<init>", "(I;I;I)V"); // parameterzed
		//jobject jobj = env->AllocObject(jcls);

		Net::ConnectionEvent conEvent;
		if (pConnection->DequeueConnectionEvent(conEvent))
		{
			jobject jobj = env->NewObject(jcls, connectionStatusConstructorID, (int)conEvent.Components.EventType, (int)conEvent.Components.State, (int)conEvent.Components.hr);

			return jobj;
		}

		return nullptr;
	}

	JNIEXPORT jobject JNICALL Java_com_SF_SFConnection_NativeDequeueMessage(JNIEnv* env, jobject thisConnection, jlong nativeHandle)
	{
		if (nativeHandle == 0)
			return 0;

		auto pConnection = (Net::Connection*)nativeHandle;

		// Create java message object
		static jclass jcls = env->FindClass("java/com/sf/SFMessage");
		static jmethodID constructorID = env->GetMethodID(jcls, "<init>", "(I)V");
		static jmethodID setValueID = env->GetMethodID(jcls, "SetValue", "(Ljava/lang/String;Ljava/lang/Object)V");
		static jmethodID setVariableSizeValueID = env->GetMethodID(jcls, "SetValue", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object)V");
		//static jmethodID getValuesID = env->GetMethodID(jcls, "GetValues", "()Ljava/lang/Object");
		//jobject jobj = env->AllocObject(jcls);

		MessageDataPtr pIMsg;
		if (!pConnection->GetRecvMessage(pIMsg))
			return nullptr;

		jobject jobj = env->NewObject(jcls, constructorID, pIMsg->GetMessageHeader()->msgID.ID);

		// Fill parameters
		VariableMapBuilderJObject builder(env, jobj, setValueID, setVariableSizeValueID);
		if (!SF::Protocol::ParseMessage(pIMsg, builder))
			return nullptr;

		return jobj;
	}


}

#endif


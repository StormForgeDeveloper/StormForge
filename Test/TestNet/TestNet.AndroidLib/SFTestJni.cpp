////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 StormForge
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFTypedefs.h"

#include "SFEngine.h"

#include "TestNetNative.h"
#include "String/SFToString.h"


using namespace SF;


namespace SF
{
	static SharedPointerT<TestNetNative> g_TestNetNative;
}



extern "C"  JNIEXPORT void JNICALL Java_com_TestNet_TestNetInterface_Initialize(JNIEnv* env, jobject thisObj)
{
	EngineInitParam initParam;

	Engine::Start(initParam);


	// test



	g_TestNetNative = new(GetSystemHeap()) TestNetNative;
	g_TestNetNative->SetTickGroup(SF::EngineTaskTick::SyncPostTick);
}

extern "C"  JNIEXPORT void JNICALL Java_com_TestNet_TestNetInterface_Deinitialize(JNIEnv* env, jobject thisObj)
{
	g_TestNetNative->Dispose();
	g_TestNetNative = nullptr;

	Engine::Stop();
}

extern "C"  JNIEXPORT void JNICALL Java_com_TestNet_TestNetInterface_Connect(JNIEnv* env, jobject thisObj, jstring address, int port)
{
	g_TestNetNative->CloseAllConnections();

	const char *nativeAddress = env->GetStringUTFChars(address, 0);

	g_TestNetNative->Connect(nativeAddress, port);

	env->ReleaseStringUTFChars(address, nativeAddress);
}


extern "C"  JNIEXPORT void JNICALL Java_com_TestNet_TestNetInterface_RequestRanking(JNIEnv* env, jobject thisObj)
{
	if (g_TestNetNative == nullptr)
		return;

	g_TestNetNative->RequestRanking();
}


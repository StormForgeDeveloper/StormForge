////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#if SF_PLATFORM == SF_PLATFORM_ANDROID

#include "Application/SFApplicationBase.h"
#include "EngineObject/SFEngineTask.h"


#include <android/looper.h>
#include <android/native_window.h>
#include <android/configuration.h>
#include <android/native_activity.h>
#include <android/sensor.h>


struct ANativeActivity;
struct AConfiguration;

namespace SF
{
	class EngineTask;

	class AndroidApp : public ApplicationBase
	{
	public:

		static constexpr FixedString TypeName = "AndroidApp";

		enum LooperID {
			/**
			* Looper data ID of commands coming from the app's main thread, which
			* is returned as an identifier from ALooper_pollOnce().  The data for this
			* identifier is a pointer to an android_poll_source structure.
			* These can be retrieved and processed with android_app_read_cmd()
			* and android_app_exec_cmd().
			*/
			LOOPER_ID_MAIN = 1,

			/**
			* Looper data ID of events coming from the AInputQueue of the
			* application's window, which is returned as an identifier from
			* ALooper_pollOnce().  The data for this identifier is a pointer to an
			* android_poll_source structure.  These can be read via the inputQueue
			* object of android_app.
			*/
			LOOPER_ID_INPUT = 2,

			/**
			* Start of user-defined ALooper identifiers.
			*/
			LOOPER_ID_SENSOR = 3,
		};


	private:

		ALooper* m_Looper;
		// When non-NULL, this is the input queue from which the app will
		// receive user input events.
		AInputQueue* m_InputQueue;

		AConfiguration* m_Config;

		AAssetManager* m_AssetManager;

		ASensorManager* m_SensorManager;
		const ASensor* m_AccelerometerSensor;
		ASensorEventQueue* m_SensorEventQueue;

	public:
		AndroidApp(AAssetManager* assetManager);
		~AndroidApp();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		virtual Result InitializeComponent() override;
		virtual void DeinitializeComponent() override;



		//void StartTestTask();

		///////////////////////////////////////////////////////////////
		//
		//	Process handler
		//
		void ProcessInput();
		void ProcessSensor();


		//////////////////////////////////////////////////////////////////
		//
		//	Accessors
		//

		ALooper* GetLooper() { return m_Looper; }

		AInputQueue* GetInputQueue() { return m_InputQueue; }
		void SetInputQueue(AInputQueue* pQueue) { m_InputQueue = pQueue; }

		AConfiguration* GetConfig() { return m_Config; }
		AAssetManager* GetAssetManager() { return m_AssetManager; }
		ASensorManager* GetSensorManager() { return m_SensorManager; }
		const ASensor* GetAccelerometerSensor() { return m_AccelerometerSensor; }
		ASensorEventQueue* GetSensorEventQueue() { return m_SensorEventQueue; }

	public:

		//virtual bool HandleKeyInput(int type, int action, int flags, int keyCode) override;
		//virtual bool HandleInput(int type, int motionAction, int flags, int buttonState, float x, float y) override;

	};




}

#endif



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryPool.h"
#include "Object/SFObject.h"
#include "Object/SFLibraryComponentManager.h"
#include "Service/SFServices.h"


namespace SF {

	class AppBase;


	// Engine initialization parameters
	struct EngineInitParam
	{
		// Context. the value has platform dependent value. 
		void* Context = nullptr;

		// Network system  name
		FixedString NetworkSystem = "MUDP";

		// Network send buffer size
		int NetSendBufferSize = 8 * 1024;

		// Network recv buffer size
		int NetRecvBufferSize = 8 * 1024;

		// Network thread count. Network system requires dedicated network thread. 1 is good for most client, 2 * core count is good for servers.
		int NetworkThreadCount = 1;

		// Graphic system name. nullptr means the graphic engine will not be initialized
		FixedString GraphicSystem = nullptr;

		// Engine tick interval, for low performance system you would want to use less tick per second. 
		DurationMS TickInterval = DurationMS(1000 / 60);

		// Enables memory leak detection. 
		bool EnableMemoryLeakDetection = false;

		// Decide whether engine will create update thread for itself.
		// If you set this false, you should call Engine::TickUpdate by yourself
		bool UseEngineThread = true; 

		// Saving crash dump, Only windows platform is supported for now
		bool EnableCrashDump = SF_PLATFORM == SF_PLATFORM_WINDOWS;

		// Async task thread count. If you put higher number it will takes more CPU cores
		int AsyncTaskThreadCount = 2;

		// Log system filter
		LogChannelParameter LogChannel;

		// Log filter mask for console output.
		LogChannelMask LogOutputConsole;

		// Log filter mask for debugger output. works only with windows
		LogChannelMask LogOutputDebugger;

		// Log filter mask for file output
		LogChannelMask LogOutputFile = { 0 };

		// Log filter mask for file output
		LogChannelMask LogOutputCommon = { 0 };

		// Log file name prefix
		const char* LogFilePrefix = nullptr;
	};


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Engine class
	//

	class Engine : public LibraryComponentManager
	{
	public:

		typedef LibraryComponentManager super;

	private:

		// Static instance
		static Engine* stm_Instance;

		// Engine thread
		Thread* m_EngineThread;

		// Engine exit code
		int m_ExitCode;

		// Expected tick interval
		DurationMS m_TickInterval;

		// Engine initialization parameter
		EngineInitParam m_InitParameter;

		TimeStampMS	m_ulPreTime;

	private:
		// Register Basic components
		Result RegisterBasicComponents();

		// calculate sleep time
		DurationMS UpdateInterval(const DurationMS& ulExpectedInterval);

	public:

		static Engine* GetInstance() { return Engine::stm_Instance; }

		virtual IHeap& GetHeap() override { return GetEngineHeap(); }

		// Constructor
		Engine();
		virtual ~Engine();

		// Override initialize/deinitialize components
		virtual Result InitializeComponents() override;
		virtual Result DeinitializeComponents() override;

		// Get/Set exit code
		int GetExitCode() { return m_ExitCode; }
		void SetExitCode(int iCode) { m_ExitCode = iCode; }


		template< class ComponentType >
		static ComponentType* GetEngineComponent()
		{
			if (stm_Instance == nullptr)
			{
				Assert(false);
				return nullptr;
			}

			return static_cast<ComponentType*>(stm_Instance->GetComponent<ComponentType>());
		}



		////////////////////////////////////////////////////////////////////////////
		//
		//	Engine start/stop
		//

		// Start engine
		static Engine* Start(const EngineInitParam& initParam);

		// Stop engine
		static void Stop();

		// Tick update
		static bool TickUpdate();

	};


	inline Engine* GetEngine() { return Engine::GetInstance(); }

	
}; // namespace SF


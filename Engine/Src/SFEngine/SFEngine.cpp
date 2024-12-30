////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine main shared
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "Task/SFAsyncTaskManager.h"
#include "Util/SFStrUtil.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeEngineComponent.h"
#include "Util/SFLogComponent.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLogOutputLogServerComponent.h"
#include "Service/SFEngineService.h"
#include "Platform/SFStackWalkerComponent.h"

#include "SFEngine.h"
#include "EngineObject/SFEngineObject.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Graphics/SFRenderCommands.h"
#include "Component/SFUnhandledExceptionHandlerComponent.h"
#include "Util/SFStringCrcComponent.h"

#include "Application/Android/AndroidApp.h"
#include "Application/Win/WindowsApp.h"

#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"
#include "Component/SFLibraryComponentInitializer.h"
#include "Online/Websocket/SFWebsocketComponent.h"
#include "Online/HTTP/SFHTTPClientSystem.h"
#include "Component/SFLibraryComponent3rdParties.h"
#if defined(SF_USE_WSAPI)
#include "Audio/WSAPI/SFAudioEngineComponentWSAPI.h"
#endif


namespace SF
{

	Engine* Engine::stm_Instance = nullptr;

	Engine::Engine()
		: m_EngineThread(nullptr)
		, m_ExitCode(-1)
		, m_TickInterval(1000/60)
	{
		Assert(stm_Instance == nullptr);
		stm_Instance = this;
	}

	Engine::~Engine()
	{
		stm_Instance = nullptr;
	}

	// Register Basic components
	Result Engine::RegisterBasicComponents()
	{
		Result result;

		IHeap::SetMemoryLeakDetection(m_InitParameter.EnableMemoryLeakDetection);

		LibraryComponentInitializer::CallInitializers(ComponentInitializeMode::PreInit);

        if (AddComponent<LibraryComponent3rdParties>() == nullptr)
            return ResultCode::FAIL;

		if (AddComponent<LibraryComponentEngineResultCode>() == nullptr)
			return ResultCode::FAIL;

		if(AddComponent<Log::LogModule>(m_InitParameter.GlobalLogOutputMask) == nullptr)
			return ResultCode::FAIL;

		if (AddComponent<StackWalker>() == nullptr)
			return ResultCode::FAIL;


		if (m_InitParameter.EnableCrashDump)
		{
			if (AddComponent<UnhandledExceptionHandlerComponent>() == nullptr)
				return ResultCode::FAIL;
		}

		if (AddComponent<Util::LibraryComponentTime>() == nullptr)
			return ResultCode::FAIL;

		if (!StrUtil::IsNullOrEmpty(m_InitParameter.StringDBBinPath))
			AddComponent<StringCrcLibraryComponent>(m_InitParameter.StringDBBinPath);

		if (AddComponent<SF::EngineObjectManager>() == nullptr)
			return ResultCode::FAIL;

		if (AddComponent<SF::EngineTaskManager>() == nullptr)
			return ResultCode::FAIL;

		if (AddComponent<SF::AsyncTaskManagerComponent>(m_InitParameter.AsyncTaskThreadCount) == nullptr)
			return ResultCode::FAIL;

		if (m_InitParameter.LogOutputConsole.Composited != 0)
		{
            Log::OutputConsole.SetChannelLogMask(m_InitParameter.LogOutputConsole);
			if (AddComponent<SF::LogOutputConsoleComponent>() == nullptr)
				return ResultCode::FAIL;
		}

		if (m_InitParameter.LogOutputDebugger.Composited != 0)
		{
            Log::OutputDebugger.SetChannelLogMask(m_InitParameter.LogOutputDebugger);

			if (AddComponent<SF::LogOutputDebuggerComponent>() == nullptr)
				return ResultCode::FAIL;
		}

		if (m_InitParameter.LogOutputFile.Composited != 0 && m_InitParameter.LogFilePrefix != nullptr)
		{
            Log::OutputFile.SetChannelLogMask(m_InitParameter.LogOutputFile);

			if (AddComponent<SF::LogOutputFileComponent>(m_InitParameter.LogFilePrefix, true) == nullptr)
				return ResultCode::FAIL;
		}

		if (!StrUtil::IsNullOrEmpty(m_InitParameter.LogServerAddress) && m_InitParameter.LogOutputLogServer.Composited != 0)
		{
            Log::OutputLogServer.SetChannelLogMask(m_InitParameter.LogOutputLogServer);

			if (AddComponent<SF::LogOutputLogServerComponent>(m_InitParameter.LogServerAddress) == nullptr)
				return ResultCode::FAIL;
		}

        if (m_InitParameter.EnableAudio)
        {
        #if defined(SF_USE_WSAPI)
            AddComponent<AudioEngineComponentWSAPI>();
        #endif
        }

		if (m_InitParameter.NetworkThreadCount > 0)
		{
			AddComponent<SF::Net::NetSystem>(m_InitParameter.NetRecvBufferSize, m_InitParameter.NetSendBufferSize, m_InitParameter.NetworkThreadCount, 1024);
		}

		AddComponent<SF::HTTPClientComponent>();
        AddComponent<SF::WebsocketComponent>();


		return ResultCode::SUCCESS;
	}


	// Override initialize/deinitialize components
	Result Engine::InitializeComponents()
	{
		LibraryComponentInitializer::CallInitializers(ComponentInitializeMode::RegisterComponent);

		for (auto itFunc : m_InitParameter.InitializationFunctions)
		{
			itFunc(this);
		}

		Result result = super::InitializeComponents();

		LibraryComponentInitializer::CallInitializers(ComponentInitializeMode::AfterRegisterComponent);

		m_ExitCode = -1;

		if (m_InitParameter.UseEngineThread)
		{
			m_EngineThread = new(GetHeap()) FunctorThread([this](Thread* pThread)
			{
				Service::EngineTaskManager->SetEngineThreadID(ThisThread::GetThreadID());

				DurationMS durationMS = m_TickInterval;
				while (GetExitCode() < 0 && !pThread->CheckKillEvent(durationMS))
				{
					SF::Engine* pEngine = Engine::GetInstance();
					if (pEngine == nullptr) break;

                    pEngine->EngineSystemUpdate();

                    if (GetExitCode() >= 0) // if still engine exit has been requested, quit the loop
                        break;

                    durationMS = pThread->UpdateInterval(m_TickInterval);
				}

				SFLog(System, Info, "Engine thread finished");
			});

			m_EngineThread->SetThreadName("EngineUpdate");
			m_EngineThread->Start();
		}

		return result;
	}

	Result Engine::DeinitializeComponents()
	{
		if (m_EngineThread != nullptr)
		{
			m_EngineThread->Stop(true);
			IHeap::Delete(m_EngineThread);
		}

		// Engine and render thread should be stopped at this moment
		Service::EngineTaskManager->SetEngineThreadID(ThisThread::GetThreadID());
		Service::EngineTaskManager->SetRenderThreadID(ThisThread::GetThreadID());

		return super::DeinitializeComponents();
	}

	DurationMS Engine::UpdateInterval(const DurationMS& ulExpectedInterval)
	{
		auto ulCurTime = Util::Time.GetTimeMs();
		if (m_ulPreTime.time_since_epoch().count() == 0)
		{
			m_ulPreTime = ulCurTime;
			return DurationMS(0);
		}

		int32_t diffTime = (int32_t)(ulCurTime - m_ulPreTime).count();
		DurationMS sleepInterval;

		if (diffTime < 0) diffTime = 0;

		if (diffTime >(int32_t)ulExpectedInterval.count())
			sleepInterval = DurationMS(0);
		else if (diffTime < (int32_t)ulExpectedInterval.count())
			sleepInterval = DurationMS((int32_t)ulExpectedInterval.count() - diffTime);
		else
			sleepInterval = ulExpectedInterval;
		m_ulPreTime = ulCurTime;

		return sleepInterval;
	}

    void Engine::EngineSystemUpdate()
    {
        ComponentTickUpdate();

        Service::EngineObjectManager->Update();
        Service::EngineTaskManager->EngineTickUpdate();
        Service::GraphicDevice->RequestCommand<RenderCommand_KickFrame>(CallTrack());
    }

	bool Engine::StaticTickUpdate()
	{
		auto pEngine = Engine::GetInstance();
		if (pEngine == nullptr)
			return false;

		DurationMS durationMS = pEngine->m_TickInterval;

		if (pEngine->GetExitCode() >= 0)
			return false;

		durationMS = pEngine->UpdateInterval(pEngine->m_TickInterval);
		ThisThread::SleepFor(durationMS);

        pEngine->EngineSystemUpdate();

		return true;
	}

} // namespace SF

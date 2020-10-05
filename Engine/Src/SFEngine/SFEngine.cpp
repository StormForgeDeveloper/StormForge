////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine main shared
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Thread/SFThread.h"
#include "Task/SFAsyncTaskManager.h"
#include "String/SFStrUtil.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Util/SFLogComponent.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"
#include "Platform/StackWalkerComponent.h"

#include "SFEngine.h"
#include "EngineObject/SFEngineObject.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Graphics/SFRenderCommands.h"
#include "Component/SFUnhandledExceptionHandlerComponent.h"

#include "Application/Android/AndroidApp.h"
#include "Application/Win/WindowsApp.h"

#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"


namespace SF {


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

		if(AddComponent<Log::LogModule>(m_InitParameter.LogChannel) == nullptr)
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

		if (AddComponent<SF::EngineObjectManager>() == nullptr)
			return ResultCode::FAIL;

		if (AddComponent<SF::EngineTaskManager>() == nullptr)
			return ResultCode::FAIL;

		if (AddComponent<SF::AsyncTaskManagerComponent>(m_InitParameter.AsyncTaskThreadCount) == nullptr)
			return ResultCode::FAIL;

		if (m_InitParameter.LogOutputConsole.Composited != 0)
		{
			if (AddComponent<SF::LogOutputConsoleComponent>(m_InitParameter.LogOutputConsole) == nullptr)
				return ResultCode::FAIL;
		}

		if (m_InitParameter.LogOutputDebugger.Composited != 0)
		{
			if (AddComponent<SF::LogOutputDebuggerComponent>(m_InitParameter.LogOutputDebugger) == nullptr)
				return ResultCode::FAIL;
		}

		if (m_InitParameter.LogOutputFile.Composited != 0 && m_InitParameter.LogFilePrefix != nullptr)
		{
			if (AddComponent<SF::LogOutputFileComponent>(m_InitParameter.LogOutputFile, m_InitParameter.LogFilePrefix, true) == nullptr)
				return ResultCode::FAIL;
		}

		if (m_InitParameter.NetworkThreadCount > 0)
		{
			AddComponent<SF::Net::NetSystem>(m_InitParameter.NetRecvBufferSize, m_InitParameter.NetSendBufferSize, m_InitParameter.NetworkThreadCount, 1024);
		}


		return ResultCode::SUCCESS;
	}


	// Override initialize/deinitialize components
	Result Engine::InitializeComponents()
	{
		auto result = super::InitializeComponents();

		m_ExitCode = -1;

		if (m_InitParameter.UseEngineThread)
		{
			m_EngineThread = new(GetHeap()) FunctorThread([this](Thread* pThread)
			{
				Service::EngineTaskManager->SetEngineThreadID(ThisThread::GetThreadID());

				DurationMS durationMS = m_TickInterval;
				while (GetExitCode() < 0 && !pThread->CheckKillEvent(durationMS))
				{
					auto pEngine = Engine::GetInstance();
					if (pEngine == nullptr) break;

					Service::EngineTaskManager->EngineTickUpdate();
					Service::EngineObjectManager->Update();
					Service::GraphicDevice->RequestCommand<RenderCommand_KickFrame>(CallTrack());

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

	bool Engine::TickUpdate()
	{
		auto pEngine = Engine::GetInstance();
		if (pEngine == nullptr)
			return false;

		DurationMS durationMS = pEngine->m_TickInterval;

		if (pEngine->GetExitCode() >= 0)
			return false;

		durationMS = pEngine->UpdateInterval(pEngine->m_TickInterval);
		ThisThread::SleepFor(durationMS);

		Service::EngineObjectManager->Update();
		Service::EngineTaskManager->EngineTickUpdate();
		Service::GraphicDevice->RequestCommand<RenderCommand_KickFrame>(CallTrack());

		return true;
	}




}; // namespace SF


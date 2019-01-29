////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Rendering thread
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/SFRenderThread.h"
#include "Graphics/SFGraphicDevice.h"
#include "Service/SFEngineService.h"


namespace SF
{

	RenderThread::RenderThread(GraphicDevice* pDevice)
		: Thread("RenderThread")
		, m_pDevice(pDevice)
	{
	}

	RenderThread::~RenderThread()
	{
	}

	void RenderThread::Run()
	{
		Service::EngineTaskManager->SetRenderThreadID(ThisThread::GetThreadID());

		while (!CheckKillEvent(DurationMS(0)))
		{
			if (m_pDevice == nullptr)
				break;

			// Run queued command
			// Kicking a frame also will be a command
			m_pDevice->RunOneFrame();
		}
	}


}


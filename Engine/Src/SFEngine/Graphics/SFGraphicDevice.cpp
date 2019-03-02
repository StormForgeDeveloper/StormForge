////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : GraphicDevice base class
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Platform/SFNativeWindow.h"
#include "Graphics/SFGraphicDevice.h"
#include "Graphics/SFRenderCommand.h"
#include "Graphics/SFRenderTargetChain.h"
#include "Service/SFEngineService.h"
#include "Resource/SFDeviceResource.h"
#include "Task/SFTask.h"


namespace SF
{





	GraphicDevice::GraphicDevice()
		: m_Heap("Graphics", GetEngineHeap())
		, m_RenderThread(this)
		, m_DrawingFrameIndex(0)
		, m_SharedObjectManager(GetEngineHeap())
		, m_ComponentDependency(m_Heap)
	{
	}

	GraphicDevice::~GraphicDevice()
	{
	}

	void GraphicDevice::SetWindow(NativeWindow nativeWindow, int width, int height)
	{
		m_NativeWindow = nativeWindow;
		m_Width = width;
		m_Height = height;
	}

	// Initialize component
	Result GraphicDevice::Initialize()
	{
		m_RenderThread.Start();

		Service::GraphicDevice = this;

		return ResultCode::SUCCESS;
	}

	// Terminate component
	void GraphicDevice::Deinitialize()
	{
		m_RenderThread.Stop(true);

		while (true)
		{
			auto pBufferItem = m_RenderCommandQueue.DequeueRead();
			if (pBufferItem == nullptr)
				break;

			auto pCmd = (RenderCommand*)pBufferItem->GetDataPtr();
			pCmd->~RenderCommand();

			m_RenderCommandQueue.ReleaseRead(pBufferItem);
		}

		m_RenderCommandQueue.Clear();

		DeinitDisplay();

		Service::GraphicDevice = nullptr;
	}

	void GraphicDevice::InitDisplay(NativeWindow pWindow)
	{
		m_NativeWindow = pWindow;
		m_Width = NativeWindow_GetWidth(m_NativeWindow);
		m_Height = NativeWindow_GetHeight(m_NativeWindow);
	}

	void GraphicDevice::DeinitDisplay()
	{
		if (m_RenderTargetChain != nullptr)
			m_RenderTargetChain->Dispose();
		m_RenderTargetChain = nullptr;

		m_NativeWindow = (NativeWindow)nullptr;
	}

	void GraphicDevice::OnResize()
	{
		if (m_NativeWindow == (NativeWindow)nullptr)
			return;

		m_Width = NativeWindow_GetWidth(m_NativeWindow);
		m_Height = NativeWindow_GetHeight(m_NativeWindow);
	}


	// Register shared object
	void GraphicDevice::RegisterSharedObject(SharedObject* pSharedObject)
	{
		m_SharedObjectManager.RegisterSharedObject(pSharedObject);

		auto pDeviceResource = static_cast<DeviceResource*>(pSharedObject);

		m_DeviceResources.Add(&pDeviceResource->GetListNodeForDevice());
	}


	// Free shared object
	void GraphicDevice::FreeSharedReference(SharedObject* pSharedObject
#ifdef REFERENCE_DEBUG_TRACKING
		, const char* fileName = __BASE_FILE__, int lineNumber
#endif
	)
	{
		auto pDeviceResource = static_cast<DeviceResource*>(pSharedObject);
		m_DeviceResources.Remove(&pDeviceResource->GetListNodeForDevice());

		m_SharedObjectManager.FreeSharedReference(pSharedObject);
	}


	void GraphicDevice::AddDependency(FixedString dependency)
	{
		m_ComponentDependency.push_back(dependency);
	}

	// Frame begin/end
	bool GraphicDevice::BeginFrame()
	{
		auto oldValue = m_DrawingFrameIndex.fetch_add(1, std::memory_order_acquire);
		unused(oldValue);
		assert((oldValue & 1) == 0);
		return true;
	}

	void GraphicDevice::RenderFrame()
	{
	}

	void GraphicDevice::EndFrame()
	{
		auto oldValue = m_DrawingFrameIndex.fetch_add(1, std::memory_order_release);
		unused(oldValue);
		assert((oldValue & 1) == 1);
	}




	// Flush command queue for a frame
	Result GraphicDevice::RunOneFrame(DurationMS waitingTimeOut)
	{
		auto timeStart = Util::Time.GetRawTimeMs();

		auto waitingFrameIndex = m_DrawingFrameIndex.load(std::memory_order_consume) + 2;
		do {

			auto pBufferItem = m_RenderCommandQueue.DequeueRead();
			if (pBufferItem == nullptr)
			{
				// No Command to wait
				auto curFrameIndex = m_DrawingFrameIndex.load(std::memory_order_consume);
				// We can't quit when frame begin is called already
				if (Util::TimeSinceRaw(timeStart) > waitingTimeOut 
					&& ((curFrameIndex&1) == 0))
				{
					// Waiting timeout
					return ResultCode::UNEXPECTED;
				}

				// We need to wait frame start and frame end
				ThisThread::SleepFor(DurationMS(0));
			}
			else
			{
				auto pCmd = (RenderCommand*)pBufferItem->GetDataPtr();


				auto pTask = pCmd->GetNotificationTask();
				if (pTask != nullptr)
				{
					TaskOperator().StartWorking(*pTask);
					pCmd->RunCommand(this);
					TaskOperator().Finished(*pTask);
				}
				else
				{
					pCmd->RunCommand(this);
				}

				m_RenderCommandQueue.ReleaseRead(pBufferItem);

				auto curFrameIndex = m_DrawingFrameIndex.load(std::memory_order_consume);
				if (curFrameIndex >= waitingFrameIndex)
					break;
			}

		} while (1);

		return ResultCode::SUCCESS;
	}

}


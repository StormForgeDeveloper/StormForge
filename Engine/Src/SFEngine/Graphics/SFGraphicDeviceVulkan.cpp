////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan Graphic Device
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFEngine.h"
#include "Graphics/SFGraphicDeviceVulkan.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"
#include "Graphics/Vulkan/SFVulkanPhysicalDevice.h"
#include "Graphics/Vulkan/SFVulkanLogicalDevice.h"
#include "Graphics/Vulkan/SFRenderTargetChainVulkan.h"
#include "Graphics/Vulkan/SFVulkanRenderPass.h"


#if HAVE_VULKAN



namespace SF
{


	GraphicDeviceVulkan::GraphicDeviceVulkan()
		: m_GraphicsQueue(VK_NULL_HANDLE)
	{
	}

	GraphicDeviceVulkan::~GraphicDeviceVulkan()
	{
		assert(m_RenderPass == nullptr);
	}



	// Select device
	VkPhysicalDevice GraphicDeviceVulkan::SelectDevice()
	{
		if (m_VKSystem == nullptr)
			return nullptr;

		VkPhysicalDevice selectedDevice = nullptr;
		for (auto itDevice : m_VKSystem->GetPhysicalDevices())
		{
			if (selectedDevice == nullptr)
			{
				selectedDevice = itDevice;
				continue;
			}


			// TODO: add device detection
		}


		return selectedDevice;
	}



	// Initialize component
	Result GraphicDeviceVulkan::Initialize()
	{
		GraphicDevice::Initialize();

		m_VKSystem = Engine::GetEngineComponent<VulkanSystem>();
		if (m_VKSystem == nullptr)
			return ResultCode::UNEXPECTED;

		auto phyDevice = SelectDevice();
		if(phyDevice == nullptr)
		{
			return ResultCode::UNEXPECTED;
		}

		m_PhysicalDevice = m_VKSystem->CreatePhysicalDevice(GetHeap(), phyDevice);
		if(m_PhysicalDevice == nullptr)
			return ResultCode::OUT_OF_MEMORY;


		return ResultCode::SUCCESS;
	}

	// Terminate component
	void GraphicDeviceVulkan::Deinitialize()
	{
		GraphicDevice::Deinitialize();

		delete m_RenderPass;
		m_RenderPass = nullptr;

		m_LogicalDevice = nullptr;

		if (m_PhysicalDevice != nullptr)
			delete m_PhysicalDevice;
		m_PhysicalDevice = nullptr;

		m_VKSystem = nullptr;

	}

	void GraphicDeviceVulkan::InitDisplay(NativeWindow pWindow)
	{
		GraphicDevice::InitDisplay(pWindow);

		SharedPointerT<RenderTargetChainVulkan> pRenderTargetChain = new(GetHeap()) RenderTargetChainVulkan(GetHeap(), this);
		auto result = pRenderTargetChain->Initialize(2, false);
		if(!result)
			return;

		SetRenderTargetChain(pRenderTargetChain.StaticCast<RenderTargetChain>());

		// Let's create all of them for now
		VulkanDeviceInitParameter parameter = {};
		parameter.UsageGraphic = true;
		parameter.UsageCompute = true;
		parameter.UsageTransfer = true;
		parameter.EnableSwapChain = true;
		parameter.Surface = pRenderTargetChain->GetVKSurface();

		m_LogicalDevice = m_PhysicalDevice->CreateLogicalDevice(GetHeap(), parameter);
		if (m_LogicalDevice == nullptr)
			return;

		// Get a graphics queue from the device
		m_LogicalDevice->GetGraphicsQueue(m_GraphicsQueue);


		VkSemaphoreCreateInfo semaphoreCreateInfo = {};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		result = vkCreateSemaphore(m_LogicalDevice->GetLogicalDevice(), &semaphoreCreateInfo, nullptr, &m_SemaphoreRenderComplete);
		if (result != VK_SUCCESS)
		{
			return;
		}

		// If window has positive extent, create render chain
		if (GetWidth() == 0 && GetHeight() == 0)
			return;

		m_RenderPass = new(GetHeap()) VulkanRenderPass(GetHeap(), m_LogicalDevice);
		m_RenderPass->SetupRenderPass(*pRenderTargetChain);

		pRenderTargetChain->OnResize(m_RenderPass->GetDeviceRenderPass());

	}

	void GraphicDeviceVulkan::DeinitDisplay()
	{
		if (m_LogicalDevice != nullptr)
			m_LogicalDevice->FlushCommandQueue();

		// Render chain has to be deinitialized before logical device is deleted
		GraphicDevice::DeinitDisplay();

		IHeap::Delete(m_RenderPass);
		m_RenderPass = nullptr;

		if(m_SemaphoreRenderComplete != VK_NULL_HANDLE)
			vkDestroySemaphore(m_LogicalDevice->GetLogicalDevice(), m_SemaphoreRenderComplete, nullptr);
		m_SemaphoreRenderComplete = VK_NULL_HANDLE;

		if (m_LogicalDevice != nullptr)
			m_LogicalDevice->Dispose();
		m_LogicalDevice = nullptr;
	}

	void GraphicDeviceVulkan::OnResize()
	{
		GraphicDevice::OnResize();

		if (GetRenderTargetChain() != nullptr)
		{
			auto pRenderTarget = (RenderTargetChainVulkan*)GetRenderTargetChain();
			pRenderTarget->OnResize(m_RenderPass->GetDeviceRenderPass());
		}
	}

	bool GraphicDeviceVulkan::BeginFrame()
	{
		// Skip if not initialized
		if (m_LogicalDevice == nullptr || GetNativeWindow() == nullptr)
			return false;

		if (!GraphicDevice::BeginFrame())
			return false;


		auto pRenderTarget = (RenderTargetChainVulkan*)GetRenderTargetChain();
		pRenderTarget->BeginRendering(m_LogicalDevice->GetLogicalDevice());

		return true;
	}

	void GraphicDeviceVulkan::RenderFrame()
	{
		
	}

	void GraphicDeviceVulkan::EndFrame()
	{
		// Skip if not initialized
		if (m_LogicalDevice == nullptr || GetNativeWindow() == nullptr)
			return;
		auto pRenderTarget = (RenderTargetChainVulkan*)GetRenderTargetChain();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pWaitDstStageMask = &m_SubmitPipelineStages;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &pRenderTarget->GetPresentSemaphore();
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &m_SemaphoreRenderComplete;

		submitInfo.commandBufferCount = 0;
		//submitInfo.pCommandBuffers = &drawCmdBuffers[currentBuffer];

		auto result = vkQueueSubmit(m_GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		if (result != VK_SUCCESS)
		{

		}

		pRenderTarget->EndRendering(m_GraphicsQueue);

		GraphicDevice::EndFrame();
	}



	///////////////////////////////////////////////////////////////////////////////////
	//
	//	Resource handling
	//



	DeviceTexture* GraphicDeviceVulkan::CreateTexture(const TextureInitParameter& initParameters)
	{
		return nullptr;
	}


	DeviceResource* GraphicDeviceVulkan::CreateBuffer()
	{
		return nullptr;
	}


}

#else
void GraphicDeviceVulkan_Dummy() {}
#endif

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan Graphic Device
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Graphics/SFGraphicDevice.h"

#if HAVE_VULKAN

#include "Graphics/Vulkan/SFVulkanSystem.h"
#include "Graphics/Vulkan/SFVulkanLogicalDevice.h"


namespace SF
{
	class VulkanDebug;
	class VulkanPhysicalDevice;
	class VulkanLogicalDevice;
	class VulkanRenderPass;


	////////////////////////////////////////////////////////////////////
	//
	//	Render command
	//
	class GraphicDeviceVulkan : public GraphicDevice
	{
	private:

		// Vulkan system
		VulkanSystem *m_VKSystem = nullptr;

		// Vulkan physical device
		VulkanPhysicalDevice* m_PhysicalDevice = nullptr;

		// Vulkan logical device, This object will be shared over multiple objects
		SharedPointerT<VulkanLogicalDevice> m_LogicalDevice;

		// Current Rendering pass
		VulkanRenderPass* m_RenderPass = nullptr;

		// Graphics queue
		VkQueue m_GraphicsQueue;

		// swap flag
		VkPipelineStageFlags m_SubmitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		// semaphore for rendering queue
		VkSemaphore m_SemaphoreRenderComplete = VK_NULL_HANDLE;

	protected:

		// Select device
		VkPhysicalDevice SelectDevice();

	public:
		GraphicDeviceVulkan();
		virtual ~GraphicDeviceVulkan();


		// Initialize component
		virtual Result Initialize() override;
		// Terminate component
		virtual void Deinitialize() override;


		virtual void InitDisplay(NativeWindow pWindow) override;
		virtual void DeinitDisplay() override;
		virtual void OnResize() override;


		virtual bool BeginFrame() override;
		virtual void RenderFrame() override;
		virtual void EndFrame() override;


		VulkanSystem *GetVKSystem() { return m_VKSystem; }
		VulkanPhysicalDevice *GetVKPhysicalDevice() { return m_PhysicalDevice; }
		VulkanLogicalDevice *GetVKLogicalDevice() { return m_LogicalDevice.GetObjectPtr(); }



		///////////////////////////////////////////////////////////////////////////////////
		//
		//	Resource handling
		//

		virtual DeviceTexture* CreateTexture(const TextureInitParameter& initParameters) override;
		virtual DeviceResource* CreateBuffer() override;

	};




}


#endif

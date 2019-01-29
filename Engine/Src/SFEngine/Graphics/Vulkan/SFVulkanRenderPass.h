////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan render pass
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#if HAVE_VULKAN

#include "Resource/SFDeviceTexture.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"

namespace SF
{
	class VulkanLogicalDevice;
	class RenderTargetChainVulkan;

	////////////////////////////////////////////////////////////////////
	//
	//	Resource
	//
	class VulkanRenderPass
	{
	private:

		SharedPointerT<VulkanLogicalDevice> m_pLogicalDevice;
		VkRenderPass m_VKRenderPass;

	public:
		VulkanRenderPass(IHeap& heap, SharedPointerT<VulkanLogicalDevice>& pDevice);
		virtual ~VulkanRenderPass();

		VulkanLogicalDevice* GetLogicalDevice() { return m_pLogicalDevice.GetObjectPtr(); }
		VkRenderPass GetDeviceRenderPass() { return m_VKRenderPass; }

		// Setup render pass
		VkResult SetupRenderPass(RenderTargetChainVulkan* pRenderTargetChain);

		// Destroy
		void Destroy();
	};



}

#endif //#if HAVE_VULKAN


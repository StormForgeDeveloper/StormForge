////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Rendering thread
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFDeviceResource.h"
#include "Graphics/SFRenderTargetChain.h"


#if SF_USE_VULKAN

#include "Graphics/Vulkan/SFVulkanSystem.h"


namespace SF
{
	class GraphicDeviceVulkan;
	class VulkanLogicalDevice;


	struct RenderTargetChainVulkan_SwapChainImage {
		VkImage Image;
		VkImageView View;
		VkFramebuffer FrameBuffer;

		RenderTargetChainVulkan_SwapChainImage() { memset(this, 0, sizeof(RenderTargetChainVulkan_SwapChainImage)); }
	};



	////////////////////////////////////////////////////////////////////
	//
	//	Render target chain
	//

	class RenderTargetChainVulkan : public RenderTargetChain
	{
	public:
		typedef RenderTargetChainVulkan_SwapChainImage SwapChainImage;

	private:

		// VK screen surface
		VkSurfaceKHR m_VKSurface;

		VkSwapchainKHR m_VKSwapChain;

		StaticArray<SwapChainImage, 4> m_SwapChainImages;

		VkFormat m_ColorFormat;
		VkColorSpaceKHR m_ColorSpace;
		VkFormat m_DepthFormat;

		VkSurfaceCapabilitiesKHR m_SurfaceCaps;

		DynamicArray<VkPresentModeKHR> m_PresentModes;

		// Selected Present mode
		VkPresentModeKHR m_SelectedPresentMode;

		bool m_VSync;

		// Selected image size
		uint32_t m_Width;
		uint32_t m_Height;

		// Selected image transform
		VkSurfaceTransformFlagBitsKHR m_ImageTransform;

		VkCompositeAlphaFlagBitsKHR m_SelectedCompositeAlpha;

		// Depth stencil 
		VkImage m_VKDepthStencilImage;
		VkDeviceMemory m_VKDepthStencilMemory;
		VkImageView m_VKDepthStencilView;



		// semaphore for present
		VkSemaphore m_SemaphorePresent;

		uint32_t m_SwapImageIndex = 0;

	private:

		VkResult SelectPresentMode();
		VkResult SelectImageFormat();
		VkResult SelectImageSize(uint32_t suggestWidth, uint32_t suggestHeight);
		VkResult SelectCompositAlpha();
		VkResult CreateChainImages();
		VkResult CreateDepthStencil(VulkanLogicalDevice* pDevice, VkFormat depthStencilFormat);

		void DestroySwapChain(VkDevice logicalDevice, VkSwapchainKHR swapChain);

	public:
		RenderTargetChainVulkan(IHeap& heap, GraphicDeviceVulkan* pDevice);
		virtual ~RenderTargetChainVulkan();

		virtual void Dispose() override;

		VkSwapchainKHR GetSwapChain() { return m_VKSwapChain; }
		VkSurfaceKHR GetVKSurface() { return m_VKSurface; }
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		VkFormat GetColorFormat() const { return m_ColorFormat; }
		VkFormat GetDepthStencilFormat() const { return m_DepthFormat; }

		const VkSemaphore& GetPresentSemaphore() { return m_SemaphorePresent; }

		// Initialize Render target chain
		virtual Result Initialize(int numChain, bool vsync = false) override;

		// Resize render target chain
		virtual Result OnResize(VkRenderPass renderPass);

		// After initialize render pass, frame buffer better to be recreated
		VkResult CreateFrameBuffer(VulkanLogicalDevice* pDevice, VkRenderPass renderPass);

		// Present
		VkResult BeginRendering(VkDevice logicalDevice);
		VkResult EndRendering(VkQueue queue);
	};




}

#endif // SF_USE_VULKAN

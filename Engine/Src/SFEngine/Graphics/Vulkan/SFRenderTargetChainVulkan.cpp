////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render target chain
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"

#if HAVE_VULKAN


#include "Graphics/Vulkan/SFVulkanSystem.h"
#include "Graphics/Vulkan/SFRenderTargetChainVulkan.h"
#include "Graphics/Vulkan/SFVulkanPhysicalDevice.h"
#include "Graphics/SFGraphicDeviceVulkan.h"
#include "SFEngine.h"



namespace SF
{

	RenderTargetChainVulkan::RenderTargetChainVulkan(IHeap& heap, GraphicDeviceVulkan* pDevice)
		: RenderTargetChain(heap, pDevice)
		, m_VKSurface(VK_NULL_HANDLE)
		, m_VKSwapChain(VK_NULL_HANDLE)
		, m_SwapChainImages(heap)
		, m_ColorFormat(VK_FORMAT_B8G8R8A8_UNORM)
		, m_ColorSpace(VK_COLORSPACE_SRGB_NONLINEAR_KHR)
		, m_DepthFormat(VK_FORMAT_R16_UNORM)
		, m_PresentModes(heap)
		, m_SelectedPresentMode(VK_PRESENT_MODE_FIFO_KHR)
		, m_VSync(false)
		, m_Width(0)
		, m_Height(0)
		, m_ImageTransform(VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
		, m_SelectedCompositeAlpha(VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
		, m_VKDepthStencilImage(VK_NULL_HANDLE)
		, m_VKDepthStencilMemory(VK_NULL_HANDLE)
		, m_VKDepthStencilView(VK_NULL_HANDLE)
		, m_SemaphorePresent(VK_NULL_HANDLE)
		, m_SwapImageIndex(0)
	{
		memset(&m_SurfaceCaps, 0, sizeof(m_SurfaceCaps));
	}

	RenderTargetChainVulkan::~RenderTargetChainVulkan()
	{
	}

	void RenderTargetChainVulkan::Dispose()
	{
		auto pDevice = static_cast<GraphicDeviceVulkan*>(GetGraphicDevice());
		auto pSystem = pDevice->GetVKSystem();
		if (pSystem != nullptr)
		{
			auto pLogicalDevice = pDevice->GetVKLogicalDevice();
			if (m_VKSwapChain != VK_NULL_HANDLE)
			{
				if (pLogicalDevice != nullptr)
				{
					DestroySwapChain(pLogicalDevice->GetLogicalDevice(), m_VKSwapChain);
				}
				m_VKSwapChain = VK_NULL_HANDLE;
			}


			if (m_SemaphorePresent != VK_NULL_HANDLE && pLogicalDevice != nullptr)
				vkDestroySemaphore(pLogicalDevice->GetLogicalDevice(), m_SemaphorePresent, nullptr);


			if (m_VKSurface != VK_NULL_HANDLE)
				vkDestroySurfaceKHR(pSystem->GetVKInstance(), m_VKSurface, nullptr);
			m_VKSurface = VK_NULL_HANDLE;
		}

		RenderTargetChain::Dispose();
	}


	VkResult RenderTargetChainVulkan::SelectPresentMode()
	{
		auto pDevice = static_cast<GraphicDeviceVulkan*>(GetGraphicDevice());
		auto pPhysicalDevice = pDevice->GetVKPhysicalDevice();

		// Get available present modes
		uint32_t presentModeCount;
		auto result = vkGetPhysicalDeviceSurfacePresentModesKHR(pPhysicalDevice->GetPhysicalDevice(), m_VKSurface, &presentModeCount, NULL);
		if (result != VK_SUCCESS)
			return result;

		m_PresentModes.resize(presentModeCount);
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(pPhysicalDevice->GetPhysicalDevice(), m_VKSurface, &presentModeCount, m_PresentModes.data());
		if (result != VK_SUCCESS)
			return result;



		// Initially fifo mode(vsync)
		static const int PresentModePriority[VK_PRESENT_MODE_RANGE_SIZE_KHR] =
		{
			2, //VK_PRESENT_MODE_IMMEDIATE_KHR = 0,
			1, //VK_PRESENT_MODE_MAILBOX_KHR = 1,
			3, //VK_PRESENT_MODE_FIFO_KHR = 2,
			4, //VK_PRESENT_MODE_FIFO_RELAXED_KHR = 3,
		};

		m_SelectedPresentMode = m_VSync ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_FIFO_RELAXED_KHR;
		int selectedPriority = PresentModePriority[m_SelectedPresentMode];
		if (!m_VSync)
		{
			for (auto itPresentMode : m_PresentModes)
			{
				if ((int)itPresentMode < 0 || itPresentMode > countof(PresentModePriority))
					continue;

				if (selectedPriority < PresentModePriority[itPresentMode])
				{
					m_SelectedPresentMode = itPresentMode;
					selectedPriority = PresentModePriority[itPresentMode];
				}
			}
		}

		return VK_SUCCESS;
	}

	VkResult RenderTargetChainVulkan::SelectImageFormat()
	{
		auto pDevice = static_cast<GraphicDeviceVulkan*>(GetGraphicDevice());
		auto pPhysicalDevice = pDevice->GetVKPhysicalDevice();

		// Get list of supported surface formats
		uint32_t formatCount;
		auto result = vkGetPhysicalDeviceSurfaceFormatsKHR(pPhysicalDevice->GetPhysicalDevice(), m_VKSurface, &formatCount, NULL);
		if (result != VK_SUCCESS)
			return result;
		assert(formatCount > 0);

		std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(pPhysicalDevice->GetPhysicalDevice(), m_VKSurface, &formatCount, surfaceFormats.data());
		if (result != VK_SUCCESS)
			return result;


		// TODO: support preference
		// If the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
		// there is no preferred format, so we assume VK_FORMAT_B8G8R8A8_UNORM
		if ((formatCount == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED))
		{
			m_ColorFormat = VK_FORMAT_B8G8R8A8_UNORM;
			m_ColorSpace = surfaceFormats[0].colorSpace;
		}
		else
		{
			// iterate over the list of available surface format and
			// check for the presence of VK_FORMAT_B8G8R8A8_UNORM
			bool found_B8G8R8A8_UNORM = false;
			for (auto& surfaceFormat : surfaceFormats)
			{
				if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
				{
					m_ColorFormat = surfaceFormat.format;
					m_ColorSpace = surfaceFormat.colorSpace;
					found_B8G8R8A8_UNORM = true;
					break;
				}
			}

			// in case VK_FORMAT_B8G8R8A8_UNORM is not available
			// select the first available color format
			if (!found_B8G8R8A8_UNORM)
			{
				m_ColorFormat = surfaceFormats[0].format;
				m_ColorSpace = surfaceFormats[0].colorSpace;
			}
		}

		return VK_SUCCESS;
	}

	VkResult RenderTargetChainVulkan::SelectImageSize(uint32_t suggestWidth, uint32_t suggestHeight)
	{
		// Determine size
		VkExtent2D swapchainExtent = {};
		// If width (and height) equals the special value 0xFFFFFFFF, the size of the surface will be set by the swapchain
		if (m_SurfaceCaps.currentExtent.width == (uint32_t)-1)
		{
			// If the surface size is undefined, the size is set to
			// the size of the images requested.
			m_Width = suggestWidth;
			m_Height = suggestHeight;
		}
		else
		{
			// If the surface size is defined, the swap chain size must match
			swapchainExtent = m_SurfaceCaps.currentExtent;
			m_Width = m_SurfaceCaps.currentExtent.width;
			m_Height = m_SurfaceCaps.currentExtent.height;
		}

		return VK_SUCCESS;
	}


	VkResult RenderTargetChainVulkan::SelectCompositAlpha()
	{
		// Find a supported composite alpha format (not all devices support alpha opaque)
		m_SelectedCompositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		// Simply select the first composite alpha format available
		const static VkCompositeAlphaFlagBitsKHR possibleCompositeAlphaFlags[] = {
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
		};

		for (auto& compositeAlphaFlag : possibleCompositeAlphaFlags) {
			if (m_SurfaceCaps.supportedCompositeAlpha & compositeAlphaFlag) {
				m_SelectedCompositeAlpha = compositeAlphaFlag;
				break;
			};
		}

		return VK_SUCCESS;
	}


	VkResult RenderTargetChainVulkan::CreateChainImages()
	{
		auto pDevice = static_cast<GraphicDeviceVulkan*>(GetGraphicDevice());
		auto pPhysicalDevice = pDevice->GetVKPhysicalDevice();
		auto pLogicalDevice = pDevice->GetVKLogicalDevice();

		auto oldSwapChain = m_VKSwapChain;

		VkSwapchainCreateInfoKHR swapchainCI = {};
		swapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCI.pNext = NULL;
		swapchainCI.surface = m_VKSurface;
		swapchainCI.minImageCount = (decltype(swapchainCI.minImageCount))m_SwapChainImages.size();
		swapchainCI.imageFormat = m_ColorFormat;
		swapchainCI.imageColorSpace = m_ColorSpace;
		swapchainCI.imageExtent = { m_Width, m_Height };
		swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCI.preTransform = m_ImageTransform;
		swapchainCI.imageArrayLayers = 1;
		swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCI.queueFamilyIndexCount = 0;
		swapchainCI.pQueueFamilyIndices = NULL;
		swapchainCI.presentMode = m_SelectedPresentMode;
		swapchainCI.oldSwapchain = oldSwapChain;
		// Setting clipped to VK_TRUE allows the implementation to discard rendering outside of the surface area
		swapchainCI.clipped = VK_TRUE;
		swapchainCI.compositeAlpha = m_SelectedCompositeAlpha;

		// Set additional usage flag for bliting from the swapchain images if supported
		VkFormatProperties formatProps;
		vkGetPhysicalDeviceFormatProperties(pPhysicalDevice->GetPhysicalDevice(), m_ColorFormat, &formatProps);
		if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) {
			swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		}

		auto result = vkCreateSwapchainKHR(pLogicalDevice->GetLogicalDevice(), &swapchainCI, nullptr, &m_VKSwapChain);
		if (result != VK_SUCCESS)
			return result;

		// If an existing swap chain is re-created, destroy the old swap chain
		// This also cleans up all the presentable images
		DestroySwapChain(pLogicalDevice->GetLogicalDevice(), oldSwapChain);


		uint32_t imageCount = 0;
		result = vkGetSwapchainImagesKHR(pLogicalDevice->GetLogicalDevice(), m_VKSwapChain, &imageCount, NULL);
		if (result != VK_SUCCESS)
			return result;

		// Get the swap chain images
		StaticArray<VkImage, 8> images(GetHeap());
		images.resize(imageCount);
		result = vkGetSwapchainImagesKHR(pLogicalDevice->GetLogicalDevice(), m_VKSwapChain, &imageCount, images.data());
		if (result != VK_SUCCESS)
			return result;

		// Get the swap chain buffers containing the image and image view
		m_SwapChainImages.resize(imageCount);
		for (uint32_t iImg = 0; iImg < imageCount; iImg++)
		{
			VkImageViewCreateInfo colorAttachmentView = {};
			colorAttachmentView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			colorAttachmentView.pNext = NULL;
			colorAttachmentView.format = m_ColorFormat;
			colorAttachmentView.components = {
				VK_COMPONENT_SWIZZLE_R,
				VK_COMPONENT_SWIZZLE_G,
				VK_COMPONENT_SWIZZLE_B,
				VK_COMPONENT_SWIZZLE_A
			};
			colorAttachmentView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			colorAttachmentView.subresourceRange.baseMipLevel = 0;
			colorAttachmentView.subresourceRange.levelCount = 1;
			colorAttachmentView.subresourceRange.baseArrayLayer = 0;
			colorAttachmentView.subresourceRange.layerCount = 1;
			colorAttachmentView.viewType = VK_IMAGE_VIEW_TYPE_2D;
			colorAttachmentView.flags = 0;

			m_SwapChainImages[iImg].Image = images[iImg];

			colorAttachmentView.image = m_SwapChainImages[iImg].Image;

			result = vkCreateImageView(pLogicalDevice->GetLogicalDevice(), &colorAttachmentView, nullptr, &m_SwapChainImages[iImg].View);
		}

		return VK_SUCCESS;
	}

	VkResult RenderTargetChainVulkan::CreateDepthStencil(VulkanLogicalDevice* pDevice, VkFormat depthStencilFormat)
	{
		VkImageCreateInfo imageInfo = {};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.pNext = NULL;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.format = depthStencilFormat;
		imageInfo.extent = { GetWidth(), GetHeight(), 1 };
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		imageInfo.flags = 0;


		auto result = vkCreateImage(pDevice->GetLogicalDevice(), &imageInfo, nullptr, &m_VKDepthStencilImage);
		if (result != VK_SUCCESS)
			return result;

		VkMemoryRequirements memReqs;
		vkGetImageMemoryRequirements(pDevice->GetLogicalDevice(), m_VKDepthStencilImage, &memReqs);

		result = pDevice->AllocateDeviceMemory(memReqs, m_VKDepthStencilMemory);
		if (result != VK_SUCCESS)
			return result;

		result = vkBindImageMemory(pDevice->GetLogicalDevice(), m_VKDepthStencilImage, m_VKDepthStencilMemory, 0);
		if (result != VK_SUCCESS)
			return result;


		VkImageViewCreateInfo depthStencilView = {};
		depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		depthStencilView.pNext = NULL;
		depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
		depthStencilView.format = depthStencilFormat;
		depthStencilView.flags = 0;
		depthStencilView.subresourceRange = {};
		depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		depthStencilView.subresourceRange.baseMipLevel = 0;
		depthStencilView.subresourceRange.levelCount = 1;
		depthStencilView.subresourceRange.baseArrayLayer = 0;
		depthStencilView.subresourceRange.layerCount = 1;
		depthStencilView.image = m_VKDepthStencilImage;
		result = vkCreateImageView(pDevice->GetLogicalDevice(), &depthStencilView, nullptr, &m_VKDepthStencilView);

		return result;
	}

	VkResult RenderTargetChainVulkan::CreateFrameBuffer(VulkanLogicalDevice* pDevice, VkRenderPass renderPass)
	{
		VkImageView attachments[2];

		// Depth/Stencil attachment is the same for all frame buffers
		attachments[1] = m_VKDepthStencilView;

		VkFramebufferCreateInfo frameBufferCreateInfo = {};
		frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		frameBufferCreateInfo.pNext = NULL;
		frameBufferCreateInfo.renderPass = renderPass;
		frameBufferCreateInfo.attachmentCount = 2;
		frameBufferCreateInfo.pAttachments = attachments;
		frameBufferCreateInfo.width = GetWidth();
		frameBufferCreateInfo.height = GetHeight();
		frameBufferCreateInfo.layers = VK_IMAGE_LAYOUT_GENERAL;

		// Create frame buffers for every swap chain image
		for (uint32_t iImg = 0; iImg < m_SwapChainImages.size(); iImg++)
		{
			attachments[0] = m_SwapChainImages[iImg].View;
			auto result = vkCreateFramebuffer(pDevice->GetLogicalDevice(), &frameBufferCreateInfo, nullptr, &m_SwapChainImages[iImg].FrameBuffer);
			if (result != VK_SUCCESS)
				return result;
		}

		return VK_SUCCESS;
	}


	void RenderTargetChainVulkan::DestroySwapChain(VkDevice logicalDevice, VkSwapchainKHR swapChain)
	{
		if (swapChain == VK_NULL_HANDLE)
			return;

		// Destroy depth stencil
		if(m_VKDepthStencilView != VK_NULL_HANDLE)
			vkDestroyImageView(logicalDevice, m_VKDepthStencilView, nullptr);
		if(m_VKDepthStencilImage != VK_NULL_HANDLE)
			vkDestroyImage(logicalDevice, m_VKDepthStencilImage, nullptr);
		if(m_VKDepthStencilMemory != VK_NULL_HANDLE)
			vkFreeMemory(logicalDevice, m_VKDepthStencilMemory, nullptr);

		m_VKDepthStencilView = VK_NULL_HANDLE;
		m_VKDepthStencilImage = VK_NULL_HANDLE;
		m_VKDepthStencilMemory = VK_NULL_HANDLE;


		for (auto& itSwapChainImage : m_SwapChainImages)
		{
			vkDestroyImageView(logicalDevice, itSwapChainImage.View, nullptr);
			vkDestroyFramebuffer(logicalDevice, itSwapChainImage.FrameBuffer, nullptr);
		}
		vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);
		m_SwapChainImages.Clear();
	}

	// Initialize Render target chain
	Result RenderTargetChainVulkan::Initialize(int numChain, bool vsync)
	{
		VkResult result = VK_SUCCESS;

		VkSurfaceKHR surface;
		auto pDevice = static_cast<GraphicDeviceVulkan*>(GetGraphicDevice());
		auto pSystem = pDevice->GetVKSystem();
		auto pPhysicalDevice = pDevice->GetVKPhysicalDevice();

		if (pDevice == nullptr || pSystem == nullptr || pPhysicalDevice == nullptr)
			return ResultCode::ENGINE_INITIALIZATION_FAILED;

		m_VSync = vsync;

		SetNumberOfChain(numChain);

#if defined(VK_USE_PLATFORM_WIN32_KHR)
		static const char AddrString[] = "TestString";
		HMODULE hModule;
		GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, AddrString, &hModule);
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hinstance = hModule;
		surfaceCreateInfo.hwnd = pDevice->GetNativeWindow();
		result = vkCreateWin32SurfaceKHR(pSystem->GetVKInstance(), &surfaceCreateInfo, nullptr, &surface);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
		VkAndroidSurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.window = pDevice->GetNativeWindow();
		result = vkCreateAndroidSurfaceKHR(pSystem->GetVKInstance(), &surfaceCreateInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
		VkIOSSurfaceCreateInfoMVK surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
		surfaceCreateInfo.pNext = NULL;
		surfaceCreateInfo.flags = 0;
		surfaceCreateInfo.pView = pDevice->GetNativeWindow();
		result = vkCreateIOSSurfaceMVK(pSystem->GetVKInstance(), &surfaceCreateInfo, nullptr, &surface);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
		VkMacOSSurfaceCreateInfoMVK surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
		surfaceCreateInfo.pNext = NULL;
		surfaceCreateInfo.flags = 0;
		surfaceCreateInfo.pView = pDevice->GetNativeWindow();
		result = vkCreateMacOSSurfaceMVK(pSystem->GetVKInstance(), &surfaceCreateInfo, NULL, &surface);
#elif defined(_DIRECT2DISPLAY)
		createDirect2DisplaySurface(width, height);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
		VkWaylandSurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.display = display;
		surfaceCreateInfo.surface = pDevice->GetNativeWindow();
		result = vkCreateWaylandSurfaceKHR(pSystem->GetVKInstance(), &surfaceCreateInfo, nullptr, &surface);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
		VkXcbSurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.connection = connection;
		surfaceCreateInfo.window = pDevice->GetNativeWindow();
		result = vkCreateXcbSurfaceKHR(pSystem->GetVKInstance(), &surfaceCreateInfo, nullptr, &surface);
#endif

		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}

		m_VKSurface = surface;


		result = SelectPresentMode();
		if(result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}

		result = SelectImageFormat();
		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}

		return ResultCode::SUCCESS;
	}

	// Resize render target chain
	Result RenderTargetChainVulkan::OnResize(VkRenderPass renderPass)
	{
		auto pDevice = static_cast<GraphicDeviceVulkan*>(GetGraphicDevice());
		auto pSystem = pDevice->GetVKSystem();
		auto pPhysicalDevice = pDevice->GetVKPhysicalDevice();
		auto pLogicalDevice = pDevice->GetVKLogicalDevice();

		if (pDevice == nullptr || pSystem == nullptr || pPhysicalDevice == nullptr)
			return ResultCode::ENGINE_INITIALIZATION_FAILED;

		// if it's already created, skip it
		if (m_VKSwapChain != VK_NULL_HANDLE && GetWidth() == pDevice->GetWidth() && GetHeight() == pDevice->GetHeight())
			return ResultCode::SUCCESS;

		// Surface caps
		auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pPhysicalDevice->GetPhysicalDevice(), m_VKSurface, &m_SurfaceCaps);
		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}


		result = SelectImageSize(pDevice->GetWidth(), pDevice->GetHeight());
		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}


		// Determine the number of swap chain images
		uint32_t desiredImageCount = m_SurfaceCaps.minImageCount + 1;
		desiredImageCount = std::min(desiredImageCount, m_SurfaceCaps.maxImageCount);
		SetNumberOfChain(desiredImageCount);
		m_SwapChainImages.resize(desiredImageCount);


		// Find the transformation of the surface
		if (m_SurfaceCaps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
			m_ImageTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		else
			m_ImageTransform = m_SurfaceCaps.currentTransform;



		result = SelectCompositAlpha();
		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}

		result = CreateChainImages();
		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}

		m_DepthFormat = pPhysicalDevice->SelectDepthStencilFormat();

		result = CreateDepthStencil(pLogicalDevice, m_DepthFormat);
		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}

		result = CreateFrameBuffer(pLogicalDevice, renderPass);
		if (result != VK_SUCCESS)
		{
			pSystem->ReportVKError(result);
			return ResultCode::ENGINE_INITIALIZATION_FAILED;
		}


		if (m_SemaphorePresent == VK_NULL_HANDLE)
		{
			VkSemaphoreCreateInfo semaphoreCreateInfo = {};
			semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			result = vkCreateSemaphore(pLogicalDevice->GetLogicalDevice(), &semaphoreCreateInfo, nullptr, &m_SemaphorePresent);
			if (result != VK_SUCCESS)
			{
				pSystem->ReportVKError(result);
				return ResultCode::ENGINE_INITIALIZATION_FAILED;
			}
		}


		return ResultCode::SUCCESS;
	}


	VkResult RenderTargetChainVulkan::BeginRendering(VkDevice logicalDevice)
	{
		return vkAcquireNextImageKHR(logicalDevice, GetSwapChain(), UINT64_MAX, m_SemaphorePresent, VK_NULL_HANDLE, &m_SwapImageIndex);
	}

	VkResult RenderTargetChainVulkan::EndRendering(VkQueue queue)
	{
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = NULL;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &m_VKSwapChain;
		presentInfo.pImageIndices = &m_SwapImageIndex;
		// Check if a wait semaphore has been specified to wait for before presenting the image
		if (m_SemaphorePresent != VK_NULL_HANDLE)
		{
			presentInfo.pWaitSemaphores = &m_SemaphorePresent;
			presentInfo.waitSemaphoreCount = 1;
		}
		return vkQueuePresentKHR(queue, &presentInfo);
	}


}

#endif // #if HAVE_VULKAN


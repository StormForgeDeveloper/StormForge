////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan library
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFVulkanLibrary.h"


#if HAVE_VULKAN

#if SF_PLATFORM == SF_PLATFORM_ANDROID
#include <dlfcn.h>
#define LOAD_VULKAN_LIBRARY() dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL)
namespace SF
{
	template<class FunctionType>
	FunctionType GetDLLProcAddress(void* dllInstance, const char* procName)
	{
		return reinterpret_cast<FunctionType>(dlsym(dllInstance, procName));
	}
}
#elif SF_PLATFORM == SF_PLATFORM_WINDOWS
#define LOAD_VULKAN_LIBRARY() LoadLibraryA("vulkan-1.dll")
namespace SF
{
	template<class FunctionType>
	FunctionType GetDLLProcAddress(HMODULE dllInstance, const char* procName)
	{
		return reinterpret_cast<FunctionType>(GetProcAddress(dllInstance, procName));
	}
}
#else
#error "Not supported platform"
#endif


#define GET_PROCADDRESS(libvulkan, procName) GetDLLProcAddress<PFN_##procName>(libvulkan, #procName)



namespace SF
{

	bool SFVulkanLibrary_Initialize()
	{
#if SF_VULKAN_DYNAMIC_LIBRARY
		if (vkCreateInstance != nullptr)
			return true;

		auto libvulkan = LOAD_VULKAN_LIBRARY();
		if (!libvulkan)
		{
			assert(false);
			return false;
		}

		// Vulkan supported, set function addresses
		vkCreateInstance = GET_PROCADDRESS(libvulkan, vkCreateInstance);
		vkDestroyInstance = GET_PROCADDRESS(libvulkan, vkDestroyInstance);
		vkEnumeratePhysicalDevices = GET_PROCADDRESS(libvulkan, vkEnumeratePhysicalDevices);
		vkGetPhysicalDeviceFeatures = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceFeatures);
		vkGetPhysicalDeviceFormatProperties = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceFormatProperties);
		vkGetPhysicalDeviceImageFormatProperties = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceImageFormatProperties);
		vkGetPhysicalDeviceProperties = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceProperties);
		vkGetPhysicalDeviceQueueFamilyProperties = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceQueueFamilyProperties);
		vkGetPhysicalDeviceMemoryProperties = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceMemoryProperties);
		vkGetInstanceProcAddr = GET_PROCADDRESS(libvulkan, vkGetInstanceProcAddr);
		vkGetDeviceProcAddr = GET_PROCADDRESS(libvulkan, vkGetDeviceProcAddr);
		vkCreateDevice = GET_PROCADDRESS(libvulkan, vkCreateDevice);
		vkDestroyDevice = GET_PROCADDRESS(libvulkan, vkDestroyDevice);
		vkEnumerateInstanceExtensionProperties = GET_PROCADDRESS(libvulkan, vkEnumerateInstanceExtensionProperties);
		vkEnumerateDeviceExtensionProperties = GET_PROCADDRESS(libvulkan, vkEnumerateDeviceExtensionProperties);
		vkEnumerateInstanceLayerProperties = GET_PROCADDRESS(libvulkan, vkEnumerateInstanceLayerProperties);
		vkEnumerateDeviceLayerProperties = GET_PROCADDRESS(libvulkan, vkEnumerateDeviceLayerProperties);
		vkGetDeviceQueue = GET_PROCADDRESS(libvulkan, vkGetDeviceQueue);
		vkQueueSubmit = GET_PROCADDRESS(libvulkan, vkQueueSubmit);
		vkQueueWaitIdle = GET_PROCADDRESS(libvulkan, vkQueueWaitIdle);
		vkDeviceWaitIdle = GET_PROCADDRESS(libvulkan, vkDeviceWaitIdle);
		vkAllocateMemory = GET_PROCADDRESS(libvulkan, vkAllocateMemory);
		vkFreeMemory = GET_PROCADDRESS(libvulkan, vkFreeMemory);
		vkMapMemory = GET_PROCADDRESS(libvulkan, vkMapMemory);
		vkUnmapMemory = GET_PROCADDRESS(libvulkan, vkUnmapMemory);
		vkFlushMappedMemoryRanges = GET_PROCADDRESS(libvulkan, vkFlushMappedMemoryRanges);
		vkInvalidateMappedMemoryRanges = GET_PROCADDRESS(libvulkan, vkInvalidateMappedMemoryRanges);
		vkGetDeviceMemoryCommitment = GET_PROCADDRESS(libvulkan, vkGetDeviceMemoryCommitment);
		vkBindBufferMemory = GET_PROCADDRESS(libvulkan, vkBindBufferMemory);
		vkBindImageMemory = GET_PROCADDRESS(libvulkan, vkBindImageMemory);
		vkGetBufferMemoryRequirements = GET_PROCADDRESS(libvulkan, vkGetBufferMemoryRequirements);
		vkGetImageMemoryRequirements = GET_PROCADDRESS(libvulkan, vkGetImageMemoryRequirements);
		vkGetImageSparseMemoryRequirements = GET_PROCADDRESS(libvulkan, vkGetImageSparseMemoryRequirements);
		vkGetPhysicalDeviceSparseImageFormatProperties = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceSparseImageFormatProperties);
		vkQueueBindSparse = GET_PROCADDRESS(libvulkan, vkQueueBindSparse);
		vkCreateFence = GET_PROCADDRESS(libvulkan, vkCreateFence);
		vkDestroyFence = GET_PROCADDRESS(libvulkan, vkDestroyFence);
		vkResetFences = GET_PROCADDRESS(libvulkan, vkResetFences);
		vkGetFenceStatus = GET_PROCADDRESS(libvulkan, vkGetFenceStatus);
		vkWaitForFences = GET_PROCADDRESS(libvulkan, vkWaitForFences);
		vkCreateSemaphore = GET_PROCADDRESS(libvulkan, vkCreateSemaphore);
		vkDestroySemaphore = GET_PROCADDRESS(libvulkan, vkDestroySemaphore);
		vkCreateEvent = GET_PROCADDRESS(libvulkan, vkCreateEvent);
		vkDestroyEvent = GET_PROCADDRESS(libvulkan, vkDestroyEvent);
		vkGetEventStatus = GET_PROCADDRESS(libvulkan, vkGetEventStatus);
		vkSetEvent = GET_PROCADDRESS(libvulkan, vkSetEvent);
		vkResetEvent = GET_PROCADDRESS(libvulkan, vkResetEvent);
		vkCreateQueryPool = GET_PROCADDRESS(libvulkan, vkCreateQueryPool);
		vkDestroyQueryPool = GET_PROCADDRESS(libvulkan, vkDestroyQueryPool);
		vkGetQueryPoolResults = GET_PROCADDRESS(libvulkan, vkGetQueryPoolResults);
		vkCreateBuffer = GET_PROCADDRESS(libvulkan, vkCreateBuffer);
		vkDestroyBuffer = GET_PROCADDRESS(libvulkan, vkDestroyBuffer);
		vkCreateBufferView = GET_PROCADDRESS(libvulkan, vkCreateBufferView);
		vkDestroyBufferView = GET_PROCADDRESS(libvulkan, vkDestroyBufferView);
		vkCreateImage = GET_PROCADDRESS(libvulkan, vkCreateImage);
		vkDestroyImage = GET_PROCADDRESS(libvulkan, vkDestroyImage);
		vkGetImageSubresourceLayout = GET_PROCADDRESS(libvulkan, vkGetImageSubresourceLayout);
		vkCreateImageView = GET_PROCADDRESS(libvulkan, vkCreateImageView);
		vkDestroyImageView = GET_PROCADDRESS(libvulkan, vkDestroyImageView);
		vkCreateShaderModule = GET_PROCADDRESS(libvulkan, vkCreateShaderModule);
		vkDestroyShaderModule = GET_PROCADDRESS(libvulkan, vkDestroyShaderModule);
		vkCreatePipelineCache = GET_PROCADDRESS(libvulkan, vkCreatePipelineCache);
		vkDestroyPipelineCache = GET_PROCADDRESS(libvulkan, vkDestroyPipelineCache);
		vkGetPipelineCacheData = GET_PROCADDRESS(libvulkan, vkGetPipelineCacheData);
		vkMergePipelineCaches = GET_PROCADDRESS(libvulkan, vkMergePipelineCaches);
		vkCreateGraphicsPipelines = GET_PROCADDRESS(libvulkan, vkCreateGraphicsPipelines);
		vkCreateComputePipelines = GET_PROCADDRESS(libvulkan, vkCreateComputePipelines);
		vkDestroyPipeline = GET_PROCADDRESS(libvulkan, vkDestroyPipeline);
		vkCreatePipelineLayout = GET_PROCADDRESS(libvulkan, vkCreatePipelineLayout);
		vkDestroyPipelineLayout = GET_PROCADDRESS(libvulkan, vkDestroyPipelineLayout);
		vkCreateSampler = GET_PROCADDRESS(libvulkan, vkCreateSampler);
		vkDestroySampler = GET_PROCADDRESS(libvulkan, vkDestroySampler);
		vkCreateDescriptorSetLayout = GET_PROCADDRESS(libvulkan, vkCreateDescriptorSetLayout);
		vkDestroyDescriptorSetLayout = GET_PROCADDRESS(libvulkan, vkDestroyDescriptorSetLayout);
		vkCreateDescriptorPool = GET_PROCADDRESS(libvulkan, vkCreateDescriptorPool);
		vkDestroyDescriptorPool = GET_PROCADDRESS(libvulkan, vkDestroyDescriptorPool);
		vkResetDescriptorPool = GET_PROCADDRESS(libvulkan, vkResetDescriptorPool);
		vkAllocateDescriptorSets = GET_PROCADDRESS(libvulkan, vkAllocateDescriptorSets);
		vkFreeDescriptorSets = GET_PROCADDRESS(libvulkan, vkFreeDescriptorSets);
		vkUpdateDescriptorSets = GET_PROCADDRESS(libvulkan, vkUpdateDescriptorSets);
		vkCreateFramebuffer = GET_PROCADDRESS(libvulkan, vkCreateFramebuffer);
		vkDestroyFramebuffer = GET_PROCADDRESS(libvulkan, vkDestroyFramebuffer);
		vkCreateRenderPass = GET_PROCADDRESS(libvulkan, vkCreateRenderPass);
		vkDestroyRenderPass = GET_PROCADDRESS(libvulkan, vkDestroyRenderPass);
		vkGetRenderAreaGranularity = GET_PROCADDRESS(libvulkan, vkGetRenderAreaGranularity);
		vkCreateCommandPool = GET_PROCADDRESS(libvulkan, vkCreateCommandPool);
		vkDestroyCommandPool = GET_PROCADDRESS(libvulkan, vkDestroyCommandPool);
		vkResetCommandPool = GET_PROCADDRESS(libvulkan, vkResetCommandPool);
		vkAllocateCommandBuffers = GET_PROCADDRESS(libvulkan, vkAllocateCommandBuffers);
		vkFreeCommandBuffers = GET_PROCADDRESS(libvulkan, vkFreeCommandBuffers);
		vkBeginCommandBuffer = GET_PROCADDRESS(libvulkan, vkBeginCommandBuffer);
		vkEndCommandBuffer = GET_PROCADDRESS(libvulkan, vkEndCommandBuffer);
		vkResetCommandBuffer = GET_PROCADDRESS(libvulkan, vkResetCommandBuffer);
		vkCmdBindPipeline = GET_PROCADDRESS(libvulkan, vkCmdBindPipeline);
		vkCmdSetViewport = GET_PROCADDRESS(libvulkan, vkCmdSetViewport);
		vkCmdSetScissor = GET_PROCADDRESS(libvulkan, vkCmdSetScissor);
		vkCmdSetLineWidth = GET_PROCADDRESS(libvulkan, vkCmdSetLineWidth);
		vkCmdSetDepthBias = GET_PROCADDRESS(libvulkan, vkCmdSetDepthBias);
		vkCmdSetBlendConstants = GET_PROCADDRESS(libvulkan, vkCmdSetBlendConstants);
		vkCmdSetDepthBounds = GET_PROCADDRESS(libvulkan, vkCmdSetDepthBounds);
		vkCmdSetStencilCompareMask = GET_PROCADDRESS(libvulkan, vkCmdSetStencilCompareMask);
		vkCmdSetStencilWriteMask = GET_PROCADDRESS(libvulkan, vkCmdSetStencilWriteMask);
		vkCmdSetStencilReference = GET_PROCADDRESS(libvulkan, vkCmdSetStencilReference);
		vkCmdBindDescriptorSets = GET_PROCADDRESS(libvulkan, vkCmdBindDescriptorSets);
		vkCmdBindIndexBuffer = GET_PROCADDRESS(libvulkan, vkCmdBindIndexBuffer);
		vkCmdBindVertexBuffers = GET_PROCADDRESS(libvulkan, vkCmdBindVertexBuffers);
		vkCmdDraw = GET_PROCADDRESS(libvulkan, vkCmdDraw);
		vkCmdDrawIndexed = GET_PROCADDRESS(libvulkan, vkCmdDrawIndexed);
		vkCmdDrawIndirect = GET_PROCADDRESS(libvulkan, vkCmdDrawIndirect);
		vkCmdDrawIndexedIndirect = GET_PROCADDRESS(libvulkan, vkCmdDrawIndexedIndirect);
		vkCmdDispatch = GET_PROCADDRESS(libvulkan, vkCmdDispatch);
		vkCmdDispatchIndirect = GET_PROCADDRESS(libvulkan, vkCmdDispatchIndirect);
		vkCmdCopyBuffer = GET_PROCADDRESS(libvulkan, vkCmdCopyBuffer);
		vkCmdCopyImage = GET_PROCADDRESS(libvulkan, vkCmdCopyImage);
		vkCmdBlitImage = GET_PROCADDRESS(libvulkan, vkCmdBlitImage);
		vkCmdCopyBufferToImage = GET_PROCADDRESS(libvulkan, vkCmdCopyBufferToImage);
		vkCmdCopyImageToBuffer = GET_PROCADDRESS(libvulkan, vkCmdCopyImageToBuffer);
		vkCmdUpdateBuffer = GET_PROCADDRESS(libvulkan, vkCmdUpdateBuffer);
		vkCmdFillBuffer = GET_PROCADDRESS(libvulkan, vkCmdFillBuffer);
		vkCmdClearColorImage = GET_PROCADDRESS(libvulkan, vkCmdClearColorImage);
		vkCmdClearDepthStencilImage = GET_PROCADDRESS(libvulkan, vkCmdClearDepthStencilImage);
		vkCmdClearAttachments = GET_PROCADDRESS(libvulkan, vkCmdClearAttachments);
		vkCmdResolveImage = GET_PROCADDRESS(libvulkan, vkCmdResolveImage);
		vkCmdSetEvent = GET_PROCADDRESS(libvulkan, vkCmdSetEvent);
		vkCmdResetEvent = GET_PROCADDRESS(libvulkan, vkCmdResetEvent);
		vkCmdWaitEvents = GET_PROCADDRESS(libvulkan, vkCmdWaitEvents);
		vkCmdPipelineBarrier = GET_PROCADDRESS(libvulkan, vkCmdPipelineBarrier);
		vkCmdBeginQuery = GET_PROCADDRESS(libvulkan, vkCmdBeginQuery);
		vkCmdEndQuery = GET_PROCADDRESS(libvulkan, vkCmdEndQuery);
		vkCmdResetQueryPool = GET_PROCADDRESS(libvulkan, vkCmdResetQueryPool);
		vkCmdWriteTimestamp = GET_PROCADDRESS(libvulkan, vkCmdWriteTimestamp);
		vkCmdCopyQueryPoolResults = GET_PROCADDRESS(libvulkan, vkCmdCopyQueryPoolResults);
		vkCmdPushConstants = GET_PROCADDRESS(libvulkan, vkCmdPushConstants);
		vkCmdBeginRenderPass = GET_PROCADDRESS(libvulkan, vkCmdBeginRenderPass);
		vkCmdNextSubpass = GET_PROCADDRESS(libvulkan, vkCmdNextSubpass);
		vkCmdEndRenderPass = GET_PROCADDRESS(libvulkan, vkCmdEndRenderPass);
		vkCmdExecuteCommands = GET_PROCADDRESS(libvulkan, vkCmdExecuteCommands);
		vkDestroySurfaceKHR = GET_PROCADDRESS(libvulkan, vkDestroySurfaceKHR);
		vkGetPhysicalDeviceSurfaceSupportKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceSurfaceSupportKHR);
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
		vkGetPhysicalDeviceSurfaceFormatsKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceSurfaceFormatsKHR);
		vkGetPhysicalDeviceSurfacePresentModesKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceSurfacePresentModesKHR);
		vkCreateSwapchainKHR = GET_PROCADDRESS(libvulkan, vkCreateSwapchainKHR);
		vkDestroySwapchainKHR = GET_PROCADDRESS(libvulkan, vkDestroySwapchainKHR);
		vkGetSwapchainImagesKHR = GET_PROCADDRESS(libvulkan, vkGetSwapchainImagesKHR);
		vkAcquireNextImageKHR = GET_PROCADDRESS(libvulkan, vkAcquireNextImageKHR);
		vkQueuePresentKHR = GET_PROCADDRESS(libvulkan, vkQueuePresentKHR);
		vkGetPhysicalDeviceDisplayPropertiesKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceDisplayPropertiesKHR);
		vkGetPhysicalDeviceDisplayPlanePropertiesKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
		vkGetDisplayPlaneSupportedDisplaysKHR = GET_PROCADDRESS(libvulkan, vkGetDisplayPlaneSupportedDisplaysKHR);
		vkGetDisplayModePropertiesKHR = GET_PROCADDRESS(libvulkan, vkGetDisplayModePropertiesKHR);
		vkCreateDisplayModeKHR = GET_PROCADDRESS(libvulkan, vkCreateDisplayModeKHR);
		vkGetDisplayPlaneCapabilitiesKHR = GET_PROCADDRESS(libvulkan, vkGetDisplayPlaneCapabilitiesKHR);
		vkCreateDisplayPlaneSurfaceKHR = GET_PROCADDRESS(libvulkan, vkCreateDisplayPlaneSurfaceKHR);
		vkCreateSharedSwapchainsKHR = GET_PROCADDRESS(libvulkan, vkCreateSharedSwapchainsKHR);

#ifdef VK_USE_PLATFORM_XLIB_KHR
		vkCreateXlibSurfaceKHR = GET_PROCADDRESS(libvulkan, vkCreateXlibSurfaceKHR);
		vkGetPhysicalDeviceXlibPresentationSupportKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceXlibPresentationSupportKHR);
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
		vkCreateXcbSurfaceKHR = GET_PROCADDRESS(libvulkan, vkCreateXcbSurfaceKHR);
		vkGetPhysicalDeviceXcbPresentationSupportKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceXcbPresentationSupportKHR);
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
		vkCreateWaylandSurfaceKHR = GET_PROCADDRESS(libvulkan, vkCreateWaylandSurfaceKHR);
		vkGetPhysicalDeviceWaylandPresentationSupportKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceWaylandPresentationSupportKHR);
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
		vkCreateMirSurfaceKHR = GET_PROCADDRESS(libvulkan, vkCreateMirSurfaceKHR);
		vkGetPhysicalDeviceMirPresentationSupportKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceMirPresentationSupportKHR);
#endif

#ifdef VK_USE_PLATFORM_ANDROID_KHR
		vkCreateAndroidSurfaceKHR = GET_PROCADDRESS(libvulkan, vkCreateAndroidSurfaceKHR);
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
		vkCreateWin32SurfaceKHR = GET_PROCADDRESS(libvulkan, vkCreateWin32SurfaceKHR);
		vkGetPhysicalDeviceWin32PresentationSupportKHR = GET_PROCADDRESS(libvulkan, vkGetPhysicalDeviceWin32PresentationSupportKHR);
#endif
#ifdef USE_DEBUG_EXTENTIONS
		vkCreateDebugReportCallbackEXT = GET_PROCADDRESS(libvulkan, vkCreateDebugReportCallbackEXT);
		vkDestroyDebugReportCallbackEXT = GET_PROCADDRESS(libvulkan, vkDestroyDebugReportCallbackEXT);
		vkDebugReportMessageEXT = GET_PROCADDRESS(libvulkan, vkDebugReportMessageEXT);
#endif

#endif
		return true;
	}
}

#if SF_VULKAN_DYNAMIC_LIBRARY
// No Vulkan support, do not set function addresses
PFN_vkCreateInstance vkCreateInstance = nullptr;
PFN_vkDestroyInstance vkDestroyInstance = nullptr;
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices = nullptr;
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures = nullptr;
PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties = nullptr;
PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties = nullptr;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties = nullptr;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties = nullptr;
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = nullptr;
PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr = nullptr;
PFN_vkCreateDevice vkCreateDevice = nullptr;
PFN_vkDestroyDevice vkDestroyDevice = nullptr;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties = nullptr;
PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties = nullptr;
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties = nullptr;
PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties = nullptr;
PFN_vkGetDeviceQueue vkGetDeviceQueue = nullptr;
PFN_vkQueueSubmit vkQueueSubmit = nullptr;
PFN_vkQueueWaitIdle vkQueueWaitIdle = nullptr;
PFN_vkDeviceWaitIdle vkDeviceWaitIdle = nullptr;
PFN_vkAllocateMemory vkAllocateMemory = nullptr;
PFN_vkFreeMemory vkFreeMemory = nullptr;
PFN_vkMapMemory vkMapMemory = nullptr;
PFN_vkUnmapMemory vkUnmapMemory = nullptr;
PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges = nullptr;
PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges = nullptr;
PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment = nullptr;
PFN_vkBindBufferMemory vkBindBufferMemory = nullptr;
PFN_vkBindImageMemory vkBindImageMemory = nullptr;
PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements = nullptr;
PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements = nullptr;
PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements = nullptr;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties = nullptr;
PFN_vkQueueBindSparse vkQueueBindSparse = nullptr;
PFN_vkCreateFence vkCreateFence = nullptr;
PFN_vkDestroyFence vkDestroyFence = nullptr;
PFN_vkResetFences vkResetFences = nullptr;
PFN_vkGetFenceStatus vkGetFenceStatus = nullptr;
PFN_vkWaitForFences vkWaitForFences = nullptr;
PFN_vkCreateSemaphore vkCreateSemaphore = nullptr;
PFN_vkDestroySemaphore vkDestroySemaphore = nullptr;
PFN_vkCreateEvent vkCreateEvent = nullptr;
PFN_vkDestroyEvent vkDestroyEvent = nullptr;
PFN_vkGetEventStatus vkGetEventStatus = nullptr;
PFN_vkSetEvent vkSetEvent = nullptr;
PFN_vkResetEvent vkResetEvent = nullptr;
PFN_vkCreateQueryPool vkCreateQueryPool = nullptr;
PFN_vkDestroyQueryPool vkDestroyQueryPool = nullptr;
PFN_vkGetQueryPoolResults vkGetQueryPoolResults = nullptr;
PFN_vkCreateBuffer vkCreateBuffer = nullptr;
PFN_vkDestroyBuffer vkDestroyBuffer = nullptr;
PFN_vkCreateBufferView vkCreateBufferView = nullptr;
PFN_vkDestroyBufferView vkDestroyBufferView = nullptr;
PFN_vkCreateImage vkCreateImage = nullptr;
PFN_vkDestroyImage vkDestroyImage = nullptr;
PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout = nullptr;
PFN_vkCreateImageView vkCreateImageView = nullptr;
PFN_vkDestroyImageView vkDestroyImageView = nullptr;
PFN_vkCreateShaderModule vkCreateShaderModule = nullptr;
PFN_vkDestroyShaderModule vkDestroyShaderModule = nullptr;
PFN_vkCreatePipelineCache vkCreatePipelineCache = nullptr;
PFN_vkDestroyPipelineCache vkDestroyPipelineCache = nullptr;
PFN_vkGetPipelineCacheData vkGetPipelineCacheData = nullptr;
PFN_vkMergePipelineCaches vkMergePipelineCaches = nullptr;
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = nullptr;
PFN_vkCreateComputePipelines vkCreateComputePipelines = nullptr;
PFN_vkDestroyPipeline vkDestroyPipeline = nullptr;
PFN_vkCreatePipelineLayout vkCreatePipelineLayout = nullptr;
PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout = nullptr;
PFN_vkCreateSampler vkCreateSampler = nullptr;
PFN_vkDestroySampler vkDestroySampler = nullptr;
PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout = nullptr;
PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout = nullptr;
PFN_vkCreateDescriptorPool vkCreateDescriptorPool = nullptr;
PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool = nullptr;
PFN_vkResetDescriptorPool vkResetDescriptorPool = nullptr;
PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets = nullptr;
PFN_vkFreeDescriptorSets vkFreeDescriptorSets = nullptr;
PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets = nullptr;
PFN_vkCreateFramebuffer vkCreateFramebuffer = nullptr;
PFN_vkDestroyFramebuffer vkDestroyFramebuffer = nullptr;
PFN_vkCreateRenderPass vkCreateRenderPass = nullptr;
PFN_vkDestroyRenderPass vkDestroyRenderPass = nullptr;
PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity = nullptr;
PFN_vkCreateCommandPool vkCreateCommandPool = nullptr;
PFN_vkDestroyCommandPool vkDestroyCommandPool = nullptr;
PFN_vkResetCommandPool vkResetCommandPool = nullptr;
PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers = nullptr;
PFN_vkFreeCommandBuffers vkFreeCommandBuffers = nullptr;
PFN_vkBeginCommandBuffer vkBeginCommandBuffer = nullptr;
PFN_vkEndCommandBuffer vkEndCommandBuffer = nullptr;
PFN_vkResetCommandBuffer vkResetCommandBuffer = nullptr;
PFN_vkCmdBindPipeline vkCmdBindPipeline = nullptr;
PFN_vkCmdSetViewport vkCmdSetViewport = nullptr;
PFN_vkCmdSetScissor vkCmdSetScissor = nullptr;
PFN_vkCmdSetLineWidth vkCmdSetLineWidth = nullptr;
PFN_vkCmdSetDepthBias vkCmdSetDepthBias = nullptr;
PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants = nullptr;
PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds = nullptr;
PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask = nullptr;
PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask = nullptr;
PFN_vkCmdSetStencilReference vkCmdSetStencilReference = nullptr;
PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets = nullptr;
PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer = nullptr;
PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers = nullptr;
PFN_vkCmdDraw vkCmdDraw = nullptr;
PFN_vkCmdDrawIndexed vkCmdDrawIndexed = nullptr;
PFN_vkCmdDrawIndirect vkCmdDrawIndirect = nullptr;
PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect = nullptr;
PFN_vkCmdDispatch vkCmdDispatch = nullptr;
PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect = nullptr;
PFN_vkCmdCopyBuffer vkCmdCopyBuffer = nullptr;
PFN_vkCmdCopyImage vkCmdCopyImage = nullptr;
PFN_vkCmdBlitImage vkCmdBlitImage = nullptr;
PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage = nullptr;
PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer = nullptr;
PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer = nullptr;
PFN_vkCmdFillBuffer vkCmdFillBuffer = nullptr;
PFN_vkCmdClearColorImage vkCmdClearColorImage = nullptr;
PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage = nullptr;
PFN_vkCmdClearAttachments vkCmdClearAttachments = nullptr;
PFN_vkCmdResolveImage vkCmdResolveImage = nullptr;
PFN_vkCmdSetEvent vkCmdSetEvent = nullptr;
PFN_vkCmdResetEvent vkCmdResetEvent = nullptr;
PFN_vkCmdWaitEvents vkCmdWaitEvents = nullptr;
PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = nullptr;
PFN_vkCmdBeginQuery vkCmdBeginQuery = nullptr;
PFN_vkCmdEndQuery vkCmdEndQuery = nullptr;
PFN_vkCmdResetQueryPool vkCmdResetQueryPool = nullptr;
PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp = nullptr;
PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults = nullptr;
PFN_vkCmdPushConstants vkCmdPushConstants = nullptr;
PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass = nullptr;
PFN_vkCmdNextSubpass vkCmdNextSubpass = nullptr;
PFN_vkCmdEndRenderPass vkCmdEndRenderPass = nullptr;
PFN_vkCmdExecuteCommands vkCmdExecuteCommands = nullptr;
PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR = nullptr;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR = nullptr;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR = nullptr;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR = nullptr;
PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR = nullptr;
PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR = nullptr;
PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR = nullptr;
PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR = nullptr;
PFN_vkQueuePresentKHR vkQueuePresentKHR = nullptr;
PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR = nullptr;
PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR = nullptr;
PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR = nullptr;
PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR = nullptr;
PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR = nullptr;
PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR = nullptr;
PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR = nullptr;
PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR = nullptr;

#ifdef VK_USE_PLATFORM_XLIB_KHR
PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR = nullptr;
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR = nullptr;
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR = nullptr;
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR = nullptr;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR = nullptr;
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR = nullptr;
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
PFN_vkCreateMirSurfaceKHR vkCreateMirSurfaceKHR = nullptr;
PFN_vkGetPhysicalDeviceMirPresentationSupportKHR vkGetPhysicalDeviceMirPresentationSupportKHR = nullptr;
#endif

#ifdef VK_USE_PLATFORM_ANDROID_KHR
PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR = nullptr;
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR = nullptr;
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR = nullptr;
#endif
PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT = nullptr;
PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = nullptr;
PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT = nullptr;

#endif


#endif // #if HAVE_VULKAN


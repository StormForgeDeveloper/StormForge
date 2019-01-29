////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan Debug
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/Vulkan/SFVulkanDebug.h"
#include "Util/SFLog.h"


#if HAVE_VULKAN



namespace SF
{
	VulkanDebug::VulkanDebug(VkInstance instance)
		: m_VKInstance(instance)
		, m_MsgCallback(VK_NULL_HANDLE)
	{
		if (m_VKInstance == nullptr)
			return;

		CreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(m_VKInstance, "vkCreateDebugReportCallbackEXT"));
		DestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(m_VKInstance, "vkDestroyDebugReportCallbackEXT"));


		if (CreateDebugReportCallbackEXT == nullptr || DestroyDebugReportCallbackEXT == nullptr)
			return;


		VkDebugReportCallbackCreateInfoEXT dbgCreateInfo = {};
		dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		dbgCreateInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)MessageCallback;
		dbgCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT;

		VkResult err = CreateDebugReportCallbackEXT(
			m_VKInstance,
			&dbgCreateInfo,
			nullptr,
			&m_MsgCallback);

		if (err != VK_SUCCESS)
		{
			SFLog(System, Error, "VulkanError: {0:X8}", (uint32_t)err);
		}
	}

	VulkanDebug::~VulkanDebug()
	{
		if (DestroyDebugReportCallbackEXT != nullptr)
		{
			if (m_MsgCallback != VK_NULL_HANDLE)
			{
				DestroyDebugReportCallbackEXT(m_VKInstance, m_MsgCallback, nullptr);
			}
		}
	}


	VkBool32 VulkanDebug::MessageCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject,
		size_t location,
		int32_t msgCode,
		const char* pLayerPrefix,
		const char* pMsg,
		void* pUserData)
	{
		if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
		{
			SFLog(System, Error, "[{0}] {1}", pLayerPrefix, pMsg);
		}
		else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
		{
			SFLog(System, Warning, "[{0}] {1}", pLayerPrefix, pMsg);
		}
		else if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
		{
			SFLog(System, Warning, "[{0}] {1}", pLayerPrefix, pMsg);
		}
		else if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
		{
			SFLog(System, Info, "[{0}] {1}", pLayerPrefix, pMsg);
		}
		else //if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
		{
			SFLog(System, Debug, "[{0}] {1}", pLayerPrefix, pMsg);
		}

		// The return value of this callback controls weather the Vulkan call that caused
		// the validation message will be aborted or not
		// We return VK_FALSE as we DON'T want Vulkan calls that cause a validation message 
		// (and return a VkResult) to abort
		// If you instead want to have calls abort, pass in VK_TRUE and the function will 
		// return VK_ERROR_VALIDATION_FAILED_EXT 
		return VK_FALSE;
	}



}


#endif // #if HAVE_VULKAN


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan Debug
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Graphics/Vulkan/SFVulkanLibrary.h"

#if SF_USE_VULKAN
#include "vulkan/vk_platform.h"



namespace SF
{
	class VulkanDebug
	{
	private:

		VkInstance m_VKInstance;
		VkDebugReportCallbackEXT m_MsgCallback;

		// These are not part of vulkan core
		PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallbackEXT;
		PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallbackEXT;
		//PFN_vkDebugReportMessageEXT dbgBreakCallback;


	private:

		static VKAPI_ATTR VkBool32 VKAPI_CALL MessageCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t srcObject,
			size_t location,
			int32_t msgCode,
			const char* pLayerPrefix,
			const char* pMsg,
			void* pUserData);

	public:
		VulkanDebug(VkInstance instance);
		~VulkanDebug();

	};

}


#endif // #if SF_USE_VULKAN

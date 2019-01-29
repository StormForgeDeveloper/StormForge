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

#if HAVE_VULKAN

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

		static VkBool32 MessageCallback(
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


#endif // #if HAVE_VULKAN

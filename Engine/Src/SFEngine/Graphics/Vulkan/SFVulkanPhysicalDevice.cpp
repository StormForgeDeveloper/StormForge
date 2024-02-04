////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan physical device
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"
#include "Graphics/Vulkan/SFVulkanPhysicalDevice.h"
#include "Graphics/Vulkan/SFVulkanLogicalDevice.h"
#include "Util/SFLog.h"


#if SF_USE_VULKAN



namespace SF
{
	VulkanPhysicalDevice::VulkanPhysicalDevice(IHeap& heap, VulkanSystem* pSystem, VkPhysicalDevice device)
		: m_VKSystem(pSystem)
		, m_VKPhysicalDevice(device)
		, m_DeviceLayers(heap)
		, m_DeviceMemoryTypes(heap)
		, m_DeviceHeaps(heap)
		, m_DeviceQueues(heap)
		, m_DeviceExtensions(heap)
	{
	}

	VulkanPhysicalDevice::~VulkanPhysicalDevice()
	{
	}



	VkResult VulkanPhysicalDevice::EnumerateDeviceLayers()
	{
		uint32_t enumCount = 0;

		// Device extensions
		// Get number of available physical devices
		m_DeviceLayers.Clear();
		auto result = vkEnumerateDeviceLayerProperties(m_VKPhysicalDevice, &enumCount, nullptr);
		if (result != VK_SUCCESS || enumCount == 0)
		{
			assert(false);
			return result;
		}
		else
		{
			// Enumerate devices
			m_DeviceLayers.resize(enumCount);
			result = vkEnumerateDeviceLayerProperties(m_VKPhysicalDevice, &enumCount, m_DeviceLayers.data());
			if (result != VK_SUCCESS)
				return result;
		}


		return VK_SUCCESS;
	}


	VkResult VulkanPhysicalDevice::UpdateDeviceInformation()
	{
		// Retrieve device informations
		vkGetPhysicalDeviceProperties(m_VKPhysicalDevice, &m_VKDeviceProperties);
		vkGetPhysicalDeviceFeatures(m_VKPhysicalDevice, &m_VKDeviceFeatures);

		memset(&m_VKDeviceMemoryProperties, 0, sizeof(m_VKDeviceMemoryProperties));
		vkGetPhysicalDeviceMemoryProperties(m_VKPhysicalDevice, &m_VKDeviceMemoryProperties);

		m_DeviceMemoryTypes.Clear();
		m_DeviceMemoryTypes.reserve(m_VKDeviceMemoryProperties.memoryTypeCount);
		for (unsigned iItem = 0; iItem < m_VKDeviceMemoryProperties.memoryTypeCount; iItem++)
		{
			m_DeviceMemoryTypes.push_back(m_VKDeviceMemoryProperties.memoryTypes[iItem]);
		}

		m_DeviceHeaps.Clear();
		m_DeviceHeaps.reserve(m_VKDeviceMemoryProperties.memoryHeapCount);
		for (unsigned iItem = 0; iItem < m_VKDeviceMemoryProperties.memoryHeapCount; iItem++)
		{
			m_DeviceHeaps.push_back(m_VKDeviceMemoryProperties.memoryHeaps[iItem]);
		}

		// Retrieve queue informations
		uint32_t itemCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_VKPhysicalDevice, &itemCount, nullptr);
		m_DeviceQueues.Clear();
		m_DeviceQueues.resize(itemCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_VKPhysicalDevice, &itemCount, m_DeviceQueues.data());

		itemCount = 0;
		vkEnumerateDeviceExtensionProperties(m_VKPhysicalDevice, nullptr, &itemCount, nullptr);
		m_DeviceExtensions.Clear();
		m_DeviceExtensions.resize(itemCount);
		vkEnumerateDeviceExtensionProperties(m_VKPhysicalDevice, nullptr, &itemCount, m_DeviceExtensions.data());

		return VK_SUCCESS;
	}


	VkResult VulkanPhysicalDevice::Initialize()
	{
		if (m_VKSystem == nullptr || m_VKPhysicalDevice == nullptr)
			return VK_ERROR_INITIALIZATION_FAILED;

		VkResult result;
		result = EnumerateDeviceLayers();
		if (result != VK_SUCCESS)
		{
			m_VKSystem->ReportVKError(result);
			return result;
		}

		result = UpdateDeviceInformation();
		if (result != VK_SUCCESS)
		{
			m_VKSystem->ReportVKError(result);
			return result;
		}

		return VK_SUCCESS;
	}



	VulkanLogicalDevice* VulkanPhysicalDevice::CreateLogicalDevice(IHeap& heap, const VulkanDeviceInitParameter& parameter)
	{
		if (m_VKSystem == nullptr || m_VKPhysicalDevice == nullptr)
			return nullptr;

		VulkanLogicalDevice *pNewLogicalDevice = new(heap) VulkanLogicalDevice(heap, m_VKSystem, this);
		auto result = pNewLogicalDevice->Initialize(m_VKDeviceFeatures, parameter);
		if(result != VK_SUCCESS)
		{
			m_VKSystem->ReportVKError(result);
			GetSystemHeap().Delete(pNewLogicalDevice);
			return nullptr;
		}

		return pNewLogicalDevice;
	}


	int32_t VulkanPhysicalDevice::FindMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties)
	{
		for (uint32_t iMem = 0; iMem < m_VKDeviceMemoryProperties.memoryTypeCount; iMem++, typeBits >>= 1)
		{
			if ((typeBits & 1) != 0)
			{
				if ((m_VKDeviceMemoryProperties.memoryTypes[iMem].propertyFlags & properties) == properties)
				{
					return (int32_t)iMem;
				}
			}
		}

		return -1;
	}

	// Get Queue index
	int32_t VulkanPhysicalDevice::GetQueueFamilyIndex(VkSurfaceKHR surface, VkQueueFlagBits queueFlags, VkQueueFlagBits preferExcludeFlags)
	{
		// For other queue types or if no separate compute queue is present, return the first one to support the requested flags
		int32_t iSelected = -1;
		for (int32_t iQueue = 0; iQueue < static_cast<int32_t>(m_DeviceQueues.size()); iQueue++)
		{
			if ((m_DeviceQueues[iQueue].queueFlags & queueFlags) == 0)
				continue;

			if (iSelected < 0)
			{
				// lets keep it and go
				iSelected = iQueue;
				continue;
			}

			if (m_DeviceQueues[iQueue].queueFlags & preferExcludeFlags)
				continue;

			// Found it!
			iSelected = iQueue;

			// for graphics queue, we prefer to have present support so if it doesn't support present keep searching
			if (surface != VK_NULL_HANDLE && (queueFlags & VK_QUEUE_GRAPHICS_BIT))
			{
				VkBool32 presentSupport = VK_FALSE;
				vkGetPhysicalDeviceSurfaceSupportKHR(m_VKPhysicalDevice, iQueue, surface, &presentSupport);
				if (!presentSupport)
					continue;
			}

			break;
		}

		return iSelected;
	}

	VkFormat VulkanPhysicalDevice::SelectDepthStencilFormat()
	{
		static const VkFormat depthFormats[] =
		{
			VK_FORMAT_D32_SFLOAT_S8_UINT,
			VK_FORMAT_D32_SFLOAT,
			VK_FORMAT_D24_UNORM_S8_UINT,
			VK_FORMAT_D16_UNORM_S8_UINT,
			VK_FORMAT_D16_UNORM
		};

		for (auto& format : depthFormats)
		{
			VkFormatProperties formatProps;
			vkGetPhysicalDeviceFormatProperties(GetPhysicalDevice(), format, &formatProps);

			if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			{
				return format;
			}
		}

		return VK_FORMAT_D32_SFLOAT;
	}

}


#endif // #if SF_USE_VULKAN


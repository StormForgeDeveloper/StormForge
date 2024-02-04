////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan physical device
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"

#if SF_USE_VULKAN

namespace SF
{


	class VulkanLogicalDevice;

	////////////////////////////////////////////////////////////////////////////////
	//
	// VulkanPhysicalDevice: Vulkan's physical device informations
	//

	class VulkanPhysicalDevice
	{
	public:

		enum USAGE_FLAGS
		{
			USAGE_GRAPHIC = 1,
			USAGE_COMPUTE = 2,
			USAGE_TRANSFER = 4,
		};

	private:

		VulkanSystem* m_VKSystem;

		VkPhysicalDevice m_VKPhysicalDevice;

		// Physical device properties
		VkPhysicalDeviceProperties m_VKDeviceProperties;
		// Device features
		VkPhysicalDeviceFeatures m_VKDeviceFeatures;
		// Device memory properties
		VkPhysicalDeviceMemoryProperties m_VKDeviceMemoryProperties;

		// Device enumerations
		DynamicArray<VkLayerProperties> m_DeviceLayers;
		DynamicArray<VkMemoryType> m_DeviceMemoryTypes;
		DynamicArray<VkMemoryHeap> m_DeviceHeaps;
		DynamicArray<VkQueueFamilyProperties> m_DeviceQueues;
		DynamicArray<VkExtensionProperties> m_DeviceExtensions;


	private:


		// Enumerate device layers
		VkResult EnumerateDeviceLayers();

		// Update all device information
		VkResult UpdateDeviceInformation();

		VkResult Initialize();

		friend class VulkanSystem;


	public:
		VulkanPhysicalDevice(IHeap& heap, VulkanSystem* pSystem, VkPhysicalDevice device);
		~VulkanPhysicalDevice();

		VkPhysicalDevice GetPhysicalDevice() { return m_VKPhysicalDevice; }

		// Get device properties
		const VkPhysicalDeviceProperties& GetDeviceProperties() { return m_VKDeviceProperties; }
		// Get device features
		const VkPhysicalDeviceFeatures& GetDeviceFeatures() { return m_VKDeviceFeatures; }
		// Get device supported layers
		const Array<VkLayerProperties>& GetDeviceLayers() { return m_DeviceLayers; }
		// Get device supported memory types
		const Array<VkMemoryType>& GetDeviceMemoryTypes() { return m_DeviceMemoryTypes; }
		// Get device supported memory heaps
		const Array<VkMemoryHeap>& GetDeviceHeaps() { return m_DeviceHeaps; }
		// Get device supported queues
		const Array<VkQueueFamilyProperties>& GetDeviceQueues() { return m_DeviceQueues; }

		// Create logical device
		VulkanLogicalDevice* CreateLogicalDevice(IHeap& heap, const VulkanDeviceInitParameter& parameter);


		// Search memory type index
		int32_t FindMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties);

		// Get Queue index
		int32_t GetQueueFamilyIndex(VkSurfaceKHR surface, VkQueueFlagBits queueFlags, VkQueueFlagBits preferExcludeFlags);

		// Select Depth format
		VkFormat SelectDepthStencilFormat();
	};

}


#endif // #if SF_USE_VULKAN

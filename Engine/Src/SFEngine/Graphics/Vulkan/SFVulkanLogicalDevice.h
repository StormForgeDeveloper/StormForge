////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan logical device
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"

#if HAVE_VULKAN

namespace SF
{
	struct VulkanDeviceInitParameter;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	class VulkanLogicalDevice
	//


	class VulkanLogicalDevice : public SharedObject
	{
	private:

		// Memory manager for this device
		IHeap& m_Heap;

		// Vulkan system
		VulkanSystem* m_VKSystem;

		// Vulkan physical device
		VulkanPhysicalDevice *m_VKPhysicalDevice;

		// Vulkan logical device
		VkDevice m_VKLogicalDevice;

		// Command pool
		VkCommandPool m_VKCommandPool;

		// Queues for the commands
		VkQueue m_GraphicQueue;
		VkQueue m_ComputeQueue;
		VkQueue m_TransferQueue;

		// Queue flags
		VulkanDeviceInitParameter m_RequestedParameter;

		struct
		{
			int32_t present;
			int32_t graphics;
			int32_t compute;
			int32_t transfer;
		} m_QueueIndices;

		// Feature list
		VkPhysicalDeviceFeatures m_EnabledFeatures;

		DynamicArray<const char*> m_EnabledExtensions;


	private:

		VkResult Initialize(VkPhysicalDeviceFeatures features, const VulkanDeviceInitParameter& parameter);
		void DecideQueueIndices(const VulkanDeviceInitParameter& parameter, Array<VkDeviceQueueCreateInfo>& queueCreateInfos);
		VkCommandPool CreateCommandPool(int32_t queueIndex, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

		friend class VulkanPhysicalDevice;

	public:
		VulkanLogicalDevice(IHeap& heap, VulkanSystem* pSystem, VulkanPhysicalDevice* pPhysicalDevice);
		~VulkanLogicalDevice();

		virtual void Dispose() override;

		// Memory for the defice
		IHeap& GetHeap() { return m_Heap; }

		// Get Logical device handle
		VkDevice GetLogicalDevice() { return m_VKLogicalDevice; }


		void GetGraphicsQueue(VkQueue& queue);

		// Flush command queue
		void FlushCommandQueue();

		// Allocate device memory
		VkResult AllocateDeviceMemory(VkMemoryRequirements memReqs, VkDeviceMemory &memory);
	};

	typedef SharedPointerT<VulkanLogicalDevice> VulkanLogicalDevicePtr;

	extern template class SharedPointerT<VulkanLogicalDevice>;

}


#endif // #if HAVE_VULKAN

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan logical device
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"
#include "Graphics/Vulkan/SFVulkanPhysicalDevice.h"
#include "Graphics/Vulkan/SFVulkanLogicalDevice.h"
#include "Util/SFLog.h"


#if HAVE_VULKAN



namespace SF
{
	template class SharedPointerT<VulkanLogicalDevice>;

	VulkanLogicalDevice::VulkanLogicalDevice(IHeap& heap, VulkanSystem* pSystem, VulkanPhysicalDevice* pPhysicalDevice)
		: m_Heap (heap)
		, m_VKSystem(pSystem)
		, m_VKPhysicalDevice(pPhysicalDevice)
		, m_VKLogicalDevice(VK_NULL_HANDLE)
		, m_VKCommandPool(VK_NULL_HANDLE)
		, m_GraphicQueue(nullptr)
		, m_ComputeQueue(nullptr)
		, m_TransferQueue(nullptr)
		, m_EnabledExtensions(heap)
	{
		memset(&m_RequestedParameter, 0, sizeof(m_RequestedParameter));
		memset(&m_QueueIndices, 0, sizeof(m_QueueIndices));
		memset(&m_EnabledFeatures, 0, sizeof(m_EnabledFeatures));
	}

	VulkanLogicalDevice::~VulkanLogicalDevice()
	{
	}

	void VulkanLogicalDevice::Dispose()
	{
		if (m_VKLogicalDevice != nullptr)
		{
			if (m_VKCommandPool != VK_NULL_HANDLE)
				vkDestroyCommandPool(m_VKLogicalDevice, m_VKCommandPool, nullptr);
			m_VKCommandPool = VK_NULL_HANDLE;

			vkDestroyDevice(m_VKLogicalDevice, nullptr);
			m_VKLogicalDevice = nullptr;
		}
	}
	
	VkResult VulkanLogicalDevice::Initialize(VkPhysicalDeviceFeatures features, const VulkanDeviceInitParameter& parameter)
	{
		if (m_VKSystem == nullptr || m_VKPhysicalDevice == nullptr)
			return VK_ERROR_INITIALIZATION_FAILED;

		if (m_VKLogicalDevice != nullptr)
		{
			Dispose();
		}

		m_RequestedParameter = parameter;
		m_EnabledFeatures = features;


		StaticArray<VkDeviceQueueCreateInfo, 5> queueCreateInfos(GetHeap());


		DecideQueueIndices(parameter, queueCreateInfos);
		
		// Create the logical device representation
		StaticArray<const char*, 32> deviceExtensions(GetHeap());
		//deviceExtensions.AddItems(m_VKPhysicalDevice)
		if (parameter.EnableSwapChain)
		{
			// If the device will be used for presenting to a display via a swapchain we need to request the swapchain extension
			deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		}

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.pEnabledFeatures = &features;

		// Enable the debug marker extension if it is present (likely meaning a debugging tool is present)
		//if (extensionSupported(VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
		//{
		//	deviceExtensions.push_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
		//	enableDebugMarkers = true;
		//}

		if (deviceExtensions.size() > 0)
		{
			deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
			deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
		}

		VkResult result = vkCreateDevice(m_VKPhysicalDevice->GetPhysicalDevice(), &deviceCreateInfo, nullptr, &m_VKLogicalDevice);
		if (result != VK_SUCCESS)
		{
			m_VKSystem->ReportVKError(result);
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		// Create a default command pool for graphics command buffers
		m_VKCommandPool = CreateCommandPool(m_QueueIndices.graphics);

		vkGetDeviceQueue(m_VKLogicalDevice, m_QueueIndices.graphics, 0, &m_GraphicQueue);
		vkGetDeviceQueue(m_VKLogicalDevice, m_QueueIndices.compute, 0, &m_ComputeQueue);
		vkGetDeviceQueue(m_VKLogicalDevice, m_QueueIndices.transfer, 0, &m_TransferQueue);

		// TODO
		//swapChain.connect(instance, physicalDevice, device);

		return VK_SUCCESS;
	}

	void VulkanLogicalDevice::DecideQueueIndices(const VulkanDeviceInitParameter& parameter, Array<VkDeviceQueueCreateInfo>& queueCreateInfos)
	{
		const float defaultQueuePriority(0.0f);

		memset(&m_QueueIndices, 0, sizeof(m_QueueIndices));

		// Graphics queue
		if (m_RequestedParameter.UsageGraphic)
		{
			m_QueueIndices.graphics = m_VKPhysicalDevice->GetQueueFamilyIndex(parameter.Surface, VK_QUEUE_GRAPHICS_BIT, (VkQueueFlagBits)0);
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = m_QueueIndices.graphics;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfos.push_back(queueInfo);

			// Initially they uses same queue
			m_QueueIndices.present = m_QueueIndices.graphics;

			if (parameter.Surface != VK_NULL_HANDLE)
			{
				VkBool32 presentSupport = VK_FALSE;
				vkGetPhysicalDeviceSurfaceSupportKHR(m_VKPhysicalDevice->GetPhysicalDevice(), m_QueueIndices.graphics, parameter.Surface, &presentSupport);
				if (!presentSupport)
				{
					m_QueueIndices.present = 0;

					for (int32_t iQueue = 0; iQueue < static_cast<int32_t>(m_VKPhysicalDevice->GetDeviceQueues().size()); iQueue++)
					{
						presentSupport = VK_FALSE;
						vkGetPhysicalDeviceSurfaceSupportKHR(m_VKPhysicalDevice->GetPhysicalDevice(), iQueue, parameter.Surface, &presentSupport);
						if (presentSupport)
						{
							m_QueueIndices.present = iQueue;
							break;
						}
					}
				}
			}
		}
		else
		{
			m_QueueIndices.graphics = 0;
		}
		// Initially they shares a queue
		m_QueueIndices.compute = m_QueueIndices.graphics;
		m_QueueIndices.transfer = m_QueueIndices.graphics;


		// compute queue
		if (m_RequestedParameter.UsageCompute)
		{
			m_QueueIndices.compute = m_VKPhysicalDevice->GetQueueFamilyIndex(VK_NULL_HANDLE, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_GRAPHICS_BIT);
			if (m_QueueIndices.compute != m_QueueIndices.graphics)
			{
				// If compute family index differs, we need an additional queue create info for the compute queue
				VkDeviceQueueCreateInfo queueInfo{};
				queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueInfo.queueFamilyIndex = m_QueueIndices.compute;
				queueInfo.queueCount = 1;
				queueInfo.pQueuePriorities = &defaultQueuePriority;
				queueCreateInfos.push_back(queueInfo);
			}
		}

		// transfer queue
		if (m_RequestedParameter.UsageTransfer)
		{
			m_QueueIndices.transfer = m_VKPhysicalDevice->GetQueueFamilyIndex(VK_NULL_HANDLE, VK_QUEUE_TRANSFER_BIT, VK_QUEUE_GRAPHICS_BIT);
			if ((m_QueueIndices.transfer != m_QueueIndices.graphics) && (m_QueueIndices.transfer != m_QueueIndices.compute))
			{
				VkDeviceQueueCreateInfo queueInfo{};
				queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueInfo.queueFamilyIndex = m_QueueIndices.transfer;
				queueInfo.queueCount = 1;
				queueInfo.pQueuePriorities = &defaultQueuePriority;
				queueCreateInfos.push_back(queueInfo);
			}
		}
	}


	VkCommandPool VulkanLogicalDevice::CreateCommandPool(int32_t queueIndex, VkCommandPoolCreateFlags createFlags)
	{
		VkCommandPoolCreateInfo cmdPoolInfo = {};
		cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cmdPoolInfo.queueFamilyIndex = (uint32_t)queueIndex;
		cmdPoolInfo.flags = createFlags;

		VkCommandPool cmdPool;
		auto result = vkCreateCommandPool(m_VKLogicalDevice, &cmdPoolInfo, nullptr, &cmdPool);
		if (result != VK_SUCCESS)
		{
			m_VKSystem->ReportVKError(result);
			return VK_NULL_HANDLE;
		}

		return cmdPool;
	}

	void VulkanLogicalDevice::GetGraphicsQueue(VkQueue& queue)
	{
		vkGetDeviceQueue(m_VKLogicalDevice, m_QueueIndices.graphics, 0, &queue);
	}

	// Flush command queue
	void VulkanLogicalDevice::FlushCommandQueue()
	{
		if (m_VKLogicalDevice == nullptr)
			return;

		vkDeviceWaitIdle(m_VKLogicalDevice);
	}

	// Allocate device memory
	VkResult VulkanLogicalDevice::AllocateDeviceMemory(VkMemoryRequirements memReqs, VkDeviceMemory &memory)
	{
		if (m_VKLogicalDevice == nullptr)
			return VK_NOT_READY;

		VkMemoryAllocateInfo mem_alloc = {};
		mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		mem_alloc.pNext = NULL;
		mem_alloc.allocationSize = 0;
		mem_alloc.memoryTypeIndex = 0;
		mem_alloc.allocationSize = memReqs.size;
		mem_alloc.memoryTypeIndex = m_VKPhysicalDevice->FindMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		return vkAllocateMemory(m_VKLogicalDevice, &mem_alloc, nullptr, &memory);
	}


}


#endif // #if HAVE_VULKAN


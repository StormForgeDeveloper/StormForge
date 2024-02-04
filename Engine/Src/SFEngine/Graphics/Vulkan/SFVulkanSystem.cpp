////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan system
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"
#include "Graphics/Vulkan/SFVulkanPhysicalDevice.h"
#include "Util/SFLog.h"


#if SF_USE_VULKAN



namespace SF
{
	template class DynamicArray<VkLayerProperties>;
	template class DynamicArray<VkPhysicalDevice>;
	template class DynamicArray<VkExtensionProperties>;
	template class DynamicArray<VkMemoryHeap>;
	template class DynamicArray<VkMemoryType>;


	constexpr StringCrc64 VulkanSystem::TypeName;


	VulkanSystem::VulkanSystem()
		: LibraryComponent("VulkanSystem")
		, m_VKInstance(VK_NULL_HANDLE)
		, m_InstanceLayers(GetEngineHeap())
		, m_Extensions(GetEngineHeap())
		, m_EnabledLayers(GetEngineHeap())
		, m_PhysicalDevices(GetEngineHeap())
		, m_VulkanDebug(nullptr)
	{
		
	}

	VulkanSystem::~VulkanSystem()
	{
		GetEngineHeap().Delete(m_VulkanDebug);
		m_VulkanDebug = nullptr;

		if (m_VKInstance != nullptr)
			vkDestroyInstance(m_VKInstance, nullptr);
	}


	// helper utility for vk error report
	void VulkanSystem::ReportVKError(VkResult vkError)
	{
		SFLog(System, Error, "VulkanError : {0:X8}", (uint32_t)vkError);
	}


	// Create Vulkan instance
	VkResult VulkanSystem::CreateVKInstance(bool enableValidation)
	{

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = Util::GetModuleName();
		appInfo.pEngineName = "StromForge";
		appInfo.apiVersion = VK_API_VERSION_1_0;

		std::vector<const char*> extensions = { VK_KHR_SURFACE_EXTENSION_NAME };

		// Enable surface extensions depending on OS
		extensions.push_back(SFVK_SURFACE_EXTENSION_NAME);

		VkInstanceCreateInfo instanceCreateInfo = {};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pNext = NULL;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		if (extensions.size() > 0)
		{
			if (enableValidation)
			{
				extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			}
			instanceCreateInfo.enabledExtensionCount = (uint32_t)extensions.size();
			instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
		}
		if (enableValidation)
		{
			// Setup validation layer list
			m_EnabledLayers.Clear();
#if SF_PLATFORM == SF_PLATFORM_ANDROID
			// On Android we need to enabled them one by one
			m_EnabledLayers.push_back("VK_LAYER_GOOGLE_threading");
			m_EnabledLayers.push_back("VK_LAYER_LUNARG_parameter_validation");
			m_EnabledLayers.push_back("VK_LAYER_LUNARG_object_tracker");
			m_EnabledLayers.push_back("VK_LAYER_LUNARG_core_validation");
			m_EnabledLayers.push_back("VK_LAYER_LUNARG_swapchain");
			m_EnabledLayers.push_back("VK_LAYER_GOOGLE_unique_objects");
#else
			// On other platform, lunarG has a package layer
			//m_EnabledLayers.push_back("VK_LAYER_LUNARG_standard_validation"); // TODO: Not supported with new SDK
#endif

			instanceCreateInfo.enabledLayerCount = (decltype(instanceCreateInfo.enabledLayerCount))m_EnabledLayers.size();
			instanceCreateInfo.ppEnabledLayerNames = m_EnabledLayers.data();
		}

		VkResult vkRes = vkCreateInstance(&instanceCreateInfo, nullptr, &m_VKInstance);

		return vkRes;
	}


	VkResult VulkanSystem::EnumerateDeviceList()
	{
		uint32_t enumCount = 0;

		if (m_VKInstance == nullptr)
			return VK_NOT_READY;

		// Physics devices
		// Get number of available physical devices
		m_PhysicalDevices.Clear();
		auto result = vkEnumeratePhysicalDevices(m_VKInstance, &enumCount, nullptr);
		if (result != VK_SUCCESS || enumCount == 0)
		{
			assert(false);
			return result;
		}
		else
		{
			// Enumerate devices
			m_PhysicalDevices.resize(enumCount);
			result = vkEnumeratePhysicalDevices(m_VKInstance, &enumCount, m_PhysicalDevices.data());
			if (result != VK_SUCCESS)
				return result;
		}

		return VK_SUCCESS;
	}

	VkResult VulkanSystem::EnumerateInstanceLayers()
	{
		uint32_t enumCount = 0;

		// Physics devices
		// Get number of available physical devices
		auto result = vkEnumerateInstanceLayerProperties(&enumCount, nullptr);
		if (result != VK_SUCCESS || enumCount == 0)
		{
			assert(false);
			return result;
		}
		else
		{
			// Enumerate devices
			m_InstanceLayers.resize(enumCount);
			result = vkEnumerateInstanceLayerProperties(&enumCount, m_InstanceLayers.data());
			if (result != VK_SUCCESS)
				return result;
		}

		return VK_SUCCESS;
	}


	VkResult VulkanSystem::EnumerateExtensionProperties(const char* extensionName, Array<VkExtensionProperties>& properties)
	{
		uint32_t enumCount = 0;

		properties.Clear();
		auto result = vkEnumerateInstanceExtensionProperties(extensionName, &enumCount, nullptr);
		if (result != VK_SUCCESS || enumCount == 0)
		{
			return result;
		}
		else
		{
			// Enumerate devices
			properties.resize(enumCount);
			result = vkEnumerateInstanceExtensionProperties(extensionName, &enumCount, properties.data());
		}

		return result;
	}


	// Create physical device
	VulkanPhysicalDevice* VulkanSystem::CreatePhysicalDevice(IHeap& heap, VkPhysicalDevice deviceToCreate)
	{
		auto pDevice = new(heap) VulkanPhysicalDevice(heap, this, deviceToCreate);
		auto result = pDevice->Initialize();
		if (result != VK_SUCCESS)
		{
			ReportVKError(result);
			IHeap::Delete(pDevice);
			return nullptr;
		}

		return pDevice;
	}

	// Initialize component
	Result VulkanSystem::InitializeComponent()
	{
		SFVulkanLibrary_Initialize();
		VkResult vkResult;

		vkResult = EnumerateInstanceLayers();
		if (vkResult != VK_SUCCESS)
			return ResultCode::ENGINE_INITIALIZATION_FAILED;

		vkResult = EnumerateExtensionProperties(nullptr, m_Extensions);
		if (vkResult != VK_SUCCESS)
			return ResultCode::ENGINE_INITIALIZATION_FAILED;

#if defined(_DEBUG) || defined(DEBUG)
		vkResult = CreateVKInstance(true);
#else
		vkResult = CreateVKInstance(false);
#endif
		if (vkResult != VK_SUCCESS)
			return ResultCode::ENGINE_INITIALIZATION_FAILED;

		GetEngineHeap().Delete(m_VulkanDebug);
		m_VulkanDebug = new(GetHeap()) VulkanDebug(m_VKInstance);

		EnumerateDeviceList();

		return super::InitializeComponent();
	}

	// Terminate component
	void VulkanSystem::DeinitializeComponent()
	{
		return super::DeinitializeComponent();
		// We need to handle reverse dependency to move deinitialization to here
	}

}


#endif // #if SF_USE_VULKAN


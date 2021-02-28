////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan system
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Component/SFLibraryComponent.h"
#include "Graphics/Vulkan/SFVulkanLibrary.h"
#include "Graphics/Vulkan/SFVulkanDebug.h"

#if HAVE_VULKAN

namespace SF
{

	////////////////////////////////////////////////////////////////////
	//
	//	Default value accessors for Vulkan
	//


	//template instancing
	extern template class DynamicArray<VkLayerProperties>;
	extern template class DynamicArray<VkPhysicalDevice>;
	extern template class DynamicArray<VkExtensionProperties>;
	extern template class DynamicArray<VkMemoryHeap>;
	extern template class DynamicArray<VkMemoryType>;


	class VulkanPhysicalDevice;




	////////////////////////////////////////////////////////////////////////////////
	//
	//	VulkanDeviceInitContext, device initialize parameter
	//

	struct VulkanDeviceInitParameter
	{
		bool UsageGraphic;
		bool UsageCompute;
		bool UsageTransfer;
		bool EnableSwapChain;
		VkSurfaceKHR Surface;
	};


	////////////////////////////////////////////////////////////////////
	//
	//	Vulkan system
	//		- Vulkan system separated from GraphciDeviceVulkan because it will be used for compute service as well
	//

	class VulkanSystem : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "VulkanSystem";

		typedef LibraryComponent super;

	private:

		// Vulkan system instance
		VkInstance m_VKInstance;

		// Layer list to be enabled
		DynamicArray<VkLayerProperties> m_InstanceLayers;
		DynamicArray<VkExtensionProperties> m_Extensions;
		DynamicArray<const char*> m_EnabledLayers;

		// Physical device list
		DynamicArray<VkPhysicalDevice> m_PhysicalDevices;

		VulkanDebug* m_VulkanDebug;


	private:


		// Create Vulkan instance
		VkResult CreateVKInstance(bool enableValidation);

		VkResult EnumerateDeviceList();
		VkResult EnumerateInstanceLayers();
		VkResult EnumerateExtensionProperties(const char* extensionName, Array<VkExtensionProperties>& properties);


		IHeap& GetHeap() { return GetEngineHeap(); }


	public:
		VulkanSystem();
		~VulkanSystem();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		VkInstance GetVulkan() { return m_VKInstance; }


		// helper utility for vk error report
		void ReportVKError(VkResult vkError);

		// Get VulkanInstance
		VkInstance GetVKInstance() { return m_VKInstance; }

		// Get Device list
		const Array<VkPhysicalDevice>& GetPhysicalDevices() { return m_PhysicalDevices; }
		// Get device supported layers
		const Array<VkLayerProperties>& GetSupportedLayers() { return m_InstanceLayers; }
		// Get device supported extensions
		const Array<VkExtensionProperties>& GetSupportedExtensions() { return m_Extensions; }
		// Get device enabled layers
		const Array<const char*>& GetEnabledLayers() { return m_EnabledLayers; }

		// Create physical device
		VulkanPhysicalDevice* CreatePhysicalDevice(IHeap& heap, VkPhysicalDevice deviceToCreate);

		// Initialize component
		virtual Result InitializeComponent() override;
		// Terminate component
		virtual void DeinitializeComponent() override;

	};

}


#endif // #if HAVE_VULKAN

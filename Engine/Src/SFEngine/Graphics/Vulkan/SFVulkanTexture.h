////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan texture
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#if SF_USE_VULKAN

#include "Resource/SFDeviceTexture.h"
#include "Graphics/Vulkan/SFVulkanSystem.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	Resource
	//
	class VulkanTexture : public DeviceTexture
	{
	public:


	private:

		//VkImage m_VKImage;
		//VkDeviceMemory m_VKMemory;
		VkImageView m_VKView;

	public:
		VulkanTexture(IHeap& heap, GraphicDevice* pDevice, Texture* sourceResource);
		virtual ~VulkanTexture();

		VkImageView GetDeviceImage() { return m_VKView; }

		virtual void Dispose() override;
	};


	typedef SharedPointerT<VulkanTexture> VulkanTexturePtr;
	extern template class SharedPointerT<VulkanTexture>;

}

#endif //#if SF_USE_VULKAN


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vulkan texture
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"

#if HAVE_VULKAN

#include "Graphics/Vulkan/SFVulkanTexture.h"
#include "Graphics/Vulkan/SFVulkanLogicalDevice.h"
#include "Graphics/SFGraphicDeviceVulkan.h"


namespace SF
{
	template class SharedPointerT<VulkanTexture>;

	struct TextureFormatConversion
	{
		TextureFormat	SFFormat;
		VkFormat		VKFormat;
		bool			RenderTarget;
		bool			CompressionTarget;
	};

	static TextureFormatConversion g_TextureFormatConversionTable[(int)TextureFormat::Max] =
	{
		{ TextureFormat::INVALID,		VK_FORMAT_UNDEFINED, true, false },

		{ TextureFormat::R8_UNORM,		VK_FORMAT_R8_UNORM, true, false },
		{ TextureFormat::R8_SNORM,		VK_FORMAT_R8_SNORM, true, false },
		{ TextureFormat::R8G8_UNORM,	VK_FORMAT_R8G8_UNORM, true, false },
		{ TextureFormat::R8G8_SNORM,	VK_FORMAT_R8G8_SNORM, true, false },
		{ TextureFormat::R8G8B8_UNORM,	VK_FORMAT_R8G8B8_UNORM, true, false },
		{ TextureFormat::R8G8B8_SNORM,	VK_FORMAT_R8G8B8_SNORM, true, false },
		{ TextureFormat::B8G8R8_UINT,	VK_FORMAT_B8G8R8_UINT, true, false },
		{ TextureFormat::B8G8R8_SINT,	VK_FORMAT_B8G8R8_SINT, true, false },
		{ TextureFormat::B8G8R8_SRGB,	VK_FORMAT_B8G8R8_SRGB, true, false },

		{ TextureFormat::R8G8B8A8_UNORM,	VK_FORMAT_R8G8B8A8_UNORM, true, false },
		{ TextureFormat::R8G8B8A8_SNORM,	VK_FORMAT_R8G8B8A8_SNORM, true, false },

		{ TextureFormat::A8B8G8R8_UNORM_PACK32,	VK_FORMAT_A8B8G8R8_UNORM_PACK32, true, false },
		{ TextureFormat::A8B8G8R8_SNORM_PACK32,	VK_FORMAT_A8B8G8R8_SNORM_PACK32, true, false },

		{ TextureFormat::R16_UNORM,	VK_FORMAT_R16_UNORM, true, false },
		{ TextureFormat::R16_SNORM,	VK_FORMAT_R16_SNORM, true, false },
		{ TextureFormat::R16_SFLOAT,	VK_FORMAT_R16_SFLOAT, true, false },
		{ TextureFormat::R16G16_SFLOAT,	VK_FORMAT_R16G16_SFLOAT, true, false },
		{ TextureFormat::R16G16B16_SFLOAT,	VK_FORMAT_R16G16B16_SFLOAT, true, false },
		{ TextureFormat::R16G16B16A16_SFLOAT,	VK_FORMAT_R16G16B16A16_SFLOAT, true, false },

		{ TextureFormat::R32_UINT,		VK_FORMAT_R32_UINT, true, false },
		{ TextureFormat::R32_SINT,		VK_FORMAT_R32_SINT, true, false },
		{ TextureFormat::R32_SFLOAT,	VK_FORMAT_R32_SFLOAT, true, false },

		{ TextureFormat::R32G32_UINT,		VK_FORMAT_R32G32_UINT, true, false },
		{ TextureFormat::R32G32_SINT,		VK_FORMAT_R32G32_SINT, true, false },
		{ TextureFormat::R32G32_SFLOAT,		VK_FORMAT_R32G32_SFLOAT, true, false },

		{ TextureFormat::R32G32B32_UINT,		VK_FORMAT_R32G32B32_UINT, true, false },
		{ TextureFormat::R32G32B32_SINT,		VK_FORMAT_R32G32B32_SINT, true, false },
		{ TextureFormat::R32G32B32_SFLOAT,		VK_FORMAT_R32G32B32_SFLOAT, true, false },

		{ TextureFormat::R32G32B32A32_UINT,		VK_FORMAT_R32G32B32A32_UINT, true, false },
		{ TextureFormat::R32G32B32A32_SINT,		VK_FORMAT_R32G32B32A32_SINT, true, false },
		{ TextureFormat::R32G32B32A32_SFLOAT,	VK_FORMAT_R32G32B32A32_SFLOAT, true, false },

		{ TextureFormat::R64_UINT,				VK_FORMAT_R64_UINT, true, false },
		{ TextureFormat::R64_SINT,				VK_FORMAT_R64_SINT, true, false },
		{ TextureFormat::R64_SFLOAT,			VK_FORMAT_R64_SFLOAT, true, false },

		{ TextureFormat::R64G64_UINT,			VK_FORMAT_R64G64_UINT, true, false },
		{ TextureFormat::R64G64_SINT,			VK_FORMAT_R64G64_SINT, true, false },
		{ TextureFormat::R64G64_SFLOAT,			VK_FORMAT_R64G64_SFLOAT, true, false },

		{ TextureFormat::R64G64B64_UINT,		VK_FORMAT_R64G64B64_UINT, true, false },
		{ TextureFormat::R64G64B64_SINT,		VK_FORMAT_R64G64B64_SINT, true, false },
		{ TextureFormat::R64G64B64_SFLOAT,		VK_FORMAT_R64G64B64_SFLOAT, true, false },

		{ TextureFormat::R64G64B64A64_UINT,		VK_FORMAT_R64G64B64A64_UINT, true, false },
		{ TextureFormat::R64G64B64A64_SINT,		VK_FORMAT_R64G64B64A64_SINT, true, false },
		{ TextureFormat::R64G64B64A64_SFLOAT,	VK_FORMAT_R64G64B64A64_SFLOAT, true, false },


		{ TextureFormat::D16_UNORM,								VK_FORMAT_D16_UNORM, true, false },
		{ TextureFormat::X8_D24_UNORM_PACK32,					VK_FORMAT_X8_D24_UNORM_PACK32, true, false },
		{ TextureFormat::D32_SFLOAT,							VK_FORMAT_D32_SFLOAT, true, false },
		{ TextureFormat::S8_UINT,								VK_FORMAT_S8_UINT, true, false },
		{ TextureFormat::D16_UNORM_S8_UINT,						VK_FORMAT_D16_UNORM_S8_UINT, true, false },
		{ TextureFormat::D24_UNORM_S8_UINT,						VK_FORMAT_D24_UNORM_S8_UINT, true, false },
		{ TextureFormat::D32_SFLOAT_S8_UINT,					VK_FORMAT_D32_SFLOAT_S8_UINT, true, false },

		{ TextureFormat::BC1_RGB_UNORM_BLOCK,					VK_FORMAT_BC1_RGB_UNORM_BLOCK, false, false },
		{ TextureFormat::BC1_RGB_SRGB_BLOCK,					VK_FORMAT_BC1_RGB_SRGB_BLOCK, false, false },
		{ TextureFormat::BC1_RGBA_UNORM_BLOCK,					VK_FORMAT_BC1_RGBA_UNORM_BLOCK, false, false },
		{ TextureFormat::BC1_RGBA_SRGB_BLOCK,					VK_FORMAT_BC1_RGBA_SRGB_BLOCK, false, false },

		{ TextureFormat::BC2_UNORM_BLOCK,						VK_FORMAT_BC2_UNORM_BLOCK, false, false },
		{ TextureFormat::BC2_SRGB_BLOCK,						VK_FORMAT_BC2_SRGB_BLOCK, false, false },

		{ TextureFormat::BC3_UNORM_BLOCK,						VK_FORMAT_BC3_UNORM_BLOCK, false, false },
		{ TextureFormat::BC3_SRGB_BLOCK,						VK_FORMAT_BC3_SRGB_BLOCK, false, false },

		{ TextureFormat::BC4_UNORM_BLOCK,						VK_FORMAT_BC4_UNORM_BLOCK, false, false },
		{ TextureFormat::BC4_SNORM_BLOCK,						VK_FORMAT_BC4_SNORM_BLOCK, false, false },

		{ TextureFormat::BC5_UNORM_BLOCK,						VK_FORMAT_BC5_UNORM_BLOCK, false, false },
		{ TextureFormat::BC5_SNORM_BLOCK,						VK_FORMAT_BC5_SNORM_BLOCK, false, false },

		{ TextureFormat::BC6H_UFLOAT_BLOCK,						VK_FORMAT_BC6H_UFLOAT_BLOCK, false, false },
		{ TextureFormat::BC6H_SFLOAT_BLOCK,						VK_FORMAT_BC6H_SFLOAT_BLOCK, false, false },

		{ TextureFormat::BC7_UNORM_BLOCK,						VK_FORMAT_BC7_UNORM_BLOCK, false, false },
		{ TextureFormat::BC7_SRGB_BLOCK,						VK_FORMAT_BC7_SRGB_BLOCK, false, false },

		{ TextureFormat::ETC2_R8G8B8_UNORM_BLOCK,				VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK, false, false },
		{ TextureFormat::ETC2_R8G8B8_SRGB_BLOCK,				VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK, false, false },
		{ TextureFormat::ETC2_R8G8B8A1_UNORM_BLOCK,				VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK, false, false },
		{ TextureFormat::ETC2_R8G8B8A1_SRGB_BLOCK,				VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK, false, false },
		{ TextureFormat::ETC2_R8G8B8A8_UNORM_BLOCK,				VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK, false, false },
		{ TextureFormat::ETC2_R8G8B8A8_SRGB_BLOCK,				VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK, false, false },

		{ TextureFormat::EAC_R11_UNORM_BLOCK,					VK_FORMAT_EAC_R11_UNORM_BLOCK, false, false },
		{ TextureFormat::EAC_R11_SNORM_BLOCK,					VK_FORMAT_EAC_R11_SNORM_BLOCK, false, false },
		{ TextureFormat::EAC_R11G11_UNORM_BLOCK,				VK_FORMAT_EAC_R11G11_UNORM_BLOCK, false, false },
		{ TextureFormat::EAC_R11G11_SNORM_BLOCK,				VK_FORMAT_EAC_R11G11_SNORM_BLOCK, false, false },

		{ TextureFormat::ASTC_4x4_UNORM_BLOCK,					VK_FORMAT_ASTC_4x4_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_4x4_SRGB_BLOCK,					VK_FORMAT_ASTC_4x4_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_5x4_UNORM_BLOCK,					VK_FORMAT_ASTC_5x4_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_5x4_SRGB_BLOCK,					VK_FORMAT_ASTC_5x4_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_5x5_UNORM_BLOCK,					VK_FORMAT_ASTC_5x5_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_5x5_SRGB_BLOCK,					VK_FORMAT_ASTC_5x5_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_6x5_UNORM_BLOCK,					VK_FORMAT_ASTC_6x5_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_6x5_SRGB_BLOCK,					VK_FORMAT_ASTC_6x5_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_6x6_UNORM_BLOCK,					VK_FORMAT_ASTC_6x6_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_6x6_SRGB_BLOCK,					VK_FORMAT_ASTC_6x6_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_8x5_UNORM_BLOCK,					VK_FORMAT_ASTC_8x5_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_8x5_SRGB_BLOCK,					VK_FORMAT_ASTC_8x5_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_8x6_UNORM_BLOCK,					VK_FORMAT_ASTC_8x6_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_8x6_SRGB_BLOCK,					VK_FORMAT_ASTC_8x6_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_8x8_UNORM_BLOCK,					VK_FORMAT_ASTC_8x8_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_8x8_SRGB_BLOCK,					VK_FORMAT_ASTC_8x8_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_10x5_UNORM_BLOCK,					VK_FORMAT_ASTC_10x5_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_10x5_SRGB_BLOCK,					VK_FORMAT_ASTC_10x5_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_10x6_UNORM_BLOCK,					VK_FORMAT_ASTC_10x6_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_10x6_SRGB_BLOCK,					VK_FORMAT_ASTC_10x6_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_10x8_UNORM_BLOCK,					VK_FORMAT_ASTC_10x8_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_10x8_SRGB_BLOCK,					VK_FORMAT_ASTC_10x8_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_10x10_UNORM_BLOCK,				VK_FORMAT_ASTC_10x10_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_10x10_SRGB_BLOCK,					VK_FORMAT_ASTC_10x10_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_12x10_UNORM_BLOCK,				VK_FORMAT_ASTC_12x10_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_12x10_SRGB_BLOCK,					VK_FORMAT_ASTC_12x10_SRGB_BLOCK, false, false },
		{ TextureFormat::ASTC_12x12_UNORM_BLOCK,				VK_FORMAT_ASTC_12x12_UNORM_BLOCK, false, false },
		{ TextureFormat::ASTC_12x12_SRGB_BLOCK,					VK_FORMAT_ASTC_12x12_SRGB_BLOCK, false, false },
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		{ TextureFormat::PVRTC1_2BPP_UNORM_BLOCK_IMG,			VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG, false, false },
		{ TextureFormat::PVRTC1_4BPP_UNORM_BLOCK_IMG,			VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG, false, false },
		{ TextureFormat::PVRTC2_2BPP_UNORM_BLOCK_IMG,			VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG, false, false },
		{ TextureFormat::PVRTC2_4BPP_UNORM_BLOCK_IMG,			VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG, false, false },
		{ TextureFormat::PVRTC1_2BPP_SRGB_BLOCK_IMG,			VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG, false, false },
		{ TextureFormat::PVRTC1_4BPP_SRGB_BLOCK_IMG,			VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG, false, false },
		{ TextureFormat::PVRTC2_2BPP_SRGB_BLOCK_IMG,			VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG, false, false },
		{ TextureFormat::PVRTC2_4BPP_SRGB_BLOCK_IMG,			VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG, false, false },
#endif
	};

	// GetDevice Texture format
	// This function made best guess for the texture
	uint32_t DeviceTexture::GetDeviceFormatFor(TextureFormat format)
	{
		return g_TextureFormatConversionTable[(int)format].VKFormat;
	}



	VulkanTexture::VulkanTexture(IHeap& heap, GraphicDevice* pDevice, Texture* sourceResource)
		: DeviceTexture(heap, pDevice, sourceResource)
		, m_VKView(VK_NULL_HANDLE)
	{

	}

	VulkanTexture::~VulkanTexture()
	{

	}

	void VulkanTexture::Dispose()
	{
		if (m_VKView != VK_NULL_HANDLE)
		{
			auto pDevice = static_cast<GraphicDeviceVulkan*>(GetDevice());
			auto pLogicalDevice = pDevice->GetVKLogicalDevice();
			if(pLogicalDevice != nullptr)
				vkDestroyImageView(pLogicalDevice->GetLogicalDevice(), m_VKView, nullptr);
		}
		m_VKView = VK_NULL_HANDLE;
	}

		//VkMemoryRequirements buffer_memory_requirements;
		//vkGetBufferMemoryRequirements(GetDevice(), buffer, &buffer_memory_requirements);

		//VkPhysicalDeviceMemoryProperties memory_properties;

		//vkGetPhysicalDeviceMemoryProperties(GetPhysicalDevice(), &memory_properties);


		//for (uint32_t i = 0; i < memory_properties.memoryTypeCount; ++i) {

		//		if ((buffer_memory_requirements.memoryTypeBits & (1 << i)) &&

		//			(memory_properties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)) {


		//				VkMemoryAllocateInfo memory_allocate_info = {

		//				VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,     // VkStructureType                        sType
		//				nullptr,                                    // const void                            *pNext
		//				buffer_memory_requirements.size,            // VkDeviceSize                           allocationSize
		//				i                                           // uint32_t                               memoryTypeIndex
		//			};

		//				if (vkAllocateMemory(GetDevice(), &memory_allocate_info, nullptr, memory) == VK_SUCCESS) {
		//						return true;
		//				}
		//		}
		//}

}

#endif // #if HAVE_VULKAN


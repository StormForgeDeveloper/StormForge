////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Texture format description
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFTextureFormatDescription.h"


namespace SF
{
	// format descriptor table
	static const TextureFormatDescription g_TextureFormatDescriptions[] = 
	{
		// Format                                 Channels BPP    WAlign   HasAlpha
		{ TextureFormat::R8_UNORM,					1,		1,		4,		false },
		{ TextureFormat::R8_SNORM,					1,		1,		4,		false },
		{ TextureFormat::R8G8_UNORM,				2,		2,		4,		false },
		{ TextureFormat::R8G8_SNORM,				2,		2,		4,		false },
		{ TextureFormat::R8G8B8_UNORM,				3,		3,		4,		false },
		{ TextureFormat::R8G8B8_SNORM,				3,		3,		4,		false },
		{ TextureFormat::B8G8R8_UINT,				3,		3,		4,		false },
		{ TextureFormat::B8G8R8_SINT,				3,		3,		4,		false },
		{ TextureFormat::B8G8R8_SRGB,				3,		3,		4,		false },
		{ TextureFormat::R8G8B8A8_UNORM,			4,		4,		4,		true  },
		{ TextureFormat::R8G8B8A8_SNORM,			4,		4,		4,		true  },
		{ TextureFormat::A8B8G8R8_UNORM_PACK32,		4,		4,		4,		true  },
		{ TextureFormat::A8B8G8R8_SNORM_PACK32,		4,		4,		4,		true  },
	};


	////////////////////////////////////////////////////////////////////////////
	//
	//	Texture helper
	//
	Result TextureFormatDescription::IsSupportedFormat(TextureFormat format)
	{
		return GetDescriptor(format) != nullptr ?  ResultCode::SUCCESS : ResultCode::NOT_SUPPORTED;
	}

	const TextureFormatDescription* TextureFormatDescription::GetDescriptor(TextureFormat format)
	{
		for (uint iDesc = 0; iDesc < countof(g_TextureFormatDescriptions); iDesc++)
		{
			auto& desc = g_TextureFormatDescriptions[iDesc];
			if (desc.Format == format)
				return &desc;
		}

		Assert(false);// not supported

		return nullptr;
	}
}


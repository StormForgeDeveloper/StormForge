////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Texture format description
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "Resource/SFTextureFormat.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	Texture description
	//
	struct TextureFormatDescription
	{
		// element format
		TextureFormat		Format;

		// number of color channel
		uint				ChannelCount : 4;

		// bytes per pixel
		uint				BytesPerPixel : 4;

		// width alignment
		uint				WidthAlignment : 8;

		// Has alpha?
		bool				HasAlpha : 1;


		////////////////////////////////////////////////////////////////////////////
		//
		//	Texture format helper
		//
		static Result IsSupportedFormat(TextureFormat format);
		static const TextureFormatDescription* GetDescriptor(TextureFormat format);

	};



}


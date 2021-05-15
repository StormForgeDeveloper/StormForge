////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : PNG image asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Asset/Importer/SFAssetImporterTexturePNG.h"
#include "Resource/SFTexture.h"

#include "png.h"



namespace SF
{


	namespace ImplPNG
	{
		// Func png convert
		typedef void(*T_Func_png_Convert)(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);

		// PNGColorTypeDesc
		struct PNGColorTypeDesc
		{
			int ColorType;
			int BitDepth		: 16;
			int NumPalette		: 16;
			bool IsGrayScale	: 1;
			bool HasAlpha		: 1;
			TextureFormat	ConvertTo;
			T_Func_png_Convert RowCopyFunction;
		};

		// converts forward declaration
		void Func_png_Convert_Gray1(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_png_Convert_Gray4(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_png_Convert_Gray8(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);

		void Func_png_Convert_Palette4(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_png_Convert_Palette8(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);

		void Func_png_Convert_RGB(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_png_Convert_RGBA(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_png_Convert_GrayAlpha(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);


		// Color Type Desc
		const PNGColorTypeDesc g_ColorTypeDesc[] =
		{
			{ PNG_COLOR_TYPE_GRAY,			1,	0,		true,	false, TextureFormat::R8_UNORM,			Func_png_Convert_Gray1 },
			{ PNG_COLOR_TYPE_GRAY,			4,	0,		true,	false, TextureFormat::R8_UNORM,			Func_png_Convert_Gray4 },
			{ PNG_COLOR_TYPE_GRAY,			8,	0,		true,	false, TextureFormat::R8_UNORM,			Func_png_Convert_Gray8 },

			{ PNG_COLOR_TYPE_PALETTE,		4,	16,		false,	false, TextureFormat::R8G8B8_UNORM,		Func_png_Convert_Palette4 },
			{ PNG_COLOR_TYPE_PALETTE,		8,	256,	false,	false, TextureFormat::R8G8B8_UNORM,		Func_png_Convert_Palette8 },

			{ PNG_COLOR_TYPE_RGB,			24,	0,		false,	false, TextureFormat::R8G8B8_UNORM,		Func_png_Convert_RGB },
			{ PNG_COLOR_TYPE_RGB_ALPHA,		32,	0,		false,	false, TextureFormat::R8G8B8A8_UNORM,	Func_png_Convert_RGBA },
			{ PNG_COLOR_TYPE_GRAY_ALPHA,	16,	0,		false,	false, TextureFormat::R8G8B8A8_UNORM,	Func_png_Convert_GrayAlpha },
		};


		const PNGColorTypeDesc* GetPNGFormatDescriptor(int bitDepth, int colorType)
		{
			for (uint iColorDesc = 0; iColorDesc < countof(ImplPNG::g_ColorTypeDesc); iColorDesc++)
			{
				auto& colorDesc = ImplPNG::g_ColorTypeDesc[iColorDesc];
				if (colorDesc.ColorType == colorType && colorDesc.BitDepth == bitDepth)
				{
					return &colorDesc;
				}
			}

			// failed to find format descriptor
			Assert(false);

			return nullptr;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Png read interface
		//
		void PNGCBAPI Func_png_rw(png_structp png_ptr, void* outBytes, size_t byteCountToRead)
		{
			png_voidp io_ptr = png_get_io_ptr((png_structp)png_ptr);
			if (io_ptr == nullptr)
				return;

			auto& inputStream = *(IInputStream*)io_ptr;
			auto result = inputStream.Read(outBytes, (size_t)byteCountToRead);

			if (!result)
				return;
		}

		// custom transform
		void PNGCBAPI Func_read_transform(png_structp png, png_row_infop row_info, png_bytep data)
		{

		}

		void PNGCBAPI Func_png_error()
		{

		}

		void* PNGCBAPI Func_png_malloc(png_structp png, png_alloc_size_t allocSize)
		{
			auto pHeap = (IHeap*)png_get_mem_ptr(png);
			if (pHeap == nullptr)
				return nullptr;

			return pHeap->Alloc(allocSize);
		}

		void PNGCBAPI Func_png_free(png_structp png, png_voidp pPtr)
		{
			auto pHeap = (IHeap*)png_get_mem_ptr(png);
			if (pHeap == nullptr)
				return;

			pHeap->Free(pPtr);
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Converting functions
		//

		void Func_png_Convert_Gray1(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			unused(palette);
			uint iDest = 0;
			for (uint iSrc = 0; iSrc < srcSize; iSrc++)
			{
				uint8_t srcByte = srcRowData[iSrc];
				for (uint iBit = 0; iBit < 8 && iDest < destSize; iBit++, iDest++, srcByte >>= 1)
				{
					destRowData[iDest] = (srcByte & 1) * 0xFF;
				}
			}
		}

		void Func_png_Convert_Gray4(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			unused(palette);
			uint iDest = 0;
			for (uint iSrc = 0; iSrc < srcSize; iSrc++)
			{
				uint8_t srcByte = srcRowData[iSrc];
				for (uint iBit = 0; iBit < 2 && iDest < destSize; iBit++, iDest++, srcByte >>= 4)
				{
					destRowData[iDest] = (uint8_t)(((uint32_t)(srcByte & 0xF) * 0xFF) / 0xF);
				}
			}
		}

		void Func_png_Convert_Gray8(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			unused(palette);
			auto copySize = Math::Min(destSize, srcSize);
			memcpy(destRowData, srcRowData, copySize);
		}


		void Func_png_Convert_Palette4(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			if (palette == nullptr)
			{
				Assert(false);
				return;
			}

			uint iDest = 0;
			for (uint iSrc = 0; iSrc < srcSize; iSrc++)
			{
				uint8_t srcByte = srcRowData[iSrc];
				for (int iBit = 0; iBit < 2 && iDest < destSize; iBit++, iDest+=3, srcByte >>= 4)
				{
					auto pPalettePos = &palette[srcByte];

					destRowData[iDest + 0] = pPalettePos[0];
					destRowData[iDest + 1] = pPalettePos[1];
					destRowData[iDest + 2] = pPalettePos[2];
				}
			}
		}

		void Func_png_Convert_Palette8(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			if (palette == nullptr)
			{
				Assert(false);
				return;
			}

			int iDest = 0;
			for (uint iSrc = 0; iSrc < srcSize; iSrc++, iDest += 3)
			{
				uint8_t srcByte = srcRowData[iSrc];
				auto pPalettePos = &palette[srcByte*3]; // 4?

				destRowData[iDest + 0] = pPalettePos[0];
				destRowData[iDest + 1] = pPalettePos[1];
				destRowData[iDest + 2] = pPalettePos[2];
			}
		}

		void Func_png_Convert_RGB(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			unused(palette);
			auto copySize = Math::Min(destSize, srcSize);
			memcpy(destRowData, srcRowData, copySize);
		}

		void Func_png_Convert_RGBA(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			unused(palette);
			auto copySize = Math::Min(destSize, srcSize);
			memcpy(destRowData, srcRowData, copySize);
		}


		void Func_png_Convert_GrayAlpha(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			unused(palette);
			for (uint iSrc = 0, iDest = 0; iSrc < srcSize; iSrc += 2, iDest++)
			{
				uint8_t srcByte = srcRowData[iSrc];
				destRowData[iDest + 0] = srcByte;
				destRowData[iDest + 1] = srcByte;
				destRowData[iDest + 2] = srcByte;
				destRowData[iDest + 4] = srcRowData[iSrc + 1];
			}
		}

	}




	AssetImporterTexturePNG::AssetImporterTexturePNG(IHeap& heap)
		: AssetImporterTexture(heap, "AssetImporterTexturePNG")
	{
		AddAssetType("png");
	}

	AssetImporterTexturePNG::~AssetImporterTexturePNG()
	{

	}

	// It returns resource and clear pointer inside
	Result AssetImporterTexturePNG::Import(AssetImportContext& context, Array<ResourcePtr>& resources)
	{
		png_structp png = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, 
			nullptr/*user_error_ptr*/, nullptr/*user_error_fn*/, nullptr/*user_warning_fn*/, 
			(png_voidp)&context.GetHeap()/*mem_ptr*/, ImplPNG::Func_png_malloc, ImplPNG::Func_png_free);

		if (png == nullptr)
			return ResultCode::OUT_OF_MEMORY;

		png_infop info = png_create_info_struct(png);
		if (info == nullptr)
		{
			png_destroy_read_struct(&png, NULL, NULL);
			return ResultCode::OUT_OF_MEMORY;
		}

		if (setjmp(png_jmpbuf(png)))
		{
			png_destroy_info_struct(png, &info);
			png_destroy_read_struct(&png, NULL, NULL);
			return ResultCode::FAIL;
		}

		/* tell libpng to strip 16 bit/color files down to 8 bits/color */
		png_set_strip_16(png);

		// invert transparent to alpha. default png uses transparent(1 for transparent). 
		png_set_invert_alpha(png);

		/* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
		* byte into separate bytes (useful for paletted and grayscale images).
		*/
		png_set_packing(png);


		// set custom transform function
		//png_set_read_user_transform_fn(png, ImplPNG::Func_read_transform);


		png_set_read_fn(png, &context.GetStream(), (png_rw_ptr)ImplPNG::Func_png_rw);

		png_read_info(png, info);

		png_uint_32 width = 0;
		png_uint_32 height = 0;
		int bitDepth = 0;
		int colorType = -1;
		png_uint_32 retval = png_get_IHDR(png, info,
			&width,
			&height,
			&bitDepth,
			&colorType,
			NULL, NULL, NULL);

		if (retval != 1)
			return ResultCode::FAIL;

		int numberOfChannels = png_get_channels(png, info);
		bitDepth *= numberOfChannels;

		/* Expand paletted colors into true RGB triplets */
		if (colorType == PNG_COLOR_TYPE_PALETTE)
		{
			colorType = PNG_COLOR_TYPE_RGB;
			png_set_palette_to_rgb(png);
		}

		///* Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel */
		//if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
		//{
		//	bitDepth = 8;
		//	png_set_expand_gray_1_2_4_to_8(png);
		//}

		auto pPngFormatDesc = ImplPNG::GetPNGFormatDescriptor(bitDepth, colorType);
		if (pPngFormatDesc == nullptr)
			return ResultCode::NOT_SUPPORTED_FORMAT;

		auto newRes = new(context.GetHeap()) Texture(context.GetHeap(), (const char*)context.GetSource());
		if (newRes == nullptr)
		{
			png_destroy_info_struct(png, &info);
			png_destroy_read_struct(&png, NULL, NULL);
			return ResultCode::OUT_OF_MEMORY;
		}


		newRes->SetSourceName((const char*)context.GetSource());
		TextureInitParameter texInit;
		memset(&texInit, 0, sizeof(texInit));
		texInit.Format = pPngFormatDesc->ConvertTo;
		texInit.Width = width;
		texInit.Height = height;
		texInit.FaceCount = 1;
		texInit.UseMipmap = true;
		texInit.Usage = TextureUsage::Transient;

		newRes->Init(texInit);

		resources.push_back(newRes);

		// TODO copy image data to texture
		auto rowByteSize = png_get_rowbytes(png, info);

#if 0 // defined(PNG_READ_INTERLACING_SUPPORTED)
		/* Turn on interlace handling.  REQUIRED if you are not using
		* png_read_image().  To see how to handle interlacing passes,
		* see the png_read_row() method below:
		*/
		int number_passes = png_set_interlace_handling(&png);
#else
		int number_passes = 1;
#endif /* PNG_READ_INTERLACING_SUPPORTED */

		auto lockedImage = newRes->LockImageData();
		auto pImage = (uint8_t*)lockedImage;
		auto bpp = newRes->GetBytePerPixel();
		auto widthAlign = newRes->GetWidthAlign();
		auto widthSize = width * bpp;
		widthSize = AlignUp(widthSize, widthAlign);

		Assert(pPngFormatDesc->NumPalette == 0); // We expect the png handled palette
		uint8_t* pReadBuffer = nullptr;
		bool useSingleBuffer = ((pPngFormatDesc->BitDepth / 8) == bpp)
			&& rowByteSize <= widthSize;
		
		if (useSingleBuffer)
		{
			for (int pass = 0; pass < number_passes; pass++)
			{
				for (uint y = 0; y < height; y++)
				{
					pReadBuffer = pImage;
					png_read_rows(png, (png_bytepp)&pReadBuffer, NULL, 1);
					pImage += widthSize; // TODO: this should be same. add check
				}
			}
		}
		else
		{
			pReadBuffer = new(GetHeap()) uint8_t[rowByteSize];
			for (int pass = 0; pass < number_passes; pass++)
			{
				for (uint y = 0; y < height; y++)
				{
					png_read_rows(png, (png_bytepp)&pReadBuffer, NULL, 1);
					pPngFormatDesc->RowCopyFunction(nullptr, const_cast<uint8_t*>(pImage), widthSize, pReadBuffer, rowByteSize);
					pImage += widthSize; // TODO: this should be same. add check
				}
			}
			IHeap::Delete(pReadBuffer);
		}

		png_destroy_info_struct(png, &info);
		png_destroy_read_struct(&png, NULL, NULL);


		return ResultCode::SUCCESS;
	}


}


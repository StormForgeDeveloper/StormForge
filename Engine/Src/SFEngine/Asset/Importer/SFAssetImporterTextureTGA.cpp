////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : ContextInfo image asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Asset/Importer/SFAssetImporterTextureTGA.h"
#include "Resource/SFTexture.h"




namespace SF
{


	namespace ImplTGA
	{
		enum class TGAImageType : uint8_t
		{
			NoImageData			= 0,
			Palette				= 1,
			Color				= 2,
			GrayScale			= 3,
			CompressedPalette	= 9,
			CompressedColor		= 10,
			CompressedGrayScale = 11
		};


		/* color format */
		//constexpr int TGA_RGB = 0x20;
		//constexpr int TGA_BGR = 0x40;

		/* orientation */
		//constexpr int TGA_BOTTOM = 0x0;
		//constexpr int TGA_TOP = 0x1;
		//constexpr int TGA_LEFT = 0x0;
		//constexpr int TGA_RIGHT = 0x1;


		// ContextInfo image header
#pragma pack(push,1)
		struct HeaderInfo {
			uint8_t			id_len;					/* image id length */
			uint8_t			paletteType;			/* color map type */
			TGAImageType	imageType;				/* image type */
			int16_t			paletteFirstIndex;		/* index of first map entry */
			int16_t			paletteCount;			/* number of entries in color map */
			uint8_t			paletteBitPerPixel;	/* bit-bitPerPixel of a cmap entry */
			int16_t			x;						/* x-coordinate */
			int16_t			y;						/* y-coordinate */
			int16_t			width;					/* width of image */
			int16_t			height;					/* height of image */
			uint8_t			bitPerPixel;			/* pixel-bitPerPixel of image */
			uint8_t			alphaDepth : 4;			/* alpha bits */
			uint8_t			horz : 1;				/* horizontal orientation */
			uint8_t			vert : 1;				/* vertical orientation */
			uint8_t : 0;
		};
#pragma pack(pop)


		struct ContextInfo {
			IInputStream*	stream = nullptr;
			IHeap*			Heap = nullptr;
			int64_t			StartPos = 0;
			HeaderInfo		hdr;

			int64_t GetCurrentOffset()
			{
				return (int64_t)stream->GetPosition() - StartPos;
			}
		};

		// Func ContextInfo convert
		typedef void(*T_Func_TGA_Convert)(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);

		// TGAColorTypeDesc
		struct TGAColorTypeDesc
		{
			TGAImageType		ColorType;
			int BitPerPixel		: 16;
			bool IsGrayScale	: 1;
			TextureFormat		ConvertTo;
			T_Func_TGA_Convert	RowCopyFunction;
		};


		// converts forward declaration
		void Func_TGA_Convert_RGBA32Palette4(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_TGA_Convert_RGBA32Palette8(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_TGA_Convert_RGBA16(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_TGA_Convert_RGB24(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_TGA_Convert_RGBA32(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_TGA_Convert_Gray(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);


		// Color Type Desc
		const TGAColorTypeDesc g_ColorTypeDesc[] =
		{
			{ TGAImageType::Palette,				8,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA32Palette8 },
			{ TGAImageType::Color,					15,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA16 },
			{ TGAImageType::Color,					16,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA16 },
			{ TGAImageType::Color,					24,		false,	TextureFormat::R8G8B8_UNORM,		Func_TGA_Convert_RGB24 },
			{ TGAImageType::Color,					32,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA32 },
			{ TGAImageType::GrayScale,				8,		true,	TextureFormat::R8G8B8_UNORM,		Func_TGA_Convert_Gray },
			{ TGAImageType::CompressedPalette,		8,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA32Palette8 },
			{ TGAImageType::CompressedColor,		15,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA16 },
			{ TGAImageType::CompressedColor,		16,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA16 },
			{ TGAImageType::CompressedColor,		24,		false,	TextureFormat::R8G8B8_UNORM,		Func_TGA_Convert_RGB24 },
			{ TGAImageType::CompressedColor,		32,		false,	TextureFormat::R8G8B8A8_UNORM,		Func_TGA_Convert_RGBA32 },
			{ TGAImageType::CompressedGrayScale,	8,		true,	TextureFormat::R8G8B8_UNORM,		Func_TGA_Convert_Gray },
		};


		const TGAColorTypeDesc* GetTGAFormatDescriptor(TGAImageType colorType, int bitbitPerPixel)
		{
			for (uint iColorDesc = 0; iColorDesc < countof(ImplTGA::g_ColorTypeDesc); iColorDesc++)
			{
				auto& colorDesc = ImplTGA::g_ColorTypeDesc[iColorDesc];
				if (colorDesc.ColorType == colorType && colorDesc.BitPerPixel == bitbitPerPixel)
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
		//	ContextInfo read interface
		//

		// This implementation based on libtga. http://tgalib.sourceforge.net/ 
		// References
		// https://en.wikipedia.org/wiki/Truevision_TGA
		// http://www.paulbourke.net/dataformats/tga/


		#define TGA_HEADER_SIZE				18
		#define TGA_PALETTE_SIZE(tga)		((tga).hdr.paletteCount * (tga).hdr.paletteBitPerPixel / 8)
		#define TGA_PALETTE_OFFSET(tga) 	(TGA_HEADER_SIZE + (tga).hdr.id_len)
		#define TGA_IMG_DATA_OFFSET(tga) 	(TGA_HEADER_SIZE + (tga).hdr.id_len + TGA_PALETTE_SIZE(tga))
		#define TGA_IMG_DATA_SIZE(tga)		((tga).hdr.width * (tga).hdr.height * (tga).hdr.bitPerPixel / 8)
		#define TGA_SCANLINE_SIZE(tga)		((tga).hdr.width * (tga).hdr.bitPerPixel / 8)
		#define TGA_CAN_SWAP(bitPerPixel)	(bitPerPixel == 24 || bitPerPixel == 32)

		#define TGA_IS_MAPPED(tga)			((tga).hdr.paletteType == 1)
		#define TGA_IS_COMPRESSED(tga)		((tga).hdr.imageType >= TGAImageType::CompressedPalette && (tga).hdr.imageType <= TGAImageType::CompressedGrayScale)



		// ContextInfo image structures


		//tga.hdr.id_len = tmp[0];
		//tga.hdr.paletteType = tmp[1];
		//tga.hdr.imageType = tmp[2];
		//tga.hdr.paletteFirstIndex = tmp[3] + tmp[4] * 256;
		//tga.hdr.paletteCount = tmp[5] + tmp[6] * 256;
		//tga.hdr.paletteBitPerPixel = tmp[7];
		//tga.hdr.x = tmp[8] + tmp[9] * 256;
		//tga.hdr.y = tmp[10] + tmp[11] * 256;
		//tga.hdr.width = tmp[12] + tmp[13] * 256;
		//tga.hdr.height = tmp[14] + tmp[15] * 256;
		//tga.hdr.bitPerPixel = tmp[16];
		//tga.hdr.alpha = tmp[17] & 0x0f;
		//tga.hdr.horz = (tmp[17] & 0x10) ? TGA_TOP : TGA_BOTTOM;
		//tga.hdr.vert = (tmp[17] & 0x20) ? TGA_RIGHT : TGA_LEFT;


		Result TGAReadHeader(ContextInfo &tga);
		Result TGAReadPalette(ContextInfo &tga, uint8_t* &buf);
		Result TGAReadRLE(ContextInfo &tga, uint8_t *buf, size_t szBufferSize);


		Result TGAReadHeader(ContextInfo& tga)
		{
			memset(&tga.hdr, 0, sizeof(tga.hdr));

			Result result = tga.stream->Read(&tga.hdr, TGA_HEADER_SIZE);
			if (!result)
				return result;


			if (tga.hdr.paletteType && tga.hdr.bitPerPixel != 8)
			{
				return ResultCode::NOT_SUPPORTED_FORMAT;
			}

			if (tga.hdr.bitPerPixel != 8 &&
				tga.hdr.bitPerPixel != 15 &&
				tga.hdr.bitPerPixel != 16 &&
				tga.hdr.bitPerPixel != 24 &&
				tga.hdr.bitPerPixel != 32)
			{
				return ResultCode::NOT_SUPPORTED_FORMAT;
			}

			return ResultCode::SUCCESS;
		}

		Result TGA16ToBGRA(uint16_t colorData, uint8_t* bytes)
		{
			union TGAColor16
			{
				struct TGAColor16Components
				{
					uint16_t R : 5;
					uint16_t G : 5;
					uint16_t B : 5;
					uint16_t A : 1;
				} Components;
				uint16_t Composited;
			};

			TGAColor16 color;
			color.Composited = colorData;// (uint16_t)buf[readPos - 1] + (uint16_t)buf[readPos] * 255;

			// We store BGRA. we will swap byte order later again
			bytes[0] = color.Components.B;
			bytes[1] = color.Components.G;
			bytes[2] = color.Components.R;
			bytes[3] = color.Components.A;

			return ResultCode::SUCCESS;
		}

		Result TGA16ToRGBA(uint16_t colorData, uint8_t* bytes)
		{
			union TGAColor16
			{
				struct TGAColor16Components
				{
					uint16_t R : 5;
					uint16_t G : 5;
					uint16_t B : 5;
					uint16_t A : 1;
				} Components;
				uint16_t Composited;
			};

			TGAColor16 color;
			color.Composited = colorData;// (uint16_t)buf[readPos - 1] + (uint16_t)buf[readPos] * 255;

			// We store BGRA. we will swap byte order later again
			bytes[0] = color.Components.R;
			bytes[1] = color.Components.G;
			bytes[2] = color.Components.B;
			bytes[3] = color.Components.A;

			return ResultCode::SUCCESS;
		}

		Result TGAReadPalette(ContextInfo &tga, uint8_t* &buf)
		{
			Result result;

			int64_t paletteSize = TGA_PALETTE_SIZE(tga);
			if (paletteSize <= 0) return 0;

			int64_t off = TGA_PALETTE_OFFSET(tga);

			if (tga.GetCurrentOffset() != off)
			{
				Assert(false);
				return ResultCode::UNEXPECTED;
			}

			auto realSize = paletteSize;
			if (tga.hdr.paletteBitPerPixel == 15 || tga.hdr.paletteBitPerPixel == 16)
				realSize = paletteSize * 2;

			buf = new(*tga.Heap) uint8_t[(size_t)realSize];
			if (!buf)
			{
				return ResultCode::OUT_OF_MEMORY;
			}

			auto readBuffer = buf + realSize - paletteSize;
			result = tga.stream->Read(readBuffer, (size_t)paletteSize);
			if (!result)
				return result;

			//if (TGA_CAN_SWAP(tga.hdr.paletteBitPerPixel))
			//{
			//	bgr2rgb(*buf, TGA_PALETTE_SIZE(tga), tga.hdr.paletteBitPerPixel / 8);
			//}

			//Color map data.                                           |
			//	|        |        |                                                            |
			//	|        |        |  The offset is determined by the size of the Image         |
			//	|        |        |  Identification Field.The length is determined by        |
			//	|        |        |  the Color Map Specification, which describes the          |
			//	|        |        |  size of each entry and the number of entries.             |
			//	|        |        |  Each color map entry is 2, 3, or 4 bytes.                 |
			//	|        |        |  Unused bits are assumed to specify attribute bits.        |
			//	|        |        |  The 4 byte entry contains 1 byte for blue, 1 byte         |
			//	|        |        |  for green, 1 byte for red, and 1 byte of attribute        |
			//	|        |        |  information, in that order.                               |
			//	|        |        |  The 3 byte entry contains 1 byte each of blue, green, |
			//	|        |        |  and red.                                                  |
			//	|        |        |  The 2 byte entry is broken down as follows : |
			//	|        |        |  ARRRRRGG GGGBBBBB, where each letter represents a bit.    |
			//	|        |        |  But, because of the lo - hi storage order, the first byte   |
			//	|        |        |  coming from the file will actually be GGGBBBBB, and the   |
			//	|        |        |  second will be ARRRRRGG. "A" represents an attribute bit. |

			if (tga.hdr.paletteBitPerPixel == 15 || tga.hdr.paletteBitPerPixel == 16)
			{
				int writePos = 0; // Point the last pixels first element
				for (int readPos = 0; readPos < paletteSize; readPos += 2, writePos += 4)
				{
					TGA16ToRGBA((uint16_t)readBuffer[readPos + 0] + (uint16_t)readBuffer[readPos + 1] * 255, buf + writePos);
				}
			}

			return ResultCode::SUCCESS;
		}

		Result TGAReadRLE(ContextInfo &tga, uint8_t *buf, size_t szBufferSize)
		{
			int head;
			char sample[4];
			uint8_t k, repeat = 0, direct = 0, bytes = tga.hdr.bitPerPixel / 8;
			int16_t x;
			int16_t width = tga.hdr.width;
			Result result;

			if (!buf) return ResultCode::UNEXPECTED;

			for (x = 0; x < width && szBufferSize > 0; ++x)
			{
				if (repeat == 0 && direct == 0)
				{
					uint8_t readByte;
					result = tga.stream->Read(readByte);
					if (!result) return result;

					head = readByte;
					if (head >= 128)
					{
						repeat = head - 127;
						result = tga.stream->Read(sample, bytes);
						if (!result) return result;
					}
					else
					{
						direct = head + 1;
					}
				}
				if (repeat > 0)
				{
					for (k = 0; k < bytes; ++k) buf[k] = sample[k];
					--repeat;
				}
				else
				{
					//if (fread(buf, bytes, 1, fd) < 1) return ResultCode::FAIL;
					result = tga.stream->Read(buf, bytes);
					if (!result) return result;
					--direct;
				}
				buf += bytes;
				szBufferSize -= bytes;
			}

			return ResultCode::SUCCESS;
		}

		Result TGAReadScanline(ContextInfo &tga, uint8_t  *buf, size_t  sln_size)
		{
			Result result;

			if (!buf)
				return ResultCode::INVALID_ARG;

			if (TGA_IS_COMPRESSED(tga))
			{
				result = TGAReadRLE(tga, buf, sln_size);
			}
			else
			{
				result = tga.stream->Read(buf, sln_size);
			}

			return result;
		}

		void TGASwapBGRA2RGBA(uint8_t  *dest, size_t  destSize, const uint8_t  *src, size_t  srcSize)
		{
			auto copySize = Util::Min(destSize, srcSize);
			for (unsigned curPos = 0; curPos < copySize; curPos+=4)
			{
				auto b = src[curPos + 0];
				auto g = src[curPos + 1];
				auto r = src[curPos + 2];
				auto a = src[curPos + 3];

				dest[curPos + 0] = r;
				dest[curPos + 1] = g;
				dest[curPos + 2] = b;
				dest[curPos + 3] = a;
			}
			
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Converting functions
		//


		void Func_TGA_Convert_RGBA32Palette4(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			const int BytePerPixel = 4;
			const int PaletteBytePerPixel = 4;
			if (palette == nullptr)
			{
				Assert(false);
				return;
			}

			for (uint iSrc = 0, iDest = 0; iSrc < srcSize; iSrc++)
			{
				uint8_t srcByte = srcRowData[iSrc];
				for (uint iBit = 0; iBit < 2 && iDest < destSize; iBit++, iDest += BytePerPixel, srcByte >>= 4)
				{
					auto pPalettePos = &palette[(srcByte&0xF) * PaletteBytePerPixel];

					destRowData[iDest + 0] = pPalettePos[0];
					destRowData[iDest + 1] = pPalettePos[1];
					destRowData[iDest + 2] = pPalettePos[2];
					destRowData[iDest + 3] = pPalettePos[3];
				}
			}
		}


		void Func_TGA_Convert_RGBA32Palette8(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			const int SrcBytePerPixel = 1;
			const int BytePerPixel = 4;
			const int PaletteBytePerPixel = 4;
			if (palette == nullptr)
			{
				Assert(false);
				return;
			}

			for (uint iSrc = 0, iDest = 0; iSrc < srcSize && iDest < destSize; iSrc += SrcBytePerPixel, iDest+= BytePerPixel)
			{
				uint8_t srcByte = srcRowData[iSrc];
				auto pPalettePos = &palette[srcByte * PaletteBytePerPixel];

				destRowData[iDest + 0] = pPalettePos[0];
				destRowData[iDest + 1] = pPalettePos[1];
				destRowData[iDest + 2] = pPalettePos[2];
				destRowData[iDest + 3] = pPalettePos[3];
			}
		}


		void Func_TGA_Convert_RGBA16(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			const int SrcBytePerPixel = 2;
			const int BytePerPixel = 4;
			unused(palette);

			for (uint iSrc = 0, iDest = 0; iSrc < srcSize && iDest < destSize; iSrc += SrcBytePerPixel, iDest += BytePerPixel)
			{
				uint16_t srcColor = *(uint16_t*)(srcRowData + iSrc);

				TGA16ToRGBA(srcColor, destRowData + iDest);
			}
		}


		void Func_TGA_Convert_RGB24(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			const int SrcBytePerPixel = 3;
			const int BytePerPixel = 3;
			unused(palette);

			for (uint iSrc = 0, iDest = 0; iSrc < destSize; iSrc += SrcBytePerPixel, iDest += BytePerPixel)
			{
				uint8_t R = srcRowData[iSrc + 2];
				uint8_t G = srcRowData[iSrc + 1];
				uint8_t B = srcRowData[iSrc + 0];


				destRowData[iDest + 0] = R;
				destRowData[iDest + 1] = G;
				destRowData[iDest + 2] = B;
			}
		}


		void Func_TGA_Convert_RGBA32(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			const int SrcBytePerPixel = 4;
			const int BytePerPixel = 4;
			unused(palette);

			for (uint iSrc = 0, iDest = 0; iSrc < destSize; iSrc += SrcBytePerPixel, iDest += BytePerPixel)
			{
				uint8_t R = srcRowData[iSrc + 2];
				uint8_t G = srcRowData[iSrc + 1];
				uint8_t B = srcRowData[iSrc + 0];
				uint8_t A = srcRowData[iSrc + 3];


				destRowData[iDest + 0] = R;
				destRowData[iDest + 1] = G;
				destRowData[iDest + 2] = B;
				destRowData[iDest + 3] = A;
			}
		}


		void Func_TGA_Convert_Gray(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			const int SrcBytePerPixel = 1;
			const int BytePerPixel = 3;

			unused(palette);
			for (uint iSrc = 0, iDest = 0; iSrc < srcSize; iSrc += SrcBytePerPixel, iDest += BytePerPixel)
			{
				uint8_t srcByte = srcRowData[iSrc];
				destRowData[iDest + 0] = srcByte;
				destRowData[iDest + 1] = srcByte;
				destRowData[iDest + 2] = srcByte;
			}
		}


		void Func_TGA_Convert_GrayAlpha(const uint8_t* palette, uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			const int SrcBytePerPixel = 2;
			const int BytePerPixel = 4;
			unused(palette);
			for (uint iSrc = 0, iDest = 0; iSrc < srcSize; iSrc += SrcBytePerPixel, iDest += BytePerPixel)
			{
				uint8_t srcByte = srcRowData[iSrc + 0];
				destRowData[iDest + 0] = srcByte;
				destRowData[iDest + 1] = srcByte;
				destRowData[iDest + 2] = srcByte;
				destRowData[iDest + 4] = srcRowData[iSrc + 1];
			}
		}

	}




	AssetImporterTextureTGA::AssetImporterTextureTGA(IHeap& heap)
		: AssetImporterTexture(heap, "AssetImporterTextureTGA")
	{
		AddAssetType("tga");
	}

	AssetImporterTextureTGA::~AssetImporterTextureTGA()
	{

	}

	// It returns resource and clear pointer inside
	Result AssetImporterTextureTGA::Import(AssetImportContext& context, Array<ResourcePtr>& resources)
	{
		uint8_t	*palette = nullptr;
		ImplTGA::ContextInfo tga;// , TGAData *data
		tga.Heap = &GetHeap();
		tga.stream = &context.GetStream();
		tga.StartPos = tga.stream->GetPosition();

		Result result = TGAReadHeader(tga);
		if (!result)
			return result;

		// Skip image ID section
		if (tga.hdr.id_len != 0)
		{
			tga.stream->Skip(tga.hdr.id_len);
		}

		// Palette?
		if (TGA_IS_MAPPED(tga))
		{
			result = TGAReadPalette(tga, palette);
			if (!result)
				return result;
		}

		// prepare texture resource
		auto pTGAFormatDesc = ImplTGA::GetTGAFormatDescriptor(tga.hdr.imageType, tga.hdr.bitPerPixel);
		if (pTGAFormatDesc == nullptr)
		{
			IHeap::Delete(palette);
			return ResultCode::NOT_SUPPORTED_FORMAT;
		}

		auto newRes = new(context.GetHeap()) Texture(context.GetHeap(), (const char*)context.GetSource());
		if (newRes == nullptr)
		{
			IHeap::Delete(palette);
			return ResultCode::OUT_OF_MEMORY;
		}


		newRes->SetSourceName((const char*)context.GetSource());
		TextureInitParameter texInit;
		memset(&texInit, 0, sizeof(texInit));
		texInit.Format = pTGAFormatDesc->ConvertTo;
		texInit.Width = tga.hdr.width;
		texInit.Height = tga.hdr.height;
		texInit.FaceCount = 1;
		texInit.UseMipmap = true;
		texInit.Usage = TextureUsage::Transient;

		newRes->Init(texInit);

		resources.push_back(newRes);


		// move to image data start
		size_t rowByteSize = TGA_SCANLINE_SIZE(tga);
		auto imageDataOffset = TGA_IMG_DATA_OFFSET(tga);
		if (imageDataOffset < tga.GetCurrentOffset())
		{
			IHeap::Delete(palette);
			Assert(false);
			return ResultCode::UNEXPECTED;
		}

		if (imageDataOffset != tga.GetCurrentOffset())
			tga.stream->Skip((size_t)(imageDataOffset - tga.GetCurrentOffset()));

		// TOTO: support origin
		//tga.hdr.horz = (tmp[17] & 0x10) ? TGA_TOP : TGA_BOTTOM;
		//tga.hdr.vert = (tmp[17] & 0x20) ? TGA_RIGHT : TGA_LEFT;


		auto lockedImage = newRes->LockImageData();
		auto pImage = (uint8_t*)lockedImage;
		auto bpp = newRes->GetBytePerPixel();
		auto widthAlign = newRes->GetWidthAlign();
		auto widthSize = tga.hdr.width * bpp;
		widthSize = AlignUp(widthSize, widthAlign);

		uint8_t* pReadBuffer = nullptr;
		if (rowByteSize > widthSize)
		{
			IHeap::Delete(palette);
			Assert(false);
			newRes->UnlockImageData();
			return ResultCode::UNEXPECTED;
		}

		for (int y = 0; y < tga.hdr.height; y++)
		{
			pReadBuffer = pImage + widthSize - rowByteSize;
			ImplTGA::TGAReadScanline(tga, pReadBuffer, rowByteSize);
			//ImplTGA::TGASwapBGRA2RGBA(pImage, widthSize, pReadBuffer, rowByteSize);
			pTGAFormatDesc->RowCopyFunction(palette, const_cast<uint8_t*>(pImage), widthSize, pReadBuffer, rowByteSize);
			pImage += widthSize; // TODO: this should be same. add check
		}


		IHeap::Delete(palette);

		return ResultCode::SUCCESS;
	}


}


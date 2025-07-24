////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Jpeg image asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Asset/Importer/SFAssetImporterTextureJPG.h"
#include "Resource/SFTexture.h"
#include "Stream/SFMemoryStream.h"

#include "jpeglib.h"
#include <setjmp.h>
//#include <turbojpeg.h> // TODO:


namespace SF
{

	namespace ImplJPG
	{
		// Func JPG convert
		typedef void(*T_Func_JPG_Convert)(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);

		// JPGColorTypeDesc
		struct JPGColorTypeDesc
		{
			int NumComponents;
			TextureFormat	ConvertTo;
			T_Func_JPG_Convert RowCopyFunction;
		};

		// converts forward declaration
		void Func_JPG_Convert_Gray(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_JPG_Convert_GrayAlpha(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);

		void Func_JPG_Convert_RGB(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);
		void Func_JPG_Convert_RGBA(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize);


		// Color Type Desc
		const JPGColorTypeDesc g_ColorTypeDesc[] =
		{
			{ 1,	TextureFormat::R8_UNORM,			Func_JPG_Convert_Gray },
			{ 2,	TextureFormat::R8G8B8_UNORM,		Func_JPG_Convert_GrayAlpha },
			{ 3,	TextureFormat::R8G8B8A8_UNORM,		Func_JPG_Convert_RGB },
			{ 4,	TextureFormat::R8G8B8A8_UNORM,		Func_JPG_Convert_RGBA },
		};


		const JPGColorTypeDesc* GetJPGFormatDescriptor(int numComponents)
		{
			for (uint iColorDesc = 0; iColorDesc < countof(ImplJPG::g_ColorTypeDesc); iColorDesc++)
			{
				auto& colorDesc = ImplJPG::g_ColorTypeDesc[iColorDesc];
				if (colorDesc.NumComponents == numComponents)
				{
					return &colorDesc;
				}
			}

			// failed to find format descriptor
			Assert(false);

			return nullptr;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		////
		////	JPG read interface
		////


		struct JPG_Error {
			struct jpeg_error_mgr pub;	/* "public" fields */

			jmp_buf setjmp_buffer;	/* for return to caller */
		};

		METHODDEF(void) Func_JPG_error_exit(j_common_ptr cinfo)
		{
			/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
			JPG_Error* myerr = (JPG_Error*)cinfo->err;

			/* Always display the message. */
			/* We could postpone this until after returning, if we chose. */
			(*cinfo->err->output_message) (cinfo);

			/* Return control to the setjmp point */
			longjmp(myerr->setjmp_buffer, 1);
		}




		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Converting functions
		//

		void Func_JPG_Convert_Gray(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			auto copySize = Math::Min(destSize, srcSize);
			memcpy(destRowData, srcRowData, copySize);
		}

		void Func_JPG_Convert_GrayAlpha(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			for (uint iSrc = 0, iDest = 0; iSrc < srcSize; iSrc += 2, iDest++)
			{
				uint8_t srcByte = srcRowData[iSrc];
				destRowData[iDest + 0] = srcByte;
				destRowData[iDest + 1] = srcByte;
				destRowData[iDest + 2] = srcByte;
				destRowData[iDest + 4] = srcRowData[iSrc + 1];
			}
		}

		void Func_JPG_Convert_RGB(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			auto copySize = Math::Min(destSize, srcSize);
			memcpy(destRowData, srcRowData, copySize);
		}

		void Func_JPG_Convert_RGBA(uint8_t* destRowData, size_t destSize, const uint8_t* srcRowData, size_t srcSize)
		{
			auto copySize = Math::Min(destSize, srcSize);
			memcpy(destRowData, srcRowData, copySize);
		}


	}




	AssetImporterTextureJPG::AssetImporterTextureJPG(IHeap& heap)
		: AssetImporterTexture(heap, "AssetImporterTextureJPG")
	{
		AddAssetType("jpg");
		AddAssetType("jpeg");
	}

	AssetImporterTextureJPG::~AssetImporterTextureJPG()
	{

	}



	// It returns resource and clear pointer inside
	Result AssetImporterTextureJPG::Import(AssetImportContext& context, Array<ResourcePtr>& resources)
	{
		jpeg_decompress_struct cinfo;
		jpeg_error_mgr jerr;
		ImplJPG::JPG_Error myErrStruct;


		/* We set up the normal JPEG error routines, then override error_exit. */
		cinfo.err = jpeg_std_error(&myErrStruct.pub);
		jerr.error_exit = ImplJPG::Func_JPG_error_exit;
		/* Establish the setjmp return context for my_error_exit to use. */
		if (setjmp(myErrStruct.setjmp_buffer)) {
			/* If we get here, the JPEG code has signaled an error.
			* We need to clean up the JPEG object, close the input file, and return.
			*/
			jpeg_destroy_decompress(&cinfo);
			//fclose(infile);
			return ResultCode::FAIL;
		}


		jpeg_create_decompress(&cinfo);

		auto memorySize = context.GetStream().GetSize() - context.GetStream().GetPosition();
		auto pMemStream = dynamic_cast<InputMemoryStream*>(&context.GetStream());
		uint8_t *pBuffer = nullptr;
		if (pMemStream != nullptr)
		{
			pBuffer = (uint8_t*)pMemStream->GetBufferPtr() + pMemStream->GetPosition();
			jpeg_mem_src(&cinfo, pBuffer, (unsigned long)memorySize);
		}
		else
		{
			pBuffer = new(GetHeap()) uint8_t[memorySize];
			if (pBuffer == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			context.GetStream().Read(pBuffer, memorySize);

			jpeg_mem_src(&cinfo, pBuffer, (unsigned long)memorySize);
		}


		jpeg_read_header(&cinfo, TRUE);

		jpeg_start_decompress(&cinfo);

		auto row_stride = cinfo.output_width * cinfo.output_components;

		auto formatDesc = ImplJPG::GetJPGFormatDescriptor(cinfo.output_components);
		if (formatDesc == nullptr)
			return ResultCode::NOT_SUPPORTED_FORMAT;

		auto newRes = new Texture((const char*)context.GetSource());
		if (newRes == nullptr)
		{
			jpeg_destroy_decompress(&cinfo);
			return ResultCode::OUT_OF_MEMORY;
		}


		newRes->SetSourceName((const char*)context.GetSource());
		TextureInitParameter texInit;
		memset(&texInit, 0, sizeof(texInit));
		texInit.Format = formatDesc->ConvertTo;
		texInit.Width = cinfo.output_width;
		texInit.Height = cinfo.output_height;
		texInit.FaceCount = 1;
		texInit.UseMipmap = 1;
		texInit.Usage = TextureUsage::Transient;
		newRes->Init(texInit);

		resources.push_back(newRes);


		auto lockedImage = newRes->LockImageData();
		auto pImage = (uint8_t*)lockedImage;
		auto bpp = newRes->GetBytePerPixel();
		auto widthAlign = newRes->GetWidthAlign();
		auto widthSize = newRes->GetWidth() * bpp;
		widthSize = AlignUp(widthSize, widthAlign);

		AssertRel(widthSize >= row_stride);

		/* Make a one-row-high sample array that will go away when done with image */
		//auto readBuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

		/* Step 6: while (scan lines remain to be read) */
		/*           jpeg_read_scanlines(...); */

		/* Here we use the library's state variable cinfo.output_scanline as the
		* loop counter, so that we don't have to keep track ourselves.
		*/
		for (uint y = 0; y < cinfo.output_height; y++)
		{
			Assert(y == cinfo.output_scanline);

			/* jpeg_read_scanlines expects an array of pointers to scanlines.
			* Here the array is only one element long, but you could ask for
			* more than one scanline at a time if that's more convenient.
			*/
			(void)jpeg_read_scanlines(&cinfo, &pImage, 1);

			pImage += widthSize; // TODO: this should be same. add check
		}


		/* Step 7: Finish decompression */

		(void)jpeg_finish_decompress(&cinfo);
		/* We can ignore the return value since suspension is not possible
		* with the stdio data source.
		*/

		/* Step 8: Release JPEG decompression object */

		/* This is an important step since it will release a good deal of memory. */
		jpeg_destroy_decompress(&cinfo);

		/* After finish_decompress, we can close the input file.
		* Here we postpone it until after no more JPEG errors are possible,
		* so as to simplify the setjmp error logic above.  (Actually, I don't
		* think that jpeg_destroy can do an error exit, but why assume anything...)
		*/
		if (pMemStream == nullptr)
			delete (pBuffer);


		//delete (readBuffer);

		/* At this point you may want to check to see whether any corrupt-data
		* warnings occurred (test whether jerr.pub.num_warnings is nonzero).
		*/

		/* And we're done! */
		return ResultCode::SUCCESS;
	}


}


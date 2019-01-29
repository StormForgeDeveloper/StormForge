////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Package serializer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Asset/Serializer/SFAssetSerializerTexture.h"
#include "Service/SFEngineService.h"
#include "Stream/SFStream.h"
#include "Resource/SFTexture.h"


namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetSerializerTexture
	//


	AssetSerializerTexture::AssetSerializerTexture(IHeap& heap)
		: AssetSerializer(heap, "Texture")
	{
		AddHandlingAssetType("Texture");
	}


	AssetSerializerTexture::~AssetSerializerTexture()
	{

	}



	// Serialize stream
	Result AssetSerializerTexture::Serialize(IOutputStream& stream, ResourcePtr& res)
	{
		TexturePtr resource = res.DynamicCast<Texture>();
		if (resource == nullptr)
			return ResultCode::INVALID_ARG;

		auto lockedImage = resource->LockImageData();
		auto pData = (uint8_t*)lockedImage;
		if (pData == nullptr)
			return ResultCode::INVALID_POINTER;

		TextureHeader header;
		memset(&header, 0, sizeof(header));
		header.Format = resource->GetFormat();
		header.Width = resource->GetWidth();
		header.Height = resource->GetHeight();
		header.Depth = resource->GetDepth();
		header.FaceCount = resource->GetFaceCount();
		header.MipmapCount = resource->GetMipmapCount();

		Result result = stream.Write(header);
		if (!result)
			return result;

		size_t imageSize = resource->CalculateImageDataSize();

		result = stream.Write(pData, imageSize);
		if (!result)
			return result;


		// TODO
		return ResultCode::SUCCESS;
	}


	// Desterialize stream
	Result AssetSerializerTexture::Deserialize(IHeap& heap, IInputStream& stream, ResourcePtr& res)
	{
		TexturePtr resource = new(heap) Texture(heap);

		TextureHeader header;
		Result result = stream.Read(header);
		if (!result)
			return result;

		TextureInitParameter texInit;
		memset(&texInit, 0, sizeof(texInit));
		texInit.Format = header.Format;
		texInit.Width = header.Width;
		texInit.Height = header.Height;
		texInit.FaceCount = header.FaceCount;
		texInit.UseMipmap = header.MipmapCount > 0;
		texInit.Usage = TextureUsage::Transient;
		result = resource->Init(texInit);
		if (!result)
			return result;

		auto lockedImage = resource->LockImageData();
		auto pData = (uint8_t*)lockedImage;
		if (pData == nullptr)
			return ResultCode::OUT_OF_MEMORY;

		size_t imageSize = resource->CalculateImageDataSize();

		result = stream.Read((void*)pData, imageSize);
		if (!result)
			return result;

		res = resource;

		// TODO
		return ResultCode::SUCCESS;
	}


}


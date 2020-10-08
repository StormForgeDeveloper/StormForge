////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Package serializer
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Container/SFArray.h"
#include "Asset/Serializer/SFAssetSerializer.h"
#include "Resource/SFTextureFormatDescription.h"


namespace SF
{
	class Texture;

	////////////////////////////////////////////////////////////////////
	//
	//	AssetPackageSerializer
	//
	class AssetSerializerTexture : public AssetSerializer
	{
	public:


#pragma pack(push,4)


		// Package header
		struct TextureHeader
		{
			uint32_t		Width;		// Offset to package dependency
			uint32_t		Height;		// Offset to the first object 
			uint32_t		Depth;		// Number of dependency
			uint32_t		FaceCount;	// Number of objects
			uint32_t		MipmapCount;					// 
			TextureFormat	Format;
		};

#pragma pack(pop)

	private:


	public:
		AssetSerializerTexture(IHeap& heap);
		virtual ~AssetSerializerTexture();


		// Serialize stream
		virtual Result Serialize(IOutputStream& stream, ResourcePtr& res) override;

		// Desterialize stream
		virtual Result Deserialize(IHeap& heap, IInputStream& stream, ResourcePtr& res) override;
	};


}


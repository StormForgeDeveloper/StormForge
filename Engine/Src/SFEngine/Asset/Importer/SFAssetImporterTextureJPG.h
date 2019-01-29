////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Jpeg image asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Asset/Importer/SFAssetImporterTexture.h"
#include "Resource/SFDeviceTexture.h"


namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporter
	//
	class AssetImporterTextureJPG : public AssetImporterTexture
	{
	private:


	private:


	public:
		AssetImporterTextureJPG(IHeap& heap);
		virtual ~AssetImporterTextureJPG();


		// It returns resource and clear pointer inside
		virtual Result Import(AssetImportContext& context, Array<ResourcePtr>& resources);
	};


}


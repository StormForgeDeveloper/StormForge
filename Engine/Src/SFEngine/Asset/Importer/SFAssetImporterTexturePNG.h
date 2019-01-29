////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : PNG image asset Importer
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
	class AssetImporterTexturePNG : public AssetImporterTexture
	{
	private:


	private:


	public:
		AssetImporterTexturePNG(IHeap& heap);
		virtual ~AssetImporterTexturePNG();


		// It returns resource and clear pointer inside
		virtual Result Import(AssetImportContext& context, Array<ResourcePtr>& resources);
	};


}


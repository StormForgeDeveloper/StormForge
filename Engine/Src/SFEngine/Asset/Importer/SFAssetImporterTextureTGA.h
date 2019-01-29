////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TGA image asset Importer
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
	class AssetImporterTextureTGA : public AssetImporterTexture
	{
	private:


	private:


	public:
		AssetImporterTextureTGA(IHeap& heap);
		virtual ~AssetImporterTextureTGA();


		// It returns resource and clear pointer inside
		virtual Result Import(AssetImportContext& context, Array<ResourcePtr>& resources);
	};


}


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Importer texture
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Asset/Importer/SFAssetImporter.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporterTexture
	//
	class AssetImporterTexture : public AssetImporter
	{
	private:

	protected:


	public:
		AssetImporterTexture(IHeap& heap, const StringCrc64& name);
		virtual ~AssetImporterTexture();

	};


}


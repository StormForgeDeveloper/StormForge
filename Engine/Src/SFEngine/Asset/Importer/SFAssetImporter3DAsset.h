////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Importer 3DAsset
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Asset/Importer/SFAssetImporter.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporter3DAsset
	//
	class AssetImporter3DAsset : public AssetImporter
	{
	private:

	protected:


	public:
		AssetImporter3DAsset(IHeap& heap, const FixedString& name);
		virtual ~AssetImporter3DAsset();

		
	};


}


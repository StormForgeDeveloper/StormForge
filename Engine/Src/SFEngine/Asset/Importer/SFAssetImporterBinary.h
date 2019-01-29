////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Importer binary
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Asset/Importer/SFAssetImporter.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporterBinary
	//
	class AssetImporterBinary : public AssetImporter
	{
	private:


	public:
		AssetImporterBinary(IHeap& heap);
		virtual ~AssetImporterBinary();


		// Import
		// @resources: imported resources will be added
		virtual Result Import(AssetImportContext& context, Array<ResourcePtr>& resources) override;

	};



}


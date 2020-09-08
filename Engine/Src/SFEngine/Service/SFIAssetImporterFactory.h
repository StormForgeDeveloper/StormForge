////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Importer Factory
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "Container/SFSortedArray.h"



namespace SF
{
	
	class AssetImporter;

	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporterFactory
	//

	class IAssetImporterFactory
	{
	public:
		// Constructor
		IAssetImporterFactory() {}
		virtual ~IAssetImporterFactory() {}

		// Get heap for importers
		virtual IHeap& GetHeap() { return GetEngineHeap(); }

		// Register importer
		// Importer will be deleted inside. don't pass static instance
		virtual Result RegisterImporter(AssetImporter* pNewImporter) { unused(pNewImporter); return ResultCode::NOT_IMPLEMENTED; }

		// 
		template<class AssetImporterType>
		Result RegisterImporter()
		{
			AssetImporterType *pImporter = new(GetHeap()) AssetImporterType(GetHeap());
			return RegisterImporter(pImporter);
		}


		// Find importer with type
		virtual Result FindImporter(StringCrc64 type, AssetImporter* &pImporter) { unused(type), unused(pImporter); return ResultCode::NOT_IMPLEMENTED; }

	};



}


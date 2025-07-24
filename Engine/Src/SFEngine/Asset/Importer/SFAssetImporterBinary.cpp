////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Asset Importer binary
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Asset/Importer//SFAssetImporterBinary.h"
#include "Resource/SFRawBinary.h"



namespace SF
{



	AssetImporterBinary::AssetImporterBinary(IHeap& heap)
		: AssetImporter(heap, "AssetImporterBinary")
	{
		AddAssetType("bin");
	}

	AssetImporterBinary::~AssetImporterBinary()
	{

	}


	Result AssetImporterBinary::Import(AssetImportContext& context, Array<ResourcePtr>& resources)
	{
		SharedPointerT<RawBinary> pNewAsset = new RawBinary;
		if (pNewAsset == nullptr)
			return ResultCode::OUT_OF_MEMORY;

		pNewAsset->SetName(context.GetStream().GetName());

		uint32_t dataSize = 0;

		auto result = context.GetStream().Read(dataSize);
		if (!result)
			return result;

		result = context.GetStream().Read(dataSize);
		if (!result)
			return result;

		resources.push_back(std::forward<ResourcePtr>(pNewAsset.StaticCast<Resource>()));

		return ResultCode::SUCCESS;
	}

}


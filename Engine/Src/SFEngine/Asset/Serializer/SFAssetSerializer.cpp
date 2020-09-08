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
#include "Asset/Serializer/SFAssetSerializer.h"
#include "Asset/Package/SFAssetPackage.h"
#include "Asset/Importer/SFAssetImporter.h"
#include "Service/SFEngineService.h"
#include "Stream/SFMemoryStream.h"
#include "Stream/SFCompressedStream.h"


namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetSerializer
	//


	AssetSerializer::AssetSerializer(IHeap& heap, const StringCrc64& name)
		: m_Name(name)
		, m_Heap(heap)
		, m_AssetTypes(m_Heap)
	{
	}

	AssetSerializer::~AssetSerializer()
	{
	}

	Result AssetSerializer::AddHandlingAssetType(StringCrc64 assetType)
	{
		return m_AssetTypes.push_back(assetType);
	}

	// Serialize stream
	Result AssetSerializer::Serialize(IOutputStream& stream, ResourcePtr& res)
	{
		auto sourceName = res->GetSourceName();
		Result result = stream.Write(sourceName);
		if (!result)
			return result;

		return ResultCode::SUCCESS;
	}


	// Desterialize stream
	Result AssetSerializer::Deserialize(IHeap& heap, IInputStream& stream, ResourcePtr& res)
	{
		StringCrc64 sourceName;
		Result result = stream.Read(sourceName);
		if (!result)
			return result;

		res->SetSourceName(sourceName);

		return ResultCode::SUCCESS;
	}




}


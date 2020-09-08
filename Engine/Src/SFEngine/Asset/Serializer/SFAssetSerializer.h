////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset serializer
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Container/SFArray.h"
#include "Asset/Package/SFAssetPackageSerializer.h"


namespace SF
{
	

	////////////////////////////////////////////////////////////////////
	//
	//	AssetSerializer
	//
	class AssetSerializer
	{
	public:

		static constexpr StringCrc64 HEADER_MAGIC = "sfpkg";
		static constexpr uint32_t HEADER_VERSION = 1;


		typedef AssetPackageSerializer::ObjectHeader ObjectHeader;


	private:

		// Name of importer
		StringCrc64 m_Name;

		// heap for importer
		IHeap& m_Heap;

		// Supporting asset types
		StaticArray<StringCrc64, 2> m_AssetTypes;



	protected:

		// Add handling asset type
		Result AddHandlingAssetType(StringCrc64 assetType);

	public:
		AssetSerializer(IHeap& heap, const StringCrc64& name);
		virtual ~AssetSerializer();

		// Heap
		IHeap& GetHeap() { return m_Heap; }

		// Asset type list
		virtual const Array<StringCrc64>& GetAssetTypes() const { return m_AssetTypes; }


		// Serialize stream
		virtual Result Serialize(IOutputStream& stream, ResourcePtr& res);

		// Desterialize stream
		virtual Result Deserialize(IHeap& heap, IInputStream& stream, ResourcePtr& res);
	};


}


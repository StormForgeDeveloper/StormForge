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

		static constexpr FixedString HEADER_MAGIC = "sfpkg";
		static constexpr uint32_t HEADER_VERSION = 1;


		typedef AssetPackageSerializer::ObjectHeader ObjectHeader;


	private:

		// Name of importer
		FixedString m_Name;

		// heap for importer
		IHeap& m_Heap;

		// Supporting asset types
		StaticArray<FixedString, 2> m_AssetTypes;



	protected:

		// Add handling asset type
		Result AddHandlingAssetType(FixedString assetType);

	public:
		AssetSerializer(IHeap& heap, const FixedString& name);
		virtual ~AssetSerializer();

		// Heap
		IHeap& GetHeap() { return m_Heap; }

		// Asset type list
		virtual const Array<FixedString>& GetAssetTypes() const { return m_AssetTypes; }


		// Serialize stream
		virtual Result Serialize(IOutputStream& stream, ResourcePtr& res);

		// Desterialize stream
		virtual Result Deserialize(IHeap& heap, IInputStream& stream, ResourcePtr& res);
	};


}


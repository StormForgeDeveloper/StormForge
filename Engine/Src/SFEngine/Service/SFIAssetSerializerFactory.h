////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Serializer Factory
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "Container/SFSortedArray.h"



namespace SF
{
	
	class AssetSerializer;

	////////////////////////////////////////////////////////////////////
	//
	//	AssetSerializerFactory
	//

	class IAssetSerializerFactory
	{
	public:
		// Constructor
		IAssetSerializerFactory() {}
		virtual ~IAssetSerializerFactory() {}

		// Get heap for importers
		virtual IHeap& GetHeap() { return GetEngineHeap(); }

		// 
		template<class AssetSerializerType>
		Result RegisterSerializer()
		{
			AssetSerializerType *pSerializer = new(GetHeap()) AssetSerializerType(GetHeap());
			return RegisterSerializer(pSerializer);
		}

		// Register importer
		// Serializer will be deleted inside. don't pass static instance
		virtual Result RegisterSerializer(AssetSerializer* pSerializer) { unused(pSerializer); return ResultCode::NOT_IMPLEMENTED; }

		// Find importer with type
		virtual Result FindSerializer(StringCrc64 type, AssetSerializer* &pSerializer) { unused(type), unused(pSerializer); return ResultCode::NOT_IMPLEMENTED; }

	};



}


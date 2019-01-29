////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Package serializer
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Container/SFArray.h"


namespace SF
{
	

	////////////////////////////////////////////////////////////////////
	//
	//	AssetPackageSerializer
	//
	class AssetPackageSerializer
	{
	public:

		static constexpr FixedString HEADER_MAGIC = "sfpkg";
		static constexpr uint32_t HEADER_VERSION = 1;

#pragma pack(push,1)

		// Package Header
		// Dpenddencies(FixedString list)
		// ObjectHeader + object data. One object can be string DB 

		// Package header
		struct PackageHeader
		{
			FixedString		Magic;
			uint16_t		Version;
			uint16_t		OffsetToDependency;		// Offset to package dependency
			uint16_t		OffsetToData;			// Offset to the first object 
			uint16_t		NumberOfDependency;		// Number of dependency
			uint32_t		NumberOfObject;			// Number of objects
			uint32_t		Dummy;					// 
		};

		// Object header
		struct ObjectHeader
		{
			FixedString		ObjectType;				// Object type
			FixedString		ObjectName;				// Object name
			uint16_t		Version;				// Version
			uint16_t		Encoding;				// Compression method
			uint32_t		DataSize;				// Data size
			uint32_t		UncompressedDataSize;	// Uncompressed Data size
			uint32_t		Dummy;
		};



#pragma pack(pop)

	private:

		// heap for importer
		IHeap& m_Heap;


	public:
		AssetPackageSerializer(IHeap& heap);
		virtual ~AssetPackageSerializer();

		// Heap
		IHeap& GetHeap() { return m_Heap; }


		// Serialize stream
		virtual Result Serialize(IOutputStream& stream, AssetPackage& package);

		// Desterialize stream
		virtual Result Deserialize(IHeap& heap, IInputStream& stream, AssetPackage& package);
	};


}


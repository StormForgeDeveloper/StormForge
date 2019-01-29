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

#include "Memory/SFMemory.h"
#include "Memory/SFMemoryManager.h"
#include "Container/SFSortedArray.h"
#include "Service/SFIAssetSerializerFactory.h"

namespace SF
{
	
	class AssetSerializer;


	////////////////////////////////////////////////////////////////////
	//
	//	AssetSerializerFactory
	//

	class AssetSerializerFactory : public IAssetSerializerFactory
	{
	private:

		// Heap
		Heap m_Heap;

		// Registered importers by type
		SortedArray<FixedString, AssetSerializer*> m_AssetSerializerByType;

		// registered importers
		DynamicArray<AssetSerializer*> m_AssetSerializers;

	public:
		// Constructor
		AssetSerializerFactory();
		virtual ~AssetSerializerFactory();


		// Get heap for importers
		virtual IHeap& GetHeap() override { return m_Heap; }

		// Clear factory and all registered importers
		void Clear();

		// Register importer
		// Serializer will be deleted inside. don't pass static instance
		virtual Result RegisterSerializer(AssetSerializer* pSerializer) override;

		// Find importer with type
		virtual Result FindSerializer(FixedString type, AssetSerializer* &pSerializer) override;


	};


	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager Component
	//

	class AssetSerializerFactoryComponent : public LibraryComponent
	{
	public:
		static constexpr FixedString TypeName = "AssetSerializerFactory";

		AssetSerializerFactory m_AssetSerializerFactory;

	public:

		AssetSerializerFactoryComponent();
		~AssetSerializerFactoryComponent();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


	};

}


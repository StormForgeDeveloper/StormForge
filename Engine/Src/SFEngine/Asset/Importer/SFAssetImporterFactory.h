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

#include "Memory/SFMemory.h"
#include "Memory/SFMemoryManager.h"
#include "Container/SFSortedArray.h"
#include "Service/SFIAssetImporterFactory.h"

namespace SF
{
	
	class AssetImporter;


	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporterFactory
	//

	class AssetImporterFactory : public IAssetImporterFactory
	{
	private:

		// Heap
		Heap m_Heap;

		// Registered importers by type
		SortedArray<StringCrc64, AssetImporter*> m_AssetImporterByType;

		// registered importers
		DynamicArray<AssetImporter*> m_AssetImporters;

	public:
		// Constructor
		AssetImporterFactory();
		virtual ~AssetImporterFactory();


		// Get heap for importers
		virtual IHeap& GetHeap() override { return *m_Heap.get(); }

		// Clear factory and all registered importers
		void Clear();

		// Register importer
		// Importer will be deleted inside. don't pass static instance
		virtual Result RegisterImporter(AssetImporter* pNewImporter) override;

		// Find importer with type
		virtual Result FindImporter(StringCrc64 type, AssetImporter* &pImporter) override;

	};


	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager Component
	//

	class AssetImporterFactoryComponent : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "AssetImporterFactory";

		AssetImporterFactory m_AssetImporterFactory;

	public:

		AssetImporterFactoryComponent();
		~AssetImporterFactoryComponent();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


	};

}


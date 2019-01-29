////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Importer Factory
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Asset/Importer/SFAssetImporterFactory.h"
#include "Asset/Importer/SFAssetImporter.h"
#include "Asset/Importer/SFAssetImporterTextureJPG.h"
#include "Asset/Importer/SFAssetImporterTexturePNG.h"
#include "Asset/Importer/SFAssetImporterTextureTGA.h"
#include "Asset/Importer/SFAssetImporterBinary.h"
#include "Service/SFEngineService.h"


namespace SF
{

	AssetImporterFactory::AssetImporterFactory()
		: m_Heap("AssetImporterFactory", GetEngineHeap())
		, m_AssetImporterByType(m_Heap)
		, m_AssetImporters(m_Heap)
	{
	}

	AssetImporterFactory::~AssetImporterFactory()
	{
	}


	// Clear factory and all registered importers
	void AssetImporterFactory::Clear()
	{
		m_AssetImporterByType.Clear();
		for (auto itAssetImporter : m_AssetImporters)
		{
			delete itAssetImporter;
		}
		m_AssetImporters.Clear();
	}

	// Register importer
	// Importer will be deleted inside. don't pass static instance
	Result AssetImporterFactory::RegisterImporter(AssetImporter* pNewImporter)
	{
		if (pNewImporter == nullptr)
			return ResultCode::INVALID_POINTER;

		bool Added = false;
		for (auto& itAssetType : pNewImporter->GetAssetTypes())
		{
			if (m_AssetImporterByType.Insert(itAssetType, pNewImporter))
			{
				Added = true;
			}
			else
			{

			}
				
		}

		if (!Added)
			return ResultCode::FAIL;

		m_AssetImporters.push_back(pNewImporter);

		return ResultCode::SUCCESS;
	}


	// Find importer with type
	Result AssetImporterFactory::FindImporter(FixedString type, AssetImporter* &pImporter)
	{

		auto result = m_AssetImporterByType.Find(type, pImporter);
		if (!result)
			return result;

		return ResultCode::SUCCESS;
	}





	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager Component
	//

	constexpr FixedString AssetImporterFactoryComponent::TypeName;


	AssetImporterFactoryComponent::AssetImporterFactoryComponent()
		: LibraryComponent(TypeName)
		, m_AssetImporterFactory()
	{
		Service::AssetImporterFactory = &m_AssetImporterFactory;
	}


	AssetImporterFactoryComponent::~AssetImporterFactoryComponent()
	{
		Service::AssetImporterFactory = nullptr;
		m_AssetImporterFactory.Clear();
	}


	// Initialize component
	Result AssetImporterFactoryComponent::InitializeComponent()
	{
		// Register default importers
		Service::AssetImporterFactory->RegisterImporter<AssetImporterTextureJPG>();
		Service::AssetImporterFactory->RegisterImporter<AssetImporterTexturePNG>();
		Service::AssetImporterFactory->RegisterImporter<AssetImporterTextureTGA>();
		Service::AssetImporterFactory->RegisterImporter<AssetImporterBinary>();

		return LibraryComponent::InitializeComponent();
	}


	// Terminate component
	void AssetImporterFactoryComponent::DeinitializeComponent()
	{
		m_AssetImporterFactory.Clear();
		LibraryComponent::DeinitializeComponent();
	}



}


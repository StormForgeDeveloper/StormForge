////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Serializer Factory
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Asset/Serializer/SFAssetSerializerFactory.h"
#include "Asset/Serializer/SFAssetSerializer.h"
#include "Asset/Serializer/SFAssetSerializerTexture.h"
#include "Service/SFEngineService.h"


namespace SF
{

	AssetSerializerFactory::AssetSerializerFactory()
		: m_Heap("AssetSerializerFactory", GetEngineHeap())
		, m_AssetSerializerByType(GetHeap())
		, m_AssetSerializers(GetHeap())
	{
	}

	AssetSerializerFactory::~AssetSerializerFactory()
	{
	}


	// Clear factory and all registered importers
	void AssetSerializerFactory::Clear()
	{
		m_AssetSerializerByType.Clear();
		for (auto itAssetSerializer : m_AssetSerializers)
		{
			delete (itAssetSerializer);
		}
		m_AssetSerializers.Clear();
	}

	// Register importer
	// Serializer will be deleted inside. don't pass static instance
	Result AssetSerializerFactory::RegisterSerializer(AssetSerializer* pNewSerializer)
	{
		if (pNewSerializer == nullptr)
			return ResultCode::INVALID_POINTER;

		bool Added = false;
		for (auto& itAssetType : pNewSerializer->GetAssetTypes())
		{
			if (m_AssetSerializerByType.Insert(itAssetType, pNewSerializer))
			{
				Added = true;
			}
			else
			{

			}
				
		}

		if (!Added)
			return ResultCode::FAIL;

		m_AssetSerializers.push_back(pNewSerializer);

		return ResultCode::SUCCESS;
	}


	// Find importer with type
	Result AssetSerializerFactory::FindSerializer(StringCrc64 type, AssetSerializer* &pSerializer)
	{

		auto result = m_AssetSerializerByType.Find(type, pSerializer);
		if (!result)
			return result;

		return ResultCode::SUCCESS;
	}





	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager Component
	//

	constexpr StringCrc64 AssetSerializerFactoryComponent::TypeName;


	AssetSerializerFactoryComponent::AssetSerializerFactoryComponent()
		: LibraryComponent(TypeName)
		, m_AssetSerializerFactory()
	{
		Service::AssetSerializerFactory = &m_AssetSerializerFactory;
	}


	AssetSerializerFactoryComponent::~AssetSerializerFactoryComponent()
	{
		Service::AssetSerializerFactory = nullptr;
		m_AssetSerializerFactory.Clear();
	}


	// Initialize component
	Result AssetSerializerFactoryComponent::InitializeComponent()
	{
		// Register default importers
		Service::AssetSerializerFactory->RegisterSerializer<AssetSerializerTexture>();

		return LibraryComponent::InitializeComponent();
	}


	// Terminate component
	void AssetSerializerFactoryComponent::DeinitializeComponent()
	{
		m_AssetSerializerFactory.Clear();
		LibraryComponent::DeinitializeComponent();
	}



}


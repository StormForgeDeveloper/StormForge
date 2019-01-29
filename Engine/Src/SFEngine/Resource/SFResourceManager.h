////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource base
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Object/SFSharedPointer.h"
#include "Object/SFSharedObjectManager.h"
#include "Object/SFLibraryComponent.h"
#include "Service/SFResourceManagerService.h"


namespace SF
{
	class AssetPackage;

	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager
	//
	class ResourceManager : public IResourceManagerService
	{
	private:


		// Asset loading notification task
		class AssetLoadingTaskImpl : public AssetLoadingTask
		{
		public:

			AssetLoadingTaskImpl(IHeap& heap, TaskEventHandler* pEventHandler);
			~AssetLoadingTaskImpl();

			Result LoadPackage(FixedString assetType, IInputStream& stream);
			Result LoadAsset(FixedString assetType, IInputStream& stream);

			virtual void Run() override;
		};


	private:

		// heap for resource manager
		Heap m_Heap;

		// Package manager
		AssetPackageList m_PackageByName;

		// Resource reference manager
		SharedObjectManager m_ReferenceManager;

	public:

		// Constructor
		ResourceManager();

		// Destructor
		virtual ~ResourceManager();

		IHeap& GetHeap() { return m_Heap; }

		// for internal
		virtual void RegisterLoadedPackage(AssetPackage* pPackage) override;
		virtual void RegisterLoadedResource(ResourcePtr& res) override;

		// Request loading an asset package. If the package is already exist, just reference count will be increased
		virtual SharedPointerT<AssetLoadingTask> LoadAssetPackage(const String& packagePath, TaskEventHandler* pEventHandler = nullptr) override;

		// Request loading a resource. If the resource is already exist, just reference count will be increased
		virtual SharedPointerT<AssetLoadingTask> LoadAsset(const String& assetPath, TaskEventHandler* pEventHandler = nullptr) override;
	};
	

	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager Component
	//

	class ResourceManagerComponent : public LibraryComponent
	{
	public:
		static constexpr FixedString TypeName = "ResourceManager";

		ResourceManager m_ResourceManager;

	public:

		ResourceManagerComponent();
		~ResourceManagerComponent();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


	};

}


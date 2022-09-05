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
#include "Component/SFLibraryComponent.h"
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

			AssetLoadingTaskImpl(IHeap& heap, const TaskFinishedEventDelegate& pEventHandler);
			~AssetLoadingTaskImpl();

			Result LoadPackage(StringCrc64 assetType, IInputStream& stream);
			Result LoadAsset(StringCrc64 assetType, IInputStream& stream);

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

		IHeap& GetHeap() { return *m_Heap.get(); }

		// for internal
		virtual void RegisterLoadedPackage(AssetPackage* pPackage) override;
		virtual void RegisterLoadedResource(ResourcePtr& res) override;

		// Request loading an asset package. If the package is already exist, just reference count will be increased
		virtual SharedPointerT<AssetLoadingTask> LoadAssetPackage(const String& packagePath, const TaskFinishedEventDelegate& pEventHandler) override;

		// Request loading a resource. If the resource is already exist, just reference count will be increased
		virtual SharedPointerT<AssetLoadingTask> LoadAsset(const String& assetPath, const TaskFinishedEventDelegate& pEventHandler) override;
	};
	

	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager Component
	//

	class ResourceManagerComponent : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "ResourceManager";

		ResourceManager m_ResourceManager;

	public:

		ResourceManagerComponent();
		~ResourceManagerComponent();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


	};

}


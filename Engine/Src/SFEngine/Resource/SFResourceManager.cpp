////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource base
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFResource.h"
#include "Resource/SFResourceManager.h"
#include "Service/SFEngineService.h"
#include "Util/SFPath.h"
#include "Asset/Importer/SFAssetImporter.h"
#include "Asset/Package/SFAssetPackage.h"
#include "Asset/Package/SFAssetPackageSerializer.h"
#include "IO/SFFileInputStream.h"



namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	Asset loading task 
	//


	// Asset loading notification task
	ResourceManager::AssetLoadingTask::AssetLoadingTask(IHeap& heap, const TaskFinishedEventDelegate& pEventHandler)
		: Task()
		, HeapForLoading(heap)
		, FilePath(heap)
		, AssetName(heap)
	{
		AddTaskEventHandler(pEventHandler);
	}



	////////////////////////////////////////////////////////////////////
	//
	//	Asset loading task implementation
	//


	ResourceManager::AssetLoadingTaskImpl::AssetLoadingTaskImpl(IHeap& heap, const TaskFinishedEventDelegate& pEventHandler)
		: AssetLoadingTask(heap, pEventHandler)
	{
	}

	ResourceManager::AssetLoadingTaskImpl::~AssetLoadingTaskImpl()
	{
	}

	Result ResourceManager::AssetLoadingTaskImpl::LoadPackage(StringCrc64 assetType, IInputStream& stream)
	{
		AssetPackage* pPackage = new(HeapForLoading) AssetPackage(HeapForLoading, AssetName.data());
		
		AssetPackageSerializer serializer(HeapForLoading);
		LoadingResult = serializer.Deserialize(HeapForLoading, stream, *pPackage);

		if (!LoadingResult)
			return LoadingResult;

		LoadedPackage = pPackage;

		Service::ResourceManager->RegisterLoadedPackage(*LoadedPackage);

		return ResultCode::SUCCESS;
	}

	Result ResourceManager::AssetLoadingTaskImpl::LoadAsset(StringCrc64 assetType, IInputStream& stream)
	{
		AssetImporter *pImporter = nullptr;
		Result result = Service::AssetImporterFactory->FindImporter(assetType, pImporter);
		if (!result)
		{
			SFLog(Engine, Error, "Asset importer not found: {0}:{1}", stream.GetName(), stream.GetSourceName());
			LoadingResult = result;
			return result;
		}

		AssetImportContext context(HeapForLoading, stream, AssetName);
		StaticArray<ResourcePtr, 2> resultRes(HeapForLoading);
		result = pImporter->Import(context, resultRes);
		if (!result)
			return result;

		if (resultRes.size() == 0)
			return ResultCode::UNEXPECTED;

		LoadedResource = resultRes[0];

		Service::ResourceManager->RegisterLoadedResource(resultRes[0]);

		return ResultCode::SUCCESS;
	}


	void ResourceManager::AssetLoadingTaskImpl::Run()
	{
		// Parse type name
		auto pExt = Util::Path::GetExt(FilePath);
		if (pExt == nullptr)
		{
			LoadingResult = ResultCode::NOT_SUPPORTED_FORMAT;
			return;
		}

		String extension(HeapForLoading, pExt + 1);
		extension = extension.ToLower();
		StringCrc64 assetType = StringCrc64(extension.data());

		// find importer for the type
		FileInputStream inputStream(FilePath);
		if (!inputStream.CanRead())
			LoadingResult = ResultCode::INVALID_FILE;

		AssetName = Util::Path::GetFileNameWithoutExt(FilePath);

		if (assetType == "sfpkg")
		{
			LoadingResult = LoadPackage(assetType, inputStream);
		}
		else
		{
			LoadingResult = LoadAsset(assetType, inputStream);
		}
	}



	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager
	//
	

	ResourceManager::ResourceManager()
		: m_Heap("ResourceManager", GetEngineHeap())
		, m_PackageByName(GetEngineHeap())
		, m_ReferenceManager(GetEngineHeap())
	{
	}

	ResourceManager::~ResourceManager()
	{
	}

	void ResourceManager::RegisterLoadedPackage(AssetPackage* pPackage)
	{
		if (pPackage == nullptr)
			return;


	}

	void ResourceManager::RegisterLoadedResource(ResourcePtr& res)
	{

	}

	// Request loading an asset package. If the package is already exist, just reference count will be increased
	SharedPointerT<IResourceManagerService::AssetLoadingTask> ResourceManager::LoadAssetPackage(const String& packagePath, const TaskFinishedEventDelegate& pEventHandler)
	{
		SharedPointerT<AssetLoadingTask> loadingTask = new(GetHeap()) AssetLoadingTaskImpl(GetHeap(), pEventHandler);

		loadingTask->FilePath = String(GetHeap(), packagePath);

		// TODO: I need package packer tool first
		Service::AsyncTaskManager->PendingTask(*loadingTask);

		return loadingTask;
	}

	// Request loading a resource. If the resource is already exist, just reference count will be increased
	SharedPointerT<IResourceManagerService::AssetLoadingTask> ResourceManager::LoadAsset(const String& assetPath, const TaskFinishedEventDelegate& pEventHandler)
	{
		SharedPointerT<AssetLoadingTask> loadingTask = new(GetHeap()) AssetLoadingTaskImpl(GetHeap(), pEventHandler);

		loadingTask->FilePath = String(GetHeap(), assetPath);
		

		// Async task manager will do the job
		Service::AsyncTaskManager->PendingTask(*loadingTask);


		return loadingTask;
	}



	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager Component
	//

	constexpr StringCrc64 ResourceManagerComponent::TypeName;


	ResourceManagerComponent::ResourceManagerComponent()
		: LibraryComponent(TypeName)
		, m_ResourceManager()
	{
		Service::ResourceManager = &m_ResourceManager;
	}

	ResourceManagerComponent::~ResourceManagerComponent()
	{
		Service::ResourceManager = nullptr;
	}


	// Initialize component
	Result ResourceManagerComponent::InitializeComponent()
	{
		return LibraryComponent::InitializeComponent();
	}

	// Terminate component
	void ResourceManagerComponent::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();
	}


}


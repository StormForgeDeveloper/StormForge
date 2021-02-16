////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource manager service
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Object/SFSharedObject.h"
#include "Resource/SFResource.h"
#include "Container/SFDualSortedMap.h"
#include "Asset/Package/SFAssetPackage.h"
#include "Util/SFString.h"
#include "Task/SFTask.h"


namespace SF
{
	class ResourcePackage;

	////////////////////////////////////////////////////////////////////
	//
	//	Resource Manager service interface
	//
	class IResourceManagerService
	{
	public:

		typedef DualSortedMap<StringCrc64, AssetPackagePtr> AssetPackageList;


		// Asset loading notification task
		class AssetLoadingTask : public Task
		{
		public:

			AssetLoadingTask(IHeap& heap, const TaskFinishedEventDelegate& pEventHandler = {});
			virtual ~AssetLoadingTask() {}


			IHeap& HeapForLoading;

			// Asset loading path
			String FilePath;

			// Asset name. loader will assign this
			String AssetName;

			// Loading result
			Result LoadingResult;

			// Asset package pointer. If you requested a package, result package will be placed here
			SharedPointerAtomicT<AssetPackage> LoadedPackage;

			// Asset resource pointer. If you request single resource, this variable will have loaded value
			SharedPointerAtomicT<Resource> LoadedResource;
		};


	public:

		// Constructor
		IResourceManagerService() {}
		virtual ~IResourceManagerService() {}

		// Internal use
		virtual void RegisterLoadedPackage(AssetPackage* pPackage) { unused(pPackage); }
		virtual void RegisterLoadedResource(ResourcePtr& res) { unused(res); }

		// Request loading an asset package. If the package is already exist, just reference count will be increased
		// @packagePath: package path
		// @pNotificationQueue: optional, notification queue will be assigned to the queue. If you want to get notification than polling task state, you need to set up 
		virtual SharedPointerT<AssetLoadingTask> LoadAssetPackage(const String& packagePath, const TaskFinishedEventDelegate& pEventHandler) { unused(packagePath); unused(pEventHandler); return SharedPointerT<AssetLoadingTask>(); }

		// Request loading a resource. If the resource is already exist, just reference count will be increased
		// @assetPath: asset resource file path
		// @pNotificationQueue: optional, notification queue will be assigned to the queue
		virtual SharedPointerT<AssetLoadingTask> LoadAsset(const String& assetPath, const TaskFinishedEventDelegate& pEventHandler) { unused(assetPath); unused(pEventHandler); return SharedPointerT<AssetLoadingTask>(); }

	};
	


}


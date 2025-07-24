////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Object/SFObject.h"

namespace SF
{
	class ResourceManager;
	class AssetPackage;

	////////////////////////////////////////////////////////////////////
	//
	//	Resource
	//
	class Resource : public SharedObject
	{
	private:

		// package name
		StringCrc64 m_AssetPackageName;

		// Name of the resource
		StringCrc64 m_Name;

		// Source name where the resource comes from. mostly file name
		StringCrc64 m_SourceName;

		// Resource type
		StringCrc64 m_ResourceType;

		// Resource creation call stack track
		CallTrack m_CallTrack;

	public:
		Resource(StringCrc64 resType, const CallTrack& callTrack);
		virtual ~Resource();

		StringCrc64 GetPackageName() const { return m_AssetPackageName; }

		StringCrc64 GetName() const { return m_Name; }
		void SetName(StringCrc64 name) { m_Name = name; }

		StringCrc64 GetResourceType() const { return m_ResourceType; }

		// set source name
		void SetSourceName(StringCrc64 sourceName) { m_SourceName = sourceName; }
		// Get source name
		StringCrc64 GetSourceName() const { return m_SourceName; }
	};


	extern template class SharedPointerT<Resource>;
	extern template class WeakPointerT<Resource>;
	typedef SharedPointerT<Resource> ResourcePtr;

}


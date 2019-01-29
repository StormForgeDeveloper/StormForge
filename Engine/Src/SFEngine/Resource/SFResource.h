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
		FixedString m_AssetPackageName;

		// Name of the resource
		FixedString m_Name;

		// Source name where the resource comes from. mostly file name
		FixedString m_SourceName;

		// Resource type
		FixedString m_ResourceType;

		// heap for resource
		IHeap& m_Heap;

		// Resource creation call stack track
		CallTrack m_CallTrack;

	public:
		Resource(IHeap& heap, FixedString resType, const CallTrack& callTrack);
		virtual ~Resource();

		FixedString GetPackageName() const { return m_AssetPackageName; }

		FixedString GetName() const { return m_Name; }
		void SetName(FixedString name) { m_Name = name; }

		FixedString GetResourceType() const { return m_ResourceType; }

		// set source name
		void SetSourceName(FixedString sourceName) { m_SourceName = sourceName; }
		// Get source name
		FixedString GetSourceName() const { return m_SourceName; }

		// Get heap
		IHeap& GetHeap() { return m_Heap; }
	};


	extern template class SharedPointerT<Resource>;
	extern template class WeakPointerT<Resource>;
	typedef SharedPointerT<Resource> ResourcePtr;

}


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource Manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Container/SFDoubleLinkedList.h"
#include "Object/SFSharedObject.h"


namespace SF
{
	class Resource;
	class GraphicDevice;

	////////////////////////////////////////////////////////////////////
	//
	//	Device Resource interface abstract class
	//

	class DeviceResource : public SharedObject
	{
	public:



	private:

		// Object memory heap
		IHeap& m_Heap;

		// Graphic device manages this resource
		GraphicDevice* m_GraphicDevice;

		// Linked list node for graphic device
		DoubleLinkedListNodeDataT<DeviceResource*> m_ListNodeForDevice;


		bool m_IsReady : 1;  // ready to use
		bool m_IsDirty : 1;  // has dirty data

		// Data texture Pointer
		Resource* m_SourceResource;

	protected:

		void SetReady(bool ready) { m_IsReady = ready; }
		void SetDirty(bool dirty) { m_IsDirty = dirty; }

		// This node will be used for Device.
		// Do not use it on the other purpose
		DoubleLinkedListNodeDataT<DeviceResource*>& GetListNodeForDevice() { return m_ListNodeForDevice; }

		// Only graph device is the one have this resource type
		friend class GraphicDevice;

	public:
		DeviceResource(IHeap& heap, GraphicDevice* pDevice, Resource* sourceResource);
		virtual ~DeviceResource();
		bool GetReady() { return m_IsReady; }
		bool GetDirty() { return m_IsDirty; }

		// Memory heap for this resource
		IHeap& GetHeap() { return m_Heap; }

		// GetDevice
		GraphicDevice* GetDevice() { return m_GraphicDevice; }

		// Get source resource.
		Resource* GetSourceResource() { return m_SourceResource; }

		// Get source resource with type casting
		template<class SourceType>
		SourceType* GetSourceResource() { return static_cast<SourceType*>(m_SourceResource); }
	};


	typedef SharedPointerT<DeviceResource> DeviceResourcePtr;
	extern template class SharedPointerT<DeviceResource>;
	extern template class WeakPointerT<DeviceResource>;

}


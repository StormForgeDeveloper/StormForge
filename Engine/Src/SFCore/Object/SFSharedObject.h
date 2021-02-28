////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared pointer
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Multithread/SFSynchronization.h"


//#define REFERENCE_DEBUG_TRACKING

namespace SF {

	class SharedObjectManager;
	class SharedPointer;

	template<typename DestType>
	class SharedPointerT;


	// Shared object base
	class SharedObject
	{
	public:
		typedef SignedCounterType ReferenceCounterType;
		typedef std::atomic<ReferenceCounterType> Counter;

	private:
		// reference counter for shared references
		mutable Counter m_ReferenceCount;

		// reference counter for weak references
		mutable Counter m_WeakReferenceCount;

		// reference counter for manager queue reference
		mutable Counter m_ManagerReferenceCount;

		// reference manager object
		SharedObjectManager *m_ReferenceManagerObject;

	public:

#ifdef REFERENCE_DEBUG_TRACKING

		volatile const char* LatestReleaseFile;
		volatile int LatestReleaseLine;
		volatile mutable SharedObjectState LatestReleaseState;

		volatile mutable const char* LatestQueueProcessResult;

#endif

		SharedObject();
		virtual ~SharedObject();

		inline ReferenceCounterType		GetReferenceCount() const				{ return m_ReferenceCount.load(std::memory_order_relaxed); }
		inline ReferenceCounterType		GetWeakReferenceCount() const			{ return m_WeakReferenceCount.load(std::memory_order_relaxed); }
		inline ReferenceCounterType		GetManagerReferenceCount() const		{ return m_ManagerReferenceCount.load(std::memory_order_relaxed); }
		inline SharedObjectManager*		GetReferenceManager()					{ return m_ReferenceManagerObject; }

		SharedPointer AsSharedPtr() const;

		template<typename DestType,
			typename = std::enable_if_t<std::is_base_of_v<SharedObject,DestType>>>
		SharedPointerT<DestType> AsSharedPtr() const
		{
			return SharedPointerT<DestType>((DestType*)this);
		}


		// If your object is added to shared object manager and CanDelete returns false the manager will give more time for the object
		virtual bool	CanDelete() { return true; }
		inline bool		IsUniquelyReferenced() const { return m_ReferenceCount.load(std::memory_order_relaxed) == 1; }

		virtual void Dispose() {}

	private:

		CounterType AddReference() const;
		CounterType ReleaseReference() const;

		CounterType AddWeakReference() const;
		CounterType ReleaseWeakReference() const;

		friend class SharedReferenceInc;
		friend class SharedReferenceDec;
		friend class SharedObjectManager;
		friend class SharedPointer;
		friend class WeakPointer;
		friend class SharedPointerAtomic;
		friend class WeakPointerAtomic;
	};

	//extern template class PageQueue<SharedObject*>;

	/////////////////////////////////////////////////////////////////////
	//
	//	Reference counter
	//    - SharedObject's reference counter is not allowed to change manually.
	//	  - To change manually, you have to use special operator. These classes are for special purpose only
	//
	
	class SharedReferenceInc
	{
	public:
		SharedReferenceInc(SharedObject* pObject)
		{
			if (pObject != nullptr)
				pObject->AddReference();
		}
	};

	class SharedReferenceDec
	{
	public:
		SharedReferenceDec(SharedObject* pObject)
		{
			if (pObject != nullptr)
				pObject->ReleaseReference();
		}
	};


} // namespace SF


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
#include "Object/SFSharedObject.h"
#include "Multithread/SFSynchronization.h"


namespace SF {

	class WeakPointer;
	class SharedPointerAtomic;
	template<class ClassType> class SharedPointerAtomicT;
	template<class ClassType> class WeakPointerT;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Shared pointer reference class
	//

	class SharedPointer
	{
	public:

	protected:
		mutable SharedObject *m_pObject;

	public:

		constexpr SharedPointer()
			: m_pObject(nullptr)
		{
		}

		SharedPointer(const SharedPointer& src)
			: m_pObject(src.m_pObject)
		{
			if (m_pObject != nullptr)
				m_pObject->AddReference();
		}

		SharedPointer(SharedPointer&& src) noexcept
			: m_pObject(src.m_pObject)
		{
			src.m_pObject = nullptr;
		}

		SharedPointer(SharedPointerAtomic&& src);

		SharedPointer(SharedObject* pRef)
			: m_pObject(pRef)
		{
			if (m_pObject != nullptr)
			{
				m_pObject->AddReference();
			}
		}

		constexpr SharedPointer(std::nullptr_t)
			: m_pObject(nullptr)
		{
		}

		virtual ~SharedPointer()
		{
			ReleaseReference();
		}

		void ReleaseReference() const
		{
			// prevent recursive release
			auto pObject = m_pObject;
			m_pObject = nullptr;
			if (pObject == nullptr)
				return;

			//assert(m_pObject->m_ReferenceCount > 0);

			pObject->ReleaseReference();

			pObject = nullptr;
		}

		explicit operator SharedObject*()
		{
			return m_pObject;
		}
#ifndef SWIG
		explicit operator const SharedObject*() const
		{
			return m_pObject;
		}
#endif
		SharedObject* get() const { return m_pObject; }

		void operator = (const SharedPointer& src)
		{
			ReleaseReference();

			auto pPtr = src.m_pObject;

			if (pPtr != nullptr)
			{
				Assert(pPtr->GetWeakReferenceCount() > 0 || pPtr->GetReferenceCount() > 0);
				pPtr->AddReference();
			}

			m_pObject = pPtr;
		}

		SharedPointer& operator = (SharedPointer&& src) noexcept
		{
			ReleaseReference();

			m_pObject = src.m_pObject;
			src.m_pObject = nullptr;

			return *this;
		}

		SharedPointer& operator = (SharedPointerAtomic&& src) noexcept;

		bool operator == (const SharedPointer& src) const
		{
			return m_pObject == src.m_pObject;
		}

		bool operator != (const SharedPointer& src) const
		{
			return m_pObject != src.m_pObject;
		}

		bool operator == (SharedObject* pRef) const
		{
			return m_pObject == pRef;
		}

		bool operator != (SharedObject* pRef) const
		{
			return m_pObject != pRef;
		}


	protected:

		virtual void SetPointer(SharedObject* pObject)
		{
			ReleaseReference();

			m_pObject = pObject;
		}

		friend class SharedObject;
		friend class SharedPointerAtomic;
	};

	template<class ClassType>
	class SharedPointerT : public SharedPointer
	{
	public:

		using ObjectType = ClassType;
		using super = SharedPointer;

	public:
		constexpr SharedPointerT()
			:SharedPointer()
		{
		}

		SharedPointerT(const SharedPointerT<ClassType>& src)
			: SharedPointer(src)
		{
		}

		SharedPointerT(const SharedPointerAtomicT<ClassType>& src)
			: SharedPointer(*src)
		{
		}

#ifndef SWIG
		SharedPointerT(SharedPointerT<ClassType>&& src)
			:SharedPointer(std::forward<SharedPointerT<ClassType>>(src))
		{
		}

		SharedPointerT(SharedPointerAtomicT<ClassType>&& src)
			: SharedPointer(std::forward<SharedPointerAtomicT<ClassType>>(src))
		{
		}
#endif

		SharedPointerT(ClassType* pRef)
			:SharedPointer(static_cast<SharedObject*>(pRef))
		{
		}

		constexpr SharedPointerT(std::nullptr_t)
			: SharedPointer()
		{
		}

		SharedPointerT(WeakPointerT<ClassType>& src);

		virtual ~SharedPointerT()
		{
		}

		ClassType* GetObjectPtr()
		{
			return (ClassType*)m_pObject;
		}

		// supporting std style interface
		ClassType* get() const
		{
			return (ClassType*)m_pObject;
		}

		explicit operator ClassType*()			{ return (ClassType*)m_pObject; }
		explicit operator ClassType*() const 	{ return (ClassType*)m_pObject; }

		ClassType* operator ->() 			{ return (ClassType*)m_pObject; }
		ClassType* operator ->() const		{ return (ClassType*)m_pObject; }

		ClassType* operator *()				{ return (ClassType*)m_pObject; }
		ClassType* operator *() const		{ return (ClassType*)m_pObject; }

		bool operator == (const SharedPointer& src) const
		{
			return SharedPointer::operator == (src);
		}

		bool operator != (const SharedPointer& src) const
		{
			return SharedPointer::operator != (src);
		}

		bool operator == (SharedObject* pRef) const
		{
			return SharedPointer::operator == (pRef);
		}

		bool operator != (SharedObject* pRef) const
		{
			return SharedPointer::operator != (pRef);
		}

		bool IsUnique() const
		{
			return m_pObject != nullptr && m_pObject->GetReferenceCount() == 1;
		}

#ifndef SWIG
		SharedPointerT<ClassType>& operator = (const SharedPointer& src)
		{
			auto pObjectSrc = (SharedObject*)(const SharedObject*)src;
			if (pObjectSrc != nullptr)
			{
				if (!TypeCheck(pObjectSrc))
				{
					AssertRel(false);
					return *this;
				}
			}

			SharedPointer::operator = (src);

			return *this;
		}

		SharedPointerT<ClassType>& operator = (SharedPointer&& src)
		{
			auto pObjectSrc = (SharedObject*)(const SharedObject*)src;
			if (pObjectSrc != nullptr)
			{
				if (!TypeCheck(pObjectSrc))
				{
					AssertRel(false);
					return *this;
				}
			}

			SharedPointer::operator = (std::forward<SharedPointer>(src));

			return *this;
		}

		SharedPointerT<ClassType>& operator = (const SharedPointerT<ClassType>& src)
		{
			SharedPointer::operator = (src);
			return *this;
		}

		SharedPointerT<ClassType>& operator = (SharedPointerT<ClassType>&& src)
		{
			SharedPointer::operator = (std::forward<SharedPointer>(src));
			return *this;
		}


		template<class TargetObjectType>
		SharedPointerT<TargetObjectType> StaticCast() { return SharedPointerT<TargetObjectType>(static_cast<TargetObjectType*>((ClassType*)m_pObject)); }

		template<class TargetObjectType>
		const SharedPointerT<TargetObjectType> StaticCast() const { return SharedPointerT<TargetObjectType>(static_cast<TargetObjectType*>((ClassType*)m_pObject)); }

		template<class TargetObjectType>
		SharedPointerT<TargetObjectType> DynamicCast() { return SharedPointerT<TargetObjectType>(dynamic_cast<TargetObjectType*>((ClassType*)m_pObject)); }

		template<class TargetObjectType>
		const SharedPointerT<TargetObjectType> DynamicCast() const { return SharedPointerT<TargetObjectType>(dynamic_cast<TargetObjectType*>((ClassType*)m_pObject)); }


		SharedPointerT<ClassType>& operator = (const SharedPointerAtomicT<ClassType>& src);

		SharedPointerT<ClassType>& operator = (SharedPointerAtomicT<ClassType>&& src);

		SharedPointerT<ClassType>& operator = (WeakPointerT<ClassType>& src);

		SharedPointerT<ClassType>& operator = (ClassType* src)
		{
			//assert(src == nullptr);
			//if(src == nullptr)
			//	SharedPointer::operator = (SharedPointer());
			//else
				SharedPointer::operator = (SharedPointerT<ClassType>(src));
			return *this;
		}
#endif

	protected:

		bool TypeCheck(SharedObject* pObject)
		{
//#ifdef DEBUG
//			if (pObject == nullptr) return true;
//
//			bool sameType = dynamic_cast<ClassType*>(pObject) != nullptr;
//			//auto type = typeid(*pObject).name();
//			//auto type2 = typeid(ClassType).name();
//			//bool sameType = type == type2;
//			assert(sameType);
//			return sameType;
//#else
			// don't check
			return true;
//#endif
		}

		virtual void SetPointer(SharedObject* pObject) override
		{
			if (!TypeCheck(pObject))
				return;

			SharedPointer::SetPointer(pObject);
		}
	};


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Shared pointer reference class
	//

	class SharedPointerAtomic
	{
	public:

	protected:
		mutable std::atomic<SharedObject*> m_pObject;

		friend class SharedPointer;
	public:

		constexpr SharedPointerAtomic() noexcept
			: m_pObject(nullptr)
		{
		}

		SharedPointerAtomic(const SharedPointer& src) noexcept
			: m_pObject(nullptr)
		{
			auto pObject = const_cast<SharedObject*>((const SharedObject*)src);
			if (pObject != nullptr)
				pObject->AddReference();
			m_pObject = pObject;
		}

		SharedPointerAtomic(const SharedPointerAtomic& src) noexcept
			: m_pObject(nullptr)
		{
			auto pObject = src.m_pObject.load(std::memory_order_relaxed);
			if (pObject != nullptr)
				pObject->AddReference();
			m_pObject = pObject;
		}

		SharedPointerAtomic(SharedPointerAtomic&& src) noexcept
			:m_pObject(nullptr)
		{
			m_pObject = src.m_pObject.exchange(nullptr,std::memory_order_release);
		}

		SharedPointerAtomic(SharedPointer&& src) noexcept
			:m_pObject(nullptr)
		{
			m_pObject = const_cast<SharedObject*>((const SharedObject*)src);
			src.m_pObject = nullptr;
		}

		SharedPointerAtomic(SharedObject* pRef) noexcept
			:m_pObject(pRef)
		{
			if (pRef != nullptr)
			{
				pRef->AddReference();
			}
		}

		constexpr SharedPointerAtomic(std::nullptr_t) noexcept
			: m_pObject(nullptr)
		{
		}

		virtual ~SharedPointerAtomic()
		{
			ReleaseReference();
		}

		void ReleaseReference() const
		{
			auto pObj = m_pObject.exchange(nullptr, std::memory_order_acq_rel);
			if (pObj == nullptr)
				return;

			pObj->ReleaseReference();
		}

		explicit operator SharedObject*()
		{
			return m_pObject.load(std::memory_order_relaxed);
		}

		SharedObject* get() const
		{
			return m_pObject.load(std::memory_order_relaxed);
		}

		void Swap(SharedPointer& src)
		{
			auto pObject = const_cast<SharedObject*>((const SharedObject*)src);
			auto pOldObject = m_pObject.exchange(pObject, std::memory_order_acq_rel);
			src.m_pObject = pOldObject;
		}

		void Swap(SharedPointerAtomic& src)
		{
			// This doesn't guarantee that assignment to the src is atomic
			auto pObject = const_cast<SharedObject*>((const SharedObject*)src);
			auto pOldObject = m_pObject.exchange(pObject, std::memory_order_relaxed);
			src.m_pObject.exchange(pOldObject, std::memory_order_release);
		}

		bool ComapreNExchange(SharedObject*& expectedValue, const SharedPointer& newValue)
		{
			auto pObject = newValue.get();
			bool bRet = m_pObject.compare_exchange_strong(expectedValue, pObject);
			if (bRet)
			{
				if (expectedValue)
					expectedValue->ReleaseReference();
				pObject->AddReference();
			}

			return bRet;
		}

		bool ComapreNExchange(SharedObject*& expectedValue, const SharedPointerAtomic& newValue)
		{
			auto pObject = newValue.get();
			bool bRet = m_pObject.compare_exchange_strong(expectedValue, pObject);
			if (bRet)
			{
				if (expectedValue)
					expectedValue->ReleaseReference();
				pObject->AddReference();
			}

			return bRet;
		}


#ifndef SWIG

		SharedObject* operator *()
		{
			return m_pObject.load(std::memory_order_relaxed);
		}

		SharedObject* operator *() const
		{
			return m_pObject.load(std::memory_order_relaxed);
		}

		explicit operator SharedObject*() const
		{
			return m_pObject.load(std::memory_order_relaxed);
		}
#endif
		void operator = (const SharedPointerAtomic& src)
		{
			auto pObject = const_cast<SharedObject*>((const SharedObject*)src);
			if (pObject != nullptr)
				pObject->AddReference();

			auto pOldObject = m_pObject.exchange(pObject, std::memory_order_acq_rel);
			if (pOldObject == nullptr)
				return;

			pOldObject->ReleaseReference();
		}

		void operator = (const SharedPointer& src)
		{
			auto pObject = const_cast<SharedObject*>((const SharedObject*)src);
			if (pObject != nullptr)
				pObject->AddReference();

			auto pOldObject = m_pObject.exchange(pObject, std::memory_order_acq_rel);
			if (pOldObject == nullptr)
				return;

			pOldObject->ReleaseReference();
		}

		void operator = (SharedPointer&& src)
		{
			auto pObject = const_cast<SharedObject*>((const SharedObject*)src);
			if (pObject != nullptr)
				pObject->AddReference();

			m_pObject = const_cast<SharedObject*>((const SharedObject*)src);
			src.m_pObject = nullptr;

			auto pOldObject = m_pObject.exchange(pObject, std::memory_order_acq_rel);
			if (pOldObject == nullptr)
				return;

			pOldObject->ReleaseReference();
		}

		void operator = (SharedPointerAtomic&& src) noexcept
		{
			auto pObject = const_cast<SharedObject*>((const SharedObject*)src);
			src.m_pObject = nullptr;

			auto pOldObject = m_pObject.exchange(pObject, std::memory_order_acq_rel);
			if (pOldObject == nullptr)
				return;

			pOldObject->ReleaseReference();
		}

		bool operator == (const SharedPointerAtomic& src) const
		{
			return m_pObject.load(std::memory_order_relaxed) == src.m_pObject.load(std::memory_order_relaxed);
		}

		bool operator != (const SharedPointerAtomic& src) const
		{
			return m_pObject.load(std::memory_order_relaxed) != src.m_pObject.load(std::memory_order_relaxed);
		}

		bool operator == (SharedObject* pRef) const
		{
			return m_pObject.load(std::memory_order_relaxed) == pRef;
		}

		bool operator != (SharedObject* pRef) const
		{
			return m_pObject.load(std::memory_order_relaxed) != pRef;
		}

	protected:

		virtual void SetPointer(SharedObject* pObject)
		{
			ReleaseReference();

			m_pObject = pObject;
		}

		friend class SharedObject;
	};

	template<class ClassType>
	class SharedPointerAtomicT : public SharedPointerAtomic
	{
	public:

		using super = SharedPointerAtomic;

	public:
		constexpr SharedPointerAtomicT()
			:SharedPointerAtomic()
		{
		}

		SharedPointerAtomicT(const SharedPointerAtomicT<ClassType>& src)
			:SharedPointerAtomic(src)
		{
		}

#ifndef SWIG
		SharedPointerAtomicT(SharedPointerAtomicT<ClassType>&& src)
			: SharedPointerAtomic(std::forward<SharedPointerAtomicT<ClassType>>(src))
		{
		}
#endif

		SharedPointerAtomicT(ClassType* pRef)
			:SharedPointerAtomic(pRef)
		{
		}

		constexpr SharedPointerAtomicT(std::nullptr_t)
			: SharedPointerAtomic()
		{
		}

		SharedPointerAtomicT(WeakPointerT<ClassType>& src);

		virtual ~SharedPointerAtomicT()
		{
		}

		ClassType* get()
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}

		ClassType* get() const
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}

		// deprecated, use std style get()
		ClassType* GetObjectPtr()
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}
#ifndef SWIG
		explicit operator ClassType*()
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}

		explicit operator const ClassType*() const
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}

		ClassType* operator ->()
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}

		ClassType* operator ->() const
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}

		ClassType* operator *()
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}

		ClassType* operator *() const
		{
			return (ClassType*)m_pObject.load(std::memory_order_relaxed);
		}
#endif
		bool operator == (const SharedPointerAtomic& src) const
		{
			return SharedPointerAtomic::operator == (src);
		}

		bool operator != (const SharedPointerAtomic& src) const
		{
			return SharedPointerAtomic::operator != (src);
		}

		bool operator == (SharedObject* pRef) const
		{
			return SharedPointerAtomic::operator == (pRef);
		}

		bool operator != (SharedObject* pRef) const
		{
			return SharedPointerAtomic::operator != (pRef);
		}

		//template<typename = std::enable_if_t<std::is_base_of_v<SharedObject, ClassType>>>
		bool ComapreNExchange(ClassType*& expectedValue, const SharedPointerT<ClassType>& newValue)
		{
			SharedObject* expectedValueLocal = static_cast<SharedObject*>(expectedValue);
			bool bRet = super::ComapreNExchange(expectedValueLocal, newValue);
			expectedValue = static_cast<ClassType*>(expectedValueLocal);;
			return bRet;
		}

		//template<typename = std::enable_if_t<std::is_base_of_v<SharedObject, ClassType>>>
		bool ComapreNExchange(ClassType*& expectedValue, const SharedPointerAtomicT<ClassType>& newValue)
		{
			SharedObject* expectedValueLocal = static_cast<SharedObject*>(expectedValue);
			bool bRet = super::ComapreNExchange(expectedValueLocal, newValue);
			expectedValue = static_cast<ClassType*>(expectedValueLocal);
			return bRet;
		}

		template<class TargetObjectType>
		SharedPointerT<TargetObjectType> Cast() { return SharedPointerT<TargetObjectType>((ClassType*)m_pObject); }

		template<class TargetObjectType>
		const SharedPointerT<TargetObjectType> Cast() const { return SharedPointerT<TargetObjectType>((ClassType*)m_pObject); }


#ifndef SWIG
		SharedPointerAtomicT<ClassType>& operator = (const SharedPointerAtomic& src)
		{
			auto pObjectSrc = (SharedObject*)(const SharedObject*)src;
			if (pObjectSrc != nullptr)
			{
				if (!TypeCheck(pObjectSrc))
				{
					AssertRel(false);
					return *this;
				}
			}

			SharedPointerAtomic::operator = (src);

			return *this;
		}

		SharedPointerAtomicT<ClassType>& operator = (SharedPointerAtomic&& src)
		{
			auto pObjectSrc = (SharedObject*)(const SharedObject*)src;
			if (pObjectSrc != nullptr)
			{
				if (!TypeCheck(pObjectSrc))
				{
					AssertRel(false);
					return *this;
				}
			}

			SharedPointerAtomic::operator = (std::forward<SharedPointerAtomic>(src));

			return *this;
		}

		SharedPointerAtomicT<ClassType>& operator = (const SharedPointerAtomicT<ClassType>& src)
		{
			SharedPointerAtomic::operator = (src);
			return *this;
		}

		SharedPointerAtomicT<ClassType>& operator = (SharedPointerAtomicT<ClassType>&& src)
		{
			SharedPointerAtomic::operator = (std::forward<SharedPointerAtomic>(src));
			return *this;
		}

		SharedPointerAtomicT<ClassType>& operator = (const SharedPointerT<ClassType>& src)
		{
			SharedPointerAtomic::operator = (src);
			return *this;
		}

		SharedPointerAtomicT<ClassType>& operator = (SharedPointerT<ClassType>&& src)
		{
			SharedPointerAtomic::operator = (std::forward<SharedPointer>(src));
			return *this;
		}


		SharedPointerAtomicT<ClassType>& operator = (WeakPointerT<ClassType>& src);

		SharedPointerAtomicT<ClassType>& operator = (void* src)
		{
			assert(src == nullptr);
			SharedPointerAtomic::operator = (SharedPointerAtomic());
			return *this;
		}
#endif

	protected:

		bool TypeCheck(SharedObject* pObject)
		{
//#ifdef DEBUG
//			if (pObject == nullptr) return true;
//
//			bool sameType = dynamic_cast<ClassType*>(pObject) != nullptr;
//			//auto type = typeid(*pObject).name();
//			//auto type2 = typeid(ClassType).name();
//			//bool sameType = type == type2;
//			assert(sameType);
//			return sameType;
//#else
			// don't check
			return true;
//#endif
		}

		virtual void SetPointer(SharedObject* pObject) override
		{
			if (!TypeCheck(pObject))
				return;

			SharedPointerAtomic::SetPointer(pObject);
		}
	};



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Weak pointer reference class
	//

	class WeakPointer
	{
	public:

	protected:

		mutable SharedObject *m_pObject;

		WeakPointer(SharedObject* pRef)
			:m_pObject(pRef)
		{
			if (m_pObject != nullptr)
				m_pObject->AddWeakReference();
		}

	public:

		void FromSharedObject(SharedObject *pObject)
		{
			ReleaseReference();

			m_pObject = pObject;

			if (m_pObject != nullptr)
			{
				m_pObject->AddWeakReference();
			}
		}

		WeakPointer() noexcept
			:m_pObject(nullptr)
		{
		}

		WeakPointer(const WeakPointer& src) noexcept
			:m_pObject(src.m_pObject)
		{
			if (m_pObject != nullptr)
				m_pObject->AddWeakReference();
		}

		WeakPointer(WeakPointer&& src) noexcept
			:m_pObject(src.m_pObject)
		{
			src.m_pObject = nullptr;
		}

		virtual ~WeakPointer()
		{
			ReleaseReference();
		}

		void ReleaseReference() const
		{
			auto pObject = m_pObject;
			m_pObject = nullptr;
			if (pObject == nullptr)
				return;

			pObject->ReleaseWeakReference();

			pObject = nullptr;
		}

		SharedPointer AsSharedPtr() const
		{
			if (m_pObject != nullptr)
				return std::forward<SharedPointer>(m_pObject->AsSharedPtr());
			else
				return SharedPointer();
		}

		template<class SharedObjectType>
		SharedPointerT<SharedObjectType> AsSharedPtr() const
		{
			if (m_pObject != nullptr)
				return SharedPointerT<SharedObjectType>(static_cast<SharedObjectType*>(m_pObject));
			else
				return SharedPointerT<SharedObjectType>();
		}

		explicit operator SharedPointer()
		{
			if (m_pObject != nullptr)
				return std::forward<SharedPointer>(m_pObject->AsSharedPtr());
			return SharedPointer();
		}

		explicit operator const SharedPointer() const
		{
			if (m_pObject != nullptr)
				return std::forward<SharedPointer>(m_pObject->AsSharedPtr());
			return SharedPointer();
		}

		bool operator == (const SharedPointer& src) const
		{
			return m_pObject == (const SharedObject*)src;
		}

		bool operator != (const SharedPointer& src) const
		{
			return m_pObject != (const SharedObject*)src;
		}

		bool operator == (const WeakPointer& src) const
		{
			return m_pObject == src.m_pObject;
		}

		bool operator != (const WeakPointer& src) const
		{
			return m_pObject != src.m_pObject;
		}

		bool operator == (SharedObject* pRef) const
		{
			return m_pObject == pRef;
		}

		bool operator != (SharedObject* pRef) const
		{
			return m_pObject != pRef;
		}

		WeakPointer& operator = (const SharedPointer& src)
		{
			ReleaseReference();

			auto *pObj = const_cast<SharedObject*>((const SharedObject*)src);
			if (pObj == nullptr)
				return *this;

			m_pObject = pObj;

			if (m_pObject != nullptr)
			{
				//Assert(m_pObject->GetWeakReferenceCount() > 0 || m_pObject->GetReferenceCount() > 0);
				m_pObject->AddWeakReference();
			}

			return *this;
		}

		WeakPointer& operator = (const WeakPointer& src)
		{
			ReleaseReference();

			if (src.m_pObject == nullptr || src.m_pObject->GetReferenceCount() == 0)
				return *this;

			auto pPtr = src.m_pObject;

			if (pPtr != nullptr)
			{
				//AssertRel(m_pObject->GetWeakReferenceCount() > 0 || m_pObject->GetReferenceCount() > 0);
				pPtr->AddWeakReference();
			}

			m_pObject = pPtr;

			return *this;
		}

		WeakPointer& operator = (WeakPointer&& src) noexcept
		{
			ReleaseReference();

			m_pObject = src.m_pObject;
			src.m_pObject = nullptr;

			return *this;
		}


		//WeakPointer& operator = (void* src)
		//{
		//	// Assigning non pointer directly isn't thread safe
		//	assert(src != nullptr);
		//	ReleaseReference();

		//	return *this;
		//}
	};

	template<class ClassType>
	class WeakPointerT : public WeakPointer
	{
	public:
		WeakPointerT()
			:WeakPointer()
		{
		}

		WeakPointerT(ClassType* src)
			:WeakPointer(src)
		{
		}
        
        WeakPointerT(const SharedPointerT<ClassType>& src)
        :WeakPointer(const_cast<ClassType*>((const ClassType*)src))
        {
        }
        

		WeakPointerT(const WeakPointerT<ClassType>& src)
			:WeakPointer(src)
		{
		}

		WeakPointerT(WeakPointerT<ClassType>&& src)
			:WeakPointer(src)
		{
		}

		~WeakPointerT()
		{
		}

		explicit operator SharedPointerT<ClassType>()
		{
			return std::forward<SharedPointerT<ClassType>>(AsSharedPtr<ClassType>());
		}

		explicit operator const SharedPointerT<ClassType>() const
		{
			return std::forward<SharedPointerT<ClassType>>(AsSharedPtr<ClassType>());
		}

		bool operator == (const SharedPointer& src) const
		{
			return WeakPointer::operator == (src);
		}

		bool operator != (const SharedPointer& src) const
		{
			return WeakPointer::operator != (src);
		}

		bool operator == (const WeakPointer& src) const
		{
			return WeakPointer::operator == (src);
		}

		bool operator != (const WeakPointer& src) const
		{
			return WeakPointer::operator != (src);
		}

		bool operator == (SharedObject* pRef) const
		{
			return WeakPointer::operator == (pRef);
		}

		bool operator != (SharedObject* pRef) const
		{
			return WeakPointer::operator != (pRef);
		}

		WeakPointerT<ClassType>& operator = (const SharedPointerT<ClassType>& src)
		{
			WeakPointer::operator = (src);

			return *this;
		}

		WeakPointerT<ClassType>& operator = (const SharedPointer& src)
		{
			WeakPointer::operator = (src);

			if (m_pObject != nullptr)
			{
				assert(typeid(m_pObject) == typeid(ClassType));
			}

			return *this;
		}

		WeakPointerT<ClassType>& operator = (const WeakPointer& src)
		{
			WeakPointer::operator = (src);

			if (m_pObject != nullptr)
			{
				assert(typeid(m_pObject) == typeid(ClassType));
			}

			return *this;
		}

		WeakPointerT<ClassType>& operator = (WeakPointer&& src)
		{
			WeakPointer::operator = (src);

			if (m_pObject != nullptr)
			{
				assert(typeid(m_pObject) == typeid(ClassType));
			}

			return *this;
		}

		WeakPointerT<ClassType>& operator = (const WeakPointerT<ClassType>& src)
		{
			WeakPointer::operator = (src);

			return *this;
		}

		WeakPointerT<ClassType>& operator = (WeakPointerT<ClassType>&& src)
		{
			WeakPointer::operator = (std::forward<WeakPointerT<ClassType>>(src));

			return *this;
		}

	};

	inline SharedPointer::SharedPointer(SharedPointerAtomic&& src)
		: m_pObject(*src)
	{
		src.m_pObject = nullptr;
	}


	inline SharedPointer& SharedPointer::operator = (SharedPointerAtomic&& src) noexcept
	{
		ReleaseReference();

		auto pObj = src.m_pObject.exchange(nullptr, std::memory_order_acq_rel);
		m_pObject = pObj;
		return *this;
	}



	template<class ClassType>
	SharedPointerT<ClassType>& SharedPointerT<ClassType>::operator = (const SharedPointerAtomicT<ClassType>& src)
	{
		auto pObj = const_cast<ClassType*>((const ClassType*)src);
		SharedPointer::operator = (SharedPointer(pObj));
		return *this;
	}

	template<class ClassType>
	SharedPointerT<ClassType>& SharedPointerT<ClassType>::operator = (SharedPointerAtomicT<ClassType>&& src)
	{
		SharedPointer::operator = (std::forward<SharedPointerAtomic>(src));
		return *this;
	}

	template<class ClassType>
	SharedPointerT<ClassType>::SharedPointerT(WeakPointerT<ClassType>& src)
	{
		*this = std::forward<SharedPointerT<ClassType>>(src.template AsSharedPtr<ClassType>());
	}

	template<class ClassType>
	SharedPointerT<ClassType>& SharedPointerT<ClassType>::operator = (WeakPointerT<ClassType>& src)
	{
		*this = std::forward<SharedPointerT<ClassType>>(src.template AsSharedPtr<ClassType>());
		return *this;
	}


}


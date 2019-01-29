////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Object Pool 
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "Container/SFStackPool.h"



namespace SF {

	class IHeap;
	class MemoryPoolManager;
	class MemoryPool;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Object Pool object implementation
	//

	class ObjectPoolObject
	{
	public:
		// Constructor, will be called only once
		ObjectPoolObject(){}
		// Destructor, clear all your dynamic allocated memory in Dispose() otherwise it's going to stay all the time.
		virtual ~ObjectPoolObject(){}

		// Called when the object is going to be reused
		virtual Result Reuse(){ return ResultCode::SUCCESS; }
		// Called when the object is going to be disposed
		virtual Result Dispose() { return ResultCode::SUCCESS; }
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Object Pool
	//


	class ObjectPool
	{
	public:
		enum {
			// Pool item count range per page
			POOL_ITEM_MIN = 16,
			POOL_ITEM_MAX = 4096,

			POOL_MEMMAGIC = 0xABABABABL
		};

		// free stack item
		struct ObjectItem
		{
			int Using;
			ObjectItem *pNext;
			ObjectPoolObject *pObject;
		};

		enum {
			MEMITEM_SIZE = sizeof(ObjectItem),
		};


	private:

		// allocation data size
		size_t	m_AllocSize;

		// Allocated item count
		SyncCounter	m_AllocatedCount;

		// 
		bool m_CallDestructor;

		// Free item stack
		ObjectItem*	m_FreeList;

		IHeap& m_Heap;

	private:


	public:
		// Constructor for singleton
		ObjectPool(IHeap& heap, size_t objectSize);
		virtual ~ObjectPool();

		IHeap& GetHeap() { return m_Heap; }

		// Get allocation size
		size_t GetAllocSize() const						{ return m_AllocSize; }

		// Call destructor when an object is actually freed
		void SetCallDestructor(bool callDestructor)		{ m_CallDestructor = callDestructor; }
		bool GetCallDestructor() const					{ return m_CallDestructor; }

		// force clear memory heap
		void ForceClear();

		// called when a object is created
		virtual ObjectPoolObject* OnNewObject(void* pNewObject) = 0;

		// Allocate/Free
		Result Alloc(ObjectPoolObject* &pPtr);
		Result Free(ObjectPoolObject* pPtr);
	};


	template< class ObjectType >
	class ObjectPoolT : public ObjectPool
	{
	public:
		ObjectPoolT(IHeap& heap)
			:ObjectPool(heap, sizeof(ObjectType))
		{
		}

		virtual ~ObjectPoolT()
		{
		}


		virtual ObjectPoolObject* OnNewObject(void* pNewObject)
		{
			return new(pNewObject)ObjectType;
		}

		Result Alloc(ObjectType* &pPtr)
		{
			ObjectPoolObject *pObj = nullptr;
			Result hr = ObjectPool::Alloc(pObj);
			pPtr = (ObjectType*)(pObj);
			return hr;
		}

		Result Free(ObjectType* pPtr)
		{
			return ObjectPool::Free(pPtr);
		}
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Object Pool(Multithread)
	//

	class ObjectPoolMT
	{
	public:
		enum {
			// Pool item count range per page
			POOL_ITEM_MIN = 8,
			POOL_ITEM_MAX = 1024,

			POOL_MEMMAGIC = 0xABABABABL
		};

		// free stack item
		struct MemItem : public StackPool::Item
		{
			int64_t MemMagic;
			SyncCounter Using;
			ObjectPoolObject *pObject;

			MemItem()
			{
				memset(this, 0, sizeof(MemItem));
			}
		};

		enum {
			MEMITEM_SIZE = AlignUp(sizeof(MemItem),SF_ALIGN_DOUBLE)
		};


	private:

		// allocation unit size
		size_t	m_AllocSize;

		// Allocated item count
		SyncCounter	m_AllocatedCount;

		// Page allocate
		IHeap& m_Heap;

		// Free item stack
		StackPool	m_FreeList;

	private:


	public:
		// Constructor for singleton
		ObjectPoolMT(IHeap& heap, size_t objectSize);
		virtual ~ObjectPoolMT();

		IHeap& GetHeap() { return m_Heap; }

		// Get allocation size
		size_t GetAllocSize() const			{ return m_AllocSize - MEMITEM_SIZE; }
		size_t GetAllocDataSize() const	{ return m_AllocSize; }

		// force clear memory heap
		void ForceClear();

		// called when a object is created
		virtual ObjectPoolObject* OnNewObject( void* pNewObject ) = 0;

		// Allocate/Free
		Result Alloc( ObjectPoolObject* &pPtr );
		Result Free( ObjectPoolObject* pPtr );
	};


	template< class ObjectType >
	class ObjectPoolMTT : public ObjectPoolMT
	{
	public:
		ObjectPoolMTT(IHeap& heap)
			:ObjectPoolMT(heap, sizeof(ObjectType))
		{
		}

		virtual ~ObjectPoolMTT()
		{
		}

		virtual ObjectPoolObject* OnNewObject( void* pNewObject )
		{
			return new(pNewObject) ObjectType;
		}

		Result Alloc( ObjectType* &pPtr )
		{
			ObjectPoolObject *pObj = nullptr;
			Result hr = ObjectPoolMT::Alloc( pObj );
			pPtr = (ObjectType*)(pObj);
			return hr;
		}

		Result Free( ObjectType* pPtr )
		{
			return ObjectPoolMT::Free( pPtr );
		}
	};

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Object Pool object implementation
	//


	template< class ObjectType >
	class ObjectPoolObjectT : public ObjectPoolObject
	{
	public:
		typedef ObjectPoolMTT<ObjectType> MyObjectPool;

	protected:
		// Memory pool that assigned with this class
		static MyObjectPool* stm_ObjectPool;

		ObjectPoolObjectT() {}
		virtual ~ObjectPoolObjectT() {}

		friend class ObjectPoolMTT<ObjectType>;

	public:

		void Release()
		{
			FreeObject((ObjectType*)this);
		}

		static ObjectType* AllocateObject()
		{
			Assert(stm_ObjectPool != nullptr);
			if( stm_ObjectPool == nullptr )
				return nullptr;

			ObjectType *pPtr = nullptr;
			stm_ObjectPool->Alloc( pPtr );
			return (ObjectType*)pPtr;
		}

		static void FreeObject( ObjectType* pObj )
		{
			Assert(stm_ObjectPool != nullptr);
			if( stm_ObjectPool == nullptr )
				return;

			stm_ObjectPool->Free( pObj );
		}
	};


	#define SF_OBJECTPOOL_IMPLEMENT(className) \
		namespace SF {\
		ObjectPoolMTT<className>* ObjectPoolObjectT<className>::stm_ObjectPool = new(GetEngineHeap()) ObjectPoolMTT<className>(GetSystemHeap()); \
		};\



}; // namespace SF




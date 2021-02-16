////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread safe hash table
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Container/SFIndexing.h"
#include "Container/SFContainerTrait.h"
#include "Multithread/SFSystemSynchronization.h"
#include "Container/SFArray.h"



namespace SF {


		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Thread safe hash map
		//

		template<	typename KeyType,
					typename ItemType, 
					typename Trait = UniqueKeyTrait, 
					typename ThreadTrait = ThreadSyncTraitReadWriteT<KeyType,ItemType>,
					typename HasherType = SF::hash<KeyType> >
		class HashTable2
		{
		public:

			// internal aliasing
			typedef ItemType ValueType;
			typedef typename ThreadTrait::TicketLockType	TicketLockType;
			typedef typename ThreadTrait::ItemContainer	ItemContainer;

			// internal aliasing
			//typedef typename ItemContainer::iterator ItemIterator;


			///////////////////////////////////////////////////////////////////////////////////////////////
			// Hash bucket
			class Bucket
			{
			public:
				// thread lock for bucket access
				TicketLockType	m_Lock;

			public:

				void ReadLock()
				{
					m_Lock.NonExLock();
				}

				void ReadUnlock()
				{
					m_Lock.NonExUnlock();
				}

				void WriteLock()
				{
					m_Lock.ExLock();
				}

				void WriteUnlock()
				{
					m_Lock.ExUnlock();
				}

				friend HashTable2;


			public:
				// Bucket item container
				ItemContainer	*m_Items;

				IHeap* m_Heap;

				// Constructor
				Bucket()
					: m_Heap(nullptr)
				{
					m_Items = nullptr;
				}

				// Copy Constructor 
				Bucket( const Bucket& src )
					: m_Heap(src.m_Heap)
				{
					m_Items = nullptr;
					(void)(src);
					// No one use this bucket, while this operation
					//Assert( !src.m_Lock.IsLocked() );
					Assert(false);
				}


				// Destructor
				~Bucket()
				{
					if (m_Items != nullptr) IHeap::Delete(m_Items);
				}

				Bucket& operator = ( const Bucket& src )
				{
					// No one use this bucket, while this operation
					Assert( !src.m_Lock.IsLocked() );
					Assert( !m_Lock.IsLocked() );

					//m_Items = src.m_Items;
					Assert(false);
					return *this;
				}

				Bucket& operator = ( Bucket&& src )
				{
					// No one use this bucket, while this operation
					Assert( !src.m_Lock.IsLocked() );
					Assert( !m_Lock.IsLocked() );

					//m_Items = src.m_Items;
					Assert(false);
					return *this;
				}

				void SetObjectPool(IHeap& memoryManager)
				{
					m_Heap = &memoryManager;
					if (m_Items) memoryManager.Delete(m_Items);
					m_Items = new(memoryManager) ItemContainer(memoryManager);
				}

				// validate bucket id
				bool Validate( size_t iMyBucket, size_t szNumBucket )
				{
					bool isSuccess = true;
					// Validate only debug mode
//#ifdef _DEBUG
//					std::atomic_thread_fence(std::memory_order_acquire);
//					m_Items->ForeachOrder(0, (uint)m_Items->size(), [](const KeyType& key, const ValueType& value) -> bool
//					{
//						size_t hashVal = HasherType()(key);
//						size_t iBucket = hashVal%szNumBucket;
//						AssertRel( iBucket == iMyBucket );
//						if( iBucket != iMyBucket )
//						{
//							isSuccess &= false;
//						}
//						return true;
//					});
//#endif
					return isSuccess;
				}
			};

			typedef std::vector<Bucket> BucketListType;
			typedef typename BucketListType::iterator BucketListIterator;




			//// Iterator
			//class iterator
			//{
			//public:


			//private:
			//	// Is Bucket internal iterator?, then only iterate inside bucket
			//	bool m_bIsIterInBucket;

			//	// Bucket list iterator. directing which bucket
			//	BucketListIterator m_itBucket;
			//	// in-bucket item iterator
			//	ItemIterator m_itItem;

			//	// Main container pointer
			//	HashTable			*m_pContainer;


			//	enum { END_IDX = -1 };

			//	// constructor
			//	iterator(HashTable *pContainer, const BucketListIterator& itBucket, const ItemIterator& itItem, bool bIsBucketIter = false)
			//		: m_bIsIterInBucket(bIsBucketIter)
			//		, m_itBucket(itBucket)
			//		, m_itItem(itItem)
			//		, m_pContainer(pContainer)
			//	{
			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end() && m_itItem != m_itBucket->m_Items.end())
			//			m_itBucket->ReadLock();
			//	}

			//	friend class HashTable2;


			//	void NextIter()
			//	{
			//		Assert(m_pContainer != nullptr);
			//		Assert(m_itBucket != m_pContainer->bucket_end());
			//		++m_itItem;
			//		if (m_itItem == m_itBucket->m_Items.end())
			//			return;

			//		if (m_bIsIterInBucket)
			//		{
			//			m_iIdx = m_itBucket->m_Items.end();
			//			m_itBucket = m_pContainer->bucket_end();
			//			return;
			//		}

			//		m_itBucket->ReadUnlock();
			//		m_itBucket++;
			//		while (m_itBucket != m_pContainer->bucket_end())
			//		{
			//			if (m_itBucket->m_Items.size() != 0)
			//			{
			//				m_itBucket->ReadLock();
			//				if (m_itBucket->m_Items.size() != 0)
			//				{
			//					m_itItem = m_itBucket->m_Items.begin();
			//					return;
			//				}
			//				// no item, move to next bucket
			//				m_itBucket->ReadUnlock();
			//			}
			//			m_itBucket++;
			//		}

			//		m_itItem = ItemIterator();
			//	}

			//	// set iter
			//	void Set(HashTable *pContainer, const BucketListIterator& itBucket, const ItemIterator& itItem, bool bIsLock = true, bool bIsBucketIter = false)
			//	{
			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end() && m_iIdx > END_IDX)
			//			m_itBucket->ReadUnlock();

			//		m_bIsIterInBucket = bIsBucketIter;
			//		m_pContainer = pContainer;
			//		m_itBucket = itBucket;
			//		m_itItem = itItem;

			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end() && m_itItem != m_itBucket->m_Items.end())
			//			m_itBucket->ReadLock();
			//	}

			//public:
			//	iterator()
			//		: m_bIsIterInBucket(false)
			//		, m_pContainer(nullptr)
			//	{
			//	}

			//	iterator(const iterator& src)
			//		: m_bIsIterInBucket(false)
			//		, m_itBucket(src.m_itBucket)
			//		, m_pContainer(src.m_pContainer)
			//		, m_itItem(src.m_itItem)
			//	{
			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end())
			//		{
			//			m_itBucket->ReadLock();
			//		}

			//	}

			//	~iterator()
			//	{
			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end())
			//			m_itBucket->ReadUnlock();
			//	}


			//	iterator& operator++()
			//	{
			//		NextIter();

			//		return *this;
			//	}

			//	const iterator& operator++() const
			//	{
			//		NextIter();

			//		return *this;
			//	}


			//	ItemType& operator* ()
			//	{
			//		AssertRel(m_pContainer != nullptr);
			//		m_pCache = m_itItem;
			//		return m_itItem->Data;
			//	}

			//	const ItemType& operator* () const
			//	{
			//		AssertRel(m_pContainer != nullptr);
			//		return m_itItem->Data;
			//	}

			//	ItemType& operator-> ()
			//	{
			//		AssertRel(m_pContainer != nullptr);
			//		return m_itItem->Data;
			//	}

			//	const ItemType& operator-> () const
			//	{
			//		AssertRel(m_pContainer != nullptr);
			//		return m_itItem->Data;
			//	}

			//	KeyType GetKey() const
			//	{
			//		return m_itItem->Key;
			//	}

			//	bool operator !=(const iterator& op) const
			//	{
			//		return ((m_pContainer != op.m_pContainer) || (m_itBucket != op.m_itBucket) || (m_itItem != op.m_itItem));
			//	}

			//	bool operator ==(const iterator& op) const
			//	{
			//		return ((m_pContainer == op.m_pContainer) && (m_itBucket == op.m_itBucket) && (m_itItem == op.m_itItem));
			//	}

			//	// Check validity
			//	bool IsValid()
			//	{
			//		return m_pContainer && m_itBucket != m_pContainer->bucket_end();
			//	}

			//	// reset iterator and make invalid
			//	void Reset()
			//	{
			//		*this = nullptr;
			//	}

			//	iterator& operator = (const iterator& op)
			//	{
			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end())
			//		{
			//			m_itBucket->ReadUnlock();
			//		}

			//		m_pContainer = op.m_pContainer;
			//		m_itBucket = op.m_itBucket;
			//		m_itItem = op.m_itItem;

			//		//// if some write lock occurred after op gain read lock then this case make Dead lock
			//		//// if you got this assert then use with another way
			//		//Assert( m_pContainer == nullptr || m_itBucket == m_pContainer->bucket_end() );
			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end())
			//		{
			//			m_itBucket->ReadLock();
			//		}

			//		return *this;
			//	}

			//	iterator& operator = (const void* pPtr)
			//	{
			//		Assert(pPtr == 0);

			//		if (m_pContainer && m_itBucket != m_pContainer->bucket_end())
			//		{
			//			m_itBucket->ReadUnlock();
			//			m_itBucket = m_pContainer->bucket_end();
			//		}

			//		m_pContainer = nullptr;
			//		m_itItem = ItemIterator();

			//		// if some write lock occurred after op gain read lock then this case make Dead lock
			//		// if you got this assert then use with another way
			//		Assert(m_pContainer == nullptr || m_itBucket == m_pContainer->bucket_end());

			//		return *this;
			//	}
			//};


		private:

			IHeap& m_Heap;

			// bucket
			std::vector<Bucket> m_Buckets;

			// total count of item
			SyncCounter		m_lItemCount;

		public:

			HashTable2( IHeap& memoryManager, INT iBucketCount = 16)
				: m_Heap(memoryManager)
				, m_lItemCount(0)
			{
				SetBucketCount(iBucketCount);
			}

			virtual ~HashTable2()
			{
			}

			CounterType size()								{ return m_lItemCount.load(std::memory_order_relaxed); }

			// resize bucket
			// NOTE: This method is NOT THREAD SAFE and NOT DATA SAFE
			void SetBucketCount( size_t iBucketCount )
			{
				m_Buckets.resize( iBucketCount );
				for (uint iBucket = 0; iBucket < m_Buckets.size(); iBucket++)
				{
					m_Buckets[iBucket].SetObjectPool(m_Heap);
				}
			}

			// Bucket Count
			size_t GetBucketCount() const							{ return m_Buckets.size(); }

			BucketListIterator bucket_begin() { return m_Buckets.begin(); }
			BucketListIterator bucket_end() { return m_Buckets.end(); }


			//////////////////////////////////////////////////////////////////////////
			//
			//	Insert/erase/clear
			//

			Result Insert( const KeyType key, const ItemType &data )
			{
				size_t hashVal = HasherType()(key);
				size_t iBucket = hashVal%m_Buckets.size();

				Bucket& bucket = m_Buckets[iBucket];
				TicketScopeLockT<TicketLockType> scopeLock( TicketLock::LockMode::Exclusive, bucket.m_Lock );

				if(Trait::UniqueKey)
				{
					ItemType dataFound;
					if(ThreadTrait::ThreadSafe)
					{
						if ((bucket.m_Items->FindInWriteTree(key, dataFound)))
						{
							return ResultCode::FAIL;
						}
					}
					else
					{
						if ((bucket.m_Items->Find(key, dataFound)))
						{
							return ResultCode::FAIL;
						}
					}
				}
				bucket.m_Items->Insert(key, data);
				if(ThreadTrait::ThreadSafe)
				{
					bucket.m_Items->CommitChanges();
				}

				m_lItemCount.fetch_add(1,std::memory_order_relaxed);

#ifdef _DEBUG
				Assert( bucket.Validate(iBucket, m_Buckets.size()) );
#endif
				return ResultCode::SUCCESS;
			}

			Result insert(const KeyType key, const ItemType &data) { return Insert(key, data); }


			Result Find( const KeyType& keyVal, ItemType &data )
			{
				size_t hashVal = HasherType()( keyVal );
				size_t iBucket = hashVal%m_Buckets.size();

				Bucket& bucket = m_Buckets[iBucket];
				TicketScopeLockT<TicketLockType> scopeLock( TicketLock::LockMode::NonExclusive, bucket.m_Lock );

				Result hr = bucket.m_Items->Find(keyVal, data);

				return hr;
			}
			Result find(const KeyType& keyVal, ItemType &data) { return Find(keyVal, data); }

			// Erase a data from hash map
			Result Erase(const KeyType &key, ValueType& erasedValue)
			{
				if (m_Buckets.size() == 0)
					return ResultCode::SUCCESS_FALSE;

				size_t hashVal = HasherType()(key);
				size_t iBucket = hashVal%m_Buckets.size();

				Bucket& bucket = m_Buckets[iBucket];
				TicketScopeLockT<TicketLockType> scopeLock(TicketLock::LockMode::Exclusive, bucket.m_Lock);

				if ((bucket.m_Items->Remove(key, erasedValue)))
				{
					if(ThreadTrait::ThreadSafe)
					{
						bucket.m_Items->CommitChanges();
					}
					m_lItemCount.fetch_sub(1, std::memory_order_relaxed);
					return ResultCode::SUCCESS;
				}

				Assert(bucket.Validate(iBucket, m_Buckets.size()));

				return ResultCode::FAIL;
			}
			Result erase(const KeyType &key) { ValueType erasedValue;  return Erase(key, erasedValue); }
			Result erase(const KeyType &key, ValueType& erasedValue) { return Erase(key, erasedValue); }


			Result Clear()
			{
				m_lItemCount = 0;

				auto itBucket = m_Buckets.begin();
				for( ; itBucket != m_Buckets.end(); ++itBucket )
				{
					itBucket->m_Items->ClearMap();
				}

				return ResultCode::SUCCESS;
			}

			bool Validate()
			{
#ifdef _DEBUG
				BucketListType::iterator itBucket = m_Buckets.begin();
				for( INT iBucket = 0; itBucket != m_Buckets.end(); ++itBucket, ++iBucket )
				{
					if( !itBucket->Validate( iBucket, m_Buckets.size() ) )
						return false;
				}
#endif
				return true;
			}


			// Func(const KeyType& key, const ItemType& item)->bool
			template<class Functor> // (const KeyType& key, const ItemType& item)
			void for_each(Functor func)
			{
				auto itBucket = m_Buckets.begin();
				for (INT iBucket = 0; itBucket != m_Buckets.end(); ++itBucket, ++iBucket)
				{
					if (itBucket->m_Items == nullptr)
						continue;

					itBucket->m_Items->ForeachOrder(0, (uint)itBucket->m_Items->size(), func);
				}

			}
		};



} // namespace SF





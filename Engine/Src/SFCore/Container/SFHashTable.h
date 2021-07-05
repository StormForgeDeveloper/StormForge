////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
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
#include "Multithread/SFSynchronization.h"
#include "Container/SFContainerTrait.h"
#include "Container/SFArray.h"
#include "Container/SFContainerTrait.h"


namespace SF {



		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Thread safe hash map
		//

		template<	typename KeyType, typename ItemType, 
					typename Trait = UniqueKeyTrait, 
					typename ThreadTrait = ThreadSyncTraitReadWriteT<KeyType,ItemType>,
					typename Hasher = SF::hash<KeyType>,
					typename MapItemType = MapItem<KeyType, ItemType>,
					typename ItemContainer = std::vector<MapItemType> >
		class HashTable
		{
		public:

			typedef ItemType MyItemType;
			typedef KeyType MyKeyType;

			typedef typename ThreadTrait::TicketLockType	TicketLockType;


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

				friend HashTable;


			public:
				// Bucket item container
				ItemContainer	m_Items;


				// Constructor
				Bucket()
				{
				}

				// Copy Constructor 
				Bucket( const Bucket& src )
					:m_Items(src.m_Items)
				{
					// No one use this bucket, while this operation
					//Assert( !src.m_Lock.IsLocked() );
				}

				Bucket( Bucket&& src )
					:m_Items(src.m_Items)
				{
					// No one use this bucket, while this operation
					//Assert( !src.m_Lock.IsLocked() );
				}

				// Destructor
				~Bucket()
				{
				}

				Bucket& operator = ( const Bucket& src )
				{
					// No one use this bucket, while this operation
					Assert( !src.m_Lock.IsLocked() );
					Assert( !m_Lock.IsLocked() );

					m_Items = src.m_Items;
					return *this;
				}

				Bucket& operator = ( Bucket&& src )
				{
					// No one use this bucket, while this operation
					Assert( !src.m_Lock.IsLocked() );
					Assert( !m_Lock.IsLocked() );

					m_Items = src.m_Items;
					return *this;
				}

				// validate bucket id
				bool Validate( size_t iMyBucket, size_t szNumBucket )
				{
					// Validate only debug mode
#ifdef _DEBUG
					ItemContainer::iterator iter = m_Items.begin();
					for( ; iter != m_Items.end(); ++iter )
					{
						KeyType curIdx = iter->Key;
						size_t hashVal = Hasher()( curIdx );
						size_t iBucket = hashVal%szNumBucket;
						AssertRel( iBucket == iMyBucket );
						if( iBucket != iMyBucket )
						{
							return false;
						}
					}
#endif
					return true;
				}
			};

			// Bucket list container type
			using BucketListType = DynamicArray<Bucket>;


			///////////////////////////////////////////
			// Hash table iterator
			class iterator
			{
			public:
				enum { END_IDX = -1 };

			public:
				iterator()
					: m_bIsIterInBucket(false)
					, m_pContainer(nullptr)
					, m_iIdx(END_IDX)
				{
				}

				iterator( const iterator& src )
					: m_bIsIterInBucket(false)
					, m_iterBucket(src.m_iterBucket)
					, m_pContainer(src.m_pContainer)
					, m_iIdx(src.m_iIdx)
				{
					if( m_pContainer && m_iterBucket != m_pContainer->bucket_end() )
					{
						m_iterBucket->ReadLock();
					}

				}

				~iterator()
				{
					if( m_pContainer && m_iterBucket != m_pContainer->bucket_end() /*&& m_iIdx > END_IDX*/ )
						m_iterBucket->ReadUnlock();
				}


				iterator& operator++()
				{
					NextIter();

					return *this;
				}

				const iterator& operator++() const
				{
					NextIter();

					return *this;
				}


				ItemType& operator* ()
				{
					AssertRel(m_pContainer != nullptr);
					m_pCache = &m_iterBucket->m_Items[m_iIdx];
					return m_iterBucket->m_Items[m_iIdx].Data;
				}

				const ItemType& operator* () const
				{
					AssertRel(m_pContainer != nullptr);
					m_pCache = &m_iterBucket->m_Items[m_iIdx];
					return m_iterBucket->m_Items[m_iIdx].Data;
				}

				ItemType& operator-> ()
				{
					AssertRel(m_pContainer != nullptr);
					m_pCache = &m_iterBucket->m_Items[m_iIdx];
					return m_iterBucket->m_Items[m_iIdx].Data;
				}

				const ItemType& operator-> () const
				{
					AssertRel(m_pContainer != nullptr);
					m_pCache = &m_iterBucket->m_Items[m_iIdx];
					return m_iterBucket->m_Items[m_iIdx].Data;
				}

				KeyType GetKey() const
				{
					return m_iterBucket->m_Items[m_iIdx].Key;
				}

				bool operator !=( const iterator& op ) const
				{
					return ( (m_pContainer != op.m_pContainer) || (m_iterBucket != op.m_iterBucket) || (m_iIdx != op.m_iIdx) );
				}

				bool operator ==( const iterator& op ) const
				{
					return ( (m_pContainer == op.m_pContainer) && (m_iterBucket == op.m_iterBucket) && (m_iIdx == op.m_iIdx) );
				}

				// Check validity
				bool IsValid()
				{
					return m_pContainer && m_iterBucket != m_pContainer->bucket_end();
				}

				// reset iterator and make invalid
				void Reset()
				{
					*this = nullptr;
				}

				iterator& operator = (iterator&& op)
				{
					if (m_pContainer && m_iterBucket != m_pContainer->bucket_end())
					{
						m_iterBucket->ReadUnlock();
					}

					m_pContainer = op.m_pContainer;
					op.m_pContainer = nullptr;
					m_iterBucket = std::forward<typename BucketListType::iterator>(op.m_iterBucket);
					m_iIdx = op.m_iIdx; op.m_iIdx = END_IDX;

					return *this;
				}

				iterator& operator = ( const iterator& op )
				{
					if( m_pContainer && m_iterBucket != m_pContainer->bucket_end() )
					{
						m_iterBucket->ReadUnlock();
					}

					m_pContainer = op.m_pContainer;
					m_iterBucket = op.m_iterBucket;
					m_iIdx = op.m_iIdx;

					//// if some write lock occurred after op gain read lock then this case make Dead lock
					//// if you got this assert then use with another way
					//Assert( m_pContainer == nullptr || m_iterBucket == m_pContainer->bucket_end() );
					if( m_pContainer && m_iterBucket != m_pContainer->bucket_end() )
					{
						m_iterBucket->ReadLock();
					}

					return *this;
				}

				iterator& operator = ( const void* pPtr )
				{
					Assert( pPtr == 0 );

					if( m_pContainer && m_iterBucket != m_pContainer->bucket_end() )
					{
						m_iterBucket->ReadUnlock();
						m_iterBucket = m_pContainer->bucket_end();
					}

					m_pContainer = nullptr;
					m_iIdx = END_IDX;

					// if some write lock occurred after op gain read lock then this case make Dead lock
					// if you got this assert then use with another way
					Assert( m_pContainer == nullptr || m_iterBucket == m_pContainer->bucket_end() );

					return *this;
				}

			private:


				// constructor
				iterator(HashTable *pContainer, typename BucketListType::iterator iterBucket, INT iIdx, bool bIsBucketIter = false)
					: m_bIsIterInBucket(bIsBucketIter)
					, m_iterBucket(iterBucket)
					, m_pContainer(pContainer)
					, m_iIdx(iIdx)
				{
					m_pCache = nullptr;
					if (m_pContainer && m_iterBucket != m_pContainer->bucket_end() && m_iIdx > END_IDX)
						m_iterBucket->ReadLock();
				}

				friend class HashTable;


				void NextIter()
				{
					Assert(m_pContainer != nullptr);
					Assert(m_iterBucket != m_pContainer->bucket_end());
					Assert(m_iIdx >= 0);
					m_iIdx++;
					if (m_iIdx < (INT)m_iterBucket->m_Items.size())
						return;

					if (m_bIsIterInBucket)
					{
						m_iterBucket = m_pContainer->bucket_end();
						m_iIdx = END_IDX;
						return;
					}

					m_iterBucket->ReadUnlock();
					m_iterBucket++;
					while (m_iterBucket != m_pContainer->bucket_end())
					{
						if (m_iterBucket->m_Items.size() != 0)
						{
							m_iterBucket->ReadLock();
							if (m_iterBucket->m_Items.size() != 0)
							{
								m_iIdx = 0;
								return;
							}
							// failed search again
							m_iterBucket->ReadUnlock();
						}
						m_iterBucket++;
					}

					m_iIdx = END_IDX;
				}

				// set iter
				void Set(HashTable *pContainer, typename BucketListType::iterator iterBucket, INT iIdx, bool bIsLock = true, bool bIsBucketIter = false)
				{
					if (m_pContainer && m_iterBucket != m_pContainer->bucket_end() && m_iIdx > END_IDX)
						m_iterBucket->ReadUnlock();

					m_bIsIterInBucket = bIsBucketIter;
					m_pContainer = pContainer;
					m_iterBucket = iterBucket;
					m_iIdx = iIdx;

					if (bIsLock && m_pContainer && m_iterBucket != m_pContainer->bucket_end() && m_iIdx > END_IDX)
						m_iterBucket->ReadLock();
				}


			private:
				// Is Bucket internal iterator?, then only iterate inside bucket
				bool m_bIsIterInBucket = false;
				// Bucket list iterator. directing which bucket
				typename BucketListType::iterator m_iterBucket;
				// Main container pointer
				HashTable			*m_pContainer = nullptr;
				// Index in bucket container
				int					m_iIdx = -1;
				// MapItemType
				mutable MapItemType		*m_pCache = nullptr;

			};

		private:
			// bucket
			BucketListType m_Bucket;

			// total count of item
			std::atomic<int32_t>		m_lItemCount;

		public:

			HashTable( INT iBucketCount = 16 )
				: m_Bucket(GetSystemHeap())
				, m_lItemCount(0)
			{
				m_Bucket.resize( iBucketCount );
			}

			HashTable(IHeap& heap, INT iBucketCount = 16)
				: m_Bucket(heap)
				, m_lItemCount(0)
			{
				m_Bucket.resize(iBucketCount);
			}

			virtual ~HashTable()
			{
			}

			// resize bucket
			// NOTE: This method is NOT THREAD SAFE and NOT DATA SAFE
			void SetBucketCount( size_t iBucketCount )
			{
				m_Bucket.resize( iBucketCount );
			}

			// Bucket Count
			size_t GetBucketCount() const
			{
				return m_Bucket.size();
			}

			// Get bucket 
			const Bucket& GetBucket( size_t iBucket ) const
			{
				return m_Bucket[iBucket];
			}
			Bucket& GetBucket( size_t iBucket )
			{
				return m_Bucket[iBucket];
			}


			// Get bucket size, count of item in bucket
			size_t GetBucketSize( size_t iBucket ) const
			{
				return m_Bucket[iBucket].m_Items.size();
			}


			// bucket iterator
			typename BucketListType::iterator bucket_begin()
			{
				return m_Bucket.begin();
			}

			typename BucketListType::iterator bucket_end()
			{
				return m_Bucket.end();
			}

			// Iterator 
			Result begin( iterator &iter )
			{
				iter = begin();

				return iter.IsValid() ? ResultCode::SUCCESS : ResultCode::FAIL;
			}

			iterator begin()
			{
				auto iterBucket = m_Bucket.begin();
				iterator iter = end();
				for( ; iterBucket != m_Bucket.end(); ++iterBucket )
				{
					if( iterBucket->m_Items.size() > 0 )
					{
						iter.Set( this, iterBucket, 0 );
						return iter;
					}
				}

				return iter;
			}

			iterator end()
			{
				return iterator(this,m_Bucket.end(),iterator::END_IDX);
			}

			long size()
			{
				return m_lItemCount.load(std::memory_order_relaxed);
			}


			//////////////////////////////////////////////////////////////////////////
			//
			//	Insert/erase/clear
			//

			Result insert(const KeyType& inKey, const ItemType &data)
			{
				size_t hashVal = Hasher()( inKey );
				size_t iBucket = hashVal%m_Bucket.size();

				Bucket& bucket = m_Bucket[iBucket];
				TicketScopeLockT<TicketLockType> scopeLock( TicketLock::LockMode::Exclusive, bucket.m_Lock );
				//_ReadBarrier();
				std::atomic_thread_fence(std::memory_order_consume);

				MapItemType MapData;
				MapData.Key = inKey;
				MapData.Data = data;

				if constexpr (Trait::UniqueKey)
				{
					auto iter = bucket.m_Items.begin();
					for( ; iter != bucket.m_Items.end(); ++iter )
					{
						KeyType curIdx = iter->Key;
						if( equal_to<KeyType>()(inKey, curIdx) )
						{
							return ResultCode::FAIL;
						}
					}

					bucket.m_Items.push_back( MapData );
				}
				else
				{
					auto iter = bucket.m_Items.begin();
					bool bIsInserted = false;
					for( ; iter != bucket.m_Items.end(); ++iter )
					{
						KeyType curKey = iter->Key;
						if( equal_to<KeyType>()(inKey, curKey) )
						{
							bucket.m_Items.insert( iter, MapData );
							bIsInserted = true;
							break;
						}
					}
					if( !bIsInserted )
					{
						bucket.m_Items.push_back( MapData );
					}
				}

				m_lItemCount.fetch_add(1,std::memory_order_relaxed);

				//_WriteBarrier();
				std::atomic_thread_fence(std::memory_order_seq_cst);

#ifdef _DEBUG
				Assert( bucket.Validate(iBucket, m_Bucket.size()) );
#endif
				return ResultCode::SUCCESS;
			}

			Result emplace(const KeyType& inKey, const ItemType& data)
			{
				size_t hashVal = Hasher()(inKey);
				size_t iBucket = hashVal % m_Bucket.size();

				{ // Scope for the lock
					Bucket& bucket = m_Bucket[iBucket];
					TicketScopeLockT<TicketLockType> scopeLock(TicketLock::LockMode::NonExclusive, bucket.m_Lock);

					auto iter = bucket.m_Items.begin();
					for (; iter != bucket.m_Items.end(); ++iter)
					{
						if (equal_to<KeyType>()(inKey, iter->Key))
						{
							iter->Data = data;
							return ResultCode::SUCCESS;
						}
					}
				}

				// If we reach here it means we failed to find
				return insert(inKey, data);
			}

			Result find( const KeyType& keyVal, ItemType &data )
			{
				size_t hashVal = Hasher()( keyVal );
				size_t iBucket = hashVal%m_Bucket.size();

				Bucket& bucket = m_Bucket[iBucket];
				TicketScopeLockT<TicketLockType> scopeLock( TicketLock::LockMode::NonExclusive, bucket.m_Lock );

				auto iter = bucket.m_Items.begin();
				for( ; iter != bucket.m_Items.end(); ++iter )
				{
					if( equal_to<KeyType>()( keyVal, iter->Key ) )
					{
						data = iter->Data;
						return ResultCode::SUCCESS;
					}
				}

				return ResultCode::FAIL;
			}

			Result find( const KeyType& keyVal, iterator &iterData )
			{
				size_t hashVal = Hasher()( keyVal );
				size_t iBucket = hashVal%m_Bucket.size();

				Bucket& bucket = m_Bucket[iBucket];

				iterData = end();
				bucket.ReadLock();

				auto iter = bucket.m_Items.begin();
				for( INT iIdx = 0; iter != bucket.m_Items.end(); ++iter, ++iIdx )
				{
					if( equal_to<KeyType>()( keyVal, iter->Key ) )
					{
						iterData.Set( this, m_Bucket.begin() + iBucket, iIdx, false );
						return ResultCode::SUCCESS;
					}
				}

				bucket.ReadUnlock();
				return ResultCode::FAIL;
			}

			iterator find(const KeyType& keyVal)
			{
				size_t hashVal = Hasher()(keyVal);
				size_t iBucket = hashVal % m_Bucket.size();

				Bucket& bucket = m_Bucket[iBucket];

				iterator iterData = end();
				bucket.ReadLock();

				auto iter = bucket.m_Items.begin();
				for (INT iIdx = 0; iter != bucket.m_Items.end(); ++iter, ++iIdx)
				{
					if (equal_to<KeyType>()(keyVal, iter->Key))
					{
						iterData.Set(this, m_Bucket.begin() + iBucket, iIdx, false);
						// taking read lock with iterator
						return iterData;
					}
				}

				bucket.ReadUnlock();
				return std::forward<iterator>(iterData);
			}

			// Erase a data from hash map
			Result erase(const KeyType& inKey, const ItemType &data)
			{
				if( m_Bucket.size() == 0 )
					return ResultCode::SUCCESS_FALSE;

				size_t hashVal = Hasher()( inKey );
				size_t iBucket = hashVal%m_Bucket.size();

				Bucket& bucket = m_Bucket[iBucket];

				bucket.WriteLock();
				//_ReadBarrier();
				std::atomic_thread_fence(std::memory_order_consume);

				auto iter = bucket.m_Items.begin();
				for( ; iter != bucket.m_Items.end(); ++iter )
				{
					KeyType curIdx = iter->Key;
					if( equal_to<KeyType>()(inKey, curIdx) )
					{
						bucket.m_Items.erase( iter );
						m_lItemCount.fetch_sub(1,std::memory_order_relaxed);
						//_WriteBarrier();
						std::atomic_thread_fence(std::memory_order_seq_cst);
						bucket.WriteUnlock();
						return ResultCode::SUCCESS;
					}
				}

				Assert( bucket.Validate(iBucket, m_Bucket.size()) );
				bucket.WriteUnlock();

				return ResultCode::FAIL;
			}

			Result eraseByKey(const KeyType &key)
			{
				if (m_Bucket.size() == 0)
					return ResultCode::SUCCESS_FALSE;

				KeyType inKey = key;
				size_t hashVal = Hasher()(inKey);
				size_t iBucket = hashVal%m_Bucket.size();

				Bucket& bucket = m_Bucket[iBucket];

				bucket.WriteLock();
				//_ReadBarrier();
				std::atomic_thread_fence(std::memory_order_consume);

				auto iter = bucket.m_Items.begin();
				for (; iter != bucket.m_Items.end(); ++iter)
				{
					KeyType curIdx = iter->Key;
					if (equal_to<KeyType>()(inKey, curIdx))
					{
						bucket.m_Items.erase(iter);
						m_lItemCount.fetch_sub(1, std::memory_order_relaxed);
						//_WriteBarrier();
						std::atomic_thread_fence(std::memory_order_seq_cst);
						bucket.WriteUnlock();
						return ResultCode::SUCCESS;
					}
				}

				Assert(bucket.Validate(iBucket, m_Bucket.size()));
				bucket.WriteUnlock();

				return ResultCode::FAIL;
			}

			Result erase( iterator &iterData )
			{
				KeyType Key;
				if( iterData.m_pContainer != this )
					return ResultCode::FAIL;

				if( iterData.m_iterBucket == bucket_end() )
					return ResultCode::INVALID_ARG;

				if( iterData.m_iIdx <= iterator::END_IDX )
					return ResultCode::INVALID_ARG;

				//ItemType data = *iterData;
				INT iIdx = iterData.m_iIdx;

				// NOTE : if bucket size changed then this operation will not safe
				auto iterBucket = iterData.m_iterBucket;


				Key = iterData.GetKey();
#ifdef _DEBUG
				size_t iBucket = &(*iterData.m_iterBucket) - &m_Bucket[0];
				size_t hashVal1 = Hasher()( Key );
				size_t iBucketTem = hashVal1%m_Bucket.size();
				Assert( iBucket == iBucketTem );
#endif

				iterData = end();

				iterBucket->WriteLock();
				//_ReadBarrier();
				std::atomic_thread_fence(std::memory_order_consume);

				//bool bNotFound = true;
				if( iIdx >= (INT)iterBucket->m_Items.size()
					|| iterBucket->m_Items[iIdx].Key != Key)
				{
					// data not found. maybe erased?
					iterBucket->WriteUnlock();
					return ResultCode::FAIL;
				}
				auto iterBucketData = iterBucket->m_Items.begin() + iIdx;
#ifdef _DEBUG
				KeyType idx = iterBucketData->Key;//Indexer()(*iterBucketData);
				size_t hashVal2 = Hasher()( idx );
				size_t iBucketTem2 = hashVal2%m_Bucket.size();
				Assert(iBucket == iBucketTem2);
#endif
				//There is a narrow window before iterBucket is locked a new data is erased and added again. so it could be same data or not
				//if(data != datTempBackup)
				iterBucket->m_Items.erase(iterBucketData);

				m_lItemCount.fetch_sub(1, std::memory_order_relaxed);

				//_WriteBarrier();
				std::atomic_thread_fence(std::memory_order_seq_cst);
#ifdef _DEBUG
				Assert( iterBucket->Validate(iBucket, m_Bucket.size()) );
#endif
				iterBucket->WriteUnlock();

				return ResultCode::SUCCESS;
			}

			Result clear()
			{
				m_lItemCount = 0;

				auto iterBucket = m_Bucket.begin();
				for( ; iterBucket != m_Bucket.end(); ++iterBucket )
				{
					iterBucket->m_Items.clear();
				}

				return ResultCode::SUCCESS;
			}

			bool Validate()
			{
#ifdef _DEBUG
				auto iterBucket = m_Bucket.begin();
				for( INT iBucket = 0; iterBucket != m_Bucket.end(); ++iterBucket, ++iBucket )
				{
					if( !iterBucket->Validate( iBucket, m_Bucket.size() ) )
						return false;
				}
#endif
				return true;
			}
		};


} // namespace SF





////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Sorted set
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "MemoryManager/SFMemoryManager.h"


namespace SF {


	class IHeap;

	///////////////////////////////////////////////////////////
	//
	//	SortedSet
	//	- Implementation of sorted vector array
	//

	template<class KeyType>
	class SortedSet
	{
	public:

		// value iterator
		class Iterator
		{
		private:

			// Container
			const SortedSet<KeyType>*  m_Container;

			mutable int           m_CurrentIndex;

			// used when m_CurrentIndex or m_Container is invalid
			bool m_ValidKey;
			KeyType m_KeyValue;

		private:
			Iterator(const SortedSet<KeyType>* container, int currentIndex);
			Iterator(const SortedSet<KeyType>* container, const KeyType& key);

			friend class SortedSet;

		public:
			Iterator();
			Iterator(const Iterator& src);

			bool IsValid() const;

			KeyType GetKey() const;

			KeyType operator * () { return GetKey(); }
			KeyType operator * () const { return GetKey(); }

            KeyType operator -> () { return GetKey(); }

			operator KeyType() { return GetKey(); }
			operator KeyType() const { return GetKey(); }

			// compare item
			bool operator == (const Iterator& op);
			bool operator != (const Iterator& op);

			// move to next item
			Iterator& operator ++();
			const Iterator& operator ++() const;
			Iterator& operator ++(int);
			const Iterator& operator ++(int) const;

			Iterator& operator = (const Iterator& src);
			// Insert/Set operation
		};

	private:

		IHeap& m_Heap;

		// Use buffer
		bool m_ExternalBuffer;

		// item count
		size_t m_ItemCount;

		// Increase size
		size_t m_IncreaseSize;

		// Allocated item count
		size_t m_AllocatedItemCount;

		// key
		KeyType* m_KeyArray;


	public:

		SortedSet();
		SortedSet(IHeap& heap, int initialCapacity = 0, int increaseSize = 16);
		SortedSet(IHeap& heap, int bufferSize, uint8_t* buffer);
		~SortedSet();

		void SetIncreaseSize(int newSize) { m_IncreaseSize = newSize; }
		int GetIncreaseSize() const { return m_IncreaseSize; }

		int GetAllocatedItemCount() const { return m_AllocatedItemCount; }
		size_t size() const { return m_ItemCount; }

		bool Contains(const KeyType& keyValue);

		// Clear array
		void Clear();

		// resize allocated buffer
		bool ResizeBuffer(size_t newSize);

		// resize
		bool resize(size_t newSize, bool dropLow = false);

		KeyType GetKeyAt(int64_t index) const;

		// Insert a key
		Result Insert(const KeyType& key, int64_t *insertedOrder = nullptr);
		Result insert(const KeyType& key, int64_t *insertedOrder = nullptr) { return Insert(key, insertedOrder); }

		Result Set(const KeyType& key, int64_t *insertedOrder = nullptr);

		// Remove an item and return the removed value
		Result Remove(const KeyType& key);

		// Find a key value
		Result Find(const KeyType& key, int64_t *pOrder = nullptr) const;

		Iterator operator[](const KeyType& key);

		// enumerate the values
		template<class Func>
		Result ForeachOrder(INT startOrderIndex, uint count, Func functor)
		{
			int iIndex = startOrderIndex;
			for (uint visitedCount = 0; visitedCount < count && iIndex < (int)m_ItemCount; visitedCount++, iIndex++)
			{
				functor(m_KeyArray[iIndex]);
			}
			return ResultCode::SUCCESS;
		}

		template<class Func>
		Result ForeachReverseOrder(INT startOrderIndex, uint count, Func functor)
		{
			int iIndex = std::min(m_ItemCount - startOrderIndex, decltype(m_ItemCount)(0));
			for (uint visitedCount = 0; visitedCount < count && iIndex >= 0; visitedCount++, iIndex--)
			{
				functor(m_KeyArray[iIndex]);
			}
			return ResultCode::SUCCESS;
		}

		// for interface match
		Result CommitChanges() { return ResultCode::SUCCESS; }

		const Iterator begin() const;
		Iterator begin();

		const Iterator end() const;
		Iterator end();

	private:

		// find parent node or candidate
		bool FindIndex(const KeyType& key, int& index) const;

		Result AddInternal(int index, const KeyType& keyValue);
	};


}

#include "SFSortedSet.inl"

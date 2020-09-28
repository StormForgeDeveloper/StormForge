////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Sorted vector array
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryManager.h"


namespace SF {


	class IHeap;

	///////////////////////////////////////////////////////////
	//
	//	SortedArray
	//	- Implementation of sorted vector array
	//

	template<class KeyType, class ValueType, bool UseUniqueKey = true, bool UseBulkCopy = true>
	class SortedArray
	{
	public:

		// value iterator
		class Iterator
		{
		private:

			// Container
			mutable SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>*  m_Container = nullptr;

			mutable int           m_CurrentIndex = -1;

			// used when m_CurrentIndex or m_Container is invalid
			bool m_ValidKey = false;
			KeyType m_KeyValue{};

		private:
			Iterator(SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>* container, int currentIndex);
			//Iterator(SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>* container, const KeyType& key);

			// Set key value only so that it can be used for insert operation
			void SetKey(const KeyType& key);

			friend class SortedArray;

		public:
			Iterator();
			Iterator(const Iterator& src);

			bool IsValid() const;

			int GetIndex() const { return m_CurrentIndex; }
			const KeyType& GetKey() const;
			const ValueType& GetValue() const;
			ValueType& GetValue();

			const ValueType* operator -> () { return &GetValue(); }
			const ValueType* operator -> () const { return &GetValue(); }
			Iterator& operator * () { return *this; }
			Iterator& operator * () const { return *this; }

			// compare item
			bool operator == (const Iterator& op);

			// move to next item
			Iterator& operator ++();
			const Iterator& operator ++() const;
			Iterator& operator ++(int);
			const Iterator& operator ++(int) const;

			Iterator& operator = (const Iterator& src);
			// Insert/Set operation
			Iterator& operator = (const ValueType& newValue);

			bool operator != (const Iterator& src) const;
			bool operator == (const Iterator& src) const;
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

		// values
		ValueType* m_ValueArray;

	public:

		//SortedArray(IHeap& heap);
		SortedArray(IHeap& heap, int initialCapacity = 0, int increaseSize = 16);
		SortedArray(IHeap& heap, int bufferSize, uint8_t* buffer);
		~SortedArray();

		IHeap& GetHeap() { return m_Heap; }

		void SetIncreaseSize(int newSize) { m_IncreaseSize = newSize; }
		int GetIncreaseSize() const { return m_IncreaseSize; }

		int GetAllocatedItemCount() const { return m_AllocatedItemCount; }
		size_t size() const { return m_ItemCount; }

		// Check if key exists
		bool Contains(const KeyType& keyValue);

		// Clear array
		void Clear();

		// reserve buffer for insert
		bool reserve(size_t newAllocationSize);

		// resize allocated buffer
		// deprecated
		bool ResizeBuffer(size_t newSize);

		// resize
		bool resize(size_t newSize, bool dropLow = false);

		// Get key or value at
		const KeyType& GetKeyAt(int64_t index) const;
		ValueType& GetValueAt(int64_t index);
		const ValueType& GetValueAt(int64_t index) const;

		// Insert a key
		Result Insert(const KeyType& key, const ValueType& value, int64_t *insertedOrder = nullptr);

		// Set a key/value 
		Result Set(const KeyType& key, const ValueType& value, int64_t *insertedOrder = nullptr);

		// Remove an item and return the removed value
		Result Remove(const KeyType& key, ValueType& value);

		// Find a key value
		Result Find(const KeyType& key, ValueType& value, int64_t *pOrder = nullptr) const;
		Result find(const KeyType& key, ValueType& value, int64_t *pOrder = nullptr) const { return Find(key, value, pOrder); }
		ValueType find(const KeyType& key) const { ValueType value{};  Find(key, value); return value; }

		Iterator operator[](const KeyType& key);

		// enumerate the values
		template<class Func>
		Result ForeachOrder(INT startOrderIndex, uint count, Func functor)
		{
			int iIndex = startOrderIndex;
			for (uint visitedCount = 0; visitedCount < count && iIndex < (int)m_ItemCount; visitedCount++, iIndex++)
			{
				functor(m_KeyArray[iIndex], m_ValueArray[iIndex]);
			}
			return ResultCode::SUCCESS;
		}

		template<class Func>
		Result ForeachReverseOrder(INT startOrderIndex, uint count, Func functor)
		{
			int iIndex = std::min(m_ItemCount - startOrderIndex, decltype(m_ItemCount)(0));
			for (uint visitedCount = 0; visitedCount < count && iIndex >= 0; visitedCount++, iIndex--)
			{
				functor(m_KeyArray[iIndex], m_ValueArray[iIndex]);
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

		void SetValue(int index, const ValueType& value);


		Result AddInternal(int index, const KeyType& keyValue, const ValueType& value);
	};


}

#include "SFSortedArray.inl"

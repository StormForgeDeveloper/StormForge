////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Sorted Set
//
////////////////////////////////////////////////////////////////////////////////


namespace SF {


		template<class KeyType>
		SortedSet<KeyType>::Iterator::Iterator(const SortedSet<KeyType>* container, int currentIndex)
			: m_Container(container)
			, m_CurrentIndex(currentIndex)
			, m_ValidKey(false)
		{
		}

		template<class KeyType>
		SortedSet<KeyType>::Iterator::Iterator(const SortedSet<KeyType>* container, const KeyType& key)
			: m_Container(container)
			, m_CurrentIndex(-1)
			, m_ValidKey(true)
			, m_KeyValue(key)
		{

		}

		template<class KeyType>
		SortedSet<KeyType>::Iterator::Iterator()
			: m_Container(nullptr)
			, m_CurrentIndex(-1)
			, m_ValidKey(false)
//			, m_KeyValue(0)
		{
		}

		template<class KeyType>
		SortedSet<KeyType>::Iterator::Iterator(const Iterator& src)
			: m_Container(src.m_Container)
			, m_CurrentIndex(src.m_CurrentIndex)
			, m_ValidKey(src.m_ValidKey)
			, m_KeyValue(src.m_KeyValue)
		{
		}

		template<class KeyType>
		bool SortedSet<KeyType>::Iterator::IsValid() const
		{
			return m_Container != nullptr
				&& m_CurrentIndex >= 0
				&& m_CurrentIndex < (decltype(m_CurrentIndex))m_Container->size();
		}

		template<class KeyType>
		KeyType SortedSet<KeyType>::Iterator::GetKey() const
		{
			if (!IsValid())
			{
				return m_KeyValue;
			}

			return m_Container->GetKeyAt(m_CurrentIndex);
		}

		template<class KeyType>
		bool SortedSet<KeyType>::Iterator::operator == (const Iterator& op)
		{
			return m_Container == op.m_Container
				&& m_CurrentIndex == op.m_CurrentIndex;
		}

		template<class KeyType>
		bool SortedSet<KeyType>::Iterator::operator != (const Iterator& op)
		{
			return m_Container != op.m_Container
				|| m_CurrentIndex != op.m_CurrentIndex;
		}

		template<class KeyType>
		typename SortedSet<KeyType>::Iterator& SortedSet<KeyType>::Iterator::operator ++()
		{
			if (!IsValid()) return *this;

			m_CurrentIndex++;
			if (m_CurrentIndex >= (decltype(m_CurrentIndex))m_Container->size())
			{
				m_Container = nullptr;
				m_CurrentIndex = -1;
			}

			return *this;
		}

		template<class KeyType>
		const typename SortedSet<KeyType>::Iterator& SortedSet<KeyType>::Iterator::operator ++() const
		{
			if (!IsValid()) return *this;

			m_CurrentIndex++;
			if (m_CurrentIndex >= (decltype(m_CurrentIndex))m_Container->size())
			{
				m_Container = nullptr;
				m_CurrentIndex = -1;
			}

			return *this;
		}

		template<class KeyType>
		typename SortedSet<KeyType>::Iterator& SortedSet<KeyType>::Iterator::operator ++(int inc)
		{
			unused(inc);
			Iterator it(*this);
			return ++it;
		}

		template<class KeyType>
		const typename SortedSet<KeyType>::Iterator& SortedSet<KeyType>::Iterator::operator ++(int inc) const
		{
			unused(inc);
			const Iterator it(*this);
			return ++it;
		}

		template<class KeyType>
		typename SortedSet<KeyType>::Iterator& SortedSet<KeyType>::Iterator::operator = (const Iterator& src)
		{
			m_Container = src.m_Container;
			m_CurrentIndex = src.m_CurrentIndex;

			return *this;
		}


		template<class KeyType>
		SortedSet<KeyType>::SortedSet()
			: m_Heap(GetSystemHeap())
			, m_ExternalBuffer(false)
			, m_ItemCount(0)
			, m_IncreaseSize(16)
			, m_AllocatedItemCount(0)
			, m_KeyArray(nullptr)
		{
		}

		template<class KeyType>
		SortedSet<KeyType>::SortedSet(IHeap& heap, int initialCapacity, int increaseSize)
			: m_Heap(heap)
			, m_ExternalBuffer(false)
			, m_ItemCount(0)
			, m_IncreaseSize(increaseSize)
			, m_AllocatedItemCount(0)
			, m_KeyArray(nullptr)
		{
			if (initialCapacity > 0)
			{
				ResizeBuffer(initialCapacity);
			}
		}

		template<class KeyType>
		SortedSet<KeyType>::SortedSet(IHeap& heap, int bufferSize, uint8_t* buffer)
			: m_Heap(heap)
			, m_ExternalBuffer(true)
			, m_ItemCount(0)
			, m_IncreaseSize(0)
			, m_AllocatedItemCount(0)
			, m_KeyArray(nullptr)
		{
			assert(bufferSize > (sizeof(KeyType)) && buffer != nullptr);
			m_AllocatedItemCount = bufferSize / (sizeof(KeyType));
			m_KeyArray = (KeyType*)buffer;
		}

		template<class KeyType>
		SortedSet<KeyType>::~SortedSet()
		{
			if (!m_ExternalBuffer)
			{
				if (m_KeyArray != nullptr) m_Heap.Free(m_KeyArray);
			}
		}


		// Clear array
		template<class KeyType>
		void SortedSet<KeyType>::Clear()
		{
			m_ItemCount = 0;
		}


		template<class KeyType>
		bool SortedSet<KeyType>::ResizeBuffer(size_t newSize)
		{
			if (m_KeyArray != nullptr)
			{
				KeyType* newKeyArray = (KeyType*)m_Heap.Realloc(m_KeyArray, newSize * sizeof(KeyType));
				if (newKeyArray != nullptr)
				{
					m_KeyArray = newKeyArray;
					memset(m_KeyArray + m_AllocatedItemCount, 0, (newSize - m_AllocatedItemCount) * sizeof(KeyType));
				}
				else
					return false; // failed to realloc
			}
			else
			{
				m_KeyArray = (KeyType*)m_Heap.Alloc(newSize * sizeof(KeyType));
				memset(m_KeyArray, 0, newSize * sizeof(KeyType));
			}

			m_AllocatedItemCount = newSize;

			// Truncate remain
			if (m_ItemCount > newSize)
				m_ItemCount = newSize;

			return true;
		}



		// resize
		template<class KeyType>
		bool SortedSet<KeyType>::resize(size_t newSize, bool dropLow)
		{
			// if need to increase size
			if (newSize >= size())
			{
				return ResizeBuffer(newSize);
			}

			// shrinking
			if (dropLow)
			{
				size_t shrinkSize = m_ItemCount - newSize;
				memmove(m_KeyArray, m_KeyArray + shrinkSize, sizeof(KeyType) * shrinkSize);
			}
			else
			{
				// nothing need to do
			}

			m_ItemCount = newSize;

			return true;
		}

		template<class KeyType>
		KeyType SortedSet<KeyType>::GetKeyAt(int64_t index) const
		{
			if (index < 0 || index >= (int64_t)m_ItemCount)
				return KeyType{};

			return m_KeyArray[index];
		}


		template<class KeyType>
		Result SortedSet<KeyType>::AddInternal(int index, const KeyType& keyValue)
		{
			// increase size if it's small
			if (m_AllocatedItemCount <= m_ItemCount)
			{
				if (m_IncreaseSize <= 0)
				{
					// increasing array size isn't allowed
					assert(false);
					return false;
				}

				if (!ResizeBuffer(m_AllocatedItemCount + m_IncreaseSize)) return ResultCode::OUT_OF_MEMORY;
			}

			if (m_ItemCount > 0)
			{
				memmove(m_KeyArray + index + 1, m_KeyArray + index, sizeof(KeyType) * (m_ItemCount - index));
			}
			else
			{
				index = 0;
			}

			m_KeyArray[index] = keyValue;
			m_ItemCount++;

			return ResultCode::SUCCESS;
		}

		// Insert a key
		template<class KeyType>
		Result SortedSet<KeyType>::Insert(const KeyType& key, int64_t *insertedOrder)
		{
			int index = -1;
			if (FindIndex(key, index))
			{
				//if (UseUniqueKey)
				{
					return ResultCode::FAIL;
				}
			}

			AddInternal(index, key);
			if (insertedOrder != nullptr) *insertedOrder = index;

			return ResultCode::SUCCESS;
		}

		// Insert a key
		template<class KeyType>
		Result SortedSet<KeyType>::Set(const KeyType& key, int64_t *insertedOrder)
		{
			int index = -1;
			if (FindIndex(key, index))
			{
				
			}
			else
			{
				AddInternal(index, key);
			}
			if (insertedOrder != nullptr) *insertedOrder = index;

			return ResultCode::SUCCESS;
		}

		// Remove an item and return the removed value
		template<class KeyType>
		Result SortedSet<KeyType>::Remove(const KeyType& key)
		{
			int index = -1;
			if (!FindIndex(key, index))
			{
				return ResultCode::FAIL;
			}

			if (m_ItemCount <= 0) return ResultCode::FAIL;

			m_ItemCount--;
			if (m_ItemCount > 0)
			{
				memmove(m_KeyArray + index, m_KeyArray + index + 1, sizeof(KeyType) * (m_ItemCount - index));
			}
			else
			{
				m_KeyArray[index] = KeyType{};
			}

			return ResultCode::SUCCESS;
		}

		// Find a key value
		template<class KeyType>
		Result SortedSet<KeyType>::Find(const KeyType& key, int64_t *pOrder) const
		{
			int index = -1;
			if (!FindIndex(key, index))
			{
				return ResultCode::FAIL;
			}

			if (pOrder != nullptr) *pOrder = index;

			return ResultCode::SUCCESS;
		}

		template<class KeyType>
		typename SortedSet<KeyType>::Iterator SortedSet<KeyType>::operator[](const KeyType& key)
		{
			int index = -1;
			if (!FindIndex(key, index))
			{
				return Iterator(this, key);
			}

			return Iterator(this, index);
		}

		// Find a key value
		template<class KeyType>
		bool SortedSet<KeyType>::Contains(const KeyType& key)
		{
			int index = -1;
			return FindIndex(key, index);
		}

		template<class KeyType>
		const typename SortedSet<KeyType>::Iterator SortedSet<KeyType>::begin() const
		{
			if(m_ItemCount > 0)
				return Iterator(this, 0);

			return Iterator();
		}

		template<class KeyType>
		typename SortedSet<KeyType>::Iterator SortedSet<KeyType>::begin()
		{
			if (m_ItemCount > 0)
				return Iterator(this, 0);

			return Iterator();
		}

		template<class KeyType>
		const typename SortedSet<KeyType>::Iterator SortedSet<KeyType>::end() const
		{
			return Iterator();
		}

		template<class KeyType>
		typename SortedSet<KeyType>::Iterator SortedSet<KeyType>::end()
		{
			return Iterator();
		}

		// find index of the object or insertion index
		template<class KeyType>
		bool SortedSet<KeyType>::FindIndex(const KeyType& keyValue, int& index) const
		{
			int Low = 0;
			int High = (int)m_ItemCount;

			// simple binary search
			while (Low < High)
			{
				int Mid = (Low + High) >> 1;
				if (m_KeyArray[Mid] > keyValue)
				{
					High = Mid;
				}
				else if (m_KeyArray[Mid] < keyValue)
				{
					Low = Mid + 1;
				}
				else
				{
					index = Mid;
					return true;
				}
			}

			if (Low == High)
			{
				index = Low;
			}
			else
			{
				index = Low + 1;
			}

			return false;
		}

}


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Sorted array
//
////////////////////////////////////////////////////////////////////////////////


namespace SF {


		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::Iterator(SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>* container, int currentIndex)
			: m_Container(container)
			, m_CurrentIndex(currentIndex)
			, m_ValidKey(false)
		{
		}

		//template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		//SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::Iterator(SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>* container, const KeyType& key)
		//	: m_Container(container)
		//	, m_CurrentIndex(-1)
		//	, m_ValidKey(true)
		//	, m_KeyValue(key)
		//{

		//}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::Iterator()
		{
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::Iterator(const Iterator& src)
			: m_Container(src.m_Container)
			, m_CurrentIndex(src.m_CurrentIndex)
			, m_ValidKey(src.m_ValidKey)
			, m_KeyValue(src.m_KeyValue)
		{
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		void SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator::SetKey(const KeyType& key)
		{
			m_ValidKey = true;
			m_KeyValue = key;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::IsValid() const
		{
			return m_Container != nullptr
				&& m_CurrentIndex >= 0
				&& m_CurrentIndex < (decltype(m_CurrentIndex))m_Container->size();
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const KeyType& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::GetKey() const
		{
			if (!IsValid())
			{
				return m_KeyValue;
			}

			return m_Container->GetKeyAt(m_CurrentIndex);
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const ValueType& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::GetValue() const
		{
			static ValueType DummyValue{};
			if (!IsValid())
			{
				assert(m_Container != nullptr && m_CurrentIndex >= 0 && m_CurrentIndex < (int)m_Container->size());
				return DummyValue;
			}

			return m_Container->GetValueAt(m_CurrentIndex);
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		ValueType& SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator::GetValue()
		{
			static ValueType DummyValue{};
			if (!IsValid())
			{
				assert(m_Container != nullptr && m_CurrentIndex >= 0 && m_CurrentIndex < (int)m_Container->size());
				return DummyValue;
			}

			return m_Container->GetValueAt(m_CurrentIndex);
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator == (const Iterator& op)
		{
			return m_Container == op.m_Container
				&& m_CurrentIndex == op.m_CurrentIndex;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		typename SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator ++()
		{
			if (!IsValid()) return *this;

			m_CurrentIndex++;
			if (m_CurrentIndex >= (int)m_Container->size())
			{
				m_Container = nullptr;
				m_CurrentIndex = -1;
			}

			return *this;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const typename SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator ++() const
		{
			if (!IsValid()) return *this;

			m_CurrentIndex++;
			if (m_CurrentIndex >= m_Container->size())
			{
				m_Container = nullptr;
				m_CurrentIndex = -1;
			}

			return *this;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		typename SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator ++(int inc)
		{
			unused(inc);
			Iterator it(*this);
			return ++it;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const typename SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator ++(int inc) const
		{
			unused(inc);
			const Iterator it(*this);
			return ++it;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		typename SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator = (const Iterator& src)
		{
			m_Container = src.m_Container;
			m_CurrentIndex = src.m_CurrentIndex;

			return *this;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		typename SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator = (const ValueType& newValue)
		{
			if (!IsValid())
			{
				assert(m_ValidKey);
				if (!m_ValidKey) return *this;

				m_Container->Replace(m_KeyValue, newValue, &m_CurrentIndex);

				return *this;
			}

			m_Container->SetValue(m_CurrentIndex, newValue);

			return *this;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator != (const Iterator& src) const
		{
			return m_Container != src.m_Container || m_CurrentIndex != src.m_CurrentIndex;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator::operator == (const Iterator& src) const
		{
			return m_Container == src.m_Container && m_CurrentIndex == src.m_CurrentIndex;
		}


		//template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		//SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::SortedArray(IHeap& heap)
		//	: m_Heap(heap)
		//	, m_ExternalBuffer(false)
		//	, m_ItemCount(0)
		//	, m_IncreaseSize(0)
		//	, m_AllocatedItemCount(0)
		//	, m_KeyArray(nullptr)
		//	, m_ValueArray(nullptr)
		//{
		//}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::SortedArray(IHeap& heap, int initialCapacity, int increaseSize)
			: m_Heap(heap)
			, m_ExternalBuffer(false)
			, m_ItemCount(0)
			, m_IncreaseSize(increaseSize)
			, m_AllocatedItemCount(0)
			, m_KeyArray(nullptr)
			, m_ValueArray(nullptr)
		{
			if (initialCapacity > 0)
			{
				ResizeBuffer(initialCapacity);
			}
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::SortedArray(IHeap& heap, int bufferSize, uint8_t* buffer)
			: m_Heap(heap)
			, m_ExternalBuffer(true)
			, m_ItemCount(0)
			, m_IncreaseSize(0)
			, m_AllocatedItemCount(0)
			, m_KeyArray(nullptr)
			, m_ValueArray(nullptr)
		{
			assert(bufferSize > (sizeof(KeyType) + sizeof(ValueType)) && buffer != nullptr);
			m_AllocatedItemCount = bufferSize / (sizeof(KeyType) + sizeof(ValueType));
			m_KeyArray = (KeyType*)buffer;
			m_ValueArray = (ValueType*)(m_KeyArray + m_AllocatedItemCount);
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::~SortedArray()
		{
			if (!m_ExternalBuffer)
			{
				GetHeap().Free(m_KeyArray);
				GetHeap().Free(m_ValueArray);
				m_KeyArray = nullptr;
				m_ValueArray = nullptr;
			}
		}

		// Clear array
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		void SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Clear()
		{
			auto defaultValue = ValueType{};
			for (size_t iItem = 0; iItem < m_ItemCount; iItem++)
			{
				m_ValueArray[iItem] = defaultValue;
			}
			m_ItemCount = 0;
		}


		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::reserve(size_t newAllocationSize)
		{
			if (m_AllocatedItemCount >= newAllocationSize)
				return true;

			if (m_KeyArray != nullptr)
			{
				KeyType* newKeyArray = (KeyType*)m_Heap.Realloc(m_KeyArray, newAllocationSize * sizeof(KeyType));
				if (newKeyArray != nullptr)
				{
					m_KeyArray = newKeyArray;
				}
				else
					return false; // failed to realloc

				ValueType* newValueArray = (ValueType*)m_Heap.Realloc(m_ValueArray, newAllocationSize * sizeof(ValueType));
				if (newValueArray != nullptr)
				{
					m_ValueArray = newValueArray;
				}
				else
					return false; // failed to realloc
			}
			else
			{
				m_KeyArray = (KeyType*)m_Heap.Alloc(newAllocationSize * sizeof(KeyType));
				m_ValueArray = (ValueType*)m_Heap.Alloc(newAllocationSize * sizeof(ValueType));
			}

			m_AllocatedItemCount = newAllocationSize;

			return true;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::ResizeBuffer(size_t newSize)
		{
			if (m_KeyArray != nullptr)
			{
				KeyType* newKeyArray = (KeyType*)m_Heap.Realloc(m_KeyArray, newSize * sizeof(KeyType));
				if (newKeyArray != nullptr)
				{
					m_KeyArray = newKeyArray;
				}
				else
					return false; // failed to realloc

				ValueType* newValueArray = (ValueType*)m_Heap.Realloc(m_ValueArray, newSize * sizeof(ValueType));
				if (newValueArray != nullptr)
				{
					m_ValueArray = newValueArray;
				}
				else
					return false; // failed to realloc
			}
			else
			{
				m_KeyArray = (KeyType*)m_Heap.Alloc(newSize * sizeof(KeyType));
				m_ValueArray = (ValueType*)m_Heap.Alloc(newSize * sizeof(ValueType));
			}

			m_AllocatedItemCount = newSize;

			// Truncate remain
			if (m_ItemCount > newSize)
				m_ItemCount = newSize;

			return true;
		}


		// resize
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::resize(size_t newSize, bool dropLow)
		{
			// if need to increase size
			if (newSize >= size())
			{
				return ResizeBuffer(newSize);
			}

			// shrinking
			size_t shrinkSize = m_ItemCount - newSize;
			if (dropLow)
			{
				if (UseBulkCopy)
				{
					memmove(m_KeyArray, m_KeyArray + shrinkSize, sizeof(KeyType) * shrinkSize);
					memmove(m_ValueArray, m_ValueArray + shrinkSize, sizeof(ValueType) * shrinkSize);
				}
				else
				{
					uint iPos = 0;
					for (; iPos < shrinkSize; iPos++)
					{
						m_KeyArray[iPos] = std::forward<KeyType>(m_KeyArray[iPos + shrinkSize]);
						m_ValueArray[iPos] = std::forward<ValueType>(m_ValueArray[iPos + shrinkSize]);
					}

					for (; iPos < m_ItemCount; iPos++)
					{
						m_KeyArray[iPos] = KeyType{};
						m_ValueArray[iPos] = ValueType{};
					}
				}
			}
			else
			{
				if (UseBulkCopy)
				{
					memset(m_KeyArray + newSize, 0, sizeof(KeyType) * shrinkSize);
					memset(m_ValueArray + newSize, 0, sizeof(ValueType) * shrinkSize);
				}
				else
				{
					for (uint iPos = (uint)newSize; iPos < m_ItemCount; iPos++)
					{
						m_KeyArray[iPos] = KeyType{};
						m_ValueArray[iPos] = ValueType{};
					}
				}
			}

			m_ItemCount = newSize;

			return true;
		}



		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const KeyType& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::GetKeyAt(int64_t index) const
		{
			static KeyType DummyValue{};
			if (index < 0 || index >= (int64_t)m_ItemCount)
				return DummyValue;

			return m_KeyArray[index];
		}


		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		ValueType& SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::GetValueAt(int64_t index)
		{
			static ValueType DummyValue{};
			if (index < 0 || index >= (decltype(index))m_ItemCount)
				return DummyValue;

			return m_ValueArray[index];
		}


		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const ValueType& SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::GetValueAt(int64_t index) const
		{
			static ValueType DummyValue{};
			if (index < 0 || index >= (decltype(index))m_ItemCount)
				return DummyValue;

			return m_ValueArray[index];
		}



		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		Result SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::AddInternal(int index, const KeyType& keyValue, const ValueType& value)
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
				auto copyCount = m_ItemCount - index;
				unused(copyCount);
				assert((index + 1 + copyCount) <= m_AllocatedItemCount);
				memmove(m_KeyArray + index + 1, m_KeyArray + index, sizeof(KeyType) * (m_ItemCount - index));
				if (UseBulkCopy)
				{
					memmove(m_ValueArray + index + 1, m_ValueArray + index, sizeof(ValueType) * (m_ItemCount - index));
				}
				else
				{
					// Copy from back so that we don't lose data
					for (int iItem = (int)m_ItemCount - 1; iItem >= index; iItem--)
					{
						m_ValueArray[iItem + 1] = m_ValueArray[iItem];
					}
				}
			}
			else
			{
				index = 0;
			}

			m_KeyArray[index] = keyValue;
			m_ValueArray[index] = value;
			m_ItemCount++;

			return ResultCode::SUCCESS;
		}

		// Insert a key
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		Result SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Insert(const KeyType& key, const ValueType& value, int64_t *insertedOrder)
		{
			int index = -1;
			if (FindIndex(key, index))
			{
				if (UseUniqueKey)
				{
					return ResultCode::FAIL;
				}
			}

			AddInternal(index, key, value);
			if (insertedOrder != nullptr) *insertedOrder = index;

			return ResultCode::SUCCESS;
		}

		// Insert a key
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		Result SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Set(const KeyType& key, const ValueType& value, int64_t *insertedOrder)
		{
			int index = -1;
			if (FindIndex(key, index))
			{
				m_ValueArray[index] = value;
			}
			else
			{
				AddInternal(index, key, value);
			}
			if (insertedOrder != nullptr) *insertedOrder = index;

			return ResultCode::SUCCESS;
		}

		// Remove an item and return the removed value
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		Result SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Remove(const KeyType& key, ValueType& value)
		{
			int index = -1;
			if (!FindIndex(key, index))
			{
				return ResultCode::FAIL;
			}

			if (m_ItemCount <= 0) return ResultCode::FAIL;

			value = std::forward<ValueType>(m_ValueArray[index]);

			m_ItemCount--;
			if (m_ItemCount > 0)
			{
				memmove(m_KeyArray + index, m_KeyArray + index + 1, sizeof(KeyType) * (m_ItemCount - index));
				if (UseBulkCopy)
				{
					memmove(m_ValueArray + index, m_ValueArray + index + 1, sizeof(ValueType) * (m_ItemCount - index));
				}
				else
				{
					for (int iItem = index; iItem < (int)m_ItemCount; iItem++)
					{
						m_ValueArray[iItem] = std::forward<ValueType>(m_ValueArray[iItem + 1]);
					}
				}
			}
			else
			{
				m_KeyArray[index] = KeyType{};
				m_ValueArray[index] = ValueType{};
			}

			return ResultCode::SUCCESS;
		}

		// Find a key value
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		Result SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Find(const KeyType& key, ValueType& value, int64_t *pOrder) const
		{
			int index = -1;
			if (!FindIndex(key, index))
			{
				return ResultCode::FAIL;
			}

			value = m_ValueArray[index];
			if (pOrder != nullptr) *pOrder = index;

			return ResultCode::SUCCESS;
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		typename SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::operator[](const KeyType& key)
		{
			int index = -1;
			if (!FindIndex(key, index))
			{
				Iterator itRes(this, -1);
				itRes.SetKey(key);
				return itRes;
			}

			return Iterator(this, index);
		}

		// Find a key value
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::Contains(const KeyType& key)
		{
			int index = -1;
			return FindIndex(key, index);
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const typename SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::begin() const
		{
			if(m_ItemCount > 0)
				return Iterator(const_cast<SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>*>(this), 0);

			return Iterator();
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		typename SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::begin()
		{
			if (m_ItemCount > 0)
				return Iterator(const_cast<SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>*>(this), 0);

			return Iterator();
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		const typename SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::end() const
		{
			return Iterator();
		}

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		typename SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::Iterator SortedArray<KeyType, ValueType, UseUniqueKey, UseBulkCopy>::end()
		{
			return Iterator();
		}

		// find index of the object or insertion index
		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		bool SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::FindIndex(const KeyType& keyValue, int& index) const
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

		template<class KeyType, class ValueType, bool UseUniqueKey, bool UseBulkCopy>
		void SortedArray<KeyType,ValueType, UseUniqueKey, UseBulkCopy>::SetValue(int index, const ValueType& value)
		{
			if (m_ValueArray == nullptr || index < 0 || index >= m_ItemCount)
			{
				assert(false);
				return;
			}

			m_ValueArray[index] = value;
		}

}


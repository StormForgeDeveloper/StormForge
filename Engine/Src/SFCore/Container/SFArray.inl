////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Utility library
//	
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {

		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	static buffer class
		//

		// Static buffer
		template< class DataType >
		Array<DataType>::Array()
			: m_Heap(&GetSystemHeap())
		{
		}

		// Static buffer
		template< class DataType >
		constexpr Array<DataType>::Array(size_t allocatedSize, DataType *pDataPtr)
			: m_Heap(nullptr)
		{
			SetBuffPtr(allocatedSize, pDataPtr);
		}

		template< class DataType >
		Array<DataType>::Array(IHeap& heap)
			: m_Heap(&heap)
		{
		}

		template< class DataType >
		Array<DataType>::~Array()
		{
		}


		// Update Data pointer
		template< class DataType >
		void Array<DataType>::SetBuffPtr(size_t AllocatedSize, DataType *pDataPtr)
		{
			assert(m_Size <= AllocatedSize); // size should be reset

			m_AllocatedSize = AllocatedSize;
			m_pDataPtr = pDataPtr;
		}

		// Update Data pointer
		template< class DataType >
		constexpr void Array<DataType>::SetBuffPtrConstexpr(size_t AllocatedSize, DataType *pDataPtr)
		{
			//m_Size = AllocatedSize;
			m_AllocatedSize = AllocatedSize;
			m_pDataPtr = (DataType*)pDataPtr;
		}


		// Get Size
		template< class DataType >
		size_t Array<DataType>::size() const
		{
			return m_Size;
		}

		// set Reserve size
		template< class DataType >
		inline Result Array<DataType>::resize(size_t szNewSize)
		{
			auto hr = reserve(szNewSize);
			if (hr)
				m_Size = szNewSize;
			return hr;
		}

		// Clear array, buffer size not reallocated, buffer data didn't erased, clear manually if need
		template< class DataType >
		void Array<DataType>::Clear()
		{
			if (m_pDataPtr != nullptr)
			{
				if constexpr (IsCopyAssignable && !IsConstType)
				{
					for (int iItem = 0; iItem < (int)m_Size; iItem++)
					{
						m_pDataPtr[iItem] = DataType{};
					}
				}
			}
			m_Size = 0;
		}

		template< class DataType >
		inline Result Array<DataType>::insert(int index, const DataType& NewData)
		{
			Result hr = ResultCode::SUCCESS;
			auto newSize = index + 1;
			while (size() == GetAllocatedSize() || newSize >= GetAllocatedSize())
			{
				hr = IncreaseSize();
				if (!(hr)) return hr;
			}

			if (index < m_Size)
			{
				for (int iIdx = (int)m_Size; iIdx > index; iIdx--)
				{
					m_pDataPtr[iIdx] = std::forward<DataType>(m_pDataPtr[iIdx - 1]);
				}

				m_Size++;
			}
			else
			{
				for (int iIdx = (int)m_Size; iIdx < index; iIdx++)
				{
					m_pDataPtr[iIdx] = {};
				}

				m_Size = index + 1;
			}

			m_pDataPtr[index] = NewData;

			return hr;
		}


		// push_back
		template< class DataType >
		inline Result Array<DataType>::push_back(DataType&& NewData)
		{
			Result hr = ResultCode::SUCCESS;
			if (size() == GetAllocatedSize())
			{
				hr = IncreaseSize();
				if (!(hr)) return hr;
			}

			Assert(size() < GetAllocatedSize());

			m_pDataPtr[m_Size] = std::forward<DataType>(NewData);
			m_Size++;

			return hr;
		}

		// push_back
		template< class DataType >
		inline Result Array<DataType>::push_back(const DataType& NewData)
		{
			Result hr = ResultCode::SUCCESS;
			if (size() == GetAllocatedSize())
			{
				hr = IncreaseSize();
				if (!(hr)) return hr;
			}

			Assert(size() < GetAllocatedSize());

			m_pDataPtr[m_Size] = NewData;
			m_Size++;

			return hr;
		}


		template< class DataType >
		inline Result Array<DataType>::push_back(size_t numItems, const DataType* NewData)
		{
			Result hr = ResultCode::SUCCESS;
			auto newSize = numItems + size();
			if (newSize > GetAllocatedSize())
			{
				hr = reserve(newSize + GetIncreaseSize());
				if (!(hr)) return hr;
			}

			Assert(newSize <= GetAllocatedSize());

			for (uint iItem = 0; iItem < numItems; iItem++)
			{
				m_pDataPtr[m_Size] = NewData[iItem];
				m_Size++;
			}

			return hr;
		}

		template< class DataType >
		DataType Array<DataType>::pop_back()
		{
			if (size() == 0)
			{
				return {};
			}

			auto item = std::forward<DataType>(m_pDataPtr[size() - 1]);
			RemoveAt((int)size() - 1);

			return std::forward<DataType>(item);
		}


		// Remove element
		template< class DataType >
		Result Array<DataType>::RemoveAt(int iIndex)
		{
			if (iIndex < 0 || (decltype(m_Size))iIndex >= m_Size)
				return ResultCode::INVALID_ARG;

			for (INT iIdx = iIndex + 1; (decltype(m_Size))iIdx < m_Size; iIdx++)
			{
				m_pDataPtr[iIdx - 1] = m_pDataPtr[iIdx];
			}
			m_Size--;

			return ResultCode::SUCCESS;
		}

		template< class DataType >
		Result Array<DataType>::RemoveItem(const DataType& RemoveData)
		{
			INT iIdx = FindItem(RemoveData);

			if (iIdx >= 0)
				return RemoveAt(iIdx);

			return ResultCode::SUCCESS;
		}

		// find
		template< class DataType >
		int Array<DataType>::FindItem(const DataType& FindData) const
		{
			for (INT iIdx = 0; (decltype(m_Size))iIdx < m_Size; iIdx++)
			{
				if (m_pDataPtr[iIdx] == FindData)
					return iIdx;
			}
			return -1;
		}


		// Element access operator
		template< class DataType >
		const DataType& Array<DataType>::operator [](size_t iElement) const
		{
			// This is abnormal operation
			AssertRel(iElement < m_Size);
			return m_pDataPtr[iElement];
		}


		template< class DataType >
		const DataType& Array<DataType>::GetAt(uint iElement) const
		{
			// This is abnormal operation
			AssertRel(iElement < m_Size);
			return m_pDataPtr[iElement];
		}

		// Called for reallocation
		template< class DataType >
		Result Array<DataType>::IncreaseSize()
		{
			size_t szNewSize = GetAllocatedSize() + GetIncreaseSize();
			Assert(szNewSize > GetAllocatedSize());

			return reserve(szNewSize);
		}

		template< class DataType >
		DataType& Array<DataType>::operator [](size_t iElement)
		{
			// This is abnormal operation
			Assert(iElement < m_Size);
			// Auto resize if not assert at above
			while (iElement >= m_Size)
			{
				AssertRel(iElement < (USHRT_MAX * 2)); // if too big
				IncreaseSize();
				m_Size = std::min(iElement + 1, GetAllocatedSize());
			}

			return m_pDataPtr[iElement];
		}



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Static Array Variable class
		//


		template< class DataType, size_t DefaultBufferSize >
		StaticArray<DataType, DefaultBufferSize>::StaticArray(IHeap& heap)
			: DynamicArray<DataType>(m_StaticHeap)
			, m_StaticHeap(heap.GetNameCrc(), heap)
		{
			super::reserve(DefaultBufferSize);
		}


		template< class DataType, size_t DefaultBufferSize >
		StaticArray<DataType, DefaultBufferSize>::~StaticArray()
		{
			// We need to release the buffer a head of parent destructor
			super::EmptyInternal();
		}





		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Dynamic Array Variable class
		//


		template< class DataType >
		DynamicArray<DataType>::DynamicArray(IHeap& heap, size_t increaseSize)
			: Array<DataType>(heap)
			, m_pAllocatedBuffer(nullptr)
		{
			Array<DataType>::SetIncreaseSize(increaseSize);
			CheckCtrMemory();
		}


		template< class DataType >
		DynamicArray<DataType>::~DynamicArray()
		{
			EmptyInternal();
		}

		template< class DataType >
		void DynamicArray<DataType>::EmptyInternal()
		{
			if (m_pAllocatedBuffer)
			{
				super::SetSizeInternal(0);

				if constexpr (super::IsDestructable)
				{
					for (uint iItem = 0; iItem < super::GetAllocatedSize(); iItem++)
					{
						(m_pAllocatedBuffer + iItem)->~DataTypeDecay();
					}
				}

				super::GetHeap().Free(m_pAllocatedBuffer);

				super::SetBuffPtr(0, nullptr);

				m_pAllocatedBuffer = nullptr;
			}
		}

		template< class DataType >
		void DynamicArray<DataType>::Empty()
		{
			EmptyInternal();
		}

		// reallocate
		template< class DataType >
		Result DynamicArray<DataType>::reserve(size_t szNewSize)
		{
			DataType *pNewBuffer = nullptr;
			DataType *pOldBuffer = nullptr;

			if (szNewSize <= Array<DataType>::GetAllocatedSize())
				return ResultCode::SUCCESS_FALSE;

			auto OldSize = super::GetAllocatedSize();
			pOldBuffer = super::data();

			if (m_pAllocatedBuffer)
			{
				pNewBuffer = (DataType*)super::GetHeap().Realloc(m_pAllocatedBuffer, szNewSize * sizeof(DataType));
				if (pNewBuffer && pNewBuffer != m_pAllocatedBuffer)
					pOldBuffer = nullptr; // this case, the old buffer already has released
			}

			uint iItem = (uint)OldSize;

			if (pNewBuffer == nullptr)
			{
				pNewBuffer = (DataType*)super::GetHeap().Alloc(szNewSize * sizeof(DataType));
				if (pNewBuffer == nullptr)
					return ResultCode::OUT_OF_MEMORY;

				iItem = 0;
				if constexpr (super::IsConstructable)
				{
					if constexpr (std::is_move_constructible_v<DataTypeDecay>)
					{
						for (; iItem < super::size(); iItem++)
						{
							new((void*)(pNewBuffer + iItem)) typename super::DataTypeDecay(std::forward<typename super::DataTypeDecay>(pOldBuffer[iItem]));
						}
					}
					else if constexpr (std::is_move_assignable_v<DataTypeDecay>)
					{
						for (; iItem < super::size(); iItem++)
						{
							new((void*)(pNewBuffer + iItem)) typename super::DataTypeDecay();
							pNewBuffer[iItem] = std::forward<typename super::DataTypeDecay>(pOldBuffer[iItem]);
						}
					}
					else if constexpr (std::is_copy_constructible_v<DataTypeDecay>)
					{
						for (; iItem < super::size(); iItem++)
						{
							new((void*)(pNewBuffer + iItem)) typename super::DataTypeDecay(pOldBuffer[iItem]);
						}
					}
					else if constexpr (std::is_copy_assignable_v<DataTypeDecay>)
					{
						for (; iItem < super::size(); iItem++)
						{
							new((void*)(pNewBuffer + iItem)) typename super::DataTypeDecay();
							pNewBuffer[iItem] = pOldBuffer[iItem];
						}
					}
					else // we can't copy nor move
					{
						assert(super::size() == 0);
					}
				}
			}

			for (; iItem < szNewSize; iItem++)
			{
				new((void*)(pNewBuffer + iItem)) typename super::DataTypeDecay();
			}

			m_pAllocatedBuffer = pNewBuffer;

			CheckCtrMemory();

			super::SetBuffPtr(szNewSize, pNewBuffer);

			if (pOldBuffer && pOldBuffer != pNewBuffer)
			{
				if constexpr (super::IsDestructable)
				{
					for (iItem = 0; iItem < OldSize; iItem++)
					{
						(pOldBuffer + iItem)->~DataTypeDecay();
					}
				}

				super::GetHeap().Free(pOldBuffer);
			}

			return ResultCode::SUCCESS;
		}



		template< class DataType >
		ArrayView<DataType>::ArrayView()
		{

		}

		template< class DataType >
		ArrayView<DataType>::ArrayView(uint maxDataCount, uint dataCount, DataType* pDataPtr)
		{
			SetLinkedBuffer(maxDataCount, dataCount, pDataPtr);
		}

		//template< class DataType >
		//ArrayView<DataType>::ArrayView(size_t dataCount, DataType* pDataPtr)
		//{
		//	SetLinkedBuffer(dataCount, dataCount, pDataPtr);
		//}

		template< class DataType >
		constexpr ArrayView<DataType>::ArrayView(size_t dataCount, DataType* pDataPtr)
		{
			SetLinkedBuffer(dataCount, pDataPtr);
		}

		template< class DataType >
		ArrayView<DataType>::~ArrayView()
		{
		}

		template< class DataType >
		void ArrayView<DataType>::SetLinkedBuffer(size_t maxDataCount, size_t dataCount, DataType* pDataPtr)
		{
			Array<DataType>::SetSizeInternal(0);
			Array<DataType>::SetBuffPtrConstexpr(maxDataCount, pDataPtr);
			Array<DataType>::SetSizeInternal(dataCount);
		}

		template< class DataType >
		constexpr void ArrayView<DataType>::SetLinkedBuffer(size_t dataCount, DataType* pDataPtr)
		{
			Array<DataType>::SetSizeInternal(0);
			Array<DataType>::SetBuffPtrConstexpr(dataCount, pDataPtr);
			Array<DataType>::SetSizeInternal(dataCount);
		}

		template< class DataType >
		void ArrayView<DataType>::SetLinkedBuffer(const Array<DataType>& srcLink)
		{
			Array<DataType>::SetSizeInternal(0);
			Array<DataType>::SetBuffPtr(srcLink.GetAllocatedSize(), const_cast<uint8_t*>(srcLink.data()));
			Array<DataType>::SetSizeInternal(srcLink.size());
		}

		template< class DataType >
		Result ArrayView<DataType>::reserve(size_t szReserv)
		{
			if (szReserv <= Array<DataType>::GetAllocatedSize())
				return ResultCode::SUCCESS;

			return ResultCode::FAIL;
		}



}



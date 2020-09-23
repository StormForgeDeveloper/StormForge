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
		constexpr Array<DataType>::Array(size_t allocatedSize, const DataType *pDataPtr)
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
			AssertRel(AllocatedSize >= m_Size);

			m_AllocatedSize = AllocatedSize;
			if (m_PreserveDataOnResize && m_pDataPtr != pDataPtr)
			{
				for (size_t iData = 0; iData < m_Size; iData++)
					pDataPtr[iData] = std::forward<DataType>(m_pDataPtr[iData]);
			}
			m_pDataPtr = pDataPtr;
		}

		// Update Data pointer
		template< class DataType >
		constexpr void Array<DataType>::SetBuffPtr(size_t AllocatedSize, const DataType *pDataPtr)
		{
			m_Size = AllocatedSize;
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
			if ((hr))
				m_Size = szNewSize;
			return hr;
		}

		// Clear array, buffer size not reallocated, buffer data didn't erased, clear manually if need
		template< class DataType >
		void Array<DataType>::Clear()
		{
			if (m_pDataPtr != nullptr)
			{
				for (int iItem = 0; iItem < (int)m_Size; iItem++)
				{
					m_pDataPtr[iItem] = {};
				}
			}
			m_Size = 0;
		}

		// ConserveDataOnResize
		template< class DataType >
		bool Array<DataType>::GetPreserveDataOnResize() const
		{
			return m_PreserveDataOnResize;
		}

		template< class DataType >
		void Array<DataType>::SetPreserveDataOnResize(bool conserveDataOnResize)
		{
			m_PreserveDataOnResize = conserveDataOnResize;
		}


		// Get Current allocated Size
		template< class DataType >
		size_t Array<DataType>::GetAllocatedSize() const
		{
			return m_AllocatedSize;
		}

		// Get Array Increase Size
		template< class DataType >
		size_t Array<DataType>::GetIncreaseSize() const
		{
			return m_IncreaseSize;
		}

		template< class DataType >
		void Array<DataType>::SetIncreaseSize(size_t szNewIncSize)
		{
			Assert(szNewIncSize > 0);

			// At least increase one
			if (szNewIncSize == 0)
				szNewIncSize = 1;

			m_IncreaseSize = szNewIncSize;
		}

		// Get data pointer
		template< class DataType >
		const DataType* Array<DataType>::data() const
		{
			return m_pDataPtr;
		}

		template< class DataType >
		DataType* Array<DataType>::data()
		{
			return m_pDataPtr;
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
				Assert(false);
				return {};
			}

			auto item = std::forward<DataType>(m_pDataPtr[size() - 1]);
			RemoveAt((int)size() - 1);

			return std::forward<DataType>(item);
		}


		// Remove element
		template< class DataType >
		Result Array<DataType>::RemoveAt(INT iIndex)
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
		INT Array<DataType>::FindItem(const DataType& FindData)
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
		DataType& Array<DataType>::operator [](size_t iElement) const
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

		template<class DataType>
		Array<DataType>& Array<DataType>::operator = (const Array<DataType>& src)
		{
			resize(src.size());
			for (size_t iItem = 0; iItem < src.size(); iItem++)
				m_pDataPtr[iItem] = src[iItem];
			return *this;
		}



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Static Array Variable class
		//


		template< class DataType, size_t DefaultBufferSize >
		StaticArray<DataType, DefaultBufferSize>::StaticArray(IHeap& heap)
			: Array<DataType>(heap)
			, m_pAllocatedBuffer(nullptr)
		{
			Array<DataType>::SetBuffPtr(DefaultBufferSize, m_pDefaultBuffer);
		}


		template< class DataType, size_t DefaultBufferSize >
		StaticArray<DataType, DefaultBufferSize>::~StaticArray()
		{
			if (m_pAllocatedBuffer)
				delete[] m_pAllocatedBuffer;
		}

		// reallocate
		template< class DataType, size_t DefaultBufferSize >
		Result StaticArray<DataType, DefaultBufferSize>::reserve(size_t szNewSize)
		{
			DataType *pNewBuffer = nullptr;
			DataType *pOldBuffer = nullptr;

			if (szNewSize <= Array<DataType>::GetAllocatedSize())
				return ResultCode::SUCCESS_FALSE;

			pNewBuffer = new(super::GetHeap()) DataType[szNewSize];
			if (pNewBuffer == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Array<DataType>::SetBuffPtr(szNewSize, pNewBuffer);

			pOldBuffer = m_pAllocatedBuffer;
			m_pAllocatedBuffer = pNewBuffer;
			if (pOldBuffer)
			{
				delete[] pOldBuffer;
			}

			return ResultCode::SUCCESS;
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
		}


		template< class DataType >
		DynamicArray<DataType>::~DynamicArray()
		{
			if (m_pAllocatedBuffer)
				delete[] m_pAllocatedBuffer;
		}

		// reallocate
		template< class DataType >
		Result DynamicArray<DataType>::reserve(size_t szNewSize)
		{
			DataType *pNewBuffer = nullptr;
			DataType *pOldBuffer = nullptr;

			if (szNewSize <= Array<DataType>::GetAllocatedSize())
				return ResultCode::SUCCESS_FALSE;

			pNewBuffer = new(super::GetHeap()) DataType[szNewSize];
			if (pNewBuffer == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Array<DataType>::SetBuffPtr(szNewSize, pNewBuffer);

			pOldBuffer = m_pAllocatedBuffer;
			m_pAllocatedBuffer = pNewBuffer;
			if (pOldBuffer)
			{
				delete[] pOldBuffer;
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

		template< class DataType >
		ArrayView<DataType>::ArrayView(size_t dataCount, DataType* pDataPtr)
		{
			SetLinkedBuffer(dataCount, dataCount, pDataPtr);
		}

		template< class DataType >
		constexpr ArrayView<DataType>::ArrayView(size_t dataCount, const DataType* pDataPtr)
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
			Array<DataType>::SetBuffPtr(maxDataCount, pDataPtr);
			Array<DataType>::resize(dataCount);
		}

		template< class DataType >
		constexpr void ArrayView<DataType>::SetLinkedBuffer(size_t dataCount, const DataType* pDataPtr)
		{
			Array<DataType>::SetBuffPtr(dataCount, pDataPtr);
			Array<DataType>::resize(dataCount);
		}

		template< class DataType >
		void ArrayView<DataType>::SetLinkedBuffer(const Array<DataType>& srcLink)
		{
			Array<DataType>::SetBuffPtr(srcLink.GetAllocatedSize(), const_cast<uint8_t*>(srcLink.data()));
			Array<DataType>::resize(srcLink.size());
			memcpy(Array<DataType>::data(), srcLink.data(), sizeof(DataType) * srcLink.size());
		}

		template< class DataType >
		Result ArrayView<DataType>::reserve(size_t szReserv)
		{
			if (szReserv <= Array<DataType>::GetAllocatedSize())
				return ResultCode::SUCCESS;

			return ResultCode::FAIL;
		}



}



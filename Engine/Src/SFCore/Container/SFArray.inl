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
		DynamicArray<DataType>::DynamicArray(IHeap& heap)
			: Array<DataType>(heap)
			, m_pAllocatedBuffer(nullptr)
		{
			Array<DataType>::SetIncreaseSize(16);
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
		void ArrayView<DataType>::SetLinkedBuffer(size_t bufferSize, size_t dataCount, DataType* pDataPtr)
		{
			Array<DataType>::SetSizeInternal(0);
			Array<DataType>::SetBuffPtrConstexpr(bufferSize, pDataPtr);
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



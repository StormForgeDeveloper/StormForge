////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Array base
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Interfaces/SFPublicInterface.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {

	class IHeap;

    // TODO: Copy from SFIMemoryManager.h. Need to work on memory header includes
    IHeap& GetSystemHeap();

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	static buffer class
	//

	template< class DataType >
	class Array
	{
	public:

		using DataTypeDecay = std::decay_t<DataType>;

		static constexpr bool IsConstType = std::is_const_v<DataType>;
		static constexpr bool IsTirviallyConstructable = std::is_trivially_constructible_v<DataTypeDecay>;
		static constexpr bool IsConstructable = std::is_constructible_v<DataTypeDecay>;
		static constexpr bool IsCopyConstructable = std::is_copy_constructible_v<DataTypeDecay>;
		static constexpr bool IsCopyAssignable = std::is_copy_assignable_v<DataTypeDecay>;
		static constexpr bool IsDestructable = std::is_destructible_v<DataTypeDecay>;
		//static constexpr bool IsCopyAssignable = std::is_copy_assignable_v<DataTypeDecay>;


#if !defined(SWIG)
		class iterator
		{
		public:
			static constexpr int END_IDX = -1;

		private:
			// Container that linked with this iterator
			Array<DataType> *m_pContainer;

			// Index 
			mutable int m_iIdx;

		public:

			iterator()
				: m_pContainer(nullptr)
				, m_iIdx(END_IDX)
			{
			}

			iterator(Array<DataType> *pContainer, int index = 0)
				: m_pContainer(pContainer)
				, m_iIdx(index)
			{
				assert(m_pContainer != nullptr);
			}

			iterator(const iterator& src)
				: m_pContainer(src.m_pContainer)
				, m_iIdx(src.m_iIdx)
			{
				assert(m_pContainer != nullptr);
			}

			iterator(iterator&& src)
				: m_pContainer(src.m_pContainer)
				, m_iIdx(src.m_iIdx)
			{
				src.Reset();
			}

			~iterator()
			{
			}


			iterator& operator++()
			{
				if (m_pContainer)
				{
					m_iIdx++;
					if (m_iIdx >= m_pContainer->size())
					{
						m_iIdx = END_IDX;
					}
				}

				return *this;
			}

			const iterator& operator++() const
			{
				if (m_pContainer)
				{
					m_iIdx++;
					if (m_iIdx >= m_pContainer->size())
					{
						m_iIdx = END_IDX;
					}
				}

				return *this;
			}


			iterator operator + (size_t szOffset)
			{
				assert(m_pContainer);
				if (m_pContainer && (m_iIdx + szOffset) < m_pContainer->size())
				{
					return iterator(m_pContainer, (uint)(m_iIdx + szOffset));
				}
				return iterator(m_pContainer, -1);
			}


			DataType& operator* ()
			{
				assert(m_pContainer != NULL);
				assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
				return m_pContainer->data()[m_iIdx];
			}

			const DataType& operator* () const
			{
				assert(m_pContainer != NULL);
				assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
				return m_pContainer->data()[m_iIdx];
			}

			DataType* operator-> ()
			{
				assert(m_pContainer != NULL);
				assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
				return &m_pContainer->data()[m_iIdx];
			}

			const DataType* operator-> () const
			{
				assert(m_pContainer != NULL);
				assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
				return &m_pContainer->data()[m_iIdx];
			}

			bool operator !=(const iterator& op) const
			{
				return ((m_pContainer != op.m_pContainer) || (m_iIdx != op.m_iIdx));
			}

			bool operator ==(const iterator& op) const
			{
				return ((m_pContainer == op.m_pContainer) && (m_iIdx == op.m_iIdx));
			}

			// Check validity
			bool IsValid()
			{
				return m_pContainer && m_iIdx < m_pContainer->size();
			}

			// reset iterator and make invalid
			void Reset()
			{
				*this = nullptr;
			}

			iterator& operator = (const iterator& src)
			{
				m_pContainer = src.m_pContainer;
				m_iIdx = src.m_iIdx;
				return *this;
			}

			iterator& operator = (const void* pPtr)
			{
				assert(pPtr == 0);

				m_pContainer = nullptr;
				m_iIdx = END_IDX;

				return *this;
			}
		};
#endif // #ifndef SWIG

	private:
		// Current size
		size_t m_Size = 0;

		// Allocated Size
		size_t m_AllocatedSize = 0;

		// Increase Size
		size_t m_IncreaseSize = 16;

		// Data pointer
		DataType* m_pDataPtr = nullptr;

		// Preserve data on resize by copying back
		bool m_PreserveDataOnResize = true;

		// Heap for memory management
		IHeap* m_Heap = nullptr;


	protected:

		SF_FORCEINLINE void SetSizeInternal(size_t newSize) { m_Size = newSize; }

		// Update Data pointer
		void SetBuffPtr(size_t AllocatedSize, DataType *pDataPtr);
		constexpr void SetBuffPtrConstexpr(size_t AllocatedSize, DataType *pDataPtr);

		// Called for reallocation
		virtual Result IncreaseSize();

	public:
		// Static buffer
		Array();
		constexpr Array(size_t allocatedSize, DataType *pDataPtr);

		template<size_t dataCount>
		constexpr Array(const DataTypeDecay pDataPtr[dataCount])
			: m_Heap(nullptr)
		{
			SetBuffPtr(dataCount, pDataPtr);
		}

		Array(IHeap& heap);
		virtual ~Array();

		SF_FORCEINLINE IHeap& GetHeap() const { return *m_Heap; }

		// Get Size
		inline size_t size() const;

		// set Reserve size
		Result resize(size_t szNewSize);

		// Clear array, buffer size not reallocated, buffer data didn't erased, clear manually if need
		SF_FORCEINLINE void Clear();
		virtual SF_FORCEINLINE void Reset() { Clear(); };
		virtual void Empty() { Reset(); }

		// PreserveDataOnResize
		SF_FORCEINLINE bool GetPreserveDataOnResize() const { return m_PreserveDataOnResize; }
		SF_FORCEINLINE void SetPreserveDataOnResize(bool conserveDataOnResize) { m_PreserveDataOnResize = conserveDataOnResize; }

		// Get Current allocated Size
		SF_FORCEINLINE size_t GetAllocatedSize() const { return m_AllocatedSize; }
		SF_FORCEINLINE size_t capacity() const { return GetAllocatedSize(); }

		// Get Array Increase Size
		SF_FORCEINLINE size_t GetIncreaseSize() const { return m_IncreaseSize; }
		SF_FORCEINLINE void SetIncreaseSize(size_t szNewIncSize)
		{
			assert(szNewIncSize > 0);

			// At least increase one
			if (szNewIncSize == 0)
				szNewIncSize = 1;

			m_IncreaseSize = szNewIncSize;
		}

        // Test if the index is in valid range
        SF_FORCEINLINE bool IsValidIndex(int iIndex) const { return iIndex >= 0 && iIndex < size(); }

		// set Reserve size
		virtual Result reserve(size_t szReserv) { return ResultCode::SUCCESS; }

		// Get data pointer
		SF_FORCEINLINE DataType* data() const { return m_pDataPtr; }
		SF_FORCEINLINE DataType* data() { return m_pDataPtr; }

		// Insert an item
		Result insert(int index, const DataType& NewData);

		// push_back
		Result push_back(size_t numItems, const DataType* NewData);
		Result push_back(DataType&& NewData);
		Result push_back(const DataType& NewData);

		template<class DataTypeFrom>
		Result Append(const Array<DataTypeFrom>& src)
		{
			Result hr;
			hr = reserve(src.size() + size());
			if (!hr.IsSuccess()) return hr;

			for (auto& itItem : src)
			{
				hr = push_back(itItem);
				if (!hr.IsSuccess()) return hr;
			}

			return hr;
		}

        template<class DataTypeFrom>
        Result Append(uint dataCount, const DataTypeFrom& data)
        {
            Result hr;
            hr = reserve(dataCount + size());
            if (!hr.IsSuccess()) return hr;

            for (uint iData = 0; iData < dataCount; iData++)
            {
                hr = push_back(data);
                if (!hr.IsSuccess()) return hr;
            }

            return hr;
        }

		DataType pop_back();

		// Remove element
		inline Result RemoveAt(int iIndex);
		inline Result RemoveItem(const DataType& RemoveData);

		// find and return index, -1 is not found
		inline int FindItem(const DataType& FindData) const;

		// Element access operator
		inline const DataType& operator [](size_t iElement) const;
		inline DataType& operator [](size_t iElement);
		inline const DataType& GetAt(uint iElement) const; // for swig


		// Get binary size
		//size_t GetBinSize() const;

		iterator begin() { return iterator(this, size() == 0 ? iterator::END_IDX : 0); }
		const iterator begin() const { return iterator(const_cast<Array<DataType>*>(this), size() == 0 ? iterator::END_IDX : 0); }
		const iterator end() const { return iterator(const_cast<Array<DataType>*>(this), uint(iterator::END_IDX)); }

		template<typename PredicatorType>
		iterator Find(const PredicatorType& predicator) const
		{
			for (int iData = 0; iData < (int)size(); iData++)
			{
				if (predicator(m_pDataPtr[iData]))
					return iterator(this, iData);
			}
			return end();
		}

		template<typename PredicatorType>
		int FindIndex(const PredicatorType& predicator) const
		{
			for (int iData = 0; iData < (int)size(); iData++)
			{
				if (predicator(m_pDataPtr[iData]))
					return iData;
			}
			return iterator::END_IDX;
		}

		template<typename PredicatorType>
		int FindIndex(int startIndex, const PredicatorType& predicator) const
		{
			for (int iData = startIndex; iData < (int)size(); iData++)
			{
				if (predicator(m_pDataPtr[iData]))
					return iData;
			}
			return iterator::END_IDX;
		}

		template<class DataType2, typename = std::enable_if_t<std::is_convertible_v<DataType, DataType2>>>
		bool operator == (const Array<DataType2>& op2) const
		{
			if (size() != op2.size())
				return false;

			for (uint iItem = 0; iItem < size(); iItem++)
			{
				if (m_pDataPtr[iItem] != op2.m_pDataPtr[iItem])
					return false;
			}

			return true;
		}

		Array<DataType>& operator = (const Array<DataType>& src) = delete;

		// copy operator
		template<class SrcDataType>
		void CopyFrom(const Array<SrcDataType>& src)
		{
			// should I use is_trivial_v ?
			constexpr bool bBulkCopy = std::is_trivially_copy_constructible_v<DataType>
				&& std::is_trivially_copy_constructible_v<SrcDataType>
				&& sizeof(DataType) == sizeof(SrcDataType); // decay+is_same test would be more precise, but I am trying to let them be able to copy if raw sizes are same

			if constexpr (bBulkCopy)
			{
				resize(src.size());
				memcpy((void*)m_pDataPtr, src.data(), src.size() * sizeof(DataType));
			}
			else
			{
				resize(src.size());
				for (size_t iItem = 0; iItem < src.size(); iItem++)
					m_pDataPtr[iItem] = src[iItem];
			}
		}

	};


    // Static buffer
    template< class DataType >
    Array<DataType>::Array()
        : m_Heap(&GetSystemHeap())
    {
    }

    // Static buffer
    template< class DataType >
    constexpr Array<DataType>::Array(size_t allocatedSize, DataType* pDataPtr)
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
    void Array<DataType>::SetBuffPtr(size_t AllocatedSize, DataType* pDataPtr)
    {
        assert(m_Size <= AllocatedSize); // size should be reset

        m_AllocatedSize = AllocatedSize;
        m_pDataPtr = pDataPtr;
    }

    // Update Data pointer
    template< class DataType >
    constexpr void Array<DataType>::SetBuffPtrConstexpr(size_t AllocatedSize, DataType* pDataPtr)
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
            if (hr.IsFailure()) return hr;
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
            if (hr.IsFailure()) return hr;
        }

        assert(size() < GetAllocatedSize());

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
            if (hr.IsFailure()) return hr;
        }

        assert(size() < GetAllocatedSize());

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
            if (hr.IsFailure()) return hr;
        }

        assert(newSize <= GetAllocatedSize());

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
        assert(iElement < m_Size);
        return m_pDataPtr[iElement];
    }


    template< class DataType >
    const DataType& Array<DataType>::GetAt(uint iElement) const
    {
        // This is abnormal operation
        assert(iElement < m_Size);
        return m_pDataPtr[iElement];
    }

    // Called for reallocation
    template< class DataType >
    Result Array<DataType>::IncreaseSize()
    {
        size_t szNewSize = GetAllocatedSize() + GetIncreaseSize();
        assert(szNewSize > GetAllocatedSize());

        return reserve(szNewSize);
    }

    template< class DataType >
    DataType& Array<DataType>::operator [](size_t iElement)
    {
        // This is abnormal operation
        assert(iElement < m_Size);
        // Auto resize if not assert at above
        while (iElement >= m_Size)
        {
            assert(iElement < (USHRT_MAX * 2)); // if too big
            IncreaseSize();
            m_Size = std::min(iElement + 1, GetAllocatedSize());
        }

        return m_pDataPtr[iElement];
    }




} // namespace SF





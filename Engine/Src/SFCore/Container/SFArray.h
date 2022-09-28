////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Array 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFIMemoryManager.h"
#include "MemoryManager/SFHeapMemory.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {

	class IHeap;


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
					Assert(m_pContainer != nullptr);
				}

				iterator(const iterator& src)
					: m_pContainer(src.m_pContainer)
					, m_iIdx(src.m_iIdx)
				{
					Assert(m_pContainer != nullptr);
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
					Assert(m_pContainer);
					if (m_pContainer && (m_iIdx + szOffset) < m_pContainer->size())
					{
						return iterator(m_pContainer, (uint)(m_iIdx + szOffset));
					}
					return iterator(m_pContainer, -1);
				}


				DataType& operator* ()
				{
					Assert(m_pContainer != NULL);
					Assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
					return m_pContainer->data()[m_iIdx];
				}

				const DataType& operator* () const
				{
					Assert(m_pContainer != NULL);
					Assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
					return m_pContainer->data()[m_iIdx];
				}

				DataType* operator-> ()
				{
					Assert(m_pContainer != NULL);
					Assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
					return &m_pContainer->data()[m_iIdx];
				}

				const DataType* operator-> () const
				{
					Assert(m_pContainer != NULL);
					Assert(m_iIdx >= 0 && m_iIdx < m_pContainer->size());
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
					Assert(pPtr == 0);

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
				Assert(szNewIncSize > 0);

				// At least increase one
				if (szNewIncSize == 0)
					szNewIncSize = 1;

				m_IncreaseSize = szNewIncSize;
			}

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
				if (!hr) return hr;

				for (auto& itItem : src)
				{
					hr = push_back(itItem);
					if (!hr) return hr;
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




		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Dynamic Array class
		//

		template< class DataType >
		class DynamicArray : public Array<DataType>
		{
		public:
			typedef Array<DataType> super;
			using DataTypeDecay = typename super::DataTypeDecay;

		protected:
			// Data pointer
			DataType*	m_pAllocatedBuffer;

			void EmptyInternal();

		public:
			DynamicArray(IHeap& heap = GetSystemHeap());
			virtual ~DynamicArray();

			virtual void Empty() override;

			// set Reserve size
			virtual Result reserve(size_t szReserv) override;

			// copy operator
			//DynamicArray<DataType>& operator = (const Array<std::decay_t<DataType>>& src) { Array<DataType>::operator = (src); return *this; }
			//DynamicArray<DataType>& operator = (const Array<const std::decay_t<DataType>>& src) { Array<DataType>::operator = (src); return *this; }
		};


		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Static Array Variable class
		//

		template< class DataType, size_t DefaultBufferSize >
		class StaticArray : public DynamicArray<DataType>
		{
		public:
			typedef DynamicArray<DataType> super;

		private:
			// item buffer space + extra for header information
			StaticMemoryAllocatorT<DefaultBufferSize * sizeof(DataType) + 256> m_StaticHeap;

		public:
			StaticArray(IHeap& heap = GetSystemHeap());
			virtual ~StaticArray();

			//virtual Result reserve(size_t szReserv);

			// copy operator
			StaticArray<DataType, DefaultBufferSize>& operator = (const Array<DataType>& src) = delete;
		};


		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Linked Array class
		//		Use externally allocated buffer only
		//

		template< class DataType >
		class ArrayView : public Array<DataType>
		{
		public:
			ArrayView();
			ArrayView(uint maxDataCount, uint dataCount, DataType* pDataPtr);
			//ArrayView(size_t dataCount, DataType* pDataPtr);
			constexpr ArrayView(size_t dataCount, DataType* pDataPtr);
			template<size_t dataCount>
			constexpr ArrayView(DataType(&pDataPtr)[dataCount])
			{
				SetLinkedBuffer(dataCount, pDataPtr);
			}

			virtual ~ArrayView();

			void SetLinkedBuffer(size_t maxDataCount, size_t dataCount, DataType* pDataPtr);
			constexpr void SetLinkedBuffer(size_t dataCount, DataType* pDataPtr);
			void SetLinkedBuffer(const Array<DataType>& srcLink);

			Result reserve(size_t szReserv) override;

			// copy operator
			ArrayView<DataType>& operator = (const Array<DataType>& src) { SetLinkedBuffer(src); return *this; }
		};




} // namespace SF

#include "SFArray.inl"



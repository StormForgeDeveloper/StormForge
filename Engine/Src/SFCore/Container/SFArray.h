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

#if !defined(SWIG)
			class iterator
			{
			public:
				enum { END_IDX = -1 };

			private:
				// Container that linked with this iterator
				Array<DataType> *m_pContainer;

				// Index 
				mutable uint m_iIdx;

			public:

				iterator()
					: m_pContainer(nullptr)
					, m_iIdx(END_IDX)
				{
				}

				iterator(Array<DataType> *pContainer, uint index = 0)
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
			size_t m_IncreaseSize = 10;

			// Data pointer
			DataType* m_pDataPtr = nullptr;

			// Preserve data on resize by copying back
			bool m_PreserveDataOnResize = true;

			// Heap for memory management
			IHeap* m_Heap = nullptr;


		protected:

			// Update Data pointer
			void SetBuffPtr(size_t AllocatedSize, DataType *pDataPtr);
			constexpr void SetBuffPtr(size_t AllocatedSize, const DataType *pDataPtr);

			// Called for reallocation
			virtual Result IncreaseSize();

		public:
			// Static buffer
			Array();
			constexpr Array(size_t allocatedSize, const DataType *pDataPtr);

			template<size_t dataCount>
			constexpr Array(const DataTypeDecay pDataPtr[dataCount])
				: m_Heap(nullptr)
			{
				SetBuffPtr(dataCount, pDataPtr);
			}

			Array(IHeap& heap);
			virtual ~Array();

			IHeap& GetHeap() const { return *m_Heap; }

			// Get Size
			inline size_t size() const;

			// set Reserve size
			Result resize(size_t szNewSize);

			// Clear array, buffer size not reallocated, buffer data didn't erased, clear manually if need
			inline void Clear();

			// PreserveDataOnResize
			inline bool GetPreserveDataOnResize() const;
			inline void SetPreserveDataOnResize(bool conserveDataOnResize);

			// Get Current allocated Size
			size_t GetAllocatedSize() const;
			size_t capacity() const { return GetAllocatedSize(); }

			// Get Array Increase Size
			size_t GetIncreaseSize() const;
			void SetIncreaseSize(size_t szNewIncSize);

			// set Reserve size
			virtual Result reserve(size_t szReserv) { return ResultCode::SUCCESS; }

			// Get data pointer
			inline const DataType* data() const;
			inline DataType* data();

			// Insert an item
			Result insert(int index, const DataType& NewData);

			// push_back
			Result push_back(size_t numItems, const DataType* NewData);
			Result push_back(DataType&& NewData);
			Result push_back(const DataType& NewData);

			DataType pop_back();

			// Remove element
			inline Result RemoveAt(INT iIndex);
			inline Result RemoveItem(const DataType& RemoveData);

			// find and return index, -1 is not found
			inline INT FindItem(const DataType& FindData);

			// Element access operator
			inline const DataType& operator [](size_t iElement) const;
			inline DataType& operator [](size_t iElement);
			inline const DataType& GetAt(uint iElement) const; // for swig


			// Get binary size
			//size_t GetBinSize() const;

			iterator begin() { return iterator(this, size() == 0 ? iterator::END_IDX : 0); }
			const iterator begin() const { return iterator(const_cast<Array<DataType>*>(this), size() == 0 ? iterator::END_IDX : 0); }
			const iterator end() const { return iterator(const_cast<Array<DataType>*>(this), iterator::END_IDX); }

			template<typename PredicatorType>
			iterator Find(const PredicatorType& predicator)
			{
				for (size_t iData = 0; iData < size(); iData++)
				{
					if (predicator(m_pDataPtr[iData]))
						return iterator(this, iData);
				}
				return end();
			}

			template<typename PredicatorType>
			int FindIndex(const PredicatorType& predicator)
			{
				for (size_t iData = 0; iData < size(); iData++)
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

			// copy operator
			Array<DataType>& operator = (const Array<DataType>& src);
		};



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Static Array Variable class
		//

		template< class DataType, size_t DefaultBufferSize >
		class StaticArray : public Array<DataType>
		{
		public:
			typedef Array<DataType> super;

		private:
			// static storage for remove heap alloc
			DataType	m_pDefaultBuffer[DefaultBufferSize];

			// Data pointer
			DataType*	m_pAllocatedBuffer;

		public:
			StaticArray(IHeap& heap = GetSystemHeap());
			virtual ~StaticArray();

			// set Reserve size
			virtual Result reserve(size_t szReserv);

			// copy operator
			StaticArray<DataType, DefaultBufferSize>& operator = (const Array<DataType>& src) { Array<DataType>::operator = (src); return *this; }
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

		private:
			// Data pointer
			DataType*	m_pAllocatedBuffer;

		public:
			DynamicArray(IHeap& heap = GetSystemHeap(), size_t increaseSize = 10);
			virtual ~DynamicArray();

			// set Reserve size
			virtual Result reserve(size_t szReserv);

			// copy operator
			DynamicArray<DataType>& operator = (const Array<DataType>& src) { Array<DataType>::operator = (src); return *this; }
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
			ArrayView(size_t dataCount, DataType* pDataPtr);
			constexpr ArrayView(size_t dataCount, const DataType* pDataPtr);
			template<size_t dataCount>
			constexpr ArrayView(const DataType(&pDataPtr)[dataCount])
			{
				SetLinkedBuffer(dataCount, pDataPtr);
			}

			virtual ~ArrayView();

			void SetLinkedBuffer(size_t maxDataCount, size_t dataCount, DataType* pDataPtr);
			constexpr void SetLinkedBuffer(size_t dataCount, const DataType* pDataPtr);
			void SetLinkedBuffer(const Array<DataType>& srcLink);

			Result reserve(size_t szReserv) override;

			// copy operator
			ArrayView<DataType>& operator = (const Array<DataType>& src) { Array<DataType>::operator = (src); return *this; }
		};




} // namespace SF

#include "SFArray.inl"



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
#include "Container/SFArrayBase.h"
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFIMemoryManager.h"
#include "MemoryManager/SFHeapMemory.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {

	class IHeap;




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
            template<class SrcDataType>
            ArrayView(const Array<SrcDataType>& src)
            {
                // We support force cast for pod types
                if constexpr (std::is_pod_v<SrcDataType> && std::is_pod_v<SrcDataType>)
                {
                    SetLinkedBuffer(src.size(), (DataType*)(src.data()));
                }
                else
                {
                    SetLinkedBuffer(src.size(), static_cast<DataType*>(src.data()));
                }
            }
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



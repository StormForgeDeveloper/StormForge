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




////////////////////////////////////////////////////////////////////////////////
//
//	Generic utility functions
//


// Swap byte of data
uint16_t SwapByte( uint16_t uiData )
{
	return (uint16_t)(((uiData&0xFF00)>>8) | (uiData<<8));
}

uint32_t SwapByte( uint32_t uiData )
{
	return ( uiData<<24 ) | ((uiData&0xFF00)<<16) | ( uiData>>24 ) | ((uiData>>16)&0xFF00);
}

uint64_t SwapByte( uint64_t uiData )
{
	return (((uint64_t)SwapByte((uint32_t)uiData))<<32) | ((uint64_t)SwapByte((uint32_t)(uiData>>32)));
}


template<class DupType>
Result ArrayDup(IHeap& memoryManager, DupType* &pDest, INT iSrcCount, const DupType* pSrc )
{
	if( pDest != NULL )
	{
		IHeap::Delete(pDest);
		pDest = NULL;
	}

	if( pSrc )
	{
		pDest = new(memoryManager) DupType[ iSrcCount ];
		if( pDest == NULL )
			return ResultCode::OUT_OF_MEMORY;

		memcpy( pDest, pSrc, iSrcCount*sizeof(DupType) );
	}

	return ResultCode::SUCCESS;
}



// MemCopy Data to binary
template< size_t szDstSize, class DataType >
Result MemCpy( uint8_t (&Dest)[szDstSize], const DataType& Src )
{
	static_assert( szDstSize >= sizeof(DataType), "Invalid Binary data size" );
	memcpy( Dest, &Src, sizeof(DataType) );
	if( szDstSize < sizeof(DataType) )
		return ResultCode::FAIL;
	return ResultCode::SUCCESS;
}


// MemCopy Data From binary
template< size_t szDstSize, class DataType >
Result MemCpy( DataType& Dest, const uint8_t (&Src)[szDstSize] )
{
	static_assert( szDstSize >= sizeof(DataType), "Invalid Binary data size" );
	memcpy( &Dest, Src, sizeof(DataType) );
	if( szDstSize < sizeof(DataType) )
		return ResultCode::FAIL;
	return ResultCode::SUCCESS;
}


template<class ArrayType>
Result SafeDeleteArray( ArrayType* &pArray )
{
	if( pArray != nullptr )
	{
		IHeap::Delete(pArray);
		pArray = nullptr;
	}

	return ResultCode::SUCCESS;
}

template<class ValueType>
Result SafeDelete( ValueType* &pObj )
{
	if( pObj != nullptr )
	{
		IHeap::Delete(pObj);
		pObj = nullptr;
	}

	return ResultCode::SUCCESS;
}




//template<class ValueType>
//constexpr ValueType Min( ValueType val1, ValueType val2 )
//{
//	return ( ((val1) < (val2)) ? (val1) : (val2) );
//}
//
//template<class ValueType>
//constexpr ValueType Max( ValueType val1, ValueType val2 )
//{
//	return ( ((val1) > (val2)) ? (val1) : (val2) );
//}

//template<class ValType>
//constexpr ValType Abs( ValType value )
//{
//	return value > 0 ? value : -value;
//}
//

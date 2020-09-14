////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Protocol parser helper
//	
//
////////////////////////////////////////////////////////////////////////////////



// parsing helper
template< class SrcType >
void PackParamCopy( uint8_t* &pMsgCur, SrcType* pSrc, size_t iParamSize )
{
	memcpy( pMsgCur, pSrc, iParamSize );
	pMsgCur += iParamSize;
}


// parsing helper
template< class DataType >
Result StreamParamCopy( DataType* pDst, uint8_t* &pMsgCur, INT &iCurMsgSize, size_t iParamSize )
{
	if( iCurMsgSize < (int)iParamSize ) return ResultCode::IO_BADPACKET_SIZE;// sizeCheck

	memcpy( pDst, pMsgCur, iParamSize );

	pMsgCur += iParamSize;
	iCurMsgSize -= (int)iParamSize;

	return ResultCode::SUCCESS;
}

template< class DataType >
Result StreamParamLnk( DataType* &pDst, uint8_t* &pMsgCur, INT &iCurMsgSize, size_t iParamSize )
{
	if( iCurMsgSize < (int)iParamSize ) return ResultCode::IO_BADPACKET_SIZE;// sizeCheck

	if( iParamSize > 0 )
	{
		pDst = (DataType*)pMsgCur;

		pMsgCur += iParamSize;
		iCurMsgSize -= (int)iParamSize;
	}
	else
		pDst = NULL;

	return ResultCode::SUCCESS;
}

template<>
inline Result StreamParamLnk( const char* &pDst, uint8_t* &pMsgCur, INT &iCurMsgSize, size_t iParamSize )
{
	if( iCurMsgSize < (int)iParamSize ) return ResultCode::IO_BADPACKET_SIZE;// sizeCheck

	if( iParamSize > 0 )
	{
		pDst = (char*)pMsgCur;

		pMsgCur += iParamSize;
		iCurMsgSize -= (int)iParamSize;
	}
	else
		pDst = StrUtil::EmptyString;

	return ResultCode::SUCCESS;
}




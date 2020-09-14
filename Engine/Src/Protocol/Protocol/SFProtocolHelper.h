////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Protocol parser helper
//	
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Stream/SFMemoryStream.h"
#include "Net/SFNetDef.h"
#include "String/SFStrUtil.h"
#include "String/SFString.h"
#include "String/SFStringSerialization.h"
#include "Variable/SFVariableSerialization.h"
#include "Container/SFArraySerialization.h"
#include "Util/SFLog.h"
#include "String/SFToStringEngineTypes.h"

namespace SF {
namespace Protocol {


	// parsing helper
	template< class SrcType >
	inline void PackParamCopy( uint8_t* &pMsgCur, SrcType* pSrc, size_t iParamSize );


	// parsing helper
	template< class DataType >
	inline Result StreamParamCopy( DataType* pDst, uint8_t* &pMsgCur, INT &iMsgSize, size_t iParamSize );

	template< class DataType >
	inline Result StreamParamLnk( DataType* &pDst, uint8_t* &pMsgCur, INT &iMsgSize, size_t iParamSize );


#include "SFProtocolHelper.inl"


#define protocolChk(e)			do{ Result hRes = e; if( !(hRes) ) SFErrJmp(Net,hRes); } while(0)
#define protocolChkPtr(e)		do{ if( e == nullptr ) SFErrJmp(Net,ResultCode::INVALID_POINTER); } while(0)
#define protocolMem(a)			do{ if( (a) == nullptr ) SFErrJmp(Net,ResultCode::OUT_OF_MEMORY); } while(0)


#define protocolCheck(e)			do{ hr = e; if(!(hr)) return hr; } while(0)
#define protocolCheckPtr(e)		do{ if( e == nullptr ) { hr = ResultCode::INVALID_POINTER; return hr; } } while(0)
#define protocolCheckMem(a)			do{ if( (a) == nullptr ) { hr = ResultCode::OUT_OF_MEMORY; return hr; } } while(0)



}; // namespace Protocol
}; // SF



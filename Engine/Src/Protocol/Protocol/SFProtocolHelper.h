////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Util/SFStrUtil.h"
#include "Util/SFString.h"
#include "Types/SFEngineTypeSerialization.h"
#include "Types/SFEngineTypeVariable.h"
#include "Variable/SFVariableToString.h"
#include "Util/SFStringSerialization.h"
#include "Variable/SFVariableSerialization.h"
#include "Container/SFArraySerialization.h"
#include "Util/SFLog.h"
#include "Util/SFToStringEngineTypes.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Math/SF3DMathSerialization.h"


namespace SF {
	namespace Protocol {


		#define protocolCheck(e)		do{ hr = e; if(!(hr)) return hr; } while(0)
		#define protocolCheckPtr(e)		do{ if( e == nullptr ) { hr = ResultCode::INVALID_POINTER; return hr; } } while(0)
		#define protocolCheckMem(a)		do{ if( (a) == nullptr ) { hr = ResultCode::OUT_OF_MEMORY; return hr; } } while(0)


	} // namespace Protocol
} // SF



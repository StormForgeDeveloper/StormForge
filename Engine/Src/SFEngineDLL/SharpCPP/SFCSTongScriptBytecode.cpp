////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"



#include "Util/SFLog.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"
#include "Script/Tong/SFTongScriptBytecode.h"


#include "SFCSUtil.h"


namespace SF
{

}

using namespace SF;




//////////////////////////////////////////////////////////////////////////////////////
//
//	Script environment  interface
//

SFDLL_EXPORT Tong::ScriptBytecode* SFTongScriptByteCode_NativeCreate()
{
	Tong::ScriptBytecode* pByteCode = new(GetSystemHeap()) Tong::ScriptBytecode(GetSystemHeap());
	return pByteCode;
}

SFDLL_EXPORT void SFTongScriptByteCode_NativeDelete(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	IHeap::Delete(pScriptByteCode);
}




/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Byte code build
//

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendNoop(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendNoop();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendLabel(uintptr_t nativeHandler, uint32_t labelHash)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendLabel(labelHash);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendExit(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendExit();
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendAdd(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendAdd();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendSub(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendSub();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendMul(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendMul();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendDiv(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendDiv();
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendAddI(uintptr_t nativeHandler, int32_t value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendAddI(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendSubI(uintptr_t nativeHandler, int32_t value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendSubI(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendMulI(uintptr_t nativeHandler, int32_t value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendMulI(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendDivI(uintptr_t nativeHandler, int32_t value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendDivI(value);
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendAddF(uintptr_t nativeHandler, float value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendAddF(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendSubF(uintptr_t nativeHandler, float value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendSubF(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendMulF(uintptr_t nativeHandler, float value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendMulF(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendDivF(uintptr_t nativeHandler, float value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendDivF(value);
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendCmpEqual(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendCmpEqual();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendCmpGreater(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendCmpGreater();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendCmpLess(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendCmpLess();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendCmpGreaterOrEqual(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendCmpGreaterOrEqual();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendCmpLessOrEqual(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendCmpLessOrEqual();
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendJump(uintptr_t nativeHandler, uint32_t label)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendJump(label);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendJumpFalse(uintptr_t nativeHandler, uint32_t label)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendJumpFalse(label);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendYieldFrame(uintptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendYieldFrame();
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendStoreToContext(uintptr_t nativeHandler, const char* name)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendStoreToContext(name);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendStore(uintptr_t nativeHandler, const char* path)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendStore(path);
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendLoadI(uintptr_t nativeHandler, int32_t value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendLoadI(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendLoadF(uintptr_t nativeHandler, float value)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendLoadF(value);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendLoad(uintptr_t nativeHandler, const char* path)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendLoad(path);
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendMoveToContext(uintptr_t nativeHandler, const char* name)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendMoveToContext(name);
}

SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendMove(uintptr_t nativeHandler, const char* path)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendMove(path);
}


SFDLL_EXPORT uint32_t SFTongScriptByteCode_NativeAppendCall(uintptr_t nativeHandler, const char* path)
{
	if (nativeHandler == 0)
		return ResultCode::UNEXPECTED;

	auto pScriptByteCode = reinterpret_cast<Tong::ScriptBytecode*>(nativeHandler);

	return pScriptByteCode->AppendCall(path);
}




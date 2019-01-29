////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TongScript
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

SFDLL_EXPORT ScriptEnvironment* SFTongScript_NativeCreateScriptEnvironment(const char* name)
{
	return Service::ScriptEngine->CreateEnvironment(nullptr, name);
}

SFDLL_EXPORT void SFTongScript_NativeDeleteScriptEnvironment(intptr_t nativeHandler)
{
	if (nativeHandler == 0)
		return;

	auto pScriptEnv = reinterpret_cast<ScriptEnvironment*>(nativeHandler);

	delete pScriptEnv;
}

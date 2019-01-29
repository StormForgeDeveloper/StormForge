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


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFStrUtil.h"
#include "Service/SFScriptService.h"
#include "Script/Tong/SFTongScriptVariable.h"
#include "Script/Tong/SFTongScriptEnvironment.h"



namespace SF
{
	namespace Tong
	{
		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Variable
		//

		ScriptVariable::ScriptVariable(IHeap& heap, ScriptEnvironment* pEnv)
			: SF::ScriptVariable(pEnv)
		{
		}

		ScriptVariable::ScriptVariable(IHeap& heap, ScriptEnvironment* pEnv, const Variable& var)
			: SF::ScriptVariable(pEnv)
			, m_BoxedVariable(var)
		{
		}

		ScriptVariable::~ScriptVariable()
		{

		}



	}

} // namespace SF



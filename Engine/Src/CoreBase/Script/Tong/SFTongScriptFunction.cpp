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
#include "Script/Tong/SFTongScriptEnvironment.h"
#include "Script/Tong/SFTongScriptVariable.h"
#include "Script/Tong/SFTongScriptFunction.h"
#include "Script/Tong/SFTongScriptContext.h"



namespace SF
{
	namespace Tong
	{
		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Variable
		//

		ScriptFunction::ScriptFunction(IHeap& heap, ScriptEnvironment* pEnv)
			: SF::ScriptFunction(pEnv)
			, m_ParameterList(GetEnvironment()->GetHeap())
			, m_ByteCode(GetEnvironment()->GetHeap())
		{
		}

		ScriptFunction::ScriptFunction(IHeap& heap, ScriptEnvironment* pEnv, const Array<ParameterInfo>& parameterList, const Array<uint8_t>& byteCode)
			: SF::ScriptFunction(pEnv)
			, m_ParameterList(GetEnvironment()->GetHeap())
			, m_ByteCode(GetEnvironment()->GetHeap())
		{
			m_ParameterList = parameterList;
			m_ByteCode = byteCode;
		}

		ScriptFunction::~ScriptFunction()
		{

		}


		// Set byte code, binary
		Result ScriptFunction::SetBytecode(const Array<uint8_t>& byteCode)
		{
			m_ByteCode = byteCode;

			return ResultCode::SUCCESS;
		}



		// Call with context
		Result ScriptFunction::CallWithContext(SF::ScriptContext& inContext) const
		{
			ScriptContext& context = static_cast<Tong::ScriptContext&>(inContext);
			auto result = context.PrepareFunctionCall(*this);
			if (!result)
				return result;

			return context.Execute();
		}


		// Format string with argument list
		// Modified buffer pointer and remain buffer size returned to original parameter
		// return used or required string buffer length
		Result ScriptFunction::CallWithParam(const Array<VariableBox>& args) const
		{
			if (args.size() != m_ParameterList.size())
				return ResultCode::INVALID_ARG;

			if (GetEnvironment() == nullptr)
				return ResultCode::INVALID_POINTER;

			ScriptContext context(*static_cast<Tong::ScriptEnvironment*>(GetEnvironment()));
			auto result = context.PrepareFunctionCall(*this);
			if (!result)
				return result;

			return context.Execute();
		}


	}

} // namespace SF



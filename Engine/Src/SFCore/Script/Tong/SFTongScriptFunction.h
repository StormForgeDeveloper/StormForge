////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : StormForge, Tong Script
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Service/SFScriptService.h"
#include "Component/SFLibraryComponent.h"
#include "Container/SFSortedArray.h"
#include "Variable/SFVariable.h"

namespace SF
{

	namespace Tong
	{
		class ScriptEnvironment;
		class ScriptVariable;
		class ScriptBytecode;

		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Function
		//

		class ScriptFunction : public SF::ScriptFunction
		{
		public:

		private:

			// Input Parameter information
			DynamicArray<ParameterInfo> m_ParameterList;

			// byte code
			DynamicArray<uint8_t> m_ByteCode;

		public:

			ScriptFunction(IHeap& heap, ScriptEnvironment* pEnv);
			ScriptFunction(IHeap& heap, ScriptEnvironment* pEnv, const Array<ParameterInfo>& parameterList, const Array<uint8_t>& byteCode);
			~ScriptFunction();


			// Set byte code, binary
			Result SetBytecode(const Array<uint8_t>& byteCode);

			// Get byte code
			const Array<uint8_t>& GetBytecode() const { return m_ByteCode; }


			// Call with context
			virtual Result CallWithContext(SF::ScriptContext& context) const override;

			// Call with variable list
			virtual Result CallWithParam(const Array<VariableBox>& args) const override;
		};

	}
}


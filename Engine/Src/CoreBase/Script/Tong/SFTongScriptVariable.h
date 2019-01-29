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
#include "Object/SFLibraryComponent.h"
#include "Container/SFSortedArray.h"

namespace SF
{

	namespace Tong
	{
		class ScriptEnvironment;
		class ScriptFunction;

		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script variable
		//

		class ScriptVariable : public SF::ScriptVariable
		{
		private:

			VariableBox m_BoxedVariable;

		public:

			ScriptVariable(IHeap& heap, ScriptEnvironment* pEnv);
			ScriptVariable(IHeap& heap, ScriptEnvironment* pEnv, const Variable& var);
			~ScriptVariable();

			// Get variable
			virtual Variable* GetVariable() override
			{
				return m_BoxedVariable.GetVariable();
			}

			// Set variable
			virtual Result SetVariable(const Variable& variable) override
			{
				m_BoxedVariable = variable;

				return ResultCode::SUCCESS;
			}
		};

	}
}

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
#include "SFResult.h"
#include "Service/SFScriptService.h"
#include "Component/SFLibraryComponent.h"
#include "Container/SFSortedArray.h"
#include "Variable/SFVariable.h"
#include "Variable/SFVariableTable.h"
#include "Variable/SFVariableStack.h"


namespace SF
{

	namespace Tong
	{
		class ScriptEnvironment;
		class ScriptVariable;
		class ScriptOpcodeInfo;

		// Byte code operation codes
		enum class SrciptBytecodeOpCode : uint8_t
		{
			NoOp,
			Label,
			Exit,						// Exit the execution
			// arithmetic
			// Pop two values from stack, operate them, and store result to stack
			Add,
			Sub,
			Mul,
			Div,
			// Pop one value from stack and get second value from instruction byte, operate them, and store result to stack
			AddI,
			SubI,
			MulI,
			DivI,

			AddF,
			SubF,
			MulF,
			DivF,

			// compare values and store bool result to stack
			CmpEqual,
			CmpGreater,
			CmpLess,
			CmpGreaterOrEqual,
			CmpLessOrEqual,

			// control
			Jump,						// jump offset from instruction buffer and jump
			JumpFalse,					// pop condition value and jump offset from instruction buffer and jump if false
			YieldFrame,					// Yield current frame and resume next frame

			// Store value to variable
			StoreToContext,				// Get a value from stack and name from instruction, and store named variable to byte code execution context
			Store,						// Get a value from stack and path from instruction, and store named variable to Environment

			// Load value from variable
			Load,						// Load named variable and store to stack
			LoadI,						// Load int constant front instruction and store to stack
			LoadF,						// Load float constant instruction and store stack

			MoveToContext,				// Pop a value and name value from stack, and store named variable to byte code execution context
			MoveToEnvironment,			// Pop a value and path value from stack, and store named variable to Environment

			Call,						// Call sub function

			Max
		};


		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Byte code execution context
		//

		class ScriptContext : public SF::ScriptContext
		{
		public:
			struct PCInfo
			{
				ArrayView<const uint8_t> ByteCodeData;
				int32_t			CurrentPosition = 0;

				PCInfo(void* pInitValue = nullptr) {}
			};

		private:

			VariableStack m_VariableStack;
			VariableTable m_VairableTable;
			StaticArray<PCInfo, 16> m_ControlStack;
			PCInfo m_BytecodeContext;

		public:
			// Constructor
			ScriptContext(ScriptEnvironment& env);
			~ScriptContext();

			// 
			VariableStack& GetVariableStack() { return m_VariableStack; }
			VariableTable& GetVariableTable() { return m_VairableTable; }
			Array<PCInfo>& GetControlStack() { return m_ControlStack; }
			PCInfo& GetBytecodeContext() { return m_BytecodeContext; }

			// Get variable
			// This function searches local context first and environment next
			Variable* GetVariable(const PathString& path);

			// Prepare function call, push current execution PCInfo and set up new one with function name
			// Function parameters should be set up beforehand
			Result PrepareFunctionCall(const ScriptFunction& function);

			// Execute context
			Result Execute();
		};


	}
}


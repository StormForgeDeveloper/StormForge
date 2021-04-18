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
#include "Script/Tong/SFTongScriptContext.h"


namespace SF
{

	namespace Tong
	{
		class ScriptEnvironment;
		class ScriptVariable;
		class ScriptOpcodeInfo;


		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Byte code
		//

		class ScriptOpcodeInfo
		{
		private:
			// operation code
			SrciptBytecodeOpCode m_OpCode;

			// first 2s are input, the last one is for output
			StringCrc64 m_Parameters[3] = { nullptr, nullptr, nullptr };

		public:

			ScriptOpcodeInfo(SrciptBytecodeOpCode opCode, StringCrc64 parameter1, StringCrc64 parameter2, StringCrc64 parameter3)
				: m_OpCode(opCode)
			{
				m_Parameters[0] = parameter1;
				m_Parameters[1] = parameter2;
				m_Parameters[2] = parameter3;
			}

			SrciptBytecodeOpCode GetOpCode() const { return m_OpCode; }
			StringCrc64 GetParameter(int i) const { return m_Parameters[i]; }

			const char* ParseString(ScriptContext& context, int& stringSize) const
			{
				stringSize = context.GetBytecodeContext().ByteCodeData.data()[context.GetBytecodeContext().CurrentPosition];
				auto result = (const char*)&context.GetBytecodeContext().ByteCodeData.data()[context.GetBytecodeContext().CurrentPosition + 1];
				context.GetBytecodeContext().CurrentPosition += 1 + stringSize;
				return result;
			}

			int32_t ParseInt32(ScriptContext& context) const
			{
				auto result = *reinterpret_cast<const int32_t*>(&context.GetBytecodeContext().ByteCodeData.data()[context.GetBytecodeContext().CurrentPosition]);
				context.GetBytecodeContext().CurrentPosition += 4;
				return result;
			}

			uint32_t ParseUInt32(ScriptContext& context) const
			{
				auto result = *reinterpret_cast<const uint32_t*>(&context.GetBytecodeContext().ByteCodeData.data()[context.GetBytecodeContext().CurrentPosition]);
				context.GetBytecodeContext().CurrentPosition += 4;
				return result;
			}

			float ParseFloat(ScriptContext& context) const
			{
				auto result = *reinterpret_cast<const float*>(&context.GetBytecodeContext().ByteCodeData.data()[context.GetBytecodeContext().CurrentPosition]);
				context.GetBytecodeContext().CurrentPosition += 4;
				return result;
			}

			virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const = 0;
			virtual Result Execute(ScriptContext& context) const = 0;
		};


		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Byte code
		//

		class ScriptBytecode
		{
		public:

			typedef SrciptBytecodeOpCode OpCode;
			typedef Array<uint8_t>::iterator iterator;

		private:

			// byte code
			DynamicArray<uint8_t> m_ByteCode;

		public:

			// Constructor/Destructor
			ScriptBytecode(IHeap& heap);

			// @heap: heap for instance
			// @byteCode: bytecode binary
			ScriptBytecode(IHeap& heap, const Array<uint8_t>& byteCode);
			~ScriptBytecode();

			// Set byte code, binary
			Result SetBytecode(const Array<uint8_t>& byteCode);

			const Array<uint8_t>& GetBytecode() const { return m_ByteCode; }



			/////////////////////////////////////////////////////////////////////////////////////////////
			//
			//	Byte code build
			//

			Result AppendNoop();
			Result AppendLabel(StringCrc32 label);
			Result AppendExit();

			Result AppendAdd();
			Result AppendSub();
			Result AppendMul();
			Result AppendDiv();

			Result AppendAddI(int32_t value);
			Result AppendSubI(int32_t value);
			Result AppendMulI(int32_t value);
			Result AppendDivI(int32_t value);

			Result AppendAddF(float value);
			Result AppendSubF(float value);
			Result AppendMulF(float value);
			Result AppendDivF(float value);

			Result AppendCmpEqual();
			Result AppendCmpGreater();
			Result AppendCmpLess();
			Result AppendCmpGreaterOrEqual();
			Result AppendCmpLessOrEqual();

			Result AppendJump(StringCrc32 label);
			Result AppendJumpFalse(StringCrc32 label);
			Result AppendYieldFrame();

			Result AppendStoreToContext(const char* name);
			Result AppendStore(const char* path);

			Result AppendLoadI(int32_t value);
			Result AppendLoadF(float value);
			Result AppendLoad(const char* path);

			Result AppendMoveToContext(const char* name);
			Result AppendMove(const char* path);

			Result AppendCall(const char* path);


			// Utility functions
			Result AppendInt32(int32_t value);
			Result AppendFloat(float value);
			Result AppendString(const char* value);


			/////////////////////////////////////////////////////////////////////////////////////////////
			//
			//	Iterator support
			//
			iterator begin() { return m_ByteCode.begin(); }
			const iterator begin() const { return m_ByteCode.begin(); }
			iterator end() { return m_ByteCode.end(); }
			const iterator end() const { return m_ByteCode.end(); }
		};

	}
}


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


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFStrUtil.h"
#include "Service/SFScriptService.h"
#include "Script/Tong/SFTongScriptEnvironment.h"
#include "Script/Tong/SFTongScriptVariable.h"
#include "Script/Tong/SFTongScriptBytecode.h"
#include "Script/Tong/SFTongScriptBytecodeOpCode.h"


namespace SF
{
	namespace Tong
	{



		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Opcode table
		//

		namespace Impl 
		{

			const ScriptOpcodeInfo* ScriptBytecode_OpCodeTable[] =
			{
				Impl::ScriptOpcodeInfoNoOp::GetInstance(),
				Impl::ScriptOpcodeInfoLabel::GetInstance(),
				Impl::ScriptOpcodeInfoExit::GetInstance(),

				// Arithmetic
				// Pop two values from stack, operate them, and store result to stack
				Impl::ScriptOpcodeInfoAdd::GetInstance(),
				Impl::ScriptOpcodeInfoSub::GetInstance(),
				Impl::ScriptOpcodeInfoMul::GetInstance(),
				Impl::ScriptOpcodeInfoDiv::GetInstance(),

				Impl::ScriptOpcodeInfoAddI::GetInstance(),
				Impl::ScriptOpcodeInfoSubI::GetInstance(),
				Impl::ScriptOpcodeInfoMulI::GetInstance(),
				Impl::ScriptOpcodeInfoDivI::GetInstance(),

				Impl::ScriptOpcodeInfoAddF::GetInstance(),
				Impl::ScriptOpcodeInfoSubF::GetInstance(),
				Impl::ScriptOpcodeInfoMulF::GetInstance(),
				Impl::ScriptOpcodeInfoDivF::GetInstance(),

				// compare values and store bool result to stack
				Impl::ScriptOpcodeInfoCmpEqual::GetInstance(),
				Impl::ScriptOpcodeInfoCmpGreater::GetInstance(),
				Impl::ScriptOpcodeInfoCmpLess::GetInstance(),
				Impl::ScriptOpcodeInfoCmpGreaterOrEqual::GetInstance(),
				Impl::ScriptOpcodeInfoCmpLessOrEqual::GetInstance(),

				// control
				Impl::ScriptOpcodeInfoJump::GetInstance(),
				Impl::ScriptOpcodeInfoJumpFalse::GetInstance(),
				Impl::ScriptOpcodeInfoYieldFrame::GetInstance(),


				// Store value to variable
				Impl::ScriptOpcodeInfoStoreToContext::GetInstance(),
				Impl::ScriptOpcodeInfoStore::GetInstance(),

				// Load value from variable
				Impl::ScriptOpcodeInfoLoad::GetInstance(),
				Impl::ScriptOpcodeInfoLoadI::GetInstance(),
				Impl::ScriptOpcodeInfoLoadF::GetInstance(),

				// Move value to variable
				Impl::ScriptOpcodeInfoMoveToContext::GetInstance(),
				Impl::ScriptOpcodeInfoMoveToEnvironment::GetInstance(),

				Impl::ScriptOpcodeInfoCall::GetInstance(),
			};

		}



		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Variable
		//

		ScriptBytecode::ScriptBytecode(IHeap& heap)
			: m_ByteCode(heap)
		{
		}

		ScriptBytecode::ScriptBytecode(IHeap& heap, const Array<uint8_t>& byteCode)
			: m_ByteCode(heap)
		{
			SetBytecode(byteCode);
		}

		ScriptBytecode::~ScriptBytecode()
		{
		}

		// Set byte code, binary
		Result ScriptBytecode::SetBytecode(const Array<uint8_t>& byteCode)
		{
			m_ByteCode = byteCode;

			return ResultCode::SUCCESS;
		}


		/////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Byte code build
		//

		Result ScriptBytecode::AppendNoop()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::NoOp);
		}

		Result ScriptBytecode::AppendLabel(FixedString32 label)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Label);
			if (!result)
				return result;

			return AppendInt32(label);
		}

		Result ScriptBytecode::AppendExit()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Exit);
		}

		Result ScriptBytecode::AppendAdd()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Add);
		}

		Result ScriptBytecode::AppendSub()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Sub);
		}

		Result ScriptBytecode::AppendMul()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Mul);
		}

		Result ScriptBytecode::AppendDiv()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Div);
		}

		Result ScriptBytecode::AppendAddI(int32_t value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::AddI);
			if (!result)
				return result;

			return AppendInt32(value);
		}

		Result ScriptBytecode::AppendSubI(int32_t value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::SubI);
			if (!result)
				return result;

			return AppendInt32(value);
		}

		Result ScriptBytecode::AppendMulI(int32_t value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::MulI);
			if (!result)
				return result;

			return AppendInt32(value);
		}

		Result ScriptBytecode::AppendDivI(int32_t value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::DivI);
			if (!result)
				return result;

			return AppendInt32(value);
		}

		Result ScriptBytecode::AppendAddF(float value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::AddF);
			if (!result)
				return result;

			return AppendFloat(value);
		}

		Result ScriptBytecode::AppendSubF(float value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::SubF);
			if (!result)
				return result;

			return AppendFloat(value);
		}

		Result ScriptBytecode::AppendMulF(float value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::MulF);
			if (!result)
				return result;

			return AppendFloat(value);
		}

		Result ScriptBytecode::AppendDivF(float value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::DivF);
			if (!result)
				return result;

			return AppendFloat(value);
		}

		Result ScriptBytecode::AppendCmpEqual()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::CmpEqual);
		}

		Result ScriptBytecode::AppendCmpGreater()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::CmpGreater);
		}

		Result ScriptBytecode::AppendCmpLess()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::CmpLess);
		}

		Result ScriptBytecode::AppendCmpGreaterOrEqual()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::CmpGreaterOrEqual);
		}

		Result ScriptBytecode::AppendCmpLessOrEqual()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::CmpLessOrEqual);
		}


		Result ScriptBytecode::AppendJump(FixedString32 label)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Jump);
			if (!result)
				return result;

			return AppendInt32(label);
		}

		Result ScriptBytecode::AppendJumpFalse(FixedString32 label)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::JumpFalse);
			if (!result)
				return result;

			return AppendInt32(label);
		}

		Result ScriptBytecode::AppendYieldFrame()
		{
			return m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::YieldFrame);
		}


		Result ScriptBytecode::AppendStoreToContext(const char* name)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::StoreToContext);
			if (!result)
				return result;

			return AppendString(name);
		}

		Result ScriptBytecode::AppendStore(const char* path)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Store);
			if (!result)
				return result;

			return AppendString(path);
		}


		Result ScriptBytecode::AppendLoadI(int32_t value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::LoadI);
			if (!result)
				return result;

			return AppendInt32(value);
		}

		Result ScriptBytecode::AppendLoadF(float value)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::LoadF);
			if (!result)
				return result;

			return AppendFloat(value);
		}

		Result ScriptBytecode::AppendLoad(const char* path)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Load);
			if (!result)
				return result;

			return AppendString(path);
		}


		Result ScriptBytecode::AppendMoveToContext(const char* name)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::MoveToContext);
			if (!result)
				return result;

			return AppendString(name);
		}

		Result ScriptBytecode::AppendMove(const char* path)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::MoveToEnvironment);
			if (!result)
				return result;

			return AppendString(path);
		}

		Result ScriptBytecode::AppendCall(const char* path)
		{
			auto result = m_ByteCode.push_back((uint8_t)SrciptBytecodeOpCode::Call);
			if (!result)
				return result;

			return AppendString(path);
		}


		// Utility functions
		Result ScriptBytecode::AppendInt32(int32_t value)
		{
			uint8_t* pValue = (uint8_t*)&value;
			return m_ByteCode.push_back(4, pValue);
		}

		Result ScriptBytecode::AppendFloat(float value)
		{
			uint8_t* pValue = (uint8_t*)&value;
			return m_ByteCode.push_back(4, pValue);
		}

		Result ScriptBytecode::AppendString(const char* value)
		{
			auto szString = strlen(value) + 1;
			if (szString > std::numeric_limits<uint8_t>::max())
				return ResultCode::INVALID_STR_DATA;

			auto result = m_ByteCode.push_back((uint8_t)szString);
			if (!result)
				return result;

			return m_ByteCode.push_back(szString, reinterpret_cast<const uint8_t*>(value));
		}



	}

} // namespace SF



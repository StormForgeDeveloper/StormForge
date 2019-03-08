////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Storm Forge, Tong Script, opcode descriptions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Service/SFScriptService.h"
#include "Object/SFLibraryComponent.h"
#include "Container/SFSortedArray.h"
#include "Script/Tong/SFTongScriptByteCode.h"

namespace SF
{
	namespace Tong
	{
		namespace Impl
		{

			//////////////////////////////////////////////////////////////////////////
			//
			//	NoOp
			//
			class ScriptOpcodeInfoNoOp : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoNoOp()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::NoOp, nullptr, nullptr, nullptr )
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoNoOp instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					return ResultCode::SUCCESS;
				}
			};


			//////////////////////////////////////////////////////////////////////////
			//
			//	Label
			//
			class ScriptOpcodeInfoLabel : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoLabel()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Label, nullptr, nullptr, nullptr)
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoNoOp instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 4;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition+=4;
					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	Add
			//
			class ScriptOpcodeInfoAdd : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoAdd()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Add, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoAdd instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() + pVarB->GetValue<int>());
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() + pVarB->GetValue<uint32_t>());
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() + pVarB->GetValue<int64_t>());
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() + pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() + pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() + pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};




			//////////////////////////////////////////////////////////////////////////
			//
			//	Sub
			//
			class ScriptOpcodeInfoSub : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoSub()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Sub, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoSub instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() - pVarB->GetValue<int>());
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() - pVarB->GetValue<uint32_t>());
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() - pVarB->GetValue<int64_t>());
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() - pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() - pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() - pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};




			//////////////////////////////////////////////////////////////////////////
			//
			//	Mul
			//
			class ScriptOpcodeInfoMul : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoMul()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Mul, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoMul instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() * pVarB->GetValue<int>());
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() * pVarB->GetValue<uint32_t>());
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() * pVarB->GetValue<int64_t>());
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() * pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() * pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() * pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	Div
			//
			class ScriptOpcodeInfoDiv : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoDiv()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Div, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoDiv instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() / pVarB->GetValue<int>());
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() / pVarB->GetValue<uint32_t>());
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() / pVarB->GetValue<int64_t>());
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() / pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() / pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() / pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};




			//////////////////////////////////////////////////////////////////////////
			//
			//	Add
			//
			class ScriptOpcodeInfoAddI : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoAddI()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::AddI, "stack", "int32", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoAddI instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseUInt32(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() + opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() + opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() + opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() + opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() + opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() + opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};




			//////////////////////////////////////////////////////////////////////////
			//
			//	Sub
			//
			class ScriptOpcodeInfoSubI : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoSubI()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::SubI, "stack", "int32", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoSubI instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseUInt32(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() - opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() - opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() - opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() - opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() - opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() - opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};




			//////////////////////////////////////////////////////////////////////////
			//
			//	Mul
			//
			class ScriptOpcodeInfoMulI : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoMulI()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::MulI, "stack", "int32", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoMulI instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseUInt32(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() * opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() * opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() * opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() * opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() * opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() * opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	Div
			//
			class ScriptOpcodeInfoDivI : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoDivI()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::DivI, "stack", "int32", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoDivI instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1 + 4;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseUInt32(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() / opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() / opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() / opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() / opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() / opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() / opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	Add
			//
			class ScriptOpcodeInfoAddF : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoAddF()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::AddI, "stack", "float", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoAddF instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseFloat(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() + opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() + opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() + opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() + opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() + opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() + opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};




			//////////////////////////////////////////////////////////////////////////
			//
			//	Sub
			//
			class ScriptOpcodeInfoSubF : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoSubF()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::SubF, "stack", "float", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoSubF instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseFloat(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() - opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() - opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() - opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() - opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() - opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() - opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};




			//////////////////////////////////////////////////////////////////////////
			//
			//	Mul
			//
			class ScriptOpcodeInfoMulF : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoMulF()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::MulI, "stack", "float", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoMulF instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseFloat(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() * opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() * opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() * opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() * opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() * opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() * opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	Div
			//
			class ScriptOpcodeInfoDivF : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoDivF()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::DivI, "stack", "float", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoDivF instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1 + 4;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseFloat(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableBool::TYPE_NAME:
					case VariableResult::TYPE_NAME:
					case VariableInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() / opB);
						break;
					case VariableUInt::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint32_t>() / opB);
						break;
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int64_t>() / opB);
						break;
					case VariableVoidP::TYPE_NAME:
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() / opB);
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() / opB);
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() / opB);
						break;
					}

					context.GetVariableStack().Pop();
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	Equal
			//
			class ScriptOpcodeInfoCmpEqual : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoCmpEqual()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::CmpEqual, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoCmpEqual instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableInt::TYPE_NAME:
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() == pVarB->GetValue<int>());
						break;
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() == pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() == pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() == pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	Greater
			//
			class ScriptOpcodeInfoCmpGreater : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoCmpGreater()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::CmpGreater, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoCmpGreater instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableInt::TYPE_NAME:
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() > pVarB->GetValue<int>());
						break;
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() > pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() > pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() > pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	Less
			//
			class ScriptOpcodeInfoCmpLess : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoCmpLess()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::CmpLess, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoCmpLess instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableInt::TYPE_NAME:
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() < pVarB->GetValue<int>());
						break;
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() < pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() < pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() < pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	GreaterOrEqual
			//
			class ScriptOpcodeInfoCmpGreaterOrEqual : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoCmpGreaterOrEqual()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::CmpGreaterOrEqual, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoCmpGreaterOrEqual instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableInt::TYPE_NAME:
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() >= pVarB->GetValue<int>());
						break;
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() >= pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() >= pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() >= pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	CmpLessOrEqual
			//
			class ScriptOpcodeInfoCmpLessOrEqual : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoCmpLessOrEqual()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::CmpLessOrEqual, "stack", "stack", "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoCmpLessOrEqual instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(1);
					auto pVarB = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr || pVarB == nullptr)
						return ResultCode::INVALID_POINTER;

					VariableBox result;

					switch (pVarA->GetTypeName())
					{
					case VariableInt::TYPE_NAME:
					case VariableInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<int>() <= pVarB->GetValue<int>());
						break;
					case VariableUInt64::TYPE_NAME:
						result = Boxing(pVarA->GetValue<uint64_t>() <= pVarB->GetValue<uint64_t>());
						break;
					case VariableFloat::TYPE_NAME:
					case VariableDouble::TYPE_NAME:
						result = Boxing(pVarA->GetValue<double>() <= pVarB->GetValue<double>());
						break;
					default:
						result = Boxing(pVarA->GetValue<int64_t>() <= pVarB->GetValue<int64_t>());
						break;
					}

					context.GetVariableStack().Pop(2);
					context.GetVariableStack().Push(*result.GetVariable());

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	Jump
			//
			class ScriptOpcodeInfoJump : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoJump()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Jump, "int32", nullptr, nullptr)
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoJump instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto jumpAddr = ParseUInt32(context);

					context.GetBytecodeContext().CurrentPosition = jumpAddr;
					Assert(context.GetBytecodeContext().CurrentPosition > 0);

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	JumpFalse
			//
			class ScriptOpcodeInfoJumpFalse : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoJumpFalse()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::JumpFalse, "stack", nullptr, nullptr)
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoJumpFalse instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 5;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto jumpAddr = ParseUInt32(context);

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					bool jump = pVarA == nullptr || !pVarA->GetValue<bool>();
					context.GetVariableStack().Pop();

					if (jump)
					{
						context.GetBytecodeContext().CurrentPosition = jumpAddr;
						Assert(context.GetBytecodeContext().CurrentPosition > 0 && context.GetBytecodeContext().CurrentPosition < context.GetBytecodeContext().ByteCodeData->size())
					}

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	Exit
			//
			class ScriptOpcodeInfoExit : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoExit()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Exit, "stack", nullptr, nullptr)
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoExit instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition = (int)context.GetBytecodeContext().ByteCodeData->size();
					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	StoreToContext
			//
			class ScriptOpcodeInfoStoreToContext : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoStoreToContext()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::StoreToContext, "stack", nullptr, "context")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoStoreToContext instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes);
					auto sizeOfName = byteCode[0];
					return 2 + sizeOfName;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_BYTE_SEQUENCE;

					int sizeOfName = 0;
					auto strName = ParseString(context, sizeOfName);

					context.GetVariableTable().SetVariable(strName, *pVarA);

					// Don't pop
					//context.GetVariableStack().Pop(1);

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	Store
			//
			class ScriptOpcodeInfoStore : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoStore()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Store, "stack", nullptr, "path")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoStore instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes);
					auto sizeOfName = byteCode[0];
					return 2 + sizeOfName;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_BYTE_SEQUENCE;

					int sizeOfName = 0;
					auto strName = ParseString(context, sizeOfName);

					context.GetEnvironment().SetVariable(PathString(strName), *pVarA);

					// Don't pop
					//context.GetVariableStack().Pop(1);

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	Load
			//
			class ScriptOpcodeInfoLoad : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoLoad()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Load, "path", nullptr, "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoLoad instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes);
					auto sizeOfName = byteCode[0];
					return 2 + sizeOfName;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					int sizeOfName = 0;
					auto strName = ParseString(context, sizeOfName);

					auto pVar = context.GetVariable(strName);
					if (pVar == nullptr)
						pVar = context.GetEnvironment().GetVariable(PathString(strName));

					if (pVar == nullptr)
						return ResultCode::VARIABLE_NOT_FOUND;

					context.GetVariableStack().Push(*pVar);


					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	Yield
			//
			class ScriptOpcodeInfoYieldFrame : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoYieldFrame()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::YieldFrame, "path", nullptr, "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoYieldFrame instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					return ResultCode::SUCCESS_YIELD;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	LoadI
			//
			class ScriptOpcodeInfoLoadI : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoLoadI()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::LoadI, "int", nullptr, "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoLoadI instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1 + 4;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseUInt32(context);

					context.GetVariableStack().PushValue(opB);

					return ResultCode::SUCCESS;
				}
			};






			//////////////////////////////////////////////////////////////////////////
			//
			//	LoadF
			//
			class ScriptOpcodeInfoLoadF : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoLoadF()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::LoadF, "float", nullptr, "stack")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoLoadF instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes, byteCode);
					return 1 + 4;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;
					auto opB = ParseFloat(context);

					context.GetVariableStack().PushValue(opB);

					return ResultCode::SUCCESS;
				}
			};





			//////////////////////////////////////////////////////////////////////////
			//
			//	MoveToContext
			//
			class ScriptOpcodeInfoMoveToContext : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoMoveToContext()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::MoveToContext, "stack", nullptr, "context")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoMoveToContext instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes);
					auto sizeOfName = byteCode[0];
					return 2 + sizeOfName;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_BYTE_SEQUENCE;

					int sizeOfName = 0;
					auto strName = ParseString(context, sizeOfName);

					context.GetVariableTable().SetVariable(strName, *pVarA);

					context.GetVariableStack().Pop(1);

					return ResultCode::SUCCESS;
				}
			};



			//////////////////////////////////////////////////////////////////////////
			//
			//	MoveToEnvironment
			//
			class ScriptOpcodeInfoMoveToEnvironment : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoMoveToEnvironment()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::MoveToEnvironment, "stack", nullptr, "path")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoMoveToEnvironment instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes);
					auto sizeOfName = byteCode[0];
					return 2 + sizeOfName;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					auto pVarA = context.GetVariableStack().GetFromFront(0);
					if (pVarA == nullptr)
						return ResultCode::INVALID_BYTE_SEQUENCE;

					int sizeOfName = 0;
					auto strName = ParseString(context, sizeOfName);

					context.GetEnvironment().SetVariable(PathString(strName), *pVarA);

					context.GetVariableStack().Pop(1);

					return ResultCode::SUCCESS;
				}
			};


			//////////////////////////////////////////////////////////////////////////
			//
			//	Call Function
			//
			class ScriptOpcodeInfoCall : public ScriptOpcodeInfo
			{
			public:
				ScriptOpcodeInfoCall()
					: ScriptOpcodeInfo(SrciptBytecodeOpCode::Call, nullptr, nullptr, "path")
				{}

				static ScriptOpcodeInfo* GetInstance() { static ScriptOpcodeInfoCall instance; return &instance; }

				virtual size_t GetSize(uint32_t remainBytes, const uint8_t* byteCode) const override
				{
					unused(remainBytes);
					auto sizeOfName = byteCode[0];
					return 2 + sizeOfName;
				}

				virtual Result Execute(ScriptContext& context)  const override
				{
					context.GetBytecodeContext().CurrentPosition++;

					int sizeOfName = 0;
					auto strName = ParseString(context, sizeOfName);

					auto pFunc = context.GetEnvironment().GetFunction(PathString(strName));
					if (pFunc == nullptr)
						return ResultCode::FUNCTION_NOT_FOUND;

					auto result = pFunc->CallWithContext(context);
					if (!result)
						return result;

					return ResultCode::SUCCESS;
				}
			};




			// opcode table
			extern const ScriptOpcodeInfo* ScriptBytecode_OpCodeTable[];
		}
	}
}


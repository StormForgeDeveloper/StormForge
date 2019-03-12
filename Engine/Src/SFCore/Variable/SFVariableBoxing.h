////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : VariableBox - Implementation of box/unboxing without micro allocation
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFToStringBase.h"
#include "Variable/SFVariable.h"


namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	// VariableBox 
	// 
	class VariableBox
	{
	public:
		// assuming all values can be contained in 32 bytes
		static constexpr int BUFFER_SIZE = 32;

	private:
		StaticArray<uint8_t, BUFFER_SIZE> m_DataBuffer;

		Variable* m_pVariable = nullptr;

	public:

		VariableBox();
		VariableBox(const VariableBox& src);
		VariableBox(const Variable& src);

		~VariableBox();

		Variable* GetVariable() const { return m_pVariable; }

		VariableBox& operator = (const VariableBox& src);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Boxing/Unboxing interfaces
	//


	template<> inline VariableBox DefaultValue<VariableBox>() { static VariableBox dummy; return dummy; }

	// Boxing
	//template<class ValueType>
	//VariableBox Boxing(ValueType value);

	// always boxing by binary value
	template<class ValueType>
	VariableBox BoxingByValue(ValueType value)
	{
		VariableByBinaryValue<ValueType> variable(value);
		return VariableBox(variable);
	}


	template<class ValueType>
	ValueType Unboxing(const VariableBox& box)
	{
		auto pVar = box.GetVariable();
		if (pVar == nullptr)
			return DefaultValue<ValueType>();

		return pVar->GetValue<ValueType>();
	}

	template<class ValueType>
	ValueType* UnboxingReference(const VariableBox& box)
	{
		auto pVar = box.GetVariable();
		if (pVar == nullptr || pVar->GetDataPtr() == nullptr)
			return nullptr;

		return reinterpret_cast<ValueType*>(pVar->GetDataPtr());
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Boxing/Unboxing define macros
	//

#define DEFINE_BOXING_TEMPLETE(varType, varClassType)	\
	inline VariableBox Boxing(varType src) { varClassType variable(src); return VariableBox(variable); }\
	template<> inline VariableBox BoxingByValue<varType>(varType src) { varClassType variable(src); return VariableBox(variable); }\
	inline VariableBox Boxing(Array<varType>& src) { VariableValueReference<Array<varType>> variable(src); return VariableBox(variable); }\
	inline VariableBox Boxing(const Array<varType>& src) { VariableValueReference<Array<varType>> variable(src); return VariableBox(variable); }\
	template<> inline Result VariableValueReference<Array<varType>>::ToString(ToStringContext& context) const\
	{\
		if (m_Value == nullptr) return ResultCode::FAIL;\
		int iNumEle = 0;\
		for (auto& itValue : *m_Value)\
		{\
			varClassType eleRef(itValue);\
			auto result = eleRef.ToString(context);\
			if (!result) return result;\
			iNumEle++; if (iNumEle >= context.MaxArraySize) break;\
		}\
		return ResultCode::SUCCESS;\
	}\

#define DEFINE_BOXING_TEMPLETE_BYVALUE(varType)	\
	inline VariableBox Boxing(const varType& src) { VariableByBinaryValue<varType> variable(src); return VariableBox(variable); } \
	template<> inline FixedString VariableByBinaryValue<varType>::GetTypeName() const { return #varType; }\
	inline VariableBox Boxing(Array<varType>& src) { VariableValueReference<Array<varType>> variable(src); return VariableBox(variable); }\
	inline VariableBox Boxing(const Array<varType>& src) { VariableValueReference<Array<varType>> variable(src); return VariableBox(variable); }\
	template<> inline Result VariableValueReference<Array<varType>>::ToString(ToStringContext& context) const\
	{\
		if (m_Value == nullptr) return ResultCode::FAIL;\
		int iNumEle = 0;\
		for (auto& itValue : *m_Value)\
		{\
			VariableByBinaryValue<varType> eleRef(itValue);\
			auto result = eleRef.ToString(context);\
			if (!result) return result;\
			iNumEle++; if (iNumEle >= context.MaxArraySize) break;\
		}\
		return ResultCode::SUCCESS;\
	}\



#define DEFINE_BOXING_TEMPLETE_BYREFERENCE(varType)					\
	inline VariableBox Boxing(const varType& src) { VariableValueReference<varType> variable(src); return VariableBox(variable); }\
	inline VariableBox Boxing(varType& src) { VariableValueReference<varType> variable(src); return VariableBox(variable); }\
	inline VariableBox Boxing(const Array<varType>& src) { VariableValueReference<Array<varType>> variable(src); return VariableBox(variable); }\
	template<> inline FixedString VariableValueReference<varType>::GetTypeName() const { return #varType; }\
	template<> inline Result VariableValueReference<Array<varType>>::ToString(ToStringContext& context) const\
	{\
		if (m_Value == nullptr) return ResultCode::FAIL;\
		int iNumEle = 0;\
		for (auto& itValue : *m_Value)\
		{\
			VariableValueReference<varType> eleRef(itValue);\
			auto result = eleRef.ToString(context);\
			if (!result) return result;\
			iNumEle++; if (iNumEle >= context.MaxArraySize) break;\
		}\
		return ResultCode::SUCCESS;\
	}\




	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Default platform types
	//



	DEFINE_BOXING_TEMPLETE(bool, VariableBool);
	DEFINE_BOXING_TEMPLETE(int8_t, VariableInt);
	DEFINE_BOXING_TEMPLETE(uint8_t, VariableUInt);
	DEFINE_BOXING_TEMPLETE(int16_t, VariableInt);
	DEFINE_BOXING_TEMPLETE(uint16_t, VariableUInt);
	DEFINE_BOXING_TEMPLETE(int32_t, VariableInt);
	DEFINE_BOXING_TEMPLETE(uint32_t, VariableUInt);
	DEFINE_BOXING_TEMPLETE(int64_t, VariableInt64);
	DEFINE_BOXING_TEMPLETE(uint64_t, VariableUInt64);
	DEFINE_BOXING_TEMPLETE(float, VariableFloat);
	DEFINE_BOXING_TEMPLETE(double, VariableDouble);
	DEFINE_BOXING_TEMPLETE(const char*, VariableCharString);
	DEFINE_BOXING_TEMPLETE(char*, VariableCharString);
	DEFINE_BOXING_TEMPLETE(void*, VariableVoidP);
	DEFINE_BOXING_TEMPLETE(const wchar_t*, VariableWCharString);
	DEFINE_BOXING_TEMPLETE(wchar_t*, VariableWCharString);
	DEFINE_BOXING_TEMPLETE(String, VariableString);
	DEFINE_BOXING_TEMPLETE(FixedString, VariableFixedString);
	DEFINE_BOXING_TEMPLETE(FixedString32, VariableFixedString32);
	DEFINE_BOXING_TEMPLETE(Result, VariableResult);

	// They comes from OS system types, but not referenced by std types on windows(VC compiler)
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	DEFINE_BOXING_TEMPLETE(long, VariableInt);
	DEFINE_BOXING_TEMPLETE(unsigned long, VariableUInt);
#endif





	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	String class method
	//	  - They are here because we need them defined after boxing/unboxing, but main body of string should be defined before hand
	//

		// Format string
	template< class ...ArgTypes >
	inline String& String::Format(const char* strFormat, ArgTypes... args)
	{
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		Format_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}

	// Format string
	template< class ...ArgTypes >
	inline String& String::AppendFormat(const char* strFormat, ArgTypes... args)
	{
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		AppendFormat_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}


}; // namespace StrUtil




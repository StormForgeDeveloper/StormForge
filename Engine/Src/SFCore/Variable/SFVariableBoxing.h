////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Util/SFToStringBase.h"
#include "Variable/SFVariableCommonDefs.h"
#include "Stream/SFStream.h"


namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	// VariableBox 
	// 
	class SF_DECLARE_ALIGN_DOUBLE VariableBox
	{
	public:
		// assuming all values can be contained in 32 bytes and extra space for alignment
		static constexpr int BUFFER_SIZE = 32 + SF_ALIGN_DOUBLE;

	private:
		StaticArray<uint8_t, BUFFER_SIZE> m_DataBuffer;

		Variable* m_pVariable = nullptr;

	public:

		VariableBox();
		VariableBox(const VariableBox& src);
		VariableBox(const Variable& src);

		~VariableBox();


		// Set variable type. It will destroy previous variable
		bool SetVariableType(StringCrc32 TypeName);

		Variable* GetVariable() const { return m_pVariable; }

		explicit operator Variable*() { return m_pVariable; }

		VariableBox& operator = (const VariableBox& src);
	};



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Boxing/Unboxing interfaces
	//


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
			return ValueType{};

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
	inline VariableBox BoxingByValue(const std::decay_t<varType>& src) { varClassType variable(src); return VariableBox(variable); } \
	inline VariableBox BoxingByValue(std::decay_t<varType>&& src) { varClassType variable(src); return VariableBox(variable); } \
	inline VariableBox BoxingByReference(const std::decay_t<varType>& src) { VariableValueReference<std::decay_t<varType>> variable(src); return VariableBox(variable); }\
	inline VariableBox BoxingByReference(const Array<std::decay_t<varType>>& src) { VariableValueReference<Array<std::decay_t<varType>>> variable(src); return VariableBox(variable); }\
	inline VariableBox Boxing(const std::decay_t<varType>& src) { varClassType variable(src); return VariableBox(variable); } \
	inline VariableBox Boxing(std::decay_t<varType>&& src) { varClassType variable(src); return VariableBox(variable); } \
	inline VariableBox Boxing(const Array<std::decay_t<varType>>& src) { VariableValueReference<Array<std::decay_t<varType>>> variable(src); return VariableBox(variable); }\
	template<> inline StringCrc32 VariableByBinaryValue<std::decay_t<varType>>::GetTypeName() const { return #varType; }\
	template<> inline StringCrc32 VariableValueReference<std::decay_t<varType>>::GetTypeName() const { return #varType; }\
	template<> inline StringCrc32 VariableValueReference<Array<std::decay_t<varType>>>::GetTypeName() const { return "Array<"#varType">"; }\
	template<> inline Result VariableValueReference<Array<std::decay_t<varType>>>::ToString(ToStringContext& context) const\
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


	//inline VariableBox Boxing(Array<varType>& src) { VariableValueReference<Array<varType>> variable(src); return VariableBox(variable); }\

#define IMPLEMENT_BOXING_TEMPLATE_INTERNAL(varType, DefaultVariableValueType) \
	template<> inline StringCrc32 VariableByBinaryValue<std::decay_t<varType>>::GetTypeName() const { return #varType; }\
	template<> inline StringCrc32 VariableValueReference<std::decay_t<varType>>::GetTypeName() const { return #varType; }\
	template<> inline StringCrc32 VariableValueReference<Array<std::decay_t<varType>>>::GetTypeName() const { return "Array<"#varType">"; }\
	template<> inline Result VariableValueReference<Array<varType>>::ToString(ToStringContext& context) const\
	{\
		if (m_Value == nullptr) return ResultCode::FAIL; \
			int iNumEle = 0; \
			for (auto& itValue : *m_Value)\
			{\
				DefaultVariableValueType eleRef(itValue); \
				auto result = eleRef.ToString(context); \
				if (!result) return result; \
					iNumEle++; if (iNumEle >= context.MaxArraySize) break; \
			}\
				return ResultCode::SUCCESS; \
	}\


#define DECLARE_BOXING_TEMPLETE_BYVALUE(varType)	\
	VariableBox BoxingByValue(const std::decay_t<varType>& src);\
	VariableBox BoxingByValue(std::decay_t<varType>&& src);\
	VariableBox BoxingByReference(const std::decay_t<varType>& src);\
	VariableBox BoxingByReference(const Array<std::decay_t<varType>>& src);\
	VariableBox Boxing(const std::decay_t<varType>& src); \
	VariableBox Boxing(std::decay_t<varType>&& src); \
	VariableBox Boxing(Array<std::decay_t<varType>>& src);\
	VariableBox Boxing(const Array<std::decay_t<varType>>& src);\
	IMPLEMENT_BOXING_TEMPLATE_INTERNAL(varType, VariableByBinaryValue<varType>)


#define IMPLEMENT_BOXING_TEMPLETE_BYVALUE(varType) \
	VariableBox BoxingByValue(const std::decay_t<varType>& src) { VariableByBinaryValue<std::decay_t<varType>> variable(src); return VariableBox(variable); } \
	VariableBox BoxingByValue(std::decay_t<varType>&& src) { VariableByBinaryValue<std::decay_t<varType>> variable(src); return VariableBox(variable); } \
	VariableBox BoxingByReference(const std::decay_t<varType>& src) { VariableValueReference<varType> variable(src); return VariableBox(variable); }\
	VariableBox BoxingByReference(const Array<std::decay_t<varType>>& src) { VariableValueReference<Array<std::decay_t<varType>>> variable(src); return VariableBox(variable); }\
	VariableBox Boxing(const std::decay_t<varType>& src) { VariableByBinaryValue<varType> variable(src); return VariableBox(variable); } \
	VariableBox Boxing(std::decay_t<varType>&& src) { VariableByBinaryValue<varType> variable(src); return VariableBox(variable); } \
	VariableBox Boxing(Array<std::decay_t<varType>>& src) { VariableValueReference<Array<std::decay_t<varType>>> variable(src); return VariableBox(variable); }\
	VariableBox Boxing(const Array<std::decay_t<varType>>& src) { VariableValueReference<Array<std::decay_t<varType>>> variable(src); return VariableBox(variable); }\




#define DECLARE_BOXING_TEMPLETE_BYREFERENCE(varType)					\
	VariableBox BoxingByValue(const std::decay_t<varType>& src); \
	VariableBox BoxingByValue(std::decay_t<varType>&& src); \
	VariableBox BoxingByReference(const std::decay_t<varType>& src);\
	VariableBox BoxingByReference(const Array<std::decay_t<varType>>& src);\
	VariableBox Boxing(const std::decay_t<varType>& src);\
	VariableBox Boxing(std::decay_t<varType>&& src);\
	VariableBox Boxing(const Array<std::decay_t<varType>>& src);\
	IMPLEMENT_BOXING_TEMPLATE_INTERNAL(varType, VariableValueReference<varType>)




#define IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(varType)					\
	VariableBox BoxingByValue(const std::decay_t<varType>& src) { VariableByBinaryValue<std::decay_t<varType>> variable(src); return VariableBox(variable); } \
	VariableBox BoxingByValue(std::decay_t<varType>&& src) { VariableByBinaryValue<std::decay_t<varType>> variable(src); return VariableBox(variable); } \
	VariableBox BoxingByReference(const std::decay_t<varType>& src) { VariableValueReference<std::decay_t<varType>> variable(src); return VariableBox(variable); }\
	VariableBox BoxingByReference(const Array<std::decay_t<varType>>& src) { VariableValueReference<Array<std::decay_t<varType>>> variable(src); return VariableBox(variable); }\
	VariableBox Boxing(const std::decay_t<varType>& src) { VariableValueReference<std::decay_t<varType>> variable(src); return VariableBox(variable); }\
	VariableBox Boxing(std::decay_t<varType>&& src) { VariableValueReference<std::decay_t<varType>> variable(src); return VariableBox(variable); }\
	VariableBox Boxing(const Array<std::decay_t<varType>>& src) { VariableValueReference<Array<std::decay_t<varType>>> variable(src); return VariableBox(variable); }\





	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Default platform type helpers
	//


	Result _ToString(ToStringContext& context, const bool& value);
	Result _ToString(ToStringContext& context, const int8_t& value);
	Result _ToString(ToStringContext& context, const uint8_t& value);
	Result _ToString(ToStringContext& context, const int16_t& value);
	Result _ToString(ToStringContext& context, const uint16_t& value);
	Result _ToString(ToStringContext& context, const int32_t& value);
	Result _ToString(ToStringContext& context, const uint32_t& value);
	Result _ToString(ToStringContext& context, const int64_t& value);
	Result _ToString(ToStringContext& context, const uint64_t& value);
	Result _ToString(ToStringContext& context, const float& value);
	Result _ToString(ToStringContext& context, const double& value);
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	Result _ToString(ToStringContext& context, const long& value);
	Result _ToString(ToStringContext& context, const unsigned long& value);
#endif
	Result _ToString(ToStringContext& context, const char* value);
	Result _ToString(ToStringContext& context, const wchar_t* value);

	Result _ToString(ToStringContext& context, const std::string& value);
	Result _ToString(ToStringContext& context, const NetAddress& value);
	Result _ToString(ToStringContext& context, const TimeStampMS& value);
	Result _ToString(ToStringContext& context, const TimeStampSec& value);
	Result _ToString(ToStringContext& context, const UTCTimeStampMS& value);
	Result _ToString(ToStringContext& context, const UTCTimeStampSec& value);
	Result _ToString(ToStringContext& context, const DurationMS& value);
	Result _ToString(ToStringContext& context, const DurationSec& value);
	Result _ToString(ToStringContext& context, const sockaddr_in6& value);
	Result _ToString(ToStringContext& context, const sockaddr_storage& value);



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Specialize for string
	template<> inline void VariableValueReference<SF::String>::SetValue(const char* value) { *reinterpret_cast<String*>(GetDataPtr()) = value; }
	//template<> inline void VariableValueReference<SF::String>::SetValue(const wchar_t* value) { super::SetValue(value); }
	template<> inline void VariableValueReference<SF::String>::SetValue(const String& value) { *reinterpret_cast<String*>(GetDataPtr()) = value; }

	template<> inline String VariableValueReference<SF::String>::GetValueString() const { return *reinterpret_cast<const String*>(GetDataPtr()); }
	template<> inline const char* VariableValueReference<SF::String>::GetValueCharString() const { return reinterpret_cast<const String*>(GetDataPtr())->data(); }
	//template<> inline const wchar_t* VariableValueReference<SF::String>::GetValueWCharString() const { return nullptr; }
	template<> inline StringCrc32 VariableValueReference<SF::String>::GetValueStringCrc32() const { return StringCrc32(reinterpret_cast<const String*>(GetDataPtr())->data()); }
	template<> inline StringCrc64 VariableValueReference<SF::String>::GetValueStringCrc64() const { return StringCrc64(reinterpret_cast<const String*>(GetDataPtr())->data()); }

	// Specialize for char*
	template<> inline String VariableValueReference<const char*>::GetValueString() const { return reinterpret_cast<const char*>(GetDataPtr()); }
	template<> inline const char* VariableValueReference<const char*>::GetValueCharString() const { return reinterpret_cast<const char*>(GetDataPtr()); }
	//template<> inline const wchar_t* VariableValueReference<const char*>::GetValueWCharString() const { return nullptr; }
	template<> inline StringCrc32 VariableValueReference<const char*>::GetValueStringCrc32() const { return StringCrc32(reinterpret_cast<const char*>(GetDataPtr())); }
	template<> inline StringCrc64 VariableValueReference<const char*>::GetValueStringCrc64() const { return StringCrc64(reinterpret_cast<const char*>(GetDataPtr())); }

	// Specialize for wchar*
	template<> inline const wchar_t* VariableValueReference<const wchar_t*>::GetValueWCharString() const { return reinterpret_cast<const wchar_t*>(GetDataPtr()); }

	template<> inline const Array<uint8_t>& VariableValueReference<Array<uint8_t>>::GetValueBLOB() const { return *reinterpret_cast<Array<uint8_t>*>(GetDataPtr()); }


	// Specialize for numerics
#define BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(DataType)\
	template<> inline void VariableValueReference<DataType>::SetValue(int8_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(uint8_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(int16_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(uint16_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(int32_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(uint32_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(int64_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(uint64_t value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(float value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline void VariableValueReference<DataType>::SetValue(double value) { *reinterpret_cast<DataType*>(GetDataPtr()) = (DataType)value; }\
	template<> inline bool VariableValueReference<DataType>::GetValueBool() const { return *reinterpret_cast<DataType*>(GetDataPtr()) == (DataType)0; }\
	template<> inline int8_t VariableValueReference<DataType>::GetValueInt8() const { return (int8_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\
	template<> inline uint8_t VariableValueReference<DataType>::GetValueUInt8() const { return (uint8_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\
	template<> inline int16_t VariableValueReference<DataType>::GetValueInt16() const { return (int16_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\
	template<> inline uint16_t VariableValueReference<DataType>::GetValueUInt16() const { return (uint16_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\
	template<> inline int32_t VariableValueReference<DataType>::GetValueInt32() const { return (int32_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\
	template<> inline uint32_t VariableValueReference<DataType>::GetValueUInt32() const { return (uint32_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\
	template<> inline int64_t VariableValueReference<DataType>::GetValueInt64() const { return (int64_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\
	template<> inline uint64_t VariableValueReference<DataType>::GetValueUInt64() const { return (uint64_t)*reinterpret_cast<DataType*>(GetDataPtr()); }\



	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(int8_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(uint8_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(int16_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(uint16_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(int32_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(uint32_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(int64_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(uint64_t)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(float)
	BR_VARIABLEBYREFERENCE_NUMERIC_SPECIALIZE(double)



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
	DECLARE_BOXING_TEMPLETE_BYVALUE(void*);
	DEFINE_BOXING_TEMPLETE(String, VariableString);
	DEFINE_BOXING_TEMPLETE(StringCrc64, VariableStringCrc64);
	DEFINE_BOXING_TEMPLETE(StringCrc32, VariableStringCrc32);
	DEFINE_BOXING_TEMPLETE(Result, VariableResult);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(std::string);

	//DECLARE_BOXING_TEMPLETE_BYVALUE(const char*);
	VariableBox BoxingByValue(const char* src);
	VariableBox BoxingByReference(const char* src);
	VariableBox Boxing(const char* src);
	VariableBox Boxing(Array<const char*>& src);
	VariableBox Boxing(const Array<const char*>& src);
	IMPLEMENT_BOXING_TEMPLATE_INTERNAL(const char*, VariableString);

	//DECLARE_BOXING_TEMPLETE_BYVALUE(const wchar_t*);
	VariableBox BoxingByValue(const wchar_t* src);
	VariableBox BoxingByReference(const wchar_t* src);
	VariableBox Boxing(const wchar_t* src);
	VariableBox Boxing(Array<const wchar_t*>& src);
	VariableBox Boxing(const Array<const wchar_t*>& src);
	IMPLEMENT_BOXING_TEMPLATE_INTERNAL(const wchar_t*, VariableWString);

	// They comes from OS system types, but not referenced by std types on windows(VC compiler)
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	DEFINE_BOXING_TEMPLETE(long, VariableInt);
	DEFINE_BOXING_TEMPLETE(unsigned long, VariableUInt);
#endif


	DECLARE_BOXING_TEMPLETE_BYREFERENCE(NetAddress);
	DECLARE_BOXING_TEMPLETE_BYVALUE(TimeStampMS);
	DECLARE_BOXING_TEMPLETE_BYVALUE(TimeStampSec);
	DECLARE_BOXING_TEMPLETE_BYVALUE(UTCTimeStampMS);
	DECLARE_BOXING_TEMPLETE_BYVALUE(UTCTimeStampSec);
	DECLARE_BOXING_TEMPLETE_BYVALUE(DurationMS);
	DECLARE_BOXING_TEMPLETE_BYVALUE(DurationSec);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(sockaddr_in6);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(sockaddr_storage);


} // namespace SF




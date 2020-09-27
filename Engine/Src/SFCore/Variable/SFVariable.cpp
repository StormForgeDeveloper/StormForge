////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Variable/SFVariable.h"
#include "String/SFToString.h"
#include "String/SFStringFormat.h"
#include "String/SFHasher32C.h"

namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	constexpr StringCrc32 VariableBool::TYPE_NAME;
 
	Result VariableBool::ToString(ToStringContext& context) const
	{
		const String& valueString = m_Value ? String::True : String::False;;
		return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, (const char*)valueString);
	}

	Variable* VariableBool::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableBool(m_Value);
	}

	Variable* VariableBool::Clone(IHeap& heap) const
	{
		return new(heap) VariableBool(m_Value);
	}


	bool VariableBool::operator == (const Variable& op) const
	{
		return GetValueBool() == op.GetValueBool();
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable void*
	//

	constexpr StringCrc32 VariableVoidP::TYPE_NAME;

	Result VariableVoidP::ToString(ToStringContext& context) const
	{
		return SF::_IToA(context, (uint64_t)m_Value);
	}

	Variable* VariableVoidP::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableVoidP(m_Value);
	}

	Variable* VariableVoidP::Clone(IHeap& heap) const
	{
		return new(heap) VariableVoidP(m_Value);
	}

	bool Variable::IsEqualTypeNValue(const Variable& op) const
	{
		if (GetTypeName() != op.GetTypeName())
			return false;

		return (*this) == op;
	}

	bool Variable::operator == (const Variable& op) const
	{
		return GetTypeName() == op.GetTypeName() && GetValueUInt64() == op.GetValueUInt64();
	}

	bool Variable::operator != (const Variable& op) const
	{
		return GetTypeName() != op.GetTypeName() || GetValueUInt64() != op.GetValueUInt64();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	constexpr StringCrc32 VariableInt::TYPE_NAME;

	void VariableInt::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}


	void VariableInt::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}

	void VariableInt::SetValue(StringCrc64 value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}




	StringCrc64 VariableInt::GetValueStringCrc64() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);

		return StringCrc64(renderBuffer);
	}

	String VariableInt::GetValueString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);

		return String(renderBuffer);
	}

	Result VariableInt::ToString(ToStringContext& context) const
	{
		return SF::_IToA(context, m_Value);
	}

	Variable* VariableInt::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableInt(m_Value);
	}

	Variable* VariableInt::Clone(IHeap& heap) const
	{
		return new(heap) VariableInt(m_Value);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable uint
	//

	constexpr StringCrc32 VariableUInt::TYPE_NAME;

	void VariableUInt::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}

	void VariableUInt::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}

	void VariableUInt::SetValue(StringCrc64 value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}

	StringCrc64 VariableUInt::GetValueStringCrc64() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return StringCrc64(renderBuffer);
	}

	String VariableUInt::GetValueString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return String(renderBuffer);
	}

	Result VariableUInt::ToString(ToStringContext& context) const
	{
		return SF::_IToA(context, m_Value);
	}

	Variable* VariableUInt::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableUInt(m_Value);
	}

	Variable* VariableUInt::Clone(IHeap& heap) const
	{
		return new(heap) VariableUInt(m_Value);
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable Result
	//

	constexpr StringCrc32 VariableResult::TYPE_NAME;

	Result VariableResult::ToString(ToStringContext& context) const
	{
		context.Radix = 16;

		return SF::_IToA(context, (uint32_t)m_Value);
	}

	Variable* VariableResult::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableResult(m_Value);
	}

	Variable* VariableResult::Clone(IHeap& heap) const
	{
		return new(heap) VariableResult(m_Value);
	}




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int64
	//

	constexpr StringCrc32 VariableInt64::TYPE_NAME;

	void VariableInt64::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}

	void VariableInt64::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}

	void VariableInt64::SetValue(StringCrc64 value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}




	StringCrc64 VariableInt64::GetValueStringCrc64() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);

		return StringCrc64(renderBuffer);
	}

	String VariableInt64::GetValueString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);

		return String(renderBuffer);
	}

	Result VariableInt64::ToString(ToStringContext& context) const
	{
		return SF::_IToA(context, m_Value);
	}

	Variable* VariableInt64::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableInt64(m_Value);
	}

	Variable* VariableInt64::Clone(IHeap& heap) const
	{
		return new(heap) VariableInt64(m_Value);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable uint
	//

	constexpr StringCrc32 VariableUInt64::TYPE_NAME;

	void VariableUInt64::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}

	void VariableUInt64::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atoi(value);
	}

	void VariableUInt64::SetValue(StringCrc64 value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}

	StringCrc64 VariableUInt64::GetValueStringCrc64() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return StringCrc64(renderBuffer);
	}

	String VariableUInt64::GetValueString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return String(renderBuffer);
	}

	Result VariableUInt64::ToString(ToStringContext& context) const
	{
		return SF::_IToA(context, m_Value);
	}

	Variable* VariableUInt64::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableUInt64(m_Value);
	}

	Variable* VariableUInt64::Clone(IHeap& heap) const
	{
		return new(heap) VariableUInt64(m_Value);
	}




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable float
	//

	constexpr StringCrc32 VariableFloat::TYPE_NAME;

	void VariableFloat::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = (float)atof(value);
	}

	void VariableFloat::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = (float)atof(value);
	}

	void VariableFloat::SetValue(StringCrc64 value)
	{
		Assert(false); // It will lose precision
		m_Value = (float)value.GetHash();
	}

	StringCrc64 VariableFloat::GetValueStringCrc64() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return StringCrc64(renderBuffer);
	}

	String VariableFloat::GetValueString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return String(renderBuffer);
	}

	Result VariableFloat::ToString(ToStringContext& context) const
	{
		return SF::_FToA(context, m_Value);
	}

	Variable* VariableFloat::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableFloat(m_Value);
	}

	Variable* VariableFloat::Clone(IHeap& heap) const
	{
		return new(heap) VariableFloat(m_Value);
	}


	bool VariableFloat::operator == (const Variable& op) const
	{
		return GetValueFloat() == op.GetValueFloat();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable double
	//

	constexpr StringCrc32 VariableDouble::TYPE_NAME;

	void VariableDouble::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atof(value);
	}

	void VariableDouble::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			m_Value = 0;
			return;
		}

		m_Value = atof(value);
	}

	void VariableDouble::SetValue(StringCrc64 value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}

	StringCrc64 VariableDouble::GetValueStringCrc64() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return StringCrc64(renderBuffer);
	}

	String VariableDouble::GetValueString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return String(renderBuffer);
	}

	Result VariableDouble::ToString(ToStringContext& context) const
	{
		return SF::_FToA(context, m_Value);
	}

	Variable* VariableDouble::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableDouble(m_Value);
	}

	Variable* VariableDouble::Clone(IHeap& heap) const
	{
		return new(heap) VariableDouble(m_Value);
	}


	bool VariableDouble::operator == (const Variable& op) const
	{
		return GetValueDouble() == op.GetValueDouble();
	}




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable 32 bit base 16 integer
	//

	constexpr StringCrc32 VariableHex32::TYPE_NAME;

	void VariableHex32::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			SetValue(0);
			return;
		}
		super::SetValue((uint32_t)strtol(value, nullptr, 16));
	}

	void VariableHex32::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			SetValue(0);
			return;
		}

		super::SetValue((uint32_t)strtol(value, nullptr, 16));
	}

	Result VariableHex32::ToString(ToStringContext& context) const
	{
		context.Radix = 16;
		return SF::_IToA(context, GetValueUInt32());
	}

	Variable* VariableHex32::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableHex32(GetValueUInt32());
	}

	Variable* VariableHex32::Clone(IHeap& heap) const
	{
		return new(heap) VariableHex32(GetValueUInt32());
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable 64 bit base 16 integer
	//

	constexpr StringCrc32 VariableHex64::TYPE_NAME;

	void VariableHex64::SetValue(const char* value)
	{
		if (value == nullptr)
		{
			SetValue(0);
			return;
		}
		super::SetValue((uint64_t)strtol(value, nullptr, 16));
	}

	void VariableHex64::SetValue(const String& value)
	{
		if (value == nullptr)
		{
			SetValue(0);
			return;
		}

		super::SetValue((uint64_t)strtol(value, nullptr, 16));
	}

	Result VariableHex64::ToString(ToStringContext& context) const
	{
		context.Radix = 16;
		return SF::_IToA(context, GetValueUInt64());
	}

	Variable* VariableHex64::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableHex64(GetValueUInt64());
	}

	Variable* VariableHex64::Clone(IHeap& heap) const
	{
		return new(heap) VariableHex64(GetValueUInt64());
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable char*
	//	  - This class only holds pointer, doesn't copy or allocate memory internally
	//

	constexpr StringCrc32 VariableCharString::TYPE_NAME;

	Result VariableCharString::ToString(ToStringContext& context) const
	{
		if(m_Value != nullptr)
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, m_Value);
		else
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "NullString");
	}

	Variable* VariableCharString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableCharString(m_Value);
	}

	Variable* VariableCharString::Clone(IHeap& heap) const
	{
		return new(heap) VariableCharString(m_Value);
	}

	bool VariableCharString::operator == (const Variable& op) const
	{
		return StrUtil::StringCompair(GetValueCharString(), op.GetValueCharString(), -1);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable char*
	//	  - This class only holds pointer, doesn't copy or allocate memory internally
	//

	constexpr StringCrc32 VariableWCharString::TYPE_NAME;

	Result VariableWCharString::ToString(ToStringContext& context) const
	{
		char destBuff[1024];


		if (m_Value != nullptr)
		{
			if (!StrUtil::WCSToUTF8(m_Value, destBuff))
				return ResultCode::FAIL;

			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, destBuff);
		}
		else
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "NullString");
	}

	Variable* VariableWCharString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableWCharString(m_Value);
	}

	Variable* VariableWCharString::Clone(IHeap& heap) const
	{
		return new(heap) VariableWCharString(m_Value);
	}

	bool VariableWCharString::operator == (const Variable& op) const
	{
		return StrUtil::StringCompair(GetValueWCharString(), op.GetValueWCharString(), -1);
	}





	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable String
	//

	constexpr StringCrc32 VariableString::TYPE_NAME;

	void VariableString::SetValue(bool value)
	{
		m_Value = value ? String::True : String::False;
	}

	void VariableString::SetValue(int8_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(uint8_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(int16_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(uint16_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(int32_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(uint32_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(int64_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(uint64_t value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(float value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(double value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(const char* value)
	{
		m_Value.Format("{0}", value);
	}

	void VariableString::SetValue(const String& value)
	{
		m_Value = value;
	}

	void VariableString::SetValue(StringCrc64 value)
	{
		m_Value.Format("{0}", value);
	}

	bool VariableString::GetValueBool() const
	{
		if (m_Value.IsEqualIgnoreCase(String::True))
			return true;

		return false;
	}

	int8_t VariableString::GetValueInt8() const
	{
		return (int8_t)atoi(m_Value);
	}

	uint8_t VariableString::GetValueUInt8() const
	{
		return (uint8_t)atoi(m_Value);
	}

	int16_t VariableString::GetValueInt16() const
	{
		return (int16_t)atoi(m_Value);
	}

	uint16_t VariableString::GetValueUInt16() const
	{
		return (uint16_t)atoi(m_Value);
	}

	int32_t VariableString::GetValueInt32() const
	{
		return (int32_t)atoi(m_Value);
	}

	uint32_t VariableString::GetValueUInt32() const
	{
		return (uint32_t)atoi(m_Value);
	}

	int64_t VariableString::GetValueInt64() const
	{
		return (int64_t)atol(m_Value);
	}

	uint64_t VariableString::GetValueUInt64() const
	{
		return (uint64_t)atol(m_Value);
	}

	float VariableString::GetValueFloat() const
	{
		return (float)atof(m_Value);
	}

	double VariableString::GetValueDouble() const
	{
		return (double)atof(m_Value);
	}

	StringCrc64 VariableString::GetValueStringCrc64() const
	{
		return StringCrc64(m_Value);
	}

	String VariableString::GetValueString() const
	{
		return m_Value;
	}


	Result VariableString::ToString(ToStringContext& context) const
	{
		if (m_Value.GetLength() != 0)
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, (const char*)m_Value);
		else
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "NullString");
	}


	Variable* VariableString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableString(m_Value);
	}

	Variable* VariableString::Clone(IHeap& heap) const
	{
		return new(heap) VariableString(m_Value);
	}

	bool VariableString::operator == (const Variable& op) const
	{
		return m_Value == op.GetValueCharString();
	}





	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable StringCrc32
	//

	constexpr StringCrc32 VariableStringCrc32::TYPE_NAME;

	String VariableStringCrc32::GetValueString() const
	{
		return Service::StringDB->GetString(m_Value);
	}

	Result VariableStringCrc32::ToString(ToStringContext& context) const
	{
		auto pStr = Service::StringDB->GetString(m_Value);
		if (pStr != nullptr)
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, pStr);
		else
		{
			auto oldRadix = context.Radix;
			context.Radix = 16;
			auto result = _IToA(context, (uint32_t)m_Value);
			context.Radix = oldRadix;
			return result;
		}
	}

	Variable* VariableStringCrc32::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableStringCrc32(m_Value);
	}

	Variable* VariableStringCrc32::Clone(IHeap& heap) const
	{
		return new(heap) VariableStringCrc32(m_Value);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable StringCrc64
	//

	constexpr StringCrc32 VariableStringCrc64::TYPE_NAME;

	String VariableStringCrc64::GetValueString() const
	{
		return Service::StringDB->GetString(m_Value);
	}

	Result VariableStringCrc64::ToString(ToStringContext& context) const
	{
		auto pStr = Service::StringDB->GetString(m_Value);
		if (pStr != nullptr)
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, pStr);
		else
		{
			auto oldRadix = context.Radix;
			context.Radix = 16;
			auto result = _IToA(context, (uint64_t)m_Value);
			context.Radix = oldRadix;
			return result;
		}
	}

	Variable* VariableStringCrc64::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableStringCrc64(m_Value);
	}

	Variable* VariableStringCrc64::Clone(IHeap& heap) const
	{
		return new(heap) VariableStringCrc64(m_Value);
	}





	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable StringCrc64
	//

	constexpr StringCrc32 VariableBLOB::TYPE_NAME;

	Result VariableBLOB::ToString(ToStringContext& context) const
	{
		// todo

		return ResultCode::SUCCESS;
	}

	Variable* VariableBLOB::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableBLOB(m_Value);
	}

	Variable* VariableBLOB::Clone(IHeap& heap) const
	{
		return new(heap) VariableBLOB(heap);
	}




} // namespace SF


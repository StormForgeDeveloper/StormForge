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


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Variable/SFVariable.h"
#include "String/SFToString.h"



namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	constexpr FixedString VariableBool::TYPE_NAME;
 
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

	constexpr FixedString VariableVoidP::TYPE_NAME;

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
		return GetValueUInt64() == op.GetValueUInt64();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	constexpr FixedString VariableInt::TYPE_NAME;

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

	void VariableInt::SetValue(FixedString value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}




	FixedString VariableInt::GetValueFixedString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);

		return FixedString(renderBuffer);
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

	constexpr FixedString VariableUInt::TYPE_NAME;

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

	void VariableUInt::SetValue(FixedString value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}

	FixedString VariableUInt::GetValueFixedString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return FixedString(renderBuffer);
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

	constexpr FixedString VariableResult::TYPE_NAME;

	Result VariableResult::ToString(ToStringContext& context) const
	{
		context.Radix = 16;

		return SF::_IToA(context, m_Value);
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

	constexpr FixedString VariableInt64::TYPE_NAME;

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

	void VariableInt64::SetValue(FixedString value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}




	FixedString VariableInt64::GetValueFixedString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);

		return FixedString(renderBuffer);
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

	constexpr FixedString VariableUInt64::TYPE_NAME;

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

	void VariableUInt64::SetValue(FixedString value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}

	FixedString VariableUInt64::GetValueFixedString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return FixedString(renderBuffer);
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

	constexpr FixedString VariableFloat::TYPE_NAME;

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

	void VariableFloat::SetValue(FixedString value)
	{
		Assert(false); // It will lose precision
		m_Value = (float)value.GetHash();
	}

	FixedString VariableFloat::GetValueFixedString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return FixedString(renderBuffer);
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

	constexpr FixedString VariableDouble::TYPE_NAME;

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

	void VariableDouble::SetValue(FixedString value)
	{
		Assert(false); // It will lose precision
		m_Value = (int)value.GetHash();
	}

	FixedString VariableDouble::GetValueFixedString() const
	{
		char renderBuffer[128] = "";
		ToStringContext context;
		context.StringBuffer = renderBuffer;
		context.StringBufferLength = sizeof(renderBuffer);

		ToString(context);
		return FixedString(renderBuffer);
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

	constexpr FixedString VariableHex32::TYPE_NAME;

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

	constexpr FixedString VariableHex64::TYPE_NAME;

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

	constexpr FixedString VariableCharString::TYPE_NAME;

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

	constexpr FixedString VariableWCharString::TYPE_NAME;

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

	constexpr FixedString VariableString::TYPE_NAME;

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

	void VariableString::SetValue(FixedString value)
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

	FixedString VariableString::GetValueFixedString() const
	{
		return FixedString(m_Value);
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
	//	Variable FixedString32
	//

	constexpr FixedString VariableFixedString32::TYPE_NAME;

	String VariableFixedString32::GetValueString() const
	{
		return Service::StringDB->GetString(m_Value);
	}

	Result VariableFixedString32::ToString(ToStringContext& context) const
	{
		auto pStr = Service::StringDB->GetString(m_Value);
		return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, pStr);
	}

	Variable* VariableFixedString32::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableFixedString32(m_Value);
	}

	Variable* VariableFixedString32::Clone(IHeap& heap) const
	{
		return new(heap) VariableFixedString32(m_Value);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable FixedString
	//

	constexpr FixedString VariableFixedString::TYPE_NAME;

	String VariableFixedString::GetValueString() const
	{
		return Service::StringDB->GetString(m_Value);
	}

	Result VariableFixedString::ToString(ToStringContext& context) const
	{
		auto pStr = Service::StringDB->GetString(m_Value);
		return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, pStr);
	}

	Variable* VariableFixedString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableFixedString(m_Value);
	}

	Variable* VariableFixedString::Clone(IHeap& heap) const
	{
		return new(heap) VariableFixedString(m_Value);
	}






} // namespace SF


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
#include "Variable/SFVariableBoxing.h"
#include "Util/SFToString.h"
#include "Util/SFStringFormat.h"
#include "Util/SFHasher32C.h"

namespace SF
{

	Result _ToString(ToStringContext& context, const VariableBLOB& Data)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "bin:"))
			return ResultCode::FAIL;

		if (!_IToA(context, Data.GetValueBLOB().size()))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	constexpr StringCrc32 VariableBool::TYPE_NAME;
 
	Result VariableBool::ToString(std::stringstream& ss) const
	{
		const String& valueString = m_Value ? String_True : String_False;
        ss << valueString;
		return ResultCode::SUCCESS;
	}

	Variable* VariableBool::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableBool(m_Value);
	}

	Variable* VariableBool::Clone() const
	{
		return new VariableBool(m_Value);
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

	Result VariableVoidP::ToString(std::stringstream& ss) const
	{
        std::format_to(std::ostreambuf_iterator(ss), "{:p}", m_Value);
		return ResultCode::SUCCESS;
	}

	Variable* VariableVoidP::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableVoidP(m_Value);
	}

	Variable* VariableVoidP::Clone() const
	{
		return new VariableVoidP(m_Value);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable
	//

	String Variable::ToString() const
	{
        std::stringstream ss;

		ToString(ss);

		return ss.str();
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



    StringCrc32 VariableInt::GetValueStringCrc32() const
    {
        return StringCrc32(uint32_t(m_Value));
    }

	StringCrc64 VariableInt::GetValueStringCrc64() const
	{
		return StringCrc64(uint64_t(m_Value));
	}

	Result VariableInt::ToString(std::stringstream& ss) const
	{
        ss << m_Value;
		return ResultCode::SUCCESS;
	}

	Variable* VariableInt::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableInt(m_Value);
	}

	Variable* VariableInt::Clone() const
	{
		return new VariableInt(m_Value);
	}

	Result VariableInt::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableInt::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
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


    StringCrc32 VariableUInt::GetValueStringCrc32() const
    {
        return StringCrc32(uint32_t(m_Value));
    }

    StringCrc64 VariableUInt::GetValueStringCrc64() const
    {
        return StringCrc64(uint64_t(m_Value));
    }


	Result VariableUInt::ToString(std::stringstream& ss) const
	{
        ss << m_Value;
        return ResultCode::SUCCESS;
	}

	Variable* VariableUInt::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableUInt(m_Value);
	}

	Variable* VariableUInt::Clone() const
	{
		return new VariableUInt(m_Value);
	}

	Result VariableUInt::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableUInt::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable Result
	//

	constexpr StringCrc32 VariableResult::TYPE_NAME;

	Result VariableResult::ToString(std::stringstream& ss) const
	{
		auto pStr = m_Value.ToString();
        ss << pStr;
		return ResultCode::SUCCESS;
	}

	Variable* VariableResult::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableResult(m_Value);
	}

	Variable* VariableResult::Clone() const
	{
		return new VariableResult(m_Value);
	}

	Result VariableResult::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableResult::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
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




    StringCrc32 VariableInt64::GetValueStringCrc32() const
    {
        uint32_t highDword = uint32_t(m_Value >> 32);
        unused(highDword);
        assert(highDword == 0xFFFFFFFF || highDword == 0);
        return StringCrc32(uint32_t(m_Value));
    }

	StringCrc64 VariableInt64::GetValueStringCrc64() const
	{
		//char renderBuffer[128] = "";
		//ToStringContext context;
		//context.OutStream.pBuffer = renderBuffer;
		//context.OutStream.BuffLen = sizeof(renderBuffer);

		//ToString(context);

		//return StringCrc64(renderBuffer);
        return StringCrc64(uint64_t(m_Value));
    }

    Result VariableInt64::ToString(std::stringstream& ss) const
    {
        ss << m_Value;
        return ResultCode::SUCCESS;
    }

	Variable* VariableInt64::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableInt64(m_Value);
	}

	Variable* VariableInt64::Clone() const
	{
		return new VariableInt64(m_Value);
	}

	Result VariableInt64::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableInt64::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
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

    StringCrc32 VariableUInt64::GetValueStringCrc32() const
    {
        uint32_t highDword = uint32_t(m_Value >> 32);
        unused(highDword);
        assert(highDword == 0xFFFFFFFF || highDword == 0);
        return StringCrc32(uint32_t(m_Value));
    }

    StringCrc64 VariableUInt64::GetValueStringCrc64() const
    {
        return StringCrc64(uint64_t(m_Value));
    }


    Result VariableUInt64::ToString(std::stringstream& ss) const
    {
        ss << m_Value;
        return ResultCode::SUCCESS;
    }


	Variable* VariableUInt64::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableUInt64(m_Value);
	}

	Variable* VariableUInt64::Clone() const
	{
		return new VariableUInt64(m_Value);
	}

	Result VariableUInt64::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableUInt64::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
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
		return StringCrc64();
	}

    Result VariableFloat::ToString(std::stringstream& ss) const
    {
        ss << m_Value;
        return ResultCode::SUCCESS;
    }


	Variable* VariableFloat::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableFloat(m_Value);
	}

	Variable* VariableFloat::Clone() const
	{
		return new VariableFloat(m_Value);
	}

	Result VariableFloat::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableFloat::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
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
		return StringCrc64();
	}

    Result VariableDouble::ToString(std::stringstream& ss) const
    {
        ss << m_Value;
        return ResultCode::SUCCESS;
    }


	Variable* VariableDouble::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableDouble(m_Value);
	}

	Variable* VariableDouble::Clone() const
	{
		return new VariableDouble(m_Value);
	}

	Result VariableDouble::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableDouble::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
	}

	bool VariableDouble::operator == (const Variable& op) const
	{
		return GetValueDouble() == op.GetValueDouble();
	}






	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable char*
	//	  - This class only holds pointer, doesn't copy or allocate memory internally
	//

	constexpr StringCrc32 VariableCharString::TYPE_NAME;

	Result VariableCharString::ToString(std::stringstream& ss) const
	{
		if(m_Value != nullptr)
            ss << m_Value;
        else
            ss << "(Null)";

        return ResultCode::SUCCESS;
	}

	Variable* VariableCharString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableCharString(m_Value);
	}

	Variable* VariableCharString::Clone() const
	{
		return new VariableCharString(m_Value);
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

	Result VariableWCharString::ToString(std::stringstream& ss) const
	{
		char destBuff[1024];


		if (m_Value != nullptr)
		{
			if (!StrUtil::WCSToUTF8(m_Value, destBuff))
				return ResultCode::FAIL;
		}

        ss << destBuff;

        return ResultCode::SUCCESS;
	}

	Variable* VariableWCharString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableWCharString(m_Value);
	}

	Variable* VariableWCharString::Clone() const
	{
		return new VariableWCharString(m_Value);
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
		m_Value = value ? String_True : String_False;
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
		if (m_Value.EqualsIgnoreCase(String_True))
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

	const char* VariableString::GetValueCharString() const
	{
		return m_Value;
	}

	StringCrc32 VariableString::GetValueStringCrc32() const
	{
		return StringCrc32(m_Value);
	}

	StringCrc64 VariableString::GetValueStringCrc64() const
	{
		return StringCrc64(m_Value);
	}

	String VariableString::GetValueString() const
	{
		return m_Value;
	}


	Result VariableString::ToString(std::stringstream& ss) const
	{
		if (m_Value.GetLength() != 0)
            ss << m_Value;
		else
            ss << "(null)";

        return ResultCode::SUCCESS;
	}


	Variable* VariableString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableString(m_Value);
	}

	Variable* VariableString::Clone() const
	{
		return new VariableString(m_Value);
	}

	Result VariableString::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableString::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
	}

	bool VariableString::operator == (const Variable& op) const
	{
		return m_Value == op.GetValueCharString();
	}





	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable WString
	//

	constexpr StringCrc32 VariableWString::TYPE_NAME;

	void VariableWString::SetValue(bool value)
	{
		m_Value = value ? WString_True : WString_False;
	}

	void VariableWString::SetValue(int8_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(uint8_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(int16_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(uint16_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(int32_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(uint32_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(int64_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(uint64_t value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(float value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(double value)
	{
		m_Value.Format(L"{0}", value);
	}

	void VariableWString::SetValue(const char* value)
	{
        StrUtil::UTF8ToWCS(value, m_Value);
	}

	void VariableWString::SetValue(const String& value)
	{
		wchar_t ConvertBuffer[1024];
		StrUtil::UTF8ToWCS(value.data(), ConvertBuffer);

		m_Value = ConvertBuffer;
	}

	void VariableWString::SetValue(StringCrc64 value)
	{
        StrUtil::UTF8ToWCS(value.ToString(), m_Value);
	}

	bool VariableWString::GetValueBool() const
	{
		if (m_Value.EqualsIgnoreCase(WString_True))
			return true;

		return false;
	}

	int8_t VariableWString::GetValueInt8() const
	{
		wchar_t* pEnd{};
		return (int8_t)wcstol(m_Value, &pEnd, 10);
	}

	uint8_t VariableWString::GetValueUInt8() const
	{
		wchar_t* pEnd{};
		return (uint8_t)wcstol(m_Value, &pEnd, 10);
	}

	int16_t VariableWString::GetValueInt16() const
	{
		wchar_t* pEnd{};
		return (int16_t)wcstol(m_Value, &pEnd, 10);
	}

	uint16_t VariableWString::GetValueUInt16() const
	{
		wchar_t* pEnd{};
		return (uint16_t)wcstol(m_Value, &pEnd, 10);
	}

	int32_t VariableWString::GetValueInt32() const
	{
		wchar_t* pEnd{};
		return (int32_t)wcstol(m_Value, &pEnd, 10);
	}

	uint32_t VariableWString::GetValueUInt32() const
	{
		wchar_t* pEnd{};
		return (uint32_t)wcstol(m_Value, &pEnd, 10);
	}

	int64_t VariableWString::GetValueInt64() const
	{
		wchar_t* pEnd{};
		return (int64_t)wcstol(m_Value, &pEnd, 10);
	}

	uint64_t VariableWString::GetValueUInt64() const
	{
		wchar_t* pEnd{};
		return (uint64_t)wcstol(m_Value, &pEnd, 10);
	}

	float VariableWString::GetValueFloat() const
	{
		wchar_t* pEnd{};
		return (float)wcstod(m_Value, &pEnd);
	}

	double VariableWString::GetValueDouble() const
	{
		wchar_t* pEnd{};
		return (double)wcstod(m_Value, &pEnd);
	}

	const wchar_t* VariableWString::GetValueWCharString() const
	{
		return m_Value;
	}

	StringCrc32 VariableWString::GetValueStringCrc32() const
	{
		char ConvertBuffer[1024];
		StrUtil::WCSToUTF8(m_Value.data(), ConvertBuffer);
		return StringCrc32(ConvertBuffer);
	}

	StringCrc64 VariableWString::GetValueStringCrc64() const
	{
		char ConvertBuffer[1024];
		StrUtil::WCSToUTF8(m_Value.data(), ConvertBuffer);
		return StringCrc64(ConvertBuffer);
	}

	String VariableWString::GetValueString() const
	{
		char ConvertBuffer[1024];
		StrUtil::WCSToUTF8(m_Value.data(), ConvertBuffer);
		return ConvertBuffer;
	}


	Result VariableWString::ToString(std::stringstream& ss) const
	{
		char ConvertBuffer[1024];

        if (m_Value.GetLength() != 0)
        {
            StrUtil::WCSToUTF8(m_Value.data(), ConvertBuffer);
            ss << ConvertBuffer;
        }

        return ResultCode::SUCCESS;
	}


	Variable* VariableWString::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableWString(m_Value);
	}

	Variable* VariableWString::Clone() const
	{
		return new VariableWString(m_Value);
	}

	Result VariableWString::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableWString::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
	}

	bool VariableWString::operator == (const Variable& op) const
	{
		return m_Value == op.GetValueWCharString();
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

	const char* VariableStringCrc32::GetValueCharString() const
	{
		return Service::StringDB->GetString(m_Value);
	}


	Result VariableStringCrc32::ToString(std::stringstream& ss) const
	{
        ss << Service::StringDB->GetString(m_Value);
        return ResultCode::SUCCESS;
	}

	Variable* VariableStringCrc32::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableStringCrc32(m_Value);
	}

	Variable* VariableStringCrc32::Clone() const
	{
		return new VariableStringCrc32(m_Value);
	}

	Result VariableStringCrc32::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableStringCrc32::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
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

	const char* VariableStringCrc64::GetValueCharString() const
	{
		return Service::StringDB->GetString(m_Value);
	}

	Result VariableStringCrc64::ToString(std::stringstream& ss) const
	{
        ss << Service::StringDB->GetString(m_Value);
        return ResultCode::SUCCESS;
	}

	Variable* VariableStringCrc64::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableStringCrc64(m_Value);
	}

	Variable* VariableStringCrc64::Clone() const
	{
		return new VariableStringCrc64(m_Value);
	}

	Result VariableStringCrc64::Serialize(IOutputStream& output) const
	{
		return output << m_Value;
	}

	Result VariableStringCrc64::Deserialize(IInputStream& input)
	{
		return input >> m_Value;
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable StringCrc64
	//

	constexpr StringCrc32 VariableBLOB::TYPE_NAME;

	Result VariableBLOB::ToString(std::stringstream& ss) const
	{
		StaticArray<uint8_t, 64> outputData;
		Util::HEXEncode(Math::Min<size_t>(m_Value.size(), 8), m_Value.data(), outputData, '-');
		outputData.push_back(')');
		outputData.push_back('\0');

        std::format_to(std::ostreambuf_iterator(ss), "(sz:{0})", m_Value.size(), (const char*)outputData.data());

		return ResultCode::SUCCESS;
	}

	Variable* VariableBLOB::Clone(Array<uint8_t>& buffer) const
	{
		return new((void*)buffer.data()) VariableBLOB(m_Value);
	}

	Variable* VariableBLOB::Clone() const
	{
		return new VariableBLOB(m_Value);
	}

	Result VariableBLOB::Serialize(IOutputStream& output) const
	{
		uint16_t NumItems = static_cast<uint16_t>(m_Value.size());
		if (!output.Write(NumItems))
			return ResultCode::END_OF_STREAM;

		return output.Write(m_Value.data(), m_Value.size());
	}
	Result VariableBLOB::Deserialize(IInputStream& input)
	{
		return input.Read(m_Value);
	}


} // namespace SF


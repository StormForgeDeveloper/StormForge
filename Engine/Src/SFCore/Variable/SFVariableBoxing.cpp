////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : VariableBox
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Variable/SFVariableBoxing.h"
#include "Util/SFToString.h"
#include "Variable/SFVariableFactoryService.h"
#include "Service/SFService.h"


namespace SF
{
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	VariableBox class
	//

	VariableBox::VariableBox()
	{
	}

	VariableBox::VariableBox(const VariableBox& src)
	{
		if (src.m_pVariable != nullptr)
		{
			m_pVariable = src.m_pVariable->Clone();
			//IHeap::TestMemoryHeaderChecked(m_pVariable);
		}
	}

	VariableBox::VariableBox(const Variable& src)
	{
		m_pVariable = src.Clone();
		//IHeap::TestMemoryHeaderChecked(m_pVariable);
	}

	VariableBox::~VariableBox()
	{
		if (m_pVariable != nullptr)
			delete (m_pVariable);
		m_pVariable = nullptr;
	}

	//void VariableBox::GetValueString(ToStringContext& context) const
	//{
	//	if (m_pVariable)
	//	{
	//		m_pVariable->ToString(context);
	//	}

	//}

	// Set variable type. It will destroy previous variable
	bool VariableBox::SetVariableType(StringCrc32 TypeName)
	{
		if (m_pVariable != nullptr)
			delete (m_pVariable);

		m_pVariable = Service::VariableFactory->CreateVariable(TypeName);
		//IHeap::TestMemoryHeaderChecked(m_pVariable);

		return m_pVariable != nullptr;
	}

	VariableBox& VariableBox::operator = (const VariableBox& src)
	{
		if (m_pVariable != nullptr)
			delete (m_pVariable);
		m_pVariable = nullptr;

		if (src.m_pVariable != nullptr)
		{
			m_pVariable = src.m_pVariable->Clone();
			//IHeap::TestMemoryHeaderChecked(m_pVariable);
		}
		return *this;
	}




	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Boxing implementations
	//

	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(std::string);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(void*);

	//IMPLEMENT_BOXING_TEMPLETE_BYVALUE(const char*);
	VariableBox BoxingByValue(const char* src) { return VariableBox(VariableString(src)); }
	VariableBox BoxingByReference(const char* src) { return VariableBox(VariableCharString(src)); }
	VariableBox Boxing(const char* src) { return VariableBox(VariableCharString(src)); }
	VariableBox Boxing(Array<const char*>& src) { VariableValueReference<Array<const char*>> variable(src); return VariableBox(variable); }
	VariableBox Boxing(const Array<const char*>& src) { VariableValueReference<Array<const char*>> variable(src); return VariableBox(variable); }

	//IMPLEMENT_BOXING_TEMPLETE_BYVALUE(const wchar_t*);
	VariableBox BoxingByValue(const wchar_t* src) { return VariableBox(VariableWString(src)); }
	VariableBox BoxingByReference(const wchar_t* src) { return VariableBox(VariableWCharString(src)); }
	VariableBox Boxing(const wchar_t* src) { return VariableBox(VariableWCharString(src)); }
	VariableBox Boxing(Array<const wchar_t*>& src) { VariableValueReference<Array<const wchar_t*>> variable(src); return VariableBox(variable); }
	VariableBox Boxing(const Array<const wchar_t*>& src) { VariableValueReference<Array<const wchar_t*>> variable(src); return VariableBox(variable); }

	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(NetAddress);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(TimeStampMS);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(TimeStampSec);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(UTCTimeStampMS);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(UTCTimeStampSec);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(DurationMS);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(DurationSec);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(sockaddr_in6);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(sockaddr_storage);



	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Default platform type helpers
	//



	Result _ToString(ToStringContext& context, const bool& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const int8_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const uint8_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const int16_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const uint16_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const int32_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const uint32_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const int64_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const uint64_t& value)
	{
		return _IToA(context, value);
	}

	Result _ToString(ToStringContext& context, const float& value)
	{
		return _FToA(context, value);
	}

	Result _ToString(ToStringContext& context, const double& value)
	{
		return _FToA(context, value);
	}
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	Result _ToString(ToStringContext& context, const long& value)
	{
		return _IToA(context, (int32_t)value);
	}
	Result _ToString(ToStringContext& context, const unsigned long& value)
	{
		return _IToA(context, (uint32_t)value);
	}
#endif

	Result _ToString(ToStringContext& context, const char* value)
	{
		if (value != nullptr)
			return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, value);
		else
			return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "(Null)");
	}

	Result _ToString(ToStringContext& context, const wchar_t* value)
	{
		char destBuff[1024];


		if (value != nullptr)
		{
			if (!StrUtil::WCSToUTF8(value, destBuff))
				return ResultCode::FAIL;

			return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, destBuff);
		}
		else
			return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "(Null)");
	}

	Result _ToString(ToStringContext& context, const std::string& value)
	{
		if (value.length() > 0)
			return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, value.c_str());
		else
			return ResultCode::SUCCESS;
	}

	Result _ToString(ToStringContext& context, const StringCrc32& value)
	{
		auto pStr = Service::StringDB->GetString(value);
		if (pStr != nullptr)
			return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, pStr);
		else
		{
			auto oldRadix = context.Radix;
			context.Radix = 16;
			auto result = _IToA(context, (uint32_t)value);
			context.Radix = oldRadix;
			return result;
		}
	}

	Result _ToString(ToStringContext& context, const StringCrc64& value)
	{
		auto pStr = Service::StringDB->GetString(value);
		if (pStr != nullptr)
			return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, pStr);
		else
		{
			auto oldRadix = context.Radix;
			context.Radix = 16;
			auto result = _IToA(context, (uint64_t)value);
			context.Radix = oldRadix;
			return result;
		}
	}

	Result _ToString(ToStringContext& context, const Result& value)
	{
		auto pStr = value.ToString();
		return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, pStr);
	}


}; // namespace StrUtil




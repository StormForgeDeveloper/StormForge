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

	constexpr int VariableBox::BUFFER_SIZE;

	VariableBox::VariableBox()
		: m_DataBuffer(GetSystemHeap())
	{
	}

	VariableBox::VariableBox(const VariableBox& src)
		: m_DataBuffer(GetSystemHeap())
	{
		if(src.m_pVariable != nullptr)
			m_pVariable = src.m_pVariable->Clone(m_DataBuffer);
	}

	VariableBox::VariableBox(const Variable& src)
		: m_DataBuffer(GetSystemHeap())
	{
		m_pVariable = src.Clone(m_DataBuffer);
	}

	VariableBox::~VariableBox()
	{
		if (m_pVariable != nullptr)
			m_pVariable->~Variable();
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
			m_pVariable->~Variable();

		m_pVariable = Service::VariableFactory->CreateVariable(m_DataBuffer, TypeName);

		return m_pVariable != nullptr;
	}

	VariableBox& VariableBox::operator = (const VariableBox& src)
	{
		if (m_pVariable != nullptr)
			m_pVariable->~Variable();
		m_pVariable = nullptr;

		if (src.m_pVariable != nullptr)
			m_pVariable = src.m_pVariable->Clone(m_DataBuffer);
		return *this;
	}


	// TODO: move to unit test
	void TestFunc()
	{
		bool TestBool = true;
		auto boxBool = Boxing(TestBool);
		Assert(Unboxing<bool>(boxBool) == TestBool);

		int TestInt = 10;
		auto boxInt = Boxing(TestInt);
		Assert(Unboxing<int>(boxInt) == TestInt);

		const char* testCharString = "TestString";
		auto boxCharStr = Boxing(testCharString);
		Assert(Unboxing<const char*>(boxCharStr) == testCharString);
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
	VariableBox BoxingByValue(const wchar_t* src) { return VariableBox(VariableWCharString(src)); } // TODO: need VariableWString
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
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, value);
		else
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(Null)");
	}

	Result _ToString(ToStringContext& context, const wchar_t* value)
	{
		char destBuff[1024];


		if (value != nullptr)
		{
			if (!StrUtil::WCSToUTF8(value, destBuff))
				return ResultCode::FAIL;

			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, destBuff);
		}
		else
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(Null)");
	}

	Result _ToString(ToStringContext& context, const std::string& value)
	{
		if (value.length() > 0)
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, value.c_str());
		else
			return ResultCode::SUCCESS;
	}



}; // namespace StrUtil




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
#include "String/SFToString.h"


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


	bool operator == (const sockaddr_storage& op1, const sockaddr_storage& op2)
	{
		if (op1.ss_family != op2.ss_family)
			return false;

		if (op1.ss_family == AF_INET)
		{
			return memcmp((sockaddr_in*)&op1, (sockaddr_in*)&op2, sizeof(sockaddr_in)) == 0;
		}
		else
		{
			return memcmp((sockaddr_in6*)&op1, (sockaddr_in6*)&op2, sizeof(sockaddr_in6)) == 0;
		}
	}

	bool operator == (const sockaddr_in& op1, const sockaddr_in& op2)
	{
		return memcmp((sockaddr_in*)&op1, (sockaddr_in*)&op2, sizeof(sockaddr_in)) == 0;
	}

	bool operator == (const sockaddr_in6& op1, const sockaddr_in6& op2)
	{
		return memcmp((sockaddr_in6*)&op1, (sockaddr_in6*)&op2, sizeof(sockaddr_in6)) == 0;
	}


}; // namespace StrUtil




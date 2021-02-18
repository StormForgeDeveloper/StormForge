////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TString
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFStrFormat.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFString.h"
#include "Util/SFStringFormat.h"
#include "Util/SFUtility.h"


namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	TString
	//


	const String String_Empty(GetSystemHeap());
	const String String_True(GetSystemHeap(), "true");
	const String String_False(GetSystemHeap(), "false");
	const String String_Success(GetSystemHeap(), "Success");
	const String String_Fail(GetSystemHeap(), "Fail");

	const WString WString_Empty(GetSystemHeap());
	const WString WString_True(GetSystemHeap(), L"true");
	const WString WString_False(GetSystemHeap(), L"false");
	const WString WString_Success(GetSystemHeap(), L"Success");
	const WString WString_Fail(GetSystemHeap(), L"Fail");


	template class TString<char>;
	template class TString<wchar_t>;


	/////////////////////////////////////////////////////////////////////////////////////
	//
	//	StringBuilder
	//

	StringBuilder::StringBuilder(IHeap& heap, size_t growSize)
		: m_GrowSize(growSize)
	{
		m_Buffer = new(heap) SharedStringBufferType(heap);
		m_Buffer->Reserve(growSize);
	}

	// Append to string
	StringBuilder& StringBuilder::Append(const StringType& src)
	{
		auto newSize = src.GetBufferLength() + m_Buffer->GetStringLength();
		if (m_Buffer->GetAllocatedSize() < newSize)
		{
			m_Buffer->Reserve(((newSize + m_GrowSize - 1) / m_GrowSize) * m_GrowSize);
		}

		m_Buffer->Append(src.data(), src.GetLength());

		return *this;
	}

	StringBuilder& StringBuilder::Append(const CharType* src)
	{
		if (src == nullptr)
			return *this;

		auto strLen = strlen(src);
		auto newSize = strLen + 1 + m_Buffer->GetStringLength();
		if (m_Buffer->GetAllocatedSize() < newSize)
		{
			m_Buffer->Reserve(((newSize + m_GrowSize - 1) / m_GrowSize) * m_GrowSize);
		}

		m_Buffer->Append(src, strLen);

		return *this;
	}

	StringBuilder& StringBuilder::Append(CharType src)
	{
		char temp[2] = {src, '\0'};

		return Append(temp);
	}


	StringBuilder& StringBuilder::Append(int number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_IToA(context, number);

		return Append(temp);
	}

	StringBuilder& StringBuilder::Append(unsigned int number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_IToA(context, number);

		return Append(temp);
	}

	StringBuilder& StringBuilder::Append(float number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_FToA(context, number);

		return Append(temp);
	}

	StringBuilder& StringBuilder::Append(double number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_FToA(context, number);

		return Append(temp);
	}

	StringBuilder::StringType StringBuilder::ToString()
	{
		return TString(GetHeap(), m_Buffer->GetBufferPointer());
	}

	size_t StringBuilder::AppendFormat_Internal(const char* szFormating, int iNumArg, VariableBox* Args)
	{
		char* szBuffer = nullptr;
		int buffLen = -1;
		size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
		size_t currentStringLen = m_Buffer->GetStringLength();
		size_t newSize = currentStringLen + requiredSize;
		if (m_Buffer->GetAllocatedSize() < newSize)
		{
			m_Buffer->Reserve(((newSize + m_GrowSize - 1) / m_GrowSize) * m_GrowSize);
		}

		szBuffer = m_Buffer->GetBufferPointer() + currentStringLen;
		buffLen = (int)requiredSize;
		auto length = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args);
		auto addedLength = StrUtil::StringLen(m_Buffer->GetBufferPointer() + currentStringLen);
		m_Buffer->Resize(currentStringLen + addedLength);

		return addedLength;
	}




} // namespace SF




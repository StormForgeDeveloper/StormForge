////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "String/SFStrFormat.h"
#include "Variable/SFVariableBoxing.h"
#include "String/SFFixedString.h"
#include "String/SFString.h"
#include "Util/SFUtility.h"


namespace SF {
	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	SharedStringBuffer
	//


	SharedStringBuffer::SharedStringBuffer(IHeap& heap)
		: m_Heap(heap)
	{

	}

	SharedStringBuffer::SharedStringBuffer(IHeap& heap, size_t initialBufferSize)
		: m_Heap(heap)
	{
		Resize(initialBufferSize);
	}

	SharedStringBuffer::SharedStringBuffer(IHeap& heap, const char* src)
		: m_Heap(heap)
	{
		if(src != nullptr)
			Append(src, strlen(src));
	}

	SharedStringBuffer::~SharedStringBuffer()
	{
		m_Heap.Free(m_StringValue);
		m_StringValue = nullptr;
	}

	bool SharedStringBuffer::Resize(size_t newAllocationSize)
	{
		if (newAllocationSize < m_StringBufferLength)
		{
			// No corping is supported
			return false;
		}

		char* newBuffer = nullptr;
		if (m_StringValue != nullptr)
		{
			newBuffer = (char*)GetHeap().Realloc(m_StringValue, newAllocationSize);
		}
		else
		{
			newBuffer = (char*)GetHeap().Alloc(newAllocationSize);
		}

		if (newBuffer == nullptr)
		{
			// out of memory
			assert(false);
			return false;
		}

		// Update allocated buffer and size
		m_StringValue = newBuffer;
		m_AllocatedSize = newAllocationSize;

		return true;
	}

	bool SharedStringBuffer::Append(const char* src, size_t strLen, size_t extraBufferSize)
	{
		if (src == nullptr) return false;

		auto newStringLength = std::max(m_StringBufferLength, (size_t)1) + strLen;
		if (newStringLength > m_AllocatedSize)
		{
			auto newAllocationSize = extraBufferSize == 0 ? newStringLength : std::max(newStringLength, m_AllocatedSize) + extraBufferSize;
			if (!Resize(newAllocationSize))
				return false;
		}

		// copy string data and update string length
		memcpy(m_StringValue + GetStringLength(), src, sizeof(char)*(strLen +1));
		m_StringValue[strLen] = '\0';
		m_StringBufferLength = strlen(m_StringValue) + 1;
		return true;
	}

	void SharedStringBuffer::Dispose()
	{
		IHeap::Free(m_StringValue);
		m_StringValue = nullptr;
	}


	void SharedStringBuffer::SetStringBufferLength(size_t newStringLength)
	{
		assert(m_AllocatedSize >= newStringLength);
		if (m_AllocatedSize < newStringLength) return;

		m_StringBufferLength = newStringLength;
		if(m_StringValue != nullptr)
			m_StringValue[m_StringBufferLength] = '\0';
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	String
	//

	const String String::Empty(GetSystemHeap());
	const String String::True(GetSystemHeap(), "true");
	const String String::False(GetSystemHeap(), "false");
	const String String::Success(GetSystemHeap(), "Success");
	const String String::Fail(GetSystemHeap(), "Fail");


	String::String()
		: m_pHeap(&GetSystemHeap())
	{
	}


	String::String(const char* src)
		: m_pHeap(&GetSystemHeap())
	{
		m_Buffer = new(GetHeap()) SharedStringBuffer(GetHeap(), src);
		m_StringValue = m_Buffer->GetBufferPointer();
	}


	String::String(const String& src)
		: m_pHeap(src.m_pHeap)
		, m_Buffer(src.m_Buffer)
	{
		m_StringValue = m_Buffer->GetBufferPointer();
	}


	String::String(IHeap& heap)
		: m_pHeap(&heap)
	{
	}


	String::String(IHeap& heap, const char* src)
		: m_pHeap(&heap)
	{
		m_Buffer = new(GetHeap()) SharedStringBuffer(GetHeap(), src);
		m_StringValue = m_Buffer->GetBufferPointer();
	}


	String::String(IHeap& heap, const char* src, int startIndex, int size)
		: m_pHeap(&heap)
	{
		size_t strLen = 0;
		if (src != nullptr)
			strLen = (int)strlen(src);

		if (startIndex >= strLen)
			return;

		if (size <= 0)
		{
			if (src != nullptr)
				size = (int)strLen - startIndex;
			else
				size = 0;
		}

		if (size > 0 && src != nullptr)
		{
			int over = (int)strLen - (startIndex + size);
			if (over < 0)
			{
				size -= over;
			}

			if (size <= 0)
				return;

			m_Buffer = new(GetHeap()) SharedStringBuffer(GetHeap(), size + 1);
			m_Buffer->Append(src + startIndex, size);
			m_StringValue = m_Buffer->GetBufferPointer();
		}
	}


	String::String(IHeap& heap, const FixedString& src)
		: m_pHeap(&heap)
	{
		m_Buffer = new(GetHeap()) SharedStringBuffer(GetHeap(), src.ToString());
		m_StringValue = m_Buffer->GetBufferPointer();
	}


	String::String(IHeap& heap, SharedStringBuffer& src)
		: m_pHeap(&heap)
	{
		m_Buffer = &src;
		m_StringValue = m_Buffer->GetBufferPointer();
	}


	String::String(IHeap& heap, const String& src)
		: m_pHeap(&heap)
		, m_Buffer(src.m_Buffer)
	{
		m_StringValue = m_Buffer->GetBufferPointer();
	}


	String::~String()
	{
	}


	String& String::Append(const String& src)
	{
		if (IsNullOrEmpty())
		{
			m_Buffer = src.m_Buffer;
			return *this;
		}

		if (src.IsNullOrEmpty())
			return *this;

		auto pStr = (const char*)src;
		auto addLen = src.GetBufferLength();
		unused(pStr, addLen);
		assert(pStr != nullptr && addLen > 0);

		auto newBuffer = new(GetHeap()) SharedStringBuffer(GetHeap(), m_Buffer->GetStringBufferLength() + src.m_Buffer->GetStringBufferLength() + 1);
		newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringBufferLength());
		newBuffer->Append(src.m_Buffer->GetBufferPointer(), src.m_Buffer->GetStringBufferLength());

		m_Buffer = newBuffer;
		m_StringValue = m_Buffer->GetBufferPointer();

		return *this;
	}

	String& String::Append(const char* src)
	{
		if (src == nullptr || src[0] == '\0')
			return *this;

		auto addLen = strlen(src);
		if (IsNullOrEmpty())
		{
			auto newBuffer = new(GetHeap()) SharedStringBuffer(GetHeap(), addLen + 1);
			newBuffer->Append(src, addLen);
			m_Buffer = newBuffer;
			return *this;
		}


		auto newBuffer = new(GetHeap()) SharedStringBuffer(GetHeap(), m_Buffer->GetStringBufferLength() + addLen + 1);
		newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringBufferLength());
		newBuffer->Append(src, addLen);

		m_Buffer = newBuffer;
		m_StringValue = m_Buffer->GetBufferPointer();

		return *this;
	}

	String& String::Append(char src)
	{
		char temp[2] = { src, '\0' };
		return Append(temp);
	}

	String& String::Append(int number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_IToA(context, number);
		//StrUtil::Format(temp, "{0}", number);
		return Append(temp);
	}

	String& String::Append(unsigned int number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_IToA(context, number);
		//StrUtil::Format(temp, "{0}", number);
		return Append(temp);
	}

	String& String::Append(float number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_FToA(context, number);
		//StrUtil::Format(temp, "{0}", number);
		return Append(temp);
	}

	String& String::Append(double number)
	{
		char temp[128];
		ToStringContext context;
		context.StringBuffer = temp;
		context.StringBufferLength = sizeof(temp);
		_FToA(context, number);
		//StrUtil::Format(temp, "{0}", number);
		return Append(temp);
	}

	String String::operator + (const String& op2) const
	{
		if (IsNullOrEmpty())
		{
			return String(op2);
		}

		if (op2.IsNullOrEmpty())
			return *this;

		auto pStr = (const char*)op2;
		auto addLen = op2.GetBufferLength();
		unused(pStr, addLen);
		assert(pStr != nullptr && addLen > 0);

		auto newBuffer = new(GetHeap()) SharedStringBuffer(GetHeap(), m_Buffer->GetStringBufferLength() + op2.m_Buffer->GetStringBufferLength() + 1);
		newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringBufferLength());
		newBuffer->Append(op2.m_Buffer->GetBufferPointer(), op2.m_Buffer->GetStringBufferLength());

		return String(GetHeap(), *newBuffer);
	}

	bool String::StartWith(const String& op, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return false;
		if (op.IsNullOrEmpty()) return false;
		auto opLen = op.GetBufferLength();
		if (opLen > GetBufferLength()) return false;

		if (opLen > 0) opLen--; // We don't want to care null terminate byte

		if(ignoreCase)
			return StrUtil::StringCompairIgnoreCase(m_Buffer->GetBufferPointer(), (int)opLen, (const char*)op, (int)opLen);
		else
			return StrUtil::StringCompair(m_Buffer->GetBufferPointer(), (int)opLen, (const char*)op, (int)opLen);
	}

	bool String::StartWith(const char* op, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return false;
		if (StrUtil::IsNullOrEmpty(op)) return false;

		auto opLen = strlen(op);
		if (opLen > GetBufferLength()) return false;

		if (ignoreCase)
			return StrUtil::StringCompairIgnoreCase(m_Buffer->GetBufferPointer(), (int)opLen, (const char*)op, (int)opLen);
		else
			return StrUtil::StringCompair(m_Buffer->GetBufferPointer(), (int)opLen, (const char*)op, (int)opLen);
	}

	bool String::StartWith(char op, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return false;
		if (op == '\0') return false;

		char opStr[] = {op, '\0'};

		if (ignoreCase)
			return StrUtil::StringCompairIgnoreCase(m_Buffer->GetBufferPointer(), 1, (const char*)opStr, (int)1);
		else
			return StrUtil::StringCompair(m_Buffer->GetBufferPointer(), 1, (const char*)opStr, (int)1);
	}

	bool String::EndsWith(const String& op, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return false;
		if (op.IsNullOrEmpty()) return false;
		auto opLen = op.GetBufferLength();
		if (opLen > GetBufferLength()) return false;

		auto compareStart = m_Buffer->GetBufferPointer() + GetBufferLength() - opLen;

		if (ignoreCase)
			return StrUtil::StringCompairIgnoreCase(compareStart, (int)opLen, (const char*)op, (int)opLen);
		else
			return StrUtil::StringCompair(compareStart, (int)opLen, (const char*)op, (int)opLen);
	}

	bool String::EndsWith(const char* op, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return false;
		if (StrUtil::IsNullOrEmpty(op)) return false;

		auto opLen = strlen(op);
		if (opLen > GetBufferLength()) return false;

		auto compareStart = m_Buffer->GetBufferPointer() + GetBufferLength() - opLen;

		if (ignoreCase)
			return StrUtil::StringCompairIgnoreCase(compareStart, (int)opLen, (const char*)op, (int)opLen);
		else
			return StrUtil::StringCompair(compareStart, (int)opLen, (const char*)op, (int)opLen);
	}

	bool String::EndsWith(char op, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return false;
		if (op == '\0') return false;

		char opStr[] = { op, '\0' };

		auto compareStart = m_Buffer->GetBufferPointer() + GetBufferLength() - 1;

		if (ignoreCase)
			return StrUtil::StringCompairIgnoreCase(compareStart, (int)1, (const char*)opStr, (int)1);
		else
			return StrUtil::StringCompair(compareStart, (int)1, (const char*)opStr, (int)1);
	}

	int String::IndexOf(char searchChar) const
	{
		if (IsNullOrEmpty()) return -1;

		auto len = GetBufferLength();
		auto pCur = m_Buffer->GetBufferPointer();
		for (size_t iChar = 0; iChar < len; iChar++, pCur++)
		{
			if (*pCur == searchChar) return (int)iChar;
		}

		return -1;
	}

	int String::IndexOf(const char* searchString, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return -1;
		if (searchString == nullptr) return -1;

		auto strLen = strlen(searchString);

		auto len = GetBufferLength();
		auto pCur = m_Buffer->GetBufferPointer();

		if (ignoreCase)
		{
			for (size_t iOffset = 0; iOffset < len; iOffset++, pCur++)
			{
				if (StrUtil::StringCompairIgnoreCase(pCur, (int)strLen, searchString, (int)strLen)) return (int)iOffset;
			}
		}
		else
		{
			for (size_t iOffset = 0; iOffset < len; iOffset++, pCur++)
			{
				if (StrUtil::StringCompair(pCur, (int)strLen, searchString, (int)strLen)) return (int)iOffset;
			}
		}

		return -1;
	}

	int String::IndexOfAny(const char* searchChars) const
	{
		if (IsNullOrEmpty()) return -1;
		if (searchChars == nullptr) return -1;

		auto numChar = strlen(searchChars);

		auto len = GetBufferLength();
		auto pCur = m_Buffer->GetBufferPointer();

		for (size_t iOffset = 0; iOffset < len; iOffset++, pCur++)
		{
			for (size_t iChar = 0; iChar < numChar; iChar++)
			{
				if (*pCur == searchChars[iChar]) return (int)iOffset;
			}
		}

		return -1;
	}

	int String::IndexOfFromEnd(const char* searchString, bool ignoreCase) const
	{
		if (IsNullOrEmpty()) return -1;
		if (searchString == nullptr) return -1;

		auto strLen = (int)strlen(searchString);

		auto len = (int)GetBufferLength() - strLen;
		auto pCur = m_Buffer->GetBufferPointer() + len;

		if (ignoreCase)
		{
			for (int iOffset = len; iOffset >= 0; iOffset--, pCur--)
			{
				if (StrUtil::StringCompairIgnoreCase(pCur, strLen, searchString, strLen)) return iOffset;
			}
		}
		else
		{
			for (int iOffset = len; iOffset >= 0; iOffset--, pCur--)
			{
				if (StrUtil::StringCompair(pCur, strLen, searchString, strLen)) return iOffset;
			}
		}

		return -1;
	}

	int String::IndexOfFromEnd(char searchChar) const
	{
		if (IsNullOrEmpty()) return -1;

		auto len = (int)GetBufferLength() - 1;
		auto pCur = m_Buffer->GetBufferPointer() + len;

		for (int iOffset = len; iOffset >= 0; iOffset--, pCur--)
		{
			if (*pCur == searchChar) return iOffset;
		}

		return -1;
	}

	int String::IndexOfAnyFromEnd(const char* searchChars) const
	{
		if (IsNullOrEmpty()) return -1;
		if (searchChars == nullptr) return -1;

		auto numChar = (int)strlen(searchChars);

		auto len = (int)GetBufferLength() - 1;
		auto pCur = m_Buffer->GetBufferPointer() + len;

		for (int iOffset = len; iOffset >= 0; iOffset--, pCur--)
		{
			for (int iChar = 0; iChar < numChar; iChar++)
			{
				if (*pCur == searchChars[iChar]) return iOffset;
			}
		}

		return -1;
	}

	String String::Join(const Array<String>& strings, const char* delimiter)
	{
		if (strings.size() == 0)
			return String(GetEngineHeap());

		size_t totalSize = 0;
		auto delimiterSize = strlen(delimiter);
		for (size_t iItem = 0; iItem < strings.size(); iItem++)
		{
			totalSize += strings[iItem].GetBufferLength();
		}

		auto& heap = strings[0].GetHeap();
		auto newBuffer = new(heap) SharedStringBuffer(heap, totalSize + strings.size() * delimiterSize + 1);
		for (size_t iItem = 0; iItem < strings.size(); iItem++)
		{
			if(iItem != 0)
				newBuffer->Append(delimiter, delimiterSize);
			newBuffer->Append((const char*)strings[iItem], strings[iItem].GetBufferLength());
		}

		return String(heap, *newBuffer);
	}

	bool String::Split(const char* delimiterString, bool ignoreCase, Array<String>& stringsOut) const
	{
		if (IsNullOrEmpty()) return false;
		if (delimiterString == nullptr) return false;

		auto strLen = strlen(delimiterString);

		auto len = GetBufferLength();
		auto pCur = m_Buffer->GetBufferPointer();
		size_t iStart = 0;

		if (ignoreCase)
		{
			for (size_t iOffset = 0; iOffset < len; iOffset++, pCur++)
			{
				if (StrUtil::StringCompairIgnoreCase(pCur, (int)strLen, delimiterString, (int)strLen))
				{
					if(iStart < iOffset)
						stringsOut.push_back(SubString((int)iStart, (int)(iOffset - iStart)));
					iStart = iOffset + 1;
				}
			}
		}
		else
		{
			for (size_t iOffset = 0; iOffset < len; iOffset++, pCur++)
			{
				if (StrUtil::StringCompair(pCur, (int)strLen, delimiterString, (int)strLen))
				{
					if (iStart < iOffset)
						stringsOut.push_back(SubString((int)iStart, (int)(iOffset - iStart)));
					iStart = iOffset + 1;
				}
			}
		}

		return true;
	}

	bool String::SplitAny(const char* delimiterChars, Array<String>& stringsOut) const
	{
		if (IsNullOrEmpty()) return false;
		if (delimiterChars == nullptr) return false;

		auto numChar = strlen(delimiterChars);

		auto len = GetBufferLength();
		auto pCur = m_Buffer->GetBufferPointer();
		size_t iStart = 0;

		size_t iOffset = 0;
		for (; iOffset < len; iOffset++, pCur++)
		{
			for (size_t iChar = 0; iChar < numChar; iChar++)
			{
				if (*pCur == delimiterChars[iChar])
				{
					if (iStart < iOffset)
						stringsOut.push_back(SubString((int)iStart, (int)(iOffset - iStart)));
					iStart = iOffset + 1;
					break;
				}
			}
		}

		if (iStart < iOffset && iStart < len)
			stringsOut.push_back(SubString((int)iStart, (int)(iOffset - iStart)));

		return true;
	}

	String& String::ConvertToUpper()
	{
		if (IsNullOrEmpty()) return *this;

		StrUtil::StringUpper(m_Buffer->GetBufferPointer(), (int)m_Buffer->GetStringBufferLength());

		return *this;
	}

	String& String::ConvertToLower()
	{
		if (IsNullOrEmpty()) return *this;

		StrUtil::StringLower(m_Buffer->GetBufferPointer(), (int)m_Buffer->GetStringBufferLength());

		return *this;
	}

	String String::ToUpper() const
	{
		if (IsNullOrEmpty()) return *this;

		auto newBuffer = new(GetHeap()) SharedStringBuffer(GetHeap(), GetBufferLength() + 1);
		auto bufferPointer = newBuffer->GetBufferPointer();
		int bufferSize = (int)newBuffer->GetAllocatedSize();
		StrUtil::StringUpper(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());

		return String(GetHeap(), *newBuffer);
	}

	String String::ToLower() const
	{
		if (IsNullOrEmpty()) return *this;

		auto newBuffer = new(GetHeap()) SharedStringBuffer(GetHeap(), GetBufferLength() + 1);
		auto bufferPointer = newBuffer->GetBufferPointer();
		int bufferSize = (int)newBuffer->GetAllocatedSize();
		StrUtil::StringLower(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());

		return String(GetHeap(), *newBuffer);
	}

	bool String::IsEqual(const String& op) const
	{
		return StrUtil::StringCompair((const char*)*this, (int)GetBufferLength(), (const char*)op, (int)op.GetBufferLength());
	}

	bool String::IsEqual(const char* op) const
	{
		auto opLen = op != nullptr ? strlen(op) : 0;
		return StrUtil::StringCompair((const char*)*this, (int)GetBufferLength(), (const char*)op, (int)opLen);
	}

	bool String::IsEqualIgnoreCase(const String& op) const
	{
		return StrUtil::StringCompairIgnoreCase((const char*)*this, (int)GetBufferLength(), (const char*)op, (int)op.GetBufferLength());
	}

	bool String::IsEqualIgnoreCase(const char* op) const
	{
		auto opLen = op != nullptr ? strlen(op) : 0;
		return StrUtil::StringCompairIgnoreCase((const char*)*this, (int)GetBufferLength(), (const char*)op, (int)opLen);
	}

	String String::Trim() const
	{
		if (IsNullOrEmpty()) return *this;

		auto len = (int)GetBufferLength();
		auto strString = m_Buffer->GetBufferPointer();
		int iStart = 0;
		int iEnd = len - 1;
		for (; iStart < len; iStart++)
		{
			if (!StrUtil::IsWhiteSpace(strString[iStart])) break;
		}

		for (; iEnd > iStart; iEnd--)
		{
			if (!StrUtil::IsWhiteSpace(strString[iEnd])) break;
		}

		if (iEnd < iStart)
		{
			return String(GetHeap(), "");
		}
		else
		{
			return SubString(iStart, iEnd - iStart + 1);
		}
	}

	String String::TrimAny(const char* chars) const
	{
		if (IsNullOrEmpty()) return *this;
		if (chars == nullptr) return *this;

		auto numChar = (int)strlen(chars);

		auto len = (int)GetBufferLength();
		auto strString = m_Buffer->GetBufferPointer();
		int iStart = 0;
		int iEnd = len - 1;

		for (; iStart < len; iStart++)
		{
			auto curChar = strString[iStart];
			int iChar = 0;
			for (; iChar < numChar; iChar++)
			{
				if (chars[iChar] == curChar) break;
			}

			if (iChar >= numChar) break;
		}

		for (; iEnd > iStart; iEnd--)
		{
			auto curChar = strString[iEnd];
			int iChar = 0;
			for (; iChar < numChar; iChar++)
			{
				if (chars[iChar] == curChar) break;
			}

			if (iChar >= numChar) break;
		}

		if (iEnd < iStart)
		{
			return String(GetHeap(), "");
		}
		else
		{
			return SubString(iStart, iEnd - iStart + 1);
		}
	}

	String String::TrimStart(const char* chars) const
	{
		if (IsNullOrEmpty()) return *this;
		if (chars == nullptr) return *this;

		auto numChar = (int)strlen(chars);

		auto len = (int)GetBufferLength();
		auto strString = m_Buffer->GetBufferPointer();
		int iStart = 0;
		int iEnd = len - 1;

		for (; iStart < len; iStart++)
		{
			auto curChar = strString[iStart];
			int iChar = 0;
			for (; iChar < numChar; iChar++)
			{
				if (chars[iChar] == curChar) break;
			}

			if (iChar >= numChar) break;
		}

		if (iEnd < iStart)
		{
			return String(GetHeap(), "");
		}
		else
		{
			return SubString(iStart, iEnd - iStart + 1);
		}
	}

	String String::TrimEnd(const char* chars) const
	{
		if (IsNullOrEmpty()) return *this;
		if (chars == nullptr) return *this;

		auto numChar = (int)strlen(chars);

		auto len = (int)GetBufferLength();
		auto strString = m_Buffer->GetBufferPointer();
		int iStart = 0;
		int iEnd = len - 1;

		for (; iEnd > iStart; iEnd--)
		{
			auto curChar = strString[iEnd];
			int iChar = 0;
			for (; iChar < numChar; iChar++)
			{
				if (chars[iChar] == curChar) break;
			}

			if (iChar >= numChar) break;
		}

		if (iEnd < iStart)
		{
			return String(GetHeap(), "");
		}
		else
		{
			return SubString(iStart, iEnd - iStart + 1);
		}
	}


	String String::SubString(int starIndex, int count) const
	{
		if (IsNullOrEmpty()) return *this;

		auto length = (int)GetBufferLength();
		if (starIndex >= length) return String(GetHeap());

		auto newBuffer = new(GetEngineHeap()) SharedStringBuffer(GetHeap(), count + 1);
		auto pDest = newBuffer->GetBufferPointer();
		//int bufferSize = (int)newBuffer->GetAllocatedSize();
		auto pSrc = m_Buffer->GetBufferPointer() + starIndex;

		// clip to the string boundary
		if ((starIndex + count) > (length + 1))
		{
			count -= (starIndex + count) - (length + 1);
		}

		memcpy(pDest, pSrc, count*sizeof(char));
		pDest[count] = '\0';

		return String(GetHeap(), *newBuffer);
	}



	bool String::operator == (const char* src) const
	{
		if (m_Buffer == nullptr && src == nullptr) return true;
		if (m_Buffer == nullptr || src == nullptr) return false;

		auto myBuffer = m_Buffer->GetBufferPointer();
		auto opBuffer = src;
		// Actually I want to check "myBuffer == nullptr && opBuffer == nullptr", but comparing both pointer will give me the result
		if (myBuffer == opBuffer) return true; 
		if (myBuffer == nullptr) return false;

		return StrUtil::StringCompair(myBuffer, (INT)m_Buffer->GetStringBufferLength(), opBuffer, -1);
	}

	bool String::operator != (const char* src) const
	{
		return !this->operator == (src);
	}

	String& String::operator = (const char* src)
	{
		m_Buffer = nullptr;

		if (src == nullptr)
			return *this;

		m_Buffer = new(GetHeap()) SharedStringBuffer(GetHeap(), src);
		m_StringValue = m_Buffer->GetBufferPointer();

		return *this;
	}

	String& String::operator = (const String& src)
	{
		m_Buffer = src.m_Buffer;
		if(m_Buffer != nullptr)
			m_StringValue = m_Buffer->GetBufferPointer();

		return *this;
	}

	size_t String::Format_Internal(const char* szFormating, int iNumArg, VariableBox* Args)
	{
		char* szBuffer = nullptr;
		int buffLen = -1;
		size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
		m_Buffer = new(GetHeap()) SharedStringBuffer(GetHeap(), requiredSize);
		if (m_Buffer->GetAllocatedSize() != requiredSize)
			return 0;

		szBuffer = m_Buffer->GetBufferPointer();
		buffLen = (int)requiredSize;
		auto length = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args);
		m_Buffer->SetStringBufferLength(length);

		m_StringValue = m_Buffer->GetBufferPointer();

		return length;
	}

	size_t String::AppendFormat_Internal(const char* szFormating, int iNumArg, VariableBox* Args)
	{
		char* szBuffer = nullptr;
		int buffLen = -1;
		size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
		size_t currentStringLen = m_Buffer->GetStringLength();
		size_t totalSize = currentStringLen + requiredSize;
		if (m_Buffer->GetAllocatedSize() < totalSize)
			m_Buffer->Resize(totalSize);

		szBuffer = m_Buffer->GetBufferPointer() + currentStringLen;
		buffLen = (int)requiredSize;
		auto length = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args);
		m_Buffer->SetStringBufferLength(totalSize);

		m_StringValue = m_Buffer->GetBufferPointer();

		return length;
	}





} // namespace SF




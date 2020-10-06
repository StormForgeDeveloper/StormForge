////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : string
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "String/SFStrUtil.h"
#include "String/SFToStringBase.h"
#include "Container/SFArray.h"


namespace SF {

	class StringCrc64;
	class VariableBox;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	TSharedStringBuffer
	//

	template<typename CharType>
	class TSharedStringBuffer : public SharedObject
	{
	private:

		// string buffer
		CharType* m_StringValue = nullptr;

		// Heap
		IHeap& m_Heap;

		// actually allocated size in bytes
		size_t m_AllocatedSize = 0;

		// TString length exclude null termination
		size_t m_StringLength = 0;

	public:

		TSharedStringBuffer(IHeap& heap)
			: m_Heap(heap)
		{
		}

		TSharedStringBuffer(IHeap& heap, size_t initialCharCount)
			: m_Heap(heap)
		{
			Reserve(initialCharCount);
		}

		template<typename CharType2>
		TSharedStringBuffer(IHeap& heap, const CharType2* src)
			: m_Heap(heap)
		{
			if (src == nullptr)
				return;

			Append(src, StrUtil::StringLen(src));
		}

		~TSharedStringBuffer()
		{
			m_Heap.Free(m_StringValue);
			m_StringValue = nullptr;
		}

		IHeap& GetHeap() { return m_Heap; }

		//  resize with string length
		bool Resize(size_t newStrLen)
		{
			Reserve(newStrLen);

			m_StringValue[newStrLen] = {};
			m_StringLength = newStrLen;

			return true;
		}

		bool Reserve(size_t newStrLen)
		{
			auto newAllocationSize = (newStrLen + 1) * sizeof(CharType);
			if (newAllocationSize > m_AllocatedSize)
			{
				CharType* newBuffer = nullptr;
				if (m_StringValue != nullptr)
				{
					newBuffer = reinterpret_cast<CharType*>(GetHeap().Realloc(m_StringValue, newAllocationSize));
				}
				else
				{
					newBuffer = reinterpret_cast<CharType*>(GetHeap().Alloc(newAllocationSize));
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
			}

			return true;
		}


		// append string
		template<typename CharType2>
		bool Append(const CharType2* src, size_t strLen)
		{
			if (src == nullptr) return false;

			auto newStringLength = m_StringLength + strLen;
			auto newAllocationSize = (newStringLength + 1) * sizeof(CharType);
			if (newAllocationSize > m_AllocatedSize)
			{
				if (!Reserve(newStringLength))
					return false;
			}

			// copy string data and update string length
			auto copyStart = m_StringValue + GetStringLength();
			memcpy(copyStart, src, sizeof(CharType) * strLen);
			copyStart[strLen] = {};
			m_StringLength = m_StringLength + strLen;
			assert(m_StringLength == StrUtil::StringLen(m_StringValue));
			return true;
		}


		virtual void Dispose() override
		{
			IHeap::Free(m_StringValue);
			m_StringValue = nullptr;
		}

		size_t GetStringLength() const { return m_StringLength; }
		size_t GetStringBufferLength() const { return m_StringLength > 0 ? (m_StringLength + 1) * sizeof(CharType) : 0; }

		CharType* GetBufferPointer() const { return m_StringValue; }
		size_t GetAllocatedSize() const { return m_AllocatedSize; }
	};




	////////////////////////////////////////////////////////////////////////////////
	//
	//	SFString
	//     - Shared string buffer system like C# string
	//

	template<typename CharType, typename SharedStringBufferType = TSharedStringBuffer<CharType>>
	class TString
	{
	public:

		using StringType = TString<CharType, SharedStringBufferType>;

		static const StringType Empty;
		static const StringType True;
		static const StringType False;
		static const StringType Success;
		static const StringType Fail;


	private:

		// cached string value for debugging
		CharType* m_StringValue = nullptr;

		// Heap for string operation
		IHeap* m_pHeap = nullptr;

		// string buffer
		SharedPointerT<SharedStringBufferType> m_Buffer;

	public:
		TString()
			: m_pHeap(&GetSystemHeap())
		{
		}

		TString(const CharType* src)
			: m_pHeap(&GetSystemHeap())
		{
			m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), src);
			m_StringValue = m_Buffer->GetBufferPointer();
		}

		TString(const TString& src)
			: m_pHeap(src.m_pHeap)
			, m_Buffer(src.m_Buffer)
			, m_StringValue(nullptr)
		{
			if (m_Buffer != nullptr)
				m_StringValue = m_Buffer->GetBufferPointer();
		}

		TString(IHeap& heap)
			: m_pHeap(&heap)
		{
		}

		TString(IHeap& heap, const CharType* src)
			: m_pHeap(&heap)
		{
			m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), src);
			m_StringValue = m_Buffer->GetBufferPointer();
		}

		TString(IHeap& heap, const CharType* src, int startIndex, int size = -1)
			: m_pHeap(&heap)
		{
			size_t strLen = 0;
			if (src != nullptr)
				strLen = (int)StrUtil::StringLen(src);

			if (startIndex >= static_cast<int>(strLen))
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

				m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), size + 1);
				m_Buffer->Append(src + startIndex, size);
				m_StringValue = m_Buffer->GetBufferPointer();
			}
		}

		TString(IHeap& heap, const StringCrc64& src)
			: m_pHeap(&heap)
		{
			m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), src.ToString());
			m_StringValue = m_Buffer->GetBufferPointer();
		}

		TString(IHeap& heap, const TString& src)
			: m_pHeap(&heap)
		{
			m_Buffer = src.m_Buffer;
			m_StringValue = m_Buffer->GetBufferPointer();
		}

		TString(IHeap& heap, SharedPointerT<SharedStringBufferType>&& src)
			: m_pHeap(&heap)
		{
			m_Buffer = std::forward<SharedPointerT<SharedStringBufferType>>(src);
			m_StringValue = m_Buffer->GetBufferPointer();
		}

		~TString() {}

		IHeap& GetHeap() const { return *m_pHeap; }
		void SetHeap(IHeap& heap) { m_pHeap = &heap; }

		// get string length
		size_t GetBufferLength() const { return m_Buffer != nullptr ? m_Buffer->GetStringBufferLength() : 0; }
		size_t GetLength() const { auto bufferLen = GetBufferLength();  return bufferLen > 0 ? bufferLen - 1 : 0; }
		size_t size() const { return GetLength(); }
		size_t length() const { return GetLength(); }


		// Reserve buffer and set size. filled data will be garbage
		void Resize(size_t newStrLen) { m_Buffer->Resize(newStrLen); }
		// Reserver buffer
		void Reserve(size_t newStrLen) { m_Buffer->Reserve(newStrLen); }
		// Check whether it's null or empty string
		bool IsNullOrEmpty() const { return m_Buffer == nullptr || m_Buffer->GetStringLength() == 0; }

		// Append to string
		StringType& Append(const StringType& src)
		{
			if (IsNullOrEmpty())
			{
				m_Buffer = src.m_Buffer;
				return *this;
			}

			if (src.IsNullOrEmpty())
				return *this;

			auto pStr = (const CharType*)src;
			auto addLen = src.GetBufferLength();
			unused(pStr, addLen);
			assert(pStr != nullptr && addLen > 0);


			if (m_Buffer->IsUniquelyReferenced())
			{
				m_Buffer->Append(src.m_Buffer->GetBufferPointer(), src.m_Buffer->GetStringLength());
			}
			else
			{
				auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + src.m_Buffer->GetStringLength() + 1);
				newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringLength());
				newBuffer->Append(src.m_Buffer->GetBufferPointer(), src.m_Buffer->GetStringLength());

				m_Buffer = newBuffer;
			}
			m_StringValue = m_Buffer->GetBufferPointer();

			return *this;
		}

		StringType& Append(const char* src)
		{
			if (StrUtil::IsNullOrEmpty(src))
				return *this;

			auto addLen = StrUtil::StringLen(src);
			if (IsNullOrEmpty())
			{
				auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), addLen + 1);
				newBuffer->Append(src, addLen);
				m_Buffer = newBuffer;
				return *this;
			}

			if (m_Buffer->IsUniquelyReferenced())
			{
				m_Buffer->Append(src, addLen);
			}
			else
			{
				auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + addLen + 1);
				newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringLength());
				newBuffer->Append(src, addLen);

				m_Buffer = newBuffer;
			}

			m_StringValue = m_Buffer->GetBufferPointer();

			return *this;
		}

		StringType& Append(const wchar_t* src)
		{
			if (StrUtil::IsNullOrEmpty(src))
				return *this;

			auto addLen = StrUtil::StringLen(src);
			if (IsNullOrEmpty())
			{
				auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), addLen + 1);
				newBuffer->Append(src, addLen);
				m_Buffer = newBuffer;
				return *this;
			}

			if (m_Buffer->IsUniquelyReferenced())
			{
				m_Buffer->Append(src, addLen);
			}
			else
			{
				auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + addLen + 1);
				newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringLength());
				newBuffer->Append(src, addLen);

				m_Buffer = newBuffer;
			}

			m_StringValue = m_Buffer->GetBufferPointer();

			return *this;
		}

		StringType& Append(char src)
		{
			char temp[2] = { src, char{} };
			return Append(temp);
		}

		StringType& Append(wchar_t src)
		{
			wchar_t temp[2] = { src, wchar_t{} };
			return Append(temp);
		}

		StringType& Append(int number)
		{
			char temp[128];
			ToStringContext context;
			context.StringBuffer = temp;
			context.StringBufferLength = sizeof(temp);
			_IToA(context, number);

			return Append(temp);
		}

		StringType& Append(unsigned int number)
		{
			char temp[128];
			ToStringContext context;
			context.StringBuffer = temp;
			context.StringBufferLength = sizeof(temp);
			_IToA(context, number);

			return Append(temp);
		}

		StringType& Append(float number)
		{
			char temp[128];
			ToStringContext context;
			context.StringBuffer = temp;
			context.StringBufferLength = sizeof(temp);
			_FToA(context, number);

			return Append(temp);
		}

		StringType& Append(double number)
		{
			char temp[128];
			ToStringContext context;
			context.StringBuffer = temp;
			context.StringBufferLength = sizeof(temp);
			_FToA(context, number);

			return Append(temp);
		}

		// combine string
		StringType operator + (const StringType& op2) const
		{
			if (IsNullOrEmpty())
			{
				return TString(op2);
			}

			if (op2.IsNullOrEmpty())
				return *this;

			auto pStr = (const CharType*)op2;
			auto addLen = op2.GetBufferLength();
			unused(pStr, addLen);
			assert(pStr != nullptr && addLen > 0);

			auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + op2.m_Buffer->GetStringLength() + 1);
			newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringLength());
			newBuffer->Append(op2.m_Buffer->GetBufferPointer(), op2.m_Buffer->GetStringLength());

			return TString(GetHeap(), std::forward<SharedPointerT<SharedStringBufferType>>(newBuffer));
		}

		// Check heading string
		bool StartWith(const StringType& op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (op.IsNullOrEmpty()) return false;
			auto opLen = op.GetBufferLength();
			if (opLen > GetBufferLength()) return false;

			if (opLen > 0) opLen--; // We don't want to care null terminate byte

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(m_Buffer->GetBufferPointer(), (int)opLen, (const CharType*)op, (int)opLen);
			else
				return StrUtil::StringCompair(m_Buffer->GetBufferPointer(), (int)opLen, (const CharType*)op, (int)opLen);
		}

		bool StartWith(const CharType* op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (StrUtil::IsNullOrEmpty(op)) return false;

			auto opLen = StrUtil::StringLen(op);
			if (opLen > GetBufferLength()) return false;

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(m_Buffer->GetBufferPointer(), (int)opLen, (const CharType*)op, (int)opLen);
			else
				return StrUtil::StringCompair(m_Buffer->GetBufferPointer(), (int)opLen, (const CharType*)op, (int)opLen);
		}

		bool StartWith(CharType op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (op == CharType{}) return false;

			CharType opStr[] = { op, CharType{} };

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(m_Buffer->GetBufferPointer(), 1, (const CharType*)opStr, (int)1);
			else
				return StrUtil::StringCompair(m_Buffer->GetBufferPointer(), 1, (const CharType*)opStr, (int)1);
		}

		// Check tailing string
		bool EndsWith(const StringType& op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (op.IsNullOrEmpty()) return false;
			auto opLen = op.GetBufferLength();
			if (opLen > GetBufferLength()) return false;

			auto compareStart = m_Buffer->GetBufferPointer() + GetBufferLength() - opLen;

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(compareStart, (int)opLen, (const CharType*)op, (int)opLen);
			else
				return StrUtil::StringCompair(compareStart, (int)opLen, (const CharType*)op, (int)opLen);
		}

		bool EndsWith(const CharType* op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (StrUtil::IsNullOrEmpty(op)) return false;

			auto opLen = StrUtil::StringLen(op);
			if (opLen > GetBufferLength()) return false;

			auto compareStart = m_Buffer->GetBufferPointer() + GetBufferLength() - opLen;

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(compareStart, (int)opLen, (const CharType*)op, (int)opLen);
			else
				return StrUtil::StringCompair(compareStart, (int)opLen, (const CharType*)op, (int)opLen);
		}

		bool EndsWith(CharType op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (op == CharType{}) return false;

			CharType opStr[] = { op, CharType{} };

			auto compareStart = m_Buffer->GetBufferPointer() + GetBufferLength() - 1;

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(compareStart, (int)1, (const CharType*)opStr, (int)1);
			else
				return StrUtil::StringCompair(compareStart, (int)1, (const CharType*)opStr, (int)1);
		}

		// Find the first index of searchChar.
		int IndexOf(CharType searchChar) const
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

		// Find the first index of searchString in the string
		int IndexOf(const CharType* searchString, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return -1;
			if (searchString == nullptr) return -1;

			auto strLen = StrUtil::StringLen(searchString);

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

		// Find the first index of any character in searchChars. The last element of the searchChars should be null
		int IndexOfAny(const CharType* searchChars) const
		{
			if (IsNullOrEmpty()) return -1;
			if (searchChars == nullptr) return -1;

			auto numChar = StrUtil::StringLen(searchChars);

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

		// search from end
		int IndexOfFromEnd(const CharType* searchString, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return -1;
			if (searchString == nullptr) return -1;

			auto strLen = (int)StrUtil::StringLen(searchString);

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

		int IndexOfFromEnd(CharType searchChar) const
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

		int IndexOfAnyFromEnd(const CharType* searchChars) const
		{
			if (IsNullOrEmpty()) return -1;
			if (searchChars == nullptr) return -1;

			auto numChar = (int)StrUtil::StringLen(searchChars);

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


		// Join string array
		static TString Join(const Array<StringType>& strings, const CharType* delimiter)
		{
			if (strings.size() == 0)
				return TString(GetEngineHeap());

			size_t totalSize = 0;
			auto delimiterSize = StrUtil::StringLen(delimiter);
			for (size_t iItem = 0; iItem < strings.size(); iItem++)
			{
				totalSize += strings[iItem].GetBufferLength();
			}

			auto& heap = strings[0].GetHeap();
			auto newBuffer = new(heap) SharedStringBufferType(heap, totalSize + strings.size() * delimiterSize + 1);
			for (size_t iItem = 0; iItem < strings.size(); iItem++)
			{
				if (iItem != 0)
					newBuffer->Append(delimiter, delimiterSize);
				newBuffer->Append((const CharType*)strings[iItem], strings[iItem].GetBufferLength());
			}

			return TString(heap, newBuffer);
		}

		// Split string into array with delimiter string 
		bool Split(const CharType* delimiterString, bool ignoreCase, Array<TString>& stringsOut) const
		{
			if (IsNullOrEmpty()) return false;
			if (delimiterString == nullptr) return false;

			auto strLen = StrUtil::StringLen(delimiterString);

			auto len = GetBufferLength();
			auto pCur = m_Buffer->GetBufferPointer();
			size_t iStart = 0;

			if (ignoreCase)
			{
				for (size_t iOffset = 0; iOffset < len; iOffset++, pCur++)
				{
					if (StrUtil::StringCompairIgnoreCase(pCur, (int)strLen, delimiterString, (int)strLen))
					{
						if (iStart < iOffset)
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

		// Split string into array with delimiter characters. The last element of the delimiterChars should be null
		bool SplitAny(const CharType* delimiterChars, Array<TString>& stringsOut) const
		{
			if (IsNullOrEmpty()) return false;
			if (delimiterChars == nullptr) return false;

			auto numChar = StrUtil::StringLen(delimiterChars);

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


		// In-place string case conversion
		StringType& ConvertToUpper()
		{
			if (IsNullOrEmpty()) return *this;

			StrUtil::StringUpper(m_Buffer->GetBufferPointer(), (int)m_Buffer->GetStringBufferLength());

			return *this;
		}

		StringType& ConvertToLower()
		{
			if (IsNullOrEmpty()) return *this;

			StrUtil::StringLower(m_Buffer->GetBufferPointer(), (int)m_Buffer->GetStringBufferLength());

			return *this;
		}

		// TString case conversion.
		StringType ToUpper() const
		{
			if (IsNullOrEmpty()) return *this;

			auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), GetBufferLength() + 1);
			auto bufferPointer = newBuffer->GetBufferPointer();
			int bufferSize = (int)newBuffer->GetAllocatedSize();
			StrUtil::StringUpper(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());

			return TString(GetHeap(), newBuffer);
		}

		StringType ToLower() const
		{
			if (IsNullOrEmpty()) return *this;

			auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), GetBufferLength() + 1);
			auto bufferPointer = newBuffer->GetBufferPointer();
			int bufferSize = (int)newBuffer->GetAllocatedSize();
			StrUtil::StringLower(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());

			return TString(GetHeap(), newBuffer);
		}

		bool IsEqual(const StringType& op) const
		{
			return StrUtil::StringCompair((const CharType*)*this, (int)GetBufferLength(), (const CharType*)op, (int)op.GetBufferLength());
		}

		bool IsEqual(const CharType* op) const
		{
			auto opLen = op != nullptr ? StrUtil::StringLen(op) : 0;
			return StrUtil::StringCompair((const CharType*)*this, (int)GetBufferLength(), (const CharType*)op, (int)opLen);
		}

		bool IsEqualIgnoreCase(const StringType& op) const
		{
			return StrUtil::StringCompairIgnoreCase((const CharType*)*this, (int)GetBufferLength(), (const CharType*)op, (int)op.GetBufferLength());
		}
		bool IsEqualIgnoreCase(const CharType* op) const
		{
			auto opLen = op != nullptr ? StrUtil::StringLen(op) : 0;
			return StrUtil::StringCompairIgnoreCase((const CharType*)*this, (int)GetBufferLength(), (const CharType*)op, (int)opLen);
		}

		// Removes all leading and trailing white-space characters from the current TString object.
		StringType Trim() const
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
				return TString(GetHeap(), "");
			}
			else
			{
				return SubString(iStart, iEnd - iStart + 1);
			}
		}

		// Removes all leading and trailing characters in the list from the current TString object.
		StringType TrimAny(const CharType* chars) const
		{
			if (IsNullOrEmpty()) return *this;
			if (chars == nullptr) return *this;

			auto numChar = (int)StrUtil::StringLen(chars);

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
				return TString(GetHeap(), "");
			}
			else
			{
				return SubString(iStart, iEnd - iStart + 1);
			}
		}

		StringType TrimStart(const CharType* chars) const
		{
			if (IsNullOrEmpty()) return *this;
			if (chars == nullptr) return *this;

			auto numChar = (int)StrUtil::StringLen(chars);

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
				return TString(GetHeap(), "");
			}
			else
			{
				return SubString(iStart, iEnd - iStart + 1);
			}
		}

		StringType TrimEnd(const CharType* chars) const
		{
			if (IsNullOrEmpty()) return *this;
			if (chars == nullptr) return *this;

			auto numChar = (int)StrUtil::StringLen(chars);

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
				return TString(GetHeap(), "");
			}
			else
			{
				return SubString(iStart, iEnd - iStart + 1);
			}
		}


		// Make a copy of sub string
		StringType SubString(int starIndex, int count) const
		{
			if (IsNullOrEmpty()) return *this;

			auto length = (int)GetBufferLength();
			if (starIndex >= length) return TString(GetHeap());

			auto newBuffer = new(GetEngineHeap()) SharedStringBufferType(GetHeap(), count + 1);
			auto pDest = newBuffer->GetBufferPointer();
			//int bufferSize = (int)newBuffer->GetAllocatedSize();
			auto pSrc = m_Buffer->GetBufferPointer() + starIndex;

			// clip to the string boundary
			if ((starIndex + count) > (length + 1))
			{
				count -= (starIndex + count) - (length + 1);
			}

			memcpy(pDest, pSrc, count * sizeof(CharType));
			pDest[count] = {};

			return TString(GetHeap(), newBuffer);
		}


		// Format string
		template< class ...ArgTypes >
		StringType& Format(const CharType* strFormat, ArgTypes... args);
		//{
		//	VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		//	Format_Internal(strFormat, sizeof...(args), arguments);
		//	return *this;
		//}

		// Format string
		template< class ...ArgTypes >
		StringType& AppendFormat(const CharType* strFormat, ArgTypes... args);
		//{
		//	VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		//	AppendFormat_Internal(strFormat, sizeof...(args), arguments);
		//	return *this;
		//}

		CharType* data() { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }
		const CharType* data() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }
		operator const CharType*() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }

		bool operator == (const CharType* src) const
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

		bool operator != (const CharType* src) const
		{
			return !this->operator == (src);
		}


		StringType& operator = (const StringType& src)
		{
			m_Buffer = src.m_Buffer;
			if (m_Buffer != nullptr)
				m_StringValue = m_Buffer->GetBufferPointer();
			else
				m_StringValue = nullptr;

			return *this;
		}


	protected:

		size_t Format_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args)
		{
			CharType* szBuffer = nullptr;
			int buffLen = -1;
			size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
			m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), requiredSize);
			if (m_Buffer->GetAllocatedSize() >= requiredSize)
				return 0;

			szBuffer = m_Buffer->GetBufferPointer();
			buffLen = (int)requiredSize;
			auto length = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args);
			m_Buffer->Resize(length);

			m_StringValue = m_Buffer->GetBufferPointer();

			return length;
		}

		size_t AppendFormat_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args)
		{
			CharType* szBuffer = nullptr;
			int buffLen = -1;
			size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
			size_t currentStringLen = m_Buffer->GetStringLength();
			size_t totalSize = currentStringLen + requiredSize;
			if (m_Buffer->GetAllocatedSize() < totalSize)
				m_Buffer->Resize(totalSize);

			szBuffer = m_Buffer->GetBufferPointer() + currentStringLen;
			buffLen = (int)requiredSize;
			auto length = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args);
			m_Buffer->Resize(totalSize);

			m_StringValue = m_Buffer->GetBufferPointer();

			return length;
		}

	};


	extern template class TString<char>;
	extern template class TString<wchar_t>;


	using String = TString<char>;
	using StringW = TString<wchar_t>;



	class StringBuilder
	{
	public:

		using CharType = char;
		using StringType = TString<char>;
		using SharedStringBufferType = TSharedStringBuffer<CharType>;

	private:

		size_t m_GrowSize;

		// string buffer
		SharedPointerT<SharedStringBufferType> m_Buffer;

	public:

		StringBuilder(IHeap& heap, size_t growSize = 1024);

		IHeap& GetHeap() { return m_Buffer->GetHeap(); }

		// Append to string
		StringBuilder& Append(const StringType& src);
		StringBuilder& Append(const CharType* src);
		StringBuilder& Append(CharType src);

		StringBuilder& Append(int number);
		StringBuilder& Append(unsigned int number);
		StringBuilder& Append(float number);
		StringBuilder& Append(double number);


		// Format string
		template< class ...ArgTypes >
		StringBuilder& AppendFormat(const CharType* strFormat, ArgTypes... args);


		// Convert to string object
		TString<CharType> ToString();

	protected:

		size_t AppendFormat_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args);
	};





}; // namespace SF




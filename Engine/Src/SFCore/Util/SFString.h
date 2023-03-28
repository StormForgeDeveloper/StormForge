////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Util/SFStrUtil.h"
#include "Util/SFToStringBase.h"
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

		SF_FORCEINLINE IHeap& GetHeap() { return m_Heap; }

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
					newBuffer[0] = CharType{};
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

			m_StringLength = m_StringLength + StrUtil::StringLen(copyStart); // Make sure string has correct length
			return true;
		}

        void Reset()
        {
            if (m_StringValue)
            {
                m_StringValue[0] = 0;
            }
            m_StringLength = 0;
        }

		virtual void Dispose() override
		{
			IHeap::Free(m_StringValue);
			m_StringValue = nullptr;
		}

		SF_FORCEINLINE size_t GetStringLength() const { return m_StringLength; }
		SF_FORCEINLINE size_t GetStringBufferLength() const { return m_StringLength > 0 ? (m_StringLength + 1) * sizeof(CharType) : 0; }

		SF_FORCEINLINE CharType* GetBufferPointer() const { return m_StringValue; }
		SF_FORCEINLINE size_t GetAllocatedSize() const { return m_AllocatedSize; }
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

	private:

		// cached string value for debugging
		CharType* m_StringView = nullptr;

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
			m_StringView = m_Buffer->GetBufferPointer();
		}

		TString(const TString& src)
			: m_pHeap(src.m_pHeap)
			, m_Buffer(src.m_Buffer)
		{
			if (m_Buffer != nullptr)
				m_StringView = m_Buffer->GetBufferPointer();
		}

		TString(IHeap& heap)
			: m_pHeap(&heap)
		{
		}

		TString(IHeap& heap, const CharType* src)
			: m_pHeap(&heap)
		{
			m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), src);
			m_StringView = m_Buffer->GetBufferPointer();
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
				m_StringView = m_Buffer->GetBufferPointer();
			}
		}

		TString(IHeap& heap, const StringCrc64& src)
			: m_pHeap(&heap)
		{
			m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), src.ToString());
			m_StringView = m_Buffer->GetBufferPointer();
		}

		TString(IHeap& heap, const TString& src)
			: m_pHeap(&heap)
		{
			m_Buffer = src.m_Buffer;
			m_StringView = m_Buffer->GetBufferPointer();
		}

		TString(IHeap& heap, SharedPointerT<SharedStringBufferType>&& src)
			: m_pHeap(&heap)
		{
			m_Buffer = std::forward<SharedPointerT<SharedStringBufferType>>(src);
			m_StringView = m_Buffer->GetBufferPointer();
		}

		~TString() {}

		SF_FORCEINLINE IHeap& GetHeap() const { return *m_pHeap; }
		SF_FORCEINLINE void SetHeap(IHeap& heap) { m_pHeap = &heap; }

		// get string length
		SF_FORCEINLINE size_t GetBufferLength() const { return m_Buffer != nullptr ? m_Buffer->GetStringBufferLength() : 0; }
		SF_FORCEINLINE size_t GetLength() const { auto bufferLen = GetBufferLength();  return bufferLen > 0 ? bufferLen - 1 : 0; }
		SF_FORCEINLINE size_t size() const { return GetLength(); }
		SF_FORCEINLINE size_t length() const { return GetLength(); }

		SF_FORCEINLINE const CharType* GetDebugStringPtr() const { return m_StringView; }

		// Reserve buffer and set size. filled data will be garbage
		SF_FORCEINLINE void Resize(size_t newStrLen)
		{
			if (m_Buffer == nullptr)
				m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap());

			m_Buffer->Resize(newStrLen);
		}

		// Reserver buffer
		SF_FORCEINLINE void Reserve(size_t newStrLen)
		{
			if (m_Buffer == nullptr)
				m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), newStrLen);
			else
				m_Buffer->Reserve(newStrLen);
		}

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
			m_StringView = m_Buffer->GetBufferPointer();

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
				m_StringView = m_Buffer->GetBufferPointer();
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

			m_StringView = m_Buffer->GetBufferPointer();

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
				m_StringView = m_Buffer->GetBufferPointer();
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

			m_StringView = m_Buffer->GetBufferPointer();

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
			context.OutStream.pBuffer = temp;
			context.OutStream.BuffLen = sizeof(temp);
			_IToA(context, number);

			return Append(temp);
		}

		StringType& Append(unsigned int number)
		{
			char temp[128];
			ToStringContext context;
			context.OutStream.pBuffer = temp;
			context.OutStream.BuffLen = sizeof(temp);
			_IToA(context, number);

			return Append(temp);
		}

		StringType& Append(float number)
		{
			char temp[128];
			ToStringContext context;
			context.OutStream.pBuffer = temp;
			context.OutStream.BuffLen = sizeof(temp);
			_FToA(context, number);

			return Append(temp);
		}

		StringType& Append(double number)
		{
			char temp[128];
			ToStringContext context;
			context.OutStream.pBuffer = temp;
			context.OutStream.BuffLen = sizeof(temp);
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

        StringType& ReplaceInline(CharType from, CharType to)
        {
            if (!m_Buffer.IsValid())
                return *this;

            if (!m_Buffer.IsUnique())
            {
                auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + 1);
                newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringLength());

                m_Buffer = newBuffer;
            }

            auto pCur = m_Buffer->GetBufferPointer();
            int iIndex = StrUtil::Indexof(pCur, from);
            while(iIndex >= 0)
            {
                pCur[iIndex] = to;
                pCur = pCur + 1;
                iIndex = StrUtil::Indexof(pCur, from);
            }

            return *this;
        }

		// Check heading string
		bool StartsWith(const StringType& op, bool ignoreCase = false) const
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

		bool StartsWith(const CharType* op, bool ignoreCase = false) const
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

		bool StartsWith(CharType op, bool ignoreCase = false) const
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

			auto compareStart = m_Buffer->GetBufferPointer() + GetLength() - opLen;

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

			auto compareStart = m_Buffer->GetBufferPointer() + GetLength() - opLen;

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

			auto compareStart = m_Buffer->GetBufferPointer() + GetLength() - 1;

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(compareStart, (int)1, (const CharType*)opStr, (int)1);
			else
				return StrUtil::StringCompair(compareStart, (int)1, (const CharType*)opStr, (int)1);
		}

		// Find the first index of searchChar.
		int IndexOf(CharType searchChar) const
		{
			if (IsNullOrEmpty()) return -1;

			auto len = GetLength();
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

			auto len = GetLength();
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

			auto len = GetLength();
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

			auto len = (int)GetLength() - strLen;
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

			auto len = (int)GetLength() - 1;
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

			auto len = (int)GetLength() - 1;
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

		static TString Join(IHeap& heap, const Array<const CharType*>& strings, const CharType* delimiter)
		{
			if (strings.size() == 0)
				return TString(GetEngineHeap());

			size_t totalSize = 0;
			auto delimiterSize = StrUtil::StringLen(delimiter);
			for (size_t iItem = 0; iItem < strings.size(); iItem++)
			{
				totalSize += StrUtil::StringLen(strings[iItem]);
			}

			auto newBuffer = new(heap) SharedStringBufferType(heap, totalSize + strings.size() * delimiterSize + 1);
			for (size_t iItem = 0; iItem < strings.size(); iItem++)
			{
				if (iItem != 0)
					newBuffer->Append(delimiter, delimiterSize);
				newBuffer->Append(strings[iItem], StrUtil::StringLen(strings[iItem]));
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

            if (iStart < len)
            {
                stringsOut.push_back(SubString((int)iStart, (int)(len - iStart)));
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

			auto len = (int)GetLength();
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

			auto len = (int)GetLength();
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

			auto len = (int)GetLength();
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
            if (count < 0)
            {
                assert(false);
                return TString(GetHeap());
            }

			auto length = (int)GetBufferLength();
			if (starIndex >= length) return TString(GetHeap());

			auto newBuffer = new(GetEngineHeap()) SharedStringBufferType(GetHeap(), count + 1);

			auto pSrc = m_Buffer->GetBufferPointer() + starIndex;

			newBuffer->Append(pSrc, count);

			return TString(GetHeap(), newBuffer);
		}


		// Format string
		template< class ...ArgTypes >
		StringType& Format(const CharType* strFormat, ArgTypes... args);

		// Format string
		template< class ...ArgTypes >
		StringType& AppendFormat(const CharType* strFormat, ArgTypes... args);

		SF_FORCEINLINE CharType* data() { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }
		SF_FORCEINLINE const CharType* data() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }
		SF_FORCEINLINE operator const CharType*() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }

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
            // if both are pointing same string buffer, we don't need to anything
            if (src.data() == data())
            {
                return *this;
            }

			m_Buffer = src.m_Buffer;
			m_StringView = m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr;

			return *this;
		}

        StringType& operator = (const CharType* src)
        {
            // if both are pointing same string buffer, we don't need to anything
            if (src == data())
            {
                return *this;
            }

            if (m_Buffer.IsValid() && m_Buffer.IsUnique())
            {
                m_Buffer->Reset();
            }
            else
            {
                m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), StrUtil::StringLen(src) + 1);
            }

            if (src)
            {
                m_Buffer->Append(src, StrUtil::StringLen(src));
            }
            m_StringView = m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr;

            return *this;
        }



	protected:

		size_t Format_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args)
		{
			CharType* szBuffer = nullptr;
			int buffLen = -1;
			size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
			m_Buffer = new(GetHeap()) SharedStringBufferType(GetHeap(), requiredSize);
			if (m_Buffer->GetAllocatedSize() < requiredSize)
			{
				m_StringView = m_Buffer->GetBufferPointer();
				return 0;
			}

			szBuffer = m_Buffer->GetBufferPointer();
			buffLen = (int)requiredSize;
			size_t usedBufferLength = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args);
			m_Buffer->Resize(usedBufferLength > 0 ? usedBufferLength - 1 : 0);

			m_StringView = m_Buffer->GetBufferPointer();

			return usedBufferLength;
		}

		size_t AppendFormat_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args)
		{
			CharType* szBuffer = nullptr;
			int buffLen = -1;
			size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
			if (requiredSize == 0)
				return 0;

			size_t currentStringLen = m_Buffer->GetStringLength();
			size_t newTotalSize = currentStringLen + requiredSize + 1;

			if (m_Buffer.IsUnique())
			{
				if (m_Buffer->GetAllocatedSize() < newTotalSize)
					m_Buffer->Resize(newTotalSize);
			}
			else
			{
				auto newBuffer = new(GetHeap()) SharedStringBufferType(GetHeap(), newTotalSize);
				newBuffer->Append(m_Buffer->GetBufferPointer(), currentStringLen);
				m_Buffer = newBuffer;
			}

			szBuffer = m_Buffer->GetBufferPointer() + currentStringLen;
			buffLen = (int)requiredSize;
			StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args);
			size_t addedSize = StrUtil::StringLen(m_Buffer->GetBufferPointer() + currentStringLen);
			m_Buffer->Resize(currentStringLen + addedSize);

			m_StringView = m_Buffer->GetBufferPointer();

			return addedSize;
		}

	};


	extern template class TString<char>;
	extern template class TString<wchar_t>;


	using String = TString<char>;
	using WString = TString<wchar_t>;


	extern const String String_Empty;
	extern const String String_True;
	extern const String String_False;
	extern const String String_Success;
	extern const String String_Fail;

	extern const WString WString_Empty;
	extern const WString WString_True;
	extern const WString WString_False;
	extern const WString WString_Success;
	extern const WString WString_Fail;



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

		void Reset();

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


	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Utility classes
	//

	class CStringArrayView : public DynamicArray<const char*>
	{
	public:
		using DataType = const char*;

	public:

		CStringArrayView() = default;
		CStringArrayView(const Array<String>& src)
		{
			for (auto& itItem : src)
			{
				push_back(itItem.data());
			}
		}

		virtual ~CStringArrayView() = default;

		// copy operator
		CStringArrayView& operator = (const Array<const char*>& src) { CopyFrom(src); return *this; }
		CStringArrayView& operator = (const Array<String>& src)
		{
			Clear();
			for (auto& itItem : src)
			{
				push_back(itItem.data());
			}
			return *this;
		}
	};

} // namespace SF




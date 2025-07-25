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

#ifndef SF_USE_STD_STRING
#define SF_USE_STD_STRING 1
#endif


namespace SF {

#if SF_USE_STD_STRING


    ////////////////////////////////////////////////////////////////////////////////
    //
    //	SFString
    //     - We are just extending founctionality. don't use virtual and other expensive stuffs
    //

    template<typename CharType>
    class TString : public std::basic_string<CharType, std::char_traits<CharType>, std::allocator<CharType>>
    {
    public:

        using super = std::basic_string<CharType, std::char_traits<CharType>, std::allocator<CharType>>;
        using Allocator = std::allocator<CharType>;
        using StringType = TString<CharType>;

    public:
        TString() = default;
        TString(const CharType* src, const Allocator& alloc = Allocator())
            // Passing null to std::basic_string is a crash. passing Empty string when it is null
            : super(src ? std::basic_string_view<CharType>(src) : TCharCode<CharType>::Empty) 
        {
        }

        TString(const TString& src, const Allocator& alloc = Allocator())
            : super(src)
        {
        }

        TString(TString&& src, const Allocator& alloc = Allocator())
            : super(std::move(src))
        {
        }

        TString(std::basic_string<CharType>&& src, const Allocator& alloc = Allocator())
            : super(std::move(src))
        {
        }

        TString(const Array<const CharType>& src, const Allocator& alloc = Allocator())
        {
            Append(src);
        }

        TString(const CharType* src, int startIndex, int size = -1, const Allocator& alloc = Allocator())
            : super(src+startIndex, size < 0 ? StrUtil::StringLen(src + startIndex) : size)
        {
        }

        ~TString() = default;

        void Reset()
        {
            super::clear();
        }

        SF_FORCEINLINE size_t GetLength() const
        {
            return super::length();
        }
        SF_FORCEINLINE size_t size() const { return GetLength(); }
        //SF_FORCEINLINE size_t length() const { return GetLength(); }

        SF_FORCEINLINE void Resize(size_t newStrLen)
        {
            super::resize(newStrLen);
        }

        // Reserver buffer
        SF_FORCEINLINE void Reserve(size_t newCapacity)
        {
            super::reserve(newCapacity);
        }

        // Check whether it's null or empty string
        bool IsNullOrEmpty() const { return super::length() == 0; }

        StringType& Append(const Array<const CharType>& src)
        {
            super::append(src.data(), src.size());

            return *this;
        }

        // Append to string
        StringType& Append(const StringType& src)
        {
            super::append(src);

            return *this;
        }

        StringType& Append(const CharType* src)
        {
            super::append(src);

            return *this;
        }

        StringType& Append(CharType src)
        {
            super::append(1, src);
            return *this;
        }


        StringType& Append(int number)
        {
            return Append(std::format(TCharCode<CharType>::DefaultFormat, number).c_str());
        }

        StringType& Append(unsigned int number)
        {
            return Append(std::format(TCharCode<CharType>::DefaultFormat, number).c_str());
        }

        StringType& Append(float number)
        {
            return Append(std::format(TCharCode<CharType>::DefaultFormat, number).c_str());
        }

        StringType& Append(double number)
        {
            return Append(std::format(TCharCode<CharType>::DefaultFormat, number).c_str());
        }

        // combine string
        StringType operator + (const StringType& op2) const
        {
            return StringType(*this).Append(op2);
        }

        StringType& ReplaceInline(CharType from, CharType to)
        {
            size_t pos = super::find(from);
            while (pos != std::string::npos)
            {
                // Replace the substring
                super::replace(pos, 1, 1, to);
                pos = super::find(from, pos + 1);
            }

            return *this;
        }

        StringType& ReplaceInline(const CharType* from, const CharType* to)
        {
            size_t fromLength = StrUtil::StringLen(from);
            size_t toLength = StrUtil::StringLen(to);
            size_t pos = super::find(from);
            while (pos != std::string::npos)
            {
                // Replace the substring
                super::replace(pos, fromLength, to);
                pos = super::find(from, pos + toLength);
            }

            return *this;
        }

        // Check heading string
        bool StartsWith(const StringType& op) const
        {
            return super::starts_with(static_cast<const std::basic_string<CharType>&>(op));
        }

        bool StartsWith(const CharType* op) const
        {
            return super::starts_with(std::basic_string_view(op));
        }

        bool StartsWith(CharType op) const
        {
            return super::starts_with(op);
        }

        // Check tailing string
        bool EndsWith(const StringType& op) const
        {
            return super::ends_with(static_cast<const std::basic_string<CharType>&>(op));
        }

        bool EndsWith(const CharType* op) const
        {
            return super::ends_with(op);
        }

        bool EndsWith(CharType op) const
        {
            return super::ends_with(op);
        }

        // Find the first index of searchChar.
        int IndexOf(CharType searchChar) const
        {
            return static_cast<int>(super::find(searchChar));
        }

        // Find the first index of searchString in the string
        int IndexOf(const CharType* searchString) const
        {
            return static_cast<int>(super::find(searchString));
        }

        // Find the first index of any character in searchChars. The last element of the searchChars should be null
        int IndexOfAny(const CharType* searchChars) const
        {
            return static_cast<int>(super::find_first_of(searchChars));
        }

        // search from end
        int IndexOfFromEnd(const CharType* searchString) const
        {
            return static_cast<int>(super::rfind(searchString));

        }

        int IndexOfFromEnd(CharType searchChar) const
        {
            return static_cast<int>(super::rfind(searchChar));
        }

        // Join string array
        static TString Join(const Array<StringType>& strings, const CharType* delimiter)
        {
            std::basic_stringstream<CharType> ss;

            bool bFirst = true;
            for (auto& str : strings)
            {
                if (bFirst)
                {
                    bFirst = false;
                }
                else
                {
                    ss << delimiter;
                }
                ss << str;
            }

            return TString(ss.str());
        }

        // Split string into array with delimiter string 
        bool Split(const CharType delimiter, Array<TString>& stringsOut) const
        {
            std::basic_stringstream<CharType> ss(*this);

            // Temporary object to store 
            // the splitted string
            std::basic_string<CharType> t;

            // Splitting the str string 
            // by delimiter
            while (std::getline(ss, t, delimiter))
                stringsOut.push_back(std::move(t));

            return true;
        }

        // TString case conversion.
        StringType ToUpper() const
        {
            StringType temp;
            temp.reserve(super::length());

            std::transform(super::begin(), super::end(), temp.begin(), StrUtil::ToUpper<CharType>);

            return temp;
        }

        StringType& ToUpperInline()
        {
            if (IsNullOrEmpty()) return *this;

            StrUtil::StringUpperInline(data(), static_cast<int>(super::length()));

            return *this;
        }

        StringType ToLower() const
        {
            StringType temp = *this;

            std::transform(super::begin(), super::end(), temp.begin(), StrUtil::ToLower<CharType>);

            return temp;
        }

        StringType& ToLowerInline()
        {
            if (IsNullOrEmpty()) return *this;

            StrUtil::StringLowerInline(data(), static_cast<int>(super::length()));

            return *this;
        }


        bool Equals(const StringType& op, bool ignoreCase = false) const
        {
            if (ignoreCase)
                return StrUtil::StringCompairIgnoreCase((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)op.GetLength());
            else
                return StrUtil::StringCompair((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)op.GetLength());
        }

        bool Equals(const CharType* op, bool ignoreCase = false) const
        {
            auto opLen = op != nullptr ? StrUtil::StringLen(op) : 0;
            if (ignoreCase)
                return StrUtil::StringCompairIgnoreCase((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)opLen);
            else
                return StrUtil::StringCompair((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)opLen);
        }

        bool EqualsIgnoreCase(const StringType& op) const
        {
            return Equals(op, true);
        }
        bool EqualsIgnoreCase(const CharType* op) const
        {
            return Equals(op, true);
        }

        // Removes all leading and trailing white-space characters from the current TString object.
        StringType Trim() const
        {
            return TrimStart(TCharCode<CharType>::WhiteSpaces.data()).TrimEnd(TCharCode<CharType>::WhiteSpaces.data());
        }

        StringType TrimStart(const CharType* chars) const
        {
            size_t start = super::find_first_not_of(chars);
            return StringType((start == std::string::npos) ? std::basic_string<CharType>() : super::substr(start));
        }

        StringType TrimEnd(const CharType* chars) const
        {
            size_t end = super::find_last_not_of(chars);
            return (end == std::string::npos) ? std::basic_string<CharType>() : super::substr(0, end + 1);
        }

        // Make a copy of sub string
        StringType SubString(int starIndex, int count = -1) const
        {
            return super::substr(starIndex, count);
        }

        // Format string
        template<class ...ArgTypes>
        StringType& Format(const std::basic_string_view<CharType>& strFormat, ArgTypes... args)
        {
            super::clear();

            if constexpr (std::is_same_v<CharType, char>)
            {
                *this = std::move(std::vformat(strFormat, std::make_format_args(args...)));
            }
            else
            {
                *this = std::move(std::vformat(strFormat, std::make_format_args<std::wformat_context>(args...)));
            }

            return *this;
        }

        // Format string
        template< class ...ArgTypes>
        StringType& AppendFormat(const std::basic_string_view<CharType>& strFormat, ArgTypes... args)
        {
            if constexpr (std::is_same_v<CharType, char>)
            {
                super::append(std::move(std::vformat(strFormat, std::make_format_args(args...))));
            }
            else
            {
                super::append(std::move(std::vformat(strFormat, std::make_format_args<std::wformat_context>(args...))));
            }
            return *this;
        }

        SF_FORCEINLINE CharType* data() { return super::data(); }
        SF_FORCEINLINE const CharType* data() const { return super::data(); }
        SF_FORCEINLINE operator const CharType* () const { return super::c_str(); }
        SF_FORCEINLINE const CharType* c_str() const { return super::c_str(); }

        //bool operator == (const CharType* src) const
        //{
        //    return super::compare(src) == 0;
        //}

        //bool operator != (const CharType* src) const
        //{
        //    return super::compare(src) != 0;
        //}

        StringType& operator = (const StringType& src)
        {
            super::operator=(src);

            return *this;
        }

        StringType& operator = (const CharType* src)
        {
            super::operator=(src ? std::basic_string_view<CharType>(src) : TCharCode<CharType>::Empty);

            return *this;
        }

        StringType& operator = (const Array<const CharType>& src)
        {
            Reset();
            return Append(src);
        }
    };

#else // SF_USE_STD_STRING

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
			size_t newAllocationSize = (newStrLen + 1) * sizeof(CharType);
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

			size_t newStringLength = m_StringLength + strLen;
			size_t newAllocationSize = (newStringLength + 1) * sizeof(CharType);
			if (newAllocationSize > m_AllocatedSize)
			{
				if (!Reserve(newStringLength))
					return false;
			}

			// copy string data and update string length
			CharType* copyStart = m_StringValue + GetStringLength();
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
		SF_FORCEINLINE size_t GetStringBufferLength() const
        {
            return m_StringLength > 0 ? (m_StringLength + 1) * sizeof(CharType) : 0;
        }

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
			m_Buffer = new SharedStringBufferType(GetHeap(), src);
			m_StringView = m_Buffer->GetBufferPointer();
		}

		TString(const TString& src)
			: m_pHeap(src.m_pHeap)
			, m_Buffer(src.m_Buffer)
		{
			if (m_Buffer != nullptr)
				m_StringView = m_Buffer->GetBufferPointer();
		}

        TString(const Array<const CharType>& src)
            : m_pHeap(&GetSystemHeap())
        {
            Append(src);
        }

		TString(IHeap& heap)
			: m_pHeap(&heap)
		{
		}

		TString(IHeap& heap, const CharType* src)
			: m_pHeap(&heap)
		{
			m_Buffer = new SharedStringBufferType(GetHeap(), src);
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

				m_Buffer = new SharedStringBufferType(GetHeap(), size + 1);
				m_Buffer->Append(src + startIndex, size);
				m_StringView = m_Buffer->GetBufferPointer();
			}
		}

		TString(IHeap& heap, const StringCrc64& src)
			: m_pHeap(&heap)
		{
			m_Buffer = new SharedStringBufferType(GetHeap(), src.ToString());
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

        void Reset()
        {
            if (m_Buffer != nullptr && m_Buffer->IsUniquelyReferenced())
            {
                m_Buffer->Reset();
            }
            else
            {
                m_Buffer = nullptr;
            }
            m_StringView = nullptr;
        }

		SF_FORCEINLINE IHeap& GetHeap() const { return *m_pHeap; }
		SF_FORCEINLINE void SetHeap(IHeap& heap) { m_pHeap = &heap; }

		// get string length
		SF_FORCEINLINE size_t GetBufferLength() const
        {
            return m_Buffer != nullptr ? m_Buffer->GetStringBufferLength() : 0;
        }
        SF_FORCEINLINE size_t GetLength() const
        {
            return m_Buffer != nullptr ? m_Buffer->GetStringLength() : 0;
        }
		SF_FORCEINLINE size_t size() const { return GetLength(); }
		SF_FORCEINLINE size_t length() const { return GetLength(); }

		SF_FORCEINLINE const CharType* GetDebugStringPtr() const { return m_StringView; }

		// Reserve buffer and set size. filled data will be garbage
		SF_FORCEINLINE void Resize(size_t newStrLen)
		{
			if (m_Buffer == nullptr)
				m_Buffer = new SharedStringBufferType(GetHeap());

			m_Buffer->Resize(newStrLen);
		}

		// Reserver buffer
		SF_FORCEINLINE void Reserve(size_t newStrLen)
		{
			if (m_Buffer == nullptr)
				m_Buffer = new SharedStringBufferType(GetHeap(), newStrLen);
			else
				m_Buffer->Reserve(newStrLen);
		}

		// Check whether it's null or empty string
		bool IsNullOrEmpty() const { return m_Buffer == nullptr || m_Buffer->GetStringLength() == 0; }

        StringType& Append(const Array<const CharType>& src)
        {
            auto pSrc = (const CharType*)src.data();

            if (m_Buffer != nullptr)
            {
                if (m_Buffer->IsUniquelyReferenced())
                {
                    m_Buffer->Append(src.data(), src.size());
                }
                else
                {
                    SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + src.size() + 1);
                    newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringLength());
                    newBuffer->Append(pSrc, src.size());

                    m_Buffer = newBuffer;
                }
            }
            else
            {
                SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), src.size() + 1);
                newBuffer->Append(pSrc, src.size());

                m_Buffer = newBuffer;
            }
            m_StringView = m_Buffer->GetBufferPointer();

            return *this;
        }

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
			size_t addLen = src.GetBufferLength();
			unused(pStr, addLen);
			assert(pStr != nullptr && addLen > 0);


			if (m_Buffer->IsUniquelyReferenced())
			{
				m_Buffer->Append(src.m_Buffer->GetBufferPointer(), src.m_Buffer->GetStringLength());
			}
			else
			{
                SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + src.m_Buffer->GetStringLength() + 1);
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

			size_t addLen = StrUtil::StringLen(src);
			if (IsNullOrEmpty())
			{
                SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), addLen + 1);
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
                SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + addLen + 1);
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

			size_t addLen = StrUtil::StringLen(src);
			if (IsNullOrEmpty())
			{
				auto newBuffer = new SharedStringBufferType(GetHeap(), addLen + 1);
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
				auto newBuffer = new SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + addLen + 1);
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

            const CharType* pStr = (const CharType*)op2;
			size_t addLen = op2.GetBufferLength();
			unused(pStr, addLen);
			assert(pStr != nullptr && addLen > 0);

            SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + op2.m_Buffer->GetStringLength() + 1);
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
                SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), m_Buffer->GetStringLength() + 1);
                newBuffer->Append(m_Buffer->GetBufferPointer(), m_Buffer->GetStringLength());

                m_Buffer = newBuffer;
                m_StringView = m_Buffer->GetBufferPointer();
            }

            CharType* pCur = m_Buffer->GetBufferPointer();
            int iIndex = StrUtil::Indexof(pCur, from);
            while(iIndex >= 0)
            {
                pCur += iIndex;
                *pCur++ = to;
                iIndex = StrUtil::Indexof(pCur, from);
            }

            return *this;
        }

        StringType& ReplaceInline(const CharType* from, const CharType* to)
        {
            if (!m_Buffer.IsValid())
                return *this;

            if (StrUtil::IsNullOrEmpty(from) || to == nullptr)
                return *this;

            size_t toLen = StrUtil::StringLen(to);

            // just rough guess
            size_t expectedBufferSize = (m_Buffer->GetStringLength() + toLen) * 2;

            SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), expectedBufferSize);

            CharType* pCur = m_Buffer->GetBufferPointer();
            int iIndex = StrUtil::Indexof(pCur, from[0]);
            size_t fromLen = StrUtil::StringLen(from);
            while (iIndex >= 0)
            {
                newBuffer->Append(pCur, iIndex);
                pCur += iIndex;
                if (StrUtil::StringCompair(pCur, from, static_cast<int>(fromLen)))
                {
                    newBuffer->Append(to, toLen);
                    pCur += fromLen;
                }
                else
                {
                    newBuffer->Append(pCur, 1);
                    pCur++;
                }
                iIndex = StrUtil::Indexof(pCur, from[0]);
            }
            // Append remain string
            newBuffer->Append(pCur, StrUtil::StringLen(pCur));

            m_Buffer = newBuffer;
            m_StringView = m_Buffer->GetBufferPointer();

            return *this;
        }

		// Check heading string
		bool StartsWith(const StringType& op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (op.IsNullOrEmpty()) return false;
			size_t opLen = op.GetBufferLength();
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
			size_t opLen = op.GetBufferLength();
			if (opLen > GetBufferLength()) return false;

            CharType* compareStart = m_Buffer->GetBufferPointer() + GetLength() - opLen;

			if (ignoreCase)
				return StrUtil::StringCompairIgnoreCase(compareStart, (int)opLen, (const CharType*)op, (int)opLen);
			else
				return StrUtil::StringCompair(compareStart, (int)opLen, (const CharType*)op, (int)opLen);
		}

		bool EndsWith(const CharType* op, bool ignoreCase = false) const
		{
			if (IsNullOrEmpty()) return false;
			if (StrUtil::IsNullOrEmpty(op)) return false;

			size_t opLen = StrUtil::StringLen(op);
			if (opLen > GetBufferLength()) return false;

			CharType* compareStart = m_Buffer->GetBufferPointer() + GetLength() - opLen;

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

			size_t len = GetLength();
            CharType* pCur = m_Buffer->GetBufferPointer();
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

			size_t strLen = StrUtil::StringLen(searchString);

            size_t len = GetLength();
            CharType* pCur = m_Buffer->GetBufferPointer();

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

            size_t numChar = StrUtil::StringLen(searchChars);

            size_t len = GetLength();
            CharType* pCur = m_Buffer->GetBufferPointer();

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

            size_t strLen = (int)StrUtil::StringLen(searchString);

            size_t len = (int)GetLength() - strLen;
            CharType* pCur = m_Buffer->GetBufferPointer() + len;

			if (ignoreCase)
			{
				for (int iOffset = static_cast<int>(len); iOffset >= 0; iOffset--, pCur--)
				{
					if (StrUtil::StringCompairIgnoreCase(pCur, static_cast<int>(strLen), searchString, static_cast<int>(strLen))) return iOffset;
				}
			}
			else
			{
				for (int iOffset = static_cast<int>(len); iOffset >= 0; iOffset--, pCur--)
				{
					if (StrUtil::StringCompair(pCur, static_cast<int>(strLen), searchString, static_cast<int>(strLen))) return iOffset;
				}
			}

			return -1;
		}

		int IndexOfFromEnd(CharType searchChar) const
		{
			if (IsNullOrEmpty()) return -1;

            size_t len = (int)GetLength() - 1;
            CharType* pCur = m_Buffer->GetBufferPointer() + len;

			for (int iOffset = static_cast<int>(len); iOffset >= 0; iOffset--, pCur--)
			{
				if (*pCur == searchChar) return iOffset;
			}

			return -1;
		}

		int IndexOfAnyFromEnd(const CharType* searchChars) const
		{
			if (IsNullOrEmpty()) return -1;
			if (searchChars == nullptr) return -1;

            size_t numChar = StrUtil::StringLen(searchChars);

            size_t len = GetLength() - 1;
			CharType* pCur = m_Buffer->GetBufferPointer() + len;

			for (int iOffset = static_cast<int>(len); iOffset >= 0; iOffset--, pCur--)
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
            size_t delimiterSize = StrUtil::StringLen(delimiter);
			for (size_t iItem = 0; iItem < strings.size(); iItem++)
			{
				totalSize += strings[iItem].GetBufferLength();
			}

			IHeap& heap = strings[0].GetHeap();
            SharedStringBufferType* newBuffer = new SharedStringBufferType(heap, totalSize + strings.size() * delimiterSize + 1);
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
            size_t delimiterSize = StrUtil::StringLen(delimiter);
			for (size_t iItem = 0; iItem < strings.size(); iItem++)
			{
				totalSize += StrUtil::StringLen(strings[iItem]);
			}

            SharedStringBufferType* newBuffer = new(heap) SharedStringBufferType(heap, totalSize + strings.size() * delimiterSize + 1);
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

			size_t strLen = StrUtil::StringLen(delimiterString);

			size_t len = GetBufferLength();
			CharType* pCur = m_Buffer->GetBufferPointer();
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

            size_t numChar = StrUtil::StringLen(delimiterChars);

			size_t len = GetBufferLength();
			CharType* pCur = m_Buffer->GetBufferPointer();
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

		// TString case conversion.
		StringType ToUpper() const
		{
			if (IsNullOrEmpty()) return *this;

			auto newBuffer = new SharedStringBufferType(GetHeap(), GetBufferLength() + 1);
            CharType* bufferPointer = newBuffer->GetBufferPointer();
			int bufferSize = (int)newBuffer->GetAllocatedSize();
			StrUtil::StringUpper(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());

			return TString(GetHeap(), newBuffer);
		}

        StringType& ToUpperInline()
        {
            if (IsNullOrEmpty()) return *this;

            if (m_Buffer.IsUnique())
            {
                StrUtil::StringUpperInline(m_Buffer->GetBufferPointer(), static_cast<int>(m_Buffer->GetStringLength()));
            }
            else
            {
                SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), GetBufferLength() + 1);
                CharType* bufferPointer = newBuffer->GetBufferPointer();
                int bufferSize = (int)newBuffer->GetAllocatedSize();
                StrUtil::StringUpper(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());
                m_Buffer = newBuffer;

                m_StringView = m_Buffer->GetBufferPointer();
            }

            return *this;
        }

		StringType ToLower() const
		{
			if (IsNullOrEmpty()) return *this;

			auto newBuffer = new SharedStringBufferType(GetHeap(), GetBufferLength() + 1);
			auto bufferPointer = newBuffer->GetBufferPointer();
			int bufferSize = (int)newBuffer->GetAllocatedSize();
			StrUtil::StringLower(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());

			return TString(GetHeap(), newBuffer);
		}

        StringType& ToLowerInline()
        {
            if (IsNullOrEmpty()) return *this;

            if (m_Buffer.IsUnique())
            {
                StrUtil::StringLowerInline(m_Buffer->GetBufferPointer(), static_cast<int>(m_Buffer->GetStringLength()));
            }
            else
            {
                SharedStringBufferType* newBuffer = new SharedStringBufferType(GetHeap(), GetBufferLength() + 1);
                CharType* bufferPointer = newBuffer->GetBufferPointer();
                int bufferSize = (int)newBuffer->GetAllocatedSize();
                StrUtil::StringLower(bufferPointer, bufferSize, m_Buffer->GetBufferPointer());
                m_Buffer = newBuffer;

                m_StringView = m_Buffer->GetBufferPointer();
            }

            return *this;
        }


		bool Equals(const StringType& op, bool ignoreCase = false) const
		{
            if (ignoreCase)
    			return StrUtil::StringCompairIgnoreCase((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)op.GetLength());
            else
                return StrUtil::StringCompair((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)op.GetLength());
		}

		bool Equals(const CharType* op, bool ignoreCase = false) const
		{
			auto opLen = op != nullptr ? StrUtil::StringLen(op) : 0;
            if (ignoreCase)
			    return StrUtil::StringCompairIgnoreCase((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)opLen);
            else
                return StrUtil::StringCompair((const CharType*)*this, (int)GetLength(), (const CharType*)op, (int)opLen);
		}

        bool EqualsIgnoreCase(const StringType& op) const
        {
            return Equals(op,true);
        }
        bool EqualsIgnoreCase(const CharType* op) const
        {
            return Equals(op, true);
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

            StringType result = *this;
            result.TrimEndInline(chars);
            return result;
		}

        StringType TrimEndInline(const CharType* chars)
        {
            if (IsNullOrEmpty()) return *this;
            if (chars == nullptr) return *this;

            auto numChar = (int)StrUtil::StringLen(chars);

            auto len = (int)GetLength();
            auto strString = m_Buffer->GetBufferPointer();
            int iEnd = len - 1;

            for (; iEnd >= 0; iEnd--)
            {
                auto curChar = strString[iEnd];
                int iChar = 0;
                for (; iChar < numChar; iChar++)
                {
                    if (chars[iChar] == curChar) break;
                }

                if (iChar >= numChar) break;
            }

            if (iEnd < 0)
            {
                m_Buffer->Reset();
            }
            else
            {
                m_Buffer->Resize(iEnd + 1);
            }

            return *this;
        }


		// Make a copy of sub string
		StringType SubString(int starIndex, int count = -1) const
		{
			if (IsNullOrEmpty()) return *this;
            if (count <= 0)
            {
                count = int(length()) - starIndex;
                if (count <= 0)
                {
                    return TString(GetHeap());
                }
            }

			auto length = (int)GetBufferLength();
			if (starIndex >= length) return TString(GetHeap());

			auto newBuffer = new SharedStringBufferType(GetHeap(), count + 1);

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
        SF_FORCEINLINE const CharType* c_str() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }

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
            if (m_Buffer == nullptr && src == nullptr) return false;
            if (m_Buffer == nullptr || src == nullptr) return true;

            auto myBuffer = m_Buffer->GetBufferPointer();
            auto opBuffer = src;
            // Actually I want to check "myBuffer == nullptr && opBuffer == nullptr", but comparing both pointer will give me the result
            if (myBuffer == opBuffer) return false;
            if (myBuffer == nullptr) return true;

            return !StrUtil::StringCompair(myBuffer, (INT)m_Buffer->GetStringBufferLength(), opBuffer, -1);
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
                m_Buffer = new SharedStringBufferType(GetHeap(), StrUtil::StringLen(src) + 1);
            }

            if (src)
            {
                m_Buffer->Append(src, StrUtil::StringLen(src));
            }
            m_StringView = m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr;

            return *this;
        }

        StringType& operator = (const Array<const CharType>& src)
        {
            Reset();
            return Append(src);
        }

	protected:

		size_t Format_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args)
		{
			CharType* szBuffer = nullptr;
			int buffLen = -1;
			size_t requiredSize = StrUtil::Format_Internal(szBuffer, buffLen, szFormating, iNumArg, Args) + 1;
			m_Buffer = new SharedStringBufferType(GetHeap(), requiredSize);
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
				auto newBuffer = new SharedStringBufferType(GetHeap(), newTotalSize);
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



#endif // SF_USE_STD_STRING
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

    private:

        std::basic_stringstream<CharType> m_Stream;

    public:

        StringBuilder() = default;

        void Reset()
        {
            m_Stream.str("");
            m_Stream.clear();
        }

        // Append to string
        StringBuilder& Append(const StringType& src)
        {
            m_Stream << src;
            return *this;
        }

        StringBuilder& Append(const CharType* src)
        {
            m_Stream << src;
            return *this;
        }

        StringBuilder& Append(CharType src)
        {
            m_Stream << src;
            return *this;
        }


        StringBuilder& Append(int number)
        {
            m_Stream << number;
            return *this;
        }

        StringBuilder& Append(unsigned int number)
        {
            m_Stream << number;
            return *this;
        }

        StringBuilder& Append(float number)
        {
            m_Stream << number;
            return *this;
        }

        StringBuilder& Append(double number)
        {
            m_Stream << number;
            return *this;
        }

        // Format string
        template< class ...ArgTypes >
        StringBuilder& AppendFormat(const CharType* strFormat, ArgTypes... args)
        {
            m_Stream << std::vformat(std::string_view(strFormat), std::make_format_args(args...));
            return *this;
        }


        // Convert to string object
        TString<CharType> ToString() const
        {
            return TString<CharType>(std::move(m_Stream.str()));
        }
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


template <>
struct std::formatter<SF::String>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::String& value, FormatContext& ctx) const
    {
#if SF_USE_STD_STRING
        return std::format_to(ctx.out(), "{}", (std::string&)value);
#else
        return std::format_to(ctx.out(), "{}", value.c_str());
#endif
    }
};


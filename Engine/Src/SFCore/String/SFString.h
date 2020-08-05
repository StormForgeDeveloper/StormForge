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
#include "Container/SFArray.h"


namespace SF {

	class FixedString;
	class VariableBox;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	SharedStringBuffer
	//

	template<typename CharType>
	class SharedStringBuffer : public SharedObject
	{
	private:

		// string buffer
		CharType* m_StringValue = nullptr;

		// Heap
		IHeap& m_Heap;

		// actually allocated size in bytes
		size_t m_AllocatedSize = 0;

		// String length exclude null termination
		size_t m_StringLength = 0;

		//friend class String<CharType>;

	public:

		SharedStringBuffer(IHeap& heap);
		SharedStringBuffer(IHeap& heap, size_t initialCharCount);
		SharedStringBuffer(IHeap& heap, const CharType* src);
		~SharedStringBuffer();

		IHeap& GetHeap() { return m_Heap; }

		//  resize with string length
		bool Resize(size_t newStrLen);

		// append string
		bool Append(const CharType* src, size_t strLen);

		virtual void Dispose() override;

		size_t GetStringLength() const { return m_StringLength; }
		size_t GetStringBufferLength() const { return m_StringLength > 0 ? (m_StringLength + 1) * sizeof(CharType) : 0; }

		CharType* GetBufferPointer() const { return m_StringValue; }
		size_t GetAllocatedSize() const { return m_AllocatedSize; }
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	SharedStringBuffer
	//

	template<typename CharType>
	SharedStringBuffer<CharType>::SharedStringBuffer(IHeap& heap)
		: m_Heap(heap)
	{
	}

	template<typename CharType>
	SharedStringBuffer<CharType>::SharedStringBuffer(IHeap& heap, size_t initialCharCount)
		: m_Heap(heap)
	{
		Resize(initialCharCount);
	}

	template<typename CharType>
	SharedStringBuffer<CharType>::SharedStringBuffer(IHeap& heap, const CharType* src)
		: m_Heap(heap)
	{
		if (src != nullptr)
			Append(src, StrUtil::StringLen(src));
	}

	template<typename CharType>
	SharedStringBuffer<CharType>::~SharedStringBuffer()
	{
		m_Heap.Free(m_StringValue);
		m_StringValue = nullptr;
	}

	template<typename CharType>
	bool SharedStringBuffer<CharType>::Resize(size_t newStrLen)
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
		else
		{
			m_StringValue[newStrLen] = {};
		}
		m_StringLength = newStrLen;

		return true;
	}

	template<typename CharType>
	bool SharedStringBuffer<CharType>::Append(const CharType* src, size_t strLen)
	{
		if (src == nullptr) return false;

		auto newStringLength = std::max(m_StringLength, size_t(1)) + strLen;
		auto newAllocationSize = (newStringLength+1) * sizeof(CharType);
		if (newAllocationSize > m_AllocatedSize)
		{
			//auto newAllocationSize = extraBufferSize == 0 ? newAllocationSize : std::max(newAllocationSize, m_AllocatedSize) + extraBufferSize;
			if (!Resize(newAllocationSize))
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

	template<typename CharType>
	void SharedStringBuffer<CharType>::Dispose()
	{
		IHeap::Free(m_StringValue);
		m_StringValue = nullptr;
	}




	////////////////////////////////////////////////////////////////////////////////
	//
	//	SFString
	//     - Shared string buffer system like C# string
	//

	class String
	{
	public:

		static const String Empty;
		static const String True;
		static const String False;
		static const String Success;
		static const String Fail;

		using CharType = char;
		using SharedStringBufferType = SharedStringBuffer<CharType>;

	private:

		// cached string value for debugging
		CharType* m_StringValue = nullptr;

		// Heap for string operation
		IHeap* m_pHeap = nullptr;

		// string buffer
		SharedPointerT<SharedStringBufferType> m_Buffer;

	public:
		String();
		String(const CharType* src);
		String(const String& src);
		String(IHeap& heap);
		String(IHeap& heap, const CharType* src);
		String(IHeap& heap, const CharType* src, int startIndex, int size = -1);
		String(IHeap& heap, const FixedString& src);
		String(IHeap& heap, const String& src);
		String(IHeap& heap, SharedStringBufferType& src);
		~String();

		IHeap& GetHeap() const { return *m_pHeap; }
		void SetHeap(IHeap& heap) { m_pHeap = &heap; }

		// get string length
		size_t GetBufferLength() const { return m_Buffer != nullptr ? m_Buffer->GetStringBufferLength() : 0; }
		size_t GetLength() const { auto bufferLen = GetBufferLength();  return bufferLen > 0 ? bufferLen - 1 : 0; }
		size_t size() const { return GetLength(); }
		size_t length() const { return GetLength(); }
		// Check whether it's null or empty string
		bool IsNullOrEmpty() const { return m_Buffer == nullptr || m_Buffer->GetStringLength() == 0; }

		// Append to string
		String& Append(const String& src);
		String& Append(const CharType* src);
		String& Append(CharType src);

		String& Append(int number);
		String& Append(unsigned int number);
		String& Append(float number);
		String& Append(double number);

		// combine string
		String operator + (const String& op2) const;

		// Check heading string
		bool StartWith(const String& op, bool ignoreCase = false) const;
		bool StartWith(const CharType* op, bool ignoreCase = false) const;
		bool StartWith(CharType op, bool ignoreCase = false) const;
		// Check tailing string
		bool EndsWith(const String& op, bool ignoreCase = false) const;
		bool EndsWith(const CharType* op, bool ignoreCase = false) const;
		bool EndsWith(char op, bool ignoreCase = false) const;

		// Find the first index of searchString in the string
		int IndexOf(const CharType* searchString, bool ignoreCase = false) const;
		// Find the first index of searchChar.
		int IndexOf(CharType searchChar) const;
		// Find the first index of any character in searchChars. The last element of the searchChars should be null
		int IndexOfAny(const CharType* searchChars) const;

		// search from end
		int IndexOfFromEnd(const CharType* searchString, bool ignoreCase = false) const;
		int IndexOfFromEnd(CharType searchChar) const;
		int IndexOfAnyFromEnd(const CharType* searchChars) const;

		// Join string array
		static String Join(const Array<String>& strings, const CharType* delimiter);
		// Split string into array with delimiter string 
		bool Split(const CharType* delimiterString, bool ignoreCase, Array<String>& stringsOut) const;
		// Split string into array with delimiter characters. The last element of the delimiterChars should be null
		bool SplitAny(const CharType* delimiterChars, Array<String>& stringsOut) const;

		// In-place string case conversion
		String& ConvertToUpper();
		String& ConvertToLower();

		// String case conversion.
		String ToUpper() const;
		String ToLower() const;

		bool IsEqual(const String& op) const;
		bool IsEqual(const CharType* op) const;

		bool IsEqualIgnoreCase(const String& op) const;
		bool IsEqualIgnoreCase(const CharType* op) const;

		// Removes all leading and trailing white-space characters from the current String object.
		String Trim() const;

		// Removes all leading and trailing characters in the list from the current String object.
		String TrimAny(const CharType* chars) const;
		String TrimStart(const CharType* chars) const;
		String TrimEnd(const CharType* chars) const;

		// Make a copy of sub string
		String SubString(int starIndex, int count) const;

		// Format string
		template< class ...ArgTypes >
		inline String& Format(const CharType* strFormat, ArgTypes... args);

		// Format string
		template< class ...ArgTypes >
		inline String& AppendFormat(const CharType* strFormat, ArgTypes... args);

		const CharType* data() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }
		operator const CharType*() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }

		bool operator == (const CharType* src) const;
		bool operator != (const CharType* src) const;

		String& operator = (const CharType* src);
		String& operator = (const String& src);

	protected:

		size_t Format_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args);
		size_t AppendFormat_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args);
	};




	class StringBuilder
	{
	public:

		using CharType = char;
		using SharedStringBufferType = SharedStringBuffer<CharType>;

	private:

		size_t m_GrowSize;

		// string buffer
		SharedPointerT<SharedStringBufferType> m_Buffer;

	public:

		StringBuilder(IHeap& heap, size_t growSize = 1024);

		IHeap& GetHeap() { return m_Buffer->GetHeap(); }

		// Append to string
		StringBuilder& Append(const String& src);
		StringBuilder& Append(const CharType* src);
		StringBuilder& Append(CharType src);

		StringBuilder& Append(int number);
		StringBuilder& Append(unsigned int number);
		StringBuilder& Append(float number);
		StringBuilder& Append(double number);


		// Format string
		template< class ...ArgTypes >
		inline StringBuilder& AppendFormat(const CharType* strFormat, ArgTypes... args);


		// Convert to string object
		String ToString();

	protected:

		size_t AppendFormat_Internal(const CharType* szFormating, int iNumArg, VariableBox* Args);
	};


}; // namespace SF




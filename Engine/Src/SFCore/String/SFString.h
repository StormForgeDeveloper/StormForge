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

	class SharedStringBuffer : public SharedObject
	{
	private:

		// string buffer
		char* m_StringValue = nullptr;

		// Heap
		IHeap& m_Heap;

		// actually allocated size
		size_t m_AllocatedSize = 0;

		// String length include null termination
		size_t m_StringBufferLength = 0;

		friend class String;

	public:

		SharedStringBuffer(IHeap& heap);
		SharedStringBuffer(IHeap& heap, size_t initialBufferSize);
		SharedStringBuffer(IHeap& heap, const char* src);
		~SharedStringBuffer();

		IHeap& GetHeap() { return m_Heap; }

		bool Resize(size_t newAllocationSize);

		bool Append(const char* src, size_t strLen, size_t extraBufferSize = 0);

		virtual void Dispose() override;

		size_t GetStringLength() const { return m_StringBufferLength > 0 ? m_StringBufferLength - 1 : 0; }
		size_t GetStringBufferLength() const { return m_StringBufferLength; }
		// set string length, this will not check actual string length
		void SetStringBufferLength(size_t newStringLength);

		char* GetBufferPointer() const { return m_StringValue; }
		size_t GetAllocatedSize() const { return m_AllocatedSize; }
	};



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

	private:

		// cached string value for debugging
		char* m_StringValue = nullptr;

		// Heap for string operation
		IHeap* m_pHeap = nullptr;

		// string buffer
		SharedPointerT<SharedStringBuffer> m_Buffer;

	public:
		String();
		String(const char* src);
		String(const String& src);
		String(IHeap& heap);
		String(IHeap& heap, const char* src);
		String(IHeap& heap, const char* src, int startIndex, int size = -1);
		String(IHeap& heap, const FixedString& src);
		String(IHeap& heap, const String& src);
		String(IHeap& heap, SharedStringBuffer& src);
		~String();

		IHeap& GetHeap() const { return *m_pHeap; }
		void SetHeap(IHeap& heap) { m_pHeap = &heap; }

		// get string length
		size_t GetBufferLength() const { return m_Buffer != nullptr ? m_Buffer->GetStringBufferLength() : 0; }
		size_t GetLength() const { auto bufferLen = GetBufferLength();  return bufferLen > 0 ? bufferLen - 1 : 0; }
		size_t size() const { return GetLength(); }
		size_t length() const { return GetLength(); }
		// Check whether it's null or empty string
		bool IsNullOrEmpty() const { return m_Buffer == nullptr || m_Buffer->GetStringBufferLength() <= 1; }

		// Append to string
		String& Append(const String& src);
		String& Append(const char* src);
		String& Append(char src);

		String& Append(int number);
		String& Append(unsigned int number);
		String& Append(float number);
		String& Append(double number);

		// combine string
		String operator + (const String& op2) const;

		// Check heading string
		bool StartWith(const String& op, bool ignoreCase = false) const;
		bool StartWith(const char* op, bool ignoreCase = false) const;
		bool StartWith(char op, bool ignoreCase = false) const;
		// Check tailing string
		bool EndsWith(const String& op, bool ignoreCase = false) const;
		bool EndsWith(const char* op, bool ignoreCase = false) const;
		bool EndsWith(char op, bool ignoreCase = false) const;

		// Find the first index of searchString in the string
		int IndexOf(const char* searchString, bool ignoreCase = false) const;
		// Find the first index of searchChar.
		int IndexOf(char searchChar) const;
		// Find the first index of any character in searchChars. The last element of the searchChars should be null
		int IndexOfAny(const char* searchChars) const;

		// search from end
		int IndexOfFromEnd(const char* searchString, bool ignoreCase = false) const;
		int IndexOfFromEnd(char searchChar) const;
		int IndexOfAnyFromEnd(const char* searchChars) const;

		// Join string array
		static String Join(const Array<String>& strings, const char* delimiter);
		// Split string into array with delimiter string 
		bool Split(const char* delimiterString, bool ignoreCase, Array<String>& stringsOut) const;
		// Split string into array with delimiter characters. The last element of the delimiterChars should be null
		bool SplitAny(const char* delimiterChars, Array<String>& stringsOut) const;

		// In-place string case conversion
		String& ConvertToUpper();
		String& ConvertToLower();

		// String case convertion.
		String ToUpper() const;
		String ToLower() const;

		bool IsEqual(const String& op) const;
		bool IsEqual(const char* op) const;

		bool IsEqualIgnoreCase(const String& op) const;
		bool IsEqualIgnoreCase(const char* op) const;

		// Removes all leading and trailing white-space characters from the current String object.
		String Trim() const;

		// Removes all leading and trailing characters in the list from the current String object.
		String TrimAny(const char* chars) const;
		String TrimStart(const char* chars) const;
		String TrimEnd(const char* chars) const;

		// Make a copy of sub string
		String SubString(int starIndex, int count) const;

		// Format string
		template< class ...ArgTypes >
		inline String& Format(const char* strFormat, ArgTypes... args);
		//{
		//	VariableBox arguments[sizeof...(args)] = { Boxing<ArgTypes>(args)... };
		//	Format_Internal(strFormat, sizeof...(args), arguments);
		//	return *this;
		//}

		// Format string
		template< class ...ArgTypes >
		inline String& AppendFormat(const char* strFormat, ArgTypes... args);
		//{
		//	VariableBox arguments[sizeof...(args)] = { Boxing<ArgTypes>(args)... };
		//	AppendFormat_Internal(strFormat, sizeof...(args), arguments);
		//	return *this;
		//}

		const char* data() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }
		operator const char*() const { return m_Buffer != nullptr ? m_Buffer->GetBufferPointer() : nullptr; }

		bool operator == (const char* src) const;
		bool operator != (const char* src) const;

		String& operator = (const char* src);
		String& operator = (const String& src);

	protected:

		size_t Format_Internal(const char* szFormating, int iNumArg, VariableBox* Args);
		size_t AppendFormat_Internal(const char* szFormating, int iNumArg, VariableBox* Args);
	};




}; // namespace SF




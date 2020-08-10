////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : string
//	
//
////////////////////////////////////////////////////////////////////////////////


namespace SF
{


	////////////////////////////////////////////////////////////////////////////////
	//
	//	TSharedStringBuffer
	//

	//template<typename CharType>
	//template<typename CharType2>
	//TSharedStringBuffer<CharType>::TSharedStringBuffer(IHeap& heap, const CharType2* src)
	//	: m_Heap(heap)
	//{
	//	if (src == nullptr)
	//		return;

	//	Append(src, StrUtil::StringLen(src));
	//}


	//template<typename CharType>
	//template<typename CharType2>
	//bool TSharedStringBuffer<CharType>::Append(const CharType2* src, size_t strLen)
	//{
	//	if (src == nullptr) return false;

	//	auto newStringLength = m_StringLength + strLen;
	//	auto newAllocationSize = (newStringLength + 1) * sizeof(CharType);
	//	if (newAllocationSize > m_AllocatedSize)
	//	{
	//		if (!Reserve(newStringLength))
	//			return false;
	//	}

	//	// copy string data and update string length
	//	auto copyStart = m_StringValue + GetStringLength();
	//	memcpy(copyStart, src, sizeof(CharType) * strLen);
	//	copyStart[strLen] = {};
	//	m_StringLength = m_StringLength + strLen;
	//	assert(m_StringLength == StrUtil::StringLen(m_StringValue));
	//	return true;
	//}

	//template<> template<>
	//inline TSharedStringBuffer<char>::TSharedStringBuffer(IHeap& heap, const wchar_t* src)
	//	: m_Heap(heap)
	//{
	//	if (src == nullptr)
	//		return;

	//	auto ConvertedMax = StrUtil::CharacterCount(src) * 4 + sizeof(char); // Just maximum byte conversion
	//	auto ConvertedString = reinterpret_cast<char*>(alloca(ConvertedMax));
	//	StrUtil::WCSToUTF8(src, ConvertedString, static_cast<int>(ConvertedMax));

	//	Append(ConvertedString, StrUtil::StringLen(src));
	//}

	//template<> template<>
	//inline TSharedStringBuffer<wchar_t>::TSharedStringBuffer(IHeap& heap, const char* src)
	//	: m_Heap(heap)
	//{
	//	if (src == nullptr)
	//		return;

	//	auto ConvertedMax = (StrUtil::CharacterCount(src) + 1) * sizeof(wchar_t); // Just maximum byte conversion
	//	auto ConvertedString = reinterpret_cast<wchar_t*>(alloca(ConvertedMax));
	//	StrUtil::UTF8ToWCS(src, ConvertedString, static_cast<int>(ConvertedMax));

	//	Append(ConvertedString, StrUtil::StringLen(src));
	//}


	//template<>
	//template<>
	//inline bool TSharedStringBuffer<char>::Append(const wchar_t* src, size_t strLen)
	//{
	//	if (src == nullptr) return false;

	//	auto newStringLength = m_StringLength + strLen * StrUtil::MAX_UTF8_BYTES;
	//	auto newAllocationSize = (newStringLength + 1) * sizeof(char);
	//	if (newAllocationSize > m_AllocatedSize)
	//	{
	//		if (!Reserve(newStringLength))
	//			return false;
	//	}

	//	// copy string data and update string length
	//	auto copyStart = m_StringValue + GetStringLength();
	//	StrUtil::WCSToUTF8(src, copyStart, static_cast<int>(strLen * StrUtil::MAX_UTF8_BYTES));

	//	m_StringLength = m_StringLength + strLen;
	//	assert(m_StringLength == StrUtil::StringLen(m_StringValue));
	//	return true;
	//}


	//template<>
	//template<>
	//inline bool TSharedStringBuffer<wchar_t>::Append(const char* src, size_t strLen)
	//{
	//	if (src == nullptr) return false;

	//	auto newStringLength = m_StringLength + strLen;
	//	auto newAllocationSize = (newStringLength + 1) * sizeof(wchar_t);
	//	if (newAllocationSize > m_AllocatedSize)
	//	{
	//		if (!Reserve(newStringLength))
	//			return false;
	//	}

	//	// copy string data and update string length
	//	auto copyStart = m_StringValue + GetStringLength();
	//	StrUtil::UTF8ToWCS(src, copyStart, static_cast<int>(strLen + 1));

	//	m_StringLength = m_StringLength + strLen;
	//	assert(m_StringLength == StrUtil::StringLen(m_StringValue));
	//	return true;
	//}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TString
	//


}


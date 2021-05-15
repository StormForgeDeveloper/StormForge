////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : path utility
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFPath.h"
#include "Util/SFStrUtil.h"





namespace SF {
namespace Util {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Path utility
	//


	// Path separator
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	const char* Path::DirectorySeparatorCharString = "\\";
	const char Path::DirectorySeparatorChar = '\\';
	const char Path::AltDirectorySeparatorChar = '/';
	const char* Path::DirectorySeparatorChars = "\\/";
#else
	const char* Path::DirectorySeparatorCharString = "/";
	const char Path::DirectorySeparatorChar = '/';
	const char Path::AltDirectorySeparatorChar = '\\';
	const char* Path::DirectorySeparatorChars = "/\\";
#endif

	// Get extension
	const char* Path::GetExt(const char* strFilePath)
	{
		if (strFilePath == nullptr)
			return nullptr;

		int iPos = StrUtil::IndexofFromBack(strFilePath, '.');
		if (iPos >= 0)
			return &strFilePath[iPos];
		return nullptr;
	}

	// Get file name with extension
	String Path::GetFileName(const String& strFilePath)
	{
		if (strFilePath.GetLength() == 0)
			return String(strFilePath.GetHeap());

		auto pStr = GetFileName(strFilePath.data());
		return String(strFilePath.GetHeap(), pStr);
	}

	const char* Path::GetFileName(const char* strFilePath)
	{
		if (strFilePath == nullptr)
			return nullptr;

		int iSeperator = StrUtil::IndexofAnyFromBack(strFilePath, DirectorySeparatorChars);
		if (iSeperator < 0)
			return strFilePath;

		return strFilePath + iSeperator + 1;
	}

	// Get Filename without extension
	String Path::GetFileNameWithoutExt(const String& strFilePath)
	{
		if (strFilePath.GetLength() == 0)
			return String(strFilePath.GetHeap());

		return GetFileNameWithoutExt(strFilePath.GetHeap(), strFilePath.data());
	}

	String Path::GetFileNameWithoutExt(IHeap& heap, const char* strFilePath)
	{
		if (strFilePath == nullptr)
			return String(heap);

		auto pExt = GetExt(strFilePath);
		auto pFileName = GetFileName(strFilePath);
		if(pFileName == nullptr)
			return String(heap);

		if (pExt != nullptr)
		{
			return String(heap, pFileName, 0, (int)((intptr_t)pExt - (intptr_t)pFileName));
		}
		else
		{
			return String(heap, pFileName);
		}

		return String(heap);
	}

	// Get file directory
	String Path::GetFileDirectory(const String& strFilePath)
	{
		if (strFilePath == nullptr)
			return nullptr;

		auto pStr = strFilePath;
		int iSeperator = StrUtil::IndexofAnyFromBack(strFilePath, DirectorySeparatorChars);
		if (iSeperator < 0)
			return strFilePath;

		return String(strFilePath.GetHeap(), strFilePath, 0, iSeperator);
	}

	// Combine paths
	String Path::Combine(const String& strFilePath1, const char* strFilePath2)
	{
		if (strFilePath1.GetLength() == 0)
			return String(strFilePath1.GetHeap(), strFilePath2);

		if (strFilePath2 == nullptr)
			return strFilePath1;

		String result(strFilePath1.GetHeap());
		result.Append(strFilePath1);
		if(strFilePath1.GetLength() > 0
			&& result[strFilePath1.GetLength() - 1] != DirectorySeparatorChar
			&& strFilePath2[0] != DirectorySeparatorChar)
			result.Append(DirectorySeparatorChar);

		result.Append(strFilePath2);

		return result;
	}

	String Path::Combine(const String& strFilePath1, const char* strFilePath2, const char* strFilePath3)
	{
		return Combine(Combine(strFilePath1, strFilePath2), strFilePath3);
	}




} // namespace Util
} // namespace SF



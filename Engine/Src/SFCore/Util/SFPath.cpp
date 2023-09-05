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
#include "IO/SFFileUtil.h"
#include <filesystem>
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#include <userenv.h>
#include <shlobj_core.h>
#else
#include <pwd.h>
#endif



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
    const char* Path::AltDirectorySeparatorCharString = "/";
	const char* Path::DirectorySeparatorChars = "\\/";
#else
	const char* Path::DirectorySeparatorCharString = "/";
	const char Path::DirectorySeparatorChar = '/';
	const char Path::AltDirectorySeparatorChar = '\\';
    const char* Path::AltDirectorySeparatorCharString = "\\";
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

    String Path::GetParentFileDirectory(const String& strFilePath)
    {
        if (strFilePath.IsNullOrEmpty())
            return nullptr;

        String resultString = strFilePath.TrimEnd(DirectorySeparatorChars);

        int iSeperator = StrUtil::IndexofAnyFromBack(resultString, DirectorySeparatorChars);

        // No more parent
        if (iSeperator < 0)
            return nullptr;

        if (iSeperator > 0)
        {
            resultString.Resize(iSeperator);
        }
        else
        {
            resultString.Resize(iSeperator + 1);
        }

        return resultString;
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


	static String SaveDir;
	const String& Path::GetSaveDir()
	{

		if (SaveDir.IsNullOrEmpty())
		{
			char profilePath[MAX_PATH]{};
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			auto tempDir = GetTempDir();
			SHGetSpecialFolderPathA(nullptr, profilePath, CSIDL_LOCAL_APPDATA, true);
#else
			struct passwd* pw = getpwuid(getuid());
			StrUtil::StringCopy(profilePath, pw->pw_dir);
#endif

			SaveDir = Combine(profilePath, GetModuleName(), "Saves");

			FileUtil::CreatePath(SaveDir.data());
		}

		return SaveDir;
	}


	static String TempDir;
	const String& Path::GetTempDir()
	{

		if (TempDir.IsNullOrEmpty())
		{
			//std::wstring tempWDir = std::filesystem::temp_directory_path();
			//char tempBuffer[1024]{};
			//StrUtil::WCSToUTF8(tempWDir.c_str(), tempBuffer);

			//TempDir = Combine(tempBuffer, GetModuleName(), "Temp");
		}

		return TempDir;
	}

	static String ContentDir;
	const String& Path::GetContentDir()
	{
        if (ContentDir.IsNullOrEmpty())
        {
            String curPath = Util::GetModulePath();
            while (curPath.length() > 0)
            {
                String testPath = Util::Path::Combine(curPath, "Contents");
                if (FileUtil::IsDirectoryExist(testPath))
                {
                    ContentDir = testPath;
                    break;
                }

                curPath = Util::Path::GetParentFileDirectory(curPath);
            }

            // put "Contents" if failed to find best path
            if (ContentDir.IsNullOrEmpty())
                ContentDir = "Contents";
        }

		return ContentDir;
	}



} // namespace Util
} // namespace SF



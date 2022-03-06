////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : File
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "IO/SFFileUtil.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Util/SFPath.h"
#include "Util/SFString.h"
#include "Util/SFStringFormat.h"
#include <filesystem>



namespace SF {

	Result FileUtil::CreateDirectory(const char* strPath)
	{
		if (StrUtil::IsNullOrEmpty(strPath))
			return ResultCode::INVALID_ARG;

		std::error_code error;

		if (!std::filesystem::create_directory(std::filesystem::path(strPath), error))
		{
			// TODO: convert std error to our error code
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}

	bool FileUtil::IsDirectoryExist(const char* strPath)
	{
		if (StrUtil::IsNullOrEmpty(strPath))
			return false;

		return std::filesystem::exists(strPath);
	}

	bool FileUtil::IsFileExist(const char* strPath)
	{
		if (StrUtil::IsNullOrEmpty(strPath))
			return false;

		return std::filesystem::exists(strPath);
	}

	Result FileUtil::DeleteFile(const char* strPath)
	{
		if (StrUtil::IsNullOrEmpty(strPath))
			return ResultCode::INVALID_ARG;

		return std::filesystem::remove(strPath);
	}

	// Create directory
	Result FileUtil::CreatePath(const char* strPath, int skipLast)
	{
		if (StrUtil::IsNullOrEmpty(strPath))
			return ResultCode::INVALID_ARG;

		PathString path(strPath);
		return CreatePath(path, skipLast);
	}

	Result FileUtil::CreatePath(const PathString& path, int skipLast)
	{
		if (path.size() == 0)
			return ResultCode::SUCCESS;

		String pathToCreate = path[0];
		FileUtil::CreateDirectory(pathToCreate.data());

		for (int iPath = 1; (iPath+skipLast) < path.size(); iPath++)
		{
			pathToCreate.AppendFormat("{0}{1}", Util::Path::DirectorySeparatorCharString, path[iPath]);

			if (!IsDirectoryExist(pathToCreate.data()))
				FileUtil::CreateDirectory(pathToCreate.data());
		}

		return ResultCode::SUCCESS;
	}


	bool FileUtil::CopyFile(const char* strPathFrom, const char* strPathTo)
	{
		return std::filesystem::copy_file(strPathFrom, strPathTo);
	}
}

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : File
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"


namespace SF {

	/////////////////////////////////////////////////////////////////////////////
	//
	//	File utility
	//

	class FileUtil
	{
	public:

		// create single directory. it fails if any parent directory doesn't exist
		static Result CreateDirectory(const char* strPath);

		// check directory existence
		static bool IsDirectoryExist(const char* strPath);

		static bool IsFileExist(const char* strPath);

		// Create path
		static Result CreatePath(const char* strPath, int skipLast = 0);
		static Result CreatePath(const PathString& path, int skipLast = 0);

		static bool CopyFile(const char* strPathFrom, const char* strPathTo);
	};


}

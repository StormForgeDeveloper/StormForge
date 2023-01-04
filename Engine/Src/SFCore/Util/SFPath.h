////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Path utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Util/SFString.h"


namespace SF {
namespace Util {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Path utility
	//

	class Path
	{
	public:

		// System path separator
		static const char DirectorySeparatorChar;
        static const char* DirectorySeparatorCharString;

        static const char AltDirectorySeparatorChar;
        static const char* AltDirectorySeparatorCharString;

		static const char* DirectorySeparatorChars;


		// Get extension
		static const char* GetExt(const char* strFilePath);

		// Get file name with extension
		static String GetFileName(const String& strFilePath);
		static const char* GetFileName(const char* strFilePath);

		// Get Filename without extension
		static String GetFileNameWithoutExt(const String& strFilePath);
		static String GetFileNameWithoutExt(IHeap& heap, const char* strFilePath);

		// Get file directory
		static String GetFileDirectory(const String& strFilePath);

        static String GetParentFileDirectory(const String& strFilePath);

		// Combine paths
		static String Combine(const String& strFilePath1, const char* strFilePath2);
		static String Combine(const String& strFilePath1, const char* strFilePath2, const char* strFilePath3);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//
		//

		static const String& GetSaveDir();
		static const String& GetTempDir();

		static const String& GetContentDir();
	};



} // namespace Util
} // namespace SF



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"
#include "String/SFStrUtil.h"





namespace SF {
namespace Util {

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module Name helper
	//
	static char g_szModulePath[MAX_PATH] = {0};
	static char g_szModuleName[MAX_PATH] = {0};
	static char g_szServiceName[MAX_PATH] = {0};

#if SF_PLATFORM == SF_PLATFORM_LINUX
	size_t get_executable_path(char* buffer, size_t len)
	{
		char* path_end;
		/* Read the target of /proc/self/exe. */
		if (readlink("/proc/self/exe", buffer, len) <= 0)
			return -1;
		/* Find the last occurrence of a forward slash, the path separator. */
		path_end = strrchr(buffer, '/');
		if (path_end == NULL)
			return -1;
		/* Advance to the character past the last slash. */
		++path_end;
		/* Obtain the directory containing the program by truncating the
		path after the last slash. */
		*path_end = '\0';
		/* The length of the path is the number of characters up through the
		last slash. */
		return (size_t)(path_end - buffer);
	}
#endif

	static void _InitModuleName()
	{
		if( g_szModulePath[0] == L'\0' || g_szModuleName[0] == L'\0')
		{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			// initialize module name
			char drive[_MAX_DRIVE] = {0};
			char dir[_MAX_DIR] = {0};
			char ext[_MAX_EXT] = "";

			GetModuleFileNameA(GetModuleHandle(NULL), g_szModulePath, MAX_PATH);
			_splitpath_s( g_szModulePath, drive, dir, g_szModuleName, ext );
			_snprintf_s( g_szModulePath, MAX_PATH, "%s%s", drive, dir );
#elif SF_PLATFORM == SF_PLATFORM_ANDROID
			strcpy(g_szModuleName, "StormForge");
#elif SF_PLATFORM == SF_PLATFORM_IOS
			strcpy(g_szModuleName, "StormForge");
#else
			get_executable_path(g_szModulePath, countof(g_szModulePath));

			char exe[1024];

			auto ret = (int)readlink("/proc/self/exe", exe, sizeof(exe) - 1);
			if (ret == -1) {
				fprintf(stderr, "ERRORRRRR\n");
				exit(1);
			}
			exe[ret] = 0;

			char* bastNameLoc = basename(exe);
			*(bastNameLoc - 1) = '\0';
			strcpy(g_szModuleName, bastNameLoc);
#endif
		}

		// If the service name isn't specified, use module name for it
		if( g_szServiceName[0] == '\0')
		{
			StrUtil::StringCopy( g_szServiceName, g_szModuleName );
		}
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module Name helper
	//



	const char* GetServiceName()
	{
		_InitModuleName();
		return g_szServiceName;
	}


	void SetServiceName(const char* serviceName)
	{
		StrUtil::StringCopy(g_szServiceName, serviceName);
	}


	// Module Name

	const char* GetModuleName()
	{
		_InitModuleName();
		return g_szModuleName;
	}

	// Module Path
	const char* GetModulePath()
	{
		_InitModuleName();
		return g_szModulePath;
	}

	void SetModulePath(const char* customModulePath, const char* moduleName)
	{
		StrUtil::StringCopy(g_szModulePath, customModulePath);
		StrUtil::StringCopy(g_szModuleName, moduleName);

		// If the service name isn't specified, use module name for it
		if (g_szServiceName[0] == '\0')
		{
			StrUtil::StringCopy(g_szServiceName, g_szModuleName);
		}
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Generic utility functions
	//


	// Find min bit can embrace the number
	uint32_t FindMinBitShift(uint32_t uiNumber)
	{
		static constexpr struct {
			uint32_t Mask;
			uint32_t Shift;
		} OperationTable[] = {
			{ 0xFFFF0000, 16 },
			{ 0x0000FF00, 8 },
			{ 0x000000F0, 4 },
			{ 0x0000000C, 2 },
			{ 0x00000002, 1 },
		};

		AssertRel((uiNumber & 0x80000000L) == 0);

		uint32_t power = 0;
		bool bIsOver = false;

		// Binary search
		for (uint32_t iOper = 0; iOper < countof(OperationTable); iOper++)
		{
			if (uiNumber & OperationTable[iOper].Mask)
			{
				bIsOver |= (uiNumber & (~OperationTable[iOper].Mask)) != 0;
				power += OperationTable[iOper].Shift;
				uiNumber >>= OperationTable[iOper].Shift;
			}
		}

		// power has the bit shift of most significant bit
		//  We need bigger number than this
		if (bIsOver) power++;
		return power;
	}

	// Calculate near power of w
	uint NearPowerOf2( uint32_t uiNumber )
	{
		auto power = FindMinBitShift(uiNumber);
		return 1<<power;
	}

} // namespace Util
} // namespace SF



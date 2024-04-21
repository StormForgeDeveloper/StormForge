////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"
#include "Util/SFStrUtil.h"
#include "json/json.h"
#include "IO/SFFile.h"
#include "Util/SFGuid.h"


namespace SF {
namespace Util {

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module Name helper
	//
	static char g_szModulePath[MAX_PATH] = {0};
	static char g_szModuleName[MAX_PATH] = {0};
	static char g_szServiceName[MAX_PATH] = {0};
	static char g_szMachineId[64] = { 0 };

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

    Guid g_TitleUID;
    const Guid& GetTitleUID()
    {
        return g_TitleUID;
    }

    void SetTitleUID(const Guid& titleUID)
    {
        g_TitleUID = titleUID;
    }

    char g_TitleEnv[256]{};
    const char* GetTitleEnv()
    {
        return g_TitleEnv;
    }

    void SetTitleEnv(const char* titleEnv)
    {
        StrUtil::StringCopy(g_TitleEnv, titleEnv);
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


	const char* GetMachineUniqueId()
	{
		if (g_szMachineId[0] != '\0')
			return g_szMachineId;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		ULONG Flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_SKIP_FRIENDLY_NAME;
		ULONG Result;
		ULONG Size = 0;
		ULONG Family = AF_UNSPEC;// : AF_INET;

		// determine the required size of the address list buffer
		Result = GetAdaptersAddresses(Family, Flags, nullptr, nullptr, &Size);
		if (Result != ERROR_BUFFER_OVERFLOW)
		{
			return nullptr;
		}

		DynamicArray<IP_ADAPTER_ADDRESSES> AdapterAddresses;
		AdapterAddresses.resize(Size);

		// get the actual list of adapters
		Result = GetAdaptersAddresses(Family, Flags, nullptr, AdapterAddresses.data(), &Size);
		if (Result != ERROR_SUCCESS)
		{
			return nullptr;
		}

		PIP_ADAPTER_ADDRESSES Selected = AdapterAddresses.data();

		// extract the list of physical addresses from each adapter
		for (PIP_ADAPTER_ADDRESSES AdapterAddress = AdapterAddresses.data(); AdapterAddress != nullptr; AdapterAddress = AdapterAddress->Next)
		{
			if ((AdapterAddress->IfType == IF_TYPE_ETHERNET_CSMACD || AdapterAddress->IfType == IF_TYPE_IEEE80211)) 
			//	&& AdapterAddress->OperStatus == IfOperStatusUp)
			{
				Selected = AdapterAddress; // any operable ethernet is selected as default
				bool bDnsEligible = false;
				for (PIP_ADAPTER_UNICAST_ADDRESS UnicastAddress = AdapterAddress->FirstUnicastAddress; UnicastAddress != nullptr; UnicastAddress = UnicastAddress->Next)
				{
					if ((UnicastAddress->Flags & IP_ADAPTER_ADDRESS_DNS_ELIGIBLE) != 0)
					{
						bDnsEligible = true;
						break;
					}
				}

				if (bDnsEligible) // we found the one
					break;
			}
		}

		ArrayView<uint8_t> machineIdView(sizeof(g_szMachineId), (uint8_t*)g_szMachineId);
		machineIdView.Reset();
		HEXEncode(Selected->PhysicalAddressLength, Selected->PhysicalAddress, machineIdView);

#else

		int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
		if (sock < 0)
			return nullptr;

		// enumerate all IP addresses of the system
		struct ifconf conf;
		char ifconfbuf[128 * sizeof(struct ifreq)];
		memset(ifconfbuf, 0, sizeof(ifconfbuf));
		conf.ifc_buf = ifconfbuf;
		conf.ifc_len = sizeof(ifconfbuf);
		if (ioctl(sock, SIOCGIFCONF, &conf))
		{
			return nullptr;
		}

		// get MAC address
		bool foundMac1 = false;
		struct ifreq* ifr;
		for (ifr = conf.ifc_req; (char*)ifr < (char*)conf.ifc_req + conf.ifc_len; ifr++)
		{
			if (ifr->ifr_addr.sa_data == (ifr + 1)->ifr_addr.sa_data) // duplicate, skip it
				continue;

			if (ioctl(sock, SIOCGIFFLAGS, ifr)) // failed to get flags, skip it
				continue;

			if (ioctl(sock, SIOCGIFHWADDR, ifr) == 0)
			{
				ArrayView<uint8_t> machineIdView(sizeof(g_szMachineId), (uint8_t*)g_szMachineId);
				machineIdView.Reset();
				HEXEncode(6, (const uint8_t*)ifr->ifr_addr.sa_data, machineIdView);
				break;
			}
		}

		close(sock);

#endif

		return g_szMachineId;
	}

	void SetMachineUniqueId(const char* machineId)
	{
		if (machineId == nullptr)
			return;

		StrUtil::StringCopy(g_szMachineId, machineId);
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

    Result LoadWholeFile(const char* path, Array<uint8_t>& outData)
    {
        Result hr;
        File file;
        file.Open(path, File::OpenMode::Read);
        if (!file.IsOpened())
            return hr = ResultCode::FAIL;

        auto fileSize = file.GetFileSize();
        outData.reserve(fileSize + 1); // prevent reallocation in case we need text terminator
        outData.resize(fileSize);
        size_t readed = 0;
        hr = file.Read(outData.data(), fileSize, readed);
        if (!hr.IsSuccess())
            return hr;

        return hr;
    }

    Result LoadJsonFile(const char* jsonPath, Json::Value& outValue)
    {
        Result hr;

        DynamicArray<uint8_t> buffer;
        hr = LoadWholeFile(jsonPath, buffer);

        buffer.push_back('\0');

        int readOffset = 0;
        constexpr uint8_t UTF8BOM[] = { 0xEF, 0xBB, 0xBF };
        if (buffer.size() >= 3 && memcmp(UTF8BOM, buffer.data(), 3) == 0)
            readOffset = 3;

        std::string errs;
        Json::CharReaderBuilder jsonBuilder;
        UniquePtr<Json::CharReader> jsonReader(jsonBuilder.newCharReader());
        auto readStart = reinterpret_cast<const char*>(buffer.data() + readOffset);
        bool bRes = jsonReader->parse(readStart, readStart + (buffer.size() - readOffset), &outValue, &errs);
        if (!bRes)
        {
            SFLog(Net, Error, "LoadJsonFile value parsing {0}, error:{1}", jsonPath, errs);
            return ResultCode::INVALID_STR_DATA;
        }

        return ResultCode::SUCCESS;
    }

} // namespace Util
} // namespace SF



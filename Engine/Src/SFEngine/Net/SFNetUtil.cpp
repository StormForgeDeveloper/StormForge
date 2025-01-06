////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Network utility. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Container/SFSpinSharedBuffer.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Util/SFToString.h"
#include "Platform/Android/SFifaddrs.h"

#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetToString.h"


#if SF_PLATFORM != SF_PLATFORM_WINDOWS
#include <net/if.h>
#	if SF_PLATFORM != SF_PLATFORM_ANDROID
#	include <ifaddrs.h>
#	endif

#else // SF_PLATFORM_WINDOWS

#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

#endif


namespace SF {
namespace Net {

	static_assert(INET6_ADDRSTRLEN <= NetAddress::MAX_NETNAME, "Net address length must be same with client");

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Utility functions
	//
	
	//
	//Result SockAddr2Addr(const sockaddr_in6 &sockAddr, NetAddress &addr)
	//{
		//Assert(sockAddr.sin6_family == AF_INET6);
		//addr.SocketFamily = SockFamily::IPV6;
		//addr.Address[0] = '\0';
		//auto result = inet_ntop(sockAddr.sin6_family, (void*)&sockAddr.sin6_addr, addr.Address, sizeof addr.Address);
		//if (result == nullptr) return GetLastNetSystemResult();
		//addr.Port = ntohs(sockAddr.sin6_port);
		//return ResultCode::SUCCESS;
	//}
//
	//Result SockAddr2Addr(const sockaddr_in &sockAddr, NetAddress &addr)
	//{
		//Assert(sockAddr.sin_family == AF_INET);
		//addr.SocketFamily = SockFamily::IPV4;
		//addr.Address[0] = '\0';
		//auto result = inet_ntop(sockAddr.sin_family, (void*)&sockAddr.sin_addr, addr.Address, sizeof addr.Address);
		//if (result == nullptr) return GetLastNetSystemResult();
		//addr.Port = ntohs(sockAddr.sin_port);
		//return ResultCode::SUCCESS;
	//}
//
	//Result SockAddr2Addr(const sockaddr_storage &sockAddr, NetAddress &addr)
	//{
		//if (sockAddr.ss_family == AF_INET6)
		//{
			//return SockAddr2Addr(*(sockaddr_in6*)&sockAddr, addr);
		//}
		//else if(sockAddr.ss_family == AF_INET)
		//{
			//return SockAddr2Addr(*(sockaddr_in*)&sockAddr, addr);
		//}
		//else
		//{
			//// Not supported address family
			//addr.SocketFamily = SockFamily::None;
			//addr.Address[0] = '\0';
			//addr.Port = 0;
		//}
//
		//return ResultCode::SUCCESS;
	//}

	Result Addr2SockAddr(const NetAddress &addr, sockaddr_in6 &sockAddr)
	{
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin6_family = AF_INET6;
		sockAddr.sin6_port = htons(addr.Port);
		int result = inet_pton(sockAddr.sin6_family, addr.Address, &sockAddr.sin6_addr);
        //SFLog(System, Info, "Addr2SockAddrIpv6: addr.Address:{0}, result:{1}", addr.Address, result);
		if (result != TRUE)
		{
			return ResultCode::FAIL;
		}
		else
			return ResultCode::SUCCESS;
	}

	Result Addr2SockAddr(const NetAddress &addr, sockaddr_in &sockAddr)
	{
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(addr.Port);
		int result = inet_pton(sockAddr.sin_family, addr.Address, &sockAddr.sin_addr);
        //SFLog(System, Info, "Addr2SockAddrIpv4: addr.Address:{0}, result:{1}", addr.Address, result);
		if (result != TRUE)
		{
			return ResultCode::FAIL;
		}
		else
			return ResultCode::SUCCESS;
	}

	Result Addr2SockAddr(const NetAddress &addr, sockaddr_storage &sockAddr)
	{
		if (addr.SocketFamily == SockFamily::IPV6)
		{
			return Addr2SockAddr(addr, *(sockaddr_in6*)&sockAddr);
		}
		else
		{
			return Addr2SockAddr(addr, *(sockaddr_in*)&sockAddr);
		}
	}

	Result SetSockAddr(sockaddr_in6& sockAddr, const char *Address, uint16_t Port)
	{
		memset(&sockAddr, 0, sizeof(sockAddr));

		sockAddr.sin6_family = AF_INET6;
		sockAddr.sin6_port = htons(Port);
		int result = inet_pton(sockAddr.sin6_family, Address, &sockAddr.sin6_addr);
		if (result != TRUE)
		{
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}

	Result SetSockAddr(sockaddr_in& sockAddr, const char *Address, uint16_t Port)
	{
		memset(&sockAddr, 0, sizeof(sockAddr));

		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(Port);
		int result = inet_pton(sockAddr.sin_family, Address, &sockAddr.sin_addr);
		if (result != TRUE)
		{
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}

	Result SetSockAddr(sockaddr_storage& sockAddr, const char *Address, uint16_t Port)
	{
		if (!(SetSockAddr(*(sockaddr_in6*)&sockAddr, Address, Port)))
		{
			return SetSockAddr(*(sockaddr_in*)&sockAddr, Address, Port);
		}
		return ResultCode::SUCCESS;
	}


	Result GetAnyBindAddr(const sockaddr_storage &sockAddr, sockaddr_storage&bindAddr)
	{
		bindAddr = sockAddr;
		if (bindAddr.ss_family == ToSockValue(SockFamily::IPV6))
		{
			auto bindSockaddr = (sockaddr_in6*)&bindAddr;
			bindSockaddr->sin6_addr = in6addr_any;
		}
		else
		{
			auto bindSockaddr = (sockaddr_in*)&bindAddr;
			bindSockaddr->sin_addr.s_addr = INADDR_ANY;
		}
		return ResultCode::SUCCESS;
	}

	Result SetLocalNetAddress(NetAddress &localAddr, const char *strLocalAddress, uint16_t port)
	{
		StrUtil::StringCopy(localAddr.Address, strLocalAddress);
		localAddr.Port = port;

		// validate local IP
		if (!CheckLocalAddress(SockFamily::IPV6, localAddr))
		{
			if (!CheckLocalAddress(SockFamily::IPV4, localAddr))
			{
				if (GetLocalAddressIPv6(localAddr))
				{
					if (CheckLocalAddress(SockFamily::IPV6, localAddr))
					{
						SFLog(Net, Error, "Invalid Address, Using another address({0}) instead of given address", localAddr);
						localAddr.SocketFamily = SockFamily::IPV6;
					}
					else
					{
						SFLog(Net, Error, "Invalid Address, expect a local IPV6 address: {0}", strLocalAddress);
						return ResultCode::IO_INVALID_ADDRESS;
					}
				}
				else
				{
					SFLog(Net, Error, "Invalid Address, expect a local IPV6 address: {0}", strLocalAddress);
					return ResultCode::IO_INVALID_ADDRESS;
				}
			}
			else
			{
				localAddr.SocketFamily = SockFamily::IPV4;
			}
		}
		else
		{
			localAddr.SocketFamily = SockFamily::IPV6;
		}

		return ResultCode::SUCCESS;
	}

	Result SetNetAddress(NetAddress &netAddr, const char *Addressess, uint16_t port)
	{
		sockaddr_storage sockAddr;

		Result hr = SetSockAddr(sockAddr, Addressess, port);
		if (hr.IsFailure())
			return hr;

		netAddr.SocketFamily = ToSockFamily(sockAddr.ss_family);
		hr = StrUtil::StringCopy(netAddr.Address, (INT)countof(netAddr.Address), Addressess);
		if (hr.IsFailure())
			return hr;

		netAddr.Port = port;
		return ResultCode::SUCCESS;
	}

    Result ResolveAddress(const char* address, Array<NetAddress>& outResolvedAddresses)
    {
        char tempBuffer[128];
        //Convert IPV6 to IPV4
        struct addrinfo hints, * res;

        // Convert remote address
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;// AF_INET | AF_INET6;
        hints.ai_socktype = SOCK_STREAM; // probably not important
        hints.ai_flags = AI_DNS_ONLY;
        int error = getaddrinfo(address, nullptr, &hints, &res);
        switch (error)
        {
        case 0:				break;
        case EAI_AGAIN:		return ResultCode::IO_TRY_AGAIN;
        case EAI_BADFLAGS:	return ResultCode::IO_BADFLAGS;
        case EAI_FAIL:		return ResultCode::FAIL;
        case EAI_FAMILY:	return ResultCode::IO_FAMILY;
        case EAI_MEMORY:	return ResultCode::OUT_OF_MEMORY;
        case EAI_NONAME:	return ResultCode::IO_HOST_NOT_FOUND;
        case EAI_SERVICE:	return ResultCode::IO_INVALID_SERVICE;
        case EAI_SOCKTYPE:	return ResultCode::IO_NOTSOCK;
        default:			return ResultCode::UNEXPECTED;
        }

        for (const addrinfo* curAddr = res; curAddr != nullptr; curAddr = curAddr->ai_next)
        {
            SockFamily foundSocketFamily = SockFamily::None;
            bool bConverted = false;
            if (curAddr->ai_family == AF_INET)
            {
                sockaddr_in* psockAddr4 = ((sockaddr_in*)curAddr->ai_addr);
                bConverted = inet_ntop(curAddr->ai_family, &psockAddr4->sin_addr, tempBuffer, sizeof tempBuffer) != nullptr;
                if (bConverted)
                    foundSocketFamily = SockFamily::IPV4;
            }
            else if (curAddr->ai_family == AF_INET6)
            {
                sockaddr_in6* psockAddr6 = ((sockaddr_in6*)curAddr->ai_addr);
                if (psockAddr6->sin6_scope_id == 0)
                {
                    bConverted = inet_ntop(curAddr->ai_family, &psockAddr6->sin6_addr, tempBuffer, sizeof tempBuffer) != nullptr;
                    if (bConverted)
                        foundSocketFamily = SockFamily::IPV6;
                }
            }

            if (foundSocketFamily != SockFamily::None)
            {
                outResolvedAddresses.push_back(NetAddress(foundSocketFamily, tempBuffer, 0));
            }
        }
        freeaddrinfo(res);

        return outResolvedAddresses.size() > 0 ? ResultCode::SUCCESS : ResultCode::FAIL;
    }


	Result GetLocalAddressBSD(SockFamily family, NetAddress &addr)
	{
		char tempBuffer[128];
		//Convert IPV6 to IPV4
		struct addrinfo hints, *res;
		bool bIsFound = false;

		// Convert remote address
		memset(&hints, 0, sizeof hints);
		hints.ai_family = ToSockValue(family);
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;
		auto error = getaddrinfo("", nullptr, &hints, &res);
		switch (error)
		{
		case 0:				break;
		case EAI_AGAIN:		return ResultCode::IO_TRY_AGAIN;
		case EAI_BADFLAGS:	return ResultCode::IO_BADFLAGS;
		case EAI_FAIL:		return ResultCode::FAIL;
		case EAI_FAMILY:	return ResultCode::IO_FAMILY;
		case EAI_MEMORY:	return ResultCode::OUT_OF_MEMORY;
		case EAI_NONAME:	return ResultCode::IO_HOST_NOT_FOUND;
		case EAI_SERVICE:	return ResultCode::IO_INVALID_SERVICE;
		case EAI_SOCKTYPE:	return ResultCode::IO_NOTSOCK;
		default:			return ResultCode::UNEXPECTED;
		}

		for (auto curAddr = res; curAddr != nullptr; curAddr = curAddr->ai_next)
		{
			if (curAddr->ai_family == AF_INET)
			{
				sockaddr_in* psockAddr4 = ((sockaddr_in*)curAddr->ai_addr);
				bIsFound = inet_ntop(AF_INET, &psockAddr4->sin_addr, tempBuffer, sizeof tempBuffer) != nullptr;
				break;
			}
			else if (curAddr->ai_family == AF_INET6)
			{
				sockaddr_in6* psockAddr6 = ((sockaddr_in6*)curAddr->ai_addr);
				if (!bIsFound || psockAddr6->sin6_scope_id == 0)
				{
					bIsFound = inet_ntop(AF_INET6, &psockAddr6->sin6_addr, tempBuffer, sizeof tempBuffer) != nullptr;
					if (bIsFound && psockAddr6->sin6_scope_id == 0)
						break;
				}
			}
		}
		freeaddrinfo(res);

		if (bIsFound)
		{
			addr.SocketFamily = family;
			StrUtil::StringCopy(addr.Address, tempBuffer);
		}

		return bIsFound ? ResultCode::SUCCESS : ResultCode::FAIL;
	}

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

	Result GetLocalAddress(SockFamily family, NetAddress &outAddr)
	{
		DWORD retval;
		MIB_IPFORWARD_TABLE2 *routes = NULL;
		MIB_IPFORWARD_ROW2 *route;

		unsigned int i;
		IP_ADAPTER_ADDRESSES IPAddressTable[256];
		ULONG AddrTableSize = sizeof(IPAddressTable);
		auto ret = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_DNS_SERVER, 0, IPAddressTable, &AddrTableSize);
		if (ret != NO_ERROR)
		{
			SFLog(Net, Error, "GetAdaptersAddresses failed (0x{0})\n.", retval);
			return ResultCode::FAIL;
		}

		PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
		retval = GetIpForwardTable2(AF_UNSPEC, &routes);
		if (retval != ERROR_SUCCESS)
		{
			SFLog(Net, Error, "GetIpForwardTable2 failed (0x{0})\n.", retval);
			return ResultCode::FAIL;
		}

		for (unsigned iRoute = 0; iRoute < routes->NumEntries; iRoute++)
		{
			route = routes->Table + iRoute;

			if (route->Loopback)
				continue;

			if (route->Protocol != PROTO_IP_NETMGMT)
				continue;

			//char ipv6AddrString[128] = {};
			//inet_pton(AF_INET6, (PCSTR)&route->NextHop.Ipv6.sin6_addr, ipv6AddrString);
			//printf("next hop: \t %s, %s\n", inet_ntoa(route->NextHop.Ipv4.sin_addr), ipv6AddrString);
			auto RoutingProtocolFamily = route->NextHop.si_family;
			if (ToSockValue(family) != RoutingProtocolFamily)
				continue;

			auto pCurrAddresses = IPAddressTable;
			for (; pCurrAddresses != nullptr; pCurrAddresses = pCurrAddresses->Next)
			{
				if (route->InterfaceIndex != pCurrAddresses->IfIndex)
					continue;

				if (pCurrAddresses->OperStatus != IfOperStatusUp)
					continue;

				pUnicast = pCurrAddresses->FirstUnicastAddress;
				if (pUnicast != nullptr)
				{
					for (i = 0; pUnicast != nullptr; pUnicast = pUnicast->Next, i++)
					{
						// Skip invalid socket family, the gateway wouldn't accept it anyway
						if (RoutingProtocolFamily != pUnicast->Address.lpSockaddr->sa_family)
							continue;


						//char AddrString[256];
						//DWORD AddressStringLength = sizeof(AddrString);
						//WSAAddressToStringA(pUnicast->Address.lpSockaddr,
						//	(DWORD)pUnicast->Address.iSockaddrLength,
						//	nullptr,
						//	AddrString,
						//	&AddressStringLength);

						//printf("  Ip Address: %s\n", AddrString);

						outAddr = *reinterpret_cast<const sockaddr_storage*>(pUnicast->Address.lpSockaddr);

						return ResultCode::SUCCESS;
					}
				}
			}
		}

        SFLog(System, Info, "GetLocalAddress family:{0}, outAddr:{1}", family, outAddr);

		return ResultCode::FAIL;
	}

	Result GetLocalAddressIPv4(NetAddress &addr)
	{
		return GetLocalAddress(SockFamily::IPV4, addr);
	}

	Result GetLocalAddressIPv6(NetAddress &addr)
	{
		return GetLocalAddress(SockFamily::IPV6, addr);
	}

	Result CheckLocalAddress(SockFamily family, NetAddress &addr)
	{
		//Convert IPV6
		struct addrinfo hints, *res;
		sockaddr_storage testSockAddr;
		bool bIsFound = false;

		addr.SocketFamily = family;
		Result hr = Addr2SockAddr(addr, testSockAddr);
        if (!hr.IsSuccess())
        {
            //SFLog(System, Info, "CheckLocalAddress family:{0}, hr:{1}", family, hr);
            return hr;
        }

        //SFLog(System, Info, "CheckLocalAddress family:{0}", family);

        // Any address test
		switch (family)
		{
		case SockFamily::IPV4:
		{
			auto *pTestSockAddr = (struct sockaddr_in *)&testSockAddr;
			if (pTestSockAddr->sin_addr.s_addr == INADDR_ANY) return ResultCode::SUCCESS;
			break;
		}

		case SockFamily::IPV6:
		{
			auto *pTestSockAddr = (struct sockaddr_in6 *)&testSockAddr;
			auto& rawAddress = pTestSockAddr->sin6_addr.s6_addr;
			auto& rawAddressSrc = in6addr_any.s6_addr;
			size_t iAddr = 0;
			for (; iAddr < countof(rawAddress); iAddr++)
			{
				if (rawAddress[iAddr] != rawAddressSrc[iAddr]) break;
			}
			if (iAddr >= countof(rawAddress)) return ResultCode::SUCCESS;
			break;
		}
        default:
            break;
        }


		// Convert remote address
		memset(&hints, 0, sizeof hints);
		hints.ai_family = ToSockValue(family);
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_flags = AI_PASSIVE;
		auto error = getaddrinfo("", nullptr, &hints, &res);
		switch (error)
		{
		case 0:				break;
		case EAI_AGAIN:		return ResultCode::IO_TRY_AGAIN;
		case EAI_BADFLAGS:	return ResultCode::IO_BADFLAGS;
		case EAI_FAIL:		return ResultCode::FAIL;
		case EAI_FAMILY:	return ResultCode::IO_FAMILY;
		case EAI_MEMORY:	return ResultCode::OUT_OF_MEMORY;
		case EAI_NONAME:	return ResultCode::IO_HOST_NOT_FOUND;
		case EAI_SERVICE:	return ResultCode::IO_INVALID_SERVICE;
		case EAI_SOCKTYPE:	return ResultCode::IO_NOTSOCK;
		default:			return ResultCode::UNEXPECTED;
		}

		for (auto curAddr = res; curAddr != nullptr && !bIsFound; curAddr = curAddr->ai_next)
		{
			if (curAddr->ai_family != ToSockValue(family))
				continue;

			switch (family)
			{
			case SockFamily::IPV4:
			{
				auto *pTestSockAddr = (struct sockaddr_in *)&testSockAddr;
				struct sockaddr_in *psockAddr = (struct sockaddr_in *)curAddr->ai_addr;
				bIsFound = memcmp(&psockAddr->sin_addr, &pTestSockAddr->sin_addr, sizeof(pTestSockAddr->sin_addr)) == 0;
				break;
			}

			case SockFamily::IPV6:
			{
				auto *pTestSockAddr = (struct sockaddr_in6 *)&testSockAddr;
				struct sockaddr_in6 *psockAddr = (struct sockaddr_in6 *)curAddr->ai_addr;
				bIsFound = memcmp(&psockAddr->sin6_addr, &pTestSockAddr->sin6_addr, sizeof(pTestSockAddr->sin6_addr)) == 0;
				break;
			}

			default:
				continue;
			}

		}
		freeaddrinfo(res);

		return bIsFound ? ResultCode::SUCCESS : ResultCode::FAIL;
	}

#else


	Result GetLocalAddress(SockFamily family, NetAddress &addr)
	{
		struct ifaddrs *ifaddr = nullptr;
		char tempBuffer[NI_MAXHOST];
		bool bIsFound = false;

		if (getifaddrs(&ifaddr) == -1)
		{
			return GetLastNetSystemResult();
		}

		/* Walk through linked list, maintaining head pointer so we
		can free list later */
		int sockFamily = ToSockValue(family);
		for (struct ifaddrs *curAddr = ifaddr; curAddr != nullptr && !bIsFound; curAddr = curAddr->ifa_next)
		{
			if (curAddr->ifa_addr == nullptr)
				continue;

			if (!(curAddr->ifa_flags & IFF_UP))
				continue;

			if ((curAddr->ifa_flags & IFF_LOOPBACK))
				continue;

			if (curAddr->ifa_addr->sa_family != sockFamily)
				continue;

			switch (curAddr->ifa_addr->sa_family)
			{
			case AF_INET:
			{
				struct sockaddr_in *psockAddr = (struct sockaddr_in *)curAddr->ifa_addr;
				bIsFound = inet_ntop(AF_INET, &psockAddr->sin_addr, tempBuffer, sizeof tempBuffer) != nullptr;
				break;
			}

			case AF_INET6:
			{
				struct sockaddr_in6 *psockAddr = (struct sockaddr_in6 *)curAddr->ifa_addr;
				if (!bIsFound || psockAddr->sin6_scope_id == 0)
				{
					bIsFound = inet_ntop(AF_INET6, &psockAddr->sin6_addr, tempBuffer, sizeof tempBuffer) != nullptr;
					if (bIsFound && psockAddr->sin6_scope_id == 0)
						break;
				}
			}

			default:
				continue;
			}
		}

		freeifaddrs(ifaddr);

		if (bIsFound)
		{
			addr.SocketFamily = family;
			StrUtil::StringCopy(addr.Address, tempBuffer);
		}

		return bIsFound ? ResultCode::SUCCESS : ResultCode::FAIL;
	}

	Result GetLocalAddressIPv4(NetAddress &addr)
	{
		return GetLocalAddress(SockFamily::IPV4, addr);
	}

	Result GetLocalAddressIPv6(NetAddress &addr)
	{
		return GetLocalAddress(SockFamily::IPV6, addr);
	}

	Result CheckLocalAddress(SockFamily family, NetAddress &addr)
	{
		struct ifaddrs *ifaddr = nullptr;
		bool bIsFound = false;
		sockaddr_storage testSockAddr;

		// make sock addr
		memset(&testSockAddr, 0, sizeof testSockAddr);
        addr.SocketFamily = family;
        Result hr = Addr2SockAddr(addr, testSockAddr);
        if (!hr.IsSuccess())
        {
            //SFLog(System, Info, "CheckLocalAddress family:{0}, hr:{1}", family, hr);
            return hr;
        }

        //SFLog(System, Info, "CheckLocalAddress family:{0}", family);

        // Any address test
        switch (family)
        {
        case SockFamily::IPV4:
        {
            auto* pTestSockAddr = (struct sockaddr_in*)&testSockAddr;
            if (pTestSockAddr->sin_addr.s_addr == INADDR_ANY) return ResultCode::SUCCESS;
            break;
        }

        case SockFamily::IPV6:
        {
            auto* pTestSockAddr = (struct sockaddr_in6*)&testSockAddr;
            auto& rawAddress = pTestSockAddr->sin6_addr.s6_addr;
            auto& rawAddressSrc = in6addr_any.s6_addr;
            size_t iAddr = 0;
            for (; iAddr < countof(rawAddress); iAddr++)
            {
                if (rawAddress[iAddr] != rawAddressSrc[iAddr]) break;
            }
            if (iAddr >= countof(rawAddress)) return ResultCode::SUCCESS;
            break;
        }
        default:
            break;
        }


		if (getifaddrs(&ifaddr) == -1)
		{
			return GetLastNetSystemResult();
		}

		/* Walk through linked list, maintaining head pointer so we
		can free list later */
		int sockFamily = ToSockValue(family);
		for (struct ifaddrs *curAddr = ifaddr; curAddr != nullptr && !bIsFound; curAddr = curAddr->ifa_next)
		{
			if (curAddr->ifa_addr == nullptr)
				continue;

			if (!(curAddr->ifa_flags & IFF_UP))
				continue;

			if ((curAddr->ifa_flags & IFF_LOOPBACK))
				continue;

			if (curAddr->ifa_addr->sa_family != sockFamily)
				continue;

			switch (sockFamily)
			{
			case AF_INET:
			{
				auto *pTestSockAddr = (struct sockaddr_in *)&testSockAddr;
				struct sockaddr_in *psockAddr = (struct sockaddr_in *)curAddr->ifa_addr;
				bIsFound = memcmp(&psockAddr->sin_addr, &pTestSockAddr->sin_addr, sizeof(pTestSockAddr->sin_addr)) == 0;
				break;
			}

			case AF_INET6:
			{
				auto *pTestSockAddr = (struct sockaddr_in6 *)&testSockAddr;
				struct sockaddr_in6 *psockAddr = (struct sockaddr_in6 *)curAddr->ifa_addr;
				bIsFound = memcmp(&psockAddr->sin6_addr, &pTestSockAddr->sin6_addr, sizeof(pTestSockAddr->sin6_addr)) == 0;
				break;
			}

			default:
				continue;
			}
		}

		freeifaddrs(ifaddr);

		return bIsFound ? ResultCode::SUCCESS : ResultCode::FAIL;

	}

#endif

	/////////////////////////////////////////////////////////////////////////////////
	//
	// Socket value
	//

	int ToSockValue(SockFamily family)
	{
		switch (family)
		{
		case SockFamily::IPV4: return AF_INET;
		case SockFamily::IPV6: return AF_INET6;
		default:
			return 0;
		}
	}

	int ToSockValue(SocketType sockType)
	{
		switch (sockType)
		{
		case SocketType::Stream: return SOCK_STREAM;
		case SocketType::DataGram: return SOCK_DGRAM;
		default:
			return 0;
		}
	}

	int ToSockProto(SocketType sockType)
	{
		switch (sockType)
		{
		case SocketType::Stream: return IPPROTO_TCP;
		case SocketType::DataGram: return IPPROTO_UDP;
		default:
			return 0;
		}
	}

	SockFamily ToSockFamily(int family)
	{
		switch (family)
		{
		case AF_INET: return SockFamily::IPV4;
		case AF_INET6: return SockFamily::IPV6;
		default:
			return SockFamily::None;
		}
	}

	SocketType ToSockType(int family)
	{
		switch (family)
		{
		case SOCK_STREAM: return SocketType::Stream;
		default:
		case SOCK_DGRAM: return SocketType::DataGram;
		}
	}


	bool operator == (const sockaddr_in6 &op1, const sockaddr_in6 &op2)
	{
		return memcmp(&op1.sin6_addr, &op2.sin6_addr, sizeof op1.sin6_addr) == 0
			&& op1.sin6_port == op2.sin6_port;
	}

	bool operator != (const sockaddr_in6 &op1, const sockaddr_in6 &op2)
	{
		return memcmp(&op1.sin6_addr, &op2.sin6_addr, sizeof op1.sin6_addr) != 0
			|| op1.sin6_port != op2.sin6_port;
		//return op1.sin_addr.S_un.S_addr != op2.sin_addr.S_un.S_addr
		//	|| op1.sin_port != op2.sin_port;
	}

	bool operator == (const sockaddr_storage &op1, const sockaddr_storage &op2)
	{
		if (op1.ss_family != op2.ss_family)
			return false;

		if (op1.ss_family == AF_INET6)
		{
			auto op1SockAddr = (sockaddr_in6*)&op1;
			auto op2SockAddr = (sockaddr_in6*)&op2;
			return memcmp(&op1SockAddr->sin6_addr, &op2SockAddr->sin6_addr, sizeof op1SockAddr->sin6_addr) == 0
				&& op1SockAddr->sin6_port == op2SockAddr->sin6_port;
		}
		else
		{
			auto op1SockAddr = (sockaddr_in*)&op1;
			auto op2SockAddr = (sockaddr_in*)&op2;
			return op1SockAddr->sin_addr.s_addr == op2SockAddr->sin_addr.s_addr
				&& op1SockAddr->sin_port == op2SockAddr->sin_port;
		}
	}

	bool operator != (const sockaddr_storage &op1, const sockaddr_storage &op2)
	{
		if (op1.ss_family != op2.ss_family)
			return true;

		if (op1.ss_family == AF_INET6)
		{
			auto op1SockAddr = (sockaddr_in6*)&op1;
			auto op2SockAddr = (sockaddr_in6*)&op2;
			return memcmp(&op1SockAddr->sin6_addr, &op2SockAddr->sin6_addr, sizeof op1SockAddr->sin6_addr) != 0
				|| op1SockAddr->sin6_port != op2SockAddr->sin6_port;
		}
		else
		{
			auto op1SockAddr = (sockaddr_in*)&op1;
			auto op2SockAddr = (sockaddr_in*)&op2;
			return op1SockAddr->sin_addr.s_addr != op2SockAddr->sin_addr.s_addr
				|| op1SockAddr->sin_port != op2SockAddr->sin_port;
		}
	}

	bool operator == (const NetAddress &op1, const NetAddress &op2)
	{
		return strncmp(op1.Address, op2.Address, 16) == 0 && op1.Port == op2.Port;
	}

	bool operator != (const NetAddress &op1, const NetAddress &op2)
	{
		return strncmp(op1.Address, op2.Address, 16) != 0 || op1.Port != op2.Port;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Packet message queue class
	//

	MsgQueue::MsgQueue(IHeap& memoryManager, uint uiNumElePerPage)
		: CircularPageQueue<MessageDataPtr>(memoryManager, uiNumElePerPage)
	{
	}

	MsgQueue::~MsgQueue()
	{
		Reset();
	}

	// Clear queue element
	void MsgQueue::Reset()
	{
		SharedPointerT<MessageData> data;

		while (Dequeue(data))
		{
		}

		super::Reset();
	}


	WriteBufferQueue::WriteBufferQueue(IHeap& memoryManager, uint uiNumElePerPage)
		: CircularPageQueueAtomic<IOBUFFER_WRITE*>(memoryManager, uiNumElePerPage)
	{
	}

	WriteBufferQueue::~WriteBufferQueue()
	{
        Reset();
	}

	// Clear queue element
	void WriteBufferQueue::Reset()
	{
		IOBUFFER_WRITE* data = NULL;

		while (Dequeue(data))
		{
			Util::SafeDelete(data);
		}

		super::Reset();
	}



    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Scoped net system init/uninit
    //

    NetSystemInitializer::NetSystemInitializer()
    {
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
        WSADATA wsaData;
        int iErr = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iErr != 0)
        {
            printf("Failed to initialize Winsock DLL err=%d", iErr);
        }
#endif
    }

    NetSystemInitializer::~NetSystemInitializer()
    {
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
        WSACleanup();
#endif
    }

	//WriteBufferQueueManager::WriteBufferQueueManager(uint numQueue, uint uiNumElePerPage)
	//	: m_AssignIndex(0)
	//{
	//	m_WriteBufferQueues.SetSize(numQueue);
	//	for (uint iQueue = 0; iQueue < m_WriteBufferQueues.GetSize(); iQueue++)
	//	{
	//		m_WriteBufferQueues[iQueue] = new(GetHeap()) WriteBufferQueue(uiNumElePerPage);
	//	}
	//}

	//WriteBufferQueueManager::~WriteBufferQueueManager()
	//{
	//	Clear();
	//}

	//// Clear queue element
	//void WriteBufferQueueManager::Clear()
	//{
	//	m_AssignIndex = 0;
	//	for (uint iQueue = 0; iQueue < m_WriteBufferQueues.GetSize(); iQueue++)
	//	{
	//		m_WriteBufferQueues[iQueue]->ClearQueue();
	//		GetHeap().Delete(m_WriteBufferQueues[iQueue]);
	//	}

	//	m_WriteBufferQueues.Clear();
	//}

	//Result WriteBufferQueueManager::ChooseQueue(WriteBufferQueue* &pQueue)
	//{
	//	auto newIndex = m_AssignIndex.fetch_add(1, std::memory_order_relaxed) % m_WriteBufferQueues.GetSize();
	//}

} // namespace Net
} // namespace SF


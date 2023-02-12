////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : NetAddress
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"

#if SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID
#include <arpa/inet.h>
#endif

namespace SF {


	
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP/IP Network Address information
	//

    static Result FindNumAddress(const char* strAddress, SockFamily& outSocketFamily, int outBufferSize, char* outAddress)
    {
        outSocketFamily = SockFamily::None;

        //Convert IPV6 to IPV4
        addrinfo hints, * res = nullptr;
        bool bIsFound = false;

        // Convert remote address
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        //hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        auto error = getaddrinfo(strAddress, nullptr, &hints, &res);
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
                bIsFound = inet_ntop(AF_INET, &psockAddr4->sin_addr, outAddress, outBufferSize) != nullptr;
                if (bIsFound)
                {
                    outSocketFamily = SockFamily::IPV4;
                    break;
                }
            }
            else if (curAddr->ai_family == AF_INET6)
            {
                sockaddr_in6* psockAddr6 = ((sockaddr_in6*)curAddr->ai_addr);
                if (!bIsFound || psockAddr6->sin6_scope_id == 0)
                {
                    bIsFound = inet_ntop(AF_INET6, &psockAddr6->sin6_addr, outAddress, outBufferSize) != nullptr;
                    if (bIsFound && psockAddr6->sin6_scope_id == 0)
                    {
                        outSocketFamily = SockFamily::IPV6;
                        break;
                    }
                }
            }
        }
        freeaddrinfo(res);

        return bIsFound ? ResultCode::SUCCESS : ResultCode::FAIL;
    }

    Result NetAddress::ParseNameAddress(const char* InAddress, Array<NetAddress>& outAddresses)
    {
        NetAddress tempAddr{};
        char strAddress[256];

        StrUtil::StringCopy(strAddress, InAddress);

        auto sepratorIndex = StrUtil::IndexofAnyFromBack(strAddress, ":,");
        if (sepratorIndex > 0
            && (strAddress[sepratorIndex] != ':' || strAddress[sepratorIndex - 1] != ':')) // Avoid treating ipv6 address chunk as port number
        {
            tempAddr.Port = (uint16_t)atoi(strAddress + sepratorIndex + 1);
            strAddress[sepratorIndex] = '\0';
        }

        //Convert IPV6 to IPV4
        addrinfo hints, * res = nullptr;
        bool bIsFound = false;

        // Convert remote address
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        //hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        auto error = getaddrinfo(strAddress, nullptr, &hints, &res);
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
                bIsFound = inet_ntop(AF_INET, &psockAddr4->sin_addr, tempAddr.Address, sizeof tempAddr.Address) != nullptr;
                if (bIsFound)
                {
                    tempAddr.SocketFamily = SockFamily::IPV4;
                    outAddresses.push_back(tempAddr);
                }
            }
            else if (curAddr->ai_family == AF_INET6)
            {
                sockaddr_in6* psockAddr6 = ((sockaddr_in6*)curAddr->ai_addr);
                if (!bIsFound || psockAddr6->sin6_scope_id == 0)
                {
                    bIsFound = inet_ntop(AF_INET6, &psockAddr6->sin6_addr, tempAddr.Address, sizeof tempAddr.Address) != nullptr;
                    if (bIsFound && psockAddr6->sin6_scope_id == 0)
                    {
                        tempAddr.SocketFamily = SockFamily::IPV6;
                        outAddresses.push_back(tempAddr);
                    }
                }
            }
        }
        freeaddrinfo(res);

        return bIsFound ? ResultCode::SUCCESS : ResultCode::FAIL;
    }

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP/IP Network Address information
	//

	NetAddress::NetAddress(const sockaddr_in& sockAddr)
	{
		Address[0] = '\0';
		*this = sockAddr;
	}

	NetAddress::NetAddress(const sockaddr_in6& sockAddr)
	{
		Address[0] = '\0';
		*this = sockAddr;
	}

	NetAddress::NetAddress(const sockaddr_storage& sockAddr)
	{
		Address[0] = '\0';
		*this = sockAddr;
	}

	NetAddress::NetAddress(SockFamily sockFamily, const char* strAdr, uint16_t port)
		: Port(port)
		, SocketFamily(sockFamily)
	{
		AssertRel(strAdr);
		StrUtil::StringCopy(Address, strAdr);
	}

	
	
	NetAddress::NetAddress(const char* strAdr, uint16_t port)
		: Port(port)
	{
		FromString(strAdr, port);
	}

	NetAddress::NetAddress(const char* strAddress)
	{
		FromString(strAddress);
	}

	void NetAddress::FromString(const char* strAddress)
	{
		Assert(strAddress);
		if (StrUtil::IsNullOrEmpty(strAddress))
		{
			Address[0] = '\0';
			Port = 0;
			SocketFamily = SockFamily::None;
			return;
		}

		auto sepratorIndex = StrUtil::IndexofAnyFromBack(strAddress, ":,");
		if (sepratorIndex < 0)
		{
			// No Port
			FromString(strAddress, 0);
		}
		else
		{
            Port = (uint16_t)atoi(strAddress + sepratorIndex + 1);
            char tempAddress[128];
			StrUtil::StringCopy(tempAddress, strAddress);
            tempAddress[sepratorIndex] = '\0';

            return FromString(tempAddress, Port);
		}
	}

	void NetAddress::FromString(const char* strAddress, uint16_t port)
	{
		Assert(strAddress);
		if (StrUtil::IsNullOrEmpty(strAddress))
		{
			Address[0] = '\0';
			Port = 0;
			SocketFamily = SockFamily::None;
			return;
		}

		Address[0] = '\0';
		//StrUtil::StringCopy(Address, strAddress);

		auto res = FindNumAddress(strAddress, SocketFamily, sizeof(Address), Address);
		if (!res)
		{
			SFLog(Net, Error, "Failed to parse net address:{0}, err:{1}", Address, res);
		}

		Port = port;
	}


	//NetAddress::NetAddress(int iVal)
	//	: SocketFamily(SockFamily::None)
	//	, Port(0)
	//{
	//	unused(iVal);
	//	memset(Address, 0, sizeof(Address));
	//}

	NetAddress::operator sockaddr_in() const
	{
		sockaddr_in sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(Port);
        if(StrUtil::IsNullOrEmpty(Address))
        {
            sockAddr.sin_addr.s_addr = INADDR_ANY;
        }
        else
        {
            int result = inet_pton(sockAddr.sin_family, Address, &sockAddr.sin_addr);
            if (result != TRUE)
            {
                assert(false);
            }
        }

		return sockAddr;
	}

	NetAddress::operator sockaddr_in6() const
	{
		sockaddr_in6 sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin6_family = AF_INET6;
		sockAddr.sin6_port = htons(Port);
        if(StrUtil::IsNullOrEmpty(Address))
        {
            sockAddr.sin6_addr = in6addr_any;
        }
        else
        {
            int result = inet_pton(sockAddr.sin6_family, Address, &sockAddr.sin6_addr);
            if (result != TRUE)
            {
                assert(false);
            }
        }

		return sockAddr;
	}

	NetAddress::operator sockaddr_storage() const
	{
		sockaddr_storage storage;
		if (SocketFamily == SockFamily::IPV6)
		{
			auto sockInfo = (sockaddr_in6)(*this);
			memcpy(&storage, &sockInfo, sizeof(sockInfo));
		}
		else
		{
			auto sockInfo = (sockaddr_in)(*this);
			memcpy(&storage, &sockInfo, sizeof(sockInfo));
		}

		return storage;
	}

    size_t NetAddress::GetSockAddrSize() const
    {
        return (SocketFamily == SockFamily::IPV6) ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);
    }

	NetAddress& NetAddress::operator = (const sockaddr_in& sockAddr)
	{
		Assert(sockAddr.sin_family == AF_INET);
		SocketFamily = SockFamily::IPV4;
		Address[0] = '\0';
		auto result = inet_ntop(sockAddr.sin_family, (void*)&sockAddr.sin_addr, Address, sizeof Address);
		if (result == nullptr)
		{
			assert(false);
			return *this;
		}
		Port = ntohs(sockAddr.sin_port);

		return *this;
	}

	NetAddress& NetAddress::operator = (const sockaddr_in6& sockAddr)
	{
		Assert(sockAddr.sin6_family == AF_INET6);
		SocketFamily = SockFamily::IPV6;
		Address[0] = '\0';
		auto result = inet_ntop(sockAddr.sin6_family, (void*)&sockAddr.sin6_addr, Address, sizeof Address);
		if (result == nullptr)
		{
			assert(false);
			return *this;
		}
		Port = ntohs(sockAddr.sin6_port);

		return *this;
	}

	NetAddress& NetAddress::operator = (const sockaddr_storage& sockAddr)
	{
		if (sockAddr.ss_family == AF_INET6)
		{
			return *this = (*(sockaddr_in6*)&sockAddr);
		}
		else if (sockAddr.ss_family == AF_INET)
		{
			return *this = (*(sockaddr_in*)&sockAddr);
		}
		else
		{
			// Not supported address family
			SocketFamily = SockFamily::None;
			Address[0] = '\0';
			Port = 0;
		}

		return *this;
	}

	NetAddress& NetAddress::operator = (const NetAddress& src)
	{
		SocketFamily = src.SocketFamily;
		memcpy(Address, src.Address, sizeof(src.Address));
		Port = src.Port;

		return *this;
	}

	bool NetAddress::operator == (const NetAddress& op) const
	{
		return strcmp(Address, op.Address) == 0 && Port == op.Port;
	}

	bool NetAddress::operator != (const NetAddress& op) const
	{
		return strcmp(Address, op.Address) != 0 || Port != op.Port;
	}



} // namespace SF



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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
#include "String/SFStrUtil.h"

#if SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID
#include <arpa/inet.h>
#endif

namespace SF {


	
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP/IP Network Address information
	//

	static Result SockAddrFromAddress(sockaddr_in6& sockAddr, const char *Address, uint16_t Port)
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

	static Result SockAddrFromAddress(sockaddr_in& sockAddr, const char *Address, uint16_t Port)
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

	
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP/IP Network Address information
	//

	NetAddress::NetAddress(const sockaddr_in& sockAddr)
		: Port(0)
		, SocketFamily(SockFamily::None)
	{
		Address[0] = '\0';
		*this = sockAddr;
	}

	NetAddress::NetAddress(const sockaddr_in6& sockAddr)
		: Port(0)
		, SocketFamily(SockFamily::None)
	{
		Address[0] = '\0';
		*this = sockAddr;
	}

	NetAddress::NetAddress(const sockaddr_storage& sockAddr)
		: Port(0)
		, SocketFamily(SockFamily::None)
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
		, SocketFamily(SockFamily::None)
	{
		Assert(strAdr);
		Address[0] = '\0';
		StrUtil::StringCopy(Address, strAdr);
		
		// Detect sock family
		sockaddr_storage sockAddr;
		auto result = SockAddrFromAddress(*(sockaddr_in6*)&sockAddr, Address, Port);
		if (!result)
		{
			result = SockAddrFromAddress(*(sockaddr_in*)&sockAddr, Address, Port);
			if(result)
			{
				SocketFamily = SockFamily::IPV4;
			}
			else
			{
				// invalid sock family
				Assert(false);
			}
		}
		else
		{
			SocketFamily = SockFamily::IPV6;
		}

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



} // namespace SF



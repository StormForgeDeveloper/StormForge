////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Result definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Container/SFArrayBase.h"
#include <stdint.h>


namespace SF
{

#pragma pack(push, 4)


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Address information
	//


	enum class SockFamily : uint8_t
	{
		None = 0,
		IPV4,// = AF_INET,
		IPV6,// = AF_INET6
        Quic,// = Quic
	};

	enum class SocketType : uint8_t
	{
		Stream,// = SOCK_STREAM,       // TCP
		DataGram,// = SOCK_DGRAM,     // UDP
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Address information
	//

	struct NetAddress
	{
		static constexpr int MAX_NETNAME = 70;

		char Address[MAX_NETNAME] = {};
		uint16_t Port = 0;
		SockFamily SocketFamily = SockFamily::None;

		NetAddress() = default;
		NetAddress(SockFamily sockFamily, const char* strAdr, uint16_t port = 0);
		NetAddress(const char* strAdr);
		NetAddress(const char* strAdr, uint16_t port);
		NetAddress(const sockaddr_in& sockAddr);
		NetAddress(const sockaddr_in6& sockAddr);
		NetAddress(const sockaddr_storage& sockAddr);


		void FromString(const char* strAddress);
		void FromString(const char* strAddress, uint16_t port);

        // Parse name address to NetAddresses
        static Result ParseNameAddress(const char* strAddress, Array<NetAddress>& outAddresses);

		explicit operator sockaddr_in() const;
		explicit operator sockaddr_in6() const;
		explicit operator sockaddr_storage() const;

		// sizeof(sockaddr_in) for IPV4, and sizeof(sockaddr_in6) for IPV6 socket
		size_t GetSockAddrSize() const;

		NetAddress& operator = (const sockaddr_in& sockAddr);
		NetAddress& operator = (const sockaddr_in6& sockAddr);
		NetAddress& operator = (const sockaddr_storage& sockAddr);
		NetAddress& operator = (const NetAddress& src);

		bool operator == (const NetAddress& op) const;
		bool operator != (const NetAddress& op) const;
	};

#pragma pack(pop)

}

template <>
struct std::formatter<SF::SockFamily>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::SockFamily& value, FormatContext& ctx) const
    {
        static const char* Names[] = {
            "None",
            "IPV4",// = AF_INET,
            "IPV6",// = AF_INET6
            "Quic",// = Quic
        };

        constexpr int MaxNames = sizeof(Names)/sizeof(Names[0]);

        return std::format_to(ctx.out(), "{}", Names[std::clamp<int>((int)value, 0, MaxNames)]);
    }
};

template <>
struct std::formatter<SF::SocketType>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::SocketType& value, FormatContext& ctx) const
    {
        static const char* Names[] = {
            "Stream",
            "DGram"
        };
        constexpr int MaxNames = sizeof(Names) / sizeof(Names[0]);

        return std::format_to(ctx.out(), "{}", Names[std::clamp<int>((int)value, 0, MaxNames)]);
    }
};

template <>
struct std::formatter<SF::NetAddress>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::NetAddress& value, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "({}:{},{})", value.SocketFamily, value.Address, value.Port);
    }
};

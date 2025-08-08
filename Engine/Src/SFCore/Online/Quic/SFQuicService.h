////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Quic service
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Service/SFService.h"


struct QUIC_API_TABLE;
typedef struct QUIC_HANDLE* HQUIC;
struct QUIC_BUFFER;


namespace SF {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	QuicService
	//

	class IQuicService
	{
	public:
        virtual const QUIC_API_TABLE* GetQuic() const { return nullptr; }
        virtual HQUIC GetRegistration() const { return nullptr; }
        virtual HQUIC GetConfiguration(const String& configurationName) const { return nullptr; }
        virtual const QUIC_BUFFER* GetAlpnBuffers(size_t& outNumAlpn) const { outNumAlpn = 0; return nullptr; }

        static Result QuicStatusToResult(uint32_t statusCode);
	};

    namespace Log
    {
        extern LogChannel Quic;
    }

    namespace Service
    {
        extern ServiceInstance<IQuicService> Quic;
    }

}//namespace SF 



template <>
struct std::formatter<HQUIC>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const HQUIC value, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}", (void*)value);
    }
};



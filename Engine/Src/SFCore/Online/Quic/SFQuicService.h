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






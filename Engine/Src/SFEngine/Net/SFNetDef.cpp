////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Network base type definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Util/SFTimeUtil.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSystem.h"
#include "Service/SFEngineService.h"



namespace SF {


	EndpointAddress& EndpointAddress::operator = (const EndpointAddress& src)
	{
		MessageServer = src.MessageServer;
		Channel = src.Channel;

		return *this;
	}

	EndpointAddress& EndpointAddress::operator = (const char* srcAddress)
	{
		if (StrUtil::IsNullOrEmpty(srcAddress))
		{
			MessageServer = "";
			Channel = "";
			return *this;
		}

		auto splitIndex = StrUtil::Indexof(srcAddress, '/');
		if (splitIndex < 0)
		{
            // Assuming that no channel is assigned
			MessageServer = srcAddress;
			Channel = "";
			return *this;
		}

		String MessageEndpointrString = srcAddress;
		MessageServer = MessageEndpointrString.SubString(0, splitIndex);
		Channel = MessageEndpointrString.SubString(splitIndex + 1, (int)MessageEndpointrString.length());

		return *this;
	}

} // namespace SF


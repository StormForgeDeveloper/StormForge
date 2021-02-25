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
namespace Net {




	////////////////////////////////////////////////////////////////////////////////
	//
	//	IConnectionEventHandler Interface
	//

	IConnectionEventHandler::~IConnectionEventHandler()
	{

	}

	Result IConnectionEventHandler::OnNetSyncMessage(Connection* pConn)
	{
		unused(pConn);
		Assert(false);
		return ResultCode::NOT_IMPLEMENTED;
	};


	// Net send message
	Result IConnectionEventHandler::OnNetSendReadyMessage(Connection* pConn)
	{
		unused(pConn);
		Assert(false);
		return ResultCode::NOT_IMPLEMENTED;
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Interface
	//





} // namespace Net


	EndpointAddress& EndpointAddress::operator = (const EndpointAddress& src)
	{
		MessageServer = src.MessageServer;
		Channel = src.Channel;

		return *this;
	}

	EndpointAddress& EndpointAddress::operator = (const char* srcAddress)
	{
		if (srcAddress == nullptr)
		{
			MessageServer = "";
			Channel = "";
			return *this;
		}

		auto splitIndex = StrUtil::Indexof(srcAddress, '/');
		if (splitIndex < 0)
		{
			SFLog(Net, Error, "EndpointAddress parsing has failed {0}", srcAddress);
			MessageServer = "";
			Channel = "";
			return *this;
		}

		String MessageEndpointrString = srcAddress;
		MessageServer = MessageEndpointrString.SubString(0, splitIndex);
		Channel = MessageEndpointrString.SubString(splitIndex + 1, MessageEndpointrString.length());

		return *this;
	}



} // namespace SF


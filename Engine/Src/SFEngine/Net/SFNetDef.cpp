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
} // namespace SF


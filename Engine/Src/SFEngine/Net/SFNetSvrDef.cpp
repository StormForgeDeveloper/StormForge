////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net server base type inline
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFNetSvrDef.h"
#include "Service/SFEngineService.h"



namespace SF {
namespace Net {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server network base interface
	//

	ServerNet::ServerNet(IHeap& heap, ServerID InServerID, NetClass localClass )
		: EngineObject(new(heap) IHeap("ServerNet", &heap), "ServerNet")
		, m_LocalClass(localClass)
		, m_ServerID(InServerID)
		, m_IsEnableAccept(false)
	{
		memset( &m_LocalAddr, 0, sizeof(m_LocalAddr) );
		memset( &m_LocalSockAddr, 0, sizeof(m_LocalSockAddr) );
	}

	ServerNet::~ServerNet()
	{
		// I created IHeap manually, so I need to check manually
		GetHeap().ReportLeak();
	}


	// change status of new connection allowance 
	void ServerNet::SetIsEnableAccept(bool bIsEnable)
	{
		m_IsEnableAccept = bIsEnable;
	}

	void ServerNet::SetNewConnectionhandler(std::function<void(ConnectionPtr&)> handler)
	{
		m_NewConnectionhandler = handler;
	}

	// check about initialize
	bool ServerNet::IsReady()
	{
		return GetSocket() != INVALID_SOCKET;
	}


	// Open host and start listen
	Result ServerNet::HostOpen(NetClass netCls, const char *strLocalIP, uint16_t usLocalPort)
	{
		Result hr = ResultCode::SUCCESS;
		NetAddress localAddr;

		SetNetClass(netCls);

		netChk(SetLocalNetAddress(localAddr, strLocalIP, usLocalPort));

		SetLocalAddress(localAddr);

	Proc_End:

		return hr;
	}


	// Close host and close all connections
	Result ServerNet::HostClose()
	{
		Result hr = ResultCode::SUCCESS;

		if(GetSocketIO() != nullptr)
			GetSocketIO()->CloseSocket();

		//Proc_End:

		return hr;
	}

	
} // namespace Net
} // namespace SF



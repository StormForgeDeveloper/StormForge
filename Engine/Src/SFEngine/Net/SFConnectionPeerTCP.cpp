////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TCP Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "Util/SFTimeUtil.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Util/SFLog.h"
#include "Util/SFStrUtil.h"
#include "Util/SFToString.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFConnection.h"
#include "Net/SFConnectionTCP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"





// define if emulate packet loss
//#ifdef _DEBUG
//#define UDP_PACKETLOS_EMULATE
//#endif


#ifdef UDP_PACKETLOS_EMULATE
	#define UDP_PACKETLOS_RATE	5
	#define UDP_PACKETLOS_BOUND	1
#endif // #ifdef UDP_PACKETLOS_EMULATE



namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Network client connection class
	//

	// Constructor
	ConnectionPeerTCP::ConnectionPeerTCP(IHeap& heap)
		: ConnectionTCP(heap)
	{
		//GetRecvBuffer()->SetupRecvTCP( GetCID() );
		SetHeartbeatTry(Const::SVR_HEARTBEAT_TIME_PEER);
		SetConnectingTimeOut(Const::SVR_CONNECTION_TIMEOUT);

		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::CONNECTING, &m_SendConnect);
		AddStateAction(ConnectionState::CONNECTED, &m_TimeoutHeartbeat);
		AddStateAction(ConnectionState::CONNECTED, &m_SendHeartbeat);
		AddStateAction(ConnectionState::DISCONNECTING, &m_TimeoutDisconnecting);
		AddStateAction(ConnectionState::DISCONNECTING, &m_SendDisconnect);
	}

	ConnectionPeerTCP::~ConnectionPeerTCP()
	{
	}

	void ConnectionPeerTCP::OnConnectionResult(Result hrConnect)
	{
		if ((hrConnect))
		{
			Assert(GetRemoteInfo().PeerID != 0);
		}

		return ConnectionTCP::OnConnectionResult(hrConnect);
	}

	// Update net control, process connection heartbeat, ... etc
	Result ConnectionPeerTCP::TickUpdate()
	{
		Result hr = ResultCode::SUCCESS;
		super::TickUpdate();

		// TODO: clean up after test
		//Message::MessageID msgIDTem;
		//TimeStampMS ulTimeCur = Util::Time.GetTimeMs();


	//	// On client side, we need to check readable/writable status by calling connect again
	//	if (m_IsClientConnection && !m_IsTCPSocketConnectionEstablished && GetConnectionState() == ConnectionState::CONNECTING)
	//	{
	//		m_IsTCPSocketConnectionEstablished = Connect();
	//	}


	//	if (m_IsTCPSocketConnectionEstablished
	//		&& GetMyNetIOAdapter().GetPendingRecvCount() == 0
	//		&& GetConnectionState() != ConnectionState::DISCONNECTED)
	//	{
	//		if (GetNetIOHandler() != nullptr)
	//		{
	//			hr = GetNetIOHandler()->PendingRecv();
	//			if (hr == ResultCode::IO_NOTCONN)
	//			{
	//				SFLog(Net, Info, "Connection not connected CID:{0}", GetCID());
	//				CloseConnection("Can't recv if not connected");
	//			}
	//		}
	//	}
	//	// connect/disconnect process
	//	msgIDTem.ID = PACKET_NETCTRL_NONE;
	//	switch (GetConnectionState())
	//	{
	//	case ConnectionState::CONNECTING:
	//		if (Util::TimeSince(m_ulNetCtrlTime) > GetConnectingTimeOut()) // connection time out
	//		{
	//			m_ulNetCtrlTryTime = ulTimeCur;
	//			SFLog(Net, Info, "Connecting Timeout CID:{0}", GetCID());
	//			netChk( CloseConnection("Connecting timeout") );
	//		}
	//		else if(Util::TimeSince(m_ulNetCtrlTryTime) > Const::CONNECTION_RETRY_TIME ) // retry
	//		{
	//			m_ulNetCtrlTryTime = ulTimeCur;
	//			Assert(GetLocalInfo().PeerClass != NetClass::Unknown);
	//			m_uiSendNetCtrlCount++;
	//			if (m_IsTCPSocketConnectionEstablished)
	//			{
	//				netChk(SendNetCtrl(PACKET_NETCTRL_CONNECT, (uint)GetLocalInfo().PeerClass, Message::MessageID(SF_PROTOCOL_VERSION), GetLocalInfo().PeerID));
	//			}
	//		}
	//		goto Proc_End;
	//		break;
	//	case ConnectionState::DISCONNECTING:
	//		if( (ulTimeCur-m_ulNetCtrlTime) > DurationMS(Const::DISCONNECT_TIMEOUT) ) // connection time out
	//		{
	//			m_ulNetCtrlTryTime = ulTimeCur;
	//			SFLog(Net, Info, "Disconnecting Timeout CID:{0}", GetCID());
	//			netChk( CloseConnection("Disconnecting") );
	//		}

	//		goto Proc_End;
	//		break;
	//	case ConnectionState::CONNECTED:
	//		if(Util::TimeSince(m_ulNetCtrlTime) > Const::HEARTBEAT_TIMEOUT ) // connection time out
	//		{
	//			m_ulNetCtrlTime = ulTimeCur;
	//			SFLog(Net, Info, "Connection Timeout CID:{0}", GetCID());

	//			netChk( CloseConnection("Net Heartbeat timeout") );
	//			goto Proc_End;
	//		}
	//		else if( (ulTimeCur-m_ulNetCtrlTryTime) > DurationMS(GetHeartbeatTry()) ) // heartbeat time
	//		{
	//			m_ulNetCtrlTryTime = ulTimeCur;
	//			if (m_IsTCPSocketConnectionEstablished)
	//			{
	//				netChk(SendNetCtrl(PACKET_NETCTRL_HEARTBEAT, 0, msgIDTem));
	//			}
	//		}
	//		break;
	//	default:
	//		break;
	//	};


	//Proc_End:


		return hr;
	}




} // namespace Net
} // namespace SF



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
#include "SFProtocol.h"

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
	ConnectionPeerTCP::ConnectionPeerTCP()
		: ConnectionTCP()
	{
		//GetRecvBuffer()->SetupRecvTCP( GetCID() );
		SetConnectingTimeOut(Const::SVR_CONNECTION_TIMEOUT);

		AddStateAction(ConnectionState::CONNECTING, &m_TimeoutConnecting);
		AddStateAction(ConnectionState::CONNECTING, &m_SendConnect);
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

} // namespace Net
} // namespace SF

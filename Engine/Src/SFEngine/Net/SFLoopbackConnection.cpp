////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Loopback fake connection
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "String/SFToString.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Protocol/SFProtocol.h"

#include "Util/SFUtility.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"

#include "Net/SFNetConst.h"
#include "Net/SFLoopbackConnection.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetToString.h"





namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network LoopbackConnection base class
	//


	LoopbackConnection::LoopbackConnection()
		: Connection(GetSystemHeap(), &m_NetIOAdapter)
		, m_NetIOAdapter(GetHeap())
	{
	}

	LoopbackConnection::~LoopbackConnection()
	{
	}



	// Initialize LoopbackConnection
	Result LoopbackConnection::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		Result hr = ResultCode::SUCCESS;

		Assert(GetConnectionState() == ConnectionState::DISCONNECTED);

		if (GetConnectionState() != ConnectionState::DISCONNECTED)
			netChk( CloseConnection("Cleanup for InitConnection") );

		netChk(Connection::InitConnection(local, remote));

		SetConnectionState(ConnectionState::CONNECTED);

		EnqueueConnectionEvent( ConnectionEvent( ConnectionEvent::EVT_CONNECTION_RESULT, ResultCode::SUCCESS)  );
		EnqueueConnectionEvent( ConnectionEvent( ConnectionEvent::EVT_STATE_CHANGE, GetConnectionState())  );

		SFLog(Net, Info, "Initialize LoopbackConnection CID:{0}, Addr:{1}", GetCID(), GetRemoteInfo().PeerAddress );

	Proc_End:

		return hr;
	}

	// Disconnect LoopbackConnection
	Result LoopbackConnection::Disconnect(const char* reason)
	{
		unused(reason);
		// cant disconnected
		return ResultCode::SUCCESS;
	}


	// Close LoopbackConnection
	Result LoopbackConnection::CloseConnection(const char* reason)
	{
		// cant closed
		return ResultCode::SUCCESS;
	}






} // namespace Net
} // namespace SF



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFToString.h"
#include "Util/SFHasher32.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFConnectionMUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetToString.h"



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
		//	Server Mobile UDP Network connection class
		//


		// Constructor
		ConnectionMUDP::ConnectionMUDP(IHeap& heap, SocketIO* ioHandler)
			: ConnectionUDPBase(heap, ioHandler)
		{
			// limit server net retry maximum
			SetMaxGuarantedRetry(Const::UDP_CLI_RETRY_ONETIME_MAX);
			SetUsePeerIDMap(true);
		}

		ConnectionMUDP::~ConnectionMUDP()
		{
		}


		// gathering
		Result ConnectionMUDP::SendPending(uint uiCtrlCode, uint uiSequence, MessageID msgID, uint64_t UID)
		{
			ScopeContext hr;

			netCheck(PrepareGatheringBuffer(sizeof(MsgNetCtrlBuffer)));

            MsgNetCtrlBuffer* pCtlBuffer = reinterpret_cast<MsgNetCtrlBuffer*>(m_pGatheringBuffer + m_uiGatheredSize);
            pCtlBuffer->Header.msgID.ID = uiCtrlCode;
            pCtlBuffer->Header.msgID.SetSequence(uiSequence);
            pCtlBuffer->Header.SetPeerID(UID == 0 ? GetLocalInfo().PeerID : UID);
            pCtlBuffer->GetNetCtrl().rtnMsgID = msgID;
            pCtlBuffer->UpdateMessageDataSize();

            if (uiCtrlCode == PACKET_NETCTRL_CONNECT || msgID.GetMsgIDOnly() == PACKET_NETCTRL_CONNECT)
            {
                MsgNetCtrlConnect* pConMsg = static_cast<MsgNetCtrlConnect*>(&pCtlBuffer->GetNetCtrl());
                pConMsg->Peer = GetLocalInfo();
            }

            pCtlBuffer->Header.Crc32 = Hasher_Crc32().Crc32(0, (uint8_t*)&pCtlBuffer->GetNetCtrl(), sizeof(MsgNetCtrl));
			if (pCtlBuffer->Header.Crc32 == 0) pCtlBuffer->Header.Crc32 = ~pCtlBuffer->Header.Crc32;

			m_uiGatheredSize += pCtlBuffer->Header.Length;

			return hr;
		}

		Result ConnectionMUDP::SendSync(uint uiSequence, uint64_t uiSyncMask)
		{
			ScopeContext hr;

			netCheck(PrepareGatheringBuffer(Message::MobileHeaderSize + sizeof(MsgMobileNetCtrlSync)));

            MsgNetCtrlBuffer* pCtlBuffer = reinterpret_cast<MsgNetCtrlBuffer*>(m_pGatheringBuffer + m_uiGatheredSize);
            pCtlBuffer->Header.msgID.ID = PACKET_NETCTRL_SYNCRELIABLE;
            pCtlBuffer->Header.msgID.SetSequence(uiSequence);
            pCtlBuffer->Header.SetPeerID(GetLocalInfo().PeerID);
            pCtlBuffer->UpdateMessageDataSize();

            MsgMobileNetCtrlSync* pSync = static_cast<MsgMobileNetCtrlSync*>(pCtlBuffer->Header.GetDataPtr());
            pSync->MessageMask = uiSyncMask;

            pCtlBuffer->Header.Crc32 = Hasher_Crc32().Crc32(0, (uint8_t*)&pCtlBuffer->GetNetCtrl(), sizeof(MsgNetCtrl));
            if (pCtlBuffer->Header.Crc32 == 0) pCtlBuffer->Header.Crc32 = ~pCtlBuffer->Header.Crc32;

            m_uiGatheredSize += pCtlBuffer->Header.Length;

			return hr;
		}


		// Update net control, process connection heartbeat, ... etc
		Result ConnectionMUDP::TickUpdate()
		{
			Result hr = ResultCode::SUCCESS;
			MessageID msgIDTem;

			MutexScopeLock scopeLock(GetUpdateLock());

			hr = super::TickUpdate();


			SendFlush();

			return hr;
		}



	} // namespace Net
} // namespace SF


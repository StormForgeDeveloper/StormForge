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
		Result ConnectionMUDP::SendPending(uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID)
		{
			ScopeContext hr;

			MsgNetCtrl* pNetCtrlMsg = nullptr;

			netCheck(PrepareGatheringBuffer(sizeof(MsgNetCtrlBuffer)));

			pNetCtrlMsg = (MsgNetCtrl*)(m_pGatheringBuffer + m_uiGatheredSize);
			pNetCtrlMsg->msgID.ID = uiCtrlCode;
			pNetCtrlMsg->msgID.SetSequence(uiSequence);
			pNetCtrlMsg->rtnMsgID = msgID;
			pNetCtrlMsg->PeerID = UID == 0 ? GetLocalInfo().PeerID : UID;

			pNetCtrlMsg->msgID.IDs.Mobile = true;
			pNetCtrlMsg->Length = sizeof(MsgNetCtrl);

			pNetCtrlMsg->Crc32 = Hasher_Crc32().Crc32(0, (uint8_t*)pNetCtrlMsg + sizeof(Message::MobileMessageHeader), sizeof(MsgNetCtrl) - sizeof(Message::MobileMessageHeader));
			if (pNetCtrlMsg->Crc32 == 0) pNetCtrlMsg->Crc32 = ~pNetCtrlMsg->Crc32;

			m_uiGatheredSize += pNetCtrlMsg->Length;

			return hr;
		}

		Result ConnectionMUDP::SendSync(uint uiSequence, uint64_t uiSyncMask)
		{
			ScopeContext hr;
			MsgMobileNetCtrlSync* pNetCtrlMsg = nullptr;

			netCheck(PrepareGatheringBuffer(sizeof(MsgMobileNetCtrlSync)));

			pNetCtrlMsg = (MsgMobileNetCtrlSync*)(m_pGatheringBuffer + m_uiGatheredSize);
			pNetCtrlMsg->msgID = PACKET_NETCTRL_SYNCRELIABLE;
			pNetCtrlMsg->msgID.SetSequence(uiSequence);
			pNetCtrlMsg->MessageMask = uiSyncMask;
			pNetCtrlMsg->PeerID = GetLocalInfo().PeerID;

			pNetCtrlMsg->msgID.IDs.Mobile = true;
			pNetCtrlMsg->Length = sizeof(MsgMobileNetCtrlSync);

			pNetCtrlMsg->Crc32 = Hasher_Crc32().Crc32(0, (uint8_t*)pNetCtrlMsg + sizeof(Message::MobileMessageHeader), sizeof(MsgMobileNetCtrlSync) - sizeof(Message::MobileMessageHeader));
			if (pNetCtrlMsg->Crc32 == 0) pNetCtrlMsg->Crc32 = ~pNetCtrlMsg->Crc32;

			//AssertRel(m_RecvReliableWindow.GetBaseSequence() != 1 && uiSequence != 1 || uiSyncMask == 0);
			SFLog(Net, Debug2, "NetCtrl Send MyRecvMask : CID:{0} mySeq:{1}, mask:{2:X8}",
				GetCID(), uiSequence, uiSyncMask);

			m_uiGatheredSize += pNetCtrlMsg->Length;

			return hr;
		}


		// Update net control, process connection heartbeat, ... etc
		Result ConnectionMUDP::TickUpdate()
		{
			Result hr = ResultCode::SUCCESS;
			Message::MessageID msgIDTem;

			MutexScopeLock scopeLock(GetUpdateLock());

			hr = super::TickUpdate();


			SendFlush();

			return hr;
		}



	} // namespace Net
} // namespace SF


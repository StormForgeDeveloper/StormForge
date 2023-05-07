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

            m_bIncludePacketHeader = true;
            m_uiMinGatherSizeForFlush = sizeof(PacketHeader);
		}

		ConnectionMUDP::~ConnectionMUDP()
		{
		}

		Result ConnectionMUDP::SendSync(uint uiSequence, uint64_t uiSyncMask)
		{
            Result hr = ResultCode::SUCCESS;

            netCheck(PrepareGatheringBuffer(sizeof(MsgNetCtrlBuffer)));

            MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(m_pGatheringBuffer + m_uiGatheredSize);
            pHeader->Length = sizeof(MsgNetCtrlBuffer); // PrepareGatheringBuffer guarantees it has space
            netCheck(MakeNetCtrl(pHeader, PACKET_NETCTRL_SYNCRELIABLE, uiSequence, 0, uiSyncMask));

            //pHeader->msgID.ID = PACKET_NETCTRL_SYNCRELIABLE;
            //pHeader->msgID.SetSequence(uiSequence);

            //MsgMobileNetCtrlSync* pSync = static_cast<MsgMobileNetCtrlSync*>(pHeader->GetDataPtr());
            //pSync->MessageMask = uiSyncMask;
            //pHeader->Length = pHeader->GetHeaderSize() + sizeof(MsgNetCtrl);

            //pHeader->Crc32 = Hasher_Crc32().Crc32(0, (uint8_t*)pHeader->GetDataPtr(), pHeader->Length - pHeader->GetHeaderSize());
            //if (pHeader->Crc32 == 0) pHeader->Crc32 = ~pHeader->Crc32;

            m_uiGatheredSize += pHeader->Length;


            return hr;
		}


		// Update net control, process connection heartbeat, ... etc
		Result ConnectionMUDP::TickUpdate()
		{
			Result hr = ResultCode::SUCCESS;
			MessageID msgIDTem;

			MutexScopeLock scopeLock(GetUpdateLock());

			hr = super::TickUpdate();

			return hr;
		}

	} // namespace Net
} // namespace SF

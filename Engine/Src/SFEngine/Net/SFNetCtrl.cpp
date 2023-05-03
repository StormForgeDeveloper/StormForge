////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net message implementation
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFNetCtrl.h"



namespace SF {
namespace Net {

    void MsgNetCtrlBuffer::UpdateMessageDataSize()
    {
        if (Header.msgID.GetMsgIDOnly() == PACKET_NETCTRL_CONNECT || GetNetCtrl().rtnMsgID.GetMsgIDOnly() == PACKET_NETCTRL_CONNECT)
        {
            Header.Length = Header.GetHeaderSize() + sizeof(MsgNetCtrlConnect);
        }
        else if (Header.msgID.GetMsgIDOnly() == PACKET_NETCTRL_SYNCRELIABLE)
        {
            Header.Length = Header.GetHeaderSize() + sizeof(MsgMobileNetCtrlSync);
        }
        else
        {
            Header.Length = Header.GetHeaderSize() + sizeof(MsgNetCtrl);
        }
    }

} // namespace Net
} // namespace SF



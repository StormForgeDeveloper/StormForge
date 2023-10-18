////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network classes definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetCtrlIDs.h"
#include "Net/SFNetConst.h"




namespace SF {
namespace Net {

	class Connection;



#pragma pack(push, 4)


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network control Message base Header
	//

	struct MsgNetCtrl
	{
		MessageID	rtnMsgID;
	};


	struct MsgNetCtrlConnect
	{
        uint ProtocolVersion{};
		PeerInfo Peer;
	};

    struct MsgMobileNetCtrlSync
    {
        uint64_t	MessageMask;
    };

    struct MsgNetCtrlTimeSync
    {
        uint32_t ClientTimeStamp;
        uint32_t ServerTimeStamp;
    };

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network control Message base Header
	//

	// Just some big enough structure to contain all net ctrl type data
    // We use this only for possible biggest netctrl packet size check, and quick MsgNetCtrl access for ack
	struct MsgNetCtrlBuffer
	{
        MsgNetCtrlBuffer()
        {
            Header.Length = sizeof(MsgNetCtrlBuffer);
        }

        // header
        MessageHeader Header;

        // common and 
        MsgNetCtrl Ctrl;
        MsgNetCtrlConnect CtrlConnect;
	};


#pragma pack(2)
	struct MsgNetCtrlSequenceFrame
	{
        uint16_t SubframeId;
		uint16_t Offset;
		uint16_t ChunkSize;
		uint16_t TotalSize;
	};

#pragma pack(4)
    struct MsgNetExtQOS
    {
        uint16_t Offset;
        uint16_t ChunkSize;
        uint16_t TotalSize;
    };

    struct MsgNetExtStun
    {
        NetAddress ReturnAddr;
    };

    struct STUNPacket
    {
        MessageHeader Header;
        Net::MsgNetExtStun Payload;
    };


#pragma pack(pop)

} // namespace Net
} // namespace SF




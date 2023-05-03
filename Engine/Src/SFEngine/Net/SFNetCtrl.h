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


	struct MsgNetCtrlConnect : public MsgNetCtrl
	{
		PeerInfo Peer;
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network control Message base Header
	//

	struct MsgMobileNetCtrlSync
	{
		uint64_t	MessageMask;
	};

	// Just some big enough structure to contain all net ctrl type data
	struct MsgNetCtrlBuffer
	{
        // header
        MessageHeader Header;

        uint64_t Dummy;

        // biggest ctrl structure
        union {
            MsgNetCtrl Ctrl;
            MsgNetCtrlConnect CtrlConnect;
            MsgMobileNetCtrlSync CtrlSync;
        };

		MsgNetCtrlBuffer() { memset(this, 0, sizeof(MsgNetCtrlBuffer)); }
		MsgNetCtrlBuffer(const MsgNetCtrlBuffer& src) { memcpy(this, &src, sizeof(src)); }

        const MessageHeader& GetHeader() const { return Header; }
        MessageHeader& GetHeader() { return Header; }
        const MsgNetCtrl& GetNetCtrl() const { return *reinterpret_cast<MsgNetCtrl*>(reinterpret_cast<uintptr_t>(this) + Header.GetHeaderSize()); }
        MsgNetCtrl& GetNetCtrl() { return *reinterpret_cast<MsgNetCtrl*>(reinterpret_cast<uintptr_t>(this) + Header.GetHeaderSize()); }

        void UpdateMessageDataSize();

		MsgNetCtrlBuffer& operator = (const MsgNetCtrlBuffer& src)
        {
            memcpy(this, &src, sizeof(src));
            return *this;
        }

		bool operator == (const MsgNetCtrlBuffer& src) const
        {
            return Header.msgID.ID == src.Header.msgID.ID;
        }
		bool operator != (const MsgNetCtrlBuffer& src) const
        {
            return Header.msgID.ID != src.Header.msgID.ID;
        }
	};


#pragma pack(2)
	struct MsgNetCtrlSequenceFrame
	{
		uint16_t Offset;
		uint16_t ChunkSize;
		uint16_t TotalSize;
	};

#pragma pack(pop)

} // namespace Net
} // namespace SF




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



#pragma pack(push)
#pragma pack(4)


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network control Message base Header
	//

	struct MsgNetCtrl : public Message::MobileMessageHeader
	{
		Message::MessageID	rtnMsgID;
	};


	struct MsgNetCtrlConnect : public MsgNetCtrl
	{
		PeerInfo Peer;
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network control Message base Header
	//

	typedef MsgNetCtrl MsgMobileNetCtrl;

	struct MsgMobileNetCtrlSync : public Message::MobileMessageHeader
	{
		uint64_t	MessageMask;
	};


	// Just some big enough structure to contain all net ctrl type data
	typedef struct tag_MsgNetCtrlBuffer : public MsgNetCtrlConnect
	{
		uint64_t	Dummy;

		tag_MsgNetCtrlBuffer() { msgID.ID = 0; }
		tag_MsgNetCtrlBuffer(void* ptr) { assert(ptr == nullptr); msgID.ID = 0; }
		tag_MsgNetCtrlBuffer(const tag_MsgNetCtrlBuffer& src) { memcpy(this, &src, sizeof(src)); }

		tag_MsgNetCtrlBuffer& operator = (const tag_MsgNetCtrlBuffer& src);

		bool operator == (const tag_MsgNetCtrlBuffer& src) const;
		bool operator != (const tag_MsgNetCtrlBuffer& src) const;
	} MsgNetCtrlBuffer;


	struct MsgMobileNetCtrlSequenceFrame : public Message::MobileMessageHeader
	{
		uint32_t SubSequence	: 16;
		uint32_t TotalSize		: 16;

		void SetSubSeqNSize(uint32_t subSequence, uint32_t totalSize);
	};


#pragma pack(pop)


#include "SFNetCtrl.inl"

} // namespace Net
} // namespace SF




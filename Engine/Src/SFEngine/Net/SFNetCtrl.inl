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





inline tag_MsgNetCtrlBuffer& tag_MsgNetCtrlBuffer::operator = ( const tag_MsgNetCtrlBuffer& src )
{
	memcpy( this, &src, sizeof(src) );
	return *this;
}

inline bool tag_MsgNetCtrlBuffer::operator == ( const tag_MsgNetCtrlBuffer& src ) const
{
	return msgID.ID == src.msgID.ID;
}

inline bool tag_MsgNetCtrlBuffer::operator != ( const tag_MsgNetCtrlBuffer& src ) const
{
	return msgID.ID != src.msgID.ID;
}


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

inline void MsgMobileNetCtrlSequenceFrame::SetSubSeqNSize(uint32_t subSequence, uint32_t totalSize)
{
	SubSequence = subSequence;
	TotalSize = totalSize;
}


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


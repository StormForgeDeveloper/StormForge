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




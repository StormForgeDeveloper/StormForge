////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net base type definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
//
//	Message ID
//



MessageID::MessageID()
	:ID(0)
{
}

//MessageID::MessageID( const MessageID& src )
//	:ID(src.ID)
//{
//}

MessageID::MessageID( uint32_t uiID )
	:ID(uiID)
{
}

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

MessageID::MessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode )
{
	IDs.MsgCode = uiCode;
	IDs.Policy = uiPolicy;
	IDs.Mobile = uiMobility;
	IDs.Encrypted = 0;
	IDs.Reliability = uiReliability;
	IDs.Type = uiType;
	IDs.Sequence = 0;// uiSeq;
}

uint32_t MessageID::SetMessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode )
{
	IDs.MsgCode = uiCode;
	IDs.Policy = uiPolicy;
	IDs.Mobile = uiMobility;
	IDs.Encrypted = 0;
	IDs.Reliability = uiReliability;
	IDs.Type = uiType;
	IDs.Sequence = 0;// uiSeq;

	return ID;
}

inline void MessageID::SetSequence(uint sequence)
{
	IDSeq.Sequence = sequence;
}

// Only MsgID part, no sequence or length
inline uint MessageID::GetMsgID() const
{
	return IDSeq.MsgID;
}

MessageID::operator uint32_t() const
{
	return ID;
}

inline void MessageHeader::SetIDNLen(uint id, uint msgLen)
{
	msgID.ID = id;
	Length = msgLen;
}

inline INT SequenceDifference(uint seq1, uint seq2)
{
	const int SEQDIFF_MAX = NET_SEQUENCE_MASK >> 1;
	const int SEQDIFF_MIN = (-SEQDIFF_MAX - 1);

	//NET_SEQUEUCN_BITS
	seq1 = NET_SEQUENCE_MASK & seq1;
	seq2 = NET_SEQUENCE_MASK & seq2;
	auto diff = (INT)(seq1 - seq2);
	if (diff > SEQDIFF_MAX)
		diff -= NET_SEQUENCE_MASK + 1;
	else if (diff < SEQDIFF_MIN)
		diff += NET_SEQUENCE_MASK + 1;

	return diff;
}


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif



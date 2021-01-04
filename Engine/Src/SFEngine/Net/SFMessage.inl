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



#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

inline MessageID::MessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode )
{
	IDs.MsgCode = uiCode;
	IDs.Policy = uiPolicy;
	IDs.Mobile = uiMobility;
	IDs.Encrypted = 0;
	IDs.Reliability = uiReliability;
	IDs.Type = uiType;
	IDs.Sequence = 0;// uiSeq;
}

inline uint32_t MessageID::SetMessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode )
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

inline uint SequenceNormalize(uint seq)
{
	seq = NET_SEQUENCE_MASK & seq;

	return seq;
}


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif



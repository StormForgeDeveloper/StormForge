////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine Common type definitions
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {

	LocalUID::LocalUID()
		:UID(0)
	{
	}

	LocalUID::LocalUID(const LocalUID& src)
		: UID(src.UID)
	{
	}

	LocalUID::LocalUID(uint32_t time, uint32_t id)
		: Time(time), ID(id)
	{
	}

	LocalUID::LocalUID(uint64_t initValue)
		: UID(initValue)
	{
	}

	LocalUID& LocalUID::operator = (const LocalUID& src)
	{
		UID = src.UID;
		return *this;
	}

	bool LocalUID::operator == (const LocalUID& op) const
	{
		return UID == op.UID;
	}

	bool LocalUID::operator != (const LocalUID& op) const
	{
		return UID != op.UID;
	}

	LocalUID::operator uint64_t () const
	{
		return UID;
	}




	inline MatchingQueueTicket::MatchingQueueTicket()
		:QueueUID(0), QueueItemID(0)
	{
	}

	MatchingQueueTicket::MatchingQueueTicket(const MatchingQueueTicket& src)
		: QueueUID(src.QueueUID), QueueItemID(src.QueueItemID)
	{
	}

	MatchingQueueTicket::MatchingQueueTicket(EntityUID queueUID, LocalUID itemID)
	{
		QueueUID = queueUID;
		QueueItemID = itemID;
	}

	MatchingQueueTicket::MatchingQueueTicket(int initValue)
		:QueueUID(0), QueueItemID(0)
	{
	}

	MatchingQueueTicket& MatchingQueueTicket::operator = (const MatchingQueueTicket& src)
	{
		QueueUID = src.QueueUID;
		QueueItemID = src.QueueItemID;

		return *this;
	}

	bool MatchingQueueTicket::operator == (const MatchingQueueTicket& op) const
	{
		return QueueUID == op.QueueUID && QueueItemID == op.QueueItemID;
	}

	bool MatchingQueueTicket::operator != (const MatchingQueueTicket& op) const
	{
		return QueueUID != op.QueueUID || QueueItemID != op.QueueItemID;
	}


}

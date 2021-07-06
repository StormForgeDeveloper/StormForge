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


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Transaction ID
	//


	TransactionID::TransactionID()
		: Components()
	{
	}

	TransactionID::TransactionID(const TransactionID& transID)
		: Components(transID.Components)
	{
	}

	TransactionID::TransactionID(EntityID entityID, uint32_t transID)
		: Components(entityID, transID)
	{
	}

	TransactionID::TransactionID(Context context)
		: Components()
	{
		ID = context;
	}


	bool TransactionID::IsValid() const
	{
		TransactionID trans;
		return trans.ID != ID;
	}

	TransactionID& TransactionID::operator = (const TransactionID& transID)
	{
		ID = transID.ID;

		return *this;
	}

	bool TransactionID::operator != (const TransactionID& src) const
	{
		return ID != src.ID;
	}

	bool TransactionID::operator == (const TransactionID& src) const
	{
		return ID == src.ID;
	}







	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Entity local unique ID
	//


	EntityID::EntityID()
		:ID(0)
	{
	}

	EntityID::EntityID(const EntityUID& entityUID)
		: ID(entityUID.Components.EntID.ID)
	{
	}

	EntityID::EntityID(const EntityID& entityID)
		: ID(entityID.ID)
	{
	}

#if !defined(SWIG)
	EntityID::EntityID(EntityFaculty facultyID, uint32_t entityLID)
	{
		Components.FacultyID = (uint)facultyID;
		Components.EntityLID = entityLID & 0xFFFFFF; // to avoid wconversion warning
	}
#endif

	EntityID::EntityID(uint32_t uiID)
		:ID(uiID)
	{
	}

	EntityID& EntityID::operator = (const EntityID& entityID)
	{
		ID = entityID.ID;

		return *this;
	}


	EntityID::operator uint32_t() const
	{
		return (uint32_t)ID;
	}




	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Entity Universal unique ID
	//


	EntityUID& EntityUID::operator = (const EntityUID& entityUID)
	{
		UID = entityUID.UID;

		return *this;
	}

	bool EntityUID::operator == (const EntityUID& src) const
	{
		return UID == src.UID;
	}

	bool EntityUID::operator != (const EntityUID& src) const
	{
		return UID != src.UID;
	}

	EntityUID::operator Context() const
	{
		return (Context)UID;
	}



	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	RouteContext
	//

	RouteContext& RouteContext::operator = (const RouteContext& src)
	{
		memcpy(ContextValue, src.ContextValue, sizeof(ContextValue));
		return *this;
	}

	bool RouteContext::operator == (const RouteContext& routeContext) const
	{
		return ContextValue[0] == routeContext.ContextValue[0] && ContextValue[1] == routeContext.ContextValue[1];
	}



	// Get swaped context( From <==> To )
	RouteContext RouteContext::GetSwaped() const
	{
		return RouteContext(Components.To, Components.From);
	}




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
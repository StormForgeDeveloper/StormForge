////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net connection definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////
//
//	Network connection base class
//


inline ConnectionEvent& ConnectionEvent::operator =(const ConnectionEvent& src)
{
	memcpy(this, &src, sizeof(src));
	return *this;
}

inline bool ConnectionEvent::operator == (const ConnectionEvent& src) const
{
	if (src.Components.EventType != Components.EventType)
		return false;

	assert(Components.EventType != EVT_NONE); // who access this?

	return Components.hr == src.Components.hr;
}

inline bool ConnectionEvent::operator != (const ConnectionEvent& src) const
{
	return src.Components.EventType != Components.EventType || Components.hr != src.Components.hr;
}



// Get Connection info
inline const PeerInfo& Connection::GetLocalInfo() const
{
	return m_LocalInfo;
}

inline void Connection::SetLocalID(uint64_t newID)
{
	m_LocalInfo.PeerID = newID;
}

inline const PeerInfo& Connection::GetRemoteInfo() const
{
	return m_RemoteInfo;
}

inline PeerInfo& Connection::GetRemoteInfo()
{
	return m_RemoteInfo;
}

inline void Connection::SetRemoteID(uint64_t newID)
{
	m_RemoteInfo.PeerID = newID;
}

inline void Connection::SetRemoteInfo(NetClass newClass, uint64_t newID)
{
	m_RemoteInfo.SetInfo(newClass, newID);
}



// Get Connection ID
inline uint64_t Connection::GetCID() const
{
	return m_CID;
}

inline void Connection::ClearCID()
{
	m_CID = 0;
}

// Get connection state
inline const ConnectionState Connection::GetConnectionState() const
{
	return m_ConnectionState.load(std::memory_order_acquire);
}

// Set local class
inline void Connection::SetLocalClass(NetClass localClass)
{
	m_LocalInfo.PeerClass = localClass;
	m_LocalInfo.PeerID = (uint)(-1);
}


// User data
inline uint64_t Connection::GetUData()
{
	return m_UData;
}

inline void Connection::SetUData(uint64_t UData)
{
	m_UData = UData;
}

// Get connection time
inline TimeStampMS Connection::GetConnectionTime()
{
	return m_tConnectionTime;
}





inline CounterType Connection::GetConnectionEventCount()
{
	return m_EventQueue.size();
}



// Get remote address
inline const sockaddr_storage& Connection::GetRemoteSockAddr() const
{
	return m_sockAddrRemote;
}

inline int Connection::GetRemoteSockAddrSize() const
{
	return m_sockAddrRemote.ss_family == AF_INET6 ? (int)sizeof(sockaddr_in6) : (int)sizeof(sockaddr_in);
}


uint16_t Connection::NewSeqNone()
{
	return (uint16_t)(m_usSeqNone.fetch_add(1,std::memory_order_relaxed) + 1);
}

inline DurationMS Connection::GetConnectingTimeOut()
{
	return m_ulConnectingTimeOut;
}

inline void Connection::SetConnectingTimeOut(DurationMS ulConnectingTimeOut )
{
	m_ulConnectingTimeOut = ulConnectingTimeOut;
}


// Get zero recv count
uint32_t Connection::GetZeroRecvCount()
{
	return m_ulZeroLengthRecvCount;
}

void Connection::IncZeroRecvCount()
{
	m_ulZeroLengthRecvCount++;
}

void Connection::ResetZeroRecvCount()
{
	m_ulZeroLengthRecvCount = 0;
}





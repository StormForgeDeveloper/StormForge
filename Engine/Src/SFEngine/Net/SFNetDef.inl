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


inline PeerInfo::PeerInfo(NetClass Class, const NetAddress& Addr, uint64_t UID)
	: PeerAddress(Addr)
	, PeerClass(Class)
	, PeerID(UID)
{
}

inline PeerInfo::PeerInfo(NetClass Class, uint64_t UID)
	: PeerClass(Class)
	, PeerID(UID)
{

}

inline PeerInfo::PeerInfo(const NetAddress& Addr)
	: PeerAddress(Addr)
	, PeerClass(NetClass::Unknown)
	, PeerID(0)
{

}

inline void PeerInfo::SetInfo(NetClass Class, const NetAddress& Addr, uint64_t UID)
{
	PeerAddress = Addr;
	PeerClass = Class;
	PeerID = UID;
}

inline void PeerInfo::SetInfo(NetClass Class, uint64_t UID)
{
	PeerClass = Class;
	PeerID = UID;
}

inline bool PeerInfo::operator == (const PeerInfo& op) const
{
	return PeerAddress == op.PeerAddress
		&& PeerClass == op.PeerClass
		&& PeerID == op.PeerID;
}

inline bool PeerInfo::operator != (const PeerInfo& op) const
{
	return PeerAddress != op.PeerAddress
		|| PeerClass != op.PeerClass
		|| PeerID != op.PeerID;
}



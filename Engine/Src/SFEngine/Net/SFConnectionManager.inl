////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net connection Map. 
//	
//
////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ConnectionManager
//

inline uint ConnectionManager::NewCID()
{
	uint counter = m_CIDGen.NewID();

	AssertRel( counter < INT_MAX );// If got this assertion that will be some thing going wrong with connection manage

	return counter;
}

inline void ConnectionManager::FreeCID( uint uiCID )
{
	m_CIDGen.FreeID( uiCID );
}


// Active connection
inline CounterType ConnectionManager::GetNumActiveConnection()
{
	return m_AddrMap.size();
}



////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net message window inline implementation. 
//	
//
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//
//	Packet message Sorting Window class
//


// get window size
inline INT MsgWindow::GetWindowSize()
{
	return m_uiWndSize;
}

// get message count in window
inline uint MsgWindow::GetMsgCount()
{
	return m_uiMsgCount;
}

// get message base sequence
inline uint MsgWindow::GetBaseSequence()
{
	return m_uiBaseSequence;
}






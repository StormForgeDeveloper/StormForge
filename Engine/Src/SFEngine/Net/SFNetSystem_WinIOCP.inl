////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network system for IOCP
//	
//
////////////////////////////////////////////////////////////////////////////////








////////////////////////////////////////////////////////////////////////////////
//
//	Overlapped I/O structures
//



// Initialize for IO
void IOBUFFER_WRITE::InitForIO(SF_SOCKET sockWrite)
{
	pSendBuff = nullptr;

	unused(sockWrite);
	HANDLE hEventTemp = hEvent;
	memset( (IOBUFFER_RWBASE*)this, 0, sizeof(IOBUFFER_RWBASE) );
	hEvent = hEventTemp;
}

void IOBUFFER_WRITE::InitMsg(SharedPointerT<MessageData>&& pMsg )
{
	pMsgs = std::forward<SharedPointerT<MessageData>>(pMsg);
	pSendBuff = nullptr;
	TransferredSize = pMsgs->GetMessageSize();
	wsaBuff.len = pMsgs->GetMessageSize();
	wsaBuff.buf = (char*)pMsgs->GetMessageBuff();
}

void IOBUFFER_WRITE::InitBuff( uint uiBuffSize, uint8_t* pBuff )
{
	pMsgs = nullptr;
	TransferredSize = uiBuffSize;
	wsaBuff.len = uiBuffSize;
	wsaBuff.buf = (char*)pBuff;
	pSendBuff = pBuff;
}

void IOBUFFER_WRITE::SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, SharedPointerT<MessageData> &&pMsg )
{
	InitForIO(sockWrite);

	InitMsg(std::forward<SharedPointerT<MessageData>>(pMsg) );

	NetAddr.To = to;

	Operation = IOBUFFER_OPERATION::OP_UDPWRITE;
}

void IOBUFFER_WRITE::SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, uint uiBuffSize, uint8_t* pBuff )
{
	InitForIO(sockWrite);

	InitBuff( uiBuffSize, pBuff );

	NetAddr.To = to;

	Operation = IOBUFFER_OPERATION::OP_UDPWRITE;
}

void IOBUFFER_WRITE::SetupSendTCP( SharedPointerT<MessageData>&& pMsg )
{
	InitForIO(0);

	InitMsg(std::forward<SharedPointerT<MessageData>>(pMsg) );

	Operation = IOBUFFER_OPERATION::OP_TCPWRITE;
}

void IOBUFFER_WRITE::SetupSendTCP( uint uiBuffSize, uint8_t* pBuff )
{
	InitForIO(0);

	InitBuff( uiBuffSize, pBuff );

	Operation = IOBUFFER_OPERATION::OP_TCPWRITE;
}



// Initialize for IO
void IOBUFFER_READ::InitForIO()
{
	HANDLE hEventTemp = hEvent;
	memset( this, 0, sizeof(IOBUFFER_RWBASE) );
	hEvent = hEventTemp;

	dwFlags = 0;
	dwNumberOfByte = 0;
	CID = 0;
	Assert(!NetSystem::IsProactorSystem() || bIsPending.load(std::memory_order_acquire));

	iSockLen = sizeof(NetAddr.From);
}

void IOBUFFER_READ::InitRecv( uint64_t iCID )
{
	InitForIO();
	wsaBuff.len = sizeof(buffer);
	wsaBuff.buf = buffer;
#ifdef DEBUG
	memset(buffer,0xCE,sizeof(buffer));
#endif
	CID = iCID;
}

// Setup recving mode
void IOBUFFER_READ::SetupRecvUDP( uint64_t iCID )
{
	InitRecv( iCID );
	Operation = IOBUFFER_OPERATION::OP_UDPREAD;
}

void IOBUFFER_READ::SetupRecvTCP( uint64_t iCID )
{
	InitRecv( iCID );
	Operation = IOBUFFER_OPERATION::OP_TCPREAD;
}



////////////////////////////////////////////////////////////////////////////////
//
//	Accept overlapped
//


// Setup accept
void IOBUFFER_ACCEPT::SetupAccept(SF_SOCKET sock )
{
	Operation = IOBUFFER_OPERATION::OP_TCPACCEPT;
	sockAccept = sock;
}



////////////////////////////////////////////////////////////////////////////////
//
//	Network IOCP thread worker
//


void IOCPSystem::IOCPWorker::SetIOCPHandle( HANDLE hIOCP )
{
	m_hIOCP = hIOCP;
}









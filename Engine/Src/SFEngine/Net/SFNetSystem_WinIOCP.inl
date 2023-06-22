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
	//pSendBuff = nullptr;

	unused(sockWrite);
	HANDLE hEventTemp = hEvent;
	memset( (IOBUFFER_RWBASE*)this, 0, sizeof(IOBUFFER_RWBASE) );
	hEvent = hEventTemp;
}

void IOBUFFER_WRITE::InitBuff( uint uiBuffSize, uint8_t* pBuff )
{
    TransferredSize = 0;
    SendBufferSize = uiBuffSize;
	wsaBuff.len = uiBuffSize;
	wsaBuff.buf = (char*)pBuff;
}

void IOBUFFER_WRITE::SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, uint uiBuffSize, uint8_t* pBuff )
{
	InitForIO(sockWrite);

	InitBuff( uiBuffSize, pBuff );

	NetAddr.To = to;

	Operation = IOBUFFER_OPERATION::OP_UDPWRITE;
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
	wsaBuff.len = MaxPacketSize;
	wsaBuff.buf = (CHAR*)GetPayloadPtr();
#ifdef DEBUG
	memset(wsaBuff.buf,0xCE, wsaBuff.len);
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


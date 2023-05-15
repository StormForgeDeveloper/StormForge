////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2015 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network system linux shared
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
	//memset(this, 0, sizeof(IOBUFFER_WRITE));
	SockWrite = sockWrite;
	//RawSendSize = 0;
	//pRawSendBuffer = nullptr;
}

void IOBUFFER_WRITE::InitBuff(uint uiBuffSize, uint8_t* pBuff)
{
	RawSendSize = uiBuffSize;
	pRawSendBuffer = pBuff;
}

void IOBUFFER_WRITE::SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, uint uiBuffSize, uint8_t* pBuff)
{
	InitForIO(sockWrite);

	InitBuff(uiBuffSize, pBuff);

	NetAddr.To = to;

	Operation = IOBUFFER_OPERATION::OP_UDPWRITE;
}

void IOBUFFER_WRITE::SetupSendTCP(uint uiBuffSize, uint8_t* pBuff)
{
	InitForIO(0);

	InitBuff(uiBuffSize, pBuff);

	Operation = IOBUFFER_OPERATION::OP_TCPWRITE;
}



// Initialize for IO
void IOBUFFER_READ::InitForIO()
{
	memset(this, 0, sizeof(IOBUFFER_RWBASE));
	CID = 0;
	iSockLen = sizeof(NetAddr.From);
}

void IOBUFFER_READ::InitRecv(uint64_t iCID)
{
	InitForIO();
#ifdef DEBUG
	memset(GetPayloadPtr(), 0xCE, Const::INTER_PACKET_SIZE_MAX);
#endif
	CID = iCID;
}

// Setup recving mode
void IOBUFFER_READ::SetupRecvUDP(uint64_t iCID)
{
	InitRecv(iCID);
	Operation = IOBUFFER_OPERATION::OP_UDPREAD;
}

void IOBUFFER_READ::SetupRecvTCP(uint64_t iCID)
{
	InitRecv(iCID);
	Operation = IOBUFFER_OPERATION::OP_TCPREAD;
}



////////////////////////////////////////////////////////////////////////////////
//
//	Accept overlapped
//


// Setup accept
void IOBUFFER_ACCEPT::SetupAccept(SF_SOCKET sock)
{
	Operation = IOBUFFER_OPERATION::OP_TCPACCEPT;
	sockAccept = sock;
}






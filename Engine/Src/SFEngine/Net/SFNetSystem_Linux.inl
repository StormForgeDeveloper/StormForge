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
	RawSendSize = 0;
	pRawSendBuffer = nullptr;
	pMsgs = nullptr;
	pSendBuff = nullptr;
}

void IOBUFFER_WRITE::InitMsg(SharedPointerT<Message::MessageData>&& pMsg)
{
	pMsgs = std::forward<SharedPointerT<Message::MessageData>>(pMsg);
	pSendBuff = nullptr;

	RawSendSize = pMsgs->GetMessageSize();
	pRawSendBuffer = pMsgs->GetMessageBuff();
}

void IOBUFFER_WRITE::InitBuff(uint uiBuffSize, uint8_t* pBuff)
{
	pMsgs = nullptr;
	pSendBuff = pBuff;

	RawSendSize = uiBuffSize;
	pRawSendBuffer = pBuff;
}

void IOBUFFER_WRITE::SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, SharedPointerT<Message::MessageData>&& pMsg)
{
	InitForIO(sockWrite);

	InitMsg(std::forward<SharedPointerT<Message::MessageData>>(pMsg));

	NetAddr.To = to;

	Operation = IOBUFFER_OPERATION::OP_UDPWRITE;
}

void IOBUFFER_WRITE::SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, uint uiBuffSize, uint8_t* pBuff)
{
	InitForIO(sockWrite);

	InitBuff(uiBuffSize, pBuff);

	NetAddr.To = to;

	Operation = IOBUFFER_OPERATION::OP_UDPWRITE;
}

void IOBUFFER_WRITE::SetupSendTCP(SharedPointerT<Message::MessageData>&& pMsg)
{
	InitForIO(0);

	InitMsg(std::forward<SharedPointerT<Message::MessageData>>(pMsg));

	Operation = IOBUFFER_OPERATION::OP_TCPWRITE;
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
	memset(buffer, 0xCE, sizeof(buffer));
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






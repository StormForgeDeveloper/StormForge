////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Util/SFLog.h"
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFMemoryPool.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFHasher32.h"

#include "Net/SFMessage.h"
#include "Net/SFNetSystem.h"


template class SF::SharedPointerT<SF::MessageData>;


namespace SF
{
    const char* MessageID::GetNameString() const
    {
        // TODO:
        return nullptr;
    }

    //Result MessageHeader::ValidateChecksum()
    //{
    //    ArrayView<uint8_t> payload = GetPayload();

    //    if (Length == 0)
    //    {
    //        Assert(0);
    //        return ResultCode::FAIL;
    //    }

    //    // Nothing to check
    //    if (payload.size() == 0)
    //        return ResultCode::SUCCESS;

    //    uint16_t ExpectedCrc32 = (uint16_t)Hasher_Crc32().Crc32(0, payload.data(), payload.size());
    //    if (ExpectedCrc32 == 0) ExpectedCrc32 = ~ExpectedCrc32;

    //    if (ExpectedCrc32 != Crc32)
    //        return ResultCode::IO_INVALID_MESSAGE_CHECKSUM;

    //    return ResultCode::SUCCESS;
    //}

    //Result MessageHeader::ValidateChecksumNDecrypt()
    //{

    //    if (Length == 0)
    //    {
    //        return ResultCode::SUCCESS_FALSE;
    //    }

    //    ArrayView<uint8_t> payload = GetPayload();

    //    // Nothing to check
    //    if (payload.size() == 0)
    //    {
    //        return ResultCode::SUCCESS;
    //    }

    //    uint16_t ExpectedCrc32 = (uint16_t)Util::Crc32NDecrypt(payload.size(), payload.data());
    //    if (ExpectedCrc32 == 0) ExpectedCrc32 = ~ExpectedCrc32;

    //    if (ExpectedCrc32 != Crc32)
    //        return ResultCode::IO_INVALID_MESSAGE_CHECKSUM;

    //    return ResultCode::SUCCESS;
    //}

    //// Update checksum
    //void MessageHeader::UpdateChecksum()
    //{
    //    ArrayView<uint8_t> payload = GetPayload();

    //    if (Length == 0
    //        || payload.size() == 0)
    //    {
    //        Crc32 = 0;
    //        return;
    //    }
    //    else
    //    {
    //        Crc32 = Hasher_Crc32().Crc32(0, payload.data(), payload.size());
    //        if (Crc32 == 0)
    //            Crc32 = ~Crc32;
    //    }
    //}

    //// Update checksum
    //void MessageHeader::UpdateChecksumNEncrypt()
    //{
    //    ArrayView<uint8_t> payload = GetPayload();

    //    if (Length == 0
    //        || payload.size() == 0)
    //    {
    //        Crc32 = 0;
    //    }
    //    else
    //    {
    //        Crc32 = Util::Crc32NEncrypt(payload.size(), payload.data());
    //        if (Crc32 == 0)
    //            Crc32 = ~Crc32;
    //    }

    //    assert(Crc32 != 0 || payload.size() == 0);
    //}

    //MessageHeader* MessageHeader::Clone()
    //{
    //    MessageHeader* pNewHeader = reinterpret_cast<MessageHeader*>(heap.Alloc(Length));
    //    if (pNewHeader)
    //    {
    //        memcpy(pNewHeader, this, Length);
    //    }

    //    return pNewHeader;
    //}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message wrapper class
	//
	
	MessageData::MessageData(uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData)
		:m_bIsSequenceAssigned(false)
	{
        // we haver reserved space for packet header
        m_pPacketHeader = reinterpret_cast<PacketHeader*>(this + 1);
        m_pPacketHeader->PeerId = 0;

        // actual header offset
		m_pMsgHeader = (MessageHeader*)(m_pPacketHeader + 1);

		if( pData )
		{
			memcpy( m_pMsgHeader, pData, uiMsgBufSize );
			assert( m_pMsgHeader->MessageSize == uiMsgBufSize );
		}
		else
		{
			memset( GetMessageHeader(), 0, sizeof(MessageHeader) );
			// Make sure the sequence is cleared
			Assert(GetMessageHeader()->GetSequence() == 0);
		}

		GetMessageHeader()->SetIDNLen(uiMsgID, uiMsgBufSize);
	}


	MessageData::~MessageData()
	{
	}

	uint8_t* MessageData::GetMessageBuff()
	{
		return (uint8_t*)m_pMsgHeader;
	}

	uint MessageData::GetMessageSize() const
	{
		return m_pMsgHeader ? m_pMsgHeader->MessageSize : 0;
	}

	void MessageData::AssignSequence( uint sequence )
	{
		// sequence must not assigned twice
		Assert(m_bIsSequenceAssigned == false);
		m_bIsSequenceAssigned = true;

		GetMessageHeader()->SetSequence(sequence);
	}

	void MessageData::ClearAssignedSequence()
	{
		// sequence must not assigned twice
		m_bIsSequenceAssigned = false;

		GetMessageHeader()->SetSequence(0);
	}

    MessageData* MessageData::NewMessage(const MessageHeader* pHeader)
    {
        return NewMessage( pHeader->GetMessageIDForClone(), pHeader->MessageSize, reinterpret_cast<const uint8_t*>(pHeader));
    }

	// Initialize message buffer
	MessageData* MessageData::NewMessage(uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData )
	{
		uint8_t *pBuffer = nullptr;
		size_t szAllocate = sizeof(PacketHeader) + sizeof(MessageData) + uiMsgBufSize;

		if (uiMsgBufSize > MAX_MESSAGE_SIZE)
		{
			SFLog(Net, Error, "Too big message allocation request, over MAX_MESSAGE_SIZE, {0} is requested", uiMsgBufSize);
			return nullptr;
		}

		if (szAllocate > USHRT_MAX)
		{
			SFLog(Net, Error, "Too big message allocation request, over 64KB, {0} is requested", szAllocate);
			return nullptr;
		}

		void *pPtr = nullptr;
		pPtr = new uint8_t[szAllocate];
		if (pPtr == nullptr)
			return nullptr;

		pBuffer = static_cast<uint8_t*>(pPtr);
		if (pBuffer == nullptr)
			return nullptr;

		MessageData *pMsg = new(pBuffer) MessageData(uiMsgID, uiMsgBufSize, pData);

		return pMsg;
	}

	MessageData* MessageData::Clone()
	{
		if( m_pMsgHeader == nullptr || m_pMsgHeader->MessageSize == 0 )
			return nullptr;

		MessageData* pMessage = NewMessage(m_pMsgHeader->GetMessageID().ID, m_pMsgHeader->MessageSize, (uint8_t*)m_pMsgHeader );
		pMessage->GetMessageHeader()->SetSequence(0);

		return pMessage;
	}


    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //
    //

    MessageBase::MessageBase(const MessageHeader* pHeader)
        : m_pHeader(pHeader)
    {

    }

    MessageBase::MessageBase(const SharedPointerT<MessageData>& pIMsg)
        : m_pIMsg(pIMsg)
        , m_pHeader(pIMsg->GetMessageHeader())
    {
    }

	Result MessageBase::ParseMsg()
	{ 
		if(m_bHasParsed)
			return m_hrParsing;

        if (m_pHeader == nullptr)
            return ResultCode::INVALID_POINTER;

		m_bHasParsed = true;
		m_hrParsing = ParseMessage(m_pHeader);

		return m_hrParsing;
	}

} // SF

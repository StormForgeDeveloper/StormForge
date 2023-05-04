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


namespace SF {
	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message wrapper class
	//
	
	MessageData::MessageData(uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData)
		:m_bIsSequenceAssigned(false)
	{
        // we haver reserved space for packet header
        m_pPacketHeader = reinterpret_cast<MobilePacketHeader*>(this + 1);
        m_pPacketHeader->PeerId = 0;

        // actual header offset
		m_pMsgHeader = (MessageHeader*)(m_pPacketHeader + 1);

		if( pData )
		{
			memcpy( m_pMsgHeader, pData, uiMsgBufSize );
			assert( m_pMsgHeader->Length == uiMsgBufSize );
		}
		else
		{
			memset( GetMessageHeader(), 0, sizeof(MessageHeader) );
			// Make sure the sequence is cleared
			Assert(GetMessageHeader()->msgID.IDSeq.Sequence == 0);
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
		return m_pMsgHeader ? m_pMsgHeader->Length : 0;
	}



	void MessageData::AssignSequence( uint sequence )
	{
		// sequence must not assigned twice
		Assert(m_bIsSequenceAssigned == false);
		m_bIsSequenceAssigned = true;

		GetMessageHeader()->msgID.SetSequence(sequence);
	}

	void MessageData::GetRouteInfo(RouteContext& routeContext, TransactionID& transID)
	{
        ArrayView<uint8_t> payload = GetPayload();

		if (payload.size() < sizeof(RouteContext))
		{
			routeContext = {};
			transID = TransactionID();
			return;
		}

		auto pRouteContext = (RouteContext*)GetPayloadPtr();
		routeContext = *pRouteContext;

		if (payload.size() < (sizeof(RouteContext)+sizeof(TransactionID)))
		{
			transID = TransactionID();
			return;
		}

		transID = *(TransactionID*)(pRouteContext+1);
	}


	void MessageData::ClearAssignedSequence()
	{
		// sequence must not assigned twice
		m_bIsSequenceAssigned = false;

		GetMessageHeader()->msgID.IDSeq.Sequence = 0;
	}

	// Initialize message buffer
	MessageData* MessageData::NewMessage(IHeap& heap, uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData )
	{
		uint8_t *pBuffer = nullptr;
		size_t szAllocate = sizeof(MobilePacketHeader) + sizeof(MessageData) + uiMsgBufSize;

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
		pPtr = new(heap) uint8_t[szAllocate];
		if (pPtr == nullptr)
			return nullptr;

		pBuffer = static_cast<uint8_t*>(pPtr);
		if (pBuffer == nullptr)
			return nullptr;

		MessageData *pMsg = new(pBuffer) MessageData(uiMsgID, uiMsgBufSize, pData);

		return pMsg;
	}


	MessageData* MessageData::Clone(IHeap& memoryManager)
	{
		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
			return nullptr;

		MessageData* pMessage = NewMessage(memoryManager, m_pMsgHeader->msgID.ID, m_pMsgHeader->Length, (uint8_t*)m_pMsgHeader );
		pMessage->GetMessageHeader()->msgID.IDSeq.Sequence = 0;

		return pMessage;
	}

	// Update checksum
	void MessageData::UpdateChecksum()
	{
        ArrayView<uint8_t> payload = GetPayload();

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
			Assert(0);
			return;
		}

		if(payload.size() == 0 )
		{
			m_pMsgHeader->Crc32 = 0;
			return;
		}

		m_pMsgHeader->Crc32 = Hasher_Crc32().Crc32(0, payload.data(), payload.size());
		if( m_pMsgHeader->Crc32 == 0 )
			m_pMsgHeader->Crc32 = ~m_pMsgHeader->Crc32;
	}
	
	// Update checksum
	void MessageData::UpdateChecksumNEncrypt()
	{
        ArrayView<uint8_t> payload = GetPayload();

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
			Assert(0);
			return;
		}

		if(payload.size() == 0)
		{
			m_pMsgHeader->Crc32 = 0;
			return;
		}

		if(m_bIsEncrypted)
		{
			// skip if the message is already encrypted
			return;
		}

		m_pMsgHeader->Crc32 = Util::Crc32NEncrypt(payload.size(), payload.data());
		if( m_pMsgHeader->Crc32 == 0 )
			m_pMsgHeader->Crc32 = ~m_pMsgHeader->Crc32;

		assert( m_pMsgHeader->Crc32 != 0 || payload.size() == 0);

        m_bIsEncrypted = true;
	}

	Result MessageData::ValidateChecksum()
	{
        ArrayView<uint8_t> payload = GetPayload();

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
			Assert(0);
			return ResultCode::FAIL;
		}

		// Nothing to check
		if(payload.size() == 0)
			return ResultCode::SUCCESS;

		uint16_t Crc32 = (uint16_t)Hasher_Crc32().Crc32(0, payload.data(), payload.size());
		if( Crc32 == 0 ) Crc32 = ~Crc32;

		if( Crc32 != m_pMsgHeader->Crc32 )
			return ResultCode::IO_INVALID_MESSAGE_CHECKSUM;

		return ResultCode::SUCCESS;
	}
	
	Result MessageData::ValidateChecksumNDecrypt()
	{
        ArrayView<uint8_t> payload = GetPayload();

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
            m_bIsEncrypted = false;
			return ResultCode::SUCCESS_FALSE;
		}

		if(!m_bIsEncrypted)
		{
			return ValidateChecksum();
		}
		
		// Nothing to check
		if(payload.size() == 0)
		{
            m_bIsEncrypted = false;
			return ResultCode::SUCCESS;
		}

		uint16_t Crc32 = (uint16_t)Util::Crc32NDecrypt(payload.size(), payload.data());
		if( Crc32 == 0 ) Crc32 = ~Crc32;

        m_bIsEncrypted = false;

		//Assert(m_pMsgHeader->Crc32 != 0);
		if( Crc32 != m_pMsgHeader->Crc32 )
			return ResultCode::IO_INVALID_MESSAGE_CHECKSUM;

		return ResultCode::SUCCESS;
	}

	Result MessageBase::ParseMsg()
	{ 
		if(m_bHasParsed)
			return m_hrParsing;

		m_bHasParsed = true;
		m_hrParsing = ParseMessage(GetMessage());

		return m_hrParsing;
	}

} // SF

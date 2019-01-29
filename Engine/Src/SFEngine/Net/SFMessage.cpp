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
#include "Memory/SFMemory.h"
#include "Memory/SFMemoryPool.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "String/SFHasher32.h"

#include "Net/SFMessage.h"
#include "Net/SFNetSystem.h"


template class SF::SharedPointerT<SF::Message::MessageData>;


namespace SF {
namespace Message {
	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message wrapper class
	//
	
	MessageData::MessageData( uint uiMsgBufSize, const uint8_t* pData )
		:m_bIsSequenceAssigned(false)
	{
		m_pMsgHeader = (MessageHeader*)(this+1);

		if( pData )
		{
			memcpy( m_pMsgHeader, pData, uiMsgBufSize );
			AssertRel( m_pMsgHeader->Length == uiMsgBufSize );
		}
		else
		{
			memset( GetMessageHeader(), 0, sizeof(Message::MessageHeader) );
			// Make sure the sequence is cleared
			Assert(GetMessageHeader()->msgID.IDSeq.Sequence == 0);
		}
	}

	MessageData::~MessageData()
	{
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
		uint length = 0;
		uint8_t* pDataPtr = nullptr;
		GetLengthNDataPtr(length, pDataPtr);

		if (length < sizeof(RouteContext))
		{
			routeContext = 0;
			transID = TransactionID();
			return;
		}

		auto pRouteContext = (RouteContext*)GetMessageData();
		routeContext = *pRouteContext;


		if (length < (sizeof(RouteContext)+sizeof(TransactionID)))
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
		size_t szAllocate = sizeof(MessageData) + uiMsgBufSize;

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
		// TODO: use regular allocation until memory pool is fixed
		//MemoryPool *pMemPool = memoryManager.GetMemoryPoolBySize(szAllocate);
		//if(pMemPool == nullptr)
		//	return nullptr;

		//pPtr = pMemPool->Alloc("MessageData::NewMessage");
		pPtr = new(heap) uint8_t[szAllocate];
		if (pPtr == nullptr)
			return nullptr;

		pBuffer = static_cast<uint8_t*>(pPtr);
		if (pBuffer == nullptr)
			return nullptr;

		MessageData *pMsg = new(pBuffer) MessageData(uiMsgBufSize, pData);

		pMsg->GetMessageHeader()->SetIDNLen(uiMsgID, uiMsgBufSize);

		return pMsg;
	}


	Message::MessageData* MessageData::Clone(IHeap& memoryManager)
	{
		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
			return nullptr;

		Message::MessageData* pMessage = NewMessage(memoryManager, m_pMsgHeader->msgID.ID, m_pMsgHeader->Length, (uint8_t*)m_pMsgHeader );
		pMessage->GetMessageHeader()->msgID.IDSeq.Sequence = 0;

		return pMessage;
	}

	void MessageData::GetLengthNDataPtr( uint& length, uint8_t* &pDataPtr)
	{
		if( m_pMsgHeader->msgID.IDs.Mobile )
		{
			AssertRel(m_pMsgHeader->Length >= sizeof(MobileMessageHeader));
			length = m_pMsgHeader->Length - (uint)sizeof(MobileMessageHeader);
			pDataPtr = (uint8_t*)(m_pMobileMsgHeader + 1);
		}
		else
		{
			AssertRel(m_pMsgHeader->Length >= sizeof(MessageHeader));
			length = m_pMsgHeader->Length - (uint)sizeof(MessageHeader);
			pDataPtr = (uint8_t*)(m_pMsgHeader + 1);
		}
	}
	
	uint MessageData::GetDataLength()
	{
		uint length;
		if( m_pMsgHeader->msgID.IDs.Mobile )
		{
			AssertRel(m_pMsgHeader->Length >= sizeof(MobileMessageHeader));
			length = m_pMsgHeader->Length - (uint)sizeof(MobileMessageHeader);
		}
		else
		{
			AssertRel(m_pMsgHeader->Length >= sizeof(MessageHeader));
			length = m_pMsgHeader->Length - (uint)sizeof(MessageHeader);
		}
		return length;
	}

	
	// Update checksume
	void MessageData::UpdateChecksum()
	{
		uint length = 0;
		uint8_t* pDataPtr = nullptr;
		GetLengthNDataPtr(length,pDataPtr);

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
			Assert(0);
			return;
		}

		if( length == 0 )
		{
			m_pMsgHeader->Crc32 = 0;
			return;
		}

		m_pMsgHeader->Crc32 = Hasher_Crc32().Crc32(0, pDataPtr, length );
		if( m_pMsgHeader->Crc32 == 0 )
			m_pMsgHeader->Crc32 = ~m_pMsgHeader->Crc32;
	}
	
	// Update checksume
	void MessageData::UpdateChecksumNEncrypt()
	{
		uint length = 0;
		uint8_t* pDataPtr = nullptr;
		GetLengthNDataPtr(length,pDataPtr);

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
			Assert(0);
			return;
		}

		if( length == 0 )
		{
			m_pMsgHeader->Crc32 = 0;
			return;
		}

		if( m_pMsgHeader->msgID.IDs.Encrypted )
		{
			// skip if the message is already encrypted
			return;
		}

		m_pMsgHeader->Crc32 = Util::Crc32NEncrypt( length, pDataPtr );
		if( m_pMsgHeader->Crc32 == 0 )
			m_pMsgHeader->Crc32 = ~m_pMsgHeader->Crc32;

		Assert( m_pMsgHeader->Crc32 != 0 || length == 0 );

		m_pMsgHeader->msgID.IDs.Encrypted = true;
	}

	Result MessageData::ValidateChecksum()
	{
		uint length = 0;
		uint8_t* pDataPtr = nullptr;
		GetLengthNDataPtr(length,pDataPtr);

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
			Assert(0);
			return ResultCode::FAIL;
		}

		// Nothing to check
		if( length == 0 )
			return ResultCode::SUCCESS;

		uint16_t Crc32 = Hasher_Crc32().Crc32(0, pDataPtr, length);
		if( Crc32 == 0 ) Crc32 = ~Crc32;

		if( Crc32 != m_pMsgHeader->Crc32 )
			return ResultCode::IO_INVALID_MESSAGE_CHECKSUM;

		return ResultCode::SUCCESS;
	}
	
	Result MessageData::ValidateChecksumNDecrypt()
	{
		uint length = 0;
		uint8_t* pDataPtr = nullptr;
		GetLengthNDataPtr(length,pDataPtr);

		if( m_pMsgHeader == nullptr || m_pMsgHeader->Length == 0 )
		{
			m_pMsgHeader->msgID.IDs.Encrypted = false;
			return ResultCode::SUCCESS_FALSE;
		}

		if( !m_pMsgHeader->msgID.IDs.Encrypted )
		{
			return ValidateChecksum();
		}
		
		// Nothing to check
		if( length == 0 )
		{
			m_pMsgHeader->msgID.IDs.Encrypted = false;
			return ResultCode::SUCCESS;
		}

		uint16_t Crc32 = Util::Crc32NDecrypt( length, pDataPtr );
		if( Crc32 == 0 ) Crc32 = ~Crc32;

		m_pMsgHeader->msgID.IDs.Encrypted = false;

		//Assert(m_pMsgHeader->Crc32 != 0);
		if( Crc32 != m_pMsgHeader->Crc32 )
			return ResultCode::IO_INVALID_MESSAGE_CHECKSUM;

		return ResultCode::SUCCESS;
	}







	Result MessageBase::ParseMsg()
	{ 
		if(m_bIsParsed)
			return m_hrParsing;

		m_bIsParsed = true;
		m_hrParsing = ParseMessage(GetMessage());

		return m_hrParsing;
	}

} // Message

} // SF


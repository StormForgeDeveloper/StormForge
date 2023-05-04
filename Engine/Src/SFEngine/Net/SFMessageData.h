////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message Definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFAssert.h"
#include "Net/SFMessage.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocol.h"


namespace SF {

	class IHeap;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Message data class
	//

	class MessageData : public SharedObject
	{
	private:

        // Mobile packet header
        MobilePacketHeader* m_pPacketHeader;

		// Message Buffer Pointer
		MessageHeader*			m_pMsgHeader;

		bool					m_bIsSequenceAssigned;

		// Encryption status
        bool m_bIsEncrypted{};

	private:
		MessageData(uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData = NULL);

	public:
		virtual ~MessageData();

        SF_FORCEINLINE MobilePacketHeader* GetPacketHeader() { return m_pPacketHeader; }
        SF_FORCEINLINE MessageHeader* GetMessageHeader() { return m_pMsgHeader; }
		uint8_t*	GetMessageBuff(); // data include header
		uint		GetMessageSize() const; // total length

        SF_FORCEINLINE uint8_t* GetPayloadPtr()
        {
            return reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(m_pMsgHeader) + m_pMsgHeader->GetHeaderSize());
        }

        SF_FORCEINLINE const uint8_t* GetPayloadPtr() const
        {
            return const_cast<MessageData*>(this)->GetPayloadPtr();
        }

		// Data except header
		SF_FORCEINLINE ArrayView<uint8_t> GetPayload() const
        {
            uint headerSize = (uint)m_pMsgHeader->GetHeaderSize();
            assert(m_pMsgHeader->Length >= headerSize);
            uint length = m_pMsgHeader->Length - headerSize;
            uint8_t* pDataPtr = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(m_pMsgHeader) + headerSize);
            return ArrayView<uint8_t>(length, pDataPtr);
        }

        SF_FORCEINLINE uint GetPayloadSize() const
        {
            uint headerSize = (uint)m_pMsgHeader->GetHeaderSize();
            assert(m_pMsgHeader->Length >= headerSize);
            return m_pMsgHeader->Length - headerSize;
        }

        SF_FORCEINLINE void SetEncrypted(bool bEncrypted) { m_bIsEncrypted = bEncrypted; }
        SF_FORCEINLINE bool IsEncrypted() const { return m_bIsEncrypted; }

		// Parsing helper
		void GetRouteInfo(RouteContext& routeContext, TransactionID& transID);

		void ClearAssignedSequence();
		void AssignSequence(uint sequence);
		inline bool GetIsSequenceAssigned() { return m_bIsSequenceAssigned; }

		// Initialize message buffer
		static MessageData* NewMessage(IHeap& heap, uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData = nullptr);

		virtual MessageData* Clone(IHeap& memoryManager);


		// Update checksum and encrypt
		void UpdateChecksum();
		void UpdateChecksumNEncrypt();

		Result ValidateChecksum();
		Result ValidateChecksumNDecrypt();
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Message base class
	//

	class MessageBase
	{
	private:
		// Message handler
		SharedPointerT<MessageData>	m_pIMsg;

		// Parsing result
		Result		m_hrParsing = ResultCode::SUCCESS_FALSE;
		bool		m_bHasParsed = false;

	public:

		MessageBase() = default;
		MessageBase(const SharedPointerT<MessageData> &pIMsg)
			: m_pIMsg(pIMsg)
		{
		}

		virtual ~MessageBase() { m_pIMsg = nullptr; }

		// Get Message
		MessageData* GetMessage() const { return *m_pIMsg; }
		const SharedPointerT<MessageData>& GetMessagePtr() const { return m_pIMsg; }

		// Get Parsing Result
		Result GetParsingResult() const { return m_hrParsing; }

		// Parse message data, message data should be passed to constructor
		virtual Result ParseMsg();

		// Parsing message data
		virtual Result ParseMessage(const MessageData* pIMsg) = 0;
	};


	using MessageDataPtr = SharedPointerT<MessageData>;

} // SF

extern template class SF::SharedPointerT<SF::MessageData>;



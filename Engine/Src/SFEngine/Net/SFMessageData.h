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
#include "SFProtocol.h"


namespace SF {

	class IHeap;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Message data class
	//

	class MessageData : public SharedObject
	{
	private:

        // Packet header
        PacketHeader* m_pPacketHeader;

		// Message Buffer Pointer
		MessageHeader*			m_pMsgHeader;

		bool					m_bIsSequenceAssigned;

		// Encryption status
        bool m_bIsEncrypted{};

	private:
		MessageData(uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData = nullptr);

	public:
		virtual ~MessageData();

        SF_FORCEINLINE PacketHeader* GetPacketHeader() { return m_pPacketHeader; }
        SF_FORCEINLINE const PacketHeader* GetPacketHeader() const { return m_pPacketHeader; }
        SF_FORCEINLINE MessageHeader* GetMessageHeader() { return m_pMsgHeader; }
        SF_FORCEINLINE const MessageHeader* GetMessageHeader() const { return m_pMsgHeader; }
        uint8_t* GetMessageBuff(); // data include header
		uint GetMessageSize() const; // total length

        SF_FORCEINLINE uint8_t* GetPayloadPtr()
        {
            return reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(m_pMsgHeader) + m_pMsgHeader->GetHeaderSize());
        }

        SF_FORCEINLINE const uint8_t* GetPayloadPtr() const
        {
            return const_cast<MessageData*>(this)->GetPayloadPtr();
        }

		// Data except header
        SF_FORCEINLINE ArrayView<uint8_t> GetPayload() const { return m_pMsgHeader->GetPayload(); }
        SF_FORCEINLINE uint GetPayloadSize() const { return m_pMsgHeader->GetPayloadSize(); }

        SF_FORCEINLINE void SetEncrypted(bool bEncrypted) { m_bIsEncrypted = bEncrypted; }
        SF_FORCEINLINE bool IsEncrypted() const { return m_bIsEncrypted; }

		// Parsing helper
		void ClearAssignedSequence();
		void AssignSequence(uint sequence);
		inline bool GetIsSequenceAssigned() { return m_bIsSequenceAssigned; }

		// Initialize message buffer
		static MessageData* NewMessage(IHeap& heap, uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData = nullptr);
        static MessageData* NewMessage(IHeap& heap, const MessageHeader* pHeader);

        // Make a clone this message
		MessageData* Clone(IHeap& heap);


		// Update checksum and encrypt

        SF_FORCEINLINE void UpdateChecksum()
        {
            m_pMsgHeader->UpdateChecksum();
        }

        SF_FORCEINLINE void UpdateChecksumNEncrypt()
        {
            m_pMsgHeader->UpdateChecksumNEncrypt();
            m_bIsEncrypted = true;
        }

        SF_FORCEINLINE Result ValidateChecksum()
        {
            return m_pMsgHeader->ValidateChecksum();
        }

        SF_FORCEINLINE Result ValidateChecksumNDecrypt()
        {
            Result hr = m_pMsgHeader->ValidateChecksumNDecrypt();
            if (hr)
            {
                m_bIsEncrypted = false;
            }
            return hr;
        }

	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Message base class
	//

	class MessageBase
	{
	private:
		// Message data reference
		SharedPointerT<MessageData>	m_pIMsg;

        // message header
        const MessageHeader* m_pHeader{};

		// Parsing result
		Result		m_hrParsing = ResultCode::SUCCESS_FALSE;
		bool		m_bHasParsed = false;

	public:

		MessageBase() = default;
        MessageBase(const MessageHeader* pHeader);
        MessageBase(const SharedPointerT<MessageData>& pIMsg);

		virtual ~MessageBase() { m_pIMsg = nullptr; }

		// Get Message
		MessageData* GetMessage() const { return *m_pIMsg; }
		const SharedPointerT<MessageData>& GetMessagePtr() const { return m_pIMsg; }

        const MessageHeader* GetMessageHeader() const { return m_pHeader; }
        void SetMessageHeader(const MessageHeader* pHeader) { m_pHeader = pHeader; }

		// Get Parsing Result
		Result GetParsingResult() const { return m_hrParsing; }

		// Parse message data, message data should be passed to constructor
		virtual Result ParseMsg();

		// Parsing message data
		virtual Result ParseMessage(const MessageHeader* pHeader) = 0;
	};


	using MessageDataPtr = SharedPointerT<MessageData>;

} // SF

extern template class SF::SharedPointerT<SF::MessageData>;



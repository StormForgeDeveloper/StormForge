////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
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


namespace SF {

	class IHeap;

namespace Message {

	struct MessageHeader;
	struct MobileMessageHeader;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network message object
	//


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Message data class
	//


	class MessageData : public SharedObject
	{
	private:
		// Message Buffer Pointer
		union {
			MessageHeader*			m_pMsgHeader;
			MobileMessageHeader*	m_pMobileMsgHeader;
		};

		bool					m_bIsSequenceAssigned;

		// Encryption status

	private:
		MessageData(uint32_t uiMsgID, uint uiMsgBufSize, const uint8_t* pData = NULL);

	public:
		virtual ~MessageData();

		MessageHeader* GetMessageHeader();
		MobileMessageHeader* GetMobileMessageHeader();
		uint8_t*	GetMessageBuff(); // data include header
		uint		GetMessageSize() const; // total length
		uint8_t* GetMessageData();       // data except header
		const uint8_t* GetMessageData() const;       // data except header

		// Data except header
		void GetLengthNDataPtr(uint& length, uint8_t* &pDataPtr);
		uint GetDataLength();

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


} // Message


	using MessageDataPtr = SharedPointerT<Message::MessageData>;

} // SF

extern template class SF::SharedPointerT<SF::Message::MessageData>;



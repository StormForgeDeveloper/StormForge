////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Generic Message
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFMessage.h"
#include "Net/SFNetDef.h"



namespace SF {
	namespace Message {

		// S2C: Used for sending general failure for not started transaction messages
		class FailResultS2CEvt : public MessageBase
		{
		private:
			Context m_Context;
			Result m_hrRes;
		public:
			FailResultS2CEvt()
			{}

			FailResultS2CEvt(MessageDataPtr&& pMsg)
				:MessageBase(std::forward<MessageDataPtr>(pMsg))
			{}

			const Context& GetContext() const { return m_Context; };
			const Result& GethrRes() const { return m_hrRes; };

			void OutputMessage(const char* Prefix);

			virtual Result ParseMessage(const MessageHeader* pHeader) override;

		}; // class FailResultS2CEvt : public BR::Net::MessageBase


	} // namespace Message
} // namespace SF


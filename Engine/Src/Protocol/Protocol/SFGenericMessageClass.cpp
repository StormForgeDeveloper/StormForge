////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
// 
// Description : Generic Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/SFGenericMessageClass.h"



namespace SF {
namespace Message {

		// S2C: Used for sending generial failure for not started transaction messages
		Result FailResultS2CEvt::ParseMessage( MessageData* pIMsg )
		{
 			FunctionContext hr = ResultCode::SUCCESS;

			protocolCheckPtr(pIMsg);

			size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));
			ArrayView<uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());
			InputMemoryStream inputStream(bufferView);
			auto* input = inputStream.ToInputStream();


			if(MsgDataSize == sizeof(Result)) // if result only
			{
				m_Context = 0;
			}
			else
			{
				protocolCheck( input->Read(m_Context) );
			}
			protocolCheck(input->Read(m_hrRes));

			return hr;

		}; // Result MsgFailResultS2CEvt::ParseIMsg( BR::Net::MessageData* pIMsg )

		void FailResultS2CEvt::OutputMessage(const char* Prefix)
		{
 			unused(Prefix);
			SFLog(Net, Debug1, "{0}:FailResultS2CEvt: , Context:{1}, hrRes:{2:X8}",
											Prefix, m_Context, m_hrRes); 
		}; // VOID MsgFailResultS2CEvt::OutputMessage(const char* Prefix)


}; // namespace Message
}; // namespace SF



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
 			Result hr = ResultCode::SUCCESS;
			int iMsgSize;
			uint8_t* pCur;

			protocolChkPtr(pIMsg);

			iMsgSize = (int)pIMsg->GetMessageSize() - sizeof(MessageHeader);
			pCur = pIMsg->GetMessageData();

			if( iMsgSize == sizeof(Result) ) // if result only
			{
				m_Context = 0;
			}
			else
			{
				protocolChk( Protocol::StreamParamCopy( &m_Context, pCur, iMsgSize, sizeof(Context) ) );
			}
			protocolChk( Protocol::StreamParamCopy( &m_hrRes, pCur, iMsgSize, sizeof(Result) ) );

		Proc_End:

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



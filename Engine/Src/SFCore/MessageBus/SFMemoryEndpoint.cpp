////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message2
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Net/SFMessage.h"
#include "Net/SFNetSystem.h"
#include "MessageBus/SFMemoryEndpoint.h"


namespace SF
{

    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Network Message header2
    //

    void MemoryEndpoint::Clear()
    {
    }

    Result MemoryEndpoint::SendMsg(const MessageHeader* messageData)
    {
        m_LastMessage = messageData;

        return ResultCode::SUCCESS;
    }

} // SF

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : Remote Entity implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Util/SFLog.h"
#include "Util/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Net/SFMessageEndpoint.h"
#include "Online/StreamDB/SFStreamDB.h"


namespace SF {

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Entity base class
	//


	MessageEndpointStreamDB::MessageEndpointStreamDB()
	{

	}

	MessageEndpointStreamDB::~MessageEndpointStreamDB()
	{

	}

	// Initialize entity to proceed new connection
	Result MessageEndpointStreamDB::InitializeEndpoint(const String& endpointServer, const String& endpointChannel)
	{
		Result hr;

		if (endpointServer.IsNullOrEmpty() || endpointChannel.IsNullOrEmpty())
			return ResultCode::FAIL;

		m_EndpointAddress.MessageServer = endpointServer;
		m_EndpointAddress.Channel = endpointChannel;

		m_TargetEndpoint = new(GetSystemHeap()) StreamDBProducer;
		hr = m_TargetEndpoint->Initialize(endpointServer, endpointChannel);

		return hr;
	}

	// Close entity and clear transaction
	Result MessageEndpointStreamDB::Terminate()
	{
		if (m_TargetEndpoint != nullptr)
			m_TargetEndpoint->Dispose();
		m_TargetEndpoint = nullptr;

		return ResultCode::SUCCESS;
	}

	bool MessageEndpointStreamDB::IsSameEndpoint(const EndpointAddress& messageEndpoint)
	{
		return m_EndpointAddress.MessageServer == messageEndpoint.MessageServer && m_EndpointAddress.Channel == messageEndpoint.Channel;
	}

    Result MessageEndpointStreamDB::SendMsg(const MessageHeader* messageData)
    {
        if (m_TargetEndpoint == nullptr)
            return ResultCode::NOT_INITIALIZED;

        if (messageData == nullptr)
        {
            return ResultCode::INVALID_POINTER;
        }

#if 0 // message logging
        DynamicArray<uint8_t> encodedBuffer;
        Util::HEXEncode(messageData->Length, messageData, encodedBuffer);
        encodedBuffer.push_back('\0');
        SFLog(System, Debug3, "ServerMessageConsumer:SendRaw: {0}, {1}", messageData->Length, (const char*)encodedBuffer.data());
#endif

        return m_TargetEndpoint->SendRecord(ArrayView<const uint8_t>(messageData->MessageSize, reinterpret_cast<const uint8_t*>(messageData)));
    }

} // namespace SF


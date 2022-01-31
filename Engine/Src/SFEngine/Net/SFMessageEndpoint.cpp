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
#include "ServerConfig/SFServerConfig.h"


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

	Result MessageEndpointStreamDB::Send(const SharedPointerT<Message::MessageData>& messageData)
	{
		if (m_TargetEndpoint == nullptr)
			return ResultCode::NOT_INITIALIZED;

		return m_TargetEndpoint->SendRecord(ArrayView<const uint8_t>(messageData->GetMessageSize(), messageData->GetMessageBuff()));
	}

} // namespace SF


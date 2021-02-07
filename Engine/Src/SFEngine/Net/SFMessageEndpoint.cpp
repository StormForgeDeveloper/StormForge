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
#include "String/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Net/SFMessageEndpoint.h"
#include "StreamDB/SFStreamDB.h"



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

		m_TargetEndpoint = new StreamDBProducer;
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

	Result MessageEndpointStreamDB::Send(const SharedPointerT<Message::MessageData>& messageData)
	{
		if (m_TargetEndpoint == nullptr)
			return ResultCode::NOT_INITIALIZED;

		return m_TargetEndpoint->SendRecord(ArrayView<uint8_t>(messageData->GetMessageSize(), messageData->GetMessageBuff()));
	}

} // namespace SF


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : Message endpoint
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Net/SFNetDef.h"

namespace SF {

	namespace Message
	{
		class MessageData;
	}

	class StreamDBConsumer;
	class StreamDBProducer;




	//////////////////////////////////////////////////////////////////////////////////////////////
	// StreamDB endpoint
	class MessageEndpointStreamDB : public MessageEndpoint
	{
	public:

		EndpointAddress m_EndpointAddress;
		SharedPointerT<StreamDBProducer> m_TargetEndpoint;

	public:

		MessageEndpointStreamDB();
		virtual ~MessageEndpointStreamDB();

		// Initialize entity to proceed new connection
		virtual Result InitializeEndpoint(const String& endpointServer, const String& endpointChannel);

		// Close entity and clear transaction
		virtual Result Terminate();

		virtual bool IsSameEndpoint(const EndpointAddress& messageEndpoint) override;
		virtual Result Send(const SharedPointerT<Message::MessageData>& messageData) override;
	};



} // namespace SF



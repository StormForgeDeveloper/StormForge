////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Public Interfaces
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Util/SFLog.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"
#include "Interfaces/SFNetRelayInterface.h"
#include "Net/SFNetRelayNetwork.h"
#include "Protocol/Message/RelayMsgClass.h"


namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	NetRelayNetwork::NetRelayNetwork()
	{
		m_Impl = new(Service::NetSystem->GetHeap()) Net::RelayNetwork(Service::NetSystem->GetHeap());
		SharedReferenceInc inc(m_Impl);
		m_Impl->RegisterToEngineObjectManager();
	}

	NetRelayNetwork::~NetRelayNetwork()
	{
		if (m_Impl == nullptr)
			return;

		m_Impl->Disconnect("Destroy");
		m_Impl->CloseConnection("Destroy");
		m_Impl->SetTickFlags(0);

		SharedReferenceDec dec(m_Impl);
	}


	RelayNetworkState NetRelayNetwork::GetRelayNetworkState()
	{
		return m_Impl->GetRelayNetworkState();
	}

	uint32_t NetRelayNetwork::GetRelayInstanceID() const
	{
		return m_Impl->GetRelayInstanceID();
	}

	uint64_t NetRelayNetwork::GetLocalPlayerID() const
	{
		return m_Impl->GetLocalPlayerID();
	}

	uint32_t NetRelayNetwork::GetLocalEndpointID() const
	{
		return m_Impl->GetLocalEndpointID();
	}


	// Connect to remote. InitConnection + Connect 
	// @relayServerAddr: relay server address
	// @relayInstanceID:  relay server instance id
	// @myPlayerID: my player id, 
	uint32_t NetRelayNetwork::Connect(const char* relayServerAddr, uint32_t port, uint32_t relayInstanceID, uint64_t myPlayerID)
	{
		return m_Impl->Connect(NetAddress(relayServerAddr, port), relayInstanceID, myPlayerID);
	}

	// Disconnect connection
	uint32_t NetRelayNetwork::Disconnect(const char* reason)
	{
		return m_Impl->Disconnect(reason);
	}

	// Close connection
	uint32_t NetRelayNetwork::CloseConnection(const char* reason)
	{
		return m_Impl->CloseConnection(reason);
	}

	// Send message to connected entity
	uint32_t NetRelayNetwork::Send(uint32_t targetEndpointMask, uint32_t payloadSize, const void* payloadData)
	{
		return m_Impl->Send(targetEndpointMask, payloadSize, payloadData);
	}

	size_t NetRelayNetwork::GetRecvMessageCount()
	{
		return m_Impl->GetRecvMessageCount();
	}

	size_t NetRelayNetwork::GetRecvDataSize()
	{
		MessageDataPtr pMsg;

		if (!m_Impl->GetFrontRecvMessage(pMsg))
			return 0;

		// Hum, shouldn't be happended
		if (pMsg->GetMessageSize() < sizeof(uint32_t) * 3)
		{
			assert(0);
			return 1;
		}

		return pMsg->GetMessageSize() - sizeof(uint32_t) * 3;
	}

	size_t NetRelayNetwork::RecvData(size_t bufferSize, void* dataBuffer)
	{
		MessageDataPtr pMsg;

		if (!m_Impl->GetRecvMessage(pMsg))
			return 0;

		Message::Relay::RelayPacketC2SEvt message(std::forward<MessageDataPtr>(pMsg));
		auto hr = message.ParseMsg();
		if (!hr)
		{
			SFLog(Net, Error, "NetRelayNetwork::RecvData, : parse error {0}", hr);
			return 0;
		}

		if (dataBuffer == nullptr || bufferSize < message.GetPayload().size())
		{
			SFLog(Net, Error, "NetRelayNetwork::RecvData, : Not enough buffer size: required:{0}", message.GetPayload().size());
			return 0;
		}

		memcpy(dataBuffer, message.GetPayload().data(), message.GetPayload().size());

		return message.GetPayload().size();
	}
	
}





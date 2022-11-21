////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StreamDB warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "Online/SFOnlineAPIClient.h"
#include "Util/SFStringFormat.h"
#include "Util/SFLog.h"
#include "json/json.h"
#include "bson/bson.h"


namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class OnlineAPIClient
	//

	OnlineAPIClient::OnlineAPIClient(IHeap& heap)
		: EngineObject(&heap,"OnlineAPIClient"_crc64)
        , m_Client(heap)
        , m_ReceivedResultQueue(heap)
	{
	}

	OnlineAPIClient::~OnlineAPIClient()
	{
        Disconnect();
	}

	Result OnlineAPIClient::Connect(const String& serverAddress, int port, const String& accessKey)
	{
		Result hr;

        Disconnect();

        m_ServerAddress = serverAddress;
        m_Port = port;
        m_AccessKey = accessKey;
        m_MachineUID = Util::GetMachineUniqueId();

        m_Client.OnRecvEvent().AddDelegate(uintptr_t(this), [this](Websocket::WSSessionData* pss, const Array<uint8_t>& data)
            {
                OnRecv(data);
			});

        String serverPath;
        serverPath.Format("/BRAPI?AccessKey={0}&MachineUID={1}", m_AccessKey, m_MachineUID);
        m_Client.SetServerPath(serverPath);

		hr = m_Client.Initialize(serverAddress, port, "ws");
		if (!hr)
			return hr;

		return ResultCode::SUCCESS;
	}

    Result OnlineAPIClient::Reconnect()
    {
        Result hr;
        if (IsConnected())
            return ResultCode::SUCCESS;

        if (m_ServerAddress.IsNullOrEmpty())
            return ResultCode::NOT_INITIALIZED;

        Disconnect();

        hr = m_Client.Initialize(m_ServerAddress, m_Port, "ws");
        if (!hr)
            return hr;

        return hr;
    }

	void OnlineAPIClient::Disconnect()
	{
		m_Client.Terminate();
    }

    void OnlineAPIClient::OnRecv(const Array<uint8_t>& data)
    {
        String temp(GetSystemHeap(), reinterpret_cast<const char*>(data.data()), 0, int(data.size()));
        SFLog(Game, Info, "Recv:{0}", temp);

        std::string errs;
        Json::CharReaderBuilder jsonBuilder;
        Json::Value rootObject;
        UniquePtr<Json::CharReader> jsonReader(jsonBuilder.newCharReader());
        auto readStart = reinterpret_cast<const char*>(data.data());
        bool bRes = jsonReader->parse(readStart, readStart + data.size(), &rootObject, &errs);
        if (!bRes)
        {
            SFLog(Net, Error, "ServerConfigJson::LoadConfig value parsing error:{0}", errs);
            return;
        }

        APIResult* Result = new(GetHeap()) APIResult;
        auto objectRequestFunc = rootObject.get("APIName", Json::Value(""));
        Result->APIName = objectRequestFunc.asCString();

        auto objectMessage = rootObject.get("Payload", Json::Value(""));
        Result->ResultPayload = objectMessage.asCString();

        m_ReceivedResultQueue.Enqueue(Result);
    }

    Result OnlineAPIClient::RequestServiceStatus()
    {
        Result hr;

        static const char* requestString = "{ \"APIName\":\"ServiceStatus\" }";

        if (!m_Client.IsConnected())
        {
            return ResultCode::IO_NOT_CONNECTED;
        }

        ArrayView<uint8_t> bufferView(strlen(requestString), (uint8_t*)requestString);
        m_Client.Send(bufferView);

        return hr;
    }

    Result OnlineAPIClient::RequestServerNotice()
    {
        Result hr;

        static const char* requestString = "{ \"APIName\":\"ServerNotice\" }";

        if (!m_Client.IsConnected())
        {
            return ResultCode::IO_NOT_CONNECTED;
        }

        ArrayView<uint8_t> bufferView(strlen(requestString), (uint8_t*)requestString);
        m_Client.Send(bufferView);

        return hr;
    }


}


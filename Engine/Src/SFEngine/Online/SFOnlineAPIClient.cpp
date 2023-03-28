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
        , m_ListeningAPINames(heap)
	{
	}

	OnlineAPIClient::~OnlineAPIClient()
	{
        Disconnect();
	}

	Result OnlineAPIClient::Connect(const String& serverAddress, int port, const String& accessKey)
	{
		Result hr;

        //Disconnect();

        m_ServerAddress = serverAddress;
        m_Port = port;
        m_AccessKey = accessKey;
        m_MachineUID = Util::GetMachineUniqueId();

        m_Client.OnRecvEvent().AddDelegate(uintptr_t(this), [this](const Array<uint8_t>& data)
            {
                OnRecv(data);
			});

        m_Client.AddParameter("AccessKey", m_AccessKey);
        m_Client.AddParameter("MachineUID", m_MachineUID);
        m_Client.SetServerPath("/BRAPI");

        m_Client.SetOnConnectedCallback([this]()
            {
                for (auto APIName : m_ListeningAPINames)
                {
                    Request((const char*)APIName);
                }
            });

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
        Result hr;

        SFLog(Websocket, Debug4, "OnlineAPIClient OnRecv: size:{0}", data.size());


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
        DynamicArray<uint8_t> decodedBuffer;
        hr = Util::HEXDecode(strlen(objectMessage.asCString()), (const uint8_t*)objectMessage.asCString(), decodedBuffer);
        decodedBuffer.push_back('\0');
        Result->ResultPayload = (const char*)decodedBuffer.data();

        m_ReceivedResultQueue.Enqueue(Result);
    }

    Result OnlineAPIClient::Request(const char* APIName)
    {
        Result hr;

        if (StrUtil::IsNullOrEmpty(APIName))
            return ResultCode::INVALID_ARG;

        SFLog(Websocket, Debug2, "OnlineAPIClient Request:{0}", APIName);

        if (!m_ListeningAPINames.Contains(APIName))
            m_ListeningAPINames.Insert(APIName);

        if (!m_Client.IsConnected())
        {
            return ResultCode::IO_NOT_CONNECTED;
        }

        String requestString = "{ \"APIName\":\"";
        requestString.Append(APIName);
        requestString.Append("\" }");

        ArrayView<uint8_t> bufferView(strlen(requestString), (uint8_t*)requestString.data());
        return m_Client.Send(bufferView);
    }


}


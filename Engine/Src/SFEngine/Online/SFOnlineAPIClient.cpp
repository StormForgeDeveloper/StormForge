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
		Terminate();
	}

	Result OnlineAPIClient::Initialize(const String& serverAddress, int port, const String& accessKey)
	{
		Result hr;

        m_AccessKey = accessKey;
        m_MachineUID = Util::GetMachineUniqueId();

		//m_Client.SetUseTickThread(false);
		//m_Client.SetClientAppendHeaderFunction([&](struct lws* wsi, void* user, void* in, size_t len)
		//	{
		//		unsigned char** p = (unsigned char**)in, * end = (*p) + len;
		//		String HeaderString;
		//		HeaderString.Format("{0}={1};{2}={3}", 
  //                  KeyName_AccessKey, m_AccessKey,
  //                  KeyName_MachineUID, m_MachineUID);
		//		auto res = lws_add_http_header_by_name(wsi, (unsigned char*)KeyName_AuthHeader, (unsigned char*)HeaderString.data(), (int)HeaderString.length(), p, end);
		//		if (res)
		//		{
		//			return -1;
		//		}
		//		return 0;
		//	});

        m_Client.OnRecvEvent().AddDelegate(uintptr_t(this), [this](Websocket::WSSessionData* pss, const Array<uint8_t>& data)
            {
                OnRecv(data);
			});

		hr = m_Client.Initialize(serverAddress, port, "ws");
		if (!hr)
			return hr;

        String serverPath;
        serverPath.Format("/BRAPI?AccessKey={0}&MachineUID={1}", m_AccessKey, m_MachineUID);
        m_Client.SetServerPath(serverPath);


		//m_Thread.reset(new(GetHeap()) FunctorTickThread([this](Thread* pThread)
		//	{
		//		if (!m_Client.IsValid())
		//		{
		//			m_Client.TryConnect();
		//			ThisThread::SleepFor(DurationMS(10000));
		//			return true;
		//		}

		//		m_Client.TickEventLoop(0);

		//		if (!m_Client.IsConnected())
		//		{
		//			ThisThread::SleepFor(DurationMS(500));
		//			return true;
		//		}

		//		return true;
		//	}));

		//m_Thread->Start();


		return ResultCode::SUCCESS;
	}

	void OnlineAPIClient::Terminate()
	{
		//if (m_Thread != nullptr)
		//{
		//	m_Thread->SetKillEvent();
		//}

		m_Client.Terminate();

		//if (m_Thread != nullptr)
		//{
		//	m_Thread->Stop();
		//	m_Thread.reset();
		//}

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

        APIResult* Result = new APIResult;
        auto objectRequestFunc = rootObject.get("RequestFunc", Json::Value(""));
        Result->APIName = objectRequestFunc.asCString();

        auto objectMessage = rootObject.get("Message", Json::Value(""));
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


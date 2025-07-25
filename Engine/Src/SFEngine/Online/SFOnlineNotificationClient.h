////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TelemetryService 
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Task/SFTask.h"
#include "Util/SFLog.h"
#include "Online/Websocket/SFWebsocketClientCurl.h"
#include "EngineObject/SFEngineObject.h"



namespace SF
{



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class OnlineServiceStatus
	//

    class OnlineNotificationClient : public EngineObject
    {
    public:

        using super = EngineObject;

        static constexpr char KeyName_AccessKey[] = "AccessKey";
		static constexpr char KeyName_MachineUID[] = "MachineUID";

        struct APIResult
        {
            String APIName;
            String ResultPayload;
        };

    public:

        OnlineNotificationClient();
        virtual ~OnlineNotificationClient();

		SF_FORCEINLINE IHeap& GetHeap() const { return GetSystemHeap(); }

        virtual Result Connect(const String& env, const String& url, const String& accessKey);
        Result Reconnect();
		void Disconnect();


		SF_FORCEINLINE bool IsInitialized() const { return m_Client.IsInitialized(); }
		SF_FORCEINLINE bool IsConnected() const { return m_Client.IsConnected(); }

        Result Request(const char* APIName);

        SF_FORCEINLINE CircularPageQueue<APIResult*>& GetRecvQueue() { return m_ReceivedResultQueue; }

    private:

        virtual Result OnTick(EngineTaskTick tick) override;
        void OnRecv(const Array<uint8_t>& data);

	private:
        String m_Url;
        String m_Env;
		String m_AccessKey;
		String m_MachineUID;

		WebsocketClientCurl m_Client;

        CircularPageQueue<APIResult*> m_ReceivedResultQueue;

        SortedSet<StringCrc32> m_ListeningAPINames;
    };

}


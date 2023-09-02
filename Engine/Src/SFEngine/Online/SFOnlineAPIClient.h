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

    class OnlineAPIClient : public EngineObject
    {
    public:

        static constexpr char KeyName_AccessKey[] = "AccessKey";
		static constexpr char KeyName_MachineUID[] = "MachineUID";

        struct APIResult
        {
            String APIName;
            String ResultPayload;
        };

    public:

        OnlineAPIClient(IHeap& heap);
        virtual ~OnlineAPIClient();

		SF_FORCEINLINE IHeap& GetHeap() const { return GetSystemHeap(); }

        virtual Result Connect(const String& url, const String& accessKey);
        Result Reconnect();
		void Disconnect();


		SF_FORCEINLINE bool IsInitialized() const { return m_Client.IsInitialized(); }
		SF_FORCEINLINE bool IsConnected() const { return m_Client.IsConnected(); }

        Result Request(const char* APIName);

        SF_FORCEINLINE CircularPageQueue<APIResult*>& GetRecvQueue() { return m_ReceivedResultQueue; }

    private:

        void OnRecv(const Array<uint8_t>& data);

	private:
        String m_Url;
		String m_AccessKey;
		String m_MachineUID;

		WebsocketClientCurl m_Client;

        CircularPageQueue<APIResult*> m_ReceivedResultQueue;

        SortedSet<StringCrc32> m_ListeningAPINames;
    };

}


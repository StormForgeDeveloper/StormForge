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
#include "Online/Websocket/SFWebsocketClient.h"
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

        virtual Result Initialize(const String& serverAddress, int port, const String& accessKey);
		void Terminate();


		SF_FORCEINLINE bool IsValid() const { return m_Client.IsValid(); }
		SF_FORCEINLINE bool IsConnected() const { return m_Client.IsConnected(); }

        Result RequestServiceStatus();
        Result RequestServerNotice();

        SF_FORCEINLINE CircularPageQueue<APIResult*>& GetRecvQueue() { return m_ReceivedResultQueue; }

    private:

        void OnRecv(const Array<uint8_t>& data);

	private:

		String m_AccessKey;
		String m_MachineUID;

		WebsocketClient m_Client;

        CircularPageQueue<APIResult*> m_ReceivedResultQueue;

    };

}


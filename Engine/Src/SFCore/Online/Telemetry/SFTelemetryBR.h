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
#include "Online/Telemetry/SFTelemetryService.h"
#include "Online/Websocket/SFWebsocketClient.h"
#include "Online/Telemetry/SFTelemetryEventQueue.h"

#include "bson/bson.h"


namespace SF
{
	class TelemetryBR;

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryEvent
	//

	// Event creation wrapper
	class TelemetryEvent
	{
	protected:
		TelemetryEvent(IHeap& heap, TelemetryBR* pClient, uint32_t eventId);
		friend class TelemetryBR;

	public:
		~TelemetryEvent();

		Array<const uint8_t>& GetSerializedData();

		SF_FORCEINLINE uint32_t GetEventId() const { return m_EventId; }

		TelemetryEvent& Add(const char* name, int value);
		TelemetryEvent& Add(const char* name, int64_t value);
		TelemetryEvent& Add(const char* name, float value);
		TelemetryEvent& Add(const char* name, const char* value);

		TelemetryEvent& Add(const String& name, int value);
		TelemetryEvent& Add(const String& name, int64_t value);
		TelemetryEvent& Add(const String& name, float value);
		TelemetryEvent& Add(const String& name, const String& value);

		void PostEvent();

	private:
		IHeap& m_Heap;
		TelemetryBR* m_pClient{};
		bool m_bSent = false;
		bson_t m_Bson{};
		uint32_t m_EventId{};
		ArrayView<const uint8_t> m_BinData;
	};




	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryBR
	//

    class TelemetryBR : public TelemetryService
    {
    public:

		static constexpr char KeyName_AuthHeader[] = "sftelemetry:";
		static constexpr int KeyName_AuthHeaderLen = sizeof(KeyName_AuthHeader) - 1; // without null terminator
		static constexpr char KeyName_ClientId[] = "clientid";
        static constexpr char KeyName_AuthKey[] = "authkey";
		static constexpr char KeyName_MachineId[] = "machineid";
		static constexpr char KeyName_SessionId[] = "sessionid";
		static constexpr char KeyName_EventId[] = "EventId";
		static constexpr char KeyName_Protocol[] = "SFTelemetry";
		static constexpr char KeyName_EventName[] = "EventName";


    public:

		TelemetryBR();
        virtual ~TelemetryBR();

		SF_FORCEINLINE IHeap& GetHeap() const { return GetSystemHeap(); }

        virtual Result Initialize(const String& serverAddress, int port, const String& clientId, const String& authKey);

		void Terminate();


		SF_FORCEINLINE bool IsValid() const { return m_Client.IsValid(); }

		SF_FORCEINLINE bool IsConnected() const { return m_Client.IsConnected(); }


		TelemetryEvent* CreateTelemetryEvent(const char* eventName);

	private:

		void EnqueueEvent(TelemetryEvent* pEvent);
		friend class TelemetryEvent;

	private:

		String m_ClientId;
		String m_AuthKey;

		String m_MachineId;
		String m_SessionId;

		Atomic<uint32_t> m_EventId;
		Atomic<uint32_t> m_SentEventId;
		Atomic<uint32_t> m_AckedEventId;

		WebsocketClient m_Client;

		TelemetryEventQueue m_EventQueue;

		SFUniquePtr<Thread> m_Thread;
    };


}


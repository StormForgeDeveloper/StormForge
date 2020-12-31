////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Zookeeper warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

#define USE_ZOOKEEPER

#ifdef USE_ZOOKEEPER
#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "Task/SFTask.h"
#include "json/json.h"

struct ACL_vector;
struct String_vector;
struct Stat;
typedef struct _zhandle zhandle_t;
typedef struct zoo_op_result zoo_op_result_t;
typedef struct zoo_op zoo_op_t;


namespace SF
{
	constexpr size_t ZOOKEEPER_STAT_BUFFER_SIZE = 128;
	constexpr size_t ZOOKEEPER_CLIENTID_BUFFER_SIZE = 32;


	class Zookeeper;


	///////////////////////////////////////////////////////////////////////////////////
	//
	//	Watcher class for the Zookeeper
	//

	class ZookeeperWatcher
	{
	public:

#pragma pack(push, 2)
		union ZKEvent
		{
			struct {
				StringCrc32 NodePath;
				int16_t State;
				int16_t EventType;
			} Components;

			uint64_t Composited;

			ZKEvent() : Composited(0) {}
		};
#pragma pack(pop)



		/////////////////////////////////////////////////////////////////
		//
		//	Tasks for each result type
		//

		class ZookeeperTask : public Task
		{
		public:
			ZookeeperWatcher* ZKWatcher;
			Result ZKResult;

			ZookeeperTask(ZookeeperWatcher* watcher)
				: ZKWatcher(watcher)
			{}

			void SetResult(int zkResult);

			virtual void Run() override {}
		};


		class StringTask : public ZookeeperTask
		{
		public:
			String ResultString;

			StringTask(IHeap& heap, ZookeeperWatcher* watcher)
				: ZookeeperTask(watcher)
				, ResultString(heap)
			{}
		};


		class StringsTask : public ZookeeperTask
		{
		public:
			DynamicArray<String> ResultStrings;

			StringsTask(IHeap& memoryManager, ZookeeperWatcher* watcher)
				: ZookeeperTask(watcher)
				, ResultStrings(memoryManager)
			{}
		};


		class StringsStatTask : public ZookeeperTask
		{
		public:
			DynamicArray<String> ResultStrings;
			uint8_t ResultStatBuffer[ZOOKEEPER_STAT_BUFFER_SIZE];
			Stat* ResultStat;


			StringsStatTask(IHeap& memoryManager, ZookeeperWatcher* watcher)
				: ZookeeperTask(watcher)
				, ResultStrings(memoryManager)
			{
				ResultStat = (Stat*)ResultStatBuffer;
				memset(ResultStatBuffer, 0, sizeof(ResultStatBuffer));
			}
		};


		class StatTask : public ZookeeperTask
		{
		public:
			uint8_t ResultStatBuffer[ZOOKEEPER_STAT_BUFFER_SIZE];
			Stat *ResultStat;

			StatTask(ZookeeperWatcher* watcher)
				: ZookeeperTask(watcher)
			{
				ResultStat = (Stat*)ResultStatBuffer;
				memset(ResultStatBuffer, 0, sizeof(ResultStatBuffer));
			}
		};


		class DataTask : public ZookeeperTask
		{
		public:
			DynamicArray<uint8_t> ResultData;

			DataTask(IHeap& heap, ZookeeperWatcher* watcher)
				: ZookeeperTask(watcher)
				, ResultData(heap)
			{}
		};

/*
		class ACLTask : public ZookeeperTask
		{
		public:
			StaticArray<ACL, 10> ResultACL;

			ACLTask(IHeap& memoryManager, ZookeeperWatcher& watcher)
				: ZookeeperTask(watcher)
				, ResultACL(memoryManager)
			{}
		};
*/
	private:

		// State of zoo keeper server
		std::atomic<int> m_State;

		// Zookeeper event queue
		CircularPageQueueAtomic<uint64_t> m_EventQueue;

		Zookeeper *m_ZKInstance = nullptr;

	private:

		void SetZKInstance(Zookeeper* pZKInstance) { m_ZKInstance = pZKInstance; }

		static void ZKWatcherCB(zhandle_t *zkHandle, int type, int state, const char *path, void*v);
		static void ZKWatcherCBComplition(int rc, const void *data);
		static void ZKWatcherCBStatComplition(int rc, const Stat *stat, const void *data);
		static void ZKWatcherCBDataComplition(int rc, const char *value, int value_len, const Stat *stat, const void *data);
		static void ZKWatcherCBStringsComplition(int rc, const String_vector *strings, const void *data);
		static void ZKWatcherCBStringsStatComplition(int rc, const String_vector *strings, const Stat *stat, const void *data);
		static void ZKWatcherCBStringComplition(int rc, const char *value, const void *data);
		//static void ZKWatcherCBACLComplition(int rc, ACL_vector *acl, Stat *stat, const void *data);

		friend class Zookeeper;

	public:

		ZookeeperWatcher(IHeap& memoryManager);
		virtual ~ZookeeperWatcher() {}

		Zookeeper* GetZKInstance() { return m_ZKInstance; }


		int GetState() const { return m_State.load(std::memory_order_relaxed); }

		// Dequeue Zookeeper event
		Result DequeueEvent(ZKEvent& eventOut);

		/////////////////////////////////////////////
		//
		//	Overridable Event handling
		//

		virtual Result OnNewEvent(const ZKEvent& eventOut);
		virtual void OnComplition(ZookeeperTask& pTask);
		virtual void OnStatComplition(StatTask& pTask);
		virtual void OnDataComplition(DataTask& pTask);
		virtual void OnStringsComplition(StringsTask& pTask);
		virtual void OnStringsStatComplition(StringsStatTask& pTask);
		virtual void OnStringComplition(StringTask& pTask);
		//virtual void OnACLComplition(ACLTask& pTask);
	};



	///////////////////////////////////////////////////////////////////////////////////
	//
	//	Zookeeper API wrapper
	//

	class Zookeeper
	{
	public:

		typedef ZookeeperWatcher::ZKEvent			ZKEvent;
		typedef ZookeeperWatcher::ZookeeperTask		ZookeeperTask;
		//typedef ZookeeperWatcher::ACLTask			ACLTask;
		typedef ZookeeperWatcher::StringTask		StringTask;
		typedef ZookeeperWatcher::StringsTask		StringsTask;
		typedef ZookeeperWatcher::StringsStatTask	StringsStatTask;
		typedef ZookeeperWatcher::StatTask			StatTask;
		typedef ZookeeperWatcher::DataTask			DataTask;

		// constants

		static const int NODE_FLAG_EPHEMERAL;
		static const int NODE_FLAG_SEQUENCE;

		static const int STATE_SESSION_EXPIRED;
		static const int STATE_CONNECTED;
		static const int STATE_CONNECTING;

		static const int EVENT_CREATED;
		static const int EVENT_DELETED;
		static const int EVENT_CHANGED; // value changed
		static const int EVENT_CHILD;
		static const int EVENT_SESSION;
		static const int EVENT_NO_WATCHING;


		static const char* FlagToString(int iFlag);
		static const char* StateToString(int iState);
		static const char* EventToString(int iEvent);

	private:

		IHeap& m_Heap;

		// ZK handle lock
		CriticalSection m_handleLock;

		// Zookeeper handle
		zhandle_t* m_ZKHandle = nullptr;

		// State of zoo keeper server
		//std::atomic<int> m_State;

		// Zookeeper client id
		uint8_t ClientIDBuffer[ZOOKEEPER_STAT_BUFFER_SIZE];
		void* m_ClientID;

		// Watcher for main Zookeeper connection
		ZookeeperWatcher m_ZKWatcher;

		// Zookeeper log level
		uint32_t m_LogLevel;

		SortedSet<ZookeeperWatcher*> m_RegisteredWatcher;

	private:

		void AddWatcher(ZookeeperWatcher* pWatcher);

	public:

		Zookeeper(IHeap& heap, uint32_t debugLogLevel = 0);
		~Zookeeper();

		IHeap& GetHeap() { return m_Heap; }

		/////////////////////////////////////////////////////////////
		//
		//	
		//

		ZookeeperWatcher& GetWatcher() { return m_ZKWatcher; }

		SortedSet<ZookeeperWatcher*>& GetRegisteredWatchers() { return m_RegisteredWatcher; }



		// check connection status
		bool IsConnected() const;
		int GetState() const { return m_ZKHandle == nullptr ? 0 : m_ZKWatcher.GetState(); }

		// Close
		void Close();

		// Connect to Zookeeper server
		Result Connect(const char* connectionString);

		// Dequeue Zookeeper event
		Result DequeueEvent(ZKEvent& eventOut) { return m_ZKWatcher.DequeueEvent(eventOut); }

		// Yield until it has something or time out
		void yield(DurationMS duration);

		// Wait for connected state
		bool WaitForConnected();

		// Wait for disconnected state
		bool WaitForDisconnected();


		static Result ToResult(int zkResult);

		static String GetLeapNodeName(const String& nodePath);


		/////////////////////////////////////////////////////////////
		//
		//	Operations
		//

		// The one 'A' prefix works as asynchronous
		Result Create(const char* path, const Array<uint8_t>& value, const struct ACL_vector *acl, int flags, String& outPath);
		Result Create(const char* path, const Json::Value& value, const struct ACL_vector *acl, int flags, String& outPath);
		SharedPointerT<StringTask> ACreate(const char* path, const Array<uint8_t>& value, const struct ACL_vector *acl, int flags);
		SharedPointerT<StringTask> ACreate(const char* path, const Json::Value& value, const struct ACL_vector *acl, int flags);

		Result Delete(const char* path, int version = -1);
		SharedPointerT<ZookeeperTask> ADelete(const char* path, int version = -1);

		Result DeleteTree(const char* path);

		Result Exists(const char* path);
		SharedPointerT<StatTask> AExists(const char* path, ZookeeperWatcher* watcher = nullptr);

		Result Get(const char *path, Array<uint8_t>& valueBuffer, struct Stat *stat = nullptr);
		Result Get(const char *path, Json::Value& jsonValue);
		SharedPointerT<DataTask> AGet(const char *path, ZookeeperWatcher* watcher = nullptr);

		Result Set(const char *path, const Array<uint8_t>& valueBuffer, int version = -1);
		Result Set(const char *path, const Json::Value& value, int version = -1);
		SharedPointerT<StatTask> ASet(const char *path, const Array<uint8_t>& valueBuffer, int version = -1);
		SharedPointerT<StatTask> ASet(const char *path, const Json::Value& value, int version = -1);

		Result GetChildren(const char *path, Array<String>& strings, bool watch = false);
		SharedPointerT<StringsTask> AGetChildren(const char *path, ZookeeperWatcher* watcher = nullptr);
		SharedPointerT<StringsStatTask> AGetChildren2(const char *path, ZookeeperWatcher* watcher = nullptr);

		Result GetAcl(const char *path, struct ACL_vector *acl, struct Stat *stat);

		Result SetAcl(const char *path, int version, struct ACL_vector *acl);

		Result BatchRun(int count, const zoo_op_t *ops, zoo_op_result_t *results);
	};

}
#endif


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : ZooKeeper warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#if SF_PLATFORM == SF_PLATFORM_WINDOWS || SF_PLATFORM == SF_PLATFORM_LINUX
#define USE_ZOOKEEPER
#endif

#ifdef USE_ZOOKEEPER
#include "String/SFFixedString32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "Task/SFTask.h"
#include "json/json.h"

struct ACL_vector;
struct String_vector;
struct Stat;
typedef struct _zhandle zhandle_t;
typedef struct clientid clientid_t;
typedef struct zoo_op_result zoo_op_result_t;
typedef struct zoo_op zoo_op_t;


namespace SF
{
	constexpr size_t ZOOKEEPER_STAT_BUFFER_SIZE = 128;
	constexpr size_t ZOOKEEPER_CLIENTID_BUFFER_SIZE = 32;


	class ZooKeeper;


	///////////////////////////////////////////////////////////////////////////////////
	//
	//	Watcher class for the ZooKeeper
	//

	class ZooKeeperWatcher
	{
	public:

#pragma pack(push, 2)
		union ZKEvent
		{
			struct {
				FixedString32 NodePath;
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

		class ZooKeeperTask : public Task
		{
		public:
			ZooKeeperWatcher& ZKWatcher;
			Result ZKResult;

			ZooKeeperTask(ZooKeeperWatcher& watcher)
				: ZKWatcher(watcher)
			{}

			void SetResult(int zkResult);

			virtual void Run() override {}
		};


		class StringTask : public ZooKeeperTask
		{
		public:
			String ResultString;

			StringTask(IHeap& memoryManager, ZooKeeperWatcher& watcher)
				: ZooKeeperTask(watcher)
				, ResultString(memoryManager)
			{}
		};


		class StringsTask : public ZooKeeperTask
		{
		public:
			DynamicArray<String> ResultStrings;

			StringsTask(IHeap& memoryManager, ZooKeeperWatcher& watcher)
				: ZooKeeperTask(watcher)
				, ResultStrings(memoryManager)
			{}
		};


		class StringsStatTask : public ZooKeeperTask
		{
		public:
			DynamicArray<String> ResultStrings;
			uint8_t ResultStatBuffer[ZOOKEEPER_STAT_BUFFER_SIZE];
			Stat* ResultStat;


			StringsStatTask(IHeap& memoryManager, ZooKeeperWatcher& watcher)
				: ZooKeeperTask(watcher)
				, ResultStrings(memoryManager)
			{
				ResultStat = (Stat*)ResultStatBuffer;
				memset(ResultStatBuffer, 0, sizeof(ResultStatBuffer));
			}
		};


		class StatTask : public ZooKeeperTask
		{
		public:
			uint8_t ResultStatBuffer[ZOOKEEPER_STAT_BUFFER_SIZE];
			Stat *ResultStat;

			StatTask(ZooKeeperWatcher& watcher)
				: ZooKeeperTask(watcher)
			{
				ResultStat = (Stat*)ResultStatBuffer;
				memset(ResultStatBuffer, 0, sizeof(ResultStatBuffer));
			}
		};


		class DataTask : public ZooKeeperTask
		{
		public:
			DynamicArray<uint8_t> ResultData;

			DataTask(IHeap& memoryManager, ZooKeeperWatcher& watcher)
				: ZooKeeperTask(watcher)
				, ResultData(memoryManager)
			{}
		};

/*
		class ACLTask : public ZooKeeperTask
		{
		public:
			StaticArray<ACL, 10> ResultACL;

			ACLTask(IHeap& memoryManager, ZooKeeperWatcher& watcher)
				: ZooKeeperTask(watcher)
				, ResultACL(memoryManager)
			{}
		};
*/
	private:

		// State of zoo keeper server
		std::atomic<int> m_State;

		// Zookeeper event queue
		CircularPageQueueAtomic<uint64_t> m_EventQueue;

		ZooKeeper *m_ZKInstance = nullptr;

	private:

		void SetZKInstance(ZooKeeper* pZKInstance) { m_ZKInstance = pZKInstance; }

		static void ZKWatcherCB(zhandle_t *zkHandle, int type, int state, const char *path, void*v);
		static void ZKWatcherCBComlition(int rc, const void *data);
		static void ZKWatcherCBStatComlition(int rc, const Stat *stat, const void *data);
		static void ZKWatcherCBDataComlition(int rc, const char *value, int value_len, const Stat *stat, const void *data);
		static void ZKWatcherCBStringsComlition(int rc, const String_vector *strings, const void *data);
		static void ZKWatcherCBStringsStatComlition(int rc, const String_vector *strings, const Stat *stat, const void *data);
		static void ZKWatcherCBStringComlition(int rc, const char *value, const void *data);
		//static void ZKWatcherCBACLComlition(int rc, ACL_vector *acl, Stat *stat, const void *data);

		friend class ZooKeeper;

	public:

		ZooKeeperWatcher(IHeap& memoryManager);
		virtual ~ZooKeeperWatcher() {}

		ZooKeeper* GetZKInstance() { return m_ZKInstance; }


		int GetState() const { return m_State.load(std::memory_order_relaxed); }

		// Dequeue ZooKeeper event
		Result DequeueEvent(ZKEvent& eventOut);

		/////////////////////////////////////////////
		//
		//	Overridable Event handling
		//

		virtual Result OnNewEvent(const ZKEvent& eventOut);
		virtual void OnComlition(ZooKeeperTask& pTask);
		virtual void OnStatComlition(StatTask& pTask);
		virtual void OnDataComlition(DataTask& pTask);
		virtual void OnStringsComlition(StringsTask& pTask);
		virtual void OnStringsStatComlition(StringsStatTask& pTask);
		virtual void OnStringComlition(StringTask& pTask);
		//virtual void OnACLComlition(ACLTask& pTask);
	};



	///////////////////////////////////////////////////////////////////////////////////
	//
	//	ZooKeeper API wrapper
	//

	class ZooKeeper
	{
	public:

		typedef ZooKeeperWatcher::ZKEvent			ZKEvent;
		typedef ZooKeeperWatcher::ZooKeeperTask		ZooKeeperTask;
		//typedef ZooKeeperWatcher::ACLTask			ACLTask;
		typedef ZooKeeperWatcher::StringTask		StringTask;
		typedef ZooKeeperWatcher::StringsTask		StringsTask;
		typedef ZooKeeperWatcher::StringsStatTask	StringsStatTask;
		typedef ZooKeeperWatcher::StatTask			StatTask;
		typedef ZooKeeperWatcher::DataTask			DataTask;

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


	private:

		IHeap& m_Heap;

		// ZooKeeper handle
		zhandle_t* m_ZKHandle = nullptr;

		// State of zoo keeper server
		std::atomic<int> m_State;

		// ZooKeeper client id
		uint8_t ClientIDBuffer[ZOOKEEPER_STAT_BUFFER_SIZE];
		clientid_t* m_ClientID;

		// Watcher for main Zookeeper connection
		ZooKeeperWatcher m_ZKWatcher;

		// Zookeeper log level
		uint32_t m_LogLevel;

		SortedSet<ZooKeeperWatcher*> m_RegisteredWatcher;

	private:

		void AddWatcher(ZooKeeperWatcher* pWatcher);

	public:

		ZooKeeper(IHeap& memoryManager, uint32_t debugLogLevel = 0);
		~ZooKeeper();

		IHeap& GetHeap() { return m_Heap; }

		/////////////////////////////////////////////////////////////
		//
		//	
		//

		ZooKeeperWatcher& GetWatcher() { return m_ZKWatcher; }

		SortedSet<ZooKeeperWatcher*>& GetRegisteredWatchers() { return m_RegisteredWatcher; }



		// check connection status
		bool IsConnected() const;
		int GetState() const { return m_ZKHandle == nullptr ? 0 : m_ZKWatcher.GetState(); }

		// Close
		void Close();

		// Connect to ZooKeeper server
		Result Connect(const char* connectionString);

		// Dequeue ZooKeeper event
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
		SharedPointerT<ZooKeeperTask> ADelete(const char* path, int version = -1);

		Result DeleteTree(const char* path);

		Result Exists(const char* path);
		SharedPointerT<StatTask> AExists(const char* path, ZooKeeperWatcher* watcher = nullptr);

		Result Get(const char *path, Array<uint8_t>& valueBuffer, struct Stat *stat = nullptr);
		Result Get(const char *path, Json::Value& jsonValue);
		SharedPointerT<DataTask> AGet(const char *path, ZooKeeperWatcher* watcher = nullptr);

		Result Set(const char *path, const Array<uint8_t>& valueBuffer, int version = -1);
		Result Set(const char *path, const Json::Value& value, int version = -1);
		SharedPointerT<StatTask> ASet(const char *path, const Array<uint8_t>& valueBuffer, int version = -1);
		SharedPointerT<StatTask> ASet(const char *path, const Json::Value& value, int version = -1);

		Result GetChildren(const char *path, Array<String>& strings, bool watch = false);
		SharedPointerT<StringsTask> AGetChildren(const char *path, ZooKeeperWatcher* watcher = nullptr);
		SharedPointerT<StringsStatTask> AGetChildren2(const char *path, ZooKeeperWatcher* watcher = nullptr);

		Result GetAcl(const char *path, struct ACL_vector *acl, struct Stat *stat);

		Result SetAcl(const char *path, int version, struct ACL_vector *acl);

		Result BatchRun(int count, const zoo_op_t *ops, zoo_op_result_t *results);
	};

}
#endif


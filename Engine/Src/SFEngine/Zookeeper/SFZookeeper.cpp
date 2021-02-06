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

#include "SFEnginePCH.h"

#include "Zookeeper/SFZookeeper.h"
#include "String/SFStringFormat.h"

#ifdef USE_ZOOKEEPER

#include "zookeeper.h"


static_assert(SF::ZOOKEEPER_STAT_BUFFER_SIZE >= sizeof(Stat), "We need enough stat buffer size");
static_assert(SF::ZOOKEEPER_CLIENTID_BUFFER_SIZE >= sizeof(clientid_t), "We need enough stat buffer size");


namespace SF
{


	void ZookeeperWatcher::ZookeeperTask::SetResult(int zkResult)
	{
		ZKResult = Zookeeper::ToResult(zkResult);
		if (!ZKResult && GetState() == State::Pending)
		{
			Finished();
		}
	}

	ZookeeperWatcher::ZookeeperWatcher(IHeap& memoryManager)
		: m_EventQueue(memoryManager)
		, m_State(0)
	{
	}

	void ZookeeperWatcher::ZKWatcherCB(zhandle_t *zkHandle, int type, int state, const char *path, void*v)
	{
		auto zkWatcher = (ZookeeperWatcher*)v;
		ZKEvent evt;

		if (type == Zookeeper::EVENT_SESSION)
		{
			auto previousState = zkWatcher->m_State.exchange(state, std::memory_order_release);

			evt.Components.State = state;
			evt.Components.EventType = type;
			zkWatcher->OnNewEvent(evt);

			SFLog(System, Info, "ZK Connected prev:{0}, new:{1}", Zookeeper::StateToString(previousState), Zookeeper::StateToString(state));

			auto zkInstance = zkWatcher->GetZKInstance();
			for (auto itRegistered : zkInstance->GetRegisteredWatchers())
			{
				if (itRegistered != zkWatcher && itRegistered->m_State.load(std::memory_order_relaxed) != state)
				{
					itRegistered->m_State.store(state, std::memory_order_release);
					itRegistered->OnNewEvent(evt);
				}
			}
		}
		else
		{
			evt.Components.NodePath = Service::StringDB->AddNGetString32(path);
			evt.Components.State = state;
			evt.Components.EventType = type;
			SFLog(System, Info, "ZK Event node:{0}, event:{1}", path, Zookeeper::EventToString(type));
			zkWatcher->OnNewEvent(evt);
		}
	}

	void ZookeeperWatcher::ZKWatcherCBComplition(int rc, const void *data)
	{
		auto pTask = (ZookeeperTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = Zookeeper::ToResult(rc);
		TaskOperator().Finished(pTask);
		if (pTask->ZKWatcher)
			pTask->ZKWatcher->OnComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZookeeperWatcher::ZKWatcherCBStatComplition(int rc, const Stat *stat, const void *data)
	{
		auto pTask = (StatTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = Zookeeper::ToResult(rc);
		if(stat != nullptr)
			*pTask->ResultStat = *stat;
		TaskOperator().Finished(pTask);
		if (pTask->ZKWatcher)
			pTask->ZKWatcher->OnStatComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZookeeperWatcher::ZKWatcherCBDataComplition(int rc, const char *value, int value_len, const Stat *stat, const void *data)
	{
		auto pTask = (DataTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = Zookeeper::ToResult(rc);
		pTask->ResultData.resize(value_len);
		memcpy(pTask->ResultData.data(), value, value_len);
		TaskOperator().Finished(pTask);
		if (pTask->ZKWatcher)
			pTask->ZKWatcher->OnDataComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZookeeperWatcher::ZKWatcherCBStringsComplition(int rc, const String_vector *strings, const void *data)
	{
		auto pTask = (StringsTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = Zookeeper::ToResult(rc);
		if (strings != nullptr)
		{
			pTask->ResultStrings.resize(strings->count);
			for (int iStr = 0; iStr < strings->count; iStr++)
			{
				pTask->ResultStrings[iStr] = strings->data[iStr];
			}
		}
		TaskOperator().Finished(pTask);

		if (pTask->ZKWatcher)
			pTask->ZKWatcher->OnStringsComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZookeeperWatcher::ZKWatcherCBStringsStatComplition(int rc, const String_vector *strings, const Stat *stat, const void *data)
	{
		auto pTask = (StringsStatTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = Zookeeper::ToResult(rc);
		if (strings != nullptr)
		{
			pTask->ResultStrings.resize(strings->count);
			for (int iStr = 0; iStr < strings->count; iStr++)
			{
				pTask->ResultStrings[iStr] = strings->data[iStr];
			}
		}
		*pTask->ResultStat = *stat;
		TaskOperator().Finished(pTask);
		if (pTask->ZKWatcher)
			pTask->ZKWatcher->OnStringsStatComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZookeeperWatcher::ZKWatcherCBStringComplition(int rc, const char *value, const void *data)
	{
		auto pTask = (StringTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = Zookeeper::ToResult(rc);
		pTask->ResultString = value;
		TaskOperator().Finished(pTask);

		if (pTask->ZKWatcher)
			pTask->ZKWatcher->OnStringComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	//void ZookeeperWatcher::ZKWatcherCBACLComplition(int rc, ACL_vector *acl, Stat *stat, const void *data)
	//{
	//	auto pTask = (ACLTask*)data;
	//	TaskOperator().StartWorking(pTask);
	//	pTask->Result = Zookeeper::ToResult(rc);
	//	if (acl != nullptr)
	//	{
	//		pTask->ResultACL.resize(acl->count);
	//		memcpy(pTask->ResultACL.data(), acl->data, sizeof(ACL)*acl->count);
	//	}
	//	TaskOperator().Finished(pTask);
	//	pTask->ZKWatcher.OnACLComplition(*pTask);
	//	SharedReferenceDec(static_cast<SharedObject*>(pTask));
	//}



	Result ZookeeperWatcher::DequeueEvent(ZKEvent& eventOut)
	{
		return m_EventQueue.Dequeue(eventOut.Composited);
	}

	Result ZookeeperWatcher::OnNewEvent(const ZKEvent& eventOut)
	{
		return m_EventQueue.Enqueue(eventOut.Composited);
	}

	void ZookeeperWatcher::OnComplition(ZookeeperTask& pTask)
	{
	}

	void ZookeeperWatcher::OnStatComplition(StatTask& pTask)
	{
	}

	void ZookeeperWatcher::OnDataComplition(DataTask& pTask)
	{
	}

	void ZookeeperWatcher::OnStringsComplition(StringsTask& pTask)
	{
	}

	void ZookeeperWatcher::OnStringsStatComplition(StringsStatTask& pTask)
	{
	}

	void ZookeeperWatcher::OnStringComplition(StringTask& pTask)
	{
	}

	//void ZookeeperWatcher::OnACLComplition(ACLTask& pTask)
	//{
	//}



	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Zookeeper class
	//

	const int Zookeeper::NODE_FLAG_EPHEMERAL = ZOO_EPHEMERAL;
	const int Zookeeper::NODE_FLAG_SEQUENCE = ZOO_SEQUENCE;

	const int Zookeeper::STATE_SESSION_EXPIRED = ZOO_EXPIRED_SESSION_STATE;
	const int Zookeeper::STATE_CONNECTED = ZOO_CONNECTED_STATE;
	const int Zookeeper::STATE_CONNECTING = ZOO_CONNECTING_STATE;

	const int Zookeeper::EVENT_CREATED = ZOO_CREATED_EVENT;
	const int Zookeeper::EVENT_DELETED = ZOO_DELETED_EVENT;
	const int Zookeeper::EVENT_CHANGED = ZOO_CHANGED_EVENT; // value changed
	const int Zookeeper::EVENT_CHILD = ZOO_CHILD_EVENT;
	const int Zookeeper::EVENT_SESSION = ZOO_SESSION_EVENT;
	const int Zookeeper::EVENT_NO_WATCHING = ZOO_NOTWATCHING_EVENT;


	Json::CharReaderBuilder Zookeeper::stm_JsonBuilder;


	const char* Zookeeper::FlagToString(int iFlag)
	{
		static char FlagString[128];

		if (iFlag == ZOO_EPHEMERAL) return "ZOO_EPHEMERAL";
		else if (iFlag == ZOO_SEQUENCE) return "ZOO_SEQUENCE";
		else
		{
			StrUtil::Format(FlagString, "Flag({0})", iFlag);
			return FlagString;
		}
	}


	const char* Zookeeper::StateToString(int iState)
	{
		static char StateString[128];

		if (iState == STATE_SESSION_EXPIRED) return "STATE_SESSION_EXPIRED";
		else if (iState == STATE_CONNECTED) return "STATE_CONNECTED";
		else if (iState == STATE_CONNECTING) return "STATE_CONNECTING";
		else if (iState == ZOO_EXPIRED_SESSION_STATE) return "ZOO_EXPIRED_SESSION_STATE";
		else if (iState == ZOO_AUTH_FAILED_STATE) return "ZOO_AUTH_FAILED_STATE";
		else if (iState == ZOO_ASSOCIATING_STATE) return "ZOO_ASSOCIATING_STATE";
		else if (iState == ZOO_READONLY_STATE) return "ZOO_READONLY_STATE";
		else if (iState == ZOO_NOTCONNECTED_STATE) return "ZOO_NOTCONNECTED_STATE";
		else
		{
			StrUtil::Format(StateString, "State({0})", iState);
			return StateString;
		}
	}

	const char* Zookeeper::EventToString(int iEvent)
	{
		static char EventString[128];

		if (iEvent == ZOO_CREATED_EVENT) return "ZOO_CREATED_EVENT";
		else if (iEvent == ZOO_DELETED_EVENT) return "ZOO_DELETED_EVENT";
		else if (iEvent == ZOO_CHANGED_EVENT) return "ZOO_CHANGED_EVENT";
		else if (iEvent == ZOO_CHILD_EVENT) return "ZOO_CHILD_EVENT";
		else if (iEvent == ZOO_SESSION_EVENT) return "ZOO_SESSION_EVENT";
		else if (iEvent == ZOO_NOTWATCHING_EVENT) return "ZOO_NOTWATCHING_EVENT";
		else
		{
			StrUtil::Format(EventString, "Event({0})", iEvent);
			return EventString;
		}
	}


	Zookeeper::Zookeeper(IHeap& heap, uint32_t debugLogLevel)
		: m_Heap(heap)
		, m_ZKHandle(nullptr)
		, m_ZKWatcher(heap)
		, m_LogLevel(debugLogLevel)
		, m_RegisteredWatcher(m_Heap)
	{
		m_ClientID = (clientid_t*)ClientIDBuffer;
		memset(m_ClientID, 0, sizeof(clientid_t));

		m_ZKWatcher.SetZKInstance(this);

		if (m_LogLevel == 0)
			m_LogLevel = ZOO_LOG_LEVEL_WARN;
	}

	Zookeeper::~Zookeeper()
	{
		Close();
	}

	void Zookeeper::AddWatcher(ZookeeperWatcher* pWatcher)
	{
		if (pWatcher == nullptr)
			return;

		if (pWatcher == &m_ZKWatcher)
			return;

		if (m_RegisteredWatcher.Find(pWatcher))
			return;

		pWatcher->SetZKInstance(this);

		m_RegisteredWatcher.Insert(pWatcher);
	}

	bool Zookeeper::IsConnected() const
	{
		return m_ZKHandle != nullptr && m_ZKWatcher.GetState() == STATE_CONNECTED;
	}

	void Zookeeper::Close()
	{
		MutexScopeLock lock(m_handleLock);

		if (m_ZKHandle != nullptr)
			zookeeper_close(m_ZKHandle);
		m_ZKHandle = nullptr;
	}

	Result Zookeeper::Connect(const char* connectionString)
	{
		MutexScopeLock lock(m_handleLock);

		Close();

		zoo_set_debug_level((ZooLogLevel)m_LogLevel);

		clientid_t* previousClientID = reinterpret_cast<clientid_t*>(m_ClientID)->client_id != 0 ? reinterpret_cast<clientid_t*>(m_ClientID) : nullptr;
		m_ZKHandle = zookeeper_init(connectionString, ZookeeperWatcher::ZKWatcherCB, 10000, previousClientID, &m_ZKWatcher, 0);
		if (m_ZKHandle == nullptr)
		{
			return ResultCode::UNEXPECTED;
		}

		*reinterpret_cast<clientid_t*>(m_ClientID) = *zoo_client_id(m_ZKHandle);

		return ResultCode::SUCCESS;
	}



	void Zookeeper::yield(DurationMS duration)
	{
		if (m_ZKHandle == nullptr)
			return;

#if 1
		ThisThread::SleepFor(duration);
#else

#ifdef WIN32
		SF_SOCKET fd;
#else
		int fd;
#endif
		int interest;
		int events;
		struct timeval tv;
		int rc;
		time_t expires = time(0) + duration.count() / 1000;
		time_t timeLeft = duration.count() / 1000;
		fd_set rfds, wfds, efds;
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_ZERO(&efds);

		while (timeLeft >= 0)
		{
			zookeeper_interest(m_ZKHandle, &fd, &interest, &tv);
			if (fd != -1) {
				if (interest&ZOOKEEPER_READ) {
					FD_SET(fd, &rfds);
				}
				else {
					FD_CLR(fd, &rfds);
				}
				if (interest&ZOOKEEPER_WRITE) {
					FD_SET(fd, &wfds);
				}
				else {
					FD_CLR(fd, &wfds);
				}
			}
			else {
				fd = 0;
			}
			FD_SET(0, &rfds);
			if (tv.tv_sec > timeLeft) {
				tv.tv_sec = timeLeft;
			}
			rc = select(fd + 1, &rfds, &wfds, &efds, &tv);
			timeLeft = expires - time(0);
			events = 0;
			if (FD_ISSET(fd, &rfds)) {
				events |= ZOOKEEPER_READ;
			}
			if (FD_ISSET(fd, &wfds)) {
				events |= ZOOKEEPER_WRITE;
			}
			zookeeper_process(m_ZKHandle, events);
		}
#endif
	}

	bool Zookeeper::WaitForConnected()
	{
		if (m_ZKHandle == nullptr)
			return false;

		time_t expires = time(0) + 10;
		while (!IsConnected() && time(0) < expires)
		{
			yield(DurationMS(500));
		}

		return IsConnected();
	}

	bool Zookeeper::WaitForDisconnected()
	{
		if (m_ZKHandle == nullptr)
			return false;

		time_t expires = time(0) + 15;
		while (IsConnected() && time(0) < expires)
		{
			yield(DurationMS(500));
		}
		return !IsConnected();
	}

	Result Zookeeper::ToResult(int zkResult)
	{
		switch (zkResult)
		{
		case (int)ZOO_ERRORS::ZOK:						return ResultCode::SUCCESS;
		case (int)ZOO_ERRORS::ZSYSTEMERROR:				return ResultCode::ZK_SYSTEM;
		case (int)ZOO_ERRORS::ZRUNTIMEINCONSISTENCY:	return ResultCode::ZK_ZRUNTIMEINCONSISTENCY;
		case (int)ZOO_ERRORS::ZDATAINCONSISTENCY:		return ResultCode::ZK_ZDATAINCONSISTENCY;
		case (int)ZOO_ERRORS::ZCONNECTIONLOSS:			return ResultCode::ZK_ZCONNECTIONLOSS;
		case (int)ZOO_ERRORS::ZMARSHALLINGERROR:		return ResultCode::ZK_ZMARSHALLINGERROR;
		case (int)ZOO_ERRORS::ZUNIMPLEMENTED:			return ResultCode::ZK_ZUNIMPLEMENTED;
		case (int)ZOO_ERRORS::ZOPERATIONTIMEOUT:		return ResultCode::ZK_ZOPERATIONTIMEOUT;
		case (int)ZOO_ERRORS::ZBADARGUMENTS:			return ResultCode::ZK_ZBADARGUMENTS;
		case (int)ZOO_ERRORS::ZINVALIDSTATE:			return ResultCode::ZK_ZINVALIDSTATE;

		case (int)ZOO_ERRORS::ZAPIERROR:				return ResultCode::ZK_ZAPIERROR;
		case (int)ZOO_ERRORS::ZNONODE:					return ResultCode::ZK_ZNONODE; // Node does not exist
		case (int)ZOO_ERRORS::ZNOAUTH:					return ResultCode::ZK_ZNOAUTH; // Not authenticated
		case (int)ZOO_ERRORS::ZBADVERSION:				return ResultCode::ZK_ZBADVERSION;
		case (int)ZOO_ERRORS::ZNOCHILDRENFOREPHEMERALS:	return ResultCode::ZK_ZNOCHILDRENFOREPHEMERALS;
		case (int)ZOO_ERRORS::ZNODEEXISTS:				return ResultCode::ZK_ZNODEEXISTS;
		case (int)ZOO_ERRORS::ZNOTEMPTY:				return ResultCode::ZK_ZNOTEMPTY;
		case (int)ZOO_ERRORS::ZSESSIONEXPIRED:			return ResultCode::ZK_ZSESSIONEXPIRED;
		case (int)ZOO_ERRORS::ZINVALIDCALLBACK:			return ResultCode::ZK_ZINVALIDCALLBACK;
		case (int)ZOO_ERRORS::ZINVALIDACL:				return ResultCode::ZK_ZINVALIDACL;
		case (int)ZOO_ERRORS::ZAUTHFAILED:				return ResultCode::ZK_ZAUTHFAILED;
		case (int)ZOO_ERRORS::ZCLOSING:					return ResultCode::ZK_ZCLOSING;
		case (int)ZOO_ERRORS::ZNOTHING:					return ResultCode::ZK_ZNOTHING;
		case (int)ZOO_ERRORS::ZSESSIONMOVED:			return ResultCode::ZK_ZSESSIONMOVED;
		default:
			return ResultCode::UNEXPECTED;
		}
	}

	String Zookeeper::GetLeapNodeName(const String& nodePath)
	{
		DynamicArray<String> pathList(GetSystemHeap());
		nodePath.Split("/", true, pathList);
		if (pathList.size() > 0)
			return pathList[pathList.size() - 1];
		else
			return String();
	}



	/////////////////////////////////////////////////////////////
	//
	//	Operations
	//

	// The one with watcher works as asynchronous

	Result Zookeeper::Create(const char* path, const Array<uint8_t>& value, const struct ACL_vector *acl, int flags, String& outPath)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto valueData = value.size() > 0 ? value.data() : nullptr;
		int valueSize = value.size() > 0 ? (int)value.size() : -1;

		if (acl == nullptr)
			acl = &ZOO_OPEN_ACL_UNSAFE;

		StaticArray<char, 1024> nameBuffer(m_Heap);

		auto zkResult = zoo_create(m_ZKHandle, path, (const char*)valueData, valueSize, acl, flags, nameBuffer.data(), (int)nameBuffer.GetAllocatedSize());
		if (zkResult == ZOK)
			outPath = nameBuffer.data();

		return ToResult(zkResult);
	}

	Result Zookeeper::Create(const char* path, const Json::Value& value, const struct ACL_vector *acl, int flags, String& outPath)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		if (acl == nullptr)
			acl = &ZOO_OPEN_ACL_UNSAFE;

		Json::StreamWriterBuilder builder;
		builder["indentation"] = "";
		auto valueBuffer = std::forward<std::string>(Json::writeString(builder, value));

		StaticArray<char, 1024> nameBuffer(m_Heap);
		auto zkResult = zoo_create(m_ZKHandle, path, (const char*)valueBuffer.data(), (int)valueBuffer.size(), acl, flags, nameBuffer.data(), (int)nameBuffer.GetAllocatedSize());
		if (zkResult == ZOK)
			outPath = nameBuffer.data();

		return ToResult(zkResult);
	}

	SharedPointerT<Zookeeper::StringTask> Zookeeper::ACreate(const char* path, const Array<uint8_t>& value, const struct ACL_vector *acl, int flags)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::StringTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::StringTask>();

		auto valueData = value.size() > 0 ? value.data() : nullptr;
		int valueSize = value.size() > 0 ? (int)value.size() : -1;

		if (acl == nullptr)
			acl = &ZOO_OPEN_ACL_UNSAFE;

		SharedPointerT<StringTask> pTask = new(m_Heap) StringTask(m_Heap, &GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		auto zkResult = zoo_acreate(m_ZKHandle, path, (const char*)valueData, valueSize, acl, flags, ZookeeperWatcher::ZKWatcherCBStringComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<StringTask>>(pTask);
	}

	SharedPointerT<Zookeeper::StringTask> Zookeeper::ACreate(const char* path, const Json::Value& value, const struct ACL_vector *acl, int flags)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::StringTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::StringTask>();


		if (acl == nullptr)
			acl = &ZOO_OPEN_ACL_UNSAFE;

		SharedPointerT<StringTask> pTask = new(m_Heap) StringTask(m_Heap, &GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));

		Json::StreamWriterBuilder builder;
		builder["indentation"] = "";
		auto valueBuffer = std::forward<std::string>(Json::writeString(builder, value));

		auto zkResult = zoo_acreate(m_ZKHandle, path, (const char*)valueBuffer.data(), (int)valueBuffer.size(), acl, flags, ZookeeperWatcher::ZKWatcherCBStringComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<StringTask>>(pTask);
	}

	Result Zookeeper::Delete(const char* path, int version)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_delete(m_ZKHandle, path, version);

		return ToResult(zkResult);
	}

	SharedPointerT<Zookeeper::ZookeeperTask> Zookeeper::ADelete(const char* path, int version)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::ZookeeperTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::ZookeeperTask>();

		SharedPointerT<ZookeeperTask> pTask = new(m_Heap) ZookeeperTask(&GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		auto zkResult = zoo_adelete(m_ZKHandle, path, version, ZookeeperWatcher::ZKWatcherCBComplition, *pTask);
		pTask->SetResult(zkResult);
		if(zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<Zookeeper::ZookeeperTask>>(pTask);
	}

	Result Zookeeper::DeleteTree(const char* path)
	{
		DynamicArray<String> children(GetHeap());
		Result result = GetChildren(path, children);
		if (!result)
			return result;

		for (auto& itChild : children)
		{
			String childPath(GetHeap());
			childPath.Format("{0}/{1}", path, itChild);
			result = DeleteTree(childPath);
			if (!result)
				return result;
		}

		return Delete(path);
	}



	Result Zookeeper::Exists(const char* path)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_exists(m_ZKHandle, path, 0, nullptr);

		return ToResult(zkResult);
	}

	SharedPointerT<Zookeeper::StatTask> Zookeeper::AExists(const char* path, ZookeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::StatTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::StatTask>();

		SharedPointerT<StatTask> pTask = new(m_Heap) StatTask(watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aexists(m_ZKHandle, path, 0, ZookeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		else
			zkResult = zoo_awexists(m_ZKHandle, path, ZookeeperWatcher::ZKWatcherCB, watcher, ZookeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<Zookeeper::StatTask>>(pTask);
	}

	Result Zookeeper::Get(const char *path, Array<uint8_t>& valueBuffer, struct Stat *stat)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		int buffLen = (int)valueBuffer.GetAllocatedSize();
		auto zkResult = zoo_get(m_ZKHandle, path, 0, (char*)valueBuffer.data(), &buffLen, stat);
		valueBuffer.resize(buffLen);

		return ToResult(zkResult);
	}

	Result Zookeeper::Get(const char *path, Json::Value& jsonValue, std::function<void()> validateFunc)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		Result res = ResultCode::SUCCESS;

		//if (validateFunc) validateFunc();

		StaticArray<uint8_t,2048> valueBuffer(GetHeap());
		int buffLen = (int)valueBuffer.GetAllocatedSize() - 1;
		auto zkResult = zoo_get(m_ZKHandle, path, 0, (char*)valueBuffer.data(), &buffLen, nullptr);
		valueBuffer.resize(buffLen);

		res = ToResult(zkResult);

		valueBuffer.push_back('\0');

		std::string errs;
		std::unique_ptr<Json::CharReader> jsonReader(stm_JsonBuilder.newCharReader());
		auto readStart = reinterpret_cast<const char*>(valueBuffer.data());
		bool bRes = jsonReader->parse(readStart, readStart + valueBuffer.size(), &jsonValue, &errs);
		if (validateFunc) validateFunc();
		if (!bRes)
		{
			SFLog(Net, Error, "Zookeeper::Get value parsing error:{0}", errs);
			return ResultCode::INVALID_STR_DATA;
		}
		if (validateFunc) validateFunc();

		return res;
	}

	SharedPointerT<Zookeeper::DataTask> Zookeeper::AGet(const char *path, ZookeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::DataTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::DataTask>();

		SharedPointerT<DataTask> pTask = new(m_Heap) DataTask(m_Heap, watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aget(m_ZKHandle, path, 0, ZookeeperWatcher::ZKWatcherCBDataComplition, *pTask);
		else
			zkResult = zoo_awget(m_ZKHandle, path, ZookeeperWatcher::ZKWatcherCB, watcher, ZookeeperWatcher::ZKWatcherCBDataComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<Zookeeper::DataTask>>(pTask);
	}

	Result Zookeeper::Set(const char *path, const Array<uint8_t>& valueBuffer, int version)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_set(m_ZKHandle, path, (char*)valueBuffer.data(), (int)valueBuffer.size(), version);

		return ToResult(zkResult);
	}

	Result Zookeeper::Set(const char *path, const Json::Value& value, int version)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		Json::StreamWriterBuilder builder;
		builder["indentation"] = "";
		auto valueBuffer = std::forward<std::string>(Json::writeString(builder, value));

		auto zkResult = zoo_set(m_ZKHandle, path, (char*)valueBuffer.data(), (int)valueBuffer.size(), version);

		return ToResult(zkResult);
	}

	SharedPointerT<Zookeeper::StatTask> Zookeeper::ASet(const char *path, const Array<uint8_t>& valueBuffer, int version)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::StatTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::StatTask>();

		SharedPointerT<StatTask> pTask = new(m_Heap) StatTask(&GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;
		zkResult = zoo_aset(m_ZKHandle, path, (char*)valueBuffer.data(), (int)valueBuffer.size(), version, ZookeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<Zookeeper::StatTask>>(pTask);
	}

	SharedPointerT<Zookeeper::StatTask> Zookeeper::ASet(const char *path, const Json::Value& value, int version)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::StatTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::StatTask>();

		SharedPointerT<StatTask> pTask = new(m_Heap) StatTask(&GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		Json::StreamWriterBuilder builder;
		builder["indentation"] = "";
		auto valueBuffer = std::forward<std::string>(Json::writeString(builder, value));
		zkResult = zoo_aset(m_ZKHandle, path, (char*)valueBuffer.data(), (int)valueBuffer.size(), version, ZookeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<Zookeeper::StatTask>>(pTask);
	}


	Result Zookeeper::GetChildren(const char *path, Array<String>& strings, bool watch)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		String_vector tempList{};

		auto zkResult = zoo_get_children(m_ZKHandle, path, watch ? 1 : 0, &tempList);
		strings.reserve(strings.size() + tempList.count);
		for (int iStr = 0; iStr < tempList.count; iStr++)
		{
			strings.push_back(String(strings.GetHeap(), tempList.data[iStr]));
		}

		return ToResult(zkResult);
	}

	SharedPointerT<Zookeeper::StringsTask> Zookeeper::AGetChildren(const char *path, ZookeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::StringsTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::StringsTask>();

		SharedPointerT<StringsTask> pTask = new(m_Heap) StringsTask(m_Heap, watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aget_children(m_ZKHandle, path, 0, ZookeeperWatcher::ZKWatcherCBStringsComplition, *pTask);
		else
			zkResult = zoo_awget_children(m_ZKHandle, path, ZookeeperWatcher::ZKWatcherCB, watcher, ZookeeperWatcher::ZKWatcherCBStringsComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<Zookeeper::StringsTask>>(pTask);
	}

	SharedPointerT<Zookeeper::StringsStatTask> Zookeeper::AGetChildren2(const char *path, ZookeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<Zookeeper::StringsStatTask>();

		if (!IsConnected())
			return SharedPointerT<Zookeeper::StringsStatTask>();

		SharedPointerT<StringsStatTask> pTask = new(m_Heap) StringsStatTask(m_Heap, watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aget_children2(m_ZKHandle, path, 0, ZookeeperWatcher::ZKWatcherCBStringsStatComplition, *pTask);
		else
			zkResult = zoo_awget_children2(m_ZKHandle, path, ZookeeperWatcher::ZKWatcherCB, watcher, ZookeeperWatcher::ZKWatcherCBStringsStatComplition, *pTask);

		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<Zookeeper::StringsStatTask>>(pTask);
	}



	Result Zookeeper::GetAcl(const char *path, struct ACL_vector *acl, struct Stat *stat)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_get_acl(m_ZKHandle, path, acl, stat);

		return ToResult(zkResult);
	}


	Result Zookeeper::SetAcl(const char *path, int version, struct ACL_vector *acl)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_set_acl(m_ZKHandle, path, version, acl);

		return ToResult(zkResult);
	}


	Result Zookeeper::BatchRun(int count, const zoo_op_t *ops, zoo_op_result_t *results)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_multi(m_ZKHandle, count, ops, results);

		return ToResult(zkResult);
	}

}

#endif

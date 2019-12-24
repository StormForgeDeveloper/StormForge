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

#include "SFEnginePCH.h"

#include "ZooKeeper/SFZooKeeper.h"

#ifdef USE_ZOOKEEPER


#include "zookeeper.h"


static_assert(SF::ZOOKEEPER_STAT_BUFFER_SIZE >= sizeof(Stat), "We need enough stat buffer size");
static_assert(SF::ZOOKEEPER_CLIENTID_BUFFER_SIZE >= sizeof(clientid_t), "We need enough stat buffer size");


namespace SF
{


	void ZooKeeperWatcher::ZooKeeperTask::SetResult(int zkResult)
	{
		ZKResult = ZooKeeper::ToResult(zkResult);
		if (!ZKResult && GetState() == State::Pending)
		{
			TaskOperator().Finished(this);
		}
	}

	ZooKeeperWatcher::ZooKeeperWatcher(IHeap& memoryManager)
		: m_EventQueue(memoryManager)
		, m_State(0)
	{
	}

	void ZooKeeperWatcher::ZKWatcherCB(zhandle_t *zkHandle, int type, int state, const char *path, void*v)
	{
		auto zkWatcher = (ZooKeeperWatcher*)v;
		ZKEvent evt;

		if (type == ZooKeeper::EVENT_SESSION)
		{
			auto previousState = zkWatcher->m_State.exchange(state, std::memory_order_release);

			evt.Components.State = state;
			evt.Components.EventType = type;
			zkWatcher->OnNewEvent(evt);

			SFLog(System, Info, "ZK Connected prev:{0}, new:{1}", previousState, state);

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
			SFLog(System, Info, "ZK Event node:{0}, event:{1}", path, type);
			zkWatcher->OnNewEvent(evt);
		}
	}

	void ZooKeeperWatcher::ZKWatcherCBComplition(int rc, const void *data)
	{
		auto pTask = (ZooKeeperTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = ZooKeeper::ToResult(rc);
		TaskOperator().Finished(pTask);
		pTask->ZKWatcher.OnComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZooKeeperWatcher::ZKWatcherCBStatComplition(int rc, const Stat *stat, const void *data)
	{
		auto pTask = (StatTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = ZooKeeper::ToResult(rc);
		if(stat != nullptr)
			*pTask->ResultStat = *stat;
		TaskOperator().Finished(pTask);
		pTask->ZKWatcher.OnStatComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZooKeeperWatcher::ZKWatcherCBDataComplition(int rc, const char *value, int value_len, const Stat *stat, const void *data)
	{
		auto pTask = (DataTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = ZooKeeper::ToResult(rc);
		pTask->ResultData.resize(value_len);
		memcpy(pTask->ResultData.data(), value, value_len);
		TaskOperator().Finished(pTask);
		pTask->ZKWatcher.OnDataComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZooKeeperWatcher::ZKWatcherCBStringsComplition(int rc, const String_vector *strings, const void *data)
	{
		auto pTask = (StringsTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = ZooKeeper::ToResult(rc);
		if (strings != nullptr)
		{
			pTask->ResultStrings.resize(strings->count);
			for (int iStr = 0; iStr < strings->count; iStr++)
			{
				pTask->ResultStrings[iStr] = strings->data[iStr];
			}
		}
		TaskOperator().Finished(pTask);
		pTask->ZKWatcher.OnStringsComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZooKeeperWatcher::ZKWatcherCBStringsStatComplition(int rc, const String_vector *strings, const Stat *stat, const void *data)
	{
		auto pTask = (StringsStatTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = ZooKeeper::ToResult(rc);
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
		pTask->ZKWatcher.OnStringsStatComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	void ZooKeeperWatcher::ZKWatcherCBStringComplition(int rc, const char *value, const void *data)
	{
		auto pTask = (StringTask*)data;
		TaskOperator().StartWorking(pTask);
		pTask->ZKResult = ZooKeeper::ToResult(rc);
		pTask->ResultString = value;
		TaskOperator().Finished(pTask);
		pTask->ZKWatcher.OnStringComplition(*pTask);
		SharedReferenceDec(static_cast<SharedObject*>(pTask));
	}

	//void ZooKeeperWatcher::ZKWatcherCBACLComplition(int rc, ACL_vector *acl, Stat *stat, const void *data)
	//{
	//	auto pTask = (ACLTask*)data;
	//	TaskOperator().StartWorking(pTask);
	//	pTask->Result = ZooKeeper::ToResult(rc);
	//	if (acl != nullptr)
	//	{
	//		pTask->ResultACL.resize(acl->count);
	//		memcpy(pTask->ResultACL.data(), acl->data, sizeof(ACL)*acl->count);
	//	}
	//	TaskOperator().Finished(pTask);
	//	pTask->ZKWatcher.OnACLComplition(*pTask);
	//	SharedReferenceDec(static_cast<SharedObject*>(pTask));
	//}



	Result ZooKeeperWatcher::DequeueEvent(ZKEvent& eventOut)
	{
		return m_EventQueue.Dequeue(eventOut.Composited);
	}

	Result ZooKeeperWatcher::OnNewEvent(const ZKEvent& eventOut)
	{
		return m_EventQueue.Enqueue(eventOut.Composited);
	}

	void ZooKeeperWatcher::OnComplition(ZooKeeperTask& pTask)
	{
	}

	void ZooKeeperWatcher::OnStatComplition(StatTask& pTask)
	{
	}

	void ZooKeeperWatcher::OnDataComplition(DataTask& pTask)
	{
	}

	void ZooKeeperWatcher::OnStringsComplition(StringsTask& pTask)
	{
	}

	void ZooKeeperWatcher::OnStringsStatComplition(StringsStatTask& pTask)
	{
	}

	void ZooKeeperWatcher::OnStringComplition(StringTask& pTask)
	{
	}

	//void ZooKeeperWatcher::OnACLComplition(ACLTask& pTask)
	//{
	//}



	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	ZooKeeper class
	//

	const int ZooKeeper::NODE_FLAG_EPHEMERAL = ZOO_EPHEMERAL;
	const int ZooKeeper::NODE_FLAG_SEQUENCE = ZOO_SEQUENCE;

	const int ZooKeeper::STATE_SESSION_EXPIRED = ZOO_EXPIRED_SESSION_STATE;
	const int ZooKeeper::STATE_CONNECTED = ZOO_CONNECTED_STATE;
	const int ZooKeeper::STATE_CONNECTING = ZOO_CONNECTING_STATE;

	const int ZooKeeper::EVENT_CREATED = ZOO_CREATED_EVENT;
	const int ZooKeeper::EVENT_DELETED = ZOO_DELETED_EVENT;
	const int ZooKeeper::EVENT_CHANGED = ZOO_CHANGED_EVENT; // value changed
	const int ZooKeeper::EVENT_CHILD = ZOO_CHILD_EVENT;
	const int ZooKeeper::EVENT_SESSION = ZOO_SESSION_EVENT;
	const int ZooKeeper::EVENT_NO_WATCHING = ZOO_NOTWATCHING_EVENT;


	ZooKeeper::ZooKeeper(IHeap& memoryManager, uint32_t debugLogLevel)
		: m_Heap(memoryManager)
		, m_ZKHandle(nullptr)
//		, m_State(0)
		, m_ZKWatcher(memoryManager)
		, m_LogLevel(debugLogLevel)
		, m_RegisteredWatcher(m_Heap)
	{
		m_ClientID = (clientid_t*)ClientIDBuffer;
		memset(m_ClientID, 0, sizeof(clientid_t));

		m_ZKWatcher.SetZKInstance(this);

		if (m_LogLevel == 0)
			m_LogLevel = ZOO_LOG_LEVEL_WARN;
	}

	ZooKeeper::~ZooKeeper()
	{
		Close();
	}

	void ZooKeeper::AddWatcher(ZooKeeperWatcher* pWatcher)
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

	bool ZooKeeper::IsConnected() const
	{
		return m_ZKHandle != nullptr && m_ZKWatcher.GetState() == STATE_CONNECTED;
	}

	void ZooKeeper::Close()
	{
		MutexScopeLock lock(m_handleLock);

		if (m_ZKHandle != nullptr)
			zookeeper_close(m_ZKHandle);
		m_ZKHandle = nullptr;
	}

	Result ZooKeeper::Connect(const char* connectionString)
	{
		MutexScopeLock lock(m_handleLock);

		Close();

		zoo_set_debug_level((ZooLogLevel)m_LogLevel);

		clientid_t* previousClientID = m_ClientID->client_id != 0 ? m_ClientID : nullptr;
		m_ZKHandle = zookeeper_init(connectionString, ZooKeeperWatcher::ZKWatcherCB, 10000, previousClientID, &m_ZKWatcher, 0);
		if (m_ZKHandle == nullptr)
		{
			return ResultCode::UNEXPECTED;
		}

		*m_ClientID = *zoo_client_id(m_ZKHandle);

		return ResultCode::SUCCESS;
	}



	void ZooKeeper::yield(DurationMS duration)
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

	bool ZooKeeper::WaitForConnected()
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

	bool ZooKeeper::WaitForDisconnected()
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

	Result ZooKeeper::ToResult(int zkResult)
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
		case (int)ZOO_ERRORS::ZNONODE:					return ResultCode::ZK_ZNONODE;
		case (int)ZOO_ERRORS::ZNOAUTH:					return ResultCode::ZK_ZNOAUTH;
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

	String ZooKeeper::GetLeapNodeName(const String& nodePath)
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

	Result ZooKeeper::Create(const char* path, const Array<uint8_t>& value, const struct ACL_vector *acl, int flags, String& outPath)
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

	Result ZooKeeper::Create(const char* path, const Json::Value& value, const struct ACL_vector *acl, int flags, String& outPath)
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

	SharedPointerT<ZooKeeper::StringTask> ZooKeeper::ACreate(const char* path, const Array<uint8_t>& value, const struct ACL_vector *acl, int flags)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::StringTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::StringTask>();

		auto valueData = value.size() > 0 ? value.data() : nullptr;
		int valueSize = value.size() > 0 ? (int)value.size() : -1;

		if (acl == nullptr)
			acl = &ZOO_OPEN_ACL_UNSAFE;

		SharedPointerT<StringTask> pTask = new(m_Heap) StringTask(m_Heap, GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		auto zkResult = zoo_acreate(m_ZKHandle, path, (const char*)valueData, valueSize, acl, flags, ZooKeeperWatcher::ZKWatcherCBStringComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<StringTask>>(pTask);
	}

	SharedPointerT<ZooKeeper::StringTask> ZooKeeper::ACreate(const char* path, const Json::Value& value, const struct ACL_vector *acl, int flags)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::StringTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::StringTask>();


		if (acl == nullptr)
			acl = &ZOO_OPEN_ACL_UNSAFE;

		SharedPointerT<StringTask> pTask = new(m_Heap) StringTask(m_Heap, GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));

		Json::StreamWriterBuilder builder;
		builder["indentation"] = "";
		auto valueBuffer = std::forward<std::string>(Json::writeString(builder, value));

		auto zkResult = zoo_acreate(m_ZKHandle, path, (const char*)valueBuffer.data(), (int)valueBuffer.size(), acl, flags, ZooKeeperWatcher::ZKWatcherCBStringComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<StringTask>>(pTask);
	}

	Result ZooKeeper::Delete(const char* path, int version)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_delete(m_ZKHandle, path, version);

		return ToResult(zkResult);
	}

	SharedPointerT<ZooKeeper::ZooKeeperTask> ZooKeeper::ADelete(const char* path, int version)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::ZooKeeperTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::ZooKeeperTask>();

		SharedPointerT<ZooKeeperTask> pTask = new(m_Heap) ZooKeeperTask(GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		auto zkResult = zoo_adelete(m_ZKHandle, path, version, ZooKeeperWatcher::ZKWatcherCBComplition, *pTask);
		pTask->SetResult(zkResult);
		if(zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<ZooKeeper::ZooKeeperTask>>(pTask);
	}

	Result ZooKeeper::DeleteTree(const char* path)
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



	Result ZooKeeper::Exists(const char* path)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_exists(m_ZKHandle, path, 0, nullptr);

		return ToResult(zkResult);
	}

	SharedPointerT<ZooKeeper::StatTask> ZooKeeper::AExists(const char* path, ZooKeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::StatTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::StatTask>();

		SharedPointerT<StatTask> pTask = new(m_Heap) StatTask(*watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aexists(m_ZKHandle, path, 0, ZooKeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		else
			zkResult = zoo_awexists(m_ZKHandle, path, ZooKeeperWatcher::ZKWatcherCB, watcher, ZooKeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<ZooKeeper::StatTask>>(pTask);
	}

	Result ZooKeeper::Get(const char *path, Array<uint8_t>& valueBuffer, struct Stat *stat)
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

	Result ZooKeeper::Get(const char *path, Json::Value& jsonValue)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		StaticArray<uint8_t,2048> valueBuffer(GetHeap());
		int buffLen = (int)valueBuffer.GetAllocatedSize();
		auto zkResult = zoo_get(m_ZKHandle, path, 0, (char*)valueBuffer.data(), &buffLen, nullptr);
		valueBuffer.resize(buffLen);

		std::stringstream inputStream(std::string(reinterpret_cast<const char*>(valueBuffer.data()), valueBuffer.size()), std::ios_base::in);
		Json::Value jsonData;
		Json::CharReaderBuilder jsonReader;
		std::string errs;
		auto bRes = Json::parseFromStream(jsonReader, inputStream, &jsonData, &errs);
		//Json::Reader reader;
		//auto bRes = reader.parse(reinterpret_cast<const char*>(valueBuffer.data()), reinterpret_cast<const char*>(valueBuffer.data()) + valueBuffer.size(), jsonValue, false);
		if (!bRes)
			return ResultCode::FAIL;

		return ToResult(zkResult);
	}

	SharedPointerT<ZooKeeper::DataTask> ZooKeeper::AGet(const char *path, ZooKeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::DataTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::DataTask>();

		SharedPointerT<DataTask> pTask = new(m_Heap) DataTask(m_Heap, *watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aget(m_ZKHandle, path, 0, ZooKeeperWatcher::ZKWatcherCBDataComplition, *pTask);
		else
			zkResult = zoo_awget(m_ZKHandle, path, ZooKeeperWatcher::ZKWatcherCB, watcher, ZooKeeperWatcher::ZKWatcherCBDataComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<ZooKeeper::DataTask>>(pTask);
	}

	Result ZooKeeper::Set(const char *path, const Array<uint8_t>& valueBuffer, int version)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_set(m_ZKHandle, path, (char*)valueBuffer.data(), (int)valueBuffer.size(), version);

		return ToResult(zkResult);
	}

	Result ZooKeeper::Set(const char *path, const Json::Value& value, int version)
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

	SharedPointerT<ZooKeeper::StatTask> ZooKeeper::ASet(const char *path, const Array<uint8_t>& valueBuffer, int version)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::StatTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::StatTask>();

		SharedPointerT<StatTask> pTask = new(m_Heap) StatTask(GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;
		zkResult = zoo_aset(m_ZKHandle, path, (char*)valueBuffer.data(), (int)valueBuffer.size(), version, ZooKeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<ZooKeeper::StatTask>>(pTask);
	}

	SharedPointerT<ZooKeeper::StatTask> ZooKeeper::ASet(const char *path, const Json::Value& value, int version)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::StatTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::StatTask>();

		SharedPointerT<StatTask> pTask = new(m_Heap) StatTask(GetWatcher());
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		Json::StreamWriterBuilder builder;
		builder["indentation"] = "";
		auto valueBuffer = std::forward<std::string>(Json::writeString(builder, value));
		zkResult = zoo_aset(m_ZKHandle, path, (char*)valueBuffer.data(), (int)valueBuffer.size(), version, ZooKeeperWatcher::ZKWatcherCBStatComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<ZooKeeper::StatTask>>(pTask);
	}


	Result ZooKeeper::GetChildren(const char *path, Array<String>& strings, bool watch)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		String_vector tempList;
		memset(&tempList, 0, sizeof(tempList));
		auto zkResult = zoo_get_children(m_ZKHandle, path, watch ? 1 : 0, &tempList);
		strings.reserve(strings.size() + tempList.count);
		for (int iStr = 0; iStr < tempList.count; iStr++)
		{
			strings.push_back(String(m_Heap, tempList.data[iStr]));
		}

		return ToResult(zkResult);
	}

	SharedPointerT<ZooKeeper::StringsTask> ZooKeeper::AGetChildren(const char *path, ZooKeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::StringsTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::StringsTask>();

		SharedPointerT<StringsTask> pTask = new(m_Heap) StringsTask(m_Heap, *watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aget_children(m_ZKHandle, path, 0, ZooKeeperWatcher::ZKWatcherCBStringsComplition, *pTask);
		else
			zkResult = zoo_awget_children(m_ZKHandle, path, ZooKeeperWatcher::ZKWatcherCB, watcher, ZooKeeperWatcher::ZKWatcherCBStringsComplition, *pTask);
		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<ZooKeeper::StringsTask>>(pTask);
	}

	SharedPointerT<ZooKeeper::StringsStatTask> ZooKeeper::AGetChildren2(const char *path, ZooKeeperWatcher* watcher)
	{
		if (m_ZKHandle == nullptr)
			return SharedPointerT<ZooKeeper::StringsStatTask>();

		if (!IsConnected())
			return SharedPointerT<ZooKeeper::StringsStatTask>();

		SharedPointerT<StringsStatTask> pTask = new(m_Heap) StringsStatTask(m_Heap, *watcher);
		TaskOperator().Requested(*pTask);
		SharedReferenceInc(static_cast<SharedObject*>(*pTask));
		int zkResult = 0;

		AddWatcher(watcher);
		if (watcher == nullptr)
			zkResult = zoo_aget_children2(m_ZKHandle, path, 0, ZooKeeperWatcher::ZKWatcherCBStringsStatComplition, *pTask);
		else
			zkResult = zoo_awget_children2(m_ZKHandle, path, ZooKeeperWatcher::ZKWatcherCB, watcher, ZooKeeperWatcher::ZKWatcherCBStringsStatComplition, *pTask);

		pTask->SetResult(zkResult);
		if (zkResult != ZOK) SharedReferenceDec(static_cast<SharedObject*>(*pTask));
		return std::forward<SharedPointerT<ZooKeeper::StringsStatTask>>(pTask);
	}



	Result ZooKeeper::GetAcl(const char *path, struct ACL_vector *acl, struct Stat *stat)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_get_acl(m_ZKHandle, path, acl, stat);

		return ToResult(zkResult);
	}


	Result ZooKeeper::SetAcl(const char *path, int version, struct ACL_vector *acl)
	{
		if (m_ZKHandle == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (!IsConnected())
			return ResultCode::INVALID_STATE;

		auto zkResult = zoo_set_acl(m_ZKHandle, path, version, acl);

		return ToResult(zkResult);
	}


	Result ZooKeeper::BatchRun(int count, const zoo_op_t *ops, zoo_op_result_t *results)
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

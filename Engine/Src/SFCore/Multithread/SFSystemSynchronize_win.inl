////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread Synchronize on windows
//
////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//
//	Critical Section
//

class CriticalSection : public MutexBase
{
public:
	CriticalSection()
	{
		InitializeCriticalSection(&m_CriticalSection);
	}
	~CriticalSection()
	{
		DeleteCriticalSection(&m_CriticalSection);
	}

	virtual void Lock() override
	{
		EnterCriticalSection(&m_CriticalSection);
	}

	virtual void UnLock() override
	{
		LeaveCriticalSection(&m_CriticalSection);
	}

private:
	CRITICAL_SECTION m_CriticalSection;
};

class Mutex : public MutexBase
{
public:
	Mutex()
	{
		m_Mutex = CreateMutex(
			NULL,              // default security attributes
			FALSE,             // initially not owned
			NULL);
	}

	Mutex(const char* MutexName, bool bInitiallyOwned = false)
	{
		m_Mutex = CreateMutexA(
			NULL,              // default security attributes
			bInitiallyOwned ? TRUE : FALSE,             // initially not owned
			MutexName);
	}

	~Mutex()
	{
		if (m_Mutex != nullptr)
			CloseHandle(m_Mutex);
	}

	bool IsValid() const {
		return m_Mutex != nullptr;
	}

	virtual void Lock() override
	{
		if (m_Mutex == nullptr)
			return;

		DWORD dwWaitResult = WaitForSingleObject(
			m_Mutex,    // handle to mutex
			INFINITE);
		if (dwWaitResult != WAIT_OBJECT_0)
		{
			assert(false);
			// error
		}
		else
		{
			// succeeded
			return;
		}
	}

	virtual void UnLock() override
	{
		if (m_Mutex != nullptr)
			ReleaseMutex(m_Mutex);
	}

private:

	HANDLE m_Mutex = nullptr;
};


class Event
{
public:

	Event(bool isInitialySet = false, bool autoReset = true)
	{
		m_hEvent = CreateEvent(NULL, !autoReset, isInitialySet, NULL);
	}

	~Event()
	{
		if (m_hEvent)
			CloseHandle(m_hEvent);
	}

	void Reset()
	{
		ResetEvent(m_hEvent);
	}

	void Set()
	{
		SetEvent(m_hEvent);
	}

	bool WaitEvent(DurationMS waitTimeMs)
	{
		DWORD dwWaitRes = WaitForSingleObject(m_hEvent, waitTimeMs.count());
		return dwWaitRes == WAIT_OBJECT_0;
	}

private:
	HANDLE	m_hEvent;
};




class Semaphore
{
public:

	Semaphore(int32_t lInitialCount = 0, int32_t lMaxCount = LONG_MAX)
	{
		m_hSemaphore = CreateSemaphore(NULL, lInitialCount, lMaxCount, NULL);
	}

	~Semaphore()
	{
		if (m_hSemaphore)
			CloseHandle(m_hSemaphore);
	}

	void Release(int32_t lResleaseCount = 1)
	{
		ReleaseSemaphore(m_hSemaphore, lResleaseCount, NULL);
	}

	bool Acquire(uint uiWaitTimeMs)
	{
		DWORD dwWaitRes = WaitForSingleObject(m_hSemaphore, uiWaitTimeMs);
		return dwWaitRes == WAIT_OBJECT_0;
	}

private:
	HANDLE	m_hSemaphore;
};




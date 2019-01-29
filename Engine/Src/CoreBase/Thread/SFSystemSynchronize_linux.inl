////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread Synchronize on linux
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include <pthread.h>
#include <assert.h>
#include <semaphore.h>



///////////////////////////////////////////////////////////////////////////////
//
//	Critical Section
//

class CriticalSection : public MutexBase
{
private:
	pthread_mutex_t m_CriticalSection;

public:
	CriticalSection()
	{
		Result hr;
		pthread_mutexattr_t mAttr;
		pthread_mutexattr_init(&mAttr);
#ifdef PTHREAD_MUTEX_RECURSIVE_NP // IOS doesn't support _NP
		pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP);
#else
		pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE);
#endif
		int result = pthread_mutex_init(&m_CriticalSection, &mAttr);
		if (result != 0)
		{
			const char* errorString = strerror(result);
			printf("%s", errorString);
			hr = ResultCode::FAIL;
			switch(result)
			{
				case EBUSY:		hr = ResultCode::UNEXPECTED;		break;
				case EINVAL:	hr = ResultCode::INVALID_ARG;		break;
				case EAGAIN:	hr = ResultCode::UNEXPECTED;		break;
				case ENOMEM:	hr = ResultCode::OUT_OF_MEMORY;		break;
				case EPERM:		hr = ResultCode::FAIL;			break;
				default:
					hr = ResultCode::UNEXPECTED;
					break;
			}

			unused(hr);
		}

		if (hr)
		{
			Lock();
			UnLock();
		}
	}
	~CriticalSection()
	{
		pthread_mutex_destroy(&m_CriticalSection);
	}

	virtual void Lock()
	{
		pthread_mutex_lock(&m_CriticalSection);
	}

	virtual void UnLock()
	{
		//Assert(((m_CriticalSection).__data).__count > 0);
		pthread_mutex_unlock(&m_CriticalSection);
	}

};



class Mutex : public MutexBase
{
private:
	pthread_mutex_t m_CriticalSection;

public:
	Mutex()
	{
		pthread_mutexattr_t mAttr;
		pthread_mutexattr_init(&mAttr);
		pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&m_CriticalSection, &mAttr);
	}

	~Mutex()
	{
		pthread_mutex_destroy(&m_CriticalSection);
	}

	virtual void Lock() override
	{
		pthread_mutex_lock(&m_CriticalSection);
	}

	virtual void UnLock() override
	{
		pthread_mutex_unlock(&m_CriticalSection);
	}

};





class Event
{
public:

	Event(bool isInitialySet = false, bool autoReset = true);


	~Event();


	void Reset();

	void Set();


	bool WaitEvent(DurationMS waitTimeMs);

private:
	std::atomic<bool>	m_hEvent;
	bool	m_AutoReset;
};



class Semaphore
{
private:
    
#if SF_PLATFORM == SF_PLATFORM_IOS
    static std::atomic<int> stm_SemaphoreName;
    char m_Name[128];
#endif
    
public:

	Semaphore(int32_t lInitialCount = 0, int32_t lMaxCount = std::numeric_limits<int32_t>::max())
	{
#if SF_PLATFORM == SF_PLATFORM_IOS
        // TODO: Need to add instance id to avoid collision
        sprintf(m_Name,"SFEngineSem%d", stm_SemaphoreName.fetch_add(1,std::memory_order_relaxed));
        sem_open(m_Name,O_CREAT,lInitialCount);
#else
		sem_init(&m_hSemaphore, lMaxCount, lInitialCount);
#endif
	}

	~Semaphore()
	{
		sem_close(&m_hSemaphore);
#if SF_PLATFORM == SF_PLATFORM_IOS
        sem_unlink(m_Name);
#else
		sem_destroy(&m_hSemaphore);
#endif
	}

	void Release(int32_t lResleaseCount = 1)
	{
		sem_post(&m_hSemaphore);
	}

	bool Acquire(uint uiWaitTimeMs)
	{
#if SF_PLATFORM == SF_PLATFORM_IOS // IOS doesn't have CLOCK_REALTIME
		sem_wait(&m_hSemaphore);
#else
		timespec waitTime;
		memset(&waitTime, 0, sizeof(waitTime));

		if (clock_gettime(CLOCK_REALTIME, &waitTime) == -1)
			return false;

		waitTime.tv_nsec += uiWaitTimeMs * 1000000;
		sem_timedwait(&m_hSemaphore, &waitTime);
#endif
		return true;
	}

private:
	sem_t	m_hSemaphore;
};




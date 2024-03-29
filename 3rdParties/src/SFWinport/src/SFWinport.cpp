

#ifdef WIN32

#include "SFWinport.h"


#ifdef __cplusplus
extern "C" {
#endif
//
//    int pthread_mutex_lock(pthread_mutex_t* _mutex) {
//        int rc = WaitForSingleObject(*_mutex,    // handle to mutex
//            INFINITE);  // no time-out interval
//        return ((rc == WAIT_OBJECT_0) ? 0 : rc);
//    }
//
//    int pthread_mutex_unlock(pthread_mutex_t* _mutex) {
//        int rc = ReleaseMutex(*_mutex);
//        return ((rc != 0) ? 0 : GetLastError());
//    }
//
//    int pthread_mutex_init(pthread_mutex_t* _mutex, void* ) {
//        //use CreateMutex as we are using the HANDLES in pthread_cond
//        *_mutex = CreateMutex(
//            NULL,              // default security attributes
//            FALSE,             // initially not owned
//            NULL);             // unnamed mutex    
//        return ((*_mutex == NULL) ? GetLastError() : 0);
//    }
//
//    int pthread_mutex_destroy(pthread_mutex_t* _mutex)
//    {
//        int rc = CloseHandle(*_mutex);
//        return ((rc != 0) ? 0 : GetLastError());
//    }
//
//    static unsigned __stdcall __sfwinport_beginthreadex_proc(void* InArg)
//    {
//        auto thread = reinterpret_cast<pthread_t*>(InArg);
//        if (thread->start_routine) 
//            thread->start_routine(thread->arg);
//
//        return 0;
//    }
//
//    int pthread_create(pthread_t* thread, const pthread_attr_t* , void* (*start_routine) (void*), void* arg)
//    {
//        int _intThreadId;
//        thread->start_routine = start_routine;
//        thread->arg = arg;
//
//        (*thread).thread_handle = (HANDLE)_beginthreadex(NULL, 0, __sfwinport_beginthreadex_proc, thread, 0, (unsigned int*)&_intThreadId);
//        (*thread).thread_id = _intThreadId;
//
//        return (((*thread).thread_handle == 0) ? errno : 0);
//    }
//
//
//    int pthread_equal(pthread_t t1, pthread_t t2) {
//        //Is there a better way to do this? GetThreadId(handle) is only supported Windows 2003 n above.
//        return ((t1.thread_id == t2.thread_id) ? 1 : 0);
//    }
//
//    pthread_t pthread_self() {
//        pthread_t thread_self;
//        thread_self.thread_handle = GetCurrentThread();
//        thread_self.thread_id = GetCurrentThreadId();
//        return thread_self;
//    }
//
//    int pthread_join(pthread_t _thread, void** )
//    {
//        int rc = WaitForSingleObject(_thread.thread_handle, INFINITE);
//        return ((rc == WAIT_OBJECT_0) ? 0 : rc);
//    }
//
//    int pthread_detach(pthread_t _thread)
//    {
//        int rc = CloseHandle(_thread.thread_handle);
//        return  (rc != 0) ? 0 : GetLastError();
//    }
//
//    void pthread_mutexattr_init(pthread_mutexattr_t* ) {}
//    void pthread_mutexattr_settype(pthread_mutexattr_t* , int ) {}
//    void pthread_mutexattr_destroy(pthread_mutexattr_t* ) {}
//
//    int
//        pthread_cond_init(pthread_cond_t* cv,
//            const pthread_condattr_t* )
//    {
//        cv->waiters_count_ = 0;
//        cv->was_broadcast_ = 0;
//        cv->sema_ = CreateSemaphore(NULL,       // no security
//            0,          // initially 0
//            0x7fffffff, // max count
//            NULL);      // unnamed 
//        if (cv->sema_ == NULL)
//            return GetLastError();
//        InitializeCriticalSection(&cv->waiters_count_lock_);
//        cv->waiters_done_ = CreateEvent(NULL,  // no security
//            FALSE, // auto-reset
//            FALSE, // non-signaled initially
//            NULL); // unnamed
//        return (cv->waiters_done_ == NULL) ? GetLastError() : 0;
//
//    }
//
//
//    int pthread_cond_destroy(pthread_cond_t* cond)
//    {
//        CloseHandle(cond->sema_);
//        DeleteCriticalSection(&cond->waiters_count_lock_);
//        return (CloseHandle(cond->waiters_done_) == 0) ? GetLastError() : 0;
//    }
//
//
//    int
//        pthread_cond_signal(pthread_cond_t* cv)
//    {
//        int have_waiters;
//        EnterCriticalSection(&(cv->waiters_count_lock_));
//        have_waiters = cv->waiters_count_ > 0;
//        LeaveCriticalSection(&cv->waiters_count_lock_);
//
//        // If there aren't any waiters, then this is a no-op.  
//        if (have_waiters) {
//            return (ReleaseSemaphore(cv->sema_, 1, 0) == 0) ? GetLastError() : 0;
//        }
//        else
//            return 0;
//    }
//
//
//    int
//        pthread_cond_broadcast(pthread_cond_t* cv)
//    {
//        // This is needed to ensure that <waiters_count_> and <was_broadcast_> are
//        // consistent relative to each other.
//        int have_waiters = 0;
//        EnterCriticalSection(&cv->waiters_count_lock_);
//
//        if (cv->waiters_count_ > 0) {
//            // We are broadcasting, even if there is just one waiter...
//            // Record that we are broadcasting, which helps optimize
//            // <pthread_cond_wait> for the non-broadcast case.
//            cv->was_broadcast_ = 1;
//            have_waiters = 1;
//        }
//
//        if (have_waiters) {
//            // Wake up all the waiters atomically.
//            ReleaseSemaphore(cv->sema_, cv->waiters_count_, 0);
//
//            LeaveCriticalSection(&cv->waiters_count_lock_);
//
//            // Wait for all the awakened threads to acquire the counting
//            // semaphore. 
//            WaitForSingleObject(cv->waiters_done_, INFINITE);
//            // This assignment is okay, even without the <waiters_count_lock_> held 
//            // because no other waiter threads can wake up to access it.
//            cv->was_broadcast_ = 0;
//        }
//        else
//            LeaveCriticalSection(&cv->waiters_count_lock_);
//
//        return 0;
//    }
//
//
//    int pthread_cond_timedwait(pthread_cond_t* cv, pthread_mutex_t* external_mutex, const struct timespec* abstime)
//    {
//        int last_waiter;
//        // Avoid race conditions.
//        EnterCriticalSection(&cv->waiters_count_lock_);
//        cv->waiters_count_++;
//        LeaveCriticalSection(&cv->waiters_count_lock_);
//
//
//        auto msec = abstime->tv_sec * 1000 + abstime->tv_nsec / 1000000;
//        // This call atomically releases the mutex and waits on the
//        // semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
//        // are called by another thread.
//        SignalObjectAndWait(*external_mutex, cv->sema_, DWORD(msec), FALSE);
//
//        // Reacquire lock to avoid race conditions.
//        EnterCriticalSection(&cv->waiters_count_lock_);
//
//        // We're no longer waiting...
//        cv->waiters_count_--;
//
//        // Check to see if we're the last waiter after <pthread_cond_broadcast>.
//        last_waiter = cv->was_broadcast_ && cv->waiters_count_ == 0;
//
//        LeaveCriticalSection(&cv->waiters_count_lock_);
//
//        // If we're the last waiter thread during this particular broadcast
//        // then let all the other threads proceed.
//        if (last_waiter)
//            // This call atomically signals the <waiters_done_> event and waits until
//            // it can acquire the <external_mutex>.  This is required to ensure fairness. 
//            SignalObjectAndWait(cv->waiters_done_, *external_mutex, INFINITE, FALSE);
//        else
//            // Always regain the external mutex since that's the guarantee we
//            // give to our callers. 
//            WaitForSingleObject(*external_mutex, INFINITE);
//
//        return 0;
//    }
//
//    int pthread_cond_wait(pthread_cond_t* cv, pthread_mutex_t* external_mutex)
//    {
//        int last_waiter;
//        // Avoid race conditions.
//        EnterCriticalSection(&cv->waiters_count_lock_);
//        cv->waiters_count_++;
//        LeaveCriticalSection(&cv->waiters_count_lock_);
//
//        // This call atomically releases the mutex and waits on the
//        // semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
//        // are called by another thread.
//        SignalObjectAndWait(*external_mutex, cv->sema_, INFINITE, FALSE);
//
//        // Reacquire lock to avoid race conditions.
//        EnterCriticalSection(&cv->waiters_count_lock_);
//
//        // We're no longer waiting...
//        cv->waiters_count_--;
//
//        // Check to see if we're the last waiter after <pthread_cond_broadcast>.
//        last_waiter = cv->was_broadcast_ && cv->waiters_count_ == 0;
//
//        LeaveCriticalSection(&cv->waiters_count_lock_);
//
//        // If we're the last waiter thread during this particular broadcast
//        // then let all the other threads proceed.
//        if (last_waiter)
//            // This call atomically signals the <waiters_done_> event and waits until
//            // it can acquire the <external_mutex>.  This is required to ensure fairness. 
//            SignalObjectAndWait(cv->waiters_done_, *external_mutex, INFINITE, FALSE);
//        else
//            // Always regain the external mutex since that's the guarantee we
//            // give to our callers. 
//            WaitForSingleObject(*external_mutex, INFINITE);
//
//        return 0;
//    }
//
//    int pthread_key_create(pthread_key_t* key, void (*destructor)(void*))
//    {
//        int result = 0;
//        pthread_key_t* newkey;
//
//        if ((newkey = (pthread_key_t*)calloc(1, sizeof(pthread_key_t))) == NULL)
//        {
//            result = ENOMEM;
//        }
//        else if ((newkey->key = TlsAlloc()) == TLS_OUT_OF_INDEXES)
//        {
//            result = EAGAIN;
//            free(newkey);
//            newkey = NULL;
//        }
//        else if (destructor != NULL)
//        {
//            //--we have to store the function pointer for destructor, so that we can call it 
//               //--to free up the user allocated storage--       
//            newkey->destructor = destructor;
//        }
//        key = newkey;
//        return (result);
//    }
//
//    int pthread_key_delete(pthread_key_t key)
//    {
//        int rc = 0;
//        LPVOID lpvData = TlsGetValue(key.key);
//        rc = TlsFree(key.key);
//        rc = (rc != 0) ? 0 : GetLastError();
//        if (key.destructor != NULL && lpvData != 0) {
//            key.destructor(lpvData);         //we take control of calling destructor, instead of calling it on thread exit.
//        }
//        free(&key);
//        return (rc);
//    }
//
//    void* pthread_getspecific(pthread_key_t key)
//    {
//        LPVOID lpvData = TlsGetValue(key.key);
//        if ((lpvData == 0) && (GetLastError() != ERROR_SUCCESS))
//            return NULL;
//        else
//            return lpvData;
//    }
//
//    int pthread_setspecific(pthread_key_t key, const void* value)
//    {
//        int rc = TlsSetValue(key.key, (LPVOID)value);
//        return ((rc != 0) ? 0 : GetLastError());
//    }
//
//    void pthread_exit(void* retval)
//    {
//        _endthreadex((unsigned)(intptr_t)retval);
//    }


    int close(SOCKET fd) {
        return closesocket(fd);
    }

    int Win32WSAStartup()
    {
        WORD    wVersionRq;
        WSADATA wsaData;
        int             err;

        wVersionRq = MAKEWORD(2, 0);
        err = WSAStartup(wVersionRq, &wsaData);
        if (err != 0)
            return 1;

        // confirm the version information
        if ((LOBYTE(wsaData.wVersion) != 2) ||
            (HIBYTE(wsaData.wVersion) != 0))
        {
            Win32WSACleanup();
            return 1;
        }
        return 0;
    }

    void Win32WSACleanup()
    {
        WSACleanup();
    }


    int gettimeofday(struct timeval* tp, timezone* tzp)
    {
        int64_t now = 0;
        if (tzp != 0) { errno = EINVAL; return -1; }
        GetSystemTimeAsFileTime((LPFILETIME)&now);
        tp->tv_sec = (long)(now / 10000000 - 11644473600LL);
        tp->tv_usec = (now / 10) % 1000000;
        return 0;
    }

    double drand48(void)
    {
        return (double)(rand()) / RAND_MAX;
    }



#ifdef __cplusplus
}
#endif

#endif //WIN32




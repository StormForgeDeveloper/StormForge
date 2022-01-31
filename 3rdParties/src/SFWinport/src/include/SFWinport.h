

#pragma once

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <errno.h>
#include <process.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* POSIX names are deprecated, use ISO conformant names instead. */
#define strdup _strdup
#define getcwd _getcwd
#define getpid _getpid

/* Windows "secure" versions of POSIX reentrant functions */
#define strtok_r strtok_s
#define localtime_r(a,b) localtime_s(b,a)

#ifndef ssize_t
#	if defined(_WIN64)
#    define _SSIZE_T_DEFINED
#    define ssize_t __int64
#  else
#    define _SSIZE_T_DEFINED
#    define ssize_t int
#  endif

//typedef int ssize_t;
#endif
typedef HANDLE pthread_mutex_t;


typedef void* (*_pthread_start_routine_type) (void*);

struct pthread_t_
{
	HANDLE thread_handle;
	DWORD  thread_id;
	_pthread_start_routine_type start_routine;
	void* arg;
};




typedef struct
{
	int waiters_count_;
	// Number of waiting threads.

	CRITICAL_SECTION waiters_count_lock_;
	// Serialize access to <waiters_count_>.

	HANDLE sema_;
	// Semaphore used to queue up threads waiting for the condition to become signaled. 

	HANDLE waiters_done_;
	// An auto-reset event used by the broadcast/signal thread to wait
	// for all the waiting thread(s) to wake up and be released from the
	// semaphore. 

	size_t was_broadcast_;
	// Keeps track of whether we were broadcasting or signaling.  This
	// allows us to optimize the code if we're just signaling.

} pthread_cond_t;

struct pthread_key_t_
{
	DWORD key;
	void(*destructor) (void *);
};

typedef struct pthread_key_t_ pthread_key_t;


typedef struct pthread_t_ pthread_t;
typedef int pthread_mutexattr_t;
typedef int pthread_condattr_t;
typedef int pthread_attr_t;
#define PTHREAD_MUTEX_RECURSIVE 0




int pthread_mutex_lock(pthread_mutex_t* _mutex);
int pthread_mutex_unlock(pthread_mutex_t* _mutex);
int pthread_mutex_init(pthread_mutex_t* _mutex, void* ignoredAttr);
int pthread_mutex_destroy(pthread_mutex_t* _mutex);
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void* (*start_routine) (void*), void *arg);
int pthread_equal(pthread_t t1, pthread_t t2);
pthread_t pthread_self();
int pthread_join(pthread_t _thread, void** ignore);
int pthread_detach(pthread_t _thread);

void pthread_mutexattr_init(pthread_mutexattr_t* ignore);
void pthread_mutexattr_settype(pthread_mutexattr_t* ingore_attr, int ignore);
void pthread_mutexattr_destroy(pthread_mutexattr_t* ignore_attr);


int pthread_cond_init(pthread_cond_t *cv, const pthread_condattr_t * ignore);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cv);
int pthread_cond_broadcast(pthread_cond_t *cv);
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
int pthread_cond_wait(pthread_cond_t *cv, pthread_mutex_t *external_mutex);

int pthread_key_create(pthread_key_t *key, void(*destructor)(void *));
int pthread_key_delete(pthread_key_t key);
void *pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value);

void pthread_exit(void* retval);

// ETC
#ifndef _TIMEZONE_DEFINED
struct timezone
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};

#endif

int gettimeofday(struct timeval *tp, struct timezone* tzp);
double drand48(void);

//int close(SOCKET fd);
int Win32WSAStartup();
void Win32WSACleanup();

// Get socket error in socket error code
int get_socket_errno();


#ifdef __cplusplus
}
#endif



#else // WIN32

#include <pthread.h>

#endif //WIN32


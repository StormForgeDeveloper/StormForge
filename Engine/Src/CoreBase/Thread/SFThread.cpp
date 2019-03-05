////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Util/SFTimeUtil.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"



namespace SF {



	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Basic multithread class
	//

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

	static const int ThreadSchedulingTable[] =
	{
		THREAD_PRIORITY_TIME_CRITICAL,		// PRIORITY_TIME_CRITICAL
		THREAD_PRIORITY_HIGHEST,			// PRIORITY_HIGHEST
		THREAD_PRIORITY_ABOVE_NORMAL,		// PRIORITY_ABOVE_NORMAL 
		THREAD_PRIORITY_NORMAL,				// PRIORITY_NORMAL
		THREAD_PRIORITY_BELOW_NORMAL,		// PRIORITY_BELOW_NORMAL
		THREAD_PRIORITY_LOWEST,				// PRIORITY_LOWEST
		THREAD_PRIORITY_IDLE,				// PRIORITY_IDLE
	};

	const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)  
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // Must be 0x1000.  
		LPCSTR szName; // Pointer to name (in user addr space).  
		DWORD dwThreadID; // Thread ID (-1=caller thread).  
		DWORD dwFlags; // Reserved for future use, must be zero.  
	} THREADNAME_INFO;
#pragma pack(pop)  

#elif SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID

	// schedulingPolicies
	//
	//	// Normal threads, No Scheduling decision. priority must be 0
	//	SCHED_OTHER,
	//	SCHED_IDLE,
	//	SCHED_BATCH,

	//	// Priority value from 1 to 99
	//	// Varies by system, use from sched_get_priority_min(2) to sched_get_priority_max(2)
	//	SCHED_FIFO,
	//	SCHED_RR,
	//

	static const struct
	{
		int Policy;
		int Priority;

	} ThreadSchedulingTable[] =
	{
#if SF_PLATFORM == SF_PLATFORM_ANDROID
		{ SCHED_FIFO,	10 },																				// PRIORITY_TIME_CRITICAL
		{ SCHED_RR,	5, },	// PRIORITY_HIGHEST
		{ SCHED_RR,	0, },																				// PRIORITY_ABOVE_NORMAL 
		{ SCHED_OTHER,	0, },																									// PRIORITY_NORMAL
		{ SCHED_OTHER,	0, },																									// PRIORITY_BELOW_NORMAL
		{ SCHED_OTHER,	0, },																									// PRIORITY_LOWEST
		{ SCHED_OTHER,	0, },																									// PRIORITY_IDLE
#else
		{ SCHED_FIFO,	sched_get_priority_max(SCHED_FIFO) },																				// PRIORITY_TIME_CRITICAL
		{ SCHED_RR,	sched_get_priority_min(SCHED_RR) + ((sched_get_priority_max(SCHED_RR) - sched_get_priority_min(SCHED_RR)) >> 1), },	// PRIORITY_HIGHEST
		{ SCHED_RR,	sched_get_priority_min(SCHED_RR), },																				// PRIORITY_ABOVE_NORMAL 
		{ SCHED_OTHER,	0, },																									// PRIORITY_NORMAL
		{ SCHED_BATCH,	0, },																									// PRIORITY_BELOW_NORMAL
		{ SCHED_BATCH,	0, },																									// PRIORITY_LOWEST
		{ SCHED_IDLE,	0, },																									// PRIORITY_IDLE
#endif
	};

	static_assert(countof(ThreadSchedulingTable) == ((int)Thread::PRIORITY::IDLE + 1), "Invalid Thread scheduling table count");


	class ModuleThread_impl
	{
	public:
		ModuleThread_impl()
		{
#if SF_PLATFORM != SF_PLATFORM_ANDROID
			rlimit limit;
			memset(&limit, 0, sizeof limit);
			if (getrlimit(RLIMIT_RTPRIO, &limit) != 0)
			{
				std::cout << "Failed to get rtpio limits:" << errno << std::endl;
				assert(!"Failed to get rtpio limits:");
				return;
			}

			unsigned int rrMax = (unsigned)sched_get_priority_max(SCHED_RR);
			unsigned int fifoMax = (unsigned)sched_get_priority_max(SCHED_FIFO);
			if (rrMax > limit.rlim_cur || rrMax > limit.rlim_max)
			{
				std::cout << "rtpio RR limit: min:" << (int)sched_get_priority_min(SCHED_RR) << " max:" << (int)sched_get_priority_max(SCHED_RR) << std::endl;
				assert(!"Invalid rtpio RR limits:");
			}
			if (fifoMax > limit.rlim_cur || fifoMax > limit.rlim_max)
			{
				std::cout << "rtpio FIFO limit: min:" << (int)sched_get_priority_min(SCHED_FIFO) << " max:" << (int)sched_get_priority_max(SCHED_FIFO) << std::endl;
				assert(!"Invalid rtpio FIFO limits:");
			}
			std::cout << "TestThreadLimits - OK" << std::endl;
#endif
		}
	};
	static ModuleThread_impl CheckThreadLimits;



#endif

	Thread::Thread()
		: m_threadPriority(PRIORITY::NORMAL)
		, m_KillFlag(false)
		, m_IsRunning(false)
	{
	}

	Thread::Thread(const char* name)
		: m_threadPriority(PRIORITY::NORMAL)
		, m_KillFlag(false)
		, m_IsRunning(false)
	{
		SetThreadName(name);
	}

	Thread::~Thread()
	{
		Stop(true);
	}

	void Thread::SetThreadNameInternal(const char* threadName)
	{
		if (threadName == nullptr || threadName[0] == '\0')
			return;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

		typedef HRESULT(_stdcall *TSetThreadDescription)(HANDLE hThread, PCWSTR threadName);
		wchar_t threadNameBuffer[512];

		static HMODULE hKernel = LoadLibraryA("Kernel32.dll");
		if (hKernel == nullptr)
			return;

		static auto pSetThreadDescription = (TSetThreadDescription)GetProcAddress(hKernel, "SetThreadDescription");
		if (pSetThreadDescription == nullptr)
			return;

		StrUtil::UTF8ToWCS(threadName, threadNameBuffer);

		auto nativeHandle = thread::native_handle();
		pSetThreadDescription((HANDLE)nativeHandle, threadNameBuffer);
#else
		pthread_setname_np(native_handle(), threadName);
#endif
	}

	void Thread::SetThreadName(const char* threadName)
	{
		if (threadName == nullptr) threadName = "NoName";

		m_ThreadName = threadName;
		m_Name = Service::StringDB->AddNGetString(threadName);

		if (GetThreadID() == thread::id())
			return;

		SetThreadNameInternal(threadName);
	}

	// Get/Set Thread Priority
	void Thread::SetPriority(PRIORITY priority)
	{
		m_threadPriority = priority;
		auto threadHandle = GetThread();
		if (threadHandle == ThreadHandle(0)) return;


#if SF_PLATFORM == SF_PLATFORM_WINDOWS


		::SetThreadPriority((HANDLE)threadHandle, ThreadSchedulingTable[(int)priority]);
		

#elif SF_PLATFORM == SF_PLATFORM_LINUX

		sched_param sch_params;
		sch_params.sched_priority = ThreadSchedulingTable[(int)priority].Priority;
		if (pthread_setschedparam(native_handle(), ThreadSchedulingTable[(int)priority].Policy, &sch_params))
		{
			std::cerr << "Failed to set Thread scheduling : " << errno << std::endl;
			assert(false);
		}

#elif SF_PLATFORM == SF_PLATFORM_ANDROID
		// No thread priority for android
#endif
	}

	// thread function for run
	void Thread::ThreadFunc(Thread* pThread)
	{
		if (pThread == nullptr)
			return;

		pThread->SetPriority(pThread->GetPriority());

		pThread->Run();

		pThread->m_IsRunning.store(false, std::memory_order_release);

		return;
	}




	// Calculate sleep interval from the expected interval
	DurationMS Thread::UpdateInterval(const DurationMS& ulExpectedInterval)
	{
		auto ulCurTime = Util::Time.GetTimeMs();
		if (m_ulPreTime.time_since_epoch().count() == 0)
		{
			m_ulPreTime = ulCurTime;
			return DurationMS(0);
		}

		int32_t diffTime = (int32_t)(ulCurTime - m_ulPreTime).count();
		DurationMS sleepInterval;

		if (diffTime < 0) diffTime = 0;

		if (diffTime > (int32_t)ulExpectedInterval.count())
			sleepInterval = DurationMS(0);
		else if (diffTime < (int32_t)ulExpectedInterval.count())
			sleepInterval = DurationMS((int32_t)ulExpectedInterval.count() - diffTime);
		else
			sleepInterval = ulExpectedInterval;
		m_ulPreTime = ulCurTime;

		return sleepInterval;
	}


	bool Thread::CheckKillEvent(const DurationMS& waitTime)
	{
		bool bRet = m_KillFlag.load(std::memory_order_acquire);
		if (!bRet)
			ThisThread::SleepFor(waitTime);

		return bRet;
	}

	bool Thread::IsKillEventSignaled()
	{
		return m_KillFlag.load(std::memory_order_relaxed);
	}

	void Thread::SetKillEvent()
	{
		m_KillFlag.store(true, std::memory_order_release);
	}

	// thread Controlling

	void Thread::Start()
	{
		m_ulPreTime = Util::Time.GetTimeMs();

		m_KillFlag.store(false, std::memory_order_release);

		m_IsRunning.store(true, std::memory_order_release);

		std::thread localThread(ThreadFunc, this);
		swap(localThread);

		// set name if specified
		auto strThreadName = Service::StringDB->GetString(GetThreadName());
		if (StrUtil::IsNullOrEmpty(strThreadName) && !StrUtil::IsNullOrEmpty(m_ThreadName))
			SetThreadNameInternal(m_ThreadName);
		else
			SetThreadNameInternal(strThreadName);

	}

	void Thread::Stop(bool bSendKillEvt)
	{
		// if already finished or not started
		if (!joinable()) return;

		if (bSendKillEvt)
		{
			// Set close event
			SetKillEvent();
		}

		join();
	}


	void Thread::Run()
	{
		while (!CheckKillEvent(m_TickInterval))
		{
			if (!Tick())
				break;
		}

	}








} // namespace SF




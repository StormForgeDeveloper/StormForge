////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread 
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Util/SFStringCrc64.h"
#include "Multithread/SFSystemSynchronization.h"



namespace SF {



	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Basic multithread class
	//
	class Thread : public std::thread
	{
	public:
		enum class PRIORITY
		{
			TIME_CRITICAL,		// Indicates 3 points above normal priority. 
			HIGHEST,			// Indicates 2 points above normal priority. 
			ABOVE_NORMAL,		// Indicates 1 point above normal priority. 
			NORMAL,				// Indicates normal priority. 
			BELOW_NORMAL,		// Indicates 1 point below normal priority. 
			LOWEST,				// Indicates 2 points below normal priority. 
			IDLE,				// Indicates 4 points below normal priority. 
		};

		static constexpr int NAMELEN = 16;

	private:

		// Thread name
		StringCrc64 m_Name;
		char m_ThreadName[NAMELEN] = {};
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		wchar_t* m_wThreadName = nullptr;
#endif

		// working thread priority
		PRIORITY m_threadPriority;

		// Event handles for thread control
		std::atomic<bool>	m_KillFlag;

		// thread running status
		std::atomic<bool> m_IsRunning;

		// Calculate sleep interval
		TimeStampMS	m_ulPreTime;

		// Tick interval
		DurationMS m_TickInterval = DurationMS(5);

		// thread function for run
		static void ThreadFunc(Thread* pThread);

	protected:

		void SetThreadNameInternal();

	public:
		Thread();
		Thread(const char* name);
		virtual ~Thread();

		StringCrc64 GetThreadName() const { return m_Name; }

		// Get thread
		inline ThreadHandle GetThread();
		inline ThreadID GetThreadID();

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		int64_t GetNativeThreadID() { return  GetThreadId(GetThread()); }
#elif SF_PLATFORM == SF_PLATFORM_ANDROID
		int64_t GetNativeThreadID() { return  gettid(); }
#elif SF_PLATFORM == SF_PLATFORM_IOS
        int64_t GetNativeThreadID() { return pthread_mach_thread_np(pthread_self()); }
#else
		int64_t GetNativeThreadID() { return  syscall(SYS_gettid); }
#endif

		bool GetIsRunning() { return m_IsRunning.load(std::memory_order_relaxed); }

		// Get/Set Thread Priority
		virtual void SetPriority(PRIORITY priority);
		inline PRIORITY GetPriority();

		void SetThreadName(const char* threadName);

		// Set tick interval
		void SetTickInterval(DurationMS tickInterval) { m_TickInterval = tickInterval; }

		// Calculate sleep interval
		DurationMS UpdateInterval(const DurationMS& ulSleepInterval);

		// Check kill event for give wait time
		bool CheckKillEvent(const DurationMS& dwWaitTime);
		bool IsKillEventSignaled();
		void SetKillEvent();

		// thread Controlling
		virtual void Start();
		virtual void Stop(bool bSendKillEvt = false);


		// run process, if return value is false then thread will stop
		virtual void Run();
		virtual bool Tick() { return false; }
	};


	// This thread helper
	class ThisThread
	{
	public:
		//static void Yield()									{ std::this_thread::yield(); }
		static std::thread::id GetThreadID()				{ return std::this_thread::get_id(); }
		static void SleepFor(DurationMS duration)			{ std::this_thread::sleep_for(duration); }
	};


	class FunctorThread : public Thread
	{
	public:

		typedef std::function<void(Thread* pThread)> Func;

	private:
		Func m_Func;

	public:

		FunctorThread()
		{}

		FunctorThread(Func func);

		void SetFunc(Func func)
		{
			m_Func = func;
		}

		virtual void Run() override
		{
			m_Func(this);
		}
	};


	class FunctorTickThread : public Thread
	{
	public:

        // Tick function type. return true to keep ticking
		using TickFunc = std::function<bool(Thread* pThread)>;
        // Other event function type
        using EventFunc = std::function<void(Thread* pThread)>;

	private:
		// functor
		// should be std::function<bool(Thread* pThread)> form
        EventFunc m_FuncOnStart;
        EventFunc m_FuncOnStop;
        TickFunc m_FuncTick;

	public:

		FunctorTickThread(TickFunc tickFunc)
			: m_FuncTick(tickFunc)
		{}

        FunctorTickThread(TickFunc tickFunc, const char* name)
            : Thread(name)
            , m_FuncTick(tickFunc)
        {
        }

        FunctorTickThread(EventFunc onStart, EventFunc onStop, TickFunc tickFunc)
            : m_FuncOnStart(onStart)
            , m_FuncOnStop(onStop)
            , m_FuncTick(tickFunc)
        {}

        FunctorTickThread(EventFunc onStart, EventFunc onStop, TickFunc tickFunc, const char* name)
            : Thread(name)
            , m_FuncOnStart(onStart)
            , m_FuncOnStop(onStop)
            , m_FuncTick(tickFunc)
        {
        }


        virtual void Run() override
        {
            if (m_FuncOnStart)
                m_FuncOnStart(this);

            Thread::Run();

            if (m_FuncOnStop)
                m_FuncOnStop(this);

        }

		virtual bool Tick() override
		{
			return m_FuncTick(this);
		}
	};


} // namespace SF



#include "SFThread.inl"

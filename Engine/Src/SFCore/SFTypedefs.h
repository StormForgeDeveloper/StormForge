////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


// Decide target architecture
// See https://sourceforge.net/p/predef/wiki/Architectures/
#if __x86_64__ || __ppc64__ || __LP64__ || _WIN64 || _M_ARM64 || _M_X64 || _M_AMD64 || __aarch64__
	#define X64	true
#else
	#define X32	true
#endif




#define SF_PLATFORM_WINDOWS		1
#define SF_PLATFORM_LINUX		2
#define SF_PLATFORM_ANDROID		3
#define SF_PLATFORM_IOS			4


// Decide platform
#if __IOS__

#define SF_PLATFORM SF_PLATFORM_IOS

#elif defined(_WIN32) || defined(_WIN64)

#define SF_PLATFORM SF_PLATFORM_WINDOWS

//#elif __GNUC__
#elif __ANDROID__

#define SF_PLATFORM SF_PLATFORM_ANDROID

#else // All others are Linux

#define SF_PLATFORM SF_PLATFORM_LINUX

#endif


// TODO: need to detect for other platform
// define SSE flags
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#	if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86) || defined(__i386__)
	#define SF_SIMD_SSE
	#define SF_SIMD_SSE42
	#define SF_SIMD_AVX
#	elif defined(__arm__ ) || defined(_M_ARM)
// TODO: detect ARM8 only
		#define SF_SIMD_NEON
#	elif defined(__powerpc__ ) || defined(_M_PPC)
#	elif defined(__mips__ )
#	else
#   endif
// if Linux or other system
#elif defined(__clang__)
#define SF_SIMD_SSE
#define SF_SIMD_SSE42
#define SF_SIMD_AVX
#endif


#if !defined(_WIN32) && !defined(_WIN64)
#include <libmemcached/mem_config.h>
#endif

//////////////////////////////////////////////////
//
//  Common headers
//

#include <assert.h>
#include <atomic>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>
#include <stddef.h>
#include <stdarg.h>
#include <errno.h>
#include <float.h>
#include <iostream>
#include <string>
#include <string.h>
#include <inttypes.h>

#include <thread>
#include <mutex>

#include <limits>
#include <limits.h>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include <time.h>
#include <memory.h>
#include <math.h>
#include <memory>

#include <array>
#include <bitset>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include <functional>
#include <condition_variable>
#include <cstring>
#include <random>
#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>


//////////////////////////////////////////////////
//
//  Feature control
//


// Initially off those
#ifndef SF_USE_VULKAN
#if !X32
#define SF_USE_VULKAN 0
#endif
#endif // SF_USE_VULKAN

#ifndef SF_USE_FBX
#define SF_USE_FBX 0
#endif


//////////////////////////////////////////////////
//
//  Windows headers
//


#if SF_PLATFORM == SF_PLATFORM_WINDOWS

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifdef _USE_32BIT_TIME_T
#error "Do not use 32bit time_t definition"
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif 

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <SDKDDKVer.h>
#include <crtdbg.h>
#include <SDKDDKVer.h>
//#include <Winnt.h>
#include <windows.h>
#include <stdint.h>

#include <psapi.h>
#include <DbgHelp.h>

#include <crtdbg.h>
#include <tchar.h>
//#include <atltrace.h>
#include <mbstring.h>
//#include <atlcore.h>
//#include <cstringt.h>
#include <winsock2.h>
#include <Mswsock.h>
#include <Ws2tcpip.h>
#include <BaseTsd.h>
#include <wmsdkidl.h>
#include <shlwapi.h>
#include <intrin.h>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <stdint.h>
#include <sys/types.h>
#include <malloc.h>
#include <iphlpapi.h>

#define timegm _mkgmtime

#define INVALID_NATIVE_HANDLE_VALUE INVALID_HANDLE_VALUE

typedef HWND NativeWindow;
typedef unsigned int uint;
using SF_SOCKET = SOCKET;



//////////////////////////////////////////////////
//
//  Linux headers
//


#elif SF_PLATFORM == SF_PLATFORM_LINUX

#include <pthread.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <execinfo.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <signal.h>
#include <semaphore.h>
#include <malloc.h>
#include <aio.h>

//#include <linux/in.h>
//#include <linux/in6.h>
#include <stdint.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <net/if.h>
#include <net/if_arp.h>

typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef void* PVOID;
typedef wchar_t WCHAR;

typedef unsigned int uint;
typedef int INT;

typedef unsigned int DWORD;
typedef unsigned short WORD;


// Additional alise type
typedef int8_t				SBYTE;
typedef SBYTE				*PSBYTE;


typedef intptr_t HANDLE;
typedef HANDLE HMODULE;

typedef intptr_t NativeWindow;

#define INVALID_NATIVE_HANDLE_VALUE NativeHandle(-1)

#define __forceinline __attribute__((always_inline))

#define TRUE (1)
#define FALSE (0)



#define IN
#define OUT

using SF_SOCKET = int;
#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif



#define MAX_PATH 512

//#define HAVE_EGL 0
//#define HAVE_GLES 0




//////////////////////////////////////////////////
//
//  Android headers
//


#elif SF_PLATFORM == SF_PLATFORM_ANDROID


#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <assert.h>
#include <malloc.h>

#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <linux/in6.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <stdint.h>
#include <unwind.h>
#include <dlfcn.h>
#include <android/log.h>
#include <android/native_window.h>


#if __ANDROID_API__ < 23
time_t timegm_Internal(struct tm * a_tm);
#define timegm timegm_Internal
#endif


typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef void* PVOID;
typedef wchar_t WCHAR;

typedef unsigned int uint;
typedef int INT;

typedef unsigned int DWORD;
typedef unsigned short WORD;


// Additional alise type
typedef int8_t				SBYTE;
typedef SBYTE				*PSBYTE;


typedef intptr_t HANDLE;
typedef HANDLE HMODULE;

typedef struct ANativeWindow* NativeWindow;

#define INVALID_NATIVE_HANDLE_VALUE NativeHandle(-1)

#define __forceinline __attribute__((always_inline))

#define TRUE (1)
#define FALSE (0)



#define IN
#define OUT

using SF_SOCKET = int;
#define INVALID_SOCKET (-1)


#define MAX_PATH 512


#define EPOLL 1

#define HAVE_EGL 1
#define HAVE_GLES 1





//////////////////////////////////////////////////
//
//  IOS headers
//


#elif SF_PLATFORM == SF_PLATFORM_IOS


#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <assert.h>

#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <stdint.h>
#include <dlfcn.h>




typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef void* PVOID;
typedef wchar_t WCHAR;

typedef unsigned int uint;
typedef int INT;

typedef unsigned int DWORD;
typedef unsigned short WORD;


// Additional alise type
typedef int8_t				SBYTE;
typedef SBYTE				*PSBYTE;


typedef void* HANDLE;
typedef HANDLE HMODULE;

typedef struct ANativeWindow* NativeWindow;

#define INVALID_NATIVE_HANDLE_VALUE NativeHandle(-1)



#define IN
#define OUT

using SF_SOCKET = int;
#define INVALID_SOCKET (-1)

#define TRUE 1
#define FALSE 0

#define MAX_PATH 512

#define KQUEUE 1

#define HAVE_EGL 0
#define HAVE_GLES 1

#else

#ifndef SWIG
#error "Not supported platform"
#endif

#endif





//////////////////////////////////////////////////
//
//  Common types
//



// Additional alias type
typedef int8_t				SBYTE;
typedef SBYTE				*PSBYTE;

typedef HANDLE				NativeHandle;


// Thread synchronize counter type
#if defined(X64)

// System sync counter type
typedef uint64_t	CounterType;
typedef int64_t	SignedCounterType;

// System atomic integer type
typedef uint64_t	SysUInt;
typedef int64_t	SysInt;

#else

// System sync counter type
typedef uint32_t	CounterType;
typedef int32_t	SignedCounterType;

// System atomic integer type
typedef int		SysInt;
typedef unsigned int		SysUInt;



#endif


////////////////////////////////////////////////////////////////////////////////
//
//	Keywords
//



#if __GNUC__ || SF_PLATFORM == SF_PLATFORM_IOS


#define SF_DO_PRAGMA(x) _Pragma (#x)
#define SF_COMPILETIME_TODO(x) SF_DO_PRAGMA(message ("TODO - " #x))
#define SF_COMPILETIME_MESSAGE(x) SF_DO_PRAGMA(message ("Message - " #x))
#define SF_COMPILETIME_WARNING(x) SF_DO_PRAGMA(message ("Warning - " #x))


#else


// disable unreferenced label warning (Proc_End)
#pragma warning(disable: 4102)
#pragma warning(disable: 4996)
#pragma warning(disable: 4091) // disable warning 4091
#pragma warning(disable: 4201) // 
#pragma warning(disable: 4100) // Allow unreferenced parameter
#pragma warning(disable: 4324) // Structure padding by alignment specifier
#pragma warning(disable: 4611) // interaction between 'xx' and C++ object destruction is non-portable


#define SF_DO_PRAGMA(x) __pragma(#x)
#define SF_COMPILETIME_TODO(x) SF_DO_PRAGMA(comment ("TODO - " #x))
#define SF_COMPILETIME_MESSAGE(x) SF_DO_PRAGMA(comment ("Message - " #x))
#define SF_COMPILETIME_WARNING(x) SF_DO_PRAGMA(comment ("Warning - " #x))


#endif



////////////////////////////////////////////////////////////////////////////////
//
//	Memory alighment
//

#ifdef X64
#define SF_ALIGN				16
#define SF_ALIGN_SHIFT			4
#define SF_ALIGN_DOUBLE			16
#define SF_ALIGN_DOUBLE_SHIFT	4
#else
#define SF_ALIGN				16
#define SF_ALIGN_SHIFT			4
#define SF_ALIGN_DOUBLE			16
#define SF_ALIGN_DOUBLE_SHIFT	4
#endif

#if __GNUC__
#define SF_DECLARE_ALIGN		__attribute__((aligned(SF_ALIGN)))
#define SF_DECLARE_ALIGN_DOUBLE __attribute__((aligned(SF_ALIGN_DOUBLE)))
#else
#define SF_DECLARE_ALIGN		__declspec(align(SF_ALIGN))
#define SF_DECLARE_ALIGN_DOUBLE __declspec(align(SF_ALIGN_DOUBLE))
#endif

//#define AlignUp(x,allign)	( (((uintptr_t)(x) + allign-1) & (~((uintptr_t)allign-1))) )



////////////////////////////////////////////////////////////////////////////////
//
//	common SF types
//

#include "SFResult.h"
#include "SFNetAddress.h"
#include "SFScopeContext.h"
#include "Interfaces/SFPublicInterface.h"

namespace SF {

	typedef char* pchar;
	typedef wchar_t* pwchar;

	using std::atomic;

	template<typename DataType, typename D = std::default_delete<DataType>>
	using UniquePtr = std::unique_ptr<DataType,D>;
	
	using MemoryOrder = std::memory_order;

	using ClockType = std::chrono::steady_clock;
	using DurationSec = std::chrono::duration<uint>;
	using TimeStampSec = std::chrono::time_point<ClockType, DurationSec>;

	using DurationMS = std::chrono::duration<uint, std::milli>;
	using DurationMSDouble = std::chrono::duration<uint64_t, std::milli>;

	using UTCClockType = std::chrono::system_clock;
	using UTCTimeStampMS = std::chrono::time_point<UTCClockType, DurationMSDouble>;
	using UTCTimeStampSec = std::chrono::time_point<UTCClockType, DurationSec>;

	using TimeStampMS = std::chrono::time_point<ClockType, DurationMS>;
	using SystemTimeStampMS = std::chrono::system_clock::time_point;

	using DurationMicro = std::chrono::duration<uint64_t, std::micro>;
	using TimeStampMicro = std::chrono::time_point<ClockType, DurationMicro>;

	template<class ToDurationType, class InputType>
	ToDurationType DurationCast(InputType Value) { return std::chrono::duration_cast<ToDurationType>(Value); }


	extern const TimeStampMS TimeStampMS_Zero;
	extern const DurationMS  DurationMS_Zero;


	typedef std::thread::id ThreadID;
	typedef std::thread::native_handle_type			ThreadHandle;

	typedef char* CharPtr;
	typedef wchar_t* WCharPtr;

	// unique actor id in zone instance
	using ActorID = uint32_t;


	struct uint128_t
	{
		uint64_t Low;
		uint64_t High;
	};



	// Network class definition
	enum class NetClass : uint32_t
	{
		Unknown,
		Client,
		Server,
		//Entity,
		Login,
		GameInstance,
		GameMaster,
		Game,
		Max
	};




	// Supporting extra accessibility
	template<typename DataType>
	class Atomic : public std::atomic<DataType>
	{
	public:

		using super = std::atomic<DataType>;

	public:
		Atomic()
			: super(DataType{})
		{
		}

		Atomic(const DataType& value)
			: super(value)
		{
		}

		Atomic(const Atomic<DataType>& value)
			: super(value.load(MemoryOrder::memory_order_acquire))
		{
		}


		Atomic<DataType>& operator = (const Atomic<DataType>& src)
		{
			super::store(src.load(MemoryOrder::memory_order_acquire), MemoryOrder::memory_order_release);
			return *this;
		}

		Atomic<DataType>& operator = (const DataType& src)
		{
			super::store(src, MemoryOrder::memory_order_release);
			return *this;
		}

	};




	template <typename T, std::size_t N>
	constexpr std::size_t countof(T const (&)[N]) noexcept	{ return N; }

	// forward an lvalue as either an lvalue or an rvalue, delegate of std::forward
	template<typename DataType>
	[[nodiscard]] constexpr DataType&& Forward(std::remove_reference_t<DataType>& _Arg) noexcept
	{
		return static_cast<DataType&&>(_Arg);
	}

	template<typename DataType>
	[[nodiscard]] constexpr DataType&& Forward(std::remove_reference_t<DataType>&& _Arg) noexcept
	{
		return static_cast<DataType&&>(_Arg);
	}

	#define OffsetOf(s,m) ((size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
	#define ContainerPtrFromMemberDirect(ContainerTypeT, member, memberPtr) ((ContainerTypeT*)((uint8_t*)(memberPtr) - OffsetOf(ContainerTypeT,member)))
	#define ContainerPtrFromMember(ContainerTypeT, member, memberPtr) (memberPtr ? ContainerPtrFromMemberDirect(ContainerTypeT, member, memberPtr) : nullptr)


#ifndef SWIG

	template<class ... ArgTypes>
	inline void unused(ArgTypes...) {}

#endif



	Result GetLastResultCode();
};


#include "ResultCode/SFResultCodeSystem.h"


/////////////////////////////////////////////////////////////////////
//
//	Type utility for global
//

// Some old compiler require them in global scope

bool operator == (const sockaddr_storage& op1, const sockaddr_storage& op2);
bool operator == (const sockaddr_in& op1, const sockaddr_in& op2);
bool operator == (const sockaddr_in6& op1, const sockaddr_in6& op2);


template<class DataType> inline bool IsDefaultValue(const DataType& value) { DataType defaultValue{}; return value == defaultValue; }

template<> inline bool IsDefaultValue(const std::function<void()>& value) { return !(bool)value; }

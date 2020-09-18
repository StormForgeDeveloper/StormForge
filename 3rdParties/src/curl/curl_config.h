#ifndef HEADER_CURL_CONFIG_H
#define HEADER_CURL_CONFIG_H

/////////////////////////////////////////////////////////////////////////////
//
//	StromForge
//  Author: KyungKun Ko
//

#include <stdint.h>

#ifdef __ANDROID__
#define OS "android"
#elif defined(_WIN32) || defined(_WIN64)
#define OS "windows"
#elif defined(__IOS__)
#define OS "IOS"
#else
#define OS "Linux"
#endif


/* ---------------------------------------------------------------- */
/*                            TYPE SIZES                            */
/* ---------------------------------------------------------------- */

/* Define to the size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* Define to the size of `long double', as computed by sizeof. */
#define SIZEOF_LONG_DOUBLE 16

/* Define to the size of `long long', as computed by sizeof. */
/* #define SIZEOF_LONG_LONG 8 */

/* Define to the size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* Define to the size of `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* Define to the size of `size_t', as computed by sizeof. */
#if SIZE_MAX >= ULLONG_MAX
#  define SIZEOF_SIZE_T 8
#else
#  define SIZEOF_SIZE_T 4
#endif

/* Define to the size of `curl_off_t', as computed by sizeof. */
#define SIZEOF_CURL_OFF_T 8


#if defined(_WIN32) || defined(_WIN64)
#define STDC_HEADERS            1
#define HAVE_WINDOWS_H          1
#define HAVE_STRDUP             1
#define HAVE_IOCTLSOCKET_FIONBIO 1
#define HAVE_STRUCT_POLLFD 1

#define HAVE_CLOSESOCKET		1

#include <BaseTsd.h>
/* Define if ssize_t is not an available 'typedefed' type. */
#ifndef _SSIZE_T_DEFINED
#  if (defined(__WATCOMC__) && (__WATCOMC__ >= 1240)) || \
      defined(__POCC__) || \
      defined(__MINGW32__)
#  elif defined(_WIN64)
#    define _SSIZE_T_DEFINED
#    define ssize_t __int64
#  else
#    define _SSIZE_T_DEFINED
#    define ssize_t int
#  endif
#endif


/* Define if struct sockaddr_in6 has the sin6_scope_id member. */
#define HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID 1
#define HAVE_WINSOCK2_H         1
#define HAVE_WS2TCPIP_H         1

#else
#define HAVE_SYS_TIME_H         1
#define HAVE_UNISTD_H           1
#define HAVE_SYS_SOCKET_H       1
#define HAVE_UTIME_H            1
#define HAVE_FCNTL_O_NONBLOCK 1
#define HAVE_SYS_SELECT_H       1
#define HAVE_NETINET_IN_H       1
#define HAVE_NETDB_H            1
#define HAVE_ARPA_INET_H        1
#define HAVE_NET_IF_H           1
#define HAVE_SIGACTION          1

#endif

#define HAVE_LONGLONG           1

/* Define if you want the built-in manual */
#define HAVE_ASSERT_H			1
#define USE_MANUAL              1
#define HAVE_ERRNO_H            1
#define HAVE_SYS_TYPES_H        1
#define HAVE_GETTIMEOFDAY       1
#define HAVE_FCNTL_H            1
#define HAVE_SYS_STAT_H         1
#define HAVE_ALLOCA_H           1
#define HAVE_STDLIB_H           1
#define HAVE_TIME_H             1
#define HAVE_SYS_UTIME_H        1
#define HAVE_STRUCT_TIMEVAL     1

#define TIME_WITH_SYS_TIME      1

#define HAVE_ALARM              1
#define HAVE_FTRUNCATE          1
#define HAVE_UTIME              1
#define HAVE_SETVBUF            1
#define HAVE_STRFTIME           1
#define HAVE_INET_ADDR          1
#define HAVE_MEMCPY             1
#define HAVE_SELECT             1
#define HAVE_SOCKET             1

/* Define if you have the strdup function. */
#define HAVE_STRDUP 1

/* Define if you have the strftime function. */
#define HAVE_STRFTIME 1

/* Define if you have the stricmp function. */
#define HAVE_STRICMP 1

/* Define if you have the strncasecmp function. */
/* #define HAVE_STRNCASECMP 1 */

/* Define if you have the strnicmp function. */
#define HAVE_STRNICMP 1

/* Define if you have the strstr function. */
#define HAVE_STRSTR 1

#define HAVE_SIGNAL_H           1
#define HAVE_SIG_ATOMIC_T       1

/* Define if you have the setmode function. */
#define HAVE_SETMODE 1

/* Define if you have the setlocale function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the <inttypes.h> header file. */
#if defined(_MSC_VER) && (_MSC_VER >= 1800)
#define HAVE_INTTYPES_H 1
#endif

/* Define if you have the <io.h> header file. */
#define HAVE_IO_H 1

/* Define if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <stdbool.h> header file. */
#if defined(_MSC_VER) && (_MSC_VER >= 1800)
#define HAVE_STDBOOL_H 1
#endif

#undef USE_OPENSSL
#define USE_MBEDTLS

/* Define if you have the `CRYPTO_cleanup_all_ex_data' function.
This is present in OpenSSL versions after 0.9.6b */
#define HAVE_CRYPTO_CLEANUP_ALL_EX_DATA 1


#define CURL_DISABLE_LDAP       1

/* Define if you have the perror function. */
#define HAVE_PERROR 1

/* Define if you have the RAND_screen function when using SSL. */
#define HAVE_RAND_SCREEN 1

#define HAVE_RAND_STATUS        1
#define HAVE_RAND_EGD           1

//#define HAVE_IOCTL              1
//#define HAVE_IOCTL_FIONBIO      1
/* Define if you have the ioctlsocket function. */
#define HAVE_IOCTLSOCKET 1


#define RETSIGTYPE void



/* Define if you have the gethostname function. */
#define HAVE_GETHOSTNAME 1

/* Define if you have the getservbyname function. */
#define HAVE_GETSERVBYNAME 1

/* Define if you have the getprotobyname function. */
#define HAVE_GETPROTOBYNAME



#define HAVE_GETNAMEINFO 1
#define GETNAMEINFO_QUAL_ARG1 const
#define GETNAMEINFO_TYPE_ARG1 struct sockaddr *
#define GETNAMEINFO_TYPE_ARG2 socklen_t
#define GETNAMEINFO_TYPE_ARG46 size_t
#define GETNAMEINFO_TYPE_ARG7 int

#define HAVE_RECV 1
#define RECV_TYPE_ARG1 int
#define RECV_TYPE_ARG2 void *
#define RECV_TYPE_ARG3 size_t
#define RECV_TYPE_ARG4 int
#define RECV_TYPE_RETV ssize_t

#define HAVE_RECVFROM 1
#define RECVFROM_TYPE_ARG1 int
#define RECVFROM_TYPE_ARG2 void
#define RECVFROM_TYPE_ARG3 size_t
#define RECVFROM_TYPE_ARG4 int
#define RECVFROM_TYPE_ARG5 struct sockaddr
#define RECVFROM_TYPE_ARG6 int
#define RECVFROM_TYPE_RETV ssize_t
#define RECVFROM_TYPE_ARG2_IS_VOID 1

#define HAVE_SEND 1
#define SEND_TYPE_ARG1 int
#define SEND_QUAL_ARG2 const
#define SEND_TYPE_ARG2 void *
#define SEND_TYPE_ARG3 size_t
#define SEND_TYPE_ARG4 int
#define SEND_TYPE_RETV ssize_t

//#define HAVE_EXTRA_STRICMP_H 1
//#define HAVE_EXTRA_STRDUP_H  1

#endif /* HEADER_CURL_CONFIG_MAC_H */

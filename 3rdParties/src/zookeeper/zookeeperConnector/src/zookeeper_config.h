#pragma once



#ifdef WIN32

#else

#define HAVE_UNISTD_H
#define HAVE_POLL
#define HAVE_ARPA_INET_H
#define HAVE_SYS_SOCKET_H
#define HAVE_SYS_TIME_H
#define HAVE_NETINET_IN_H
#define HAVE_SYS_UTSNAME_H

#endif


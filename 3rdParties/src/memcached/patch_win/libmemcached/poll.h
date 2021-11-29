/* LibMemcached
 * Copyright (C) 2013 Data Differential, http://datadifferential.com/
 * Copyright (C) 2010 Brian Aker, Trond Norbye
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license.  See
 * the COPYING file in the parent directory for full text.
 *
 * Summary: Implementation of poll by using select
 *
 */

#pragma once

#if defined(_WIN32)

#include <winsock2.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_WIN32)
	typedef struct pollfd
{
  int fd;
  short events;
  short revents;
} pollfd_t;
#endif

typedef int nfds_t;

#if !defined(_WIN32)

#define POLLIN 0x0001
#define POLLOUT 0x0004
#define POLLERR 0x0008
#define POLLHUP		0x010		/* Hung up.  */
#define POLLNVAL	0x020		/* Invalid polling request.  */
#endif

int poll(struct pollfd fds[], nfds_t nfds, int tmo);

#ifdef __cplusplus
}
#endif

#endif // defined(_WIN32)

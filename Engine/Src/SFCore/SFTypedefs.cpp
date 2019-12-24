////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFAssert.h"
#include "String/SFStrUtil.h"
#include "ResultCode/SFResultCodeSystem.h"



/////////////////////////////////////////////////////////////////////
//
//	Type utility for global
//

bool operator == (const sockaddr_storage& op1, const sockaddr_storage& op2)
{
	if (op1.ss_family != op2.ss_family)
		return false;

	if (op1.ss_family == AF_INET)
	{
		return memcmp((sockaddr_in*)&op1, (sockaddr_in*)&op2, sizeof(sockaddr_in)) == 0;
	}
	else
	{
		return memcmp((sockaddr_in6*)&op1, (sockaddr_in6*)&op2, sizeof(sockaddr_in6)) == 0;
	}
}

bool operator == (const sockaddr_in& op1, const sockaddr_in& op2)
{
	return memcmp((sockaddr_in*)&op1, (sockaddr_in*)&op2, sizeof(sockaddr_in)) == 0;
}

bool operator == (const sockaddr_in6& op1, const sockaddr_in6& op2)
{
	return memcmp((sockaddr_in6*)&op1, (sockaddr_in6*)&op2, sizeof(sockaddr_in6)) == 0;
}



namespace SF {

	/////////////////////////////////////////////////////////////////////
	//
	//	Type utility
	//


#if SF_PLATFORM == SF_PLATFORM_WINDOWS

	Result GetLastResultCode()
	{
		// TODO: Need to translate them to internal error code
		return Result(HRESULT_FROM_WIN32(GetLastError()));
	}

#elif SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID || SF_PLATFORM == SF_PLATFORM_IOS

	Result GetLastResultCode()
	{
		int ierr = errno;
		switch (ierr)
		{
		case 0: return ResultCode::SUCCESS;
		case EPERM: return ResultCode::NO_PERMITION;
		case ENOENT: return ResultCode::NO_FILE_OR_DIR;
		case ESRCH: return ResultCode::NO_SUCH_PROCESS;
		case EINTR: return ResultCode::INTERRUPTED_SYSCALL;
		case EIO: return ResultCode::IO_ERROR;
		case ENXIO: return ResultCode::NOT_DEVICE;
		case E2BIG: return ResultCode::TOO_MANY_ARGLIST;
		case ENOEXEC: return ResultCode::INVALID_EXEC_FROMAT;
		case EBADF: return ResultCode::INVALID_FILE_HANDLE;
		case ECHILD: return ResultCode::NO_CHILD_PROCESS;
		case ENOMEM: return ResultCode::OUT_OF_MEMORY;
		case EACCES: return ResultCode::NO_PERMITION;
		case EFAULT: return ResultCode::INVALID_POINTER;
		case ENOTBLK: return ResultCode::NOT_BLOCK;
		case EBUSY: return ResultCode::BUSY;
		case EEXIST: return ResultCode::FILE_EXISTS;
		case EXDEV: return ResultCode::CROSS_LINK;
		case ENODEV: return ResultCode::INVALID_DEVICE;
		case ENOTDIR: return ResultCode::INVALID_DIRECTORY;
		case EISDIR: return ResultCode::DIRECTORY;
		case EINVAL: return ResultCode::INVALID_ARG;
		case ENFILE: return ResultCode::NOT_ENOUGH_FILE_TABLE;
		case EMFILE: return ResultCode::TOO_MANY_OPENED_FILE;
		case ENOTTY: return ResultCode::INVALID_TYPEWRITER;
		case ETXTBSY: return ResultCode::BUSY_FILE;
		case EFBIG: return ResultCode::TOO_BIG_FILE;
		case ENOSPC: return ResultCode::NOT_ENOUGH_SPACE;
		case ESPIPE: return ResultCode::INVALID_SEEK;
		case EROFS: return ResultCode::READ_ONLY;
		case EMLINK: return ResultCode::TOO_MANY_LINK;
		case EPIPE: return ResultCode::INVALID_PIPE;
		case EDOM: return ResultCode::INVALID_MATH_DOMAIN;

		case ERANGE: return ResultCode::INVALID_NUMERIC;
		//case EBADF: return ResultCode::IO_BADF;
		//case EACCES: return ResultCode::IO_ACCES;
		//case EFAULT: return ResultCode::IO_FAULT;
		//case EINVAL: return ResultCode::IO_INVAL;
		//case EMFILE: return ResultCode::IO_MFILE;
		case EWOULDBLOCK: return ResultCode::IO_WOULDBLOCK; // Linux epoll
#if (EWOULDBLOCK - EAGAIN) != 0
		case EAGAIN: return ResultCode::IO_TRY_AGAIN;
#endif
		case EINPROGRESS: return ResultCode::IO_INPROGRESS;
		case EALREADY: return ResultCode::IO_ALREADY;
		case ENOTSOCK: return ResultCode::IO_NOTSOCK;
		case EDESTADDRREQ: return ResultCode::IO_DESTADDRREQ;
		case ENETDOWN: return ResultCode::IO_NETDOWN;
		case ENETUNREACH: return ResultCode::IO_NETUNREACH;
		case ENETRESET: return ResultCode::IO_NETRESET;
		case ECONNABORTED: return ResultCode::IO_CONNABORTED;
		case ECONNRESET: return ResultCode::IO_CONNRESET;
		case ENOBUFS: return ResultCode::IO_NOBUFS;
		case EISCONN: return ResultCode::IO_ISCONN;
		case ENOTCONN: return ResultCode::IO_NOTCONN;
		case ESHUTDOWN: return ResultCode::IO_SHUTDOWN;
		case ETOOMANYREFS: return ResultCode::IO_TOOMANYREFS;
		case ETIMEDOUT: return ResultCode::IO_TIMEDOUT;
		case ECONNREFUSED: return ResultCode::IO_CONNECTION_REFUSSED;
		case ELOOP: return ResultCode::IO_LOOP;
		case ENAMETOOLONG: return ResultCode::IO_NAMETOOLONG;

		case EHOSTDOWN: return ResultCode::IO_HOSTDOWN;
		case EHOSTUNREACH: return ResultCode::IO_HOSTUNREACH;
		case ENOTEMPTY: return ResultCode::IO_NOTEMPTY;
		case EPROTO: return ResultCode::IO_PROTO;
		case EPROTOTYPE: return ResultCode::IO_PROTOTYPE;
		case ENOPROTOOPT: return ResultCode::IO_NOPROTOOPT;
#if SF_PLATFORM != SF_PLATFORM_IOS
		case ENONET: return ResultCode::IO_NONET;
#endif
		case EOPNOTSUPP: return ResultCode::IO_OPNOTSUPP;
		case EADDRINUSE: return ResultCode::IO_ADDRINUSE;
			//case EPROCLIM: return ResultCode::IO_PROCLIM;
			//case SYSNOTREADY: return ResultCode::IO_SYSNOTREADY;
			//case VERNOTSUPPORTED: return ResultCode::IO_VERNOTSUPPORTED;
			//case NOTINITIALISED: return ResultCode::IO_NOTINITIALISED;
			//case EDISCON: return ResultCode::IO_DISCON;
			//case SYSCALLFAILURE: return ResultCode::IO_SYSCALLFAILURE;
			//case HOST_NOT_FOUND: return ResultCode::IO_HOST_NOT_FOUND;

			//case TRY_AGAIN: return ResultCode::IO_TRY_AGAIN;
			//case _SECURE_HOST_NOT_FOUND: return ResultCode::IO_SECURE_HOST_NOT_FOUND;
			//case WSA_IO_PENDING: return ResultCode::IO_IO_PENDING;
		default:
			return ResultCode::UNEXPECTED;
		}
	}
    
#else
    
    #error "Not supported platform"

#endif



	const TimeStampMS TimeStampMS_Zero = TimeStampMS(DurationMS(0));
	const DurationMS DurationMS_Zero = DurationMS(0);





} // namespace SF



  // Backup implementation for timegm
time_t timegm_Internal(struct tm * a_tm)
{
	time_t ltime = mktime(a_tm);
	struct tm tm_val;
	tm_val = *gmtime(&ltime);
	int offset = (tm_val.tm_hour - a_tm->tm_hour);
	if (offset > 12)
	{
		offset = 24 - offset;
	}
	time_t utc = mktime(a_tm) - offset * 3600;
	return utc;
}


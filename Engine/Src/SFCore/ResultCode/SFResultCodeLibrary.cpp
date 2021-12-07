﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated header, SF
//
////////////////////////////////////////////////////////////////////////////////

#include "SFTypedefs.h"
#include "ResultCode/SFResultTable.h"
#include "ResultCode/SFResultCodeLibrary.h"



namespace SF {
namespace ResultCode {

	void InitializeResultCodeSF() {

		auto& codeMap = ResultTable::GetOrAddFacility(1793);
		codeMap.Insert(INVALID_BYTE_SEQUENCE, {"INVALID_BYTE_SEQUENCE", "Invalid byte sequence. usually caused by invalid data stream"});
		codeMap.Insert(DUPLICATE_COMPONENT, {"DUPLICATE_COMPONENT", "You can not register same name or type component"});
		codeMap.Insert(NOT_INITIALIZED, {"NOT_INITIALIZED", "Called without initialization."});
		codeMap.Insert(VERSION_NOT_AVAIL, {"VERSION_NOT_AVAIL", "The version not available or miss match with system."});
		codeMap.Insert(INVALID_CLUSTERMASTER, {"INVALID_CLUSTERMASTER", "Invalid Cluster Master server"});
		codeMap.Insert(INVALID_STATE, {"INVALID_STATE", "The version not available or miss match with system."});
		codeMap.Insert(INVALID_STR_FORMAT, {"INVALID_STR_FORMAT", "Invalid string format."});
		codeMap.Insert(DUPLICATED_SERVERID, {"DUPLICATED_SERVERID", "ServerID is duplicated."});
		codeMap.Insert(INVALID_ENTITY, {"INVALID_ENTITY", "Invalid entity"});
		codeMap.Insert(DUPLICATED_ENTITY, {"DUPLICATED_ENTITY", "Invalid duplicated entity"});
		codeMap.Insert(DUPLICATED_ENTITYID, {"DUPLICATED_ENTITYID", "Invalid duplicated entity"});
		codeMap.Insert(DUPLICATED_ACCOUNTID, {"DUPLICATED_ACCOUNTID", "Duplicated Account ID"});
		codeMap.Insert(DUPLICATED_PLAYERID, {"DUPLICATED_PLAYERID", "Duplicated Player ID"});
		codeMap.Insert(DUPLICATED_NAME, {"DUPLICATED_NAME", "Duplicated name"});
		codeMap.Insert(DUPLICATED_ID, {"DUPLICATED_ID", "Duplicated ID"});
		codeMap.Insert(INVALID_ACCOUNTID, {"INVALID_ACCOUNTID", "Invalid duplicated entity"});
		codeMap.Insert(INVALID_TICKET, {"INVALID_TICKET", "Invalid ticket"});
		codeMap.Insert(INVALID_PLAYERID, {"INVALID_PLAYERID", "Invalid player ID"});
		codeMap.Insert(INVALID_VALUE, {"INVALID_VALUE", "Invalid value"});
		codeMap.Insert(INVALID_CLASS, {"INVALID_CLASS", "Invalid class value"});
		codeMap.Insert(INVALID_DIFFICULTY, {"INVALID_DIFFICULTY", "Invalid Difficulty"});
		codeMap.Insert(INVALID_REGISTRATION, {"INVALID_REGISTRATION", "Invalid registration to play"});
		codeMap.Insert(INVALID_CHANNELID, {"INVALID_CHANNELID", "Invalid Channel ID"});
		codeMap.Insert(INVALID_INSTANCEID, {"INVALID_INSTANCEID", "Invalid Zone instance ID"});
		codeMap.Insert(DUPLICATED_COMPONENT, {"DUPLICATED_COMPONENT", "Duplicated component"});
		codeMap.Insert(MAX_FRIEND, {"MAX_FRIEND", "Maximum friend"});
		codeMap.Insert(INVALID_PLAYER_COUNT, {"INVALID_PLAYER_COUNT", "Invalid player count for service"});
		codeMap.Insert(INVALID_PLAYER_LEVEL, {"INVALID_PLAYER_LEVEL", "Invalid player level"});
		codeMap.Insert(INVALID_PLAYER_NICK, {"INVALID_PLAYER_NICK", "Invalid player nick"});
		codeMap.Insert(INVALID_NOTIFICATIONID, {"INVALID_NOTIFICATIONID", "Invalid Notification ID"});
		codeMap.Insert(INVALID_RANKING_RANGE, {"INVALID_RANKING_RANGE", "Invalid Ranking range"});
		codeMap.Insert(TARGET_MAX_FRIEND, {"TARGET_MAX_FRIEND", "Target Maximum friend"});
		codeMap.Insert(INVALID_STR_DATA, {"INVALID_STR_DATA", "Invalid string data."});
		codeMap.Insert(NOT_AUTORIZED, {"NOT_AUTORIZED", "Not authorized"});
		codeMap.Insert(NO_PERMITION, {"NO_PERMITION", "No permition"});
		codeMap.Insert(NO_FILE_OR_DIR, {"NO_FILE_OR_DIR", "No file or directory"});
		codeMap.Insert(NO_SUCH_PROCESS, {"NO_SUCH_PROCESS", "No such process"});
		codeMap.Insert(INTERRUPTED_SYSCALL, {"INTERRUPTED_SYSCALL", "Interrupted system call"});
		codeMap.Insert(IO_ERROR, {"IO_ERROR", "I/O error"});
		codeMap.Insert(NOT_DEVICE, {"NOT_DEVICE", "No such device or address"});
		codeMap.Insert(TOO_MANY_ARGLIST, {"TOO_MANY_ARGLIST", "Arg list too long"});
		codeMap.Insert(INVALID_EXEC_FROMAT, {"INVALID_EXEC_FROMAT", "Exec format error"});
		codeMap.Insert(INVALID_FILE_HANDLE, {"INVALID_FILE_HANDLE", "Bad file number"});
		codeMap.Insert(NO_CHILD_PROCESS, {"NO_CHILD_PROCESS", "No child process"});
		codeMap.Insert(NOT_BLOCK, {"NOT_BLOCK", "Block device required"});
		codeMap.Insert(NOT_EXIST, {"NOT_EXIST", "Not exist"});
		codeMap.Insert(BUSY, {"BUSY", "Busy"});
		codeMap.Insert(FILE_EXISTS, {"FILE_EXISTS", "File exists"});
		codeMap.Insert(CROSS_LINK, {"CROSS_LINK", "Cross-device link"});
		codeMap.Insert(INVALID_DEVICE, {"INVALID_DEVICE", "No such device"});
		codeMap.Insert(INVALID_DIRECTORY, {"INVALID_DIRECTORY", "Not a directory"});
		codeMap.Insert(DIRECTORY, {"DIRECTORY", "Is a directory"});
		codeMap.Insert(NOT_ENOUGH_FILE_TABLE, {"NOT_ENOUGH_FILE_TABLE", "File table overflow"});
		codeMap.Insert(TOO_MANY_OPENED_FILE, {"TOO_MANY_OPENED_FILE", "Too many open files"});
		codeMap.Insert(INVALID_TYPEWRITER, {"INVALID_TYPEWRITER", "Not a typewriter"});
		codeMap.Insert(BUSY_FILE, {"BUSY_FILE", "Text file busy"});
		codeMap.Insert(TOO_BIG_FILE, {"TOO_BIG_FILE", "File too large"});
		codeMap.Insert(NOT_ENOUGH_SPACE, {"NOT_ENOUGH_SPACE", "No space left on device"});
		codeMap.Insert(INVALID_SEEK, {"INVALID_SEEK", "Illegal seek"});
		codeMap.Insert(READ_ONLY, {"READ_ONLY", "Read-only file system"});
		codeMap.Insert(TOO_MANY_LINK, {"TOO_MANY_LINK", "Too many links"});
		codeMap.Insert(INVALID_PIPE, {"INVALID_PIPE", "Broken pipe"});
		codeMap.Insert(INVALID_MATH_DOMAIN, {"INVALID_MATH_DOMAIN", "Math argument out of domain of func"});
		codeMap.Insert(INVALID_NUMERIC, {"INVALID_NUMERIC", "Math result not representable"});
		codeMap.Insert(INVALID_PASSWORD, {"INVALID_PASSWORD", "Invalid password"});
		codeMap.Insert(ALREADY_IN_FRIEND, {"ALREADY_IN_FRIEND", "Target already in friends list"});
		codeMap.Insert(INVALID_THREAD, {"INVALID_THREAD", "Thread is wrong, running on wrong thread?"});
		codeMap.Insert(ALREADY_EXIST, {"ALREADY_EXIST", "Requested object already exist"});
		codeMap.Insert(SUCCESS_IO_PROCESSED_SEQUENCE, {"SUCCESS_IO_PROCESSED_SEQUENCE", "Network sequence already processed"});
		codeMap.Insert(IO_PROTOCOL_VERSION_MISMATCH, {"IO_PROTOCOL_VERSION_MISMATCH", "The version not available or miss match with system."});
		codeMap.Insert(IO_NOTINITIALIZED, {"IO_NOTINITIALIZED", "Network is not initialized"});
		codeMap.Insert(IO_INVALID_NETCLASS, {"IO_INVALID_NETCLASS", "The version not available or miss match with system."});
		codeMap.Insert(IO_NOT_ENOUGH_WINDOWSPACE, {"IO_NOT_ENOUGH_WINDOWSPACE", "Not enough space in sliding window"});
		codeMap.Insert(IO_IO_ABORTED, {"IO_IO_ABORTED", "Network IO aborted"});
		codeMap.Insert(IO_IO_SEND_FAIL, {"IO_IO_SEND_FAIL", "Network IO send failed"});
		codeMap.Insert(IO_IO_RECV_FAIL, {"IO_IO_RECV_FAIL", "Network IO recv failed"});
		codeMap.Insert(IO_SEND_FAIL, {"IO_SEND_FAIL", "Network send failed"});
		codeMap.Insert(IO_RECV_FAIL, {"IO_RECV_FAIL", "Network recv failed"});
		codeMap.Insert(IO_INVALID_SEQUENCE, {"IO_INVALID_SEQUENCE", "Network Message sequence is invalid"});
		codeMap.Insert(IO_BADPACKET_SIZE, {"IO_BADPACKET_SIZE", "Network Message not expected bad packet size"});
		codeMap.Insert(IO_CONNECTION_CLOSED, {"IO_CONNECTION_CLOSED", "Network connection closed"});
		codeMap.Insert(IO_NOT_CONNECTED, {"IO_NOT_CONNECTED", "Network connection is never made"});
		codeMap.Insert(IO_INVALID_CID, {"IO_INVALID_CID", "Network connection ID is invalid"});
		codeMap.Insert(IO_CONNECTION_TIMEOUT, {"IO_CONNECTION_TIMEOUT", "Network Connection timeout"});
		codeMap.Insert(IO_CONNECTION_FAIL, {"IO_CONNECTION_FAIL", "Network connection is failed"});
		codeMap.Insert(IO_BADPACKET_TOOBIG, {"IO_BADPACKET_TOOBIG", "Too big packet data"});
		codeMap.Insert(IO_BADPACKET_NOTEXPECTED, {"IO_BADPACKET_NOTEXPECTED", "Network Message not expected bad packet"});
		codeMap.Insert(IO_INVALID_MESSAGE_CHECKSUM, {"IO_INVALID_MESSAGE_CHECKSUM", "Checksum value of the message is invalid"});
		codeMap.Insert(IO_INVALID_MESSAGE_ENCRYPTION, {"IO_INVALID_MESSAGE_ENCRYPTION", "Message encryption is invalid"});
		codeMap.Insert(IO_INVALID_CONNECTION_STATE, {"IO_INVALID_CONNECTION_STATE", "Invalid connection state"});
		codeMap.Insert(IO_SEQUENCE_OVERFLOW, {"IO_SEQUENCE_OVERFLOW", "Too big sequence id"});
		codeMap.Insert(IO_WOULDBLOCK, {"IO_WOULDBLOCK", "A non-blocking socket operation could not be completed immediately."});
		codeMap.Insert(IO_INPROGRESS, {"IO_INPROGRESS", "A blocking operation is currently executing."});
		codeMap.Insert(IO_ALREADY, {"IO_ALREADY", "An operation was attempted on a non-blocking socket that already had an operation in progress."});
		codeMap.Insert(IO_NOTSOCK, {"IO_NOTSOCK", "An operation was attempted on something that is not a socket."});
		codeMap.Insert(IO_DESTADDRREQ, {"IO_DESTADDRREQ", "A required address was omitted from an operation on a socket."});
		codeMap.Insert(IO_NETDOWN, {"IO_NETDOWN", "A socket operation encountered a dead network."});
		codeMap.Insert(IO_NETUNREACH, {"IO_NETUNREACH", "A socket operation was attempted to an unreachable network."});
		codeMap.Insert(IO_NETRESET, {"IO_NETRESET", "The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress."});
		codeMap.Insert(IO_CONNABORTED, {"IO_CONNABORTED", "An established connection was aborted by the software in your host machine."});
		codeMap.Insert(IO_CONNRESET, {"IO_CONNRESET", "An existing connection was forcibly closed by the remote host."});
		codeMap.Insert(IO_NOBUFS, {"IO_NOBUFS", "An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full."});
		codeMap.Insert(IO_ISCONN, {"IO_ISCONN", "A connect request was made on an already connected socket."});
		codeMap.Insert(IO_NOTCONN, {"IO_NOTCONN", "A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied."});
		codeMap.Insert(IO_SHUTDOWN, {"IO_SHUTDOWN", "A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call."});
		codeMap.Insert(IO_TOOMANYREFS, {"IO_TOOMANYREFS", "Too many references to some kernel object."});
		codeMap.Insert(IO_TIMEDOUT, {"IO_TIMEDOUT", "A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond."});
		codeMap.Insert(IO_CONNECTION_REFUSSED, {"IO_CONNECTION_REFUSSED", "No connection could be made because the target machine actively refused it."});
		codeMap.Insert(IO_LOOP, {"IO_LOOP", "Cannot translate name."});
		codeMap.Insert(IO_NAMETOOLONG, {"IO_NAMETOOLONG", "Name component or name was too long."});
		codeMap.Insert(IO_HOSTDOWN, {"IO_HOSTDOWN", "A socket operation failed because the destination host was down."});
		codeMap.Insert(IO_HOSTUNREACH, {"IO_HOSTUNREACH", "A socket operation was attempted to an unreachable host."});
		codeMap.Insert(IO_NOTEMPTY, {"IO_NOTEMPTY", "Cannot remove a directory that is not empty."});
		codeMap.Insert(IO_PROCLIM, {"IO_PROCLIM", "A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously."});
		codeMap.Insert(IO_SYSNOTREADY, {"IO_SYSNOTREADY", "WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable."});
		codeMap.Insert(IO_VERNOTSUPPORTED, {"IO_VERNOTSUPPORTED", "The Windows Sockets version requested is not supported."});
		codeMap.Insert(IO_NOTINITIALISED, {"IO_NOTINITIALISED", "Either the application has not called WSAStartup, or WSAStartup failed."});
		codeMap.Insert(IO_DISCON, {"IO_DISCON", "Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence."});
		codeMap.Insert(IO_SYSCALLFAILURE, {"IO_SYSCALLFAILURE", "A system call has failed."});
		codeMap.Insert(IO_HOST_NOT_FOUND, {"IO_HOST_NOT_FOUND", "Host not found."});
		codeMap.Insert(IO_TRY_AGAIN, {"IO_TRY_AGAIN", "Try again"});
		codeMap.Insert(IO_IO_PENDING, {"IO_IO_PENDING", "IOPending"});
		codeMap.Insert(IO_SECURE_HOST_NOT_FOUND, {"IO_SECURE_HOST_NOT_FOUND", "No such host is known securely."});
		codeMap.Insert(IO_PROTO, {"IO_PROTO", "Protocol error"});
		codeMap.Insert(IO_PROTOTYPE, {"IO_PROTOTYPE", "Protocol wrong type for socket."});
		codeMap.Insert(IO_NOPROTOOPT, {"IO_NOPROTOOPT", "Protocol not available"});
		codeMap.Insert(IO_NONET, {"IO_NONET", "Machine is not on the network"});
		codeMap.Insert(IO_OPNOTSUPP, {"IO_OPNOTSUPP", "Operation not supported on socket"});
		codeMap.Insert(IO_BADFLAGS, {"IO_BADFLAGS", "An invalid value was provided for the ai_flags member of the pHints parameter."});
		codeMap.Insert(IO_FAMILY, {"IO_FAMILY", "Bad network family"});
		codeMap.Insert(IO_INVALID_SERVICE, {"IO_INVALID_SERVICE", "The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter."});
		codeMap.Insert(IO_INVALID_ADDRESS, {"IO_INVALID_ADDRESS", "Invalid network address"});
		codeMap.Insert(IO_ADDRINUSE, {"IO_ADDRINUSE", "Address in use"});
		codeMap.Insert(IO_BADPACKET, {"IO_BADPACKET", "Network Message not expected packet data"});
		codeMap.Insert(IO_DISCONNECTED, {"IO_DISCONNECTED", "Disconnected"});
		codeMap.Insert(IO_CANCELED, {"IO_CANCELED", "Canceled"});
		codeMap.Insert(ZK_SYSTEM, {"ZK_SYSTEM", "Zookeeper System and server-side errors."});
		codeMap.Insert(ZK_ZRUNTIMEINCONSISTENCY, {"ZK_ZRUNTIMEINCONSISTENCY", "Zookeeper  A runtime inconsistency was found"});
		codeMap.Insert(ZK_ZDATAINCONSISTENCY, {"ZK_ZDATAINCONSISTENCY", "Zookeeper A data inconsistency was found"});
		codeMap.Insert(ZK_ZCONNECTIONLOSS, {"ZK_ZCONNECTIONLOSS", "Zookeeper Connection to the server has been lost"});
		codeMap.Insert(ZK_ZMARSHALLINGERROR, {"ZK_ZMARSHALLINGERROR", "Zookeeper Error while marshalling or unmarshalling data"});
		codeMap.Insert(ZK_ZUNIMPLEMENTED, {"ZK_ZUNIMPLEMENTED", "Zookeeper Operation is unimplemented"});
		codeMap.Insert(ZK_ZOPERATIONTIMEOUT, {"ZK_ZOPERATIONTIMEOUT", "Zookeeper Operation timeout"});
		codeMap.Insert(ZK_ZBADARGUMENTS, {"ZK_ZBADARGUMENTS", "Zookeeper Invalid arguments"});
		codeMap.Insert(ZK_ZINVALIDSTATE, {"ZK_ZINVALIDSTATE", "Zookeeper Invliad zhandle state"});
		codeMap.Insert(ZK_ZAPIERROR, {"ZK_ZAPIERROR", "Zookeeper API errors."});
		codeMap.Insert(ZK_ZNONODE, {"ZK_ZNONODE", "Zookeeper Node does not exist"});
		codeMap.Insert(ZK_ZNOAUTH, {"ZK_ZNOAUTH", "Zookeeper Not authenticated"});
		codeMap.Insert(ZK_ZBADVERSION, {"ZK_ZBADVERSION", "Zookeeper Version conflict"});
		codeMap.Insert(ZK_ZNOCHILDRENFOREPHEMERALS, {"ZK_ZNOCHILDRENFOREPHEMERALS", "Zookeeper Ephemeral nodes may not have children"});
		codeMap.Insert(ZK_ZNODEEXISTS, {"ZK_ZNODEEXISTS", "Zookeeper The node already exists"});
		codeMap.Insert(ZK_ZNOTEMPTY, {"ZK_ZNOTEMPTY", "Zookeeper The node has children"});
		codeMap.Insert(ZK_ZSESSIONEXPIRED, {"ZK_ZSESSIONEXPIRED", "Zookeeper The session has been expired by the server"});
		codeMap.Insert(ZK_ZINVALIDCALLBACK, {"ZK_ZINVALIDCALLBACK", "Zookeeper Invalid callback specified"});
		codeMap.Insert(ZK_ZINVALIDACL, {"ZK_ZINVALIDACL", "Zookeeper Invalid ACL specified"});
		codeMap.Insert(ZK_ZAUTHFAILED, {"ZK_ZAUTHFAILED", "Zookeeper Client authentication failed"});
		codeMap.Insert(ZK_ZCLOSING, {"ZK_ZCLOSING", "Zookeeper Zookeeper is closing"});
		codeMap.Insert(ZK_ZNOTHING, {"ZK_ZNOTHING", "Zookeeper (not error) no server responses to process"});
		codeMap.Insert(ZK_ZSESSIONMOVED, {"ZK_ZSESSIONMOVED", "Zookeeper session moved to another server, so operation is ignored"});
		codeMap.Insert(END_OF_STREAM, {"END_OF_STREAM", "End of stream"});
		codeMap.Insert(END_OF_FILE, {"END_OF_FILE", "End of file"});
		codeMap.Insert(OUT_OF_RESERVED_MEMORY, {"OUT_OF_RESERVED_MEMORY", "Out of reserved memory"});
		codeMap.Insert(NOT_OPENED, {"NOT_OPENED", "The object not initialized or opened"});
		codeMap.Insert(SUCCESS_CANCELED, {"SUCCESS_CANCELED", "Operation is canceled"});
		codeMap.Insert(NOT_SUPPORTED, {"NOT_SUPPORTED", "Operation is not supported"});
		codeMap.Insert(NOT_SUPPORTED_FORMAT, {"NOT_SUPPORTED_FORMAT", "Format is not supported"});
		codeMap.Insert(INVALID_FORMAT, {"INVALID_FORMAT", "Format is not valid"});
		codeMap.Insert(INVALID_FILE, {"INVALID_FILE", "Failed to open file"});
		codeMap.Insert(INVALID_FRAME, {"INVALID_FRAME", "Invalid frame"});
		codeMap.Insert(VARIABLE_NOT_FOUND, {"VARIABLE_NOT_FOUND", "Specific variable not found"});
		codeMap.Insert(FUNCTION_NOT_FOUND, {"FUNCTION_NOT_FOUND", "Specific function not found"});
		codeMap.Insert(OBJECT_NOT_FOUND, {"OBJECT_NOT_FOUND", "Specific object not found"});
		codeMap.Insert(INVALID_STREAMID, {"INVALID_STREAMID", "Invalid stream ID"});
		codeMap.Insert(DB_FAILURE, {"DB_FAILURE", "Generic DB failure"});
		codeMap.Insert(SERVICE_NOT_AVAILABLE, {"SERVICE_NOT_AVAILABLE", "Service is not available"});
		codeMap.Insert(INVALID_CHARACTERID, {"INVALID_CHARACTERID", "Invalid character ID"});
		codeMap.Insert(CHARACTER_NOT_SELECTED, {"CHARACTER_NOT_SELECTED", "Character hasn't selected"});
		codeMap.Insert(INVALID_VERSION, {"INVALID_VERSION", "Invalid version"});
		codeMap.Insert(SERVER_INTERNAL_ERROR, {"SERVER_INTERNAL_ERROR", "Server internal error"});
		codeMap.Insert(GENERIC_SERVER_ERROR, {"GENERIC_SERVER_ERROR", "Generic Server error"});
		codeMap.Insert(KEY_NOTFOUND, {"KEY_NOTFOUND", "Specified key not found"});
		codeMap.Insert(INVALID_KEY, {"INVALID_KEY", "Specified key has invalid data"});
		codeMap.Insert(INVALID_PROTOCOL, {"INVALID_PROTOCOL", "Invalid protocol has specified"});
		codeMap.Insert(TOO_BIG_PARAMETER, {"TOO_BIG_PARAMETER", "Too big parameter has assigned"});
		codeMap.Insert(DEPRECATED_FEATURE, {"DEPRECATED_FEATURE", "Deprecated"});
		codeMap.Insert(IN_PROGRESS, {"IN_PROGRESS", "In progress"});
		codeMap.Insert(INVALID_DATA, {"INVALID_DATA", "Invalid data"});
		codeMap.Insert(INVALID_CACHE_DATA, {"INVALID_CACHE_DATA", "Invalid cache data"});

	}//InitializeResultCode 
}//namespace ResultCode 
}//namespace SF 




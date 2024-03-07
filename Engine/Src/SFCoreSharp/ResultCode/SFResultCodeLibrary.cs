﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated file, SF
//
////////////////////////////////////////////////////////////////////////////////

using System;


namespace SF {
	public partial struct ResultCode {

		// Invalid byte sequence. usually caused by invalid data stream 
		public static readonly Result INVALID_BYTE_SEQUENCE =               new Result(unchecked((int)0xE7010000)); 

		// You can not register same name or type component 
		public static readonly Result DUPLICATE_COMPONENT =                 new Result(unchecked((int)0xE7010001)); 

		// Called without initialization. 
		public static readonly Result NOT_INITIALIZED =                     new Result(unchecked((int)0xE7010002)); 

		// The version not available or miss match with system. 
		public static readonly Result VERSION_NOT_AVAIL =                   new Result(unchecked((int)0xE7010003)); 

		// Invalid Cluster Master server 
		public static readonly Result INVALID_CLUSTERMASTER =               new Result(unchecked((int)0xE7010004)); 

		// The version not available or miss match with system. 
		public static readonly Result INVALID_STATE =                       new Result(unchecked((int)0xE7010005)); 

		// Invalid string format. 
		public static readonly Result INVALID_STR_FORMAT =                  new Result(unchecked((int)0xE7010006)); 

		// ServerID is duplicated. 
		public static readonly Result DUPLICATED_SERVERID =                 new Result(unchecked((int)0xE7010007)); 

		// Invalid entity 
		public static readonly Result INVALID_ENTITY =                      new Result(unchecked((int)0xE7010008)); 

		// Invalid duplicated entity 
		public static readonly Result DUPLICATED_ENTITY =                   new Result(unchecked((int)0xE7010009)); 

		// Invalid duplicated entity 
		public static readonly Result DUPLICATED_ENTITYID =                 new Result(unchecked((int)0xE701000A)); 

		// Duplicated Account ID 
		public static readonly Result DUPLICATED_ACCOUNTID =                new Result(unchecked((int)0xE701000B)); 

		// Duplicated Player ID 
		public static readonly Result DUPLICATED_PLAYERID =                 new Result(unchecked((int)0xE701000C)); 

		// Duplicated name 
		public static readonly Result DUPLICATED_NAME =                     new Result(unchecked((int)0xE701000D)); 

		// Duplicated ID 
		public static readonly Result DUPLICATED_ID =                       new Result(unchecked((int)0xE701000E)); 

		// Invalid duplicated entity 
		public static readonly Result INVALID_ACCOUNTID =                   new Result(unchecked((int)0xE701000F)); 

		// Invalid ticket 
		public static readonly Result INVALID_TICKET =                      new Result(unchecked((int)0xE7010010)); 

		// Invalid player ID 
		public static readonly Result INVALID_PLAYERID =                    new Result(unchecked((int)0xE7010011)); 

		// Invalid value 
		public static readonly Result INVALID_VALUE =                       new Result(unchecked((int)0xE7010012)); 

		// Invalid class value 
		public static readonly Result INVALID_CLASS =                       new Result(unchecked((int)0xE7010013)); 

		// Invalid Difficulty 
		public static readonly Result INVALID_DIFFICULTY =                  new Result(unchecked((int)0xE7010014)); 

		// Invalid registration to play 
		public static readonly Result INVALID_REGISTRATION =                new Result(unchecked((int)0xE7010015)); 

		// Invalid Channel ID 
		public static readonly Result INVALID_CHANNELID =                   new Result(unchecked((int)0xE7010016)); 

		// Invalid Zone instance ID 
		public static readonly Result INVALID_INSTANCEID =                  new Result(unchecked((int)0xE7010017)); 

		// Duplicated component 
		public static readonly Result DUPLICATED_COMPONENT =                new Result(unchecked((int)0xE7010018)); 

		// Maximum friend 
		public static readonly Result MAX_FRIEND =                          new Result(unchecked((int)0xE7010019)); 

		// Invalid player count for service 
		public static readonly Result INVALID_PLAYER_COUNT =                new Result(unchecked((int)0xE701001A)); 

		// Invalid player level 
		public static readonly Result INVALID_PLAYER_LEVEL =                new Result(unchecked((int)0xE701001B)); 

		// Invalid player nick 
		public static readonly Result INVALID_PLAYER_NICK =                 new Result(unchecked((int)0xE701001C)); 

		// Invalid Notification ID 
		public static readonly Result INVALID_NOTIFICATIONID =              new Result(unchecked((int)0xE701001D)); 

		// Invalid Ranking range 
		public static readonly Result INVALID_RANKING_RANGE =               new Result(unchecked((int)0xE701001E)); 

		// Target Maximum friend 
		public static readonly Result TARGET_MAX_FRIEND =                   new Result(unchecked((int)0xE701001F)); 

		// Invalid string data. 
		public static readonly Result INVALID_STR_DATA =                    new Result(unchecked((int)0xE7010020)); 

		// Not authorized 
		public static readonly Result NOT_AUTORIZED =                       new Result(unchecked((int)0xE7010021)); 

		// No permition 
		public static readonly Result NO_PERMITION =                        new Result(unchecked((int)0xE7010022)); 

		// No file or directory 
		public static readonly Result NO_FILE_OR_DIR =                      new Result(unchecked((int)0xE7010023)); 

		// No such process 
		public static readonly Result NO_SUCH_PROCESS =                     new Result(unchecked((int)0xE7010024)); 

		// Interrupted system call 
		public static readonly Result INTERRUPTED_SYSCALL =                 new Result(unchecked((int)0xE7010025)); 

		// I/O error 
		public static readonly Result IO_ERROR =                            new Result(unchecked((int)0xE7010026)); 

		// No such device or address 
		public static readonly Result NOT_DEVICE =                          new Result(unchecked((int)0xE7010027)); 

		// Arg list too long 
		public static readonly Result TOO_MANY_ARGLIST =                    new Result(unchecked((int)0xE7010028)); 

		// Exec format error 
		public static readonly Result INVALID_EXEC_FROMAT =                 new Result(unchecked((int)0xE7010029)); 

		// Bad file number 
		public static readonly Result INVALID_FILE_HANDLE =                 new Result(unchecked((int)0xE701002A)); 

		// No child process 
		public static readonly Result NO_CHILD_PROCESS =                    new Result(unchecked((int)0xE701002B)); 

		// Block device required 
		public static readonly Result NOT_BLOCK =                           new Result(unchecked((int)0xE701002C)); 

		// Not exist 
		public static readonly Result NOT_EXIST =                           new Result(unchecked((int)0xE701002D)); 

		// Busy 
		public static readonly Result BUSY =                                new Result(unchecked((int)0xE701002E)); 

		// File exists 
		public static readonly Result FILE_EXISTS =                         new Result(unchecked((int)0xE701002F)); 

		// Cross-device link 
		public static readonly Result CROSS_LINK =                          new Result(unchecked((int)0xE7010030)); 

		// No such device 
		public static readonly Result INVALID_DEVICE =                      new Result(unchecked((int)0xE7010031)); 

		// Not a directory 
		public static readonly Result INVALID_DIRECTORY =                   new Result(unchecked((int)0xE7010032)); 

		// Is a directory 
		public static readonly Result DIRECTORY =                           new Result(unchecked((int)0xE7010033)); 

		// File table overflow 
		public static readonly Result NOT_ENOUGH_FILE_TABLE =               new Result(unchecked((int)0xE7010034)); 

		// Too many open files 
		public static readonly Result TOO_MANY_OPENED_FILE =                new Result(unchecked((int)0xE7010035)); 

		// Not a typewriter 
		public static readonly Result INVALID_TYPEWRITER =                  new Result(unchecked((int)0xE7010036)); 

		// Text file busy 
		public static readonly Result BUSY_FILE =                           new Result(unchecked((int)0xE7010037)); 

		// File too large 
		public static readonly Result TOO_BIG_FILE =                        new Result(unchecked((int)0xE7010038)); 

		// No space left on device 
		public static readonly Result NOT_ENOUGH_SPACE =                    new Result(unchecked((int)0xE7010039)); 

		// Illegal seek 
		public static readonly Result INVALID_SEEK =                        new Result(unchecked((int)0xE701003A)); 

		// Read-only file system 
		public static readonly Result READ_ONLY =                           new Result(unchecked((int)0xE701003B)); 

		// Too many links 
		public static readonly Result TOO_MANY_LINK =                       new Result(unchecked((int)0xE701003C)); 

		// Broken pipe 
		public static readonly Result INVALID_PIPE =                        new Result(unchecked((int)0xE701003D)); 

		// Math argument out of domain of func 
		public static readonly Result INVALID_MATH_DOMAIN =                 new Result(unchecked((int)0xE701003E)); 

		// Math result not representable 
		public static readonly Result INVALID_NUMERIC =                     new Result(unchecked((int)0xE701003F)); 

		// Invalid password 
		public static readonly Result INVALID_PASSWORD =                    new Result(unchecked((int)0xE7010040)); 

		// Target already in friends list 
		public static readonly Result ALREADY_IN_FRIEND =                   new Result(unchecked((int)0xE7010041)); 

		// Thread is wrong, running on wrong thread? 
		public static readonly Result INVALID_THREAD =                      new Result(unchecked((int)0xE7010042)); 

		// Requested object already exist 
		public static readonly Result ALREADY_EXIST =                       new Result(unchecked((int)0xE7010043)); 

		// Network sequence already processed 
		public static readonly Result SUCCESS_IO_PROCESSED_SEQUENCE =       new Result(unchecked((int)0x27010044)); 

		// The version not available or miss match with system. 
		public static readonly Result IO_PROTOCOL_VERSION_MISMATCH =        new Result(unchecked((int)0xE7010045)); 

		// Network is not initialized 
		public static readonly Result IO_NOTINITIALIZED =                   new Result(unchecked((int)0xE7010046)); 

		// The version not available or miss match with system. 
		public static readonly Result IO_INVALID_NETCLASS =                 new Result(unchecked((int)0xE7010047)); 

		// Not enough space in sliding window 
		public static readonly Result IO_NOT_ENOUGH_WINDOWSPACE =           new Result(unchecked((int)0xE7010048)); 

		// Network IO aborted 
		public static readonly Result IO_IO_ABORTED =                       new Result(unchecked((int)0xE7010049)); 

		// Network IO send failed 
		public static readonly Result IO_IO_SEND_FAIL =                     new Result(unchecked((int)0xE701004A)); 

		// Network IO recv failed 
		public static readonly Result IO_IO_RECV_FAIL =                     new Result(unchecked((int)0xE701004B)); 

		// Network send failed 
		public static readonly Result IO_SEND_FAIL =                        new Result(unchecked((int)0xE701004C)); 

		// Network recv failed 
		public static readonly Result IO_RECV_FAIL =                        new Result(unchecked((int)0xE701004D)); 

		// Network Message sequence is invalid 
		public static readonly Result IO_INVALID_SEQUENCE =                 new Result(unchecked((int)0xE701004E)); 

		// Network Message not expected bad packet size 
		public static readonly Result IO_BADPACKET_SIZE =                   new Result(unchecked((int)0xE701004F)); 

		// Network connection closed 
		public static readonly Result IO_CONNECTION_CLOSED =                new Result(unchecked((int)0xE7010050)); 

		// Network connection is never made 
		public static readonly Result IO_NOT_CONNECTED =                    new Result(unchecked((int)0xE7010051)); 

		// Network connection ID is invalid 
		public static readonly Result IO_INVALID_CID =                      new Result(unchecked((int)0xE7010052)); 

		// Network Connection timeout 
		public static readonly Result IO_CONNECTION_TIMEOUT =               new Result(unchecked((int)0xE7010053)); 

		// Network connection is failed 
		public static readonly Result IO_CONNECTION_FAIL =                  new Result(unchecked((int)0xE7010054)); 

		// Too big packet data 
		public static readonly Result IO_BADPACKET_TOOBIG =                 new Result(unchecked((int)0xE7010055)); 

		// Network Message not expected bad packet 
		public static readonly Result IO_BADPACKET_NOTEXPECTED =            new Result(unchecked((int)0xE7010056)); 

		// Checksum value of the message is invalid 
		public static readonly Result IO_INVALID_MESSAGE_CHECKSUM =         new Result(unchecked((int)0xE7010057)); 

		// Message encryption is invalid 
		public static readonly Result IO_INVALID_MESSAGE_ENCRYPTION =       new Result(unchecked((int)0xE7010058)); 

		// Invalid connection state 
		public static readonly Result IO_INVALID_CONNECTION_STATE =         new Result(unchecked((int)0xE7010059)); 

		// Too big sequence id 
		public static readonly Result IO_SEQUENCE_OVERFLOW =                new Result(unchecked((int)0xE701005A)); 

		// A non-blocking socket operation could not be completed immediately. 
		public static readonly Result IO_WOULDBLOCK =                       new Result(unchecked((int)0xE701005B)); 

		// A blocking operation is currently executing. 
		public static readonly Result IO_INPROGRESS =                       new Result(unchecked((int)0xE701005C)); 

		// An operation was attempted on a non-blocking socket that already had an operation in progress. 
		public static readonly Result IO_ALREADY =                          new Result(unchecked((int)0xE701005D)); 

		// An operation was attempted on something that is not a socket. 
		public static readonly Result IO_NOTSOCK =                          new Result(unchecked((int)0xE701005E)); 

		// A required address was omitted from an operation on a socket. 
		public static readonly Result IO_DESTADDRREQ =                      new Result(unchecked((int)0xE701005F)); 

		// A socket operation encountered a dead network. 
		public static readonly Result IO_NETDOWN =                          new Result(unchecked((int)0xE7010060)); 

		// A socket operation was attempted to an unreachable network. 
		public static readonly Result IO_NETUNREACH =                       new Result(unchecked((int)0xE7010061)); 

		// The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. 
		public static readonly Result IO_NETRESET =                         new Result(unchecked((int)0xE7010062)); 

		// An established connection was aborted by the software in your host machine. 
		public static readonly Result IO_CONNABORTED =                      new Result(unchecked((int)0xE7010063)); 

		// An existing connection was forcibly closed by the remote host. 
		public static readonly Result IO_CONNRESET =                        new Result(unchecked((int)0xE7010064)); 

		// An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full. 
		public static readonly Result IO_NOBUFS =                           new Result(unchecked((int)0xE7010065)); 

		// A connect request was made on an already connected socket. 
		public static readonly Result IO_ISCONN =                           new Result(unchecked((int)0xE7010066)); 

		// A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied. 
		public static readonly Result IO_NOTCONN =                          new Result(unchecked((int)0xE7010067)); 

		// A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. 
		public static readonly Result IO_SHUTDOWN =                         new Result(unchecked((int)0xE7010068)); 

		// Too many references to some kernel object. 
		public static readonly Result IO_TOOMANYREFS =                      new Result(unchecked((int)0xE7010069)); 

		// A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond. 
		public static readonly Result IO_TIMEDOUT =                         new Result(unchecked((int)0xE701006A)); 

		// No connection could be made because the target machine actively refused it. 
		public static readonly Result IO_CONNECTION_REFUSSED =              new Result(unchecked((int)0xE701006B)); 

		// Cannot translate name. 
		public static readonly Result IO_LOOP =                             new Result(unchecked((int)0xE701006C)); 

		// Name component or name was too long. 
		public static readonly Result IO_NAMETOOLONG =                      new Result(unchecked((int)0xE701006D)); 

		// A socket operation failed because the destination host was down. 
		public static readonly Result IO_HOSTDOWN =                         new Result(unchecked((int)0xE701006E)); 

		// A socket operation was attempted to an unreachable host. 
		public static readonly Result IO_HOSTUNREACH =                      new Result(unchecked((int)0xE701006F)); 

		// Cannot remove a directory that is not empty. 
		public static readonly Result IO_NOTEMPTY =                         new Result(unchecked((int)0xE7010070)); 

		// A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously. 
		public static readonly Result IO_PROCLIM =                          new Result(unchecked((int)0xE7010071)); 

		// WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable. 
		public static readonly Result IO_SYSNOTREADY =                      new Result(unchecked((int)0xE7010072)); 

		// The Windows Sockets version requested is not supported. 
		public static readonly Result IO_VERNOTSUPPORTED =                  new Result(unchecked((int)0xE7010073)); 

		// Either the application has not called WSAStartup, or WSAStartup failed. 
		public static readonly Result IO_NOTINITIALISED =                   new Result(unchecked((int)0xE7010074)); 

		// Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence. 
		public static readonly Result IO_DISCON =                           new Result(unchecked((int)0xE7010075)); 

		// A system call has failed. 
		public static readonly Result IO_SYSCALLFAILURE =                   new Result(unchecked((int)0xE7010076)); 

		// Host not found. 
		public static readonly Result IO_HOST_NOT_FOUND =                   new Result(unchecked((int)0xE7010077)); 

		// Try again 
		public static readonly Result IO_TRY_AGAIN =                        new Result(unchecked((int)0xE7010078)); 

		// IOPending 
		public static readonly Result IO_IO_PENDING =                       new Result(unchecked((int)0xE7010079)); 

		// No such host is known securely. 
		public static readonly Result IO_SECURE_HOST_NOT_FOUND =            new Result(unchecked((int)0xE701007A)); 

		// Protocol error 
		public static readonly Result IO_PROTO =                            new Result(unchecked((int)0xE701007B)); 

		// Protocol wrong type for socket. 
		public static readonly Result IO_PROTOTYPE =                        new Result(unchecked((int)0xE701007C)); 

		// Protocol not available 
		public static readonly Result IO_NOPROTOOPT =                       new Result(unchecked((int)0xE701007D)); 

		// Machine is not on the network 
		public static readonly Result IO_NONET =                            new Result(unchecked((int)0xE701007E)); 

		// Operation not supported on socket 
		public static readonly Result IO_OPNOTSUPP =                        new Result(unchecked((int)0xE701007F)); 

		// An invalid value was provided for the ai_flags member of the pHints parameter. 
		public static readonly Result IO_BADFLAGS =                         new Result(unchecked((int)0xE7010080)); 

		// Bad network family 
		public static readonly Result IO_FAMILY =                           new Result(unchecked((int)0xE7010081)); 

		// The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter. 
		public static readonly Result IO_INVALID_SERVICE =                  new Result(unchecked((int)0xE7010082)); 

		// Invalid network address 
		public static readonly Result IO_INVALID_ADDRESS =                  new Result(unchecked((int)0xE7010083)); 

		// Address in use 
		public static readonly Result IO_ADDRINUSE =                        new Result(unchecked((int)0xE7010084)); 

		// Network Message not expected packet data 
		public static readonly Result IO_BADPACKET =                        new Result(unchecked((int)0xE7010085)); 

		// Disconnected 
		public static readonly Result IO_DISCONNECTED =                     new Result(unchecked((int)0xE7010086)); 

		// Canceled 
		public static readonly Result IO_CANCELED =                         new Result(unchecked((int)0xE7010087)); 

		// Zookeeper System and server-side errors. 
		public static readonly Result ZK_SYSTEM =                           new Result(unchecked((int)0xE7010088)); 

		// Zookeeper  A runtime inconsistency was found 
		public static readonly Result ZK_ZRUNTIMEINCONSISTENCY =            new Result(unchecked((int)0xE7010089)); 

		// Zookeeper A data inconsistency was found 
		public static readonly Result ZK_ZDATAINCONSISTENCY =               new Result(unchecked((int)0xE701008A)); 

		// Zookeeper Connection to the server has been lost 
		public static readonly Result ZK_ZCONNECTIONLOSS =                  new Result(unchecked((int)0xE701008B)); 

		// Zookeeper Error while marshalling or unmarshalling data 
		public static readonly Result ZK_ZMARSHALLINGERROR =                new Result(unchecked((int)0xE701008C)); 

		// Zookeeper Operation is unimplemented 
		public static readonly Result ZK_ZUNIMPLEMENTED =                   new Result(unchecked((int)0xE701008D)); 

		// Zookeeper Operation timeout 
		public static readonly Result ZK_ZOPERATIONTIMEOUT =                new Result(unchecked((int)0xE701008E)); 

		// Zookeeper Invalid arguments 
		public static readonly Result ZK_ZBADARGUMENTS =                    new Result(unchecked((int)0xE701008F)); 

		// Zookeeper Invliad zhandle state 
		public static readonly Result ZK_ZINVALIDSTATE =                    new Result(unchecked((int)0xE7010090)); 

		// Zookeeper API errors. 
		public static readonly Result ZK_ZAPIERROR =                        new Result(unchecked((int)0xE7010091)); 

		// Zookeeper Node does not exist 
		public static readonly Result ZK_ZNONODE =                          new Result(unchecked((int)0xE7010092)); 

		// Zookeeper Not authenticated 
		public static readonly Result ZK_ZNOAUTH =                          new Result(unchecked((int)0xE7010093)); 

		// Zookeeper Version conflict 
		public static readonly Result ZK_ZBADVERSION =                      new Result(unchecked((int)0xE7010094)); 

		// Zookeeper Ephemeral nodes may not have children 
		public static readonly Result ZK_ZNOCHILDRENFOREPHEMERALS =         new Result(unchecked((int)0xE7010095)); 

		// Zookeeper The node already exists 
		public static readonly Result ZK_ZNODEEXISTS =                      new Result(unchecked((int)0xE7010096)); 

		// Zookeeper The node has children 
		public static readonly Result ZK_ZNOTEMPTY =                        new Result(unchecked((int)0xE7010097)); 

		// Zookeeper The session has been expired by the server 
		public static readonly Result ZK_ZSESSIONEXPIRED =                  new Result(unchecked((int)0xE7010098)); 

		// Zookeeper Invalid callback specified 
		public static readonly Result ZK_ZINVALIDCALLBACK =                 new Result(unchecked((int)0xE7010099)); 

		// Zookeeper Invalid ACL specified 
		public static readonly Result ZK_ZINVALIDACL =                      new Result(unchecked((int)0xE701009A)); 

		// Zookeeper Client authentication failed 
		public static readonly Result ZK_ZAUTHFAILED =                      new Result(unchecked((int)0xE701009B)); 

		// Zookeeper Zookeeper is closing 
		public static readonly Result ZK_ZCLOSING =                         new Result(unchecked((int)0xE701009C)); 

		// Zookeeper (not error) no server responses to process 
		public static readonly Result ZK_ZNOTHING =                         new Result(unchecked((int)0xE701009D)); 

		// Zookeeper session moved to another server, so operation is ignored 
		public static readonly Result ZK_ZSESSIONMOVED =                    new Result(unchecked((int)0xE701009E)); 

		// End of stream 
		public static readonly Result END_OF_STREAM =                       new Result(unchecked((int)0xE701009F)); 

		// End of file 
		public static readonly Result END_OF_FILE =                         new Result(unchecked((int)0xE70100A0)); 

		// Out of reserved memory 
		public static readonly Result OUT_OF_RESERVED_MEMORY =              new Result(unchecked((int)0xE70100A1)); 

		// The object not initialized or opened 
		public static readonly Result NOT_OPENED =                          new Result(unchecked((int)0xE70100A2)); 

		// Operation is canceled 
		public static readonly Result SUCCESS_CANCELED =                    new Result(unchecked((int)0x270100A3)); 

		// stream doesn't exist 
		public static readonly Result STREAM_NOT_EXIST =                    new Result(unchecked((int)0xE70100A4)); 

		// Operation is not supported 
		public static readonly Result NOT_SUPPORTED =                       new Result(unchecked((int)0xE70100A5)); 

		// Format is not supported 
		public static readonly Result NOT_SUPPORTED_FORMAT =                new Result(unchecked((int)0xE70100A6)); 

		// Format is not valid 
		public static readonly Result INVALID_FORMAT =                      new Result(unchecked((int)0xE70100A7)); 

		// Failed to open file 
		public static readonly Result INVALID_FILE =                        new Result(unchecked((int)0xE70100A8)); 

		// Invalid frame 
		public static readonly Result INVALID_FRAME =                       new Result(unchecked((int)0xE70100A9)); 

		// Specific variable not found 
		public static readonly Result VARIABLE_NOT_FOUND =                  new Result(unchecked((int)0xE70100AA)); 

		// Specific function not found 
		public static readonly Result FUNCTION_NOT_FOUND =                  new Result(unchecked((int)0xE70100AB)); 

		// Specific object not found 
		public static readonly Result OBJECT_NOT_FOUND =                    new Result(unchecked((int)0xE70100AC)); 

		// Invalid stream ID 
		public static readonly Result INVALID_STREAMID =                    new Result(unchecked((int)0xE70100AD)); 

		// Generic DB failure 
		public static readonly Result DB_FAILURE =                          new Result(unchecked((int)0xE70100AE)); 

		// Service is not available 
		public static readonly Result SERVICE_NOT_AVAILABLE =               new Result(unchecked((int)0xE70100AF)); 

		// Invalid character ID 
		public static readonly Result INVALID_CHARACTERID =                 new Result(unchecked((int)0xE70100B0)); 

		// Character hasn't selected 
		public static readonly Result CHARACTER_NOT_SELECTED =              new Result(unchecked((int)0xE70100B1)); 

		// Invalid version 
		public static readonly Result INVALID_VERSION =                     new Result(unchecked((int)0xE70100B2)); 

		// Server internal error 
		public static readonly Result SERVER_INTERNAL_ERROR =               new Result(unchecked((int)0xE70100B3)); 

		// Generic Server error 
		public static readonly Result GENERIC_SERVER_ERROR =                new Result(unchecked((int)0xE70100B4)); 

		// Specified key not found 
		public static readonly Result KEY_NOTFOUND =                        new Result(unchecked((int)0xE70100B5)); 

		// Specified key has invalid data 
		public static readonly Result INVALID_KEY =                         new Result(unchecked((int)0xE70100B6)); 

		// Invalid protocol has specified 
		public static readonly Result INVALID_PROTOCOL =                    new Result(unchecked((int)0xE70100B7)); 

		// Too big parameter has assigned 
		public static readonly Result TOO_BIG_PARAMETER =                   new Result(unchecked((int)0xE70100B8)); 

		// Deprecated 
		public static readonly Result DEPRECATED_FEATURE =                  new Result(unchecked((int)0xE70100B9)); 

		// In progress 
		public static readonly Result IN_PROGRESS =                         new Result(unchecked((int)0xE70100BA)); 

		// Invalid data 
		public static readonly Result INVALID_DATA =                        new Result(unchecked((int)0xE70100BB)); 

		// Invalid response data 
		public static readonly Result INVALID_RESPONSE_DATA =               new Result(unchecked((int)0xE70100BC)); 

		// Invalid cache data 
		public static readonly Result INVALID_CACHE_DATA =                  new Result(unchecked((int)0xE70100BD)); 

		// Invalid schema data 
		public static readonly Result INVALID_SCHEMA =                      new Result(unchecked((int)0xE70100BE)); 

		// Invalid type 
		public static readonly Result INVALID_TYPE =                        new Result(unchecked((int)0xE70100BF)); 

		// Maximum packet 
		public static readonly Result MAX_PACKET =                          new Result(unchecked((int)0xE70100C0)); 

		// The protocol is not supported. 
		public static readonly Result HTTP_UNSUPPORTED_PROTOCOL =           new Result(unchecked((int)0xE70100C1)); 

		// CURL initialization is failed. 
		public static readonly Result HTTP_FAILED_INIT =                    new Result(unchecked((int)0xE70100C2)); 

		// Invalid URL format. 
		public static readonly Result HTTP_URL_MALFORMAT =                  new Result(unchecked((int)0xE70100C3)); 

		// Not a build-in feature. 
		public static readonly Result HTTP_NOT_BUILT_IN =                   new Result(unchecked((int)0xE70100C4)); 

		// Failed to resolve URL. 
		public static readonly Result HTTP_COULDNT_RESOLVE_PROXY =          new Result(unchecked((int)0xE70100C5)); 

		// Failed to resolve URL. 
		public static readonly Result HTTP_COULDNT_RESOLVE_HOST =           new Result(unchecked((int)0xE70100C6)); 

		// Connection is failed 
		public static readonly Result HTTP_COULDNT_CONNECT =                new Result(unchecked((int)0xE70100C7)); 

		// HTTP Post can't be done. 
		public static readonly Result HTTP_HTTP_POST_ERROR =                new Result(unchecked((int)0xE70100C8)); 

		// Not supported SSL type. 
		public static readonly Result HTTP_SSL_ENGINE_NOTFOUND =            new Result(unchecked((int)0xE70100C9)); 

		// Not supported SSL type. 
		public static readonly Result HTTP_SSL_ENGINE_SETFAILED =           new Result(unchecked((int)0xE70100CA)); 

		// Network send failed 
		public static readonly Result HTTP_SEND_ERROR =                     new Result(unchecked((int)0xE70100CB)); 

		// Network receive failed 
		public static readonly Result HTTP_RECV_ERROR =                     new Result(unchecked((int)0xE70100CC)); 

		// Invalid SSL setting. 
		public static readonly Result HTTP_USE_SSL_FAILED =                 new Result(unchecked((int)0xE70100CD)); 

		// No Connection is available now. 
		public static readonly Result HTTP_NO_CONNECTION_AVAILABLE =        new Result(unchecked((int)0xE70100CE)); 

		// SSL error 
		public static readonly Result HTTP_SSL_CONNECT_ERROR =              new Result(unchecked((int)0xE70100CF)); 

		// please call curl_multi_perform() or curl_multi_socket*() soon 
		public static readonly Result HTTP_CALL_MULTI_PERFORM =             new Result(unchecked((int)0xE70100D0)); 

		// the passed-in handle is not a valid CURLM handle 
		public static readonly Result HTTP_BAD_HANDLE =                     new Result(unchecked((int)0xE70100D1)); 

		// an easy handle was not good/valid 
		public static readonly Result HTTP_BAD_EASY_HANDLE =                new Result(unchecked((int)0xE70100D2)); 

		// this is a libcurl bug 
		public static readonly Result HTTP_INTERNAL_ERROR =                 new Result(unchecked((int)0xE70100D3)); 

		// the passed in socket argument did not match 
		public static readonly Result HTTP_BAD_SOCKET =                     new Result(unchecked((int)0xE70100D4)); 

		// curl_multi_setopt() with unsupported option 
		public static readonly Result HTTP_UNKNOWN_OPTION =                 new Result(unchecked((int)0xE70100D5)); 

		// an easy handle already added to a multi handle was attempted to get added - again 
		public static readonly Result HTTP_ADDED_ALREADY =                  new Result(unchecked((int)0xE70100D6)); 

		// an api function was called from inside a callback 
		public static readonly Result HTTP_RECURSIVE_API_CALL =             new Result(unchecked((int)0xE70100D7)); 

		// wakeup is unavailable or failed 
		public static readonly Result HTTP_WAKEUP_FAILURE =                 new Result(unchecked((int)0xE70100D8)); 

		// function called with a bad parameter 
		public static readonly Result HTTP_BAD_FUNCTION_ARGUMENT =          new Result(unchecked((int)0xE70100D9)); 

		// ? 
		public static readonly Result HTTP_ABORTED_BY_CALLBACK =            new Result(unchecked((int)0xE70100DA)); 

		// ? 
		public static readonly Result HTTP_UNRECOVERABLE_POLL =             new Result(unchecked((int)0xE70100DB)); 

		// Canceled  
		public static readonly Result HTTP_CANCELED =                       new Result(unchecked((int)0xE70100DC)); 

	}
}




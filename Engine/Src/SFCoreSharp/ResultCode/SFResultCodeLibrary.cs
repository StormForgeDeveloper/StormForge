﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated file, SF
//
////////////////////////////////////////////////////////////////////////////////

using System;


namespace SF {
	public partial struct ResultCode {

		// Invalid byte sequence. usually casued by invalid data stream 
		public const int INVALID_BYTE_SEQUENCE =                            unchecked((int)0xE7010000); 

		// You can not register same name or type component 
		public const int DUPLICATE_COMPONENT =                              unchecked((int)0xE7010001); 

		// Called without initialization. 
		public const int NOT_INITIALIZED =                                  unchecked((int)0xE7010002); 

		// The version not available or miss match with system. 
		public const int VERSION_NOT_AVAIL =                                unchecked((int)0xE7010003); 

		// Invalid Cluster Master server 
		public const int INVALID_CLUSTERMASTER =                            unchecked((int)0xE7010004); 

		// The version not available or miss match with system. 
		public const int INVALID_STATE =                                    unchecked((int)0xE7010005); 

		// Invalid string format. 
		public const int INVALID_STR_FORMAT =                               unchecked((int)0xE7010006); 

		// ServerID is duplicated. 
		public const int DUPLICATED_SERVERID =                              unchecked((int)0xE7010007); 

		// Invalid entity 
		public const int INVALID_ENTITY =                                   unchecked((int)0xE7010008); 

		// Invalid duplicated entity 
		public const int DUPLICATED_ENTITY =                                unchecked((int)0xE7010009); 

		// Invalid duplicated entity 
		public const int DUPLICATED_ENTITYID =                              unchecked((int)0xE701000A); 

		// Duplicated Account ID 
		public const int DUPLICATED_ACCOUNTID =                             unchecked((int)0xE701000B); 

		// Duplicated Player ID 
		public const int DUPLICATED_PLAYERID =                              unchecked((int)0xE701000C); 

		// Duplicated name 
		public const int DUPLICATED_NAME =                                  unchecked((int)0xE701000D); 

		// Duplicated ID 
		public const int DUPLICATED_ID =                                    unchecked((int)0xE701000E); 

		// Invalid duplicated entity 
		public const int INVALID_ACCOUNTID =                                unchecked((int)0xE701000F); 

		// Invalid ticket 
		public const int INVALID_TICKET =                                   unchecked((int)0xE7010010); 

		// Invalid player ID 
		public const int INVALID_PLAYERID =                                 unchecked((int)0xE7010011); 

		// Invalid value 
		public const int INVALID_VALUE =                                    unchecked((int)0xE7010012); 

		// Invalid class value 
		public const int INVALID_CLASS =                                    unchecked((int)0xE7010013); 

		// Invalid Difficulty 
		public const int INVALID_DIFFICULTY =                               unchecked((int)0xE7010014); 

		// Invalid registration to play 
		public const int INVALID_REGISTRATION =                             unchecked((int)0xE7010015); 

		// Invalid Channel ID 
		public const int INVALID_CHANNELID =                                unchecked((int)0xE7010016); 

		// Invalid Zone instance ID 
		public const int INVALID_INSTANCEID =                               unchecked((int)0xE7010017); 

		// Duplicated component 
		public const int DUPLICATED_COMPONENT =                             unchecked((int)0xE7010018); 

		// Maximum friend 
		public const int MAX_FRIEND =                                       unchecked((int)0xE7010019); 

		// Invalid player count for service 
		public const int INVALID_PLAYER_COUNT =                             unchecked((int)0xE701001A); 

		// Invalid player level 
		public const int INVALID_PLAYER_LEVEL =                             unchecked((int)0xE701001B); 

		// Invalid player nick 
		public const int INVALID_PLAYER_NICK =                              unchecked((int)0xE701001C); 

		// Invalid Notification ID 
		public const int INVALID_NOTIFICATIONID =                           unchecked((int)0xE701001D); 

		// Invalid Ranking range 
		public const int INVALID_RANKING_RANGE =                            unchecked((int)0xE701001E); 

		// Target Maximum friend 
		public const int TARGET_MAX_FRIEND =                                unchecked((int)0xE701001F); 

		// Invalid string data. 
		public const int INVALID_STR_DATA =                                 unchecked((int)0xE7010020); 

		// Not authorized 
		public const int NOT_AUTORIZED =                                    unchecked((int)0xE7010021); 

		// No permition 
		public const int NO_PERMITION =                                     unchecked((int)0xE7010022); 

		// No file or directory 
		public const int NO_FILE_OR_DIR =                                   unchecked((int)0xE7010023); 

		// No such process 
		public const int NO_SUCH_PROCESS =                                  unchecked((int)0xE7010024); 

		// Interrupted system call 
		public const int INTERRUPTED_SYSCALL =                              unchecked((int)0xE7010025); 

		// I/O error 
		public const int IO_ERROR =                                         unchecked((int)0xE7010026); 

		// No such device or address 
		public const int NOT_DEVICE =                                       unchecked((int)0xE7010027); 

		// Arg list too long 
		public const int TOO_MANY_ARGLIST =                                 unchecked((int)0xE7010028); 

		// Exec format error 
		public const int INVALID_EXEC_FROMAT =                              unchecked((int)0xE7010029); 

		// Bad file number 
		public const int INVALID_FILE_HANDLE =                              unchecked((int)0xE701002A); 

		// No child process 
		public const int NO_CHILD_PROCESS =                                 unchecked((int)0xE701002B); 

		// Block device required 
		public const int NOT_BLOCK =                                        unchecked((int)0xE701002C); 

		// Not exist 
		public const int NOT_EXIST =                                        unchecked((int)0xE701002D); 

		// Busy 
		public const int BUSY =                                             unchecked((int)0xE701002E); 

		// File exists 
		public const int FILE_EXISTS =                                      unchecked((int)0xE701002F); 

		// Cross-device link 
		public const int CROSS_LINK =                                       unchecked((int)0xE7010030); 

		// No such device 
		public const int INVALID_DEVICE =                                   unchecked((int)0xE7010031); 

		// Not a directory 
		public const int INVALID_DIRECTORY =                                unchecked((int)0xE7010032); 

		// Is a directory 
		public const int DIRECTORY =                                        unchecked((int)0xE7010033); 

		// File table overflow 
		public const int NOT_ENOUGH_FILE_TABLE =                            unchecked((int)0xE7010034); 

		// Too many open files 
		public const int TOO_MANY_OPENED_FILE =                             unchecked((int)0xE7010035); 

		// Not a typewriter 
		public const int INVALID_TYPEWRITER =                               unchecked((int)0xE7010036); 

		// Text file busy 
		public const int BUSY_FILE =                                        unchecked((int)0xE7010037); 

		// File too large 
		public const int TOO_BIG_FILE =                                     unchecked((int)0xE7010038); 

		// No space left on device 
		public const int NOT_ENOUGH_SPACE =                                 unchecked((int)0xE7010039); 

		// Illegal seek 
		public const int INVALID_SEEK =                                     unchecked((int)0xE701003A); 

		// Read-only file system 
		public const int READ_ONLY =                                        unchecked((int)0xE701003B); 

		// Too many links 
		public const int TOO_MANY_LINK =                                    unchecked((int)0xE701003C); 

		// Broken pipe 
		public const int INVALID_PIPE =                                     unchecked((int)0xE701003D); 

		// Math argument out of domain of func 
		public const int INVALID_MATH_DOMAIN =                              unchecked((int)0xE701003E); 

		// Math result not representable 
		public const int INVALID_NUMERIC =                                  unchecked((int)0xE701003F); 

		// Invalid password 
		public const int INVALID_PASSWORD =                                 unchecked((int)0xE7010040); 

		// Target already in friends list 
		public const int ALREADY_IN_FRIEND =                                unchecked((int)0xE7010041); 

		// Thread is wrong, running on wrong thread? 
		public const int INVALID_THREAD =                                   unchecked((int)0xE7010042); 

		// Requested object already exist 
		public const int ALREADY_EXIST =                                    unchecked((int)0xE7010043); 

		// Network sequence already processed 
		public const int SUCCESS_IO_PROCESSED_SEQUENCE =                    unchecked((int)0x27010044); 

		// The version not available or miss match with system. 
		public const int IO_PROTOCOL_VERSION_MISMATCH =                     unchecked((int)0xE7010045); 

		// Network is not initialized 
		public const int IO_NOTINITIALIZED =                                unchecked((int)0xE7010046); 

		// The version not available or miss match with system. 
		public const int IO_INVALID_NETCLASS =                              unchecked((int)0xE7010047); 

		// Not enough space in sliding window 
		public const int IO_NOT_ENOUGH_WINDOWSPACE =                        unchecked((int)0xE7010048); 

		// Network IO aborted 
		public const int IO_IO_ABORTED =                                    unchecked((int)0xE7010049); 

		// Network IO send failed 
		public const int IO_IO_SEND_FAIL =                                  unchecked((int)0xE701004A); 

		// Network IO recv failed 
		public const int IO_IO_RECV_FAIL =                                  unchecked((int)0xE701004B); 

		// Network send failed 
		public const int IO_SEND_FAIL =                                     unchecked((int)0xE701004C); 

		// Network recv failed 
		public const int IO_RECV_FAIL =                                     unchecked((int)0xE701004D); 

		// Network Message sequence is invalid 
		public const int IO_INVALID_SEQUENCE =                              unchecked((int)0xE701004E); 

		// Network Message not expected bad packet size 
		public const int IO_BADPACKET_SIZE =                                unchecked((int)0xE701004F); 

		// Network connection closed 
		public const int IO_CONNECTION_CLOSED =                             unchecked((int)0xE7010050); 

		// Network connection is never made 
		public const int IO_NOT_CONNECTED =                                 unchecked((int)0xE7010051); 

		// Network connection ID is invalid 
		public const int IO_INVALID_CID =                                   unchecked((int)0xE7010052); 

		// Network Connection timeout 
		public const int IO_CONNECTION_TIMEOUT =                            unchecked((int)0xE7010053); 

		// Network connection is failed 
		public const int IO_CONNECTION_FAIL =                               unchecked((int)0xE7010054); 

		// Too big packet data 
		public const int IO_BADPACKET_TOOBIG =                              unchecked((int)0xE7010055); 

		// Network Message not expected bad packet 
		public const int IO_BADPACKET_NOTEXPECTED =                         unchecked((int)0xE7010056); 

		// Checksum value of the message is invalid 
		public const int IO_INVALID_MESSAGE_CHECKSUM =                      unchecked((int)0xE7010057); 

		// Message encryption is invalid 
		public const int IO_INVALID_MESSAGE_ENCRYPTION =                    unchecked((int)0xE7010058); 

		// Invalid connection state 
		public const int IO_INVALID_CONNECTION_STATE =                      unchecked((int)0xE7010059); 

		// Too big sequence id 
		public const int IO_SEQUENCE_OVERFLOW =                             unchecked((int)0xE701005A); 

		// A non-blocking socket operation could not be completed immediately. 
		public const int IO_WOULDBLOCK =                                    unchecked((int)0xE701005B); 

		// A blocking operation is currently executing. 
		public const int IO_INPROGRESS =                                    unchecked((int)0xE701005C); 

		// An operation was attempted on a non-blocking socket that already had an operation in progress. 
		public const int IO_ALREADY =                                       unchecked((int)0xE701005D); 

		// An operation was attempted on something that is not a socket. 
		public const int IO_NOTSOCK =                                       unchecked((int)0xE701005E); 

		// A required address was omitted from an operation on a socket. 
		public const int IO_DESTADDRREQ =                                   unchecked((int)0xE701005F); 

		// A socket operation encountered a dead network. 
		public const int IO_NETDOWN =                                       unchecked((int)0xE7010060); 

		// A socket operation was attempted to an unreachable network. 
		public const int IO_NETUNREACH =                                    unchecked((int)0xE7010061); 

		// The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. 
		public const int IO_NETRESET =                                      unchecked((int)0xE7010062); 

		// An established connection was aborted by the software in your host machine. 
		public const int IO_CONNABORTED =                                   unchecked((int)0xE7010063); 

		// An existing connection was forcibly closed by the remote host. 
		public const int IO_CONNRESET =                                     unchecked((int)0xE7010064); 

		// An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full. 
		public const int IO_NOBUFS =                                        unchecked((int)0xE7010065); 

		// A connect request was made on an already connected socket. 
		public const int IO_ISCONN =                                        unchecked((int)0xE7010066); 

		// A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied. 
		public const int IO_NOTCONN =                                       unchecked((int)0xE7010067); 

		// A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. 
		public const int IO_SHUTDOWN =                                      unchecked((int)0xE7010068); 

		// Too many references to some kernel object. 
		public const int IO_TOOMANYREFS =                                   unchecked((int)0xE7010069); 

		// A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond. 
		public const int IO_TIMEDOUT =                                      unchecked((int)0xE701006A); 

		// No connection could be made because the target machine actively refused it. 
		public const int IO_CONNECTION_REFUSSED =                           unchecked((int)0xE701006B); 

		// Cannot translate name. 
		public const int IO_LOOP =                                          unchecked((int)0xE701006C); 

		// Name component or name was too long. 
		public const int IO_NAMETOOLONG =                                   unchecked((int)0xE701006D); 

		// A socket operation failed because the destination host was down. 
		public const int IO_HOSTDOWN =                                      unchecked((int)0xE701006E); 

		// A socket operation was attempted to an unreachable host. 
		public const int IO_HOSTUNREACH =                                   unchecked((int)0xE701006F); 

		// Cannot remove a directory that is not empty. 
		public const int IO_NOTEMPTY =                                      unchecked((int)0xE7010070); 

		// A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously. 
		public const int IO_PROCLIM =                                       unchecked((int)0xE7010071); 

		// WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable. 
		public const int IO_SYSNOTREADY =                                   unchecked((int)0xE7010072); 

		// The Windows Sockets version requested is not supported. 
		public const int IO_VERNOTSUPPORTED =                               unchecked((int)0xE7010073); 

		// Either the application has not called WSAStartup, or WSAStartup failed. 
		public const int IO_NOTINITIALISED =                                unchecked((int)0xE7010074); 

		// Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence. 
		public const int IO_DISCON =                                        unchecked((int)0xE7010075); 

		// A system call has failed. 
		public const int IO_SYSCALLFAILURE =                                unchecked((int)0xE7010076); 

		// Host not found. 
		public const int IO_HOST_NOT_FOUND =                                unchecked((int)0xE7010077); 

		// Try again 
		public const int IO_TRY_AGAIN =                                     unchecked((int)0xE7010078); 

		// IOPending 
		public const int IO_IO_PENDING =                                    unchecked((int)0xE7010079); 

		// No such host is known securely. 
		public const int IO_SECURE_HOST_NOT_FOUND =                         unchecked((int)0xE701007A); 

		// Protocol error 
		public const int IO_PROTO =                                         unchecked((int)0xE701007B); 

		// Protocol wrong type for socket. 
		public const int IO_PROTOTYPE =                                     unchecked((int)0xE701007C); 

		// Protocol not available 
		public const int IO_NOPROTOOPT =                                    unchecked((int)0xE701007D); 

		// Machine is not on the network 
		public const int IO_NONET =                                         unchecked((int)0xE701007E); 

		// Operation not supported on socket 
		public const int IO_OPNOTSUPP =                                     unchecked((int)0xE701007F); 

		// An invalid value was provided for the ai_flags member of the pHints parameter. 
		public const int IO_BADFLAGS =                                      unchecked((int)0xE7010080); 

		// Bad network family 
		public const int IO_FAMILY =                                        unchecked((int)0xE7010081); 

		// The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter. 
		public const int IO_INVALID_SERVICE =                               unchecked((int)0xE7010082); 

		// Invalid network address 
		public const int IO_INVALID_ADDRESS =                               unchecked((int)0xE7010083); 

		// Address in use 
		public const int IO_ADDRINUSE =                                     unchecked((int)0xE7010084); 

		// Network Message not expected packet data 
		public const int IO_BADPACKET =                                     unchecked((int)0xE7010085); 

		// Disconnected 
		public const int IO_DISCONNECTED =                                  unchecked((int)0xE7010086); 

		// Canceled 
		public const int IO_CANCELED =                                      unchecked((int)0xE7010087); 

		// Zookeeper System and server-side errors. 
		public const int ZK_SYSTEM =                                        unchecked((int)0xE7010088); 

		// Zookeeper  A runtime inconsistency was found 
		public const int ZK_ZRUNTIMEINCONSISTENCY =                         unchecked((int)0xE7010089); 

		// Zookeeper A data inconsistency was found 
		public const int ZK_ZDATAINCONSISTENCY =                            unchecked((int)0xE701008A); 

		// Zookeeper Connection to the server has been lost 
		public const int ZK_ZCONNECTIONLOSS =                               unchecked((int)0xE701008B); 

		// Zookeeper Error while marshalling or unmarshalling data 
		public const int ZK_ZMARSHALLINGERROR =                             unchecked((int)0xE701008C); 

		// Zookeeper Operation is unimplemented 
		public const int ZK_ZUNIMPLEMENTED =                                unchecked((int)0xE701008D); 

		// Zookeeper Operation timeout 
		public const int ZK_ZOPERATIONTIMEOUT =                             unchecked((int)0xE701008E); 

		// Zookeeper Invalid arguments 
		public const int ZK_ZBADARGUMENTS =                                 unchecked((int)0xE701008F); 

		// Zookeeper Invliad zhandle state 
		public const int ZK_ZINVALIDSTATE =                                 unchecked((int)0xE7010090); 

		// Zookeeper API errors. 
		public const int ZK_ZAPIERROR =                                     unchecked((int)0xE7010091); 

		// Zookeeper Node does not exist 
		public const int ZK_ZNONODE =                                       unchecked((int)0xE7010092); 

		// Zookeeper Not authenticated 
		public const int ZK_ZNOAUTH =                                       unchecked((int)0xE7010093); 

		// Zookeeper Version conflict 
		public const int ZK_ZBADVERSION =                                   unchecked((int)0xE7010094); 

		// Zookeeper Ephemeral nodes may not have children 
		public const int ZK_ZNOCHILDRENFOREPHEMERALS =                      unchecked((int)0xE7010095); 

		// Zookeeper The node already exists 
		public const int ZK_ZNODEEXISTS =                                   unchecked((int)0xE7010096); 

		// Zookeeper The node has children 
		public const int ZK_ZNOTEMPTY =                                     unchecked((int)0xE7010097); 

		// Zookeeper The session has been expired by the server 
		public const int ZK_ZSESSIONEXPIRED =                               unchecked((int)0xE7010098); 

		// Zookeeper Invalid callback specified 
		public const int ZK_ZINVALIDCALLBACK =                              unchecked((int)0xE7010099); 

		// Zookeeper Invalid ACL specified 
		public const int ZK_ZINVALIDACL =                                   unchecked((int)0xE701009A); 

		// Zookeeper Client authentication failed 
		public const int ZK_ZAUTHFAILED =                                   unchecked((int)0xE701009B); 

		// Zookeeper Zookeeper is closing 
		public const int ZK_ZCLOSING =                                      unchecked((int)0xE701009C); 

		// Zookeeper (not error) no server responses to process 
		public const int ZK_ZNOTHING =                                      unchecked((int)0xE701009D); 

		// Zookeeper session moved to another server, so operation is ignored 
		public const int ZK_ZSESSIONMOVED =                                 unchecked((int)0xE701009E); 

		// End of stream 
		public const int END_OF_STREAM =                                    unchecked((int)0xE701009F); 

		// End of file 
		public const int END_OF_FILE =                                      unchecked((int)0xE70100A0); 

		// Out of reserved memory 
		public const int OUT_OF_RESERVED_MEMORY =                           unchecked((int)0xE70100A1); 

		// The object not initialized or opened 
		public const int NOT_OPENED =                                       unchecked((int)0xE70100A2); 

		// Operation is canceled 
		public const int SUCCESS_CANCELED =                                 unchecked((int)0x270100A3); 

		// Operation is not supported 
		public const int NOT_SUPPORTED =                                    unchecked((int)0xE70100A4); 

		// Format is not supported 
		public const int NOT_SUPPORTED_FORMAT =                             unchecked((int)0xE70100A5); 

		// Format is not valid 
		public const int INVALID_FORMAT =                                   unchecked((int)0xE70100A6); 

		// Failed to open file 
		public const int INVALID_FILE =                                     unchecked((int)0xE70100A7); 

		// Invalid frame 
		public const int INVALID_FRAME =                                    unchecked((int)0xE70100A8); 

		// Specific variable not found 
		public const int VARIABLE_NOT_FOUND =                               unchecked((int)0xE70100A9); 

		// Specific function not found 
		public const int FUNCTION_NOT_FOUND =                               unchecked((int)0xE70100AA); 

		// Specific object not found 
		public const int OBJECT_NOT_FOUND =                                 unchecked((int)0xE70100AB); 

		// Invalid stream ID 
		public const int INVALID_STREAMID =                                 unchecked((int)0xE70100AC); 

		// Generic DB failure 
		public const int DB_FAILURE =                                       unchecked((int)0xE70100AD); 

		// Service is not available 
		public const int SERVICE_NOT_AVAILABLE =                            unchecked((int)0xE70100AE); 

		// Map object is already in use 
		public const int MAPOBJECT_ALREADY_IN_USE =                         unchecked((int)0xE70100AF); 

		// Map object is not in use 
		public const int MAPOBJECT_NOT_IN_USE =                             unchecked((int)0xE70100B0); 

		// Map object is already in use 
		public const int MAPOBJECT_NOT_FOUND =                              unchecked((int)0xE70100B1); 

		// Map object is not occupied by the player 
		public const int MAPOBJECT_NOT_OCCUPIED_BY_PLAYER =                 unchecked((int)0xE70100B2); 

		// Invalid character ID 
		public const int INVALID_CHARACTERID =                              unchecked((int)0xE70100B3); 

		// Character hasn't selected 
		public const int CHARACTER_NOT_SELECTED =                           unchecked((int)0xE70100B4); 

	}
}




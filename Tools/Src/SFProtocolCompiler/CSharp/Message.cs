////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Generic Message
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Concurrent;
using System.Net;
using System.Net.Sockets;
using System.IO;


namespace SF.Message
{
    
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Constants
	//
	enum Constants
	{
		// Packet type
		MSGTYPE_NETCONTROL		= 0,	// Net Control
		MSGTYPE_S2CEVT 			= 1,	// Event
		MSGTYPE_C2SEVT 			= 1,	// Event
		MSGTYPE_CMD	    		= 2,	// Command
		MSGTYPE_RES 			= 3,	// Result

        // Protocol 
        PROTOCOLID_NONE = 0,              // Not defined Protocol

        PROTOCOLID_LOGIN,
        PROTOCOLID_SVR_LOGIN,

        PROTOCOLID_GAME,                // Game policy
        PROTOCOLID_SVR_GAME,				// Game policy

        PROTOCOL_CLIENTNETMAX = PROTOCOLID_SVR_GAME + 1,
    };


    public struct MessageID
    {
        public UInt32 ID;

        public uint MsgID
        {
            get { return (ID & 0xFFFFF800) >> 11; }
            set { ID = (ID & (0x7FF)) | ((value << 11) & 0xFFFFF800); }
        }

        public uint Length
        {
            get { return (ID & 0x7FF); }
            set { ID = (ID & (0xFFFFF800)) | (value & 0x7FF); }
        }

        public uint MsgCode
        {
            get { return (ID&0x7FF800) >> 11; }
            set { ID = (ID & 0xE001FFFF) | ((value << 11) & 0x7FF800); }
        }

        public uint Policy
        {
            get { return (ID & 0xF800000) >> 23; }
            set { ID = (ID & 0xF07FFFFF) | ((value << 23) & 0xF800000); }
        }

        public bool Mobile
        {
            get { return ((ID & 0x10000000) >> 28) != 0; }
            set { ID = (ID & 0xEFFFFFFF) | (((value ? (UInt32)1 : (UInt32)0) << 28) & 0x10000000); }
        }

        public bool Reliable
        {
            get { return ((ID&0x20000000) >> 29) != 0; }
            set { ID = (ID & 0xDFFFFFFF) | (((value ? (UInt32)1 : (UInt32)0) << 29) & 0x20000000); }
        }

        public uint Type
        {
            get { return (ID&0xC0000000) >> 30; }
            set { ID = (ID & 0x3FFFFFFF) | ((value << 23) & 0xC0000000); }
        }

        // constructors
        public MessageID(uint uiType, bool reliable, uint uiPolicy, uint uiCode, uint uiLen = 0)
        {
            ID = 0;
            SetMessageID(uiType, reliable, uiPolicy, uiCode, uiLen);
        }

        public void SetMessageID(uint uiType, bool reliable, uint uiPolicy, uint uiCode, uint uiLen = 0)
        {
            Type = uiType;
            Reliable = reliable;
            Policy = uiPolicy;
            MsgCode = uiCode;
        }
    };


    // Unpacked packet header
    public struct MessageHeader
    {
        // Packet Maximum packet size
        // we just assume maximum packet size as 1KB for easy use
        public const int MaxPacketSize = 1024;

        // Packet header size, 4bytes for Message header
        public const int SizeOfHeader = 4;

        // Packet Class shift value
        public const int ShiftClass = 24;

        // packet class
        public MessageID MsgID;

        // Packet size that include header size
        public uint Sequence;

        // CRC32
        public uint Crc32;

        // PeerID
        public UInt64 PeerID;

        // read from bin reader
        public void Read(BinaryReader binReader)
        {
            MsgID.MsgID = binReader.ReadUInt32();
            Sequence = binReader.ReadUInt16();
            Crc32 = binReader.ReadUInt16();
            PeerID = binReader.ReadUInt64();
        }

        // write from bin writer
        public void Write(BinaryWriter binWriter)
        {
            binWriter.Write(MsgID.MsgID);
            binWriter.Write((UInt16)Sequence);
            binWriter.Write((UInt16)Crc32);
            binWriter.Write((UInt64)PeerID);
        }
	};


    /// <summary> 
    /// Message over network
    /// </summary>
    public abstract class MessageBase : IDisposable
    {
        // Message header
        public MessageHeader Header { get; private set; }

        // constructor
        public MessageBase()
        {
        }

        public MessageBase(ref MessageHeader header)
        {
            Header = header;
        }

        public virtual void Dispose()
        {
        }

        // Trace out message
        public abstract void TraceOut(string Prefix);

        //////////////////////////////////////////////////////////////////////////
        // Packet streaming 
        //  - We don't need to make streaming to binary. this will be done 

        // just virtual interface
        public abstract void ParseMsg(BinaryReader binReader);

        // build message buffer
        public abstract byte[] BuildMessageBuffer();
        public abstract byte[] BuildMessageBuffer( byte[] bufferToWrite );
    }
} 

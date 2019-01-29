////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message processor
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.IO;



namespace SF.Message
{
    /// <summary> 
    /// Message Processor
    /// </summary>
    public class MessageProcessor
    {
        // Memory stream of packet data
        private MemoryStream m_memStream;

        // packet binary stream reader
        private BinaryReader m_recvBinReader;

        // Packet header for header analysis
        private MessageHeader m_hdrParse;

        // Packet processing information by Message id
        private Dictionary<uint, Tuple<Type, Action<MessageBase>>> m_parseMap;


        // Constructor
        public MessageProcessor(MemoryStream stream)
        {
            m_memStream = stream;
            m_recvBinReader = new BinaryReader(stream);

            m_hdrParse = new MessageHeader();

            m_parseMap = new Dictionary<uint, Tuple<Type, Action<MessageBase>>>();
        }

        //////////////////////////////////////////////////////////////////////////////////
        // streaming with binary stream



        // Process packet parsing
        public MessageBase PacketParseNProcess()
        {
            // if there is not enough size then return
            if (m_recvBinReader.BaseStream.Length < MessageHeader.SizeOfHeader)
                return null;

            // seek set stream position
            m_recvBinReader.BaseStream.Seek(0, SeekOrigin.Begin);

            // Parse header first
            m_hdrParse.Read(m_recvBinReader);
            if (m_recvBinReader.BaseStream.Length < m_hdrParse.MsgID.Length) // if we need more data to receive
                return null;

            // find mapped message processing info
            Tuple<Type, Action<MessageBase>> processor = m_parseMap[m_hdrParse.MsgID.MsgID];
            if (processor == null)
                throw new System.NotImplementedException("Not implemented packet process");

            // create packet instance
            MessageBase newPacket = Activator.CreateInstance(processor.Item1) as MessageBase;

            // parse the packet
            newPacket.ParseMsg(m_recvBinReader);

            // remove processed data from stream
            int iRemainSize = (int)m_memStream.Length - (int)m_hdrParse.MsgID.Length;
            m_memStream.Read(m_memStream.GetBuffer(), 0, iRemainSize);
            m_memStream.SetLength(iRemainSize);

            // process message
            processor.Item2(newPacket);

            return newPacket;
        }

        // register parsing map
        //  - Type for message class
        //  - Action for packet processing
        public void RegisterProcessMap(uint msgID, Type msgClassType, Action<MessageBase> action)
        {
            m_parseMap.Add(msgID, Tuple.Create<Type, Action<MessageBase>>(msgClassType, action));
        }

    }

}

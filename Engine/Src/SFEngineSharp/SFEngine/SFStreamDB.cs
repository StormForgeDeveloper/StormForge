////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StreamDB interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
#if UNITY_IOS
using AOT;
#endif

#nullable enable

namespace SF
{


    public class StreamDB : SFObject
    {
        public StreamDB()
        {
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        //	interfaces
        //

        public virtual Result Initialize(string brokers, string topic)
        {
            var result = NativeInitialize(NativeHandle, System.Text.Encoding.UTF8.GetBytes(brokers + "\0"), System.Text.Encoding.UTF8.GetBytes(topic + "\0"));
            return new Result(result);
        }

        public string GetTopic()
        {
            var nativeStr = NativeGetTopic(NativeHandle);
            string topic = Marshal.PtrToStringAnsi(nativeStr) ?? string.Empty;
            return topic;
        }


        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //

        #region Native interfaces

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif


        [DllImport(NativeDllName, EntryPoint = "StreamDB_NativeInitialize", CharSet = CharSet.Auto)]
        static extern Int32 NativeInitialize(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] strBrokers, [MarshalAs(UnmanagedType.LPArray)] byte[] strTopic);


        [DllImport(NativeDllName, EntryPoint = "StreamDB_NativeGetTopic", CharSet = CharSet.Ansi)]
        static extern IntPtr NativeGetTopic(IntPtr nativeHandle);


        #endregion
    }


    public class StreamDBDirectory : SFObject
    {
        public enum DirectoryMode
        {
            Broker,
            Client
        }

        DirectoryMode m_DirectoryMode;

        public string ServerAddress { get; private set; } = string.Empty;

        public StreamDBDirectory(DirectoryMode mode = DirectoryMode.Broker)
        {
            m_DirectoryMode = mode;

            if (mode == DirectoryMode.Broker)
                NativeHandle = NativeCreateDirectoryBroker();
            else
                NativeHandle = NativeCreateDirectoryClient();
        }


        public virtual Result Initialize(string serverAddress)
        {
            ServerAddress = serverAddress;

            var result = NativeInitialize(NativeHandle, System.Text.Encoding.UTF8.GetBytes(serverAddress + "\0"));
            return new Result(result);
        }

        public Result RequestStreamList()
        {
            return new Result(NativeRequestStreamList(NativeHandle));
        }

        //public int GetTopicCount()
        //{
        //    if (m_DirectoryMode != DirectoryMode.Broker)
        //        return 0;

        //    return NativeGetTopicCount(NativeHandle);
        //}

        //public string GetTopic(int index)
        //{
        //    if (m_DirectoryMode != DirectoryMode.Broker)
        //        return null;

        //    var nativeStr = NativeGetTopic(NativeHandle, index);
        //    return Marshal.PtrToStringAnsi(nativeStr);
        //}


        public SFMessage? PollMessageData()
        {
            lock (SFMessageParsingUtil.stm_ParsingLock)
            {
                System.Diagnostics.Debug.Assert(SFMessageParsingUtil.stm_ParsingMessage == null);

                NativePollMessage(NativeHandle,
                    SFMessageParsingUtil.MessageParseCreateCallback,
                    SFMessageParsingUtil.MessageParseSetValue,
                    SFMessageParsingUtil.MessageParseSetArray
                    );

                var message = SFMessageParsingUtil.stm_ParsingMessage;
                SFMessageParsingUtil.stm_ParsingMessage = null;
                return message;
            }
        }



        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //

        #region Native interfaces

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativeInitialize", CharSet = CharSet.Auto)]
        static extern Int32 NativeInitialize(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] strBrokers);

        [DllImport(NativeDllName, EntryPoint = "StreamDB_NativeCreateDirectoryBroker", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateDirectoryBroker();

        [DllImport(NativeDllName, EntryPoint = "StreamDB_NativeCreateDirectoryClient", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateDirectoryClient();

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativeRequestStreamList", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequestStreamList(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativeGetTopicCount", CharSet = CharSet.Auto)]
        static extern Int32 NativeGetTopicCount(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativeGetTopic", CharSet = CharSet.Ansi)]
        static extern IntPtr NativeGetTopic(IntPtr nativeHandle, Int32 index);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_MESSAGE_FUNCTION(MessageID messageID);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, IntPtr Value);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_ARRAY_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, int arrayCount, IntPtr Value);

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativePollMessage", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativePollMessage(IntPtr nativeHandle, SET_MESSAGE_FUNCTION setMessageFunc, SET_FUNCTION setValueFunc, SET_ARRAY_FUNCTION setArrayValueFunc);

        #endregion
    }

    public class StreamDBProducer : StreamDB
    {
        public StreamDBProducer()
        {
            NativeHandle = NativeCreateProducer();
        }


        public Result SendRecord(byte[] data)
        {
            var result = NativeSendRecord(NativeHandle, data.Length, data);
            return new Result(result);
        }

        public Result Flush()
        {
            var result = NativeFlush(NativeHandle);
            return new Result(result);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //

        #region Native interfaces

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDllName, EntryPoint = "StreamDB_NativeCreateProducer", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateProducer();

        [DllImport(NativeDllName, EntryPoint = "StreamDBProducer_NativeSendRecord", CharSet = CharSet.Auto)]
        static extern Int32 NativeSendRecord(IntPtr nativeHandle, Int32 dataSize, byte[] data);

        [DllImport(NativeDllName, EntryPoint = "StreamDBProducer_NativeFlush", CharSet = CharSet.Auto)]
        static extern Int32 NativeFlush(IntPtr nativeHandle);

        #endregion
    }


    public class StreamDBConsumer : StreamDB
    {
        public StreamDBConsumer()
        {
            NativeHandle = NativeCreateConsumer();
        }

        /// <summary>
        /// Convert offset from tail to offset value can be used to request data call
        /// </summary>
        /// <param name="offsetFromTail"></param>
        /// <returns></returns>
        public Int64 ToOffsetFromTail(Int64 offsetFromTail)
        {
            return NativeToOffsetFromTail(NativeHandle, offsetFromTail);
        }

        public Result RequestData(Int64 start_offset)
        {
            var result = NativeRequestData(NativeHandle, start_offset);
            return new Result(result);
        }

        public static DateTime UnixTimeStampToDateTime(Int64 unixTimeStamp)
        {
            // Unix timestamp is seconds past epoch
            System.DateTime dtDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, System.DateTimeKind.Utc);
            dtDateTime = dtDateTime.AddMilliseconds(unixTimeStamp);
            return dtDateTime;
        }

        public Result PollData(out Int64 InOutmessageOffset, out DateTime InOutmessageTimeStamp, out byte[]? recordData)
        {
            InOutmessageOffset = 0;
            recordData = null;
            Int64 messageTimeStamp = 0;
            Int32 messageDataSize = 0;
            IntPtr messageData = IntPtr.Zero;

            var result = NativePollData(NativeHandle, out InOutmessageOffset, out messageTimeStamp, out messageDataSize, out messageData);

            InOutmessageTimeStamp = UnixTimeStampToDateTime(messageTimeStamp);
            if (messageDataSize > 0 && messageData != IntPtr.Zero)
            {
                recordData = new byte[messageDataSize];
                Marshal.Copy(messageData, recordData, 0, messageDataSize);
            }

            return new Result(result);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //

        #region Native interfaces

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif


        [DllImport(NativeDllName, EntryPoint = "StreamDB_NativeCreateConsumer", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateConsumer();

        [DllImport(NativeDllName, EntryPoint = "StreamDBConsumer_NativeToOffsetFromTail", CharSet = CharSet.Auto)]
        static extern Int64 NativeToOffsetFromTail(IntPtr nativeHandle, Int64 offsetFromTail);

        [DllImport(NativeDllName, EntryPoint = "StreamDBConsumer_NativeRequestData", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequestData(IntPtr nativeHandle, Int64 start_offset);

        [DllImport(NativeDllName, EntryPoint = "StreamDBConsumer_NativePollData", CharSet = CharSet.Auto)]
        static extern Int32 NativePollData(IntPtr nativeHandle, out Int64 InOutmessageOffset, out Int64 InOutmessageTimeStamp, out Int32 InOutmessageDataSize, out IntPtr InOutmessageData);

        #endregion
    }
}

#nullable restore

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
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
            return Marshal.PtrToStringAnsi(nativeStr);
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


    public class StreamDBDirectory : StreamDB
    {
        public StreamDBDirectory()
        {
            NativeHandle = NativeCreateDirectory();
        }




        public Result RefreshTopicList()
        {
            return new Result(NativeRefreshTopicList(NativeHandle));
        }

        public int GetTopicCount()
        {
            return NativeGetTopicCount(NativeHandle);
        }

        public string GetTopic(int index)
        {
            var nativeStr = NativeGetTopic(NativeHandle, index);
            return Marshal.PtrToStringAnsi(nativeStr);
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

        [DllImport(NativeDllName, EntryPoint = "StreamDB_NativeCreateDirectory", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateDirectory();

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativeRefreshTopicList", CharSet = CharSet.Auto)]
        static extern Int32 NativeRefreshTopicList(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativeGetTopicCount", CharSet = CharSet.Auto)]
        static extern Int32 NativeGetTopicCount(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "StreamDBDirectory_NativeGetTopic", CharSet = CharSet.Ansi)]
        static extern IntPtr NativeGetTopic(IntPtr nativeHandle, Int32 index);

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


        public Result RequestData(Int64 start_offset)
        {
            var result = NativeRequestData(NativeHandle, start_offset);
            return new Result(result);
        }

        public Result PollData(out byte[] recordData)
        {
            recordData = null;
            Int32 messageDataSize = 0;
            IntPtr messageData = IntPtr.Zero;
            var result = NativePollData(NativeHandle, ref messageDataSize, ref messageData);

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

        [DllImport(NativeDllName, EntryPoint = "StreamDBConsumer_NativeRequestData", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequestData(IntPtr nativeHandle, Int64 start_offset);

        [DllImport(NativeDllName, EntryPoint = "StreamDBConsumer_NativePollData", CharSet = CharSet.Auto)]
        static extern Int32 NativePollData(IntPtr nativeHandle, ref Int32 InOutmessageDataSize, ref IntPtr InOutmessageData);

        #endregion
    }
}


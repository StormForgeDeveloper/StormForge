////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StreamDB administration
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

    public class StreamDBAdmin : SFObject
    {
        public StreamDBAdmin(string brokers)
        {
            NativeHandle = NativeCreate(System.Text.Encoding.UTF8.GetBytes(brokers + "\0"));
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        //	interfaces
        //


        public Result CreateStream(string streamName)
        {
            return new Result(NativeCreateStream(NativeHandle, System.Text.Encoding.UTF8.GetBytes(streamName + "\0")));
        }

        public Result DeleteStream(string streamName)
        {
            return new Result(NativeDeleteStream(NativeHandle, System.Text.Encoding.UTF8.GetBytes(streamName + "\0")));
        }

        public void PollMessageData()
        {
            lock (SFMessageParsingUtil.stm_ParsingLock)
            {
                // FIXME
                System.Diagnostics.Debug.Assert(false);

                //SFMessageParsingUtil.stm_MessageDequeueConnection = this;

                //NativeDequeueMessage(NativeHandle,
                //    SFMessageParsingUtil.OnMessageData
                //    );

                //SFMessageParsingUtil.stm_MessageDequeueConnection = null;
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


        [DllImport(NativeDllName, EntryPoint = "StreamDBAdmin_NativeCreate", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreate([MarshalAs(UnmanagedType.LPArray)] byte[] strBrokers);


        [DllImport(NativeDllName, EntryPoint = "StreamDBAdmin_NativeCreateStream", CharSet = CharSet.Ansi)]
        static extern int NativeCreateStream(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] streamName);

        [DllImport(NativeDllName, EntryPoint = "StreamDBAdmin_NativeDeleteStream", CharSet = CharSet.Ansi)]
        static extern int NativeDeleteStream(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] streamName);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_MESSAGE_FUNCTION(MessageID messageID);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, IntPtr Value);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_ARRAY_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, int arrayCount, IntPtr Value);

        [DllImport(NativeDllName, EntryPoint = "StreamDBAdmin_NativePollMessage", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativePollMessage(IntPtr nativeHandle, SET_MESSAGE_FUNCTION setMessageFunc, SET_FUNCTION setValueFunc, SET_ARRAY_FUNCTION setArrayValueFunc);


        #endregion
    }


}

#nullable restore

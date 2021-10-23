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

        public SFMessage PollMessageData()
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


        [DllImport(NativeDllName, EntryPoint = "StreamDBAdmin_NativeCreate", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreate([MarshalAs(UnmanagedType.LPArray)] byte[] strBrokers);


        [DllImport(NativeDllName, EntryPoint = "StreamDBAdmin_NativeCreateStream", CharSet = CharSet.Ansi)]
        static extern int NativeCreateStream(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] streamName);

        [DllImport(NativeDllName, EntryPoint = "StreamDBAdmin_NativeDeleteStream", CharSet = CharSet.Ansi)]
        static extern int NativeDeleteStream(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] streamName);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_MESSAGE_FUNCTION(UInt32 messageID);

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


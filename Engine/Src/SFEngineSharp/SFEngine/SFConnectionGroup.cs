////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection group interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;


namespace SF
{


    public class SFConnectionGroup : SFObject
    {
        public SFConnectionGroup(int maximumQueueBufferSize)
        {
            // Don't use constructor of SFObject, it will increase reference count of the object
            NativeHandle = NativeCreateConnectionGroup(maximumQueueBufferSize);
        }

        public struct EventInformation : IDisposable
        {
            public IntPtr ConnectionHandle;
            public SFConnection.Event Event;
            public SFMessage pMsg;

            public void Dispose()
            {
                if (pMsg != null)
                    pMsg.Dispose();
                pMsg = null;
            }
        };


        // Message
        public IntPtr DequeueConnectionEvent(out EventInformation eventInfo)
        {
            eventInfo = new EventInformation();
            IntPtr connectionHandle;

            lock (SFMessageParsingUtil.stm_ParsingLock)
            {
                System.Diagnostics.Debug.Assert(SFMessageParsingUtil.stm_ParsingMessage == null);

                SFMessageParsingUtil.stm_Event = new SFConnection.Event();

                connectionHandle = NativeDequeueEvent(NativeHandle,
                    SFMessageParsingUtil.MessageParseSetEventCallback,
                    SFMessageParsingUtil.MessageParseCreateCallback,
                    SFMessageParsingUtil.MessageParseSetValue,
                    SFMessageParsingUtil.MessageParseSetArray
                    );

                var message = SFMessageParsingUtil.stm_ParsingMessage;

                eventInfo.ConnectionHandle = connectionHandle;
                eventInfo.pMsg = SFMessageParsingUtil.stm_ParsingMessage;
                eventInfo.Event = SFMessageParsingUtil.stm_Event;

                SFMessageParsingUtil.stm_ParsingMessage = null;

                if (connectionHandle == IntPtr.Zero)
                    return IntPtr.Zero;
            }

            return connectionHandle;
        }



        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //

        #region Native interfaces

        const string NativeDLLName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_EVENT_FUNCTION(SFConnection.EventTypes eventType, int result, SFConnection.ConnectionState state);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_MESSAGE_FUNCTION(UInt32 messageID);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, IntPtr Value);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_ARRAY_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, int arrayCount, IntPtr Value);

        [DllImport(NativeDLLName, EntryPoint = "SFConnectionGroup_NativeCreateConnectionGroup", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateConnectionGroup(int maximumQueueBufferSize);
        
        [DllImport(NativeDLLName, EntryPoint = "SFConnectionGroup_NativeDequeueEvent", CharSet = CharSet.Auto)]
        static extern IntPtr NativeDequeueEvent(IntPtr nativeHandle, SET_EVENT_FUNCTION setEventFunc, SET_MESSAGE_FUNCTION setMessageFunc, SET_FUNCTION setValueFunc, SET_ARRAY_FUNCTION setArrayValueFunc);

        #endregion
    }
}
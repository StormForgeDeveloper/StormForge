////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : OnlineClient interface
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


    public class OnlineClient : SFObject
    {
        // Connection event
        public delegate void ConnectionEventHandler(object sender, ref SFConnection.Event e);
        public event ConnectionEventHandler OnConnectionEvent;

        // Message event
        public delegate void MessageEventHandler(object sender, SFMessage msg);
        public event MessageEventHandler OnMessageEvent;


        public OnlineClient()
        {
            NativeHandle = NativeCreateOnlineClient();
        }

        public void UpdateGameTick()
        {
            lock (SFMessageParsingUtil.stm_ParsingLock)
            {
                stm_StaticEventReceiver = this;

                NativeUpdateGameTick(NativeHandle,
                    OnEvent_Internal,
                    SFMessageParsingUtil.MessageParseCreateCallback,
                    SFMessageParsingUtil.MessageParseSetValue,
                    SFMessageParsingUtil.MessageParseSetArray,
                    OnMessageReady_Internal
                    );

                SFMessageParsingUtil.stm_ParsingMessage = null;
                stm_StaticEventReceiver = null;
            }
        }


        #region Event Receiving

        static internal OnlineClient stm_StaticEventReceiver = null;

        static internal void OnEvent_Internal(SFConnection.EventTypes eventType, int result, SFConnection.ConnectionState state)
        {
            if (stm_StaticEventReceiver == null)
                return;

            SFConnection.Event evt = new SFConnection.Event();
            evt.EventType = eventType;
            evt.HResult.Code = result;
            evt.State = state;

            stm_StaticEventReceiver.OnConnectionEvent.Invoke(stm_StaticEventReceiver, ref evt);
        }

        static internal void OnMessageReady_Internal()
        {
            if (stm_StaticEventReceiver == null)
                return;

            var message = SFMessageParsingUtil.stm_ParsingMessage;
            SFMessageParsingUtil.stm_ParsingMessage = null;

            // fire message handler
            stm_StaticEventReceiver.OnMessageEvent.Invoke(stm_StaticEventReceiver, message);
        }


        #endregion

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
        public delegate void ON_READY_FUNCTION();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_EVENT_FUNCTION(SFConnection.EventTypes eventType, int result, SFConnection.ConnectionState state);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_MESSAGE_FUNCTION(UInt32 messageID);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, IntPtr Value);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_ARRAY_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, int arrayCount, IntPtr Value);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeCreateOnlineClient", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateOnlineClient();
        
        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeUpdateGameTick", CharSet = CharSet.Auto)]
        static extern UInt32 NativeUpdateGameTick(IntPtr nativeHandle, SET_EVENT_FUNCTION setEventFunc, SET_MESSAGE_FUNCTION setMessageFunc, SET_FUNCTION setValueFunc, SET_ARRAY_FUNCTION setArrayValueFunc, ON_READY_FUNCTION onMessageReady);

        #endregion
    }
}
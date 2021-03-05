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
        public enum OnlineState
        {
            None,

			// Login operations
			ConnectingToLogin,
			LogingIn,
			LoggedIn,

			// In game state
			ConnectingToGameServer,
			JoiningToGameServer,
			InGameServer,

            // In game instance state. the player still in game as well
            InGameJoiningGameInstance,
            InGameConnectingGameInstance,
            InGameGameInstanceJoining,
            InGameInGameInstance,

            // Disconnected
            Disconnected,
		};

        public enum ConnectionType
        {
            Login,
            Game,
            GameInstance
        }

        readonly SFIMessageRouter m_MessageRouter = null;

        public SFIMessageRouter MessageRouter { get { return m_MessageRouter; } }


        // Connection event
        public delegate void ConnectionEventHandler(object sender, ref SFConnection.Event e);
        public event ConnectionEventHandler OnConnectionEvent;

        // Message event
        public delegate void MessageEventHandler(object sender, SFMessage msg);
        public event MessageEventHandler OnMessageEvent;

        public delegate void OnlineStateChangedHandler(object sender, OnlineState prevState, OnlineState newState);
        public static event OnlineStateChangedHandler OnOnlineStateChanged;


        public OnlineClient(SFIMessageRouter messageRouter = null)
        {
            NativeHandle = NativeCreateOnlineClient();
            m_MessageRouter = messageRouter;

            NativeSetOnlineStateCallback(NativeHandle, OnOnlineStateChanged_Internal);
        }

        public Result StartConnection(string gameId, string loginAddress, string userId, string password)
        {
            var res = NativeStartConnection(NativeHandle, gameId, loginAddress, userId, password);
            return new Result((int)res);
        }

        public Result JoinGameInstance(UInt64 gameInstanceUID)
        {
            var res = NativeJoinGameInstance(NativeHandle, gameInstanceUID);
            return new Result((int)res);
        }

        public void DisconnectAll()
        {
            NativeDisconnectAll(NativeHandle);
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

        public OnlineState GetOnlineState()
        {
            return (OnlineState)NativeGetOnlineState(NativeHandle);
        }

        static void OnOnlineStateChanged_Internal(OnlineState prevState, OnlineState newState)
        {
            OnOnlineStateChanged?.Invoke(null, prevState, newState);
        }

        public Int32 GetGameId()
        {
            return NativeGetGameId(NativeHandle);
        }

        public UInt64 GetGameInstanceUID()
        {
            return NativeGetGameInstanceUID(NativeHandle);
        }

        public SFConnection GetConnection(ConnectionType connectionType)
        {
            var connectionHandle = NativeGetConnection(NativeHandle, (int) connectionType);
            if (connectionHandle != IntPtr.Zero)
                return new SFConnection(connectionHandle);

            return null;
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

            stm_StaticEventReceiver.OnConnectionEvent?.Invoke(stm_StaticEventReceiver, ref evt);
        }

        static internal void OnMessageReady_Internal()
        {
            if (stm_StaticEventReceiver == null)
                return;

            var message = SFMessageParsingUtil.stm_ParsingMessage;
            SFMessageParsingUtil.stm_ParsingMessage = null;

            // fire message handler
            stm_StaticEventReceiver.OnMessageEvent?.Invoke(stm_StaticEventReceiver, message);

            stm_StaticEventReceiver.m_MessageRouter?.HandleRecvMessage(message);
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

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ONLINE_STATECHAGED_CALLBACK(OnlineState prevState, OnlineState newState);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeCreateOnlineClient", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateOnlineClient();

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeStartConnection", CharSet = CharSet.Auto)]
        static extern Int32 NativeStartConnection(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string gameId, [MarshalAs(UnmanagedType.LPStr)] string loginAddress, [MarshalAs(UnmanagedType.LPStr)] string userId, [MarshalAs(UnmanagedType.LPStr)] string password);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeJoinGameInstance", CharSet = CharSet.Auto)]
        static extern Int32 NativeJoinGameInstance(IntPtr nativeHandle, UInt64 gameInstanceUID);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeDisconnectAll", CharSet = CharSet.Auto)]
        static extern void NativeDisconnectAll(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetOnlineState", CharSet = CharSet.Auto)]
        static extern Int32 NativeGetOnlineState(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetGameId", CharSet = CharSet.Auto)]
        static extern Int32 NativeGetGameId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetGameInstanceUID", CharSet = CharSet.Auto)]
        static extern UInt64 NativeGetGameInstanceUID(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeUpdateGameTick", CharSet = CharSet.Auto)]
        static extern Int32 NativeUpdateGameTick(IntPtr nativeHandle, SET_EVENT_FUNCTION setEventFunc, SET_MESSAGE_FUNCTION setMessageFunc, SET_FUNCTION setValueFunc, SET_ARRAY_FUNCTION setArrayValueFunc, ON_READY_FUNCTION onMessageReady);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetConnection", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetConnection(IntPtr nativeHandle, Int32 connectionIndex);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeSetOnlineStateCallback", CharSet = CharSet.Auto)]
        static extern Int32 NativeSetOnlineStateCallback(IntPtr nativeHandle, ONLINE_STATECHAGED_CALLBACK setEventFunc);

        #endregion
    }
}
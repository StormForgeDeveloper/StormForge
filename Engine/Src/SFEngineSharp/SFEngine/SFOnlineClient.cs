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
using SF.Net;
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

			// Disconnected
			Disconnected,

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

        public delegate void OnlineTaskFinishedHandler(UInt64 transactionId);
        public static event OnlineTaskFinishedHandler OnOnlineTaskFinished;



        public OnlineClient(SFIMessageRouter messageRouter = null)
        {
            NativeHandle = NativeCreateOnlineClient();
            m_MessageRouter = messageRouter;
        }

        public Result StartConnection(UInt64 transactionId, string gameId, string loginAddress, string userId, string password)
        {
            ResetConnectionAdapter();

            SF.Log.Info($"Online StartConnection: gameId:{gameId}, loginAddr:{loginAddress}, userId:{userId}");

            var res = NativeStartConnection(NativeHandle, transactionId, gameId, loginAddress, userId, password);
            return new Result((int)res);
        }

        public Result StartConnection(UInt64 transactionId, string gameId, string loginAddress, UInt64 steamUserId, string steamUserName, string steamUserToken)
        {
            ResetConnectionAdapter();

            SF.Log.Info($"Online StartConnection: gameId:{gameId}, loginAddr:{loginAddress}, steamUserId:{steamUserId}, steamUserName:{steamUserName}");

            var res = NativeStartConnectionSteam(NativeHandle, transactionId, gameId, loginAddress, steamUserId, steamUserName, steamUserToken);
            return new Result((int)res);
        }

        public Result JoinGameInstance(UInt64 transactionId, UInt64 gameInstanceUID)
        {
            var res = NativeJoinGameInstance(NativeHandle, transactionId, gameInstanceUID);
            return new Result((int)res);
        }

        public void DisconnectAll()
        {
            ResetConnectionAdapter();

            NativeDisconnectAll(NativeHandle);
        }

        public UInt64 GetPlayerId()
        {
            return NativeGetPlayerId(NativeHandle);
        }

        public StringCrc32 GetGameId()
        {
            return new StringCrc32(NativeGetGameId(NativeHandle));
        }

        public UInt64 GetGameInstanceUID()
        {
            return NativeGetGameInstanceUID(NativeHandle);
        }

        public UInt32 GetCharacterId()
        {
            return NativeGetCharacterId(NativeHandle);
        }

        public UInt32 GetActorId()
        {
            return NativeGetActorId(NativeHandle);
        }

        public void UpdateGameTick(out UInt32 deltaFrames)
        {
            lock (SFMessageParsingUtil.stm_ParsingLock)
            {
                stm_StaticEventReceiver = this;

                NativeUpdateGameTick(NativeHandle,
                    OnOnlineStateChanged_Internal,
                    OnEvent_Internal,
                    SFMessageParsingUtil.MessageParseCreateCallback,
                    SFMessageParsingUtil.MessageParseSetValue,
                    SFMessageParsingUtil.MessageParseSetArray,
                    OnMessageReady_Internal,
                    OnTaskFinished_Internal
                    );

                SFMessageParsingUtil.stm_ParsingMessage = null;
                stm_StaticEventReceiver = null;
            }

            NativeUpdateMovement(NativeHandle, out deltaFrames);
        }

        public OnlineState GetOnlineState()
        {
            return (OnlineState)NativeGetOnlineState(NativeHandle);
        }

#if UNITY_EDITOR
        static bool PrintOnlineStateChangeDebug = true;
#endif
#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof (ONLINE_STATECHAGED_CALLBACK))]
#endif
        static void OnOnlineStateChanged_Internal(OnlineState prevState, OnlineState newState)
        {
#if UNITY_EDITOR

            if (PrintOnlineStateChangeDebug)
                UnityEngine.Debug.Log(string.Format("OnOnlineStateChanged InvokeCount = {0}", OnOnlineStateChanged?.GetInvocationList().Length));
#endif
            OnOnlineStateChanged?.Invoke(null, prevState, newState);
        }

        public SFConnection GetConnection(ConnectionType connectionType)
        {
            var connectionHandle = NativeGetConnection(NativeHandle, (int)connectionType);
            if (connectionHandle != IntPtr.Zero)
                return new SFConnection(connectionHandle);

            return null;
        }


        #region Connection cache

        SendMessageLogin m_LoginAdapterCached;
        SendMessageGame m_GameAdapterCached;
        SendMessagePlayInstance m_PlayInstanceAdapterCached;

        public virtual void ResetConnectionAdapter()
        {
            m_LoginAdapterCached = null;
            m_GameAdapterCached = null;
            m_PlayInstanceAdapterCached = null;
        }


        protected TAdapter GetAdapterInternal<TAdapter>(ConnectionType conType, ref TAdapter CachedAdapter)
            where TAdapter : SendMessage, new()
        {
            var connectionHandle = NativeGetConnection(NativeHandle, (int)conType);
            if (connectionHandle == IntPtr.Zero)
            {
                CachedAdapter = null;
                return null;
            }

            if (CachedAdapter != null && CachedAdapter.Connection.NativeHandle == connectionHandle)
                return CachedAdapter;

            CachedAdapter = new TAdapter();
            CachedAdapter.Connection = new SFConnection(connectionHandle);
            return CachedAdapter;
        }

        public SendMessageLogin LoginAdapter
        {
            get
            {
                return GetAdapterInternal<SendMessageLogin>(ConnectionType.Login, ref m_LoginAdapterCached);
            }
        }
        public SendMessageGame GameAdapter
        {
            get
            {
                return GetAdapterInternal<SendMessageGame>(ConnectionType.Game, ref m_GameAdapterCached);
            }
        }

        public SendMessagePlayInstance PlayInstanceAdapter
        {
            get
            {
                return GetAdapterInternal<SendMessagePlayInstance>(ConnectionType.GameInstance, ref m_PlayInstanceAdapterCached);
            }
        }


        #endregion

        public UInt32 GetCurrentMoveFrame()
        {
            return NativeGetCurrentMoveFrame(NativeHandle);
        }

        public Result SendMovement(ref ActorMovement newMove)
        {
            return new Result(NativeSendMovement(NativeHandle, ref newMove));
        }

        #region Event Receiving

        static internal OnlineClient stm_StaticEventReceiver = null;

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SET_EVENT_FUNCTION))]
#endif
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

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(ON_READY_FUNCTION))]
#endif
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

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(ONLINE_TASK_FINISHED_CALLBACK))]
#endif
        static internal void OnTaskFinished_Internal(UInt64 transactionId)
        {
            OnOnlineTaskFinished?.Invoke(transactionId);
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

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ONLINE_TASK_FINISHED_CALLBACK(UInt64 transactionId);


        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeCreateOnlineClient", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateOnlineClient();

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeStartConnection", CharSet = CharSet.Auto)]
        static extern Int32 NativeStartConnection(IntPtr nativeHandle, UInt64 transactionId, [MarshalAs(UnmanagedType.LPStr)] string gameId, [MarshalAs(UnmanagedType.LPStr)] string loginAddress, [MarshalAs(UnmanagedType.LPStr)] string userId, [MarshalAs(UnmanagedType.LPStr)] string password);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeStartConnectionSteam", CharSet = CharSet.Auto)]
        static extern Int32 NativeStartConnectionSteam(IntPtr nativeHandle, UInt64 transactionId, [MarshalAs(UnmanagedType.LPStr)] string gameId, [MarshalAs(UnmanagedType.LPStr)] string loginAddress, UInt64 steamUserId, [MarshalAs(UnmanagedType.LPStr)] string steamUserName, [MarshalAs(UnmanagedType.LPStr)] string steamUserToken);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeJoinGameInstance", CharSet = CharSet.Auto)]
        static extern Int32 NativeJoinGameInstance(IntPtr nativeHandle, UInt64 transactionId, UInt64 gameInstanceUID);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeDisconnectAll", CharSet = CharSet.Auto)]
        static extern void NativeDisconnectAll(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetOnlineState", CharSet = CharSet.Auto)]
        static extern Int32 NativeGetOnlineState(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetPlayerId", CharSet = CharSet.Auto)]
        static extern UInt64 NativeGetPlayerId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetCharacterId", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetCharacterId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetActorId", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetActorId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetGameId", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetGameId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetGameInstanceUID", CharSet = CharSet.Auto)]
        static extern UInt64 NativeGetGameInstanceUID(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeUpdateGameTick", CharSet = CharSet.Auto)]
        static extern Int32 NativeUpdateGameTick(IntPtr nativeHandle, ONLINE_STATECHAGED_CALLBACK setOnlineStateEventFunc, SET_EVENT_FUNCTION setEventFunc, SET_MESSAGE_FUNCTION setMessageFunc, SET_FUNCTION setValueFunc, SET_ARRAY_FUNCTION setArrayValueFunc, ON_READY_FUNCTION onMessageReady, ONLINE_TASK_FINISHED_CALLBACK onTaskFinished);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeUpdateMovement", CharSet = CharSet.Auto)]
        static extern Int32 NativeUpdateMovement(IntPtr nativeHandle, out UInt32 deltaFrames);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetConnection", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetConnection(IntPtr nativeHandle, Int32 connectionIndex);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetCurrentMoveFrame", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetCurrentMoveFrame(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeSendMovement", CharSet = CharSet.Auto)]
        static extern Int32 NativeSendMovement(IntPtr nativeHandle, ref ActorMovement actorMovement);

        #endregion
    }
}

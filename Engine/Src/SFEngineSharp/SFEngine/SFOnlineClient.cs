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
using SF.Flat;
using SF.Net;
#if UNITY_IOS
using AOT;
#endif

#nullable enable

namespace SF
{


    public partial class OnlineClient : SFObject
    {
        public enum OnlineState
        {
            None,

            // Disconnected
            Disconnected,

            // Login operations
            ConnectingToLogin, // Not used
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
            None, // not used
            Game,
            GameInstance
        }

        SFMessageRouterGroup m_MessageRouterGroup = new();

        public SFMessageRouterGroup MessageRouter { get { return m_MessageRouterGroup; } }


        // Connection event
        public delegate void ConnectionEventHandler(object sender, ref SFConnection.Event e);
        public event ConnectionEventHandler? OnConnectionEvent = null;

        // Message event
        public delegate void OnlineStateChangedHandler(object? sender, OnlineState prevState, OnlineState newState);
        public static event OnlineStateChangedHandler? OnOnlineStateChanged = null;



        public OnlineClient()
        {
            NativeHandle = NativeCreateOnlineClient();

            MessageRouter.AddUnique(m_RequestCallbackRouter);
        }

        public Result StartConnection(TransactionID transactionId, string gameId, string loginAddress, string userId, string password, Action<SFMessage>? callback = null)
        {
            ResetConnectionAdapter();

            SF.Log.Info($"Online StartConnection: gameId:{gameId}, loginAddr:{loginAddress}, userId:{userId}");

            if (!transactionId.IsValid)
                transactionId = NewTransactionID();

            Result res = new(NativeStartConnection(NativeHandle, transactionId.TransactionId, gameId, loginAddress, userId, password));
            if (res.IsFailure)
                return res;

            m_RequestCallbackRouter.AddPendingRequest(transactionId, callback);

            return res;
        }

        public Result StartConnection(TransactionID transactionId, string gameId, string loginAddress, UInt64 steamUserId, string steamUserName, string steamUserToken, Action<SFMessage>? callback = null)
        {
            ResetConnectionAdapter();

            SF.Log.Info($"Online StartConnection: gameId:{gameId}, loginAddr:{loginAddress}, steamUserId:{steamUserId}, steamUserName:{steamUserName}");

            if (!transactionId.IsValid)
                transactionId = NewTransactionID();

            Result res = new(NativeStartConnectionSteam(NativeHandle, transactionId.TransactionId, gameId, loginAddress, steamUserId, steamUserName, steamUserToken));
            if (res.IsFailure)
                return res;

            m_RequestCallbackRouter.AddPendingRequest(transactionId, callback);

            return res;
        }

        public Result JoinGameInstance(GameInstanceUID gameInstanceUID, Action<SFMessage>? callback = null)
        {
            TransactionID transactionId = NewTransactionID();

            return JoinGameInstance(transactionId, gameInstanceUID, callback);
        }
        public Result JoinGameInstance(TransactionID transactionId, GameInstanceUID gameInstanceUID, Action<SFMessage>? callback = null)
        {
            Result res = new(NativeJoinGameInstance(NativeHandle, transactionId.TransactionId, gameInstanceUID.UID));
            if (res.IsFailure)
                return res;

            m_RequestCallbackRouter.AddPendingRequest(transactionId, callback);

            return res;
        }


        public void DisconnectAll()
        {
            ResetConnectionAdapter();

            NativeDisconnectAll(NativeHandle);
        }

        public AccountID GetPlayerId()
        {
            IntPtr valuePtr = NativeGetPlayerId(NativeHandle);
            if (valuePtr == IntPtr.Zero)
                return new AccountID();

            var bytes = new byte[16];
            Marshal.Copy(valuePtr, bytes, 0, bytes.Length);
            return new AccountID(bytes);
        }

        public StringCrc32 GetGameId()
        {
            return new StringCrc32(NativeGetGameId(NativeHandle));
        }

        public SF.GameInstanceUID GetGameInstanceUID()
        {
            return new SF.GameInstanceUID(NativeGetGameInstanceUID(NativeHandle));
        }

        public CharacterID GetCharacterId()
        {
            IntPtr valuePtr = NativeGetCharacterId(NativeHandle);
            if (valuePtr == IntPtr.Zero)
                return new CharacterID();

            var bytes = new byte[16];
            Marshal.Copy(valuePtr, bytes, 0, bytes.Length);
            return new CharacterID(bytes);
        }

        public UInt32 GetActorId()
        {
            return NativeGetActorId(NativeHandle);
        }

#if UNITY_STANDALONE
		[AOT.MonoPInvokeCallback(typeof(ON_MESSAGE_FUNCTION))]
#endif
        static public void OnMessageData(UInt32 messageID, UInt64 transactionId, Result result, uint payloadSize, IntPtr payloadPtr)
        {
            SFMessage message = new SFMessage(new MessageID(messageID), new TransactionID(transactionId), result, payloadSize, payloadPtr);
            stm_StaticEventReceiver?.MessageRouter.HandleRecvMessage(message);
        }


        public void UpdateGameTick(out UInt32 deltaFrames)
        {
            lock (SFMessageParsingUtil.stm_ParsingLock)
            {
                stm_StaticEventReceiver = this;

                NativeUpdateGameTick(NativeHandle,
                    OnOnlineStateChanged_Internal,
                    OnEvent_Internal,
                    OnMessageData,
                    OnTaskFinished_Internal
                    );

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


        #region Connection cache

        GameRPCSendAdapter? m_GameAdapterCached = null;
        PlayInstanceRPCSendAdapter? m_PlayInstanceAdapterCached = null;

        public virtual void ResetConnectionAdapter()
        {
            m_GameAdapterCached = null;
            m_PlayInstanceAdapterCached = null;
        }


        protected TAdapter? GetAdapterInternal<TAdapter>(ConnectionType conType, ref TAdapter? CachedAdapter)
            where TAdapter : RPCAdapter, new()
        {
            var connectionHandle = NativeGetConnection(NativeHandle, (int)conType);
            if (connectionHandle == IntPtr.Zero)
            {
                CachedAdapter = null;
                return null;
            }

            var connection = CachedAdapter?.Endpoint as SFConnection;
            if (CachedAdapter != null && connection != null && connection.NativeHandle == connectionHandle)
                return CachedAdapter;

            CachedAdapter = new TAdapter();
            CachedAdapter.Endpoint = new SFConnection(connectionHandle
                , messageRouter: MessageRouter
                , transactionIdGenerator: m_OnlineTransactionIDGenerator);
            return CachedAdapter;
        }

        public GameRPCSendAdapter? GameAdapter
        {
            get
            {
                return GetAdapterInternal<GameRPCSendAdapter>(ConnectionType.Game, ref m_GameAdapterCached);
            }
        }

        public PlayInstanceRPCSendAdapter? PlayInstanceAdapter
        {
            get
            {
                return GetAdapterInternal<PlayInstanceRPCSendAdapter>(ConnectionType.GameInstance, ref m_PlayInstanceAdapterCached);
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

        static internal OnlineClient? stm_StaticEventReceiver = null;

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SET_EVENT_FUNCTION))]
#endif
        static internal void OnEvent_Internal(SFConnection.EventTypes eventType, Result result, SFConnection.ConnectionState state)
        {
            if (stm_StaticEventReceiver == null)
                return;

            SFConnection.Event evt = new SFConnection.Event();
            evt.EventType = eventType;
            evt.HResult = result;
            evt.State = state;

            stm_StaticEventReceiver.OnConnectionEvent?.Invoke(stm_StaticEventReceiver, ref evt);
        }

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(ONLINE_TASK_FINISHED_CALLBACK))]
#endif
        static internal void OnTaskFinished_Internal(UInt64 inTransactionId, Result result)
        {
            if (stm_StaticEventReceiver != null)
            {
                // FIXME: We need message ID for it
                var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
                var transactionId = new TransactionID(inTransactionId);
                var transactionIdOffset = builder.CreateTransactionID(transactionId);

                SF.Flat.Generic.GenericTransactionRes.StartGenericTransactionRes(builder);
                SF.Flat.Generic.GenericTransactionRes.AddFinishedTransaction(builder, transactionIdOffset);
                var packetOffset = SF.Flat.Generic.GenericTransactionRes.EndGenericTransactionRes(builder);

                builder.Finish(packetOffset.Value);

                var buf = builder.DataBuffer;
                var segment = buf.ToArraySegment(buf.Position, buf.Length - buf.Position);

                var message = new SFMessage(SF.Net.MessageIDGeneric.GenericTransactionRes, transactionId, result, segment);

                stm_StaticEventReceiver.MessageRouter.HandleRecvMessage(message);
            }
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
        public delegate void SET_EVENT_FUNCTION(SFConnection.EventTypes eventType, Result result, SFConnection.ConnectionState state);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ON_MESSAGE_FUNCTION(UInt32 messageID, UInt64 transactionId, Result result, uint payloadSize, IntPtr payloadPtr);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ONLINE_STATECHAGED_CALLBACK(OnlineState prevState, OnlineState newState);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ONLINE_TASK_FINISHED_CALLBACK(UInt64 transactionId, Result result);


        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeCreateOnlineClient", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateOnlineClient();

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeStartConnection", CharSet = CharSet.Auto)]
        static extern Int32 NativeStartConnection(IntPtr nativeHandle, UInt64 transactionId, [MarshalAs(UnmanagedType.LPStr)] string gameId, [MarshalAs(UnmanagedType.LPStr)] string loginAddress, [MarshalAs(UnmanagedType.LPStr)] string userId, [MarshalAs(UnmanagedType.LPStr)] string password);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeStartConnectionSteam", CharSet = CharSet.Auto)]
        static extern Int32 NativeStartConnectionSteam(IntPtr nativeHandle, UInt64 transactionId, [MarshalAs(UnmanagedType.LPStr)] string gameId, [MarshalAs(UnmanagedType.LPStr)] string loginAddress, UInt64 steamUserId, [MarshalAs(UnmanagedType.LPStr)] string steamUserName, [MarshalAs(UnmanagedType.LPStr)] string steamUserToken);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeJoinGameInstance", CharSet = CharSet.Auto)]
        static extern Int32 NativeJoinGameInstance(IntPtr nativeHandle, UInt64 transactionId, UInt32 gameInstanceUID);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeDisconnectAll", CharSet = CharSet.Auto)]
        static extern void NativeDisconnectAll(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetOnlineState", CharSet = CharSet.Auto)]
        static extern Int32 NativeGetOnlineState(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetPlayerId", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetPlayerId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetCharacterId", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetCharacterId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetActorId", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetActorId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetGameId", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetGameId(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeGetGameInstanceUID", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetGameInstanceUID(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineClient_NativeUpdateGameTick", CharSet = CharSet.Auto)]
        static extern Int32 NativeUpdateGameTick(IntPtr nativeHandle, ONLINE_STATECHAGED_CALLBACK setOnlineStateEventFunc, SET_EVENT_FUNCTION setEventFunc, ON_MESSAGE_FUNCTION onMessageFunc, ONLINE_TASK_FINISHED_CALLBACK onTaskFinished);

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

#nullable restore

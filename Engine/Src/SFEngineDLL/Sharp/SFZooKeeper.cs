﻿////////////////////////////////////////////////////////////////////////////////
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


    public class SFZooKeeper : IDisposable
    {

        #region Constants

        /// <summary>
        /// Constants
        /// </summary>


        static public int NODE_FLAG_EPHEMERAL { get { return SFZooKeeper_NODE_FLAG_EPHEMERAL(); } }
        static public int NODE_FLAG_SEQUENCE { get { return SFZooKeeper_NODE_FLAG_SEQUENCE(); } }

        static public int STATE_SESSION_EXPIRED { get { return SFZooKeeper_STATE_SESSION_EXPIRED(); } }
        static public int STATE_CONNECTED { get { return SFZooKeeper_STATE_CONNECTED(); } }
        static public int STATE_CONNECTING { get { return SFZooKeeper_STATE_CONNECTING(); } }

        static public int EVENT_CREATED { get { return SFZooKeeper_EVENT_CREATED(); } }
        static public int EVENT_DELETED { get { return SFZooKeeper_EVENT_DELETED(); } }
        static public int EVENT_CHANGED { get { return SFZooKeeper_EVENT_CHANGED(); } }
        static public int EVENT_CHILD { get { return SFZooKeeper_EVENT_CHILD(); } }
        static public int EVENT_SESSION { get { return SFZooKeeper_EVENT_SESSION(); } }
        static public int EVENT_NO_WATCHING { get { return SFZooKeeper_EVENT_NO_WATCHING(); } }

        #endregion


        private IntPtr m_NativeHandle = IntPtr.Zero;
        public IntPtr NativeHandle { get { return m_NativeHandle; } }


        Queue<string> m_EventQueue = new Queue<string>();

        public SFZooKeeper()
        {
            m_NativeHandle = NativeCreateZooKeeper();
        }

        public void Dispose()
        {
            if (m_NativeHandle != IntPtr.Zero)
            {
                NativeDestroyZooKeeper(m_NativeHandle);
                m_NativeHandle = IntPtr.Zero;
            }
        }


        public bool Connect(string connectionString)
        {
            return NativeConnect(NativeHandle, connectionString);
        }

        public void Close()
        {
            NativeClose(NativeHandle);
        }

        public int GetState()
        {
            return NativeGetState(NativeHandle);
        }

        public bool IsConnected()
        {
            return GetState() == STATE_CONNECTED;
        }

        public bool WaitForConnected()
        {
            return NativeWaitForConnected(NativeHandle);
        }

        public bool WaitForDisconnected()
        {
            return NativeWaitForDisconnected(NativeHandle);
        }

        public int CreateNode(string nodePath, string value, int flag = 0)
        {
            return NativeCreateNode(NativeHandle, nodePath, value, flag);
        }

        public bool Exists(string nodePath)
        {
            return NativeExists(NativeHandle, nodePath);
        }

        public string Get(string nodePath)
        {
            return Marshal.PtrToStringAnsi(NativeGet(NativeHandle, nodePath));
        }

        public string[] GetChildren(string nodePath, bool watch = false)
        {
            List<string> children = new List<string>();
            NativeGetChildren(NativeHandle, nodePath, (IntPtr stringPtr) =>
            {
                children.Add(Marshal.PtrToStringAnsi(stringPtr));
            }, watch ? 1 : 0);

            return children.ToArray();
        }

        public int DeleteAllChildren(string nodePath)
        {
            return NativeDeleteAllChildren(NativeHandle, nodePath);
        }
        

        public struct ZKEvent
        {
            public string NodePath;
            public int State;
            public int EventType;
        }

        public bool DequeueEvent(out ZKEvent zkEvent)
        {
            zkEvent = new ZKEvent();

            IntPtr nodePath;

            var result = NativeDequeueEvent(NativeHandle, out nodePath, out zkEvent.State, out zkEvent.EventType);
            if(result == 0)
            {
                zkEvent.NodePath = Marshal.PtrToStringAnsi(nodePath);
            }

            return result == 0;
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


        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_NODE_FLAG_EPHEMERAL", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_NODE_FLAG_EPHEMERAL();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_NODE_FLAG_SEQUENCE", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_NODE_FLAG_SEQUENCE();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_STATE_SESSION_EXPIRED", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_STATE_SESSION_EXPIRED();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_STATE_CONNECTED", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_STATE_CONNECTED();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_STATE_CONNECTING", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_STATE_CONNECTING();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_EVENT_CREATED", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_EVENT_CREATED();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_EVENT_DELETED", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_EVENT_DELETED();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_EVENT_CHANGED", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_EVENT_CHANGED();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_EVENT_CHILD", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_EVENT_CHILD();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_EVENT_SESSION", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_EVENT_SESSION();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_Const_EVENT_NO_WATCHING", CharSet = CharSet.Auto)]
        static extern int SFZooKeeper_EVENT_NO_WATCHING();




        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeCreateZooKeeper", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateZooKeeper();

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeDestroyZooKeeper", CharSet = CharSet.Auto)]
        static extern void NativeDestroyZooKeeper(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeIsConnected", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeIsConnected(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeGetState", CharSet = CharSet.Auto)]
        static extern int NativeGetState(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeConnect", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeConnect(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string connectionString);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeClose", CharSet = CharSet.Auto)]
        static extern void NativeClose(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeWaitForConnected", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeWaitForConnected(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeWaitForDisconnected", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeWaitForDisconnected(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeCreateNode", CharSet = CharSet.Auto)]
        static extern int NativeCreateNode(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string nodePath, [MarshalAs(UnmanagedType.LPStr)] string nodeValue, int flags);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeExists", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeExists(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string nodePath);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeGet", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGet(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string nodePath);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void NATIVE_GETCHILDREN_CB_FUNCTION(IntPtr stringPtr);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeGetChildren", CharSet = CharSet.Auto)]
        static extern int NativeGetChildren(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string nodePath, NATIVE_GETCHILDREN_CB_FUNCTION func, int watch);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeDeleteAllChildren", CharSet = CharSet.Auto)]
        static extern int NativeDeleteAllChildren(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string nodePath);

        [DllImport(NativeDLLName, EntryPoint = "SFZooKeeper_NativeDequeueEvent", CharSet = CharSet.Auto)]
        static extern int NativeDequeueEvent(IntPtr nativeHandle, out IntPtr nodePath, out int state, out int eventType);

        #endregion
    }
}


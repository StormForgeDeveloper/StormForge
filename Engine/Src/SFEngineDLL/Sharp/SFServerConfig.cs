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


    public class SFServerConfig : IDisposable
    {
        private IntPtr m_NativeHandle = IntPtr.Zero;
        public IntPtr NativeHandle { get { return m_NativeHandle; } }

        #region Interface Structures

        public class NativeStruct
        {
            public IntPtr NativeHandle { get; internal set; }
        }

        public class NetPrivate : NativeStruct
        {
            public string IP { get { return Marshal.PtrToStringAnsi(NativeIP(NativeHandle)); } }
            public int Port { get { return NativePort(NativeHandle); } }

            #region Native interface 
            [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NetPrivate_NativeIP", CharSet = CharSet.Auto)]
            static extern IntPtr NativeIP(IntPtr nativeHandle);

            [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NetPrivate_NativePort", CharSet = CharSet.Auto)]
            static extern int NativePort(IntPtr nativeHandle);
            #endregion
        };


        public class GenericServer : NativeStruct
        {
            public UInt64 GameID { get { return NativeGameID(NativeHandle); } }
            public uint UID { get { return NativeUID(NativeHandle); } }
            public string Name { get { return Marshal.PtrToStringAnsi(NativeName(NativeHandle)); } }
            public NetPrivate PrivateNet {
                get { var value = new NetPrivate() { NativeHandle = NativePrivateNet(NativeHandle) }; return value; }
            }

            #region Native interface 
            [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_GenericServer_NativeGameID", CharSet = CharSet.Auto)]
            static extern UInt64 NativeGameID(IntPtr nativeHandle);

            [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_GenericServer_NativeUID", CharSet = CharSet.Auto)]
            static extern uint NativeUID(IntPtr nativeHandle);

            [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NetPrivate_NativeName", CharSet = CharSet.Auto)]
            static extern IntPtr NativeName(IntPtr nativeHandle);

            [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_GenericServer_NativePrivateNet", CharSet = CharSet.Auto)]
            static extern IntPtr NativePrivateNet(IntPtr nativeHandle);
            #endregion
        };

        #endregion



        public SFServerConfig()
        {
            m_NativeHandle = NativeCreateConfig();
        }

        public void Dispose()
        {
            if (m_NativeHandle != IntPtr.Zero)
            {
                NativeDestroyConfig(m_NativeHandle);
                m_NativeHandle = IntPtr.Zero;
            }
        }

        public int LoadXML(string filePath)
        {
            return NativeLoadXML(NativeHandle, filePath);
        }

        public int LoadZooKeeper(SFZooKeeper zkInstance, string rootNodePath)
        {
            return NativeLoadZooKeeper(NativeHandle, zkInstance.NativeHandle, rootNodePath);
        }

        public int StoreZooKeeper(SFZooKeeper zkInstance, string rootNodePath)
        {
            return NativeStoreZooKeeper(NativeHandle, zkInstance.NativeHandle, rootNodePath);
        }

        //public delegate void FOREACH_CB_FUNCTION(GenericServer pGenericServer);

        public void ForEachServer(Action<SFServerConfig.GenericServer> cbFunc)
        {
            NativeForEachServer(NativeHandle, (IntPtr nativeGenericServer) =>
            {
                GenericServer template = new GenericServer();
                template.NativeHandle = nativeGenericServer;
                cbFunc(template);
            });
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
        
        [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NativeCreateConfig", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateConfig();


        [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NativeDestroyConfig", CharSet = CharSet.Auto)]
        static extern int NativeDestroyConfig(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NativeLoadXML", CharSet = CharSet.Auto)]
        static extern int NativeLoadXML(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string filePath);

        [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NativeLoadZooKeeper", CharSet = CharSet.Auto)]
        static extern int NativeLoadZooKeeper(IntPtr nativeHandle, IntPtr nativeHandleZooKeeper, [MarshalAs(UnmanagedType.LPStr)] string filePath);

        [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NativeStoreZooKeeper", CharSet = CharSet.Auto)]
        static extern int NativeStoreZooKeeper(IntPtr nativeHandle, IntPtr nativeHandleZooKeeper, [MarshalAs(UnmanagedType.LPStr)] string filePath);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void NATIVE_FOREACH_CB_FUNCTION(IntPtr nativeGenericServer);

        [DllImport(NativeDLLName, EntryPoint = "SFServerConfig_NativeForEachServer", CharSet = CharSet.Auto)]
        static extern void NativeForEachServer(IntPtr nativeHandle, NATIVE_FOREACH_CB_FUNCTION cbFunc);


        #endregion
    }
}


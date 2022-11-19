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

    public class OnlineAPIClient : SFObject
    {
        public delegate void delOnRecv(string APIName, string resultPayload);

        public delOnRecv OnRecv { get; set; }

        public OnlineAPIClient()
        {
            NativeHandle = NativeCreateOnlineAPIClient();
        }

        public Result Initialize(string serverAddress, int port, string accessKey)
        {
            var res = NativeInitialize(NativeHandle, serverAddress, port, accessKey);
            return new Result((int)res);
        }

        public void TickUpdate()
        {
            NativeTickUpdate(NativeHandle, OnRecvCallback);
        }

        void OnRecvCallback(string APIName, string resultPayload)
        {
            if (OnRecv != null)
                OnRecv(APIName, resultPayload);
        }

        public void RequestServiceStatus()
        {
            Native
        }

        public void RequestServerNotice()
        {

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
        public delegate void RECV_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string APIName, [MarshalAs(UnmanagedType.LPStr)] string resultPayload);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeCreate", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateOnlineAPIClient();

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeInitialize", CharSet = CharSet.Auto)]
        static extern Int32 NativeInitialize(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string serverAddress, int port, [MarshalAs(UnmanagedType.LPStr)] string accessKey);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeTickUpdate", CharSet = CharSet.Auto)]
        static extern Int32 NativeTickUpdate(IntPtr nativeHandle, RECV_FUNCTION recvFunction);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeRequestServiceStatus", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequestServiceStatus(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeRequestServerNotice", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequestServerNotice(IntPtr nativeHandle);


        #endregion
    }
}

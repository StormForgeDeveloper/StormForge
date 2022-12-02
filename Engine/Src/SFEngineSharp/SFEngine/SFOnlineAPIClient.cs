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

        public Result Connect(string serverAddress, int port, string accessKey)
        {
            var res = NativeConnect(NativeHandle, serverAddress, port, accessKey);
            return new Result((int)res);
        }

        public void Disconnect()
        {
            NativeDisconnect(NativeHandle);
        }

        public bool IsConnected()
        {
            return NativeIsConnected(NativeHandle) != 0;
        }

        public void TickUpdate()
        {
#if UNITY_STANDALONE
			stm_Instance = this;
			NativeTickUpdate(NativeHandle, OnRecvCallbackStatic);
			stm_Instance = null;
#else
			NativeTickUpdate(NativeHandle, OnRecvCallback);
#endif
		}

#if UNITY_STANDALONE
		static OnlineAPIClient? stm_Instance = null;
		[AOT.MonoPInvokeCallback(typeof(RECV_FUNCTION))]
		static void OnRecvCallbackStatic(string APIName, string resultPayload)
        {
            if (stm_Instance != null)
            {
                stm_Instance.OnRecvCallback(APIName, resultPayload);
            }
        }
#endif

		internal void OnRecvCallback(string APIName, string resultPayload)
        {
            if (OnRecv != null)
                OnRecv(APIName, resultPayload);
        }

        public void Request(string APIName)
        {
            NativeRequest(NativeHandle, APIName);
        }

        public void RequestServiceStatus()
        {
            NativeRequestServiceStatus(NativeHandle);
        }

        public void RequestServerNotice()
        {
            NativeRequestServerNotice(NativeHandle);
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

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeConnect", CharSet = CharSet.Auto)]
        static extern Int32 NativeConnect(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string serverAddress, int port, [MarshalAs(UnmanagedType.LPStr)] string accessKey);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeDisconnect", CharSet = CharSet.Auto)]
        static extern void NativeDisconnect(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_IsConnected", CharSet = CharSet.Auto)]
        static extern Int32 NativeIsConnected(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeTickUpdate", CharSet = CharSet.Auto)]
        static extern Int32 NativeTickUpdate(IntPtr nativeHandle, RECV_FUNCTION recvFunction);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeRequest", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequest(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string APIName);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeRequestServiceStatus", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequestServiceStatus(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineAPIClient_NativeRequestServerNotice", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequestServerNotice(IntPtr nativeHandle);


        #endregion
    }
}

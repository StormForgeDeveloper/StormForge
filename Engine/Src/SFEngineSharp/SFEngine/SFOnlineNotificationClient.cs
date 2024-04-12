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

#nullable enable

namespace SF
{

    public class OnlineNotificationClient : SFObject
    {
        public delegate void delOnRecv(string APIName, string resultPayload);

        public delOnRecv OnRecv { get; set; } = (x, y) => { };

        public OnlineNotificationClient()
        {
            NativeHandle = NativeCreateOnlineNotificationClient();
        }

        public Result Connect(string env, string url, string accessKey)
        {
            var res = NativeConnect(NativeHandle, env, url, accessKey);
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
		static OnlineNotificationClient? stm_Instance = null;
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

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineNotificationClient_NativeCreate", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateOnlineNotificationClient();

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineNotificationClient_NativeConnect", CharSet = CharSet.Auto)]
        static extern Int32 NativeConnect(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string env, [MarshalAs(UnmanagedType.LPStr)] string url, [MarshalAs(UnmanagedType.LPStr)] string accessKey);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineNotificationClient_NativeDisconnect", CharSet = CharSet.Auto)]
        static extern void NativeDisconnect(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineNotificationClient_IsConnected", CharSet = CharSet.Auto)]
        static extern Int32 NativeIsConnected(IntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineNotificationClient_NativeTickUpdate", CharSet = CharSet.Auto)]
        static extern Int32 NativeTickUpdate(IntPtr nativeHandle, RECV_FUNCTION recvFunction);

        [DllImport(NativeDLLName, EntryPoint = "SFOnlineNotificationClient_NativeRequest", CharSet = CharSet.Auto)]
        static extern Int32 NativeRequest(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string APIName);


        #endregion
    }
}

#nullable restore

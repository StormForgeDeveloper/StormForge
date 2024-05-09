////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Runtime.InteropServices;

#nullable enable

namespace SF
{
    public class Engine
    {
        private IntPtr m_EngineNativeHandle;

        static bool bInitialized = false;


        /** Called when the activity is first created. */
        public Engine()
        {
            if (!bInitialized)
            {
                bInitialized = true;
                Log.InitializeEngineLog();
            }
        }

        static public System.Guid GetTitleUID()
        {
            IntPtr valuePtr = NativeGetTitleUID();
            if (valuePtr == IntPtr.Zero)
                return System.Guid.Empty;

            var bytes = new byte[16];
            Marshal.Copy(valuePtr, bytes, 0, bytes.Length);
            return new System.Guid(bytes);
        }

        static public void SetTitleUID(System.Guid uid)
        {
            NativeSetTitleUID(uid.ToByteArray());
        }

        static public string GetTitleEnv()
        {
            return Marshal.PtrToStringAnsi(NativeGetTitleEnv())??string.Empty;
        }

        static public void SetTitleEnv(string value)
        {
            NativeSetTitleEnv(value);
        }

        public void StartEngine(string processName, string logServerAddress, string logFilePrefix, UInt32 globalLogMask = 0)
        {
            var curPath = System.IO.Directory.GetCurrentDirectory();
            m_EngineNativeHandle = NativeStartEngine(processName, logServerAddress, logFilePrefix, globalLogMask);
        }

        public void StartEngineWithGraphic()
        {
            m_EngineNativeHandle = NativeStartEngine(IntPtr.Zero);
        }

        public void StopEngine()
        {
            if (m_EngineNativeHandle == IntPtr.Zero) return;

            NativeStopEngine();
            m_EngineNativeHandle = IntPtr.Zero;
        }

        // Initialize and enable telemetry module
        static public void InitializeTelemetry(string serverAddress, UInt32 clientId, string authKey)
        {
            NativeInitializeTelemetry(serverAddress, clientId, authKey);
        }

        // Initialize and enable native unhandled exception handler
        // crashShellCommand will have additional parameters when it actually called.
        // -dumpfile=<dumpfilepath>  -logfile=<logfilePath>
        static public void InitializeNativeUnhandledExceptionHandler(string crashDumpfilePrefix, string crashShellCommand)
        {
            NativeInitializeNativeUnhandledExceptionHandler(crashDumpfilePrefix, crashShellCommand);
        }

        static public void SetCrashShellCommand(string crashShellCommand)
        {
            NativeSetCrashShellCommand(crashShellCommand);
        }

        static public string GetLogFileName()
        {
            IntPtr fileNamePtr = NativeGetLogFileName();
            if (fileNamePtr != IntPtr.Zero)
            {
                string? fileName = Marshal.PtrToStringAnsi(fileNamePtr);
                if (fileName != null)
                {
                    return fileName;
                }
            }

            return string.Empty;
        }

        public void onWindowFocusChanged(bool hasFocus)
        {
            NativeFocused(hasFocus);
        }

        public void OnWindowFocusChanged(bool hasFocus)
        {
            NativeFocused(hasFocus);
        }

        public void OnWindowCreated(IntPtr winHandle)
        {
            NativeWindowCreated(winHandle);
        }

        public void OnWindowClosed(IntPtr winHandle)
        {
            NativeWindowClosed(winHandle);
        }

        public void OnWindowResized()
        {
            NativeWindowResized();
        }

        static public void ForceCrash()
        {
            NativeForceCrash();
        }


        #region Native interfaces 

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeGetTitleUID", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetTitleUID();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeSetTitleUID", CharSet = CharSet.Auto)]
        static extern void NativeSetTitleUID([MarshalAs(UnmanagedType.LPArray)] byte[] bytes);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeGetTitleEnv", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetTitleEnv();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeSetTitleEnv", CharSet = CharSet.Auto)]
        static extern void NativeSetTitleEnv([MarshalAs(UnmanagedType.LPStr)] string env);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeStartEngineWithLog", CharSet = CharSet.Auto)]
        static extern IntPtr NativeStartEngine([MarshalAs(UnmanagedType.LPStr)] string processName, [MarshalAs(UnmanagedType.LPStr)] string logServerAddress, [MarshalAs(UnmanagedType.LPStr)] string logFilePrefix, UInt32 globalLogMask);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeStartEngineWithGraphic", CharSet = CharSet.Auto)]
        static extern IntPtr NativeStartEngine(IntPtr graphicContext);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeStopEngine", CharSet = CharSet.Auto)]
        static extern void NativeStopEngine();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeInitializeTelemetry", CharSet = CharSet.Auto)]
        static extern void NativeInitializeTelemetry([MarshalAs(UnmanagedType.LPStr)] string serverAddress, UInt32 gameId, [MarshalAs(UnmanagedType.LPStr)] string authKey);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeInitializeNativeUnhandledExceptionHandler", CharSet = CharSet.Auto)]
        static extern void NativeInitializeNativeUnhandledExceptionHandler([MarshalAs(UnmanagedType.LPStr)] string crashDumpfilePrefix, [MarshalAs(UnmanagedType.LPStr)] string crashShellCommand);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeSetCrashShellCommand", CharSet = CharSet.Auto)]
        static extern void NativeSetCrashShellCommand([MarshalAs(UnmanagedType.LPStr)] string crashShellCommand);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeGetLogFileName", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetLogFileName();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeFocused", CharSet = CharSet.Auto)]
        static extern void NativeFocused(bool focused);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeWindowCreated", CharSet = CharSet.Auto)]
        static extern void NativeWindowCreated(IntPtr nativeWindowHandle);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeWindowClosed", CharSet = CharSet.Auto)]
        static extern void NativeWindowClosed(IntPtr nativeWindowHandle);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeWindowResized", CharSet = CharSet.Auto)]
        static extern void NativeWindowResized();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeForceCrash", CharSet = CharSet.Auto)]
        static extern void NativeForceCrash();

        #endregion

    }
}

#nullable restore

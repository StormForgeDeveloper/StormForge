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
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;

namespace SF
{
    public class Engine
    {
        private IntPtr m_EngineNativeHandle;

        /** Called when the activity is first created. */
        public Engine()
        {
        }

	    public void StartEngine()
        {
            m_EngineNativeHandle = NativeStartEngine();
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



        #region Native interfaces 

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeStartEngineEmpty", CharSet = CharSet.Auto)]
        static extern IntPtr NativeStartEngine();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeStartEngine", CharSet = CharSet.Auto)]
        static extern IntPtr NativeStartEngine(IntPtr context);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeStopEngine", CharSet = CharSet.Auto)]
        static extern void NativeStopEngine();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeFocused", CharSet = CharSet.Auto)]
        static extern void NativeFocused(bool focused);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeWindowCreated", CharSet = CharSet.Auto)]
        static extern void NativeWindowCreated(IntPtr nativeWindowHandle);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeWindowClosed", CharSet = CharSet.Auto)]
        static extern void NativeWindowClosed(IntPtr nativeWindowHandle);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_NativeWindowResized", CharSet = CharSet.Auto)]
        static extern void NativeWindowResized();

        #endregion

    }
}

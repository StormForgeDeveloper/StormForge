////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Object interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Runtime.InteropServices;

#nullable enable

namespace SF
{
    /// <summary>
    /// Engine object interface
    /// </summary>
    public class SFObject : IDisposable
    {
        // Native handle
        private IntPtr m_NativeHandle = IntPtr.Zero;

        // Native access handle
        public IntPtr NativeHandle { get { return m_NativeHandle; } protected set { SetNativeHandle(value); } }


	    public SFObject()
	    {
	    }

	    public SFObject(IntPtr nativeHandle)
	    {
		    m_NativeHandle = nativeHandle;
		    NativeAddReference(nativeHandle);
	    }

	    public virtual void Dispose()
	    {
            if (m_NativeHandle != IntPtr.Zero)
                NativeRelease(m_NativeHandle);
            m_NativeHandle = IntPtr.Zero;
        }

        public void SetNativeHandle(IntPtr nativeHandle)
	    {
            if (m_NativeHandle != IntPtr.Zero)
                NativeRelease(m_NativeHandle);
            m_NativeHandle = IntPtr.Zero;

            m_NativeHandle = nativeHandle;
		    if(m_NativeHandle != IntPtr.Zero)
			    NativeAddReference(nativeHandle);
	    }


        #region Native interfaces
        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //
        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif


        [DllImport(NativeDllName, EntryPoint = "SFEngine_Object_NativeAddReference", CharSet = CharSet.Auto)]
        static extern void NativeAddReference(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_Object_NativeReleaseReference", CharSet = CharSet.Auto)]
        static extern void NativeRelease(IntPtr nativeHandle);

        #endregion

    }

}

#nullable restore

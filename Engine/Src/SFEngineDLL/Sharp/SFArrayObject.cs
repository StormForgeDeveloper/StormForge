////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Array Object interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Runtime.InteropServices;

namespace SF
{
    /// <summary>
    /// Engine object interface
    /// </summary>
    public class ArrayObjectString : SFObject
    {
	    public ArrayObjectString()
            : base(NativeCreateStringArray())
	    {
	    }

        public ArrayObjectString(string[] items)
            : this()
        {
            foreach(var item in items)
            {
                AppendItem(item);
            }
        }

        public int Count
        {
            get => NativeGetCount(NativeHandle);
        }

        public void AppendItem(string item)
        {
            NativeAppendItem(NativeHandle, System.Text.Encoding.UTF8.GetBytes(item + "\0"));
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

        [DllImport(NativeDllName, EntryPoint = "SFEngine_ArrayObjectString_NativeCreateArray", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateStringArray();

        [DllImport(NativeDllName, EntryPoint = "SFEngine_ArrayObjectString_NativeGetCount", CharSet = CharSet.Auto)]
        static extern int NativeGetCount(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_ArrayObjectString_NativeAppendItem", CharSet = CharSet.Auto)]
        static extern void NativeAppendItem(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] InItem);

        [DllImport(NativeDllName, EntryPoint = "SFEngine_ArrayObjectString_NativeRemoveItem", CharSet = CharSet.Auto)]
        static extern void NativeRemoveItem(IntPtr nativeHandle, [MarshalAs(UnmanagedType.LPArray)] byte[] InItem);

        #endregion

    }

}

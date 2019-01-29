////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
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
using System.Text;

namespace SF
{
    public class FixedString
    {
        public UInt64 StringHash;


        public FixedString(UInt64 strHash)
        {
            StringHash = strHash;
        }

        public FixedString(string strValue)
        {
            StringHash = NativeAddNGetString(strValue);
        }


        public override string ToString()
        {
            return Marshal.PtrToStringAnsi(NativeGetString(StringHash));
        }

        public static UInt64 HashString(string strValue)
        {
            return NativeAddNGetString(strValue);
        }


        #region Native interfaces 

        const string NativeDLLName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDLLName, EntryPoint = "SFFixedString_AddNGetString", CharSet = CharSet.Auto)]
        static extern UInt64 NativeAddNGetString([MarshalAs(UnmanagedType.LPStr)] string strValue);

        [DllImport(NativeDLLName, EntryPoint = "SFFixedString_GetString", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetString(UInt64 strHash);


        #endregion

    }
}

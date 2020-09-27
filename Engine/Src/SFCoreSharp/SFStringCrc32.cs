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
    public struct StringCrc32
    {
        public UInt32 StringHash;


        public StringCrc32(UInt32 strHash)
        {
            StringHash = strHash;
        }

        public StringCrc32(string strValue)
        {
            StringHash = NativeAddNGetString32(strValue);
        }


        public override string ToString()
        {
            return Marshal.PtrToStringAnsi(NativeGetString32(StringHash));
        }

        public static UInt32 HashString(string strValue)
        {
            return NativeAddNGetString32(strValue);
        }

        public override int GetHashCode()
        {
            return (int)StringHash;
        }

        #region Native interfaces 

        const string NativeDLLName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDLLName, EntryPoint = "SFStringCrc_AddNGetString32", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAddNGetString32([MarshalAs(UnmanagedType.LPStr)] string strValue);
        
        [DllImport(NativeDLLName, EntryPoint = "SFStringCrc_GetString32", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetString32(UInt32 strHash);

        #endregion

    }
}

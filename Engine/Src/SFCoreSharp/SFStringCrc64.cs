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

namespace SF
{
    public class StringCrc64
    {
        public UInt64 StringHash;


        public StringCrc64(UInt64 strHash)
        {
            StringHash = strHash;
        }

        public StringCrc64(string strValue)
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

        public override int GetHashCode()
        {
            // TODO: is it enough?
            return (int)StringHash;
        }


        #region Native interfaces 

        const string NativeDLLName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDLLName, EntryPoint = "SFStringCrc_AddNGetString", CharSet = CharSet.Auto)]
        static extern UInt64 NativeAddNGetString([MarshalAs(UnmanagedType.LPStr)] string strValue);

        [DllImport(NativeDLLName, EntryPoint = "SFStringCrc_GetString", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetString(UInt64 strHash);


        #endregion

    }
}

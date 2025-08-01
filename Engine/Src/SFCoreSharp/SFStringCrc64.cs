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
            string strMarshal.PtrToStringAnsi(NativeGetString(StringHash));

            return string.IsNullOrEmpty(str) ? $"0x{StringHash.ToString("X16")}" : str;
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

        public override bool Equals(object? op)
        {
            if (op is StringCrc64)
                return this.Equals((StringCrc64)op);
            return false;
        }
        public bool Equals(StringCrc64 op)
        {
            return StringHash == op.StringHash;
        }


        public static bool operator ==(StringCrc64 op1, StringCrc64 op2) { return op1.StringHash == op2.StringHash; }
        public static bool operator !=(StringCrc64 op1, StringCrc64 op2) { return op1.StringHash != op2.StringHash; }


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

#nullable restore

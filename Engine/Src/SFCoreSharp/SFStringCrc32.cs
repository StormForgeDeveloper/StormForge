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
    public struct StringCrc32
    {
        public UInt32 StringHash;


        public StringCrc32(UInt32 strHash)
        {
            StringHash = strHash;
        }

        public StringCrc32(string? strValue)
        {
            if (!string.IsNullOrEmpty(strValue))
            {
                StringHash = NativeAddNGetString32(strValue);
            }
            else
            {
                StringHash = 0;
            }
        }


        public override string ToString()
        {
			string str = Marshal.PtrToStringAnsi(NativeGetString32(StringHash));

			return string.IsNullOrEmpty(str) ? $"0x{StringHash.ToString("X8")}" : str;
        }

        public static UInt32 HashString(string strValue)
        {
            return NativeAddNGetString32(strValue);
        }

        public override int GetHashCode()
        {
            return (int)StringHash;
        }

        public override bool Equals(object? op) 
        {
            if (op is StringCrc32)
                return this.Equals((StringCrc32)op);
            return false;
        }
        public bool Equals(StringCrc32 op)
        {
            return StringHash == op.StringHash;
        }


        public static bool operator ==(StringCrc32 op1, StringCrc32 op2) { return op1.StringHash == op2.StringHash; }
        public static bool operator !=(StringCrc32 op1, StringCrc32 op2) { return op1.StringHash != op2.StringHash; }

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

#nullable restore

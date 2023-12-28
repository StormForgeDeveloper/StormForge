////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : Utility
//	
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Text;
using System.Runtime.InteropServices;
#if UNITY_IOS
using AOT;
#endif

namespace SF
{
    public static class Util
    {
		// Get module path
        public static string GetModulePath()
	    {
            string? mobuldPath = Marshal.PtrToStringAnsi(NativeGetModulePath());
            return mobuldPath == null ? string.Empty : mobuldPath;
	    }


        public static string ToHexString(byte[] bytes)
        {
            return ToHexString(bytes, 0, bytes.Length, '\0');
        }

        public static string ToHexString(byte[] bytes, int startIndex)
        {
            return ToHexString(bytes, startIndex, bytes.Length - startIndex, '\0');
        }

        public static string ToHexString(byte[] bytes, int startIndex, int count, char separator = '\0')
        {
            StringBuilder sb = new StringBuilder(bytes.Length * 2);
            if (separator != '\0')
            {
                for (int i = 0; i < count; i++)
                {
                    var curByte = bytes[startIndex + i];

                    if (i > 0) sb.Append(separator);
                    sb.AppendFormat("{0:X2}", curByte);
                }
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    var curByte = bytes[startIndex + i];
                    sb.AppendFormat("{0:X2}", curByte);
                }
            }
            return sb.ToString();
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


        [DllImport(NativeDllName, EntryPoint = "SFUtil_NativeGetModulePath", CharSet = CharSet.Auto)]
        static extern IntPtr NativeGetModulePath();

        #endregion

    }
}




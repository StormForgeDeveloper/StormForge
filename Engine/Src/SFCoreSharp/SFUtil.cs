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

namespace SF
{
    public static class Util
    {
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
                    sb.AppendFormat("{0X2}", curByte);
                }
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    var curByte = bytes[startIndex + i];
                    sb.AppendFormat("{0X2}", curByte);
                }
            }
            return sb.ToString();
        }
    }
}




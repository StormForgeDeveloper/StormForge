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
    public static class StringCrcDB
    {
        
        public static Result LoadStringTable(string fileName)
        {
            return new Result((int)NativeLoadStringTable(fileName));
        }

        public static Result LoadStringTable(byte[] memoryBuffer)
        {
            return new Result((int)NativeLoadStringTableFromMemory(memoryBuffer.Length, memoryBuffer));
        }



        #region Native interfaces 

        const string NativeDLLName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDLLName, EntryPoint = "SFStringCrc_LoadStringTable", CharSet = CharSet.Auto)]
        static extern UInt32 NativeLoadStringTable([MarshalAs(UnmanagedType.LPStr)] string strFileName);

        [DllImport(NativeDLLName, EntryPoint = "SFStringCrc_LoadStringTableFromMemory", CharSet = CharSet.Auto)]
        static extern UInt32 NativeLoadStringTableFromMemory(Int32 dataSize, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 0)] byte[] buffer);


        #endregion

    }
}

#nullable restore

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
    public static class StringCrcDB
    {
        
        public static Result LoadStringTable(string fileName)
        {
            return new Result((int)NativeLoadStringTable(fileName));
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


        #endregion

    }
}

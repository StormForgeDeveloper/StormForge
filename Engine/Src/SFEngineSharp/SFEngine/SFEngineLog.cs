﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine Log interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;

namespace SF
{

    public abstract class EngineLog
    {

        static public void Initialize()
        {
            SF.Log.LogHandler += (level, message) =>
            {
                NativeSFLogMessage((int)level, System.Text.Encoding.UTF8.GetBytes(message + "\0"));
            };
        }

        #region Native interfaces 

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDllName, EntryPoint = "SFCSLog_LogMessage", CharSet = CharSet.Auto)]
        static extern void NativeSFLogMessage(Int32 logLevel, [MarshalAs(UnmanagedType.LPArray)] byte[] logMessage);

        #endregion

    }
}
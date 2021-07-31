////////////////////////////////////////////////////////////////////////////////
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
    public abstract class Log
    {
        public enum Level
        {
            Info,
            Warning,
            Error,
            Debug1,
            Debug2,
            Debug3,
        }

        public delegate void delLogHandler(Level level, string message);
        public static event delLogHandler LogHandler;

        static Log()
        {
        }

        static public void Info(string strFormat, params object[] args)
        {
            var message = string.Format(strFormat, args);
            LogHandler(Level.Info, message);
        }

        static public void Warning(string strFormat, params object[] args)
        {
            var message = string.Format(strFormat, args);
            LogHandler(Level.Warning, message);
        }

        static public void Error(string strFormat, params object[] args)
        {
            var message = string.Format(strFormat, args);
            LogHandler(Level.Error, message);
        }

        static public void Debug(string strFormat, params object[] args)
        {
            var message = string.Format(strFormat, args);
            LogHandler(Level.Debug1, message);
        }



    }
}

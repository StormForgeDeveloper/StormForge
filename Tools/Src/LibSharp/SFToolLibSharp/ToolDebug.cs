////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tool debug
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using System.Text;

namespace SF
{
    static public class ToolDebug
    {
        static public bool Enable_DebugLog = true;
        static public bool Enable_Warning = true;

        static ToolDebug()
        {
#if DEBUG
            Enable_DebugLog = false;
            Enable_Warning = true;
#else
            Enable_DebugLog = false;
            Enable_Warning = true;
#endif
        }

        static public void Log(string message, params object[] args)
        {
            message = string.Format("Log: " + message, args);

            System.Diagnostics.Debug.Print(message);
        }

        static public void DebugLog(string message, params object[] args)
        {
            if (!Enable_DebugLog) return;

            message = string.Format("DbgLog: " + message, args);

            System.Diagnostics.Debug.Print(message);
        }

        static public void Warning(string message, params object[] args)
        {
            if (!Enable_Warning) return;

            message = string.Format("Warning: " + message, args);
            System.Diagnostics.Debug.Print(message);
        }

        static public void Error(string message, params object[] args)
        {
            message = string.Format("Error: " + message, args);

            System.Diagnostics.Debug.Fail(message);

            StringBuilder builder = new StringBuilder();
            builder.Append(message);
            var stackTrace = new StackTrace();
            for (int iStackFrame = 1; iStackFrame < stackTrace.FrameCount; iStackFrame++)
            {
                var stackFrame = stackTrace.GetFrame(iStackFrame);
                var methodBase = stackFrame.GetMethod();
                builder.AppendFormat("\n => {0}::{1},0x{2:X},{3}", methodBase.ReflectedType.ToString(), methodBase.Name, stackFrame.GetNativeOffset(), stackFrame.GetFileLineNumber());
            }
            System.Diagnostics.Debug.Print(builder.ToString());
        }

        static public void Assert(bool bCondition)
        {
#if DEBUG
            System.Diagnostics.Debug.Assert(bCondition);
#else
            if (!bCondition) Error("Asster! ");
#endif
        }

        static public void Assert(bool bCondition, string message, params object[] args)
        {
#if DEBUG
            System.Diagnostics.Debug.Assert(bCondition);
#else
            if (!bCondition) Error("Asster! " + message, args);
#endif
        }
    }
}

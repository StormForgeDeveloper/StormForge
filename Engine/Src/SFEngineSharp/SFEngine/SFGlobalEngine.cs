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
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;

namespace SF
{
    public class GlobalEngine
    {
        static Engine stm_Instance;
        static long stm_RefCount = 0;

        public static void Start(string processName, string logServerAddress, LogMask debuggerLogMask)
        {
            Start(processName, logServerAddress, debuggerLogMask.Composited);
        }


        public static void Start(string processName, string logServerAddress = null, UInt32 debuggerLogMask = 0)
        {
            var newRefCount = Interlocked.Increment(ref stm_RefCount);
            if (newRefCount == 1)
            {
                if (stm_Instance != null)
                {
                    stm_Instance.StopEngine();
                    stm_Instance = null;
                }

                stm_Instance = new Engine();
                stm_Instance.StartEngine(processName, logServerAddress, debuggerLogMask); 

            }
        }

        public static void Stop()
        {
            if (Interlocked.Read(ref stm_RefCount) == 0)
            {
                return;
            }

            var newRefCount = Interlocked.Decrement(ref stm_RefCount);
            if (newRefCount <= 0)
            {
                stm_RefCount = 0;
                if (stm_Instance != null)
                {
                    stm_Instance.StopEngine();
                    stm_Instance = null;
                }
            }
        }

    }
}

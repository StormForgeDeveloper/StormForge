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
using System.Threading;

#nullable enable

namespace SF
{
    public class GlobalEngine
    {
        static Engine? stm_Instance = null;
        static long stm_RefCount = 0;

        public static void Start(string processName, string logServerAddress, string logFilePrefix, LogMask defaultLogMask)
        {
            Start(processName, logServerAddress, logFilePrefix, defaultLogMask.Composited);
        }


        public static void Start(string processName, string logServerAddress, string logFilePrefix, UInt32 defaultLogMask)
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
                stm_Instance.StartEngine(processName, logServerAddress, logFilePrefix, defaultLogMask); 

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

#nullable restore

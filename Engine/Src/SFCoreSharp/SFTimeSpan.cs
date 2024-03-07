////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Time utilities
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Runtime.InteropServices;

#nullable enable

namespace SF
{

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct TimeSpan
    {
        public long MilliSeconds;
        public TimeSpan(long milliseconds)
        {
            MilliSeconds = milliseconds;
        }
        public TimeSpan(int hour, int min, int second)
            : this(0, hour, min, second, 0)
        {
        }

        public TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
        {
            MilliSeconds = ((long)days * 3600 * 24 + (long)hours * 3600 + (long)minutes * 60 + seconds) * 1000 + milliseconds;
        }

        System.TimeSpan AsSystemTimeSpan()
        {
            return new System.TimeSpan(MilliSeconds);
        }
    }


}

#nullable restore

#nullable enable

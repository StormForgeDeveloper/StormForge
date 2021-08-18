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

namespace SF
{

    public class Date
    {
        public const int ReferenceYear = 2010;
        static int[] MonthDays = new int [12] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        public int Year;
        public int Month;
        public int Day;
        public int Hour;
        public int Min;
        public int Sec;

        public bool IsLeapYear
        {
            get { return IsThisLeapYear(Year); }
        }

        public Date()
        {
            Year = 0;
            Month = 0;
            Day = 0;
            Hour = 0;
            Min = 0;
            Sec = 0;
        }

        public Date(uint inTime)
        {
            SetTime(inTime);
        }

        public void SetTime( uint inTime )
        {
            // When the most significant bit is set, simple modulo operation will failed with signed type
            int time = (int)(inTime / 60);
            Sec = (int)(inTime - ((uint)time * 60));

            Min = time % 60;
            time /= 60;

            Hour = time % 24;
            time /= 24;

            int remainDays = time;
            // Calculate year from the reference year
            int year = ReferenceYear;
            for (; remainDays >= 365; year++)
            {
                if (IsThisLeapYear(year))
                {
                    if (remainDays < 366) break;
                    remainDays -= 366;
                }
                else
                {
                    remainDays -= 365;
                }
            }
            Year = year;

            // Calculate month
            int month = 0;
            for (; month < 12 && remainDays >= MonthDays[month]; month++)
            {
                remainDays -= MonthDays[month];
            }
            Month = month;

            Day = remainDays;
        }


        static public bool IsThisLeapYear(int year)
        {
            return (year % 4) == 0
                && ((year % 100) != 0 || (year % 400) == 0);
        }
    };


    // converter between time32 to DateTime
    public struct TimeUTC
    {
        // Server Reference year is 1970
        const int UTCReferenceYear = 1970;

        static private DateTime ToDateTimeMs(ulong UTCTimeMs)
        {
            DateTime origin = new DateTime(UTCReferenceYear, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
            return origin.AddMilliseconds(UTCTimeMs);
        }

        static private DateTime ToDateTimeSec(ulong UTCTimeSec)
        {
            DateTime origin = new DateTime(UTCReferenceYear, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
            return origin.AddSeconds(UTCTimeSec);
        }

        static public DateTime NowDateTime()
        {
            return DateTime.UtcNow;
        }

        static public ulong FromDateTimeMs(DateTime date)
        {
            DateTime origin = new DateTime(UTCReferenceYear, 1, 1, 0, 0, 0, 0);
            TimeSpan diff = date.ToUniversalTime() - origin;
            return (ulong)diff.TotalMilliseconds;
        }

        static public ulong FromDateTimeSec(DateTime date)
        {
            DateTime origin = new DateTime(UTCReferenceYear, 1, 1, 0, 0, 0, 0);
            TimeSpan diff = date.ToUniversalTime() - origin;
            return (ulong)diff.TotalSeconds;
        }

        static public ulong NowMs()
        {
            return FromDateTimeMs(DateTime.UtcNow);
        }

        static public ulong NowSec()
        {
            return FromDateTimeSec(DateTime.UtcNow);
        }

    };

}

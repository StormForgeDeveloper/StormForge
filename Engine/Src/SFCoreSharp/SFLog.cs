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
    public struct LogMask
    {
        public UInt32 Composited;

        public bool GetBit(int bit)
        {
            return (Composited & (1 << bit)) != 0;
        }

        public void SetBit(int bit, bool value)
        {
            Composited = (Composited & (~((UInt32)1 << bit))) | ((UInt32)(value ? 1 : 0) << bit);
        }

        // Generic trace
        public bool Factal
        {
            get => GetBit(0);
            set => SetBit(0, value);
        }
        public bool Error
        {
            get => GetBit(1);
            set => SetBit(1, value);
        }
        public bool Warning
        {
            get => GetBit(2);
            set => SetBit(2, value);
        }
        public bool Info
        {
            get => GetBit(3);
            set => SetBit(3, value);
        }

        // Module additional traces
        public bool Custom1
        {
            get => GetBit(4);
            set => SetBit(4, value);
        }
        public bool Custom2
        {
            get => GetBit(5);
            set => SetBit(5, value);
        }
        public bool Custom3
        {
            get => GetBit(6);
            set => SetBit(6, value);
        }
        public bool Custom4
        {
            get => GetBit(7);
            set => SetBit(7, value);
        }
        public bool Custom5
        {
            get => GetBit(8);
            set => SetBit(8, value);
        }
        public bool Custom6
        {
            get => GetBit(9);
            set => SetBit(9, value);
        }
        public bool Custom7
        {
            get => GetBit(10);
            set => SetBit(10, value);
        }
        public bool Custom8
        {
            get => GetBit(11);
            set => SetBit(11, value);
        }
        public bool Custom9
        {
            get => GetBit(12);
            set => SetBit(12, value);
        }
        public bool Custom10
        {
            get => GetBit(13);
            set => SetBit(13, value);
        }

        public bool Debug
        {
            get => GetBit(14);
            set => SetBit(14, value);
        }

        public bool Debug1
        {
            get => GetBit(15);
            set => SetBit(15, value);
        }

        public bool Debug2
        {
            get => GetBit(16);
            set => SetBit(16, value);
        }

        public bool Debug3
        {
            get => GetBit(17);
            set => SetBit(17, value);
        }

        public bool Debug4
        {
            get => GetBit(18);
            set => SetBit(18, value);
        }

        public bool Debug5
        {
            get => GetBit(19);
            set => SetBit(19, value);
        }

        public bool Debug6
        {
            get => GetBit(20);
            set => SetBit(20, value);
        }

        public bool Debug7
        {
            get => GetBit(21);
            set => SetBit(21, value);
        }

        public bool Debug8
        {
            get => GetBit(22);
            set => SetBit(22, value);
        }

    }



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

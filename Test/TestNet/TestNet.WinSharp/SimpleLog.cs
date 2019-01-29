using System;
using System.Windows;
using System.Windows.Controls;
using System.Collections.Generic;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;


using SF;
using Microsoft.Win32;
using System.Threading;
using System.IO;

namespace TestNet.WinSharp
{
    public class SimpleLog
    {      
        public SimpleLog(string DummyFileName)
        {
            mDummyFileName = DummyFileName;
        }

        private readonly object Locker = new object();
        private string LogPath = string.Empty;

        private string mDummyFileName = string.Empty;

        public void WriteToLog(string format, params object[] args)
        {
            string logText = string.Format(format, args);
            WriteToLog(logText);
        }

        void WriteToLog(string text)
        {
            lock (Locker)
            {
                try
                {
                    StreamWriter SW;
                    if (LogPath == string.Empty)
                    {
                        LogPath = string.Format("{0}/../logs", System.IO.Directory.GetCurrentDirectory());

                        if (!System.IO.Directory.Exists(LogPath))
                            System.IO.Directory.CreateDirectory(LogPath);

                        string FileName = DateTime.Now.ToString("dd_MM_yyyy_hh_mm_ss_") + mDummyFileName;
                        LogPath += string.Format("/{0}.log", FileName);
                    }

                    SW = File.AppendText(LogPath);
                    SW.WriteLine(string.Format("{0}, {1}", DateTime.Now.ToString("yyyy_MM_dd_hh_mm_ss"), text));
                    SW.Close();
                    SW.Dispose();
                }
                catch (Exception e)
                {
                    System.Diagnostics.Debug.Print(e.Message);
                    return;
                }
            }
        }
    }
}

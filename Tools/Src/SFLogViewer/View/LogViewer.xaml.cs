using System;
using System.IO.Compression;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Threading;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using SF;
using System.Collections.Specialized;
using System.IO;

namespace SFLogViewer.View
{
    public class LogEntry : PropertyChangedBase
    {
        public DateTime DateTime { get; set; }

        public Int64 Index { get; set; }

        public string Message { get; set; }
    }


    public class LogEntryCollection : List<LogEntry>, INotifyCollectionChanged
    {
        public event NotifyCollectionChangedEventHandler CollectionChanged;

        public void FireChangedEvent(NotifyCollectionChangedEventArgs eventArg)
        {
            CollectionChanged.Invoke(this, eventArg);
        }
    }

    /// <summary>
    /// Interaction logic for LogViewer.xaml
    /// </summary>
    public partial class LogViewer : Window
    {
        DispatcherTimer m_TickTimer;
        bool m_ReadThreadTerminate;
        System.Threading.Thread m_ReadThread;

        int m_MaxEntries = 10000;
        int m_InitialBacklog = 100;

        public ObservableCollection<LogEntry> m_LogEntries { get; set; }

        StreamDBConsumer m_StreamDB;


        public LogViewer(string logServerAddress, string topic, int initialBacklog = 100)
        {
            InitializeComponent();

            DataContext = m_LogEntries = new ObservableCollection<LogEntry>();

            AddHotKeys();

            GlobalEngine.Start("SFLogViewer", string.Empty, string.Empty, 0);

            m_InitialBacklog = initialBacklog;
            this.Title = string.Format("{0},{1}", logServerAddress, topic);

            m_StreamDB = new StreamDBConsumer();
            m_StreamDB.Initialize(logServerAddress, topic);

            m_StreamDB.RequestData(m_StreamDB.ToOffsetFromTail(m_InitialBacklog));

            m_TickTimer = new DispatcherTimer();
            m_TickTimer.Tick += new EventHandler(Timer_Tick);
            m_TickTimer.Interval = new TimeSpan(0, 0, 0, 0, 200);
            m_TickTimer.Start();

            m_ReadThreadTerminate = false;
            m_ReadThread = new System.Threading.Thread(ThreadRun);
            m_ReadThread.Start();
        }

        private void AddHotKeys()
        {
            RoutedCommand firstSettings = new RoutedCommand();
            firstSettings.InputGestures.Add(new KeyGesture(Key.F, ModifierKeys.Control));
            CommandBindings.Add(new CommandBinding(firstSettings, OnShowFind));
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);

            m_ReadThreadTerminate = true;
            m_ReadThread.Join();

            m_TickTimer.Stop();
            m_TickTimer = null;

            GlobalEngine.Stop();

        }

        private void OnShowFind(object sender, ExecutedRoutedEventArgs e)
        {
            //FindDialogBox dlg = new FindDialogBox(this.documentTextBox);

            //// Configure the dialog box
            //dlg.Owner = this;
            //dlg.TextFound += new TextFoundEventHandler(dlg_TextFound);

            //// Open the dialog box modally
            //dlg.Show();
        }


        private bool AutoScroll = true;
        private void ScrollViewer_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            // User scroll event : set or unset auto scroll mode
            if (e.ExtentHeightChange == 0)
            {   // Content unchanged : user scroll event
                if ((e.Source as ScrollViewer).VerticalOffset == (e.Source as ScrollViewer).ScrollableHeight)
                {   // Scroll bar is in bottom
                    // Set auto scroll mode
                    AutoScroll = true;
                }
                else
                {   // Scroll bar isn't in bottom
                    // Unset auto scroll mode
                    AutoScroll = false;
                }
            }

            // Content scroll event : auto scroll eventually
            if (AutoScroll && e.ExtentHeightChange != 0)
            {   // Content changed and auto scroll mode set
                // Auto scroll
                (e.Source as ScrollViewer).ScrollToVerticalOffset((e.Source as ScrollViewer).ExtentHeight);
            }
        }

        void TickStreamDB()
        {
            if (m_StreamDB == null)
                return;

            DateTime messageTimeStamp;
            Int64 messageOffset;
            byte[] recordData;
            while (m_StreamDB.PollData(out messageOffset, out messageTimeStamp, out recordData).IsSucceeded)
            {
                // skip null data
                if (recordData == null || recordData.Length == 0)
                    continue;

                LogEntry newLogEntry = new LogEntry();
                newLogEntry.DateTime = messageTimeStamp;
                newLogEntry.Index = messageOffset;
                newLogEntry.Message = Encoding.UTF8.GetString(recordData);
                AddEntry(newLogEntry);
            }
        }

        readonly static byte[] BinaryModeMagic = new byte[4] { (byte)'S', (byte)'F', (byte)'C', 0 };


        static byte[] Decompress(byte[] compressedData, int uncompressedSize, int offset = 0)
        {
            // https://stackoverflow.com/questions/185690/how-to-inflate-a-file-with-zlib-net/33855097#33855097
            // Skipping Zlib header 2bytes 0x78, 0x9c so that I can use .Net lib
            offset += 2;
            byte[] buffer = new byte[uncompressedSize];
            int count = compressedData.Length - offset;
            using (var msi = new MemoryStream(compressedData, offset, count))
            {
                using (var gs = new DeflateStream(msi, CompressionMode.Decompress))
                {
                    gs.Read(buffer, 0, buffer.Length);
                }

                return buffer;
            }
        }

        object m_NewLogEntryLock = new object();
        List<LogEntry> m_NewLogEntries;
        void ReadThreadTick()
        {
            if (m_StreamDB == null)
                return;

            lock (m_NewLogEntryLock)
            {
                if (m_NewLogEntries == null)
                    m_NewLogEntries = new List<LogEntry>();

                DateTime messageTimeStamp;
                Int64 messageOffset;
                byte[] recordData;
                while (m_StreamDB.PollData(out messageOffset, out messageTimeStamp, out recordData).IsSucceeded)
                {
                    // skip null data
                    if (recordData == null || recordData.Length == 0)
                        continue;

                    var isBinary = recordData[0] == BinaryModeMagic[0] && recordData[1] == BinaryModeMagic[1] && recordData[2] == BinaryModeMagic[2] && recordData[3] == BinaryModeMagic[3];
                    if (isBinary)
                    {
                        int uncompressedSize = (int)recordData[4] | ((int)recordData[5] << 8) | ((int)recordData[6] << 16) | ((int)recordData[7] << 24);
                        var decompressedData = Decompress(recordData, uncompressedSize, 8);

                        var logText = Encoding.UTF8.GetString(decompressedData);
                        var logs = logText.Split('\n');

                        foreach(var log in logs)
                        {
                            if (string.IsNullOrEmpty(log))
                                continue;

                            LogEntry newLogEntry = new LogEntry();
                            newLogEntry.DateTime = messageTimeStamp;
                            newLogEntry.Index = messageOffset;
                            newLogEntry.Message = log;
                            m_NewLogEntries.Add(newLogEntry);
                        }
                    }
                    else if (recordData[3] == '\0')
                    {
                        // skip. probably version mismatch
                    }
                    else
                    {
                        LogEntry newLogEntry = new LogEntry();
                        newLogEntry.DateTime = messageTimeStamp;
                        newLogEntry.Index = messageOffset;
                        newLogEntry.Message = Encoding.UTF8.GetString(recordData);
                        m_NewLogEntries.Add(newLogEntry);
                    }

                }
            }
        }

        void ThreadRun()
        {
            while(!m_ReadThreadTerminate)
            {
                System.Threading.Thread.Sleep(10);
                ReadThreadTick();
            }
        }

        void UITickUpdate()
        {
            if (m_NewLogEntries == null || m_NewLogEntries.Count == 0)
                return;

            List<LogEntry> newLogEntries;
            lock (m_NewLogEntryLock)
            {
                newLogEntries = m_NewLogEntries;
                m_NewLogEntries = new List<LogEntry>();
            }

            //NotifyCollectionChangedEventArgs eventArg = null;

            if (newLogEntries.Count > m_MaxEntries)
            {
                newLogEntries.RemoveRange(0, newLogEntries.Count - m_MaxEntries);

                m_LogEntries.Clear();
                //eventArg = new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Reset);
            }
            else
            {
                var newTotal = m_LogEntries.Count + newLogEntries.Count;
                if (newTotal > m_MaxEntries)
                {
                    var removeCount = newTotal - (m_MaxEntries * 0.9);
                    for (int iIndex = 0; iIndex < removeCount; iIndex++)
                        m_LogEntries.RemoveAt(0);
                }
            }

            foreach (var logEntry in newLogEntries)
            {
                m_LogEntries.Add(logEntry);
            }
            //m_LogEntries.CopyTo(newLogEntries.ToArray(), m_LogEntries.Count);
            //m_LogEntries.FireChangedEvent(eventArg);
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            UITickUpdate();
            //TickStreamDB();

            // Test data
            //AddRandomEntry();
        }

        void AddEntry(LogEntry newLogEntry)
        {
            m_LogEntries.Add(newLogEntry);
            var threshold = Math.Max(1, (int)(m_MaxEntries * 0.1));
            if (m_LogEntries.Count > (m_MaxEntries + threshold))
            {
                for (int iIndex = 0; iIndex < threshold; iIndex++)
                    m_LogEntries.RemoveAt(0);
            }
        }

        #region Generate test data
        private string TestData = @"I should start selling these WPF samples instead of giving them out for free.
DataTemplates for each kind of LogEntry type.These give you the ability to customize as much as you want.I only implemented 2 kinds of LogEntries (basic and nested), but you get the idea.You may subclass LogEntry as much as you need.You may even support rich text or images.
Expandable (Nested) Items. You can implement filtering, etc by using a CollectionView. WPF Rocks, just copy and paste my code in a File -> New -> WPF Application and see the results for yourself.";
        private List<string> words = new List<string>();
        private int maxword;
        private int index;
        private System.Random random;
        private void AddRandomEntry()
        {
            if (random == null)
            {
                random = new Random();
                words.AddRange(TestData.Split(' '));
                maxword = words.Count - 1;

                Enumerable.Range(0, m_MaxEntries)
                          .ToList()
                          .ForEach(x => AddEntry(GetRandomEntry()));
            }

            AddEntry(GetRandomEntry());
            //Dispatcher.BeginInvoke((Action)(() => AddEntry(GetRandomEntry())));
        }

        private LogEntry GetRandomEntry()
        {
            return new LogEntry
            {
                Index = index++,
                DateTime = DateTime.Now,
                Message = string.Join(" ", Enumerable.Range(5, random.Next(10, 50))
                                                     .Select(x => words[random.Next(0, maxword)])),
            };

        }
        #endregion
    }
}

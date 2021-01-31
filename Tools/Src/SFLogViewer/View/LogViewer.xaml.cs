using System;
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

namespace SFLogViewer.View
{
    public class LogEntry : PropertyChangedBase
    {
        public DateTime DateTime { get; set; }

        public Int64 Index { get; set; }

        public string Message { get; set; }
    }


    /// <summary>
    /// Interaction logic for LogViewer.xaml
    /// </summary>
    public partial class LogViewer : Window
    {
        DispatcherTimer m_TickTimer;

        int m_MaxEntries = 1000;

        public ObservableCollection<LogEntry> m_LogEntries { get; set; }

        StreamDBConsumer m_StreamDB;


        public LogViewer(string logServerAddress, string topic)
        {
            InitializeComponent();

            DataContext = m_LogEntries = new ObservableCollection<LogEntry>();

            AddHotKeys();

            GlobalEngine.Start("SFLogViewer");

            m_StreamDB = new StreamDBConsumer();
            m_StreamDB.Initialize(logServerAddress, topic);

            m_StreamDB.RequestData(m_StreamDB.ToOffsetFromTail(m_MaxEntries));


            m_TickTimer = new DispatcherTimer();
            m_TickTimer.Tick += new EventHandler(Timer_Tick);
            m_TickTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            m_TickTimer.Start();
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

        private void Timer_Tick(object sender, EventArgs e)
        {
            TickStreamDB();

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

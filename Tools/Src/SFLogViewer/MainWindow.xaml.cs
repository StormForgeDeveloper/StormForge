using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using SF;

namespace SFLogViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DispatcherTimer m_TickTimer;

        StreamDBDirectory m_StreamDirectory;

        public MainWindow()
        {
            var logServerAddress = SavedValueRegistry.ReadValue("LogServerAddress", "");

            var processName = SavedValueRegistry.ReadValue("ProcessName", "SFLogViewer");
            SavedValueRegistry.SaveValue("ProcessName", processName);

            InitializeComponent();

            txtLogServerAddress.Text = logServerAddress;

            var backLog = SavedValueRegistry.ReadValue("InitialBacklog", "100");
            textBacklog.Text = backLog;

            GlobalEngine.Start("SFLogViewer");

            RefreshChannelList();

            m_TickTimer = new DispatcherTimer();
            m_TickTimer.Tick += new EventHandler(Timer_Tick);
            m_TickTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            m_TickTimer.Start();

        }

        void RefreshChannelList()
        {
            var logServerAddress = txtLogServerAddress.Text;
            if (string.IsNullOrEmpty(logServerAddress))
                return;

            SavedValueRegistry.SaveValue("LogServerAddress", logServerAddress);


            if (m_StreamDirectory == null || m_StreamDirectory.ServerAddress != logServerAddress)
            {
                if (m_StreamDirectory != null)
                    m_StreamDirectory.Dispose();

                m_StreamDirectory = new StreamDBDirectory(StreamDBDirectory.DirectoryMode.Broker);
                m_StreamDirectory.Initialize(logServerAddress);
            }

            m_StreamDirectory.RequestStreamList();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);

            m_TickTimer.Stop();
            m_TickTimer = null;

            if (m_StreamDirectory != null)
                m_StreamDirectory.Dispose();
            m_StreamDirectory = null;

            GlobalEngine.Stop();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            if (m_StreamDirectory != null)
            {
                SFMessage message = null;

                do
                {
                    message = m_StreamDirectory.PollMessageData();
                    if (message != null)
                    {
                        if (message.GetMessageID() == SF.Net.MessageIDPlayInstance.GetStreamListRes)
                        {
                            var requestResult = message.GetValue<Result>("Result");
                            var streamNames = message.GetValue<string[]>("StreamNames");

                            Array.Sort(streamNames);

                            listLogChannels.BeginInit();
                            listLogChannels.Items.Clear();

                            foreach (var streamName in streamNames)
                            {
                                listLogChannels.Items.Add(streamName);
                            }

                            listLogChannels.EndInit();

                        }
                    }
                } while (message != null);
            }
        }

        private void OnChannel_DoubleClick(object sender, MouseButtonEventArgs e)
        {
            var logServerAddress = txtLogServerAddress.Text;
            if (string.IsNullOrEmpty(logServerAddress))
                return;

            var selectedChannelItem = listLogChannels.SelectedItem;
            if (selectedChannelItem == null || string.IsNullOrEmpty(selectedChannelItem.ToString()))
                return;

            UInt32 InitialBackLog = 100;
            if (UInt32.TryParse(textBacklog.Text, out InitialBackLog))
            {
                SavedValueRegistry.SaveValue("InitialBacklog", InitialBackLog.ToString());
            }

            var logChannel = selectedChannelItem.ToString();

            var logView = new View.LogViewer(logServerAddress, logChannel, (int)InitialBackLog);
            logView.Show();
        }

        private void OnBtnRefresh_Clicked(object sender, RoutedEventArgs e)
        {
            RefreshChannelList();
        }
    }

}

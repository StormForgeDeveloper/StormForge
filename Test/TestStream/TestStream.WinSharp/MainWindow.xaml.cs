using System;
using System.Collections.Generic;
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



namespace TestStream.WinSharp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        SF.StreamDBDirectory m_Directory;
        SF.StreamDBProducer m_Producer;
        SF.StreamDBConsumer m_Consumer;

        public MainWindow()
        {
            InitializeComponent();

            SF.GlobalEngine.Start("TestNet.WinSharp");

            SF.ServerAddressRegistry.ReadServerAddress();
            var serverAddresses = SF.ServerAddressRegistry.GetServerAddresses();
            if (serverAddresses.Count > 0)
                textStreamDBServer.Text = serverAddresses[0];
        }

        protected override void OnClosed(EventArgs e)
        {
            SF.GlobalEngine.Stop();

            SF.ServerAddressRegistry.SaveServerAddressToRegistry();

            base.OnClosed(e);
        }

        void PrintStatus(string text)
        {
            textOutput.Text = textOutput.Text + (text + "\n");
        }

        void PrintStatus(string format, params object[] args)
        {
            PrintStatus(string.Format(format, args));
        }

        private void OnRefreshStreamList(object sender, RoutedEventArgs e)
        {
            var serverAddress = textStreamDBServer.Text;
            if (m_Directory == null)
            {
                m_Directory = new SF.StreamDBDirectory(SF.StreamDBDirectory.DirectoryMode.Broker);
                var result = m_Directory.Initialize(serverAddress);
            }

            SF.ServerAddressRegistry.AddServerAddress(serverAddress);

            m_Directory.RequestStreamList();

            // TODO:
            //comboStreamList.Items.Clear();
            //var topicCount = m_Directory.GetTopicCount();
            //for (int iTopic = 0; iTopic < topicCount; iTopic++)
            //{
            //    string topic = m_Directory.GetTopic(iTopic);
            //    comboStreamList.Items.Add(topic);
            //}

        }

        void TickUpdateStreamDirectory()
        {
            if (m_Directory == null)
                return;

            var msgData = m_Directory.PollMessageData();
            for (; msgData != null; msgData = m_Directory.PollMessageData())
            {
                switch (msgData.GetMessageID())
                {
                    case SF.Net.MessageIDPlayInstance.CreateStreamRes:
                        //Debug.Log("CreateStreamRes {0}, {1}", msgData.GetValue<Result>("Result").ToString(), msgData.GetValue<string>(StreamName));
                        break;
                    case SF.Net.MessageIDPlayInstance.DeleteStreamRes:
                        //Debug.Log("DeleteStreamRes {0}, {1}", msgData.GetValue<Result>("Result").ToString(), msgData.GetValue<string>(StreamName));
                        break;
                }
            }
        }

        //void TickUpdateStreamConsumer()
        //{
        //    if (m_Consumer == null)
        //        return;

        //    m_Consumer += Time.deltaTime;
        //    var expectedFrame = (int)(m_StreamCurTime * m_StreamFPS);
        //    if (expectedFrame > m_StreamCurFrame)
        //    {
        //        byte[] frameData;
        //        var result = m_Consumer.PollData(out frameData);
        //        if (result == SF.ResultCode.END_OF_STREAM)
        //        {
        //            Debug.Log(string.Format("EndOfStream:{0}", m_StreamConsumer.GetTopic()));
        //        }
        //        else if (result == SF.ResultCode.SUCCESS && frameData != null)
        //        {
        //            m_StreamCurFrame++;
        //            Debug.Log(string.Format("RecvStream: frame:{0}, size:{1}", m_StreamCurFrame, frameData.Length));
        //        }
        //        else
        //        {
        //            // data is not ready yet
        //        }
        //    }
        //}

        private void OnNewStream(object sender, RoutedEventArgs e)
        {
            var streamName = textStreamName.Text;
            if (string.IsNullOrEmpty(streamName))
                return;

            PrintStatus("Producing new data stream:{0}", streamName);

            if (m_Producer != null && m_Producer.GetTopic() != streamName)
            {
                m_Producer.Dispose();
                m_Producer = null;
            }

            if (m_Producer == null)
            {
                m_Producer = new SF.StreamDBProducer();
                m_Producer.Initialize(textStreamDBServer.Text, streamName);
            }

            System.Random random = new System.Random();
            byte[] data = new byte[128 + random.Next()%128];
            for (int iIndex = 0; iIndex < data.Length; iIndex++)
            {
                data[iIndex] = (byte)random.Next();
            }
            
            m_Producer.SendRecord(data);
        }

        private void OnStreamSelected(object sender, SelectionChangedEventArgs e)
        {
            if (comboStreamList.SelectedItem == null)
                return;

            var streamName = comboStreamList.SelectedItem.ToString();
            if (string.IsNullOrEmpty(streamName))
                return;


            if (m_Consumer != null)
            {
                m_Consumer.Dispose();
                m_Consumer = null;
            }
            m_Consumer = new SF.StreamDBConsumer();
            m_Consumer.Initialize(textStreamDBServer.Text, streamName);

            PrintStatus("Consumer requesting data:{0}", streamName);

            m_Consumer.RequestData(0);
            do
            {
                byte[] recordData;
                Int64 messageOffset;
                DateTime messageTimeStamp;
                var result = m_Consumer.PollData(out messageOffset, out messageTimeStamp, out recordData);
                if (result.IsFailed)
                    break;
                else 
                {
                    if (result == SF.ResultCode.END_OF_STREAM)
                    {
                        // finished
                        break;
                    }

                    if (recordData != null)
                        PrintStatus("ReceivedData size:{0}", recordData.Length);
                }



            } while (true);


            PrintStatus("Consumer data finished");
        }
    }
}

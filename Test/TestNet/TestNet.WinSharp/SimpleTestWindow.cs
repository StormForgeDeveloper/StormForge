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

namespace TestNet.WinSharp
{
    public class SimpleTestWindow
    {            
        const int DataTestSize = 1024;

        public string SimpleTestGameID = "MyTownHero";
        SimpleTestUser m_NetTestUser = new SimpleTestUser();

        public void InitSimpleTest()
        {           
            MainWindow.InitGameIDComboBox(MainWindow.Instance.comboBoxGameID, SimpleTestGameID);
            MainWindow.InitIPAdressComboBox(MainWindow.Instance.comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(0));
        
            m_NetTestUser.InitEngine();
            m_NetTestUser.SetPrintHanlde(PrintStatus);

            UpdateUI();
        }

        void PrintStatus(string text)
        {
            MainWindow.Instance.textOutput.Text = MainWindow.Instance.textOutput.Text + ("\n" + text);
        }

        void PrintStatus(string format, params object[] args)
        {
            PrintStatus(string.Format(format, args));
        }

        void UpdateUI()
        {
            MainWindow.Instance.comboBoxGameID.SelectedItem = 
                ServerAddressRegistry.ReadGameID(100,SimpleTestGameID).ToString();

            UpdateLoginIDUI();
        }

        void UpdateLoginIDUI()
        {
            MainWindow.Instance.comboBoxLoginID.Items.Clear();
            foreach (var loginID in ServerAddressRegistry.LoginIDs)
                MainWindow.Instance.comboBoxLoginID.Items.Add(loginID);

            if (ServerAddressRegistry.HasAddresses)
                MainWindow.Instance.comboBoxLoginID.SelectedIndex = 0;
            else
                MainWindow.Instance.comboBoxLoginID.SelectedIndex = -1;
        }

        void UpdateServerAddressUI()
        {
            MainWindow.InitIPAdressComboBox(MainWindow.Instance.comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(0));
            //ServerAddressRegistry.SaveServerAddressToRegistry();
        }

        public void btnUpdateRanking_Click(object sender, RoutedEventArgs e)
        {
            if (m_NetTestUser.m_Login == null)
                return;

            Random rand = new Random();

            //m_Login.UpdateMyScoreCmd((ulong)rand.Next() % 5000, RankingType.World, 10);
            ulong score = (ulong)rand.Next() % 5000;
            PrintStatus("UpdateMyScoreCmd score:{0}", score);
            m_NetTestUser.m_Login.UpdateMyScoreCmd(score, RankingType.World, 10);
        }

        public void btnMatching_Click(object sender, RoutedEventArgs e)
        {
            if (m_NetTestUser.m_Game == null)
                return;

            m_NetTestUser.m_Game.RequestGameMatchCmd(0, 4, (byte)PlayerRole.None);
        }

        public void OnClearLog(object sender, RoutedEventArgs e)
        {
            MainWindow.Instance.textOutput.Text = "";
        }

        public void OnDataTestClick(object sender, RoutedEventArgs e)
        {
            if (m_NetTestUser.m_Login == null)
                return;

            var data = new byte[DataTestSize];
            for (int iData = 0; iData < DataTestSize; iData++)
            {
                data[iData] = (byte)iData;
            }
            m_NetTestUser.m_Login.DataTestCmd(data);

            m_NetTestUser.m_Login.DebugPrintALLRankingCmd("RankData");

        }

        public void OnDisconnectClick()
        {
            m_NetTestUser.CloseAllConnections();
        }

        public void btnLogin_Click(object sender, RoutedEventArgs e)
        {
            string loginID = MainWindow.Instance.comboBoxLoginID.Text;
            
            loginID = loginID.Trim();
            if (string.IsNullOrEmpty(loginID))
            {
                MessageBox.Show("Enter valid Login ID");
                return;
            }
           
            if( ServerAddressRegistry.AddLoginID(loginID))
                 UpdateLoginIDUI();

            OnClearLog(sender, e);
            m_NetTestUser.CloseAllConnections();
            
            m_NetTestUser.m_LoginID = loginID;

            SimpleTestGameID = MainWindow.GetGameIDFromUI(MainWindow.Instance.comboBoxGameID);
            m_NetTestUser.gameID = SimpleTestGameID;

            ServerAddressRegistry.SaveGameID(100, SimpleTestGameID);

            NetAddress serverAddress = MainWindow.Instance.GetServerAddressFromUI(0, MainWindow.Instance.comboBoxIPAddress, UpdateServerAddressUI);

            m_NetTestUser.RunConnect(serverAddress);
        }


        public void OnClosed(EventArgs e)
        {
            m_NetTestUser.CloseAllConnections();
            m_NetTestUser.Dispose();
        }
    }
}

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
    public class StressTestWindowRank
    {            
        public string SimpleTestGameID = "MyTownHero";
        public string RankTestUserID = "Good41";

        StressTest_RankTestUser m_RankTestUser = new StressTest_RankTestUser();

        public void InitStressTest()
        {           
            MainWindow.InitGameIDComboBox(MainWindow.Instance.RankTest_GameID, SimpleTestGameID);
            MainWindow.InitGameIDComboBox(MainWindow.Instance.RankDataUserIDs, RankTestUserID);

            //MainWindow.InitIPAdressComboBox(MainWindow.Instance.comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(0));
            m_RankTestUser.InitEngine();
            m_RankTestUser.SetPrintHanlde(PrintStatus);

            m_RankingConnectedUser = 0;

            UpdateUI();
        }

        void PrintStatus(string text)
        {
            MainWindow.Instance.textOutput1.Text = MainWindow.Instance.textOutput1.Text + ("\n" + text);
        }

        void PrintStatus(string format, params object[] args)
        {
            PrintStatus(string.Format(format, args));
        }

        void UpdateUI()
        {
     //       MainWindow.Instance.comboBoxGameID.SelectedItem = 
     //        ServerAddressRegistry.ReadGameID(100,SimpleTestGameID).ToString();

            UpdateLoginIDUI();
        }

        void UpdateLoginIDUI()
        {
            MainWindow.Instance.RankDataUserIDs.Items.Clear();
            foreach (var loginID in ServerAddressRegistry.LoginIDs)
                MainWindow.Instance.RankDataUserIDs.Items.Add(loginID);

            if (ServerAddressRegistry.HasAddresses)
                MainWindow.Instance.RankDataUserIDs.SelectedIndex = 0;
           else
                MainWindow.Instance.RankDataUserIDs.SelectedIndex = -1;
        }

        void UpdateServerAddressUI()
        {
            MainWindow.InitIPAdressComboBox(MainWindow.Instance.stress_comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(0));
            ServerAddressRegistry.SaveServerAddressToRegistry();
        }
    
        public bool IsLogin()
        {
            if (m_RankTestUser.m_Login == null)
                return false;

            return m_RankTestUser.IsLogin();
        }

        public void ReqSaveRankData(string FileName)
        {
            if (m_RankTestUser.m_Login == null)
                return;

            PrintStatus("Request Save Rank Data!! fName = {0}", FileName);
            m_RankTestUser.SaveRankData(FileName);
        }

        public void StartTest()
        {
            string loginID = MainWindow.Instance.RankDataUserIDs.Text;

            loginID = loginID.Trim();
            if (string.IsNullOrEmpty(loginID))
            {
                MessageBox.Show("Enter valid Login ID");
                return;
            }

            if (ServerAddressRegistry.AddLoginID(loginID))
                UpdateLoginIDUI();

            MainWindow.Instance.textOutput1.Text = "";
            m_RankTestUser.CloseAllConnections();

            m_RankTestUser.m_LoginID = loginID;

            SimpleTestGameID = MainWindow.GetGameIDFromUI(MainWindow.Instance.RankTest_GameID);
            m_RankTestUser.gameID = SimpleTestGameID;

            ServerAddressRegistry.SaveGameID(100, SimpleTestGameID);

            NetAddress serverAddress = MainWindow.Instance.GetServerAddressFromUI(0, MainWindow.Instance.stress_comboBoxIPAddress, UpdateServerAddressUI);

            m_RankTestUser.CloseAllConnections();
            m_RankTestUser.Dispose();

            m_RankingConnectedUser = 0;

            m_RankTestUser.RunConnect(serverAddress,
                   (StressTest_RankTestUser user) =>
                    {                       
                        m_RankingConnectedUser++;
                        UpdateRankingTestStatueUI();
                    },
                    (StressTest_RankTestUser user, SF.Net.SendMessageLogin l) =>
                    {
                        if (l != null)
                            m_RankingConnectedUser--;

                        UpdateRankingTestStatueUI();
                       
                    });
        }

        public int m_RankingConnectedUser = 0;
        public delegate void UpdateTextLabel_Delegate();
        public void UpdateRankingTestStatueUI()
        {
            MainWindow.Instance.UpdateTotalUserCount();
            MainWindow.Instance.L_RankingConnectedUser.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_RankingConnectedUser.Content = m_RankingConnectedUser.ToString();
            }));
        }

        public void OnClosed()
        {
            m_RankTestUser.CloseAllConnections();
            m_RankTestUser.Dispose();
        }
    }
}

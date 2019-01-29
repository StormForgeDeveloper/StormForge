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
using System.Windows.Threading;

using SF;
using Microsoft.Win32;

namespace TestNet.WinSharp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {   
     
        public StressTestWindow mStressTestWin = new StressTestWindow();
        static readonly string RegistryKeyName = @"SOFTWARE\StormForge\SecondTest";

        public static MainWindow Instance { get; private set; }
        Engine m_Engine = null;

        public MainWindow()
        {
            InitializeComponent();

            Instance = this;

            m_Engine = new Engine();
            m_Engine.StartEngine();


            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
            }

            string IniFilePath = string.Format("{0}/default.ini", System.IO.Directory.GetCurrentDirectory());

            if (!ServerAddressRegistry.ReadServerAddress(0))
                ServerAddressRegistry.SetDefaultServerAddress(0, IniFilePath);

            if (!ServerAddressRegistry.ReadServerAddress(1))
                ServerAddressRegistry.SetDefaultServerAddress(1, IniFilePath);

            ServerAddressRegistry.ReadLoginID();

           int MaxUserValue = 400;
           if( ServerAddressRegistry.ReadMaxUser(IniFilePath, ref MaxUserValue))
           {              
                StressTestWindowMatchTest.MaxUser = MaxUserValue;
     
            }
          
            mStressTestWin.InitStressTest();
        }

      
        static  public readonly int SAVE_PREFIX_KEY_ID = 1000;
        static public readonly int SAVE_USER_BEGIN_NUM_KEY_ID = 1001;
        static public readonly int SAVE_TENKBGRUCOUNT_KEY_ID = 1002;
        static public readonly int SAVE_TENKBMAXUSERCOUNT_KEY_ID = 1003;
        static public readonly int SAVE_MATCHGRUCOUNT_KEY_ID = 1004;
        static public readonly int SAVE_MATCHMAXUSERCOUNT_ID = 1005;
        static public readonly int SAVE_TAB_INDEX_ID = 1006;



        

        protected override void OnClosed(EventArgs e)
        {        
            mStressTestWin.OnClosed();

            if (m_Engine != null)
                m_Engine.StopEngine();
            m_Engine = null;

            var StresssTestGameID1 = MainWindow.GetGameIDFromUI(MainWindow.Instance.RankTest_GameID);
            var StresssTestGameID2 = MainWindow.GetGameIDFromUI(MainWindow.Instance.stress_comboBoxGameID_Match);
            var StresssTestGameID3 = MainWindow.GetGameIDFromUI(MainWindow.Instance.stress_comboBoxGameID_Matced10KB);


            ServerAddressRegistry.SaveGameID(0, StresssTestGameID1);
            ServerAddressRegistry.SaveGameID(1, StresssTestGameID2);
            ServerAddressRegistry.SaveGameID(2, StresssTestGameID3);
        

            ServerAddressRegistry.AddServerAddress(1, stress_comboBoxIPAddress.Text);
//            ServerAddressRegistry.AddServerAddress(0, comboBoxIPAddress.Text);
           
            ServerAddressRegistry.SaveServerAddressToRegistry();
            ServerAddressRegistry.SaveLoginIDFromRegistry();

            ServerAddressRegistry.SaveValue(SAVE_PREFIX_KEY_ID, PreFixUserID.Text);

            ServerAddressRegistry.SaveValue(SAVE_USER_BEGIN_NUM_KEY_ID, UserBeginIdNum.Text);
            ServerAddressRegistry.SaveValue(SAVE_MATCHGRUCOUNT_KEY_ID, MatchInGroupUserCount.Text);
            ServerAddressRegistry.SaveValue(SAVE_MATCHMAXUSERCOUNT_ID, MatchKBMaxUserNumber.Text);




            mStressTestWin = null;

            base.OnClosed(e);
        }
           
        private void OnHandleInputKeyDown(object sender, KeyEventArgs e)
        {
            //if (e.Key == Key.Enter)
            //{
            //    btnLogin_Click(sender, e);
            //}
        }

        public static string GetGameIDFromUI(ComboBox cb)
        {
                string gameIDString = cb.SelectedItem.ToString();
                return gameIDString;
        }


        public static void InitGameIDComboBox(ComboBox cb, string gID)
        {
            cb.Items.Clear();

            // TODO: Iterate all game types
            cb.Items.Add("MyTownHero");
            cb.Items.Add("Conspiracy");

            cb.SelectedItem = gID.ToString();
        }

        public static void InitIPAdressComboBox(ComboBox IPAddressBox, List<NetAddress> ServerAddresses)
        {
            if (ServerAddresses == null)
                return;

            IPAddressBox.Items.Clear();
            foreach (var ipAddress in ServerAddresses)
            {
                var addressString = string.Format("{0},{1}", ipAddress.Address, ipAddress.Port);
                IPAddressBox.Items.Add(addressString);
            }

            if (ServerAddresses.Count > 0)
                IPAddressBox.SelectedIndex = 0;
            else
                IPAddressBox.SelectedIndex = -1;
        }

        public NetAddress GetServerAddressFromUI(int KeyIndex, ComboBox comboBoxIPAddress, System.Action UpdateUI)
        {
            NetAddress curSelectedAddress = new NetAddress()
            {
                Address = "127.0.0.1",
                Port = 21001
            };

            if (!string.IsNullOrEmpty(comboBoxIPAddress.Text) && curSelectedAddress.Parse(comboBoxIPAddress.Text))
            {
                if (ServerAddressRegistry.AddServerAddress(KeyIndex, comboBoxIPAddress.Text))
                    UpdateUI();
            }

            return curSelectedAddress;
        }


        //-- Ranking Data save.
        private void btnSaveRankData_Click(object sender, RoutedEventArgs e)
        {
            mStressTestWin.SaveRankData();
        }

        private void btnRankTestStart_Click(object sender, RoutedEventArgs e)
        {
            mStressTestWin.StartRankTest();
        }

        //////////////////////////////////////////////////////////////////////
        private void MaxUserNumber_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            e.Handled = new System.Text.RegularExpressions.Regex("[^0-9]+").IsMatch(e.Text);
        }

        private void UserBeginIdNum_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            e.Handled = new System.Text.RegularExpressions.Regex("[^0-9]+").IsMatch(e.Text);
        }

        
        
        private void btnTestMatching_cp_Click(object sender, RoutedEventArgs e)
        {           
            mStressTestWin.StartMatchingTest(true,1);
        }
        private void btnTestMatchedAndChat_cp_Click(object sender, RoutedEventArgs e)
        {
            mStressTestWin.StartMatchedChatTest(true,1);
        }

 

        
        private void btnTestMatching_Click(object sender, RoutedEventArgs e)
        {
            ServerAddressRegistry.SaveValue(SAVE_MATCHGRUCOUNT_KEY_ID, MatchInGroupUserCount.Text);
            ServerAddressRegistry.SaveValue(SAVE_MATCHMAXUSERCOUNT_ID, MatchKBMaxUserNumber.Text);
            mStressTestWin.StartMatchingTest(false,1);
        }

        private void btnTestMatchedAndChat_Click(object sender, RoutedEventArgs e)
        {
            mStressTestWin.StartMatchedChatTest(false,1);
        }



        private void btnStressTestClearLog_Click(object sender, RoutedEventArgs e)
        {
            textOutput1.Text = "";
            textOutput2.Text = "";
            textOutput3.Text = "";
           
        }

        public void UpdateTotalUserCount()
        {
            if (mStressTestWin == null)
                return;

            int CurTotalUser = 0;

           
            if (mStressTestWin.mMatcingTestWin != null)
            {
                CurTotalUser += mStressTestWin.mMatcingTestWin.mMainStatus.mLoginCurrectConnectedUser;
                CurTotalUser += mStressTestWin.mMatcingTestWin.mMainStatus.mGameSvrCurrectConnectedUser;
            }

            if (mStressTestWin.mMatched10KBTestWin != null)
            {
                CurTotalUser += mStressTestWin.mMatched10KBTestWin.mLoginCurrectConnectedUser;
                CurTotalUser += mStressTestWin.mMatched10KBTestWin.mPartyGameSvrCurrectConnectedUser;
            }

            if (mStressTestWin.mRankTestWin != null)
            {
                if (mStressTestWin.mRankTestWin.IsLogin())
                    CurTotalUser += 1;
            }


            L_ToTalConnectedUserCount.Dispatcher.Invoke(delegate ()
            {
                L_ToTalConnectedUserCount.Content = CurTotalUser.ToString();
            });
        }


        private void btnMatcing_Manaul_Click(object sender, RoutedEventArgs e)
        {
            if (mStressTestWin.mMatcingTestWin == null)
                return;

            mStressTestWin.mMatcingTestWin.SendReqMatchManaul();
        }        
    }
}



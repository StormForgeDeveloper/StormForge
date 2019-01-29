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
    public class StressTestWindowLoginTest
    {
        public static int MaxUser = 400;

        int mCurrectMaxUser = 1;

        public int mReTryCount = 0;
        public int mFailedReTryCount = 0;
        long mCurDealyReTryTime = 0;

        public class LoginTestUserGroupStatus
        {
            public int mLoginFaieldUserCount = 0;
            public int mLoginCurrectConnectedUser = 0;
            public int mGameSvrCurrectConnectedUser = 0;
            public int mGameSvrFailedConnectUser = 0;
            public int mGameSvrTotalJoinCount = 0;

            public void Clear()
            {
                mLoginFaieldUserCount = 0;
                mLoginCurrectConnectedUser = 0;
                mGameSvrCurrectConnectedUser = 0;
                mGameSvrFailedConnectUser = 0;
                mGameSvrTotalJoinCount = 0;
            }
        }

        List<StressTest_LoginUser> mLoginTesterUsers = new List<StressTest_LoginUser>();
        List<LoginTestUserGroupStatus> mTestGroupStatus = new List<LoginTestUserGroupStatus>();

        Dictionary<int, List<StressTest_LoginUser>> mTestUserGroups = new Dictionary<int, List<StressTest_LoginUser>>();
    
        int mCurLoginTestSuccessfulGroupCount = 0;

        int mTotalGroup = 0;

        DispatcherTimer m_LoginTestTimer;
        public LoginTestUserGroupStatus mMainStatus = new LoginTestUserGroupStatus();

        public void InitStressTest()
        {
            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.TestLoginInGroupUserCount, false);
            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.TestLoginMaxUserNumber, false);

            var StresssTestGameID = "MyTownHero";

            MainWindow.InitGameIDComboBox(MainWindow.Instance.stress_comboBoxGameID_TestLogin, StresssTestGameID);

            MainWindow.Instance.stress_comboBoxGameID_TestLogin.SelectedItem = 
                ServerAddressRegistry.ReadGameID(3, StresssTestGameID).ToString();

            UpdateStatueUI();
        }

        void _PrintStatus(int Screen, string text)
        {
            if (Screen == 0)
                return;

            MainWindow.Instance.textOutput4.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.textOutput4.Text = MainWindow.Instance.textOutput4.Text + ("\n" + text);

                MainWindow.Instance.StressTestLogScrollViewer4.ScrollToBottom();
                System.Diagnostics.Debug.WriteLine(text);
            }));
        }

        void PrintStatus(int Screen, string format, params object[] args)
        {
            string log = string.Format(format, args);
            _PrintStatus(Screen, log);
            mLoger.WriteToLog(log);
        }

        SimpleLog mLoger = new SimpleLog("LoginTester");
        NetAddress mServerAddress;

        public delegate void UpdateTextLabel_Delegate();
        public delegate void UpdateButtonPress_Delegate();

        public void OnClosed()
        {
            CloseAllConnections();
        }

        private void UpdateStatueUI()
        {
            MainWindow.Instance.UpdateTotalUserCount();

            MainWindow.Instance.L_CurTestLogin_LoginSvrUserCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurTestLogin_LoginSvrUserCount.Content = mMainStatus.mLoginCurrectConnectedUser.ToString();
            }));

            MainWindow.Instance.L_CurTestLogin_GameSvrUserCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurTestLogin_GameSvrUserCount.Content = mMainStatus.mGameSvrCurrectConnectedUser.ToString();
            }));

            MainWindow.Instance.L_TestLogin_LoginSvrFailed.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TestLogin_LoginSvrFailed.Content = mMainStatus.mLoginFaieldUserCount.ToString();
            }));


            MainWindow.Instance.L_TestLogin_GameSvrFailed.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TestLogin_GameSvrFailed.Content = mMainStatus.mGameSvrFailedConnectUser.ToString();
            }));


            MainWindow.Instance.L_TestLoginRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TestLoginRepeatCount.Content = mReTryCount.ToString();
            }));

            MainWindow.Instance.L_TestLoginReTryFailedRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TestLoginReTryFailedRepeatCount.Content = mFailedReTryCount.ToString();
            }));
        }

        void CloseAllConnections()
        {
            if (m_LoginTestTimer != null)
            {
                while (m_LoginTestTimer.IsEnabled)
                {
                    m_LoginTestTimer.Stop();
                }
            }

            m_LoginTestTimer = null;

            for (int i = 0; i < mLoginTesterUsers.Count; i++)
            {
                mLoginTesterUsers[i].CloseAllConnections();
                mLoginTesterUsers[i].UnInitEngine();
            }

            mLoginTesterUsers.Clear();
            mTestUserGroups.Clear();
        }

        string MakeStreesTestUserID(int StartID, string PrefIxName, int AppedID)
        {
            return PrefIxName + "_LoginTest" + (StartID + AppedID).ToString();
        }

        private void InitStatusValue()
        {
            mCurDealyReTryTime = 0;
            mCurLoginTestSuccessfulGroupCount = 0;

            mTotalGroup = 0;

            mMainStatus.Clear();
            mTestGroupStatus.Clear();          
        }

        public void StartTest(bool bAutoClick, int ClickIndex)
        {
            string PreFixUserID = MainWindow.Instance.PreFixUserID.Text.Trim();
            if (string.IsNullOrEmpty(PreFixUserID))
            {
                MessageBox.Show("Enter valid PreFixUserID");
                return;
            }

            int MaxConnectionUser = Convert.ToInt32(MainWindow.Instance.TestLoginMaxUserNumber.Text);
            if (MaxConnectionUser > MaxUser)
            {
                MessageBox.Show(string.Format("{0} users limit!!", MaxUser));
                return;
            }

            int PrefixStartID = Convert.ToInt32(MainWindow.Instance.UserBeginIdNum.Text);
            if (PrefixStartID <= 0)
            {
                MessageBox.Show("Enter valid StartID!! be Higher than Zero");
                return;
            }

            if (bAutoClick == false)
            {
                mReTryCount = 0;
                mFailedReTryCount = 0;
            }

            if (bAutoClick == true && ClickIndex == 1)
                PrintStatus(1, "ReTry Login Test!!");

            if (bAutoClick == true && ClickIndex == 2)
                mFailedReTryCount++;

            CloseAllConnections();
            mCurrectMaxUser = MaxConnectionUser;

            InitStatusValue();
            UpdateStatueUI();
            
            MainWindow.Instance.textOutput4.Text = string.Empty;
            var StresssTestGameID = MainWindow.GetGameIDFromUI(MainWindow.Instance.stress_comboBoxGameID_TestLogin);

            for (int i = 0; i < MaxConnectionUser; i++)
            {
                StressTest_LoginUser TestUser = new StressTest_LoginUser();
                TestUser.InitEngine();
                TestUser.SetPrintHanlde(PrintStatus);

                TestUser.m_LoginID = MakeStreesTestUserID(PrefixStartID, PreFixUserID, i);
                TestUser.gameID = StresssTestGameID;
                mLoginTesterUsers.Add(TestUser);
            }

            ServerAddressRegistry.SaveGameID(3, StresssTestGameID);
            mServerAddress = MainWindow.Instance.GetServerAddressFromUI(1, MainWindow.Instance.stress_comboBoxIPAddress,
                () =>
                {
                    MainWindow.InitIPAdressComboBox(MainWindow.Instance.stress_comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(1));
                });

            CreateGroup();

            RunConnectGroup(0, mServerAddress);

            m_LoginTestTimer = new DispatcherTimer();
            m_LoginTestTimer.Tick += new EventHandler(
                (object ts, EventArgs te) =>
                {
                    for (int i = 0; i < mLoginTesterUsers.Count; i++)
                    {
                        mLoginTesterUsers[i].OnTimerTick(1000);
                    }

                    if (IsProgressFailed() && MainWindow.Instance.InfiniteReTryFailedRepeattCheck_LoginTest.IsChecked == true)
                    {
                        mCurDealyReTryTime += 1000;
                        PrintStatus(1, "Plz ReTry Test!! {0}..", 3 - (mCurDealyReTryTime / 1000));
                        if (mCurDealyReTryTime >= 3000)
                        {
                            this.StartTest(true, 2);
                        }
                    }
                });

            m_LoginTestTimer.Interval = new TimeSpan(0, 0, 1);
            m_LoginTestTimer.Start();
        }

        private void CreateGroup()
        {
            if (mLoginTesterUsers.Count == 0)
                return;

            // Create Group
            int InUserCountGroup = Convert.ToInt32(MainWindow.Instance.TestLoginInGroupUserCount.Text);
            mTotalGroup = mLoginTesterUsers.Count / InUserCountGroup;
            if ((mLoginTesterUsers.Count % InUserCountGroup) != 0)
                mTotalGroup++;

            ////////////////////////////////////////////
            for (int i = 0; i < mTotalGroup; i++)
            {
                mTestUserGroups.Add(i, new List<StressTest_LoginUser>());
                mTestGroupStatus.Add(new LoginTestUserGroupStatus());
            }

            for (int GroupIndex = 0; GroupIndex < mTotalGroup; GroupIndex++)
            {
                for (int j = 0; j < InUserCountGroup; j++)
                {
                    int TempIndex = (GroupIndex * InUserCountGroup) + j;
                    if (TempIndex >= mLoginTesterUsers.Count)
                        break;

                    mLoginTesterUsers[TempIndex].GroupID = GroupIndex;
                    mTestUserGroups[GroupIndex].Add(mLoginTesterUsers[TempIndex]);
                }
            }
        }


        private void RunConnectGroup(int GroupIndex, NetAddress serverAddress)
        {
            if (GroupIndex >= mTestUserGroups.Count)
                return;

            List<StressTest_LoginUser> TestUsers = mTestUserGroups[GroupIndex];

            for (int i = 0; i < TestUsers.Count; i++)
            {
                TestUsers[i].RunConnect(serverAddress,
                     (StressTest_LoginUser user) =>
                     {
                         mMainStatus.mLoginCurrectConnectedUser++;
                         mTestGroupStatus[user.GroupID].mLoginCurrectConnectedUser++;
                         UpdateStatueUI();
                     },
                    (StressTest_LoginUser user, SF.Net.SendMessageLogin l) =>
                    {
                        if (l == null)
                            return;

                        mMainStatus.mLoginCurrectConnectedUser--;
                        mTestGroupStatus[user.GroupID].mLoginCurrectConnectedUser--;

                        UpdateStatueUI();
                    },
                    (StressTest_LoginUser user, int FailedIndex) =>
                    {

                        mMainStatus.mLoginFaieldUserCount++;
                        UpdateStatueUI();
                    },
                    (StressTest_LoginUser user) =>
                    {
                        mTestGroupStatus[user.GroupID].mGameSvrCurrectConnectedUser++;
                        mMainStatus.mGameSvrCurrectConnectedUser++;
                        UpdateStatueUI();
                    },
                    (StressTest_LoginUser user, SF.Net.SendMessageGame l) =>
                    {
                        if (l == null)
                            return;

                        mTestGroupStatus[user.GroupID].mGameSvrCurrectConnectedUser--;
                        mMainStatus.mGameSvrCurrectConnectedUser--;

                        UpdateStatueUI();
                    },
                    (StressTest_LoginUser user) =>
                    {
                        mTestGroupStatus[user.GroupID].mGameSvrFailedConnectUser++;
                        mMainStatus.mGameSvrFailedConnectUser++;
                        UpdateStatueUI();
                    },
                    (StressTest_LoginUser user, bool bSucceess) =>
                    {

                        //-- 여기서 체크,해서 다음으로 넘어가면되겠네.
                        //m_LoginTestTimer
                        if (bSucceess)
                        {
                            mMainStatus.mGameSvrTotalJoinCount++;
                            mTestGroupStatus[user.GroupID].mGameSvrTotalJoinCount++;
                        }

                        UpdateStatueUI();

                        if (!bSucceess)
                            return;

                        int InGroupUserCount = mTestUserGroups[user.GroupID].Count;

                        if (mTestGroupStatus[user.GroupID].mGameSvrTotalJoinCount != InGroupUserCount)
                            return;

                        mCurLoginTestSuccessfulGroupCount++;

                        RunConnectGroup(mCurLoginTestSuccessfulGroupCount, mServerAddress);

                        if (mCurLoginTestSuccessfulGroupCount == mTestGroupStatus.Count)
                        {
                            if (MainWindow.Instance.InfiniteRepeatCheck_Login.IsChecked == true)
                            {
                                System.Threading.Tasks.Task.Delay(3000).ContinueWith(t =>
                                {
                                    MainWindow.Instance.btnStressTest_cp_Login.Dispatcher.Invoke(new UpdateButtonPress_Delegate(delegate ()
                                    {
                                        mReTryCount++;

                                        MainWindow.Instance.btnStressTest_cp_Login.RaiseEvent(new RoutedEventArgs(Button.ClickEvent));
                                    }));
                                });
                            }
                        }

                    }
               );
            }
        }


        public bool IsProgressFailed()
        {
            if (mMainStatus.mLoginFaieldUserCount > 0)
                return true;

            if (mMainStatus.mGameSvrFailedConnectUser > 0)
                return true;

            if (mCurLoginTestSuccessfulGroupCount == mTotalGroup)
                return false;

            if (!mTestUserGroups.ContainsKey(mCurLoginTestSuccessfulGroupCount))
                return true;

            foreach (StressTest_LoginUser user in mTestUserGroups[mCurLoginTestSuccessfulGroupCount])
            {
                if (user.CurState == StressTest_LoginUser.eTesterState.COMPLTE)
                    continue;

                if (user.CurState == StressTest_LoginUser.eTesterState.NONE)
                    continue;

                if (user.CurState == StressTest_LoginUser.eTesterState.LOGINING)
                {
                    if (user.m_ConnectionLogin == null)
                        return true;

                    if (user.m_ConnectionLogin.State == SFConnection.ConnectionState.DISCONNECTED)
                        return true;
                }
                else if (user.CurState == StressTest_LoginUser.eTesterState.GAMESVR_JOIN_FAILED)
                {
                    return true;
                }
                else
                { 
                    if (user.m_ConnectionGame == null)
                        return true;

                    if (user.m_ConnectionGame.State == SFConnection.ConnectionState.DISCONNECTED)
                        return true;

                }
            }
            return false;
        }
    }
}

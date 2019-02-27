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
    public class StressTestWindowMatchTest
    {
        public static int MaxUser = 400;

        int mCurrectMaxUser = 1;

        public int mReTryCount = 0;
        public int mFailedReTryCount = 0;

        public class MatchUserGroupStatus
        {
            public int mLoginFaieldUserCount = 0;
            public int mLoginCurrectConnectedUser = 0;
            public int mGameSvrCurrectConnectedUser = 0;
            public int mGameSvrFailedConnectUser = 0;
            public int mGameJoinUserCount = 0;
            public int mGameJoinFailedUserCount = 0;
            public int mGameMatchSendCount = 0;
            public int mGameTotalMatchCount = 0;

            public void Clear()
            {
                mLoginFaieldUserCount = 0;
                mLoginCurrectConnectedUser = 0;
                mGameSvrCurrectConnectedUser = 0;
                mGameSvrFailedConnectUser = 0;
                mGameJoinUserCount = 0;
                mGameJoinFailedUserCount = 0;
                mGameTotalMatchCount = 0;
                mGameMatchSendCount = 0;
            }
        }

        List<StressTest_MatchingUser> mTestMatchingBUsers = new List<StressTest_MatchingUser>();
        List<MatchUserGroupStatus> mTestGroupStatus = new List<MatchUserGroupStatus>();

        Dictionary<int, List<StressTest_MatchingUser>> mTestMatchingBUserGroups = new Dictionary<int, List<StressTest_MatchingUser>>();
    

        int mCurTestSuccessfulGroupCount = 0;
        int mCurTestSendMatchGroupCount = 0;


        int mCurTestGameLoginGroupCount = 0;

        //int mCurTestLoginSuccessfulGroupCount = 0;
        //int mCurTestSendSuccessfulGroupCount = 0;

        int mTotalGroup = 0;

        bool IsAutoTest = false;
        bool mbStartSend = false;
        int  mTickCount = 0;
        int  UpdateTick = 1000;

        DispatcherTimer m_MatchingTestTimer;
        public MatchUserGroupStatus mMainStatus = new MatchUserGroupStatus();

        public void InitStressTest()
        {
            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.MatchKBMaxUserNumber, false);
            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.MatchInGroupUserCount, false);


            var StresssTestGameID = "MyTownHero";

            MainWindow.InitGameIDComboBox(MainWindow.Instance.stress_comboBoxGameID_Match, StresssTestGameID);

            MainWindow.Instance.stress_comboBoxGameID_Match.SelectedItem =
             ServerAddressRegistry.ReadGameID(1, StresssTestGameID).ToString();

            MainWindow.Instance.buttonManual_Matcing.IsEnabled = false;
            MainWindow.Instance.buttonManual_Matcing.Visibility = Visibility.Hidden;


            UpdateMatchingTestStatueUI();
        }

        void _PrintStatus(int Screen,  string text)
        {
            if (Screen == 0)
                return;

            MainWindow.Instance.textOutput2.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.textOutput2.Text = MainWindow.Instance.textOutput2.Text + ("\n" + text);

                MainWindow.Instance.StressTestLogScrollViewer2.ScrollToBottom();
                System.Diagnostics.Debug.WriteLine(text);
            }));
        }

        void PrintStatus(int Screen, string format, params object[] args)
        {
            string log = string.Format(format, args);          
           _PrintStatus(Screen,  log);
            mLoger.WriteToLog(log);
        }

        SimpleLog mLoger = new SimpleLog("MatcingTest");
        NetAddress mServerAddress;

        public delegate void UpdateTextLabel_Delegate();
        public delegate void UpdateButtonPress_Delegate();

        public void OnClosed()
        {
            CloseAllConnections();
        }

        private void UpdateMatchingTestStatueUI()
        {
            MainWindow.Instance.UpdateTotalUserCount();

            MainWindow.Instance.L_CurGameConnectedUser.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurGameConnectedUser.Content = mMainStatus.mGameSvrCurrectConnectedUser.ToString();
            }));

            MainWindow.Instance.L_CurGameLoginUser.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurGameLoginUser.Content = mMainStatus.mGameJoinUserCount.ToString();
            }));

            MainWindow.Instance.L_CurGameFailedLoginUser.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurGameFailedLoginUser.Content = mMainStatus.mGameJoinFailedUserCount.ToString();
            }));


            MainWindow.Instance.L_TotalMatchCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TotalMatchCount.Content = mMainStatus.mGameTotalMatchCount.ToString();
            }));

            MainWindow.Instance.L_SendMatchCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_SendMatchCount.Content = mMainStatus.mGameMatchSendCount.ToString();
            }));

            MainWindow.Instance.L_MatchRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_MatchRepeatCount.Content = mReTryCount.ToString();
            }));


            MainWindow.Instance.L_MatchLoginUser_Failed.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_MatchLoginUser_Failed.Content = mMainStatus.mLoginFaieldUserCount.ToString();
            }));

            MainWindow.Instance.L_MatchReTryFaieldRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_MatchReTryFaieldRepeatCount.Content = mFailedReTryCount.ToString();
            }));


        }

        void CloseAllConnections()
        {
            if (m_MatchingTestTimer != null)
            {
                while (m_MatchingTestTimer.IsEnabled)
                {
                    m_MatchingTestTimer.Stop();
                }
            }

            m_MatchingTestTimer = null;
            for (int i = 0; i < mTestMatchingBUsers.Count; i++)
            {
                mTestMatchingBUsers[i].CloseAllConnections();
                mTestMatchingBUsers[i].UnInitEngine();
            }

            mTestMatchingBUsers.Clear();

            mTestMatchingBUserGroups.Clear();
        }

        string MakeStreesTestUserID(int StartID, string PrefIxName, int AppedID)
        {
            return PrefIxName + "_MatchTest" + (StartID + AppedID).ToString();
        }

        private void InitStatusValue()
        {
            mCurTestGameLoginGroupCount = 0;

            mCurTestSendMatchGroupCount = 0;
            mCurTestSuccessfulGroupCount = 0;
            mTotalGroup = 0;

            mMainStatus.Clear();
            mTestGroupStatus.Clear();

            mCurDealyReTryTime = 0;
            mTickCount = 0;
            mbStartSend = false;
        }


        // Matching Test..
        public void StartTest(bool bAutoClick, int ClickIndex)
        {
            string PreFixUserID = MainWindow.Instance.PreFixUserID.Text.Trim();
            if (string.IsNullOrEmpty(PreFixUserID))
            {
                MessageBox.Show("Enter valid PreFixUserID");
                return;
            }

            int MaxConnectionUser = Convert.ToInt32(MainWindow.Instance.MatchKBMaxUserNumber.Text);
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

                IsAutoTest = MainWindow.Instance.TestMatcingAutoCheck.IsChecked == true;

                MainWindow.Instance.buttonManual_Matcing.IsEnabled = false;
                MainWindow.Instance.buttonManual_Matcing.Visibility = Visibility.Hidden;

            }

            if(bAutoClick == true && ClickIndex == 1)
                PrintStatus(1, "ReTry Matcing Test!!");

            if (bAutoClick == true && ClickIndex == 2)
                mFailedReTryCount++;
            

            CloseAllConnections();
            mCurrectMaxUser = MaxConnectionUser;

            InitStatusValue();
            UpdateMatchingTestStatueUI();
            
            MainWindow.Instance.textOutput2.Text = string.Empty;

            var StresssTestGameID = MainWindow.GetGameIDFromUI(MainWindow.Instance.stress_comboBoxGameID_Match);

            for (int i = 0; i < MaxConnectionUser; i++)
            {
                StressTest_MatchingUser TestMatchingUser = new StressTest_MatchingUser();
                TestMatchingUser.InitEngine();
                TestMatchingUser.SetPrintHanlde(PrintStatus);

                TestMatchingUser.m_LoginID = MakeStreesTestUserID(PrefixStartID, PreFixUserID, i);
                TestMatchingUser.gameID = StresssTestGameID;
                mTestMatchingBUsers.Add(TestMatchingUser);
            }

            ServerAddressRegistry.SaveGameID(1, StresssTestGameID);
            mServerAddress = MainWindow.Instance.GetServerAddressFromUI(1, MainWindow.Instance.stress_comboBoxIPAddress,
                () =>
                {
                    MainWindow.InitIPAdressComboBox(MainWindow.Instance.stress_comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(1));
                });


            CreateGroup();
         

            RunConnectGroup(0, mServerAddress);

            m_MatchingTestTimer = new DispatcherTimer();
            m_MatchingTestTimer.Tick += new EventHandler(
                (object ts, EventArgs te) =>
                {
                    for (int i = 0; i < mTestMatchingBUsers.Count; i++)
                    {
                        mTestMatchingBUsers[i].OnTimerTick(UpdateTick);
                    }

                    if (IsAutoTest)
                    {
                        if (IsProgressFailed() && MainWindow.Instance.InfiniteReTryFailedRepeatCheck_Match.IsChecked == true)
                        {
                            mCurDealyReTryTime += UpdateTick;

                            if (mCurDealyReTryTime >= 1000)
                            {
                                mCurDealyReTryTime = 0;
                                mTickCount++;
                                PrintStatus(1, "Plz ReTry Test!! {0}..", 3 - mTickCount);
                                if (mTickCount >= 3)
                                {
                                    this.StartTest(true, 2);
                                }
                            }
                        }
                    }
                    else
                    {
                        if (mMainStatus.mGameJoinUserCount == mTestMatchingBUsers.Count)
                        {
                            bool bJonedUser = false;

                            for (int i = 0; i < mTestMatchingBUsers.Count; i++)
                            {
                                if( mTestMatchingBUsers[i].m_JoinedGameUID != 0)
                                {
                                    bJonedUser = true;
                                    break;
                                }
                            }

                            if (bJonedUser)
                                return;

                            if (mbStartSend)
                                return;

                            MainWindow.Instance.buttonManual_Matcing.IsEnabled = true;
                            MainWindow.Instance.buttonManual_Matcing.Visibility = Visibility.Visible;
                        }
                    }
                });

            m_MatchingTestTimer.Interval = new TimeSpan(0, 0, 0, 0, UpdateTick);
            m_MatchingTestTimer.Start();
        }

        long mCurDealyReTryTime = 0;

        private void CreateGroup()
        {
            if (mTestMatchingBUsers.Count == 0)
                return;

            // Create Group
            int InUserCountGroup = Convert.ToInt32(MainWindow.Instance.MatchInGroupUserCount.Text);
            mTotalGroup = mTestMatchingBUsers.Count / InUserCountGroup;
            if ((mTestMatchingBUsers.Count % InUserCountGroup) != 0)
                mTotalGroup++;

            ////////////////////////////////////////////
            for (int i = 0; i < mTotalGroup; i++)
            {
                mTestMatchingBUserGroups.Add(i, new List<StressTest_MatchingUser>());
                mTestGroupStatus.Add(new MatchUserGroupStatus());
            }

            for (int GroupIndex = 0; GroupIndex < mTotalGroup; GroupIndex++)
            {
                for (int j = 0; j < InUserCountGroup; j++)
                {
                    int TempIndex = (GroupIndex * InUserCountGroup) + j;
                    if (TempIndex >= mTestMatchingBUsers.Count)
                        break;

                    mTestMatchingBUsers[TempIndex].GroupID = GroupIndex;
                    mTestMatchingBUserGroups[GroupIndex].Add(mTestMatchingBUsers[TempIndex]);
                }
            }
        }

        private void RunMatchingGroup(int GroupIndex)
        {
            if (GroupIndex >= mTestMatchingBUserGroups.Count)
                return;

            List<StressTest_MatchingUser> TestUsers = mTestMatchingBUserGroups[GroupIndex];

            for (int i = 0; i < TestUsers.Count; i++)
            {
                StressTest_MatchingUser user = TestUsers[i];
                PrintStatus(0, "Send RequestGameMatchCmd ID = {0}", user.m_LoginID);
                user.m_Game.RequestGameMatchCmd(0, 4, (byte)PlayerRole.None);

                mTestGroupStatus[user.GroupID].mGameMatchSendCount++;
                mMainStatus.mGameMatchSendCount++;                
            }

            UpdateMatchingTestStatueUI();
        }

        private void RunConnectGroup(int GroupIndex, NetAddress serverAddress)
        {
            if (GroupIndex >= mTestMatchingBUserGroups.Count)
                return;

            List<StressTest_MatchingUser> TestUsers = mTestMatchingBUserGroups[GroupIndex];

            for (int i = 0; i < TestUsers.Count; i++)
            {
                TestUsers[i].RunConnect(serverAddress,
                     (StressTest_MatchingUser user) =>
                     {
                         mMainStatus.mLoginCurrectConnectedUser++;
                         mTestGroupStatus[user.GroupID].mLoginCurrectConnectedUser++;
                         UpdateMatchingTestStatueUI();
                     },
                    (StressTest_MatchingUser user, SF.Net.SendMessageLogin l) =>
                    {
                        if (l == null)
                            return;

                        mMainStatus.mLoginCurrectConnectedUser--;
                        mTestGroupStatus[user.GroupID].mLoginCurrectConnectedUser--;

                        UpdateMatchingTestStatueUI();
                    },
                    (StressTest_MatchingUser user, int FailedIndex) =>
                    {
                        mMainStatus.mLoginFaieldUserCount++;
                        UpdateMatchingTestStatueUI();
                    },
                    (StressTest_MatchingUser user) =>
                    {
                        mTestGroupStatus[user.GroupID].mGameSvrCurrectConnectedUser++;
                        mMainStatus.mGameSvrCurrectConnectedUser++;
                        UpdateMatchingTestStatueUI();                     
                    },
                    (StressTest_MatchingUser user, SF.Net.SendMessageGame l) =>
                    {
                        if (l == null)
                            return;

                        mTestGroupStatus[user.GroupID].mGameSvrCurrectConnectedUser--;
                        mMainStatus.mGameSvrCurrectConnectedUser--;

                        UpdateMatchingTestStatueUI();
                    },
                    (StressTest_MatchingUser user) =>
                    {
                        mTestGroupStatus[user.GroupID].mGameSvrFailedConnectUser++;
                        mMainStatus.mGameSvrFailedConnectUser++;
                        UpdateMatchingTestStatueUI();
                    },
                    (StressTest_MatchingUser user, bool Success) =>
                    {
                        if (Success)
                        {
                            mTestGroupStatus[user.GroupID].mGameJoinUserCount++;
                            mMainStatus.mGameJoinUserCount++;

                            ///////////////////////////////////////////////////////
                            if (!IsAutoTest)
                            {
                                int GroupUserCount = mTestMatchingBUserGroups[user.GroupID].Count;
                                if (mTestGroupStatus[user.GroupID].mGameJoinUserCount == GroupUserCount)
                                {
                                    mCurTestGameLoginGroupCount++;
                                    RunConnectGroup(mCurTestGameLoginGroupCount, mServerAddress);
                                }
                            }
                        }
                        else
                        {
                            mTestGroupStatus[user.GroupID].mGameJoinFailedUserCount++;
                            mMainStatus.mGameJoinFailedUserCount++;
                        }

                        UpdateMatchingTestStatueUI();
                    },
                    (StressTest_MatchingUser user) =>
                    {
                        if (!IsAutoTest)
                            return;

                        PrintStatus(0, "Send RequestGameMatchCmd ID = {0}", user.m_LoginID);
                        user.m_Game.RequestGameMatchCmd(0, 4, (byte)PlayerRole.None);

                        mTestGroupStatus[user.GroupID].mGameMatchSendCount++;

                        mMainStatus.mGameMatchSendCount++;
                        UpdateMatchingTestStatueUI();

                        int GroupUserCount = mTestMatchingBUserGroups[user.GroupID].Count;
                        if (mTestGroupStatus[user.GroupID].mGameMatchSendCount == GroupUserCount)
                        {
                            //--
                            mCurTestSendMatchGroupCount++;
                            RunConnectGroup(mCurTestSendMatchGroupCount, mServerAddress);
                        }
                    },

                    (StressTest_MatchingUser user, bool Success) =>
                    {
                        if (Success)
                        {
                            mMainStatus.mGameTotalMatchCount++;
                            mTestGroupStatus[user.GroupID].mGameTotalMatchCount++;
                        }

                        UpdateMatchingTestStatueUI();

                        if (!Success)
                            return;

                        int InGroupUserCount = mTestMatchingBUserGroups[user.GroupID].Count;

                        if (mTestGroupStatus[user.GroupID].mGameTotalMatchCount == InGroupUserCount)
                        {
                            if (IsAutoTest)
                            {
                                mCurTestSuccessfulGroupCount++;
                                if (mCurTestSuccessfulGroupCount == mTestGroupStatus.Count)
                                {
                                    if (MainWindow.Instance.InfiniteRepeatCheck_MatcingTest.IsChecked == true)
                                    {
                                        System.Threading.Tasks.Task.Delay(3000).ContinueWith(t =>
                                        {
                                            MainWindow.Instance.btnStressTestMatching_Cp.Dispatcher.Invoke(new UpdateButtonPress_Delegate(delegate ()
                                            {
                                                mReTryCount++;
                                                MainWindow.Instance.btnStressTestMatching_Cp.RaiseEvent(new RoutedEventArgs(Button.ClickEvent));
                                            }));
                                        });
                                    }
                                }
                            }
                            else
                            {

                                mCurTestSendMatchGroupCount++;
                                RunMatchingGroup(mCurTestSendMatchGroupCount);

                            }
                        }
                    },
                    (StressTest_MatchingUser user) =>
                    {
                        if (IsAutoTest)
                        {
                            //PrintStatus(0, "Send RequestGameMatchCmd ID = {0}", user.m_LoginID);
                            //user.m_Game.RequestGameMatchCmd(4, (byte)PlayerRole.None);
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

            if (mMainStatus.mGameJoinFailedUserCount > 0)
                return true;

            if (mCurTestSuccessfulGroupCount == mTotalGroup)
                return false;

            if (!mTestMatchingBUserGroups.ContainsKey(mCurTestSuccessfulGroupCount))
                return true;

            foreach (StressTest_MatchingUser user in mTestMatchingBUserGroups[mCurTestSuccessfulGroupCount])
            {
                if (user.CurState == StressTest_MatchingUser.eTesterState.COMPLTE)
                    continue;

                if (user.CurState == StressTest_MatchingUser.eTesterState.NONE)
                    continue;

                if (user.CurState == StressTest_MatchingUser.eTesterState.LOGINING)
                {
                    if (user.m_ConnectionLogin == null)
                        return true;

                    if (user.m_ConnectionLogin.State == SFConnection.ConnectionState.DISCONNECTED)
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

        public void SendReqMatchManaul()
        {
            if (mMainStatus.mGameSvrCurrectConnectedUser != mTestMatchingBUsers.Count)
                return;
            
            if (mCurTestSendMatchGroupCount != 0)
                return;

            if (mbStartSend)
                return;

            mbStartSend = true;
            MainWindow.Instance.buttonManual_Matcing.IsEnabled = false;

            RunMatchingGroup(mCurTestSendMatchGroupCount);
        }

    }
}

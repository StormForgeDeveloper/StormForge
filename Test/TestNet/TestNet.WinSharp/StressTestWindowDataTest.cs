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
    public class StressTestWindowDataTest
    {
        public static int MaxUser = 400;

       

        public class GroupStatus
        {
            public int mLoginCurrectConnectedUser = 0;
            public int mLoginFailedConnectUser = 0;
            public int mLoginSuccessCount = 0;
            public int mLoginFailedCount = 0;
            public int m_TenKBSendCount = 0;
            public int m_TenKBSendSuccess = 0;
            public int m_TenKBSendFailed = 0;

            public void Clear()
            {
                mLoginCurrectConnectedUser = 0;
                mLoginFailedConnectUser = 0;
                mLoginSuccessCount = 0;
                mLoginFailedCount = 0;
                m_TenKBSendCount = 0;
                m_TenKBSendSuccess = 0;
                m_TenKBSendFailed = 0;
            }
        }

        public GroupStatus mMainStatus = new GroupStatus();


        int mCurrectMaxUser = 1;
        List<StressTest_TenKBUser> mTestTenKBUsers = new List<StressTest_TenKBUser>();
        DispatcherTimer m_TenKBTimer;

        Dictionary<int, List<StressTest_TenKBUser>> mTestTenKBUserGroups = new Dictionary<int, List<StressTest_TenKBUser>>();
        List<GroupStatus> mTestGroupStatus = new List<GroupStatus>();

        int mCurTestLoginSuccessfulGroupCount = 0;
        int mCurTestSendSuccessfulGroupCount = 0;


        int mTotalGroup = 0;
        byte[] mTestSendData = null;

        NetAddress mServerAddress;
        public int mReTryCount = 0;
        public int mFailedReTryCount = 0;

        long mCurDealyReTryTime = 0;

        bool IsAutoTest = false;

        bool mbStartSend = false;
        int mTickCount = 0;
        int UpdateTick = 1000;

        public void InitStressTest()
        {
            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.TenKBMaxUserNumber, false);
            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.TenKBInGroupUserCount, false);

            int DataTestSize = 1024;
            mTestSendData = new byte[DataTestSize];
            for (int iData = 0; iData < DataTestSize; iData++)
                mTestSendData[iData] = (byte)iData;

            var StresssTestGameID = "MyTownHero";

            MainWindow.InitGameIDComboBox(MainWindow.Instance.stress_comboBoxGameID_10KB, StresssTestGameID);
            MainWindow.Instance.stress_comboBoxGameID_10KB.SelectedItem =
               ServerAddressRegistry.ReadGameID(0, StresssTestGameID).ToString();

            MainWindow.Instance.buttonSendData_Manaul.IsEnabled = false;
            MainWindow.Instance.buttonSendData_Manaul.Visibility = Visibility.Hidden;

            UpdateTestUserStateUI();
        }

        void _PrintStatus(int Screen, string text)
        {
            if (Screen == 0)
                return;

            MainWindow.Instance.textOutput1.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.textOutput1.Text = MainWindow.Instance.textOutput1.Text + ("\n" + text);
                MainWindow.Instance.StressTestLogScrollViewer.ScrollToBottom();
                System.Diagnostics.Debug.WriteLine(text);
            }));
        }

        void PrintStatus(int Screen, string format, params object[] args)
        {
            string log = string.Format(format, args);
            _PrintStatus(Screen, log);

            mLoger.WriteToLog(log);
        }

        SimpleLog mLoger = new SimpleLog("default");

        public void OnClosed()
        {
            CloseAllConnections();
        }

        public delegate void UpdateTextLabel_Delegate();
        public delegate void UpdateButtonPress_Delegate();

        private void UpdateTestUserStateUI()
        {
            MainWindow.Instance.UpdateTotalUserCount();

            MainWindow.Instance.L_CurConnectedUser.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurConnectedUser.Content = mMainStatus.mLoginCurrectConnectedUser.ToString();

            }));

            MainWindow.Instance.L_CurLoginSuccess.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurLoginSuccess.Content = mMainStatus.mLoginSuccessCount.ToString();
            }));
            MainWindow.Instance.L_CurLoginFailed.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurLoginFailed.Content = mMainStatus.mLoginFailedCount.ToString();
            }));

            MainWindow.Instance.L_TenKBSendCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TenKBSendCount.Content = mMainStatus.m_TenKBSendCount.ToString();
            }));

            MainWindow.Instance.L_TenKBSendSuccess.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TenKBSendSuccess.Content = mMainStatus.m_TenKBSendSuccess.ToString();
            }));

            MainWindow.Instance.L_FailedTenKBCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_FailedTenKBCount.Content = mMainStatus.m_TenKBSendFailed.ToString();
            }));

            MainWindow.Instance.L_TenKBRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TenKBRepeatCount.Content = mReTryCount.ToString();
            }));

            MainWindow.Instance.L_TenKBRetryFailedRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_TenKBRetryFailedRepeatCount.Content = mFailedReTryCount.ToString();
            }));



        }

        void CloseAllConnections()
        {
            if (m_TenKBTimer != null)
            {
                while (m_TenKBTimer.IsEnabled)
                    m_TenKBTimer.Stop();
            }

            m_TenKBTimer = null;

            for (int i = 0; i < mTestTenKBUsers.Count; i++)
            {
                mTestTenKBUsers[i].CloseAllConnections();
                mTestTenKBUsers[i].UnInitEngine();
            }

            mTestTenKBUsers.Clear();


            mTestTenKBUserGroups.Clear();
        }

        string MakeStreesTestUserID(int StartID, string PrefIxName, int AppedID)
        {
            return PrefIxName + "_DataTest" + (StartID + AppedID).ToString();
        }


        private void InitStatusValue()
        {
            mCurDealyReTryTime = 0;
            mMainStatus.Clear();
            mTestGroupStatus.Clear();

            mCurTestSendSuccessfulGroupCount = 0;
            mCurTestLoginSuccessfulGroupCount = 0;

            mTotalGroup = 0;
            mTickCount = 0;

            mbStartSend = false;
        }

        //-- Login And 10KB Test..
        public void StartTest(bool bAutoClick, int ClickIndex)
        {
            string PreFixUserID = MainWindow.Instance.PreFixUserID.Text.Trim();
            if (string.IsNullOrEmpty(PreFixUserID))
            {
                MessageBox.Show("Enter valid PreFixUserID");
                return;
            }

            int MaxConnectionUser = Convert.ToInt32(MainWindow.Instance.TenKBMaxUserNumber.Text);
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
                 IsAutoTest = MainWindow.Instance.TenKBTestAutoCheck.IsChecked == true;

                MainWindow.Instance.buttonSendData_Manaul.IsEnabled = false;
                MainWindow.Instance.buttonSendData_Manaul.Visibility = Visibility.Hidden;
            }

            if (bAutoClick == true && ClickIndex == 1)
                PrintStatus(1, "ReTry Data Test!!");

            if (bAutoClick == true && ClickIndex == 2)
                mFailedReTryCount++;

            CloseAllConnections();

            mCurrectMaxUser = MaxConnectionUser;

            InitStatusValue();
            UpdateTestUserStateUI();

            MainWindow.Instance.textOutput1.Text = string.Empty;

            var StresssTestGameID = MainWindow.GetGameIDFromUI(MainWindow.Instance.stress_comboBoxGameID_10KB);

            for (int i = 0; i < MaxConnectionUser; i++)
            {
                StressTest_TenKBUser Testuser = new StressTest_TenKBUser();
                Testuser.InitEngine();
                Testuser.SetPrintHanlde(PrintStatus);

                Testuser.m_LoginID = MakeStreesTestUserID(PrefixStartID, PreFixUserID, i);
                Testuser.gameID = StresssTestGameID;
                mTestTenKBUsers.Add(Testuser);
            }

            ServerAddressRegistry.SaveGameID(0, StresssTestGameID);

            mServerAddress = MainWindow.Instance.GetServerAddressFromUI(1, MainWindow.Instance.stress_comboBoxIPAddress,
                () =>
                {
                    MainWindow.InitIPAdressComboBox(MainWindow.Instance.stress_comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(1));
                });


            CreateGroup();

            RunConnectGroup(mCurTestLoginSuccessfulGroupCount, mServerAddress);
     
            m_TenKBTimer = new DispatcherTimer();
            m_TenKBTimer.Tick += new EventHandler((object ts, EventArgs te) =>
            {         
               for (int i = 0; i < mTestTenKBUsers.Count; i++)
               {
                    mTestTenKBUsers[i].OnTimerTick(UpdateTick);
               }

                if (IsAutoTest)
                {
                    if (IsProgressFailed() && MainWindow.Instance.InfiniteReTryFailedRepeatCheck_10KBTest.IsChecked == true)
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
                    if (mMainStatus.mLoginSuccessCount != 0 && mMainStatus.mLoginSuccessCount == mTestTenKBUsers.Count)
                    {
                        if (mbStartSend == false)
                        {
                            MainWindow.Instance.buttonSendData_Manaul.IsEnabled = true;
                            MainWindow.Instance.buttonSendData_Manaul.Visibility = Visibility.Visible;
                        }
                        //PrintStatus(1, "{0} User Login Success Plz SendData Push!!", mTestTenKBUsers.Count);
                    }
                    else
                    {
                        MainWindow.Instance.buttonSendData_Manaul.IsEnabled = false;
                        MainWindow.Instance.buttonSendData_Manaul.Visibility = Visibility.Hidden;
                    }
                }
            });

            m_TenKBTimer.Interval = new TimeSpan(0, 0, 0, 0, UpdateTick);//, 0, UpdateTick);
            m_TenKBTimer.Start();
        }

        private void CreateGroup()
        {
            if (mTestTenKBUsers.Count == 0)
                return;

            // Create Group
            int InUserCountGroup = Convert.ToInt32(MainWindow.Instance.TenKBInGroupUserCount.Text);
            mTotalGroup = mTestTenKBUsers.Count / InUserCountGroup;
            if ((mTestTenKBUsers.Count % InUserCountGroup) != 0)
                mTotalGroup++;

            for (int i = 0; i < mTotalGroup; i++)
            {
                mTestTenKBUserGroups.Add(i, new List<StressTest_TenKBUser>());
                mTestGroupStatus.Add(new GroupStatus());
            }

            for (int GroupIndex = 0; GroupIndex < mTotalGroup; GroupIndex++)
            {
                for (int j = 0; j < InUserCountGroup; j++)
                {
                    int TempIndex = (GroupIndex * InUserCountGroup) + j;
                    if (TempIndex >= mTestTenKBUsers.Count)
                        break;

                    mTestTenKBUsers[TempIndex].GroupID = GroupIndex;
                    mTestTenKBUserGroups[GroupIndex].Add(mTestTenKBUsers[TempIndex]);
                }
            }
        }

        private readonly object FromProgramClick = new object();

        private void RunConnectGroup(int GroupIndex, NetAddress serverAddress)
        {
            if(GroupIndex >= mTestTenKBUserGroups.Count )
                return;

            List<StressTest_TenKBUser> TestUsers = mTestTenKBUserGroups[GroupIndex];

            for (int i = 0; i < TestUsers.Count; i++)
            {
                TestUsers[i].RunConnect(serverAddress,
                       (StressTest_TenKBUser user) =>
                       {
                           mMainStatus.mLoginCurrectConnectedUser++;
                           mTestGroupStatus[user.GroupID].mLoginCurrectConnectedUser++;
                          
                           UpdateTestUserStateUI();
                       },
                       (StressTest_TenKBUser user, SF.Net.SendMessageLogin l) =>
                       {
                           if (l == null)
                               return;

                           mMainStatus.mLoginCurrectConnectedUser--;
                           mTestGroupStatus[user.GroupID].mLoginCurrectConnectedUser--;

                           UpdateTestUserStateUI();
                       },
                       (StressTest_TenKBUser user) =>
                       {
                           mMainStatus.mLoginFailedConnectUser++;
                           mTestGroupStatus[user.GroupID].mLoginFailedConnectUser++;
                           UpdateTestUserStateUI();
                       },
                       (StressTest_TenKBUser user, bool loginSuccess) =>
                       {
                           if (loginSuccess)
                           {
                               mMainStatus.mLoginSuccessCount++;
                               mTestGroupStatus[user.GroupID].mLoginSuccessCount++;

                              
                               int InGroupUserCount = mTestTenKBUserGroups[user.GroupID].Count;
                               if (mTestGroupStatus[user.GroupID].mLoginSuccessCount == (InGroupUserCount))
                               {
                                   mCurTestLoginSuccessfulGroupCount++;
                               }

                               if (IsAutoTest)
                               {
                                   user.NextState = StressTest_TenKBUser.eTesterState.SENDING;

                                   for (int tk = 0; tk < 10; tk++)
                                   {
                                       var result = user.m_Login.DataTestCmd(mTestSendData);
                                       if (result == 0)
                                       {
                                           mMainStatus.m_TenKBSendCount++;
                                           mTestGroupStatus[user.GroupID].m_TenKBSendCount++;
                                       }
                                   }
                               }
                               else
                               {
                                   user.NextState = StressTest_TenKBUser.eTesterState.SEND_WAIT;
                                   if (mTestGroupStatus[user.GroupID].mLoginSuccessCount == (InGroupUserCount))
                                   {
                        
                                       RunConnectGroup(mCurTestLoginSuccessfulGroupCount, mServerAddress);
                                   }
                               }
                           }
                           else
                           {
                               mMainStatus.mLoginFailedCount++;
                               mTestGroupStatus[user.GroupID].mLoginFailedCount++;
                           }
                           UpdateTestUserStateUI();
                       },
                       (StressTest_TenKBUser user, bool SendSuccess) =>
                       {
                           if (SendSuccess)
                           {
                               mMainStatus.m_TenKBSendSuccess++;
                               mTestGroupStatus[user.GroupID].m_TenKBSendSuccess++;
                           }
                           else
                           {
                               mMainStatus.m_TenKBSendFailed++;
                               mTestGroupStatus[user.GroupID].m_TenKBSendFailed++;
                           }

                           UpdateTestUserStateUI();

                           if (IsAutoTest)
                           {
                               int InGroupUserCount = mTestTenKBUserGroups[user.GroupID].Count;
                               if (mTestGroupStatus[user.GroupID].m_TenKBSendSuccess == (InGroupUserCount * 10))
                               {
                                   mCurTestSendSuccessfulGroupCount++;

                                   RunConnectGroup(mCurTestSendSuccessfulGroupCount, mServerAddress);

                                   if (MainWindow.Instance.InfiniteRepeatCheck_10KBTest.IsChecked == true && mCurTestSendSuccessfulGroupCount == mTotalGroup)
                                   {
                                       System.Threading.Tasks.Task.Delay(3000).ContinueWith(t =>
                                       {
                                           MainWindow.Instance.buttonDataTest_cp.Dispatcher.Invoke(new UpdateButtonPress_Delegate(delegate ()
                                           {
                                               mReTryCount++;
                                               RoutedEventArgs evt = new RoutedEventArgs(Button.ClickEvent, null);
                                               MainWindow.Instance.buttonDataTest_cp.RaiseEvent(evt);
                                           }));
                                       });
                                   }
                               }
                           }
                           else
                           {

                               int InGroupUserCount = mTestTenKBUserGroups[user.GroupID].Count;
                               if (mTestGroupStatus[user.GroupID].m_TenKBSendSuccess == (InGroupUserCount))
                               {
                                   mCurTestSendSuccessfulGroupCount++;
                                   RunSendGroup(mCurTestSendSuccessfulGroupCount);
                               }
                           }
                       }
                );
            }
        }

        void RunSendGroup(int GroupIndex)
        {
            if (IsAutoTest)
                return;

            if (GroupIndex >= mTestTenKBUserGroups.Count)
                return;


            List<StressTest_TenKBUser> TestUsers = mTestTenKBUserGroups[GroupIndex];
            for (int i = 0; i < TestUsers.Count; i++)
            {
                StressTest_TenKBUser user = TestUsers[i];

                user.NextState = StressTest_TenKBUser.eTesterState.SENDING;

                for (int tk = 0; tk < 10; tk++)
                {
                    var result = user.m_Login.DataTestCmd(mTestSendData);
                    if (result == 0)
                    {
                        mMainStatus.m_TenKBSendCount++;
                        mTestGroupStatus[user.GroupID].m_TenKBSendCount++;
                    }
                }
            }

            UpdateTestUserStateUI();
        }
        //mCurTestSendSuccessfulGroupCount);
        //public void 

        public bool IsProgressFailed()
        {
            if (mMainStatus.mLoginFailedConnectUser > 0)
                return true;

            if( mMainStatus.mLoginFailedCount > 0)
                return true;

            if (mMainStatus.m_TenKBSendFailed > 0)
                return true;

            if (mCurTestSendSuccessfulGroupCount == mTotalGroup)
                return false;

            if (!mTestTenKBUserGroups.ContainsKey(mCurTestSendSuccessfulGroupCount))
                return true;

            foreach (StressTest_TenKBUser user in mTestTenKBUserGroups[mCurTestSendSuccessfulGroupCount])
            {
                if (user.CurState == StressTest_TenKBUser.eTesterState.COMPLTE)
                    continue;

                if (user.CurState == StressTest_TenKBUser.eTesterState.NONE)
                    continue;

                if (user.m_ConnectionLogin == null)
                    return true;

                if (user.m_ConnectionLogin.State == SFConnection.ConnectionState.DISCONNECTED)
                    return true;
            }
            return false;
        }


        public void SendTenKBManaul()
        {
            if (mMainStatus.mLoginCurrectConnectedUser != mTestTenKBUsers.Count)
                return;

            if (mCurTestSendSuccessfulGroupCount != 0)
                return;

            if (mbStartSend)
                return;

            mbStartSend = true;
            MainWindow.Instance.buttonSendData_Manaul.IsEnabled = false;
            RunSendGroup(mCurTestSendSuccessfulGroupCount);
        }
    }
}

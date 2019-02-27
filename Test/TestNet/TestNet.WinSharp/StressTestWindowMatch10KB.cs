
﻿using System;
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
    public class StressTestWindowMatch10KB
    {

        List<StressTest_Matched_Chat> mTestMatchedChatUsers = new List<StressTest_Matched_Chat>();

        StressTest_Matched_Chat mPartyBoss = null;
        DispatcherTimer m_MatchedChatTestTimer;

        public int mLoginCurrectConnectedUser = 0;

        public int mPartyGameSvrCurrectConnectedUser = 0;
        int mPartyGameSvrFailedConnectUser = 0;

        int mPartyGameSuccessJoinCount = 0;
        int mPartyGameJoinedCount = 0;
        
        int mPartyOneKBChatSendCount = 0;
        int mPartyOneKBChatSendSuccessCount = 0;

        long mPartyChatLAverageValue = 0;
        int mPartyChatRecevice_FinishUserCount = 0;

        public int mLoginFailedUserCount = 0;

        int mFailedReTryCount = 0;

        string mCurPartyBossName = "";

        Thread mWaitFullJoin = null;

        long mCurDealyReTryTime = 0;

        public static readonly int SendChatRepeatCount = 10;

        string[] mTestSend1KBData = new string[SendChatRepeatCount];// string.Empty;
        DateTime[] mPartyChatSendTime = new DateTime[SendChatRepeatCount];//.MaxValue;

        int mTickCount = 0;
        int UpdateTick = 30;

        public void InitStressTest()
        {
            int ChatDataTestSize = 1024 / 2;

            for (int i = 0; i < SendChatRepeatCount; i++)
            {                
                // 65 A ~~~
                char d = (char) (65 +i);
                mTestSend1KBData[i] = string.Empty;

               mTestSend1KBData[i] = mTestSend1KBData[i].PadRight(ChatDataTestSize, d);

               mPartyChatSendTime[i] = DateTime.MaxValue;
            }

            var StresssTestGameID = "MyTownHero";

            MainWindow.InitGameIDComboBox(MainWindow.Instance.stress_comboBoxGameID_Matced10KB, StresssTestGameID);
            MainWindow.Instance.stress_comboBoxGameID_Matced10KB.SelectedItem =
             ServerAddressRegistry.ReadGameID(2, StresssTestGameID).ToString();

//            UpdateTestUserStateUI();
        }

        void _PrintStatus(int Screen, string text)
        {
            if (Screen == 0)
                return;

            MainWindow.Instance.textOutput3.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.textOutput3.Text = MainWindow.Instance.textOutput3.Text + ("\n" + text);

                MainWindow.Instance.StressTestLogScrollViewer3.ScrollToBottom();
                System.Diagnostics.Debug.WriteLine(text);
            }));

        }

        void PrintStatus(int Screen, string format, params object[] args)
        {
            string log = string.Format(format, args);

            _PrintStatus(Screen, log);

            mLoger.WriteToLog(log);
        }

        SimpleLog mLoger = new SimpleLog("Party");
      
        public delegate void UpdateTextLabel_Delegate();
        public delegate void UpdateButtonPress_Delegate();

        public void OnClosed()
        {
            CloseAllConnections();
        }


        private void UpdateMatchedChatTestStatueUI()
        {
            MainWindow.Instance.UpdateTotalUserCount();

            MainWindow.Instance.L_CurPartyTestGameConnectedUser.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurPartyTestGameConnectedUser.Content = mPartyGameSvrCurrectConnectedUser.ToString();
            }));

            MainWindow.Instance.L_CurGameSuccessPartyChatUser.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_CurGameSuccessPartyChatUser.Content = mPartyGameSuccessJoinCount.ToString();
            }));

            MainWindow.Instance.L_PartyJoinedUserCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_PartyJoinedUserCount.Content = mPartyGameJoinedCount.ToString();
            }));

            MainWindow.Instance.L_ChatOneKBSendCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_ChatOneKBSendCount.Content = mPartyOneKBChatSendCount.ToString();
            }));

            MainWindow.Instance.L_ChatOneKBSendSuccessCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_ChatOneKBSendSuccessCount.Content = mPartyOneKBChatSendSuccessCount.ToString();
            }));

            MainWindow.Instance.L_ChatAverageValue.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_ChatAverageValue.Content = string.Format("{0}ms", (mPartyChatLAverageValue));
                        //.ToString();
                    }));

            MainWindow.Instance.L_MatchChatRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_MatchChatRepeatCount.Content = mReTryCount.ToString();
            }));

            MainWindow.Instance.L_MatchedLoginFailed.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_MatchedLoginFailed.Content = mLoginFailedUserCount.ToString();
            }));

            MainWindow.Instance.L_MatchChatReTryFailedRepeatCount.Dispatcher.Invoke(new UpdateTextLabel_Delegate(delegate ()
            {
                MainWindow.Instance.L_MatchChatReTryFailedRepeatCount.Content = mFailedReTryCount.ToString();
            }));
        }

        void CloseAllConnections()
        {
            if (mWaitFullJoin != null)
            {
                mWaitFullJoin.Abort();

                if (mWaitFullJoin.IsAlive)
                    mWaitFullJoin.Join();
            }

            mWaitFullJoin = null;

            for (int i = 0; i < mTestMatchedChatUsers.Count; i++)
            {
                mTestMatchedChatUsers[i].CloseAllConnections();
                mTestMatchedChatUsers[i].UnInitEngine();
            }

            mTestMatchedChatUsers.Clear();

            if (m_MatchedChatTestTimer != null)
                m_MatchedChatTestTimer.Stop();

            m_MatchedChatTestTimer = null;

            mPartyBoss = null;

        }

        //void UpdateServerAddressUI()
        //{
       
        //    //ServerAddressRegistry.SaveServerAddressToRegistry();
        //}

        string MakeStreesTestUserID(int StartID, string PrefIxName, int AppedID)
        {
            return PrefIxName + "_PartyChatTest" + (StartID + AppedID).ToString();
        }

        private void InitStatusValue()
        {
            mCurDealyReTryTime = 0;
            mPartyGameSvrCurrectConnectedUser = 0;
            mPartyGameSvrFailedConnectUser = 0;
            mPartyGameSuccessJoinCount = 0;
            mPartyGameJoinedCount = 0;
            mPartyOneKBChatSendCount = 0;
            mPartyOneKBChatSendSuccessCount = 0;
            mPartyChatRecevice_FinishUserCount = 0;

            mCurPartyBossName = string.Empty;

            for(int i=0;i < SendChatRepeatCount; i++)
                mPartyChatSendTime[i] = DateTime.MaxValue;

            mPartyChatLAverageValue = 0;
            mLoginCurrectConnectedUser = 0;
            mLoginFailedUserCount = 0;

        }
        int mReTryCount = 0;

        // Matched And 10KB Chat Test
        public void StartTest(bool bAutoClick, int ClickIndex)
        {
            string PreFixUserID = MainWindow.Instance.PreFixUserID.Text.Trim();
            if (string.IsNullOrEmpty(PreFixUserID))
            {
                MessageBox.Show("Enter valid PreFixUserID");
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
                PrintStatus(1, "ReTry PartyChat Test!!");

            if (bAutoClick == true && ClickIndex == 2)
                mFailedReTryCount++;

            CloseAllConnections();
            InitStatusValue();

            UpdateMatchedChatTestStatueUI();

            MainWindow.Instance.textOutput3.Text = string.Empty;
            var StresssTestGameID = MainWindow.GetGameIDFromUI(MainWindow.Instance.stress_comboBoxGameID_Matced10KB);


            for (int i = 0; i < 4; i++)
            {
                StressTest_Matched_Chat TestMatchedChatUser = new StressTest_Matched_Chat();
                TestMatchedChatUser.InitEngine();
                TestMatchedChatUser.SetPrintHanlde(PrintStatus);

                TestMatchedChatUser.m_LoginID = MakeStreesTestUserID(PrefixStartID, PreFixUserID, i);

                if (i == 0)
                {
                    TestMatchedChatUser.IsPartyBoss = true;
                    mCurPartyBossName = TestMatchedChatUser.m_LoginID;

                    this.mPartyBoss = TestMatchedChatUser;
                }
                else
                    TestMatchedChatUser.IsPartyBoss = false;

                TestMatchedChatUser.gameID = StresssTestGameID;
                mTestMatchedChatUsers.Add(TestMatchedChatUser);
            }


            UpdateMatchedChatTestStatueUI();

            ServerAddressRegistry.SaveGameID(2, StresssTestGameID);
            NetAddress serverAddress = MainWindow.Instance.GetServerAddressFromUI(1, MainWindow.Instance.stress_comboBoxIPAddress,
                () =>
                {
                   MainWindow.InitIPAdressComboBox(MainWindow.Instance.stress_comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(1));
                });

            //mLoginCurrectConnectedUser

            for (int i = 0; i < mTestMatchedChatUsers.Count; i++)
            {
                mTestMatchedChatUsers[i].RunConnect(serverAddress,
                    (StressTest_Matched_Chat user) =>
                    {
                        mLoginCurrectConnectedUser++;
                        UpdateMatchedChatTestStatueUI();
                    },
                    (StressTest_Matched_Chat user, SF.Net.SendMessageLogin l) =>
                    {
                        if(l != null)
                            mLoginCurrectConnectedUser--;

                        UpdateMatchedChatTestStatueUI();
                    },
                    (StressTest_Matched_Chat user, int FailedIndex) =>
                    {
                        mLoginFailedUserCount++;
                        UpdateMatchedChatTestStatueUI();
                    },
                    (StressTest_Matched_Chat user) =>
                    {
                        mPartyGameSvrCurrectConnectedUser++;
                        UpdateMatchedChatTestStatueUI();
                    },
                    (StressTest_Matched_Chat user, SF.Net.SendMessageGame l) =>
                    {
                        if(l != null)
                            mPartyGameSvrCurrectConnectedUser--;

                        UpdateMatchedChatTestStatueUI();
                    },
                    (StressTest_Matched_Chat user) =>
                    {
                        mPartyGameSvrFailedConnectUser++;
                        UpdateMatchedChatTestStatueUI();
                    },

                    ///
                    (StressTest_Matched_Chat user, bool Success) =>
                    {
                        if (Success)
                            mPartyGameSuccessJoinCount++;

                        UpdateMatchedChatTestStatueUI();
                    },

                    // Party Create Res
                    (StressTest_Matched_Chat user) =>
                    {
                        if (!user.IsPartyBoss)
                            return;

                        if (mWaitFullJoin != null)
                        {
                            MessageBox.Show("WaitFullJoin did not Stop!!");
                            return;
                        }

                        mPartyGameJoinedCount++;
                        UpdateMatchedChatTestStatueUI();

                        DateTime StartWaitTime = DateTime.Now;

                        mWaitFullJoin = new Thread(new ThreadStart(() =>
                        {
                            bool IsFullReadyJoin = false;
                            while (!IsFullReadyJoin)
                            {
                                if ((StartWaitTime - DateTime.Now).Seconds > 10)
                                {
                                    PrintStatus(1, "Plz Retry Chat Test!!");
                                    break;
                                }

                                if (mPartyGameSuccessJoinCount == 4)
                                {
                                    int FreeUserCount = 0;
                                    for (int j = 0; j < mTestMatchedChatUsers.Count; j++)
                                    {
                                        if (mTestMatchedChatUsers[j].IsPartyBoss)
                                        {
                                            if (mTestMatchedChatUsers[j].CurState == StressTest_Matched_Chat.eTesterState.PARTY_MATCING)
                                                FreeUserCount++;
                                        }
                                        else
                                        {
                                            if (mTestMatchedChatUsers[j].CurState == StressTest_Matched_Chat.eTesterState.PARTY_WAIT_INVITE)
                                                FreeUserCount++;
                                        }
                                    }

                                    if (FreeUserCount == 4)
                                    {
                                         IsFullReadyJoin = true;
                                         break;
                                    }
                                }
                                Thread.Sleep(1000);
                            }

                            if (IsFullReadyJoin)// == 4)
                            {
                                PrintStatus(1, "FullJoin!! Do it Test Invite");
                                OnTestPartyChatInvite();
                            }
                        }));

                        mWaitFullJoin.Start();
                    },
                    // Party Joined
                    (StressTest_Matched_Chat user, bool success) =>
                    {
                        if (success)
                        {
                            mPartyGameJoinedCount++;
                            UpdateMatchedChatTestStatueUI();

                            if (mPartyGameJoinedCount == 4)
                            {                               
                                //-- for..
                                for (int j = 0; j < mTestMatchedChatUsers.Count; j++)
                                {
                                    if (mTestMatchedChatUsers[j].IsPartyBoss)
                                        mTestMatchedChatUsers[j].NextState = StressTest_Matched_Chat.eTesterState.SEND_CHATING;
                                    else
                                        mTestMatchedChatUsers[j].NextState = StressTest_Matched_Chat.eTesterState.WAIT_RECV_CHATING;
                                }
                                
                                // Send 1KB Chat Repeat 10
                                for (int scc = 0; scc < SendChatRepeatCount; scc++)
                                {
                                    if (mPartyBoss.m_Game.PartyChatMessageCmd(0, mTestSend1KBData[scc]) == 0)
                                    {
                                        mPartyOneKBChatSendCount++;

                                        mPartyChatSendTime[scc] = DateTime.Now;
                                        PrintStatus(1, "Send 1KB Chat Repeat {0} Time = {1}  / {2}", scc, mPartyChatSendTime[scc].ToString("hh/mm/ss.fff"), mPartyBoss.m_LoginID);
                                    }
                                }

                                //PrintStatus(1, "Send 1KB Chat Repeat {0} Time = {1} ", SendChatRepeatCount, mPartyChatSendTime.ToString("hh/mm/ss.fff"));
                                UpdateMatchedChatTestStatueUI();
                            }
                        }
                        else
                        {

                        }
                    },
                    (StressTest_Matched_Chat user, bool success) =>
                    {
                        if (!user.IsPartyBoss)
                            return;

                        if (success)
                        {
                            mPartyOneKBChatSendSuccessCount++;
                            UpdateMatchedChatTestStatueUI();
                        }
                    },
                    (StressTest_Matched_Chat user) =>
                    {
                        mPartyChatRecevice_FinishUserCount++;

                        if (!user.IsPartyBoss)
                        {
                            // 1KB Recved 10                        
                            mPartyChatLAverageValue = user.GetChatRecved_AverageValue(mPartyChatSendTime[0]);
                            PrintStatus(1, "Receviced 10KB Average Speed = {0}ms / ID ={1}", mPartyChatLAverageValue, user.m_LoginID);
                            UpdateMatchedChatTestStatueUI();
                        }

                        if (mPartyChatRecevice_FinishUserCount == 4)
                        {
                            if (MainWindow.Instance.InfiniteRepeatCheck.IsChecked == true)
                            {
                                System.Threading.Tasks.Task.Delay(3000).ContinueWith(t =>
                                {
                                    MainWindow.Instance.btnStressTestMatched_Cp_Chat.Dispatcher.Invoke(new UpdateButtonPress_Delegate(delegate ()
                                    {
                                        
                                        mReTryCount++;
                                        MainWindow.Instance.btnStressTestMatched_Cp_Chat.RaiseEvent(new RoutedEventArgs(Button.ClickEvent));
                                    }));
                                });
                            }
                        }
                    }
                    );
            }

            m_MatchedChatTestTimer = new DispatcherTimer();
            m_MatchedChatTestTimer.Tick += new EventHandler(
                     (object ts, EventArgs te) =>
                     {
                         for (int i = 0; i < mTestMatchedChatUsers.Count; i++)
                         {
                             mTestMatchedChatUsers[i].OnTimerTick(UpdateTick);
                         }

                         if (IsProgressFailed() && MainWindow.Instance.InfiniteReTryFailedRepeattCheck_MatchChat.IsChecked == true)
                         {
                             mCurDealyReTryTime += UpdateTick;
                             if(mCurDealyReTryTime >=1000)
                             {
                                 mTickCount++;
                                 mCurDealyReTryTime = 0;
                                 PrintStatus(1, "Plz ReTry Test!! {0}..", 3 - mTickCount);
                                 if (mTickCount == 3)
                                    this.StartTest(true, 2);
                             }
                         }
                     });

            m_MatchedChatTestTimer.Interval = new TimeSpan(0, 0, 0,0, UpdateTick);
            m_MatchedChatTestTimer.Start();
        }

     
        private void OnTestPartyChatInvite()
        {
            if (mPartyGameSuccessJoinCount != 4)
                return;

            StressTest_Matched_Chat PartyBoss = mTestMatchedChatUsers.Find(ply => ply.IsPartyBoss == true);

            if (PartyBoss == null)
                return;

            for (int i = 0; i < mTestMatchedChatUsers.Count; i++)
            {
                if (PartyBoss == mTestMatchedChatUsers[i])
                    continue;

                ulong UserAccountID = mTestMatchedChatUsers[i].m_AccountID;
                ulong PartyUID = mTestMatchedChatUsers[i].m_PartyUID;
                if (PartyUID == 0)
                {
                    PartyBoss.m_Game.PartyInviteCmd(0, UserAccountID);
                    PrintStatus(1, "Send PartyInviteCmd TargetID = {0}", UserAccountID);
                }
                else
                {
                    PrintStatus(1, "{0} is has Party!! PariyID = {1} ", mTestMatchedChatUsers[i].m_LoginID, PartyUID);
                }
            }
        }

        public bool IsProgressFailed()
        {            
            if (mPartyGameSvrFailedConnectUser > 0)
                return true;

            if (mLoginFailedUserCount > 0)
                return true;

            foreach (StressTest_Matched_Chat user in mTestMatchedChatUsers)
            {
                if (user.CurState == StressTest_Matched_Chat.eTesterState.COMPLTE)
                    continue;

                if (user.CurState == StressTest_Matched_Chat.eTesterState.NONE)
                    continue;

                if (user.CurState == StressTest_Matched_Chat.eTesterState.LOGINING)
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
    }
}


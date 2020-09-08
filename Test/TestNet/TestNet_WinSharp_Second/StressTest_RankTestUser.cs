using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using Microsoft.Win32;
using System.Windows.Threading;

namespace TestNet.WinSharp
{
    class StressTest_RankTestUser
    {
      //  SFEngine m_Engine;
        SFMessageRouter m_MessageRouter = new SFMessageRouter();
        SFConnection m_ConnectionLogin;

        //public SF.Net.SendMessageGame m_Game;
        public SF.Net.SendMessageLogin m_Login;

        SFConnectionGroup m_ConnectionManagermentGroup = new SFConnectionGroup(1024);

        UInt64 m_LoginTicket;
        UInt64 m_AccountID;
        UInt64 m_LoginEntityID;
        NetAddress m_GameServerAddress;

        public string m_LoginID;

        DispatcherTimer m_Timer;

        string m_GameID = "MyTownHero";
        public string gameID
        {
            get { return m_GameID; }
            set { m_GameID = value;}
        }

        System.Action<StressTest_RankTestUser> mLoginConnectedAction = null;
        System.Action<StressTest_RankTestUser, SF.Net.SendMessageLogin> mLoginDisConnectedAction = null;


        public bool IsLogin()
        {
            if (m_ConnectionLogin == null)
                return false;

            if (m_ConnectionLogin.State == SFConnection.ConnectionState.CONNECTED)
                return true;

            return false;
        }
        public void InitEngine()
        {         
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, 0, HandleLoginRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.UpdateMyScoreRes, 0, HandleScoreRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.DebugPrintALLRankingRes, 0, HandleDebugPrintALLRankingRes);
        }

        public void UnInitEngine()
        {
            m_MessageRouter = null;
        }

        public void Dispose()
        {
            CloseAllConnections();

            if(m_ConnectionManagermentGroup != null)
                m_ConnectionManagermentGroup.Dispose();
            m_ConnectionManagermentGroup = null;          
        }
        public void CloseAllConnections()
        {
            if (m_ConnectionLogin != null)
                m_ConnectionLogin.Dispose();
            m_ConnectionLogin = null;
         
            if(m_Timer != null)
                m_Timer.Stop();

            m_Timer = null;
        }

        public void RunConnect(NetAddress serverAddress,
           System.Action<StressTest_RankTestUser> OnLoginConnected,
           System.Action<StressTest_RankTestUser, SF.Net.SendMessageLogin> OnLoginDisConnected)
        {
            m_ConnectionLogin = new SFConnection(m_MessageRouter);
            m_ConnectionLogin.Connect(0, serverAddress.Address, (int)serverAddress.Port);

            mLoginConnectedAction = OnLoginConnected;
            mLoginDisConnectedAction = OnLoginDisConnected;

            m_Timer = new DispatcherTimer();
            m_Timer.Tick += new EventHandler(OnTimerTick);
            m_Timer.Interval = new TimeSpan(0, 0, 1);
            m_Timer.Start();
        }

        System.Action<string, object[]> mPritHanlde = null;
        public void SetPrintHanlde(System.Action<string, object[]> hanlde)
        {
            mPritHanlde = hanlde;
        }

        void PrintStatus(string format, params object[] args)
        {
            if (mPritHanlde != null)
                mPritHanlde(format, args);

        }

        void HandleLoginConnectionEvent(SFConnection.Event conEvent)
        {
            switch (conEvent.EventType)
            {
                case SFConnection.EventTypes.EVT_STATE_CHANGE:
                    PrintStatus("Login Connection state chagned {0}", conEvent.State);
                    break;
                case SFConnection.EventTypes.EVT_CONNECTION_RESULT:
                    PrintStatus("Login Connection result {0}", conEvent.HResult);
                    if (conEvent.HResult.IsSucceeded)
                    {
                        m_Login = new SF.Net.SendMessageLogin(m_ConnectionLogin);
                        m_Login.CreateRandomUserCmd(0, StringCrc32.HashString(m_GameID), m_LoginID);

                        if (mLoginConnectedAction != null)
                            mLoginConnectedAction(this);
                    }
                    break;
                case SFConnection.EventTypes.EVT_DISCONNECTED:
                    {
                        PrintStatus("Login Connection disconnected");
                        if (mLoginDisConnectedAction != null)
                            mLoginDisConnectedAction(this, m_Login);
                    }
                    break;
            }
        }

      

        private void OnTimerTick(object sender, EventArgs e)
        {
            SFConnection.Event conEvent;
            // Individual connection update loop
            if (m_ConnectionLogin != null)
            {
                var result = m_ConnectionLogin.DequeueEvent(out conEvent);
                while (result)
                {
                    HandleLoginConnectionEvent(conEvent);
                    result = m_ConnectionLogin.DequeueEvent(out conEvent);
                }

                m_ConnectionLogin.UpdateMessageQueue();
            }


            // Connection Group management
            if (m_ConnectionManagermentGroup != null)
            {
                SFConnectionGroup.EventInformation eventInfo;
                IntPtr connectionNativeHandle = m_ConnectionManagermentGroup.DequeueConnectionEvent(out eventInfo);
                if (connectionNativeHandle != null)
                {
                    if (eventInfo.pMsg != null)
                    {
                        // You can separate message handling
                        // 1. By having separate message router per connection
                        m_MessageRouter.HandleRecvMessage(eventInfo.pMsg);
                    }
                    else if (m_ConnectionLogin != null && m_ConnectionLogin.NativeHandle == connectionNativeHandle)
                    {
                        HandleLoginConnectionEvent(eventInfo.Event);
                    }
           

                    eventInfo.Dispose();
                }
            }
        }

        void HandleLoginRes(SFMessage message)
        {
            var loginResult = message.GetValue<Result>("Result");
            if (loginResult.IsFailed)
            {
                PrintStatus("Login failed {0}", loginResult);
                CloseAllConnections();
                return;
            }

            m_LoginTicket = message.GetValue<UInt64>("Ticket");
            m_AccountID = message.GetValue<UInt64>("AccID");
            m_GameServerAddress = message.GetValue<NetAddress>("GameServerAddrIPV4");
            m_LoginEntityID = message.GetValue<UInt64>("LoginEntityUID");

            Random rand = new Random();
            m_Login.UpdateMyScoreCmd(0, (ulong)rand.Next() % 5000, RankingType.World, 10);
        }

        public void SaveRankData(string FileName)
        {
            if (m_Login == null)
                return;

            PrintStatus("Request Save Rank Data!!");
            m_Login.DebugPrintALLRankingCmd(0, FileName);
        }

        void HandleScoreRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus("Login failed {0}", result);
                return;
            }

            PrintStatus("MyPlayerID {0}", m_AccountID);
            var rankingInfos = message.GetValue<TotalRankingPlayerInformation[]>("Ranking");
            foreach (var ranking in rankingInfos)
                PrintStatus("Ranking info {0}", ranking);
        }

        void HandleDebugPrintALLRankingRes(SFMessage message)
        {
            PrintStatus("HandleDebugPrintALLRankingRes");
        }
    }
}

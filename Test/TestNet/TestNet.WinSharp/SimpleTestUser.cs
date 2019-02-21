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
    class SimpleTestUser
    {
      //  SFEngine m_Engine;
        SFMessageRouter m_MessageRouter = new SFMessageRouter();

        SFConnection m_ConnectionLogin;
        SFConnection m_ConnectionGame;

        public SF.Net.SendMessageGame m_Game;
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

        public void InitEngine()
        {         
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, 0, HandleLoginRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.UpdateMyScoreRes, 0, HandleScoreRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameServerRes, 0, HandleJoinGameServerRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.DataTestRes, 0, HandleDataTestRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.CreatePartyRes, 0, HandleCreatePartyRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GetFriendListRes, 0, HandleGetFriendListRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.RequestGameMatchRes, 0, HandleRequestGameMatchRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchedS2CEvt, 0, HandleGameMatchedS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchFailedS2CEvt, 0, HandleGameMatchFailedS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchingStartedS2CEvt, 0, HandleGameMatchingStartedS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchingCanceledS2CEvt, 0, HandleGameMatchingCanceledS2CEvt);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.DebugPrintALLRankingRes, 0, HandleDebugPrintALLRankingRes);


        }

        public void Dispose()
        {
            CloseAllConnections();

            if(m_ConnectionManagermentGroup != null)
                m_ConnectionManagermentGroup.Dispose();
            m_ConnectionManagermentGroup = null;

            m_MessageRouter = null;
        }

        public void CloseAllConnections()
        {
            if (m_ConnectionLogin != null)
                m_ConnectionLogin.Dispose();
            m_ConnectionLogin = null;

            if (m_ConnectionGame != null)
                m_ConnectionGame.Dispose();
            m_ConnectionGame = null;

            if(m_Timer != null)
                m_Timer.Stop();

            m_Timer = null;
        }

        public void RunConnect(NetAddress serverAddress)
        {
            m_ConnectionLogin = new SFConnection(m_MessageRouter);
            m_ConnectionLogin.Connect(0, serverAddress.Address, (int)serverAddress.Port);

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
                        m_Login.CreateRandomUserCmd(FixedString32.HashString(m_GameID), m_LoginID);
                    }
                    break;
                case SFConnection.EventTypes.EVT_DISCONNECTED:
                    PrintStatus("Login Connection disconnected");
                    break;
            }
        }

        void HandleGameConnectionEvent(SFConnection.Event conEvent)
        {
            switch (conEvent.EventType)
            {
                case SFConnection.EventTypes.EVT_STATE_CHANGE:
                    PrintStatus("Game Connection state chagned {0}", conEvent.State);
                    break;
                case SFConnection.EventTypes.EVT_CONNECTION_RESULT:
                    PrintStatus("Game Connection result {0}", conEvent.HResult);
                    if (conEvent.HResult.IsSucceeded)
                    {
                        m_Game = new SF.Net.SendMessageGame(m_ConnectionGame);
                        m_Game.JoinGameServerCmd(m_AccountID, m_LoginTicket, m_LoginEntityID);
                    }
                    break;
                case SFConnection.EventTypes.EVT_DISCONNECTED:
                    PrintStatus("Game Connection disconnected");
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


            if (m_ConnectionGame != null)
            {
                var result = m_ConnectionGame.DequeueEvent(out conEvent);
                while (result)
                {
                    HandleGameConnectionEvent(conEvent);
                    result = m_ConnectionGame.DequeueEvent(out conEvent);
                }
                m_ConnectionGame.UpdateMessageQueue();
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
                    else if (m_ConnectionGame != null && m_ConnectionGame.NativeHandle == connectionNativeHandle)
                    {
                        HandleGameConnectionEvent(eventInfo.Event);
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

            if (m_ConnectionLogin != null) m_ConnectionLogin.LocalPeerID = m_LoginTicket;


            //Random rand = new Random();
            //m_Login.UpdateMyScoreCmd((ulong)rand.Next() % 5000, RankingType.World, 10);

                // If the game has game servers, we need to connect to the game server
            if (!string.IsNullOrEmpty(m_GameServerAddress.Address))
            {
                if (m_ConnectionManagermentGroup != null)
                    m_ConnectionGame = new SFConnection(m_ConnectionManagermentGroup, m_MessageRouter);
                else
                    m_ConnectionGame = new SFConnection(m_MessageRouter);

                m_ConnectionGame.LocalPeerID = m_LoginTicket;
                m_ConnectionGame.Connect(m_LoginTicket, m_GameServerAddress.Address, m_GameServerAddress.Port);
            }
        }

        void HandleScoreRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus("Update Score failed {0:8X}", result);
                return;
            }

            PrintStatus("MyPlayerID {0}", m_AccountID);
            var rankingInfos = message.GetValue<TotalRankingPlayerInformation[]>("Ranking");
            foreach (var ranking in rankingInfos)
            {
                PrintStatus("Ranking info {0}", ranking);
            }
        }

        void HandleDataTestRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus("TestData failed {0}", result);
                return;
            }


            var testDatas = message.GetValue<byte[]>("TestData");
            PrintStatus("TestData Res {0}", testDatas.Length);
        }

        void HandleJoinGameServerRes(SFMessage message)
        {
            var joinResult = message.GetValue<Result>("Result");
            if (joinResult.IsFailed)
            {
                PrintStatus("Join game server failed {0}", joinResult);
                CloseAllConnections();
                return;
            }

            // When game server join is finished you can disconnect login connection
            if (m_ConnectionLogin != null)
            {
                m_ConnectionLogin.Dispose();
                m_ConnectionLogin = null;
            }

            m_Game.GetFriendListCmd(0,20);
            //m_Game.GetNotificationListCmd();
            //m_Game.RequestGameMatchCmd(4, (byte)PlayerRole.None);
            //m_Game.CreatePartyCmd();
        }

        void HandleRequestGameMatchRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus("Game match request failed {0}", result);
                return;
            }
            
        }

        void HandleCreatePartyRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus("CreateParty has failed {0}", result);
                return;
            }

        }


        void HandleGetFriendListRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus("Game friend list failed {0}", result);
                return;
            }

        }

        void HandleGameMatchedS2CEvt(SFMessage message)
        {
            PrintStatus("Game matched ");

        }

        void HandleGameMatchFailedS2CEvt(SFMessage message)
        {
            PrintStatus("HandleGameMatchFailedS2CEvt");

        }

        void HandleGameMatchingStartedS2CEvt(SFMessage message)
        {
            PrintStatus("HandleGameMatchingStartedS2CEvt ");

        }

        void HandleGameMatchingCanceledS2CEvt(SFMessage message)
        {
            PrintStatus("HandleGameMatchingCanceledS2CEvt");

        }

        void HandleDebugPrintALLRankingRes(SFMessage message)
        {
            PrintStatus("HandleDebugPrintALLRankingRes");
        }
    }
}

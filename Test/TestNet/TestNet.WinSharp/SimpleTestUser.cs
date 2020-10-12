using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using Microsoft.Win32;
using System.Windows.Threading;
using System.Security.Cryptography.X509Certificates;

namespace TestNet.WinSharp
{
    class TestAction : IDisposable
    {
        protected readonly SimpleTestUser Owner;

        public TestAction(SimpleTestUser owner)
        {
            Owner = owner;
        }

        public void Dispose()
        {
            Disposing();
        }

        virtual public void Disposing()
        { }

        virtual public void DoAction() { }

        public void PrintStatus(string format, params object[] args)
        {
            Owner.PrintStatus(format, args);
        }

        public void CloseAllConnections()
        {
            Owner.CloseAllConnections();
        }

        virtual public void OnLoginConnected() { }
        virtual public void OnGameConnected() { }

        public void RegisterMessageHandler(int messageID, int priority, Action<SFMessage> handler)
        {
            Owner.m_MessageRouter.RegisterMessageHandler(messageID, priority, handler);
        }

        public void UnregisterMessageHandler(int messageID, Action<SFMessage> handler)
        {
            Owner.m_MessageRouter.UnregisterMessageHandler(messageID, handler);
        }
    }

    class TestActionNop : TestAction
    {
        public TestActionNop(SimpleTestUser owner)
            : base(owner)
        {
        }

        override public void DoAction()
        {
        }
    }


    class TestActionConnectLogin : TestAction
    {
        public TestActionConnectLogin(SimpleTestUser owner)
            : base(owner)
        {
        }

        override public void DoAction()
        {
            Owner.m_ConnectionLogin = new SFConnection(Owner.m_MessageRouter);
            Owner.m_ConnectionLogin.Connect(0, Owner.m_LoginServerAddress.Address, (int)Owner.m_LoginServerAddress.Port);
        }

        override public void OnLoginConnected()
        {
            Owner.m_Login = new SF.Net.SendMessageLogin(Owner.m_ConnectionLogin);
            Owner.KickNextAction();
        }

    }

    class TestActionLogin : TestAction
    {
        public TestActionLogin(SimpleTestUser owner)
            : base(owner)
        {
        }

        override public void Disposing()
        {
            UnregisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, HandleLoginRes);
        }

        override public void DoAction()
        {
            RegisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, 0, HandleLoginRes);

            Owner.m_Login.CreateRandomUserCmd(0, StringCrc32.HashString(Owner.m_GameID), Owner.m_LoginID);
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

            Owner.m_LoginTicket = message.GetValue<UInt64>("Ticket");
            Owner.m_AccountID = message.GetValue<UInt64>("AccID");
            Owner.m_GameServerAddress = message.GetValue<NetAddress>("GameServerAddrIPV4");
            Owner.m_LoginEntityID = message.GetValue<UInt64>("LoginEntityUID");

            if (Owner.m_ConnectionLogin != null) Owner.m_ConnectionLogin.LocalPeerID = Owner.m_LoginTicket;

            PrintStatus("Login success Ticket:{0}, Acc:{1}, GameSvr:{2}, LoginEntity:{3}", Owner.m_LoginTicket, Owner.m_AccountID, Owner.m_GameServerAddress, Owner.m_LoginEntityID);
            //Random rand = new Random();
            //m_Login.UpdateMyScoreCmd((ulong)rand.Next() % 5000, RankingType.World, 10);

            // If the game has game servers, we need to connect to the game server
            if (!string.IsNullOrEmpty(Owner.m_GameServerAddress.Address))
            {
                if (Owner.m_ConnectionManagermentGroup != null)
                    Owner.m_ConnectionGame = new SFConnection(Owner.m_ConnectionManagermentGroup, Owner.m_MessageRouter);
                else
                    Owner.m_ConnectionGame = new SFConnection(Owner.m_MessageRouter);

                Owner.m_ConnectionGame.LocalPeerID = Owner.m_LoginTicket;
                Owner.m_ConnectionGame.Connect(Owner.m_LoginTicket, Owner.m_GameServerAddress.Address, Owner.m_GameServerAddress.Port);
            }
        }

    }


    class TestActionConnectGame : TestAction
    {
        public TestActionConnectGame(SimpleTestUser owner)
            : base(owner)
        {
        }

        override public void DoAction()
        {
            Owner.m_ConnectionGame = new SFConnection(Owner.m_MessageRouter);
            Owner.m_ConnectionGame.Connect(0, Owner.m_LoginServerAddress.Address, (int)Owner.m_LoginServerAddress.Port);
        }

        override public void OnGameConnected()
        {
            Owner.m_Game = new SF.Net.SendMessageGame(Owner.m_ConnectionGame);
            Owner.KickNextAction();
        }

    }

    class TestActionJoinGameServer : TestAction
    {
        public TestActionJoinGameServer(SimpleTestUser owner)
            : base(owner)
        {
        }

        override public void Disposing()
        {
            UnregisterMessageHandler(SF.Net.MessageIDGame.JoinGameServerRes, HandleJoinGameServerRes);
        }

        override public void DoAction()
        {
            RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameServerRes, 0, HandleJoinGameServerRes);

            Owner.m_Game.JoinGameServerCmd(0, Owner.m_AccountID, Owner.m_LoginTicket, Owner.m_LoginEntityID);
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
            if (Owner.m_ConnectionLogin != null)
            {
                Owner.m_ConnectionLogin.Dispose();
                Owner.m_ConnectionLogin = null;
            }

            //m_Game.GetFriendListCmd(0,20);
            //m_Game.GetNotificationListCmd();
            //m_Game.RequestGameMatchCmd(4, (byte)PlayerRole.None);
            //m_Game.CreatePartyCmd(0);
        }

    }


    class SimpleTestUser
    {
      //  SFEngine m_Engine;
        public SFMessageRouter m_MessageRouter = new SFMessageRouter();
        public NetAddress m_LoginServerAddress;

        public SFConnection m_ConnectionLogin;
        public SFConnection m_ConnectionGame;
        public DateTime m_GameHeartBitTime = DateTime.Now;

        public SF.Net.SendMessageGame m_Game;
        public SF.Net.SendMessageLogin m_Login;

        public SFConnectionGroup m_ConnectionManagermentGroup = new SFConnectionGroup(1024);

        public UInt64 m_LoginTicket;
        public UInt64 m_AccountID;
        public UInt64 m_LoginEntityID;
        public NetAddress m_GameServerAddress;

        public string m_LoginID;

        DispatcherTimer m_Timer;

        public string m_GameID = "MyTownHero";
        public string gameID
        {
            get { return m_GameID; }
            set { m_GameID = value;}
        }

        public void InitEngine()
        {         
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.UpdateMyScoreRes, 0, HandleScoreRes);
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

        List<TestAction> ActionList = new List<TestAction>();
        public void KickNextAction()
        {
            if (ActionList.Count > 0)
            {
                ActionList[0].Dispose();
                ActionList.RemoveAt(0);
            }

            if (ActionList.Count > 0)
                ActionList[0].DoAction();
        }

        public void ClearActions()
        {
            foreach (var action in ActionList)
                action.Dispose();

            ActionList.Clear();
        }

        public void RunConnect(NetAddress serverAddress)
        {
            m_Timer = new DispatcherTimer();
            m_Timer.Tick += new EventHandler(OnTimerTick);
            m_Timer.Interval = new TimeSpan(0, 0, 1);
            m_Timer.Start();

            m_LoginServerAddress = serverAddress;

            ClearActions();
            ActionList.Add(new TestActionNop(this)); // first one will be skipped by KickNextAction
            ActionList.Add(new TestActionConnectLogin(this));
            ActionList.Add(new TestActionLogin(this));
            ActionList.Add(new TestActionConnectGame(this));
            ActionList.Add(new TestActionJoinGameServer(this));
            KickNextAction();
        }

        System.Action<string, object[]> mPritHanlde = null;
        public void SetPrintHanlde(System.Action<string, object[]> hanlde)
        {
            mPritHanlde = hanlde;
        }

        public void PrintStatus(string format, params object[] args)
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
                        if (ActionList.Count > 0)
                            ActionList[0].OnLoginConnected();
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
                        if (ActionList.Count > 0)
                            ActionList[0].OnGameConnected();
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

                if(m_ConnectionGame != null && m_ConnectionGame.State == SFConnection.ConnectionState.CONNECTED && (DateTime.Now - m_GameHeartBitTime).Seconds > 10)
                {
                    m_GameHeartBitTime = DateTime.Now;
                    if (m_Game != null)
                        m_Game.HeartBitC2SEvt();
                }
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

            PrintStatus("PartyCreated {0}", message.GetValue<UInt64>("PartyUID"));
        }


        void HandleGetFriendListRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus("Game friend list failed {0}", result);
                return;
            }

            PrintStatus("Friend list");
            var friendList = message.GetValue<FriendInformation[]>("FriendList");
            foreach(var friend in friendList)
            {
                PrintStatus("    {0}:{1}", friend.PlayerID, friend.NickName);
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

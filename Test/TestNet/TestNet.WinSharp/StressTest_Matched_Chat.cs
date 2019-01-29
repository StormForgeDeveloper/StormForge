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
    public class StressTest_Matched_Chat
    {
        struct PartyChatMessageRecvInfo
        {
            public DateTime RecvTime;
            public int RecvChatSize;
            public string ChatMsg;
        };

        //  SFEngine m_Engine;
        SFMessageRouter m_MessageRouter = new SFMessageRouter();

        public SFConnection m_ConnectionLogin;
        public SFConnection m_ConnectionGame;

        public SF.Net.SendMessageGame m_Game;
        public SF.Net.SendMessageLogin m_Login;


        public string m_LoginID;

        UInt64 m_LoginTicket;
        public UInt64 m_AccountID;
        UInt64 m_LoginEntityID;
        NetAddress m_GameServerAddress;

        public bool IsPartyBoss { get; set; }

        public class PartyMatchedInfo : IDisposable
        {
            public UInt64 mPartyID;
            public List<PlayerInformation> mOtherPlayers = new List<PlayerInformation>();

            public PartyMatchedInfo(UInt64 PartyID)
            {
                mPartyID = PartyID;
            }

            public void Dispose()
            {
                mOtherPlayers.Clear();
                mOtherPlayers = null;
            }
        }

        PartyMatchedInfo m_PartyInfo = null;

        string m_GameID = "MyTownHero";

        int mRecvedPartyChatMessageCount = 0;

        public UInt64 m_PartyUID = 0;

        public int GetMatchedCount()
        {
            if (m_PartyInfo == null)
                return 0;

            return m_PartyInfo.mOtherPlayers.Count;
        }

        public string gameID
        {
            get { return m_GameID; }
            set { m_GameID = value; }
        }


        public enum eTesterState
        {
            NONE,
            LOGINING,
            GAME_LOGINING,
            PARTY_MATCING,
            PARTY_WAIT_INVITE,
            SEND_CHATING,
            WAIT_RECV_CHATING,
            COMPLTE,
        };

        eTesterState mCurState = eTesterState.NONE;
        public eTesterState CurState { get { return mCurState; } }

        eTesterState mNextState = eTesterState.NONE;
        public eTesterState NextState
        {
            set
            {
                if (mNextState != eTesterState.NONE)
                    PrintStatus(0,"Matched_Chat NextState Warring!!");

                mNextState = value;
            }
        }

        public void InitEngine()
        {
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, 0, HandleLoginRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameServerRes, 0, HandleJoinGameServerRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.CreatePartyRes, 0, HandleCreatePartyRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.LeavePartyRes, 0, HandleLeavePartyRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinPartyRes, 0, HandleJoinPartyRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PartyChatMessageRes, 0, HandlePartyChatMessageRes);


            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PartyInviteRes, 0, HandlePartyInviteRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PartyPlayerJoinedS2CEvt, 0, HandlePartyPlayerJoinedS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PartyPlayerLeftS2CEvt, 0, HandlePartyPlayerLeftS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PartyInviteRequestedS2CEvt, 0, HandlePartyInviteRequestedS2CEvt);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PartyChatMessageS2CEvt, 0, HandlePartyChatMessageS2CEvt);

        }

        public void UnInitEngine()
        {
            m_MessageRouter = null;

            if (m_ConnectionLogin != null)
                m_ConnectionLogin.Dispose();
            m_ConnectionLogin = null;

            if (m_ConnectionGame != null)
                m_ConnectionGame.Dispose();
            m_ConnectionGame = null;

            if (mRecvChatHistorys != null)
            {
                mRecvChatHistorys.Clear();
                mRecvChatHistorys = null;
            }
        }

        public void CloseAllConnections()
        {
            if (m_ConnectionGame != null)
            {
                if (m_ConnectionGame.State != SFConnection.ConnectionState.DISCONNECTED)
                {
                    if (mGameSvrDisConnectedAction != null)
                        mGameSvrDisConnectedAction(this, m_Game);
                }
            }

            if (m_ConnectionLogin != null)
            {
                if (m_ConnectionLogin.State != SFConnection.ConnectionState.DISCONNECTED)
                {
                    if (mLoginDisConnectedAction != null)
                        mLoginDisConnectedAction(this, m_Login);
                }
            }

            if (m_Login != null)
                m_Login = null;

            if (m_Game != null)
                m_Game = null;

            if (m_ConnectionLogin != null)
                m_ConnectionLogin.Dispose();
            m_ConnectionLogin = null;

            if (m_ConnectionGame != null)
                m_ConnectionGame.Dispose();
            m_ConnectionGame = null;

            if (m_PartyInfo != null)
                m_PartyInfo.Dispose();

            m_PartyInfo = null;

            mRecvChatHistorys.Clear();
        }

        System.Action<StressTest_Matched_Chat> mGameSvrConnectedAction = null;
        System.Action<StressTest_Matched_Chat, SF.Net.SendMessageGame> mGameSvrDisConnectedAction = null;
        System.Action<StressTest_Matched_Chat> mGameSvrFailedConnectAction = null;

        System.Action<StressTest_Matched_Chat, bool> mGameJoinResAction = null;
        System.Action<StressTest_Matched_Chat> mPartyCreateAction = null;

        System.Action<StressTest_Matched_Chat, bool> mGamePartyJoinedAction = null;

        System.Action<StressTest_Matched_Chat, bool> mPartyChatSendResAction = null;
        System.Action<StressTest_Matched_Chat> mPartyChatOneKBRecivedTen = null;

        System.Action<StressTest_Matched_Chat> mLoginConnectedAction = null;
        System.Action<StressTest_Matched_Chat, SF.Net.SendMessageLogin> mLoginDisConnectedAction = null;
        System.Action<StressTest_Matched_Chat, int> mLoginFailedAction = null;

        public void RunConnect(NetAddress serverAddress,

            System.Action<StressTest_Matched_Chat> OnLoginConnected,
            System.Action<StressTest_Matched_Chat, SF.Net.SendMessageLogin> OnLoginDisConnected,
            System.Action<StressTest_Matched_Chat, int> OnLoginFailed,

            System.Action<StressTest_Matched_Chat> OnGameSvrConnected,
            System.Action<StressTest_Matched_Chat, SF.Net.SendMessageGame> OnGameSvrDisConnected,
            System.Action<StressTest_Matched_Chat> OnGameSvrFailedConnect,
            
            System.Action<StressTest_Matched_Chat, bool> OnGameJoinResAction,


            System.Action<StressTest_Matched_Chat> OnPartyCreateAction,
            System.Action<StressTest_Matched_Chat, bool> OnGamePartyJoinedAction,
            System.Action<StressTest_Matched_Chat, bool> OnPartyChatSendResAction,
            System.Action<StressTest_Matched_Chat> OnPartyChatOneKBRecivedTen)
        {
            mLoginConnectedAction = OnLoginConnected;
            mLoginDisConnectedAction = OnLoginDisConnected;
            mLoginFailedAction = OnLoginFailed;

            // Game Sever
            mGameSvrConnectedAction = OnGameSvrConnected;
            mGameSvrDisConnectedAction = OnGameSvrDisConnected;
            mGameSvrFailedConnectAction = OnGameSvrFailedConnect;

            //---
            mGameJoinResAction = OnGameJoinResAction;
            mPartyCreateAction = OnPartyCreateAction;


            mGamePartyJoinedAction = OnGamePartyJoinedAction;
            mPartyChatSendResAction = OnPartyChatSendResAction;
            mPartyChatOneKBRecivedTen = OnPartyChatOneKBRecivedTen;
            mRecvedPartyChatMessageCount = 0;

            m_PartyInfo = new PartyMatchedInfo(0);

            NextState = eTesterState.LOGINING;
            m_ConnectionLogin = new SFConnection(m_MessageRouter);
            m_ConnectionLogin.Connect(0, serverAddress.Address, (int)serverAddress.Port);
        }

        System.Action<int, string, object[]> mPritHanlde = null;
        public void SetPrintHanlde(System.Action<int, string, object[]> hanlde)
        {
            mPritHanlde = hanlde;
        }

        void PrintStatus(int Screen, string format, params object[] args)
        {
            if (mPritHanlde != null)
                mPritHanlde(Screen, format, args);

        }

        void HandleLoginConnectionEvent(SFConnection.Event conEvent)
        {
            switch (conEvent.EventType)
            {
                case SFConnection.EventTypes.EVT_STATE_CHANGE:
                    PrintStatus(1,"Login Connection state chagned {0} {1}", conEvent.State, m_LoginID);
                    break;
                case SFConnection.EventTypes.EVT_CONNECTION_RESULT:
                    PrintStatus(1, "Login Connection result {0} {1}", conEvent.HResult, m_LoginID);
                    if (conEvent.HResult.IsSucceeded)
                    {
                        if (mLoginConnectedAction != null)
                            mLoginConnectedAction(this);

                        m_Login = new SF.Net.SendMessageLogin(m_ConnectionLogin);
                        m_Login.CreateRandomUserCmd(SFFixedString32.HashString(m_GameID), m_LoginID);
                    }
                    else
                    {
                        if (mLoginFailedAction != null)
                            mLoginFailedAction(this, 1);

                    }
                    break;
                case SFConnection.EventTypes.EVT_DISCONNECTED:
                    {
                        PrintStatus(1, "Login Connection disconnected {0}", m_LoginID);
                        if (mLoginDisConnectedAction != null)
                            mLoginDisConnectedAction(this, m_Login);
                    }
                    break;
            }
        }

        void HandleGameConnectionEvent(SFConnection.Event conEvent)
        {
            switch (conEvent.EventType)
            {
                case SFConnection.EventTypes.EVT_STATE_CHANGE:
                    PrintStatus(1, "Game Connection state chagned {0}", conEvent.State);
                    break;
                case SFConnection.EventTypes.EVT_CONNECTION_RESULT:

                    PrintStatus(1, "Game Connection result  {0} ID = {1}", conEvent.HResult, m_LoginID);

                    if (conEvent.HResult.IsSucceeded)
                    {
                        if (mGameSvrConnectedAction != null)
                            mGameSvrConnectedAction(this);

                        PrintStatus(1, "Send JoinGameServerCmd ID = {0}",m_LoginID);

                        m_Game = new SF.Net.SendMessageGame(m_ConnectionGame);
                        m_Game.JoinGameServerCmd(m_AccountID, m_LoginTicket, m_LoginEntityID);
                    }
                    else
                    {
                        if (mGameSvrFailedConnectAction != null)
                            mGameSvrFailedConnectAction(this);
                    }
                    break;
                case SFConnection.EventTypes.EVT_DISCONNECTED:
                    {
                        if (mGameSvrDisConnectedAction != null)
                            mGameSvrDisConnectedAction(this, m_Game);

                        PrintStatus(1, "Game Connection disconnected");
                    }
                    break;
            }
        }

        public void OnTimerTick(long TickMs)
        {
            if (mNextState != eTesterState.NONE)
            {
                if (mCurState != mNextState)
                    mCurState = mNextState;

                mNextState = eTesterState.NONE;
            }
            SFConnection.Event conEvent;

            // Individual connection update loop
            if (m_ConnectionLogin != null)
            {
                var result = m_ConnectionLogin.DequeueEvent(out conEvent);
                while (result)
                {
                    HandleLoginConnectionEvent(conEvent);
                    if (m_ConnectionLogin == null)
                        return;

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
                    if (m_ConnectionGame == null)
                        return;

                    result = m_ConnectionGame.DequeueEvent(out conEvent);
                }
                m_ConnectionGame.UpdateMessageQueue();
            }


         
        }

        void HandleLoginRes(SFMessage message)
        {
            var loginResult = message.GetValue<Result>("Result");
            if (loginResult.IsFailed)
            {
                PrintStatus(1, "Login failed {0}", loginResult);
                CloseAllConnections();

                if (mLoginFailedAction != null)
                    mLoginFailedAction(this, 2);

                return;
            }

            NextState = eTesterState.GAME_LOGINING;

            m_LoginTicket = message.GetValue<UInt64>("Ticket");
            m_AccountID = message.GetValue<UInt64>("AccID");
            m_GameServerAddress = message.GetValue<NetAddress>("GameServerAddrIPV4");
            m_LoginEntityID = message.GetValue<UInt64>("LoginEntityUID");

            PrintStatus(1, "Login Success!! {0}", m_LoginID);////loginResult);

            if (!string.IsNullOrEmpty(m_GameServerAddress.Address))
            {
                m_ConnectionGame = new SFConnection(m_MessageRouter);
                m_ConnectionGame.Connect(m_LoginTicket, m_GameServerAddress.Address, m_GameServerAddress.Port);
            }
        }

        void HandleJoinGameServerRes(SFMessage message)
        {
            if (m_Game == null || m_ConnectionGame == null)
                return;

            if (m_ConnectionGame.State != SFConnection.ConnectionState.CONNECTED)
                return;

            var joinResult = message.GetValue<Result>("Result");
            if (joinResult.IsFailed)
            {
                if (mGameJoinResAction != null)
                    mGameJoinResAction(this, false);

                PrintStatus(1, "Join game server failed {0} ID = {1}", joinResult, m_LoginID);
                CloseAllConnections();
                return;
            }
            else
            {
                if (mGameJoinResAction != null)
                    mGameJoinResAction(this, true);
            }

            m_PartyUID = message.GetValue<UInt64>("PartyUID");

            if (m_PartyUID == 0)
            {
                if (IsPartyBoss)
                {
                    NextState = eTesterState.PARTY_MATCING;

                    if (m_Game.CreatePartyCmd() != 0)
                        return;

                    PrintStatus(1, "Create PartyCmd ID = {0}", m_LoginID);
                }
                else
                {
                    NextState = eTesterState.PARTY_WAIT_INVITE;
                }
            }
            else
            {
                NextState = eTesterState.PARTY_MATCING;

                // already has party
                m_PartyInfo = new PartyMatchedInfo(m_PartyUID);
                if(IsPartyBoss)
                {
                    PrintStatus(1, "Already has partyID = {0} ID = {1} IsBoss = {2} ", m_PartyUID, m_LoginID, IsPartyBoss);
                    if (mPartyCreateAction != null)
                        mPartyCreateAction(this);
                }
                else
                {
                    PrintStatus(1, "Already has PartyJoined!! = {0} ID = {1} And LeavePartyCmd!!", m_PartyUID, m_LoginID);
                    m_Game.LeavePartyCmd(m_PartyUID, m_AccountID);
                }
            }
        }

        void HandleLeavePartyRes(SFMessage message)
        {
            PrintStatus(1, "HandleLeavePartyRes {0}", m_LoginID);

            m_PartyUID = 0;

            if (!IsPartyBoss)    
                NextState = eTesterState.PARTY_WAIT_INVITE;
        }

        void HandleCreatePartyRes(SFMessage message)
        {
            //variableBuilder.SetVariable("Result", parser.GetResult());
            //variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
            var Result = message.GetValue<Result>("Result");
            if (Result.IsFailed)
            {
                PrintStatus(1, "CreateParty failed {0} ID = {1}", Result, m_LoginID);
                return;
            }

            m_PartyUID = message.GetValue<UInt64>("PartyUID");

            PrintStatus(1, "HandleCreatePartyRes PartyUID ={0} ID ={1}", m_PartyUID, m_LoginID);

            m_PartyInfo = new PartyMatchedInfo(m_PartyUID);

            if (mPartyCreateAction != null)
                mPartyCreateAction(this);
        }

        void HandleJoinPartyRes(SFMessage message)
        {
            //variableBuilder.SetVariable("Result", parser.GetResult());
            //variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
            //variableBuilder.SetVariable("PartyLeaderID", parser.GetPartyLeaderID());
            //variableBuilder.SetVariable("ChatHistoryData", (int)parser.GetChatHistoryData().size(), parser.GetChatHistoryData().data());            
            var Result = message.GetValue<Result>("Result");
            if (Result.IsFailed)
            {
                PrintStatus(1, "JoinParty failed {0} ID = {1}", Result, m_LoginID);
                mGamePartyJoinedAction(this, false);
                return;
            }

            m_PartyUID = message.GetValue<UInt64>("PartyUID");

           // mPartyGameJoinedCount
            PrintStatus(1, "HandleJoinPartyRes PartyUID = {0} {1} ", m_PartyUID, m_LoginID);
            m_PartyInfo = new PartyMatchedInfo(m_PartyUID);

            if (mGamePartyJoinedAction != null)
                mGamePartyJoinedAction(this, true);
        }

        void HandlePartyChatMessageRes(SFMessage message)
        {
            PrintStatus(1, "HandlePartyChatMessageRes");
            var Result = message.GetValue<Result>("Result");
            if (Result.IsFailed)
            {
                if (mPartyChatSendResAction != null)
                    mPartyChatSendResAction(this, false);

                PrintStatus(1, "PartyChatMessage failed {0}", Result);
                return;
            }
    
            if(mPartyChatSendResAction !=  null)
                mPartyChatSendResAction(this, true);
        }

    


        List<PartyChatMessageRecvInfo> mRecvChatHistorys = new List<PartyChatMessageRecvInfo>();

        void HandlePartyChatMessageS2CEvt(SFMessage message)
        {           
            //AccountID m_SenderID;
            //const char* m_SenderName;
            //const char* m_ChatMessage;
            //variableBuilder.SetVariable("SenderID", parser.GetSenderID());
            //variableBuilder.SetVariable("SenderName", parser.GetSenderName());
            //variableBuilder.SetVariable("ChatMessage", parser.GetChatMessage());            
            mRecvedPartyChatMessageCount++;

            PartyChatMessageRecvInfo data = new PartyChatMessageRecvInfo();
            data.RecvTime = DateTime.Now;
            data.RecvChatSize = message.GetValue<string>("ChatMessage").Length;
            data.ChatMsg = message.GetValue<string>("ChatMessage");

            mRecvChatHistorys.Add(data);

            if(!IsPartyBoss)
                PrintStatus(1, "Recivice 1KB  ID ={0} Time = {1} ", m_LoginID, data.RecvTime.ToString("hh/mm/ss.fff"));

            if (mRecvedPartyChatMessageCount == StressTestWindowMatch10KB.SendChatRepeatCount)
            {
                NextState = eTesterState.COMPLTE;

                if (!IsPartyBoss)
                    PrintStatus(1, "Recivice 1KB {0}... ID ={1}", StressTestWindowMatch10KB.SendChatRepeatCount,  m_LoginID);

                if(mPartyChatOneKBRecivedTen != null)
                    mPartyChatOneKBRecivedTen(this);
            }
        }

        public long GetChatRecved_AverageValue(DateTime SendTime)
        {
            if (mRecvChatHistorys.Count == 0)
                return 0;

            double TotalMilliseconds = 0;
            for(int i=0;i < mRecvChatHistorys.Count; i++)
            {
                TotalMilliseconds += (mRecvChatHistorys[i].RecvTime - SendTime).TotalMilliseconds;
            }

            long AverageValue = (long)(TotalMilliseconds / mRecvChatHistorys.Count);
            return AverageValue;
        }

        void HandlePartyPlayerJoinedS2CEvt(SFMessage message)
        {
            //PartyUID m_PartyUID;
            //PlayerInformation m_JoinedPlayer;
            //variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
            //variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());
            PrintStatus(1, "HandlePartyPlayerJoinedS2CEvt Onwer ={0}", m_LoginID);

            UInt64 PartyUID = message.GetValue<UInt64>("PartyUID");

            if (m_PartyInfo.mPartyID != PartyUID)
                return;

            PlayerInformation JoinedPlayer = message.GetValue<PlayerInformation>("JoinedPlayer");
            m_PartyInfo.mOtherPlayers.Add(JoinedPlayer);

        }

        void HandlePartyPlayerLeftS2CEvt(SFMessage message)
        {
            //variableBuilder.SetVariable("PartyUID", parser.GetPartyUID());
            //variableBuilder.SetVariable("LeftPlayerID", parser.GetLeftPlayerID());
            PrintStatus(1, "HandlePartyPlayerLeftS2CEvt Onwer ={0}", m_LoginID);

            UInt64 PartyUID = message.GetValue<UInt64>("PartyUID");
            if (m_PartyInfo.mPartyID != PartyUID)
                return;

            UInt64 LeavePlayerID = message.GetValue<UInt64>("LeftPlayerID");
            PlayerInformation LeavePlayer = m_PartyInfo.mOtherPlayers.Find(pl => pl.PlayerID == (ulong)LeavePlayerID);

            if (LeavePlayer != null)
                m_PartyInfo.mOtherPlayers.Remove(LeavePlayer);
        }

        void HandlePartyInviteRequestedS2CEvt(SFMessage message)
        {
            if (m_Game == null)
                return;
            //AccountID m_InviterID;
            //const char* m_InviterName;
            //PartyUID m_PartyToJoinUID;
            //variableBuilder.SetVariable("InviterID", parser.GetInviterID());
            //variableBuilder.SetVariable("InviterName", parser.GetInviterName());
            //variableBuilder.SetVariable("PartyToJoinUID", parser.GetPartyToJoinUID());
            UInt64 InPartyUID = message.GetValue<UInt64>("PartyToJoinUID");
            UInt64 InInviterID = message.GetValue<UInt64>("InviterID");

            PrintStatus(1, "HandlePartyInviteRequestedS2CEvt InviterID = {0} PartyID ={1}", InInviterID, InPartyUID);
        
            m_Game.JoinPartyCmd(InPartyUID, InInviterID);
            PrintStatus(1, "JoinPartyCmd InviterID = {0} PartyID ={1} ID = {2}", InInviterID, InPartyUID, m_LoginID);
        }

        void HandlePartyInviteRes(SFMessage message)
        {

        }
    }
}


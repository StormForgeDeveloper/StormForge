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
    public class StressTest_MatchingUser
    {

        //  SFEngine m_Engine;
        SFMessageRouter m_MessageRouter = new SFMessageRouter();

        public SFConnection m_ConnectionLogin;
        public SFConnection m_ConnectionGame;

        public SF.Net.SendMessageGame m_Game;
        public SF.Net.SendMessageLogin m_Login;


        public string m_LoginID;

        UInt64 m_LoginTicket;
        UInt64 m_AccountID;
        UInt64 m_LoginEntityID;

        public UInt64 m_JoinedGameUID;

        NetAddress m_GameServerAddress;

        public int GroupID { get; set; }

        public class MatchedInfo : IDisposable
        {
            public UInt64 mJoinedGameID;
            public List<UInt64> mOtherPlayers = new List<UInt64>();

            public MatchedInfo(UInt64 JoinGameID)
            {
                mJoinedGameID = JoinGameID;
            }

            public void Dispose()
            {
                mOtherPlayers.Clear();
                mOtherPlayers = null;
            }
        }

        MatchedInfo m_MatchedInfo = null;
        
        string m_GameID = "MyTownHero";
        public string gameID
        {
            get { return m_GameID; }
            set { m_GameID = value; }
        }

        public bool Is4xComplte()
        {
            if (m_MatchedInfo == null)
                return false;

            if (m_MatchedInfo.mOtherPlayers.Count == 4)
                return true;

            return false;
        }

        public enum eTesterState
        {
            NONE,
            LOGINING,
            GAME_LOGINING,
            MATCHING,
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
                    PrintStatus(1, "MatchTestUser NextState Warring!!");

                mNextState = value;
            }
        }


        public void InitEngine()
        {
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, 0, HandleLoginRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameServerRes, 0, HandleJoinGameServerRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.RequestGameMatchRes, 0, HandleGameMatchRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameRes, 0, HandleJoinGameRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.LeaveGameRes, 0, HandleLeaveGameRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PlayerJoinedS2CEvt, 0, HandlePlayerJoinedS2Evt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.PlayerLeftS2CEvt, 0, HandlePlayerLeftS2CEvt);
           
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchedS2CEvt, 0, HandleGameMatchedS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchFailedS2CEvt, 0, HandleGameMatchFailedS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchingStartedS2CEvt, 0, HandleGameMatchingStartedS2CEvt);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GameMatchingCanceledS2CEvt, 0, HandleGameMatchingCanceledS2CEvt);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.ChatMessageRes, 0, HandleChatMessageGameRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.ChatMessageS2CEvt, 0, HandleChatMessageEvt);

        }

        public void UnInitEngine()
        {
            m_MessageRouter = null;
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

            m_Login = null;
            m_Game = null;

            if (m_ConnectionLogin != null)
                m_ConnectionLogin.Dispose();

            m_ConnectionLogin = null;

            if (m_ConnectionGame != null)
                m_ConnectionGame.Dispose();
            m_ConnectionGame = null;

            if (m_MatchedInfo != null)
                m_MatchedInfo.Dispose();

         //   PrintStatus("m_MatchedInfo Delete ID = {0}", m_LoginID);
            m_MatchedInfo = null;
        }

        System.Action<StressTest_MatchingUser> mGameSvrConnectedAction = null;
        System.Action<StressTest_MatchingUser, SF.Net.SendMessageGame> mGameSvrDisConnectedAction = null;
        System.Action<StressTest_MatchingUser> mGameSvrFailedConnectAction = null;

        System.Action<StressTest_MatchingUser, bool> mGameJoinResAction = null;

        System.Action<StressTest_MatchingUser> m4xMatchedAction = null;
        System.Action<StressTest_MatchingUser> mSendReqMatchAction = null;
        System.Action<StressTest_MatchingUser, bool> mReqMatchResAction = null;

        System.Action<StressTest_MatchingUser> mLoginConnectedAction = null;
        System.Action<StressTest_MatchingUser, SF.Net.SendMessageLogin> mLoginDisConnectedAction = null;
        System.Action<StressTest_MatchingUser, int> mLoginFailedAction = null;


        System.Action<StressTest_MatchingUser> mRecvChatDataAction = null;

        public void RunConnect(NetAddress serverAddress,

            System.Action<StressTest_MatchingUser> OnLoginConnected,
            System.Action<StressTest_MatchingUser, SF.Net.SendMessageLogin> OnLoginDisConnected,
            System.Action<StressTest_MatchingUser, int> OnLoginFailed,

            System.Action<StressTest_MatchingUser> OnGameSvrConnected,
            System.Action<StressTest_MatchingUser, SF.Net.SendMessageGame> OnGameSvrDisConnected,
            System.Action<StressTest_MatchingUser> OnGameSvrFailedConnect,
            System.Action<StressTest_MatchingUser, bool> OnGameJoinAction,

            System.Action<StressTest_MatchingUser> On4xMatchedAction,
            System.Action<StressTest_MatchingUser> OnSendMatchAction,

            
            System.Action<StressTest_MatchingUser, bool> OnReqMatchResAction,


            System.Action<StressTest_MatchingUser> OnRecvChatDataAction)
        {
            mLoginConnectedAction = OnLoginConnected;
            mLoginDisConnectedAction = OnLoginDisConnected;
            mLoginFailedAction = OnLoginFailed;

            // Game Sever
            mGameSvrConnectedAction = OnGameSvrConnected;
            mGameSvrDisConnectedAction = OnGameSvrDisConnected;
            mGameSvrFailedConnectAction = OnGameSvrFailedConnect;

            mGameJoinResAction = OnGameJoinAction;

            m4xMatchedAction = On4xMatchedAction;
            mSendReqMatchAction = OnSendMatchAction;
            mReqMatchResAction = OnReqMatchResAction;

            mRecvChatDataAction = OnRecvChatDataAction;
            m_MatchedInfo = new MatchedInfo(0);

            NextState = eTesterState.LOGINING;
            mCurDeltaTime = 0;

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
                 //   PrintStatus("Login Connection state chagned {0}", conEvent.State);
                    break;
                case SFConnection.EventTypes.EVT_CONNECTION_RESULT:
                    PrintStatus(1, "Login Connection result {0} {1}", conEvent.HResult, m_LoginID);
                    if (conEvent.HResult.IsSucceeded)
                    {
                        if (mLoginConnectedAction != null)
                            mLoginConnectedAction(this);

                        m_Login = new SF.Net.SendMessageLogin(m_ConnectionLogin);
                        m_Login.CreateRandomUserCmd(FixedString32.HashString(m_GameID), m_LoginID);
                    }
                    else
                    {
                        if (mLoginFailedAction != null)
                            mLoginFailedAction(this, 1);
                    }
                    break;
                case SFConnection.EventTypes.EVT_DISCONNECTED:
                    {
                        if (mLoginDisConnectedAction != null)
                             mLoginDisConnectedAction(this, m_Login);

                        PrintStatus(0, "Login Connection disconnected {0}", m_LoginID);
                    }
                    break;
            }
        }

        void HandleGameConnectionEvent(SFConnection.Event conEvent)
        {
            switch (conEvent.EventType)
            {
                case SFConnection.EventTypes.EVT_STATE_CHANGE:
                  //  PrintStatus("Game Connection state chagned {0}", conEvent.State);
                    break;
                case SFConnection.EventTypes.EVT_CONNECTION_RESULT:
                    PrintStatus(1, "Game Connection result {0} {1}", conEvent.HResult, m_LoginID);
                    if (conEvent.HResult.IsSucceeded)
                    {
                        if (mGameSvrConnectedAction != null)
                            mGameSvrConnectedAction(this);

                        PrintStatus(0, "JoinGameServerCmd {1}", conEvent.HResult, m_LoginID);
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

                        PrintStatus(0, "Game Connection disconnected {0}", m_LoginID);
                    }
                    break;
            }
        }

        long mCurDeltaTime = 0;
        public void OnTimerTick(long TickMs)
        {
            if (mNextState != eTesterState.NONE)
            {
                if (mCurState != mNextState)
                    mCurState = mNextState;

                mNextState = eTesterState.NONE;
            }

            mCurDeltaTime += TickMs;

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
                if (mCurState != eTesterState.NONE)// && m_ConnectionLogin.State != SFConnection.ConnectionState.DISCONNECTED)
                {
                    if (m_Game != null && mCurDeltaTime >= 10000)
                    {
                        m_Game.HeartBitC2SEvt();
                        mCurDeltaTime = 0;
                    }
                }
            }          
        }

        void HandleLoginRes(SFMessage message)
        {
            var loginResult = message.GetValue<Result>("Result");
            if (loginResult.IsFailed)
            {
                PrintStatus(1, "Login failed {0}", loginResult);

                if (mLoginFailedAction != null)
                    mLoginFailedAction(this, 2);

                CloseAllConnections();
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
            var joinResult = message.GetValue<Result>("Result");

            if (joinResult.IsFailed)
            {
                if (mGameJoinResAction != null)
                    mGameJoinResAction(this, false);

                PrintStatus(1, "Join game server failed {0}", joinResult);
                CloseAllConnections();
                return;
            }
            else
            {
                if (mGameJoinResAction != null)
                    mGameJoinResAction(this, true);
            }

            NextState = eTesterState.MATCHING;
            m_JoinedGameUID = message.GetValue<UInt64>("GameUID");
            if (m_JoinedGameUID != 0)
            {
                PrintStatus(1, "Already has JoinedGame!! = {0} ID = {1} And LeaveGameCMD!!", m_JoinedGameUID, m_LoginID);
                m_MatchedInfo = new MatchedInfo(m_JoinedGameUID);

                m_Game.LeaveGameCmd(m_JoinedGameUID, m_AccountID, m_LoginTicket);

            } 
            else
            {
                if (mSendReqMatchAction != null)
                    mSendReqMatchAction(this);
            }
        }

        void HandleGameMatchRes(SFMessage message)
        {
            var Result = message.GetValue<Result>("Result");
            if (Result.IsFailed)
            {                
                PrintStatus(1, "HandleGameMatchRes failed {0}", Result);
                // This comes twice when I run the test second time.
                if(Result.Code != ResultCode.SVR_ALREADY_INQUEUE)
                    CloseAllConnections();
                return;
            }
            PrintStatus(0, "HandleGameMatchRes {0} ID = {1}", Result, m_LoginID);
        }

        // matching successed
        //-- 매칭 요청 완료시..
        void HandleGameMatchedS2CEvt(SFMessage message)
        {          
            if (m_Game == null)
                return;

            UInt64 GameInsID = message.GetValue<UInt64>("InsUID");

            PrintStatus(1, "GameMatchedS2CEvt !! InsUID = {0} and JoinGameCmd!! ID = {1} ", GameInsID, m_LoginID);
            //m_Game.JoinGameCmd(m_AccountID, m_LoginTicket, GameInsID);
            //variableBuilder.SetVariable("InsUID", parser.GetInsUID());
            //variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());
            //variableBuilder.SetVariable("GameState", (int)parser.GetGameState());
            //variableBuilder.SetVariable("Day", parser.GetDay());
            //variableBuilder.SetVariable("MaxPlayer", parser.GetMaxPlayer());
            //variableBuilder.SetVariable("PlayerIndex", parser.GetPlayerIndex());
            //variableBuilder.SetVariable("PlayerCharacter", parser.GetPlayerCharacter());
            //variableBuilder.SetVariable("Role", (int)parser.GetRole());
            //variableBuilder.SetVariable("Dead", parser.GetDead());
            //variableBuilder.SetVariable("ChatHistoryData", (int)parser.GetChatHistoryData().size(), parser.GetChatHistoryData().data());
            //variableBuilder.SetVariable("GameLogData", (int)parser.GetGameLogData().size(), parser.GetGameLogData().data());
            //variableBuilder.SetVariable("Stamina", parser.GetStamina());
            //variableBuilder.SetVariable("TotalGem", parser.GetTotalGem());
            //variableBuilder.SetVariable("TotalGameMoney", parser.GetTotalGameMoney());        
            UInt64 JoinedGameUID = message.GetValue<UInt64>("InsUID");
            if (m_JoinedGameUID == 0)
            {
                m_JoinedGameUID = JoinedGameUID;
                m_MatchedInfo = new MatchedInfo(m_JoinedGameUID);

                if (mReqMatchResAction != null)
                    mReqMatchResAction(this, true);

                NextState = eTesterState.COMPLTE;
            }
            else if (JoinedGameUID == m_JoinedGameUID)
            {
                // Already has Joined!!                   

            }
        }

        void HandleLeaveGameRes(SFMessage message)
        {
            var Result = message.GetValue<Result>("Result");
            if (Result.IsFailed)
            {
                PrintStatus(1, "HandleLeaveGameRes failed {0} {1}", Result, m_LoginID);
                CloseAllConnections();
                return;
            }

//          PrintStatus("HandleLeaveGameRes ID = {0}", m_LoginID);
            if (m_JoinedGameUID == 0)
                return;

            if (m_MatchedInfo.mOtherPlayers.Contains(m_AccountID))
                m_MatchedInfo.mOtherPlayers.Remove(m_AccountID);

            m_MatchedInfo.mJoinedGameID = 0;
            m_JoinedGameUID = 0;

            PrintStatus(1, "HandleLeaveGameRes And Send RequestGameMatchCmd ID = {0}", m_LoginID);
            
           // if (mSendReqLeaveGameAction != null)
           //     mSendReqLeaveGameAction(this);

            if (mSendReqMatchAction != null)
                mSendReqMatchAction(this);

        }


        void HandleJoinGameRes(SFMessage message)
        {
            var Result = message.GetValue<Result>("Result");
            if (Result.IsFailed)
            {
                PrintStatus(1, "JoinGameRes failed {0}", Result);
                CloseAllConnections();
                return;
            }

            m_JoinedGameUID = message.GetValue<UInt64>("InsUID");
            
            //if(m_JoinGameUID == 0)
            PrintStatus(1, "JoinGameRes Success GameID={0} MaxPlayer = {1} ID ={2}", m_JoinedGameUID, 
                message.GetValue<uint>("MaxPlayer"), m_LoginID);

            m_MatchedInfo = new MatchedInfo(m_JoinedGameUID);
        }

        void HandlePlayerJoinedS2Evt(SFMessage message)
        {
            UInt64 GameInsID = message.GetValue<UInt64>("GameInsUID");
            PlayerInformation JoinedPlayer = message.GetValue<PlayerInformation>("JoinedPlayer");

            PrintStatus(1, "HandlePlayerJoinedS2Evt  GameInsID = {0} MyID  = {1} JoinedPlayerID = {2} ",
                GameInsID, m_LoginID, JoinedPlayer.PlayerID);

            //variableBuilder.SetVariable("GameInsUID", parser.GetGameInsUID());
            //variableBuilder.SetVariable("JoinedPlayer", parser.GetJoinedPlayer());
            //variableBuilder.SetVariable("JoinedPlayerRole", parser.GetJoinedPlayerRole());
            //variableBuilder.SetVariable("JoinedPlayerDead", parser.GetJoinedPlayerDead());
            //variableBuilder.SetVariable("JoinedPlayerIndex", parser.GetJoinedPlayerIndex());
            //variableBuilder.SetVariable("JoinedPlayerCharacter", parser.GetJoinedPlayerCharacter());
            if (m_MatchedInfo == null || m_Game == null)
                return;

            if (m_MatchedInfo.mJoinedGameID != GameInsID)
                return;
           
            m_MatchedInfo.mOtherPlayers.Add(JoinedPlayer.PlayerID);

            if(Is4xComplte())
            {
                if (m4xMatchedAction != null)
                    m4xMatchedAction(this);
            }
        }

        void HandlePlayerLeftS2CEvt(SFMessage message)
        {
            UInt64 GameInsID = message.GetValue<UInt64>("GameInsUID");
            if (m_MatchedInfo.mJoinedGameID != GameInsID)
                return;

            UInt64 LeavePlayerID = message.GetValue<UInt64>("LeftPlayerID");
            UInt64 FindLeavePlayerID = m_MatchedInfo.mOtherPlayers.Find(pl => pl == (ulong) LeavePlayerID);

            // if(FindLeavePlayer != null)
            PrintStatus(1, "HandlePlayerLeftS2CEvt LeavePlayerID = {0}", LeavePlayerID);
            m_MatchedInfo.mOtherPlayers.Remove(FindLeavePlayerID);
        }

        void HandleGameMatchingStartedS2CEvt(SFMessage message)
        {
      //      PrintStatus("HandleGameMatchingStartedS2CEvt ");
        }

        void HandleGameMatchingCanceledS2CEvt(SFMessage message)
        {
       //     PrintStatus("HandleGameMatchingCanceledS2CEvt");
        }

        //matching failed
        void HandleGameMatchFailedS2CEvt(SFMessage message)
        {
            if (mReqMatchResAction != null)
                mReqMatchResAction(this, false);

            var Result = message.GetValue<Result>("FailedReason");
            PrintStatus(1, "GameMatchFailedS2CEvt failed {0}", Result);
        }

        void HandleChatMessageGameRes(SFMessage message)
        {
            //PrintStatus("HandleChatMessageGameRes");
        }

        void HandleChatMessageEvt(SFMessage message)
        {
            UInt64 SenderID = message.GetValue<UInt64>("SenderID");
            if (SenderID <= 10) return;

            PrintStatus(1, "Recived!! ChatMessage UserID = {0}", m_LoginID);

            if (mRecvChatDataAction != null)
                mRecvChatDataAction(this);
        }
    }
}

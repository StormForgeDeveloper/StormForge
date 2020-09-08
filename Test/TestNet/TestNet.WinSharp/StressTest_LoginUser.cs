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
    public class StressTest_LoginUser
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

        UInt64 m_JoinedGameUID;

        NetAddress m_GameServerAddress;

        public int GroupID { get; set; }

        string m_GameID = "MyTownHero";
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
            GAMESVR_JOIN_FAILED,
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
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.LeaveGameRes, 0, HandleLeaveGameRes);
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

        }

        System.Action<StressTest_LoginUser> mGameSvrConnectedAction = null;
        System.Action<StressTest_LoginUser, SF.Net.SendMessageGame> mGameSvrDisConnectedAction = null;
        System.Action<StressTest_LoginUser> mGameSvrFailedConnectAction = null;

        System.Action<StressTest_LoginUser, bool> mGameJoinResAction = null;

        System.Action<StressTest_LoginUser> mLoginConnectedAction = null;
        System.Action<StressTest_LoginUser, SF.Net.SendMessageLogin> mLoginDisConnectedAction = null;
        System.Action<StressTest_LoginUser, int> mLoginFailedAction = null;

        public void RunConnect(NetAddress serverAddress,

            System.Action<StressTest_LoginUser> OnLoginConnected,
            System.Action<StressTest_LoginUser, SF.Net.SendMessageLogin> OnLoginDisConnected,
            System.Action<StressTest_LoginUser, int> OnLoginFailed,

            System.Action<StressTest_LoginUser> OnGameSvrConnected,
            System.Action<StressTest_LoginUser, SF.Net.SendMessageGame> OnGameSvrDisConnected,
            System.Action<StressTest_LoginUser> OnGameSvrFailedConnect,

            System.Action<StressTest_LoginUser, bool> OnGameJoinAction)
        {
            mLoginConnectedAction = OnLoginConnected;
            mLoginDisConnectedAction = OnLoginDisConnected;
            mLoginFailedAction = OnLoginFailed;

            // Game Sever
            mGameSvrConnectedAction = OnGameSvrConnected;
            mGameSvrDisConnectedAction = OnGameSvrDisConnected;
            mGameSvrFailedConnectAction = OnGameSvrFailedConnect;

            mGameJoinResAction = OnGameJoinAction;

            NextState = eTesterState.LOGINING;
            mCurDeltaTime = 0;

            m_ConnectionLogin = new SFConnection(m_MessageRouter);
            m_ConnectionLogin.Connect(0, serverAddress.Address, (int)serverAddress.Port);            
        }

        System.Action<int, string, object[]> mPritHanlde = null;
        public void SetPrintHanlde( System.Action<int, string, object[]> hanlde)
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
                        m_Login.CreateRandomUserCmd(0, StringCrc32.HashString(m_GameID), m_LoginID);
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
                        m_Game.JoinGameServerCmd(0, m_AccountID, m_LoginTicket, m_LoginEntityID);
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

                if (mCurState != eTesterState.NONE)
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

                NextState = eTesterState.GAMESVR_JOIN_FAILED;
                PrintStatus(1, "Join game server failed {0}", joinResult);
                CloseAllConnections();
                return;
            }
            else
            {
                if (mGameJoinResAction != null)
                    mGameJoinResAction(this, true);
            }

            NextState = eTesterState.COMPLTE;

            m_JoinedGameUID = message.GetValue<UInt64>("GameUID");
            if (m_JoinedGameUID != 0)
            {
                PrintStatus(1, "Already has JoinedGame!! = {0} ID = {1} And LeaveGameCMD!!", m_JoinedGameUID, m_LoginID);
                m_Game.LeaveGameCmd(0, m_JoinedGameUID, m_AccountID, m_LoginTicket);
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

            if (m_JoinedGameUID == 0)
                return;

            m_JoinedGameUID = 0;
            PrintStatus(0, "HandleLeaveGameRes {0}", m_LoginID);            
        }
    }
}

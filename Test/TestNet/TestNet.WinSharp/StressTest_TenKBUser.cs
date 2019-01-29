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
    public class StressTest_TenKBUser
    {
      //  SFEngine m_Engine;
        SFMessageRouter m_MessageRouter = new SFMessageRouter();

        public SFConnection m_ConnectionLogin;
        public SF.Net.SendMessageLogin m_Login;

        UInt64 m_LoginTicket;
        UInt64 m_AccountID;
        UInt64 m_LoginEntityID;
        NetAddress m_GameServerAddress;

        public string m_LoginID;

        public int GroupID { get; set; }

        int mDataTestResCount = 0;

        public enum eTesterState
        {
            NONE,
            LOGINING,
            SEND_WAIT,
            SENDING,
            COMPLTE,
        };

        eTesterState mCurState = eTesterState.NONE;
        public eTesterState CurState { get { return mCurState; } }

        eTesterState mNextState = eTesterState.NONE;
        public eTesterState NextState {
            set
            {
                if(mNextState != eTesterState.NONE)
                    PrintStatus(1, "TenKBUser NextState Warring!!");

                mNextState = value;
            } }


        string m_GameID = "MyTownHero";
        public string gameID
        {
            get { return m_GameID; }
            set { m_GameID = value;}
        }

        public void InitEngine()
        {
            GroupID = 0;

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, 0, HandleLoginRes);                       
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.DataTestRes, 0, HandleDataTestRes);
        }

        public void UnInitEngine()
        {

            m_MessageRouter = null;
        }

        public void CloseAllConnections()
        {
            if (m_ConnectionLogin != null)
            {
                if (m_ConnectionLogin.State != SFConnection.ConnectionState.DISCONNECTED)
                {
                    if (mLoginDisConnectedAction != null)
                        mLoginDisConnectedAction(this, m_Login);
                }
            }

            if (m_ConnectionLogin != null)
                m_ConnectionLogin.Dispose();
            m_ConnectionLogin = null;

            m_Login = null;

        }

        System.Action<StressTest_TenKBUser> mLoginConnectedAction = null;
        System.Action<StressTest_TenKBUser, SF.Net.SendMessageLogin> mLoginDisConnectedAction = null;
        System.Action<StressTest_TenKBUser> mLoginFailedConnectAction = null;

        System.Action<StressTest_TenKBUser,bool> mLoginResAction = null;
        System.Action<StressTest_TenKBUser, bool> mDataTestSendRes = null;

        public void RunConnect(NetAddress serverAddress,
            System.Action<StressTest_TenKBUser> OnLoginConnected,
            System.Action<StressTest_TenKBUser, SF.Net.SendMessageLogin> OnLoginDisConnected,
            System.Action<StressTest_TenKBUser> OnLoginFailedConnect,
            System.Action<StressTest_TenKBUser, bool > OnLoginRes,
            System.Action<StressTest_TenKBUser, bool> OnDataTestSendRes)
        {
            mLoginConnectedAction = OnLoginConnected;
            mLoginDisConnectedAction = OnLoginDisConnected;
            mLoginFailedConnectAction = OnLoginFailedConnect;

            mLoginResAction = OnLoginRes;
            mDataTestSendRes = OnDataTestSendRes;

            mNextState = eTesterState.LOGINING;
            mDataTestResCount = 0;
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
                    //PrintStatus("Login Connection state chagned {0} ID = {1}", conEvent.State, m_LoginID);
                    break;
                case SFConnection.EventTypes.EVT_CONNECTION_RESULT:

                    PrintStatus(1, "Login Connection result CID:{0}, hr:{1} ID = {2}", m_ConnectionLogin.CID, conEvent.HResult, m_LoginID);
                    if (conEvent.HResult.IsSucceeded)
                    {
                        if (mLoginConnectedAction != null)
                            mLoginConnectedAction(this);

                        m_Login = new SF.Net.SendMessageLogin(m_ConnectionLogin);
                        m_Login.CreateRandomUserCmd(SFFixedString32.HashString(m_GameID), m_LoginID);
                    }
                    else
                    {
                        if (mLoginFailedConnectAction != null)
                            mLoginFailedConnectAction(this);
                    }
                    break;
                case SFConnection.EventTypes.EVT_DISCONNECTED:
                    {
                        if (mLoginDisConnectedAction != null)
                            mLoginDisConnectedAction(this,m_Login);

                        PrintStatus(0,"Login Connection disconnected ID = {0}", m_LoginID);
                    }
                    break;
            }
        }

        long mCurDeltaTime = 0;

        public void OnTimerTick(long ms)
        {
            SFConnection.Event conEvent;
            mCurDeltaTime += ms;

            if (mNextState != eTesterState.NONE)
            {
                if (mCurState != mNextState)
                    mCurState = mNextState;

                mNextState = eTesterState.NONE;
            }

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

                if (mCurState == eTesterState.COMPLTE && m_Login != null && mCurDeltaTime >= 10000)// && m_ConnectionLogin.State != SFConnection.ConnectionState.DISCONNECTED)
                {
                   m_Login.HeartBitC2SEvt();
                   mCurDeltaTime = 0;
                }
            }
        }

        void HandleLoginRes(SFMessage message)
        {
            var loginResult = message.GetValue<Result>("Result");
            if (loginResult.IsFailed)
            {
                if (mLoginResAction != null)
                    mLoginResAction(this, false);

                PrintStatus(1, "Login failed {0}", loginResult);
                CloseAllConnections();
                return;
            }
            else
            {
                m_LoginTicket = message.GetValue<UInt64>("Ticket");
                m_AccountID = message.GetValue<UInt64>("AccID");
                m_GameServerAddress = message.GetValue<NetAddress>("GameServerAddrIPV4");
                m_LoginEntityID = message.GetValue<UInt64>("LoginEntityUID");

                if (mLoginResAction != null)
                    mLoginResAction(this, true);
            }       
        }

        void HandleDataTestRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                PrintStatus(1, "TestData failed {0}", result);

                if (mDataTestSendRes != null)
                    mDataTestSendRes(this, false);
                return;
            }

            if (mDataTestSendRes != null)
                mDataTestSendRes(this, true);

            var testDatas = message.GetValue<byte[]>("TestData");

            PrintStatus(0, "TestData Res {0} bytes ID = {1} ", testDatas.Length, m_LoginID);

            mDataTestResCount++;
            if (mDataTestResCount == 10)
                NextState = StressTest_TenKBUser.eTesterState.COMPLTE;
        }
    }
}

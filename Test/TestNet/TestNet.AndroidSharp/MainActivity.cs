using System;
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;

using SF;
using System.Threading;

namespace TestNet.AndroidSharp
{
    [Activity(Label = "TestNet.AndroidSharp", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Activity
    {
        GameID m_GameID = GameID.MyTownHero;
        SFEngine m_Engine;
        SFMessageRouter m_MessageRouter = new SFMessageRouter();
        SFConnection m_ConnectionLogin;
        SF.Net.SendMessageLogin m_Login;
        string m_LoginID = "testDDD";

        UInt64 m_LoginTicket;
        UInt64 m_AccountID;
        UInt64 m_LoginEntityID;


        TextView m_TextOutput;


        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            // Get our button from the layout resource,
            // and attach an event to it
            Button btnConnect = FindViewById<Button>(Resource.Id.btnConnect);

            btnConnect.Click += delegate
            {

                // Update combo box text
                NetAddress serverAddress = new NetAddress()
                {
                    Address = "192.168.0.2",
                    Port = 21001
                };

                Connect(serverAddress);
            };

            Button btnUpdateRanking = FindViewById<Button>(Resource.Id.btnUpdateRanking);
            btnUpdateRanking.Click += delegate
            {
                if (m_Login == null)
                    return;

                Random rand = new Random();
                m_Login.UpdateMyScoreCmd((ulong)rand.Next() % 5000, RankingType.World, 10);
            };


            m_TextOutput = FindViewById<TextView>(Resource.Id.textOutput);
        }

        protected override void OnStart()
        {
            base.OnStart();

            m_Engine = new SFEngine();
            m_Engine.StartEngine();

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.CreateRandomUserRes, 0, HandleLoginRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDLogin.UpdateMyScoreRes, 0, HandleScoreRes);
        }

        protected override void OnStop()
        {
            CloseAllConnections();


            if (m_Engine != null)
                m_Engine.StopEngine();
            m_Engine = null;

            base.OnStop();
        }


        Timer m_Timer;
        protected override void OnPause()
        {
            base.OnPause();
            if(m_Timer != null)
            {
                m_Timer.Dispose();
                m_Timer = null;
            }
        }

        protected override void OnResume()
        {
            base.OnResume();

            m_Timer = new Timer((caller)=>
            {
                UpdateConnection();

            }, this, 1000, 1000);
        }


        void Connect(NetAddress serverAddress)
        {
            CloseAllConnections();

            m_ConnectionLogin = new SFConnection(m_MessageRouter);
            m_ConnectionLogin.Connect(0, serverAddress.Address, (int)serverAddress.Port);
            m_Login = new SF.Net.SendMessageLogin(m_ConnectionLogin);
        }

        void CloseAllConnections()
        {
            if (m_ConnectionLogin != null)
                m_ConnectionLogin.Dispose();
            m_ConnectionLogin = null;
        }

        void UpdateConnection()
        {
            if (m_ConnectionLogin == null)
                return;

            SFConnection.Event conEvent;

            var result = m_ConnectionLogin.DequeueEvent(out conEvent);
            while (result)
            {
                switch (conEvent.EventType)
                {
                    case SFConnection.EventTypes.EVT_STATE_CHANGE:
                        PrintStatus("Login Connection state chagned {0}", conEvent.State);
                        break;
                    case SFConnection.EventTypes.EVT_CONNECTION_RESULT:
                        PrintStatus("Login Connection result {0}", conEvent.HResult);
                        if (conEvent.HResult >= 0)
                        {
                            m_Login = new SF.Net.SendMessageLogin(m_ConnectionLogin);
                            m_Login.CreateRandomUserCmd(m_GameID, m_LoginID);
                        }
                        break;
                    case SFConnection.EventTypes.EVT_DISCONNECTED:
                        PrintStatus("Login Connection disconnected");
                        if(m_ConnectionLogin != null)
                            m_ConnectionLogin.Dispose();
                        m_ConnectionLogin = null;
                        m_Login = null;
                        break;
                }

                if (m_ConnectionLogin != null)
                    result = m_ConnectionLogin.DequeueEvent(out conEvent);
            }

            if (m_ConnectionLogin != null)
                m_ConnectionLogin.UpdateMessageQueue();

        }


        void PrintStatus(string text)
        {
            RunOnUiThread(()=>
            {
                if (m_TextOutput != null)
                    m_TextOutput.Append("\n" + text);
            });
        }

        void PrintStatus(string format, params object[] args)
        {
            PrintStatus(string.Format(format, args));
        }



        void HandleLoginRes(SFMessage message)
        {
            var loginResult = message.GetValue<int>("Result");
            if (loginResult < 0)
            {
                PrintStatus("Login failed {0:X8}", loginResult);
                CloseAllConnections();
                return;
            }

            m_LoginTicket = message.GetValue<UInt64>("Ticket");
            m_AccountID = message.GetValue<UInt64>("AccID");
            m_LoginEntityID = message.GetValue<UInt64>("LoginEntityUID");

            Random rand = new Random();
            m_Login.UpdateMyScoreCmd((ulong)rand.Next() % 5000, RankingType.World, 10);
        }

        void HandleScoreRes(SFMessage message)
        {
            var result = message.GetValue<int>("Result");
            if (result < 0)
            {
                PrintStatus("Login failed {0:X8}", result);
                return;
            }


            var rankingInfos = message.GetValue<TotalRankingPlayerInformation[]>("Ranking");
            foreach (var ranking in rankingInfos)
            {
                PrintStatus("Ranking info {0}", ranking);
            }
        }

    }
}


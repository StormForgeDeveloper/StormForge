using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Navigation;
using System.ComponentModel;
using SF;

namespace TestNet2.WinSharp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class TestNet2MainWindow : Window
    {
        System.Windows.Threading.DispatcherTimer m_TickTimer;
        OnlineClient m_OnlineClient;
        SFMessageRouter m_MessageRouter;

        Random m_Rand = new Random();

        public TestNet2MainWindow()
        {
            InitializeComponent();

            var logServerAddress = SavedValueRegistry.ReadValue("LogServer", null);
            if (!string.IsNullOrEmpty(logServerAddress))
                txtLogServer.Text = logServerAddress;

            var loginServerAddress = SavedValueRegistry.ReadValue("LoginServer", null);
            if (!string.IsNullOrEmpty(loginServerAddress))
                txtLoginServer.Text = loginServerAddress;

            txtLoginName.Text = SavedValueRegistry.ReadValue("LoginName", "");

            var processName = SavedValueRegistry.ReadValue("ProcessName", "TestNet2.WinSharp");
            SavedValueRegistry.SaveValue("ProcessName", processName);

            GlobalEngine.Start(processName, logServerAddress);

            m_MessageRouter = new SFMessageRouter();
            RegisterMessageLiteners();


            UpdateButtonState();


            m_TickTimer = new System.Windows.Threading.DispatcherTimer();
            m_TickTimer.Tick += new EventHandler(Timer_Tick);
            m_TickTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            m_TickTimer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            if (m_OnlineClient != null)
            {
                m_OnlineClient.UpdateGameTick();
            }
        }

        void UpdateButtonState()
        {
            if (m_OnlineClient == null
                || m_OnlineClient.GetOnlineState() == OnlineClient.OnlineState.Disconnected)
            {
                btnDisconnect.IsEnabled = false;
                btnLogin.IsEnabled = true;
                listCharacter.IsEnabled = false;
                btnCreateCharacter.IsEnabled = false;
                btnRefreshCharacterList.IsEnabled = false;
                return;
            }

            btnDisconnect.IsEnabled = true;
            btnLogin.IsEnabled = false;
            var onlineState = m_OnlineClient.GetOnlineState();
            switch (onlineState)
            {
                case OnlineClient.OnlineState.InGameServer:
                    btnCreateCharacter.IsEnabled = true;
                    listCharacter.IsEnabled = true;
                    btnRefreshCharacterList.IsEnabled = true;
                    break;
                case OnlineClient.OnlineState.InGameJoiningGameInstance:
                case OnlineClient.OnlineState.InGameConnectingGameInstance:
                case OnlineClient.OnlineState.InGameInGameInstance:
                    btnCreateCharacter.IsEnabled = false;
                    listCharacter.IsEnabled = false;
                    btnRefreshCharacterList.IsEnabled = false;
                    break;
            }
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);

            m_TickTimer.Stop();
            m_TickTimer = null;


            if (m_OnlineClient != null)
            {
                m_OnlineClient.DisconnectAll();
                m_OnlineClient.Dispose();
                m_OnlineClient = null;
            }

            if (m_MessageRouter != null)
            {
                m_MessageRouter.Dispose();
                m_MessageRouter = null;
            }

            GlobalEngine.Stop();
        }


        private void OnDisconnectClicked(object sender, RoutedEventArgs e)
        {
            if (m_OnlineClient != null)
            {
                m_OnlineClient.DisconnectAll();
                m_OnlineClient.Dispose();
                m_OnlineClient = null;
            }

            UpdateButtonState();
        }

        private void OnLoginClicked(object sender, RoutedEventArgs e)
        {
            var userId = txtLoginName.Text;
            if (string.IsNullOrEmpty(userId))
                return;

            if (m_OnlineClient == null)
            {
                m_OnlineClient = new OnlineClient(m_MessageRouter);
            }

             SavedValueRegistry.SaveValue("LoginName", userId);

            var loginAddress = txtLoginServer.Text;
            SavedValueRegistry.SaveValue("LoginServer", loginAddress);

            var logServer = txtLogServer.Text;
            SavedValueRegistry.SaveValue("LogServer", logServer);

            var result = m_OnlineClient.StartConnection("FishingOnline", loginAddress, userId, userId);
            if (result.IsSucceeded)
            {
            }
            UpdateButtonState();
        }

        public class CharacterItem
        {
            public string CharacterName;
            public UInt32 CharacterId;
            public VariableTable VisualData;

            public override string ToString()
            {
                return string.Format("({0}){1}", CharacterId, CharacterName);
            }
        };

        private void OnCharacterListDoubleClicked(object sender, MouseButtonEventArgs e)
        {
            var selectedCharacter = listCharacter.SelectedItem as CharacterItem;

            var gameConn = m_OnlineClient.GetConnection(OnlineClient.ConnectionType.Game);
            if (gameConn == null)
                return;

            var gamePolicy = new SF.Net.SendMessageGame(gameConn);
            gamePolicy.SelectCharacterCmd(0, selectedCharacter.CharacterId);
        }

        private void OnCreateCharacterClicked(object sender, RoutedEventArgs e)
        {
            var gameConn = m_OnlineClient.GetConnection(OnlineClient.ConnectionType.Game);
            if (gameConn == null)
                return;

            var gamePolicy = new SF.Net.SendMessageGame(gameConn);
            var charName = string.Format("testchar{0}{1}", txtLoginName.Text, m_Rand.Next()%100);

            var visualConfig = new VariableTable();
            visualConfig.Add(new StringCrc32("sex"), 1);
            visualConfig.Add(new StringCrc32("hat"), 10);
            visualConfig.Add(new StringCrc32("shoes"), 10);

            var attributes = new VariableTable();
            attributes.Add(new StringCrc32("Gold"), 100);
            attributes.Add(new StringCrc32("Agile"), 10);
            attributes.Add(new StringCrc32("Strength"), 20);
            attributes.Add(new StringCrc32("Integer"), 30);
            gamePolicy.CreateCharacterCmd(0, charName, visualConfig, attributes);
        }

        private void OnRefreshCharacterListClicked(object sender, RoutedEventArgs e)
        {
            var gameConn = m_OnlineClient.GetConnection(OnlineClient.ConnectionType.Game);
            if (gameConn == null)
                return;

            var gamePolicy = new SF.Net.SendMessageGame(gameConn);
            gamePolicy.GetCharacterListCmd(0);
        }

        #region Message handling

        void RegisterMessageLiteners()
        {
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameServerRes, 0, HandleJoinGameServerRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GetCharacterListRes, 0, HandleGetCharacterListRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GetCharacterDataRes, 0, HandleGetCharacterDataRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.SelectCharacterRes, 0, HandleSelectCharacterRes);
        }

        void HandleJoinGameServerRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                //PrintStatus("CreateParty has failed {0}", result);
                return;
            }

            var gameConn = m_OnlineClient.GetConnection(OnlineClient.ConnectionType.Game);
            if (gameConn == null)
                return;


            UpdateButtonState();

            var gamePolicy = new SF.Net.SendMessageGame(gameConn);
            gamePolicy.GetCharacterListCmd(0);
        }

        void HandleGetCharacterListRes(SFMessage message)
        {
            UpdateButtonState();

            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                return;
            }

            var characters = message.GetValue<VariableTable[]>("Characters");
            var numCharacter = characters.Length;

            listCharacter.BeginInit();
            listCharacter.Items.Clear();

            for (int iChar = 0; iChar < numCharacter; iChar++)
            {
                object obj;
                characters[iChar].TryGetValue(new StringCrc32("CharacterId"), out obj);
                var characterId = (UInt64)Convert.ChangeType(obj, typeof(UInt64));
                characters[iChar].TryGetValue(new StringCrc32("Name"), out obj);
                string characterName = (string)Convert.ChangeType(obj, typeof(string));
                characters[iChar].TryGetValue(new StringCrc32("VisualData"), out obj);
                byte[] characterVisual = (byte[])obj;
                VariableTable parsedValue = new VariableTable();
                parsedValue.FromSerializedMemory(characterVisual);

                listCharacter.Items.Add(new CharacterItem()
                {
                    CharacterId = (uint)characterId,
                    CharacterName = characterName,
                    VisualData = parsedValue
                });
            }

            listCharacter.EndInit();
        }

        void HandleGetCharacterDataRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                return;
            }

        }

        void HandleSelectCharacterRes(SFMessage message)
        {
            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                return;
            }

            var characterId = message.GetValue<UInt32>("CharacterID");
            var characterData = message.GetValue<VariableTable>("Attributes");

            int Gold, Agile, Strength, Integer;
            object obj;
            characterData.TryGetValue(new StringCrc32("Gold"), out obj);
            Gold = (int)obj;
            characterData.TryGetValue(new StringCrc32("Agile"), out obj);
            Agile = (int)obj;
            characterData.TryGetValue(new StringCrc32("Strength"), out obj);
            Strength = (int)obj;
            characterData.TryGetValue(new StringCrc32("Integer"), out obj);
            Integer = (int)obj;

        }


        #endregion

    }
}

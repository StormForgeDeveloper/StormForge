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
            txtLogId.Text = processName;

            GlobalEngine.Start(processName, logServerAddress, 0xFFFFFFFF);

            m_MessageRouter = new SFMessageRouter();
            RegisterMessageLiteners();


            UpdateButtonState();

            OnlineClient.OnOnlineStateChanged += (object sender, OnlineClient.OnlineState prevState, OnlineClient.OnlineState newState) =>
            {
                UpdateStatusText(newState);
            };
            UpdateStatusText(OnlineClient.OnlineState.None);


            m_TickTimer = new System.Windows.Threading.DispatcherTimer();
            m_TickTimer.Tick += new EventHandler(Timer_Tick);
            m_TickTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            m_TickTimer.Start();
        }

        void UpdateStatusText(SF.OnlineClient.OnlineState status)
        {
            textOnlineStatus.Content = status.ToString();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            if (m_OnlineClient == null)
                return;

            m_OnlineClient.UpdateGameTick();

            m_OnlineClient.SendMovement(ref m_MyMove);
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
                listZone.IsEnabled = false;
                btnZoneList.IsEnabled = false;
                return;
            }

            btnDisconnect.IsEnabled = true;
            btnLogin.IsEnabled = false;
            listZone.IsEnabled = false;
            btnZoneList.IsEnabled = false;
            var onlineState = m_OnlineClient.GetOnlineState();
            switch (onlineState)
            {
                case OnlineClient.OnlineState.InGameServer:
                    btnCreateCharacter.IsEnabled = true;
                    listCharacter.IsEnabled = true;
                    btnRefreshCharacterList.IsEnabled = true;
                    listZone.IsEnabled = true;
                    btnZoneList.IsEnabled = true;
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

            SavedValueRegistry.SaveValue("LoginName", txtLoginName.Text);
            SavedValueRegistry.SaveValue("LoginServer", txtLoginServer.Text);
            SavedValueRegistry.SaveValue("LogServer", txtLogServer.Text);
            SavedValueRegistry.SaveValue("ProcessName", txtLogId.Text);

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

            listCharacter.Items.Clear();
            listZone.Items.Clear();

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

        public class ZoneItem
        {
            public Int32 ZoneTableId;
            public UInt64 ZoneInstanceId;
            public StringCrc32 ZoneType;

            public override string ToString()
            {
                return string.Format("table:{0}, instance:{1:X}", ZoneTableId, ZoneInstanceId);
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
            var charName = string.Format("testchar{0}{1}", txtLoginName.Text, m_Rand.Next() % 100);

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

        private void OnBtnZoneListClicked(object sender, RoutedEventArgs e)
        {
            var gameConn = m_OnlineClient.GetConnection(OnlineClient.ConnectionType.Game);
            if (gameConn == null)
                return;

            var gamePolicy = new SF.Net.SendMessageGame(gameConn);
            gamePolicy.SearchGameInstanceCmd(0, "");
        }

        private void OnZoneListDoubleClicked(object sender, MouseButtonEventArgs e)
        {
            var selectedZone = listZone.SelectedItem as ZoneItem;

            var res = m_OnlineClient.JoinGameInstance(selectedZone.ZoneInstanceId);
            if (res.IsFailed)
            {
            }
        }

        ActorMovement m_MyMove = new ActorMovement();
        private void OnClickedMove(object sender, RoutedEventArgs e)
        {
            if (m_OnlineClient == null)
                return;

            if (sender == btnMoveUp)
            {
                m_MyMove.MoveFrame = m_OnlineClient.GetCurrentMoveFrame();
                m_MyMove.Position.z += 3;
            }
            else if (sender == btnMoveDown)
            {
                m_MyMove.MoveFrame = m_OnlineClient.GetCurrentMoveFrame();
                m_MyMove.Position.z -= 3;
            }
            else if (sender == btnMoveRight)
            {
                m_MyMove.MoveFrame = m_OnlineClient.GetCurrentMoveFrame();
                m_MyMove.Position.x += 3;
            }
            else if (sender == btnMoveLeft)
            {
                m_MyMove.MoveFrame = m_OnlineClient.GetCurrentMoveFrame();
                m_MyMove.Position.x -= 3;
            }
        }

        #region Message handling

        void RegisterMessageLiteners()
        {
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameServerRes, 0, HandleJoinGameServerRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GetCharacterListRes, 0, HandleGetCharacterListRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.GetCharacterDataRes, 0, HandleGetCharacterDataRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.SelectCharacterRes, 0, HandleSelectCharacterRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.SearchGameInstanceRes, 0, HandleZoneListRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.JoinGameInstanceRes, 0, HandleJoinGameInstanceRes);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDGame.LeaveGameInstanceRes, 0, HandleLeaveGameInstanceRes);

            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDPlayInstance.NewPlayerInViewS2CEvt, 0, HandleNewPlayerInView);
            m_MessageRouter.RegisterMessageHandler(SF.Net.MessageIDPlayInstance.RemovePlayerFromViewS2CEvt, 0, HandleRemovePlayerFromView);
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
                UInt64 characterId = 0;
                string characterName = null;
                byte[] characterVisual = null;

                if (characters[iChar].TryGetValue(new StringCrc32("CharacterId"), out obj))
                    characterId = (UInt64)Convert.ChangeType(obj, typeof(UInt64));
                if (characters[iChar].TryGetValue(new StringCrc32("Name"), out obj))
                    characterName = (string)Convert.ChangeType(obj, typeof(string));
                if (characters[iChar].TryGetValue(new StringCrc32("VisualData"), out obj))
                    characterVisual = (byte[])obj;
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

        void HandleZoneListRes(SFMessage message)
        {
            UpdateButtonState();

            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                return;
            }

            var zoneInstances = message.GetValue<VariableTable[]>("GameInstances");

            listZone.BeginInit();
            listZone.Items.Clear();

            foreach (var zoneInfo in zoneInstances)
            {
                object obj;
                UInt64 instanceUID = 0;
                Int32 zoneTableId = 0;
                StringCrc32 zoneType = new StringCrc32();

                if (zoneInfo.TryGetValue(new StringCrc32("InstanceUID"), out obj))
                    instanceUID = (UInt64)Convert.ChangeType(obj, typeof(UInt64));
                if (zoneInfo.TryGetValue(new StringCrc32("ZoneTableID"), out obj))
                    zoneTableId = (Int32)Convert.ChangeType(obj, typeof(Int32));
                if (zoneInfo.TryGetValue(new StringCrc32("Type"), out obj))
                    zoneType = (StringCrc32)obj;

                listZone.Items.Add(new ZoneItem()
                {
                    ZoneInstanceId = instanceUID,
                    ZoneTableId = zoneTableId,
                    ZoneType = zoneType,
                });
            }

            listZone.EndInit();
        }

        void HandleJoinGameInstanceRes(SFMessage message)
        {
            UpdateButtonState();

            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                return;
            }
        }

        void HandleLeaveGameInstanceRes(SFMessage message)
        {
            UpdateButtonState();

            var result = message.GetValue<Result>("Result");
            if (result.IsFailed)
            {
                return;
            }
        }

        void HandleNewPlayerInView(SFMessage message)
        {
            var PlayInstanceUID = message.GetValue<UInt64>("PlayInstanceUID");
            var PlayerID = message.GetValue<UInt64>("PlayerID");
            var VisualData = message.GetValue<UInt64>("Attributes");

            // player moved in visual range or joined
        }

        void HandleRemovePlayerFromView(SFMessage message)
        {
            var PlayInstanceUID = message.GetValue<UInt64>("PlayInstanceUID");
            var PlayerID = message.GetValue<UInt64>("PlayerID");

            // player left or moved away
        }

        #endregion

    }
}

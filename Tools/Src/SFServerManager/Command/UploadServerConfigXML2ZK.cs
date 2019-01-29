////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Upload server config xml command
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.Composition;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Dom;

using SF;

namespace SFServerManager.Command
{
    /// <summary>
    /// Upload XML server config to ZooKeeper
    /// </summary>
    [Export(typeof(UploadServerConfigXML2ZK))]
    [Export(typeof(IContextMenuCommandProvider))]
    [Export(typeof(IInitializable))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    class UploadServerConfigXML2ZK : ICommandClient, IInitializable, IContextMenuCommandProvider
    {
        public static CommandInfo[] MyCommands = {
            new CommandInfo(
                    "UploadServerConfigXML2ZK".GetHashCode(),
                    StandardMenu.Edit,
                    StandardCommandGroup.EditGroup,
                    "Upload XML ServerConfig to ZooKeeper".Localize(),
                    "Upload XML ServerConfig to ZooKeeper".Localize(),
                    Sce.Atf.Input.Keys.None,
                    Resources.ArrowUpload,
                    CommandVisibility.Default),
        };


        /// <summary>
        /// Constructor</summary>
        /// <param name="commandService">Command service</param>
        [ImportingConstructor]
        public UploadServerConfigXML2ZK(ICommandService commandService, IContextRegistry contextRegistry)
        {
            m_commandService = commandService;
            m_contextRegistry = contextRegistry;
        }


        #region IInitializable Members

        void IInitializable.Initialize()
        {
            foreach (var myCommand in MyCommands)
                m_commandService.RegisterCommand(myCommand, this);
        }

        #endregion

        #region ICommandClient Members

        /// <summary>
        /// Checks whether the client can do the command, if it handles it</summary>
        /// <param name="commandTag">Command to be done</param>
        /// <returns>True iff client can do the command</returns>
        bool ICommandClient.CanDoCommand(object commandTag)
        {
            CommandInfo myCommand = null;
            foreach (var itCommand in MyCommands)
                if (itCommand.CommandTag.Equals(commandTag))
                {
                    myCommand = itCommand;
                    break;
                }
            if (myCommand == null)
                return false;

            if (m_Setting == null)
                return false;

            if (m_Setting.XMLPaths.Count == 0)
                return false;

            if (m_ZooKeeperSession == null || m_ZooKeeperSession.ZKInstance == null || !m_ZooKeeperSession.ZKInstance.IsConnected())
                return false;

            if (string.IsNullOrEmpty(m_Setting.ConfigNodePath))
                return false;

            if (string.IsNullOrEmpty(m_Setting.CommandNodePath))
                return false;

            if(m_ZooKeeperSession.ServerConfig == null)
                return false;


            return true;
        }

        /// <summary>
        /// Does the command</summary>
        /// <param name="commandTag">Command to be done</param>
        void ICommandClient.DoCommand(object commandTag)
        {
            CommandInfo myCommand = null;
            foreach (var itCommand in MyCommands)
                if (itCommand.CommandTag.Equals(commandTag))
                {
                    myCommand = itCommand;
                    break;
                }
            if (myCommand == null)
                return;

            if (m_Setting.XMLPaths.Count == 0)
                return;

            if (m_ZooKeeperSession == null || m_ZooKeeperSession.ZKInstance == null || !m_ZooKeeperSession.ZKInstance.IsConnected())
                return;

            if (string.IsNullOrEmpty(m_Setting.ConfigNodePath))
                return;

            if (string.IsNullOrEmpty(m_Setting.CommandNodePath))
                return;

            if (!myCommand.CommandTag.Equals("UploadServerConfigXML2ZK".GetHashCode()))
                return;

            Outputs.WriteLine(OutputMessageType.Info, "Connecting ZooKeeper server {0}", m_Setting.ConnectionString);
            SFZooKeeper zooKeeper = m_ZooKeeperSession.ZKInstance;
            if (zooKeeper == null || !zooKeeper.IsConnected())
            {
                Outputs.WriteLine(OutputMessageType.Error, "ZooKeeper is not connected");
                return;
            }

            // Create command root node if not exists
            if (!zooKeeper.Exists(m_Setting.CommandNodePath))
                zooKeeper.CreateNode(m_Setting.CommandNodePath, "");

            SFServerConfig serverConfig = m_ZooKeeperSession.ServerConfig;

            // Load from xml
            Outputs.WriteLine(OutputMessageType.Info, "Loading XML server config");
            var result = serverConfig.LoadXML(m_Setting.XMLPaths[0]);
            if(result != 0)
            {
                Outputs.WriteLine(OutputMessageType.Error, "XML loading is failed {0:X8}", result);
                return;
            }

            // Store to ZooKeeper
            Outputs.WriteLine(OutputMessageType.Info, "Storing server config to ZooKeeper: node:{0}", m_Setting.ConfigNodePath);
            result = serverConfig.StoreZooKeeper(zooKeeper, m_Setting.ConfigNodePath);
            if (result != 0)
            {
                Outputs.WriteLine(OutputMessageType.Error, "Storing to ZooKeeper is failed {0:X8}", result);
                return;
            }

            // Creating command nodes
            string commandNode = string.Format("{0}/{1}", m_Setting.CommandNodePath, "ReloadConfig");
            var commencedIPs = new HashSet<string>();
            serverConfig.ForEachServer((SFServerConfig.GenericServer server) =>
            {
                var serverInstanceName = server.Name;
                var serverIP = server.PrivateNet.IP;

                Outputs.WriteLine(OutputMessageType.Warning, "Server Instance {0}", serverInstanceName);

                if (commencedIPs.Contains(serverIP))
                    return;

                commencedIPs.Add(serverIP);
                var commandValue = ZooKeeperCommand.ReloadConfig(serverIP);

                result = zooKeeper.CreateNode(commandNode, commandValue, SFZooKeeper.NODE_FLAG_SEQUENCE);
                if (result != 0)
                {
                    Outputs.WriteLine(OutputMessageType.Warning, "Failed to create command root for {0}, result:{1:X8}", serverInstanceName, result);
                }
                else
                {
                    Outputs.WriteLine(OutputMessageType.Info, "Command root for {0} has created", serverInstanceName);
                }
            });



            Outputs.WriteLine(OutputMessageType.Info, "XML server config successfully uploaded");
        }


        /// <summary>
        /// Updates command state for given command</summary>
        /// <param name="commandTag">Command</param>
        /// <param name="commandState">Command info to update</param>
        void ICommandClient.UpdateCommand(object commandTag, CommandState commandState)
        {
        }

        #endregion


        #region IContextMenuCommandProvider Members

        /// <summary>
        /// Gets tags for context menu (right click) commands</summary>
        /// <param name="context">Context containing target object</param>
        /// <param name="clicked">Right clicked object, or null if none</param>
        IEnumerable<object> IContextMenuCommandProvider.GetCommands(object context, object clicked)
        {
            ISelectionContext selectionContext = context.As<ISelectionContext>();
            if (selectionContext == null)
                return EmptyEnumerable<object>.Instance;

            return new object[]
                {
                    MyCommands[0].CommandTag,
                };
        }

        #endregion


        [Import(AllowDefault = false)]
        private ZooKeeperSession m_ZooKeeperSession = null;

        [Import(AllowDefault = false)]
        private ServerManagerSetting m_Setting = null;

        private readonly ICommandService m_commandService;
        private readonly IContextRegistry m_contextRegistry;
    }
}

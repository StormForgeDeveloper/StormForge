////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : stop server instances command
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
    [Export(typeof(StopServerInstances))]
    [Export(typeof(IContextMenuCommandProvider))]
    [Export(typeof(IInitializable))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    class StopServerInstances : ICommandClient, IInitializable, IContextMenuCommandProvider
    {
        public static CommandInfo[] MyCommands = {
            new CommandInfo(
                    "StopServerInstancess".GetHashCode(),
                    StandardMenu.Edit,
                    StandardCommandGroup.EditGroup,
                    "StopServerInstances".Localize(),
                    "Stop Server Instances".Localize(),
                    Sce.Atf.Input.Keys.None,
                    Resources.ButtonStop,
                    CommandVisibility.Default),
        };


        /// <summary>
        /// Constructor</summary>
        /// <param name="commandService">Command service</param>
        [ImportingConstructor]
        public StopServerInstances(ICommandService commandService, IContextRegistry contextRegistry)
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

            if (m_ZooKeeperSession == null || m_ZooKeeperSession.ZKInstance == null || !m_ZooKeeperSession.ZKInstance.IsConnected())
                return false;

            if (string.IsNullOrEmpty(m_Setting.CommandNodePath))
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

            if (m_ZooKeeperSession == null || m_ZooKeeperSession.ZKInstance == null || !m_ZooKeeperSession.ZKInstance.IsConnected())
                return;
            
            if (string.IsNullOrEmpty(m_Setting.CommandNodePath))
                return;

            if (!myCommand.CommandTag.Equals("StopServerInstancess".GetHashCode()))
                return;

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
            string commandNode = string.Format("{0}/{1}", m_Setting.CommandNodePath, "Stop");


            serverConfig.ForEachServer((SFServerConfig.GenericServer server) =>
            {
                var serverInstanceName = server.Name;
                var commandValue = ZooKeeperCommand.StopServerInstance(server.PrivateNet.IP, server.Name);

                var result = zooKeeper.CreateNode(commandNode, commandValue, SFZooKeeper.NODE_FLAG_SEQUENCE);
                if (result != 0)
                {
                    Outputs.WriteLine(OutputMessageType.Warning, "Failed to push command for {0}, result:{1:X8}", serverInstanceName, result);
                }
                else
                {
                    Outputs.WriteLine(OutputMessageType.Info, "Command pushed {0}", serverInstanceName);
                }
            });


            Outputs.WriteLine(OutputMessageType.Info, "Command push process is done");

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

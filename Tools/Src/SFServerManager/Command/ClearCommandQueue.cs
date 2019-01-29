////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Clear command queue command
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
using System.IO;
using System.Runtime.Serialization.Json;

namespace SFServerManager.Command
{
    /// <summary>
    /// Upload XML server config to ZooKeeper
    /// </summary>
    [Export(typeof(ClearCommandQueue))]
    [Export(typeof(IContextMenuCommandProvider))]
    [Export(typeof(IInitializable))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    class ClearCommandQueue : ICommandClient, IInitializable, IContextMenuCommandProvider
    {

        public static CommandInfo[] MyCommands = {
            new CommandInfo(
                    "ClearCommandQueues".GetHashCode(),
                    StandardMenu.Edit,
                    StandardCommandGroup.EditGroup,
                    "Clear command queue".Localize(),
                    "Clear ZooKeeper command queue".Localize(),
                    Sce.Atf.Input.Keys.None,
                    Resources.DeleteImage,
                    CommandVisibility.Default),
        };


        /// <summary>
        /// Constructor</summary>
        /// <param name="commandService">Command service</param>
        [ImportingConstructor]
        public ClearCommandQueue(ICommandService commandService, IContextRegistry contextRegistry)
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

            if (!myCommand.CommandTag.Equals("ClearCommandQueues".GetHashCode()))
                return;

            Outputs.WriteLine(OutputMessageType.Info, "Commencing Clear Command Queue");

            SFZooKeeper zooKeeper = m_ZooKeeperSession.ZKInstance;
            if (zooKeeper == null || !zooKeeper.IsConnected())
            {
                Outputs.WriteLine(OutputMessageType.Error, "ZooKeeper is not connected");
                return;
            }

            // Create command root node if not exists
            if (!zooKeeper.Exists(m_Setting.CommandNodePath))
                zooKeeper.CreateNode(m_Setting.CommandNodePath, "");


            if (!zooKeeper.Exists(m_Setting.CommandNodePath))
                zooKeeper.CreateNode(m_Setting.CommandNodePath, "");
            else
                zooKeeper.DeleteAllChildren(m_Setting.CommandNodePath);

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

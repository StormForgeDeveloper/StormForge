////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.Composition;
using System.Windows.Forms;

using Sce.Atf;
using Sce.Atf.Applications;
using Sce.Atf.Controls;
using Sce.Atf.Dom;
using Sce.Atf.Adaptation;
using Sce.Atf.Perforce;

using SF;

namespace SFServerManager
{
    /// <summary>
    /// Server config uploader view
    /// </summary>
    [Export(typeof(ServerConfigUploadView))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    class ServerConfigUploadView : TreeViewEditorBase
    {

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="contextRegistry">Context registry</param>
        /// <param name="settingsService">Settings service</param>
        /// <param name="controlHostService">Control host service</param>
        [ImportingConstructor]
        public ServerConfigUploadView(
            ICommandService commandService,
            IContextRegistry contextRegistry,
            ISettingsService settingsService,
            ServerManagerSetting serverManagerSetting,
            IControlHostService controlHostService)
            : base(
                "TableUploader",
                commandService,
                contextRegistry,
                settingsService,
                controlHostService)
        {
            m_ServerManagerSetting = serverManagerSetting;
            m_ControlPannel.SettingService = serverManagerSetting;
        }

        protected override TreeControlAdapter CreateAdapter(TreeControl treeControl)
        {
            var treeControlAdapter = base.CreateAdapter(treeControl);

            var newTreeRoot = new DomNode(ServerInstanceTreeType.Type);
            newTreeRoot.InitializeExtensions();
            treeControlAdapter.TreeView = newTreeRoot.As<TreeViewDataAdapter>();

            return treeControlAdapter;
        }

        protected override void InitializeControls(UserControl parentControl, ref int x, ref int y, ref int buttonHeight)
        {
            base.InitializeControls(parentControl, ref x, ref y, ref buttonHeight);

            var ctrl = CreateChildControl<ServerConfigUploadControl>(new System.Drawing.Size(0, 0), ref x, ref y, ref buttonHeight);
            m_ControlPannel = ctrl;

            parentControl.Controls.Add(ctrl);
        }



        protected override void OnInitialized()
        {
        }

        ServerManagerSetting m_ServerManagerSetting = null;
        ServerConfigUploadControl m_ControlPannel;
    }

}

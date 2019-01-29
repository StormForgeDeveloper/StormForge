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
using System.ComponentModel.Composition;
using System.Drawing;
using System.Windows.Forms;

using Sce.Atf;
using Sce.Atf.Applications;
using Sce.Atf.Controls;
using Sce.Atf.Controls.PropertyEditing;
using Sce.Atf.Dom;
using Sce.Atf.Adaptation;

namespace SF
{
    /// <summary>
    /// Common data item editor derived from TreeListViewEditor used for all the tree view editors
    /// except RawTreeListView.
    /// </summary>
    [InheritedExport(typeof(IInitializable))]
    class TreeViewEditorBase : TreeControlEditor, IInitializable, IControlHostClient, IAdaptable
    {
        /// <summary>
        /// Constructor that configures TreeListView. Creates and registers control it populates with desired buttons
        /// that have the handler method BtnClick().</summary>
        /// <param name="name">Name of editor</param>
        /// <param name="style">TreeListView style</param>
        /// <param name="contextRegistry">Context registry</param>
        /// <param name="settingsService">Settings service</param>
        /// <param name="controlHostService">Control host service</param>
        public TreeViewEditorBase(
            string name,
            ICommandService commandService,
            IContextRegistry contextRegistry,
            ISettingsService settingsService,
            IControlHostService controlHostService)
            : base(commandService)
        {
            m_Name = name;

            m_contextRegistry = contextRegistry;
            m_controlHostService = controlHostService;
            m_SettingService = settingsService;

            EditorTheme = new DataEditorTheme(TreeControl.Font);



            {
                //
                // Create custom control to contain any
                // data creation buttons + TreeListView
                //
                m_uberControl = new UserControl {Dock = DockStyle.Fill};

                int x = 2, y = 2;
                int buttonHeight = -1;
                InitializeControls(m_uberControl, ref x, ref y, ref buttonHeight);
                
                {
                    TreeControl.Location = new Point(0, buttonHeight + 2);
                    TreeControl.Anchor =
                        AnchorStyles.Left | AnchorStyles.Top |
                        AnchorStyles.Right | AnchorStyles.Bottom;

                    TreeControl.Width = m_uberControl.Width;
                    TreeControl.Height = m_uberControl.Height - buttonHeight - 2;
                    TreeControl.LabelEditMode = TreeControl.LabelEditModes.Disable;

                    m_uberControl.Controls.Add(TreeControl);
                }

            }
        }


        /// <summary>
        /// Add new control from inherited class
        /// </summary>
        /// <param name="parentControl"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="buttonHeight"></param>
        protected virtual void InitializeControls(UserControl parentControl, ref int x, ref int y, ref int buttonHeight)
        {

        }
        
        /// <summary>
        /// Initialize</summary>
        void IInitializable.Initialize()
        {
            var info =
                new ControlInfo(
                    m_Name,
                    m_Name + " - TreeView",
                    StandardControlGroup.Center);


            var treeAdapter = TreeView.As<TreeViewDataAdapter>();
            treeAdapter.Theme = EditorTheme;
            TreeControl.ItemRenderer = new TreeListItemRenderer(treeAdapter.As<IItemView>());

            UpdateColumnInformation();

            m_controlHostService.RegisterControl(
                m_uberControl,
                info,
                this);



            OnInitialized();

        }

        /// <summary>
        /// Override when you need to do something on initialization
        /// </summary>
        protected virtual void OnInitialized()
        {

        }

        protected override TreeControl CreateControl()
        {
            return new TreeListControl
            {
                ImageList = ResourceUtil.GetImageList16(),
                StateImageList = ResourceUtil.GetImageList16()
            };
        }

        private void UpdateColumnInformation()
        {
            var treeAdapter = TreeView.As<TreeViewDataAdapter>();
            var treeListControl = TreeControl as TreeListControl;
            treeListControl.Columns.Clear();
            foreach (var columnInfo in treeAdapter.ListViewColumnInfos)
            {
                treeListControl.Columns.Add(new TreeListView.Column(columnInfo.Name, columnInfo.DefaultWidth));
            }

        }

        #region IControlHostClient Interface

        /// <summary>
        /// Notifies the client that its Control has been activated. Activation occurs when
        /// the Control gets focus, or a parent "host" Control gets focus.</summary>
        /// <param name="control">Client Control that was activated</param>
        /// <remarks>This method is only called by IControlHostService if the Control was previously
        /// registered for this IControlHostClient.</remarks>
        public void Activate(Control control)
        {
            if (!ReferenceEquals(control, m_uberControl) || TreeView == null)
                return;

            var treeAdapter = TreeView.As<TreeViewDataAdapter>();
            treeAdapter.BindPropertyContext(GetPropertyEditingContext());
            m_contextRegistry.ActiveContext = TreeView;
        }

        /// <summary>
        /// Notifies the client that its Control has been deactivated. Deactivation occurs when
        /// another Control or "host" Control gets focus.</summary>
        /// <param name="control">Client Control that was deactivated</param>
        /// <remarks>This method is only called by IControlHostService if the Control was previously
        /// registered for this IControlHostClient.</remarks>
        public void Deactivate(Control control)
        {
        }

        /// <summary>
        /// Requests permission to close the client's Control</summary>
        /// <param name="control">Client Control to be closed</param>
        /// <returns>True if the Control can close, or false to cancel</returns>
        /// <remarks>
        /// 1. This method is only called by IControlHostService if the Control was previously
        /// registered for this IControlHostClient.
        /// 2. If true is returned, the IControlHostService calls its own
        /// UnregisterControl. The IControlHostClient has to call RegisterControl again
        /// if it wants to re-register this Control.</remarks>
        public bool Close(Control control)
        {
            return true;
        }

        #endregion


        #region IAdaptable Interface

        /// <summary>
        /// Gets an adapter for a type</summary>
        /// <param name="type">Type to get adapter for</param>
        /// <returns>Adapter or null</returns>
        public virtual object GetAdapter(Type type)
        {
            // Try to convert to sub-parts

            if (type.Equals(typeof(TreeControl)))
                return TreeControl;

            if (type.Equals(typeof(Control)))
                return TreeControl;

            if (type.Equals(typeof(TreeListViewAdapter)))
                return TreeView.As<TreeListViewAdapter>();
            
            return type.Equals(typeof(ITreeView)) ? TreeView : null;
        }

        #endregion


        private IPropertyEditingContext GetPropertyEditingContext()
        {
            // first try to get a client-defined IPropertyEditingContext
            IPropertyEditingContext context = m_contextRegistry.GetMostRecentContext<IPropertyEditingContext>();
            if (context != null)
            {
                m_defaultPropertyEditingContext.SelectionContext = null;
            }
            else
            {
                // otherwise, try to get a client-defined ISelectionContext and adapt it
                ISelectionContext selectionContext = m_contextRegistry.GetMostRecentContext<ISelectionContext>();
                m_defaultPropertyEditingContext.SelectionContext = selectionContext;
                if (selectionContext != null)
                    context = m_defaultPropertyEditingContext;
            }

            return context;
        }


        private void TreeListViewNodeExpandedChanged(object sender, TreeListView.NodeEventArgs e)
        {
            Outputs.WriteLine(
                OutputMessageType.Info,
                "{0} {1}",
                e.Node.Label,
                e.Node.Expanded ? "expanded!" : "collapsed!");
        }


        protected static ControlType CreateChildControl<ControlType>( Size expectedSize, ref int x, ref int y, ref int height) where ControlType : Control
        {
            var newCtrl = Activator.CreateInstance<ControlType>();

            if (expectedSize.Width > 0)
                newCtrl.Width = expectedSize.Width;

            newCtrl.Location = new Point(x, y);
            newCtrl.Anchor = AnchorStyles.Left | AnchorStyles.Top;

            x += newCtrl.Width + 2;

            if (height == -1)
                height = newCtrl.Height;

            return newCtrl;
        }

        protected static Button CreateButton(string text, ref int x, ref int y, ref int height)
        {
            var btn = new Button {Text = text};

            var size = TextRenderer.MeasureText(btn.Text, btn.Font);
            btn.Width = size.Width + 20;

            btn.Location = new Point(x, y);
            btn.Anchor = AnchorStyles.Left | AnchorStyles.Top;

            x += btn.Width + 2;

            if (height == -1)
                height = btn.Height;

            return btn;
        }

        protected static CheckBox CreateCheckbox(string text, ref int x, ref int y, ref int height)
        {
            var btn = new CheckBox { Text = text };

            var size = TextRenderer.MeasureText(btn.Text, btn.Font);
            btn.Width = size.Width + 20;

            btn.Location = new Point(x, y);
            btn.Anchor = AnchorStyles.Left | AnchorStyles.Top;

            x += btn.Width + 2;

            if (height == -1)
                height = btn.Height;

            return btn;
        }

        private string m_Name;
        private readonly UserControl m_uberControl;
        private readonly IContextRegistry m_contextRegistry;
        private SelectionPropertyEditingContext m_defaultPropertyEditingContext = new SelectionPropertyEditingContext();
        private IControlHostService m_controlHostService;
        public DataEditorTheme EditorTheme { get; private set; }
        private ISettingsService m_SettingService;

        public ISettingsService SettingService {  get { return m_SettingService; } }

        private const string SettingsDisplayName = "TreeListView Persisted Settings";
        private const string SettingsCategory = "TreeListView";
        private const string SettingsDescription = "TreeListView Persisted Settings";
    }
    

    
}
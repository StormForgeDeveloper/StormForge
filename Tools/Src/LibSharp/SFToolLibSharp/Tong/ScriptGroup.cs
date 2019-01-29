////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script script group
//
////////////////////////////////////////////////////////////////////////////////


using System.Collections.Generic;
using System.Drawing;
using Sce.Atf.Adaptation;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to group in a circuit</summary>
    public class ScriptGroup : Sce.Atf.Controls.Adaptable.Graphs.Group, ICircuitGroupType<ScriptNode, ScriptNodeConnection, ICircuitPin>, IGraph<ScriptNode, ScriptNodeConnection, ICircuitPin>
    {
        /// <summary>
        /// Performs initialization when the adapter is connected to the group's DomNode.
        /// Raises the DomNodeAdapter NodeSet event and performs custom processing:
        /// creates a DomNodeListAdapter for various circuit elements.</summary>
        protected override void OnNodeSet()
        {
            m_modules = new DomNodeListAdapter<ScriptNode>(DomNode, groupType.moduleChild);
            m_connections = new DomNodeListAdapter<ScriptNodeConnection>(DomNode, groupType.connectionChild);
            new DomNodeListAdapter<ScriptAnnotation>(DomNode, groupType.annotationChild);
            new DomNodeListAdapter<ScriptGroupSocket>(DomNode, groupType.inputChild);
            new DomNodeListAdapter<ScriptGroupSocket>(DomNode, groupType.outputChild);
            m_thisModule = DomNode.Cast<ScriptNode>();

            base.OnNodeSet();
        }

        /// <summary>
        /// Gets the bounding rectangle for the node in world space (or local space if a
        /// hierarchy is involved, as with sub-circuits). The location portion should always
        /// be accurate, but the renderer should be queried for the size of the rectangle.
        /// See D2dGraphRenderer.GetBounds() or use ILayoutContext.GetBounds().</summary>
        /// <remarks>Note: TongScriptEditor.Group does not drive from Module due to single inheritance in C#,
        /// but groupType derives from moduleType in XML schema. Now it is possible that the DomNode underneath
        /// is adapted to both Module and CircuitGroup, which can bring in two Element.Bounds: one from Module->Element,
        /// another from Group->Element. Explicitly use bounds from Module for graph drawing.</remarks>
        Rectangle IGraphNode.Bounds
        {
            get { return m_thisModule.Bounds; }
        }

        /// <summary>
        /// Gets or sets the bounding rectangle for the node in world space (or local space if a
        /// hierarchy is involved, as with sub-circuits). The location portion should always
        /// be accurate, but the renderer should be queried for the size of the rectangle.
        /// See D2dGraphRenderer.GetBounds() or use ILayoutContext.GetBounds().</summary>
        public override Rectangle Bounds
        {
            get { return m_thisModule.Bounds; }
            set { m_thisModule.Bounds = value; }
        }

        /// <summary>
        /// Gets name attribute for group</summary>
        protected override AttributeInfo NameAttribute
        {
            get { return moduleType.nameAttribute; }
        }

        /// <summary>
        /// Gets label attribute on group</summary>
        protected override AttributeInfo LabelAttribute
        {
            get { return moduleType.labelAttribute; }
        }

        /// <summary>
        /// Gets x-coordinate position attribute for group</summary>
        protected override AttributeInfo XAttribute
        {
            get { return moduleType.xAttribute; }
        }

        /// <summary>
        /// Gets y-coordinate position attribute for group</summary>
        protected override AttributeInfo YAttribute
        {
            get { return moduleType.yAttribute; }
        }

        /// <summary>
        /// Gets visible attribute for group</summary>
        protected override AttributeInfo VisibleAttribute
        {
            get { return moduleType.visibleAttribute; }
        }

        /// <summary>
        /// Gets minimum width (when the group is expanded) attribute for group</summary>
        protected override AttributeInfo MinWidthAttribute
        {
            get { return groupType.minwidthAttribute; }
        }

        /// <summary>
        /// Gets minimum height (when the group is expanded) attribute for group</summary>
        protected override AttributeInfo MinHeightAttribute
        {
            get { return groupType.minheightAttribute; }
        }

        /// <summary>
        /// Gets width (when the group is expanded) attribute for group</summary>
        protected override AttributeInfo WidthAttribute
        {
            get { return groupType.widthAttribute; }
        }

        /// <summary>
        /// Gets height (when the group is expanded) attribute for group</summary>
        protected override AttributeInfo HeightAttribute
        {
            get { return groupType.heightAttribute; }
        }

        /// <summary>
        /// Gets autosize attribute for group.
        /// When autosize is true, container size is computed.</summary>
        protected override AttributeInfo AutosizeAttribute
        {
            get { return groupType.autosizeAttribute; }
        }

        /// <summary>
        /// Gets expanded attribute for group</summary>
        protected override AttributeInfo ExpandedAttribute
        {
            get { return groupType.expandedAttribute; }
        }

        /// <summary>
        /// Gets showExpandedGroupPins attribute for group</summary>
        protected override AttributeInfo ShowExpandedGroupPinsAttribute
        {
            get { return groupType.showExpandedGroupPinsAttribute; }
        }

        /// <summary>
        /// Gets showExpandedGroupPins attribute for group</summary>
        protected override AttributeInfo ValidatedAttribute
        {
            get { return groupType.validatedAttribute; }
        }

        protected override AttributeInfo SourceGuidAttribute
        {
            get { return groupType.sourceGuidAttribute; }
        }

        /// <summary>
        /// Gets ChildInfo for Modules in group</summary>
        protected override ChildInfo ElementChildInfo
        {
            get { return groupType.moduleChild; }
        }

        /// <summary>
        /// Gets ChildInfo for Wires in group</summary>
        protected override ChildInfo WireChildInfo
        {
            get { return groupType.connectionChild; }
        }

        /// <summary>
        /// Gets ChildInfo for input group pins in group</summary>
        protected override ChildInfo InputChildInfo
        {
            get { return groupType.inputChild; }
        }

        /// <summary>
        /// Gets ChildInfo for output group pins in group</summary>
        protected override ChildInfo OutputChildInfo
        {
            get { return groupType.outputChild; }
        }

        /// <summary>
        /// Gets group pin type.
        /// A group pin is a pin on a grouped sub-circuit; it extends the information of a pin
        /// to preserve the internal pin/module which is connected to the outside circuit.</summary>
        protected override DomNodeType GroupPinType
        {
            get { return groupSocketType.Type; }
        }

        // optional child info
        /// <summary>
        /// Gets ChildInfo for annotations (comments) in group.
        /// Return null if annotations are not supported.</summary>
        protected override ChildInfo AnnotationChildInfo
        {
            get { return groupType.annotationChild; }
        }

        #region IHierarchicalGraphNode and ICircuitGroupType Members

        /// <summary>
        /// Gets the sequence of nodes that are children of this group (hierarchical graph node)</summary>
        IEnumerable<ScriptNode> IHierarchicalGraphNode<ScriptNode, ScriptNodeConnection, ICircuitPin>.SubNodes
        {
            get
            {
                var graph = (IGraph<ScriptNode, ScriptNodeConnection, ICircuitPin>)this;
                return graph.Nodes;
            }
        }

        /// <summary>
        /// Gets the group's (subgraph's) internal edges</summary>
        IEnumerable<ScriptNodeConnection> ICircuitGroupType<ScriptNode, ScriptNodeConnection, ICircuitPin>.SubEdges
        {
            get { return m_connections; }
        }

        #endregion

        #region IGraph<Module,Connection,ICircuitPin> Members

        /// <summary>
        /// Gets the nodes in the group</summary>
        IEnumerable<ScriptNode> IGraph<ScriptNode, ScriptNodeConnection, ICircuitPin>.Nodes
        {
            get { return m_modules; }
        }

        /// <summary>
        /// Gets the edges in the group</summary>
        IEnumerable<ScriptNodeConnection> IGraph<ScriptNode, ScriptNodeConnection, ICircuitPin>.Edges
        {
            get
            {
                return m_connections;
            }
        }

        #endregion

        private DomNodeListAdapter<ScriptNode> m_modules;
        private DomNodeListAdapter<ScriptNodeConnection> m_connections;
        private ScriptNode m_thisModule;
    }
}

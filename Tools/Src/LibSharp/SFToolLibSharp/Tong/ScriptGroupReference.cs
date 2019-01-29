////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script ScriptGroup Reference
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    public class ScriptGroupReference : Sce.Atf.Controls.Adaptable.Graphs.GroupReference,
         ICircuitGroupType<ScriptNode, ScriptNodeConnection, ICircuitPin>, // for circuit render
         IReference<ScriptNode>
    {
        #region Fill required AttributeInfos 
        /// <summary>
        /// Gets name attribute for group instance</summary>
        protected override AttributeInfo NameAttribute
        {
            get { return groupType.nameAttribute; }
        }

        /// <summary>
        /// Gets label attribute for group instance</summary>
        protected override AttributeInfo LabelAttribute
        {
            get { return moduleType.labelAttribute; }
        }

        /// <summary>
        /// Gets x-coordinate position attribute for group instance</summary>
        protected override AttributeInfo XAttribute
        {
            get { return groupType.xAttribute; }
        }

        /// <summary>
        /// Gets y-coordinate position attribute for group instance</summary>
        protected override AttributeInfo YAttribute
        {
            get { return groupType.yAttribute; }
        }

        /// <summary>
        /// Gets visibility attribute for group instance</summary>
        protected override AttributeInfo VisibleAttribute
        {
            get { return groupType.visibleAttribute; }
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

        protected override AttributeInfo ShowExpandedGroupPinsAttribute
        {
            get { return groupTemplateRefType.refShowExpandedGroupPinsAttribute; }
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


        protected override AttributeInfo GuidRefAttribute
        {
            get { return groupTemplateRefType.guidRefAttribute; }
        }

        #endregion

        #region ICircuitGroupType members

        IEnumerable<ScriptNode> IHierarchicalGraphNode<ScriptNode, ScriptNodeConnection, ICircuitPin>.SubNodes
        {
            get
            {
                if (Group != null)
                    return Group.Elements.AsIEnumerable<ScriptNode>();
                return EmptyEnumerable<ScriptNode>.Instance;
            }
        }

        /// <summary>
        /// Gets the group's (subgraph's) internal edges</summary>
        IEnumerable<ScriptNodeConnection> ICircuitGroupType<ScriptNode, ScriptNodeConnection, ICircuitPin>.SubEdges
        {
            get
            {
                if (Group != null)
                    return Group.Wires.AsIEnumerable<ScriptNodeConnection>();
                return EmptyEnumerable<ScriptNodeConnection>.Instance;
            }
        }

        #endregion

        #region IReference<Module> members

        bool IReference<ScriptNode>.CanReference(ScriptNode item)
        {
            return item.Is<ScriptGroup>();
        }

        ScriptNode IReference<ScriptNode>.Target
        {
            get { return Template.Target.As<ScriptNode>(); }
            set
            {
                throw new InvalidOperationException("The group template determines the target");
            }
        }
        #endregion

    }
}

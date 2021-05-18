////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node element reference
//
////////////////////////////////////////////////////////////////////////////////


using System;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;


namespace SF.Tong
{
    /// <summary>
    /// Adapter for a reference instance of a module template</summary>
    public class ScriptNodeReference : ElementReference, IReference<ScriptNode>
    {
        protected override AttributeInfo GuidRefAttribute
        {
            get { return moduleTemplateRefType.guidRefAttribute; }
        }

        #region IReference<Module>  memebers

        bool IReference<ScriptNode>.CanReference(ScriptNode item)
        {
            return true;
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

        /// <summary>
        /// Gets the name attribute for module instance</summary>
        protected override AttributeInfo NameAttribute
        {
            get { return moduleType.nameAttribute; }
        }

        /// <summary>
        /// Gets the label attribute for module instance</summary>
        protected override AttributeInfo LabelAttribute
        {
            get { return moduleType.labelAttribute; }
        }

        /// <summary>
        /// Gets the x-coordinate position attribute for module instance</summary>
        protected override AttributeInfo XAttribute
        {
            get { return moduleType.xAttribute; }
        }

        /// <summary>
        /// Gets the y-coordinate position attribute for module instance</summary>
        protected override AttributeInfo YAttribute
        {
            get { return moduleType.yAttribute; }
        }

        /// <summary>
        /// Gets the visible attribute for module instance</summary>
        protected override AttributeInfo VisibleAttribute
        {
            get { return moduleType.visibleAttribute; }
        }
    }
}

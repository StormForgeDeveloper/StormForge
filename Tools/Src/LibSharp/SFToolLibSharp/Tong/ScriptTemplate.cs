////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script template
//
////////////////////////////////////////////////////////////////////////////////

using System;

using Sce.Atf.Adaptation;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to a template, which is is a module that can be referenced into a circuit</summary>
    public class ScriptTemplate : Template
    {
        /// <summary>
        /// Gets and sets the user-visible name of the template</summary>
        public override string Name
        {
            get { return (string)DomNode.GetAttribute(templateType.labelAttribute); }
            set { DomNode.SetAttribute(templateType.labelAttribute, value); }
        }

        /// <summary>
        /// Gets or sets DomNode module that represents the template</summary>
        public override DomNode Target
        {
            get { return GetChild<DomNode>(templateType.moduleChild); }
            set
            {
                SetChild(templateType.moduleChild, value);
                if (value != null) // initialize  model name
                {
                    var module = Target.Cast<ScriptNode>();
                    Name = module.TitleText;
                    if (string.IsNullOrEmpty(Name))
                        Name = module.ElementType.TitleText;

                }
            }
        }

        /// <summary>Gets and sets  a globally unique identifier (GUID) that represents this template</summary>
        public override Guid Guid
        {
            get { return new Guid((string)DomNode.GetAttribute(templateType.guidAttribute)); }
            set { DomNode.SetAttribute(templateType.guidAttribute, value.ToString()); }
        }

        /// <summary>
        /// Returns true iff the template can reference the specified target item</summary>
        public override bool CanReference(DomNode item)
        {
            return item.Is<ScriptNode>();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script validator
//
////////////////////////////////////////////////////////////////////////////////

using System;

using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;


namespace SF.Tong
{
    /// <summary>
    /// Adapter that tracks changes to transitions and updates their routing during validation.
    /// Update transitions on Ending event are part of the transactions themselves, 
    /// then validate all sub-graphs in the current document on Ended event. Requires
    /// Sce.Atf.Dom.ReferenceValidator to be available on the adapted DomNode.</summary>
    public class ScriptValidator : Sce.Atf.Controls.Adaptable.Graphs.CircuitValidator
    {

        /// <summary>
        /// Performs initialization when the adapter's node is set</summary>
        protected override void OnNodeSet()
        {
            base.OnNodeSet();
            ValidateNodes();
        }


        /// <summary>
        /// Gets module label attribute</summary>
        protected override AttributeInfo ElementLabelAttribute
        {
            get { return moduleType.labelAttribute; }
        }

        /// <summary>
        /// Gets pin name attribute</summary>
        protected override AttributeInfo PinNameAttributeAttribute
        {
            get { return socketType.nameAttribute; }
        }

        /// <summary>
        /// Performs custom actions on validation Ended events</summary>
        /// <param name="sender">Validation context</param>
        /// <param name="e">Event args</param>
        protected override void OnEnded(object sender, EventArgs e)
        {
            base.OnEnded(sender, e);
            ValidateNodes();
        }

        private void ValidateNodes()
        {
            //// pseudo code to update element's IsValid 
            //foreach (var node in DomNode.Subtree)
            //{
            //    var element = node.As<Element>();
            //    if (element != null)
            //        element.ElementInfo.IsValid = !string.IsNullOrEmpty(element.Name);
            //}
        }
    }
}

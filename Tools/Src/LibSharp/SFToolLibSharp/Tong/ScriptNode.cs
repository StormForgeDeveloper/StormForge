////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script script node
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;


namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to circuit modules, which is the base circuit element with pins.
    /// It maintains local name and bounds for faster
    /// circuit rendering during editing operations, like dragging modules and wires.</summary>
    public class ScriptNode : Element
    {
        public ScriptNode()
        {

        }

        /// <summary>
        /// Gets name attribute for node
        /// </summary>
        protected override AttributeInfo NameAttribute
        {
            get { return moduleType.nameAttribute; }
        }

        /// <summary>
        /// Gets label attribute on module</summary>
        protected override AttributeInfo LabelAttribute
        {
            get { return moduleType.labelAttribute; }
        }

        /// <summary>
        /// Gets x-coordinate position attribute for module</summary>
        protected override AttributeInfo XAttribute
        {
            get { return moduleType.xAttribute; }
        }

        /// <summary>
        /// Gets y-coordinate position attribute for module</summary>
        protected override AttributeInfo YAttribute
        {
            get { return moduleType.yAttribute; }
        }

        /// <summary>
        /// Gets visible attribute for module</summary>
        protected override AttributeInfo VisibleAttribute
        {
            get { return moduleType.visibleAttribute; }
        }

        /// <summary>
        /// Gets the optional AttributeInfo for the original GUID of template 
        /// if this module is a copy-instance of a template(and nothing else) </summary>
        protected override AttributeInfo SourceGuidAttribute
        {
            get { return moduleType.sourceGuidAttribute; }
        }

        /// <summary>
        /// Gets the optional AttributeInfo for storing whether or not unconnected
        /// pins should be displayed.</summary>
        protected override AttributeInfo ShowUnconnectedPinsAttribute
        {
            get { return moduleType.showUnconnectedPinsAttribute; }
        }

        protected override CircuitElementInfo CreateElementInfo()
        {
            return new ScriptNodeElementInfo();
        }
    }
}

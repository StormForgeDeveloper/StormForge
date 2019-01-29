////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script script group socket
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;


namespace SF.Tong
{
    /// <summary>
    /// Adapter for a pin on a group module, with extra information needed to associate the pin
    /// on the group with the internal module where it was connected before grouping.
    /// A group pin is a pin on a grouped sub-circuit; it extends the information
    /// of a pin to preserve the internal pin/module which is connected to the outside circuit.</summary>
    public class ScriptGroupSocket : Sce.Atf.Controls.Adaptable.Graphs.GroupPin, ICircuitGroupPin<ScriptNode>
    {
        // for bases class Pin
        /// <summary>
        /// Gets type attribute for group pin</summary>
        protected override AttributeInfo TypeNameAttribute => socketType.typeAttribute;

        /// <summary>
        /// Gets name attribute for group pin</summary>
        protected override AttributeInfo NameAttribute => socketType.nameAttribute;

        /// <summary>
        /// Pint Type, is this input pin?
        /// </summary>
        protected override AttributeInfo IsInputAttribute => socketType.isInputAttribute;

        /// <summary>
        /// Gets index (pin order in its sub-graph owner) attribute for group pin</summary>
        protected override AttributeInfo IndexAttribute => groupSocketType.indexAttribute;

        /// <summary>
        /// Gets floating y-coordinate attribute for group pin. 
        /// Floating pin location y value is user defined (x value is auto-generated).</summary>
        protected override AttributeInfo PinYAttribute => groupSocketType.pinYAttribute;

        /// <summary>
        /// Gets module (associated internal subelement) attribute for group pin</summary>
        protected override AttributeInfo ElementAttribute => groupSocketType.moduleAttribute;

        /// <summary>
        /// Gets pin (associated internal subpin) attribute for group pin</summary>
        protected override AttributeInfo PinAttribute => groupSocketType.pinAttribute;

        /// <summary>
        /// Gets pinned attribute for group pin</summary>
        protected override AttributeInfo PinnedAttribute => groupSocketType.pinnedAttribute;

        /// <summary>
        /// Gets visible attribute for group pin</summary>
        protected override AttributeInfo VisibleAttribute => groupSocketType.visibleAttribute;

        #region ICircuitGroupPin members (needed for drawing)

        /// <summary>
        /// Gets the internal module corresponding to this group pin</summary>
        ScriptNode ICircuitGroupPin<ScriptNode>.InternalElement
        {
            get { return GetReference<ScriptNode>(groupSocketType.moduleAttribute); }
        
        }    

        #endregion

       
    }
}

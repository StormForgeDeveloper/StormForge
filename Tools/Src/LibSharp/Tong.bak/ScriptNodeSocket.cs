////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node socket
//
////////////////////////////////////////////////////////////////////////////////

using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to a pin in a circuit; used in mastering and as a base
    /// class for GroupPin</summary>
    public class ScriptNodeSocket : Sce.Atf.Controls.Adaptable.Graphs.Pin
    {
        /// <summary>
        /// Gets type attribute of Pin</summary>
        protected override AttributeInfo TypeNameAttribute => socketType.typeAttribute;

        /// <summary>
        /// Gets name attribute of Pin</summary>
        protected override AttributeInfo NameAttribute => socketType.nameAttribute;

        /// <summary>
        /// Pint Type, is this input pin?
        /// </summary>
        protected override AttributeInfo IsInputAttribute => socketType.isInputAttribute;

        protected override AttributeInfo IndexAttribute => null;
    }
}

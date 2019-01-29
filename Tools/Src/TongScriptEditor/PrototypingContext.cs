////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Prototyping context
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf.Dom;

using SF.Tong;
using SF.Tong.Schema;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong.Editor
{
    /// <summary>
    /// Editing context for prototypes in the circuit document; this is the context that is
    /// bound to the PrototypeLister when a circuit document becomes the active context. This
    /// context implements instancing differently than the CircuitContext. It can insert modules
    /// and connections, converting them into prototypes. It can only copy and delete prototypes.</summary>
    public class PrototypingContext : Sce.Atf.Controls.Adaptable.Graphs.PrototypingContext
    {
        /// <summary>
        /// Gets ChildInfo for prototype folders in prototype folder</summary>
        protected override ChildInfo PrototypeFolderChildInfo
        {
            get { return tongScriptDocumentType.prototypeFolderChild; }
        }

        /// <summary>
        /// Gets type of prototype</summary>
        protected override DomNodeType PrototypeType
        {
            get { return prototypeType.Type; }
        }
    }
}

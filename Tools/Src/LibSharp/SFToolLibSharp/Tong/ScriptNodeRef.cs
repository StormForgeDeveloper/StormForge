////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node 
//
////////////////////////////////////////////////////////////////////////////////

using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    /// <summary>
    /// Adapter for a script node reference, used within layer folders to represent
    /// circuit modules that belong to that layer.
    /// </summary>
    public class ScriptNodeRef : ElementRef
    {
        /// <summary>
        /// Gets the AttributeInfo for a module reference</summary>
        protected override AttributeInfo RefAttribute
        {
            get { return moduleRefType.refAttribute; }
        }
    }
}

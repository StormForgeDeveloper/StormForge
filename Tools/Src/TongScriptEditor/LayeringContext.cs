////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Layering context
//
////////////////////////////////////////////////////////////////////////////////

using Sce.Atf.Dom;

using SF.Tong;
using SF.Tong.Schema;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong.Editor
{
    /// <summary>
    /// Context for the LayerLister</summary>
    /// <remarks>This context has its own independent selection, 
    /// but uses the main GameContext's HistoryContext for undo/redo operations.
    /// IInstancingContext and IHierarchicalInsertionContext implementations control drag/drop and 
    /// copy/paste operations within the LayerLister (internal), pastes/drops to the 
    /// LayerLister and drag/copies from the LayerLister (external).
    /// The IObservableContext implementation notifies the LayerLister's TreeControl
    /// when a change occurs that requires an update of one or more tree nodes.
    /// The ITreeView implementation controls the hierarchy in the LayerLister's TreeControl.
    /// The IItemView implementation controls icons and labels in the LayerLister's TreeControl.</remarks>
    class LayeringContext : Sce.Atf.Controls.Adaptable.Graphs.LayeringContext
    {
        /// <summary>
        /// Gets visible attribute for layer</summary>
        protected override AttributeInfo VisibleAttribute
        {
            get { return moduleType.visibleAttribute; }
        }

        /// <summary>
        /// Gets ChildInfo for layers in circuit</summary>
        protected override ChildInfo LayerFolderChildInfo
        {
            get { return tongScriptType.layerFolderChild; }
        }

        /// <summary>
        /// Gets type of layer folder</summary>
        protected override DomNodeType LayerFolderType
        {
            get { return layerFolderType.Type; }
        }

        /// <summary>
        /// Gets type of module reference</summary>
        protected override DomNodeType ElementRefType
        {
            get { return moduleRefType.Type; }
        }
    }
}

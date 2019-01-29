////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Layering command
//
////////////////////////////////////////////////////////////////////////////////

using System.ComponentModel.Composition;
using Sce.Atf.Applications;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

using SF.Tong;

namespace SF.Tong.Editor
{
    /// <summary>
    /// Component to add "Add Layer" command to application. Command is accessible only
    /// by right click (context menu).</summary>
    [Export(typeof(LayeringCommands))]
    public class LayeringCommands : Sce.Atf.Controls.Adaptable.Graphs.LayeringCommands
    {
        /// <summary>
        /// Constructor</summary>
        /// <param name="commandService">Command service</param>
        /// <param name="contextRegistry">Context registry</param>
        /// <param name="layerLister">Layer lister</param>
        [ImportingConstructor]
        public LayeringCommands(ICommandService commandService, IContextRegistry contextRegistry, LayerLister layerLister) :
            base(commandService, contextRegistry, layerLister)
        {
        }

        /// <summary>
        /// Gets type of layer folder</summary>
        protected override DomNodeType LayerFolderType
        {
            get { return layerFolderType.Type; }
        }
    }
}

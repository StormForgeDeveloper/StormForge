////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script 
//
////////////////////////////////////////////////////////////////////////////////

using System.Collections.Generic;
using System.Linq;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using SF.Tong.Schema;

namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to a circuit and observable context with change notification events</summary>
    public class TongScript : Sce.Atf.Controls.Adaptable.Graphs.Circuit, IGraph<ScriptNode, ScriptNodeConnection, ICircuitPin>
    {
        /// <summary>
        /// Performs initialization when the adapter is connected to the circuit's DomNode</summary>
        protected override void OnNodeSet()
        {
            // cache these list wrapper objects
            m_modules = new DomNodeListAdapter<ScriptNode>(DomNode, tongScriptType.moduleChild);
            m_connections = new DomNodeListAdapter<ScriptNodeConnection>(DomNode, tongScriptType.connectionChild);
            new DomNodeListAdapter<ScriptAnnotation>(DomNode, tongScriptType.annotationChild);
            base.OnNodeSet();
        }

        /// <summary>
        /// Gets ChildInfo for Elements (circuit elements with pins) in circuit</summary>
        protected override ChildInfo ElementChildInfo
        {
            get { return tongScriptType.moduleChild; }
        }

        /// <summary>
        /// Gets ChildInfo for Wires (connections) in circuit</summary>
        protected override ChildInfo WireChildInfo
        {
            get { return tongScriptType.connectionChild; }
        }

        // optional child info
        /// <summary>
        /// Gets ChildInfo for annotations (comments) in circuit.
        /// Return null if annotations are not supported.</summary>
        protected override ChildInfo AnnotationChildInfo
        {
            get { return tongScriptType.annotationChild; }
        }

        #region IGraph Members

        /// <summary>
        /// Gets all visible nodes in the circuit</summary>
        ///<remarks>IGraph.Nodes is called during circuit rendering, and picking(in reverse order).</remarks>
        IEnumerable<ScriptNode> IGraph<ScriptNode, ScriptNodeConnection, ICircuitPin>.Nodes
        {
            get
            {
                return m_modules.Where(x => x.Visible);
            }
        }

        /// <summary>
        /// Gets enumeration of all connections between visible nodes in the circuit</summary>
        IEnumerable<ScriptNodeConnection> IGraph<ScriptNode, ScriptNodeConnection, ICircuitPin>.Edges
        {
            get
            {
                  return m_connections.Where(x => x.InputElement != null && x.OutputElement != null && x.InputElement.Visible && x.OutputElement.Visible);
            }
        }


        #endregion
       

        private DomNodeListAdapter<ScriptNode> m_modules;
        private DomNodeListAdapter<ScriptNodeConnection> m_connections;
    }
}

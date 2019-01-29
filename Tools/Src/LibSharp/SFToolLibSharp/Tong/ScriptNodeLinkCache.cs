////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node link cache
//
////////////////////////////////////////////////////////////////////////////////

using System.Collections.Generic;
using System.Linq;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

using SF.Tong.Schema;
using Sce.Atf.Adaptation;

namespace SF.Tong
{
    /// <summary>Script node link cache</summary>
    public class ScriptNodeLinkCache : DomNodeAdapter
    {
        // connections
        public List<ScriptNodeConnection> FromThis => m_From;
        public List<ScriptNodeConnection> ToThis => m_To;


        /// <summary>
        /// Performs initialization when the adapter is connected to the circuit's DomNode</summary>
        protected override void OnNodeSet()
        {

            base.OnNodeSet();

        }


        // This list will be updated by TongScriptObjectTable
        private List<ScriptNodeConnection> m_From = new List<ScriptNodeConnection>();
        private List<ScriptNodeConnection> m_To = new List<ScriptNodeConnection>();
    }
}

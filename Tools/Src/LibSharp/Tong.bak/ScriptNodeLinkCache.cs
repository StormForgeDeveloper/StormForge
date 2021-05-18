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
        public List<ScriptNodeConnection> FromThisNode => m_FromThisNode;
        public Dictionary<ICircuitPin, List<ScriptNodeConnection>> FromThisNodePin => m_FromThisNodePin;
        public List<ScriptNodeConnection> ToThisNode => m_ToThisNode;
        public Dictionary<ICircuitPin, List<ScriptNodeConnection>> ToThisNodePin => m_ToThisNodePin;

        public void NewConnectionFromThis(ScriptNodeConnection connection)
        {
            FromThisNode.Add(connection);
            List<ScriptNodeConnection> pinList;
            m_FromThisNodePin.TryGetValue(connection.OutputPin, out pinList);
            if(pinList == null)
            {
                pinList = new List<ScriptNodeConnection>();
            }

            if (pinList.Find(x => x == connection) == null)
                pinList.Add(connection);
        }

        public void NewConnectionToThis(ScriptNodeConnection connection)
        {
            ToThisNode.Add(connection);
            List<ScriptNodeConnection> pinList;
            m_ToThisNodePin.TryGetValue(connection.InputPin, out pinList);
            if (pinList == null)
            {
                pinList = new List<ScriptNodeConnection>();
            }

            if (pinList.Find(x => x == connection) == null)
                pinList.Add(connection);
        }

        /// <summary>
        /// Performs initialization when the adapter is connected to the circuit's DomNode</summary>
        protected override void OnNodeSet()
        {

            base.OnNodeSet();

        }


        Dictionary<ICircuitPin, List<ScriptNodeConnection>> m_FromThisNodePin = new Dictionary<ICircuitPin, List<ScriptNodeConnection>>();
        Dictionary<ICircuitPin, List<ScriptNodeConnection>> m_ToThisNodePin = new Dictionary<ICircuitPin, List<ScriptNodeConnection>>();
        // This list will be updated by TongScriptObjectTable
        private List<ScriptNodeConnection> m_FromThisNode = new List<ScriptNodeConnection>();
        private List<ScriptNodeConnection> m_ToThisNode = new List<ScriptNodeConnection>();
    }
}

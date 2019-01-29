////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script object table
//
////////////////////////////////////////////////////////////////////////////////

using System.Collections.Generic;
using System.Linq;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;
using Sce.Atf.Adaptation;

using SF.Tong.Schema;

namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to a circuit and observable context with change notification events</summary>
    public class TongScriptObjectTable : DomNodeAdapter
    {
        // Nodes
        public IDictionary<string, ScriptNode> NodeMap => m_Nodes;


        /// <summary>
        /// Performs initialization when the adapter is connected to the circuit's DomNode</summary>
        protected override void OnNodeSet()
        {

            base.OnNodeSet();

            var nodes = GetChildList<ScriptNode>(tongScriptType.moduleChild);
            foreach(var node in nodes)
            {
                AddNode(node);
            }

            var connections = GetChildList<ScriptNodeConnection>(tongScriptType.connectionChild);
            foreach (var connection in connections)
            {
                AddConnection(connection);
            }

            DomNode.ChildInserted += DomNode_ChildInserted;
            DomNode.ChildRemoved += DomNode_ChildRemoved;
        }

        private void DomNode_ChildInserted(object sender, ChildEventArgs e)
        {
            if (e.Parent == DomNode)
            {
                if (e.Child.Type == connectionType.Type)
                {
                    AddConnection(e.Child.As<ScriptNodeConnection>());
                }
                else if (e.Child.Type == groupType.Type || e.Child.Type == moduleType.Type)
                {
                    AddNode(e.Child.As<ScriptNode>());
                }
            }
            // should be some child of group
            else if (e.Parent.Type == groupType.Type)
            {
                AddNode(e.Child.As<ScriptNode>());
            }
            else
            {
                // Ignore other case
            }
        }

        private void DomNode_ChildRemoved(object sender, ChildEventArgs e)
        {
            if (e.Parent == DomNode)
            {
                if (e.Child.Type == connectionType.Type)
                {
                    RemoveConnection(e.Child.As<ScriptNodeConnection>());
                }
                else if (e.Child.Type == groupType.Type || e.Child.Type == moduleType.Type)
                {
                    RemoveNode(e.Child.As<ScriptNode>());
                }
            }
            // should be some child of group
            else if (e.Parent.Type == groupType.Type)
            {
                RemoveNode(e.Child.As<ScriptNode>());
            }
        }


        void AddNode(ScriptNode node)
        {
            if (node == null)
                return;

            if (node.DomNode.Type == groupType.Type)
            {
                var group = node.As<ScriptGroup>();

                m_Nodes.Add(node.Id, node);

                foreach (var child in group.Elements)
                {
                    m_Nodes.Add(child.Id, child.As<ScriptNode>());
                }
            }
            else
            {
                m_Nodes.Add(node.Id, node);
            }
        }

        void RemoveNode(ScriptNode node)
        {
            if (node == null)
                return;

            if (node.DomNode.Type == groupType.Type)
            {
                var group = node.As<ScriptGroup>();

                m_Nodes.Remove(node.Id);

                foreach (var child in group.Elements)
                {
                    m_Nodes.Remove(child.Id);
                }
            }
            else if (node.DomNode.Type == moduleType.Type)
            {
                m_Nodes.Remove(node.Id);
            }
        }

        void AddConnection(ScriptNodeConnection connection)
        {
            if (connection == null)
                return;

            var linkCache = connection.OutputElement.As<ScriptNodeLinkCache>();
            if (linkCache == null)
                throw new System.Exception("We need ScriptNodeLinkCache adaptable for nodes");

            linkCache.FromThis.Add(connection);

            var linkCacheTo = connection.InputElement.As<ScriptNodeLinkCache>();
            if (linkCacheTo == null)
                throw new System.Exception("We need ScriptNodeLinkCache adaptable for nodes");

            linkCacheTo.ToThis.Add(connection);
        }

        void RemoveConnection(ScriptNodeConnection connection)
        {
            if (connection == null)
                return;

            var linkCache = connection.OutputElement.As<ScriptNodeLinkCache>();
            if (linkCache == null)
                throw new System.Exception("We need ScriptNodeLinkCache adaptable for nodes");

            linkCache.FromThis.Remove(connection);

            var linkCacheTo = connection.InputElement.As<ScriptNodeLinkCache>();
            if (linkCacheTo == null)
                throw new System.Exception("We need ScriptNodeLinkCache adaptable for nodes");

            linkCacheTo.ToThis.Remove(connection);
        }

        // 
        private Dictionary<string, ScriptNode> m_Nodes = new Dictionary<string, ScriptNode>();
    }
}

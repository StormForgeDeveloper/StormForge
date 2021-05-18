////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
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
using Sce.Atf;
using System;

namespace SF.Tong
{
    /// <summary>Script graph node</summary>
    public class ScriptGraphNode : DomNodeAdapter
    {
        public class NodePin
        {
            public NameString Name;
            public NameString Type;
            public List<NodeLink> LinkTo;
        }
        public class NodeLink
        {
            public ScriptNodeConnection Connection;
            public ScriptGraphNode Target;
            public NodePin Pin;
        }

        // connections
        public Dictionary<NameString, NodePin> FromThisNodePin => m_FromThisNodePin;
        public Dictionary<NameString, NodePin> ToThisNodePin => m_ToThisNodePin;

        public void NewConnectionFromThis(ScriptNodeConnection connection)
        {
            var pinInfo = connection.OutputPin;
            NodePin pinList;
            m_FromThisNodePin.TryGetValue(pinInfo.Name, out pinList);
            if(pinList == null)
            {
                pinList = new NodePin()
                {
                    Name = new NameString(pinInfo.Name),
                    Type = new NameString(pinInfo.PinType.Name),
                    LinkTo = new List<NodeLink>()
                };
            }

            if (pinList.LinkTo.Find(x => x.Connection == connection) == null)
            {
                var newPinInfo = new NodeLink()
                {
                    Connection = connection,
                    Target = connection.OutputElement.As<ScriptGraphNode>(),
                    Pin = new NodePin()
                };
                pinList.LinkTo.Add(newPinInfo);
            }
        }

        public void NewConnectionToThis(ScriptNodeConnection connection)
        {
            var pinInfo = connection.InputPin;
            NodePin pinList;
            m_ToThisNodePin.TryGetValue(pinInfo.Name, out pinList);
            if (pinList == null)
            {
                pinList = new NodePin()
                {
                    Name = new NameString(pinInfo.Name),
                    Type = new NameString(pinInfo.PinType.Name),
                    LinkTo = new List<NodeLink>()
                };
            }

            if (pinList.LinkTo.Find(x => x.Connection == connection) == null)
            {
                var newPinInfo = new NodeLink()
                {
                    Connection = connection,
                    Target = connection.InputElement.As<ScriptGraphNode>(),
                    Pin = new NodePin()
                };
                pinList.LinkTo.Add(newPinInfo);
            }
        }

        /// <summary>
        /// Performs initialization when the adapter is connected to the circuit's DomNode</summary>
        protected override void OnNodeSet()
        {
            base.OnNodeSet();
        }


        public delegate bool delNodeHandler(ScriptGraphNode curNode );

        /// <summary>
        /// Traverse
        /// </summary>
        public void TraverseInputDFS(delNodeHandler handleFunc)
        {
            var traversed = new HashSet<ScriptGraphNode>();
            TraverseInputInternalDFS(traversed, this, handleFunc);
        }

        static bool TraverseInputInternalDFS(HashSet<ScriptGraphNode> traversed, ScriptGraphNode curNode, delNodeHandler handleFunc)
        {
            if (curNode == null)
                return true;

            if (!traversed.Contains(curNode))
            {
                if (curNode.m_ToThisNodePin != null)
                {
                    foreach (var itNodePin in curNode.m_ToThisNodePin)
                    {
                        var nodePin = itNodePin.Value;
                        foreach (var link in nodePin.LinkTo)
                        {
                            if (!TraverseInputInternalDFS(traversed, link.Target, handleFunc))
                                return false;
                        }
                    }
                }

                traversed.Add(curNode);
            }

            return handleFunc(curNode);
        }


        Dictionary<NameString, NodePin> m_FromThisNodePin = new Dictionary<NameString, NodePin>();
        Dictionary<NameString, NodePin> m_ToThisNodePin = new Dictionary<NameString, NodePin>();
    }
}

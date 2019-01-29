////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script editing context
//
////////////////////////////////////////////////////////////////////////////////


using System.Collections.Generic;
using System.Drawing;
using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Controls.Adaptable;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

using SF.Tong;

namespace SF.Tong.Editor
{
    /// <summary>
    /// Class that defines a circuit editing context. Each context represents a circuit,
    /// with a history, selection, and editing capabilities. There may be multiple
    /// contexts within a single circuit document, because each sub-circuit has its own
    /// editing context.</summary>
    public class TongScriptEditingContext : Sce.Atf.Controls.Adaptable.Graphs.CircuitEditingContext, 
        IEditableGraphContainer<ScriptNode, ScriptNodeConnection, ICircuitPin>
    {
        public TongScriptEditingContext()
        {

        }

        /// <summary>
        /// Gets DomNodeType of Wire</summary>
        protected override DomNodeType WireType
        {
            get { return connectionType.Type; }
        }


        #region IEditableGraphContainer<Module, Connection, ICircuitPin>
        /// <summary>
        /// Can given modules be moved into a new container</summary>
        /// <param name="newParent">New module parent</param>
        /// <param name="movingObjects">Objects being moved</param>
        /// <returns>True iff objects can be moved to new parent</returns>
        bool IEditableGraphContainer<ScriptNode, ScriptNodeConnection, ICircuitPin>.CanMove(object newParent, IEnumerable<object> movingObjects)
        {
            if (newParent.Is<IReference<ScriptNode>>())
                return false; 
            var editableGraphContainer =
                DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            return editableGraphContainer.CanMove(newParent, movingObjects);
        }

        /// <summary>
        /// Move the given nodes into the container</summary>
        /// <param name="newParent">New container</param>
        /// <param name="movingObjects">Nodes to move</param>
        void IEditableGraphContainer<ScriptNode, ScriptNodeConnection, ICircuitPin>.Move(object newParent, IEnumerable<object> movingObjects)
        {
            var editableGraphContainer =
               DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            editableGraphContainer.Move(newParent, movingObjects);
        }

        /// <summary>
        /// Can a container be resized</summary>
        /// <param name="container">Container to resize</param>
        /// <param name="borderPart">Part of border to resize</param>
        /// <returns>True iff the container border can be resized</returns>
        bool IEditableGraphContainer<ScriptNode, ScriptNodeConnection, ICircuitPin>.CanResize(object container, DiagramBorder borderPart)
        {
            var editableGraphContainer =
               DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            return editableGraphContainer.CanResize(container, borderPart);
        }

        /// <summary>
        /// Resize a container</summary>
        /// <param name="container">Container to resize</param>
        /// <param name="newWidth">New container width</param>
        /// <param name="newHeight">New container height</param>
        void IEditableGraphContainer<ScriptNode, ScriptNodeConnection, ICircuitPin>.Resize(object container, int newWidth, int newHeight)
        {
            var editableGraphContainer =
                 DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            editableGraphContainer.Resize(container, newWidth, newHeight);
        }

        #endregion

        /// <summary>
        /// Returns whether two nodes can be connected. "from" and "to" refer to the corresponding
        /// properties in IGraphEdge, not to a dragging operation, for example.</summary>
        /// <param name="fromNode">"From" node</param>
        /// <param name="fromRoute">"From" edge route</param>
        /// <param name="toNode">"To" node</param>
        /// <param name="toRoute">"To" edge route</param>
        /// <returns>Whether the "from" node/route can be connected to the "to" node/route</returns>
        public bool CanConnect(ScriptNode fromNode, ICircuitPin fromRoute, ScriptNode toNode, ICircuitPin toRoute)
        {
            var editableGraphContainer =
               DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            return editableGraphContainer.CanConnect(fromNode, fromRoute, toNode, toRoute);
        }

        /// <summary>
        /// Connects the "from" node/route to the "to" node/route by creating an IGraphEdge whose
        /// "from" node is "fromNode", "to" node is "toNode", etc.</summary>
        /// <param name="fromNode">"From" node</param>
        /// <param name="fromRoute">"From" edge route</param>
        /// <param name="toNode">"To" node</param>
        /// <param name="toRoute">"To" edge route</param>
        /// <param name="existingEdge">Existing edge that is being reconnected, or null if new edge</param>
        /// <returns>New edge connecting the "from" node/route to the "to" node/route</returns>
        public ScriptNodeConnection Connect(ScriptNode fromNode, ICircuitPin fromRoute, ScriptNode toNode, ICircuitPin toRoute, ScriptNodeConnection existingEdge)
        {
            var editableGraphContainer =
            DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            return editableGraphContainer.Connect(fromNode, fromRoute, toNode, toRoute, existingEdge).Cast<ScriptNodeConnection>();
        }

        /// <summary>
        /// Gets whether the edge can be disconnected</summary>
        /// <param name="edge">Edge to disconnect</param>
        /// <returns>Whether the edge can be disconnected</returns>
        public bool CanDisconnect(ScriptNodeConnection edge)
        {
            var editableGraphContainer =
              DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            return editableGraphContainer.CanDisconnect(edge);
        }

        /// <summary>
        /// Disconnects the edge</summary>
        /// <param name="edge">Edge to disconnect</param>
        public void Disconnect(ScriptNodeConnection edge)
        {
            var editableGraphContainer =
                DomNode.Cast<TongScriptEditingContext>() as IEditableGraphContainer<Element, Wire, ICircuitPin>;
            editableGraphContainer.Disconnect(edge);
        }

        /// <summary>
        /// Finds element, edge or pin hit by the given point</summary>
        /// <param name="point">point in client space</param>
        /// <remarks>Implement the pick method to support drag & drop onto a group directly</remarks>
        protected override GraphHitRecord<Element, Wire, ICircuitPin> Pick(Point point)
        {
            var viewingContext = DomNode.Cast<IViewingContext>();
            var control = viewingContext.As<AdaptableControl>();
            if (viewingContext == null || control == null)
                return null;

            var graphAdapter = control.As<D2dGraphAdapter<ScriptNode, ScriptNodeConnection, ICircuitPin>>();
            GraphHitRecord<ScriptNode, ScriptNodeConnection, ICircuitPin> hitRecord = graphAdapter.Pick(point);
            var result = new GraphHitRecord<Element, Wire, ICircuitPin>(hitRecord.Node, hitRecord.Part);
            result.SubItem = hitRecord.SubItem;
            result.SubPart = hitRecord.SubPart;

            return result;
        }     
    }
}

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node element type
//
////////////////////////////////////////////////////////////////////////////////



using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using Sce.Atf.Adaptation;
using Sce.Atf.Rendering;
using System.Drawing;
using System.Collections.Generic;
using System.Xml;
using Sce.Atf;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to circuit ModuleDynamicSocketss, which is the base circuit element with pins.
    /// It maintains local name and bounds for faster
    /// circuit rendering during editing operations, like dragging ModuleDynamicSocketss and wires.</summary>
    public class ScriptNodeElementType : DomNodeAdapter, ICircuitElementType
    {

        /// <summary>
        /// Gets the element type name
        ///  This is going to be drawn on the title bar
        /// </summary>
        public string TitleText
        {
            get
            {
                if (string.IsNullOrEmpty(m_cachedTitleText))
                    UpdateTitleText();

                return m_cachedTitleText;
            }
        }


        /// <summary>
        /// Gets the element display name
        ///  This show up at the bottom of the box
        /// </summary>
        //public string DisplayName => GetAttribute<string>(moduleType.nameAttribute);
        public string BottomDisplayName => GetAttribute<string>(moduleType.nameAttribute);

        /// <summary>
        /// Gets desired interior size, in pixels, of this element type
        /// </summary>
        public Size InteriorSize => (m_Image != null) ? new Size(32, 32) : new Size();

        /// <summary>
        /// Gets image to draw for this element type</summary>
        public Image Image => m_Image;

        /// <summary>
        /// Gets a read-only list of input pins for this element type. For Groups, this list
        /// only includes pins whose Info.Visible property is true. Consider using GetAllInputPins()
        /// or GetInputPin() when using ICircuitGroupPin's InternalPinName to look for the
        /// corresponding pin.</summary>
        public PinList<ICircuitPin> Inputs => m_Inputs;

        /// <summary>
        /// Gets a read-only list of output pins for this element type. For Groups, this list
        /// only includes pins whose Info.Visible property is true. Consider using GetAllOutputPins()
        /// or GetOutputPin() when using ICircuitGroupPin's InternalPinName to look for the
        /// corresponding pin.</summary>
        public PinList<ICircuitPin> Outputs => m_Outputs;


        protected virtual void OnAttributeChanged(object sender, AttributeEventArgs e)
        {
            if (e.DomNode != DomNode)
                return;

            if (e.AttributeInfo == moduleType.labelAttribute)
            {
                m_labelText = GetAttribute<string>(moduleType.labelAttribute);
                UpdateTitleText();
            }
            else if (e.AttributeInfo == moduleType.nameAttribute)
            {
                m_nameText = GetAttribute<string>(moduleType.nameAttribute);
                UpdateTitleText();
            }
        }

        string GetBaseNameFor(ChildInfo childInfo, DomNode child)
        {
            string socketName = childInfo.Name;
            //var nameInfo = child.Type.GetAttributeInfo("Name");
            //if (nameInfo != null)
            //{
            //    var name = child.GetAttribute(nameInfo) as string;
            //    if (!string.IsNullOrEmpty(name))
            //        socketName = name;
            //}
            return socketName;
        }

        protected override void OnNodeSet()
        {
            base.OnNodeSet();

            if(string.IsNullOrEmpty(GetAttribute<string>(moduleType.labelAttribute)))
                SetAttribute(moduleType.labelAttribute, GetAttribute<string>(moduleType.nameAttribute));

            // Pull image icon image from node definition
            var nodeDef = DomNode.Type.GetTag<SF.Tong.Schema.NodeTypeInfo>();
            m_Image = string.IsNullOrEmpty(nodeDef.Icon) ? null : ResourceUtil.GetImage32(nodeDef.Icon);

            // Create non-string child classes
            if (DomNode.Children != null)
            {
                foreach (var childInfo in DomNode.Type.Children)
                {
                    if (childInfo.IsList) continue;
                    if (DomNode.GetChild(childInfo) != null) continue;

                    var newChild = new DomNode(childInfo.Type);
                    DomNode.SetChild(childInfo, newChild);
                }
            }

            // Add sockets for attributes
            if (DomNode.Type.Attributes != null)
            {
                foreach (var attrInfo in DomNode.Type.Attributes)
                {
                    var attrRule = attrInfo.GetRule<GameDataAttributeRule>();
                    if (attrRule == null || attrRule.SchemaProperty == null) continue;

                    switch (attrRule.SchemaProperty.Socket)
                    {
                        case SF.Tong.Schema.SocketType.Input:
                            m_Inputs.Add(new ElementType.Pin(attrInfo.Name, attrInfo.Type, m_Inputs.Count, allowFanIn:attrRule.SchemaProperty.AllowMultipleInput));
                            break;
                        case SF.Tong.Schema.SocketType.Output:
                            m_Outputs.Add(new ElementType.Pin(attrInfo.Name, attrInfo.Type, m_Outputs.Count, allowFanOut: attrRule.SchemaProperty.AllowMultipleOutput));
                            break;
                        case SF.Tong.Schema.SocketType.InOut:
                            m_Inputs.Add(new ElementType.Pin(attrInfo.Name, attrInfo.Type, m_Inputs.Count, allowFanIn: attrRule.SchemaProperty.AllowMultipleInput));
                            m_Outputs.Add(new ElementType.Pin(attrInfo.Name, attrInfo.Type, m_Outputs.Count, allowFanOut: attrRule.SchemaProperty.AllowMultipleOutput));
                            break;
                        default:
                            break;
                    }
                }
            }


            // Create child sockets
            if (DomNode.Children != null)
            {
                foreach (var child in DomNode.Children)
                {
                    if (child.ChildInfo.Type != socketType.Type) continue;

                    string socketName = GetBaseNameFor(child.ChildInfo, child);

                    // Only output can vary
                    var newPin = new ElementType.Pin(socketName, AttributeType.BooleanType, m_Outputs.Count);
                    m_Outputs.Add(newPin);

                }
            }


            // Update socket as new a child node is added
            DomNode.ChildInserted += (sender, args) =>
            {
                if (DomNode != args.Parent) return;

                if(args.ChildInfo.Type == socketType.Type)
                {
                    string socketName = GetBaseNameFor(args.ChildInfo, args.Child);

                    // Only output can vary
                    var newPin = new ElementType.Pin(socketName, AttributeType.BooleanType, m_Outputs.Count);
                    m_Outputs.Add(newPin);
                }
            };

            // Update socket as new a child node is removed
            DomNode.ChildRemoved += (sender, args) =>
            {
                if (DomNode != args.Parent) return;

                if (args.ChildInfo.Type == socketType.Type)
                {
                    string socketName = GetBaseNameFor(args.ChildInfo, args.Child);

                    // Only output can vary
                    int iSocket = 0;
                    for (; iSocket < m_Outputs.Count; iSocket++)
                    {
                        var output = m_Outputs[iSocket];
                        if (output.Name == socketName)
                        {
                            m_Outputs.RemoveAt(iSocket);
                            break;
                        }
                    }

                    // fix up index
                    for (; iSocket < m_Outputs.Count; iSocket++)
                    {
                        var output = m_Outputs[iSocket];
                        output.Index = iSocket;
                    }
                }
            };

            // For title text
            UpdateTitleText();

            DomNode.AttributeChanged += OnAttributeChanged;
        }



        void UpdateTitleText()
        {
            m_labelText = GetAttribute<string>(moduleType.labelAttribute);
            m_nameText = GetAttribute<string>(moduleType.nameAttribute);
            m_cachedTitleText = m_labelText;// string.Format("{0}:{1}", m_labelText, m_nameText);
        }

        private string m_labelText;
        private string m_nameText;
        private string m_cachedTitleText;

        Image m_Image;

        PinList<ICircuitPin> m_Inputs = new PinList<ICircuitPin>();
        PinList<ICircuitPin> m_Outputs = new PinList<ICircuitPin>();
    }
}

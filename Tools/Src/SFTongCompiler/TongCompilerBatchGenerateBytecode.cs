////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong compiler task - generate bytecode
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;
using Sce.Atf.Dom;

using SF.Tong;
using SF.Tong.Schema;
using SF.Tool;

using BytecodeGenContext = SFTongCompiler.TongCompilerContext.BytecodeGenContext;

namespace SFTongCompiler
{
    [Export(typeof(TongCompilerBatchGenerateBytecode))]
    [Export(typeof(IBatchTask))]
    class TongCompilerBatchGenerateBytecode : IBatchTask
    {
        public override int Priority => 3;

        delegate void delByteCodeHandler(BytecodeGenContext context, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks);
        private Dictionary<string, delByteCodeHandler> m_ByteCodeGen = new Dictionary<string, delByteCodeHandler>();

        delegate void delNodeHandler(TongCompilerContext.DocumentContext docContext, ScriptNode scriptNode);
        private Dictionary<string, delNodeHandler> m_NodeHandler = new Dictionary<string, delNodeHandler>();

        static TongCompilerBatchGenerateBytecode()
        {
        }


        [ImportingConstructor]
        public TongCompilerBatchGenerateBytecode(IBatchTaskManager manager)
            : base(manager)
        {
            m_ByteCodeGen.Add("boolean", BuildByteCode_AppendBooleanPin);
            m_ByteCodeGen.Add("decimal", BuildByteCode_AppendDecimalPin);
            m_ByteCodeGen.Add("float", BuildByteCode_AppendFloatPin);
            m_ByteCodeGen.Add("double", BuildByteCode_AppendDoublePin);
            m_ByteCodeGen.Add("int", BuildByteCode_AppendIntPin);

            m_NodeHandler.Add("Interface", CompileInterface);
            m_NodeHandler.Add("TaskStart", CompileTask);

        }

        /// <summary>
        /// Execute the task
        /// </summary>
        public override void Execute()
        {
            if (m_compileContext.DocumentContexts == null || m_compileContext.DocumentContexts.Count == 0)
                return;

            foreach (var docContext in m_compileContext.DocumentContexts)
            {
                try
                {
                    CompileDocument(docContext);
                }
                catch(Exception exp)
                {
                    Outputs.WriteLine(OutputMessageType.Error, "Failed to compiling {0}, error:{1}", docContext.ScriptDocument.GetPathName(), exp.Message);
                    throw exp;
                }
            }
        }

        public void CompileDocument(TongCompilerContext.DocumentContext docContext)
        {
            var scriptObjects = docContext.ScriptDocument.As<TongScriptObjectTable>();
            var scriptObjectMap = scriptObjects.NodeMap;

            // Find interface nodes
            foreach(var obj in scriptObjectMap)
            {
                delNodeHandler nodeHandler = null;
                var nodeDefInfo = obj.Value.DomNode.Type.GetTag<SF.Tong.Schema.NodeTypeInfo>();
                var curNodeDefInfo = nodeDefInfo;
                // Search hierarchy for the handler
                for (; curNodeDefInfo != null; curNodeDefInfo = curNodeDefInfo.Parent)
                {
                    if (m_NodeHandler.TryGetValue(curNodeDefInfo.Name, out nodeHandler))
                        break;
                }

                if (nodeHandler != null)
                {
                    nodeHandler(docContext, obj.Value);
                }
                else
                {
                    throw new Exception("Don't know how to handle:" + nodeDefInfo.Name);
                }

            }
        }


        IList<ScriptNodeConnection> GetSignalOutputs(ScriptNodeLinkCache link)
        {
            return link.FromThisNode.Where(x => x.OutputPin.TypeName == "Signal").ToList();
        }

        PropertyType ToPropertyType(NameString typeName)
        {
            PropertyType res;
            Enum.TryParse<PropertyType>(typeName.ToString(), out res);
            return res;
        }


        void BuildByteCode_AppendBooleanPin(BytecodeGenContext byteCodeContext, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
            if(samePinLinks.Count != 1)
                throw new Exception("Invalid link count for " + inputPin.Name);

            var connection = samePinLinks[0];
            var outElement = connection.OutputElement;
            var outLinkCache = outElement.As<ScriptNodeLinkCache>();
        }

        void BuildByteCode_AppendFloatPin(BytecodeGenContext byteCodeContext, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendDoublePin(BytecodeGenContext byteCodeContext, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendDecimalPin(BytecodeGenContext byteCodeContext, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendIntPin(BytecodeGenContext byteCodeContext, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendPropertyValueLoad(BytecodeGenContext byteCodeContext, DomNode node, ICircuitPin inputPin)
        {
            var attrInfo = node.Type.GetAttributeInfo(inputPin.Name.ToString());
            var value = node.GetAttribute(attrInfo);
            if(value == null)
            {
                byteCodeContext.Builder.AppendLoadI(0);
                return;
            }

            switch(attrInfo.Type.Name)
            {
                case "boolean":
                    byteCodeContext.Builder.AppendLoadI((bool)value ? 1 : 0);
                    break;
                case "decimal":
                    decimal decVal = (decimal)value;
                    if((decVal - (Int64)decVal) != 0)
                        byteCodeContext.Builder.AppendLoadF((float)decVal);
                    else
                        byteCodeContext.Builder.AppendLoadI((int)decVal);
                    break;
                case "double":
                    double dblVal = (double)value;
                    if ((dblVal - (Int64)dblVal) != 0)
                        byteCodeContext.Builder.AppendLoadF((float)dblVal);
                    else
                        byteCodeContext.Builder.AppendLoadI((int)dblVal);
                    break;
                case "float":
                    float fltVal = (float)value;
                    if ((fltVal - (Int64)fltVal) != 0)
                        byteCodeContext.Builder.AppendLoadF(fltVal);
                    else
                        byteCodeContext.Builder.AppendLoadI((int)fltVal);
                    break;
                case "int":
                    byteCodeContext.Builder.AppendLoadI((int)value);
                    break;
                case "string":
                    byteCodeContext.Builder.AppendLoadString((string)value);
                    break;
                default:
                    throw new Exception("Not supported load bytecode type:" + attrInfo.Type.Name);
            }
        }

        // DFS traversal based bytecode gen
        void BuildByteCode(BytecodeGenContext byteCodeContext, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
            if (samePinLinks == null || samePinLinks.Count == 0) // if nothing linked just take constant
            {
                var node = linkCache.As<ScriptNode>();
                BuildByteCode_AppendPropertyValueLoad(byteCodeContext, node.DomNode, inputPin);
            }
            else
            {
                delByteCodeHandler byteCodeHandler;
                if (!m_ByteCodeGen.TryGetValue(inputPin.TypeName.ToString(), out byteCodeHandler))
                    throw new Exception("Bytecode handler not found for :" + inputPin.TypeName.ToString());

                byteCodeHandler(byteCodeContext, linkCache, inputPin, samePinLinks);
            }
            // 
        }

        // bytecode gen for all inputs of the node
        void BuildByteCodeForInput(BytecodeGenContext byteCodeContext, ScriptNodeConnection inputConn)
        {
            var node = inputConn.InputElement.As<ScriptNode>();
            var linkCache = node.As<ScriptNodeLinkCache>();
            // create a copy of links
            var allLinks = new List<ScriptNodeConnection>(linkCache.ToThisNode);
            // 
            foreach (var input in node.AllInputPins)
            {
                var samePinLinks = allLinks.Where(con => con.InputPin == input).ToList();
 
                // remove from processed pins
                if(samePinLinks != null)
                {
                    foreach (var inputProcessing in samePinLinks)
                        allLinks.Remove(inputProcessing);
                }

                var propertyType = ToPropertyType(input.TypeName);
                // we are handling this node, so other input signal has no meaning
                if (propertyType == PropertyType.Signal)
                {
                    //Outputs.WriteLine(OutputMessageType.Warning, "Multiple input signal type for {0}, ignoring", node.Id);
                    continue;
                }

                // build bytecode for the input DFS traversal
                BuildByteCode(byteCodeContext, linkCache, input, samePinLinks);
            }
        }

        void CompileInterface(TongCompilerContext.DocumentContext docContext, ScriptNode interfaceNode)
        {
            var linkCache = interfaceNode.As<ScriptNodeLinkCache>();
            var signalConnections = GetSignalOutputs(linkCache);

            if (signalConnections.Count == 0)
                return;

            // interface only allow single output
            if (signalConnections.Count > 1)
                return;

            BytecodeGenContext byteCodeGenContext = new BytecodeGenContext();
            BuildByteCodeForInput(byteCodeGenContext, signalConnections[0]);

            docContext.CompiledInterfaces.Add(byteCodeGenContext.Builder);
        }

        void CompileTask(TongCompilerContext.DocumentContext docContext, ScriptNode interfaceNode)
        {
            var linkCache = interfaceNode.As<ScriptNodeLinkCache>();
            foreach (var connection in linkCache.FromThisNode)
            {

            }

            docContext.CompiledInterfaces.Add(new object());
        }


        [Import(AllowDefault = false)]
        protected TongCompilerContext m_compileContext = null;

        [Import(AllowDefault = false)]
        protected ScriptNodeDefinitionManager m_nodeDefinitionManager = null;
    }
}

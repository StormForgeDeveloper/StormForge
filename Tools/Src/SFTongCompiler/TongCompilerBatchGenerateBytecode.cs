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


namespace SFTongCompiler
{
    [Export(typeof(TongCompilerBatchGenerateBytecode))]
    [Export(typeof(IBatchTask))]
    class TongCompilerBatchGenerateBytecode : IBatchTask
    {
        public override int Priority => 3;

        delegate void delByteCodeHandler(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks);
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


        void BuildByteCode_AppendBooleanPin(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
            if(samePinLinks.Count != 1)
                throw new Exception("Invalid link count for " + inputPin.Name);

            var connection = samePinLinks[0];
            var outElement = connection.OutputElement;
            var outLinkCache = outElement.As<ScriptNodeLinkCache>();
        }

        void BuildByteCode_AppendFloatPin(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendDoublePin(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendDecimalPin(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendIntPin(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
        }

        void BuildByteCode_AppendPropertyValueLoad(SF.Tong.Compiler.BytecodeBuilder byteCode, DomNode node, ICircuitPin inputPin)
        {
            var attrInfo = node.Type.GetAttributeInfo(inputPin.Name.ToString());
            var value = node.GetAttribute(attrInfo);
            if(value == null)
            {
                byteCode.AppendLoadI(0);
                return;
            }

            switch(attrInfo.Type.Name)
            {
                case "boolean":
                    byteCode.AppendLoadI((bool)value ? 1 : 0);
                    break;
                case "decimal":
                    decimal decVal = (decimal)value;
                    if((decVal - (Int64)decVal) != 0)
                        byteCode.AppendLoadF((float)decVal);
                    else
                        byteCode.AppendLoadI((int)decVal);
                    break;
                case "double":
                    double dblVal = (double)value;
                    if ((dblVal - (Int64)dblVal) != 0)
                        byteCode.AppendLoadF((float)dblVal);
                    else
                        byteCode.AppendLoadI((int)dblVal);
                    break;
                case "float":
                    float fltVal = (float)value;
                    if ((fltVal - (Int64)fltVal) != 0)
                        byteCode.AppendLoadF(fltVal);
                    else
                        byteCode.AppendLoadI((int)fltVal);
                    break;
                case "int":
                    byteCode.AppendLoadI((int)value);
                    break;
                case "string":
                    byteCode.AppendLoadString((string)value);
                    break;
                default:
                    throw new Exception("Not supported load bytecode type:" + attrInfo.Type.Name);
            }
        }

        // DFS traversal based bytecode gen
        void BuildByteCode(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin inputPin, IList<ScriptNodeConnection> samePinLinks)
        {
            if (samePinLinks == null || samePinLinks.Count == 0) // if nothing linked just take constant
            {
                var node = linkCache.As<ScriptNode>();
                BuildByteCode_AppendPropertyValueLoad(byteCode, node.DomNode, inputPin);
            }
            else
            {
                delByteCodeHandler byteCodeHandler;
                if (!m_ByteCodeGen.TryGetValue(inputPin.TypeName.ToString(), out byteCodeHandler))
                    throw new Exception("Bytecode handler not found for :" + inputPin.TypeName.ToString());

                byteCodeHandler(byteCode, linkCache, inputPin, samePinLinks);
            }
            // 
        }

        // bytecode gen for all inputs of the node
        void BuildByteCode(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNode node, ICircuitPin inputPin)
        {
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
                BuildByteCode(byteCode, linkCache, input, samePinLinks);
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

            var byteCode = new SF.Tong.Compiler.BytecodeBuilder();
            BuildByteCode(byteCode, signalConnections[0].InputElement.As<ScriptNode>(), signalConnections[0].InputPin);

            docContext.CompiledInterfaces.Add(new object());
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

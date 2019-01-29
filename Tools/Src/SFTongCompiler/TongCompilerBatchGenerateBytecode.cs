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

        [ImportingConstructor]
        public TongCompilerBatchGenerateBytecode(IBatchTaskManager manager)
            : base(manager)
        {
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
                var nodeDefInfo = obj.Value.DomNode.Type.GetTag<SF.Tong.Schema.NodeTypeInfo>();
                if (nodeDefInfo.IsA("Interface"))
                {
                    CompileInterface(docContext, obj.Value);
                }
                else if (nodeDefInfo.IsA("TaskStart"))
                {
                    CompileTask(docContext, obj.Value);
                }
            }
        }


        IList<ScriptNodeConnection> GetSignalOutputs(ScriptNodeLinkCache link)
        {
            return link.FromThis.Where(x => x.OutputPin.TypeName == "Signal").ToList();
        }

        PropertyType ToPropertyType(NameString typeName)
        {
            PropertyType res;
            Enum.TryParse<PropertyType>(typeName.ToString(), out res);
            return res;
        }

        void BuildByteCode_AppendValue(SF.Tong.Compiler.BytecodeBuilder byteCode, DomNode node, AttributeInfo attrInfo)
        {
            //attrInfo.Name
        }

        // DFS based bytecode gen
        void BuildByteCode(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNodeLinkCache linkCache, ICircuitPin input)
        {
            var allLink = linkCache.ToThis.Where(con => con.InputPin == input).ToList();
            if (allLink.Count == 0) // if nothing linked just take constant
            {
                var node = linkCache.As<ScriptNode>();
                var attrInfo = node.DomNode.Type.GetAttributeInfo(input.Name.ToString());
                BuildByteCode_AppendValue(byteCode, node.DomNode, attrInfo);
            }
            // 
        }

        // bytecode gen for all inputs of the node
        void BuildByteCode(SF.Tong.Compiler.BytecodeBuilder byteCode, ScriptNode node, ICircuitPin inputPin)
        {
            var linkCache = node.As<ScriptNodeLinkCache>();
            // 
            foreach(var input in node.AllInputPins)
            {
                var propertyType = ToPropertyType(input.TypeName);
                // we only accept one signal for regular bytecode generation
                // Other special case is task and state which works in different way
                if (propertyType == PropertyType.Signal)
                {
                    Outputs.WriteLine(OutputMessageType.Warning, "Multiple input signal type for {0}, ignoring", node.Id);
                    continue;
                }

                // build bytecode for the input
                BuildByteCode(byteCode, linkCache, input);
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
            foreach (var connection in linkCache.FromThis)
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

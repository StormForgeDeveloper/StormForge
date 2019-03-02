////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong compiler context
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
    [Export(typeof(TongCompilerContext))]
    class TongCompilerContext : IInitializable
    {
        public class DocumentContext
        {
            public ScriptDocument ScriptDocument;
            public List<object> CompiledInterfaces = new List<object>();
        }

        public List<DocumentContext> DocumentContexts { get; } = new List<DocumentContext>();


        public class BytecodeGenContext
        {
            public HashSet<ScriptNode> VisitedNodes { get; } = new HashSet<ScriptNode>();
            public List<ScriptNode> TraversalStack { get; } = new List<ScriptNode>();
            public SF.Tong.Compiler.BytecodeBuilder Builder { get; } = new SF.Tong.Compiler.BytecodeBuilder();
        }



        [ImportingConstructor]
        public TongCompilerContext()
        {
        }

        public void Initialize()
        {

        }
    }
}

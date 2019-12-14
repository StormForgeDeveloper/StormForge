////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong Script compiler type manager
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.ComponentModel;
using System.ComponentModel.Composition;
using System.Xml.Schema;

using Sce.Atf;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Dom;
using PropertyDescriptor = System.ComponentModel.PropertyDescriptor;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

using SF.Tong;
using SF.Tong.Schema;
using System.Xml;

namespace SFTongCompiler
{
    /// <summary>
    /// Loads the UI schema, registers data extensions on the DOM types and annotates
    /// the types with display information and PropertyDescriptors</summary>
    [Export(typeof(TongScriptTypeManager))]
    [Export(typeof(TongScriptCompilerTypeManager))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class TongScriptCompilerTypeManager : TongScriptTypeManager
    {
        /// <summary>Constructor that initialize the schema</summary>
        /// [ImportingConstructor]
        public TongScriptCompilerTypeManager()
        {
        }


        protected override void RegisterExtensions()
        {
            base.RegisterExtensions();
            // register extensions

            // decorate circuit type
            tongScriptType.Type.Define(new ExtensionInfo<TongScriptObjectTable>());

            moduleType.Type.Define(new ExtensionInfo<ScriptNodeLinkCache>());
            moduleType.Type.Define(new ExtensionInfo<ScriptGraphNode>());
        }

    }
}

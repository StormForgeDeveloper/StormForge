////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script Editor type manager
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

namespace SF.Tong.Editor
{
    /// <summary>
    /// Loads the UI schema, registers data extensions on the DOM types and annotates
    /// the types with display information and PropertyDescriptors</summary>
    [Export(typeof(TongScriptTypeManager))]
    [Export(typeof(TongScriptEditorTypeManager))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class TongScriptEditorTypeManager : TongScriptTypeManager
    {
        /// <summary>Constructor that initialize the schema</summary>
        /// [ImportingConstructor]
        public TongScriptEditorTypeManager()
        {
        }


        protected override void RegisterExtensions()
        {
            base.RegisterExtensions();
            // register extensions

            // decorate circuit document type
            tongScriptDocumentType.Type.Define(new ExtensionInfo<Editor.PrototypingContext>());        // document-wide prototype hierarchy
            tongScriptDocumentType.Type.Define(new ExtensionInfo<Editor.TemplatingContext>());         // document-wide template hierarchy
            tongScriptDocumentType.Type.Define(new ExtensionInfo<MultipleHistoryContext>());    // ties sub-context histories into document dirty bit


            // decorate circuit type
            tongScriptType.Type.Define(new ExtensionInfo<Editor.LayeringContext>());                   // circuit layer hierarchy
            tongScriptType.Type.Define(new ExtensionInfo<Editor.PrintableDocument>());                 // printing
            tongScriptType.Type.Define(new ExtensionInfo<GlobalHistoryContext>());


            // decorate group type
            groupType.Type.Define(new ExtensionInfo<TongScriptEditingContext>());                    // main editable circuit adapter

            tongScriptType.Type.Define(new ExtensionInfo<TongScriptEditingContext>()); // main editable circuit adapter

            tongScriptDocumentType.Type.SetTag(TongScriptEditor.EditorInfo);
        }

    }
}

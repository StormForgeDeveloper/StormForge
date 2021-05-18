////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node type manager
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

using SF.Tong.Schema;
using System.Xml;

namespace SF.Tong
{
    /// <summary>
    /// Loads the UI schema, registers data extensions on the DOM types and annotates
    /// the types with display information and PropertyDescriptors</summary>
    [Export(typeof(TongScriptTypeManager))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class TongScriptTypeManager
    {
        public static readonly string NameSpaceName = "Tong";

        /// <summary>Constructor that initialize the schema</summary>
        /// [ImportingConstructor]
        public TongScriptTypeManager()
        {
            var nameSpaces = new XmlQualifiedName[] {
                    new XmlQualifiedName(NameSpaceName, "http://www.blue3k.com/")
                };

            m_typeCollection = new XmlSchemaTypeCollection(
                nameSpaces,
                NameSpaceName,
                new DomNodeTypeCollection(NameSpaceName)
            );
            m_version = new Version("1.0");// string.IsNullOrEmpty(version) ? new Version("1.0") : new Version(version);

            m_ChildInfoOfTheRoot = new ChildInfo(NameSpaceName, tongScriptDocumentType.Type);

            Initialize();
        }

        public XmlSchemaTypeCollection TypeCollection => m_typeCollection;

        public DomNodeTypeCollection DomNodeTypeCollection => m_typeCollection.DomNodeTypeCollection;

        public ChildInfo ChildInfoOfTheRoot => m_ChildInfoOfTheRoot;

        /// <summary>
        /// Gets the schema version</summary>
        public Version Version
        {
            get { return m_version; }
        }
        private Version m_version;

        /// <summary>
        /// Method called after the schema set has been loaded and the DomNodeTypes have been created, but
        /// before the DomNodeTypes have been frozen. This means that DomNodeType.SetIdAttribute, for example, has
        /// not been called on the DomNodeTypes. Is called shortly before OnDomNodeTypesFrozen.
        /// Defines DOM adapters for types. Create PropertyDescriptors for types to use in property editors.</summary>
        protected virtual void Initialize()
        {
            RegisterTypes();

            RegisterExtensions();

            // types are initialized, register property descriptors on module, folder types
            moduleType.Type.SetTag(
                new PropertyDescriptorCollection(
                    new PropertyDescriptor[] {
                        new AttributePropertyDescriptor(
                            "Name".Localize(),
                            moduleType.labelAttribute, // 'nameAttribute' is unique id, label is user visible name
                            null,
                            "Module name".Localize(),
                            false),
                        new AttributePropertyDescriptor(
                            "ID".Localize(),
                            moduleType.nameAttribute, // 'nameAttribute' is unique id, label is user visible name
                            null,
                            "Unique ID".Localize(),
                            true),
                        new AttributePropertyDescriptor(
                            "X".Localize(),
                            moduleType.xAttribute, 
                            null,
                            "location x".Localize(),
                            false),
                        new AttributePropertyDescriptor(
                            "Y".Localize(),
                            moduleType.yAttribute, 
                            null,
                            "location Y".Localize(),
                            false),

                }));

            layerFolderType.Type.SetTag(
                new PropertyDescriptorCollection(
                    new PropertyDescriptor[] {
                        new AttributePropertyDescriptor(
                            "Name".Localize(),
                            layerFolderType.nameAttribute,
                            null,
                            "Layer name".Localize(),
                            false)
                }));

            prototypeFolderType.Type.SetTag(
                new PropertyDescriptorCollection(
                    new PropertyDescriptor[] {
                        new AttributePropertyDescriptor(
                            "Name".Localize(),
                            prototypeFolderType.nameAttribute,
                            null,
                            "Prototype folder name".Localize(),
                            false)
                }));           
        } 

        void RegisterType(DomNodeType nodeType)
        {
            var xmlName = string.Format("{0}:{1}", NameSpaceName, nodeType.Name);
            DomNodeTypeCollection.AddNodeType(xmlName, nodeType);
            DomNodeTypeCollection.AddNodeType(xmlName, nodeType);
        }

        protected virtual void RegisterTypes()
        {
            RegisterType(tongScriptDocumentType.Type);
            RegisterType(tongScriptType.Type);
            RegisterType(moduleType.Type);
            RegisterType(groupType.Type);
            RegisterType(connectionType.Type);
            RegisterType(expressionType.Type);
            RegisterType(socketType.Type);
            RegisterType(groupSocketType.Type);
            RegisterType(prototypeFolderType.Type);
            RegisterType(prototypeType.Type);
            RegisterType(layerFolderType.Type);
            RegisterType(moduleRefType.Type);
            RegisterType(annotationType.Type);
            RegisterType(tongScriptType.Type);
            RegisterType(templateFolderType.Type);
            RegisterType(templateType.Type);
            RegisterType(moduleTemplateRefType.Type);
            RegisterType(groupTemplateRefType.Type);
            RegisterType(missingModuleType.Type);
            RegisterType(moduleTemplateRefType.Type);
            RegisterType(moduleTemplateRefType.Type);
            RegisterType(moduleTemplateRefType.Type);
        }

        protected virtual void RegisterExtensions()
        {
            // register extensions

            // decorate circuit document type
            tongScriptDocumentType.Type.Define(new ExtensionInfo<ScriptDocument>());                  // document info
            tongScriptDocumentType.Type.Define(new ExtensionInfo<Sce.Atf.Dom.CategoryUniqueIdValidator>());   // ensures all ids are local unique in its category
            tongScriptDocumentType.Type.Define(new ExtensionInfo<ScriptValidator>());          // validate group hierarchy
            tongScriptDocumentType.Type.Define(new ExtensionInfo<ReferenceValidator>());        // tracks references and targets

            // decorate circuit type
            tongScriptType.Type.Define(new ExtensionInfo<ViewingContext>());                    // manages module and circuit bounds, efficient layout
            tongScriptType.Type.Define(new ExtensionInfo<ExpressionManager>());                 // printing

            // decorate group type
            groupType.Type.Define(new ExtensionInfo<ScriptGroup>());
            groupType.Type.Define(new ExtensionInfo<ViewingContext>());

            connectionType.Type.Define(new ExtensionInfo<WireStyleProvider<ScriptNode, ScriptNodeConnection, ICircuitPin>>());

            // register Expression.
            expressionType.Type.Define(new ExtensionInfo<Expression>());

            // adapts the default implementation  of circuit types
            moduleType.Type.Define(new ExtensionInfo<ScriptNode>());
            moduleType.Type.Define(new ExtensionInfo<ScriptNodeProperties>());
            connectionType.Type.Define(new ExtensionInfo<ScriptNodeConnection>());
            socketType.Type.Define(new ExtensionInfo<ScriptNodeSocket>());
            groupSocketType.Type.Define(new ExtensionInfo<ScriptGroupSocket>());
            prototypeFolderType.Type.Define(new ExtensionInfo<ScriptPrototypeFolder>());
            prototypeType.Type.Define(new ExtensionInfo<ScriptPrototype>());
            layerFolderType.Type.Define(new ExtensionInfo<ScriptLayerFolder>());
            moduleRefType.Type.Define(new ExtensionInfo<ScriptNodeRef>());
            annotationType.Type.Define(new ExtensionInfo<ScriptAnnotation>());
            tongScriptType.Type.Define(new ExtensionInfo<TongScript>());

            templateFolderType.Type.Define(new ExtensionInfo<ScriptTemplateFolder>());
            templateType.Type.Define(new ExtensionInfo<ScriptTemplate>());
            moduleTemplateRefType.Type.Define(new ExtensionInfo<ScriptNodeReference>());
            groupTemplateRefType.Type.Define(new ExtensionInfo<ScriptGroupReference>());
            missingModuleType.Type.Define(new ExtensionInfo<MissingScriptNode >());
        }


        private XmlSchemaTypeCollection m_typeCollection;
        private ChildInfo m_ChildInfoOfTheRoot;
    }
}

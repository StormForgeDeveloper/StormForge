////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script type
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;

using Sce.Atf;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong.Schema
{
    public static class tongScriptDocumentType
    {
            static tongScriptDocumentType()
            {
                Type = new DomNodeType("tongScriptDocumentType", tongScriptType.Type);
                versionAttribute = Type.DefineNewAttributeInfo("version", AttributeType.StringType, "0.1");
                moduleChild = Type.DefineNewChildInfo("module", moduleType.Type, true);
                connectionChild = Type.DefineNewChildInfo("connection", connectionType.Type, true);
                layerFolderChild = Type.DefineNewChildInfo("layerFolder", layerFolderType.Type, true);
                expressionChild = Type.DefineNewChildInfo("expression", expressionType.Type, true);
                annotationChild = Type.DefineNewChildInfo("annotation", annotationType.Type, true);
                prototypeFolderChild = Type.DefineNewChildInfo("prototypeFolder", prototypeFolderType.Type, false);
                templateFolderChild = Type.DefineNewChildInfo("templateFolder", templateFolderType.Type, false);

                Type.SetTag(new System.ComponentModel.PropertyDescriptorCollection(new PropertyDescriptor[] {
                        new AttributePropertyDescriptor("version".Localize(), versionAttribute, null, "version".Localize(), false, null, null ),
                    }));

            }

            public static DomNodeType Type;
            public static AttributeInfo versionAttribute;
            public static ChildInfo moduleChild;
            public static ChildInfo connectionChild;
            public static ChildInfo layerFolderChild;
            public static ChildInfo expressionChild;
            public static ChildInfo annotationChild;
            public static ChildInfo prototypeFolderChild;
            public static ChildInfo templateFolderChild;
        }

        public static class tongScriptType
    {
            static tongScriptType()
            {
                Type = new DomNodeType("visualScriptType", moduleType.Type);
                moduleChild = Type.DefineNewChildInfo("module", moduleType.Type, true);
                connectionChild = Type.DefineNewChildInfo("connection", connectionType.Type, true);
                layerFolderChild = Type.DefineNewChildInfo("layerFolder", layerFolderType.Type, true);
                expressionChild = Type.DefineNewChildInfo("expression", expressionType.Type, true);
                annotationChild = Type.DefineNewChildInfo("annotation", annotationType.Type, true);
            }

            public static DomNodeType Type;
            public static ChildInfo moduleChild;
            public static ChildInfo connectionChild;
            public static ChildInfo layerFolderChild;
            public static ChildInfo expressionChild;
            public static ChildInfo annotationChild;
        }

}

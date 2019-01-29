////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script script writer
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;

using Sce.Atf.Adaptation;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    /// <summary>
    /// This custom writer only writes out the sub-circuits that are actually referenced 
    /// by a SubCircuitInstance</summary>
    public class ScriptWriter : DomXmlWriter
    {
        public ScriptWriter(XmlSchemaTypeCollection typeCollection)
            : base(typeCollection)
        {
            PreserveSimpleElements = true;
        }   

        protected override void WriteChildElementsRecursive(DomNode node, XmlWriter writer)
        {
            // Filter out external template file references that should not be in-lined
            if (node.Is<TemplateFolder>())
            {
                var pathUri = node.GetAttribute(templateFolderType.referenceFileAttribute) as Uri;
                if (pathUri != null)
                    return;
            }
            base.WriteChildElementsRecursive(node, writer);
        }

		protected override string Convert(DomNode node, AttributeInfo attributeInfo)
		{
			object value = node.GetAttribute(attributeInfo);
			if (attributeInfo.Type.Type == AttributeTypes.Reference && attributeInfo.Name == "guidRef")
			{
				// guidRef refers a template whose guid value should be persisted
				var templateNode = value as DomNode;
				return templateNode.GetAttribute(templateType.guidAttribute) as string;
			}

			return base.Convert(node, attributeInfo);
		}

     }

}

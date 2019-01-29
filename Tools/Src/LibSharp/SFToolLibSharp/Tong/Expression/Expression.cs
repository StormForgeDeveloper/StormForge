////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script expression
//
////////////////////////////////////////////////////////////////////////////////



using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Sce.Atf;
using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;


namespace SF.Tong
{

    /// <summary>
    /// DomNode adapter for expression element</summary>
    public class Expression : DomNodeAdapter
    {
        protected override void OnNodeSet()
        {
            if (!expressionType.Type.IsAssignableFrom(DomNode.Type))
                throw new Exception("can be attached only to DomNode of type expressionType");
        }


        public string Label
        {
            get { return GetAttribute<string>(expressionType.labelAttribute); }
            set { SetAttribute(expressionType.labelAttribute, value); }

        }

        public string Id
        {
            get { return GetAttribute<string>(expressionType.idAttribute); }
            set
            {
                string id = value ?? "Expression";
                SetAttribute(expressionType.idAttribute, id);
            }
        }


        public string Script
        {
            get { return GetAttribute<string>(expressionType.scriptAttribute); }
            set
            {
                string script = value ?? string.Empty;
                SetAttribute(expressionType.scriptAttribute, script);
            }
        }

    }
}

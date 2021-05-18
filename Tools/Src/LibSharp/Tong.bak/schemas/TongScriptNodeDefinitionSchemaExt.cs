////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node definition file schema
//
////////////////////////////////////////////////////////////////////////////////



using SF.Tong;

namespace SF.Tong.Schema
{
    using Sce.Atf.Dom;
    using System.Collections.Generic;
    using System.Runtime.Serialization;
    using System.Xml.Serialization;
    using SF.Tong;

    public partial class Node
    {
        List<ScriptNodeSocket> m_SocketList = new List<ScriptNodeSocket>();

        public List<ScriptNodeSocket> GetSocketList()
        {
            return m_SocketList;
        }
    }

    public partial class EnumTypeInfo
    {
        [System.Xml.Serialization.XmlIgnore]
        public string DefinitionFile { get; set; }

        [System.Xml.Serialization.XmlIgnore]
        public AttributeType SingleValueType { get; set; }

        [System.Xml.Serialization.XmlIgnore]
        public AttributeType ArrayValueType { get; set; }

        [System.Xml.Serialization.XmlIgnore]
        public StringEnumRule EnumRule { get; set; }
    }

    public partial class ObjectTypeInfo
    {
        [System.Xml.Serialization.XmlIgnore]
        public string DefinitionFile { get; set; }

    }

    public partial class NodeTypeInfo
    {
        [System.Xml.Serialization.XmlIgnore]
        public NodeTypeInfo Parent { get; set; }

        [System.Xml.Serialization.XmlIgnore]
        public string NodeDefinitionFile { get; set; }

        // Check type
        public bool IsA(string typeName)
        {
            if (Name == typeName)
                return true;

            if (Parent != null)
                return Parent.IsA(typeName);

            return false;
        }
    }


}



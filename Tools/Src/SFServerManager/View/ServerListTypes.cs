////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.ComponentModel.Composition;
using System.Windows.Forms;

using Sce.Atf;
using Sce.Atf.Applications;
using Sce.Atf.Controls;
using Sce.Atf.Dom;
using Sce.Atf.Adaptation;
using System.Collections.Generic;
using System.ComponentModel;

namespace SFServerManager
{


    // Server instance 
    static class ServerInstanceTreeType
    {
        static ServerInstanceTreeType()
        {
            Type.Define(NameAttribute);
            Type.Define(new ExtensionInfo<ServerListAdapter>());             // Support tree view editor
            Type.Define(ChildNodeInfo);
        }


        public readonly static DomNodeType Type = new DomNodeType("ServerInstanceTreeType");

        public readonly static AttributeInfo NameAttribute = new AttributeInfo("Name", new AttributeType(AttributeTypes.String.ToString(), typeof(string)));

        public readonly static ChildInfo ChildNodeInfo = new ChildInfo("ChildItems", ServerInstanceType.Type, true);
    }


    /// <summary>
    /// ServerInstance type adapter
    /// </summary>
    class ServerInstance : DomNodeAdapter
    {

        public UInt32 UID
        {
            get { return GetAttribute<UInt32>(ServerInstanceType.UIDAttribute); }
            set { SetAttribute(ServerInstanceType.UIDAttribute, value); }
        }

        public string Name
        {
            get { return GetAttribute<string>(ServerInstanceType.NameAttribute); }
            set { SetAttribute(ServerInstanceType.NameAttribute, value); }
        }

        public string Status
        {
            get { return GetAttribute<string>(ServerInstanceType.StatusAttribute); }
            set { SetAttribute(ServerInstanceType.StatusAttribute, value); }
        }

    }

    /// <summary>
    /// Server instance type
    /// </summary>
    static class ServerInstanceType
    {
        static ServerInstanceType()
        {
            Type.Define(NameAttribute);
            Type.Define(UIDAttribute);
            Type.Define(StatusAttribute);
            Type.Define(new ExtensionInfo<ServerInstance>());

            Type.SetTag(new PropertyDescriptorCollection(new Sce.Atf.Dom.PropertyDescriptor[] {
                        // Hide ID
                        new AttributePropertyDescriptor(
                            "UID".Localize(),
                            UIDAttribute,
                            null,
                            "UID".Localize(),
                            true),
                        new AttributePropertyDescriptor(
                            "Name".Localize(),
                            NameAttribute,
                            null,
                            "Name".Localize(),
                            true),
                        new AttributePropertyDescriptor(
                            "Status".Localize(),
                            StatusAttribute,
                            null,
                            "Status".Localize(),
                            true),
                        }));

        }


        public readonly static DomNodeType Type = new DomNodeType("ServerInstanceType");

        public readonly static AttributeInfo NameAttribute = new AttributeInfo("Name", new AttributeType(AttributeTypes.String.ToString(), typeof(string)));
        public readonly static AttributeInfo UIDAttribute = new AttributeInfo("UID", new AttributeType(AttributeTypes.UInt32.ToString(), typeof(UInt64)));
        public readonly static AttributeInfo StatusAttribute = new AttributeInfo("Status", new AttributeType(AttributeTypes.String.ToString(), typeof(string)));

    }


}


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
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.ComponentModel;

using Sce.Atf.Perforce;
using Sce.Atf;
using Sce.Atf.Applications;
using Sce.Atf.Controls;
using Sce.Atf.Dom;
using Sce.Atf.Adaptation;

using SF;
using System.Runtime.Serialization.Json;
using System.Runtime.Serialization;
using System.IO;

namespace SFServerManager
{


    class ServerListAdapter : TreeViewDataAdapter
    {
        public static readonly string SERVER_INSTANCES_PATH = "/BRServices/ServerInstances";

        public override ChildInfo ChildListInfo { get { return ServerInstanceTreeType.ChildNodeInfo; } }
        

        private static readonly TreeListViewColumnInfo[] m_ColumnNames = new TreeListViewColumnInfo[]
        {
            new TreeListViewColumnInfo() { Name = "UID",                 DefaultWidth = 100,    BindAttributes = new string[]{ "UID" } },
            //new TreeListViewColumnInfo() { Name = "Name",                DefaultWidth = 100,    BindAttributes = new string[]{ "Name" } },
            new TreeListViewColumnInfo() { Name = "Status",              DefaultWidth = 100,    BindAttributes = new string[]{ "Status" } },
        };

        override public TreeListViewColumnInfo[] ListViewColumnInfos
        {
            get { return m_ColumnNames; }
        }




        /// <summary>
        /// ZooKeeper Server instance info
        /// </summary>
        [DataContract]
        class ServerInstanceInfo
        {
            /// <summary>
            /// Server instance name
            /// </summary>
            [DataMember]
            public string ServiceName = null;

            /// <summary>
            /// IPAddress
            /// </summary>
            [DataMember]
            public string IPAddress = null;

            /// <summary>
            /// Process ID
            /// </summary>
            [DataMember]
            public uint ProcessID = 0;
        }


        public IList<DomNode> GetServerNodeList()
        {
            return DomNode.GetChildList(ServerInstanceTreeType.ChildNodeInfo);
        }

        public void RefreshServerList(SFZooKeeper zooKeeper, SFServerConfig serverConfig)
        {
            var childList = DomNode.GetChildList(ServerInstanceTreeType.ChildNodeInfo);
            var alreadyExist = new Dictionary<string, ServerInstance>();
            foreach(var serverNode in childList)
            {
                var serverInstance = serverNode.As<ServerInstance>();

                alreadyExist.Add(serverInstance.Name, serverInstance);
            }

            var activeInstances = new Dictionary<string, ServerInstanceInfo>();
            var activeInstanceChildren = zooKeeper.GetChildren(SERVER_INSTANCES_PATH, watch:true);
            foreach(var child in activeInstanceChildren)
            {
                var childPath = string.Format("{0}/{1}", SERVER_INSTANCES_PATH, child);
                var childValue = zooKeeper.Get(childPath);
                if(childValue == null)
                    continue;

                MemoryStream ms = new MemoryStream(Encoding.UTF8.GetBytes(childValue));
                DataContractJsonSerializer ser = new DataContractJsonSerializer(typeof(ServerInstanceInfo));
                var instanceInfo = ser.ReadObject(ms) as ServerInstanceInfo;

                activeInstances.Add(instanceInfo.ServiceName, instanceInfo);
            }

            serverConfig.ForEachServer((SFServerConfig.GenericServer server) =>
            {
                var serverInstanceName = server.Name;
                ServerInstance instance;
                if(alreadyExist.TryGetValue(serverInstanceName, out instance))
                {
                    alreadyExist.Remove(serverInstanceName);
                }
                else
                {
                    instance = (new DomNode(ServerInstanceType.Type)).As<ServerInstance>();
                    instance.Name = serverInstanceName;
                    instance.UID = server.UID;
                    childList.Add(instance.DomNode);
                }

                instance.Status = activeInstances.ContainsKey(serverInstanceName) ? "Active" : "Down";

            });
            
            // Remove remain server instances, they will be added by previous list
            foreach(var remain in alreadyExist)
            {
                childList.Remove(remain.Value.DomNode);
            }

            Selection = new object[] { };
        }
    }
}

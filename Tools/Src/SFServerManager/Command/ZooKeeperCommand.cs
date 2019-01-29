////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Zookeeper command helper
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.Composition;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Dom;

using SF;
using System.Runtime.Serialization;
using System.IO;
using System.Runtime.Serialization.Json;

namespace SFServerManager.Command
{

    public class ZooKeeperCommand
    {

        /// <summary>
        /// ZooKeeper command base
        /// </summary>
        [DataContract]
        class ZKCommandBase
        {
            /// <summary>
            /// Command Name
            /// </summary>
            [DataMember]
            public string Command;

            /// <summary>
            /// Specify target machine who will going to receive this command
            /// </summary>
            [DataMember]
            public string IPAddress;

            /// <summary>
            /// Specify target machine who will going to receive this command
            /// </summary>
            [DataMember]
            public long TimeStamp = DateTime.Now.Ticks;
        }

        /// <summary>
        /// ZooKeeper command Reload config
        /// </summary>
        [DataContract]
        class ZKReloadConfig : ZKCommandBase
        {
        }


        /// <summary>
        /// ZooKeeper command Start server instance
        /// </summary>
        [DataContract]
        class ZKStartServerInstance : ZKCommandBase
        {
            /// <summary>
            /// Server instance name to start
            /// </summary>
            [DataMember]
            public string ServerInstanceName;

            /// <summary>
            /// Server module name(executable name) to start
            /// </summary>
            [DataMember]
            public string ServerExecutionModule;

            /// <summary>
            /// Module path
            /// </summary>
            [DataMember]
            public string ModulePath;
        }


        /// <summary>
        /// ZooKeeper command Stop server instance
        /// </summary>
        [DataContract]
        class ZKStopServerInstance : ZKCommandBase
        {
            /// <summary>
            /// Server instance name to stop
            /// </summary>
            [DataMember]
            public string ServerInstanceName;
        }


        /// <summary>
        /// ZooKeeper command Restart server instance
        /// </summary>
        [DataContract]
        class ZKRestartServerInstance : ZKStartServerInstance
        {
        }




        static public string ReloadConfig(string ipAddress)
        {
            var valueObject = new ZKReloadConfig()
            {
                Command = "ReloadConfig",
                IPAddress = ipAddress,
            };

            using (MemoryStream stream1 = new MemoryStream())
            {
                DataContractJsonSerializer ser = new DataContractJsonSerializer(valueObject.GetType());
                ser.WriteObject(stream1, valueObject);

                return Encoding.UTF8.GetString(stream1.GetBuffer());
            }
        }

        static public string StartServerInstance(string ipAddress, string serverName, string serverExecutionModule, string modulePath)
        {
            var valueObject = new ZKStartServerInstance()
            {
                Command = "StartServerInstance",
                IPAddress = ipAddress,
                ServerInstanceName = serverName,
                ServerExecutionModule = serverExecutionModule,
                ModulePath = modulePath,

            };

            using (MemoryStream stream1 = new MemoryStream())
            {
                DataContractJsonSerializer ser = new DataContractJsonSerializer(valueObject.GetType());
                ser.WriteObject(stream1, valueObject);

                return Encoding.UTF8.GetString(stream1.GetBuffer());
            }
        }

        static public string StopServerInstance(string ipAddress, string serverName)
        {
            var valueObject = new ZKStopServerInstance()
            {
                Command = "StopServerInstance",
                IPAddress = ipAddress,
                ServerInstanceName = serverName,

            };

            using (MemoryStream stream1 = new MemoryStream())
            {
                DataContractJsonSerializer ser = new DataContractJsonSerializer(valueObject.GetType());
                ser.WriteObject(stream1, valueObject);

                return Encoding.UTF8.GetString(stream1.GetBuffer());
            }
        }

        static public string RestartServerInstance(string ipAddress, string serverName, string serverExecutionModule)
        {
            var valueObject = new ZKStartServerInstance()
            {
                Command = "RestartServerInstance",
                IPAddress = ipAddress,
                ServerInstanceName = serverName,
                ServerExecutionModule = serverExecutionModule,

            };

            using (MemoryStream stream1 = new MemoryStream())
            {
                DataContractJsonSerializer ser = new DataContractJsonSerializer(valueObject.GetType());
                ser.WriteObject(stream1, valueObject);

                return Encoding.UTF8.GetString(stream1.GetBuffer());
            }
        }


    }

}

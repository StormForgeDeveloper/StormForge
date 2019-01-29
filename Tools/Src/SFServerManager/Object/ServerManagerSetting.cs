////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server manager setting
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf;
using Sce.Atf.Applications;
using Sce.Atf.Controls.PropertyEditing;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Net;

namespace SFServerManager
{

    [Export(typeof(IInitializable))]
    [Export(typeof(ServerManagerSetting))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class ServerManagerSetting : IInitializable
    {
        const string DefaultConfigFilePath = "ServerConfig_StressTest.xml";

        List<string> m_XMLPaths = new List<string>();
        public List<string> XMLPaths { get { return m_XMLPaths; } set { m_XMLPaths = value; } }

        string m_ConnectionString = "127.0.0.1:2181";
        public string ConnectionString { get { return m_ConnectionString; }
            set
            {
                if(IsValidIP(value))
                    m_ConnectionString = value;
            }
        }


        public static bool IsValidIP(string Address)
        {
            System.Net.IPAddress ip;

            bool success = IPAddress.TryParse(Address.Split(':')[0], out ip);
            if (!success)
                return false;

            switch (ip.AddressFamily)
            {
                case System.Net.Sockets.AddressFamily.InterNetwork:
                    if (Address.Length > 6 && Address.Contains("."))
                    {
                        string[] s = Address.Split('.');
                        if (s.Length == 4 && s[0].Length > 0 && s[1].Length > 0 && s[2].Length > 0 && s[3].Length > 0)
                            return true;
                    }
                    break;
                case System.Net.Sockets.AddressFamily.InterNetworkV6:
                    if (Address.Contains(":") && Address.Length > 15)
                        return true;
                    break;
                default:
                    break;
            }

            return false;
        }

        string m_ConfigNodePath = "/ServerConfig";
        public string ConfigNodePath { get { return m_ConfigNodePath; } set { m_ConfigNodePath = value; } }

        string m_CommandNodePath = "/BRServerCommand";
        public string CommandNodePath { get { return m_CommandNodePath; } set { m_CommandNodePath = value; } }

        string m_ModulePath = "x64Debug";
        public string ModulePath { get { return m_ModulePath; } set { m_ModulePath = value; } }

        [ImportingConstructor]
        public ServerManagerSetting(ISettingsService settingService)
        {
            m_SettingService = settingService;

        }

        public void Initialize() 
        {

            if (m_SettingService != null)
            {
                var settings = new[]
                {
                  new BoundPropertyDescriptor(this, () => XMLPaths,
                        "XMLPaths".Localize(), 
                        "ServerManager".Localize(),
                        "XML config paths".Localize()),
                    new BoundPropertyDescriptor(this, () => ConnectionString,
                        "ConnectionString".Localize(), 
                        "ServerManager".Localize(),
                        "ZooKeeper ConnectionString such as 127.0.0.1:2181".Localize()),
                    new BoundPropertyDescriptor(this, () => ConfigNodePath,
                        "ConfigNodePath".Localize(), 
                        "ServerManager".Localize(),
                        "ZooKeeper Config node path".Localize()),
                    new BoundPropertyDescriptor(this, () => CommandNodePath,
                        "CommandNodePath".Localize(),
                        "ServerManager".Localize(),
                        "ZooKeeper command node path".Localize()),
                    new BoundPropertyDescriptor(this, () => ModulePath,
                        "ModulePath".Localize(),
                        "ServerManager".Localize(),
                        "Executable module path".Localize()),
                };
                m_SettingService.RegisterUserSettings("ServerManager", settings);
                m_SettingService.RegisterSettings(this, settings);
            }
        }

        



        ISettingsService m_SettingService = null;
    }


}

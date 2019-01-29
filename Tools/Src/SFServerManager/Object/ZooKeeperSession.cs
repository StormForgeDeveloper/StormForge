////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : ZooKeeper session
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Controls.PropertyEditing;
using SF;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace SFServerManager
{

    /// <summary>
    /// Zookeeper main connection section manager
    /// </summary>
    [Export(typeof(IInitializable))]
    [Export(typeof(ZooKeeperSession))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class ZooKeeperSession : IInitializable
    {
        public SFZooKeeper ZKInstance {  get { return m_zkInstance; } }
        public SFServerConfig ServerConfig { get { return m_ServerConfig; } }


        [ImportingConstructor]
        public ZooKeeperSession()
        {
        }

        public void Initialize() 
        {
            m_zkInstance = new SFZooKeeper();
            m_Timer = new Timer(OnTimer, this, 1000, 1000);
        }

        void OnTimer(object state)
        {
            if (m_Setting == null || string.IsNullOrEmpty(m_Setting.ConnectionString))
                return;

            if (!m_zkInstance.IsConnected())
            {
                if(m_zkInstance.GetState() != SFZooKeeper.STATE_CONNECTING)
                    m_zkInstance.Connect(m_Setting.ConnectionString);
                return;
            }

            if (m_ServerConfig == null)
            {
                m_ServerConfig = new SFServerConfig();
                m_ServerConfig.LoadZooKeeper(m_zkInstance, m_Setting.ConfigNodePath);
                RefreshServerList();
            }

            SFZooKeeper.ZKEvent zkEvent;

            while(m_zkInstance.DequeueEvent(out zkEvent))
            {
                if(zkEvent.EventType == SFZooKeeper.EVENT_CHILD)
                {
                    // It should be server list for now
                    RefreshServerList();
                }
            }
        }

        void RefreshServerList()
        {
            var serverListAdapter = m_ServerInstanceView.TreeView.As<ServerListAdapter>();
            if (serverListAdapter == null)
                return;

            m_ServerInstanceView.TreeControl.InvokeIfRequired(() =>
            {
                serverListAdapter.RefreshServerList(m_zkInstance, m_ServerConfig);
            });
        }


        SFServerConfig m_ServerConfig;
        SFZooKeeper m_zkInstance;

        Timer m_Timer;

        [Import(AllowDefault = false)]
        private ServerConfigUploadView m_ServerInstanceView = null;

        [Import(AllowDefault =false)]
        ServerManagerSetting m_Setting = null;
    }


}
